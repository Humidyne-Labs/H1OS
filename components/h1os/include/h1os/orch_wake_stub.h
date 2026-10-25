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

#include "h1os_constants.h"

#define ORCH_TSENS_SETTLING_DELAY_US          H1OS_TSENS_SETTLING_DELAY_US          /**< Layer 3 alias: analog settling delay (400 µs). */
#define ORCH_TSENS_READY_POLL_INTERVAL_US     H1OS_TSENS_READY_POLL_INTERVAL_US     /**< Layer 3 alias: ready polling interval (5 µs).    */
#define ORCH_TSENS_READY_TIMEOUT_CYCLES       H1OS_TSENS_READY_TIMEOUT_CYCLES       /**< Layer 3 alias: polling loop bound (100 cycles).   */
#define ORCH_SHTC3_CONVERSION_TOTAL_US        H1OS_SHTC3_CONVERSION_TOTAL_US        /**< Layer 3 alias: max measurement duration (14.5 ms).*/
#define ORCH_TSENS_ESTIMATED_SAMPLE_US        H1OS_TSENS_ESTIMATED_SAMPLE_US        /**< Layer 3 alias: TSENS sample duration (450 µs).    */
#define ORCH_SHTC3_POST_TSENS_DELAY_US        H1OS_SHTC3_POST_TSENS_DELAY_US        /**< Layer 3 alias: remainder wait (14,050 µs).        */

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
