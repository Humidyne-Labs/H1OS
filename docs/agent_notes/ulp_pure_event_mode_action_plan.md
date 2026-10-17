# Revised Action Plan: Pure Event Mode Architecture & PCF85063A Periodic Pulsed Timebase

**Target Silicon:** ESP32-S3-PICO-1-N8R8  
**Target Board:** Waveshare ESP32-S3 ePaper 1.54" V2  
**Branch:** `E-Class-Dev-002`  
**Governing Authority:** Architecture Documents (`05_ulp.md`, `07_state_machine.md`, `01_master.md`)  
**Date:** 2026-10-17  

---

## 1. Architectural Alignment: Timer Mode vs Event Mode

An in-depth analysis of ESP-IDF's ULP subsystem (`components/ulp/ulp_riscv/ulp_riscv.c`) confirms the fundamental silicon distinction between the two wake sources:

| Property | Timer Mode (`ULP_RISCV_WAKEUP_SOURCE_TIMER`) | Event Mode (`ULP_RISCV_WAKEUP_SOURCE_GPIO`) |
|---|---|---|
| **Trigger Source** | Periodic: Internal PMU timer counts `RTC_CNTL_ULP_CP_TIMER_1_REG` ticks of `RTC_SLOW_CLK` | Asynchronous: RTC IO pin event starts the core once on demand |
| **Hardware Bit** | `RTC_CNTL_ULP_CP_SLP_TIMER_EN` | `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` |
| **Driver Configuration** | `ulp_riscv_config_wakeup_source()` sets `SLP_TIMER_EN` | `ulp_riscv_config_wakeup_source()` sets `GPIO_WAKEUP_ENA` |
| **Behavior on Halt** | Timer **restarts automatically** upon `RTC_CNTL_COCPU_DONE` | Core **stays powered down** until the next external pin event |
| **Latch Clearance** | Must clear `SLP_TIMER_EN` via `ulp_riscv_timer_stop()` | Call `ulp_riscv_gpio_wakeup_clear()` (`GPIO_WAKEUP_CLR`) |

### Hardware Erratum (ERR-001: PMU Dual-Wake Coprocessor Block)
- In ESP-IDF, `ulp_riscv_config_wakeup_source()` is an exclusive `switch` statement that sets only one bit per mode.
- In silicon, manually forcing both bits simultaneously (`SLP_TIMER_EN | GPIO_WAKEUP_ENA`) causes an internal PMU arbitration deadlock where the internal timer countdown overrides and suppresses external RTC GPIO edge wakeups.
- **The Solution:** Fully commit to **Event Mode** (`ULP_RISCV_WAKEUP_SOURCE_GPIO`). Stop the internal PMU timer entirely (`SLP_TIMER_EN = 0`). Offload periodic timekeeping to the quartz-accurate external PCF85063A RTC on `GPIO 5`.

---

## 2. PCF85063A Periodic Pulsed Configuration

The PCF85063A countdown timer is configured in **Repetitive Pulsed Mode** (`TI_TP = 1` in `Timer_mode` register `0x11`):

1. **Step 1: Stop timer before configuration:** Clear bit 2 (`TE = 0`) in `Timer_mode` (`0x11`).
2. **Step 2: Set countdown period:** Write $T = 10$ into `Timer_value` (`0x10`).
3. **Step 3: Enable periodic pulse:**
   - `TCF[1:0] = 10` ($1\text{ Hz}$ clock source)
   - `TE = 1` (Timer Enable)
   - `TIE = 1` (Timer Interrupt Enable to $\overline{\text{INT}}$)
   - `TI_TP = 1` (Pulsed Mode: timer runs repeatedly in a continuous auto-reloading loop)
   - Register `0x11` byte value = `0x17` (`(2 << 3) | (1 << 2) | (1 << 1) | (1 << 0)`).
4. **Hardware Pulse Characteristics:**
   - $\overline{\text{INT}}$ pin pulls LOW for a fixed, self-clearing pulse of $1/64\text{ s}$ ($\approx 15.6\text{ ms}$) and automatically releases back HIGH.
   - Zero I2C bus transactions are required from the ULP to clear or acknowledge the interrupt.

---

## 3. Deterministic Slice Counter Architecture

Let $N = 6$ slices of $10\text{ s}$ each ($60\text{ s}$ total Flow A period):

