/**
 * @file h1os.h
 * @brief H1OS: E-Class Environmental Operating System Master Public Interface
 *
 * Platform: H1OS (Humid-1 Operating System)
 * Hardware Target: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
 * Role: E-Class Environmental Telemetry Executive Engine
 *
 * @version 2.0.0-dev
 * @par Attribution:
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
#define H1OS_SUBTITLE           "E-Class Environmental Operating System"
#define H1OS_VERSION_MAJOR       2
#define H1OS_VERSION_MINOR       0
#define H1OS_VERSION_PATCH       0
#define H1OS_VERSION_TAG        "dev"
#define H1OS_VERSION_STRING     "2.0.0-dev"

/* =========================================================================
 * Lifecycle Types & Contexts
 * ========================================================================= */
typedef struct {
    esp_reset_reason_t       reset_reason;       ///< Reset reason
    uint32_t                 wakeup_causes;      ///< Bitmap of wakeup sources (esp_sleep_get_wakeup_causes)
    uint32_t                 boot_count;         ///< Boot count
    uint32_t                 deep_sleep_count;   ///< Deep sleep count
    bool                     woke_from_button;   ///< Woke from button
    uint8_t                  wake_button;        ///< Wake button GPIO
    uint32_t                 sleep_duration_sec; ///< Sleep duration in seconds
    void                     *user_data;         ///< User data
} h1os_wake_context_t;

/** @brief Splash screens */
typedef enum {
    H1OS_SPLASH_BOOT = 0, ///< Boot
    H1OS_SPLASH_SLEEP,    ///< Sleep
    H1OS_SPLASH_SHUTDOWN, ///< Shutdown
    H1OS_SPLASH_MAX       ///< Max
} h1os_splash_type_t;

/** @brief Chime Types */
typedef enum {
    H1OS_CHIME_BOOT = 0,  ///< Boot
    H1OS_CHIME_SLEEP,     ///< Sleep
    H1OS_CHIME_SHUTDOWN,  ///< Shutdown
    H1OS_CHIME_ALARM,     ///< Alarm
    H1OS_CHIME_MAX        ///< Max
} h1os_chime_type_t;

typedef void (*h1os_boot_cb_t)     (void *user_data);
typedef void (*h1os_wake_cb_t)     (const h1os_wake_context_t *ctx, void *user_data);
typedef void (*h1os_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);
typedef void (*h1os_shutdown_cb_t) (void *user_data);
typedef void (*h1os_splash_cb_t)   (h1os_splash_type_t type, void *user_data);
typedef void (*h1os_chime_cb_t)    (h1os_chime_type_t type, void *user_data);

typedef struct {
    /* Core Lifecycle Execution Hooks */
    h1os_boot_cb_t      on_boot;       ///< System boot / power-on reset hook
    h1os_wake_cb_t      on_wake;       ///< Interactive wake hook (Timer / RTC Alarm / Button Tap)
    h1os_pre_sleep_cb_t on_pre_sleep;  ///< Hook executed immediately prior to entering deep sleep
    h1os_shutdown_cb_t  on_shutdown;   ///< Hook executed immediately prior to battery cut

    /* Presentation Cues */
    struct {
        h1os_splash_cb_t on_splash;    ///< Custom splash rendering callback
        h1os_chime_cb_t  on_chime;     ///< Custom chime callback
        uint8_t          chime_mask;   ///< Hardware synthesized chime bitmask
        uint8_t          volume_pct;   ///< Initial audio output volume (0 - 100%, default 60% if 0)
    } presentation;

    /* Interactive Session Parameters */
    struct {
        uint32_t inactivity_timeout_sec; ///< Inactivity sleep timer (default: 30s)
        bool     enable_dfs_80mhz;       ///< Enable 80 MHz power droop while waiting for input (default: true)
        uint32_t flow_a_period_sec;      ///< Flow A headless sensor sample burst interval (default: 60s)
        uint32_t flow_b_period_sec;      ///< Flow B main application wake interval (default: 120s)
    } session;

    void *user_data;
} h1os_lifecycle_t;

/* =========================================================================
 * Telemetry Snapshot Structure
 * ========================================================================= */
typedef struct {
    // Active Ambient & Psychrometric Readings (Current Valid Sample or Promoted Reference)
    float    ambient_temp_c;          ///< Ambient temp C
    float    ambient_temp_f;          ///< Ambient temp F
    float    ambient_rh_pct;          ///< Ambient RH %
    float    dew_point_c;             ///< Dew point C
    float    dew_point_f;             ///< Dew point F
    float    absolute_humidity_g;     ///< Absolute humidity g

    // Three-Tier Temporal Hierarchy Metrics
    float    window_low_c;            ///< Valid Window Floor (min over valid 32-sample window)
    float    window_high_c;           ///< Valid Window Ceiling (max over valid 32-sample window)
    float    window_avg_shtc3_c;      ///< Short-term valid SHTC3 window average
    float    window_avg_die_c;        ///< Short-term valid MCU Die window average
    float    temp_historical_c;       ///< Long-term light EWMA temperature history
    float    rh_historical_pct;       ///< Long-term light EWMA relative humidity history

    // Multi-Node & Tri-Node Confidence Diagnostics
    float    raw_shtc3_temp_c;        ///< Raw SHTC3 temp C
    float    mcu_die_temp_c;          ///< MCU die temp C
    float    epd_glass_temp_c;        ///< EPD glass temp C
    float    trinode_temp_c;          ///< (T_valid + T_die + T_glass) / 3.0
    float    trinode_delta_c;         ///< T_valid - T_trinode
    uint8_t  trinode_confidence_pct;  ///< 0-100% linear confidence score

    // Quality & Stability Metrics
    bool     is_thermally_settled;    ///< Is thermally settled
    uint16_t valid_trend;             ///< Consecutive thermally settled Flow A samples
    uint32_t sample_count;            ///< Sample count
    uint16_t battery_mv;              ///< Battery mV
    uint8_t  battery_percent;         ///< Battery percent
    bool     is_usb_powered;          ///< Is USB powered
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
 * @brief Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).
 */
esp_err_t h1os_set_volume(uint8_t volume_pct);

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 */
esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 */
esp_err_t h1os_sleep(uint32_t sleep_sec);

/**
 * @brief Reset the interactive session inactivity timer (extends session by timeout_sec).
 */
void h1os_reset_session_timer(void);

/**
 * @brief Check whether an interactive inactivity countdown session is active.
 *
 * @return true if running in an interactive user session, false during unattended wakes.
 */
bool h1os_is_session_active(void);

/**
 * @brief Orderly system shutdown and physical battery power cut.
 */
void h1os_shutdown(void);

/**
 * @brief Shutdown for long-term storage: clears display to pure white before cutting power.
 * Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.
 */
void h1os_shutdown_for_storage(void);

#ifdef __cplusplus
}
#endif
