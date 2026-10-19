/**
 * @file sub_rtc.h
 * @brief Layer 2: PCF85063A real-time clock and hardware countdown timer driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize PCF85063A real-time clock over shared I2C bus.
 *
 * Disables CLKOUT push-pull square wave to eliminate continuous trace leakage,
 * verifies oscillator integrity, and clears residual timer/alarm flags.
 *
 * @return ESP_OK on success, or I2C communication error.
 */
esp_err_t sub_rtc_init(void);

/**
 * @brief Read current date and time into POSIX struct tm.
 *
 * @param[out] out_time Pointer to struct tm populated with current RTC timestamp. Must not be NULL.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_get_time(struct tm *out_time);

/**
 * @brief Set RTC calendar date and time.
 *
 * @param[in] time Pointer to struct tm containing target timestamp. Must not be NULL.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_set_time(const struct tm *time);

/**
 * @brief Arm hardware countdown timer.
 *
 * Drives open-drain interrupt line GPIO 5 LOW upon expiration to wake platform.
 *
 * @param[in] seconds Countdown interval in seconds (1 to 15300s).
 *
 * @return ESP_OK on success, or error code.
 */
esp_err_t sub_rtc_arm_countdown(uint32_t seconds);

/**
 * @brief Cancel and disarm hardware countdown timer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_rtc_cancel_countdown(void);

/**
 * @brief Read remaining seconds on the active countdown timer.
 *
 * Used for zero-hour collision avoidance.
 *
 * @param[out] out_sec Destination pointer for remaining seconds. Must not be NULL.
 *
 * @return ESP_OK on success, or error code.
 */
esp_err_t sub_rtc_get_remaining_seconds(uint32_t *out_sec);

/**
 * @brief Inspect and acknowledge RTC interrupt flags.
 *
 * Clears TF (Timer Flag) and AF (Alarm Flag) in Control_2 to deassert GPIO 5.
 *
 * @param[out] out_alarm Set to true if an alarm interrupt triggered.
 * @param[out] out_timer Set to true if a countdown timer interrupt triggered.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_get_and_clear_interrupts(bool *out_alarm, bool *out_timer);

#ifdef __cplusplus
}
#endif
