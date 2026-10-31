#!/usr/bin/env python3
"""
H1OS Interactive Flash Partition Manager
========================================
Dynamic partition discovery, alignment auditing, memory map visualization,
multi-format partition dumping (bin/hex/view), and OTA slot switching.
"""

import argparse
import datetime
import os
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple, Any

# Ensure components/h1os/tools is importable
CURRENT_DIR = Path(__file__).resolve().parent
TOOLS_DIR = CURRENT_DIR.parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

from h1os_tool import H1OSConfig
from partition.part_backend import (
    execute_parttool_erase,
    execute_parttool_read,
    execute_parttool_write,
    execute_otatool_read,
    execute_otatool_switch,
)
from partition.part_hexdump import (
    format_canonical_hexdump,
    render_live_hex_view,
)

try:
    from rich.console import Console
    from rich.table import Table
    from rich.panel import Panel
    from rich import box
    from rich.text import Text
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False

TERM_WIDTH = 78


@dataclass
class PartitionEntry:
    name: str
    type: str
    subtype: str
    offset: int
    size: int
    flags: str = ""

    @property
    def end_offset(self) -> int:
        return self.offset + self.size

    @property
    def size_kb(self) -> float:
        return self.size / 1024.0

    @property
    def size_mb(self) -> float:
        return self.size / (1024.0 * 1024.0)

    @property
    def formatted_size(self) -> str:
        if self.size >= 1024 * 1024 and (self.size % (1024 * 1024) == 0):
            return f"{self.size // (1024 * 1024)} MB"
        if self.size >= 1024:
            return f"{self.size // 1024} KB"
        return f"{self.size} B"


def parse_size_str(val: str) -> int:
    """Parse size string with optional hex, K, or M suffix."""
    v = val.strip().upper()
    if v.startswith("0X"):
        return int(v, 16)
    if v.endswith("MB") or v.endswith("M"):
        num_str = v.rstrip("MB").rstrip("M")
        return int(num_str) * 1024 * 1024
    if v.endswith("KB") or v.endswith("K"):
        num_str = v.rstrip("KB").rstrip("K")
        return int(num_str) * 1024
    return int(v)


def parse_offset_str(val: str) -> Optional[int]:
    """Parse offset string (usually hex like 0x9000)."""
    v = val.strip()
    if not v:
        return None
    if v.lower().startswith("0x"):
        return int(v, 16)
    return int(v)


def parse_csv_partitions(csv_path: Path, table_offset: int = 0x8000) -> List[PartitionEntry]:
    """Parse CSV partition table and auto-compute contiguous offsets if omitted."""
    if not csv_path.is_file():
        return []

    partitions = []
    # ESP-IDF default: first partition starts at table_offset + 0x1000
    current_offset = table_offset + 0x1000

    with open(csv_path, "r", encoding="utf-8") as f:
        for line in f:
            clean = line.strip()
            if not clean or clean.startswith("#"):
                continue

            parts = [p.strip() for p in clean.split(",")]
            if len(parts) < 5:
                continue

            name = parts[0]
            ptype = parts[1].lower()
            subtype = parts[2].lower()
            offset_raw = parts[3]
            size_raw = parts[4]
            flags = parts[5].strip() if len(parts) > 5 else ""

            size = parse_size_str(size_raw)
            explicit_offset = parse_offset_str(offset_raw)

            if explicit_offset is not None:
                offset = explicit_offset
                current_offset = offset + size
            else:
                # Alignment rules: app requires 64KB (0x10000), data requires 4KB (0x1000)
                align = 0x10000 if ptype == "app" else 0x1000
                if current_offset % align != 0:
                    current_offset += align - (current_offset % align)
                offset = current_offset
                current_offset += size

            partitions.append(PartitionEntry(
                name=name,
                type=ptype,
                subtype=subtype,
                offset=offset,
                size=size,
                flags=flags,
            ))

    return partitions


