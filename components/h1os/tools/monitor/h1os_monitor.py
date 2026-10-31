#!/usr/bin/env python3
"""
H1OS Dedicated Serial Monitor & Telemetry Console (h1os_monitor)
Version: 1.1.0
License: Apache-2.0

High-performance, zero-dot serial monitor for ESP32-S3 firmware development.
Features:
- Static pinned header window with independent scrollable terminal region.
- Zero scrollback pollution during deep sleep (in-place status spinner).
- Clean ANSI color decoding on console & clean plain-text disk logging (no malformed [0;32m tags).
- Millisecond-precision timestamps (toggled via 'T', default: OFF).
- Dual live Rich console display + persistent disk logging (toggled via 'L', default: OFF).
- Hardware reset on demand (key 'R') using the proven Windows usbser.sys DTR/RTS pulse.
- Working terminal clear (key 'C').
- Auto-reconnect on deep-sleep wake with zero DTR/RTS glitching.
"""

import argparse
import datetime
import os
import re
import shutil
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
    from rich.console import Console
    from rich.text import Text
except ImportError:
    Console = None
    Text = None

# Regex to strip ANSI escape sequences for pristine plain-text disk logging
ANSI_ESCAPE_RE = re.compile(r"\x1b\[[0-9;]*[a-zA-Z]")
SPINNER_FRAMES = ["⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"]


