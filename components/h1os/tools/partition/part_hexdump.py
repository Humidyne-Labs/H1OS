#!/usr/bin/env python3
"""
H1OS Hex Dump Formatter & Interactive Terminal Viewer
=====================================================
Provides canonical hexdump formatting for text logs and an interactive
paginated terminal hex inspector for rapid non-destructive diagnostics.
"""

import sys
from typing import List, Optional

try:
    from rich.console import Console
    from rich.table import Table
    from rich import box
    from rich.text import Text
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False


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
    """Render interactive or paginated hex viewer for partition dump in terminal."""
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

    # Windows msvcrt keyboard input
    try:
        import msvcrt

        def read_key() -> str:
            ch = msvcrt.getch()
            if ch in (b"\x00", b"\xe0"):
                ch2 = msvcrt.getch()
                if ch2 == b"H":
                    return "UP"
                if ch2 == b"P":
                    return "DOWN"
                if ch2 == b"I":
                    return "PGUP"
                if ch2 == b"Q":
                    return "PGDN"
                if ch2 == b"G":
                    return "HOME"
                if ch2 == b"O":
                    return "END"
            if ch in (b"\r", b"\n"):
                return "ENTER"
            if ch in (b"\x1b", b"q", b"Q"):
                return "QUIT"
            return ch.decode("utf-8", errors="ignore").upper()

    except ImportError:
        def read_key() -> str:
            line = sys.stdin.readline().strip().upper()
            return line if line else "ENTER"

    ROWS_PER_PAGE = 16  # 256 bytes per page
    BYTES_PER_PAGE = ROWS_PER_PAGE * 16
    total_bytes = len(data)
    total_pages = max(1, (total_bytes + BYTES_PER_PAGE - 1) // BYTES_PER_PAGE)
    current_page = 0

    while True:
        console.clear()
        page_start = current_page * BYTES_PER_PAGE
        page_end = min(total_bytes, page_start + BYTES_PER_PAGE)
        chunk = data[page_start:page_end]

        title_text = (
            f"[bold white]Partition Hex Inspector: [/][bold cyan]{partition_name}[/] "
            f"([dim]{total_bytes:,} bytes total[/])"
        )
        subtitle_text = (
            f"[dim]Page {current_page + 1} of {total_pages} | "
            f"Offset: 0x{base_offset + page_start:08X} - 0x{base_offset + page_end - 1:08X}[/]"
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

        for row_idx in range(0, len(chunk), 16):
            row_chunk = chunk[row_idx:row_idx + 16]
            hex_bytes = [f"{b:02x}" for b in row_chunk]
            if len(hex_bytes) > 8:
                hex_str = " ".join(hex_bytes[:8]) + "  " + " ".join(hex_bytes[8:])
            else:
                hex_str = " ".join(hex_bytes)

            pad_len = 48 - len(hex_str)
            if pad_len > 0:
                hex_str += " " * pad_len

            ascii_str = "".join(chr(b) if 32 <= b <= 126 else "." for b in row_chunk)
            row_addr = f"0x{base_offset + page_start + row_idx:08X}"

            table.add_row(row_addr, hex_str, ascii_str)

        console.print(table)
        footer = Text(
            "  [↑/↓] Row   [PgUp/PgDn] Page   [Home/End] Jump   [Q/Esc] Exit Inspector",
            style="dim",
        )
        console.print(footer)

        key = read_key()
        if key in ("QUIT", "Q", "ESC"):
            break
        elif key in ("DOWN", "PGDN", "SPACE"):
            if current_page < total_pages - 1:
                current_page += 1
        elif key in ("UP", "PGUP"):
            if current_page > 0:
                current_page -= 1
        elif key == "HOME":
            current_page = 0
        elif key == "END":
            current_page = total_pages - 1
