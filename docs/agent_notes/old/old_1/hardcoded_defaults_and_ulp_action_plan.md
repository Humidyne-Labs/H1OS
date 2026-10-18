# Action Plan: Removal of Hardcoded Defaults, Telemetry NA Standards & Hardware Architecture Clarifications

This action plan addresses all review comments across `sub_power.c`, `h1os_lifecycle.c`, `orch_flow.c`, `orch_state.c`, `sub_audio.c`, `sub_display.cpp`, `sub_sdcard.c`, `sub_sensor.c`, and `ulp/main.c`.

---

## 1. Executive Summary of Review Findings

| File | Target Lines / Symbol | Issue / Comment | Resolution Strategy |
| :--- | :--- | :--- | :--- |
| [h1os_lifecycle.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/main/h1os_lifecycle.c) | `sleep_sec == 0` (47, 84, 142), `timeout_sec == 0` (246, 250) | Silent fallback to hardcoded constants (`300s`, `120s`, `30s`). Should abort with error. | Log `ESP_LOGE` detailing unconfigured lifecycle contract parameter and return `ESP_ERR_INVALID_ARG` / abort flow execution cleanly. |
| [orch_state.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/main/orch_state.c) | `window_low_temp_centi_c = 2500`, `window_high_temp_centi_c = 2500` | Seeded fake `25.0°C` on cold boot without sensor read. | Zero out to `0` (`0.0°C`), matching user requirement that `0.0` signifies uninitialized/NA telemetry. |
| [sub_sensor.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/main/sub_sensor.c) | `*out_die_temp_c = 25.0f;` (164-165) | Fallback to `25.0f` on TSENS failure. | Change fallback to `0.0f` on sensor read failure. |
| [sub_audio.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/main/sub_audio.c) | `s_volume_pct = 50;` (81-82) | Hardcoded volume default. | Bind to Kconfig `CONFIG_H1OS_AUDIO_DEFAULT_VOLUME_PCT` (or initialize to `0` / require explicit config from lifecycle presentation). |
| [orch_flow.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/main/orch_flow.c) | Ring buffer hex dumping inline logic (240-275, 301-302) | Inline debug clutter inside main flow orchestration. | Modularize into a dedicated static helper function: `orch_flow_dump_ring_debug()`. |
| [sub_display.cpp](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os_sub_display/sub_display.cpp) | `centi_c += 50;`, `+ 0.50f` (166, 346) | "why 50?", "why 0.50?" | Document SSD1681 Register `0x1B` Bit 7 ($2^{-1} = 0.5^\circ\text{C}$). Define explicit constant `SSD1681_TEMP_HALF_DEG_CENTI_C = 50`. |
| [sub_sdcard.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os_sub_sdcard/sub_sdcard.c) | `allocation_unit_size = 16 * 1024` (30-31) | "this a max supported value?" | Clarify that FatFS `allocation_unit_size` is formatting cluster size, not a hardware or transfer maximum. Allow `0` (auto-format). |
| [sub_power.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os_sub_power/sub_power.c) & [ulp/main.c](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os_sub_power/ulp/main.c) | `gpio_wakeup_enable()` | "is this for ulp or application wake?", "the ulp cant wake on external button/io input?" | Document and verify the RTC interrupt routing: `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` wakes the ULP coprocessor. The ULP processes edges and then wakes the Xtensa main processor. |

---

## 2. Work Breakdown Packages

### Work Package 1: Eradicate Hardcoded Fallbacks & Enforce Telemetry Standards
1. **`h1os_lifecycle.c`**:
   - Inspect all functions accepting `sleep_duration_sec` and `timeout_sec`.
   - Remove `if (sleep_sec == 0) sleep_sec = 300;`, `if (sleep_sec == 0) sleep_sec = 120;`, and `if (timeout_sec == 0) timeout_sec = 30;`.
   - Replace with:
     ```c
     if (sleep_sec == 0) {
         ESP_LOGE(TAG, "Lifecycle error: sleep_duration_sec is 0 (unconfigured). Aborting sleep transition.");
         return ESP_ERR_INVALID_ARG;
     }
     ```
   - Standardize all telemetry initialization to explicit `0.0f` / `0` centi-units to signify `NA` / uninitialized state.
