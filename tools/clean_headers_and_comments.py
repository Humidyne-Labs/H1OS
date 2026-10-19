#!/usr/bin/env python3
"""
H1OS Header Standardizer & Comment Stripper (Lexer-Based)
Standardizes top Doxygen header comment blocks, strips internal comments across file bodies,
preserves clang-format directives, trims whitespace, and formats the codebase.
"""

import os
import re
import sys
import subprocess
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

FILE_BRIEFS = {
    "h1os_boot_hook.c": "Early 2nd-stage bootloader power hold hook for ESP32-S3",
    "h1os.h": "H1OS E-Class Environmental Telemetry OS master public API",
    "h1os_lvgl.h": "Layer 4: LVGL v9 graphics port, keypad indev, and interactive event loop",
    "h1os_time.h": "Layer 4: System time services, timezone management, and external SNTP bridge",
    "h1os_version.h": "H1OS semantic version information and inline getters",
    "hal_flash.h": "Layer 1: Raw flash partition storage driver for EPD framebuffer",
    "hal_i2c.h": "Layer 1: Thread-safe shared I2C master bus driver",
    "hal_io.h": "Layer 1: Base pinout, power latch, and sleep pad hold driver",
    "hal_spi.h": "Layer 1: DMA-backed SPI master bus driver for SSD1681 display",
    "hal_types.h": "Layer 1: Base hardware constants, pinout mappings, and primitive types",
    "orch_display_sync.h": "Layer 3: Deferred flash frame sync engine",
    "orch_flow.h": "Layer 3: Execution flow arbiter and thermal lockout MUX",
    "orch_math.h": "Layer 3: Class-E psychrometric invariant engine and EWMA filters",
    "orch_state.h": "Layer 3: Persistent RTC Slow SRAM state and ring buffer manager",
    "orch_wake_stub.h": "Layer 3: RTC Fast Memory deep sleep wake stub (<3ms Flow A sample burst)",
    "sub_audio.h": "Layer 2: ES8311 codec and NS4168 audio power/standby driver",
    "sub_display.h": "Layer 2: SSD1681 1.54\" 200x200 monochrome e-Paper display manager",
    "sub_nvs.h": "Layer 2: Non-volatile configuration storage (NVS) manager",
    "sub_power.h": "Layer 2: Battery ADC monitoring, dynamic frequency scaling, and deep sleep engine",
    "sub_rtc.h": "Layer 2: PCF85063A real-time clock and hardware countdown timer driver",
    "sub_sdcard.h": "Layer 2: MicroSD card subsystem manager (1-bit SDMMC FATFS)",
    "sub_sensor.h": "Layer 2: Sensirion SHTC3 and ESP32-S3 internal TSENS driver",
    "h1os_lifecycle.c": "Layer 4: Declarative application lifecycle engine implementation",
    "h1os_lvgl.cpp": "Layer 4: LVGL v9 FreeRTOS integration port and keypad input driver",
    "h1os_time.c": "Layer 4: System time services, timezone management, and RTC bridge",
    "hal_flash.c": "Layer 1: Raw flash partition storage implementation",
    "hal_i2c.c": "Layer 1: Shared I2C master bus driver implementation",
    "hal_io.c": "Layer 1: Base pin, pad hold, and power rail driver implementation",
    "hal_spi.c": "Layer 1: SPI master bus driver implementation",
    "orch_display_sync.c": "Layer 3: Deferred flash frame sync engine implementation",
    "orch_flow.c": "Layer 3: Execution flow arbiter and thermal lockout MUX implementation",
    "orch_math.c": "Layer 3: Class-E psychrometric and signal math implementation",
    "orch_state.c": "Layer 3: Persistent RTC Slow SRAM state implementation",
    "orch_wake_stub.c": "Layer 3: RTC Fast Memory deep sleep wake stub implementation",
    "sub_audio.c": "Layer 2: ES8311 codec and NS4168 audio driver implementation",
    "sub_display.cpp": "Layer 2: SSD1681 e-Paper display manager implementation",
    "sub_nvs.c": "Layer 2: Non-volatile storage (NVS) manager implementation",
    "sub_power.c": "Layer 2: Battery ADC monitoring, DFS, and sleep engine implementation",
    "sub_rtc.c": "Layer 2: PCF85063A real-time clock driver implementation",
    "sub_sdcard.c": "Layer 2: MicroSD card subsystem manager implementation",
    "sub_sensor.c": "Layer 2: Sensirion SHTC3 and MCU TSENS driver implementation",
    "main.c": "Application entry point and lifecycle orchestration",
    "battery_estimator.c": "Empirical battery state-of-charge estimator implementation",
    "battery_estimator.h": "Empirical battery state-of-charge estimator interface",
    "humid1_cyber_wave.c": "HUMID1 cyber-wave EPD boot graphic asset",
    "humid1_cyber_wave.h": "HUMID1 cyber-wave EPD boot graphic descriptor",
    "screen_base.c": "Common base layout builder for 200x200 monochrome e-Paper screens",
    "screen_diagnostics.c": "Screen 4: Verbose system diagnostics page",
    "screen_env_hero.c": "Screen 1: Primary environmental hero display page",
    "screen_psychrometrics.c": "Screen 2: Psychrometric engine and invariant metrics page",
    "screen_system_health.c": "Screen 3: System health, autonomy, and power page",
    "screens.h": "H1OS showcase application modular screen layouts header",
    "power_hold_hook.c": "Early 2nd-stage bootloader power hold hook for test app",
    "shared_test_data.h": "Shared test data definitions between Xtensa and ULP",
    "ulp_test_main.c": "ULP test firmware main routine",
}

