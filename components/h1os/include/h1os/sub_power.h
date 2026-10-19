/**
 * @file sub_power.h
 * @brief Layer 2: Battery ADC monitoring, dynamic frequency scaling, and deep sleep engine
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

esp_err_t sub_power_init(void);

esp_err_t sub_power_deinit(void);

esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);

esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv);

esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec);

typedef enum { SUB_POWER_SLEEP_FULL_CYCLE = 0, SUB_POWER_SLEEP_FLOW_A_BURST } sub_power_sleep_mode_t;

esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);

esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);

void sub_power_cut_power_latch(void);

bool sub_power_connected_usb(void);

esp_err_t sub_power_init_dfs(bool enable_dfs);

esp_err_t sub_power_cpu_max_acquire(void);

esp_err_t sub_power_cpu_max_release(void);

#ifdef __cplusplus
}
#endif
