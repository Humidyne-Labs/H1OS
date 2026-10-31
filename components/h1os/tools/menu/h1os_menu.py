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

try:
    from rich import box
    from rich.console import Console
    from rich.panel import Panel
    from rich.table import Table
    from rich.text import Text
    HAVE_RICH = True
except ImportError:
    HAVE_RICH = False

from h1os_tool import (
    H1OSConfig,
    run_build,
    run_erase,
    run_flash,
    run_pack,
    run_size,
)

TERM_WIDTH = 78


def get_key_windows() -> str:
    """Read a single keypress or arrow key on Windows using msvcrt."""
    import msvcrt
    ch = msvcrt.getch()
    if ch in (b"\x00", b"\xe0"):
        ch2 = msvcrt.getch()
        if ch2 == b"H":
            return "UP"
        elif ch2 == b"P":
            return "DOWN"
        elif ch2 == b"K":
            return "LEFT"
        elif ch2 == b"M":
            return "RIGHT"
        return "SPECIAL"
    elif ch in (b"\r", b"\n"):
        return "ENTER"
    elif ch == b"\x1b":
        return "ESC"
    elif ch in (b"\x03", b"\x1a"):  # Ctrl+C, Ctrl+Z
        return "QUIT"
    else:
        try:
            return ch.decode("utf-8", errors="ignore").upper()
        except Exception:
            return ""


def get_key_posix() -> str:
    """Read a single keypress or arrow key on POSIX systems."""
    try:
        import termios
        import tty
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
            if ch == "\x1b":
                seq = sys.stdin.read(2)
                if seq == "[A":
                    return "UP"
                elif seq == "[B":
                    return "DOWN"
                return "ESC"
            elif ch in ("\r", "\n"):
                return "ENTER"
            elif ch in ("\x03", "\x1a"):
                return "QUIT"
            return ch.upper()
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    except Exception:
        line = sys.stdin.readline().strip().upper()
        return line if line else "ENTER"


def read_nav_key() -> str:
    """Read a navigation key across platforms with non-interactive fallback."""
    if not sys.stdin.isatty():
        try:
            line = sys.stdin.readline()
            if not line:
                return "QUIT"
            return line.strip().upper()
        except Exception:
            return "QUIT"

    if os.name == "nt":
        return get_key_windows()
    return get_key_posix()


def render_console_frame(config: H1OSConfig, console: "Console", selected_idx: int, menu_items: List[Dict[str, str]]) -> None:
    """Render the full 78-column frame with header and highlighted selection."""
    console.clear()

    # 1. Header Information Panel (78 columns max)
    port_label = config.port if config.port else "Auto-discover"
    app_root_str = str(config.app_root)
    if len(app_root_str) > 28:
        app_root_str = "..." + app_root_str[-25:]

    header_table = Table.grid(padding=(0, 1))
    header_table.add_column("K1", style="bold cyan", width=9)
    header_table.add_column("V1", width=29)
    header_table.add_column("K2", style="bold cyan", width=9)
    header_table.add_column("V2", width=25)

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

    header_panel = Panel(
        header_table,
        title="[bold white]H1OS Firmware & Packaging Console[/]",
        border_style="cyan",
        box=box.ROUNDED,
        width=TERM_WIDTH,
    )
    console.print(header_panel)

    # 2. Operations Table (78 columns max)
    ops_table = Table(
        box=box.ROUNDED,
        width=TERM_WIDTH,
        header_style="bold bright_cyan",
        show_lines=False,
        pad_edge=False,
    )
    ops_table.add_column(" ", justify="center", width=2)
    ops_table.add_column("#", justify="center", style="bold white", width=3)
    ops_table.add_column("Operation", style="bold", width=32)
    ops_table.add_column("Target Build", style="dim", width=18)
    ops_table.add_column("Backend Engine", style="cyan", width=16)

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

    console.print(ops_table)

    # 3. Navigation Help Footer
    footer_text = Text(
        "  [↑/↓] Navigate   [Enter] Select   [Quick-Key] Direct Action   [Q/Esc] Exit",
        style="dim",
    )
    console.print(footer_text)


