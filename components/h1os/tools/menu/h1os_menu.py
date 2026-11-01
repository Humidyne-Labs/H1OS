#!/usr/bin/env python3
"""
H1OS Interactive Developer Tooling Console (h1os_menu)
Version: 2.4.2
License: Apache-2.0

Interactive Rich console with arrow-key keyboard navigation
for release packaging, binary sizing, and esptool hardware operations.
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional

# Add tools directory to sys.path so we can import h1os_tool directly
TOOLS_DIR = Path(__file__).resolve().parent.parent
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

from h1os_tool import (
    H1OS_TOOLING_VERSION,
    H1OSConfig,
    check_tooling_dependencies,
    run_build,
    run_clean,
    run_erase,
    run_flash,
    run_pack,
    run_size,
    spawn_serial_monitor,
)

# Pre-flight check: display pip command if dependencies missing and exit safely
if not check_tooling_dependencies():
    sys.exit(1)

try:
    from rich import box
    from rich.console import Console, Group
    from rich.live import Live
    from rich.panel import Panel
    from rich.table import Table
    from rich.text import Text
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False

from partition.h1os_part import parse_csv_partitions, run_partition_manager_menu
from partition.part_backend import execute_dual_slot_deploy, execute_otatool_toggle

try:
    from menu.console_events import (
        ConsoleEventDispatcher,
        ConsoleEvent,
        EventType,
        get_single_key,
        restore_default_console_mode,
    )
except ImportError:
    from console_events import (
        ConsoleEventDispatcher,
        ConsoleEvent,
        EventType,
        get_single_key,
        restore_default_console_mode,
    )

VERSION = H1OS_TOOLING_VERSION
read_nav_key = get_single_key


def clear_screen() -> None:
    """Clear terminal screen to eliminate visual artifacts across menu transitions."""
    if os.name == "nt":
        os.system("cls")
    else:
        sys.stdout.write("\033[2J\033[H")
        sys.stdout.flush()


def run_interactive_choice_menu(
    console: Optional["Console"],
    title: str,
    subtitle: str,
    options: List[Dict[str, Any]],
    default_idx: int = 0,
    header_panel: Optional["Panel"] = None,
) -> Optional[Any]:
    """Interactive arrow-key navigable sub-menu eliminating numpad / key switching."""
    if not console or not sys.stdin.isatty():
        print(f"\n--- {title} ---")
        print(f"  {subtitle}")
        print("-" * 60)
        for opt in options:
            print(f"  [{opt['key']}] {opt['label']} - {opt.get('desc', '')}")
        print("-" * 60)
        try:
            choice = input(f"Select option [Enter={options[default_idx]['key']}, B=Back]: ").strip().upper()
        except (KeyboardInterrupt, EOFError):
            return None
        if not choice:
            return options[default_idx].get("value")
        for opt in options:
            if choice == opt["key"]:
                return opt.get("value")
        return None

    clear_screen()
    selected_idx = default_idx
    total_rows = len(options)

    def build_frame(idx: int) -> Group:
        sub_table = Table(
            box=box.ROUNDED,
            header_style="bold bright_cyan",
            title=f"[bold white]{title}[/]\n[dim]{subtitle}[/]",
            show_lines=False,
            pad_edge=False,
            expand=True,
        )
        sub_table.add_column(" ", justify="center", no_wrap=True, width=2)
        sub_table.add_column("#", justify="center", style="bold white", no_wrap=True, width=3)
        sub_table.add_column("Option", style="bold", ratio=3)
        sub_table.add_column("Details", style="dim", ratio=3)

        for i, item in enumerate(options):
            is_sel = (i == idx)
            marker = ">" if is_sel else " "
            row_style = "bold white on blue" if is_sel else ""
            if item.get("warning"):
                row_style = "bold white on red" if is_sel else "bold red"

            sub_table.add_row(
                marker,
                item["key"],
                item["label"],
                item.get("desc", ""),
                style=row_style,
            )

        footer = Text("  [↑/↓] Navigate   [→/Enter] Select   [←/Esc/B] Cancel   [Quick-Key] Direct Action", style="dim")
        if header_panel:
            return Group(header_panel, sub_table, footer)
        return Group(sub_table, footer)

    frame = build_frame(selected_idx)
    with Live(frame, console=console, auto_refresh=False, screen=False, transient=True) as live:
        with ConsoleEventDispatcher(enable_mouse=True, enable_resize=True) as dispatcher:
            while True:
                ev = dispatcher.get_event(timeout=0.05)
                if not ev:
                    continue

                if ev.type == EventType.SCROLL:
                    selected_idx = (selected_idx - ev.delta) % total_rows
                    live.update(build_frame(selected_idx), refresh=True)
                elif ev.type == EventType.RESIZE:
                    live.update(build_frame(selected_idx), refresh=True)
                elif ev.type == EventType.KEY:
                    key = ev.key
                    if key == "UP":
                        selected_idx = (selected_idx - 1) % total_rows
                        live.update(build_frame(selected_idx), refresh=True)
                    elif key == "DOWN":
                        selected_idx = (selected_idx + 1) % total_rows
                        live.update(build_frame(selected_idx), refresh=True)
                    elif key in ("ENTER", "SPACE", "RIGHT"):
                        return options[selected_idx].get("value")
                    elif key in ("B", "ESC", "Q", "QUIT", "CANCEL", "LEFT"):
                        return None
                    else:
                        for opt in options:
                            if key == opt["key"]:
                                return opt.get("value")


def build_header_panel(config: H1OSConfig) -> Panel:
    """Build pre-populated static header information panel."""
    port_label = config.port if config.port else "Auto-discover"
    app_root_str = str(config.app_root)
    if len(app_root_str) > 28:
        app_root_str = "..." + app_root_str[-25:]

    header_table = Table.grid(padding=(0, 2), expand=True)
    header_table.add_column("K1", style="bold cyan", no_wrap=True)
    header_table.add_column("V1")
    header_table.add_column("K2", style="bold cyan", no_wrap=True)
    header_table.add_column("V2")

    header_table.add_row(
        "Project:", f"[white]{app_root_str}[/]",
        "Silicon:", f"[bold white]{config.chip.upper()}[/]",
    )
    header_table.add_row(
        "Version:", f"[bold green]v{config.version}[/] ({config.git_commit})",
        "Serial :", f"{port_label} @ {config.baud}",
    )

    # Dynamic Profile Status rows
    prof_list = list(config.profiles.values())
    for i in range(0, len(prof_list), 2):
        p1 = prof_list[i]
        p1_built = p1.build_dir.is_dir() and (p1.build_dir / "project_description.json").is_file()
        p1_status = "[bold green]READY[/]" if p1_built else "[dim red]NOT BUILT[/]"
        k1 = f"{p1.name.capitalize()}:"
        v1 = f"{p1.build_dir.name}: {p1_status}"

        if i + 1 < len(prof_list):
            p2 = prof_list[i + 1]
            p2_built = p2.build_dir.is_dir() and (p2.build_dir / "project_description.json").is_file()
            p2_status = "[bold green]READY[/]" if p2_built else "[dim red]NOT BUILT[/]"
            k2 = f"{p2.name.capitalize()}:"
            v2 = f"{p2.build_dir.name}: {p2_status}"
        else:
            k2 = ""
            v2 = ""

        header_table.add_row(k1, v1, k2, v2)

    return Panel(
        header_table,
        title="[bold white]H1OS Firmware & Packaging Console[/]",
        border_style="cyan",
        box=box.ROUNDED,
    )


def build_console_frame(
    config: H1OSConfig,
    selected_idx: int,
    menu_items: List[Dict[str, str]],
    header_panel: Optional[Panel] = None,
) -> Group:
    """Build the frame with pre-populated header and highlighted selection."""
    if header_panel is None:
        header_panel = build_header_panel(config)

    # 2. Operations Table (auto-sized full-width columns)
    ops_table = Table(
        box=box.ROUNDED,
        header_style="bold bright_cyan",
        show_lines=False,
        pad_edge=False,
        expand=True,
    )
    ops_table.add_column(" ", justify="center", no_wrap=True, width=2)
    ops_table.add_column("#", justify="center", style="bold white", no_wrap=True, width=3)
    ops_table.add_column("Operation", style="bold", ratio=4)
    ops_table.add_column("Target Build", style="dim", ratio=2)
    ops_table.add_column("Backend Engine", style="cyan", ratio=2)

    for i, item in enumerate(menu_items):
        is_sel = (i == selected_idx)
        marker = ">" if is_sel else " "
        row_style = "bold white on blue" if is_sel else ""

        ops_table.add_row(
            marker,
            item["key"],
            item["label"],
            item["target"],
            item["engine"],
            style=row_style,
        )

    # 3. Navigation Help Footer
    footer_text = Text(
        "  [↑/↓] Navigate   [→/Enter] Select   [←/Esc/Q] Exit   [Quick-Key] Direct Action",
        style="dim",
    )
    return Group(header_panel, ops_table, footer_text)


def render_console_frame(config: H1OSConfig, console: "Console", selected_idx: int, menu_items: List[Dict[str, str]]) -> None:
    """Render the full 78-column frame with header and highlighted selection."""
    console.print(build_console_frame(config, selected_idx, menu_items))


def find_compiled_app_bin(profile, app_name: Optional[str] = None) -> Optional[Path]:
    """Locate compiled application binary in build directory."""
    if not profile.build_dir.is_dir():
        return None
    if app_name:
        cand = profile.build_dir / f"{app_name}.bin"
        if cand.is_file():
            return cand
    for b in profile.build_dir.glob("*.bin"):
        if b.name not in ("bootloader.bin", "partition-table.bin", "ota_data_initial.bin"):
            return b
    return None


def get_ota_app_partitions(config: H1OSConfig) -> List[Any]:
    """Retrieve app partitions matching ota_* subtype from partition table."""
    part_file = config.partition_file or (config.app_root / "partitions.csv")
    if part_file and part_file.is_file():
        parts = parse_csv_partitions(part_file)
        return [p for p in parts if p.type == "app" and p.subtype.startswith("ota_")]
    return []


def build_dynamic_menu_items(config: H1OSConfig) -> List[Dict[str, str]]:
    """Auto-populate operations table dynamically based on configured build profiles.

    When 2 or more profiles exist, operations collapse into clean single rows that open
    an auto-populated profile selection sub-menu. If only 1 profile exists, actions target
    it directly.
    """
    menu_items = []
    KEY_POOL = [
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "A", "B", "C", "F", "G", "H", "J", "K", "L",
        "M", "N", "R", "S", "U", "V", "W", "X", "Y", "Z"
    ]
    key_idx = 0

    def next_key() -> str:
        nonlocal key_idx
        if key_idx < len(KEY_POOL):
            k = KEY_POOL[key_idx]
            key_idx += 1
            return k
        return "-"

    has_multi_profiles = len(config.profiles) >= 2
    target_label = "/".join(config.profiles.keys()) if config.profiles else "dev"

    if has_multi_profiles:
        # Multi-profile collapsed menu (opens sub-menu on selection)
        menu_items.append({
            "key": next_key(),
            "label": "Build Firmware",
            "target": target_label,
            "engine": "idf.py build",
            "action": "build",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Reconfigure Build Profile",
            "target": target_label,
            "engine": "idf.py reconfigure",
            "action": "reconfig",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Clean Build Directory",
            "target": target_label,
            "engine": "rmtree",
            "action": "clean",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Clean & Full Rebuild",
            "target": target_label,
            "engine": "erase & rebuild",
            "action": "clean_rebuild",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Size Audit Diagnostic",
            "target": target_label,
            "engine": "h1os_size.py",
            "action": "size",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Package Release Bundle",
            "target": target_label,
            "engine": "h1os_pack.py",
            "action": "pack",
        })
        menu_items.append({
            "key": next_key(),
            "label": "Flash Firmware to Device",
            "target": target_label,
            "engine": "esptool write",
            "action": "flash",
        })
    else:
        # Single profile direct actions
        single_name = list(config.profiles.keys())[0] if config.profiles else "dev"
        single_prof = config.profiles.get(single_name)
        target_dir = single_prof.build_dir.name if single_prof else f"build_{single_name}"

        menu_items.append({
            "key": next_key(),
            "label": f"Build {single_name.upper()} Firmware",
            "target": target_dir,
            "engine": "idf.py build",
            "action": f"build:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Reconfigure {single_name.upper()} Profile",
            "target": target_dir,
            "engine": "idf.py reconfigure",
            "action": f"reconfig:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Clean {single_name.upper()} Build Directory",
            "target": target_dir,
            "engine": "rmtree",
            "action": f"clean:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Clean & Full Rebuild ({single_name.upper()})",
            "target": target_dir,
            "engine": "erase & rebuild",
            "action": f"clean_rebuild:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Size Audit - {single_name.upper()}",
            "target": target_dir,
            "engine": "h1os_size.py",
            "action": f"size:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Package {single_name.upper()} Release",
            "target": target_dir,
            "engine": "h1os_pack.py",
            "action": f"pack:{single_name}",
        })
        menu_items.append({
            "key": next_key(),
            "label": f"Flash {single_name.upper()} Build",
            "target": target_dir,
            "engine": "esptool write",
            "action": f"flash:{single_name}",
        })

    # Conditional Dual-Slot OTA Deployment & Quick Toggle
    ota_parts = get_ota_app_partitions(config)
    prof_list = list(config.profiles.values())

    # 1. Dual-Slot deploy: Exactly 2 profiles AND both .bin files compiled on disk
    if len(prof_list) == 2 and len(ota_parts) >= 2:
        p1, p2 = prof_list[0], prof_list[1]
        bin1 = find_compiled_app_bin(p1, config.app_name)
        bin2 = find_compiled_app_bin(p2, config.app_name)
        if bin1 and bin2:
            menu_items.append({
                "key": "D",
                "label": f"Deploy Dual-Slot ({p1.name}->ota_0, {p2.name}->ota_1)",
                "target": "ota_0/ota_1",
                "engine": "parttool write",
                "action": f"dual_deploy:{p1.name}:{p2.name}",
            })

    # 2. Quick toggle: At least 2 OTA partitions in partition table
    if len(ota_parts) >= 2:
        menu_items.append({
            "key": "T",
            "label": "Toggle Active OTA Slot",
            "target": "ota_0 <-> ota_1",
            "engine": "otatool switch",
            "action": "ota_toggle",
        })

    # Hardware maintenance & Partition Management
    part_target = config.partition_file.name if config.partition_file else "partitions.csv"
    menu_items.append({
        "key": "P",
        "label": "Flash Partition Manager",
        "target": part_target,
        "engine": "parttool/otatool",
        "action": "partition_menu",
    })
    menu_items.append({
        "key": "M",
        "label": "Spawn Serial Monitor",
        "target": config.port or "Auto-detect",
        "engine": "h1os_monitor.py",
        "action": "monitor",
    })
    menu_items.append({
        "key": "E",
        "label": "Erase Entire Flash Die",
        "target": config.chip.upper(),
        "engine": "esptool erase",
        "action": "erase",
    })
    menu_items.append({
        "key": "Q",
        "label": "Quit Console",
        "target": "-",
        "engine": "-",
        "action": "quit",
    })

    return menu_items


def run_interactive_menu(
    config: H1OSConfig,
    console: "Console",
    header_panel: Optional[Panel] = None,
) -> str:
    """Run real-time keyboard navigation loop with arrow keys and smooth Live rendering."""
    clear_screen()
    menu_items = build_dynamic_menu_items(config)
    selected_idx = 0

    if header_panel is None:
        header_panel = build_header_panel(config)

    frame = build_console_frame(config, selected_idx, menu_items, header_panel=header_panel)
    total_items = len(menu_items)
    with Live(frame, console=console, auto_refresh=False, screen=False, transient=True) as live:
        with ConsoleEventDispatcher(enable_mouse=True, enable_resize=True) as dispatcher:
            while True:
                ev = dispatcher.get_event(timeout=0.05)
                if not ev:
                    continue

                if ev.type == EventType.SCROLL:
                    selected_idx = (selected_idx - ev.delta) % total_items
                    live.update(build_console_frame(config, selected_idx, menu_items, header_panel=header_panel), refresh=True)
                elif ev.type == EventType.RESIZE:
                    live.update(build_console_frame(config, selected_idx, menu_items, header_panel=header_panel), refresh=True)
                elif ev.type == EventType.KEY:
                    key = ev.key
                    if key == "UP":
                        selected_idx = (selected_idx - 1) % total_items
                        live.update(build_console_frame(config, selected_idx, menu_items, header_panel=header_panel), refresh=True)
                    elif key == "DOWN":
                        selected_idx = (selected_idx + 1) % total_items
                        live.update(build_console_frame(config, selected_idx, menu_items, header_panel=header_panel), refresh=True)
                    elif key in ("ENTER", "SPACE", "RIGHT"):
                        return menu_items[selected_idx]["action"]
                    elif key in ("Q", "ESC", "QUIT"):
                        return "quit"
                    elif key == "LEFT":
                        pass
                    else:
                        # Quick-jump by key
                        for item in menu_items:
                            if key == item["key"]:
                                return item["action"]


def run_plain_fallback(config: H1OSConfig) -> str:
    """Plain console fallback if rich is absent or non-interactive."""
    menu_items = build_dynamic_menu_items(config)

    print("\n" + "=" * 78)
    print("  H1OS Firmware & Packaging Console")
    print(f"  App Root: {config.app_root}")
    print(f"  Target  : {config.chip.upper()} | Version: v{config.version} ({config.git_commit})")
    print("=" * 78)
    for item in menu_items:
        print(f"  [{item['key']}] {item['label']} ({item['target']})")
    print("=" * 78)
    try:
        choice = input("Select action [Enter=1]: ").strip().upper()
    except (KeyboardInterrupt, EOFError):
        return "quit"

    if not choice:
        return menu_items[0]["action"]

    for item in menu_items:
        if choice == item["key"]:
            return item["action"]
    return "quit"


def build_profile_sub_frame(
    title: str,
    subtitle: str,
    items: List[Dict[str, str]],
    selected_idx: int,
    header_panel: Optional[Panel] = None,
) -> Group:
    """Build the profile selection sub-menu frame."""
    sub_table = Table(
        box=box.ROUNDED,
        header_style="bold bright_cyan",
        title=f"[bold white]{title}[/]\n[dim]{subtitle}[/]",
        show_lines=False,
        pad_edge=False,
        expand=True,
    )
    sub_table.add_column(" ", justify="center", no_wrap=True, width=2)
    sub_table.add_column("#", justify="center", style="bold white", no_wrap=True, width=3)
    sub_table.add_column("Profile", style="bold", ratio=2)
    sub_table.add_column("Target Build Dir", style="dim", ratio=3)
    sub_table.add_column("CMake Preset", style="cyan", ratio=2)
    sub_table.add_column("Status", ratio=1)

    for i, item in enumerate(items):
        is_sel = (i == selected_idx)
        marker = ">" if is_sel else " "
        row_style = "bold white on blue" if is_sel else ""
        status_style = "[bold green]READY[/]" if item["status"] == "READY" else "[dim red]NOT BUILT[/]"

        sub_table.add_row(
            marker,
            item["key"],
            item["label"],
            item["target"],
            item["preset"],
            status_style,
            style=row_style,
        )

    back_is_sel = (selected_idx == len(items))
    back_marker = ">" if back_is_sel else " "
    back_style = "bold white on blue" if back_is_sel else "dim"
    sub_table.add_row(
        back_marker,
        "B",
        "[yellow]Back to Main Menu[/]",
        "-",
        "-",
        "-",
        style=back_style,
    )

    footer = Text("  [↑/↓] Navigate   [→/Enter] Select   [←/Esc/B] Back   [1-9/B] Quick-Key", style="dim")
    if header_panel:
        return Group(header_panel, sub_table, footer)
    return Group(sub_table, footer)


def pause_before_menu(console: Optional["Console"]) -> bool:
    """Pause after tool execution so developer can review terminal scrollback."""
    restore_default_console_mode()
    if console:
        console.print("\n[dim]Press [bold white]Enter[/bold white] or [bold white]B[/bold white] to return to menu ([bold white]Q[/bold white] to exit)...[/]", end="")
    else:
        print("\nPress Enter or B to return to menu (Q to exit)...", end="", flush=True)

    while True:
        key = get_single_key()
        # Allow terminal scrolling keys without returning to the menu
        if key in ("UP", "DOWN", "PAGEUP", "PAGEDOWN", "HOME", "END"):
            continue
        clear_screen()
        if key in ("Q", "QUIT"):
            return False
        return True


def run_profile_selection_menu(
    config: H1OSConfig,
    console: Optional["Console"],
    title: str = "Select Build Profile",
    subtitle: str = "Choose an auto-populated profile to execute",
    allow_all: bool = False,
    all_label: str = "All Profiles & Dependencies",
    header_panel: Optional[Panel] = None,
) -> Optional[str]:
    """Interactive pop-up sub-menu to select an auto-populated build profile."""
    clear_screen()
    prof_list = list(config.profiles.values())
    if not prof_list:
        return None

    items = []
    for i, prof in enumerate(prof_list):
        built = prof.build_dir.is_dir() and (prof.build_dir / "project_description.json").is_file()
        status = "READY" if built else "NOT BUILT"
        items.append({
            "key": str(i + 1),
            "profile": prof.name,
            "label": f"{prof.name.upper()} Profile",
            "target": prof.build_dir.name,
            "preset": prof.preset,
            "status": status,
        })

    if allow_all:
        items.append({
            "key": "A",
            "profile": "__ALL__",
            "label": all_label,
            "target": "build_*/deps",
            "preset": "-",
            "status": "-",
        })

    # Plain fallback if rich is absent or non-interactive
    if not console or not sys.stdin.isatty():
        print(f"\n--- {title} ---")
        print(f"  {subtitle}")
        print("-" * 60)
        for item in items:
            print(f"  [{item['key']}] {item['label']} ({item['target']}) [preset: {item['preset']}] - {item['status']}")
        print("  [B] Back to Main Menu")
        print("-" * 60)
        try:
            choice = input(f"Select option [1-{len(prof_list)}, B=Back, Enter=1]: ").strip().upper()
        except (KeyboardInterrupt, EOFError):
            return None

        if choice in ("B", "BACK", "Q", "QUIT", "ESC"):
            return None
        if not choice:
            return items[0]["profile"]
        for item in items:
            if choice in (item["key"], item["profile"].upper()):
                return item["profile"]
        return None

    # Interactive Rich sub-menu loop
    selected_idx = 0
    total_rows = len(items) + 1  # items + Back entry

    frame = build_profile_sub_frame(title, subtitle, items, selected_idx, header_panel=header_panel)
    with Live(frame, console=console, auto_refresh=False, screen=False, transient=True) as live:
        with ConsoleEventDispatcher(enable_mouse=True, enable_resize=True) as dispatcher:
            while True:
                ev = dispatcher.get_event(timeout=0.05)
                if not ev:
                    continue

                if ev.type == EventType.SCROLL:
                    selected_idx = (selected_idx - ev.delta) % total_rows
                    live.update(build_profile_sub_frame(title, subtitle, items, selected_idx, header_panel=header_panel), refresh=True)
                elif ev.type == EventType.RESIZE:
                    live.update(build_profile_sub_frame(title, subtitle, items, selected_idx, header_panel=header_panel), refresh=True)
                elif ev.type == EventType.KEY:
                    key = ev.key
                    if key == "UP":
                        selected_idx = (selected_idx - 1) % total_rows
                        live.update(build_profile_sub_frame(title, subtitle, items, selected_idx, header_panel=header_panel), refresh=True)
                    elif key == "DOWN":
                        selected_idx = (selected_idx + 1) % total_rows
                        live.update(build_profile_sub_frame(title, subtitle, items, selected_idx, header_panel=header_panel), refresh=True)
                    elif key in ("ENTER", "SPACE", "RIGHT"):
                        if selected_idx == len(items):
                            return None
                        return items[selected_idx]["profile"]
                    elif key in ("B", "ESC", "Q", "QUIT", "LEFT"):
                        return None
                    else:
                        for item in items:
                            if key in (item["key"], item["profile"].upper()):
                                return item["profile"]


def main():
    parser = argparse.ArgumentParser(description=f"H1OS Interactive Developer Tooling Console v{H1OS_TOOLING_VERSION}")
    parser.add_argument(
        "-v", "--version",
        action="version",
        version=f"%(prog)s {H1OS_TOOLING_VERSION}",
    )
    parser.add_argument("-C", "--project-dir", dest="project_dir", default=None, help="Application project root directory")
    parser.add_argument("-c", "--config", dest="config", default=None, help="Explicit path to h1os.ini")
    args = parser.parse_args()

    config = H1OSConfig(project_dir=args.project_dir, config_path=args.config)
    console = Console() if HAVE_RICH else None
    header_panel = build_header_panel(config) if console else None

    while True:
        if console and sys.stdin.isatty():
            action = run_interactive_menu(config, console, header_panel=header_panel)
        else:
            action = run_plain_fallback(config)

        if action == "quit":
            if console:
                console.print("\n[dim]Exiting H1OS Console. Goodbye![/]\n")
            else:
                print("\nExiting. Goodbye!\n")
            break

        if action == "build":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Build Firmware",
                subtitle="Select an auto-populated profile to build with 'idf.py build'",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            run_build(config, profile=sel_prof, clean=False, reconfig_only=False)
            header_panel = build_header_panel(config) if console else None

        elif action.startswith("build:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=False, reconfig_only=False)
            header_panel = build_header_panel(config) if console else None

        elif action == "reconfig":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Reconfigure Build Profile",
                subtitle="Select an auto-populated profile to run 'idf.py reconfigure'",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            run_build(config, profile=sel_prof, clean=False, reconfig_only=True)
            header_panel = build_header_panel(config) if console else None

        elif action.startswith("reconfig:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=False, reconfig_only=True)
            header_panel = build_header_panel(config) if console else None

        elif action == "clean":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Clean Build Directory",
                subtitle="Select a profile to erase its build directory (without rebuilding)",
                allow_all=True,
                all_label="Clean All Profiles & Dependencies",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            if sel_prof == "__ALL__":
                run_clean(config, clean_all=True)
            else:
                run_clean(config, profile=sel_prof)
            header_panel = build_header_panel(config) if console else None

        elif action.startswith("clean:"):
            prof = action.split(":", 1)[1]
            if prof.upper() in ("__ALL__", "ALL"):
                run_clean(config, clean_all=True)
            else:
                run_clean(config, profile=prof)
            header_panel = build_header_panel(config) if console else None

        elif action == "clean_rebuild":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Clean & Full Rebuild",
                subtitle="WARNING: Erases build directory, dependencies.lock & managed_components before rebuilding",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            run_build(config, profile=sel_prof, clean=True, reconfig_only=False)
            header_panel = build_header_panel(config) if console else None

        elif action.startswith("clean_rebuild:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=True, reconfig_only=False)
            header_panel = build_header_panel(config) if console else None

        elif action == "size":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Size Audit Diagnostic",
                subtitle="Select an auto-populated profile to analyze firmware memory footprint",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            restore_default_console_mode()
            run_size(config, profile=sel_prof)

        elif action.startswith("size:"):
            prof = action.split(":", 1)[1]
            restore_default_console_mode()
            run_size(config, profile=prof)

        elif action == "pack":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Package Release Bundle",
                subtitle="Select an auto-populated profile to package release distribution artifacts",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            restore_default_console_mode()
            run_pack(config, profile=sel_prof)

        elif action.startswith("pack:"):
            prof = action.split(":", 1)[1]
            restore_default_console_mode()
            run_pack(config, profile=prof)

        elif action == "flash":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Flash Firmware to Device",
                subtitle="Select an auto-populated profile to flash over serial COM port",
                header_panel=header_panel,
            )
            if not sel_prof:
                continue
            run_flash(config, profile=sel_prof)

        elif action.startswith("flash:"):
            prof = action.split(":", 1)[1]
            run_flash(config, profile=prof)

        elif action.startswith("dual_deploy:"):
            parts = action.split(":")
            n1, n2 = parts[1], parts[2]
            p1 = config.profiles[n1]
            p2 = config.profiles[n2]
            b1 = find_compiled_app_bin(p1, config.app_name)
            b2 = find_compiled_app_bin(p2, config.app_name)

            deploy_opts = [
                {
                    "key": "1",
                    "label": f"Deploy ota_0={n1} & ota_1={n2} (Boot ota_0)",
                    "desc": f"ota_0: {b1.name if b1 else n1}, ota_1: {b2.name if b2 else n2}",
                    "value": (b1, b2, n1, n2, 0),
                },
                {
                    "key": "2",
                    "label": f"Deploy ota_0={n1} & ota_1={n2} (Boot ota_1)",
                    "desc": f"ota_0: {b1.name if b1 else n1}, ota_1: {b2.name if b2 else n2} (Active: 1)",
                    "value": (b1, b2, n1, n2, 1),
                },
                {
                    "key": "3",
                    "label": f"Swap: ota_0={n2} & ota_1={n1} (Boot ota_0)",
                    "desc": f"ota_0: {b2.name if b2 else n2}, ota_1: {b1.name if b1 else n1}",
                    "value": (b2, b1, n2, n1, 0),
                },
                {
                    "key": "4",
                    "label": f"Swap: ota_0={n2} & ota_1={n1} (Boot ota_1)",
                    "desc": f"ota_0: {b2.name if b2 else n2}, ota_1: {b1.name if b1 else n1} (Active: 1)",
                    "value": (b2, b1, n2, n1, 1),
                },
                {
                    "key": "B",
                    "label": "Cancel & Return to Menu",
                    "desc": "Abort dual-slot deployment",
                    "value": None,
                },
            ]

            selected = run_interactive_choice_menu(
                console,
                title="Dual-Slot OTA Deployment",
                subtitle="Select firmware slot mapping and initial active boot partition",
                options=deploy_opts,
                header_panel=header_panel,
            )
            if not selected:
                continue

            tb1, tb2, tn1, tn2, slot = selected
            ok, msg = execute_dual_slot_deploy(config, tb1, tb2, tn1, tn2, active_slot=slot)
            if ok:
                if console:
                    console.print(f"\n[bold green]SUCCESS:[/] {msg}")
                else:
                    print(f"\nSUCCESS: {msg}")
            else:
                if console:
                    console.print(f"\n[bold red]{msg}[/]")
                else:
                    print(f"\n{msg}")

        elif action == "ota_toggle":
            if console:
                console.print(f"\n[cyan]Toggling active OTA boot slot on {config.port}...[/]")
            else:
                print(f"\nToggling active OTA boot slot on {config.port}...")
            ok, msg = execute_otatool_toggle(config)
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

        elif action == "partition_menu":
            run_partition_manager_menu(config, console)
            continue

        elif action == "monitor":
            ok, msg = spawn_serial_monitor(config)
            if ok:
                if console:
                    console.print(f"\n[bold green]SUCCESS:[/] {msg}")
                    console.print("[dim]Serial monitor running independently in external window.[/]")
                else:
                    print(f"\nSUCCESS: {msg}")
            else:
                if console:
                    console.print(f"\n[bold red]ERROR:[/] {msg}")
                else:
                    print(f"\nERROR: {msg}")

        elif action == "erase":
            erase_opts = [
                {
                    "key": "C",
                    "label": "Cancel Erase Operation (Safe)",
                    "desc": "Return to menu without touching flash",
                    "value": False,
                },
                {
                    "key": "E",
                    "label": f"Scrub Entire Flash Die on {config.chip.upper()} (0xFF)",
                    "desc": "PERMANENT DATA LOSS: Completely erase all partitions",
                    "value": True,
                    "warning": True,
                },
            ]

            confirmed = run_interactive_choice_menu(
                console,
                title="Erase Entire Flash Die",
                subtitle=f"DANGER: Completely wipe physical SPI flash on {config.chip.upper()} to 0xFF",
                options=erase_opts,
                default_idx=0,
                header_panel=header_panel,
            )

            if confirmed:
                run_erase(config)
            else:
                if console:
                    console.print("[yellow]Erase operation cancelled.[/]")
                else:
                    print("Erase cancelled.")

        # Pause before returning to menu for actions that produce terminal output
        if not pause_before_menu(console):
            if console:
                console.print("\n[dim]Exiting H1OS Console. Goodbye![/]\n")
            else:
                print("\nExiting. Goodbye!\n")
            break


if __name__ == "__main__":
    main()
