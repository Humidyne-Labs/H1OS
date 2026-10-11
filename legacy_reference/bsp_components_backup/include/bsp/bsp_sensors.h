/**
 * @file bsp_sensors.h
 * @brief Sensirion SHTC3 High-Precision I2C Environmental Sensor & Tri-Node Psychrometric Engine Driver
 *
 * Hardware Target:
 *  - Primary Sensor: Sensirion SHTC3 (I2C address: 0x70)
 *  - Die Temperature: ESP32-S3 Internal TSENS Macro
 *  - Substrate Temperature: SSD1681 EPD On-Glass Sensor (SPI 0x1B)
 *
 * Features:
 *  - NIST-traceable SHTC3 reads with CRC-8 validation.
 *  - Tri-Node Sensing (SHTC3 PCB, ESP32-S3 Die, SSD1681 Glass).
 *  - Psychrometric Engine: Invariant Water Vapor Pressure, True Invariant Dew Point,
 *    Reconstructed Ambient Relative Humidity, Absolute Humidity (g/m³).
 *  - Sliding-Window Ambient Floor Tracking & EWMA smoothing.
 *  - Thermal Lockout MUX Gatekeeper to eliminate PCB self-heating bias.
 *  - Native support for both US/Imperial (°F) and SI (°C / K) units.
 *
 * IMPORTANT DEVELOPER NOTICE - SHTC3 THERMAL PHYSICS & ARCHITECTURE:
 *  - PCB Self-Heating: The onboard Sensirion SHTC3 sensor is situated on the shared
 *    ground copper plane directly adjacent to the ESP32-S3 SoC, onboard 3.3V LDO, and
 *    display boost circuit. During active CPU run time, display EPD refresh, and Wi-Fi
 *    transmissions, board dissipation causes localized copper plane heating (+1.5°C to +3.0°C),
 *    which artificially lowers the raw relative humidity reading.
 *  - Autonomous 60s Hot-Wake Sprints: The BSP internalizes a 60-second headless sprint
 *    in bsp_app_start(). The MCU wakes from deep sleep at 80 MHz, captures NIST samples
 *    in <15 ms before any thermal gradient can develop, commits them to the RTC Slow
 *    Memory ring buffer (bsp_env_telemetry_history_t), and returns to deep sleep.
 *  - Tri-Node Psychrometric Compensation: Applications running full UI refresh cycles
 *    should invoke bsp_sensors_read_tri_node(), which correlates MCU Die TSENS, EPD Glass,
 *    and SHTC3 to mathematically compute invariant water vapor pressure (e) and dew point (Tdp),
 *    reconstructing true ambient temperature and relative humidity with dynamic confidence scoring.
 *
 * @version 1.2.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Peripheral Driver Basis: Waveshare Electronics SHTC3 Sensor Code & Datasheet
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BSP_SENSORS_H
#define BSP_SENSORS_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "bsp/bsp_env_telemetry.h"
#include "bsp/bsp_equ_math.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Comprehensive Class-E Environmental Telemetry & Dynamic Sliding Window Data
 */
