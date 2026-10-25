# Layer 4: Application Lifecycle API & Services Specification

## 1. Overview
Layer 4 is the top-level public interface of H1OS (`h1os.h`). It isolates developers from low-level register manipulation, coprocessor details, and power sequencing by exposing:
1. **Declarative Lifecycle Engine:** `h1os_start()`, `h1os_sleep()`, `h1os_shutdown()`, `h1os_shutdown_for_storage()`, `h1os_get_telemetry()`, and `h1os_set_volume()`.
2. **Interactive UI Session Engine:** LVGL v9 display driver port, keypad indev binding, 80 MHz DFS idle power droop with 240 MHz pixel-pack blitz, and configurable inactivity sleep.
3. **System Time Services:** POSIX clock bridge, timezone formatting, and pluggable external SNTP sync callbacks.

---

## 2. Declarative Application Lifecycle Configuration

```c
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "hal_types.h"
#include "sub_power.h"

/**
 * @brief Structured Wake Context delivered to on_wake handler
 */
typedef struct {
    esp_reset_reason_t reset_reason;
    uint32_t           wakeup_causes;      ///< Bitmap of wakeup sources (esp_sleep_get_wakeup_causes)
    uint32_t           boot_count;
    uint32_t           deep_sleep_count;
    bool               woke_from_button;
    uint8_t            wake_button;        ///< h1os_wake_btn_t (0=None, 1=BOOT, 2=POWER)
    uint32_t           sleep_duration_sec;
    void               *user_data;
} h1os_wake_context_t;

/**
 * @brief Presentation splash screen types
 */
typedef enum {
    H1OS_SPLASH_BOOT = 0,
    H1OS_SPLASH_SLEEP,
    H1OS_SPLASH_SHUTDOWN,
    H1OS_SPLASH_MAX
} h1os_splash_type_t;

typedef void (*h1os_boot_cb_t)     (void *user_data);
typedef void (*h1os_wake_cb_t)     (const h1os_wake_context_t *ctx, void *user_data);
typedef void (*h1os_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);
typedef void (*h1os_shutdown_cb_t) (void *user_data);
typedef void (*h1os_splash_cb_t)   (h1os_splash_type_t type, void *user_data);
typedef void (*h1os_chime_cb_t)    (h1os_chime_type_t type, void *user_data);

/**
 * @brief Master Application Lifecycle Configuration
 */
typedef struct {
    /* Core Execution Hooks */
    h1os_boot_cb_t      on_boot;       ///< System boot / power-on reset hook
    h1os_wake_cb_t      on_wake;       ///< Interactive wake hook (Timer / RTC Alarm / Button Tap)
    h1os_pre_sleep_cb_t on_pre_sleep;  ///< Hook executed immediately prior to entering deep sleep
    h1os_shutdown_cb_t  on_shutdown;   ///< Hook executed immediately prior to battery cut

    /* Presentation Cues */
    struct {
        h1os_splash_cb_t on_splash;    ///< Custom splash rendering callback
        h1os_chime_cb_t  on_chime;     ///< Custom chime callback
        uint8_t          chime_mask;   ///< Hardware synthesized chime bitmask
        uint8_t          volume_pct;   ///< Acoustic presentation master volume (0..100%)
    } presentation;

    /* Interactive Session Parameters */
    struct {
        uint32_t       inactivity_timeout_sec; ///< Inactivity sleep timer (e.g. 30s)
        sys_clk_mode_t clk_mode;               ///< CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default)
        uint32_t       flow_a_period_sec;      ///< Flow A headless sensor sample burst interval (e.g. 60s)
        uint32_t       flow_b_period_sec;      ///< Flow B main application wake interval (e.g. 300s)
    } session;

    void *user_data;
} h1os_lifecycle_t;
```

---

## 3. Core Lifecycle Control APIs

### 3.1 `h1os_start()`
Entry point for the application, called from `app_main()`:
```c
esp_err_t h1os_start(const h1os_lifecycle_t *config);
```
- Initializes DFS (`sub_power_init_dfs()`), base HAL (`hal_io_early_init()`, `hal_i2c_init()`), PCF85063A RTC (`sub_rtc_init()`, `h1os_time_sync_rtc_to_system()`), and NVS (`sub_nvs_init()`).
- Inspects hardware reset reason and ULP dispatch reason (`orch_flow_determine_wakeup()`):
  - If `ORCH_FLOW_BOOT`: Restores persisted battery runtimes from NVS (`orch_state_load_runtimes_from_nvs()`), loads and starts the ULP-RISC-V binary in Pure Event Mode (`sub_power_init_ulp()`), plays boot chime/splash, invokes `on_boot()`, and starts the interactive session.
  - If `ORCH_FLOW_BOOTLOADER_JUMP`: Jumps straight to ROM Download Bootloader via `RTC_CNTL_FORCE_DOWNLOAD_BOOT`.
  - If `ORCH_FLOW_CRITICAL_OFF`: Executes orderly shutdown (`h1os_shutdown()`).
  - If `ORCH_FLOW_B_MAIN_WAKE`:
    - Restores previous EPD frame from flash (`orch_display_sync_restore_to_framebuffer()`) for differential partial refresh.
    - Initializes audio codec only on user button wakes (`button_woke == true`).
    - Invokes `on_wake()`, starts Core 1 LVGL task (`h1os_lvgl_start(5, 1)`), and either returns to sleep immediately (unattended RTC refresh) or spawns `h1os_session_monitor_task` (user interactive wake).