```
  PCF85063A (/INT Pulse) ──► GPIO 5  ┐
  BOOT Button (Active-Low) ──► GPIO 0  ┼──► RTC IO Level Comparator ──► ULP Boots (Event Mode)
  POWER Button (Active-Low)─► GPIO 18 ┘
                                              │
                      ┌───────────────────────┴───────────────────────┐
                      ▼                                               ▼
            GPIO 0 / 18 Asserted                            GPIO 5 Asserted
        (Immediate Button Interaction)                     (Periodic Time Slice)
                      │                                               │
                      ▼                                               ▼
          Wake Main CPU Immediately                              slice_counter++
             (Flow B Session)                                         │
                                             ┌────────────────────────┼────────────────────────┐
                                             ▼                        ▼                        ▼
                                      slice == N - 1             slice >= N               Intermediary
                                      (5th slice / 50s)       (6th slice / 60s)         (1st - 4th slice)
                                             │                        │                        │
                                             ▼                        ▼                        ▼
                                      Last Sensor Run          Main App Run               Clear Latch &
                                    (Sample ADC & SHTC3)    (Reset slice_counter,           Halt ULP
                                     Do not wake CPU yet      Wake Main CPU for          (CPU Sleeps)
                                                             ePaper screen refresh)
```

---

## 4. Detailed Implementation Steps

### Phase 1: Silicon Errata Documentation (`docs/architecture/errata.md`)
- Document ERR-001 (ESP32-S3 PMU Dual-Wake Coprocessor Block).
- Update `docs/architecture/05_ulp.md` cross-referencing Pure Event Mode operation.

### Phase 2: PCF85063A Pulsed Mode Driver (`components/h1os/src/sub_rtc.c`)
- Add `#define TIMER_PULSE_MODE_BIT (1 << 0)`.
- In `sub_rtc_arm_countdown()`:
  - Stop timer (`Timer_mode = 0`).
  - Write $T$ to `Timer_value` (`0x10`).
  - Write `clk_src | TIMER_ENABLE_BIT | TIMER_INT_ENABLE_BIT | TIMER_PULSE_MODE_BIT` to `Timer_mode` (`0x11`).

### Phase 3: Pure Event Sleep Setup (`components/h1os/src/sub_power.c`)
- In `sub_power_init_ulp()`:
  - Configure ULP with `ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };`
  - Call `ulp_riscv_config_and_run(&cfg);`
  - Do not enable internal sleep timer.
- In `sub_power_enter_deep_sleep()`:
  - Arm PCF85063A countdown in pulsed mode ($10\text{ s}$ slice): `sub_rtc_arm_countdown(10);`
  - Route wake pins (GPIO 0, 18, 5) into RTC domain with low-level comparator (`INT_TYPE = 4`).
  - **No pad hold on input pins** (`rtc_gpio_hold_en` strictly omitted for wake inputs).
  - Enforce Pure Event Mode:
    ```c
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    ```
  - Strobe `GPIO_WAKEUP_CLR` and start deep sleep.

### Phase 4: ULP Coprocessor Slice Counter (`components/h1os/ulp/main.c`)
- Export `slice_counter` to Main CPU.
- Snapshot `RTC_GPIO_STATUS_REG` at line 1 of `main()`.
- On `GPIO 0` / `GPIO 18`:
  - Classify tap vs hold.
  - Set `dispatch_reason = 2 (ULP_DISPATCH_MAIN_WAKE)`, wake Main CPU immediately.
- On `GPIO 5` (PCF85063A pulse):
  - `slice_counter++`
  - If `slice_counter == (SLICES_OVERFLOW - 1)` (5th slice / 50s):
    - Run sensor reading / ADC battery guard.
    - Do not wake Main CPU.
  - If `slice_counter >= SLICES_OVERFLOW` (6th slice / 60s):
    - Reset `slice_counter = 0`.
    - Set `dispatch_reason = 2 (ULP_DISPATCH_MAIN_WAKE)`.
    - Wake Main CPU for ePaper screen refresh.
  - Intermediary slices:
    - Clear latches via `ulp_riscv_gpio_wakeup_clear()` and `RTC_GPIO_STATUS_W1TC_REG`.
    - Halt ULP with zero Main CPU wake.

### Phase 5: Restore Full H1OS Lifecycle (`examples/H1OS/main/main.c`)
- Reconnect `h1os_start(&lifecycle)` in `app_main()`.
- Restore the 4 modular screens, LVGL keypad navigation, audio feedback, and orchestrator state machine.

---

## 5. Verification & Testing Matrix

1. **Compilation Verification:**
   - `build_dev` and `build_prod` targets compile cleanly with exit code 0.
2. **Serial Monitor Validation on COM3:**
   - Pre-sleep log confirms `TIMER_REG = 0x20000000` (`GPIO_WAKEUP_ENA = 1`, `SLP_TIMER_EN = 0`).
   - Tapping BOOT or POWER wakes Main CPU into Flow B with immediate sub-millisecond response.
   - Slices 1–4: ULP increments counter and halts; Main CPU sleeps undisturbed.
   - Slice 5 (`overflow - 1`): ULP runs battery ADC sample.
   - Slice 6 (`overflow`): ULP wakes Main CPU for ePaper screen refresh.