def audit_partition_invariants(
    partitions: List[PartitionEntry],
    flash_size_bytes: int = 0x800000,
) -> List[str]:
    """Audit partition boundaries against physical hardware and MMU invariants."""
    warnings = []

    if not partitions:
        warnings.append("No partitions found in partition table.")
        return warnings

    # 1. Check each partition alignment and bounds
    for p in partitions:
        # 4KB sector alignment
        if p.offset % 0x1000 != 0:
            warnings.append(
                f"Partition '{p.name}' offset 0x{p.offset:X} is not 4KB sector-aligned (mod 0x1000 = 0x{p.offset % 0x1000:X})."
            )

        # 64KB MMU mapping alignment for app partitions
        if p.type == "app" and (p.offset % 0x10000 != 0):
            warnings.append(
                f"App partition '{p.name}' offset 0x{p.offset:X} is not 64KB MMU-aligned (mod 0x10000 = 0x{p.offset % 0x10000:X})."
            )

        # Size must be multiple of 4KB
        if p.size % 0x1000 != 0:
            warnings.append(
                f"Partition '{p.name}' size 0x{p.size:X} ({p.size_kb:.1f} KB) is not a multiple of 4KB flash sector size."
            )

    # 2. Overlap checks
    sorted_parts = sorted(partitions, key=lambda x: x.offset)
    for i in range(len(sorted_parts) - 1):
        p1 = sorted_parts[i]
        p2 = sorted_parts[i + 1]
        if p1.end_offset > p2.offset:
            overlap = p1.end_offset - p2.offset
            warnings.append(
                f"OVERLAP DETECTED: '{p1.name}' (0x{p1.offset:X}-0x{p1.end_offset:X}) overlaps '{p2.name}' (starts 0x{p2.offset:X}) by {overlap:,} bytes."
            )

    # 3. Flash size bounds check
    last_end = max(p.end_offset for p in partitions)
    if last_end > flash_size_bytes:
        excess = last_end - flash_size_bytes
        warnings.append(
            f"FLASH OVERFLOW: Partitions extend to 0x{last_end:X} ({last_end / (1024*1024):.2f} MB), exceeding physical flash size 0x{flash_size_bytes:X} ({flash_size_bytes / (1024*1024):.2f} MB) by {excess:,} bytes."
        )

    return warnings


def render_partition_bar(
    partitions: List[PartitionEntry],
    flash_size_bytes: int = 0x800000,
    width: int = 60,
) -> Tuple[str, str]:
    """Generate visual ASCII allocation block representation of physical SPI flash."""
    if not partitions or flash_size_bytes <= 0:
        return "[Empty Flash]", "0% Allocated"

    total_allocated = sum(p.size for p in partitions)
    # Include partition table + bootloader headroom (~36KB)
    headroom = 0x9000
    total_used = total_allocated + headroom
    unallocated = max(0, flash_size_bytes - total_used)

    pct_used = (total_used / flash_size_bytes) * 100.0
    pct_unalloc = (unallocated / flash_size_bytes) * 100.0

    bar_items = []
    # Add bootloader & partition table block
    bar_items.append("[BOOT+PART: 36KB]")
    for p in partitions:
        bar_items.append(f"[{p.name.upper()}: {p.formatted_size}]")
    if unallocated > 0:
        bar_items.append(f"[FREE: {unallocated // 1024} KB]")

    summary = (
        f"Flash Die Span: {total_used / (1024*1024):.3f} MB / {flash_size_bytes / (1024*1024):.3f} MB "
        f"({pct_used:.1f}% Allocated, {pct_unalloc:.1f}% Free)"
    )

    return "".join(bar_items), summary


