/**
 * @file h1os_lvgl.h
 * @brief Layer 4: LVGL v9 Graphics Port, Keypad Indev & Interactive Event Loop
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.
 */
esp_err_t h1os_lvgl_init(void);

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

#ifdef __cplusplus
}
#endif
