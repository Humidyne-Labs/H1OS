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
 * @brief Explicit Wake State Classification (v2.4.5-dev / MANDATE-04)
 */
typedef enum {
    H1OS_WAKE_STATE_BOOT = 0,            ///< Cold power-on reset
    H1OS_WAKE_STATE_INTERACTIVE_SESSION, ///< Tactile button wake (interactive session)
    H1OS_WAKE_STATE_RTC_FLOW_B           ///< Periodic headless Flow B wake (sync + EPD refresh)
} h1os_wake_state_t;

/**
 * @brief Structured Wake Context delivered to on_wake and on_sync handlers
 */
typedef struct {
    esp_reset_reason_t reset_reason;
    uint32_t           wakeup_causes;      ///< Bitmap of wakeup sources (esp_sleep_get_wakeup_causes)
    uint32_t           boot_count;         ///< Monotonic cold-boot counter
    uint32_t           wake_count;         ///< Monotonic total deep-sleep wake counter
    uint32_t           flow_b_count;       ///< Monotonic Flow B application wake counter
    uint32_t           button_wake_count;  ///< Monotonic tactile button wake counter
    h1os_wake_state_t  wake_state;         ///< Explicit wake state classification
    uint8_t            ulp_dispatch_reason;///< orch_ulp_dispatch_t reason code
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
typedef void (*h1os_sync_cb_t)     (const h1os_wake_context_t *ctx, void *user_data);
typedef void (*h1os_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);
typedef void (*h1os_shutdown_cb_t) (void *user_data);
typedef void (*h1os_error_cb_t)    (esp_err_t err, const char *stage, void *user_data);
typedef void (*h1os_splash_cb_t)   (h1os_splash_type_t type, void *user_data);
typedef void (*h1os_chime_cb_t)    (h1os_chime_type_t type, void *user_data);

/**
 * @brief Master Application Lifecycle Configuration
 */
typedef struct {
    /* Core Execution Hooks */
    h1os_boot_cb_t      on_boot;       ///< System boot / power-on reset hook
    h1os_wake_cb_t      on_wake;       ///< Wake hook (executed before Core 1 LVGL starts)
    h1os_sync_cb_t      on_sync;       ///< Parallel Core 0 sync hook (runs alongside Core 1 EPD refresh)
    h1os_pre_sleep_cb_t on_pre_sleep;  ///< Hook executed immediately prior to entering deep sleep
    h1os_shutdown_cb_t  on_shutdown;   ///< Hook executed immediately prior to battery cut
    h1os_error_cb_t     on_error;      ///< Fatal startup error callback prior to battery latch release

    /* Presentation Cues */
    struct {
        h1os_splash_cb_t on_splash;    ///< Custom splash rendering callback
        h1os_chime_cb_t  on_chime;     ///< Custom chime callback
        uint8_t          chime_mask;   ///< Hardware synthesized chime bitmask
        uint8_t          volume_pct;   ///< Acoustic presentation master volume (0..100%)
    } presentation;

    /* Interactive Session & Concurrency Parameters */
    struct {
        uint32_t       inactivity_timeout_sec; ///< Inactivity sleep timer (e.g. 30s)
        sys_clk_mode_t clk_mode;               ///< CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default)
        uint32_t       flow_a_period_sec;      ///< Flow A headless sensor sample burst interval (e.g. 60s)
        uint32_t       flow_b_period_sec;      ///< Flow B main application wake interval (e.g. 300s)
        uint32_t       sync_wait_ms;           ///< Max pre-flush wait (ms) to coalesce inbound sync data
        uint32_t       sync_timeout_ms;        ///< Max sleep barrier wait (ms) for async on_sync completion
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
    - Invokes `on_wake()` (while Core 1 is still stopped), arms the optional inbound pre-flush gate (`h1os_lvgl_set_sync_gate(sync_wait_ms)`), starts Core 1 LVGL task (`h1os_lvgl_start(5, 1)`), and dispatches `on_sync()` on Core 0 in parallel with Core 1's e-Paper refresh.
    - On headless RTC wakes (`H1OS_WAKE_STATE_RTC_FLOW_B`), blocks on the static `EventGroup` sleep barrier (`BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`) and immediately enters deep sleep; on interactive button wakes (`H1OS_WAKE_STATE_INTERACTIVE_SESSION`), arms the one-shot `esp_timer` inactivity timer (`s_session_timer`).

### 3.2 `h1os_set_flow_periods()`
Dynamically update Flow A (headless sample) and Flow B (display/cloud wake) intervals at runtime:
```c
esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec);
```
- **Authoritative Constants & Range:**
  - `H1OS_FLOW_A_MIN_SEC` ($60\text{s}$) .. `H1OS_FLOW_A_MAX_SEC` ($14,400\text{s}$ / $4\text{ hours}$).
  - `H1OS_FLOW_B_MIN_SEC` ($300\text{s}$ / $5\text{ min}$) .. `H1OS_FLOW_B_MAX_SEC` ($86,400\text{s}$ / $24\text{ hours}$).
  - `H1OS_FLOW_REMAINDER_MIN_SEC` ($60\text{s}$ minimum overlap remainder floor).
- **Conversion Macros:** `H1OS_MIN_TO_SEC(m)`, `H1OS_HOURS_TO_SEC(h)`, `H1OS_SEC_TO_MIN(s)`, `H1OS_SEC_TO_HOURS(s)`.
- **Validation Law:** Fails immediately with `ESP_ERR_INVALID_ARG` if out of bounds, if prescaler is unaligned ($> 255\text{s}$ not divisible by 60), if $B \le A$, or if $\text{remainder} > 0 \land \text{remainder} < 60\text{s}$.
- Both `h1os_start()` and `h1os_set_flow_periods()` funnel through `h1os_validate_flow_periods()` and `h1os_apply_flow_periods()`. On cold boot, validation executes before `orch_flow_init()` and application executes *after* `orch_state_reset()` so configured periods are never overwritten by default state initialization (`REV-01`).

### 3.3 `h1os_sleep()`
Explicit command to enter deep sleep:
```c
esp_err_t h1os_sleep(uint32_t sleep_sec);
```
- Invokes `on_pre_sleep()`, drains and stops the Core 1 LVGL task (`h1os_quiesce_lvgl_pipeline()`), and executes `orch_flow_transition_to_sleep(sleep_sec)`.

### 3.4 `h1os_shutdown()` & `h1os_shutdown_for_storage()`
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
    float ambient_temp_k;
    float ambient_rh_pct;
    float dew_point_c;
    float dew_point_f;
    float dew_point_k;
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
    uint32_t                boot_count;
    uint32_t                wake_count;
    uint32_t                flow_b_count;
    uint32_t                button_wake_count;
    uint8_t                 ulp_dispatch_reason;
    uint32_t                sample_count;
    uint32_t                flow_a_period_sec;
    uint32_t                flow_b_period_sec;
    uint16_t                battery_mv;
    uint16_t                boot_vbat_mv;
    uint8_t                 battery_percent;
    bool                    is_usb_powered;
    h1os_battery_state_t    battery_state;
    h1os_autonomy_metrics_t autonomy;
    uint32_t                sensor_fail_count;
    uint8_t                 last_sensor_error;
    bool                    is_rh_alert_active;
} h1os_telemetry_t;

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);
esp_err_t h1os_get_telemetry_history(orch_tri_node_sample_t *out_samples, size_t max_samples, size_t *out_count);
esp_err_t h1os_set_rh_alert_bounds(uint16_t rh_low_centi_pct, uint16_t rh_high_centi_pct);
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
  - Maintains 80 MHz baseline during idle and during `GPIO 8` (`EPD_BUSY`) falling-edge interrupt semaphore waits (`sub_display_wait_busy()`).
  - Acquires 240 MHz turbo (`CpuMaxTurboScope`) strictly during widget tree rendering, 1-bit pixel packing, and SPI DMA transfer.
- **Cross-Core Actor Queue & Mutex Safety (`MANDATE-04` / `REV-02`):**
  - Provides `h1os_ui_post(h1os_ui_fn_t fn, void *arg, uint32_t timeout_ms)` backed by a 16-slot static FreeRTOS queue (`xQueueCreateStatic`) that wakes Core 1 via `xTaskNotifyGive()` and drains all queued callbacks inside `h1os_lvgl_lock(100)` immediately prior to `lv_timer_handler()`.
  - Provides recursive mutex guards `h1os_lvgl_lock(uint32_t timeout_ms)` and `h1os_lvgl_unlock()`, plus inbound single-refresh gate controls (`h1os_lvgl_set_sync_gate()`, `h1os_lvgl_release_sync_gate()`).

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