HEADER_TEMPLATE = """/**
 * @file {filename}
 * @brief {brief}
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */
"""


def get_brief_for_file(file_path: Path) -> str:
    name = file_path.name
    posix_path = file_path.as_posix()
    if "ulp/main.c" in posix_path:
        return "Pure event-mode ULP-RISC-V coprocessor hardware monitor"
    elif "examples/boilerplate" in posix_path:
        return "H1OS turnkey starter application boilerplate"
    elif "examples/H1OS" in posix_path:
        return "H1OS showcase application: modular 4-screen environmental telemetry"
    elif "examples/riscv_test/main/main.c" in posix_path:
        return "ULP-RISC-V verification harness application main"

    return FILE_BRIEFS.get(name, f"Source implementation for {name}")


def strip_comments_safely(text: str) -> str:
    """
    Exact lexer state-machine comment stripper.
    Correctly ignores quotes inside comments (e.g. 1.54")
    and slashes inside string literals ("http://").
    Preserves // clang-format on/off directives.
    """
    out = []
    i = 0
    n = len(text)
    state = "NORMAL"

    while i < n:
        c = text[i]
        next_c = text[i + 1] if i + 1 < n else ""

        if state == "NORMAL":
            if c == '"':
                state = "STRING"
                out.append(c)
            elif c == "'":
                state = "CHAR"
                out.append(c)
            elif c == "/" and next_c == "/":
                line_rest = text[i:].split("\n", 1)[0]
                if "clang-format" in line_rest:
                    out.append(line_rest)
                    i += len(line_rest) - 1
                else:
                    state = "LINE_COMMENT"
                    i += 1
            elif c == "/" and next_c == "*":
                state = "BLOCK_COMMENT"
                i += 1
            else:
                out.append(c)
        elif state == "STRING":
            out.append(c)
            if c == "\\":
                i += 1
                if i < n:
                    out.append(text[i])
            elif c == '"':
                state = "NORMAL"
        elif state == "CHAR":
            out.append(c)
            if c == "\\":
                i += 1
                if i < n:
                    out.append(text[i])
            elif c == "'":
                state = "NORMAL"
        elif state == "LINE_COMMENT":
            if c == "\n":
                out.append(c)
                state = "NORMAL"
        elif state == "BLOCK_COMMENT":
            if c == "*" and next_c == "/":
                state = "NORMAL"
                i += 1
                out.append(" ")

        i += 1
    return "".join(out)


def process_file_content(content: str, filename: str, brief: str) -> str:
    # 1. Strip existing top comment block
    content = content.lstrip()
    if content.startswith("/*"):
        end_idx = content.find("*/")
        if end_idx != -1:
            content = content[end_idx + 2:].lstrip()
    elif content.startswith("//"):
        lines = content.splitlines()
        first_non_comment = 0
        for i, line in enumerate(lines):
            if not line.strip().startswith("//"):
                first_non_comment = i
                break
        content = "\n".join(lines[first_non_comment:]).lstrip()

    # 2. Strip internal comments using exact lexer state machine
    stripped_body = strip_comments_safely(content)

    # 3. Clean up empty lines and trailing whitespace
    lines = [line.rstrip() for line in stripped_body.splitlines()]
    cleaned_lines = []
    prev_empty = False
    for line in lines:
        is_empty = (len(line) == 0)
        if is_empty and prev_empty:
            continue
        cleaned_lines.append(line)
        prev_empty = is_empty

    body = "\n".join(cleaned_lines).strip()

    # 4. Prepend standardized Doxygen header
    header = HEADER_TEMPLATE.format(filename=filename, brief=brief)
    return header + "\n" + body + "\n"


def find_source_files(repo_root: Path):
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
    files = find_source_files(repo_root)
    print(f"[Header & Clean] Processing {len(files)} source files...")

    for file_path in files:
        with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
            original = f.read()

        brief = get_brief_for_file(file_path)
        cleaned = process_file_content(original, file_path.name, brief)

        with open(file_path, "w", encoding="utf-8") as f:
            f.write(cleaned)

        print(f"  [PROCESSED] {file_path.relative_to(repo_root)}")

    print("\n[Header & Clean] Running clang-format pass...")
    subprocess.run([sys.executable, str(repo_root / "tools" / "check_format.py")], check=True)
    print("\n[Header & Clean] Successfully standardized headers and stripped internal comments!")


if __name__ == "__main__":
    main()
