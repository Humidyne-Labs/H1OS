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

typedef enum {
    ORCH_FLOW_BOOT = 0,
    ORCH_FLOW_A_SAMPLE,
    ORCH_FLOW_B_MAIN_WAKE,
    ORCH_FLOW_BOOTLOADER_JUMP,
    ORCH_FLOW_CRITICAL_OFF
} orch_flow_type_t;

orch_flow_type_t orch_flow_determine_wakeup(void);

bool orch_flow_is_thermal_lockout(void);

esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c);

esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec);

#ifdef __cplusplus
}
#endif
