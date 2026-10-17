# Action Plan: ESP32-S3 RTC Domain Handover, ULP Pulse Polling, and Flow Observability

**Target Project:** H1OS (ESP32-S3)  
**Branch:** `E-Class-Dev-002`  
**Reference Document:** [`docs/logs/agent_help.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/logs/agent_help.md)  
**Date:** 2026-10-16  

---

## 1. Executive Summary & Architectural Directives

Based on the architectural guidance in `agent_help.md`, hardware log analysis (`10-16-2026-05-41-pm.log`), and user directives, this plan formalizes the exact RTC domain handover, ULP IO polling, and driver logging resolutions:

```
[Deep Sleep: HP Domain Powered OFF]
              |
     [RTC IO Interrupt Event] (BOOT GPIO 0 or POWER GPIO 18 transitions LOW)
              v
[ULP Restarts in RTC Slow SRAM @ 17.5 MHz]
              |
 1. Assert RTC Pull-ups (ulp_riscv_gpio_pullup)
 2. Inspect RTC GPIO Status & Pin Level
              v
 [Poll & Measure Pulse Duration]
 while (ulp_riscv_gpio_get_level(btn) == 0) {
     hold_ms += 10;
     ulp_riscv_delay_cycles(175000); // 10ms
     if (hold_ms >= 3000) break;
 }
              |
              +---> If < 20 ms: Spurious glitch -> Clear latch & ulp_riscv_halt()
              |
              +---> If 20 ms <= hold < 3000 ms: Valid User Tap!
              |     dispatch_reason = 2 (MAIN_WAKE)
              |     ulp_riscv_wakeup_main_processor();
              |     ulp_riscv_halt();
              |
              +---> If hold >= 3000 ms: Long Press Hold!
                    dispatch_reason = (BOOT ? 4 [BL_JUMP] : 5 [PWR_OFF])
                    ulp_riscv_wakeup_main_processor();
                    ulp_riscv_halt();
              v
[Main Processor Wakes (Xtensa Core)]
 1. Reclaim IO to HP Domain (rtc_gpio_deinit -> gpio_config)
 2. Display Prominent Flow State Banner
 3. Execute Flow B Interactive Session
```

---

## 2. Technical Design & Implementation Tasks

### Task 1: RTC Domain IO Ownership Handover & ULP Pull-Up Assertion
Per `agent_help.md` (Sections 1 & 2), GPIOs 0–21 support RTC pad logic (`RTC_MUX`). The HP domain and RTC domain must cleanly transfer ownership:
- **Sleep Preparation (Main CPU $\rightarrow$ RTC Domain):**
  - In [`components/h1os/src/hal_io.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/hal_io.c) (`hal_io_isolate_sleep_pads()`):
    ```c
    rtc_gpio_init(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(HAL_PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_wakeup_enable(HAL_PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    ```
    (Repeated for `HAL_PIN_BUTTON_POWER` and `HAL_PIN_RTC_INT`).
- **Wake Reclamation (RTC Domain $\rightarrow$ Main CPU):**
  - In `hal_io_release_pad_holds()`:
    ```c
    rtc_gpio_wakeup_disable(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT); // Clears RTC_MUX routing back to HP digital matrix
    ```
- **ULP Coprocessor Pad Assertion:**
  - In [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c):
    Call `ulp_riscv_gpio_init()` and explicitly enable pull-ups:
    ```c
    ulp_riscv_gpio_init(GPIO_NUM_0);
    ulp_riscv_gpio_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_pullup(GPIO_NUM_0);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_0);

    ulp_riscv_gpio_init(GPIO_NUM_18);
    ulp_riscv_gpio_input_enable(GPIO_NUM_18);
    ulp_riscv_gpio_pullup(GPIO_NUM_18);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_18);

    ulp_riscv_gpio_init(GPIO_NUM_5);
    ulp_riscv_gpio_input_enable(GPIO_NUM_5);
    ulp_riscv_gpio_pullup(GPIO_NUM_5);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_5);
    ```
    *Root Cause Addressed:* Because GPIO 0 has no physical pull-up resistor on the PCB, omitting `ulp_riscv_gpio_pullup()` caused released lines to float LOW, artificially stalling the loop for 2,960 ms.

---

### Task 2: Responsive ULP Pulse-Duration Polling Loop
Per `agent_help.md` (Section 4), implement precise level-polling while maintaining strict architecture invariants (Wake ULP on IO event $\rightarrow$ ULP polls IO $\rightarrow$ ULP wakes main app):
- **In [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c):**
  ```c
  /* Read initial state */
  uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
  int boot_lvl = ulp_riscv_gpio_get_level(GPIO_NUM_0);
  int pwr_lvl  = ulp_riscv_gpio_get_level(GPIO_NUM_18);

  bool boot_active = ((rtcio_int_st & BIT(0)) != 0) || (boot_lvl == 0);
  bool pwr_active  = ((rtcio_int_st & BIT(18)) != 0) || (pwr_lvl == 0);

  if (boot_active || pwr_active) {
      int active_btn = (pwr_active && !boot_active) ? 2 : 1;
      gpio_num_t pin = (active_btn == 2) ? GPIO_NUM_18 : GPIO_NUM_0;

      /* Count delay & measure hold duration while button is actively held LOW */
      uint32_t hold_ms = 0;
      while (ulp_riscv_gpio_get_level(pin) == 0) {
          loop_sample_count++;
          ulp_riscv_delay_cycles(cycles_per_ms * 10); // 10 ms delay per step
          hold_ms += 10;
          if (hold_ms >= 3000) {
              break; // Guard against infinite stall
          }
      }
      hold_duration_ms = hold_ms;

      /* Clear RTC GPIO status and ULP interrupt wakeup latch */
      REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
      ulp_riscv_gpio_wakeup_clear();

      /* Glitch filter: Ignore transients shorter than 20 ms */
      if (hold_ms < 20 && ((rtcio_int_st & (BIT(0) | BIT(18))) == 0)) {
          exit_ccount = ULP_RISCV_GET_CCOUNT();
          ulp_riscv_halt();
          return 0;
      }

      last_wake_btn = active_btn;

      if (hold_ms >= 3000) {
          /* Long Hold: 3.0s */
          dispatch_reason = (active_btn == 1) ? 4 /* BL_JUMP */ : 5 /* POWER_OFF */;
      } else {
          /* Normal User Tap: Immediately wakes main application */
          dispatch_reason = 2; /* MAIN_WAKE (Flow B) */
          boot_btn_events++;
      }

      exit_ccount = ULP_RISCV_GET_CCOUNT();
      ulp_riscv_wakeup_main_processor();
      ulp_riscv_halt();
      return 0;
  }
  ```
