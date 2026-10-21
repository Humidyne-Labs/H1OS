/**
 * @file h1os.h
 * @brief H1OS E-Class Environmental Telemetry OS master public API
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "hal_types.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "h1os_version.h"

/**
 * @brief Platform wakeup context descriptor.
 *
 * Populated during boot and passed to the application lifecycle on_wake hook.
 */
typedef struct {
    esp_reset_reason_t reset_reason;       /**< Hardware reset reason code.                                         */
    uint32_t wakeup_causes;                /**< Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).             */
    uint32_t boot_count;                   /**< Monotonic system boot cycle count.                                  */
    uint32_t deep_sleep_count;             /**< Monotonic deep sleep wake cycle count.                              */
    bool     woke_from_button;             /**< True if system woke due to physical button actuation.               */
    uint8_t  wake_button;                  /**< Waking button ID (h1os_wake_btn_t: 0=None, 1=BOOT, 2=POWER).        */
    uint32_t sleep_duration_sec;           /**< Configured sleep interval prior to wake in seconds.                 */
    void     *user_data;                   /**< User context pointer passed to lifecycle.                           */
} h1os_wake_context_t;

/**
 * @brief Graphical splash screen trigger types.
 */
typedef enum {
    H1OS_SPLASH_BOOT = 0, /**< Initial cold boot / power-on splash screen.        */
    H1OS_SPLASH_SLEEP,    /**< Transition to unattended deep sleep splash screen. */
    H1OS_SPLASH_SHUTDOWN, /**< Orderly physical power-down splash screen.         */
    H1OS_SPLASH_MAX       /**< Sentinel maximum splash enum value.                */
} h1os_splash_type_t;

/**
 * @brief System boot and power-on reset callback signature.
 *
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_boot_cb_t)(void *user_data);

/**
 * @brief Interactive wake callback signature (Timer / RTC Alarm / Button Tap).
 *
 * @param[in] ctx       Pointer to populated wake context struct.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_wake_cb_t)(const h1os_wake_context_t *ctx, void *user_data);

/**
 * @brief Callback executed immediately prior to entering deep sleep.
 *
 * @param[in] sleep_sec Planned sleep interval in seconds.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);

/**
 * @brief Callback executed immediately prior to battery power cut.
 *
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_shutdown_cb_t)(void *user_data);

/**
 * @brief Presentation splash screen rendering callback signature.
 *
 * @param[in] type      Type of splash screen being rendered.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_splash_cb_t)(h1os_splash_type_t type, void *user_data);

/**
 * @brief Acoustic presentation chime playback callback signature.
 *
 * @param[in] type      Type of chime pattern requested.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_chime_cb_t)(h1os_chime_type_t type, void *user_data);

/**
 * @brief Declarative application lifecycle configuration structure.
 */
typedef struct {
    h1os_boot_cb_t on_boot;           /**< System boot / power-on reset hook.                      */
    h1os_wake_cb_t on_wake;           /**< Interactive wake hook (Timer / RTC Alarm / Button Tap). */
    h1os_pre_sleep_cb_t on_pre_sleep; /**< Hook executed immediately prior to entering deep sleep. */
    h1os_shutdown_cb_t on_shutdown;   /**< Hook executed immediately prior to battery power cut.   */

    struct {
        h1os_splash_cb_t on_splash;   /**< Presentation splash screen rendering hook.     */
        h1os_chime_cb_t on_chime;     /**< Presentation chime playback hook.              */
        uint8_t chime_mask;           /**< Bitmask of enabled audio chime types.          */
        uint8_t volume_pct;           /**< Acoustic presentation master volume (0..100%). */
    } presentation;

    struct {
        uint32_t inactivity_timeout_sec; /**< Interactive session idle sleep timeout in seconds.              */
        sys_clk_mode_t clk_mode;         /**< CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default).       */
        uint32_t flow_a_period_sec;      /**< Period between headless sensor sample bursts in seconds.        */
        uint32_t flow_b_period_sec;      /**< Period between unattended display flushes in seconds.           */
    } session;

    void *user_data;                     /**< Arbitrary user context pointer passed to lifecycle hooks.       */
} h1os_lifecycle_t;

/**
 * @brief Comprehensive environmental telemetry and system metrics snapshot.
 */