def set_rts_with_windows_quirk(port: serial.Serial, state: bool) -> None:
    """Set RTS pin state with the Windows usbser.sys CDC workaround."""
    port.setRTS(state)
    # Windows usbser.sys only sends SET_CONTROL_LINE_STATE when both lines are touched
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
    """Zero-dot, dual-stream serial monitor with pinned static header and deep-sleep supervisor."""

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

        self.console = Console(highlight=False) if Console else None

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
            self._print_notice(f"Logging ENABLED -> {self.log_path.name if self.log_path else 'log'}", style="bold green")
        else:
            saved_name = self.log_path.name if self.log_path else "log"
            self._close_log_file()
            self._print_notice(f"Logging DISABLED (saved: {saved_name})", style="bold yellow")
        self.render_static_header()

    def toggle_timestamps(self):
        """Toggle millisecond timestamps on/off interactively."""
        self.enable_timestamps = not self.enable_timestamps
        state_str = "ENABLED" if self.enable_timestamps else "DISABLED"
        style = "bold green" if self.enable_timestamps else "bold yellow"
        self._print_notice(f"Timestamps {state_str}", style=style)
        self.render_static_header()

    def trigger_hardware_reset(self):
        """Pulse DTR/RTS lines to perform a clean hardware reset on ESP32-S3."""
        if not self.ser or not self.ser.is_open:
            self._print_notice("Cannot reset: Serial port not open.", style="bold red")
            return

        try:
            execute_hardware_reset(self.ser, hold_delay=0.2, settle_delay=0.2)
            self._print_notice("Hardware RESET triggered via DTR/RTS pulse.", style="bold yellow")
        except (serial.SerialException, OSError):
            # Native USB-Serial-JTAG drops connection immediately upon reset assertion
            if self.ser:
                try:
                    self.ser.close()
                except Exception:
                    pass
            self.ser = None
            self._print_notice("Hardware RESET triggered (device re-enumerating)...", style="bold yellow")
        except Exception as e:
            self._print_notice(f"Hardware reset failed: {e}", style="bold red")

    def _print_notice(self, text: str, style: str = "bold yellow"):
        """Print an in-band monitor diagnostic notice."""
        if self.console:
            self.console.print(f"[{style}][H1OS] {text}[/{style}]")
        else:
            print(f"[H1OS] {text}")

    def clear_screen(self):
        """Perform native console blank and re-lock static header."""
        if os.name == "nt":
            os.system("cls")
        else:
            sys.stdout.write("\033[2J\033[H")
            sys.stdout.flush()
        self.render_static_header()

    def render_static_header(self):
        """Render a static pinned header on lines 1..3 and set VT100 scroll margin."""
        cols, lines = shutil.get_terminal_size((80, 24))
        port_desc = self.port or "Auto-detect"
        ts_state = "ON" if self.enable_timestamps else "OFF"
        log_state = f"ON ({self.log_path.name})" if (self.enable_logging and self.log_path) else "OFF"

        # Update terminal window title bar
        title_str = (
            f"H1OS Monitor: {port_desc} @ {self.baud} | "
            f"Chip: {self.chip.upper()} | "
            f"Logging: {log_state} | "
            f"Timestamps: {ts_state} | "
            f"[R] Reset [T] Time [L] Log [C] Clear [Q] Quit"
        )
        sys.stdout.write(f"\033]0;{title_str}\007")

        # Static 3-line header text
        divider = "─" * min(cols, 100)
        h1 = f" H1OS Serial Monitor │ Port: {port_desc} @ {self.baud} │ Target: {self.chip.upper()} │ Timestamps: {ts_state} │ Log: {log_state}"
        h2 = f" Hotkeys: [R] Reset Target │ [T] Timestamps │ [L] Log to File │ [C] Clear │ [Q] Quit │ Log Dir: {self.log_dir.name}"

        # Draw pinned lines 1..3
        sys.stdout.write("\033[s")  # Save cursor
        sys.stdout.write("\033[1;1H\033[2K")
        sys.stdout.write(f"\033[1;36m{h1[:cols]}\033[0m\n")
        sys.stdout.write("\033[2;1H\033[2K")
        sys.stdout.write(f"\033[0;37m{h2[:cols]}\033[0m\n")
        sys.stdout.write("\033[3;1H\033[2K")
        sys.stdout.write(f"\033[0;36m{divider[:cols]}\033[0m\n")

        # Configure VT100 scrolling margin from line 4 to bottom
        sys.stdout.write(f"\033[4;{lines}r")
        sys.stdout.write("\033[u")  # Restore cursor
        sys.stdout.flush()

    def reset_scroll_region(self):
        """Restore standard full-screen scrolling region on exit."""
        sys.stdout.write("\033[r")
        sys.stdout.flush()

    def _format_styled_line(self, raw_line: str) -> Text:
        """Parse raw serial line, decode ANSI escapes into Rich styles, and add optional timestamp."""
        clean = raw_line.rstrip("\r\n")
        styled_body = Text.from_ansi(clean) if Text else clean

        if not self.enable_timestamps:
            return styled_body

        now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
        if Text:
            ts_text = Text()
            ts_text.append(f"[{now_ms}] ", style="dim cyan")
            ts_text.append_text(styled_body)
            return ts_text
        return f"[{now_ms}] {styled_body}"

    def run(self):
        """Main execution loop supervising serial streaming, deep sleep, and keyboard input."""
        self.clear_screen()

        # Keyboard polling thread
        kb_thread = threading.Thread(target=self._keyboard_listener, daemon=True)
        kb_thread.start()

        line_buffer = bytearray()
        sleep_start_time: Optional[float] = None
        spinner_idx = 0

        try:
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
                            # Explicitly hold lines low so MCU is not reset
                            set_dtr_pin(self.ser, False)
                            set_rts_with_windows_quirk(self.ser, False)

                            # Clear in-place spinner line
                            sys.stdout.write("\r" + " " * 85 + "\r")
                            sys.stdout.flush()

                            self.port = target_port
                            reconn_msg = f"Target connected on {self.port} (slept {time_str})."
                            self._print_notice(reconn_msg, style="bold green")
                            self.render_static_header()
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

                                # Live display with native Rich ANSI color decoding
                                if self.console:
                                    styled = self._format_styled_line(raw_line)
                                    self.console.print(styled)
                                else:
                                    clean_line = raw_line.rstrip("\r\n")
                                    if self.enable_timestamps:
                                        now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
                                        print(f"[{now_ms}] {clean_line}")
                                    else:
                                        print(clean_line)

                                # Persistent disk logging (ANSI stripped for 100% clean plain text)
                                if self.enable_logging and self.log_file:
                                    clean_for_log = ANSI_ESCAPE_RE.sub("", raw_line.rstrip("\r\n"))
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
                    self._print_notice("Target entered deep sleep / USB suspended.", style="yellow")

        finally:
            self.reset_scroll_region()

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
        self.reset_scroll_region()
        if self.ser and self.ser.is_open:
            try:
                self.ser.close()
            except Exception:
                pass
        self._close_log_file()
        if self.console:
            self.console.print("\n[bold cyan]H1OS Serial Monitor closed.[/bold cyan]")
        else:
            print("\nH1OS Serial Monitor closed.")


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
