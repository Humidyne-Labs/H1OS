#!/usr/bin/env python3
"""
H1OS Standalone Extensions for ESP-IDF idf.py CLI.
Version: 2.4.0
License: Apache-2.0
"""
import os
import subprocess
import sys
from pathlib import Path
from typing import Any


def find_h1os_comp_dir(project_path: str, script_path: str) -> Path:
    """Resolve h1os component directory for in-tree and managed component consumers."""
    script_p = Path(script_path).resolve()

    # Case 1: idf_ext.py executed directly from inside components/h1os
    if (script_p.parent / "tools" / "h1os_tool.py").is_file():
        return script_p.parent

    proj_p = Path(project_path).resolve()

    # Case 2: Standard project component paths
    candidates = [
        proj_p / "components" / "h1os",
        proj_p / "../../components" / "h1os",
        proj_p / "managed_components" / "h1os",
        proj_p / "managed_components" / "espressif__h1os",
    ]
    for c in candidates:
        if c.is_dir() and (c / "tools" / "h1os_tool.py").is_file():
            return c.resolve()

    return proj_p / "components" / "h1os"


def action_extensions(base_actions: dict, project_path: str) -> dict:
    """H1OS Standalone Extensions for ESP-IDF idf.py CLI."""
    comp_dir = find_h1os_comp_dir(project_path, __file__)
    tool_script = comp_dir / "tools" / "h1os_tool.py"
    menu_script = comp_dir / "tools" / "menu" / "h1os_menu.py"

    # Capture native monitor without modifying base_actions
    orig_monitor = base_actions.get("actions", {}).get("monitor", {})
    orig_monitor_cb = orig_monitor.get("callback")
    orig_monitor_opts = list(orig_monitor.get("options", []))

    # Helper to resolve active build directory
    def get_explicit_build_dir(global_args: Any) -> str:
        has_b_flag = any(arg in sys.argv for arg in ("-B", "--build-dir"))
        has_preset_flag = any(arg in sys.argv for arg in ("--preset",))
        b_dir = getattr(global_args, "build_dir", None)
        if (not has_b_flag and not has_preset_flag) or not b_dir:
            print("Error: Target build directory must be explicitly specified with -B <build_dir> (e.g. idf.py -B build_prod h1os_size) or --preset <name>.", file=sys.stderr)
            sys.exit(1)
        return str(b_dir)

    # 1. monitor-ts: Display serial output with timestamps enabled
    def callback_monitor_ts(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        if orig_monitor_cb:
            action_args["timestamps"] = True
            orig_monitor_cb(action, ctx, global_args, **action_args)
        else:
            print("Error: Native ESP-IDF monitor action not found.", file=sys.stderr)
            sys.exit(1)

    # 2. h1os_tool: Master backend entry point with arguments
    def callback_tool(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        cmd = [sys.executable, str(tool_script), "-C", project_path]
        b_dir = getattr(global_args, "build_dir", None)
        if b_dir:
            cmd.extend(["-B", str(b_dir)])
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 3. h1os_menu: Interactive Rich Developer Tooling Console
    def callback_menu(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        cmd = [sys.executable, str(menu_script), "-C", project_path]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 4. h1os_pack: Release bundler
    def callback_pack(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        b_dir = get_explicit_build_dir(global_args)
        cmd = [sys.executable, str(tool_script), "-C", project_path, "pack", "-B", b_dir]
        if action_args.get("no_zip"):
            cmd.append("--no-zip")
        if action_args.get("version"):
            cmd.extend(["-V", action_args["version"]])
        if action_args.get("prefix"):
            cmd.extend(["--prefix", action_args["prefix"]])
        if action_args.get("suffix"):
            cmd.extend(["--suffix", action_args["suffix"]])
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 5. h1os_size: Memory and partition headroom audit
    def callback_size(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        b_dir = get_explicit_build_dir(global_args)
        cmd = [sys.executable, str(tool_script), "-C", project_path, "size", "-B", b_dir]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 6. h1os_flash: Flash firmware via esptool
    def callback_flash(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        b_dir = get_explicit_build_dir(global_args)
        cmd = [sys.executable, str(tool_script), "-C", project_path, "flash", "-B", b_dir]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 7. h1os_erase: Erase flash via esptool
    def callback_erase(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        cmd = [sys.executable, str(tool_script), "-C", project_path, "erase"]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    pack_options = [
        {
            "names": ["--no-zip"],
            "is_flag": True,
            "default": False,
            "help": "Skip zip bundle generation",
        },
        {
            "names": ["-V", "--version"],
            "help": "Explicit version string override",
        },
        {
            "names": ["--prefix"],
            "help": "Custom prefix for the release zip file",
        },
        {
            "names": ["--suffix"],
            "help": "Custom suffix for the release zip file",
        },
    ]

    all_actions = {
        "h1os_menu": {
            "callback": callback_menu,
            "short_help": "Launch Interactive H1OS Rich Developer Tooling Console.",
            "help": "Launch interactive Rich terminal console for packaging, sizing, and hardware operations.",
            "aliases": ["menu", "tools", "tools-menu"],
        },
        "h1os_tool": {
            "callback": callback_tool,
            "short_help": "Execute H1OS Master Developer Dispatcher.",
            "help": "Unified command dispatcher driven by h1os.ini project configuration.",
            "aliases": ["h1os", "tool"],
        },
        "h1os_pack": {
            "callback": callback_pack,
            "options": pack_options,
            "short_help": "Package H1OS Zero-Dependency Firmware Release Bundle.",
            "help": "Package firmware binaries and turnkey flasher bundle based on build directory and naming prefix/suffix.",
            "aliases": ["pack", "release", "h1os-release"],
        },
        "h1os_size": {
            "callback": callback_size,
            "short_help": "Run H1OS Binary Size & Partition Headroom Diagnostic.",
            "help": "Inspect memory allocation, RAM usage, and partition headroom (leaves native 'size' untouched).",
            "aliases": ["size-audit", "h1os-size"],
        },
        "h1os_flash": {
            "callback": callback_flash,
            "short_help": "Flash H1OS firmware to hardware using esptool.",
            "help": "Write firmware binaries to flash using flash_args configuration.",
            "aliases": ["flash-now"],
        },
        "h1os_erase": {
            "callback": callback_erase,
            "short_help": "Erase target SPI flash die using esptool.",
            "help": "Scrub entire target flash die to 0xFF using esptool erase-flash.",
            "aliases": ["erase-chip"],
        },
        "monitor-ts": {
            "callback": callback_monitor_ts,
            "options": orig_monitor_opts,
            "short_help": "Display serial output with timestamps enabled by default.",
            "help": "Display serial output with timestamps enabled at the start of each line, leaving standard 'monitor' untouched.",
        },
    }

    # Deduplicate against base_actions so redundant component registration does not trigger warnings
    existing_actions = base_actions.get("actions", {})
    filtered_actions = {k: v for k, v in all_actions.items() if k not in existing_actions}

    return {
        "version": 1,
        "actions": filtered_actions,
    }