typedef struct {
    // 1. Reconstructed True Ambient Temperature (Fixed, EWMA Smoothed)
    float temperature_c;            ///< Ambient Temperature in Celsius (°C)
    float temperature_f;            ///< Ambient Temperature in Fahrenheit (°F)
    float temperature_k;            ///< Ambient Temperature in Kelvin (K) - Cloud Target

    // 2. Reconstructed True Ambient Relative Humidity (Fixed, EWMA Smoothed)
    float humidity_percent;         ///< Ambient Relative Humidity (% RH)

    // 3. Physical Invariant Dew Point
    float dew_point_c;              ///< True Invariant Dew Point (°C)
    float dew_point_f;              ///< True Invariant Dew Point (°F)
    float dew_point_k;              ///< True Invariant Dew Point in Kelvin (K)

    // 4. Physical Invariant Absolute Humidity
    float absolute_humidity_g;      ///< Absolute Humidity (g/m³)

    // 5. 64-Slot Sliding Window Dynamics (Calculated over Clean Settled Slots)
    float sliding_temp_avg_c;       ///< Window Mean Temperature (°C)
    float sliding_temp_avg_f;       ///< Window Mean Temperature (°F)
    float sliding_temp_floor_c;     ///< Baseline Ambient Floor Temperature (°C)
    float sliding_temp_floor_f;     ///< Baseline Ambient Floor Temperature (°F)
    float sliding_temp_ceiling_c;   ///< Thermal Ceiling Temperature (°C)
    float sliding_temp_ceiling_f;   ///< Thermal Ceiling Temperature (°F)
    float sliding_rh_min_pct;       ///< Minimum RH over sliding window (% RH)
    float sliding_rh_max_pct;       ///< Maximum RH over sliding window (% RH)
    float sliding_trend_rate;       ///< RH Rate-of-Change (% RH / hour)

    // 6. Thermal Health & Window Gating Metrics
    float settled_sample_rate_per_hr; ///< Settled "Clean" Samples per Hour (0 - 60 smp/h)
    float raw_shtc3_temp_c;           ///< Raw uncompensated PCB SHTC3 Temperature (°C)
    float raw_shtc3_rh_pct;           ///< Raw uncompensated PCB SHTC3 RH (%)
    float mcu_die_temp_c;             ///< ESP32-S3 TSENS Internal Die Temp (°C)
    float epd_glass_temp_c;           ///< SSD1681 On-Glass Surface Temp (°C)
    float thermal_delta_c;            ///< |T_sens - T_amb| Substrate Rise (°C)
    uint8_t confidence_pct;           ///< Dynamic Thermal Confidence Score (0 - 100%)
    bool  valid;                      ///< True if sensor checksum & acquisition passed
    bool  gate_passed;                ///< Latest slot differential cooldown gate passed
    bool  is_clean_window;            ///< Clean Window flag: window is clean, cold & settled
} bsp_shtc3_data_t;

/**
 * @brief Initialize Sensirion SHTC3 Environmental Sensor & Internal TSENS
 *
 * Wakes the sensor from sleep, verifies the hardware Product ID,
 * installs internal TSENS driver, and puts SHTC3 into low-power standby.
 *
 * @return esp_err_t ESP_OK on success, or ESP_ERR_NOT_FOUND if sensor is absent
 */
esp_err_t bsp_shtc3_init(void);

/**
 * @brief Initialize Internal TSENS
 *
 * Installs internal TSENS driver.
 *
 * @return esp_err_t ESP_OK on success, or ESP_ERR_NOT_FOUND if sensor is unavailable
 */
esp_err_t init_tsens_driver(void);

/**
 * @brief Generic sensor subsystem initialization alias
 * @return esp_err_t ESP_OK on success
 */
//static inline esp_err_t bsp_sensors_init(void) { return bsp_shtc3_init(); }

/**
 * @brief Direct Physical SHTC3 Sensor Read (Wake -> Read -> Sleep)
 *
 * Exclusively communicates with the physical Sensirion SHTC3 over I2C.
 * Performs zero mathematics, zero psychrometric transformations, and zero statistical filtering.
 *
 * @param[out] out_raw_temp Raw 16-bit temperature word from SHTC3
 * @param[out] out_raw_rh   Raw 16-bit relative humidity word from SHTC3
 * @param[in]  low_power    true for low-power read (~1ms), false for normal read (~12ms)
 * @return esp_err_t ESP_OK on success, or I2C communication error
 */
esp_err_t bsp_shtc3_read_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);

/**
 * @brief Autonomous Sub-Execution Sample & Integer Raw Gating Engine
 *
 * Reads physical SHTC3 raw words via bsp_shtc3_read_raw(), evaluates integer differential gate,
 * and commits the raw measurement into the 64-slot RTC ring buffer.
 *
 * @param[in] low_power true for low-power mode, false for normal mode
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_sensors_sample_raw(bool low_power);

/**
 * @brief Check if the RTC ring buffer currently contains clean, settled samples
 *
 * @return true if at least one valid settled sample exists in history
 */
bool bsp_sensors_has_clean_samples(void);

/**
 * @brief Evaluate Sensor Samples into Comprehensive Telemetry Struct
 *
 * Pure computation engine: correlates the latest clean SHTC3 sample with external
 * hardware reference nodes (ESP32-S3 Die TSENS and SSD1681 Glass), runs psychrometric
 * equations, applies EWMA smoothing, and calculates sliding-window dynamics.
 * Performs NO I2C bus traffic or physical sensor communication.
 *
 * @param[in]  die_temp_c    Pre-acquired ESP32-S3 internal die temperature in °C
 * @param[in]  glass_temp_c  Pre-acquired SSD1681 on-glass substrate temperature in °C
 * @param[out] out_data      Destination telemetry structure to populate
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_sensors_eval_samples(float die_temp_c, float glass_temp_c, bsp_shtc3_data_t *out_data);

/**
 * @brief Convenience Telemetry Read (Evaluates auxiliary nodes and samples)
 *
 * Reads die and glass temperatures, then calls bsp_sensors_eval_samples().
 *
 * @param[out] out_data Destination struct to receive telemetry
 * @param[in]  low_power Ignored (kept for backward compatibility)
 * @return esp_err_t ESP_OK on success
 */
