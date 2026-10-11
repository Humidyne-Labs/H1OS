/**
 * @file orch_state.h
 * @brief Layer 3: Persistent RTC Slow SRAM State & Ring Buffer Manager
 *
 * Persists system lifecycle counters, ULP sentinel dispatch reasons, calibration
 * parameters, dynamic psychrometric floors, and a 32-sample Tri-Node ring buffer.
 * Total memory footprint is strictly < 512 bytes in RTC Slow Memory.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ORCH_RTC_MAGIC       0x534C4154  /* ASCII "SLAT" */
#define ORCH_RING_CAPACITY    32

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SPRINT,    /* Flow A: <4ms wake stub sprint */
    ULP_DISPATCH_MAIN_WAKE,        /* Flow B: Full application / LVGL UI wake */
    ULP_DISPATCH_CRITICAL_SHUTDOWN /* Battery brownout tripwire (<3.25V) */
} orch_ulp_dispatch_t;

typedef struct {
    int16_t  shtc3_temp_centi_c;    /* SHTC3 temp (centi-°C: 2350 = 23.50 °C) */
    uint16_t shtc3_rh_centi_pct;    /* SHTC3 RH (centi-%: 5520 = 55.20 %) */
    int16_t  mcu_tsens_centi_c;     /* Internal MCU junction TSENS (centi-°C) */
    int16_t  epd_glass_centi_c;     /* SSD1681 glass thermistor (centi-°C) */
    uint32_t timestamp_sec;         /* POSIX epoch or relative seconds */
    uint8_t  quality_flags;         /* Bit 0: Cold sample, Bit 1: Thermally settled */
    uint8_t  _pad[3];
} orch_tri_node_sample_t;

typedef struct {
    uint32_t            magic;
    uint32_t            boot_count;
    uint32_t            wake_count;
    uint8_t             flags;
    uint8_t             ulp_dispatch_reason;
    uint16_t            last_vbat_mv;
    
    uint32_t            sample_interval_sec;
    uint32_t            wake_timestamp_epoch;

    /* ULP coprocessor battery ADC calibration parameters */
    uint32_t            ulp_vbat_scale;
    int32_t             ulp_vbat_offset_mv;

    /* Dynamic sliding ambient floor (minimum over recent history) */
    int16_t             amb_floor_temp_centi_c;
    int16_t             _pad;

    /* Continuous EWMA running state */
    float               reconstructed_amb_temp_c;
    float               reconstructed_amb_rh_pct;
    float               reconstructed_dew_point_c;
    float               vapor_pressure_hpa;
    bool                ewma_inited;

    /* Application lifecycle stage and scratchpad (replaces legacy bsp_rtc_mem) */
    uint8_t             app_stage;
    uint8_t             scratchpad_len;
    uint8_t             scratchpad[32];

    /* 32-sample telemetry ring buffer (32 * 16 bytes = 512 bytes) */
    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY];
    uint8_t             ring_head;
    uint32_t            total_samples;
} orch_persisted_state_t;

/* Status Flags Bitmask */
#define ORCH_FLAG_NONE              0
#define ORCH_FLAG_EPD_FRAME_VALID   (1 << 0)
#define ORCH_FLAG_CRITICAL_BATTERY  (1 << 1)
#define ORCH_FLAG_THERMAL_LOCKOUT   (1 << 2)

/**
 * @brief Retrieve pointer to the persistent state in RTC Slow Memory.
 * Initializes default structure on cold boot magic mismatch.
 */
orch_persisted_state_t* orch_state_get(void);

/**
 * @brief Reset persisted RTC state to default values.
 */
void orch_state_reset(void);

/**
 * @brief Push a new Tri-Node telemetry sample into the RTC ring buffer.
 *
 * @param[in] sample Pointer to sample data to commit.
 */
void orch_state_push_sample(const orch_tri_node_sample_t *sample);

/**
 * @brief Get the latest committed cold reading from the ring buffer.
 *
 * @param[out] out_sample Destination pointer.
 * @return true if valid reading present, false if buffer empty.
 */
bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample);

#ifdef __cplusplus
}
#endif
