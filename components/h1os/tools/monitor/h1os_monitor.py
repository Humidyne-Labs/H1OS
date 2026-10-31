#!/usr/bin/env python3
"""
H1OS Dedicated Serial Monitor & Telemetry Console (h1os_monitor)
Version: 1.0.0
License: Apache-2.0

High-performance, zero-dot serial monitor for ESP32-S3 firmware development.
Features:
- Zero scrollback pollution during deep sleep (in-place status spinner).
- 100% millisecond-precision timestamps (toggled via 'T' or --timestamps, default: OFF).
- Dual live Rich console display + persistent disk logging (toggled via 'L' or --log, default: OFF).
- Hardware reset on demand (key 'R').
- Auto-reconnect on deep-sleep wake with zero DTR/RTS glitching.
"""

import argparse
import datetime
import os
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
    from rich.panel import Panel
    from rich.text import Text
except ImportError:
    Console = None
    Panel = None
    Text = None


SPINNER_FRAMES = ["⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"]


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
    """Zero-dot, dual-stream serial monitor with deep-sleep auto-reconnect."""

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
        """Open or rotate session disk log with authoritative header."""
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
            f"# Date        : {now_str}\n",
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
            self._close_log_file()
            self._print_notice("Logging DISABLED", style="bold yellow")

    def toggle_timestamps(self):
        """Toggle millisecond timestamps on/off interactively."""
        self.enable_timestamps = not self.enable_timestamps
        state_str = "ENABLED" if self.enable_timestamps else "DISABLED"
        style = "bold green" if self.enable_timestamps else "bold yellow"
        self._print_notice(f"Timestamps {state_str}", style=style)

    def trigger_hardware_reset(self):
        """Pulse DTR/RTS lines to perform a clean hardware reset on ESP32-S3."""
        if not self.ser or not self.ser.is_open:
            self._print_notice("Cannot reset: Serial port not open.", style="bold red")
            return

        try:
            # ESP32 auto-reset circuit: RTS asserts EN (active-low), DTR asserts IO0 (active-low).
            # To reset cleanly into application: assert RTS=True with DTR=False (pulls EN LOW),
            # wait, then release RTS=False (pulls EN HIGH).
            self.ser.dtr = False
            self.ser.rts = True
            time.sleep(0.12)
            self.ser.rts = False
            time.sleep(0.05)
            self._print_notice("Hardware RESET triggered via DTR/RTS lines.", style="bold yellow")
        except Exception as e:
            self._print_notice(f"Hardware reset failed: {e}", style="bold red")

    def _print_notice(self, text: str, style: str = "bold yellow"):
        """Print an in-band monitor diagnostic message."""
        if self.console:
            self.console.print(f"[{style}][H1OS] {text}[/{style}]")
        else:
            print(f"[H1OS] {text}")

    def print_banner(self):
        """Display authoritative header panel."""
        port_desc = self.port or "Auto-detect"
        ts_state = "[green]ON[/]" if self.enable_timestamps else "[dim]OFF[/]"
        log_state = f"[green]ON[/] ({self.log_path.name})" if (self.enable_logging and self.log_path) else "[dim]OFF[/]"

        banner_text = (
            f"[bold cyan]Port:[/] {port_desc} @ {self.baud} baud  |  "
            f"[bold cyan]Target:[/] {self.chip.upper()}  |  "
            f"[bold cyan]Timestamps:[/] {ts_state}  |  "
            f"[bold cyan]Logging:[/] {log_state}\n"
            f"[dim]Hotkeys: [bold]R[/] Reset Target  |  [bold]T[/] Toggle Timestamps  |  [bold]L[/] Toggle Log  |  [bold]C[/] Clear  |  [bold]Q/ESC[/] Quit[/]"
        )

        if self.console and Panel:
            self.console.print(Panel(banner_text, title="[bold white]H1OS Dedicated Serial Monitor[/]", border_style="cyan"))
        else:
            print("=" * 78)
            print(f"H1OS Serial Monitor on {port_desc} @ {self.baud} baud ({self.chip.upper()})")
            print("Hotkeys: [R] Reset  [T] Timestamps  [L] Logging  [C] Clear  [Q] Quit")
            print("=" * 78)

    def _format_styled_line(self, raw_line: str) -> Text:
        """Apply Rich styles based on standard ESP-IDF log level tags."""
        text = Text()

        # Optional timestamp prefix
        if self.enable_timestamps:
            now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
            text.append(f"[{now_ms}] ", style="dim cyan")

        # Color-code standard ESP log levels
        clean = raw_line.rstrip("\r\n")
        if clean.startswith("E (") or " [E] " in clean or clean.startswith("[ERROR]"):
            text.append(clean, style="bold red")
        elif clean.startswith("W (") or " [W] " in clean or clean.startswith("[WARN]"):
            text.append(clean, style="yellow")
        elif clean.startswith("I (") or " [I] " in clean or clean.startswith("[INFO]"):
            text.append(clean, style="bright_white")
        elif clean.startswith("D (") or " [D] " in clean or clean.startswith("[DEBUG]"):
            text.append(clean, style="dim white")
        elif clean.startswith("V (") or " [V] " in clean:
            text.append(clean, style="dim bright_black")
        else:
            text.append(clean)

        return text

    def run(self):
        """Main execution loop supervising serial streaming and deep-sleep reconnects."""
        self.print_banner()

        # Keyboard polling thread
        kb_thread = threading.Thread(target=self._keyboard_listener, daemon=True)
        kb_thread.start()

        line_buffer = bytearray()
        sleep_start_time: Optional[float] = None
        spinner_idx = 0

        while self.running:
            # 1. Ensure Port Connection
            if self.ser is None or not self.ser.is_open:
                # Resolve target port
                target_port = self.port or auto_detect_serial_port()

                if sleep_start_time is None:
                    sleep_start_time = time.time()

                # Calculate elapsed time in sleep
                elapsed_sec = int(time.time() - sleep_start_time)
                mins = elapsed_sec // 60
                secs = elapsed_sec % 60
                time_str = f"{mins:02d}m {secs:02d}s" if mins > 0 else f"{secs:02d}s"

                # In-place spinner update (NO DOTS, NO NEWLINE)
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
                        self.ser.dtr = False
                        self.ser.rts = False

                        # Clear in-place spinner line
                        sys.stdout.write("\r" + " " * 85 + "\r")
                        sys.stdout.flush()

                        self.port = target_port
                        reconn_msg = f"Target connected on {self.port} (slept {time_str})."
                        self._print_notice(reconn_msg, style="bold green")
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

                            # Format and display
                            if self.console:
                                styled = self._format_styled_line(raw_line)
                                self.console.print(styled)
                            else:
                                if self.enable_timestamps:
                                    now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
                                    print(f"[{now_ms}] {raw_line.rstrip()}")
                                else:
                                    print(raw_line.rstrip())

                            # Write to persistent log file if enabled
                            if self.enable_logging and self.log_file:
                                if self.enable_timestamps:
                                    now_ms = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
                                    self.log_file.write(f"[{now_ms}] {raw_line.rstrip()}\n")
                                else:
                                    self.log_file.write(f"{raw_line.rstrip()}\n")
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

    def _keyboard_listener(self):
        """Poll keyboard asynchronously for hotkeys without blocking serial stream."""
        if os.name == "nt":
            import msvcrt

            while self.running:
                if msvcrt.kbhit():
                    ch = msvcrt.getch()
                    # Handle special keys / arrows
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
                        if self.console:
                            self.console.clear()
                        else:
                            os.system("cls" if os.name == "nt" else "clear")
                        self.print_banner()
                time.sleep(0.05)
        else:
            # Unix / macOS non-blocking key read
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
                            if self.console:
                                self.console.clear()
                            else:
                                os.system("clear")
                            self.print_banner()
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
