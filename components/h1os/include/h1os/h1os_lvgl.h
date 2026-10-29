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
 * @brief Asynchronous UI mutation callback signature executed on Core 1 inside the LVGL context.
 *
 * @param[in] arg User argument pointer passed to h1os_ui_post().
 */
typedef void (*h1os_ui_fn_t)(void *arg);

/**
 * @brief Message envelope for the Core 0 -> Core 1 asynchronous UI mutation queue.
 */
typedef struct {
    h1os_ui_fn_t fn;  /**< Callback function to execute on Core 1 under LVGL lock. */
    void        *arg; /**< Opaque payload pointer passed to fn.                    */
} h1os_ui_msg_t;

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
 * @param[in] priority FreeRTOS task priority (e.g. 5).
 * @param[in] core_id  CPU core affinity (0 or 1).
 *
 * @return
 *   - ESP_OK: Task created and running.
 *   - ESP_FAIL: Task creation failed.
 */
esp_err_t h1os_lvgl_start(int32_t priority, int32_t core_id);

/**
 * @brief Stop the LVGL background task.
 *
 * Signals the event loop to terminate cleanly via event-driven semaphore synchronization and waits for task exit.
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
 * @brief Enqueue an asynchronous UI mutation callback to execute on Core 1 (`h1os_lvgl_port_task`).
 *
 * @details Thread-safe, lock-free producer API backed by a 16-slot static FreeRTOS queue.
 *          Immediately wakes the Core 1 LVGL task via `xTaskNotifyGive()` to drain the queue
 *          inside its `h1os_lvgl_lock()` critical section before `lv_timer_handler()`.
 *
 * @param[in] fn         Callback function to execute on Core 1. Must not be NULL.
 * @param[in] arg        Opaque argument passed to fn.
 * @param[in] timeout_ms Maximum time to wait if the 16-slot queue is full (0 for non-blocking).
 *
 * @return
 *   - ESP_OK: Mutation successfully queued and Core 1 notified.
 *   - ESP_ERR_INVALID_ARG: fn is NULL.
 *   - ESP_ERR_INVALID_STATE: LVGL subsystem not initialized.
 *   - ESP_ERR_TIMEOUT: Queue full after timeout_ms.
 */
esp_err_t h1os_ui_post(h1os_ui_fn_t fn, void *arg, uint32_t timeout_ms);

/**
 * @brief Arm a pre-flush inbound synchronization gate on Core 1 for single-refresh coalescing.
 *
 * @details When `wait_ms > 0`, the Core 1 LVGL task defers `lv_timer_handler()` (and thus physical
 *          SSD1681 display flushing) for up to `wait_ms` or until `h1os_lvgl_release_sync_gate()`
 *          is called by `h1os_sync_notify_complete()`, ensuring initial `on_wake()` widgets and
 *          inbound `on_sync()` mutations coalesce into a single physical e-Paper refresh.
 *
 * @param[in] wait_ms Maximum gate hold duration in milliseconds (0 disables the gate).
 */
void h1os_lvgl_set_sync_gate(uint32_t wait_ms);

/**
 * @brief Release the pre-flush inbound synchronization gate and wake Core 1 immediately.
 */
void h1os_lvgl_release_sync_gate(void);

/**
 * @brief Check if the LVGL display pipeline has pending render/flush tasks.
 *
 * @return True if display driver is currently flushing, UI queue has items, or widgets are invalidated.
 */
bool h1os_lvgl_has_pending_tasks(void);

/**
 * @brief Event-driven wait until the LVGL display pipeline completes all pending renders and flushes.
 *
 * Blocks on a static binary semaphore signaled immediately by the Core 1 LVGL task when idle,
 * eliminating 20 ms polling loops during pre-sleep teardown.
 *
 * @param[in] timeout_ms Maximum wait time in milliseconds.
 *
 * @return ESP_OK when pipeline is idle, ESP_ERR_TIMEOUT on expiration.
 */
esp_err_t h1os_lvgl_wait_idle(uint32_t timeout_ms);

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