### 3.2 `h1os_sleep()`
Explicit command to enter deep sleep:
```c
esp_err_t h1os_sleep(uint32_t sleep_sec);
```
- Invokes `on_pre_sleep()`, drains and stops the Core 1 LVGL task (`h1os_quiesce_lvgl_pipeline()`), and executes `orch_flow_transition_to_sleep(sleep_sec)`.

### 3.3 `h1os_shutdown()` & `h1os_shutdown_for_storage()`
Orderly power cut:
```c
void h1os_shutdown(void);
void h1os_shutdown_for_storage(void);
```
- Cancels RTC countdown, plays shutdown chime/splash, invokes `on_shutdown()`, drains LVGL and audio, saves frame (or clears panel to pure white in storage mode), saves cumulative autonomy runtimes to NVS, waits for `POWER` button release, and cuts `GPIO 17 (BAT_CTRL)`.

---

## 4. Telemetry Consumption API

```c
typedef struct {
    float ambient_temp_c;
    float ambient_temp_f;
    float ambient_rh_pct;
    float dew_point_c;
    float dew_point_f;
    float vapor_pressure_hpa;
    float absolute_humidity_g;

    float window_low_c;
    float window_high_c;
    float window_avg_shtc3_c;
    float window_avg_die_c;
    float temp_historical_c;
    float rh_historical_pct;

    float   raw_shtc3_temp_c;
    float   mcu_die_temp_c;
    float   epd_glass_temp_c;
    float   trinode_temp_c;
    float   trinode_delta_c;
    uint8_t trinode_confidence_pct;

    bool                    is_thermally_settled;
    uint16_t                valid_trend;
    uint32_t                sample_count;
    uint32_t                flow_a_period_sec;
    uint32_t                flow_b_period_sec;
    uint16_t                battery_mv;
    uint16_t                boot_vbat_mv;
    uint8_t                 battery_percent;
    bool                    is_usb_powered;
    h1os_battery_state_t    battery_state;
    h1os_autonomy_metrics_t autonomy;
} h1os_telemetry_t;

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);
```

---

## 5. UI Engine: `h1os_lvgl.cpp/.h` (LVGL v9 Port)

- **Monochrome Buffer:** Allocates 40-line partial render buffer in internal DMA-capable SRAM with 1-bit monochrome palette (Index 0 = Black, Index 1 = White).
- **Keypad Input Device (`lv_indev`):**
  - Samples `hal_io_read_buttons()`.
  - Sets `long_press_time = 2000` ms (`LV_EVENT_LONG_PRESSED` triggers `h1os_shutdown()`).
  - Maps `HAL_BTN_BOOT` (`GPIO 0`) to `LV_KEY_RIGHT` (`LV_EVENT_KEY` forward carousel navigation) and `HAL_BTN_POWER` (`GPIO 18`) to `LV_KEY_ENTER` (`LV_EVENT_SHORT_CLICKED` reverse carousel navigation).
  - Resets the inactivity session timer on every button press transition.
- **Dynamic Frequency Scaling (DFS) Power Droop:**
  - Maintains 80 MHz baseline during idle and during mechanical SSD1681 `EPD_BUSY` polling.
  - Acquires 240 MHz turbo (`CpuMaxTurboScope` / `h1os_lvgl_lock`) strictly during widget tree updates and 1-bit pixel packing.
- **Mutex Safety:** Provides `h1os_lvgl_lock()` and `h1os_lvgl_unlock()` around FreeRTOS tasks.

---

## 6. Time Services: `h1os_time.c/.h`

- Automatically synchronizes PCF85063A hardware RTC time into the POSIX system clock on boot/wake via `h1os_time_sync_rtc_to_system()`.
- Provides timezone formatting (`h1os_time_set_timezone()`) and formatted time/date string helpers (`h1os_time_get_formatted()`, `h1os_time_get_date_formatted()`).
- Implements a pluggable external time sync callback:
  ```c
  typedef esp_err_t (*h1os_time_sync_cb_t)(uint32_t timeout_ms, void *user_data);
  esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data);
  esp_err_t h1os_time_sync_now(uint32_t timeout_ms);
  ```
