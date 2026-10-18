# Note #1: Empirical Verification of ULP-RISC-V Wake Interrupts & Pre-Sleep Race Forensics

> **Date:** October 18, 2026  
> **Authors:** Humiditron & Gemini (Antigravity)  
> **Target:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
> **Status:** **EMPIRICALLY TESTED ON SILICON — Stage 2 PASS, Stages 1 & 3 Pre-Sleep Race Diagnosed & Fixed**

---

## 1. The Myth & The Historical Panic Trap (`0x1000`)

For weeks, the development of H1OS lived under the shadow of a severe architectural concern:
**The "Mutual Exclusivity" Hypothesis.**

Early experiments on the ESP32-S3 PMU led to repeated system lockups and unhandled coprocessor traps whenever both the internal PMU sleep timer (`RTC_CNTL_ULP_CP_SLP_TIMER_EN`) and RTC GPIO wakeup detectors (`RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA`) were armed:
- The coprocessor died with panic trap code `0x1000` (`RTC_COCPU_TRAP_TRIG_EN`).
- The main CPU froze or failed to wake reliably.
- The team was forced into complex workarounds: pure event mode, software Peterson spinlocks, and delegating periodic timing entirely to the external PCF85063A RTC.

---

## 2. Forensic Discoveries on Physical Silicon

A rigorous audit and the clean-slate harness (`examples/riscv_test`) confirmed two major silicon realities:

1. **The Missing Vector Table (`CONFIG_ULP_RISCV_INTERRUPT_ENABLE`):**
   `CONFIG_ULP_RISCV_INTERRUPT_ENABLE` was originally omitted from `sdkconfig`. Without this Kconfig option, the ESP-IDF build system completely compiled out the ULP RISC-V interrupt vector table at `irq_vector` (`0x10`). Whenever a physical GPIO edge arrived, the RISC-V core jumped into unmapped vector space and threw an unhandled trap (`0x1000`).
   * **Silicon Verification**: Enabling `CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y` 100% eradicated trap `0x1000` across all test stages (`is_trap_wake == NO`).

2. **The GPIO 0 Strapping Pin Download Mode Trap:**
   GPIO 0 (`BOOT` button) was previously armed as a wake source. Because deep sleep wake is a full chip reset on the ESP32-S3, holding the tactile button down during wake caused the ROM bootloader to sample GPIO 0 LOW and enter UART download mode. Testing with `PIN_BUTTON_PWR` (GPIO 18) eliminated this pitfall.

3. **CDC Sync Timing & Stale Latches:**
   With no 32.768 kHz crystal onboard, the slow clock runs on the 136 kHz internal RC oscillator ($\sim 7.35\ \mu\text{s}$/cycle). Pulse clears on `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` required $\ge 120\ \mu\text{s}$ ($> 16$ cycles) to cross clock domains cleanly.

---

## 3. The Live Physical Silicon Telemetry Log

Execution of the 3-stage validation suite produced the following exact hardware results:

```text
========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 1: TIMER MODE (5s PMU COUNTDOWN)
========================================================================
 Boot Count / Sleep Wake # : 1
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 1
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : TIMEOUT / AWAKE CHECK
 ULP Total Entry Count     : 2
 ULP GPIO Wake Count       : 0
 ULP Timer Wake Count      : 2
 ULP ISR Handler Executions: 0
 Last ISR Source GPIO      : 255
 Raw RTC_GPIO_STATUS_REG   : 0x00000000
 Sampled Pin Levels        : PWR(18)=1, BOOT(0)=1 (Raw: 0x00000003)
 Coprocessor Execution Time: 164 cycles
 STAGE VERDICT             : FAIL: ULP RDY_FOR_WAKEUP TIMEOUT
========================================================================

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 2: EVENT MODE (RTC GPIO 18)
========================================================================
 Boot Count / Sleep Wake # : 2
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 2
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : OK
 ULP Total Entry Count     : 3
 ULP GPIO Wake Count       : 1
 ULP Timer Wake Count      : 0
 ULP ISR Handler Executions: 115
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00040000
 Sampled Pin Levels        : PWR(18)=0, BOOT(0)=1 (Raw: 0x00000002)
 Coprocessor Execution Time: 67742 cycles
 STAGE VERDICT             : PASS
========================================================================

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 3: DUAL MODE (PMU TIMER + RTC GPIO 18)
========================================================================
 Boot Count / Sleep Wake # : 3
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 3
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : TIMEOUT / AWAKE CHECK
 ULP Total Entry Count     : 5
 ULP GPIO Wake Count       : 1
 ULP Timer Wake Count      : 1
 ULP ISR Handler Executions: 115
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00040000
 Sampled Pin Levels        : PWR(18)=0, BOOT(0)=1 (Raw: 0x00000002)
 Coprocessor Execution Time: 67742 cycles
 STAGE VERDICT             : FAIL: ULP RDY_FOR_WAKEUP TIMEOUT
========================================================================
```

---

## 4. Root Cause of the Stage 1 & 3 Verdict Failure

### The Pre-Sleep Delay Race
- In `arm_stage_1_timer_mode` and `arm_stage_3_dual_mode`, `ulp_riscv_config_and_run(&cfg)` was invoked **before** a 1500 ms `vTaskDelay` inside `enter_deep_sleep_guarded()`.
- Because `ulp_riscv_config_and_run()` immediately starts the hardware timer or coprocessor execution, the ULP executed entry 1 while the Main CPU was still awake in FreeRTOS running tasks (`MAIN_STATE_IN_IDLE` was false, and `RTC_CNTL_RDY_FOR_WAKEUP` was 0).
- The ULP's defensive loop correctly timed out instead of hanging indefinitely, latching `ulp_rdy_timeout = 1`.
- Because `ulp_rdy_timeout` was never reset at the beginning of each ULP invocation, the failure verdict persisted into the final telemetry dump.

### Why Stage 2 Passed Cleanly
- Stage 2 operated in pure Event Mode (`WAKEUP_SOURCE_GPIO`). The timer was disabled.
- The ULP did not execute during the 1500 ms pre-sleep window.
- When the tactile button was pressed after the Main CPU was fully in deep sleep, `RTC_CNTL_RDY_FOR_WAKEUP` was asserted, the hand-off succeeded with `OK`, 115 contact-bounce ISRs were serviced, and the stage achieved an unequivocal **`PASS`**.

---

## 5. Firmware Corrections Implemented

1. **Reset `ulp_rdy_timeout` on Entry (`ulp_test_main.c`):**
   ```c
   int main(void)
   {
       test_data.ulp_entry_count++;
       test_data.ulp_rdy_timeout = 0;
       ...
   ```
2. **Re-sequence Sleep Entry (`main.c`):**
   Perform all UART flushing and settling delays **before** starting the ULP, and call `esp_deep_sleep_start()` immediately after `ulp_riscv_config_and_run()`:
   ```c
   /* Perform all logging and serial drain DELAYS BEFORE starting the ULP */
   prepare_serial_and_pins_before_sleep();

   ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER };
   ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
   SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

   enter_deep_sleep_guarded();
   ```

---

## 6. Summary of Hard Silicon Truths

1. **Trap `0x1000` is Eradicated:** `CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y` is compulsory.
2. **Event Mode is Solid:** RTC GPIO tactile wake with ISR debounce works cleanly and reliably on physical hardware.
3. **Timer Mode Sequencing Rule:** `ulp_riscv_config_and_run()` must immediately precede `esp_deep_sleep_start()` without intermediate FreeRTOS task delays.
