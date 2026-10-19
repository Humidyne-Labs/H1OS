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

/**
 * @brief Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.
 *
 * Configures the bilevel draw buffer, registers the display flush callback,
 * and sets up keypad input navigation.
 *
 * @param[in] is_wake_cycle True if resuming from sleep (enables differential partial flush).
 *
 * @return
 *   - ESP_OK: LVGL core initialized successfully.
 *   - ESP_ERR_NO_MEM: Insufficient memory for draw buffer allocation.
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
 *
 * Spawns the dedicated presentation task pinned to Core 1 for decoupled UI rendering.
 *
 * @param[in] priority FreeRTOS task priority (e.g. 4).
 * @param[in] core_id  CPU core affinity (0 or 1).
 *
 * @return
 *   - ESP_OK: Task created and running.
 *   - ESP_FAIL: Task creation failed.
 */
esp_err_t h1os_lvgl_start(int priority, int core_id);

/**
 * @brief Stop the LVGL background task.
 *
 * Signals the event loop to terminate cleanly and waits for task exit.
 *
 * @return
 *   - ESP_OK: Task stopped successfully.
 */
esp_err_t h1os_lvgl_stop(void);

/**
 * @brief Acquire LVGL reentrant mutex lock.
 *
 * Must be acquired before creating, modifying, or deleting any LVGL widgets or objects
 * from tasks other than the LVGL event loop.
 *
 * @param[in] timeout_ms Mutex acquisition timeout in milliseconds.
 *
 * @return True if mutex was successfully acquired within timeout, false otherwise.
 */
bool h1os_lvgl_lock(uint32_t timeout_ms);

/**
 * @brief Release LVGL reentrant mutex lock.
 *
 * Releases the mutex acquired via h1os_lvgl_lock().
 */
void h1os_lvgl_unlock(void);

/**
 * @brief Check if the LVGL display pipeline has pending render/flush tasks.
 *
 * @return True if display driver is currently flushing or widgets are invalidated.
 */
bool h1os_lvgl_has_pending_tasks(void);

/**
 * @brief Retrieve the LVGL keypad input device handle.
 *
 * @return Pointer to registered keypad indev instance for focus group binding.
 */
lv_indev_t *h1os_lvgl_get_indev(void);

#include "h1os_fonts.h"

#ifdef __cplusplus
}
#endif
