# Jules Instructions for H1OS

Welcome, Jules! These instructions govern all tasks, refactors, formatting, and contributions to the **H1OS** firmware repository. Follow these constraints strictly.

---

## 1. Project Architecture & Scope

H1OS is an event-driven, ultra-low-power operating system for ESP32-S3 and ULP-RISC-V hardware:
- **`components/h1os/`**: Core OS component.
  - `include/h1os/`: Public Layer 1 HAL, Subsystem, and Orchestrator headers.
  - `src/`: C and C++ implementation sources.
  - `ulp/`: ULP-RISC-V assembly and C firmware for sub-milliamp background hardware monitoring.
  - `bootloader_components/`: Second-stage bootloader hooks for early power-hold and brownout mitigation.
- **`examples/`**: Applications and target reference designs (e.g. `examples/H1OS/`, `examples/boilerplate/`).
- **`tools/`**: Host-side audit, formatting, and build verification utilities.

---

## 2. Strict Directory & File Exclusions

**NEVER modify, delete, or commit files in these directories:**
- `managed_components/**` (ESP Component Registry managed dependencies)
- `build/**`, `build_dev/**`, `build_prod/**` (CMake / Ninja build trees)
- `.gemini/**`

---

## 3. Formatting & Code Style Standards

H1OS enforces a zero-column-limit, clean-layout philosophy defined in `.clang-format`:

1. **No Artificial Line Wrapping (`ColumnLimit: 0`)**:
   - Clang-format does not break lines purely due to length.
   - Write clean, natural statements without arbitrary mid-expression breaks.
   - Avoid excessive horizontal sprawling; break lines logically at natural semantic operators (e.g., function parameters, logical operators) when it aids readability.

2. **Standard Doxygen Header**:
   Every `.c`, `.cpp`, and `.h` source file must begin with:
   ```c
   /**
    * @file <filename>
    * @brief <Accurate 1-line functional summary>
    *
    * Copyright (c) 2026 Humidyne Labs
    * SPDX-License-Identifier: MIT
    */
   ```

3. **Protection Directives (`clang-format off` / `on`)**:
   - Never remove or alter `// clang-format off` and `// clang-format on` blocks.
   - These protect critical hardware register bitmasks, ULP variable dispatch tables, calibration arrays, and raw pixel bitmaps.

4. **Formatting Verification**:
   - Verify formatting with:
     ```bash
     python tools/check_format.py --check
     ```
   - Automatically format in-place with:
     ```bash
     python tools/check_format.py
     ```

---

## 4. Semantic Code Organization & Beautification

When asked to format, organize, or beautify code:
1. **Vertical Spacing & Paragraphing**:
   - Group related variable declarations together at function starts.
   - Separate logical phases (validation -> hardware setup -> processing -> cleanup) with a single blank line.
   - No redundant whitespace (max 1 blank line inside functions, 2 between functions).
2. **Flatten Logic with Guard Clauses**:
   - Convert deeply nested `if/else` ladders into early returns (`if (err != ESP_OK) return err;`).
3. **Preserve ABI & Hardware Semantics**:
   - Do NOT rename public APIs, struct fields, enum constants, or macros.
   - Do NOT alter register addresses, bit shifts, or timing delays (`vTaskDelay`, `esp_rom_delay_us`).

---

## 5. Verification Commands

Always run these verifications before completing a task:
1. **Format Check**:
   ```bash
   python tools/check_format.py --check
   ```
2. **Documentation Audit**:
   ```bash
   python tools/audit_gfm.py
   python tools/audit_docs.py
   ```
3. **Incremental Firmware Build (Never clean build)**:
   ```powershell
   powershell -NoProfile -ExecutionPolicy Bypass -Command "& 'C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1' ; ninja -C examples/H1OS/build_dev"
   ```
