# Task Prompt: Jules Code Formatting & Semantic Beautification

Use this prompt when kicking off a Jules session to format, organize, or beautify code in H1OS:

```markdown
# Task: Semantic Code Beautification & Formatting for H1OS

## Objective
Act as a Senior Embedded Systems Engineer and Code Aesthetics Specialist. Format, organize, and beautify the C and C++ source code in this repository to maximize legibility, maintainability, and clean layout, without altering any logic, execution semantics, or ABI contracts.

---

## Scope & Constraints

1. **Target Directories:**
   - `components/h1os/` (include, src, ulp, bootloader_components)
   - `examples/`
   
2. **Strict Exclusions (DO NOT TOUCH):**
   - `managed_components/**`
   - `build/**`, `build_dev/**`, `build_prod/**`
   - Submodules or third-party vendored SDK files

3. **Zero Logic Mutation:**
   - Do NOT rename public APIs, structs, enum members, or macros.
   - Do NOT alter logic flow, register addresses, timing delays (`vTaskDelay`, `esp_rom_delay_us`), or bitwise math.
   - Do NOT remove or modify `// clang-format off` and `// clang-format on` directive blocks (especially in `ulp/main.c`, `humid1_cyber_wave.c`, and hardware pinout tables).

---

## Formatting & Structural Rules

1. **File Headers:**
   Every `.c`, `.cpp`, and `.h` file must begin with the standardized Doxygen header:
   ```c
   /**
    * @file <filename>
    * @brief <Accurate 1-line functional summary of the file>
    *
    * Copyright (c) 2026 Humidyne Labs
    * SPDX-License-Identifier: MIT
    */
   ```

2. **Semantic Paragraphing & Vertical Spacing:**
   - Group related variable declarations together at the top of functions or scopes.
   - Separate logical phases of a function (parameter validation -> hardware acquisition -> core processing -> cleanup/return) with a single blank line.
   - Avoid excessive consecutive blank lines (maximum 1 blank line between statements, 2 between functions).

3. **Guard Clauses & Flat Logic:**
   - Flatten deeply nested `if/else` ladders by converting early validation errors into early returns / guard clauses (`if (err != ESP_OK) return err;`).

4. **Hardware Tables & Definitions:**
   - In hardware register tables, LUTs, or calibration structs wrapped with `// clang-format off`, align table columns visually using neat whitespace so that fields, values, and hex constants are easily readable.

5. **Deterministic Formatting & Verification:**
   - Note that `.clang-format` uses `ColumnLimit: 0` (no artificial column wrapping).
   - Run the project format verification:
     ```bash
     python tools/check_format.py
     ```
   - Verify that all modified files pass:
     ```bash
     python tools/check_format.py --check
     ```

---

## Verification & Output Deliverables
1. Run `python tools/check_format.py --check` and verify all files pass with `[OK]`.
2. Run `python tools/audit_gfm.py` to ensure markdown integrity.
3. Verify compilation with `ninja -C examples/H1OS/build_dev`.
4. Provide a clear Git commit message following Conventional Commits:
   `style(format): semantic code organization and layout beautification`
```