def render_partition_table_rich(
    partitions: List[PartitionEntry],
    flash_size_bytes: int = 0x800000,
    console: Optional["Console"] = None,
    source_label: str = "partitions.csv",
) -> None:
    """Render formatted Rich table of discovered partitions and alignment health."""
    if not HAVE_RICH or not console:
        print(f"\n--- PARTITION TABLE ({source_label}) ---")
        for p in partitions:
            print(f"  {p.name:<12} {p.type:<6} {p.subtype:<10} 0x{p.offset:08X} - 0x{p.end_offset:08X} ({p.formatted_size:>8})")
        bar_str, summary = render_partition_bar(partitions, flash_size_bytes)
        print(f"\n{summary}\n")
        return

    table = Table(
        box=box.ROUNDED,
        width=TERM_WIDTH,
        header_style="bold bright_cyan",
        title=f"[bold white]Physical Flash Partition Map[/]\n[dim]Source: {source_label}[/]",
        show_lines=False,
        pad_edge=False,
    )
    table.add_column("Name", style="bold white", width=12)
    table.add_column("Type", style="cyan", width=8)
    table.add_column("Subtype", style="blue", width=10)
    table.add_column("Start Offset", style="dim", width=12, justify="right")
    table.add_column("End Offset", style="dim", width=12, justify="right")
    table.add_column("Size", style="bold green", width=10, justify="right")
    table.add_column("Flags", style="yellow", width=8, justify="center")

    for p in partitions:
        flags_str = p.flags if p.flags else "-"
        table.add_row(
            p.name,
            p.type,
            p.subtype,
            f"0x{p.offset:08X}",
            f"0x{p.end_offset:08X}",
            p.formatted_size,
            flags_str,
        )

    console.print(table)

    bar_str, summary = render_partition_bar(partitions, flash_size_bytes)
    panel = Panel(
        f"[dim]{bar_str}[/]\n\n[bold white]{summary}[/]",
        title="[bold cyan]Flash Memory Allocation[/]",
        border_style="cyan",
        box=box.ROUNDED,
        width=TERM_WIDTH,
    )
    console.print(panel)


def select_partition_interactive(
    partitions: List[PartitionEntry],
    console: Optional["Console"],
    title: str = "Select Target Partition",
) -> Optional[PartitionEntry]:
    """Interactively select a partition from the auto-discovered list."""
    if not partitions:
        return None

    if not HAVE_RICH or not console or not sys.stdin.isatty():
        print(f"\n--- {title} ---")
        for i, p in enumerate(partitions):
            print(f"  [{i+1}] {p.name:<12} ({p.type}/{p.subtype}, 0x{p.offset:08X}, {p.formatted_size})")
        print("  [B] Cancel / Back")
        try:
            choice = input(f"Select partition [1-{len(partitions)}, B=Cancel]: ").strip().upper()
            if choice in ("B", "BACK", "Q", "QUIT", "ESC", ""):
                return None
            idx = int(choice) - 1
            if 0 <= idx < len(partitions):
                return partitions[idx]
        except (ValueError, KeyboardInterrupt, EOFError):
            return None
        return None

    # Interactive Rich loop
    selected_idx = 0
    total_rows = len(partitions) + 1  # partitions + Back

    try:
        import msvcrt

        def read_nav_key() -> str:
            ch = msvcrt.getch()
            if ch in (b"\x00", b"\xe0"):
                ch2 = msvcrt.getch()
                if ch2 == b"H":
                    return "UP"
                if ch2 == b"P":
                    return "DOWN"
            if ch in (b"\r", b"\n"):
                return "ENTER"
            if ch in (b"\x1b", b"b", b"B"):
                return "BACK"
            if ch in (b"q", b"Q"):
                return "QUIT"
            return ch.decode("utf-8", errors="ignore").upper()

    except ImportError:
        def read_nav_key() -> str:
            line = sys.stdin.readline().strip().upper()
            return line if line else "ENTER"

    while True:
        console.clear()
        sub_table = Table(
            box=box.ROUNDED,
            width=TERM_WIDTH,
            header_style="bold bright_cyan",
            title=f"[bold white]{title}[/]\n[dim]Choose an auto-discovered partition from active table[/]",
            show_lines=False,
            pad_edge=False,
        )
        sub_table.add_column(" ", justify="center", width=2)
        sub_table.add_column("#", justify="center", style="bold white", width=3)
        sub_table.add_column("Partition", style="bold", width=14)
        sub_table.add_column("Type/Subtype", style="cyan", width=16)
        sub_table.add_column("Offset", style="dim", width=14, justify="right")
        sub_table.add_column("Size", style="green", width=12, justify="right")

        for i, p in enumerate(partitions):
            is_sel = (i == selected_idx)
            marker = ">" if is_sel else " "
            row_style = "bold white on blue" if is_sel else ""

            sub_table.add_row(
                marker,
                str(i + 1),
                p.name,
                f"{p.type}/{p.subtype}",
                f"0x{p.offset:08X}",
                p.formatted_size,
                style=row_style,
            )

        back_is_sel = (selected_idx == len(partitions))
        back_marker = ">" if back_is_sel else " "
        back_style = "bold white on blue" if back_is_sel else "dim"
        sub_table.add_row(
            back_marker,
            "B",
            "[yellow]Cancel / Back[/]",
            "-",
            "-",
            "-",
            style=back_style,
        )

        console.print(sub_table)
        footer = Text("  [↑/↓] Navigate   [Enter] Select   [1-9/B] Quick-Key   [Esc/B] Cancel", style="dim")
        console.print(footer)

        key = read_nav_key()
        if key == "UP":
            selected_idx = (selected_idx - 1) % total_rows
        elif key == "DOWN":
            selected_idx = (selected_idx + 1) % total_rows
        elif key in ("ENTER", "SPACE"):
            if selected_idx == len(partitions):
                return None
            return partitions[selected_idx]
        elif key in ("BACK", "QUIT", "ESC"):
            return None
        else:
            if key.isdigit():
                val = int(key) - 1
                if 0 <= val < len(partitions):
                    return partitions[val]


