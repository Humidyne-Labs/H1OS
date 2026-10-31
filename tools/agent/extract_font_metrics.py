#!/usr/bin/env python3
"""
H1OS Font Metrics & Kerning Extractor.
Parses compiled LVGL 1bpp font C descriptors (sizes 14 to 32) and exports:
  1. tools/fonts/char_widths_montserrat_<size>.csv (advance widths, bounding boxes, offsets)
  2. tools/fonts/kern_pairs_montserrat_<size>.csv (class-based kerning pair adjustments)
"""

import argparse
import csv
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
OUTPUT_DIR = REPO_ROOT / "tools" / "fonts"
FONT_SIZES = [14, 16, 18, 20, 24, 32]


def resolve_generated_dir(custom_build_dir: str | None = None) -> Path:
    """Resolve directory containing generated C font files."""
    if custom_build_dir:
        p = Path(custom_build_dir).resolve()
        sub = p / "esp-idf" / "h1os" / "generated_fonts"
        return sub if sub.is_dir() else p

    candidates = [
        REPO_ROOT / "examples" / "H1OS" / "build_dev" / "esp-idf" / "h1os" / "generated_fonts",
        REPO_ROOT / "examples" / "H1OS" / "build_prod" / "esp-idf" / "h1os" / "generated_fonts",
    ]
    for c in candidates:
        if c.is_dir():
            return c
    return candidates[0]


def parse_font_c_file(c_path: Path) -> tuple[dict, dict]:
    """Parse glyph_dsc and kerning classes from a compiled LVGL font descriptor C file."""
    content = c_path.read_text(encoding="utf-8")

    # 1. Parse glyph_dsc block
    marker = "static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {"
    start = content.find(marker)
    if start == -1:
        raise ValueError(f"glyph_dsc table not found in {c_path}")
    end = content.find("};\n\n/*---------------------", start)
    if end == -1:
        end = content.find("};", start)
    glyph_block = content[start + len(marker):end]

    entry_pat = re.compile(
        r"\{\.bitmap_index\s*=\s*(\d+),\s*\.adv_w\s*=\s*(\d+),\s*\.box_w\s*=\s*(\d+),\s*\.box_h\s*=\s*(\d+),\s*\.ofs_x\s*=\s*(-?\d+),\s*\.ofs_y\s*=\s*(-?\d+)\}"
    )
    glyph_entries = [
        {
            "bitmap_index": int(m.group(1)),
            "adv_w": int(m.group(2)),
            "box_w": int(m.group(3)),
            "box_h": int(m.group(4)),
            "ofs_x": int(m.group(5)),
            "ofs_y": int(m.group(6)),
        }
        for m in entry_pat.finditer(glyph_block)
    ]

    # 2. Parse unicode_list_1 (extended unicode mappings)
    unicode_list = []
    u_marker = "static const uint16_t unicode_list_1[] = {"
    u_start = content.find(u_marker)
    if u_start != -1:
        u_end = content.find("};", u_start)
        u_block = content[u_start + len(u_marker):u_end]
        unicode_list = [int(v, 16) for v in re.findall(r"0x[0-9a-fA-F]+", u_block)]

    # 3. Map glyph IDs to Unicode character codes
    chars = {}
    glyph_to_code = {}

    for code in range(32, 127):
        glyph_id = code - 32 + 1
        if glyph_id < len(glyph_entries):
            chars[code] = glyph_entries[glyph_id]
            glyph_to_code[glyph_id] = code

    for i, offset in enumerate(unicode_list):
        code = 176 + offset
        glyph_id = 96 + i
        if glyph_id < len(glyph_entries):
            chars[code] = glyph_entries[glyph_id]
            glyph_to_code[glyph_id] = code

    # 4. Parse kerning classes
    kern_pairs = {}
    left_m = re.search(r"static const uint8_t kern_left_class_mapping\[\]\s*=\s*\{([^}]+)\};", content)
    right_m = re.search(r"static const uint8_t kern_right_class_mapping\[\]\s*=\s*\{([^}]+)\};", content)
    vals_m = re.search(r"static const int8_t kern_class_values\[\]\s*=\s*\{([^}]+)\};", content)

    if left_m and right_m and vals_m:
        left_map = [int(x.strip()) for x in left_m.group(1).split(",") if x.strip()]
        right_map = [int(x.strip()) for x in right_m.group(1).split(",") if x.strip()]
        kern_vals = [int(x.strip()) for x in vals_m.group(1).split(",") if x.strip()]

        if left_map and right_map and kern_vals:
            right_class_cnt = max(right_map) + 1
            for g_left, c_left in enumerate(left_map):
                if c_left == 0 or g_left not in glyph_to_code:
                    continue
                code_l = glyph_to_code[g_left]
                for g_right, c_right in enumerate(right_map):
                    if c_right == 0 or g_right not in glyph_to_code:
                        continue
                    code_r = glyph_to_code[g_right]
                    idx = (c_left * right_class_cnt) + c_right
                    if idx < len(kern_vals) and kern_vals[idx] != 0:
                        kern_pairs[(code_l, code_r)] = kern_vals[idx]

    return chars, kern_pairs


