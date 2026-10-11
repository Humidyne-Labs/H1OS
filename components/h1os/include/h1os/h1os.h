/**
 * @file h1os.h
 * @brief H1OS: Class-E Environmental Operating System Master Public Interface
 *
 * Platform: H1OS (Humid-1 Operating System)
 * Hardware Target: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
 * Role: Luxury Hygrometer & Environmental Telemetry Executive Engine
 *
 * @version 2.0.0-dev
 * @attribution
 * - Architecture & System Design: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Platform Identity & Versioning
 * ========================================================================= */
#define H1OS_NAME               "H1OS"
#define H1OS_SUBTITLE           "Class-E Environmental Operating System"
#define H1OS_VERSION_MAJOR      2
#define H1OS_VERSION_MINOR      0
#define H1OS_VERSION_PATCH      0
#define H1OS_VERSION_TAG        "dev"
#define H1OS_VERSION_STRING     "2.0.0-dev"

/* =========================================================================
 * Lifecycle Types & Contexts
 * ========================================================================= */
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

typedef enum {
    H1OS_SPLASH_BOOT = 0,
    H1OS_SPLASH_WAKE,
    H1OS_SPLASH_SLEEP,
    H1OS_SPLASH_SHUTDOWN,
    H1OS_SPLASH_MAX
} h1os_splash_type_t;

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

typedef struct {
    /* Core Lifecycle Execution Hooks */
    h1os_boot_cb_t      on_boot;       ///< Cold boot / power-on reset hook
    h1os_wake_cb_t      on_wake;       ///< Interactive wake hook (Timer / RTC Alarm / Button Tap)
    h1os_pre_sleep_cb_t on_pre_sleep;  ///< Hook executed immediately prior to deep sleep stand-down
    h1os_shutdown_cb_t  on_shutdown;   ///< Hook executed immediately prior to battery cut

    /* Presentation Cues */
    struct {
        h1os_splash_cb_t on_splash;    ///< Custom splash rendering callback
        h1os_chime_cb_t  on_chime;     ///< Custom chime callback
        uint8_t          chime_mask;   ///< Hardware synthesized chime bitmask
    } presentation;

    /* Interactive Session Parameters */
    struct {
        uint32_t inactivity_timeout_sec; ///< Inactivity stand-down timer (default: 30s)
        bool     enable_dfs_80mhz;       ///< Enable 80 MHz power droop while waiting for input (default: true)
    } session;

    void *user_data;
} h1os_lifecycle_t;

/* =========================================================================
 * Telemetry Snapshot Structure
 * ========================================================================= */
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

/* =========================================================================
 * Master API Functions
 * ========================================================================= */

/**
 * @brief Get the H1OS semantic version string.
 */
static inline const char *h1os_get_version(void)
{
    return H1OS_VERSION_STRING;
}

/**
 * @brief Initialize H1OS and dispatch application lifecycle.
 */
esp_err_t h1os_start(const h1os_lifecycle_t *config);

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 */
esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 */
esp_err_t h1os_sleep(uint32_t sleep_sec);

/**
 * @brief Orderly system shutdown and physical battery power cut.
 */
void h1os_shutdown(void);

#ifdef __cplusplus
}
#endif