2. **`orch_state.c`**:
   - Replace initial min/max window temp defaults:
     ```c
     // Previously: window_low_temp_centi_c = 2500, window_high_temp_centi_c = 2500
     state->window_low_temp_centi_c = 0;   // 0 centi-C indicates uninitialized/NA
     state->window_high_temp_centi_c = 0;  // 0 centi-C indicates uninitialized/NA
     ```
3. **`sub_sensor.c`**:
   - In `sub_sensor_read_mcu_die_temp()`:
     ```c
     if (ret != ESP_OK) {
         *out_die_temp_c = 0.0f; // Explicitly report 0.0C on read failure
         return ret;
     }
     ```
4. **`sub_audio.c`**:
   - Replace static `s_volume_pct = 50;` with Kconfig default (`CONFIG_H1OS_AUDIO_DEFAULT_VOLUME_PCT`) or zero-initialized until configured by presentation policy.

### Work Package 2: Modularity & Code Cleanliness
1. **`orch_flow.c`**:
   - Extract lines ~240-275 (telemetry struct formatting, serial terminal dump, ring buffer index inspection) out of `orch_flow_execute_a()` into:
     ```c
     static void orch_flow_dump_ring_debug(const orch_persisted_state_t *st);
     ```
   - Keep `orch_flow_execute_a()` concise, linear, and focused strictly on sequence execution (RTC check $\to$ sensor reads $\to$ state recording $\to$ display dispatch).

### Work Package 3: Hardware Registers & Subsystem Architecture Clarifications
1. **SSD1681 Temperature Sensor Fraction Bit (`sub_display.cpp`)**:
   - Hardware register `0x1B` (Read Internal Temperature Sensor) returns 2 bytes:
     - Byte 1: Signed 8-bit integer temperature in degrees Celsius ($1^\circ\text{C}$ per LSB).
     - Byte 2: Bit 7 represents the $0.5^\circ\text{C}$ fractional bit ($2^{-1}$). Bits 6:0 are reserved.
   - Introduce constant:
     ```cpp
     static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50; // 0.50 deg C = 50 centi-degrees
     ```
   - Add inline documentation explaining the register bitfield structure to eliminate ambiguity.
2. **SD Card Allocation Unit Size (`sub_sdcard.c`)**:
   - In `esp_vfs_fat_sdmmc_mount_config_t`, `allocation_unit_size` specifies the cluster size *if and only if FatFS formats the volume* (`format_if_mount_failed`).
   - It is not a hardware capacity or transfer limit. Pre-formatted cards (FAT32/exFAT) use their own native cluster size.
   - Set to `0` by default (allowing FatFS to automatically determine optimal cluster size based on card volume geometry), or document clearly.
3. **ULP vs. SoC GPIO Wakeup Mechanics (`sub_power.c` & `ulp/main.c`)**:
   - On ESP32-S3:
     - `gpio_wakeup_enable()` configures the RTC IO subsystem.
     - When `esp_sleep_enable_ulp_wakeup()` is set and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` is configured, an IO edge/level wakes the **ULP-RISC-V core**, while the Xtensa main cores remain powered down in deep sleep.
     - The ULP RISC-V program boots, executes `main()`, performs debounce or edge classification, updates shared RTC slow memory, and only calls `ulp_riscv_wakeup_main_processor()` if an authorized Flow B trigger condition is satisfied.
   - Add clear architecture comments to both `sub_power.c` and `ulp/main.c` so the separation of responsibilities between coprocessor wake and main CPU wake is crystal clear.

---

## 3. Verification Plan

1. **Compilation**:
   - Run `idf.py -B build_prod build` to verify clean compilation with zero warnings on all modified components.
2. **Lifecycle Validation Guard Tests**:
   - Verify that passing `sleep_duration_sec = 0` or `timeout_sec = 0` triggers explicit error logs and halts without silent hangs or fallback timeouts.
3. **Telemetry Cold Boot Verification**:
   - Verify that in a fresh state (before SHTC3 conversion), all telemetry fields report `0.0` / `0` centi-units rather than synthetic `25.0`.
