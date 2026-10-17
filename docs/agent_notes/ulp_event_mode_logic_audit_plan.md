# Implementation Plan: Calibrated Time-Bounded Polling & Stuck-Line Fault Recovery (v4)

Following technical review, this plan refines the ULP coprocessor's pulse handling during non-wake sensor ticks to replace uncalibrated cycle iterations with deterministic, time-calibrated polling using `ulp_riscv_delay_us()`, alongside stuck-pin fault detection and telemetry export.

---

## 1. Problem Analysis & Invariants

### 1.1 Uncalibrated Iteration Spin Issue
- The previous implementation used an uncalibrated counter `uint32_t wait_timeout = 500000; while (...)`.
- Loop iteration speed varies based on compiler optimization, branch prediction, and ULP core frequency (internal 17.5 MHz RTC_FAST_CLK or 8.5 MHz divider), providing no guaranteed time duration.
- Spinning back-to-back thrashes `RTC_GPIO_IN_REG` without physical settling time.
- If the `/INT` line is stuck LOW (hardware solder bridge, broken pull-up resistor, or unserviced PCF85063A register latch), the loop timed out silently without notifying the Main CPU.

### 1.2 Calibrated Time-Bounded Polling Solution
- **Calibrated Delay:** Using `ulp_riscv_delay_us(100)` relies on the hardware cycle counter and `ULP_RISCV_CYCLES_PER_US_*` conversion macros for genuine microsecond accuracy.
- **Poll Interval:** Polling every $100\ \mu\text{s}$ provides $\approx 156$ sample opportunities during the PCF85063A's $15.6\text{ ms}$ pulse ($64\text{ Hz}$ mode), completely eliminating bus thrashing.
- **Timeout Window:** A $50\text{ ms}$ timeout ($50000\ \mu\text{s}$) spans $>3\times$ the maximum expected pulse width.
- **Fault Detection & Export:** Export `volatile uint32_t rtc_int_stuck` to RTC Slow RAM.
- **Safe State Recovery:** If the pin remains LOW after $50\text{ ms}$, **do NOT re-arm `GPIO_WAKEUP_ENA`** (which would otherwise enter an immediate, catastrophic 15 µs wake storm draining battery power). Instead, assert `last_wake_cause = 5` (`RTC_INT_STUCK_FAULT`) and wake the Main CPU so it can log the error and clear the PCF85063A over I2C!

---

## 2. Proposed Changes

### Component 1: `components/h1os/ulp/main.c`
1. Export shared telemetry symbol:
   ```c
   volatile uint32_t rtc_int_stuck = 0;
   ```
2. Define timing constants:
   ```c
   #define RTC_INT_PIN        GPIO_NUM_5
   #define RTC_INT_TIMEOUT_US 50000   /* >3x the ~15.6ms PCF85063A pulse */
   #define RTC_INT_POLL_US    100
   ```
3. Implement the calibrated poll loop in the non-wake sensor tick branch:
   ```c
   } else {
       /* Sensor Poll Tick: wait for external PCF85063A pulse to return HIGH */
       uint32_t waited_us = 0;
       while (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0 &&
              waited_us < RTC_INT_TIMEOUT_US) {
           ulp_riscv_delay_us(RTC_INT_POLL_US);
           waited_us += RTC_INT_POLL_US;
       }
       rtc_int_stuck = (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0);

       /* Clear peripheral interrupt flag & controller latch */
       REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
       ulp_riscv_gpio_wakeup_clear();

       if (rtc_int_stuck) {
           /* Pin is stuck LOW: DO NOT re-arm GPIO_WAKEUP_ENA to prevent wake storm.
            * Wake Main CPU to log hardware fault and service PCF85063A over I2C. */
           while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP));
           last_wake_cause = 5; /* RTC_INT_STUCK_FAULT */
           dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
           ulp_riscv_wakeup_main_processor();
       } else {
           /* Line is clean HIGH: Re-arm GPIO wakeup for subsequent events */
           SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
       }
   }
   ```

### Component 2: `components/h1os/src/sub_power.c`
1. Initialize `ulp_rtc_int_stuck = 0;` alongside other exported symbols in `sub_power_enter_deep_sleep()`.

### Component 3: `components/h1os/src/h1os_lifecycle.c`
1. Update `debug_dump_ulp_telemetry()` to parse cause `5` as `"RTC_INT_STUCK_FAULT"` and log a prominent error if `ulp_rtc_int_stuck != 0`.

### Component 4: Architecture Document (`docs/architecture/ulp_event_mode_logic_audit.md`)
1. Update Section 5.2 to document the calibrated polling mechanism, timing calculations, and stuck-pin protection behavior.

---

## 3. Verification & Execution Steps

1. Apply modifications to `components/h1os/ulp/main.c`, `sub_power.c`, and `h1os_lifecycle.c`.
2. Compile development build:
   ```powershell
   & "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev build
   ```
3. Compile production build:
   ```powershell
   & "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod build
   ```
4. Verify symbol generation (`ulp_h1os.sym` includes `rtc_int_stuck`), clean compilation, and zero link errors.