def run_partition_manager_menu(config: H1OSConfig, console: Optional["Console"] = None) -> None:
    """Run interactive Partition Manager sub-menu loop."""
    part_file = config.partition_file
    if not part_file or not part_file.is_file():
        # Fallback search in project root or component
        cand = config.app_root / "partitions.csv"
        if cand.is_file():
            part_file = cand
        else:
            cand_comp = config.component_dir / "partitions.csv"
            if cand_comp.is_file():
                part_file = cand_comp

    partitions = parse_csv_partitions(part_file) if part_file else []

    MENU_ITEMS = [
        {"key": "1", "label": "View Flash Memory Map & Table", "desc": "Display table with offsets and physical allocation bar"},
        {"key": "2", "label": "Erase Specific Partition", "desc": "Wipe nvs, epd_frame, storage, or otadata partition"},
        {"key": "3", "label": "Dump Partition (Bin / Hex / View)", "desc": "Extract partition content as .bin, .hex log, or console view"},
        {"key": "4", "label": "Flash Binary Image to Partition", "desc": "Write standalone .bin directly to partition offset"},
        {"key": "5", "label": "Inspect OTA Status & Active Slot", "desc": "Read otadata rollback state and active boot slot"},
        {"key": "6", "label": "Switch Active OTA Boot Slot", "desc": "Toggle active boot slot between ota_0 and ota_1"},
        {"key": "7", "label": "Audit Sector Alignment Invariants", "desc": "Verify 4KB sector and 64KB MMU alignment rules"},
        {"key": "B", "label": "Back to Main Menu", "desc": "Return to main developer console"},
    ]

    selected_idx = 0
    total_items = len(MENU_ITEMS)

    try:
        import msvcrt

        def read_menu_key() -> str:
            ch = msvcrt.getch()
            if ch in (b"\x00", b"\xe0"):
                ch2 = msvcrt.getch()
                if ch2 == b"H":
                    return "UP"
                if ch2 == b"P":
                    return "DOWN"
            if ch in (b"\r", b"\n"):
                return "ENTER"
            if ch in (b"\x1b", b"b", b"B"):
                return "BACK"
            if ch in (b"q", b"Q"):
                return "QUIT"
            return ch.decode("utf-8", errors="ignore").upper()

    except ImportError:
        def read_menu_key() -> str:
            line = sys.stdin.readline().strip().upper()
            return line if line else "ENTER"

    while True:
        if not HAVE_RICH or not console or not sys.stdin.isatty():
            print("\n" + "=" * 78)
            print("  H1OS Flash Partition Manager")
            print(f"  Source: {part_file.name if part_file else 'None'} ({len(partitions)} partitions)")
            print(f"  Device: {config.chip.upper()} | Port: {config.port}")
            print("=" * 78)
            for item in MENU_ITEMS:
                print(f"  [{item['key']}] {item['label']} - {item['desc']}")
            print("=" * 78)
            try:
                choice = input("Select partition operation [1-7, B=Back]: ").strip().upper()
            except (KeyboardInterrupt, EOFError):
                break
            action_key = choice if choice else "1"
        else:
            console.clear()

            sub_table = Table(
                box=box.ROUNDED,
                width=TERM_WIDTH,
                header_style="bold bright_cyan",
                title=(
                    f"[bold white]H1OS Flash Partition Manager[/]\n"
                    f"[dim]Table: {part_file.name if part_file else 'None'} ({len(partitions)} auto-discovered partitions) | "
                    f"Port: {config.port}[/]"
                ),
                show_lines=False,
                pad_edge=False,
            )
            sub_table.add_column(" ", justify="center", width=2)
            sub_table.add_column("#", justify="center", style="bold white", width=3)
            sub_table.add_column("Operation", style="bold", width=36)
            sub_table.add_column("Description", style="dim", width=32)

            for i, item in enumerate(MENU_ITEMS):
                is_sel = (i == selected_idx)
                marker = ">" if is_sel else " "
                row_style = "bold white on blue" if is_sel else ("yellow" if item["key"] == "B" else "")

                sub_table.add_row(
                    marker,
                    item["key"],
                    item["label"],
                    item["desc"],
                    style=row_style,
                )

            console.print(sub_table)
            footer = Text("  [↑/↓] Navigate   [Enter] Select   [1-7/B] Quick-Key   [Esc/B] Back", style="dim")
            console.print(footer)

            key = read_menu_key()
            if key == "UP":
                selected_idx = (selected_idx - 1) % total_items
                continue
            elif key == "DOWN":
                selected_idx = (selected_idx + 1) % total_items
                continue
            elif key in ("ENTER", "SPACE"):
                action_key = MENU_ITEMS[selected_idx]["key"]
            elif key in ("BACK", "QUIT", "ESC"):
                break
            else:
                action_key = key

        # Dispatch action
        if action_key in ("B", "BACK", "Q", "QUIT", "ESC"):
            break

        elif action_key == "1":
            # View Map & Allocation Bar
            if console:
                console.clear()
            render_partition_table_rich(
                partitions,
                flash_size_bytes=0x800000,
                console=console,
                source_label=str(part_file),
            )
            pause_prompt(console)

        elif action_key == "2":
            # Erase Specific Partition
            target = select_partition_interactive(partitions, console, title="Select Partition to Erase")
            if target:
                confirmed = prompt_confirmation(
                    console,
                    f"ERASE PARTITION: '{target.name}' at 0x{target.offset:08X} ({target.formatted_size}) on {config.chip.upper()}?",
                )
                if confirmed:
                    if console:
                        console.print(f"\n[cyan]Erasing partition '{target.name}' on {config.port}...[/]")
                    ok, msg = execute_parttool_erase(config, target.name)
                    if ok:
                        if console:
                            console.print(f"[bold green]SUCCESS:[/] {msg}")
                        else:
                            print(f"SUCCESS: {msg}")
                    else:
                        if console:
                            console.print(f"[bold red]ERROR:[/] {msg}")
                        else:
                            print(f"ERROR: {msg}")
                else:
                    if console:
                        console.print("[yellow]Erase cancelled.[/]")
            pause_prompt(console)

        elif action_key == "3":
            # Dump Partition (Bin / Hex / View)
            target = select_partition_interactive(partitions, console, title="Select Partition to Dump")
            if target:
                dump_mode = prompt_dump_mode(console)
                if dump_mode:
                    dumps_dir = config.audit_log_dir / "dumps"
                    dumps_dir.mkdir(parents=True, exist_ok=True)
                    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
                    temp_bin = dumps_dir / f"tmp_{target.name}_{timestamp}.bin"

                    if console:
                        console.print(f"\n[cyan]Reading {target.formatted_size} from partition '{target.name}' over {config.port}...[/]")
                    ok, msg = execute_parttool_read(config, target.name, temp_bin)

                    if ok and temp_bin.is_file():
                        raw_bytes = temp_bin.read_bytes()

                        if dump_mode == "bin":
                            final_bin = dumps_dir / f"dump_{target.name}_{timestamp}.bin"
                            temp_bin.rename(final_bin)
                            if console:
                                console.print(f"[bold green]SUCCESS:[/] Raw binary saved to [cyan]{final_bin}[/]")
                            else:
                                print(f"SUCCESS: Raw binary saved to {final_bin}")
                            pause_prompt(console)

                        elif dump_mode == "hex":
                            final_hex = dumps_dir / f"dump_{target.name}_{timestamp}.hex"
                            hex_str = format_canonical_hexdump(raw_bytes, base_offset=target.offset)
                            final_hex.write_text(hex_str, encoding="utf-8")
                            temp_bin.unlink(missing_ok=True)
                            if console:
                                console.print(f"[bold green]SUCCESS:[/] Formatted hex log saved to [cyan]{final_hex}[/]")
                            else:
                                print(f"SUCCESS: Formatted hex log saved to {final_hex}")
                            pause_prompt(console)

                        elif dump_mode == "view":
                            temp_bin.unlink(missing_ok=True)
                            render_live_hex_view(
                                raw_bytes,
                                partition_name=target.name,
                                base_offset=target.offset,
                                console=console,
                            )
                    else:
                        temp_bin.unlink(missing_ok=True)
                        if console:
                            console.print(f"[bold red]ERROR:[/] {msg}")
                        else:
                            print(f"ERROR: {msg}")
                        pause_prompt(console)

        elif action_key == "4":
            # Flash Binary to Partition
            target = select_partition_interactive(partitions, console, title="Select Destination Partition")
            if target:
                image_path = prompt_file_path(console, f"Enter path to binary image to flash into '{target.name}':")
                if image_path and image_path.is_file():
                    img_size = image_path.stat().st_size
                    if img_size > target.size:
                        if console:
                            console.print(
                                f"[bold red]ERROR:[/] Image size ({img_size:,} bytes) exceeds partition '{target.name}' capacity ({target.size:,} bytes)!"
                            )
                        else:
                            print(f"ERROR: Image exceeds partition capacity!")
                    else:
                        confirmed = prompt_confirmation(
                            console,
                            f"Flash image ({img_size:,} bytes) into partition '{target.name}' (0x{target.offset:08X}) on {config.chip.upper()}?",
                        )
                        if confirmed:
                            if console:
                                console.print(f"[cyan]Flashing {image_path.name} to '{target.name}'...[/]")
                            ok, msg = execute_parttool_write(config, target.name, image_path)
                            if ok:
                                if console:
                                    console.print(f"[bold green]SUCCESS:[/] {msg}")
                                else:
                                    print(f"SUCCESS: {msg}")
                            else:
                                if console:
                                    console.print(f"[bold red]ERROR:[/] {msg}")
                                else:
                                    print(f"ERROR: {msg}")
                else:
                    if console:
                        console.print("[yellow]Invalid or missing file. Flashing cancelled.[/]")
            pause_prompt(console)

        elif action_key == "5":
            # Inspect OTA Status
            if console:
                console.print(f"\n[cyan]Querying otadata status from {config.port}...[/]")
            ok, msg = execute_otatool_read(config)
            if ok:
                if console:
                    console.print(Panel(msg, title="[bold green]OTA State Machine[/]", border_style="green", width=TERM_WIDTH))
                else:
                    print(f"\n--- OTA State Machine ---\n{msg}\n")
            else:
                if console:
                    console.print(f"[bold red]ERROR:[/] {msg}")
                else:
                    print(f"ERROR: {msg}")
            pause_prompt(console)

        elif action_key == "6":
            # Switch Active OTA Boot Slot
            slot_choice = prompt_ota_slot(console)
            if slot_choice is not None:
                confirmed = prompt_confirmation(console, f"Switch active boot slot to slot {slot_choice} (ota_{slot_choice})?")
                if confirmed:
                    if console:
                        console.print(f"[cyan]Switching boot partition to slot {slot_choice} on {config.port}...[/]")
                    ok, msg = execute_otatool_switch(config, slot_choice)
                    if ok:
                        if console:
                            console.print(f"[bold green]SUCCESS:[/] {msg}")
                        else:
                            print(f"SUCCESS: {msg}")
                    else:
                        if console:
                            console.print(f"[bold red]ERROR:[/] {msg}")
                        else:
                            print(f"ERROR: {msg}")
            pause_prompt(console)

        elif action_key == "7":
            # Audit Sector Alignment
            if console:
                console.clear()
            warnings = audit_partition_invariants(partitions, flash_size_bytes=0x800000)
            if not warnings:
                msg = "[bold green]PASS:[/] All partitions strictly satisfy 4KB sector alignment, 64KB MMU app alignment, zero overlaps, and flash die ceiling."
                if console:
                    console.print(Panel(msg, title="[bold green]Physical Alignment Audit[/]", border_style="green", width=TERM_WIDTH))
                else:
                    print(f"\nPASS: All partitions aligned and within bounds.\n")
            else:
                warn_text = "\n".join(f"• [bold red]{w}[/]" for w in warnings)
                if console:
                    console.print(Panel(warn_text, title="[bold red]Alignment Warnings Detected[/]", border_style="red", width=TERM_WIDTH))
                else:
                    print(f"\nALIGNMENT WARNINGS:\n" + "\n".join(warnings) + "\n")
            pause_prompt(console)


