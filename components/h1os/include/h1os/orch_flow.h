/**
 * @file orch_flow.h
 * @brief Layer 3: Execution flow arbiter and thermal lockout MUX
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "h1os/orch_state.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Execution flow lifecycle pathways.
 */
typedef enum {
    ORCH_FLOW_BOOT = 0,         /**< Initial system boot / cold power-on reset.                 */
    ORCH_FLOW_A_SAMPLE,         /**< Headless sub-3ms sensor sample burst.                      */
    ORCH_FLOW_B_MAIN_WAKE,      /**< Full interactive UI wake / Button wake / RTC timer expiry. */
    ORCH_FLOW_BOOTLOADER_JUMP,  /**< ROM bootloader download mode transition.                   */
    ORCH_FLOW_CRITICAL_OFF      /**< Low battery shutdown or physical power cut.                */
} orch_flow_type_t;

/**
 * @brief Evaluate hardware reset cause and RTC state to determine execution flow.
 *
 * @return Selected execution flow type.
 */
orch_flow_type_t orch_flow_determine_wakeup(void);

/**
 * @brief Check whether thermal self-heating lockout is currently active.
 *
 * @return True if radio/CPU self-heating is actively decaying.
 */
bool orch_flow_is_thermal_lockout(void);

/**
 * @brief Query current filtered Tri-Node environmental telemetry.
 *
 * @param[out] out_temp_c Pointer to store ambient temperature in Celsius.
 * @param[out] out_rh_pct Pointer to store ambient relative humidity %.
 * @param[out] out_dew_c  Pointer to store calculated dew point in Celsius.
 *
 * @return ESP_OK on success, or ESP_ERR_INVALID_ARG if any pointer is NULL.
 */
esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c);

/**
 * @brief Prepare platform subsystems and enter target low-power sleep state.
 *
 * @param[in] sleep_sec Target sleep duration in seconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec);

#ifdef __cplusplus
}
#endif
