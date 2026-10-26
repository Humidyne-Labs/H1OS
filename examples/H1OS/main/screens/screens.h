/**
 * @file screens.h
 * @brief H1OS showcase application modular screen layouts header
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "h1os/h1os.h"
#include "lvgl.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define H1OS_NUM_SCREENS 5 /**< Total number of carousel screen pages. */

/**
 * @brief Showcase application screen page identifiers.
 */
typedef enum {
    H1OS_SCREEN_ENV_DASH = 0,     /**< Screen 1: Primary environmental dashboard telemetry.        */
    H1OS_SCREEN_PSYCHROMETRICS,   /**< Screen 2: Psychrometric invariants and dew point metrics.   */
    H1OS_SCREEN_THERMAL_NODES,    /**< Screen 3: TriNode sensor cross-correlation and delta.       */
    H1OS_SCREEN_SYSTEM_HEALTH,    /**< Screen 4: Battery autonomy, voltage, and system health.     */
    H1OS_SCREEN_DIAGNOSTICS       /**< Screen 5: Verbose hardware register and memory diagnostics. */
} h1os_screen_id_t;

/**
 * @brief Construct standardized 200x200 monochrome base layout frame with title and header.
 *
 * @param[in] title    Screen page header title string.
 * @param[in] page_str Page counter indicator string (e.g. "1/5").
 * @param[in] event_cb Keypad navigation event callback.
 *
 * @return Pointer to created base container screen object.
 */
lv_obj_t *screen_base_create(const char *title, const char *page_str, lv_event_cb_t event_cb);

/**
 * @brief Update the interactive session badge indicator in the top header.
 *
 * Inverts the top-right pill to visually distinguish interactive session from unattended sleep.
 *
 * @param[in] is_awake True for interactive awake session, false for unattended sleep.
 */
void screen_base_set_awake_badge(bool is_awake);

/**
 * @brief Render Screen 1: Environmental Dashboard display page.
 *
 * @param[in] telem       Current validated environmental telemetry snapshot.
 * @param[in] cycle_count Monotonic update cycle counter.
 * @param[in] event_cb    Keypad event callback for user navigation.
 */
void screen_env_dash_render(const h1os_telemetry_t *telem, uint32_t cycle_count, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 2: Psychrometric engine and invariant metrics page.
 *
 * @param[in] telem    Current validated environmental telemetry snapshot.
 * @param[in] event_cb Keypad event callback.
 */
void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 3: TriNode sensor cross-correlation and delta page.
 *
 * @param[in] telem    Current validated environmental telemetry snapshot.
 * @param[in] event_cb Keypad event callback.
 */
void screen_thermal_nodes_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 4: System health, autonomy, and power page.
 *
 * @param[in] telem    Current validated environmental telemetry snapshot.
 * @param[in] event_cb Keypad event callback.
 */
void screen_system_health_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 5: Verbose system diagnostics page.
 *
 * @param[in] telem    Current validated environmental telemetry snapshot.
 * @param[in] event_cb Keypad event callback.
 */
void screen_diagnostics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

#ifdef __cplusplus
}
#endif
