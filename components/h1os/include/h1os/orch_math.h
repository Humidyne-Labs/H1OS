/**
 * @file orch_math.h
 * @brief Layer 3: Class-E Psychrometric & Signal Math Engine
 *
 * Implements physical invariant equations (August-Roche-Magnus approximation):
 *  1. Water vapor pressure invariant (e)
 *  2. Dew point invariant (Tdp)
 *  3. Dynamic ambient floor tracking
 *  4. Reconstructed ambient relative humidity (RH_amb)
 *  5. Absolute humidity (vapor density, g/m³)
 *  6. Recursive EWMA filter
 *
 * Zero synthetic offsets or artificial curve divisions.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate saturation vapor pressure e_s(T) in hPa.
 * Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))
 *
 * @param[in] temp_c Temperature in Celsius.
 * @return Saturation vapor pressure in hPa.
 */
float orch_math_calc_sat_vapor_pressure(float temp_c);

/**
 * @brief Calculate actual water vapor pressure (e) in hPa.
 * Formula: e = (rh_pct / 100.0) * e_s(temp_c)
 *
 * @param[in] temp_c Temperature in Celsius.
 * @param[in] rh_pct Relative humidity in percent (0 - 100).
 * @return Actual water vapor pressure in hPa.
 */
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct);

/**
 * @brief Calculate true dew point (T_dew) in Celsius from physical vapor pressure.
 * Invariant against package heating because vapor mass in air does not change with temperature.
 *
 * @param[in] temp_c Measured package temperature in Celsius.
 * @param[in] rh_pct Measured package relative humidity in percent.
 * @return Dew point in Celsius.
 */
float orch_math_calc_dew_point(float temp_c, float rh_pct);

/**
 * @brief Reconstruct true ambient relative humidity using the ambient baseline floor temperature.
 * Formula: RH_amb = (e / e_s(temp_ambient_floor)) * 100.0%
 *
 * @param[in] vapor_pressure_hpa Invariant vapor pressure in hPa.
 * @param[in] amb_floor_temp_c   Ambient floor temperature in Celsius.
 * @return Reconstructed ambient relative humidity in percent (clamped to [0, 100]).
 */
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c);

/**
 * @brief Unified Psychrometric Vector Transform.
 * Evaluates water vapor pressure invariant (e), true dew point (T_dew),
 * and reconstructed ambient relative humidity (RH_amb) in a single consolidated pass.
 *
 * @param[in]  temp_c        Measured package temperature in Celsius.
 * @param[in]  rh_pct        Measured package relative humidity in percent.
 * @param[in]  amb_floor_c   Ambient floor baseline temperature in Celsius.
 * @param[out] out_vp_hpa    Output vapor pressure in hPa (optional, can be NULL).
 * @param[out] out_dew_c     Output dew point in Celsius (optional, can be NULL).
 * @param[out] out_rh_amb    Output reconstructed ambient RH in percent (optional, can be NULL).
 */
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float amb_floor_c, float *out_vp_hpa, float *out_dew_c,
                                   float *out_rh_amb);

/**
 * @brief Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).
 * Formula: d_v = 216.7 * (e / (273.15 + T_ambient))
 *
 * @param[in] vapor_pressure_hpa Vapor pressure in hPa.
 * @param[in] amb_temp_c Ambient temperature in Celsius.
 * @return Vapor density in g/m³.
 */
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c);

/**
 * @brief Update continuous recursive EWMA filter.
 * S_t = alpha * X_t + (1 - alpha) * S_{t-1}
 *
 * @param[in] current_sample New sample value.
 * @param[in] previous_ewma  Previous filtered value.
 * @param[in] alpha          Weight coefficient (typically 0.25 to 0.35).
 * @return Filtered result.
 */
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha);

/**
 * @brief Evaluates whether sensor package has settled to thermal plateau.
 * Formula: Delta T = initial_temp - current_temp >= gate_threshold
 *
 * @param[in] initial_temp_centi_c Initial sleep entry baseline temp (centi-°C).
 * @param[in] current_temp_centi_c Current sample temp (centi-°C).
 * @param[in] gate_threshold_centi_c Threshold drop (typically 5 to 20 centi-°C, i.e. 0.05 - 0.20
 * °C).
 * @return True if thermally settled.
 */
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c,
                                  int16_t gate_threshold_centi_c);

#ifdef __cplusplus
}
#endif
