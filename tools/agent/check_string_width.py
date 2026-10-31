#!/usr/bin/env python3
"""
H1OS Font String Width & Kerning Validation Engine.
Calculates exact sub-pixel string widths using LVGL 1bpp Montserrat font metrics and kerning classes,
validating against the 200x200 display's 188.0 px usable margin.
"""

import argparse
import csv
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
METRICS_DIR = REPO_ROOT / "tools" / "fonts"
SCREEN_DIR = REPO_ROOT / "examples" / "H1OS" / "main" / "screens"
MAX_USABLE_WIDTH_PX = 188.0  # 200px width - 6px left margin - 6px right margin

# Built-in FontAwesome 5 Unicode mappings for LVGL icons
LVGL_SYMBOL_MAP = {
    "LV_SYMBOL_AUDIO": "\uf001",
    "LV_SYMBOL_VIDEO": "\uf008",
    "LV_SYMBOL_LIST": "\uf00b",
    "LV_SYMBOL_OK": "\uf00c",
    "LV_SYMBOL_CLOSE": "\uf00d",
    "LV_SYMBOL_POWER": "\uf011",
    "LV_SYMBOL_SETTINGS": "\uf013",
    "LV_SYMBOL_HOME": "\uf015",
    "LV_SYMBOL_DOWNLOAD": "\uf019",
    "LV_SYMBOL_DRIVE": "\uf01c",
    "LV_SYMBOL_REFRESH": "\uf021",
    "LV_SYMBOL_MUTE": "\uf026",
    "LV_SYMBOL_VOLUME_MID": "\uf027",
    "LV_SYMBOL_VOLUME_MAX": "\uf028",
    "LV_SYMBOL_IMAGE": "\uf03e",
    "LV_SYMBOL_TINT": "\uf043",
    "LV_SYMBOL_PREV": "\uf048",
    "LV_SYMBOL_PLAY": "\uf04b",
    "LV_SYMBOL_PAUSE": "\uf04c",
    "LV_SYMBOL_STOP": "\uf04d",
    "LV_SYMBOL_NEXT": "\uf051",
    "LV_SYMBOL_PLUS": "\uf067",
    "LV_SYMBOL_MINUS": "\uf068",
    "LV_SYMBOL_WARNING": "\uf071",
    "LV_SYMBOL_CHARGE": "\uf0e7",
    "LV_SYMBOL_BELL": "\uf0f3",
    "LV_SYMBOL_WIFI": "\uf1eb",
    "LV_SYMBOL_BATTERY_FULL": "\uf240",
    "LV_SYMBOL_BATTERY_3": "\uf241",
    "LV_SYMBOL_BATTERY_2": "\uf242",
    "LV_SYMBOL_BATTERY_1": "\uf243",
    "LV_SYMBOL_BATTERY_EMPTY": "\uf244",
    "LV_SYMBOL_USB": "\uf287",
    "LV_SYMBOL_BLUETOOTH": "\uf293",
    "LV_SYMBOL_SD_CARD": "\uf7c2",
}


class LVGLFontMetrics:
    """Loads authoritative font metrics from tools/fonts/ CSV tables."""

    def __init__(self, size: int):
        self.size = size
        self.widths: dict[int, float] = {}
        self.kern_pairs: dict[tuple[int, int], float] = {}
        self._load_from_csv()

    def _load_from_csv(self):
        char_csv = METRICS_DIR / f"char_widths_montserrat_{self.size}.csv"
        kern_csv = METRICS_DIR / f"kern_pairs_montserrat_{self.size}.csv"

        if not char_csv.is_file():
            print(f"[!] Error: Font metric table missing: {char_csv}")
            print(f"    Run 'python tools/agent/extract_font_metrics.py' to generate metrics.")
            sys.exit(1)

        with open(char_csv, "r", encoding="utf-8") as f:
            for row in csv.DictReader(f):
                self.widths[int(row["unicode_dec"])] = float(row["width_px"])

        if kern_csv.is_file():
            with open(kern_csv, "r", encoding="utf-8") as f:
                for row in csv.DictReader(f):
                    left_code = int(row["left_code"], 16)
                    right_code = int(row["right_code"], 16)
                    self.kern_pairs[(left_code, right_code)] = float(row["kern_px"])

    def calc_width(self, text: str) -> tuple[float, list[dict]]:
        """Calculate total pixel width including kerning pair adjustments."""
        total_px = 0.0
        details = []
        prev_code = None

        for ch in text:
            code = ord(ch)
            adv = self.widths.get(code, 8.0)
            kern = self.kern_pairs.get((prev_code, code), 0.0) if prev_code is not None else 0.0

            char_w = adv + kern
            total_px += char_w
            details.append({
                "char": ch,
                "code": code,
                "adv_px": adv,
                "kern_px": kern,
                "total_char_px": char_w,
            })
            prev_code = code

        return round(total_px, 2), details


