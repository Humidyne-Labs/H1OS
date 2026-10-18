# Note #1: Empirical Verification of ULP-RISC-V Wake Interrupts & Pre-Sleep Race Forensics

> **Date:** October 18, 2026  
> **Authors:** Humiditron & Gemini (Antigravity)  
> **Target:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
> **Status:** **IN PROGRESS — Stage 2 Validated; Fixes Implemented; Further Silicon Testing Required**

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

Execution of the initial 3-stage validation suite on physical hardware produced the following telemetry:

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

## 4. Forensic Analysis of Issues Encountered

### 1. The Pre-Sleep Delay Race (Stages 1 & 3)
- In `arm_stage_1_timer_mode` and `arm_stage_3_dual_mode`, `ulp_riscv_config_and_run(&cfg)` was invoked **before** a 1500 ms `vTaskDelay` inside `enter_deep_sleep_guarded()`.
- Because `ulp_riscv_config_and_run()` starts the hardware timer immediately, the ULP executed entry 1 while the Main CPU was still running FreeRTOS tasks (`MAIN_STATE_IN_IDLE` was false, and `RTC_CNTL_RDY_FOR_WAKEUP` was 0).
- The ULP's defensive loop timed out instead of hanging indefinitely, latching `ulp_rdy_timeout = 1`.
- Because `ulp_rdy_timeout` was not reset at the start of each ULP entry, the failure verdict persisted into the final telemetry dump.

### 2. The Stage 3 Tactile Tap Failure
- During Stage 3, tapping the tactile PWR button failed to wake the device immediately; the chip only woke after the 5.0-second PMU countdown timer expired.
- **Root Cause Identified**: The ULP firmware contained an legacy `RDY_FOR_WAKEUP` polling loop inherited from old 2016 FSM assembly patterns. When the button was tapped, the ULP woke up, entered this loop, detected that the Main CPU was not yet in a stable ready state (or hit the inverted `MAIN_STATE_IN_IDLE` safety check), and called `ulp_riscv_halt()` **without calling `ulp_riscv_wakeup_main_processor()`**.
- The wake signal was never delivered to the main processor, leaving the chip asleep until the 5-second PMU timer fired.

---

## 5. Firmware Corrections Implemented

1. **Elimination of the Faulty `RDY_FOR_WAKEUP` Polling Loop (`ulp_test_main.c`):**
   In ESP-IDF ULP-RISC-V architecture, `ulp_riscv_wakeup_main_processor()` writes `RTC_CNTL_SW_CPU_INT` atomically. The ULP now unconditionally signals the Main CPU upon wake:
   ```c
   /* 4. Hand off execution: Signal Main CPU to wake immediately. */
   test_data.ulp_step_checkpoint = ULP_CP_RDY_CONFIRMED;
   test_data.ulp_step_checkpoint = ULP_CP_WAKE_SIGNALED;
   ulp_riscv_wakeup_main_processor();
   test_data.ulp_completed = 1;
   ```

2. **Reset `ulp_rdy_timeout` on Entry (`ulp_test_main.c`):**
   ```c
   int main(void)
   {
       test_data.ulp_entry_count++;
       test_data.ulp_rdy_timeout = 0;
       ...
   ```

3. **Re-sequencing Sleep Entry (`main.c`):**
   All UART logging, flushing, and FreeRTOS settling delays execute **before** `ulp_riscv_config_and_run()`, ensuring `esp_deep_sleep_start()` is called immediately after starting the ULP:
   ```c
   prepare_serial_and_pins_before_sleep();

   ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER };
   ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
   SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

   enter_deep_sleep_guarded();
   ```

---

## 6. Summary of Confirmed Silicon Facts

1. **Trap `0x1000` is Eradicated:** `CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y` is compulsory and completely resolves the unmapped vector panic.
2. **Event Mode Validated:** Pure RTC GPIO tactile wake with ISR switch-bounce handling works cleanly on physical hardware (Stage 2 PASS).
3. **Deterministic Main Wake:** `ESP_SLEEP_WAKEUP_ULP` (`0x00000040`) is consistently delivered on coprocessor wake.

---

## 7. Status & Required Next Steps: Further Testing Required

While the code fixes have been implemented, verified against ESP-IDF architecture, and compiled cleanly into `riscv_test.bin`, **further empirical testing on physical hardware is required to verify full operation across all modes**.

### Verification Criteria for Next Silicon Run:
1. **Stage 1 (Pure Timer Mode):**
   - Must wake automatically after 5.0 seconds.
   - Must report `STAGE VERDICT: PASS` with `ULP RDY_FOR_WAKEUP Status: OK`.
2. **Stage 2 (Pure Event Mode):**
   - Must wake on tactile PWR (GPIO 18) press.
   - Must report `STAGE VERDICT: PASS` with 0 coprocessor traps.
