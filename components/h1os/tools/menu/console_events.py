#!/usr/bin/env python3
"""
H1OS Console Event Dispatcher
=============================
Cross-platform asynchronous event-driven console input subsystem.
Captures keyboard strokes, mouse wheel scroll events, and terminal window resizes
using the native Windows Console API (ReadConsoleInputW) and POSIX VT/SGR sequences.
"""

import enum
import os
import queue
import re
import shutil
import sys
import threading
import time
from dataclasses import dataclass
from typing import Optional, Tuple


class EventType(enum.Enum):
    KEY = "KEY"
    SCROLL = "SCROLL"
    RESIZE = "RESIZE"


@dataclass
class ConsoleEvent:
    type: EventType
    key: Optional[str] = None
    delta: int = 0
    columns: int = 0
    rows: int = 0


# Windows Console API structures
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

    class WINDOW_BUFFER_SIZE_RECORD(ctypes.Structure):
        _fields_ = [("dwSize", COORD)]

    class EVENT_UNION(ctypes.Union):
        _fields_ = [
            ("KeyEvent", KEY_EVENT_RECORD),
            ("MouseEvent", MOUSE_EVENT_RECORD),
            ("WindowBufferSizeEvent", WINDOW_BUFFER_SIZE_RECORD),
        ]

    class INPUT_RECORD(ctypes.Structure):
        _fields_ = [
            ("EventType", wintypes.WORD),
            ("Event", EVENT_UNION),
        ]


SGR_MOUSE_RE = re.compile(r"\x1b\[<(\d+);(\d+);(\d+)([Mm])")


