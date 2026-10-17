/**
 * @file h1os_time.h
 * @brief Layer 4: System Time Services, Timezone Management & External SNTP Bridge
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Time Format */
typedef enum {
    H1OS_TIME_FMT_24H_SEC = 0, ///< "14:35:08"
    H1OS_TIME_FMT_24H_MIN = 1, ///< "14:35"
    H1OS_TIME_FMT_12H_SEC = 2, ///< "02:35:08 PM"
    H1OS_TIME_FMT_12H_MIN = 3, ///< "02:35 PM"
} h1os_time_format_t;

/** @brief Date Format */
typedef enum {
    H1OS_DATE_FMT_MM_DD_YY     = 0, ///< "09/26/26"
    H1OS_DATE_FMT_DOW          = 1, ///< "Saturday"
    H1OS_DATE_FMT_MM_DD_YY_DOW = 2, ///< "09/26/26 Saturday"
} h1os_date_format_t;

/**
 * @brief Callback for external network/remote time acquisition (SNTP, GPS, BLE).
 */
typedef esp_err_t (*h1os_time_sync_cb_t)(uint32_t timeout_ms, void *user_data);

/**
 * @brief Configure POSIX timezone string.
 */
esp_err_t h1os_time_set_timezone(const char *tz_str);

/**
 * @brief Register external time sync callback.
 */
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data);

/**
 * @brief Trigger time synchronization using registered callback.
 */
esp_err_t h1os_time_sync_now(uint32_t timeout_ms);

/**
 * @brief Synchronize internal system clock into PCF85063A RTC hardware.
 */
esp_err_t h1os_time_sync_system_to_rtc(void);

/**
 * @brief Synchronize PCF85063A RTC hardware into internal POSIX system clock.
 */
esp_err_t h1os_time_sync_rtc_to_system(void);

/**
 * @brief Format current local time into destination buffer.
 */
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char *dest, size_t max_len);

/**
 * @brief Format current local date into destination buffer.
 */
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char *dest, size_t max_len);

#ifdef __cplusplus
}
#endif
