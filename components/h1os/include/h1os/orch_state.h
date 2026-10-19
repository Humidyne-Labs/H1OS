/**
 * @file orch_state.h
 * @brief Layer 3: Persistent RTC Slow SRAM state and ring buffer manager
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off
#define ORCH_RTC_MAGIC              0x534C4154
#define ORCH_RING_CAPACITY          32

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SAMPLE,
    ULP_DISPATCH_MAIN_WAKE,
    ULP_DISPATCH_CRITICAL_SHUTDOWN,
    ULP_DISPATCH_BOOTLOADER_JUMP,
    ULP_DISPATCH_POWER_OFF
} orch_ulp_dispatch_t;

#define SAMPLE_FLAG_VALID_COLD      0x01
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02
#define SAMPLE_DELTA_GATE_CENTI_C   20
// clang-format on

typedef struct {
    int16_t shtc3_temp_centi_c;
    uint16_t shtc3_rh_centi_pct;
    int16_t mcu_tsens_centi_c;
    int16_t epd_glass_centi_c;
    uint32_t timestamp_sec;
    uint8_t quality_flags;
    uint8_t _pad[3];
} orch_tri_node_sample_t;

typedef struct {
    uint32_t magic;
    uint32_t boot_count;
    uint32_t wake_count;
    uint8_t flags;
    uint8_t ulp_dispatch_reason;
    uint16_t last_vbat_mv;

    uint32_t sample_interval_sec;
    uint32_t flow_b_period_sec;
    uint32_t wake_timestamp_epoch;

    uint32_t ulp_vbat_scale;
    int32_t ulp_vbat_offset_mv;

    uint16_t epd_partial_refresh_count;
    uint16_t valid_trend;

    int16_t amb_floor_temp_centi_c;
    int16_t window_low_temp_centi_c;
    int16_t window_high_temp_centi_c;
    int16_t last_glass_temp_centi_c;

    float window_avg_shtc3_c;
    float window_avg_die_c;
    float temp_historical_c;
    float rh_historical_pct;

    float reconstructed_amb_temp_c;
    float reconstructed_amb_rh_pct;
    float reconstructed_dew_point_c;
    float vapor_pressure_hpa;

    float trinode_temp_c;
    float trinode_delta_c;
    uint8_t trinode_confidence_pct;
    bool ewma_inited;
    int16_t tsens_cal_centi_c;

    uint8_t app_stage;
    uint8_t scratchpad_len;
    uint8_t scratchpad[32];

    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY];

    uint8_t ring_head;
    uint32_t total_samples;
} orch_persisted_state_t;

#define ORCH_FLAG_NONE 0
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)

orch_persisted_state_t *orch_state_get(void);

void orch_state_reset(void);

void orch_state_push_sample(const orch_tri_node_sample_t *sample);

bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample);

bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample);

#ifdef __cplusplus
}
#endif
