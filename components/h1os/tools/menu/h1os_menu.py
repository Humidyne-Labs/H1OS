#!/usr/bin/env python3
"""
H1OS Component Tool Launcher & Interactive Console (h1os_menu)
Version: 2.3.1
License: Apache-2.0
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path


def resolve_project_and_component_dirs(script_dir: Path, explicit_proj: str = None) -> tuple:
    """Resolve application project root and h1os component root."""
    app_root = Path(explicit_proj).resolve() if explicit_proj else Path.cwd().resolve()
    comp_dir = script_dir.parent.parent
    return app_root, comp_dir


def main():
    parser = argparse.ArgumentParser(description="H1OS Interactive Tool Launcher Menu")
    parser.add_argument("-C", "--project-dir", dest="project_dir", default=None, help="Application project root directory")
    args = parser.parse_args()

    script_dir = Path(__file__).resolve().parent
    app_root, comp_dir = resolve_project_and_component_dirs(script_dir, args.project_dir)

    pack_script = comp_dir / "tools" / "pack_build" / "h1os_pack.py"
    size_script = comp_dir / "tools" / "audit_size" / "h1os_size.py"
    flasher_script = comp_dir / "tools" / "pack_build" / "flasher.ps1"

    py_exe = sys.executable

    while True:
        print("\n" + "=" * 75)
        print("  H1OS Component Developer Tooling Console")
        print(f"  App Root: {app_root}")
        print("=" * 75)
        print("  [1] Package Production Release (h1os_pack.py -B build_prod)")
        print("  [2] Package Dev Release        (h1os_pack.py -B build_dev --dev)")
        print("  [3] Size Diagnostic - Prod     (h1os_size.py -B build_prod)")
        print("  [4] Size Diagnostic - Dev      (h1os_size.py -B build_dev)")
        print("  [5] Launch Interactive USB Flasher (flasher.ps1 -Interactive)")
        print("  [Q] Quit")
        print("=" * 75)

        try:
            choice = input("Select action [1-5, Q, Enter=1]: ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\nExiting.")
            break

        if not choice:
            choice = "1"

        if choice.lower() in ("q", "quit", "exit"):
            break

        if choice == "1":
            target_build = app_root / "build_prod"
            if not target_build.is_dir():
                print(f"[ERROR] Target build directory does not exist: {target_build}")
                print("Please build first via 'idf.py -B build_prod build'.")
                continue
            cmd = [py_exe, str(pack_script), "-C", str(app_root), "-B", str(target_build)]
            subprocess.run(cmd)

        elif choice == "2":
            target_build = app_root / "build_dev"
            if not target_build.is_dir():
                print(f"[ERROR] Target build directory does not exist: {target_build}")
                print("Please build first via 'idf.py -B build_dev build'.")
                continue
            cmd = [py_exe, str(pack_script), "-C", str(app_root), "-B", str(target_build), "--dev"]
            subprocess.run(cmd)

        elif choice == "3":
            target_build = app_root / "build_prod"
            if not target_build.is_dir():
                print(f"[ERROR] Target build directory does not exist: {target_build}")
                print("Please build first via 'idf.py -B build_prod build'.")
                continue
            cmd = [py_exe, str(size_script), "-C", str(app_root), "-B", str(target_build)]
            subprocess.run(cmd)

        elif choice == "4":
            target_build = app_root / "build_dev"
            if not target_build.is_dir():
                print(f"[ERROR] Target build directory does not exist: {target_build}")
                print("Please build first via 'idf.py -B build_dev build'.")
                continue
            cmd = [py_exe, str(size_script), "-C", str(app_root), "-B", str(target_build)]
            subprocess.run(cmd)

        elif choice == "5":
            if os.name == "nt":
                cmd = ["powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", str(flasher_script), "-Interactive"]
                subprocess.run(cmd, cwd=str(app_root))
            else:
                print("[!] Flasher PowerShell script requires Windows PowerShell environment.")

        else:
            print(f"[!] Invalid selection: {choice}")


if __name__ == "__main__":
    main()
