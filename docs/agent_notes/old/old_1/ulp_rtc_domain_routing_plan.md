# Action Plan: RTC Domain Pad Routing & Retaining MUX_SEL Across ULP Sleep Cycles

**Target Silicon:** ESP32-S3-PICO-1-N8R8  
**Target Board:** Waveshare ESP32-S3 ePaper 1.54" V2  
**Branch:** `E-Class-Dev-002`  
**Governing Authority:** Architecture Documents (`05_ulp.md`, `07_state_machine.md`, `01_master.md`)  
**Date:** 2026-10-16  

---

## 1. Executive Summary & Root Cause

An in-depth hardware register and architectural audit of the ESP32-S3 RTC GPIO wakeup subsystem revealed two critical findings:

1. **`ulp_release_gpios_and_wakeup_main()` Inadvertently De-routed RTC Pads:**
   - In `components/h1os/ulp/main.c`, `ulp_release_gpios_and_wakeup_main()` called `ulp_riscv_gpio_deinit()` for GPIO 0, 18, and 5.
   - `ulp_riscv_gpio_deinit()` executes `CLEAR_PERI_REG_MASK(..., RTC_IO_TOUCH_PAD0_MUX_SEL)`.
   - On the very first ULP cycle (e.g. 60-second periodic timer wake), this cleared `MUX_SEL`, disconnecting the physical pads from the RTC domain and routing them back to the unpowered HP digital IO multiplexer.
   - Consequently, for all subsequent deep sleep intervals, `RTC_GPIO_PINx_WAKEUP_ENABLE` was monitoring disconnected pins, guaranteeing `rtcio_raw = 0x000000` and `cause = 3` (timer wake only).
   - **Resolution:** Remove `ulp_riscv_gpio_deinit()` calls from `ulp_release_gpios_and_wakeup_main()`. The pads must remain connected to the RTC domain (`MUX_SEL = 1`). On main CPU wake, the ESP32-S3 hardware resets and re-initializes digital peripherals cleanly.

2. **Main CPU Explicit RTC Domain Routing & Pad Hold Synchronization:**
   - While sleeping, the ULP is halted until an armed comparator or timer triggers. The wake comparator path is:
     $$\text{Pad} \longrightarrow \text{MUX\_SEL (RTC Mux)} \longrightarrow \text{FUN\_IE (Input Enable)} \longrightarrow \text{INT\_TYPE / WAKEUP\_ENABLE} \longrightarrow \text{RTC\_GPIO\_STATUS} \longrightarrow \text{RTC\_CNTL\_ULP\_CP\_GPIO\_WAKEUP\_ENA} \longrightarrow \text{ULP Core}$$
   - Before `esp_deep_sleep_start()`, the main CPU must explicitly ensure all stages of this comparator pipeline are initialized and locked into the RTC domain via `rtc_gpio_init()`, `rtc_gpio_set_direction()`, `rtc_gpio_hold_en()`, and `RTC_GPIO_PIN0_REG` comparator programming.
   - Verified: `hal_io_isolate_sleep_pads()` does not call `rtc_gpio_isolate()` on GPIO 0, 5, or 18 (which would disconnect the input comparator).

---

## 2. Invariants & Architecture Compliance

1. **Architecture Is Law:**
   - Adheres strictly to `docs/architecture/05_ulp.md`, `07_state_machine.md`, and `01_master.md`.
2. **Zero IO Polling:**
   - No background tasks or main loops poll IO pins in Flow A or Flow B.
   - Flow B UI button events are handled exclusively through LVGL keypad callbacks (`lvgl_keypad_read_cb`).
3. **Hardware Pull-Ups:**
   - Discrete 10 kΩ pull-up resistors are physically present on GPIO 0 (BOOT) and GPIO 18 (POWER). Internal pull-ups must remain disabled (`rtc_gpio_pullup_dis`) across all execution domains to prevent quiescent current leakage.
   - GPIO 5 (RTC INT / PCF85063A open-drain interrupt) retains internal pull-up (`rtc_gpio_pullup_en`).

---

## 3. Detailed Proposed Code Changes

