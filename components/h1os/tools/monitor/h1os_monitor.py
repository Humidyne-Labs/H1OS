#!/usr/bin/env python3
"""
H1OS Dedicated Serial Monitor & Telemetry Console (h1os_monitor)
Version: 1.2.0
License: Apache-2.0

High-performance, beautifully styled serial monitor for ESP32-S3 firmware development.
Features:
- Gorgeous Rich UI with rounded borders and columnar alignment inspired by Rich inspection panels.
- Intelligent ESP-IDF and LVGL log parser: converts raw tags into colored pills, aligned uptime, and module tags.
- Zero scrollback pollution during deep sleep (in-place status spinner with elapsed time).
- 100% millisecond-precision timestamps (toggled via 'T', default: OFF).
- Dual live Rich console display + pristine ANSI-stripped plain-text disk logging (toggled via 'L', default: OFF).
- Hardware reset on demand (key 'R') using the proven Windows usbser.sys DTR/RTS sequence.
- Native console blank on clear (key 'C').
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
from pathlib import Path
from typing import Optional

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    print("[ERROR] pyserial is required. Install via 'pip install pyserial'.", file=sys.stderr)
    sys.exit(1)

try:
    from rich import box
    from rich.console import Console
    from rich.panel import Panel
    from rich.table import Table
    from rich.text import Text
except ImportError:
    print("[ERROR] rich is required. Install via 'pip install rich'.", file=sys.stderr)
    sys.exit(1)

# Regex to strip ANSI escape codes for clean disk logging
ANSI_ESCAPE_RE = re.compile(r"\x1b\[[0-9;]*[a-zA-Z]")

# Pattern matchers for ESP-IDF and LVGL logging protocols
ESP_LOG_RE = re.compile(r"^([EWIDV])\s*\(([0-9]+)\)\s*([a-zA-Z0-9_]+):\s*(.*)$")
LVGL_LOG_RE = re.compile(r"^\[(Info|Warn|Error|Trace|User)\]\s*\(([0-9.]+,\s*[+\-0-9]+)\)\s*([a-zA-Z0-9_]+):\s*(.*)$")

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


class H1OSMonitor:
    """Zero-dot, dual-stream serial monitor with beautiful Rich formatting."""

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

        self.console = Console(highlight=False)

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

    def toggle_logging(self):
        """Toggle disk logging on/off interactively."""
        self.enable_logging = not self.enable_logging
        if self.enable_logging:
            self._open_log_file()
            self._print_badge("LOGGING", f"Active session recording to [bold white]{self.log_path.name if self.log_path else 'log'}[/]", "green")
        else:
            saved_name = self.log_path.name if self.log_path else "log"
            self._close_log_file()
            self._print_badge("LOGGING", f"Session saved and closed [dim]({saved_name})[/]", "yellow")
        self._update_window_title()

    def toggle_timestamps(self):
        """Toggle millisecond timestamps on/off interactively."""
        self.enable_timestamps = not self.enable_timestamps
        if self.enable_timestamps:
            self._print_badge("TIMESTAMPS", "Millisecond timestamps enabled [dim]([HH:MM:SS.mmm])[/]", "cyan")
        else:
            self._print_badge("TIMESTAMPS", "Timestamps disabled", "yellow")
        self._update_window_title()

    def trigger_hardware_reset(self):
        """Pulse DTR/RTS lines to perform a clean hardware reset on ESP32-S3."""
        if not self.ser or not self.ser.is_open:
            self._print_badge("RESET", "Cannot reset: Serial port not open.", "red")
            return

        try:
            self._print_badge("RESET", "Pulsing EN low for 200 ms via DTR/RTS...", "yellow")
            execute_hardware_reset(self.ser, hold_delay=0.2, settle_delay=0.2)
        except (serial.SerialException, OSError):
            # Native USB-Serial-JTAG drops connection immediately upon reset assertion
            if self.ser:
                try:
                    self.ser.close()
                except Exception:
                    pass
            self.ser = None
            self._print_badge("RESET", "Target reset triggered (device re-enumerating)...", "yellow")
        except Exception as e:
            self._print_badge("RESET", f"Hardware reset failed: {e}", "red")

    def _print_badge(self, tag: str, message: str, color: str = "cyan"):
        """Print a sleek inline badge notice."""
        t = Text()
        t.append(f" {tag} ", style=f"bold black on {color}")
        t.append(" ")
        t.append_text(Text.from_markup(message))
        self.console.print(t)

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

    def render_header_panel(self):
        """Render the primary Rich rounded panel banner."""
        port_label = self.port or "Auto-detect"
        ts_badge = "[bold green]ON[/]" if self.enable_timestamps else "[dim]OFF[/]"
        log_badge = f"[bold green]RECORDING[/] [dim]({self.log_path.name if self.log_path else ''})[/]" if (self.enable_logging and self.log_path) else "[dim]OFF[/]"
        status_badge = "[bold green]● ONLINE[/]" if (self.ser and self.ser.is_open) else "[bold yellow]⏳ SLEEPING[/]"

        grid = Table.grid(padding=(0, 2))
        grid.add_column()
        grid.add_column()
        grid.add_column()
        grid.add_column()

        grid.add_row(
            status_badge,
            f"[dim]Port:[/] [bold cyan]{port_label}[/] [dim]@{self.baud}[/]",
            f"[dim]Chip:[/] [bold bright_white]{self.chip.upper()}[/]",
            f"[dim]Log:[/] {log_badge}",
        )
        grid.add_row(
            "[dim]Keys:[/] [bold yellow]R[/] [dim]Reset[/]",
            f"[bold cyan]T[/] [dim]Time[/] ({ts_badge})",
            f"[bold green]L[/] [dim]Log[/] [dim]({self.log_dir.name}/)[/]",
            "[bold white]C[/] [dim]Clear[/]  •  [bold red]Q[/] [dim]Quit[/]",
        )

        p = Panel(
            grid,
            title="[bold bright_white]H1OS[/] [bold cyan]Serial Telemetry Console[/]",
            subtitle=f"[dim]Session UID: {self.session_uid[:8]}[/]",
            box=box.ROUNDED,
            border_style="bright_blue",
            padding=(0, 1),
        )
        self.console.print(p)
        self._update_window_title()

    def clear_screen(self):
        """Perform native console blank and redraw the header panel."""
        if os.name == "nt":
            os.system("cls")
        else:
            sys.stdout.write("\033[2J\033[H")
            sys.stdout.flush()
        self.render_header_panel()

    def format_log_line(self, raw_line: str) -> Text:
        """Parse raw serial line and convert into a styled Rich telemetry entry."""
        # 1. Strip raw ANSI sequences to extract unpolluted line text
        clean = ANSI_ESCAPE_RE.sub("", raw_line).rstrip("\r\n")
        text = Text()

        # Optional timestamp prefix
        if self.enable_timestamps:
            now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
            text.append(f"{now_ms} ", style="dim cyan")

        # 2. Match standard ESP-IDF log lines: e.g. "I (5418) h1os_lvgl: Button pressed"
        m_esp = ESP_LOG_RE.match(clean)
        if m_esp:
            lvl, tick, tag, msg = m_esp.groups()
            badge_text = f" {lvl} "
            badge_style = {
                "E": "bold white on red",
                "W": "bold black on yellow",
                "I": "bold black on bright_green",
                "D": "dim cyan",
                "V": "dim bright_black",
            }.get(lvl, "dim")

            text.append(badge_text, style=badge_style)
            text.append(f" {tick:>5}ms ", style="dim")

            tag_style = TAG_STYLES.get(tag, "bold cyan")
            text.append(f"{tag:<18}", style=tag_style)
            text.append(": ", style="dim")

            # Style numbers, hex, and key metrics in the message body
            msg_text = self._highlight_metrics(msg)
            text.append_text(msg_text)
            return text

        # 3. Match LVGL log lines: e.g. "[Info] (4.606, +3465) lv_label_create: begin"
        m_lvgl = LVGL_LOG_RE.match(clean)
        if m_lvgl:
            lvl, timing, fn, msg = m_lvgl.groups()
            text.append(" LVGL ", style="bold black on bright_cyan")
            text.append(f" {timing:<14} ", style="dim")
            text.append(f"{fn:<18}", style="dim white")
            text.append(": ", style="dim")
            text.append_text(self._highlight_metrics(msg))
            return text

        # 4. Fallback for unformatted system lines (bootloader, psychrometrics, dumps)
        text.append_text(Text.from_ansi(raw_line.rstrip("\r\n")))
        return text

    def _highlight_metrics(self, msg: str) -> Text:
        """Highlight hex numbers, milliseconds, and measurements in log messages."""
        t = Text()
        # Highlight hex (0x..), numbers with units (ms, Hz, %, C), and status codes
        pattern = re.compile(r"(0x[0-9a-fA-F]+|[0-9.]+\s*(?:ms|Hz|%|C|KB|MB)|ESP_[A-Z_]+)")
        last_idx = 0
        for match in pattern.finditer(msg):
            start, end = match.span()
            if start > last_idx:
                t.append(msg[last_idx:start])
            val = match.group(0)
            if val.startswith("0x"):
                t.append(val, style="bold bright_yellow")
            elif "ESP_" in val:
                t.append(val, style="bold red" if "TIMEOUT" in val or "FAIL" in val else "bold yellow")
            else:
                t.append(val, style="bold cyan")
            last_idx = end
        if last_idx < len(msg):
            t.append(msg[last_idx:])
        return t

    def run(self):
        """Main execution loop supervising serial streaming, deep sleep, and keyboard input."""
        self.clear_screen()

        # Keyboard polling thread
        kb_thread = threading.Thread(target=self._keyboard_listener, daemon=True)
        kb_thread.start()

        line_buffer = bytearray()
        sleep_start_time: Optional[float] = None
        spinner_idx = 0

        while self.running:
            # 1. Port Connection / Deep Sleep Supervisor
            if self.ser is None or not self.ser.is_open:
                target_port = self.port or auto_detect_serial_port()

                if sleep_start_time is None:
                    sleep_start_time = time.time()

                # Calculate elapsed time in sleep
                elapsed_sec = int(time.time() - sleep_start_time)
                mins = elapsed_sec // 60
                secs = elapsed_sec % 60
                time_str = f"{mins:02d}m {secs:02d}s" if mins > 0 else f"{secs:02d}s"

                # In-place spinner update (ZERO DOTS, NO SCROLL POLLUTION)
                spin_char = SPINNER_FRAMES[spinner_idx % len(SPINNER_FRAMES)]
                spinner_idx += 1

                port_label = target_port or "active port"
                status_msg = f"\r  {spin_char} Target in deep sleep (elapsed: {time_str}). Listening on {port_label}...   "
                sys.stdout.write(status_msg)
                sys.stdout.flush()

                # Attempt to open port with DTR/RTS held LOW (zero-reset)
                if target_port:
                    try:
                        self.ser = serial.Serial(
                            port=target_port,
                            baudrate=self.baud,
                            timeout=0.1,
                            dsrdtr=False,
                            rtscts=False,
                        )
                        # Explicitly hold lines low so MCU is not reset on connect
                        set_dtr_pin(self.ser, False)
                        set_rts_with_windows_quirk(self.ser, False)

                        # Clear in-place spinner line
                        sys.stdout.write("\r" + " " * 85 + "\r")
                        sys.stdout.flush()

                        self.port = target_port
                        reconn_msg = f"Target connected on {self.port} [dim](slept {time_str})[/]"
                        self._print_badge("ONLINE", reconn_msg, "green")
                        self._update_window_title()
                        sleep_start_time = None
                        line_buffer.clear()
                    except (serial.SerialException, OSError):
                        self.ser = None

                time.sleep(0.15)
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

                            # Render styled telemetry line on console
                            styled = self.format_log_line(raw_line)
                            self.console.print(styled)

                            # Persistent disk logging (ANSI stripped for 100% clean plain text)
                            if self.enable_logging and self.log_file:
                                clean_for_log = ANSI_ESCAPE_RE.sub("", raw_line).rstrip("\r\n")
                                if self.enable_timestamps:
                                    now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
                                    self.log_file.write(f"[{now_ms}] {clean_for_log}\n")
                                else:
                                    self.log_file.write(f"{clean_for_log}\n")
                                self.log_file.flush()

                        elif b != ord("\r"):
                            line_buffer.append(b)
                else:
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
                sys.stdout.write("\n")
                self._print_badge("SUSPEND", "Target entered deep sleep / USB PHY power gated.", "yellow")
                self._update_window_title()

    def _keyboard_listener(self):
        """Poll keyboard asynchronously for hotkeys without blocking serial stream."""
        if os.name == "nt":
            import msvcrt

            while self.running:
                if msvcrt.kbhit():
                    ch = msvcrt.getch()
                    # Handle arrow/function escape sequences
                    if ch in (b"\x00", b"\xe0"):
                        msvcrt.getch()
                        continue

                    key = ch.decode("utf-8", errors="ignore").lower()
                    if key == "q" or ch == b"\x1b" or ch == b"\x03":  # Q, ESC, Ctrl+C
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
                time.sleep(0.05)
        else:
            import select
            import termios
            import tty

            fd = sys.stdin.fileno()
            old_settings = termios.tcgetattr(fd)
            try:
                tty.setcbreak(fd)
                while self.running:
                    r, _, _ = select.select([sys.stdin], [], [], 0.05)
                    if r:
                        ch = sys.stdin.read(1)
                        key = ch.lower()
                        if key == "q" or ch == "\x1b" or ch == "\x03":
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
            finally:
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
