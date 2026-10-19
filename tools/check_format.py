#!/usr/bin/env python3
"""
H1OS Automated Formatting and Style Checker
Wraps clang-format to enforce Layer 1 code style across H1OS component sources.

Usage:
    python tools/check_format.py          # Format in-place
    python tools/check_format.py --check  # Verify without modifying (exit 1 on diff)
"""

import os
import sys
import subprocess
import argparse
from pathlib import Path

TARGET_DIRS = [
    Path("components/h1os/include"),
    Path("components/h1os/src"),
    Path("components/h1os/ulp"),
    Path("components/h1os/bootloader_components/h1os_boot_hook"),
]

EXCLUDE_DIRS = [
    "generated_fonts",
    "build",
    "build_prod",
]

EXTENSIONS = {".c", ".cpp", ".h", ".hpp"}


def find_source_files(repo_root: Path):
    source_files = []
    for target in TARGET_DIRS:
        target_path = repo_root / target
        if not target_path.exists():
            continue
        for root, dirs, files in os.walk(target_path):
            # Prune excluded directories
            dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
            for file in files:
                p = Path(root) / file
                if p.suffix.lower() in EXTENSIONS:
                    source_files.append(p)
    return sorted(source_files)


def main():
    parser = argparse.ArgumentParser(description="H1OS Code Formatter")
    parser.add_argument(
        "--check",
        action="store_true",
        help="Check formatting without modifying files (exits non-zero if diff found)",
    )
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parent.parent
    files = find_source_files(repo_root)

    if not files:
        print("[H1OS Format] No source files found to check.")
        return 0

    print(f"[H1OS Format] Found {len(files)} source files.")

    unformatted = []
    for file_path in files:
        if args.check:
            res = subprocess.run(
                ["clang-format", "--dry-run", "--Werror", str(file_path)],
                capture_output=True,
                text=True,
            )
            if res.returncode != 0:
                unformatted.append(file_path)
                print(f"  [FAIL] {file_path.relative_to(repo_root)}")
            else:
                print(f"  [OK]   {file_path.relative_to(repo_root)}")
        else:
            subprocess.run(["clang-format", "-i", str(file_path)], check=True)
            print(f"  [FORMATTED] {file_path.relative_to(repo_root)}")

    if args.check and unformatted:
        print(f"\n[H1OS Format] ERROR: {len(unformatted)} file(s) require formatting.")
        print("Run 'python tools/check_format.py' to format automatically.")
        return 1

    print("\n[H1OS Format] All source files conform to H1OS Layer 1 style.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
