# 🎯 Comprehensive Implementation Plan: ULP Battery Calibration LUT, Flow A Execution, Sleep Modes & Audio Unmute Delay

> [!NOTE]
> **Branch:** `E-Class-Dev-002`
> **Hardware Target:** Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
> **ADC Pin:** `GPIO 4` (`ADC1_CHANNEL_3`) with 1:2 resistor divider ($V_{\text{BAT}} = V_{\text{ADC}} \times 2$)

---

## ⚡ Overview of Newly Incorporated Capabilities

Based on your guidance and the technical specification, we can achieve high-accuracy factory eFuse-calibrated battery voltage sensing directly within the ULP-RISC-V coprocessor using a **17-point piecewise linear lookup table (LUT)** that takes only **34 bytes** of RTC Slow RAM!

```
+-------------------------------------------------------------------------------------------------+
|                                 17-POINT PIECEWISE LINEAR ADC ARCHITECTURE                       |
+-------------------------------------------------------------------------------------------------+
|                                                                                                 |
|   1. MAIN CPU BOOT:                                                                             |
|      - Reads eFuse curve-fitting calibration scheme via `adc_cali_raw_to_voltage()`.             |
|      - Populates `vbat_lut[17]` in RTC Slow Memory (34 bytes):                                  |
|        Indices 0..16 correspond to raw counts 0, 256, 512, ..., 4095.                          |
|        Stores scaled millivolts directly ($V_{\text{BAT}} = V_{\text{ADC}} \times 2$).         |
|      - Calls `ulp_riscv_adc_init()` for `ADC_UNIT_1`, `ADC_CHANNEL_3`, `ADC_ATTEN_DB_12`.         |
|                                                                                                 |
|   2. ULP-RISC-V COP-PROCESSOR EXECUTION (Every hardware wake):                                  |
|      - Reads `raw = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_3)`.                      |
|      - Interpolates $V_{\text{BAT}}$ via RV32M hardware multiply:                               |
|        `vbat_mv = y0 + (((y1 - y0) * rem) >> 8)`.                                               |
|      - Exports `ulp_last_vbat_mv` to RTC memory for Main CPU.                                   |
|      - Zero-Volt USB Guard: If `vbat_mv < 100 mV`, unit is running on USB without LiPo -> OK!   |
|      - Brownout Guard: If `vbat_mv >= 100 mV && vbat_mv < 3250 mV`:                            |
|        * Sets `last_wake_cause = 6` (`CRITICAL_BATTERY_FAULT`).                                 |
|        * Sets `dispatch_reason = 5` (`ULP_DISPATCH_CRITICAL_SHUTDOWN`).                         |
|        * Wakes Main CPU immediately to display critical battery graphic and cut power latch!    |
|                                                                                                 |
+-------------------------------------------------------------------------------------------------+
```

---

## 🛠️ Complete Multi-Subsystem Plan

### 1. Audio First-Click Unmuting Fix (`sub_audio.c`)
- **Root Cause:** When `sub_audio_prepare_and_unmute()` brings `HAL_PIN_PA_CTRL` from 0 to 1, the NS4168 Class-D amplifier H-bridge and external DC coupling capacitors require charging time to settle the analog bias. Tones sent immediately without delay are clipped or muted.
- **Implementation:**
  - Insert an explicit **100 ms settling delay** (`vTaskDelay(pdMS_TO_TICKS(100));`) in `sub_audio_prepare_and_unmute()` whenever `HAL_PIN_PA_CTRL` is brought active.

### 2. 17-Point Battery Calibration LUT Generation (`sub_power.c` & `ulp/main.c`)
- **In `components/h1os/ulp/main.c`:**
  - Define exported RTC Slow Memory symbols:
    ```c
    volatile uint16_t vbat_lut[17]     = {0};
    volatile uint32_t last_vbat_mv    = 4000;
    volatile uint32_t vbat_raw_adc    = 0;
    ```
  - Implement piecewise linear interpolation function:
    ```c
    static inline uint32_t ulp_raw_to_mv(int32_t raw)
    {
        if (raw <= 0) return vbat_lut[0];
        if (raw >= 4095) return vbat_lut[16];

        uint32_t idx = (uint32_t)raw >> 8;       /* 0..15 */
        uint32_t rem = (uint32_t)raw & 0xFF;     /* 0..255 */

        uint32_t y0 = vbat_lut[idx];
        uint32_t y1 = vbat_lut[idx + 1];

        return y0 + (((y1 - y0) * rem) >> 8);
    }
    ```
  - In `main()`:
    ```c
    int32_t raw_adc = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_3);
    vbat_raw_adc = (uint32_t)raw_adc;
    uint32_t vbat_mv = ulp_raw_to_mv(raw_adc);
    last_vbat_mv = vbat_mv;

    /* Brownout Guard (< 3.25V, with Zero-Volt USB bypass) */
    if (vbat_mv >= 100 && vbat_mv < 3250) {
        last_wake_cause = 6; /* CRITICAL_BATTERY_FAULT */
        dispatch_reason = 5; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
        wake_main = true;
    }
    ```
