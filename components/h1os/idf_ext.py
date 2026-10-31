import os
import subprocess
import sys
from pathlib import Path
from typing import Any


def find_h1os_comp_dir(project_path: str, script_path: str) -> Path:
    """Resolve h1os component directory for in-tree and managed component consumers."""
    script_p = Path(script_path).resolve()

    # Case 1: idf_ext.py executed directly from inside components/h1os
    if (script_p.parent / "tools" / "pack_build").is_dir():
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
        if c.is_dir() and (c / "tools" / "pack_build").is_dir():
            return c.resolve()

    return proj_p / "components" / "h1os"


def action_extensions(base_actions: dict, project_path: str) -> dict:
    """H1OS Standalone Extensions for ESP-IDF idf.py CLI."""
    comp_dir = find_h1os_comp_dir(project_path, __file__)
    pack_script = comp_dir / "tools" / "pack_build" / "h1os_pack.py"
    size_script = comp_dir / "tools" / "audit_size" / "h1os_size.py"
    menu_script = comp_dir / "tools" / "menu" / "h1os_menu.py"

    # Capture native monitor without modifying base_actions
    orig_monitor = base_actions.get("actions", {}).get("monitor", {})
    orig_monitor_cb = orig_monitor.get("callback")
    orig_monitor_opts = list(orig_monitor.get("options", []))

    # 1. New Tool: monitor-ts (leaves native 'monitor' 100% stock)
    def callback_monitor_ts(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        if orig_monitor_cb:
            action_args["timestamps"] = True
            orig_monitor_cb(action, ctx, global_args, **action_args)
        else:
            print("Error: Native ESP-IDF monitor action not found.", file=sys.stderr)
            sys.exit(1)

    # 2. New Tool: h1os_pack (strictly requires explicit -B <build_dir> or --preset <name>)
    def callback_pack(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        has_b_flag = any(arg in sys.argv for arg in ("-B", "--build-dir"))
        has_preset_flag = any(arg in sys.argv for arg in ("--preset",))
        build_dir = getattr(global_args, "build_dir", None)
        if (not has_b_flag and not has_preset_flag) or not build_dir:
            print("Error: Target build directory must be explicitly specified with -B <build_dir> (e.g. idf.py -B build_prod h1os_pack) or --preset <name>.", file=sys.stderr)
            sys.exit(1)
        cmd = [sys.executable, str(pack_script), "-C", project_path, "-B", str(build_dir)]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 3. New Tool: h1os_size (strictly requires explicit -B <build_dir> or --preset <name>)
    def callback_size(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        has_b_flag = any(arg in sys.argv for arg in ("-B", "--build-dir"))
        has_preset_flag = any(arg in sys.argv for arg in ("--preset",))
        build_dir = getattr(global_args, "build_dir", None)
        if (not has_b_flag and not has_preset_flag) or not build_dir:
            print("Error: Target build directory must be explicitly specified with -B <build_dir> (e.g. idf.py -B build_prod h1os_size) or --preset <name>.", file=sys.stderr)
            sys.exit(1)
        cmd = [sys.executable, str(size_script), "-C", project_path, "-B", str(build_dir)]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    # 4. New Tool: h1os_menu
    def callback_menu(action: str, ctx: Any, global_args: Any, **action_args: Any) -> None:
        cmd = [sys.executable, str(menu_script), "-C", project_path]
        res = subprocess.run(cmd)
        sys.exit(res.returncode)

    all_actions = {
        "h1os_pack": {
            "callback": callback_pack,
            "short_help": "Package H1OS Zero-Dependency Firmware Release Bundle.",
            "help": "Package production firmware binaries, factory image, and turnkey flasher bundle.",
            "aliases": ["pack", "release", "h1os-release"],
        },
        "h1os_size": {
            "callback": callback_size,
            "short_help": "Run H1OS Binary Size & Partition Headroom Diagnostic.",
            "help": "Inspect memory allocation, RAM usage, and partition headroom (leaves native 'size' untouched).",
            "aliases": ["size-audit", "h1os-size"],
        },
        "h1os_menu": {
            "callback": callback_menu,
            "short_help": "Launch Interactive H1OS Developer Tooling Console.",
            "help": "Launch interactive menu for packaging, size diagnostics, and USB flashing.",
            "aliases": ["tools-menu", "h1os-menu", "tools"],
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
