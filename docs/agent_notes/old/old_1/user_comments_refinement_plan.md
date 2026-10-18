# Action Plan: Hardware Review & Architecture Refinements

**Target Project:** H1OS (ESP32-S3)  
**Branch:** `E-Class-Dev-002`  
**Date:** 2026-10-16  

---

## 1. Executive Summary & Review Responses

This action plan addresses the three review comments from the latest code diff:

| # | Topic | Review Comment | Architectural Resolution |
|---|---|---|---|
| **1** | **LED Breathing Heartbeat** | *"we should include an async "heartbeat" that "breaths" fade in, fade out."* | Introduce asynchronous background breathing engine (`hal_led_start_breathing(uint32_t period_ms)`, `hal_led_stop_breathing()`) using FreeRTOS and LEDC hardware fading. Auto-stops on sleep pad isolation. |
| **2** | **SD Probe IO De-initialization** | *"de we need to de-init the io before mounting?"* | **Yes.** In `sub_sdcard_probe()`, we temporarily pull down `MISO`/`MOSI`. We must call `gpio_reset_pin()` immediately upon probe exit so the GPIO matrix and IO MUX are clean before SDMMC peripheral initialization or idle sleep. |
| **3** | **Modular Debug Dumps** | *"all verbose debug dumps "should" be commented functions, that are called, for easy removal later."* | Refactor all inline ULP telemetry and EXT1 logging into dedicated, documented static functions (`debug_dump_ulp_telemetry()`, `debug_dump_ext1_wake_status()`) guarded by clean one-line call sites for trivial removal/commenting. |

---

## 2. Technical Design & Implementation Details

### Area 1: Asynchronous LED Breathing ("Heartbeat")
- **Interface in [`components/h1os/include/h1os/hal_io.h`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/include/h1os/hal_io.h):**
  ```c
  /**
   * @brief Starts an asynchronous background task to "breathe" (fade in and fade out) the status LED.
   * @param cycle_period_ms Total duration of one breathe cycle in ms (fade-in + fade-out). Default: 2000 ms if 0.
   * @return ESP_OK on success, or ESP_FAIL if task creation fails.
   */
  esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms);

  /**
   * @brief Stops the asynchronous breathing task and turns the LED off.
   * @return ESP_OK on success.
   */
  esp_err_t hal_led_stop_breathing(void);

  /**
   * @brief Queries whether the asynchronous breathing task is actively running.
   */
  bool hal_led_is_breathing(void);
  ```
- **Implementation in [`components/h1os/src/hal_io.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/hal_io.c):**
  - Manages a static `TaskHandle_t s_breath_task` and `volatile bool s_breathing_running`.
  - Worker task executes:
    1. `hal_led_fade_to(100, half_period)` and waits for `half_period` ticks.
    2. `hal_led_fade_to(0, half_period)` and waits for `half_period` ticks.
    3. Seamless exit on `s_breathing_running == false`.
  - Automatically called in `hal_led_pwm_deinit()` and `hal_io_isolate_sleep_pads()` to guarantee the task terminates before deep sleep.

---

### Area 2: SD Card IO Reset & De-init
- **Issue:** `sub_sdcard_probe()` configures GPIO 40 (`MISO`/`DAT0`) and GPIO 41 (`MOSI`/`CMD`) as GPIO input with pulldown. If left configured, IO MUX registers retain pulldown/input routing, which can disturb SDMMC 1-bit high-speed timing or leak power if no card is inserted.
- **Implementation in [`components/h1os/src/sub_sdcard.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_sdcard.c):**
  ```c
  bool sub_sdcard_probe(void)
  {
      if (s_sd_card != NULL) return true;

      gpio_config_t probe_cfg = {
          .pin_bit_mask = (1ULL << HAL_PIN_SD_MISO) | (1ULL << HAL_PIN_SD_MOSI),
          .mode         = GPIO_MODE_INPUT,
          .pull_up_en   = GPIO_PULLUP_DISABLE,
          .pull_down_en = GPIO_PULLDOWN_ENABLE,
          .intr_type    = GPIO_INTR_DISABLE,
      };
      gpio_config(&probe_cfg);
      esp_rom_delay_us(100);

      int miso_lvl = gpio_get_level(HAL_PIN_SD_MISO);
      int mosi_lvl = gpio_get_level(HAL_PIN_SD_MOSI);

      /* Release pull-downs and reset pins back to clean reset state */
      gpio_pulldown_dis(HAL_PIN_SD_MISO);
      gpio_pulldown_dis(HAL_PIN_SD_MOSI);
      gpio_reset_pin(HAL_PIN_SD_MISO);
      gpio_reset_pin(HAL_PIN_SD_MOSI);

      return (miso_lvl != 0 || mosi_lvl != 0);
  }
  ```
  - Additionally, if `sub_sdcard_mount()` fails or `sub_sdcard_unmount()` is executed, ensure all SD pins (CLK, CMD, DAT0) are cleanly parked via `gpio_reset_pin()`.

---

### Area 3: Clean Modular Diagnostic Dumps
- **Implementation in [`components/h1os/src/h1os_lifecycle.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_lifecycle.c):**
  - Extract multi-line diagnostic logs into self-contained static functions with Doxygen headers:
    1. `debug_dump_ulp_telemetry()`: logs ULP wake cause, RTC IO status mask, button ID, hold duration, loop samples, and cycle execution.
    2. `debug_dump_ext1_wake_status(uint64_t ext1_pins, bool button_woke, bool timer_f, bool alarm_f, bool is_rtc_wake)`: logs EXT1 wake pin mask and external RTC interrupt flags.
  - Lifecycle calling sites become clean, single-line calls:
    ```c
    /* [DEBUG] Diagnostic telemetry dump — comment out for production release */
    debug_dump_ulp_telemetry();
    ```
    and
    ```c
    /* [DEBUG] EXT1 wake status dump — comment out for production release */
    debug_dump_ext1_wake_status(ext1_pins, button_woke, timer_f, alarm_f, is_rtc_wake);
    ```

---

## 3. Verification & Validation Steps
1. **Compilation Check:** Run production build using ESP-IDF v6.1 profile script to verify zero compiler warnings or linking errors.
2. **Heartbeat Test:** Call `hal_led_start_breathing(2000)` in `examples/H1OS/main/main.c` on boot to verify smooth hardware PWM breathing without CPU starvation.
3. **SD Probe De-init Test:** Verify SD card mounting works when a card is inserted and cleanly resets pins when no card is present.
4. **Lifecycle Code Cleanliness:** Verify `h1os_lifecycle.c` contains clean, isolated debug functions that can be toggled by commenting a single line.
