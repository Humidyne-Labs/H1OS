/**
 * @file orch_wake_stub.h
 * @brief Layer 3: RTC Fast Memory deep sleep wake stub (<3ms Flow A sample burst)
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ORCH_TSENS_SETTLING_DELAY_US          400U   /**< Minimum analog settling delay following TSENS power-up (400 µs). */
#define ORCH_TSENS_READY_POLL_INTERVAL_US     5U     /**< Polling step interval while awaiting TSENS ready bit (5 µs).     */
#define ORCH_TSENS_READY_TIMEOUT_CYCLES       100U   /**< Maximum polling loop iterations (100 * 5 µs = 500 µs bound).     */
#define ORCH_SHTC3_CONVERSION_TOTAL_US        14500U /**< Sensirion SHTC3 maximum measurement duration (14.5 ms).          */
#define ORCH_TSENS_ESTIMATED_SAMPLE_US        450U   /**< Nominal TSENS acquisition duration (settling + ready poll).      */

/**< Remainder wait: 14,050 µs */
#define ORCH_SHTC3_POST_TSENS_DELAY_US (ORCH_SHTC3_CONVERSION_TOTAL_US - ORCH_TSENS_ESTIMATED_SAMPLE_US) 

/**
 * @brief Install the deep sleep wake stub into RTC Fast Memory.
 *
 * Registers bsp_wake_stub() with esp_set_deep_sleep_wake_stub().
 */
void orch_wake_stub_install(void);

/**
 * @brief Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.
 *
 * Executes fast sub-3ms Flow A sensor bursts using bitbanged I2C without booting the main
 * ESP-IDF OS or spinning up the 160/240 MHz PLL clocks.
 */
void bsp_wake_stub(void);

#ifdef __cplusplus
}
#endif
