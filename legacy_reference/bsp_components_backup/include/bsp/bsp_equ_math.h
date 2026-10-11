/**
 * @file bsp_equ_math.h
 * @brief Consolidated Mathematical & Psychrometric Equations Engine
 *
 * Encapsulates all environmental and thermodynamic calculations:
 *  - Magnus Formula for Water Vapor Pressure & Invariant Dew Point.
 *  - Reconstructed True Ambient Relative Humidity & Absolute Humidity.
 *  - Fixed-Point Centi-Degree Conversions for ULP / low-power compatibility.
 *  - Exponentially Weighted Moving Average (EWMA) digital filtering.
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_EQU_MATH_H
#define BSP_EQU_MATH_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp/bsp_env_telemetry.h"

/* Unit Conversion Macros */
#ifndef C_TO_F
#define C_TO_F(c) (((c) * 1.8f) + 32.0f)
#endif
#ifndef F_TO_C
#define F_TO_C(f) (((f) - 32.0f) / 1.8f)
#endif
#ifndef C_TO_K
#define C_TO_K(c) ((c) + 273.15f)
#endif
#ifndef K_TO_C
#define K_TO_C(k) ((k) - 273.15f)
#endif
#ifndef K_TO_F
#define K_TO_F(k) (C_TO_F(K_TO_C(k)))
#endif

#define BSP_MATH_C_TO_F(c) C_TO_F(c)
#define BSP_MATH_F_TO_C(f) F_TO_C(f)
#define BSP_MATH_C_TO_K(c) C_TO_K(c)
#define BSP_MATH_K_TO_C(k) K_TO_C(k)
#define BSP_MATH_K_TO_F(k) K_TO_F(k)

#define BSP_MATH_CLAMP(x, low, high) (((x) < (low)) ? (low) : (((x) > (high)) ? (high) : (x)))

/* SHTC3 Raw Physical Conversion Macros */
#define SHTC3_RAW_TO_TEMP_C(raw) (-45.0f + (175.0f * ((float)(raw) / 65536.0f)))
#define SHTC3_RAW_TO_RH_PCT(raw) (100.0f * ((float)(raw) / 65536.0f))
#define SHTC3_TEMP_C_TO_RAW(c)   ((uint16_t)((((c) + 45.0f) / 175.0f) * 65536.0f))
#define SHTC3_RH_PCT_TO_RAW(rh)  ((uint16_t)(((rh) / 100.0f) * 65536.0f))

/* SHTC3 Raw ADC Count Differential Gating: 1.50°C * (65536 / 175) = 562 LSB counts */
#define SHTC3_RAW_THERMAL_MARGIN_LSB          562
#define SHTC3_RAW_IS_SETTLED(raw1, raw2)     (abs((int)(raw1) - (int)(raw2)) <= SHTC3_RAW_THERMAL_MARGIN_LSB)

/* Fixed-Point Centi-Unit Scale: 1.00 unit = 100 integer units */
#define BSP_MATH_FLOAT_TO_CENTI(f) ((int16_t)((f) * 100.0f))
#define BSP_MATH_CENTI_TO_FLOAT(c) ((float)(c) / 100.0f)

/**
 * @brief Sliding Window & Clean Window Metrics
 */
typedef struct {
    float    temp_avg_c;                  ///< Mean temperature over clean slots (°C)
    float    temp_floor_c;                ///< Baseline floor temperature (°C)
    float    temp_ceiling_c;              ///< Thermal ceiling temperature (°C)
    float    rh_min_pct;                  ///< Minimum relative humidity (% RH)
    float    rh_max_pct;                  ///< Maximum relative humidity (% RH)
    float    trend_rate_rh_per_hr;        ///< RH rate of change (% RH / hour)
    float    settled_sample_rate_per_hr;  ///< Clean settled samples per hour (0 - 60 smp/h)
    uint32_t clean_sample_count;          ///< Total clean slots in buffer
    bool     is_clean_window;             ///< True if active sliding window is cold and settled
} bsp_sliding_window_metrics_t;

