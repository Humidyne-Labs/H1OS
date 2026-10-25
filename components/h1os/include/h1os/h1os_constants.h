/**
 * @file h1os_constants.h
 * @brief Canonical architectural constants, hardware timing budgets, and default configuration macros.
 *
 * @copyright Copyright (c) 2026
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @defgroup H1OS_Hardware_Timing Hardware Acquisition & Polling Timing Bounds
 * @{
 */
#define H1OS_TSENS_SETTLING_DELAY_US          400U   /**< Minimum analog settling delay following TSENS power-up (400 µs). */
#define H1OS_TSENS_READY_POLL_INTERVAL_US     5U     /**< Polling step interval while awaiting TSENS ready bit (5 µs).    */
#define H1OS_TSENS_READY_TIMEOUT_CYCLES       100U   /**< Maximum polling loop iterations (100 * 5 µs = 500 µs bound).     */
#define H1OS_SHTC3_CONVERSION_TOTAL_US        14500U /**< Sensirion SHTC3 maximum measurement duration (14.5 ms).        */
#define H1OS_TSENS_ESTIMATED_SAMPLE_US         450U   /**< Nominal TSENS acquisition duration (settling + ready poll).    */
#define H1OS_SHTC3_POST_TSENS_DELAY_US        (H1OS_SHTC3_CONVERSION_TOTAL_US - H1OS_TSENS_ESTIMATED_SAMPLE_US) /**< Remainder wait: 14,050 µs */
/** @} */

/**
 * @defgroup H1OS_System_Intervals System Intervals, Buffer Sizes & Thresholds
 * @{
 */
#define H1OS_NVS_AUTONOMY_COMMIT_INTERVAL_SEC 3600U  /**< Minimum elapsed deep sleep interval between unattended NVS commits (1 hour). */
#define H1OS_TELEMETRY_RING_CAPACITY          32U    /**< Fixed capacity of historical telemetry sample circular ring buffer. */
#define H1OS_TSENS_DEFAULT_INTERCEPT_CENTI_C  2052   /**< Default TSENS Q12 fixed-point intercept in centi-°C (20.52°C).     */
#define H1OS_RTC_STATE_MAGIC                  0x534C4154U /**< RTC state validation magic word ('SLAT').                  */
/** @} */

/**
 * @defgroup H1OS_Default_Config Default Presets for Application Lifecycle Configuration
 * @{
 */
#define H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC   30U    /**< Recommended default interactive session inactivity sleep timeout in seconds. */
#define H1OS_DEFAULT_FLOW_A_PERIOD_SEC        60U    /**< Recommended default Flow A headless sensor sample burst period in seconds.    */
#define H1OS_DEFAULT_FLOW_B_PERIOD_SEC        300U   /**< Recommended default Flow B unattended presentation refresh period in seconds. */
/** @} */

#ifdef __cplusplus
}
#endif
