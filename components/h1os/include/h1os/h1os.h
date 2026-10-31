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
#include "orch_state.h"
#include "sub_power.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "h1os_constants.h"
#include "h1os_version.h"

/**
 * @name Thermodynamic & Psychrometric Unit Conversion Primitives
 * @brief Base Celsius derived mathematical conversions avoiding compounding precision loss.
 * @{
 */
#define H1OS_CELSIUS_TO_KELVIN(c)      ((float)(c) + 273.15f)
#define H1OS_CELSIUS_TO_FAHRENHEIT(c)  (((float)(c) * 1.8f) + 32.0f)
/** @} */

/**
 * @name Slicing & Flow Period Boundaries
 * @brief Authoritative limits and time unit conversion primitives for Flow A and Flow B.
 * @{
 */
#define H1OS_FLOW_A_MIN_SEC         60U        /**< 1 minute minimum Flow A period.         */
#define H1OS_FLOW_A_MAX_SEC         14400U     /**< 4 hours maximum Flow A period.          */
#define H1OS_FLOW_B_MIN_SEC         300U       /**< 5 minutes minimum Flow B period.        */
#define H1OS_FLOW_B_MAX_SEC         86400U     /**< 24 hours maximum Flow B period.         */
#define H1OS_FLOW_REMAINDER_MIN_SEC 60U        /**< 60 seconds minimum remainder slice.     */

#define H1OS_MIN_TO_SEC(m)          ((uint32_t)(m) * 60U)
#define H1OS_HOURS_TO_SEC(h)        ((uint32_t)(h) * 3600U)
#define H1OS_SEC_TO_MIN(s)          ((uint32_t)(s) / 60U)
#define H1OS_SEC_TO_HOURS(s)        ((uint32_t)(s) / 3600U)
/** @} */

/**
 * @brief Default compound literal macro for standard lifecycle session configuration.
 */
#define H1OS_LIFECYCLE_DEFAULT_CONFIG()                                    \
    {                                                                      \
        .session = {                                                       \
            .inactivity_timeout_sec = H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC, \
            .clk_mode = SYS_CLK_MODE_DYNAMIC,                              \
            .flow_a_period_sec = H1OS_DEFAULT_FLOW_A_PERIOD_SEC,           \
            .flow_b_period_sec = H1OS_DEFAULT_FLOW_B_PERIOD_SEC,           \
            .sync_wait_ms = 0U,                                            \
            .sync_timeout_ms = 5000U,                                      \
        },                                                                 \
        .presentation = { 0 }                                              \
    }

/**
 * @brief High-level application wake state classification (MANDATE-04).
 */
typedef enum {
    H1OS_WAKE_STATE_BOOT                = 0, /**< Cold boot / power-on reset cycle.                          */
    H1OS_WAKE_STATE_INTERACTIVE_SESSION = 1, /**< User tactile button wake into interactive UI session.      */
    H1OS_WAKE_STATE_RTC_FLOW_B          = 2  /**< Unattended periodic RTC countdown Flow B refresh & sync.   */
} h1os_wake_state_t;

/**
 * @brief Platform wakeup context descriptor.
 *
 * Populated during boot and passed to the application lifecycle on_wake and on_sync hooks.
 */
typedef struct {
    esp_reset_reason_t reset_reason; /**< Hardware reset reason code.                                         */
    uint32_t wakeup_causes;          /**< Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).             */
    h1os_wake_state_t wake_state;    /**< Explicit wake state classification (BOOT, INTERACTIVE, RTC_FLOW_B). */
    uint32_t boot_count;             /**< Monotonic system boot cycle count.                                  */
    uint32_t deep_sleep_count;       /**< Monotonic total deep sleep wake cycle count (Flow A + Flow B).      */
    uint32_t flow_b_count;           /**< Monotonic unattended RTC Flow B presentation wake cycle count.      */
    uint32_t button_wake_count;      /**< Monotonic interactive tactile button wake cycle count.              */
    bool woke_from_button;           /**< True if system woke due to physical button actuation.               */
    uint8_t wake_button;             /**< Waking button ID (h1os_wake_btn_t: 0=None, 1=BOOT, 2=POWER).        */
    uint32_t sleep_duration_sec;     /**< Configured sleep interval prior to wake in seconds.                 */
    void *user_data;                 /**< User context pointer passed to lifecycle.                           */
} h1os_wake_context_t;

/**
 * @brief Graphical splash screen trigger types.
 */