/**
 * @brief Compute Sliding Window Metrics across the 64-slot Ring Buffer
 *
 * Expands 4-byte raw samples and clean mask into statistical metrics.
 *
 * @param[in]  history Persistent history ring buffer from RTC Slow Memory
 * @param[out] out_metrics Destination struct to receive computed metrics
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_math_calc_sliding_window_metrics(const bsp_env_telemetry_history_t *history, bsp_sliding_window_metrics_t *out_metrics);

/**
 * @brief Calculate Actual Invariant Water Vapor Pressure (e in hPa)
 *
 * Equation: e = (RH / 100) * 6.112 * exp( (17.625 * T) / (243.04 + T) )
 *
 * @param[in] temp_c Sensor temperature in degrees Celsius
 * @param[in] rh_pct Relative humidity percentage (0 - 100)
 * @return float Invariant actual vapor pressure in hPa
 */
float bsp_math_calc_vapor_pressure_hpa(float temp_c, float rh_pct);

/**
 * @brief Calculate True Invariant Dew Point (Td in °C)
 *
 * Equation: gamma = ln(RH / 100) + (17.625 * T) / (243.04 + T)
 *           Td = (243.04 * gamma) / (17.625 - gamma)
 *
 * @param[in] temp_c Sensor temperature in degrees Celsius
 * @param[in] rh_pct Relative humidity percentage (0 - 100)
 * @return float Invariant dew point in degrees Celsius
 */
float bsp_math_calc_dew_point_c(float temp_c, float rh_pct);

/**
 * @brief Reconstruct True Ambient Relative Humidity (RH_amb in %)
 *
 * Reconstructs the true ambient relative humidity by normalizing invariant vapor pressure
 * against true isolated ambient substrate temperature (e.g. SSD1681 on-glass).
 *
 * Equation: RH_amb = RH_sens * exp( 17.625*T_sens/(243.04+T_sens) - 17.625*T_amb/(243.04+T_amb) )
 *
 * @param[in] temp_sens_c Heated sensor die temperature in °C
 * @param[in] rh_sens_pct Measured sensor relative humidity in %
 * @param[in] temp_amb_c True isolated ambient temperature in °C
 * @return float Reconstructed true ambient RH (0.0 to 100.0 %)
 */
float bsp_math_reconstruct_ambient_rh(float temp_sens_c, float rh_sens_pct, float temp_amb_c);

/**
 * @brief Calculate Physical Invariant Absolute Humidity (dv in g/m³)
 *
 * Equation: dv = 216.7 * (e / (273.15 + T_amb))
 *
 * @param[in] vapor_pressure_hpa Actual vapor pressure in hPa
 * @param[in] temp_amb_c Ambient temperature in °C
 * @return float Absolute humidity in grams of water vapor per cubic meter (g/m³)
 */
float bsp_math_calc_absolute_humidity_g(float vapor_pressure_hpa, float temp_amb_c);

/**
 * @brief Calculate Dynamic Thermal Confidence Score (0 - 100 %)
 *
 * Evaluates thermal equilibrium between measured silicon temperature and isolated ambient reference.
 *
 * @param[in] temp_sens_c Sensor package temperature in °C
 * @param[in] temp_amb_c Ambient reference temperature in °C
 * @return uint8_t Confidence score (10 to 100 %)
 */
uint8_t bsp_math_calc_confidence_score(float temp_sens_c, float temp_amb_c);

/**
 * @brief Apply Exponentially Weighted Moving Average (EWMA) digital filter
 *
 * Equation: y[n] = alpha * x[n] + (1 - alpha) * y[n-1]
 *
 * @param[in] current_sample Newest measurement value
 * @param[in,out] state_val Previous filtered state value (updated in-place)
 * @param[in] alpha Smoothing factor (0.0 < alpha <= 1.0, typically 0.25)
 * @return float Filtered output
 */
float bsp_math_apply_ewma(float current_sample, float *state_val, float alpha);

#ifdef __cplusplus
}
#endif

#endif /* BSP_EQU_MATH_H */
