/**
 * @file sub_display.h
 * @brief Layer 2: SSD1681 1.54" 200x200 monochrome e-Paper display manager
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EPD_WIDTH 200
#define EPD_HEIGHT 200

#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)

esp_err_t sub_display_init(bool is_wake_cycle);

uint8_t *sub_display_get_framebuffer(void);

void sub_display_clear(uint8_t color);

esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame);

esp_err_t sub_display_wait_busy(TickType_t timeout_ticks);

esp_err_t sub_display_refresh_full(void);

esp_err_t sub_display_clear_to_white_full(void);

esp_err_t sub_display_refresh_partial(void);

esp_err_t sub_display_read_glass_temp(float *out_temp_c);

esp_err_t sub_display_enter_deep_sleep(void);

#ifdef __cplusplus
}
#endif
