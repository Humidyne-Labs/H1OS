#!/usr/bin/env python3
"""
H1OS Code Unwrapper & Layout Reset Tool
Masks all comments and strings, joins artificially fractured lines (macros, parens, declarations),
unmasks comments/strings, and lets clang-format re-layout from clean single-line statements.
"""

import os
import re
import sys
from pathlib import Path

TARGET_DIRS = [
    Path("components/h1os/include"),
    Path("components/h1os/src"),
    Path("components/h1os/ulp"),
    Path("components/h1os/bootloader_components/h1os_boot_hook"),
    Path("examples"),
]

EXCLUDE_DIRS = {
    "generated_fonts",
    "managed_components",
    ".git",
    ".gemini",
}

EXTENSIONS = {".c", ".cpp", ".h", ".hpp"}


def unwrap_code(content: str) -> str:
    placeholders = []

    def mask_literal(m):
        idx = len(placeholders)
        placeholders.append(m.group(0))
        return f"__MASKED_BLOCK_{idx}__"

    # 1. Mask block comments, line comments, and string literals
    token_pattern = re.compile(
        r'(/\*.*?\*/|//[^\r\n]*|"(?:\\.|[^"\\])*")',
        re.DOTALL
    )
    masked = token_pattern.sub(mask_literal, content)

    # 2. Join split simple #define macros: e.g. #define FOO \ \n BAR
    masked = re.sub(
        r'^(#define\s+[A-Za-z0-9_]+)\s*\\\s*\r?\n\s*',
        r'\1 ',
        masked,
        flags=re.MULTILINE
    )

    # 3. Join split types and variable names in declarations: e.g. type \n name;
    types_pattern = (
        r'(bool|uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|'
        r'float|double|void|size_t|esp_err_t|gpio_num_t|TickType_t|h1os_init_mode_t|'
        r'h1os_sleep_mode_t|ulp_dispatch_reason_t)'
    )
    masked = re.sub(
        r'^(\s*)' + types_pattern + r'\s*\r?\n\s+([A-Za-z0-9_]+)',
        r'\1\2 \3',
        masked,
        flags=re.MULTILINE
    )

    # 4. Join function call and definition parens: e.g. foo(\n  a,\n  b\n) -> foo(a, b)
    def clean_paren_content(match):
        raw = match.group(0)
        # Skip if contains preprocessor directives
        if '\n#' in raw:
            return raw
        # Collapse whitespace
        lines = [line.strip() for line in raw.splitlines() if line.strip()]
        joined = ' '.join(lines)
        joined = re.sub(r'\s*,\s*', ', ', joined)
        joined = re.sub(r'\(\s+', '(', joined)
        joined = re.sub(r'\s+\)', ')', joined)
        return joined

    masked = re.sub(r'\([^\(\)\{\};]{3,400}\)', clean_paren_content, masked, flags=re.DOTALL)

    # 5. Restore masked comments and string literals
    for idx, orig in enumerate(placeholders):
        masked = masked.replace(f"__MASKED_BLOCK_{idx}__", orig)

    return masked


def find_files(repo_root: Path):
    source_files = []
    for target in TARGET_DIRS:
        target_path = repo_root / target
        if not target_path.exists():
            continue
        for root, dirs, files in os.walk(target_path):
            dirs[:] = [
                d for d in dirs
                if d not in EXCLUDE_DIRS and not d.startswith("build")
            ]
            for file in files:
                p = Path(root) / file
                if p.suffix.lower() in EXTENSIONS:
                    source_files.append(p)
    return sorted(source_files)


def main():
    repo_root = Path(__file__).resolve().parent.parent
    files = find_files(repo_root)
    print(f"[Unwrap] Processing {len(files)} source files...")

    unwrapped_count = 0
    for file_path in files:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            original = f.read()

        unwrapped = unwrap_code(original)
        if unwrapped != original:
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(unwrapped)
            unwrapped_count += 1
            print(f"  [UNWRAPPED] {file_path.relative_to(repo_root)}")

    print(f"[Unwrap] Complete. Unwrapped {unwrapped_count} files.")


if __name__ == "__main__":
    main()
