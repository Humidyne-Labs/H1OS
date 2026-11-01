#!/usr/bin/env python3
"""
H1OS Dedicated Serial Monitor & Telemetry Console (h1os_monitor)
Version: 1.4.1
License: Apache-2.0

High-performance, beautifully styled serial monitor for ESP32-S3 firmware development.
Features:
- Pinned static header panel with zero vertical scroll drift.
- Fully framed, rounded telemetry viewport (box.ROUNDED) matching h1os_menu aesthetics.
- Flicker-free native Rich rendering with throttled refresh (no strobe or line-clearing artifacts).
- Full mouse scroll wheel support in terminal (native Windows Console API + VT SGR sequences).
- Keyboard-driven interactive scrollback (PageUp/PageDown, Up/Down, Home/End).
- Intelligent ESP-IDF, LVGL, and ROM bootloader log parsing into colored pills, aligned uptime, and module tags.
- Zero scrollback pollution during deep sleep (in-place status spinner with elapsed time in the header).
- Dynamic millisecond timestamps toggled on-the-fly (key 'T', default: OFF).
- Dual live Rich console display + pristine ANSI-stripped plain-text disk logging (key 'L', default: OFF).
- Hardware reset on demand (key 'R') using the proven Windows usbser.sys DTR/RTS sequence.
- Clean buffer erase on clear (key 'C').
- Auto-reconnect on deep-sleep wake with zero DTR/RTS glitching.
"""

import argparse
import datetime
import os
import re
import sys
import threading
import time
import uuid
from collections import deque
from pathlib import Path
from typing import Deque, List, Optional

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("[ERROR] pyserial is required. Install via 'pip install pyserial'.", file=sys.stderr)
    sys.exit(1)

try:
    from rich import box
    from rich.console import Console
    from rich.layout import Layout
    from rich.live import Live
    from rich.panel import Panel
    from rich.table import Table
    from rich.text import Text
except ImportError:
    print("[ERROR] rich is required. Install via 'pip install rich'.", file=sys.stderr)
    sys.exit(1)

# Windows Console API structures for native mouse and keyboard input
if os.name == "nt":
    import ctypes
    from ctypes import wintypes

    class COORD(ctypes.Structure):
        _fields_ = [("X", wintypes.SHORT), ("Y", wintypes.SHORT)]

    class KEY_EVENT_RECORD(ctypes.Structure):
        _fields_ = [
            ("bKeyDown", wintypes.BOOL),
            ("wRepeatCount", wintypes.WORD),
            ("wVirtualKeyCode", wintypes.WORD),
            ("wVirtualScanCode", wintypes.WORD),
            ("UnicodeChar", wintypes.WCHAR),
            ("dwControlKeyState", wintypes.DWORD),
        ]

    class MOUSE_EVENT_RECORD(ctypes.Structure):
        _fields_ = [
            ("dwMousePosition", COORD),
            ("dwButtonState", wintypes.DWORD),
            ("dwControlKeyState", wintypes.DWORD),
            ("dwEventFlags", wintypes.DWORD),
        ]

    class EVENT_UNION(ctypes.Union):
        _fields_ = [
            ("KeyEvent", KEY_EVENT_RECORD),
            ("MouseEvent", MOUSE_EVENT_RECORD),
        ]

    class INPUT_RECORD(ctypes.Structure):
        _fields_ = [
            ("EventType", wintypes.WORD),
            ("Event", EVENT_UNION),
        ]


# Regex to strip ANSI escape codes for clean disk logging
ANSI_ESCAPE_RE = re.compile(r"\x1b\[[0-9;]*[a-zA-Z]")

# Pattern matchers for ESP-IDF, LVGL, and ROM bootloader logging protocols
ESP_LOG_RE = re.compile(r"^([EWIDV])\s*\(([0-9]+)\)\s*([a-zA-Z0-9_.\-/]+):\s*(.*)$")
LVGL_LOG_RE = re.compile(r"^\[(Info|Warn|Error|Trace|User)\]\s*\(([0-9.]+,\s*[+\-0-9]+)\)\s*([a-zA-Z0-9_]+):\s*(.*)$")
ROM_PREFIXES = ("ESP-ROM:", "Build:", "rst:", "Saved PC:", "SPIWP:", "mode:", "load:", "entry ")
SGR_MOUSE_RE = re.compile(r"\x1b\[<(\d+);(\d+);(\d+)([Mm])")

