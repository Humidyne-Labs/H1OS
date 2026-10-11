#!/usr/bin/env python3
"""
generate_1bpp_fonts.py
======================
Automated Bilevel (1-bpp) Font Generation Tool for ESP32-S3 E-Paper BSP & LVGL v9.

Author: HUMIDYNE LABS / Humiditron
License: Apache-2.0

Overview:
---------
Standard LVGL fonts use 4-bpp anti-aliasing (16 levels of gray). On 1-bit monochrome
electrophoretic displays (EPD / E-Ink), downsampling anti-aliased glyphs into 1-bit
space causes severe stroke erosion and pixel disintegration when rendered as inverted
white text on solid black backgrounds.

This script uses `lv_font_conv` (via npx/Node.js) to convert TTF/WOFF font sources
into true 1-bit bilevel C bitmap descriptors (`--bpp 1`), ensuring:
  1. Identical stroke weight in both normal (black-on-white) and inverted (white-on-black) modes.
  2. Approximately 50% reduction in flash footprint compared to 4-bpp fonts.
  3. Seamless integration into `components/esp32-s3_bsp/src/`.
"""

import os
import sys
import shutil
import subprocess
import argparse
from pathlib import Path

# Standard glyph ranges for embedded UI: ASCII + Degree symbol + Bullet point
DEFAULT_UNICODE_RANGE = "0x20-0x7F,0xB0,0x2022"

# Key FontAwesome 5 symbols commonly used in IoT / telemetry dashboards
# (e.g. battery gauges, wifi bars, thermometer, drop, exclamation, cog, etc.)
DEFAULT_FONTAWESOME_ICONS = (
    "61441,61448,61451,61452,61453,61457,61459,61461,61465,61468,"
    "61473,61478,61479,61480,61502,61507,61512,61515,61516,61517,"
    "61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,"
    "61559,61560,61561,61563,61587,61589,61636,61637,61639,61641,"
    "61664,61671,61674,61683,61724,61732,61787,61931,62016,62017,"
    "62018,62019,62020,62087,62099,62212,62189,62810,63426,63650"
)

def find_font_sources(repo_root: Path):
    """Attempt to locate Montserrat and FontAwesome source files."""
    candidates_ttf = [
        repo_root.parent / "assets" / "tool_harness" / "lvgl-9.6.0" / "scripts" / "generators" / "built_in_font" / "Montserrat-Medium.ttf",
        repo_root / "examples" / "Peripherals_Test_Suite" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "Montserrat-Medium.ttf",
        repo_root / "examples" / "OSDemo" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "Montserrat-Medium.ttf",
        repo_root / "examples" / "Unified_Environmental_Demo" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "Montserrat-Medium.ttf",
    ]
    candidates_fa = [
        repo_root.parent / "assets" / "tool_harness" / "lvgl-9.6.0" / "scripts" / "generators" / "built_in_font" / "FontAwesome5-Solid+Brands+Regular.woff",
        repo_root / "examples" / "Peripherals_Test_Suite" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "FontAwesome5-Solid+Brands+Regular.woff",
        repo_root / "examples" / "OSDemo" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "FontAwesome5-Solid+Brands+Regular.woff",
        repo_root / "examples" / "Unified_Environmental_Demo" / "managed_components" / "lvgl__lvgl" / "scripts" / "generators" / "built_in_font" / "FontAwesome5-Solid+Brands+Regular.woff",
    ]

    ttf_path = next((p for p in candidates_ttf if p.is_file()), None)
    fa_path = next((p for p in candidates_fa if p.is_file()), None)
    return ttf_path, fa_path

def generate_font(size: int, ttf_path: Path, fa_path: Path, output_file: Path, font_symbol_name: str):
    """Invoke lv_font_conv and patch include header."""
    cmd = [
        "npx", "lv_font_conv",
        "--size", str(size),
        "--bpp", "1",
        "--font", str(ttf_path),
        "-r", DEFAULT_UNICODE_RANGE,
    ]
    if fa_path and fa_path.is_file():
        cmd.extend([
            "--font", str(fa_path),
            "-r", DEFAULT_FONTAWESOME_ICONS
        ])

    cmd.extend([
        "--format", "lvgl",
        "--lv-font-name", font_symbol_name,
        "-o", str(output_file),
        "--no-compress",
        "--no-prefilter",
        "--force-fast-kern-format"
    ])

    print(f"[*] Generating {font_symbol_name} ({size}px, 1-bpp)...")
    res = subprocess.run(cmd, capture_output=True, text=True, shell=sys.platform == "win32")
    if res.returncode != 0:
        print(f"[!] Error generating font:\n{res.stderr}")
        return False

    # Patch header for ESP-IDF component structure
    if output_file.is_file():
        content = output_file.read_text(encoding="utf-8")
        # Replace conditional lvgl include with standard #include "lvgl.h"
        if '#ifdef LV_LVGL_H_INCLUDE_SIMPLE' in content:
            old_block = (
                '#ifdef LV_LVGL_H_INCLUDE_SIMPLE\n'
                '#include "lvgl.h"\n'
                '#else\n'
                '#include "lvgl/lvgl.h"\n'
                '#endif'
            )
            content = content.replace(old_block, '#include "lvgl.h"')
            output_file.write_text(content, encoding="utf-8")

        size_kb = output_file.stat().st_size / 1024.0
        print(f"[+] Successfully wrote {output_file.name} ({size_kb:.1f} KB)")
        return True
    return False

def main():
    parser = argparse.ArgumentParser(description="Generate 1-bpp monochrome fonts for ESP32-S3 e-Paper BSP")
    parser.add_argument("--sizes", nargs="+", type=int, default=[14, 20], help="Font pixel sizes to generate (default: 14 20)")
    parser.add_argument("--out-dir", type=str, default="components/esp32-s3_bsp/src", help="Target output directory")
    args = parser.parse_args()

    repo_root = Path(__file__).resolve().parent.parent
    out_dir = (repo_root / args.out_dir).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    ttf_path, fa_path = find_font_sources(repo_root)
    if not ttf_path:
        print("[!] Could not locate Montserrat-Medium.ttf in standard asset/component paths.")
        sys.exit(1)

    print(f"[*] TTF Source: {ttf_path}")
    print(f"[*] FontAwesome Source: {fa_path if fa_path else 'None'}")

    for size in args.sizes:
        sym_name = f"bsp_font_montserrat_{size}_1bpp"
        out_file = out_dir / f"{sym_name}.c"
        success = generate_font(size, ttf_path, fa_path, out_file, sym_name)
        if not success:
            print(f"[!] Failed to generate size {size}")

    print("\n[+] Font generation completed successfully.")

if __name__ == "__main__":
    main()
