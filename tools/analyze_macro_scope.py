#!/usr/bin/env python3
"""
analyze_macro_scope.py
----------------------
Analyzes all macro definitions in h1os_constants.h across the entire repository.
Maps each macro to the files that reference it, classifying them into:
  - Global / Shared Scope (>= 2 files): Justified in h1os_constants.h
  - Local Scope (== 1 file): Candidates to dissolve into the specific local file
  - Unused / Dead (== 0 files outside definition): Dead code
"""

import os
import re
import sys
from collections import defaultdict

HEADER_PATH = os.path.join("components", "h1os", "include", "h1os", "h1os_constants.h")

def extract_macros_from_header(header_path):
    macros = []
    with open(header_path, "r", encoding="utf-8") as f:
        for line in f:
            match = re.match(r'^\s*#define\s+([A-Za-z0-9_]+)', line)
            if match:
                macro_name = match.group(1)
                macros.append(macro_name)
    return macros

def map_macro_references(macros, search_dirs):
    # Map: macro -> set of files where it appears
    usage_map = defaultdict(set)
    extensions = ('.c', '.h', '.cpp', '.hpp')

    for sdir in search_dirs:
        for root, _, files in os.walk(sdir):
            for file in files:
                if file.endswith(extensions):
                    fpath = os.path.join(root, file)
                    # normalize relative path
                    rel_path = os.path.relpath(fpath, os.getcwd())
                    try:
                        with open(fpath, "r", encoding="utf-8", errors="ignore") as f:
                            content = f.read()
                    except Exception as e:
                        continue
                    
                    for m in macros:
                        # Use word boundary search
                        if re.search(r'\b' + re.escape(m) + r'\b', content):
                            # Don't count the definition line in h1os_constants.h itself
                            if rel_path == os.path.normpath(HEADER_PATH):
                                # check if it appears more than once in h1os_constants.h (e.g. in another macro formula)
                                occurrences = len(re.findall(r'\b' + re.escape(m) + r'\b', content))
                                if occurrences > 1:
                                    usage_map[m].add(rel_path)
                            else:
                                usage_map[m].add(rel_path)
    return usage_map

def main():
    if not os.path.exists(HEADER_PATH):
        print(f"Error: {HEADER_PATH} not found.")
        sys.exit(1)

    macros = extract_macros_from_header(HEADER_PATH)
    print(f"Loaded {len(macros)} macros from {HEADER_PATH}.")

    search_dirs = ["components", "examples"]
    usage_map = map_macro_references(macros, search_dirs)

    shared = []
    local = []
    unused = []

    for m in macros:
        files = sorted(list(usage_map[m]))
        if len(files) >= 2:
            shared.append((m, files))
        elif len(files) == 1:
            local.append((m, files[0]))
        else:
            unused.append(m)

    print("\n" + "="*80)
    print("1. SHARED DEFINITIONS MAP (>= 2 files) -> WARRANTED IN h1os_constants.h")
    print("="*80)
    for m, files in sorted(shared, key=lambda x: len(x[1]), reverse=True):
        print(f"[{len(files)} files] {m}")
        for f in files:
            print(f"    - {f}")

    print("\n" + "="*80)
    print("2. SINGLE-FILE DEFINITIONS MAP (== 1 file) -> DISSOLVE TO COMPONENT FILE")
    print("="*80)
    # Group by target file
    by_target = defaultdict(list)
    for m, target_file in local:
        by_target[target_file].append(m)

    for target_file, m_list in sorted(by_target.items()):
        print(f"\nTarget File: {target_file} ({len(m_list)} macros)")
        for m in m_list:
            print(f"    - {m}")

    print("\n" + "="*80)
    print(f"3. UNREFERENCED / DEAD DEFINITIONS ({len(unused)} macros)")
    print("="*80)
    for m in unused:
        print(f"    - {m}")

if __name__ == "__main__":
    main()
