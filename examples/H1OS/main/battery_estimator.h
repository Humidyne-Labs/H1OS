/**
 * @file battery_estimator.h
 * @brief Empirical Battery State-of-Charge & Average Current Estimation Module
 *
 * Implements 4-segment piecewise linear State of Charge in basis points (0 to 10,000)
 * and empirical average current derivation (mA / µA) over elapsed duration delta_t.
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron (2026)
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BATTERY_ESTIMATOR_H
#define BATTERY_ESTIMATOR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Returns State of Charge in basis points (0 to 10,000 = 0.00% to 100.00%)
 *        using a 4-segment piecewise linear approximation for 3.7V LiPo cells.
 *
 * @param vbat_mv Battery terminal voltage in millivolts
 * @return uint32_t State of charge in basis points (0 - 10000)
 */
uint32_t battery_get_soc_basis_pts(uint32_t vbat_mv);

/**
 * @brief Estimates empirical average current consumption over delta_t.
 *
 * @param nominal_mah Rated cell capacity in mAh (e.g. 400).
 * @param v1_mv       Initial terminal voltage in mV.
 * @param v2_mv       Ending terminal voltage in mV.
 * @param delta_t_sec Elapsed duration between readings in seconds.
 * @return float Average current draw in mA.
 *         Returns -1.0f if delta_t is 0.
 *         Returns -2.0f if voltage increased/unchanged (charging or cell relaxation).
 */
float battery_estimate_avg_current_ma(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv,
                                      uint32_t delta_t_sec);

/**
 * @brief Helper to convert estimated mA to microamps (µA) for sleep current validation.
 *
 * @param nominal_mah Rated cell capacity in mAh.
 * @param v1_mv       Initial voltage in mV.
 * @param v2_mv       Ending voltage in mV.
 * @param delta_t_sec Elapsed duration in seconds.
 * @return int32_t Estimated current in µA, or negative error code.
 */
static inline int32_t battery_estimate_avg_current_ua(uint32_t nominal_mah, uint32_t v1_mv,
                                                      uint32_t v2_mv, uint32_t delta_t_sec)
{
    float i_ma = battery_estimate_avg_current_ma(nominal_mah, v1_mv, v2_mv, delta_t_sec);
    if (i_ma < 0.0f) {
        return (int32_t)i_ma;
    }
    return (int32_t)(i_ma * 1000.0f);
}

/**
 * @brief Calculate estimated remaining battery autonomy in days
 *
 * @param nominal_mah    Nominal battery capacity in mAh (400)
 * @param current_vbat_mv Current terminal voltage in mV
 * @param avg_current_ma  Measured or model average current in mA
 * @return float Estimated autonomy in days
 */
float battery_estimate_remaining_days(uint32_t nominal_mah, uint32_t current_vbat_mv,
                                      float avg_current_ma);

#ifdef __cplusplus
}
#endif

#endif /* BATTERY_ESTIMATOR_H */
