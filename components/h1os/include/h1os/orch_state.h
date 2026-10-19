/**
 * @file orch_state.h
 * @brief Layer 3: Persistent RTC Slow SRAM State & Ring Buffer Manager
 *
 * Persists system lifecycle counters, ULP coprocessor dispatch reasons, calibration
 * parameters, dynamic psychrometric floors, and a 32-sample Tri-Node ring buffer.
 * Total memory footprint is strictly < 512 bytes in RTC Slow Memory.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ORCH_RTC_MAGIC 0x534C4154 /* ASCII "SLAT" */
#define ORCH_RING_CAPACITY 32

/** @brief ULP Dispatch Reason */
typedef enum {
    ULP_DISPATCH_NONE = 0,  ///< None
    ULP_DISPATCH_SENSOR_SAMPLE,  ///< Sensor sample
    ULP_DISPATCH_MAIN_WAKE,  ///< Main wake
    ULP_DISPATCH_CRITICAL_SHUTDOWN,  ///< Shutdown
    ULP_DISPATCH_BOOTLOADER_JUMP,  ///< Bootloader
    ULP_DISPATCH_POWER_OFF  ///< Power off
} orch_ulp_dispatch_t;

#define SAMPLE_FLAG_VALID_COLD 0x01 /* Bit 0: Passed successive-sample <= 0.20 C thermal delta gate */
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02 /* Bit 1: Consecutive settled pair verified                     */
#define SAMPLE_DELTA_GATE_CENTI_C 20 /* Max successive sample delta: 20 centi-°C (0.20 °C)           */

typedef struct {
    int16_t shtc3_temp_centi_c;  ///< SHTC3 temp (centi-°C: 2350 = 23.50 °C)
    uint16_t shtc3_rh_centi_pct;  ///< SHTC3 RH (centi-%: 5520 = 55.20 %)
    int16_t mcu_tsens_centi_c;  ///< Internal MCU junction TSENS (centi-°C)
    int16_t epd_glass_centi_c;  ///< SSD1681 glass thermistor (centi-°C)
    uint32_t timestamp_sec;  ///< POSIX epoch or relative seconds
    uint8_t quality_flags;  ///< Bit 0: SAMPLE_FLAG_VALID_COLD, Bit 1: SAMPLE_FLAG_THERMAL_SETTLED
    uint8_t _pad[3];  ///< Padding for 32-bit alignment
} orch_tri_node_sample_t;

typedef struct {
    uint32_t magic;  ///< Magic word
    uint32_t boot_count;  ///< Boot count
    uint32_t wake_count;  ///< Wake count
    uint8_t flags;  ///< Flags
    uint8_t ulp_dispatch_reason;  ///< ULP dispatch reason
    uint16_t last_vbat_mv;  ///< Last vbat mv

    uint32_t sample_interval_sec;  ///< Sample interval sec
    uint32_t flow_b_period_sec;  ///< Flow B period sec
    uint32_t wake_timestamp_epoch;  ///< Wake timestamp epoch

    /* ULP coprocessor battery ADC calibration parameters */
    uint32_t ulp_vbat_scale;  ///< ULP vbat scale
    int32_t ulp_vbat_offset_mv;  ///< ULP vbat offset mv

    /* E-Paper anti-ghosting quota counter (survives deep sleep) */
    uint16_t epd_partial_refresh_count;  ///< EPD partial refresh count
    uint16_t valid_trend;  ///< Valid trend

    /* Valid sample window bounds and pre-display glass reference (centi-°C) */
    int16_t amb_floor_temp_centi_c; /* Alias / Valid Window Floor (window_low)    */
    int16_t window_low_temp_centi_c; /* Valid Window Floor (min over valid ring)   */
    int16_t window_high_temp_centi_c; /* Valid Window Ceiling (max over valid ring) */
    int16_t last_glass_temp_centi_c; /* Pre-display SSD1681 0x1B glass reading     */

    /* Short-term window averages & Long-term historical EWMA (temp_historical) */
    float window_avg_shtc3_c;  ///< Window avg shtc3 c
    float window_avg_die_c;  ///< Window avg die c
    float temp_historical_c; /* Long-term runtime light EWMA temperature       */
    float rh_historical_pct; /* Long-term runtime light EWMA relative humidity */

    /* Active ambient & psychrometric outputs (computed on Flow B) */
    float reconstructed_amb_temp_c;  ///< Reconstructed amb temp c
    float reconstructed_amb_rh_pct;  ///< Reconstructed amb rh pct
    float reconstructed_dew_point_c;  ///< Reconstructed dew point c
    float vapor_pressure_hpa;  ///< Vapor pressure hpa

    /* Tri-Node composite mean & 0-100% linear confidence score */
    float trinode_temp_c;  ///< Trinode temp c
    float trinode_delta_c;  ///< Trinode delta c
    uint8_t trinode_confidence_pct;  ///< Trinode confidence pct
    bool ewma_inited;  ///< EWMA inited
    int16_t tsens_cal_centi_c; /* Per-die factory eFuse TSENS calibration (centi-°C) */

    /* Application lifecycle stage and scratchpad (replaces legacy bsp_rtc_mem) */
    uint8_t app_stage;  ///< App stage
    uint8_t scratchpad_len;  ///< Scratchpad len
    uint8_t scratchpad[32];  ///< Scratchpad

    /* 32-sample telemetry ring buffer (32 * 16 bytes = 512 bytes) */
    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY];  ///< Ring buffer

    uint8_t ring_head;  ///< Ring head
    uint32_t total_samples;  ///< Total samples
} orch_persisted_state_t;

/* Status Flags Bitmask */
#define ORCH_FLAG_NONE 0
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)

/**
 * @brief Retrieve pointer to the persistent state in RTC Slow Memory.
 * Initializes default structure on boot magic mismatch.
 */
orch_persisted_state_t *orch_state_get(void);

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
 * @brief Get the latest committed sample from the ring buffer.
 *
 * @param[out] out_sample Destination pointer.
 * @return true if reading present, false if buffer empty.
 */
bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample);

/**
 * @brief Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.
 * Falls back to the latest sample if no sample has been marked valid yet.
 *
 * @param[out] out_sample Destination pointer.
 * @return true if a sample is returned, false if buffer empty.
 */
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample);

#ifdef __cplusplus
}
#endif
