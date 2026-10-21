/**
 * @file battery_estimator.c
 * @brief Unified 13-point LiPo OCV state-of-charge and schedule-aware autonomy estimator
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "battery_estimator.h"

#include <stddef.h>

/**
 * @brief Unified 13-point LiPo Open-Circuit Voltage (OCV) lookup table in basis points (10000 = 100.00%).
 *
 * Matches sub_power.c s_lipo_table exactly so battery percentage and autonomy days never diverge.
 */
static const struct {
    uint16_t mv;
    uint16_t soc_bp;
} s_lipo_ocv_lut[] = {
    {4200, 10000},
    {4120,  9500},
    {4040,  8800},
    {3960,  8000},
    {3890,  7300},
    {3820,  6000},
    {3780,  4800},
    {3750,  3600},
    {3720,  2500},
    {3680,  1500},
    {3600,   800},
    {3450,   300},
    {3300,     0},
};

#define LIPO_OCV_LUT_SIZE (sizeof(s_lipo_ocv_lut) / sizeof(s_lipo_ocv_lut[0]))

/**
 * @brief Calculates battery State-of-Charge (SoC) in basis points (0..10000 = 0.00%..100.00%).
 *
 * @param[in]    vbat_mv         Sampled battery terminal voltage in millivolts.
 *
 * @return State of charge in basis points.
 */
uint32_t battery_get_soc_basis_pts(uint32_t vbat_mv)
{
    if (vbat_mv >= s_lipo_ocv_lut[0].mv) {
        return 10000;
    }
    if (vbat_mv <= s_lipo_ocv_lut[LIPO_OCV_LUT_SIZE - 1].mv) {
        return 0;
    }

    for (size_t i = 0; i < LIPO_OCV_LUT_SIZE - 1; i++) {
        if (vbat_mv <= s_lipo_ocv_lut[i].mv && vbat_mv >= s_lipo_ocv_lut[i + 1].mv) {
            uint32_t span_mv  = (uint32_t)(s_lipo_ocv_lut[i].mv - s_lipo_ocv_lut[i + 1].mv);
            uint32_t span_bp  = (uint32_t)(s_lipo_ocv_lut[i].soc_bp - s_lipo_ocv_lut[i + 1].soc_bp);
            uint32_t diff_mv  = vbat_mv - (uint32_t)s_lipo_ocv_lut[i + 1].mv;
            return (uint32_t)s_lipo_ocv_lut[i + 1].soc_bp + ((diff_mv * span_bp) / span_mv);
        }
    }
    return 0;
}

/**
 * @brief Estimates average continuous system current draw in milliamperes (mA) from empirical drop.
 *
 * @param[in]    nominal_mah     Nominal battery cell capacity in milliampere-hours.
 * @param[in]    v1_mv           Initial battery voltage in millivolts.
 * @param[in]    v2_mv           Final battery voltage in millivolts.
 * @param[in]    delta_t_sec     Elapsed operating time between samples in seconds.
 *
 * @return Estimated current draw in mA, or negative value on charging/invalid.
 */
float battery_estimate_avg_current_ma(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv, uint32_t delta_t_sec)
{
    if (delta_t_sec == 0) {
        return -1.0f;
    }

    uint32_t soc1_bp = battery_get_soc_basis_pts(v1_mv);
    uint32_t soc2_bp = battery_get_soc_basis_pts(v2_mv);

    if (soc1_bp <= soc2_bp) {
        return -2.0f;
    }

    float delta_soc    = (float)(soc1_bp - soc2_bp) / 10000.0f;
    float consumed_mah = (float)nominal_mah * delta_soc;
    float delta_hours  = (float)delta_t_sec / 3600.0f;

    return consumed_mah / delta_hours;
}

/**
 * @brief Computes schedule-aware baseline current draw in mA from Flow A and Flow B intervals.
 *
 * @details Accounts for:
 *          - Deep sleep base current (~0.045 mA across LDO, 400k divider, RTC Periph, SHTC3/SSD1681/ES8311 standby)
 *          - Flow A 16ms wake stub charge (~0.45 mAs per Flow A sample)
 *          - Flow B display wake charge (~38 mAs average across 5 partial + 1 full OTP refresh + flash sync)
 *
 * @param[in]    flow_a_sec      Configured Flow A sample period in seconds.
 * @param[in]    flow_b_sec      Configured Flow B display refresh period in seconds.
 *
 * @return Schedule-based average current draw in milliamperes (mA).
 */
float battery_estimate_schedule_current_ma(uint32_t flow_a_sec, uint32_t flow_b_sec)
{
    if (flow_a_sec == 0) {
        flow_a_sec = 60;
    }
    if (flow_b_sec == 0) {
        flow_b_sec = 300;
    }

    const float i_sleep_ma       = 0.045f;
    const float q_flow_a_mas     = 0.45f;
    const float q_flow_b_avg_mas = 38.0f;

    float i_flow_a_ma = q_flow_a_mas / (float)flow_a_sec;
    float i_flow_b_ma = q_flow_b_avg_mas / (float)flow_b_sec;

    return i_sleep_ma + i_flow_a_ma + i_flow_b_ma;
}

/**
 * @brief Estimates remaining operational battery autonomy in days.
 *
 * @param[in]    nominal_mah     Nominal battery capacity in milliampere-hours.
 * @param[in]    current_vbat_mv Current sampled battery voltage in millivolts.
 * @param[in]    avg_current_ma  Estimated average system draw in mA.
 *
 * @return Estimated autonomy in fractional days.
 */
float battery_estimate_remaining_days(uint32_t nominal_mah, uint32_t current_vbat_mv, float avg_current_ma)
{
    if (avg_current_ma <= 0.001f) {
        avg_current_ma = 0.20f;
    }

    uint32_t soc_bp       = battery_get_soc_basis_pts(current_vbat_mv);
    float remaining_mah   = (float)nominal_mah * ((float)soc_bp / 10000.0f);
    float remaining_hours = remaining_mah / avg_current_ma;
    return remaining_hours / 24.0f;
}