- **Performance Characteristics:**
  - Standard tap ($50\text{--}100\text{ ms}$): Polling exits within $10\text{ ms}$ of physical release. Main processor wakes in $< 110\text{ ms}$.
  - Long press ($\ge 3000\text{ ms}$): Detects $3.0\text{s}$ threshold and triggers ROM Bootloader jump or Power Off.
  - Sub-20ms contact glitches are filtered without waking the main Xtensa core.

---

### Task 3: Prominent Flow State Console Banner
- **In [`components/h1os/src/h1os_lifecycle.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_lifecycle.c):**
  - Implement `h1os_log_flow_banner()` called immediately after `flow = orch_flow_determine_wakeup()`:
    ```text
    ================================================================================
    >>> H1OS ACTIVE FLOW: [FLOW B - INTERACTIVE UI SESSION] <<<
    >>> Wake Trigger    : ULP Button Press (BOOT / GPIO 0)
    >>> Boot Count      : 1 | Wake Count: 2 | Inactivity Timeout: 30s
    ================================================================================
    ```
    or for Flow A:
    ```text
    ================================================================================
    >>> H1OS ACTIVE FLOW: [FLOW A - QUIESCENT SENSOR SAMPLE BURST] <<<
    >>> Wake Trigger    : ULP Periodic Timer (Period: 60s)
    >>> Target Action   : SHTC3 Burst -> Ring Buffer -> Deep Sleep (Display Untouched)
    ================================================================================
    ```

---

### Task 4: MicroSD Absence Latching & Log Noise Elimination
- **In [`components/h1os/src/sub_sdcard.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_sdcard.c):**
  - Latch card absence on first boot timeout: `s_card_absent_latched = true`.
  - In `sub_sdcard_mount_async()`, if `s_card_absent_latched`, return `ESP_ERR_NOT_FOUND` immediately to prevent repeating the 1.0s ACMD41 timeout on every button wake.
  - Temporarily lower driver log levels (`esp_log_level_set("sdmmc_common", ESP_LOG_NONE)`, `esp_log_level_set("vfs_fat_sdmmc", ESP_LOG_NONE)`, `esp_log_level_set("SD_HOST", ESP_LOG_NONE)`, `esp_log_level_set("SD_TRANS", ESP_LOG_NONE)`) during the initial probe.
  - Cleanly park SD pins with `gpio_reset_pin()` when unmounted or absent.
- **In [`examples/H1OS/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/examples/H1OS/main/main.c):**
  - Skip calling `sub_sdcard_mount_async()` in `app_on_wake()` if card is absent.

---

### Task 5: SDKConfig Integrity & Runtime LEDC Filtering
- **SDKConfig Invariant:** Leave `sdkconfig.defaults.dev` with `CONFIG_LOG_DEFAULT_LEVEL_DEBUG=y` 100% untouched.
- **In [`components/h1os/src/hal_io.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/hal_io.c):**
  - In `hal_io_early_init()`, set runtime log level for internal drivers:
    `esp_log_level_set("ledc", ESP_LOG_WARN);`
  - In `h1os_early_init()`, set default log level to `ESP_LOG_INFO` via `esp_log_level_set("*", ESP_LOG_INFO)` and explicitly elevate all H1OS application component tags (`h1os_lifecycle`, `orch_flow`, `orch_display_sync`, `HAL_IO`, `HAL_FLASH`, `sub_power`, `sub_sdcard`, `sub_audio`) to `ESP_LOG_DEBUG`.
  - This compiles out/suppresses `ESP_EARLY_LOGD` driver spam while keeping all H1OS application debug logs completely intact.

---

## 3. Verification & Validation Steps

1. **Compilation Check:** Build production target with profile script:
   `& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"`
   `idf.py -C examples\H1OS -B examples\H1OS\build_prod build`
   Ensure exit code 0 and zero warnings.
2. **Flow Banner Verification:** Observe serial console on cold boot, Flow A wake, and Flow B button wake to verify distinct framed ASCII banners.
3. **ULP Latency Verification:** Tap the BOOT button; verify ULP telemetry reports `hold` time corresponding to the exact tap duration ($< 150\text{ ms}$) rather than 2960 ms, and main CPU wakes immediately.
4. **SD Absence Verification:** On systems with an empty SD slot, verify SD card mount attempt runs once on boot, latches absent, and produces zero subsequent mount delays or error traces on wake.
5. **Log Cleanliness Check:** Confirm that `ledc: duty_config` messages are silenced during asynchronous LED breathing.