SPINNER_FRAMES = ["⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"]

# Known H1OS component module colors
TAG_STYLES = {
    "h1os_lvgl": "bold bright_cyan",
    "h1os_demo": "bold cyan",
    "h1os_lifecycle": "bold magenta",
    "h1os_main": "bold bright_white",
    "orch_flow": "bold bright_green",
    "orch_display_sync": "bold green",
    "orch_math": "bold green",
    "sub_display": "bold bright_yellow",
    "sub_power": "bold yellow",
    "sub_audio": "bold bright_magenta",
    "sub_sdcard": "bold blue",
    "sub_rtc": "bold cyan",
    "sub_nvs": "bold bright_blue",
    "hal_io": "bold white",
    "hal_i2c": "bold white",
    "main_task": "dim white",
    "boot": "bold white",
    "boot.esp32s3": "bold white",
}


def set_rts_with_windows_quirk(port: serial.Serial, state: bool) -> None:
    """Set RTS pin state with the Windows usbser.sys CDC workaround."""
    port.setRTS(state)
    # Windows usbser.sys only flushes SET_CONTROL_LINE_STATE when both lines are touched
    port.setDTR(port.dtr)


def set_dtr_pin(port: serial.Serial, state: bool) -> None:
    """Set DTR pin state directly."""
    port.setDTR(state)


def execute_hardware_reset(port: serial.Serial, hold_delay: float = 0.2, settle_delay: float = 0.2) -> None:
    """Pulse EN line low for 200 ms to hard reset the ESP32-S3 cleanly."""
    try:
        from esp_pylib.serial_reset import hard_reset
        hard_reset(port, hold_delay=hold_delay, post_release_delay=settle_delay)
    except ImportError:
        # Fallback implementation of Espressif's proven hard_reset
        set_dtr_pin(port, False)  # IO0 = HIGH
        set_rts_with_windows_quirk(port, True)  # EN = LOW (reset asserted)
        time.sleep(hold_delay)
        set_rts_with_windows_quirk(port, False)  # EN = HIGH (reset released)
        if settle_delay:
            time.sleep(settle_delay)


def auto_detect_serial_port() -> Optional[str]:
    """Auto-detect connected ESP or active serial port without resetting target."""
    try:
        ports = list(serial.tools.list_ports.comports())
        if not ports:
            return None
        # Prioritize Espressif USB-JTAG / USB CDC / UART bridges
        for p in ports:
            desc = (p.description or "").lower()
            hwid = (p.hwid or "").lower()
            mfg = (p.manufacturer or "").lower()
            if "303a" in hwid or "espressif" in desc or "espressif" in mfg:
                return p.device
            if any(k in desc or k in hwid for k in ("jtag", "usb serial", "uart", "ch340", "cp210", "ftdi")):
                return p.device
        # Exclude legacy motherboard COM1 if other ports exist
        non_com1 = [p.device for p in ports if p.device.upper() != "COM1"]
        if non_com1:
            return non_com1[0]
        return ports[0].device
    except Exception:
        return None


class LogEntry:
    """Structured telemetry log record preserving timestamp and inline badge state."""

    def __init__(
        self,
        raw: str,
        ts: Optional[datetime.datetime] = None,
        is_badge: bool = False,
        badge_tag: str = "",
        badge_msg: str = "",
        badge_color: str = "cyan",
    ):
        self.raw = raw
        self.ts = ts or datetime.datetime.now()
        self.is_badge = is_badge
        self.badge_tag = badge_tag
        self.badge_msg = badge_msg
        self.badge_color = badge_color


