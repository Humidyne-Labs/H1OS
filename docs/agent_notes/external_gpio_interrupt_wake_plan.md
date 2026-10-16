# Restoration of External GPIO Interrupt & Timer Wakeup via ULP Coprocessor (ESP32-S3)

## 1. Executive Summary & Silicon Architecture

Based on user feedback, ESP32-S3 Technical Reference Manual (TRM Chapter 1 & 2), and the ESP-IDF v6.1 source tree, this revised plan establishes a **dual-wakeup ULP coprocessor architecture** where the ULP is triggered from deep sleep by **either the software periodic timer OR an RTC GPIO interrupt**:

```
                  ┌──────────────────────────────────────────────┐
                  │            ESP32-S3 Deep Sleep Mode           │
                  └──────────────────────────────────────────────┘
                                  │
                 ┌────────────────┴────────────────┐
                 ▼                                 ▼
   ┌───────────────────────────┐     ┌───────────────────────────┐
   │    Software Sleep Timer   │     │      RTC GPIO Matrix      │
   │ (RTC_CNTL_ULP_CP_SLP_TIMER│     │(RTC_CNTL_ULP_CP_GPIO_WAKE │
   │           _EN)            │     │          UP_ENA)          │
   └─────────────┬─────────────┘     └─────────────┬─────────────┘
                 │                                 │
                 │ 60s Flow A                      │ GPIO 0 (BOOT0)
                 │ Periodic Telemetry              │ GPIO 18 (POWER)
                 │                                 │ GPIO 5 (RTC INT)
                 └────────────────┬────────────────┘
                                  ▼
                   ┌─────────────────────────────┐
                   │    ULP-RISC-V Coprocessor   │
                   │  Executes in RTC Slow SRAM  │
                   └──────────────┬──────────────┘
                                  │
         ┌────────────────────────┼────────────────────────┐
         ▼                        ▼                        ▼
  [Short Tap <2.5s         [BOOT Held >2.5s]       [POWER Held >2.5s]
    or RTC INT]                   │                        │
         │                        ▼                        ▼
         │               dispatch_reason = 4      dispatch_reason = 5
         ▼             (ULP_DISPATCH_BOOTLOADER) (ULP_DISPATCH_POWER_OFF)
  dispatch_reason = 2             │                        │
  (ULP_DISPATCH_MAIN_WAKE)        │                        │
         │                        │                        │
         └────────────────────────┼────────────────────────┘
                                  ▼
                    ulp_riscv_wakeup_main_processor()
                                  │
                                  ▼
                  ┌───────────────────────────────┐
                  │      Xtensa Main CPU Core     │
                  │ Wakes with ESP_SLEEP_WAKEUP_ULP│
                  │    Dispatches on reason       │
                  └───────────────────────────────┘
```

### Key Silicon Architectural Principles
1. **All Target IOs Reside in the RTC IO Domain (GPIO 0–21):**
   - `HAL_PIN_BUTTON_BOOT` = **GPIO 0** (RTCIO 0) — Active LOW, internal pull-up required.
   - `HAL_PIN_BUTTON_POWER` = **GPIO 18** (RTCIO 18) — Active LOW, internal pull-up required (*Note: GPIO 17 is `HAL_PIN_POWER_HOLD` / BAT_CTRL power latch, held HIGH during sleep*).
   - `HAL_PIN_RTC_INT` = **GPIO 5** (RTCIO 5) — Open-drain PCF85063A Alarm INT, active LOW, internal pull-up required.
