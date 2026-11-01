#!/usr/bin/env python3
"""
H1OS Hex Dump Formatter & Interactive Terminal Viewer
=====================================================
Provides canonical hexdump formatting for text logs and an interactive
smooth Live terminal hex inspector with mouse wheel scrolling and keyboard navigation.
"""

import sys
from pathlib import Path
from typing import List, Optional

# Ensure tools directory is in sys.path
TOOLS_DIR = Path(__file__).resolve().parent.parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

try:
    from rich.console import Console, Group
    from rich.live import Live
    from rich.table import Table
    from rich import box
    from rich.text import Text
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False

try:
    from menu.console_events import ConsoleEventDispatcher, ConsoleEvent, EventType
except ImportError:
    from console_events import ConsoleEventDispatcher, ConsoleEvent, EventType


def format_canonical_hexdump(data: bytes, base_offset: int = 0) -> str:
    """Format raw binary bytes into standard canonical hexdump (16 bytes per row)."""
    lines = []
    header = "OFFSET    00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  |ASCII|"
    sep = "-" * len(header)
    lines.append(header)
    lines.append(sep)

    length = len(data)
    for i in range(0, length, 16):
        chunk = data[i:i + 16]
        hex_bytes = [f"{b:02x}" for b in chunk]

        # 8-byte group separator
        if len(hex_bytes) > 8:
            hex_part = " ".join(hex_bytes[:8]) + "  " + " ".join(hex_bytes[8:])
        else:
            hex_part = " ".join(hex_bytes)

        # Pad remaining if chunk < 16
        pad_len = 49 - len(hex_part)
        if pad_len > 0:
            hex_part += " " * pad_len

        # ASCII printable column
        ascii_part = "".join(chr(b) if 32 <= b <= 126 else "." for b in chunk)

        addr = base_offset + i
        lines.append(f"{addr:08x}  {hex_part}  |{ascii_part}|")

    return "\n".join(lines) + "\n"


def render_live_hex_view(
    data: bytes,
    partition_name: str,
    base_offset: int = 0,
    console: Optional["Console"] = None,
) -> None:
    """Render interactive smooth Live hex viewer for partition dump in terminal."""
    if not data:
        if console:
            console.print("[yellow]Partition data buffer is empty (0 bytes).[/]")
        else:
            print("Partition data buffer is empty (0 bytes).")
        return

    # Fallback if rich is absent or non-interactive
    if not HAVE_RICH or not console or not sys.stdin.isatty():
        dump_text = format_canonical_hexdump(data[:512], base_offset=base_offset)
        print(f"\n--- HEX DUMP PREVIEW: {partition_name} (First 512 of {len(data)} bytes) ---")
        print(dump_text)
        if len(data) > 512:
            print(f"... ({len(data) - 512} additional bytes omitted from console preview) ...\n")
        return

    ROWS_PER_SCREEN = 16  # 16 rows = 256 bytes per screen
    total_bytes = len(data)
    total_rows = max(1, (total_bytes + 15) // 16)
    max_row = max(0, total_rows - ROWS_PER_SCREEN)
    current_row = 0

    def build_hex_frame(row_idx: int) -> Group:
        start_byte = row_idx * 16
        end_byte = min(total_bytes, start_byte + (ROWS_PER_SCREEN * 16))
        chunk = data[start_byte:end_byte]

        pct = int((row_idx / max(1, max_row)) * 100) if max_row > 0 else 100
        title_text = (
            f"[bold white]Partition Hex Inspector: [/][bold cyan]{partition_name}[/] "
            f"([dim]{total_bytes:,} bytes total[/])"
        )
        subtitle_text = (
            f"[dim]Offset: 0x{base_offset + start_byte:08X} - 0x{base_offset + max(start_byte, end_byte - 1):08X} | "
            f"Row {row_idx + 1} of {total_rows} ({pct}%)[/]"
        )

        table = Table(
            box=box.ROUNDED,
            width=78,
            title=f"{title_text}\n{subtitle_text}",
            header_style="bold bright_cyan",
            pad_edge=False,
            show_lines=False,
        )
        table.add_column("Offset", style="dim", width=10, justify="right")
        table.add_column("Hex Bytes (00-0F)", style="bold white", width=50)
        table.add_column("ASCII", style="green", width=16)

        for offset in range(0, len(chunk), 16):
            row_chunk = chunk[offset:offset + 16]
            hex_bytes = [f"{b:02x}" for b in row_chunk]
            if len(hex_bytes) > 8:
                hex_str = " ".join(hex_bytes[:8]) + "  " + " ".join(hex_bytes[8:])
            else:
                hex_str = " ".join(hex_bytes)

            pad_len = 48 - len(hex_str)
            if pad_len > 0:
                hex_str += " " * pad_len

            ascii_str = "".join(chr(b) if 32 <= b <= 126 else "." for b in row_chunk)
            row_addr = f"0x{base_offset + start_byte + offset:08X}"
            table.add_row(row_addr, hex_str, ascii_str)

        footer = Text(
            "  [↑/↓/MouseWheel] Row   [PgUp/PgDn] Page   [Home/End] Jump   [←/Esc/Q] Back",
            style="dim",
        )
        return Group(table, footer)

    frame = build_hex_frame(current_row)
    with Live(frame, console=console, auto_refresh=False, screen=False, transient=True) as live:
        with ConsoleEventDispatcher(enable_mouse=True, enable_resize=True) as dispatcher:
            while True:
                ev = dispatcher.get_event(timeout=0.05)
                if not ev:
                    continue

                if ev.type == EventType.SCROLL:
                    # Wheel Up moves rows up (towards offset 0), Wheel Down moves rows down
                    if ev.delta > 0:
                        current_row = max(0, current_row - 2)
                    else:
                        current_row = min(max_row, current_row + 2)
                    live.update(build_hex_frame(current_row), refresh=True)

                elif ev.type == EventType.RESIZE:
                    live.update(build_hex_frame(current_row), refresh=True)

                elif ev.type == EventType.KEY:
                    key = ev.key
                    if key in ("QUIT", "Q", "ESC", "LEFT", "B"):
                        break
                    elif key == "UP":
                        current_row = max(0, current_row - 1)
                        live.update(build_hex_frame(current_row), refresh=True)
                    elif key == "DOWN":
                        current_row = min(max_row, current_row + 1)
                        live.update(build_hex_frame(current_row), refresh=True)
                    elif key in ("PAGEUP", "PGUP"):
                        current_row = max(0, current_row - ROWS_PER_SCREEN)
                        live.update(build_hex_frame(current_row), refresh=True)
                    elif key in ("PAGEDOWN", "PGDN", "SPACE"):
                        current_row = min(max_row, current_row + ROWS_PER_SCREEN)
                        live.update(build_hex_frame(current_row), refresh=True)
                    elif key == "HOME":
                        current_row = 0
                        live.update(build_hex_frame(current_row), refresh=True)
                    elif key == "END":
                        current_row = max_row
                        live.update(build_hex_frame(current_row), refresh=True)
