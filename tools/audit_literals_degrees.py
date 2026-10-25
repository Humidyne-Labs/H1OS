#!/usr/bin/env python3
"""
audit_literals_degrees.py
-------------------------
Classifies codebase integer literals into 3 distinct risk tiers:
  - 1st Degree: Bitwise masks, shifts, pin mappings, register addresses, state codes, and enums (Structural / State Protocol)
  - 2nd Degree: Mathematical polynomials, metrological constants, unit scales, state curve tables (Contextual / Metrological)
  - 3rd Degree: Timeouts, delays, thresholds, stack sizes, loop bounds (High-Risk Operational Magic Numbers)
"""

import os
import sys
import re

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from tools.scan_hardcoded_integers import scan_directory

def classify_finding(f: dict, file_path: str) -> dict:
    ctx = f['context']
    token = f['token']
    norm = f['normalized']
    val = f['value']

    degree = 3
    category = "Magic Constant"
    rationale = ""

    # =========================================================================
    # 1st Degree: Structural, Hardware, State Variables & Enums
    # =========================================================================
    if f['is_hex']:
        if any(w in ctx for w in ['REG', '0x', '0X', 'ADDR', 'CHIP_ID', 'BIT']):
            degree = 1
            category = "Register Address / Bitmask"
            rationale = "Hardware register address or bitmask literal."
        elif 'palette' in ctx.lower() or 'mask' in ctx.lower():
            degree = 1
            category = "Bitmask / Pixel Mask"
            rationale = "Pixel manipulation bitmask."
        else:
            degree = 1
            category = "Hex Literal"
            rationale = "Hexadecimal constant."
    elif any(term in ctx for term in ['#define HAL_PIN_', '#define H1OS_PIN_', 'GPIO_NUM_', 'PIN_FUNC_']) or re.search(r'GPIO\s*' + re.escape(norm), ctx):
        degree = 1
        category = "Hardware Pin Mapping"
        rationale = "PCB GPIO physical pin assignment."
    elif re.search(r'(<<|>>)\s*' + re.escape(norm), ctx) or re.search(re.escape(norm) + r'\s*(<<|>>)', ctx):
        degree = 1
        category = "Bit Shift Operator"
        rationale = "Bitwise shift count."
    elif re.search(r'(&|\||\^)\s*' + re.escape(norm), ctx) or re.search(re.escape(norm) + r'\s*(&|\||\^)', ctx):
        degree = 1
        category = "Bitwise Mask Operation"
        rationale = "Bitwise bit extraction."
    elif 'sizeof(' in ctx:
        degree = 1
        category = "Sizeof / Type Boundary"
        rationale = "Type/memory boundary."
    elif re.search(r'\bcase\s+' + re.escape(norm) + r'\s*:', ctx):
        degree = 1
        category = "State Machine Case / Switch Label"
        rationale = "State machine branch case discriminator."
    elif any(state_var in ctx for state_var in [
        'ulp_last_wake_cause', 'ulp_last_wake_btn', 'ulp_dispatch_reason',
        'flow ==', 'flow !=', 'mode ==', 'mode !=', 'state ==', 'state !=',
        'status ==', 'status !=', 'cause ==', 'cause !=', 'reason ==', 'reason !=',
        'valid_trend'
    ]):
        degree = 1
        category = "State Variable / Enum Discriminator"
        rationale = "Protocol or state machine enum state comparison."
    elif any(term in ctx for term in ['enum ', 'typedef enum', 'H1OS_CHIME_', 'H1OS_FLOW_']):
        degree = 1
        category = "Enum Definition / Identifier"
        rationale = "Enumeration definition value."

    # =========================================================================
    # 2nd Degree: Math, Metrology, Conversion Scales & Curve Tables
    # =========================================================================
    elif any(term in ctx for term in ['1000000', '1000ULL', '1000LL', '1000.0', '100ULL', '100LL', '1000']):
        degree = 2
        category = "Unit Scale Factor (s/ms/us)"
        rationale = "Standard temporal or metric unit scaling factor."
    elif any(term in ctx for term in ['179651', '65535', '17500', '10000U', '-4500', '4500', '12500', '-4000', '2052']):
        degree = 2
        category = "Metrological Polynomial Constant"
        rationale = "Sensirion SHTC3 / ESP32 TSENS polynomial curve coefficient."
    elif any(term in ctx for term in ['EPD_WIDTH / 8', 'EPD_HEIGHT / 8', 'bytes_per_line', 'epd_stride', 'PALETTE_SIZE', 'FRAME_SIZE']):
        degree = 2
        category = "Display Geometry Math"
        rationale = "EPD 1-bit-per-pixel buffer geometry math."
    elif 's_soc_lut' in ctx or any(term in ctx for term in ['{3300,', '{3400,', '{3500,', '{3600,', '{3700,', '{3800,', '{3900,', '{4000,', '{4100,', '{4180,']):
        degree = 2
        category = "Battery State-of-Charge Curve Table"
        rationale = "Empirical LiPo cell discharge lookup table point."
    elif any(term in file_path for term in ['sub_audio.c']) and any(c in ctx for c in ['0x', '{', '}']):
        degree = 2
        category = "Audio Attenuation Table Entry"
        rationale = "Logarithmic attenuation lookup table entry."

    # =========================================================================
    # 3rd Degree: Operational Magic Numbers (Timeouts, Thresholds, Allocations)
    # =========================================================================
    else:
        if any(term in ctx for term in ['timeout', 'wait_ms', 'delay', 'Timeout', 'pdMS_TO_TICKS', 'esp_rom_delay_us', 'vTaskDelay', 'long_press', 'timeout_us']):
            degree = 3
            category = "Timeout / Delay Duration"
            rationale = "Hardcoded time duration in milliseconds or microseconds."
        elif any(term in ctx for term in ['xTaskCreate', 'xTaskCreatePinnedToCore', 'stack_depth', 'stack']):
            degree = 3
            category = "Stack Size / RTOS Priority"
            rationale = "FreeRTOS task stack size or scheduler priority literal."
        elif any(term in ctx for term in ['mV', 'vbat', 'soc', 'threshold', '3250', '4000', '3300', '4200']):
            degree = 3
            category = "Battery / Voltage Threshold"
            rationale = "Critical electrical or state-of-charge threshold limit."
        elif any(term in ctx for term in ['attempt', 'retry', 'stable_high', 'for (int32_t i = 0; i <']):
            degree = 3
            category = "Loop Bound / Retry Limit"
            rationale = "Arbitrary loop retry limit or debounce counter."
        else:
            degree = 3
            category = "Magic Integer Constant"
            rationale = "Literal integer without named macro abstraction."

    f['degree'] = degree
    f['category'] = category
    f['rationale'] = rationale
    return f