def build_dynamic_menu_items(config: H1OSConfig) -> List[Dict[str, str]]:
    """Auto-populate operations table dynamically based on configured build profiles.

    When 2 or more profiles exist, operations collapse into clean single rows that open
    an auto-populated profile selection sub-menu. If only 1 profile exists, actions target
    it directly.
    """
    menu_items = []
    KEY_POOL = [
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "A", "B", "C", "D", "F", "G", "H", "J", "K", "L",
        "M", "N", "P", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
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
            "label": "Clean & Full Rebuild",
            "target": target_label,
            "engine": "nuke & rebuild",
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
            "label": f"Clean & Full Rebuild ({single_name.upper()})",
            "target": target_dir,
            "engine": "nuke & rebuild",
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

    # Hardware maintenance & Exit
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


def run_interactive_menu(config: H1OSConfig, console: "Console") -> str:
    """Run real-time keyboard navigation loop with arrow keys."""
    menu_items = build_dynamic_menu_items(config)
    selected_idx = 0

    while True:
        render_console_frame(config, console, selected_idx, menu_items)
        key = read_nav_key()

        if key == "UP":
            selected_idx = (selected_idx - 1) % len(menu_items)
        elif key == "DOWN":
            selected_idx = (selected_idx + 1) % len(menu_items)
        elif key in ("ENTER", "SPACE"):
            return menu_items[selected_idx]["action"]
        elif key in ("Q", "ESC", "QUIT"):
            return "quit"
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


def run_profile_selection_menu(
    config: H1OSConfig,
    console: Optional["Console"],
    title: str = "Select Build Profile",
    subtitle: str = "Choose an auto-populated profile to execute",
) -> Optional[str]:
    """Interactive pop-up sub-menu to select an auto-populated build profile."""
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
            choice = input(f"Select profile [1-{len(items)}, B=Back, Enter=1]: ").strip().upper()
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

    while True:
        console.clear()

        sub_table = Table(
            box=box.ROUNDED,
            width=TERM_WIDTH,
            header_style="bold bright_cyan",
            title=f"[bold white]{title}[/]\n[dim]{subtitle}[/]",
            show_lines=False,
            pad_edge=False,
        )
        sub_table.add_column(" ", justify="center", width=2)
        sub_table.add_column("#", justify="center", style="bold white", width=3)
        sub_table.add_column("Profile", style="bold", width=18)
        sub_table.add_column("Target Build Dir", style="dim", width=20)
        sub_table.add_column("CMake Preset", style="cyan", width=14)
        sub_table.add_column("Status", width=12)

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

        console.print(sub_table)
        footer = Text("  [↑/↓] Navigate   [Enter] Select   [1-9/B] Quick-Key   [Esc/B] Back", style="dim")
        console.print(footer)

        key = read_nav_key()

        if key == "UP":
            selected_idx = (selected_idx - 1) % total_rows
        elif key == "DOWN":
            selected_idx = (selected_idx + 1) % total_rows
        elif key in ("ENTER", "SPACE"):
            if selected_idx == len(items):
                return None
            return items[selected_idx]["profile"]
        elif key in ("B", "ESC", "Q", "QUIT"):
            return None
        else:
            for item in items:
                if key in (item["key"], item["profile"].upper()):
                    return item["profile"]


def main():
    parser = argparse.ArgumentParser(description="H1OS Interactive Developer Tooling Console")
    parser.add_argument("-C", "--project-dir", dest="project_dir", default=None, help="Application project root directory")
    parser.add_argument("-c", "--config", dest="config", default=None, help="Explicit path to h1os.ini")
    args = parser.parse_args()

    config = H1OSConfig(project_dir=args.project_dir, config_path=args.config)
    console = Console(width=TERM_WIDTH) if HAVE_RICH else None

    while True:
        if console and sys.stdin.isatty():
            action = run_interactive_menu(config, console)
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
            )
            if sel_prof:
                run_build(config, profile=sel_prof, clean=False, reconfig_only=False)
            else:
                if console:
                    console.print("[dim]Build cancelled.[/]")
                else:
                    print("Build cancelled.")

        elif action.startswith("build:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=False, reconfig_only=False)

        elif action == "reconfig":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Reconfigure Build Profile",
                subtitle="Select an auto-populated profile to run 'idf.py reconfigure'",
            )
            if sel_prof:
                run_build(config, profile=sel_prof, clean=False, reconfig_only=True)
            else:
                if console:
                    console.print("[dim]Reconfiguration cancelled.[/]")
                else:
                    print("Reconfiguration cancelled.")

        elif action.startswith("reconfig:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=False, reconfig_only=True)

        elif action == "clean_rebuild":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Clean & Full Rebuild",
                subtitle="WARNING: Nukes build directory, dependencies.lock & managed_components before rebuilding",
            )
            if sel_prof:
                run_build(config, profile=sel_prof, clean=True, reconfig_only=False)
            else:
                if console:
                    console.print("[dim]Clean rebuild cancelled.[/]")
                else:
                    print("Clean rebuild cancelled.")

        elif action.startswith("clean_rebuild:"):
            prof = action.split(":", 1)[1]
            run_build(config, profile=prof, clean=True, reconfig_only=False)

        elif action == "size":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Size Audit Diagnostic",
                subtitle="Select an auto-populated profile to analyze firmware memory footprint",
            )
            if sel_prof:
                run_size(config, profile=sel_prof)
            else:
                if console:
                    console.print("[dim]Size audit cancelled.[/]")
                else:
                    print("Size audit cancelled.")

        elif action.startswith("size:"):
            prof = action.split(":", 1)[1]
            run_size(config, profile=prof)

        elif action == "pack":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Package Release Bundle",
                subtitle="Select an auto-populated profile to package release distribution artifacts",
            )
            if sel_prof:
                run_pack(config, profile=sel_prof)
            else:
                if console:
                    console.print("[dim]Packaging cancelled.[/]")
                else:
                    print("Packaging cancelled.")

        elif action.startswith("pack:"):
            prof = action.split(":", 1)[1]
            run_pack(config, profile=prof)

        elif action == "flash":
            sel_prof = run_profile_selection_menu(
                config,
                console,
                title="Flash Firmware to Device",
                subtitle="Select an auto-populated profile to flash over serial COM port",
            )
            if sel_prof:
                run_flash(config, profile=sel_prof)
            else:
                if console:
                    console.print("[dim]Flash cancelled.[/]")
                else:
                    print("Flash cancelled.")

        elif action.startswith("flash:"):
            prof = action.split(":", 1)[1]
            run_flash(config, profile=prof)

        elif action == "erase":
            confirmed = False
            if console:
                console.print(f"\n[bold red]WARNING:[/] This operation will completely scrub all SPI Flash on {config.chip.upper()} to 0xFF.")
                console.print("[yellow]Type 'yes' or 'y' to confirm, or press Enter/any key to cancel: [/]", end="")
                try:
                    c = input().strip().lower()
                    confirmed = c in ("y", "yes")
                except (KeyboardInterrupt, EOFError):
                    confirmed = False
            else:
                try:
                    c = input(f"Scrub full flash on {config.chip.upper()} to 0xFF? [y/N]: ").strip().lower()
                    confirmed = c in ("y", "yes")
                except (KeyboardInterrupt, EOFError):
                    confirmed = False

            if confirmed:
                run_erase(config)
            else:
                if console:
                    console.print("[yellow]Erase operation cancelled.[/]")
                else:
                    print("Erase cancelled.")

        # Pause before returning to menu
        if console:
            console.print("\n[dim]Press Enter to return to menu...[/]", end="")
            try:
                input()
            except (KeyboardInterrupt, EOFError):
                break
        else:
            try:
                input("\nPress Enter to return to menu...")
            except (KeyboardInterrupt, EOFError):
                break


if __name__ == "__main__":
    main()