### Phase 1: ULP Firmware (`components/h1os/ulp/main.c`)
- **File:** [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c)
- **Change:** In `ulp_release_gpios_and_wakeup_main()`, remove the three `ulp_riscv_gpio_deinit()` calls so that `MUX_SEL` remains permanently routed to the RTC domain across deep sleep cycles.

```diff
 static inline void ulp_release_gpios_and_wakeup_main(void)
 {
-    /* Release RTC IO ownership back to HP digital GPIO matrix before waking main CPU */
-    ulp_riscv_gpio_deinit(GPIO_NUM_0);
-    ulp_riscv_gpio_deinit(GPIO_NUM_18);
-    ulp_riscv_gpio_deinit(GPIO_NUM_5);
+    /* Note: We intentionally do NOT deinitialize RTC GPIOs here.
+     * Clearing MUX_SEL would disconnect the pads from the RTC domain and disable
+     * the hardware level comparator during subsequent sleep intervals. */
     exit_ccount = ULP_RISCV_GET_CCOUNT();
     ulp_riscv_wakeup_main_processor();
     ulp_riscv_halt();
 }
```

### Phase 2: Main CPU Sleep Entry Pipeline (`components/h1os/src/sub_power.c`)
- **File:** [`components/h1os/src/sub_power.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_power.c)
- **Change:** Ensure full, explicit pad routing and comparator arming inside `sub_power_enter_deep_sleep()`:
  - Call `rtc_gpio_init(pin)` to set `RTC_IO_TOUCH_PADx_MUX_SEL = 1` and enable the LP IO clock.
  - Call `rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY)` to set `FUN_IE = 1`.
  - Disable pull-ups on GPIO 0 and 18; enable pull-up on GPIO 5.
  - Enable pad hold `rtc_gpio_hold_en(pin)` so configuration survives power transitions.
  - Program `RTC_GPIO_PIN0_WAKEUP_ENABLE` and `RTC_GPIO_PIN0_INT_TYPE = 4` (`ULP_RISCV_GPIO_INTR_LOW_LEVEL`).
  - Strobe `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` and arm `SLP_TIMER_EN | GPIO_WAKEUP_ENA`.

```diff
     /* Arm per-pin RTC GPIO wakeup comparator & low-level trigger on Main CPU before sleep */
     const gpio_num_t wake_pins[] = {HAL_PIN_BUTTON_BOOT, HAL_PIN_BUTTON_POWER, HAL_PIN_RTC_INT};
     for (size_t i = 0; i < sizeof(wake_pins) / sizeof(wake_pins[0]); i++) {
         gpio_num_t pin = wake_pins[i];
+        rtc_gpio_init(pin);                                    /* sets MUX_SEL, routes to RTC domain */
+        rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY); /* enables FUN_IE */
+        if (pin == HAL_PIN_RTC_INT) {
+            rtc_gpio_pullup_en(pin);                           /* open-drain PCF85063A INT */
+            rtc_gpio_pulldown_dis(pin);
+        } else {
+            rtc_gpio_pullup_dis(pin);                          /* external 10k pull-ups on buttons */
+            rtc_gpio_pulldown_dis(pin);
+        }
+        rtc_gpio_hold_en(pin);                                 /* preserve configuration across sleep */
         SET_PERI_REG_MASK(RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_WAKEUP_ENABLE);
         REG_SET_FIELD    (RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_INT_TYPE, 4 /* ULP_RISCV_GPIO_INTR_LOW_LEVEL */);
     }
```

---

## 4. Verification & Testing Strategy

1. **Compilation Validation:**
   - Execute `idf.py -B build_dev build` and verify clean compilation (exit code 0).
   - Execute `idf.py -B build_prod build` and verify clean compilation (exit code 0).
2. **Hardware Execution (COM3):**
   - Boot firmware and let H1OS enter Flow A deep sleep.
   - Verify periodic soft-timer telemetry wake runs without disconnecting pins.
   - Press POWER button (GPIO 18) or BOOT button (GPIO 0) during deep sleep:
     - Observe immediate ULP wake log.
     - Confirm `rtcio_raw` contains `0x040000` (GPIO 18) or `0x000001` (GPIO 0).
     - Confirm `cause = 1` (RTCIO status latch) or `cause = 2` (live level LOW).
     - Confirm system transitions into Flow B interactive session immediately.