typedef struct {
    float ambient_temp_c;            /**< Filtered ambient temperature in degrees Celsius.                   */
    float ambient_temp_f;            /**< Filtered ambient temperature in degrees Fahrenheit.                */
    float ambient_rh_pct;            /**< Filtered ambient relative humidity percentage (0..100%).           */
    float dew_point_c;               /**< Psychrometrically calculated dew point in degrees Celsius.         */
    float dew_point_f;               /**< Psychrometrically calculated dew point in degrees Fahrenheit.      */
    float absolute_humidity_g;       /**< Calculated absolute humidity in grams per cubic meter (g/m³).      */

    float window_low_c;              /**< Valid Window Floor (minimum over valid 32-sample window).          */
    float window_high_c;             /**< Valid Window Ceiling (maximum over valid 32-sample window).        */
    float window_avg_shtc3_c;        /**< Short-term valid SHTC3 sensor window average in degrees Celsius.   */
    float window_avg_die_c;          /**< Short-term valid MCU Die internal sensor window average.           */
    float temp_historical_c;         /**< Long-term light EWMA historical baseline temperature.              */
    float rh_historical_pct;         /**< Long-term light EWMA historical baseline relative humidity.        */

    float raw_shtc3_temp_c;          /**< Instantaneous raw Sensirion SHTC3 temperature in degrees Celsius.  */
    float mcu_die_temp_c;            /**< Instantaneous ESP32-S3 internal TSENS die temperature.             */
    float epd_glass_temp_c;          /**< Instantaneous SSD1681 display on-glass temperature sensor reading. */
    float trinode_temp_c;            /**< Tri-Node consensus temperature: (T_valid + T_die + T_glass) / 3.0. */
    float trinode_delta_c;           /**< Thermal gradient delta: T_valid - T_trinode.                       */
    uint8_t trinode_confidence_pct;  /**< 0-100% linear psychrometric confidence score.                      */

    bool is_thermally_settled;       /**< True if thermal equilibrium criteria are satisfied.                */
    uint16_t valid_trend;            /**< Monotonic count of consecutive thermally settled Flow A samples.   */
    uint32_t sample_count;           /**< Total monotonic environmental telemetry sample count.              */
    uint16_t battery_mv;             /**< Sampled battery terminal voltage in millivolts.                    */
    uint8_t battery_percent;         /**< Estimated battery state-of-charge percentage (0..100%).            */
    bool is_usb_powered;             /**< True if USB VBUS power connection is actively detected.            */
} h1os_telemetry_t;

/**
 * @brief Get the H1OS semantic version string.
 *
 * @return Null-terminated semantic version string (e.g. "2.3.2-dev").
 */
static inline const char *h1os_get_version(void)
{
    return h1os_version_get_string();
}

/**
 * @brief Initialize H1OS and dispatch application lifecycle.
 *
 * Configures hardware subsystems, determines boot/wake flow, initializes FreeRTOS
 * tasks, and dispatches the configured application lifecycle hooks.
 *
 * @param[in] config Pointer to valid lifecycle configuration structure. Must not be NULL.
 *
 * @return
 *   - ESP_OK: System initialized and lifecycle dispatched successfully.
 *   - ESP_ERR_INVALID_ARG: Null pointer provided for configuration.
 *   - ESP_FAIL: Hardware initialization failure.
 */
esp_err_t h1os_start(const h1os_lifecycle_t *config);

/**
 * @brief Set audio subsystem output volume percentage.
 *
 * Controls ES8311 DAC gain and NS4168 power state. 0% volume automatically mutes
 * the output and puts the amplifier into low-power standby.
 *
 * @param[in] volume_pct Desired volume percentage (0 = Mute, 100 = 0 dB Maximum).
 *
 * @return
 *   - ESP_OK: Volume level configured successfully.
 *   - ESP_ERR_INVALID_STATE: Audio subsystem not initialized.
 */
esp_err_t h1os_set_volume(uint8_t volume_pct);

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 *
 * Copies the latest validated psychrometric invariants, sensor readings, and battery
 * metrics into the caller-provided telemetry structure.
 *
 * @param[out] out_telemetry Pointer to destination telemetry structure. Must not be NULL.
 *
 * @return
 *   - ESP_OK: Telemetry snapshot copied successfully.
 *   - ESP_ERR_INVALID_ARG: Null pointer passed.
 */
esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 *
 * Arms the PCF85063A countdown timer, isolates GPIO sleep pads, holds power latch,
 * and enters ESP32-S3 deep sleep.
 *
 * @param[in] sleep_sec Duration of sleep in seconds before hardware wake.
 *
 * @return
 *   - ESP_OK: Sleep transition armed.
 *   - ESP_ERR_INVALID_ARG: sleep_sec out of supported hardware range.
 */
esp_err_t h1os_sleep(uint32_t sleep_sec);

/**
 * @brief Reset the interactive session inactivity timer.
 *
 * Extends the interactive user session by inactivity_timeout_sec, preventing premature
 * deep sleep while user interaction or animation is underway.
 */
void h1os_reset_session_timer(void);

/**
 * @brief Check whether an interactive inactivity countdown session is active.
 *
 * @return True if running in an interactive user session, false during unattended wakes.
 */
bool h1os_is_session_active(void);

/**
 * @brief Orderly system shutdown and physical battery power cut.
 *
 * Invokes lifecycle on_shutdown hook, safely isolates peripherals, deactivates
 * displays, and releases GPIO 17 BAT_CTRL power latch.
 */
void h1os_shutdown(void);

/**
 * @brief Shutdown for long-term storage.
 *
 * Performs pure white full OTP refresh on electrophoretic display before cutting
 * power latch, protecting e-Paper microcapsules against dye migration and burn-in.
 */
void h1os_shutdown_for_storage(void);

#ifdef __cplusplus
}
#endif
