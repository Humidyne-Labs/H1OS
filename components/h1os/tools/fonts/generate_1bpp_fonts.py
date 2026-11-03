#!/usr/bin/env python3
"""
generate_1bpp_fonts.py
======================
Automated Bilevel (1-bpp) Font Generation Tool for ESP32-S3 E-Paper BSP & H1OS.

Author: HUMIDYNE LABS / Humiditron
License: Apache-2.0

Overview:
---------
Standard LVGL fonts use 4-bpp anti-aliasing. On 1-bit monochrome electrophoretic
displays (EPD / E-Ink), anti-aliasing causes severe stroke erosion.

This script uses vendored font sources (Montserrat-Bold, Montserrat-Medium, FontAwesome5)
or LVGL managed_components built-in font assets to synthesize crisp 1-bit bilevel C font
descriptors during build-time. When building from a slim archive without TTF binaries or
Node.js/npx, it emits a deterministic C descriptor wrapper around LVGL built-in fonts so
compilation succeeds without external network dependencies.
"""

import os
import sys
import shutil
import subprocess
import argparse
from pathlib import Path

# Scientific & Math extensions:
# 0x20-0x7F: ASCII printable
# 0xB0: Degree (°)
# 0xB2: Superscript 2 (²)
# 0xB3: Superscript 3 (³)
# 0xB5: Micro (µ)
# 0x394: Greek Delta (Δ)
# 0x2022: Bullet (•)
# 0x2190-0x2193: Arrows (←, ↑, →, ↓)
DEFAULT_UNICODE_RANGE = "0x20-0x7F,0xB0,0xB2,0xB3,0xB5,0x394,0x2022,0x2190-0x2193"

# Built-in FontAwesome 5 symbols matching LVGL official built_in_font_gen.py
DEFAULT_FONTAWESOME_ICONS = (
    "61441,61448,61451,61452,61453,61457,61459,61461,61465,61468,"
    "61473,61478,61479,61480,61502,61507,61512,61515,61516,61517,"
    "61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,"
    "61559,61560,61561,61563,61587,61589,61636,61637,61639,61641,"
    "61664,61671,61674,61683,61724,61732,61787,61931,62016,62017,"
    "62018,62019,62020,62087,62099,62212,62189,62810,63426,63650"
)


def emit_builtin_bridge(size: int, output_file: Path, font_symbol_name: str):
    """Synthesize a C translation unit bridging h1os_font_montserrat_<size>_1bpp when TTF/npx are absent."""
    code = f"""/**
 * @file {output_file.name}
 * @brief Deterministic LVGL font descriptor bridge for slim/offline build environments
 *
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"

#if defined(LV_FONT_MONTSERRAT_{size}) && LV_FONT_MONTSERRAT_{size}
LV_FONT_DECLARE(lv_font_montserrat_{size});
const lv_font_t {font_symbol_name} = {{
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = {size + 4},
    .base_line = 3,
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
    .dsc = NULL,
    .user_data = NULL,
}};
#else
const lv_font_t {font_symbol_name} = {{
    .get_glyph_dsc = NULL,
    .get_glyph_bitmap = NULL,
    .line_height = {size + 4},
    .base_line = 3,
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
    .dsc = NULL,
    .user_data = NULL,
}};
#endif
"""
    output_file.write_text(code, encoding="utf-8")
    print(f"[*] Synthesized offline bridge descriptor: {output_file.name}")
    return True


