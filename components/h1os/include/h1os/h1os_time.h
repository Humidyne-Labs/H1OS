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

typedef enum {
    H1OS_TIME_FMT_24H_SEC = 0,
    H1OS_TIME_FMT_24H_MIN = 1,
    H1OS_TIME_FMT_12H_SEC = 2,
    H1OS_TIME_FMT_12H_MIN = 3,
} h1os_time_format_t;

typedef enum {
    H1OS_DATE_FMT_MM_DD_YY = 0,
    H1OS_DATE_FMT_DOW = 1,
    H1OS_DATE_FMT_MM_DD_YY_DOW = 2,
} h1os_date_format_t;

typedef esp_err_t (*h1os_time_sync_cb_t)(uint32_t timeout_ms, void *user_data);

esp_err_t h1os_time_set_timezone(const char *tz_str);

esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data);

esp_err_t h1os_time_sync_now(uint32_t timeout_ms);

esp_err_t h1os_time_sync_system_to_rtc(void);

esp_err_t h1os_time_sync_rtc_to_system(void);

esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char *dest, size_t max_len);

esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char *dest, size_t max_len);

#ifdef __cplusplus
}
#endif