typedef enum {
    H1OS_SPLASH_BOOT = 0,   /**< Initial cold boot / power-on splash screen.        */
    H1OS_SPLASH_SLEEP,      /**< Transition to unattended deep sleep splash screen. */
    H1OS_SPLASH_SHUTDOWN,   /**< Orderly physical power-down splash screen.         */
    H1OS_SPLASH_MAX         /**< Maximum splash enum value.                         */
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
 * @brief Parallel data synchronization callback signature (MANDATE-04).
 *
 * @details Invoked on Core 0 after Core 1 LVGL task startup so network/bus I/O
 *          overlaps in parallel with physical SSD1681 display refresh.
 *
 * @param[in] ctx       Pointer to populated wake context struct.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_sync_cb_t)(const h1os_wake_context_t *ctx, void *user_data);

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
 * @brief Fatal startup or lifecycle error callback signature (MANDATE-06).
 *
 * @param[in] err       Error code that triggered the fatal condition.
 * @param[in] context   Null-terminated diagnostic string identifying the failing stage.
 * @param[in] user_data User context pointer configured in h1os_lifecycle_t.
 */
typedef void (*h1os_error_cb_t)(esp_err_t err, const char *context, void *user_data);

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
    h1os_sync_cb_t on_sync;           /**< Optional parallel network/storage sync hook on Core 0.  */
    h1os_pre_sleep_cb_t on_pre_sleep; /**< Hook executed immediately prior to entering deep sleep. */
    h1os_shutdown_cb_t on_shutdown;   /**< Hook executed immediately prior to battery power cut.   */
    h1os_error_cb_t on_error;         /**< Optional fatal startup/lifecycle error hook.            */

    struct {
        h1os_splash_cb_t on_splash; /**< Presentation splash screen rendering hook.     */
        h1os_chime_cb_t on_chime;   /**< Presentation chime playback hook.              */
        uint8_t chime_mask;         /**< Bitmask of enabled audio chime types.          */
        uint8_t volume_pct;         /**< Acoustic presentation master volume (0..100%). */
    } presentation;

    struct {
        uint32_t inactivity_timeout_sec; /**< Interactive session idle sleep timeout in seconds.              */
        sys_clk_mode_t clk_mode;         /**< CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default).       */
        uint32_t flow_a_period_sec;      /**< Period between headless sensor sample bursts in seconds.        */
        uint32_t flow_b_period_sec;      /**< Period between unattended display flushes in seconds.           */
        uint32_t sync_wait_ms;           /**< Inbound sync pre-flush gate window in ms (0 = immediate flush). */
        uint32_t sync_timeout_ms;        /**< Max barrier wait for async on_sync completion before sleep.     */
    } session;

    void *user_data; /**< Arbitrary user context pointer passed to lifecycle hooks.       */
} h1os_lifecycle_t;

/**
 * @brief Comprehensive environmental telemetry and system metrics snapshot.
 */
typedef struct {
    float ambient_temp_c;           /**< Trusted steady-state SHTC3 ambient temperature in degrees Celsius.  */
    float ambient_temp_f;           /**< Trusted steady-state SHTC3 ambient temperature in degrees Fahr.     */
    float ambient_temp_k;           /**< Trusted steady-state SHTC3 ambient temperature in Kelvin (derived). */
    float ambient_rh_pct;           /**< Trusted steady-state SHTC3 relative humidity percentage (0..100%).  */
    float dew_point_c;              /**< Psychrometrically calculated dew point in degrees Celsius.          */
    float dew_point_f;              /**< Psychrometrically calculated dew point in degrees Fahrenheit.       */
    float dew_point_k;              /**< Psychrometrically calculated dew point in Kelvin (derived).         */
    float vapor_pressure_hpa;       /**< Calculated water vapor partial pressure in hectopascals (hPa).      */
    float absolute_humidity_g;      /**< Calculated absolute humidity in grams per cubic meter (g/m³).       */

    float window_low_c;             /**< Valid Window Floor (minimum over valid 32-sample window).           */
    float window_high_c;            /**< Valid Window Ceiling (maximum over valid 32-sample window).         */
    float window_avg_shtc3_c;       /**< Short-term valid SHTC3 sensor window average in degrees Celsius.    */
    float window_avg_die_c;         /**< Short-term valid MCU Die internal sensor window average.            */
    float temp_historical_c;        /**< Long-term light EWMA historical baseline temperature.               */
    float rh_historical_pct;        /**< Long-term light EWMA historical baseline relative humidity.         */

    float raw_shtc3_temp_c;         /**< Instantaneous raw Sensirion SHTC3 temperature in degrees Celsius.   */
    float mcu_die_temp_c;           /**< Instantaneous ESP32-S3 internal TSENS die temperature.              */
    float epd_glass_temp_c;         /**< Instantaneous SSD1681 display on-glass temperature sensor reading.  */
    float trinode_temp_c;           /**< Tri-Node verification consensus: (T_valid + T_die + T_glass) / 3.0. */
    float trinode_delta_c;          /**< Cross-node verification delta: T_valid - T_trinode.                 */
    uint8_t trinode_confidence_pct; /**< 0-100% cross-node range verification confidence score.              */

    bool is_thermally_settled;          /**< True if steady-state thermal criteria (|T2-T1| <= gate) are met.   */
    uint16_t valid_trend;               /**< Monotonic count of consecutive thermally settled Flow A samples.   */
    uint32_t sample_count;              /**< Total monotonic environmental telemetry sample count.              */
    uint32_t boot_count;                /**< Total monotonic system boot cycles.                                */
    uint32_t wake_count;                /**< Total monotonic deep sleep wake cycles (Flow A + Flow B + Button). */
    uint32_t flow_b_count;              /**< Monotonic unattended RTC Flow B presentation wake cycles.          */
    uint32_t button_wake_count;         /**< Monotonic interactive tactile button wake cycles.                  */
    uint8_t ulp_dispatch_reason;        /**< Reason code from last ULP coprocessor dispatch.                    */
    uint32_t flow_a_period_sec;         /**< Active Flow A sensor sample interval in seconds.                   */
    uint32_t flow_b_period_sec;         /**< Active Flow B display refresh interval in seconds.                 */
    uint16_t battery_mv;                /**< Sampled battery terminal voltage in millivolts.                    */
    uint16_t boot_vbat_mv;              /**< Initial non-USB battery voltage captured on boot in millivolts.    */
    uint8_t battery_percent;            /**< Estimated battery state-of-charge percentage (0..100%).            */
    bool is_usb_powered;                /**< True if USB VBUS power connection is actively detected.            */
    h1os_battery_state_t battery_state; /**< Charge / discharge / charged operational state.                    */
    h1os_autonomy_metrics_t autonomy;   /**< Empirical battery autonomy metrics over total elapsed runtime.     */
    uint32_t sensor_fail_count;         /**< Total count of failed wake-stub sensor sample attempts.            */
    uint8_t last_sensor_error;          /**< Most recent sensor error enum code (orch_sensor_err_t).            */
    bool is_rh_alert_active;            /**< True if settled RH is outside configured humidor target bounds.    */
} h1os_telemetry_t;

