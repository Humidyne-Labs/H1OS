# Action Plan: ESP32-S3 ULP-RISC-V Wakeup Signal Chain Audit & Hardening

**Target Silicon:** ESP32-S3-PICO-1-N8R8  
**Target Board:** Waveshare ESP32-S3 ePaper 1.54" V2  
**Branch:** `E-Class-Dev-002`  
**Governing Authority:** Architecture Documents (`05_ulp.md`, `07_state_machine.md`, `01_master.md`)  
**Date:** 2026-10-16  

---

## 1. Architectural & Register Chain Alignment

Based on the register-level audit and attachment specifications, the hardware signal path is:

$$\text{Physical Pad} \xrightarrow[\text{LP IO Clock}]{\text{MUX\_SEL}} \text{RTC Pad} \xrightarrow{\text{FUN\_IE}} \text{PINx Comparator} \xrightarrow{\text{LOW\_LEVEL}} \text{STATUS\_INT Latch} \xrightarrow{\text{GPIO\_WAKEUP\_ENA}} \text{ULP Core Power-Up}$$

### Key Findings & Confirmations from Attachments:
1. **Comparator Must Be Armed by Main CPU ([2b, 5a]):**
   - `RTC_GPIO_PINx_INT_TYPE` resets to `0` (interrupt disabled). If never set, the status latch cannot fire.
   - The Main CPU explicitly configures both `WAKEUP_ENABLE = BIT(10)` and `INT_TYPE = 4` (`ULP_RISCV_GPIO_INTR_LOW_LEVEL`) in `RTC_GPIO_PIN0_REG + 4*n` for GPIO 0, 18, and 5 before sleep.
2. **Signal Latch Bit Mapping ([2c, 4c]):**
   - `RTC_GPIO_STATUS_INT` occupies bits `[31:10]` of `RTC_GPIO_STATUS_REG`.
   - `REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT)` shifts right by 10 (`RTC_GPIO_STATUS_INT_S = 10`), so bit $i$ of the returned value corresponds exactly to `RTCIO i`.
   - On ESP32-S3, `RTCIO 0 = GPIO 0`, `RTCIO 5 = GPIO 5`, and `RTCIO 18 = GPIO 18`. Testing `BIT(0)`, `BIT(5)`, and `BIT(18)` is 100% correct.
3. **Pad Isolation Verification ([5c]):**
   - Calling `rtc_gpio_isolate()` cuts the input path and disables pull-ups, blinding the comparator.
   - **Verification:** Verified that neither `hal_io_isolate_sleep_pads()` nor any other function calls `rtc_gpio_isolate()` on GPIO 0, 5, or 18. Wake pins strictly retain input buffers (`FUN_IE = 1`) and RTC domain multiplexing (`MUX_SEL = 1`).
4. **State Preservation ([5d]):**
   - Pad configuration survives deep sleep via `rtc_gpio_hold_en()`, `gpio_deep_sleep_hold_en()`, and `esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON)`.
5. **Halt Variant & Sleep Timer Preservation ([5e]):**
   - The ULP binary links `ulp_core/ulp_riscv_utils.c`, which does **not** stop the sleep timer upon halt (`RTC_CNTL_ULP_CP_SLP_TIMER_EN` remains asserted), ensuring continuous 60s periodic wakes.
6. **No De-init on Wake ([5b]):**
   - `ulp_release_gpios_and_wakeup_main()` does not call `ulp_riscv_gpio_deinit()`, preventing `MUX_SEL` from being cleared across sleep intervals.

---

## 2. Hardening Actions

### Hardening 1: Immediate Status Latch Snapshot at ULP Entry ([4a])
- **Problem:** In `components/h1os/ulp/main.c`, `main()` currently initialized pins and re-armed wakeup comparators *before* reading `RTC_GPIO_STATUS_REG`. Re-writing `RTC_GPIO_PIN0_REG` before reading `RTC_GPIO_STATUS_REG` risks resetting or perturbing the hardware latch.
- **Action:** Move `REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT)` to the **very first statement** in ULP `main()`.

### Hardening 2: Remove Redundant Entry Re-arming in ULP
- **Problem:** ULP entry called `ulp_arm_gpio_wakeup_pin()` for all three pins, which is redundant because the Main CPU already armed the comparators before sleep. Re-arming is only required when the ULP filters a glitch and halts without waking the Main CPU.
- **Action:** Remove redundant `ulp_arm_gpio_wakeup_pin()` calls at entry; keep them strictly in the glitch-filter halt path (`hold_ms < 20`).

