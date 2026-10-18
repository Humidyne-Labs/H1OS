#!/usr/bin/env python3
"""
tools/generate_api_md.py - Automated Doxygen & Moxygen API Documentation Generator for H1OS

Executes:
1. doxygen Doxyfile (Generates Doxygen XML into docs/doxygen/xml)
2. moxygen -F github docs/doxygen/xml -o docs/api.md (Converts XML to GitHub Flavored Markdown)
3. Validates that docs/api.md exists and is non-empty.

SPDX-License-Identifier: MIT
"""

import os
import sys
import subprocess
import shutil

def main():
    repo_root = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    os.chdir(repo_root)

    print("=== H1OS Automated API Documentation Generator ===")

    # 1. Check for Doxygen
    doxygen_bin = shutil.which("doxygen")
    if not doxygen_bin:
        # Fallback to standard Program Files location
        prog_doxygen = r"C:\Program Files\doxygen\bin\doxygen.exe"
        if os.path.exists(prog_doxygen):
            doxygen_bin = prog_doxygen
        else:
            print("ERROR: doxygen executable not found on PATH or in Program Files.")
            sys.exit(1)

    print(f"[1/3] Running Doxygen: {doxygen_bin} Doxyfile")
    res = subprocess.run([doxygen_bin, "Doxyfile"], capture_output=True, text=True)
    if res.returncode != 0:
        print(f"ERROR: Doxygen failed with return code {res.returncode}")
        print(res.stderr)
        sys.exit(res.returncode)
    print("Doxygen XML generation completed.")

    # 2. Check for Moxygen
    moxygen_cmd = "moxygen"
    # On Windows, npm global scripts might be moxygen.cmd or moxygen.ps1
    moxygen_bin = shutil.which("moxygen")
    if not moxygen_bin:
        npm_moxygen = os.path.expandvars(r"%APPDATA%\npm\moxygen.cmd")
        if os.path.exists(npm_moxygen):
            moxygen_bin = npm_moxygen
        else:
            print("ERROR: moxygen not found on PATH or in AppData/npm.")
            sys.exit(1)

    xml_dir = os.path.join("docs", "doxygen", "xml")
    out_file = os.path.join("docs", "api.md")

    if not os.path.isdir(xml_dir):
        print(f"ERROR: Doxygen XML directory not found: {xml_dir}")
        sys.exit(1)

    print(f"[2/3] Running Moxygen (-F github): {moxygen_bin} -F github {xml_dir} -o {out_file}")
    res_mox = subprocess.run([moxygen_bin, "-F", "github", xml_dir, "-o", out_file], capture_output=True, text=True, shell=True)
    if res_mox.returncode != 0:
        print(f"ERROR: Moxygen failed with return code {res_mox.returncode}")
        print(res_mox.stderr)
        sys.exit(res_mox.returncode)
    print(f"Moxygen conversion completed: {out_file}")

    # 3. Post-process verification
    if not os.path.isfile(out_file) or os.path.getsize(out_file) == 0:
        print(f"ERROR: Output file {out_file} was not generated or is empty.")
        sys.exit(1)

    lines_count = sum(1 for _ in open(out_file, "r", encoding="utf-8", errors="ignore"))
    print(f"[3/3] Verification SUCCESS: {out_file} ({lines_count} lines, {os.path.getsize(out_file):,} bytes)")
    print("API Reference generation finished cleanly.")

if __name__ == "__main__":
    main()