/**
 * @brief Get the H1OS semantic version string.
 *
 * @return Null-terminated semantic version string (e.g. "2.4.7-dev").
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
 * @brief Dynamically configure Flow A and Flow B sleep intervals at runtime.
 *
 * Enforces all silicon constraints, ordering invariants, and remainder slice floors.
 * Updates active RTC Slow Memory state and immediately arms the hardware RTC countdown
 * timer with the new Flow A period.
 *
 * @param[in] flow_a_sec Headless sensor acquisition interval (60s .. 14400s / 4h).
 *                       Must be an exact multiple of 60 seconds if > 255s.
 * @param[in] flow_b_sec Display refresh and network wake interval (300s .. 86400s / 24h).
 *                       Must be strictly greater than flow_a_sec.
 *                       Any remainder (flow_b_sec % flow_a_sec) must be >= 60 seconds.
 *
 * @return
 *   - ESP_OK: Flow periods validated, committed to RTC Slow Memory, and hardware timer armed.
 *   - ESP_ERR_INVALID_ARG: Any boundary, prescaler, ordering, or remainder invariant violated.
 */
esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec);

/**
 * @brief Hold the deep-sleep barrier open for an asynchronous synchronization task.
 *
 * @details When called inside on_sync(), prevents unattended RTC Flow B wakes from entering
 *          deep sleep when on_sync() returns, deferring sleep until h1os_sync_notify_complete()
 *          is called or session.sync_timeout_ms expires.
 */
void h1os_sync_hold(void);

/**
 * @brief Signal that Core 0 data synchronization is complete (`BARRIER_SYNC_DONE`).
 *
 * @details Releases the pre-flush inbound sync gate (if `session.sync_wait_ms > 0`) so Core 1
 *          flushes any queued UI updates in a single physical refresh, and satisfies the sync
 *          half of the deep-sleep barrier.
 */
void h1os_sync_notify_complete(void);

/**
 * @brief Signal that the Core 1 LVGL / SSD1681 display pipeline is quiescent (`BARRIER_DISPLAY_DONE`).
 */
void h1os_display_notify_quiescent(void);

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
 * @brief Retrieve historical Tri-Node telemetry samples from the RTC Slow SRAM ring buffer in chronological order.
 *
 * Designed for batch wireless telemetry publishing (Wi-Fi MQTT / BLE GATT) and local SD card logging
 * without exposing Layer 3 internal structures to the application layer.
 *
 * @param[out] out_samples  Destination array of orch_tri_node_sample_t elements. Must not be NULL.
 * @param[in]  max_samples  Maximum capacity of out_samples array (up to ORCH_RING_CAPACITY = 32).
 * @param[out] out_count    Number of valid chronological samples copied into out_samples. Must not be NULL.
 *
 * @return
 *   - ESP_OK: Historical samples copied in oldest-to-newest chronological order.
 *   - ESP_ERR_INVALID_ARG: Null pointer or zero capacity passed.
 */
