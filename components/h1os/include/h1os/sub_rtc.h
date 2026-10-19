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

esp_err_t sub_rtc_init(void);

esp_err_t sub_rtc_get_time(struct tm *out_time);

esp_err_t sub_rtc_set_time(const struct tm *time);

esp_err_t sub_rtc_arm_countdown(uint32_t seconds);

esp_err_t sub_rtc_cancel_countdown(void);

esp_err_t sub_rtc_get_remaining_seconds(uint32_t *out_sec);

esp_err_t sub_rtc_get_and_clear_interrupts(bool *out_alarm, bool *out_timer);

#ifdef __cplusplus
}
#endif