class ConsoleEventDispatcher:
    """Threaded cross-platform event dispatcher for keyboard, mouse wheel, and window resize."""

    def __init__(self, enable_mouse: bool = True, enable_resize: bool = True) -> None:
        self.enable_mouse = enable_mouse
        self.enable_resize = enable_resize
        self.event_queue: queue.Queue = queue.Queue()
        self.running = False
        self._thread: Optional[threading.Thread] = None
        self._orig_mode: Optional[int] = None
        self._h_in: Optional[int] = None
        self._is_tty = sys.stdin.isatty()
        self._last_cols, self._last_rows = shutil.get_terminal_size((80, 24))

    def __enter__(self) -> "ConsoleEventDispatcher":
        self.start()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:
        self.stop()

    def start(self) -> None:
        """Start the background event listener thread."""
        if self.running or not self._is_tty:
            return
        self.running = True
        if os.name == "nt":
            self._thread = threading.Thread(target=self._listener_windows, daemon=True)
        else:
            self._thread = threading.Thread(target=self._listener_posix, daemon=True)
        self._thread.start()

    def stop(self) -> None:
        """Stop listener thread and restore console terminal modes."""
        self.running = False
        if self._thread and self._thread.is_alive():
            self._thread.join(timeout=0.2)
        self._thread = None

    def get_event(self, timeout: Optional[float] = None) -> Optional[ConsoleEvent]:
        """Fetch next event from queue or return None if timeout expires."""
        if not self._is_tty:
            return None
        try:
            return self.event_queue.get(timeout=timeout)
        except queue.Empty:
            return None

    def empty(self) -> bool:
        """Check if event queue is currently empty."""
        return self.event_queue.empty()

    def drain(self) -> None:
        """Discard all pending queued events."""
        while not self.event_queue.empty():
            try:
                self.event_queue.get_nowait()
            except queue.Empty:
                break

    def _listener_windows(self) -> None:
        """Listen for Windows Console events (Keyboard, Mouse Wheel, Window Resize)."""
        kernel32 = ctypes.windll.kernel32
        GENERIC_READ = 0x80000000
        GENERIC_WRITE = 0x40000000

        self._h_in = kernel32.CreateFileW("CONIN$", GENERIC_READ | GENERIC_WRITE, 1 | 2, None, 3, 0, None)
        if self._h_in == -1:
            self._h_in = kernel32.GetStdHandle(-10)

        mode = wintypes.DWORD()
        has_console = kernel32.GetConsoleMode(self._h_in, ctypes.byref(mode)) != 0
        self._orig_mode = mode.value if has_console else 0

        if has_console:
            # Enable mouse input (0x0010), extended flags (0x0080), window resize (0x0008), disable quick-edit (0x0040)
            new_mode = (self._orig_mode | 0x0010 | 0x0080 | 0x0008) & ~0x0040
            kernel32.SetConsoleMode(self._h_in, new_mode)

        try:
            num_events = wintypes.DWORD()
            records = (INPUT_RECORD * 32)()
            read_count = wintypes.DWORD()

            while self.running:
                if has_console:
                    kernel32.GetNumberOfConsoleInputEvents(self._h_in, ctypes.byref(num_events))
                    if num_events.value > 0:
                        kernel32.ReadConsoleInputW(
                            self._h_in,
                            ctypes.byref(records),
                            min(32, num_events.value),
                            ctypes.byref(read_count),
                        )
                        for i in range(read_count.value):
                            rec = records[i]

                            # 1. KEY_EVENT (0x0001)
                            if rec.EventType == 0x0001 and rec.Event.KeyEvent.bKeyDown:
                                vk = rec.Event.KeyEvent.wVirtualKeyCode
                                ch = rec.Event.KeyEvent.UnicodeChar

                                key_name = None
                                if vk == 0x26:  # VK_UP
                                    key_name = "UP"
                                elif vk == 0x28:  # VK_DOWN
                                    key_name = "DOWN"
                                elif vk == 0x27:  # VK_RIGHT
                                    key_name = "RIGHT"
                                elif vk == 0x25:  # VK_LEFT
                                    key_name = "LEFT"
                                elif vk == 0x0D:  # VK_RETURN
                                    key_name = "ENTER"
                                elif vk == 0x1B:  # VK_ESCAPE
                                    key_name = "ESC"
                                elif vk == 0x20:  # VK_SPACE
                                    key_name = "SPACE"
                                elif vk == 0x21:  # VK_PRIOR (PageUp)
                                    key_name = "PAGEUP"
                                elif vk == 0x22:  # VK_NEXT (PageDown)
                                    key_name = "PAGEDOWN"
                                elif vk == 0x24:  # VK_HOME
                                    key_name = "HOME"
                                elif vk == 0x23:  # VK_END
                                    key_name = "END"
                                elif ch:
                                    key_name = ch.upper()

                                if key_name:
                                    self.event_queue.put(ConsoleEvent(type=EventType.KEY, key=key_name))

                            # 2. MOUSE_EVENT (0x0002)
                            elif rec.EventType == 0x0002 and self.enable_mouse:
                                ev_flags = rec.Event.MouseEvent.dwEventFlags
                                if ev_flags & 0x0004:  # MOUSE_WHEELED
                                    delta_raw = ctypes.c_int16(rec.Event.MouseEvent.dwButtonState >> 16).value
                                    direction = 1 if delta_raw > 0 else -1
                                    self.event_queue.put(ConsoleEvent(type=EventType.SCROLL, delta=direction))

                            # 3. WINDOW_BUFFER_SIZE_EVENT (0x0004)
                            elif rec.EventType == 0x0004 and self.enable_resize:
                                cols, rows = shutil.get_terminal_size((80, 24))
                                if cols != self._last_cols or rows != self._last_rows:
                                    self._last_cols, self._last_rows = cols, rows
                                    self.event_queue.put(ConsoleEvent(type=EventType.RESIZE, columns=cols, rows=rows))

                        continue
                time.sleep(0.015)
        finally:
            if has_console and self._orig_mode:
                kernel32.SetConsoleMode(self._h_in, self._orig_mode)
            if self._h_in != -1 and self._h_in != kernel32.GetStdHandle(-10):
                kernel32.CloseHandle(self._h_in)

    def _listener_posix(self) -> None:
        """Listen for POSIX terminal events via termios, select, and SIGWINCH."""
        import select
        import termios
        import tty

        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)

        # Hook SIGWINCH for window resize notifications
        def handle_sigwinch(signum, frame):
            cols, rows = shutil.get_terminal_size((80, 24))
            self._last_cols, self._last_rows = cols, rows
            self.event_queue.put(ConsoleEvent(type=EventType.RESIZE, columns=cols, rows=rows))

        try:
            import signal
            signal.signal(signal.SIGWINCH, handle_sigwinch)
        except Exception:
            pass

        try:
            tty.setraw(fd)
            if self.enable_mouse:
                # Enable SGR 1006 mouse tracking
                sys.stdout.write("\x1b[?1000h\x1b[?1006h")
                sys.stdout.flush()

            while self.running:
                r, _, _ = select.select([sys.stdin], [], [], 0.05)
                if not r:
                    continue

                ch = sys.stdin.read(1)
                if not ch:
                    continue

                if ch == "\x1b":
                    # Non-blocking read remaining sequence bytes
                    seq = ""
                    while select.select([sys.stdin], [], [], 0.005)[0]:
                        seq += sys.stdin.read(1)

                    if not seq:
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="ESC"))
                        continue

                    # SGR mouse tracking: \x1b[<64;X;YM (Wheel Up) or \x1b[<65;X;YM (Wheel Down)
                    if self.enable_mouse and seq.startswith("[<"):
                        m_mouse = SGR_MOUSE_RE.match("\x1b" + seq)
                        if m_mouse:
                            btn = int(m_mouse.group(1))
                            if btn == 64:  # Wheel Up
                                self.event_queue.put(ConsoleEvent(type=EventType.SCROLL, delta=1))
                            elif btn == 65:  # Wheel Down
                                self.event_queue.put(ConsoleEvent(type=EventType.SCROLL, delta=-1))
                            continue

                    if seq == "[A":
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="UP"))
                    elif seq == "[B":
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="DOWN"))
                    elif seq == "[C":
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="RIGHT"))
                    elif seq == "[D":
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="LEFT"))
                    elif seq in ("[5~", "[[5~"):
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="PAGEUP"))
                    elif seq in ("[6~", "[[6~"):
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="PAGEDOWN"))
                    elif seq in ("[H", "[1~"):
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="HOME"))
                    elif seq in ("[F", "[4~"):
                        self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="END"))
                elif ch in ("\r", "\n"):
                    self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="ENTER"))
                elif ch == " ":
                    self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="SPACE"))
                elif ch in ("\x03", "\x1a"):
                    self.event_queue.put(ConsoleEvent(type=EventType.KEY, key="QUIT"))
                else:
                    self.event_queue.put(ConsoleEvent(type=EventType.KEY, key=ch.upper()))
        finally:
            if self.enable_mouse:
                # Disable SGR 1006 mouse tracking
                sys.stdout.write("\x1b[?1006l\x1b[?1000l")
                sys.stdout.flush()
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
