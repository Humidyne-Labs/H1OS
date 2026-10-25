#!/usr/bin/env python3
"""
scan_hardcoded_integers.py
--------------------------
Recursively traverses a target directory (default: components/),
extracts space-terminated tokens into an evaluation buffer, detects
literal integer values (decimal and hexadecimal), and logs the file,
line number, token, and line context for code review.

Usage:
    python tools/scan_hardcoded_integers.py [--dir components] [--exclude-trivial] [--output report.md]
"""

import os
import re
import sys
import argparse
from typing import List, Dict, Tuple, Optional

# Regex to detect C-style integer literals with optional type suffixes (u, l, ull, etc.)
INT_PATTERN = re.compile(r'^[+-]?(0x[0-9a-fA-F]+|[0-9]+)[uUlL]*$')

def is_integer_token(token: str) -> Tuple[bool, Optional[int], str]:
    """
    Check if a string token evaluates to an integer.
    Strips common trailing and leading C delimiters/punctuation.
    Returns (is_int, integer_value, normalized_token).
    """
    # Strip common syntax punctuation surrounding tokens
    stripped = token.strip(';,()[]{}:?+*-/=<>&|!~^"')
    if not stripped:
        return False, None, ""
    
    # Check if the stripped token matches C integer literal regex
    if INT_PATTERN.match(stripped):
        clean_num = re.sub(r'[uUlL]+$', '', stripped)
        try:
            val = int(clean_num, 0)
            return True, val, stripped
        except ValueError:
            return False, None, ""
    
    return False, None, ""

def scan_file(filepath: str, exclude_trivial: bool = False) -> List[Dict]:
    """
    Scan a single source file line by line, splitting by whitespace.
    """
    findings = []
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
    except Exception as e:
        print(f"Error reading {filepath}: {e}", file=sys.stderr)
        return findings

    in_block_comment = False

    for line_idx, raw_line in enumerate(lines, start=1):
        line = raw_line.strip()
        if not line:
            continue

        # Handle simple block comment boundaries
        if '/*' in line:
            in_block_comment = True
        if '*/' in line:
            in_block_comment = False
            continue
        if in_block_comment:
            continue
        if line.startswith('//') or line.startswith('*'):
            continue

        # Gobble space-terminated strings into evaluation tokens
        tokens = raw_line.split()
        for tok in tokens:
            # Skip C preprocessor #line or string literals
            if tok.startswith('"') and tok.endswith('"'):
                continue
            is_int, val, norm = is_integer_token(tok)
            if is_int and val is not None:
                if exclude_trivial and val in (0, 1, -1):
                    continue
                findings.append({
                    'line_no': line_idx,
                    'token': tok,
                    'normalized': norm,
                    'value': val,
                    'is_hex': norm.lower().startswith('0x'),
                    'context': raw_line.strip()
                })

    return findings

def scan_directory(root_dir: str, extensions: Tuple[str, ...], exclude_trivial: bool = False) -> Dict[str, List[Dict]]:
    """
    Recursively scans the directory for files with given extensions.
    """
    results = {}
    for root, _, files in os.walk(root_dir):
        for file in files:
            if file.endswith(extensions):
                full_path = os.path.join(root, file)
                rel_path = os.path.relpath(full_path, start=os.getcwd())
                file_findings = scan_file(full_path, exclude_trivial=exclude_trivial)
                if file_findings:
                    results[rel_path] = file_findings
    return results

def generate_report(results: Dict[str, List[Dict]], output_path: Optional[str], exclude_trivial: bool):
    """
    Generate markdown review ledger of findings.
    """
    total_findings = sum(len(items) for items in results.values())
    files_with_findings = len(results)

    lines = []
    lines.append("# Codebase Hardcoded Integer Scanner Audit Report")
    lines.append("")
    lines.append(f"- **Files Inspected with Findings:** {files_with_findings}")
    lines.append(f"- **Total Integer Tokens Found:** {total_findings}")
    lines.append(f"- **Filter Trivial (0, 1, -1):** {'Yes' if exclude_trivial else 'No'}")
    lines.append("")

    # Summary table
    lines.append("## 1. Summary by File")
    lines.append("")
    lines.append("| File | Non-Trivial Magic Constants | Hex / Bitmasks | Total |")
    lines.append("| :--- | :---: | :---: | :---: |")

    for file_path, items in sorted(results.items()):
        magic_count = sum(1 for x in items if not x['is_hex'] and x['value'] not in (0, 1, -1))
        hex_count = sum(1 for x in items if x['is_hex'])
        lines.append(f"| `{file_path}` | {magic_count} | {hex_count} | {len(items)} |")
    lines.append("")

    # Detailed listings
    lines.append("## 2. Detailed Findings by File")
    lines.append("")

    for file_path, items in sorted(results.items()):
        lines.append(f"### `{file_path}` ({len(items)} matches)")
        lines.append("")
        lines.append("| Line | Token | Value | Context |")
        lines.append("| :---: | :---: | :---: | :--- |")
        for item in items:
            escaped_ctx = item['context'].replace('|', '\\|')
            lines.append(f"| {item['line_no']} | `{item['token']}` | `{item['value']}` | `{escaped_ctx}` |")
        lines.append("")

    report_text = "\n".join(lines)

    if output_path:
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(report_text)
        print(f"Audit report saved to: {output_path}")

    return report_text

def main():
    parser = argparse.ArgumentParser(description="Scan components directory recursively for hardcoded integer tokens.")
    parser.add_argument("--dir", default="components", help="Target directory to scan (default: components)")
    parser.add_argument("--exclude-trivial", action="store_true", help="Exclude trivial integers (0, 1, -1)")
    parser.add_argument("--output", default=None, help="Path to write markdown audit report")
    args = parser.parse_args()

    target_dir = os.path.abspath(args.dir)
    if not os.path.exists(target_dir):
        print(f"Error: directory {target_dir} does not exist.", file=sys.stderr)
        sys.exit(1)

    print(f"Scanning '{target_dir}' recursively for hardcoded integer tokens...")
    results = scan_directory(target_dir, ('.c', '.h', '.cpp', '.hpp'), exclude_trivial=args.exclude_trivial)

    total_tokens = sum(len(v) for v in results.values())
    print(f"Scan complete: {len(results)} files contained integer tokens (Total tokens: {total_tokens}).")

    if args.output:
        generate_report(results, args.output, args.exclude_trivial)
    else:
        # Print top highlights to console
        for file_path, items in sorted(results.items()):
            magics = [x for x in items if not x['is_hex'] and x['value'] not in (0, 1, -1)]
            if magics:
                print(f"\n--- {file_path} ({len(magics)} non-trivial integers) ---")
                for m in magics[:10]:
                    print(f"  Line {m['line_no']:4d}: token '{m['token']}' (val {m['value']}) -> {m['context']}")
                if len(magics) > 10:
                    print(f"  ... and {len(magics) - 10} more.")

if __name__ == "__main__":
    main()