def prompt_dump_mode(console: Optional["Console"]) -> Optional[str]:
    """Prompt user to select partition dump output format."""
    options = [
        ("1", "bin", "Raw Binary Stream (.bin)"),
        ("2", "hex", "Formatted Canonical Hex Log (.hex)"),
        ("3", "view", "Live Interactive Terminal Hex Inspector"),
    ]

    if not HAVE_RICH or not console or not sys.stdin.isatty():
        print("\nSelect Dump Output Format:")
        for k, _, label in options:
            print(f"  [{k}] {label}")
        print("  [B] Cancel")
        try:
            c = input("Choice [1-3, B=Cancel]: ").strip().upper()
            for k, mode, _ in options:
                if c == k:
                    return mode
        except (KeyboardInterrupt, EOFError):
            return None
        return None

    console.print("\n[bold white]Select Dump Output Format:[/]")
    for k, _, label in options:
        console.print(f"  [bold cyan][{k}][/] {label}")
    console.print("  [yellow][B][/] Cancel")

    try:
        c = input("\nChoice [1-3, B=Cancel]: ").strip().upper()
        for k, mode, _ in options:
            if c == k:
                return mode
    except (KeyboardInterrupt, EOFError):
        return None
    return None


def prompt_ota_slot(console: Optional["Console"]) -> Optional[int]:
    """Prompt user to select OTA boot slot (0 or 1)."""
    if console:
        console.print("\n[bold white]Select Target OTA Boot Slot:[/]")
        console.print("  [bold cyan][0][/] Slot 0 (ota_0)")
        console.print("  [bold cyan][1][/] Slot 1 (ota_1)")
        console.print("  [yellow][B][/] Cancel")
    else:
        print("\nSelect Target OTA Boot Slot [0=ota_0, 1=ota_1, B=Cancel]:")

    try:
        c = input("Choice: ").strip().upper()
        if c == "0":
            return 0
        if c == "1":
            return 1
    except (KeyboardInterrupt, EOFError):
        return None
    return None


