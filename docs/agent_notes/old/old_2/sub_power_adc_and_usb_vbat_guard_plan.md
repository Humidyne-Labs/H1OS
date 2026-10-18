# Architecture Plan: ADC1 Oneshot Arbitration & USB VBUS Battery Guard

## 1. Problem Analysis from Hardware Log

### Issue 1: `sub_power: Failed to initialize ADC1 unit: ESP_ERR_NOT_FOUND`
- **Log trace:**
  ```text
  I (1870) sub_power: Loading ULP-RISC-V Coprocessor binary...
  I (1885) ulp_adc: No ulp mode specified in cfg struct, default to riscv
  ...
  E (5642) adc_oneshot: adc_oneshot_new_unit(99): adc1 is already in use
  E (5649) sub_power: Failed to initialize ADC1 unit: ESP_ERR_NOT_FOUND
  ```
- **Root Cause:**
  1. On cold boot, `sub_power_init_ulp()` called `ulp_riscv_adc_init(&adc_cfg)`. Internally, ESP-IDF's `ulp_adc_init()` calls `adc_oneshot_new_unit()` on `ADC_UNIT_1`, which claims the hardware unit lock (`s_adc_unit_claim(0) = true`).
  2. Later, when the main application queried battery voltage, `sub_power_get_battery_voltage()` invoked `sub_power_init()`.
  3. `sub_power_init()` attempted to call `adc_oneshot_new_unit()` with `.ulp_mode = ADC_ULP_MODE_DISABLE`. Because ADC1 had already been claimed by `ulp_adc_init()`, `adc_oneshot_new_unit()` rejected the second allocation with `ESP_ERR_NOT_FOUND` (`adc1 is already in use`).
  4. Furthermore, because `sub_power_init()` was called *after* `sub_power_init_ulp()`, the calibration handle `s_cali_handle` was NULL when `generate_vbat_lut()` executed, forcing the ULP battery LUT to fall back to uncalibrated ideal math (`0=0 mV, 2048=3100 mV, 4095=6200 mV`).

---

### Issue 2: `[CRITICAL LOW POWER SHUTDOWN]` When Running on USB Without Battery
- **Log trace:**
  ```text
  [ULP TELEMETRY] Wake #4: cause=6 (CRITICAL_BATTERY), slice=2/5, vbat=1972 mV (raw=1304), btn=0, stuck=0, cycles=698 (~41 us)
  [ULP FAULT] Battery critically low: 1972 mV (< 3250 mV threshold)!
  >>> H1OS ACTIVE FLOW: [CRITICAL LOW POWER SHUTDOWN] <<<
  Trigger Source  : Battery Brownout Guard (< 3.25V)
  ```
- **Root Cause & User Feedback:**
  1. On the user's test hardware, **no physical LiPo battery is installed**. The unit is running on USB power only.
  2. With no battery connected to the charge circuit, the `VBAT` sensing divider (GPIO 4) floats around ~1.97V (`1972 mV`).
  3. The ULP brownout check in `components/h1os/ulp/main.c`:
     ```c
     if (vbat_mv >= 100 && vbat_mv < 3250) {
         last_wake_cause = 6; /* CRITICAL_BATTERY_FAULT */
         dispatch_reason = 5; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
         wake_main       = true;
     }
     ```
     Because `1972 mV` is between `100 mV` and `3250 mV`, the ULP interpreted this floating voltage as an emergency depleted battery and repeatedly woke the CPU to execute emergency shutdown.
  4. **User Directive:**
     - Add a battery installed flag (`is_battery_installed`).
     - Before deep sleep, pass the USB connection state into the ULP (`ulp_usb_connected`).
     - If USB is connected: report battery at 100% (`vbat = 100%`), and prevent the ULP from waking the CPU for power/brownout faults.

---

## 2. Proposed Implementation

### 2.1 Fix ADC1 Coexistence & Calibration (`components/h1os/src/sub_power.c`)
1. **Initialize `sub_power_init()` with `ADC_ULP_MODE_RISCV`:**
   Configure `adc_oneshot_unit_init_cfg_t` with `.ulp_mode = ADC_ULP_MODE_RISCV`.
2. **Order of Initialization in `sub_power_init_ulp()`:**
   - Call `sub_power_init()` **first** on cold boot.
   - This creates `s_adc_handle` and calibrates eFuse curve fitting (`s_cali_handle`).
   - Call `generate_vbat_lut()`, which now uses real eFuse calibrated points instead of linear fallback.
   - Remove redundant `ulp_riscv_adc_init(&adc_cfg)` call, as `sub_power_init()` has already configured ADC1 unit and channel 3 for shared RISC-V ULP operation.
   - `s_adc_handle` remains valid on the main CPU for all subsequent runtime readings without error.

---

### 2.2 Export USB Connection State to ULP (`components/h1os/ulp/main.c` & `sub_power.c`)
1. **Add `volatile uint32_t usb_connected = 0;` in `components/h1os/ulp/main.c`:**
   Automatically exported to the main CPU as `ulp_usb_connected`.
2. **In `sub_power_enter_deep_sleep_mode()` before sleep:**
   ```c
   bool usb_state = sub_power_connected_usb();
   ulp_usb_connected = usb_state ? 1 : 0;
   ```
3. **In `components/h1os/ulp/main.c` (Brownout Check):**
   ```c
   if (usb_connected) {
       last_vbat_mv = 4200; /* Nominal full voltage on USB VBUS */
       /* Bypass brownout wake completely when powered from USB */
   } else if (vbat_mv >= 100 && vbat_mv < 3250) {
       last_wake_cause = 6; /* CRITICAL_BATTERY_FAULT */
       last_wake_btn   = 0;
       dispatch_reason = 5; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
       wake_main       = true;
   }
   ```

---

### 2.3 Battery Installed Flag & 100% USB Reporting (`h1os.h`, `h1os_lifecycle.c`, `screen_system_health.c`)
1. **Add `is_battery_installed` to [`h1os_telemetry_t`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/include/h1os/h1os.h#L137-L141):**
   ```c
   bool is_battery_installed; ///< True if physical LiPo cell detected (VBAT >= 2.80V)
   ```
2. **In `h1os_get_telemetry()` ([`components/h1os/src/h1os_lifecycle.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_lifecycle.c#L407-L418)):**
   - Detect USB connection via `sub_power_connected_usb()`.
   - Classify `is_battery_installed = (vbat_mv >= 2800);`.
   - If `is_usb_powered`: force `battery_percent = 100`.
3. **In UI ([`examples/H1OS/main/screens/screen_system_health.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/examples/H1OS/main/screens/screen_system_health.c#L18-L38)):**
   - If `telem->is_usb_powered`:
     - If `!telem->is_battery_installed`:
       - Row 1: `Power:       USB (NO BATTERY)`
       - Row 2: `Autonomy:    CONTINUOUS`
     - Else:
       - Row 1: `Power:       USB (100%)`
       - Row 2: `Autonomy:    CHARGING`

---

## 3. Verification & Execution Steps
1. Apply edits to `sub_power.c`, `ulp/main.c`, `h1os.h`, `h1os_lifecycle.c`, and `screen_system_health.c`.
2. Run development build: `& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev build`
3. Run production build: `& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod build`
4. Confirm 0 errors, 0 warnings.
5. Commit and push to `origin/E-Class-Dev-002`.
