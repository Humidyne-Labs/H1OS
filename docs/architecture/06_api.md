# Layer 4: Application Lifecycle API & Services Specification

## 1. Overview
Layer 4 is the top-level public interface of H1OS (`h1os.h`). It isolates developers from low-level register manipulation, coprocessor details, and power sequencing by exposing:
1. **Declarative Lifecycle Engine:** `h1os_start()`, `h1os_sleep()`, `h1os_shutdown()`, and `h1os_get_telemetry()`.
2. **Interactive UI Session Engine:** LVGL v9 display driver port, keypad indev binding, 80 MHz DFS idle power droop, and 30-second inactivity sleep.
3. **System Time Services:** POSIX clock bridge, timezone formatting, and pluggable external SNTP sync callbacks.

---

## 2. Declarative Application Lifecycle Configuration

```c
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

/**
 * @brief Structured Wake Context delivered to on_wake handler
 */
typedef struct {
    esp_reset_reason_t       reset_reason;
    esp_sleep_wakeup_cause_t wake_cause;
    uint32_t                 boot_count;
    uint32_t                 deep_sleep_count;
    bool                     woke_from_button;
    uint8_t                  wake_button;
    uint32_t                 sleep_duration_sec;
    void                     *user_data;
} h1os_wake_context_t;

/**
 * @brief Presentation splash screen types
 */
typedef enum {
    H1OS_SPLASH_BOOT = 0,
    H1OS_SPLASH_WAKE,
    H1OS_SPLASH_SLEEP,
    H1OS_SPLASH_SHUTDOWN,
    H1OS_SPLASH_MAX
} h1os_splash_type_t;

/**
 * @brief Hardware acoustic chime types
 */
typedef enum {
    H1OS_CHIME_BOOT = 0,
    H1OS_CHIME_WAKE,
    H1OS_CHIME_SLEEP,
    H1OS_CHIME_SHUTDOWN,
    H1OS_CHIME_ALARM,
    H1OS_CHIME_MAX
} h1os_chime_type_t;

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
    h1os_boot_cb_t      on_boot;       ///< Cold boot / power-on reset hook
    h1os_wake_cb_t      on_wake;       ///< Interactive wake hook (Timer / RTC Alarm / Button Tap)
    h1os_pre_sleep_cb_t on_pre_sleep;  ///< Hook executed immediately prior to entering deep sleep
    h1os_shutdown_cb_t  on_shutdown;   ///< Hook executed immediately prior to battery cut

    /* Presentation Cues */
    struct {
        h1os_splash_cb_t on_splash;    ///< Custom splash rendering callback
        h1os_chime_cb_t  on_chime;     ///< Custom chime callback
        uint8_t          chime_mask;   ///< Hardware synthesized chime bitmask
    } presentation;

    /* Interactive Session Parameters */
    struct {
        uint32_t inactivity_timeout_sec; ///< Inactivity sleep timer (default: 30s)
        bool     enable_dfs_80mhz;       ///< Enable 80 MHz power droop while waiting for input (default: true)
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
- Initializes base HAL and releases RTC pad holds.
- Inspects ULP dispatch reason:
  - If `DISPATCH_BOOTLOADER_JUMP`: Jumps straight to ROM Download Bootloader.
  - If `DISPATCH_POWER_OFF`: Cuts power latch immediately.
  - If `DISPATCH_MAIN_WAKE` / Boot:
    - Launches Flow B interactive session.
    - Sets 240 MHz turbo for initial render.
    - Binds physical buttons to LVGL `lv_indev` (Keypad).
    - Dispatches to user `on_boot` or `on_wake`.
    - Manages the 30-second inactivity sleep loop with 80 MHz DFS idle power droop.

### 3.2 `h1os_sleep()`
Explicit command to enter deep sleep:
```c
esp_err_t h1os_sleep(uint32_t sleep_sec);
```
- Executes the deterministic 7-step sleep sequence via Layer 3 `orch_flow`.

### 3.3 `h1os_shutdown()`
Orderly power cut:
```c
void h1os_shutdown(void);
```
- Calls `on_shutdown()`, commits final frame, resets RTC memory, and releases `GPIO 17 (BAT_CTRL)`.

---

## 4. Telemetry Consumption API

```c
typedef struct {
    // Smoothed Ambient Readings (EWMA)
    float    ambient_temp_c;
    float    ambient_temp_f;
    float    ambient_rh_pct;
    float    dew_point_c;
    float    dew_point_f;
    float    absolute_humidity_g;

    // Multi-Node Diagnostics
    float    raw_shtc3_temp_c;
    float    mcu_die_temp_c;
    float    epd_glass_temp_c;

    // Quality & Stability Metrics
    bool     is_thermally_settled;
    uint32_t sample_count;
    uint16_t battery_mv;
    uint8_t  battery_percent;
    bool     is_usb_powered;
} h1os_telemetry_t;

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);
```
- **Thermal Lockout MUX:** If the CPU is awake and running hot, `h1os_get_telemetry()` automatically serves pristine cold baseline values from RTC memory, preventing PCB self-heating from corrupting displayed data.

---

## 5. UI Engine: `h1os_lvgl.cpp/.h` (LVGL v9 Port)

- **Monochrome Buffer:** Allocates 40-line partial render buffer in internal SRAM with 1-bit monochrome palette (Index 0 = Black, Index 1 = White).
- **Keypad Input Device (`lv_indev`):**
  - Samples `hal_io_button_is_pressed()`.
  - Sets `indev->long_press_time = 1500`.
  - Dispatches `LV_EVENT_CLICKED` on BOOT to switch between Screen 1 (Env) and Screen 2 (Health).
  - Resets the 30-second inactivity timer on every click.
- **Dynamic Frequency Scaling (DFS) Power Droop:**
  - Maintains 80 MHz baseline between user clicks.
  - Automatically raises CPU to 240 MHz during LVGL display flushes.
- **Mutex Safety:** Provides `h1os_lvgl_lock()` and `h1os_lvgl_unlock()` around FreeRTOS tasks.

---

## 6. Time Services: `h1os_time.c/.h`

- Bridges PCF85063A hardware RTC time into the POSIX system clock via `settimeofday()`.
- Provides timezone formatting (`TZ="EST5EDT,M3.2.0,M11.1.0"`).
- Implements a pluggable external SNTP sync callback:
  ```c
  typedef void (*h1os_time_sync_cb_t)(struct tm *out_time, void *user_data);
  esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data);
  ```