def prompt_file_path(console: Optional["Console"], prompt_text: str) -> Optional[Path]:
    """Prompt user for a filesystem path."""
    if console:
        console.print(f"\n[bold white]{prompt_text}[/] ", end="")
    else:
        print(f"\n{prompt_text} ", end="")
    try:
        raw = input().strip().strip('"').strip("'")
        if raw:
            p = Path(raw).resolve()
            return p
    except (KeyboardInterrupt, EOFError):
        return None
    return None


def prompt_confirmation(console: Optional["Console"], message: str) -> bool:
    """Prompt user for explicit yes/no confirmation."""
    if console:
        console.print(f"\n[bold yellow]CONFIRMATION REQUIRED:[/] {message}")
        console.print("[yellow]Type 'y' or 'yes' to proceed: [/]", end="")
    else:
        print(f"\nCONFIRMATION REQUIRED: {message}")
        print("Type 'y' or 'yes' to proceed: ", end="")
    try:
        c = input().strip().lower()
        return c in ("y", "yes")
    except (KeyboardInterrupt, EOFError):
        return False


def pause_prompt(console: Optional["Console"]) -> None:
    """Pause before clearing or returning to sub-menu."""
    if console:
        console.print("\n[dim]Press Enter to continue...[/]", end="")
    else:
        print("\nPress Enter to continue...", end="")
    try:
        input()
    except (KeyboardInterrupt, EOFError):
        pass