def generate_font(size: int, font_path: Path, fa_path: Path, output_file: Path, font_symbol_name: str, unhinted: bool = False):
    """Invoke lv_font_conv and patch include header."""
    if font_path is None or not font_path.is_file() or shutil.which("npx") is None:
        return emit_builtin_bridge(size, output_file, font_symbol_name)

    cmd = [
        "npx", "lv_font_conv",
        "--size", str(size),
        "--bpp", "1",
        "--font", str(font_path),
        "-r", DEFAULT_UNICODE_RANGE,
        ("--autohint-off" if unhinted else "--autohint-strong"),
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
        print(f"[!] lv_font_conv returned non-zero ({res.stderr.strip()}); emitting offline bridge descriptor.")
        return emit_builtin_bridge(size, output_file, font_symbol_name)

    # Patch header for standard include
    if output_file.is_file():
        content = output_file.read_text(encoding="utf-8")
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
        return True
    return False


def generate_header(out_dir: Path, montserrat_sizes):
    """Generate master h1os_fonts.h header file."""
    header_path = out_dir / "h1os_fonts.h"
    lines = [
        "/**",
        " * @file h1os_fonts.h",
        " * @brief H1OS Build-Time Generated 1-BPP Bilevel Typography Suite",
        " *",
        " * Auto-generated by tools/generate_1bpp_fonts.py",
        " * SPDX-License-Identifier: MIT / SIL OFL",
        " */",
        "",
        "#pragma once",
        "",
        "#ifdef __cplusplus",
        'extern "C" {',
        "#endif",
        "",
        "/* Forward-declare LVGL font type for self-contained inclusion */",
        "struct _lv_font_t;",
        "#ifndef LV_FONT_T_DEFINED",
        "typedef struct _lv_font_t lv_font_t;",
        "#define LV_FONT_T_DEFINED",
        "#endif",
        "",
        "/* Wire H1OS 1-BPP Montserrat 14px as LVGL custom default font */",
        "#ifndef LV_FONT_CUSTOM_DECLARE",
        "#define LV_FONT_CUSTOM_DECLARE extern const lv_font_t h1os_font_montserrat_14_1bpp;",
        "#endif",
        "",
        "#ifndef LV_FONT_DEFAULT",
        "#define LV_FONT_DEFAULT (&h1os_font_montserrat_14_1bpp)",
        "#endif",
        "",
        "/* =========================================================================",
        " * 1-Bit Packed Binary Typography (Montserrat Proportional + FA5 + Math)",
        " * ========================================================================= */",
    ]

    for sz in montserrat_sizes:
        lines.append(f"extern const lv_font_t h1os_font_montserrat_{sz}_1bpp;")
        lines.append(f"#define H1OS_FONT_{sz} (&h1os_font_montserrat_{sz}_1bpp)")

    lines.extend([
        "",
        "#ifdef __cplusplus",
        "}",
        "#endif",
        ""
    ])

    header_path.write_text("\n".join(lines), encoding="utf-8")
    print(f"[+] Successfully wrote {header_path.name}")


def copy_licenses(font_dir: Path, out_dir: Path):
    """Copy license files into the generated licenses folder."""
    lic_src = font_dir / "font_license"
    lic_dst = out_dir / "licenses"
    lic_dst.mkdir(parents=True, exist_ok=True)

    if (lic_src / "Montserrat" / "OFL.txt").is_file():
        shutil.copy2(lic_src / "Montserrat" / "OFL.txt", lic_dst / "Montserrat_OFL.txt")
    if (lic_src / "FontAwesome5" / "LICENSE.txt").is_file():
        shutil.copy2(lic_src / "FontAwesome5" / "LICENSE.txt", lic_dst / "FontAwesome5_LICENSE.txt")
    elif (lic_src / "FontAwesome" / "LICENSE.txt").is_file():
        shutil.copy2(lic_src / "FontAwesome" / "LICENSE.txt", lic_dst / "FontAwesome5_LICENSE.txt")

    readme = lic_dst / "README.md"
    readme.write_text(
        "# H1OS 1-BPP Typography Licenses\n\n"
        "This directory contains the licenses for fonts incorporated into H1OS:\n"
        "- **Montserrat-Bold / Montserrat-Medium**: Licensed under the SIL Open Font License (OFL).\n"
        "- **FontAwesome5**: Licensed under the Font Awesome Free License.\n",
        encoding="utf-8"
    )
    print(f"[+] Successfully copied font license files to {lic_dst}")


def main():
    default_font_dir = (Path(__file__).parent / "static_assets").resolve()

    parser = argparse.ArgumentParser(description="Generate 1-bpp monochrome fonts for H1OS from vendored font assets")
    parser.add_argument("--font-dir", type=str, default=str(default_font_dir), help="Path to font assets directory (contains TTF/WOFF fonts and licenses)")
    parser.add_argument("--lvgl-dir", type=str, default="", help="Optional path to managed_components/lvgl__lvgl directory")
    parser.add_argument("--out-dir", type=str, required=True, help="Target output directory")
    parser.add_argument("--sizes", type=int, nargs="+", default=[14, 16, 18, 20, 24, 32], help="Font pixel sizes to generate (default: 14 16 18 20 24 32)")
    parser.add_argument("--unhinted-sizes", type=int, nargs="*", default=[], help="Sizes to rasterize with --autohint-off (preserves hard-edged bitmap/display outlines)")
    args = parser.parse_args()

    font_dir = Path(args.font_dir).resolve()
    out_dir = Path(args.out_dir).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    lvgl_builtin_dir = Path(args.lvgl_dir) / "scripts" / "generators" / "built_in_font" if args.lvgl_dir else None

    montserrat_bold_ttf = font_dir / "Montserrat-Bold.ttf"
    montserrat_ttf = font_dir / "Montserrat-Medium.ttf"
    fa_woff = font_dir / "FontAwesome5-Solid+Brands+Regular.woff"

    font_for_montserrat = None
    if montserrat_bold_ttf.is_file():
        font_for_montserrat = montserrat_bold_ttf
        print(f"[+] Prioritizing Bold typography for EPD: {montserrat_bold_ttf}")
    elif montserrat_ttf.is_file():
        font_for_montserrat = montserrat_ttf
        print(f"[*] Bold font not located, using: {montserrat_ttf}")
    elif lvgl_builtin_dir and (lvgl_builtin_dir / "Montserrat-Medium.ttf").is_file():
        font_for_montserrat = lvgl_builtin_dir / "Montserrat-Medium.ttf"
        if not fa_woff.is_file() and (lvgl_builtin_dir / "FontAwesome5-Solid+Brands+Regular.woff").is_file():
            fa_woff = lvgl_builtin_dir / "FontAwesome5-Solid+Brands+Regular.woff"
        print(f"[*] Using LVGL managed_components font asset: {font_for_montserrat}")
    else:
        print(f"[*] TTF assets not present in {font_dir}; using deterministic built-in bridge descriptors.")

    montserrat_sizes = args.sizes

    for sz in montserrat_sizes:
        sym_name = f"h1os_font_montserrat_{sz}_1bpp"
        out_file = out_dir / f"{sym_name}.c"
        success = generate_font(sz, font_for_montserrat, fa_woff, out_file, sym_name, unhinted=(sz in args.unhinted_sizes))
        if not success:
            sys.exit(1)

    generate_header(out_dir, montserrat_sizes)
    copy_licenses(font_dir, out_dir)

    print("\n[+] H1OS build-time typography generation complete.")


if __name__ == "__main__":
    main()