def run_audit(target_dir='components'):
    raw_results = scan_directory(target_dir, ('.c', '.h', '.cpp', '.hpp'), exclude_trivial=True)
    classified = {}
    for fpath, items in raw_results.items():
        classified[fpath] = [classify_finding(item, fpath) for item in items]
    return classified

def generate_markdown_report(results: dict, out_file: str):
    total = sum(len(v) for v in results.values())
    d1 = sum(sum(1 for x in v if x['degree'] == 1) for v in results.values())
    d2 = sum(sum(1 for x in v if x['degree'] == 2) for v in results.values())
    d3 = sum(sum(1 for x in v if x['degree'] == 3) for v in results.values())

    lines = []
    lines.append("# H1OS Firmware Literal Integer & Magic Constant Audit Report")
    lines.append("")
    lines.append("> **Audit Target:** `components/` (ESP-IDF Firmware Core & Drivers)  ")
    lines.append("> **Analysis Methodology:** Space-delimited string tokenization, delimiter stripping, and 3-Tier Risk Degree Classification.")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("## 1. Executive Summary & Degree Taxonomy")
    lines.append("")
    lines.append("| Tier | Classification | Criteria | Risk Level | Total Count | Percentage |")
    lines.append("| :---: | :--- | :--- | :---: | :---: | :---: |")
    lines.append(f"| **1st Degree** | Structural / Protocol & Enums | Bitmasks (`& 0xFF`), shifts (`<< 8`), pin mappings (`GPIO 17`), register addresses, state machine cases, state variables (`ulp_last_wake_cause`), and enum definitions | **Acceptable** | {d1} | {d1/total*100:.1f}% |")
    lines.append(f"| **2nd Degree** | Mathematical & Metrology | Sensor transfer functions (`65535`, `17500`), unit scaling (`1000ULL`), battery SoC curve tables (`s_soc_lut`), audio attenuation curves | **Contextual** | {d2} | {d2/total*100:.1f}% |")
    lines.append(f"| **3rd Degree** | Operational Magic Numbers | Timeouts, delays, electrical cutoff thresholds (`3250` mV), task stack floors, RTOS priorities, loop retry bounds | **Actionable** | {d3} | {d3/total*100:.1f}% |")
    lines.append(f"| **TOTAL** | — | Non-trivial integers across `components/` | — | **{total}** | **100.0%** |")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("## 2. Inventory by Component & Degree")
    lines.append("")
    lines.append("| Component File | 1st Degree (Structural & Enums) | 2nd Degree (Math & Curve Tables) | 3rd Degree (Operational Magic Numbers) | Total Literals |")
    lines.append("| :--- | :---: | :---: | :---: | :---: |")

    for fpath, items in sorted(results.items()):
        c1 = sum(1 for x in items if x['degree'] == 1)
        c2 = sum(1 for x in items if x['degree'] == 2)
        c3 = sum(1 for x in items if x['degree'] == 3)
        lines.append(f"| `{fpath}` | {c1} | {c2} | **{c3}** | {len(items)} |")

    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("## 3. High-Priority 3rd Degree Magic Literals (Actionable Review)")
    lines.append("")
    lines.append("The following table isolates true 3rd degree operational magic numbers (timeouts, stack floors, retry limits, debounce delays, electrical thresholds):")
    lines.append("")
    lines.append("| File | Line | Token | Category | Code Context | Rationale / Recommended Abstraction |")
    lines.append("| :--- | :---: | :---: | :--- | :--- | :--- |")

    for fpath, items in sorted(results.items()):
        d3_items = [x for x in items if x['degree'] == 3]
        for it in d3_items:
            ctx_esc = it['context'].replace('|', '\\|')
            lines.append(f"| `{os.path.basename(fpath)}` | {it['line_no']} | `{it['token']}` | **{it['category']}** | `{ctx_esc}` | {it['rationale']} |")

    lines.append("")
    report_text = "\n".join(lines)

    with open(out_file, 'w', encoding='utf-8') as f:
        f.write(report_text)
    print(f"Report written to: {out_file}")

if __name__ == "__main__":
    classified_results = run_audit('components')
    out_path = os.path.join('docs', 'agent_notes', 'audits', 'literal_integers_degree_audit.md')
    generate_markdown_report(classified_results, out_path)