def main():
    parser = argparse.ArgumentParser(description="H1OS Flash Partition Manager")
    parser.add_argument("-C", "--project-dir", dest="project_dir", default=None, help="Application project root")
    parser.add_argument("-c", "--config", dest="config", default=None, help="Explicit path to h1os.ini")
    parser.add_argument("--map", action="store_true", help="Display partition map and memory layout table")
    parser.add_argument("--audit", action="store_true", help="Audit sector and MMU alignment invariants")
    parser.add_argument("--erase", dest="erase_part", metavar="PARTITION", help="Erase a specific partition on device")
    parser.add_argument("--dump", dest="dump_part", metavar="PARTITION", help="Dump a specific partition from device")
    parser.add_argument("--format", dest="dump_format", choices=["bin", "hex", "view"], default="hex", help="Dump format")
    parser.add_argument("--flash", dest="flash_part", metavar="PARTITION", help="Flash binary image to partition")
    parser.add_argument("-i", "--input", dest="input_file", help="Input binary image file for flashing")
    parser.add_argument("--ota-info", action="store_true", help="Query OTA boot slot and state machine")
    parser.add_argument("--ota-switch", dest="ota_slot", type=int, choices=[0, 1], help="Switch active OTA boot slot")
    args = parser.parse_args()

    config = H1OSConfig(project_dir=args.project_dir, config_path=args.config)
    console = Console(width=TERM_WIDTH) if HAVE_RICH else None

    # CLI direct commands
    part_file = config.partition_file or (config.app_root / "partitions.csv")
    partitions = parse_csv_partitions(part_file) if part_file and part_file.is_file() else []

    if args.map:
        render_partition_table_rich(partitions, console=console, source_label=str(part_file))
        return

    if args.audit:
        warnings = audit_partition_invariants(partitions)
        if not warnings:
            print("PASS: All partitions aligned and within bounds.")
        else:
            print("ALIGNMENT WARNINGS DETECTED:")
            for w in warnings:
                print(f"  • {w}")
        return

    if args.erase_part:
        ok, msg = execute_parttool_erase(config, args.erase_part)
        print(f"{'SUCCESS' if ok else 'ERROR'}: {msg}")
        return

    if args.ota_info:
        ok, msg = execute_otatool_read(config)
        print(msg)
        return

    if args.ota_slot is not None:
        ok, msg = execute_otatool_switch(config, args.ota_slot)
        print(f"{'SUCCESS' if ok else 'ERROR'}: {msg}")
        return

    # Default to interactive sub-menu
    run_partition_manager_menu(config, console)


if __name__ == "__main__":
    main()
