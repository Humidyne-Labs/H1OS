---
name: esp-idf-codegen
description: Conservative, verified C/C++ firmware generation and patching for ESP-IDF projects. Use whenever writing, editing, refactoring, or reviewing ESP32 / ESP-IDF C/C++ source code, drivers, or header files.
---

# ESP-IDF Code Generation Protocol (`v2.4.5-dev`)

## 1. Operating Rules & Blast Radius
- **Atomic Header-Implementation Coherency & Surgical Edits:** Keep edits surgical and scoped strictly to the target subsystem or feature. When changing a public or internal C/C++ prototype, struct layout, or enum, update the `.h` declaration and `.c`/`.cpp` implementation atomically so the build tree remains compilable at every step. Never perform unrelated drive-by rewrites across untouched modules.
- **No Unsolicited Monolithic Overwrites:** Provide exact targeted edits or standalone helper functions. Do not rewrite unmodified setup code or replace whole files unless explicitly refactoring that module or initializing a new file.
- **No Unverified Auto-Commit:** Do not automatically stage, commit, or merge into `main` without completing compilation verification and user approval.

## 2. API Grounding & Zero Hallucination
- **ESP-IDF Registry Check:** Only use standard, existing ESP-IDF v6.1 APIs and drivers.
- **No Invented APIs:** If an API function or macro name is uncertain, do not guess standard-sounding names (e.g., `esp_sleep_enable_ulp_gpio_wakeup()`). Query the local ESP-IDF docs/MCP server or inspect project header files (`h1os.h`, `h1os_lvgl.h`, `hal_types.h`, `sub_*.h`, `orch_*.h`) first.
- **Diagnostics First:** Assume a `clangd` language server is active. Ensure all referenced types, macros, and function declarations have concrete header `#include` statements present in the file, and strictly obey the 4-layer unidirectional boundary hierarchy (`Layer 4 h1os_* -> Layer 3 orch_* -> Layer 2 sub_* -> Layer 1 hal_*`).

## 3. Hardware, Dual-Core Concurrency & Silicon Constraints
- **Pin & Domain Verification:**
  - Verify pin capabilities before configuring (e.g., ESP32-S3 RTC GPIO is strictly `GPIO 0`–`21`; `GPIO 47/48` I2C pins are digital-only).
  - Explicitly identify power domain dependencies (keeping `ESP_PD_DOMAIN_RTC_PERIPH` enabled during deep sleep so `GPIO 17` `BAT_CTRL` pad hold and RTC IO interrupt detectors remain powered).
  - Never de-assert `PA_EN` (`GPIO 42 = 1`) on the Waveshare v2 board; keep `PA_EN` held LOW (`0`) and place the ES8311 codec into software standby (`Reg 0x0D = 0xFC`) per Errata E4.
- **FreeRTOS & Dual-Core Concurrency Rules (`MANDATE-04` & `MANDATE-06`):**
  - Allocate all FreeRTOS synchronization primitives statically (`xSemaphoreCreateMutexStatic`, `xSemaphoreCreateRecursiveMutexStatic`, `xSemaphoreCreateBinaryStatic`, `xQueueCreateStatic`, `xEventGroupCreateStatic`).
  - Never call blocking APIs or non-ISR FreeRTOS primitives from interrupt service routines.
  - Never spin in `vTaskDelay()` polling loops for hardware `BUSY` pins, button states, or worker exits; use `esp_timer`, GPIO edge interrupts (`GPIO_INTR_NEGEDGE` / `GPIO_INTR_ANYEDGE`), static binary semaphores, and static `EventGroup` barriers.
  - Core 1 owns the LVGL v9 context (`h1os_lvgl`, priority `5`). From Core 0 `on_sync()` or background tasks, enqueue UI updates via `h1os_ui_post(fn, arg, timeout_ms)` or acquire `h1os_lvgl_lock(timeout_ms)` with an explicit timeout argument.
  - In `RTC_IRAM_ATTR` wake stub functions (`orch_wake_stub.c`), never call Flash-resident library routines (`memset`, `memcpy`, `esp_timer`, FreeRTOS); guard fixed-trip-count loops with `__attribute__((noinline))`, `asm volatile("" : "+r"(i))`, and `rtc_reg_barrier()` (`memw`).

## 4. Build Error "Two-Strike" Policy
If the build tool or compiler reports an error following an edit:
1. Isolate the exact compiler diagnostic from the terminal or `compile_commands.json`.
2. Propose exactly one targeted syntactic or signature fix.
3. If the compilation still fails, **STOP IMMEDIATELY**. Do not guess alternative signatures, suppress warnings, or cast types to force compilation. State the diagnostic verbatim and ask the user for confirmation.