# Layer 4: User Application Lifecycle API Specification

## 1. Overview
Layer 4 is the top-level user-facing interface (`bsp.h`). It provides an intuitive, declarative application framework that isolates application developers from low-level register juggling, FreeRTOS synchronization, and deep sleep state transitions.

> **Key Design Tenet:** All user interaction with the BSP happens through **declarative lifecycle configuration** and **three high-level lifecycle functions** (`bsp_app_start`, `bsp_app_sleep`, `bsp_app_shutdown`).

---

## 2. Declarative Application Lifecycle Configuration

The application configures its behavior through `bsp_app_config_t`:

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
    uint32_t                 wake_count;
    bool                     woke_from_button;
    uint8_t                  wake_button_num;
    uint32_t                 last_sleep_sec;
    void                     *user_data;
} bsp_app_wake_context_t;

/**
 * @brief Presentation splash screen types
 */
typedef enum {
    BSP_SPLASH_BOOT = 0,
    BSP_SPLASH_WAKE,
    BSP_SPLASH_SLEEP,
    BSP_SPLASH_SHUTDOWN,
    BSP_SPLASH_MAX
} bsp_splash_type_t;

/**
 * @brief Hardware acoustic chime types
 */
typedef enum {
    BSP_CHIME_BOOT = 0,
    BSP_CHIME_WAKE,
    BSP_CHIME_SLEEP,
    BSP_CHIME_SHUTDOWN,
    BSP_CHIME_ALARM,
    BSP_CHIME_MAX
} bsp_chime_type_t;

/**
 * @brief Callback Signatures
 */
typedef void (*bsp_app_boot_cb_t)     (void *user_data);
typedef void (*bsp_app_wake_cb_t)     (const bsp_app_wake_context_t *ctx, void *user_data);
typedef void (*bsp_app_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);
typedef void (*bsp_app_shutdown_cb_t) (void *user_data);
typedef void (*bsp_app_splash_cb_t)   (bsp_splash_type_t type, void *user_data);
typedef void (*bsp_app_chime_cb_t)    (bsp_chime_type_t type, void *user_data);

/**
 * @brief Master Application Lifecycle Configuration
 */
typedef struct {
    /* 1. Core Execution Hooks */
    bsp_app_boot_cb_t      on_boot;       ///< Executed on cold power-on / hardware reset
    bsp_app_wake_cb_t      on_wake;       ///< Executed on wake from deep sleep (Timer / RTC / Button)
    bsp_app_pre_sleep_cb_t on_pre_sleep;  ///< Executed immediately prior to sleep entry
    bsp_app_shutdown_cb_t  on_shutdown;   ///< Executed immediately prior to battery cut

    /* 2. Autonomous Background Sub-Execution */
    struct {
        bool     enabled;                 ///< Enable headless SHTC3 sensor acquisition during sleep
        uint32_t interval_sec;            ///< Sub-execution sampling cadence (default: 60s)
    } sub_execution;

    /* 3. Audio & Visual Presentation Cues */
    struct {
        bsp_app_splash_cb_t on_splash;    ///< Custom splash screen rendering callback
        bsp_app_chime_cb_t  on_chime;     ///< Custom chime callback (overrides hardware synthesizer)
        uint8_t             chime_mask;   ///< Default hardware synthesized beeps to play
    } presentation;

    void *user_data;                      ///< User context passed to all registered callbacks
} bsp_app_config_t;
```

---

## 3. Core Lifecycle Control APIs

### 3.1 `bsp_app_start()`
Entry point for the application, typically called from `app_main()`:
```c
esp_err_t bsp_app_start(const bsp_app_config_t *config);
```
- Initializes base hardware latch, inspects wake source.
- If deep sleep timer wake & sub-execution armed: executes **Flow A** (<10ms) and returns directly to sleep without invoking `app_main()` logic.
- If main wake / boot: executes **Flow B**, restores display state, disarms sub-execution, and dispatches to `on_boot` or `on_wake`.

---

### 3.2 `bsp_app_sleep()`
Single unified entry point for sleep:
```c
esp_err_t bsp_app_sleep(uint32_t sleep_sec);
```
- Executes the deterministic stand-down sequence:
  1. Calls user `on_pre_sleep()`.
  2. Calls `on_splash(BSP_SPLASH_SLEEP)`.
  3. Plays sleep chime.
  4. Waits for E-Paper panel to complete particle latching.
  5. Commits dirty frame to `epd_frame` partition.
  6. Configures wake sources (External RTC alarm for `sleep_sec`, internal sub-exec timer).
  7. Arms sub-execution in RTC memory if enabled.
  8. Enters deep sleep.

---

### 3.3 `bsp_app_shutdown()`
Executes an orderly board power cut:
```c
void bsp_app_shutdown(void);
```
- Calls user `on_shutdown()`.
- Renders `BSP_SPLASH_SHUTDOWN`.
- Commits final frame to flash.
- Resets RTC Slow Memory to pristine state.
- Drops power latch (`BAT_CTRL` = 0).

---

## 4. Telemetry Consumption API

Instead of forcing users to assemble readings from three different sensors and math functions, Layer 4 provides a single, unified getter:

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
    uint32_t battery_mv;
    uint8_t  battery_percent;
} bsp_app_telemetry_t;

esp_err_t bsp_app_get_telemetry(bsp_app_telemetry_t *out_telemetry);
```

---

## 5. Typical `app_main()` Example Implementation

```c
#include "bsp.h"

static void my_on_boot(void *user_data) {
    ESP_LOGI("APP", "Cold boot initialized!");
}

static void my_on_wake(const bsp_app_wake_context_t *ctx, void *user_data) {
    ESP_LOGI("APP", "Woke from sleep! Cause: %d, Cycles: %lu", ctx->wake_cause, ctx->wake_count);
    
    bsp_app_telemetry_t telem;
    if (bsp_app_get_telemetry(&telem) == ESP_OK) {
        // Render UI with telem data...
    }
    
    // Sleep for 10 minutes; sub-execution samples every 60s in background
    bsp_app_sleep(600);
}

void app_main(void) {
    bsp_app_config_t config = {
        .on_boot = my_on_boot,
        .on_wake = my_on_wake,
        .sub_execution = {
            .enabled      = true,
            .interval_sec = 60,
        },
    };
    bsp_app_start(&config);
}
```
