/**
 * @file h1os_lvgl.h
 * @brief Layer 4: LVGL v9 Graphics Port, Keypad Indev & Interactive Event Loop
 *
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

/**
 * @brief Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.
 *
 * @param[in] is_wake_cycle True if resuming from sleep (enables differential partial flush).
 */
esp_err_t h1os_lvgl_init(bool is_wake_cycle);

/**
 * @brief Explicitly override whether the first flush executes a full or partial refresh.
 *
 * @param[in] full_refresh True for full OTP flashing refresh, False for differential partial.
 */
void h1os_lvgl_set_first_flush_mode(bool full_refresh);

/**
 * @brief Start the LVGL background FreeRTOS task.
 */
esp_err_t h1os_lvgl_start(int priority, int core_id);

/**
 * @brief Stop the LVGL background task.
 */
esp_err_t h1os_lvgl_stop(void);

/**
 * @brief Acquire LVGL reentrant mutex lock.
 */
bool h1os_lvgl_lock(uint32_t timeout_ms);

/**
 * @brief Release LVGL reentrant mutex lock.
 */
void h1os_lvgl_unlock(void);

/**
 * @brief Check if the LVGL display pipeline has pending render/flush tasks.
 */
bool h1os_lvgl_has_pending_tasks(void);

/**
 * @brief Retrieve the LVGL keypad input device handle.
 */
lv_indev_t *h1os_lvgl_get_indev(void);

/* =========================================================================
 * 1-Bit Packed Binary Typography Suite
 * ========================================================================= */
#include "h1os_fonts.h"

#ifdef __cplusplus
}
#endif
