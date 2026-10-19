/**
 * @file orch_flow.h
 * @brief Layer 3: Execution Flow Arbiter & Thermal Lockout MUX
 *
 * Distinguishes and arbitrates:
 *  - Flow A: Headless Sensor Sample Burst (<4ms) for zero-heat periodic telemetry.
 *  - Flow B: Full Application Wake for LVGL UI and network interactions.
 *  - Thermal Lockout MUX: Prevents self-heating bias from tainting environmental data.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "h1os/orch_state.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ORCH_FLOW_BOOT = 0,          /**< Initial system boot / power-on reset.          */
    ORCH_FLOW_A_SAMPLE,          /**< Headless sensor sample burst.                  */
    ORCH_FLOW_B_MAIN_WAKE,       /**< Full UI wake / Button wake / RTC timer expiry. */
    ORCH_FLOW_BOOTLOADER_JUMP,   /**< ROM bootloader download mode.                  */
    ORCH_FLOW_CRITICAL_OFF       /**< Low battery shutdown or power cut.             */
} orch_flow_type_t;

/**
 * @brief Inspect system wake source and arbitrate target flow.
 *
 * @return Detected flow type.
 */
orch_flow_type_t orch_flow_determine_wakeup(void);


/**
 * @brief Check whether system is in Thermal Lockout state.
 * If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.
 *
 * @return True if in lockout, False if in thermal equilibrium.
 */
bool orch_flow_is_thermal_lockout(void);

/**
 * @brief Arm or disarm thermal lockout gatekeeper.
 *
 * @param[in] enable       True to arm thermal lockout (e.g. after display refresh or Wi-Fi).
 * @param[in] duration_sec Duration of lockout in seconds (typically 30-60s).
 */
void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec);

/**
 * @brief Query current environmental telemetry through the Thermal Lockout MUX.
 *
 * If in thermal equilibrium, takes fresh sensor reading.
 * If in thermal lockout, transparently returns pristine cold reading from RTC ring buffer.
 *
 * @param[out] out_temp_c Reconstructed ambient temperature in Celsius.
 * @param[out] out_rh_pct Reconstructed ambient relative humidity in percent.
 * @param[out] out_dew_c  True dew point in Celsius.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c);

/**
 * @brief Execute coordinated 8-step sleep transition sequence to deep sleep.
 *
 * @param[in] sleep_sec Sleep duration in seconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec);

#ifdef __cplusplus
}
#endif
