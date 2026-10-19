/**
 * @file hal_io.h
 * @brief Layer 1: Base pinout, power latch, and sleep pad hold driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "h1os/hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t hal_io_early_init(void);

esp_err_t hal_io_set_led(bool on);

esp_err_t hal_led_pwm_init(void);

esp_err_t hal_led_set_brightness(uint8_t brightness_pct);

esp_err_t hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms);

esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms);

esp_err_t hal_led_stop_breathing(void);

bool hal_led_is_breathing(void);

esp_err_t hal_led_pwm_deinit(void);

esp_err_t hal_io_release_power_latch(void);

hal_btn_mask_t hal_io_read_buttons(void);

static inline bool hal_io_button_is_pressed(gpio_num_t pin)
{
    return (gpio_get_level(pin) == 0) ? true : false;
}

esp_err_t hal_io_isolate_sleep_pads(void);

esp_err_t hal_io_release_pad_holds(void);

bool hal_check_usb_ll(void);

#ifdef __cplusplus
}
#endif