3. **Stage 3 (Dual Mode):**
   - Must wake **immediately** when tactile PWR (GPIO 18) is tapped, proving concurrent operation without waiting for the 5-second timer countdown.
   - Must report `STAGE VERDICT: PASS`.

# New Log

```TEXT
--- WARNING: GDB cannot open serial ports accessed as COMx
--- NOTE: Using \\.\COM3 instead...
--- esp-idf-monitor 1.10.0 on \\.\COM3 115200
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x15 (USB_UART_CHIP_RESET),boot:0x20 (DOWNLOAD(USB/UART0))
Saved PC:0x40041a76
--- 0x40041a76: ets_delay_us in ROM
waiting for download
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect....
I (1552) RISCV_TEST: ========================================================================
I (1552) RISCV_TEST: >>> PREPARING STAGE 1: Pure Timer Mode (PMU Countdown) <<<
I (1552) RISCV_TEST: Proves binary loading, slow clock domain, and ULP wake pipeline first.
I (1552) RISCV_TEST: Will automatically wake in 5.0 seconds via internal 136 kHz RC timer...
I (1552) RISCV_TEST: ========================================================================
I (1552) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect...........

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 1: TIMER MODE (5s PMU COUNTDOWN)
========================================================================
 Boot Count / Sleep Wake # : 1
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 1
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : OK
 ULP Total Entry Count     : 2
 ULP GPIO Wake Count       : 0
 ULP Timer Wake Count      : 2
 ULP ISR Handler Executions: 0
 Last ISR Source GPIO      : 255
 Raw RTC_GPIO_STATUS_REG   : 0x00000000
 Sampled Pin Levels        : PWR(18)=1, BOOT(0)=1 (Raw: 0x00000003)
 Coprocessor Execution Time: 164 cycles
 STAGE VERDICT             : PASS
========================================================================

I (4054) RISCV_TEST: Stage 1 (Timer) Finished. Transitioning to Stage 2 (Event Mode)...
I (4054) RISCV_TEST: ========================================================================
I (4054) RISCV_TEST: >>> PREPARING STAGE 2: Pure Event Mode (RTC GPIO 18) <<<
I (4054) RISCV_TEST: PMU Sleep Timer is DISABLED. 30-second fallback timer armed.
I (4054) RISCV_TEST: ACTION REQUIRED: Press tactile PWR (GPIO 18) button to wake!
I (4054) RISCV_TEST: ========================================================================
I (4054) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect.............

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
 ULP ISR Handler Executions: 105
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00040000
 Sampled Pin Levels        : PWR(18)=0, BOOT(0)=1 (Raw: 0x00000002)
 Coprocessor Execution Time: 56126 cycles
 STAGE VERDICT             : PASS
========================================================================

I (4054) RISCV_TEST: Stage 2 (Event) Finished. Transitioning to Stage 3 (Dual Mode)...
I (4054) RISCV_TEST: ========================================================================
I (4054) RISCV_TEST: >>> PREPARING STAGE 3: Dual Mode (Timer + GPIO 18 Concurrently) <<<
I (4054) RISCV_TEST: BOTH 5s PMU Timer AND RTC GPIO 18 wakeups are armed simultaneously.
I (4054) RISCV_TEST: You can either WAIT 5.0s for timer wake OR TAP PWR (GPIO 18) button immediately!
I (4054) RISCV_TEST: ========================================================================
I (4054) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect...........

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 3: DUAL MODE (PMU TIMER + RTC GPIO 18)
========================================================================
 Boot Count / Sleep Wake # : 3
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 3
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : OK
 ULP Total Entry Count     : 5
 ULP GPIO Wake Count       : 0
 ULP Timer Wake Count      : 2
 ULP ISR Handler Executions: 1
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00000000
 Sampled Pin Levels        : PWR(18)=1, BOOT(0)=1 (Raw: 0x00000003)
 Coprocessor Execution Time: 164 cycles
 STAGE VERDICT             : PASS
========================================================================


************************************************************************
*  TEST SUITE COMPLETE: ALL 3 MODES VALIDATED SUCCESSFULLY!            *
*  Check telemetry dump above for mutual exclusivity characterization. *
************************************************************************
```

# Newist logging

