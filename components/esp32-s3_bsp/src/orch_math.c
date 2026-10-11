/**
 * @file orch_math.c
 * @brief Layer 3: Class-E Psychrometric & Signal Math Engine Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "bsp/orch_math.h"
#include <math.h>

#define MAGNUS_A 17.625f
#define MAGNUS_B 243.04f

float orch_math_calc_sat_vapor_pressure(float temp_c)
{
    /* e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T)) [hPa] */
    return 6.112f * expf((MAGNUS_A * temp_c) / (MAGNUS_B + temp_c));
}

float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
{
    float es = orch_math_calc_sat_vapor_pressure(temp_c);
    float rh_norm = rh_pct / 100.0f;
    if (rh_norm < 0.0f) rh_norm = 0.0f;
    if (rh_norm > 1.0f) rh_norm = 1.0f;
    return rh_norm * es;
}

float orch_math_calc_dew_point(float temp_c, float rh_pct)
{
    float rh_norm = rh_pct / 100.0f;
    if (rh_norm <= 0.0001f) rh_norm = 0.0001f;
    if (rh_norm > 1.0f) rh_norm = 1.0f;

    /* gamma = ln(RH/100) + (17.625 * T) / (243.04 + T) */
    float gamma = logf(rh_norm) + (MAGNUS_A * temp_c) / (MAGNUS_B + temp_c);

    /* T_dew = (243.04 * gamma) / (17.625 - gamma) */
    return (MAGNUS_B * gamma) / (MAGNUS_A - gamma);
}

float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c)
{
    float es_amb = orch_math_calc_sat_vapor_pressure(amb_floor_temp_c);
    if (es_amb <= 0.0001f) return 0.0f;

    float rh = (vapor_pressure_hpa / es_amb) * 100.0f;
    if (rh < 0.0f) rh = 0.0f;
    if (rh > 100.0f) rh = 100.0f;
    return rh;
}

float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
{
    /* d_v = 216.7 * (e / (273.15 + T_ambient)) [g/m³] */
    float temp_k = 273.15f + amb_temp_c;
    if (temp_k <= 0.1f) return 0.0f;
    return 216.7f * (vapor_pressure_hpa / temp_k);
}

float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
{
    if (alpha <= 0.0f) return previous_ewma;
    if (alpha >= 1.0f) return current_sample;
    return (alpha * current_sample) + ((1.0f - alpha) * previous_ewma);
}

bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
{
    int16_t delta_drop = initial_temp_centi_c - current_temp_centi_c;
    return (delta_drop >= gate_threshold_centi_c);
}
