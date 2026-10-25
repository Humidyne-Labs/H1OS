/**
 * @file h1os_time.h
 * @brief Layer 4: System time services, timezone management, and external SNTP bridge
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Time presentation format options.
 */
typedef enum {
    H1OS_TIME_FMT_24H_SEC = 0, /**< 24-hour time with seconds:    "14:35:08"    */
    H1OS_TIME_FMT_24H_MIN = 1, /**< 24-hour time without seconds: "14:35"       */
    H1OS_TIME_FMT_12H_SEC = 2, /**< 12-hour time with seconds:    "02:35:08 PM" */
    H1OS_TIME_FMT_12H_MIN = 3  /**< 12-hour time without seconds: "02:35 PM"    */
} h1os_time_format_t;

/**
 * @brief Date presentation format options.
 */
typedef enum {
    H1OS_DATE_FMT_MM_DD_YY     = 0, /**< Month/Day/Year format:      "09/26/26"          */
    H1OS_DATE_FMT_DOW          = 1, /**< Day-of-week textual format: "Saturday"          */
    H1OS_DATE_FMT_MM_DD_YY_DOW = 2  /**< Combined date and day:      "09/26/26 Saturday" */
} h1os_date_format_t;

/**
 * @brief Callback for external network/remote time acquisition (SNTP, GPS, BLE).
 *
 * @param[in] timeout_ms Network acquisition timeout in milliseconds.
 * @param[in] user_data  Arbitrary user context pointer.
 *
 * @return ESP_OK if external time was synchronized, or error code.
 */
typedef esp_err_t (*h1os_time_sync_cb_t)(uint32_t timeout_ms, void *user_data);

/**
 * @brief Configure POSIX timezone string for local time conversions.
 *
 * @param[in] tz_str POSIX TZ format string (e.g. "EST5EDT,M3.2.0,M11.1.0").
 *
 * @return
 *   - ESP_OK: Timezone configured and applied.
 *   - ESP_ERR_INVALID_ARG: Null pointer provided.
 */
esp_err_t h1os_time_set_timezone(const char *tz_str);

/**
 * @brief Register external time synchronization provider callback.
 *
 * @param[in] cb        Time acquisition callback function pointer.
 * @param[in] user_data User context pointer passed to callback.
 *
 * @return ESP_OK on success.
 */
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data);

/**
 * @brief Execute immediate time synchronization via registered provider.
 *
 * @param[in] timeout_ms Synchronization timeout in milliseconds.
 *
 * @return ESP_OK on success, or provider error code.
 */
esp_err_t h1os_time_sync_now(uint32_t timeout_ms);

/**
 * @brief Synchronize internal POSIX system clock to external PCF85063A hardware RTC.
 *
 * @return ESP_OK on success, or I2C bus communication error.
 */
esp_err_t h1os_time_sync_system_to_rtc(void);

/**
 * @brief Synchronize external PCF85063A hardware RTC to internal POSIX system clock.
 *
 * @return ESP_OK on success, or I2C bus communication error.
 */
esp_err_t h1os_time_sync_rtc_to_system(void);

/**
 * @brief Format current local time into destination buffer.
 *
 * @param[in]  fmt     Requested time presentation format.
 * @param[out] dest    Pointer to destination character buffer.
 * @param[in]  max_len Capacity of destination buffer in bytes.
 *
 * @return ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.
 */
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char *dest, size_t max_len);

/**
 * @brief Format current local calendar date into destination buffer.
 *
 * @param[in]  fmt     Requested date presentation format.
 * @param[out] dest    Pointer to destination character buffer.
 * @param[in]  max_len Capacity of destination buffer in bytes.
 *
 * @return ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.
 */
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char *dest, size_t max_len);

#ifdef __cplusplus
}
#endif