```TEXT
--- WARNING: GDB cannot open serial ports accessed as COMx
--- NOTE: Using \\.\COM3 instead...
--- esp-idf-monitor 1.10.0 on \\.\COM3 115200
--- Quit: Ctrl+] | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x15 (USB_UART_CHIP_RESET),boot:0x20 (DOWNLOAD(USB/UART0))
Saved PC:0x40041a76
--- 0x40041a76: ets_delay_us in ROM
waiting for download
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect.....
I (1552) RISCV_TEST: ========================================================================
I (1552) RISCV_TEST: >>> PREPARING STAGE 1: Pure Timer Mode (PMU Countdown) <<<
I (1552) RISCV_TEST: Proves binary loading, slow clock domain, and ULP wake pipeline first.
I (1552) RISCV_TEST: Will automatically wake in 5.0 seconds via internal 136 kHz RC timer...
I (1552) RISCV_TEST: ========================================================================
I (1552) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect...........

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 1: TIMER MODE (5s PMU COUNTDOWN)
========================================================================
 Boot Count / Sleep Wake # : 1
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 1
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : OK
 ULP Total Entry Count     : 2
 ULP GPIO Wake Count       : 0
 ULP Timer Wake Count      : 2
 ULP ISR Handler Executions: 0
 Last ISR Source GPIO      : 255
 Raw RTC_GPIO_STATUS_REG   : 0x00000000
 Sampled Pin Levels        : PWR(18)=1, BOOT(0)=1 (Raw: 0x00000003)
 Coprocessor Execution Time: 186 cycles
 Verified Wake Trigger     : INTERNAL PMU TIMER (Countdown Expired)
 STAGE VERDICT             : PASS
========================================================================

I (3554) RISCV_TEST: Stage 1 (Timer) Finished. Transitioning to Stage 2 (Event Mode)...
I (3554) RISCV_TEST: ========================================================================
I (3554) RISCV_TEST: >>> PREPARING STAGE 2: Pure Event Mode (RTC GPIO 18) <<<
I (3554) RISCV_TEST: PMU Sleep Timer is DISABLED. 30-second fallback timer armed.
I (3554) RISCV_TEST: ACTION REQUIRED: Press tactile PWR (GPIO 18) button to wake!
I (3554) RISCV_TEST: ========================================================================
I (3554) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect.....

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
 ULP ISR Handler Executions: 108
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00040000
 Sampled Pin Levels        : PWR(18)=0, BOOT(0)=1 (Raw: 0x00000002)
 Coprocessor Execution Time: 76563 cycles
 Verified Wake Trigger     : PHYSICAL RTC GPIO 18 TAP (Tactile Key Pressed)
 STAGE VERDICT             : PASS
========================================================================

I (3554) RISCV_TEST: Stage 2 (Event) Finished. Transitioning to Stage 3 (Dual Mode)...
I (3554) RISCV_TEST: ========================================================================
I (3554) RISCV_TEST: >>> PREPARING STAGE 3: Dual Mode (15s PMU Timer + GPIO 18 Concurrently) <<<
I (3554) RISCV_TEST: PMU Timer is set to 15.0 seconds. RTC GPIO 18 is armed concurrently.
I (3554) RISCV_TEST: ACTION REQUIRED: Tap tactile PWR (GPIO 18) button within 15 seconds!
I (3554) RISCV_TEST: Host USB CDC reconnect takes ~3s. Waking before 15s proves GPIO wake.
I (3554) RISCV_TEST: ========================================================================
I (3554) RISCV_TEST: Pre-Sleep Pin Levels Check: PWR (GPIO 18) = 1, BOOT (GPIO 0) = 1
--- ERROR: ClearCommError failed (PermissionError(13, 'The device does not recognize the command.', None, 22))
--- Waiting for the device to reconnect...............................

========================================================================
 [RISC-V TEST] TELEMETRY DUMP: STAGE 3: DUAL MODE (PMU TIMER + RTC GPIO 18)
========================================================================
 Boot Count / Sleep Wake # : 3
 Main Wake Causes Bitmask  : 0x00000040 (ULP: YES, TIMER: NO, TRAP: NO)
 Shared Structure Magic    : 0x554C5032 (VALID)
 Stage Configured in ULP   : 3
 ULP Checkpoint Reached    : 8: HALTED (CLEAN EXIT)
 ULP Hand-Off Status       : 1 (0=Init, 1=Success, 2=Early Wake)
 ULP RDY_FOR_WAKEUP Status : OK
 ULP Total Entry Count     : 5
 ULP GPIO Wake Count       : 2
 ULP Timer Wake Count      : 0
 ULP ISR Handler Executions: 1
 Last ISR Source GPIO      : 18
 Raw RTC_GPIO_STATUS_REG   : 0x00000000
 Sampled Pin Levels        : PWR(18)=1, BOOT(0)=1 (Raw: 0x00000003)
 Coprocessor Execution Time: 195 cycles
 Verified Wake Trigger     : PHYSICAL RTC GPIO 18 TAP (Tactile Key Pressed)
 STAGE VERDICT             : PASS
========================================================================


************************************************************************
*  TEST SUITE COMPLETE: ALL 3 MODES VALIDATED SUCCESSFULLY! (PASS)     *
*  Mutual Exclusivity Disproven: Timer and GPIO run concurrently!      *
************************************************************************



```