esp_err_t h1os_get_telemetry_history(orch_tri_node_sample_t *out_samples, size_t max_samples, size_t *out_count);

/**
 * @brief Configure relative humidity target alert thresholds in centi-percent (1% = 100, e.g. 6200..7200).
 *
 * Persisted in RTC Slow SRAM so humidor out-of-bounds excursions are evaluated deterministically across
 * deep sleep cycles (set both to 0 to disable alert evaluation).
 *
 * @param[in] rh_low_centi_pct  Lower relative humidity alert threshold in centi-% (0..10000).
 * @param[in] rh_high_centi_pct Upper relative humidity alert threshold in centi-% (0..10000).
 *
 * @return
 *   - ESP_OK: Alert bounds configured successfully.
 *   - ESP_ERR_INVALID_ARG: Invalid range (low > high or > 10000).
 */
esp_err_t h1os_set_rh_alert_bounds(uint16_t rh_low_centi_pct, uint16_t rh_high_centi_pct);

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

/**
 * @brief Force a driver-level electrophoretic display clear and full waveform scrub.
 *
 * @note This is a hardware driver-level operation on the SSD1681 controller (not an LVGL widget call).
 *       It writes pure white (0xFF) to both black/white and red RAM planes, triggers a full OTP waveform
 *       refresh cycle (~2.5s), waits for hardware BUSY de-assertion, and resets the partial refresh counter.
 *       Use to eliminate electrophoretic microcapsule ghosting or initialize the panel.
 *
 * @return ESP_OK on success, or an error code from the display driver.
 */
esp_err_t h1os_display_force_clear(void);

/**
 * @brief Play raw 16-bit signed Mono PCM audio asynchronously from memory (C header arrays or RAM buffer).
 *
 * @param[in]  ptr           Pointer to 16-bit signed PCM buffer in Flash or RAM. Must not be NULL.
 * @param[in]  len           Length of sample buffer in bytes.
 * @param[out] bytes_written Pointer to receive count of bytes queued. Can be NULL.
 * @return ESP_OK on success, ESP_ERR_INVALID_ARG on NULL ptr, or I2S/DMA driver error code.
 */
esp_err_t h1os_audio_play_raw(const int16_t *ptr, size_t len, size_t *bytes_written);

/**
 * @brief Synthesize and play a pure sine tone asynchronously at specified frequency and duration.
 *
 * @param[in] freq_hz     Tone frequency in Hertz (100..10000 Hz).
 * @param[in] duration_ms Tone duration in milliseconds (10..5000 ms).
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t h1os_audio_play_tone(uint32_t freq_hz, uint32_t duration_ms);

/**
 * @brief Play a predefined acoustic presentation chime asynchronously.
 *
 * @param[in] chime_type Predefined chime pattern (H1OS_CHIME_BOOT, H1OS_CHIME_SLEEP, etc.).
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t h1os_audio_play_chime(h1os_chime_type_t chime_type);

/**
 * @brief Check if a MicroSD card is actively mounted in the FATFS filesystem.
 *
 * @return true if mounted and ready for file I/O, false otherwise.
 */
bool h1os_sdcard_is_mounted(void);

/**
 * @brief Retrieve total capacity of the mounted MicroSD card in megabytes.
 *
 * @param[out] out_capacity_mb Pointer to receive card capacity in megabytes (MB).
 * @return ESP_OK on success, ESP_ERR_INVALID_STATE if card is not mounted, or ESP_ERR_INVALID_ARG.
 */
esp_err_t h1os_sdcard_get_capacity_mb(uint32_t *out_capacity_mb);

/**
 * @brief Asynchronously mount the MicroSD card in a background FreeRTOS task.
 *
 * @return ESP_OK if already mounted or mount task dispatched successfully.
 */
esp_err_t h1os_sdcard_mount_async(void);

/**
 * @brief Unmount the MicroSD card and release SDMMC host peripheral resources.
 *
 * @return ESP_OK on success.
 */
esp_err_t h1os_sdcard_unmount(void);

/**
 * @brief Start non-blocking hardware LEDC fade breathing effect on the status LED (GPIO 3).
 *
 * @param[in] period_ms Full breathing cycle period in milliseconds (e.g. 2000 ms).
 */
void h1os_led_start_breathing(uint32_t period_ms);

/**
 * @brief Stop the status LED breathing effect and turn the LED off.
 */
void h1os_led_stop_breathing(void);

/**
 * @brief Set the status LED static state (true = ON, false = OFF).
 *
 * @param[in] on True to illuminate LED, false to turn off.
 */
void h1os_led_set(bool on);

#ifdef __cplusplus
}
#endif
