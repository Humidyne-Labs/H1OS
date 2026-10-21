/**
 * @file battery_estimator.h
 * @brief Empirical battery state-of-charge estimator interface
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate battery State-of-Charge (SoC) in basis points.
 *
 * Uses piece-wise linear interpolation across 11 empirical LiPo cell voltage breakpoints.
 *
 * @param[in] vbat_mv Battery terminal voltage in millivolts.
 *
 * @return State-of-Charge in basis points (0..10000 = 0.00%..100.00%).
 */
uint32_t battery_get_soc_basis_pts(uint32_t vbat_mv);

/**
 * @brief Estimate average system current consumption in milliamperes (mA).
 *
 * @param[in] nominal_mah Nominal battery capacity in milliampere-hours.
 * @param[in] v1_mv       Initial sampled battery voltage in millivolts.
 * @param[in] v2_mv       Final sampled battery voltage in millivolts.
 * @param[in] delta_t_sec Elapsed operational time in seconds between samples.
 *
 * @return Estimated average current in mA, or negative value if charging / invalid.
 */
float battery_estimate_avg_current_ma(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv, uint32_t delta_t_sec);

/**
 * @brief Inline helper to estimate average system current in microamperes (uA).
 *
 * @param[in] nominal_mah Nominal battery capacity in milliampere-hours.
 * @param[in] v1_mv       Initial voltage in millivolts.
 * @param[in] v2_mv       Final voltage in millivolts.
 * @param[in] delta_t_sec Elapsed operational time in seconds.
 *
 * @return Estimated average current in uA.
 */
static inline int32_t battery_estimate_avg_current_ua(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv, uint32_t delta_t_sec)
{
    float i_ma = battery_estimate_avg_current_ma(nominal_mah, v1_mv, v2_mv, delta_t_sec);
    if (i_ma < 0.0f) {
        return (int32_t)i_ma;
    }
    return (int32_t)(i_ma * 1000.0f);
}

/**
 * @brief Estimate remaining battery operating autonomy in days.
 *
 * @param[in] nominal_mah     Nominal battery capacity in milliampere-hours.
 * @param[in] current_vbat_mv Current sampled battery terminal voltage in millivolts.
 * @param[in] avg_current_ma  Estimated average continuous system current draw in mA.
 *
 * @return Remaining autonomy in days (e.g. 180.5 days).
 */
float battery_estimate_schedule_current_ma(uint32_t flow_a_sec, uint32_t flow_b_sec);

float battery_estimate_remaining_days(uint32_t nominal_mah, uint32_t current_vbat_mv, float avg_current_ma);

#ifdef __cplusplus
}
#endif