//esp_err_t bsp_sensors_read(bsp_shtc3_data_t *out_data, bool low_power);

/**
 * @brief Backwards-compatible Read alias (Normal Power Mode)
 */
//static inline esp_err_t bsp_shtc3_read(bsp_shtc3_data_t *out_data) {
//    return bsp_sensors_read(out_data, false);
//}

/**
 * @brief Backwards-compatible Read alias (Low Power Mode)
 */
//static inline esp_err_t bsp_shtc3_read_lp(bsp_shtc3_data_t *out_data) {
//    return bsp_sensors_read(out_data, true);
//}

/**
 * @brief Backwards-compatible alias for bsp_sensors_read
 */
//static inline esp_err_t bsp_sensors_read_tri_node(bsp_shtc3_data_t *out_data) {
//    return bsp_sensors_read(out_data, false);
//}

/**
 * @brief Read ESP32-S3 Internal Silicon Die Temperature
 *
 * @param[out] out_temp_c Destination pointer for Die temperature in °C
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_mcu_die_temp_read(float *out_temp_c);

/**
 * @brief Check if the system is currently inside the post-wake Thermal Lockout window
 *
 * @return true if Main CPU heating lockout is active, false if system is thermally settled
 */
bool bsp_sensors_is_in_thermal_lockout(void);

/**
 * @brief Get the current dynamic sliding ambient floor temperature
 *
 * @param[out] out_floor_c Destination pointer for floor temperature in °C
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_sensors_get_ambient_floor(float *out_floor_c);

/**
 * @brief Get persistent environmental telemetry history structure from RTC Slow Memory
 *
 * @return const bsp_env_telemetry_history_t* Pointer to shared memory structure
 */
const bsp_env_telemetry_history_t *bsp_sensors_get_telemetry_history(void);

/**
 * @brief Get monotonic total sample count captured in RTC Slow Memory
 *
 * @return uint32_t Total sample count
 */
uint32_t bsp_sensors_get_sample_count(void);

/**
 * @brief Arm autonomous background sub-execution sensor acquisition for sleep cycles
 *
 * Configures the sensor sub-execution state in RTC Slow Memory with the specified cadence.
 * When armed, bsp_app_start() autonomously executes an isolated sub-execution on timer wake
 * (<10ms) and returns directly to sleep without invoking application on_wake() until disarmed
 * or an external RTC alarm/timer fires.
 *
 * @param[in] interval_sec Sampling cadence in seconds (minimum 1)
 * @return esp_err_t ESP_OK on success, or ESP_ERR_INVALID_ARG
 */
esp_err_t bsp_sensors_arm_sub_execution(uint32_t interval_sec);

/**
 * @brief Disarm autonomous background sub-execution sensor acquisition
 *
 * Clears sub-execution arm flag in RTC memory so subsequent timer wakeups boot normally
 * and invoke on_wake().
 *
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_sensors_disarm_sub_execution(void);

/**
 * @brief Check if autonomous background sub-execution is currently armed
 *
 * @return bool true if sub-execution is active/armed, false otherwise
 */
bool bsp_sensors_is_sub_execution_armed(void);

/**
 * @brief Get configured background sub-execution interval in seconds
 *
 * @return uint32_t Interval in seconds (default 60 if not configured)
 */
uint32_t bsp_sensors_get_sub_execution_interval(void);

/* Backward-compatibility aliases */
//#define bsp_sensors_arm_sleep_sprint    bsp_sensors_arm_sub_execution
//#define bsp_sensors_disarm_sleep_sprint bsp_sensors_disarm_sub_execution
//#define bsp_sensors_is_sprint_armed     bsp_sensors_is_sub_execution_armed
//#define bsp_sensors_get_sprint_interval bsp_sensors_get_sub_execution_interval

#ifdef __cplusplus
}
#endif

#endif /* BSP_SENSORS_H */