def export_char_csv(chars: dict, out_csv: Path):
    """Write glyph advance width table to CSV."""
    fieldnames = ["char", "unicode_hex", "unicode_dec", "adv_w_raw", "width_px", "box_w", "box_h", "ofs_x", "ofs_y"]
    with open(out_csv, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for code, g in sorted(chars.items()):
            try:
                ch_repr = "<SPACE>" if code == 32 else (chr(code) if 32 < code < 127 else f"<U+{code:04X}>")
            except Exception:
                ch_repr = f"<U+{code:04X}>"

            writer.writerow({
                "char": ch_repr,
                "unicode_hex": f"0x{code:04X}",
                "unicode_dec": code,
                "adv_w_raw": g["adv_w"],
                "width_px": round(g["adv_w"] / 16.0, 4),
                "box_w": g["box_w"],
                "box_h": g["box_h"],
                "ofs_x": g["ofs_x"],
                "ofs_y": g["ofs_y"],
            })
    print(f"  Exported {len(chars):3d} glyphs -> {out_csv.name}")


def export_kern_csv(kern_pairs: dict, out_csv: Path):
    """Write kerning pair adjustment table to CSV."""
    fieldnames = ["left_char", "left_code", "right_char", "right_code", "kern_raw_16th", "kern_px"]
    with open(out_csv, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for (cl, cr), kv in sorted(kern_pairs.items()):
            try:
                sl = chr(cl) if cl >= 32 else f"<U+{cl:04X}>"
            except Exception:
                sl = f"<U+{cl:04X}>"
            try:
                sr = chr(cr) if cr >= 32 else f"<U+{cr:04X}>"
            except Exception:
                sr = f"<U+{cr:04X}>"

            writer.writerow({
                "left_char": sl,
                "left_code": f"0x{cl:04X}",
                "right_char": sr,
                "right_code": f"0x{cr:04X}",
                "kern_raw_16th": kv,
                "kern_px": round(kv / 16.0, 4),
            })
    print(f"  Exported {len(kern_pairs):4d} kerning pairs -> {out_csv.name}")


def main():
    parser = argparse.ArgumentParser(description="Extract LVGL font metrics and kerning tables into CSV")
    parser.add_argument("-B", "--build-dir", type=str, default=None, help="Path to ESP-IDF build directory")
    args = parser.parse_args()

    gen_dir = resolve_generated_dir(args.build_dir)
    if not gen_dir.is_dir():
        print(f"[!] Error: Generated fonts directory not found: {gen_dir}")
        print("    Build the project first (e.g. idf.py -B build_dev --preset dev build).")
        sys.exit(1)

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    print("=" * 70)
    print("EXTRACTING METRICS & KERNING FOR ALL FONTS (14..32)")
    print(f"Source: {gen_dir}")
    print(f"Target: {OUTPUT_DIR}")
    print("=" * 70)

    for sz in FONT_SIZES:
        font_file = gen_dir / f"h1os_font_montserrat_{sz}_1bpp.c"
        if not font_file.is_file():
            print(f"[!] Warning: {font_file.name} not found, skipping.")
            continue

        chars, kern_pairs = parse_font_c_file(font_file)
        export_char_csv(chars, OUTPUT_DIR / f"char_widths_montserrat_{sz}.csv")
        export_kern_csv(kern_pairs, OUTPUT_DIR / f"kern_pairs_montserrat_{sz}.csv")

    print("=" * 70)
    print("ALL FONT METRICS SUCCESSFULLY GENERATED!")
    print("=" * 70)


if __name__ == "__main__":
    main()