class H1OSMonitor:
    """High-performance, flicker-free bordered serial monitor with mouse scroll support."""

    def __init__(
        self,
        port: Optional[str] = None,
        baud: int = 115200,
        chip: str = "esp32s3",
        enable_timestamps: bool = False,
        enable_logging: bool = False,
        log_dir: Optional[Path] = None,
    ):
        self.port = port
        self.baud = baud
        self.chip = chip
        self.enable_timestamps = enable_timestamps
        self.enable_logging = enable_logging
        self.log_dir = log_dir or Path.cwd() / "logs"

        self.session_uid = str(uuid.uuid4())
        self.ser: Optional[serial.Serial] = None
        self.running = True
        self.log_file = None
        self.log_path: Optional[Path] = None

        self.history: Deque[LogEntry] = deque(maxlen=5000)
        self.scroll_offset = 0  # 0 = live at bottom, >0 = scrolled up N lines
        self.lock = threading.Lock()
        self.dirty = True

        self.console = Console(highlight=False)
        self.layout = Layout()
        self.layout.split(
            Layout(name="header", size=5),
            Layout(name="body"),
        )

        self.live: Optional[Live] = None
        self.last_status_text = "[bold green]ONLINE[/]"

        if self.enable_logging:
            self._open_log_file()

    def _open_log_file(self):
        """Open or rotate session disk log with authoritative metadata header."""
        self.log_dir.mkdir(parents=True, exist_ok=True)
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        short_uid = self.session_uid[:8]
        filename = f"monitor_{timestamp}_{short_uid}.log"
        self.log_path = self.log_dir / filename

        self.log_file = open(self.log_path, "w", encoding="utf-8", buffering=1)
        now_str = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        header = [
            "# ==============================================================================\n",
            "# H1OS Serial Session Log\n",
            f"# Session UID : {self.session_uid}\n",
            f"# Start Date  : {now_str}\n",
            f"# Target Port : {self.port or 'auto-detect'} @ {self.baud} baud\n",
            f"# Target Chip : {self.chip.upper()}\n",
            "# ==============================================================================\n\n",
        ]
        self.log_file.writelines(header)
        self.log_file.flush()

    def _close_log_file(self):
        """Flush and close active session log file."""
        if self.log_file and not self.log_file.closed:
            self.log_file.flush()
            self.log_file.close()
        self.log_file = None

    def _add_badge_entry(self, tag: str, message: str, color: str = "cyan"):
        """Append an inline system badge entry to telemetry history."""
        with self.lock:
            self.history.append(
                LogEntry(
                    raw=f"[{tag}] {message}",
                    is_badge=True,
                    badge_tag=tag,
                    badge_msg=message,
                    badge_color=color,
                )
            )
            self.dirty = True
        self.update_display()

    def toggle_logging(self):
        """Toggle disk logging on/off interactively."""
        self.enable_logging = not self.enable_logging
        if self.enable_logging:
            self._open_log_file()
            self._add_badge_entry("LOGGING", f"Active session recording to [bold white]{self.log_path.name if self.log_path else 'log'}[/]", "green")
        else:
            saved_name = self.log_path.name if self.log_path else "log"
            self._close_log_file()
            self._add_badge_entry("LOGGING", f"Session saved and closed [dim]({saved_name})[/]", "yellow")
        self._update_window_title()

    def toggle_timestamps(self):
        """Toggle millisecond timestamps on/off dynamically across all visible lines."""
        self.enable_timestamps = not self.enable_timestamps
        state_str = "ENABLED" if self.enable_timestamps else "DISABLED"
        color = "cyan" if self.enable_timestamps else "yellow"
        self._add_badge_entry("TIMESTAMPS", f"Millisecond timestamps {state_str}.", color)
        self._update_window_title()

    def clear_screen(self):
        """Erase scrollback buffer while preserving the static header frame."""
        with self.lock:
            self.history.clear()
            self.scroll_offset = 0
            self.dirty = True
        self._add_badge_entry("CLEARED", "Telemetry buffer erased.", "cyan")

    def trigger_hardware_reset(self):
        """Pulse DTR/RTS lines to perform a clean hardware reset on ESP32-S3."""
        if not self.ser or not self.ser.is_open:
            self._add_badge_entry("RESET", "Cannot reset: Serial port not open.", "red")
            return

        try:
            self._add_badge_entry("RESET", "Pulsing EN low for 200 ms via DTR/RTS...", "yellow")
            execute_hardware_reset(self.ser, hold_delay=0.2, settle_delay=0.2)
        except (serial.SerialException, OSError):
            # Native USB-Serial-JTAG drops connection immediately upon reset assertion
            if self.ser:
                try:
                    self.ser.close()
                except Exception:
                    pass
            self.ser = None
            self._add_badge_entry("RESET", "Target reset triggered (device re-enumerating)...", "yellow")
        except Exception as e:
            self._add_badge_entry("RESET", f"Hardware reset failed: {e}", "red")

    def scroll_up(self, count: int = 1):
        """Scroll history up towards older lines."""
        with self.lock:
            max_offset = max(0, len(self.history) - 3)
            self.scroll_offset = min(max_offset, self.scroll_offset + count)
            self.dirty = True
        self.update_display()

    def scroll_down(self, count: int = 1):
        """Scroll history down towards latest lines."""
        with self.lock:
            self.scroll_offset = max(0, self.scroll_offset - count)
            self.dirty = True
        self.update_display()

    def scroll_page_up(self):
        """Scroll history up by one full screen page."""
        vis = max(3, (self.console.size.height or 25) - 7)
        self.scroll_up(vis)

    def scroll_page_down(self):
        """Scroll history down by one full screen page."""
        vis = max(3, (self.console.size.height or 25) - 7)
        self.scroll_down(vis)

    def scroll_home(self):
        """Jump to the very beginning of the history buffer."""
        with self.lock:
            self.scroll_offset = max(0, len(self.history) - 3)
            self.dirty = True
        self.update_display()

    def scroll_end(self):
        """Jump to the bottom and resume live auto-scrolling."""
        with self.lock:
            self.scroll_offset = 0
            self.dirty = True
        self.update_display()

    def _update_window_title(self):
        """Keep the console window title bar synchronized with live session state."""
        port_label = self.port or "Auto-detect"
        ts_state = "ON" if self.enable_timestamps else "OFF"
        log_state = f"ON ({self.log_path.name})" if (self.enable_logging and self.log_path) else "OFF"

        title_str = (
            f"H1OS Monitor: {port_label} @ {self.baud} | "
            f"Chip: {self.chip.upper()} | "
            f"Time: {ts_state} | "
            f"Log: {log_state} | "
            f"[R] Reset [T] Time [L] Log [C] Clear [Q] Quit"
        )
        sys.stdout.write(f"\033]0;{title_str}\007")
        sys.stdout.flush()

    def _highlight_metrics(self, msg: str) -> Text:
        """Highlight hex numbers, milliseconds, and measurements in log messages."""
        t = Text()
        pattern = re.compile(r"(0x[0-9a-fA-F]+|[0-9.]+\s*(?:ms|Hz|%|C|KB|MB|MHz)|ESP_[A-Z_]+)")
        last_idx = 0
        for match in pattern.finditer(msg):
            start, end = match.span()
            if start > last_idx:
                t.append(msg[last_idx:start])
            val = match.group(0)
            if val.startswith("0x"):
                t.append(val, style="bold bright_yellow")
            elif "ESP_" in val:
                t.append(val, style="bold red" if ("TIMEOUT" in val or "FAIL" in val) else "bold yellow")
            else:
                t.append(val, style="bold cyan")
            last_idx = end
        if last_idx < len(msg):
            t.append(msg[last_idx:])
        return t

    def format_entry(self, entry: LogEntry) -> Text:
        """Parse structured entry and render into a beautifully styled Rich telemetry line."""
        text = Text()

        # 1. Optional Millisecond Timestamp: [HH:MM:SS.mmm]
        if self.enable_timestamps:
            ms_str = entry.ts.strftime("%H:%M:%S.%f")[:-3]
            text.append(f"{ms_str} ", style="dim cyan")

        # 2. Inline System Badge
        if entry.is_badge:
            text.append(f" {entry.badge_tag} ", style=f"bold black on {entry.badge_color}")
            text.append(" ")
            text.append_text(Text.from_markup(entry.badge_msg))
            return text

        clean = ANSI_ESCAPE_RE.sub("", entry.raw).rstrip("\r\n")

        # 3. Standard ESP-IDF Log Lines: e.g. "I (5418) h1os_lvgl: Button pressed"
        m_esp = ESP_LOG_RE.match(clean)
        if m_esp:
            lvl, tick, tag, msg = m_esp.groups()
            badge_style = {
                "E": "bold white on red",
                "W": "bold black on yellow",
                "I": "bold black on bright_green",
                "D": "dim cyan",
                "V": "dim bright_black",
            }.get(lvl, "dim")

            text.append(f" {lvl} ", style=badge_style)
            text.append(f" {tick:>5}ms ", style="dim")

            tag_style = TAG_STYLES.get(tag, "bold cyan")
            text.append(f"{tag:<18}", style=tag_style)
            text.append(": ", style="dim")
            text.append_text(self._highlight_metrics(msg))
            return text

        # 4. LVGL Log Lines: e.g. "[Info] (4.606, +3465) lv_label_create: begin"
        m_lvgl = LVGL_LOG_RE.match(clean)
        if m_lvgl:
            lvl, timing, fn, msg = m_lvgl.groups()
            text.append(" LVGL ", style="bold black on bright_cyan")
            text.append(f" {timing:<14} ", style="dim")
            text.append(f"{fn:<18}", style="dim white")
            text.append(": ", style="dim")
            text.append_text(self._highlight_metrics(msg))
            return text

        # 5. ESP ROM Bootloader Lines
        if clean.startswith(ROM_PREFIXES):
            text.append(" ROM ", style="bold black on bright_yellow")
            text.append("           ")
            text.append_text(self._highlight_metrics(clean))
            return text

        # 6. Fallback for unformatted lines (dumps, psychrometric tables, boot banners)
        text.append("       ")
        text.append_text(Text.from_ansi(clean))
        return text

    def _build_header_panel(self, status_text: str) -> Panel:
        """Construct the static 5-row header panel."""
        port_label = self.port or "Auto-detect"
        ts_badge = "[bold green]ON[/]" if self.enable_timestamps else "[dim]OFF[/]"
        log_badge = f"[bold green]ACTIVE[/] [dim]({self.log_path.name})[/]" if (self.enable_logging and self.log_path) else "[dim]OFF[/]"

        log_dir_str = str(self.log_dir)
        if len(log_dir_str) > 28:
            log_dir_str = "..." + log_dir_str[-25:]

        header_table = Table.grid(padding=(0, 1), expand=True)
        header_table.add_column("K1", style="bold cyan", width=9)
        header_table.add_column("V1", ratio=1)
        header_table.add_column("K2", style="bold cyan", width=9)
        header_table.add_column("V2", ratio=1)

        header_table.add_row(
            "Target :", f"[bold white]{self.chip.upper()}[/]",
            "Status :", status_text,
        )
        header_table.add_row(
            "Serial :", f"[bold cyan]{port_label}[/] [dim]@{self.baud}[/]",
            "Log Dir:", f"[white]{log_dir_str}[/]",
        )
        header_table.add_row(
            "Time   :", f"{ts_badge} [dim](key 'T')[/]",
            "Logging:", f"{log_badge} [dim](key 'L')[/]",
        )

        return Panel(
            header_table,
            title="[bold white]H1OS Serial Monitor & Telemetry Console[/]",
            subtitle=f"[dim]UID: {self.session_uid[:8]}  |  [R] Reset  [C] Clear  [Q/Esc] Quit[/]",
            border_style="cyan",
            box=box.ROUNDED,
        )

    def _build_telemetry_panel(self) -> Panel:
        """Construct the bordered rounded telemetry stream panel with scroll navigation."""
        total_h = self.console.size.height or 25
        visible_count = max(3, total_h - 7)

        with self.lock:
            total_lines = len(self.history)
            if self.scroll_offset == 0:
                lines = list(self.history)[-visible_count:]
                subtitle = f"[dim]Scroll: Mouse Wheel / [PageUp/Down]  |  [End] Live Stream ({total_lines} lines)[/]"
            else:
                end_idx = max(0, total_lines - self.scroll_offset)
                start_idx = max(0, end_idx - visible_count)
                lines = list(self.history)[start_idx:end_idx]
                subtitle = f"[bold yellow]-- SCROLLBACK ({self.scroll_offset} lines above live) -- Press [End] for Live Stream[/]"

            body_text = Text()
            for entry in lines:
                body_text.append_text(self.format_entry(entry))
                body_text.append("\n")

        return Panel(
            body_text,
            title="[bold cyan]Telemetry Stream[/]",
            subtitle=subtitle,
            border_style="cyan",
            box=box.ROUNDED,
        )

    def update_display(self, status_text: Optional[str] = None):
        """Update live layout smoothly through Rich without line-clearing strobing."""
        if not self.live:
            return
        if status_text is not None:
            self.last_status_text = status_text
        st = self.last_status_text or "[bold green]ONLINE[/]"

        self.layout["header"].update(self._build_header_panel(st))
        self.layout["body"].update(self._build_telemetry_panel())
        self.live.update(self.layout, refresh=True)

    def run(self):
        """Main execution loop supervising serial streaming, deep sleep, and keyboard/mouse input."""
        self._update_window_title()

        # Input listener thread (handles mouse wheel, navigation keys, and hotkeys)
        in_thread = threading.Thread(target=self._input_listener, daemon=True)
        in_thread.start()

        line_buffer = bytearray()
        sleep_start_time: Optional[float] = None
        last_sec = -1
        last_render_time = 0.0

        with Live(self.layout, console=self.console, screen=True, auto_refresh=False) as live:
            self.live = live
            self.update_display("[bold green]ONLINE[/]")

            try:
                while self.running:
                    now = time.time()

                    # 1. Port Connection / Deep Sleep Supervisor
                    if self.ser is None or not self.ser.is_open:
                        target_port = self.port or auto_detect_serial_port()

                        if sleep_start_time is None:
                            sleep_start_time = now

                        elapsed_sec = int(now - sleep_start_time)
                        mins = elapsed_sec // 60
                        secs = elapsed_sec % 60
                        time_str = f"{mins:02d}m {secs:02d}s" if mins > 0 else f"{secs:02d}s"

                        # Update ONLY when the second changes (1 FPS clock tick) to completely eliminate flicker
                        if elapsed_sec != last_sec:
                            last_sec = elapsed_sec
                            port_label = target_port or "active port"
                            status_text = f"[bold yellow]SLEEPING ({time_str})[/] [dim]Listening on {port_label}...[/]"
                            self.update_display(status_text)
                            self.dirty = False

                        # Attempt to open port with DTR/RTS held LOW before connection (prevents hardware auto-reset)
                        if target_port:
                            try:
                                ser = serial.Serial()
                                ser.port = target_port
                                ser.baudrate = self.baud
                                ser.timeout = 0.05
                                ser.dsrdtr = False
                                ser.rtscts = False
                                # Configure control lines LOW before open() to ensure DCB disables DTR/RTS on creation
                                ser.dtr = False
                                ser.rts = False
                                ser.open()

                                # Confirm lines held low post-open
                                set_dtr_pin(ser, False)
                                set_rts_with_windows_quirk(ser, False)

                                self.ser = ser
                                self.port = target_port
                                self._add_badge_entry("ONLINE", f"Target connected on {self.port} [dim](slept {time_str})[/]", "green")
                                self._update_window_title()
                                sleep_start_time = None
                                last_sec = -1
                                line_buffer.clear()
                                self.update_display("[bold green]ONLINE[/]")
                                self.dirty = True
                            except (serial.SerialException, OSError) as exc:
                                self.ser = None
                                exc_msg = str(exc).lower()
                                if "access is denied" in exc_msg or "permissionerror" in exc_msg:
                                    status_text = f"[bold red]LOCKED (Access Denied)[/] [dim]Retrying {target_port}...[/]"
                                    self.update_display(status_text)

                        time.sleep(0.1)
                        continue

                    # 2. Read Serial Stream
                    try:
                        available = self.ser.in_waiting
                        if available > 0:
                            chunk = self.ser.read(available)
                            for b in chunk:
                                if b == ord("\n"):
                                    try:
                                        raw_line = line_buffer.decode("utf-8", errors="replace")
                                    except Exception:
                                        raw_line = line_buffer.decode("latin-1", errors="replace")
                                    line_buffer.clear()

                                    entry = LogEntry(raw=raw_line)
                                    with self.lock:
                                        self.history.append(entry)
                                        self.dirty = True

                                    # Persistent disk logging (ANSI stripped for clean plain text)
                                    if self.enable_logging and self.log_file:
                                        clean_for_log = ANSI_ESCAPE_RE.sub("", raw_line).rstrip("\r\n")
                                        if self.enable_timestamps:
                                            ms_str = entry.ts.strftime("%H:%M:%S.%f")[:-3]
                                            self.log_file.write(f"[{ms_str}] {clean_for_log}\n")
                                        else:
                                            self.log_file.write(f"{clean_for_log}\n")
                                        self.log_file.flush()

                                elif b != ord("\r"):
                                    line_buffer.append(b)

                        # Smooth, throttled 10 FPS batch refresh so high-speed serial doesn't strobe
                        if self.dirty and (now - last_render_time >= 0.080):
                            self.update_display("[bold green]ONLINE[/]")
                            last_render_time = now
                            self.dirty = False

                        if available == 0:
                            # Final drain update if data arrived
                            if self.dirty:
                                self.update_display("[bold green]ONLINE[/]")
                                last_render_time = now
                                self.dirty = False
                            time.sleep(0.01)

                    except (serial.SerialException, OSError):
                        # Target entered deep sleep and dropped USB serial PHY
                        if self.ser:
                            try:
                                self.ser.close()
                            except Exception:
                                pass
                        self.ser = None
                        sleep_start_time = time.time()
                        last_sec = -1
                        self._add_badge_entry("SUSPEND", "Target entered deep sleep / USB PHY power gated.", "yellow")
                        self._update_window_title()
                        self.update_display("[bold yellow]SLEEPING[/]")

            finally:
                self.live = None

    def _input_listener(self):
        """Cross-platform keyboard and mouse wheel input listener."""
        if os.name == "nt":
            self._input_listener_windows()
        else:
            self._input_listener_posix()

    def _input_listener_windows(self):
        """Listen for keyboard and mouse wheel events on Windows via Console API with msvcrt fallback."""
        kernel32 = ctypes.windll.kernel32
        GENERIC_READ = 0x80000000
        GENERIC_WRITE = 0x40000000

        # Open CONIN$ to guarantee true interactive console input handle
        h_in = kernel32.CreateFileW("CONIN$", GENERIC_READ | GENERIC_WRITE, 1 | 2, None, 3, 0, None)
        if h_in == -1:
            h_in = kernel32.GetStdHandle(-10)

        mode = wintypes.DWORD()
        has_console = kernel32.GetConsoleMode(h_in, ctypes.byref(mode)) != 0
        orig_mode = mode.value if has_console else 0

        if has_console:
            # Enable mouse input (0x0010) and extended flags (0x0080), disable quick edit (0x0040)
            # so mouse wheel and clicks are passed to our application instead of freezing console
            new_mode = (orig_mode | 0x0010 | 0x0080 | 0x0008) & ~0x0040
            kernel32.SetConsoleMode(h_in, new_mode)

        try:
            num_events = wintypes.DWORD()
            records = (INPUT_RECORD * 32)()
            read_count = wintypes.DWORD()

            while self.running:
                if has_console:
                    kernel32.GetNumberOfConsoleInputEvents(h_in, ctypes.byref(num_events))
                    if num_events.value > 0:
                        kernel32.ReadConsoleInputW(
                            h_in,
                            ctypes.byref(records),
                            min(32, num_events.value),
                            ctypes.byref(read_count),
                        )
                        for i in range(read_count.value):
                            rec = records[i]
                            # 1. KEY_EVENT
                            if rec.EventType == 0x0001 and rec.Event.KeyEvent.bKeyDown:
                                vk = rec.Event.KeyEvent.wVirtualKeyCode
                                ch = rec.Event.KeyEvent.UnicodeChar.lower()
                                if vk == 0x21:  # PageUp
                                    self.scroll_page_up()
                                elif vk == 0x22:  # PageDown
                                    self.scroll_page_down()
                                elif vk == 0x26:  # Up
                                    self.scroll_up(1)
                                elif vk == 0x28:  # Down
                                    self.scroll_down(1)
                                elif vk == 0x24:  # Home
                                    self.scroll_home()
                                elif vk == 0x23:  # End
                                    self.scroll_end()
                                elif ch in ("q", "\x1b", "\x03"):
                                    self.running = False
                                    break
                                elif ch == "r":
                                    self.trigger_hardware_reset()
                                elif ch == "t":
                                    self.toggle_timestamps()
                                elif ch == "l":
                                    self.toggle_logging()
                                elif ch == "c":
                                    self.clear_screen()
                                elif ch == "b":
                                    self.scroll_end()

                            # 2. MOUSE_EVENT (Wheel)
                            elif rec.EventType == 0x0002:
                                ev_flags = rec.Event.MouseEvent.dwEventFlags
                                # MOUSE_WHEELED is 0x0004
                                if ev_flags & 0x0004:
                                    delta = ctypes.c_int16(rec.Event.MouseEvent.dwButtonState >> 16).value
                                    if delta > 0:
                                        self.scroll_up(3)  # Scroll up 3 lines per notch
                                    elif delta < 0:
                                        self.scroll_down(3)  # Scroll down 3 lines per notch

                        continue
                time.sleep(0.02)
        finally:
            if has_console and orig_mode:
                kernel32.SetConsoleMode(h_in, orig_mode)
            if h_in != -1 and h_in != kernel32.GetStdHandle(-10):
                kernel32.CloseHandle(h_in)

    def _input_listener_posix(self):
        """Listen for keyboard and mouse wheel events on POSIX/VT terminals via stdin."""
        import select
        import termios
        import tty

        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setcbreak(fd)
            # Enable SGR mouse tracking in VT terminal
            sys.stdout.write("\x1b[?1000h\x1b[?1006h")
            sys.stdout.flush()

            while self.running:
                r, _, _ = select.select([sys.stdin], [], [], 0.02)
                if r:
                    ch = sys.stdin.read(1)
                    if ch == "\x1b":
                        # Check for escape sequences
                        seq = ""
                        while select.select([sys.stdin], [], [], 0.002)[0]:
                            seq += sys.stdin.read(1)

                        # Check for SGR mouse sequences: \x1b[<64;X;YM (Wheel Up) or \x1b[<65;X;YM (Wheel Down)
                        m_mouse = SGR_MOUSE_RE.match("\x1b" + seq)
                        if m_mouse:
                            btn = int(m_mouse.group(1))
                            if btn == 64:
                                self.scroll_up(3)
                            elif btn == 65:
                                self.scroll_down(3)
                            continue

                        if seq == "[A":
                            self.scroll_up(1)
                        elif seq == "[B":
                            self.scroll_down(1)
                        elif seq in ("[5~", "[I"):
                            self.scroll_page_up()
                        elif seq in ("[6~", "[G"):
                            self.scroll_page_down()
                        elif seq in ("[H", "[1~"):
                            self.scroll_home()
                        elif seq in ("[F", "[4~"):
                            self.scroll_end()
                        elif not seq:
                            self.running = False
                            break
                        continue

                    key = ch.lower()
                    if key in ("q", "\x03"):
                        self.running = False
                        break
                    elif key == "r":
                        self.trigger_hardware_reset()
                    elif key == "t":
                        self.toggle_timestamps()
                    elif key == "l":
                        self.toggle_logging()
                    elif key == "c":
                        self.clear_screen()
                    elif key == "b":
                        self.scroll_end()
        finally:
            # Disable SGR mouse tracking on exit
            sys.stdout.write("\x1b[?1000l\x1b[?1006l")
            sys.stdout.flush()
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)

    def close(self):
        """Clean shutdown and resource release."""
        self.running = False
        if self.ser and self.ser.is_open:
            try:
                self.ser.close()
            except Exception:
                pass
        self._close_log_file()
        self.console.print("\n[bold cyan]H1OS Serial Monitor closed.[/bold cyan]")


def main():
    parser = argparse.ArgumentParser(description="H1OS Dedicated Rich Serial Monitor & Telemetry Console")
    parser.add_argument("-p", "--port", type=str, default=None, help="Serial port (auto-detects if omitted)")
    parser.add_argument("-b", "--baud", type=int, default=115200, help="Baud rate (default: 115200)")
    parser.add_argument("--chip", type=str, default="esp32s3", help="Target chip (default: esp32s3)")
    parser.add_argument("-t", "--timestamps", action="store_true", help="Enable millisecond timestamps on startup (default: OFF)")
    parser.add_argument("-l", "--log", action="store_true", help="Enable file logging on startup (default: OFF)")
    parser.add_argument("--log-dir", type=str, default=None, help="Directory to save session logs")

    args = parser.parse_args()

    log_dir = Path(args.log_dir).resolve() if args.log_dir else None

    monitor = H1OSMonitor(
        port=args.port,
        baud=args.baud,
        chip=args.chip,
        enable_timestamps=args.timestamps,
        enable_logging=args.log,
        log_dir=log_dir,
    )

    try:
        monitor.run()
    except KeyboardInterrupt:
        pass
    finally:
        monitor.close()


if __name__ == "__main__":
    main()