def audit_screen_files(font: LVGLFontMetrics):
    """Scan all screen source files and validate string templates against layout boundary."""
    print("\n" + "=" * 78)
    print(f"SCREEN SOURCE FILE AUTOMATED STRING WIDTH AUDIT (Threshold: <= {MAX_USABLE_WIDTH_PX:.1f} px)")
    print("=" * 78)

    c_files = sorted(SCREEN_DIR.glob("screen_*.c"))
    if not c_files:
        print(f"[!] No screen files found in {SCREEN_DIR}")
        sys.exit(1)

    total_checked = 0
    overflows = 0
    str_pat = re.compile(r'lv_label_set_text(?:_fmt)?\s*\([^,]+,\s*"([^"\\]*(?:\\.[^"\\]*)*)"', re.DOTALL)

    for c_file in c_files:
        with open(c_file, "r", encoding="utf-8") as f:
            code = f.read()

        # Concatenate LVGL symbol constants (e.g., LV_SYMBOL_TINT " text" -> "\uf043 text")
        for sym_name, sym_char in LVGL_SYMBOL_MAP.items():
            code = re.sub(rf'\b{sym_name}\s*"', f'"{sym_char}', code)
            code = re.sub(rf'"\s*{sym_name}\b', f'{sym_char}"', code)
            code = re.sub(rf'\b{sym_name}\b', f'"{sym_char}"', code)

        for raw_str in str_pat.findall(code):
            # Substitute format specifiers with realistic worst-case values
            sim_str = raw_str
            sim_str = sim_str.replace("%lu", "625").replace("%u", "100").replace("%d", "100")
            sim_str = sim_str.replace("%.2f", "4.00").replace("%.1f", "72.5").replace("%.0f", "120")
            sim_str = sim_str.replace("%+.1f", "+0.0").replace("%3lu", "240")
            sim_str = sim_str.replace("%02X", "00").replace("%X", "00").replace("%%", "%")
            sim_str = sim_str.replace("%s", "CHARGED")
            sim_str = sim_str.replace("\\n", " ").replace('\\"', '"')

            w, _ = font.calc_width(sim_str)
            total_checked += 1
            status = "PASS" if w <= MAX_USABLE_WIDTH_PX else "FAIL"

            if status == "FAIL":
                overflows += 1
                print(f"[{status:4s}] {w:6.2f} px > {MAX_USABLE_WIDTH_PX:.0f} px | {c_file.name:24s} | Template: '{raw_str}' -> Sim: '{sim_str}'")

    if overflows == 0:
        print(f"\nAUDIT VERDICT: ALL {total_checked} STRINGS PASS! Zero screen boundaries breached.")
    else:
        print(f"\nAUDIT VERDICT: {overflows} of {total_checked} STRINGS EXCEED {MAX_USABLE_WIDTH_PX:.0f}px!")
        sys.exit(1)


def main():
    parser = argparse.ArgumentParser(description="H1OS Font Metric and String Width Checker")
    parser.add_argument("string", nargs="?", help="String to calculate width for")
    parser.add_argument("--size", type=int, default=14, choices=[14, 16, 18, 20, 24, 32], help="Font size (default: 14)")
    parser.add_argument("--audit-screens", action="store_true", help="Audit all screen string templates")
    args = parser.parse_args()

    font = LVGLFontMetrics(args.size)

    if args.string:
        w, details = font.calc_width(args.string)
        status = "PASS" if w <= MAX_USABLE_WIDTH_PX else "OVERFLOW"
        print(f"\nFont:   Montserrat-{args.size} 1bpp")
        print(f"String: '{args.string}'")
        print(f"Width:  {w} px (Max: {MAX_USABLE_WIDTH_PX} px) -> [{status}]")
        print("-" * 50)
        print(f"{'Char':<6} {'Adv(px)':<10} {'Kern(px)':<10} {'Total(px)':<10}")
        print("-" * 50)
        for d in details:
            print(f"{d['char']:<6} {d['adv_px']:<10.2f} {d['kern_px']:<10.2f} {d['total_char_px']:<10.2f}")
    else:
        audit_screen_files(font)


if __name__ == "__main__":
    main()