2. **Dual ULP Wakeup Triggers (`RTC_CNTL_ULP_CP_TIMER_REG`):**
   - The ESP32-S3 RTC controller supports setting both `RTC_CNTL_ULP_CP_SLP_TIMER_EN` (Bit 31) and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` (Bit 29) simultaneously.
   - When sleeping, the ULP coprocessor activates whenever:
     - The periodic timer expires (e.g. 60s for Flow A telemetry).
     - **OR** an RTC GPIO level transition pulls LOW (instantaneous button press or RTC alarm).
3. **The Low-Power IO Clock Prerequisite (`io_mux_enable_lp_io_clock`):**
   - On ESP32-S3, `SOC_LP_IO_CLOCK_IS_INDEPENDENT = 1`. Calling `rtc_gpio_wakeup_enable()` alone is insufficient because the LP IO clock is gated off by default.
   - `io_mux_enable_lp_io_clock(gpio_num, true)` must be enabled for each wake pin so the RTC sampling logic is continuously clocked during sleep.
4. **Zero CPU Interrupt Matrix Exposure:**
   - Digital GPIO level interrupts (`gpio_config` with `.intr_type = GPIO_INTR_LOW_LEVEL`) must **NEVER** be registered on the Xtensa CPU.
   - The Xtensa CPU enters deep sleep with **only** `esp_sleep_enable_ulp_wakeup()`.
   - The CPU never enables EXT1 or digital GPIO interrupts.
   - This eliminates all risk of CPU interrupt storms, IWDT panics, and spurious reboots.

---

## 2. Component Modifications

### A. Sleep Pad Isolation & LP IO Clock (`components/h1os/src/hal_io.c`)
In `hal_io_isolate_sleep_pads()`:
1. For each wake pin (`HAL_PIN_RTC_INT`, `HAL_PIN_BUTTON_BOOT`, `HAL_PIN_BUTTON_POWER`):
   ```c
   // Configure RTC IO domain pull-ups and input buffer
   rtc_gpio_init(pin);
   rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY);
   rtc_gpio_pullup_en(pin);
   rtc_gpio_pulldown_dis(pin);

   // Enable independent LP IO clock for sampling
   io_mux_enable_lp_io_clock(pin, true);

   // Arm RTC GPIO level detector for LOW level
   rtc_gpio_wakeup_enable(pin, GPIO_INTR_LOW_LEVEL);
   ```
2. In `hal_io_release_pad_holds()`:
   ```c
   // Disable RTC wakeup and release LP IO clock
   rtc_gpio_wakeup_disable(pin);
   io_mux_enable_lp_io_clock(pin, false);
   rtc_gpio_deinit(pin);
   ```

### B. ULP & Deep Sleep Setup (`components/h1os/src/sub_power.c`)
1. In `sub_power_init_ulp()`:
   - Configure ULP periodic timer for 60 seconds (`ulp_set_wakeup_period(0, 60000000)`).
   - Start ULP with `ulp_riscv_config_and_run(&cfg)` (`ULP_RISCV_WAKEUP_SOURCE_TIMER`).
   - Enable GPIO wakeups in the hardware register:
     ```c
     SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
     ```
2. In `sub_power_enter_deep_sleep()`:
   - Isolate sleep pads (`hal_io_isolate_sleep_pads()`).
   - Enable ULP wake for Xtensa: `esp_sleep_enable_ulp_wakeup()`.
   - Re-assert both bits in `RTC_CNTL_ULP_CP_TIMER_REG`:
     ```c
     SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, 
                       RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
     ```
   - Keep RTC domain powered: `esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON)`.
   - Enter deep sleep: `esp_deep_sleep_start()`.

### C. ULP Firmware Wake Arbitration (`components/h1os/ulp/main.c`)
Verify and ensure `components/h1os/ulp/main.c`:
1. On wake, clears the RTC GPIO wakeup latch: `ulp_riscv_gpio_wakeup_clear()`.
2. Inspects `HAL_PIN_RTC_INT` (GPIO 5):
   - If LOW, `dispatch_reason = 2` (`ULP_DISPATCH_MAIN_WAKE`) and wakes Xtensa.
3. Inspects buttons (`HAL_PIN_BUTTON_BOOT` GPIO 0, `HAL_PIN_BUTTON_POWER` GPIO 18):
   - If pressed, tracks hold duration:
     - Held $\ge 2500\text{ms}$ on BOOT: `dispatch_reason = 4` (`ULP_DISPATCH_BOOTLOADER_JUMP`).
     - Held $\ge 2500\text{ms}$ on POWER: `dispatch_reason = 5` (`ULP_DISPATCH_POWER_OFF`).
     - Released between $30\text{ms}$ and $2500\text{ms}$ (short tap): `dispatch_reason = 2` (`ULP_DISPATCH_MAIN_WAKE`).
     - Pulses $<30\text{ms}$ discarded as noise.
   - Clears GPIO wake latch: `ulp_riscv_gpio_wakeup_clear()`.
   - Wakes Xtensa: `ulp_riscv_wakeup_main_processor()`.
4. If neither button nor RTC INT triggered (soft-timer expiration):
   - Samples battery and sensors.
   - If update needed: `dispatch_reason = 1` (`ULP_DISPATCH_SENSOR_UPDATE`), wakes Xtensa.
   - If no update needed: halts (`return 0;`), allowing the SoC to remain asleep until the next timer tick or button press.

### D. Main Core Dispatch Handler (`components/h1os/src/h1os_lifecycle.c`)
When Xtensa wakes from `ESP_SLEEP_WAKEUP_ULP`:
1. Inspects `ulp_dispatch_reason`:
   - `ULP_DISPATCH_BOOTLOADER_JUMP` (4):
     - Logs: `[LIFECYCLE] BOOT0 long hold (>2.5s) detected by ULP. Jumping to ROM Bootloader...`
     - Sets `RTC_CNTL_FORCE_DOWNLOAD_BOOT` in `RTC_CNTL_OPTION1_REG`.
     - Calls `esp_restart()`.
   - `ULP_DISPATCH_POWER_OFF` (5):
     - Logs: `[LIFECYCLE] POWER long hold (>2.5s) detected by ULP. Shutting down...`
     - Calls `h1os_shutdown()` to release GPIO 17 battery latch.
   - `ULP_DISPATCH_MAIN_WAKE` (2):
     - Launches Flow B Interactive Main Session.
   - `ULP_DISPATCH_SENSOR_UPDATE` (1):
     - Launches Flow A Quick Sensor Refresh.

---

## 3. Architecture Comparison Table

| Feature | Legacy EXT1 Wake | Prior Crash Attempt | **Dual-Wake ULP Architecture (This Plan)** |
| :--- | :--- | :--- | :--- |
| **Wake Trigger to Xtensa** | Direct EXT1 to CPU | Unhandled CPU level ISR | **Pure ULP software interrupt (`ESP_SLEEP_WAKEUP_ULP`)** |
| **ULP Wake Trigger** | Soft-Timer only | Broken / unclocked | **Soft-Timer OR RTC GPIO (`io_mux_enable_lp_io_clock`)** |
| **Pins Monitored** | GPIO 0, 18, 5 | GPIO 0, 18, 5 | **GPIO 0 (BOOT), GPIO 18 (PWR), GPIO 5 (RTC INT)** |
| **LP IO Sampling Clock** | Unconfigured | Unconfigured | **Explicitly enabled via `io_mux_enable_lp_io_clock`** |
| **Hold Timing (>2.5s)** | CPU busy-wait after boot | N/A (panicked) | **Autonomous ULP coprocessor timing in deep sleep** |
| **Bootloader Jump** | CPU software branch | N/A | **ULP triggers `ULP_DISPATCH_BOOTLOADER_JUMP`** |
| **CPU Panic Risk** | None | High (IWDT timeout) | **Zero (no CPU interrupt matrix involvement)** |

---

## 4. Verification & Validation Steps

1. **Compilation & Linking:**
   - Build `examples/H1OS/build_prod` with PowerShell profile `C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1`.
   - Build `examples/H1OS/build_dev`.
   - Run `tools/inspect_size.py -B examples/H1OS/build_prod` to verify flash budget and image validity.
2. **Functional Validation on Target Hardware:**
   - **Soft-Timer Wake:** Verify device wakes every 60s for Flow A telemetry when untouched.
   - **Short Button Tap:** Tap BOOT or POWER button while device is in deep sleep; verify instantaneous wake to Flow B with `dispatch_reason = 2`.
   - **Long BOOT Hold (>2.5s):** Hold BOOT button while asleep for >2.5s; verify device jumps immediately to ROM Bootloader mode for firmware flashing.
   - **Long POWER Hold (>2.5s):** Hold POWER button while asleep for >2.5s; verify device cuts the GPIO 17 battery latch and powers off.
   - **RTC External Alarm (GPIO 5):** Verify alarm event from PCF85063A wakes device cleanly.
   - **Stability:** Verify 0 CPU watchdog panics, 0 interrupt storms, and clean serial console logs.