- **In `components/h1os/src/sub_power.c`:**
  - On cold boot in `sub_power_init_ulp()`:
    - Call `generate_vbat_lut()` using `s_cali_handle` to populate `ulp_vbat_lut[0..16]`.
    - Initialize ULP ADC attenuation:
      ```c
      ulp_riscv_adc_cfg_t adc_cfg = {
          .adc_n   = ADC_UNIT_1,
          .channel = ADC_CHANNEL_3,
          .width   = ADC_BITWIDTH_DEFAULT,
          .atten   = ADC_ATTEN_DB_12,
      };
      ulp_riscv_adc_init(&adc_cfg);
      ```

### 3. ULP Coprocessor: Wake Main CPU for Flow A Sensor Slices (`components/h1os/ulp/main.c`)
- On RTC INT pulse (`GPIO 5`):
  - Increment `slice_counter++`.
  - If `slice_counter < overflow_limit`:
    - `last_wake_cause = 4; /* SENSOR TICK */`
    - `dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */`
    - `wake_main = true; /* Wake Main CPU for Flow A sprint sample */`
  - If `slice_counter >= overflow_limit`:
    - `slice_counter = 0;`
    - `last_wake_cause = 3; /* LONG OVERFLOW WAKE */`
    - `dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */`
    - `wake_main = true; /* Wake Main CPU for Flow B interactive session */`

### 4. Sleep Entry Mode Flag (A/B/C) (`sub_power.h` & `sub_power.c`)
- In `sub_power.h`:
  ```c
  typedef enum {
      SUB_POWER_SLEEP_FULL_CYCLE = 0,  /* Flow B Sleep: Arms PCF85063A countdown & resets slice_counter */
      SUB_POWER_SLEEP_FLOW_A_BURST     /* Flow A Sleep: Preserves running PCF85063A countdown & slice_counter */
  } sub_power_sleep_mode_t;

  esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);
  ```
- In `sub_power.c`:
  - If `mode == SUB_POWER_SLEEP_FULL_CYCLE`:
    - `sub_rtc_arm_countdown(flow_a_sec);`
    - `ulp_slice_counter = 0;`
  - If `mode == SUB_POWER_SLEEP_FLOW_A_BURST`:
    - Skip countdown re-arming.
    - Skip `ulp_slice_counter` reset.

### 5. Verified Execution Time Logging for Flow A (`h1os_lifecycle.c`)
- In `h1os_lifecycle.c` line 255:
  ```c
  if (flow == ORCH_FLOW_A_SAMPLE) {
      int64_t t_start_us = esp_timer_get_time();
      ESP_LOGI(TAG, "Executing Flow A Sensor Sample Burst...");
      orch_flow_execute_sensor_sample();
      int64_t t_duration_us = esp_timer_get_time() - t_start_us;
      ESP_LOGI(TAG, "[FLOW A METRICS] Execution duration: %lld us (%.2f ms) | Ring Head: %u/32",
               t_duration_us, (double)t_duration_us / 1000.0, orch_state_get()->ring_head);
      return sub_power_enter_deep_sleep_mode(0, 0, SUB_POWER_SLEEP_FLOW_A_BURST);
  }
  ```

### 6. Ring Buffer Telemetry Verbose Dump Verification (`orch_flow.c`)
- Keep the `st->total_samples == 0` guard for cold boot.
- Now that Flow A populates samples on ticks 1, 2, 3, 4, when Flow B wakes at tick 5 (`LONG_OVERFLOW`), `total_samples` is already $\ge 4$, so `orch_flow_dump_ring_debug(st)` will execute and display the complete 32-sample ring table!

---

## 📋 File Modification Plan

1. **`components/h1os/ulp/main.c`**:
   - Add `#include "ulp_riscv_adc_ulp_core.h"`.
   - Add exported variables: `vbat_lut[17]`, `last_vbat_mv`, `vbat_raw_adc`.
   - Add `ulp_raw_to_mv()` interpolation function.
   - Read battery ADC, evaluate 3.25V brownout, wake Main CPU on sensor ticks (`wake_main = true` with `dispatch_reason = 1`).
2. **`components/h1os/include/h1os/sub_power.h`**:
   - Add `sub_power_sleep_mode_t` enum.
   - Declare `sub_power_enter_deep_sleep_mode()`.
3. **`components/h1os/src/sub_power.c`**:
   - Implement `generate_vbat_lut()`.
   - Call `ulp_riscv_adc_init()` on cold boot in `sub_power_init_ulp()`.
   - Implement mode switching in `sub_power_enter_deep_sleep_mode()`.
4. **`components/h1os/src/h1os_lifecycle.c`**:
   - Add execution duration profiling for Flow A.
   - Call `sub_power_enter_deep_sleep_mode(..., SUB_POWER_SLEEP_FLOW_A_BURST)` on Flow A completion.
5. **`components/h1os/src/sub_audio.c`**:
   - Add 100 ms settling delay in `sub_audio_prepare_and_unmute()`.
6. **`components/h1os/src/orch_flow.c`**:
   - Ensure verbose ring dump logs each entry cleanly when Flow B wakes.