### Hardening 3: Pre-Sleep Diagnostic Hardware Register Log
- **Problem:** Lack of visibility into actual hardware register bits before `esp_deep_sleep_start()`.
- **Action:** In `sub_power_enter_deep_sleep()`, log `PIN0_REG`, `PIN18_REG`, `PIN5_REG`, `RTC_CNTL_ULP_CP_TIMER_REG`, and `RTC_GPIO_STATUS_REG`. This guarantees immediate visual verification on COM3 that all comparator, clock gate, and latch bits are active prior to sleep.

---

## 3. Detailed Proposed Code Changes

### Phase 1: ULP Entry Snapshot (`components/h1os/ulp/main.c`)
- **File:** [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c)

```diff
 int main(void)
 {
+    /* 1. IMMEDIATELY snapshot RTC GPIO interrupt status upon core wake */
+    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
+    gpio_status_raw = rtcio_int_st;
+
     entry_ccount = ULP_RISCV_GET_CCOUNT();
     wake_counter++;
     loop_sample_count = 0;
     hold_duration_ms = 0;
     trace_count = 0;
 
     /* Initialize and enable input buffers for RTC GPIOs in the ULP domain */
     ulp_riscv_gpio_init(GPIO_NUM_5);
     ulp_riscv_gpio_input_enable(GPIO_NUM_5);
     ulp_riscv_gpio_pullup(GPIO_NUM_5); /* PCF85063A INT is open-drain; internal pull-up required */
     ulp_riscv_gpio_pulldown_disable(GPIO_NUM_5);
-    ulp_arm_gpio_wakeup_pin(GPIO_NUM_5);
 
     ulp_riscv_gpio_init(GPIO_NUM_0);
     ulp_riscv_gpio_input_enable(GPIO_NUM_0);
     ulp_riscv_gpio_pullup_disable(GPIO_NUM_0);   /* Discrete 10k pull-up on PCB */
     ulp_riscv_gpio_pulldown_disable(GPIO_NUM_0);
-    ulp_arm_gpio_wakeup_pin(GPIO_NUM_0);
 
     ulp_riscv_gpio_init(GPIO_NUM_18);
     ulp_riscv_gpio_input_enable(GPIO_NUM_18); /* BAT_KEY has external 10k pull-up on hardware */
     ulp_riscv_gpio_pullup_disable(GPIO_NUM_18);
     ulp_riscv_gpio_pulldown_disable(GPIO_NUM_18);
-    ulp_arm_gpio_wakeup_pin(GPIO_NUM_18);
 
-    /* Read RTC GPIO interrupt status and live pin levels immediately */
-    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
-    gpio_status_raw = rtcio_int_st;
     int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
     int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
     int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);
```

### Phase 2: Main CPU Pre-Sleep Register Audit Log (`components/h1os/src/sub_power.c`)
- **File:** [`components/h1os/src/sub_power.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_power.c)

```diff
     /* Clear any lingering GPIO wakeup latch and arm both ULP periodic sleep timer AND RTC GPIO wakeup */
     SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
     CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
     SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG,
                       RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
 #endif
 
     /* Keep RTC domain powered so ULP and RTC pad holds remain active */
     esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
 
+    ESP_LOGI(TAG, "RTC Wake Armed: PIN0=0x%08" PRIx32 ", PIN18=0x%08" PRIx32 ", PIN5=0x%08" PRIx32 ", TIMER_REG=0x%08" PRIx32 ", STATUS=0x%08" PRIx32,
+             REG_READ(RTC_GPIO_PIN0_REG),
+             REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_BUTTON_POWER),
+             REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_RTC_INT),
+             REG_READ(RTC_CNTL_ULP_CP_TIMER_REG),
+             REG_READ(RTC_GPIO_STATUS_REG));
+
     ESP_LOGI(TAG, "Entering deep sleep with ULP Coprocessor reactive monitor...");
     esp_deep_sleep_start();
```

---

## 4. Verification & Testing

1. **Compilation Validation:**
   - Compile both `build_dev` and `build_prod` targets cleanly (`idf.py build`).
2. **Serial Log Audit on COM3:**
   - Confirm `RTC Wake Armed` outputs:
     - `PIN0` has bit 10 (`WAKEUP_ENABLE`) and bits [9:7] = 4 (`LOW_LEVEL`).
     - `PIN18` has bit 10 and bits [9:7] = 4.
     - `PIN5` has bit 10 and bits [9:7] = 4.
     - `TIMER_REG` has bit 31 (`SLP_TIMER_EN`) and bit 29 (`GPIO_WAKEUP_ENA`) set.
3. **Execution Validation:**
   - When tapping BOOT (GPIO 0) or POWER (GPIO 18) during sleep:
     - ULP logs `rtcio_raw` with bit 0 (`0x000001`) or bit 18 (`0x040000`).
     - `cause = 1` (Hardware RTC GPIO latch) is registered.
     - System transitions to Flow B interactive mode immediately.
