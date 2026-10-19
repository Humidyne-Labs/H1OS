/**
 * @file h1os_lvgl.h
 * @brief Layer 4: LVGL v9 graphics port, keypad indev, and interactive event loop
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "lvgl.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t h1os_lvgl_init(bool is_wake_cycle);

void h1os_lvgl_set_first_flush_mode(bool full_refresh);

esp_err_t h1os_lvgl_start(int priority, int core_id);

esp_err_t h1os_lvgl_stop(void);

bool h1os_lvgl_lock(uint32_t timeout_ms);

void h1os_lvgl_unlock(void);

bool h1os_lvgl_has_pending_tasks(void);

lv_indev_t *h1os_lvgl_get_indev(void);

#include "h1os_fonts.h"

#ifdef __cplusplus
}
#endif
