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
#define ORCH_RTC_MAGIC              0x534C4154 /**< RTC state validation sentinel word ('SLAT').               */
#define ORCH_RING_CAPACITY          32         /**< Fixed capacity of historical telemetry sample ring buffer. */

/**
 * @brief ULP coprocessor dispatch wakeup reasons.
 */
typedef enum {
    ULP_DISPATCH_NONE = 0,             /**< No dispatch action required.                          */
    ULP_DISPATCH_SENSOR_SAMPLE,        /**< Headless Flow A sensor sample burst dispatch.         */
    ULP_DISPATCH_MAIN_WAKE,            /**< Interactive Flow B UI presentation wake dispatch.     */
    ULP_DISPATCH_CRITICAL_SHUTDOWN,    /**< Low-battery brownout threshold cut dispatch.          */
    ULP_DISPATCH_BOOTLOADER_JUMP,      /**< BOOT0 held down during sleep: jump to download mode.  */
    ULP_DISPATCH_POWER_OFF             /**< BAT_KEY long-press held down during sleep: power off. */
} orch_ulp_dispatch_t;

#define SAMPLE_FLAG_VALID_COLD      0x01 /**< Cold baseline sample captured before MCU self-heating. */
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02 /**< Thermal plateau settled indicator.                     */
#define SAMPLE_DELTA_GATE_CENTI_C   20   /**< Maximum allowable drift for thermal plateau (0.20°C).  */
// clang-format on

/**
 * @brief Compact 16-byte Tri-Node sample entry in RTC Slow SRAM.
 */
typedef struct {
    int16_t  shtc3_temp_centi_c;  /**< SHTC3 temperature in centi-degrees Celsius (1°C = 100).           */
    uint16_t shtc3_rh_centi_pct;  /**< SHTC3 relative humidity in centi-percent (1% = 100).              */
    int16_t  mcu_tsens_centi_c;   /**< ESP32-S3 internal TSENS die temperature in centi-degrees Celsius. */
    int16_t  epd_glass_centi_c;   /**< SSD1681 on-glass thermal sensor in centi-degrees Celsius.         */
    uint32_t timestamp_sec;       /**< Sample epoch timestamp in seconds.                                */
    uint8_t  quality_flags;       /**< Sample qualification bitmask (SAMPLE_FLAG_*).                     */
    uint8_t  _pad[3];             /**< Alignment padding to 32-bit boundary.                             */
} orch_tri_node_sample_t;

/**
 * @brief Master persistent state block allocated in RTC Slow SRAM.
 *
 * Retained across all deep sleep cycles and wake stub executions.
 */
typedef struct {
    uint32_t magic;                     /**< Sentinel validation magic word (ORCH_RTC_MAGIC).                      */
    uint32_t boot_count;                /**< Total monotonic system boot cycles.                                   */
    uint32_t wake_count;                /**< Monotonic deep sleep wake cycle count.                                */
    uint8_t flags;                      /**< Operating state flags (ORCH_FLAG_*).                                  */
    uint8_t ulp_dispatch_reason;        /**< Reason code from last ULP coprocessor dispatch.                       */
    uint16_t last_vbat_mv;              /**< Last sampled battery terminal voltage in millivolts.                  */

    uint32_t sample_interval_sec;       /**< Interval between Flow A sensor samples in seconds.                    */
    uint32_t flow_b_period_sec;         /**< Interval between Flow B display refreshes in seconds.                 */
    uint32_t wake_timestamp_epoch;      /**< POSIX timestamp of most recent system wake.                           */

    uint32_t ulp_vbat_scale;            /**< Two-point ADC slope calibration coefficient for ULP.                  */
    int32_t ulp_vbat_offset_mv;         /**< Two-point ADC offset calibration in millivolts for ULP.               */

    uint16_t epd_partial_refresh_count; /**< Consecutive differential partial refreshes on EPD.                    */
    uint16_t valid_trend;               /**< Monotonic count of consecutive settled cold samples.                  */

    int16_t amb_floor_temp_centi_c;     /**< Lowest observed ambient baseline temperature in centi-°C.             */
    int16_t window_low_temp_centi_c;    /**< Valid Window Floor (minimum over active window) in centi-°C.          */
    int16_t window_high_temp_centi_c;   /**< Valid Window Ceiling (maximum over active window) in centi-°C.        */
    int16_t last_glass_temp_centi_c;    /**< Last sampled EPD glass temperature in centi-°C.                       */

    float window_avg_shtc3_c;           /**< Short-term valid SHTC3 window average in degrees Celsius.             */
    float window_avg_die_c;             /**< Short-term valid MCU Die window average in degrees Celsius.           */
    float temp_historical_c;            /**< Long-term light EWMA baseline temperature.                            */
    float rh_historical_pct;            /**< Long-term light EWMA baseline relative humidity.                      */

    float reconstructed_amb_temp_c;     /**< Psychrometrically reconstructed ambient temperature.                  */
    float reconstructed_amb_rh_pct;     /**< Psychrometrically reconstructed ambient relative humidity.            */
    float reconstructed_dew_point_c;    /**< Reconstructed dew point temperature.                                  */
    float vapor_pressure_hpa;           /**< Conserved ambient water vapor partial pressure in hPa.                */

    float trinode_temp_c;               /**< Tri-Node consensus temperature: (T_valid + T_die + T_glass) / 3.0.    */
    float trinode_delta_c;              /**< Thermal gradient delta: T_valid - T_trinode.                          */
    uint8_t trinode_confidence_pct;     /**< 0-100% linear psychrometric confidence score.                         */
    bool ewma_inited;                   /**< True if EWMA filters have been seeded with initial samples.           */
    int16_t tsens_cal_centi_c;          /**< Factory calibrated TSENS offset in centi-degrees Celsius.             */

    uint8_t app_stage;                  /**< Application state machine stage index.                                */
    uint8_t scratchpad_len;             /**< Length of active data in user scratchpad.                             */
    uint8_t scratchpad[32];             /**< 32-byte generic persistent scratchpad for user data.                  */

    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY]; /**< Circular ring buffer of historical telemetry samples.    */

    uint8_t ring_head;                  /**< Write head index into circular ring buffer (0..ORCH_RING_CAPACITY-1). */
    uint32_t total_samples;             /**< Total lifetime samples recorded across all sessions.                  */
} orch_persisted_state_t;

// clang-format off
#define ORCH_FLAG_NONE              0        /**< No persistent flags active.                             */
#define ORCH_FLAG_EPD_FRAME_VALID   (1 << 0) /**< Flash partition contains valid preserved display frame. */
#define ORCH_FLAG_CRITICAL_BATTERY  (1 << 1) /**< Battery below brownout threshold.                       */
#define ORCH_FLAG_THERMAL_LOCKOUT   (1 << 2) /**< Self-heating lockout active.                            */
// clang-format on

/**
 * @brief Retrieve pointer to persistent state structure in RTC Slow SRAM.
 *
 * Automatically initializes default values if magic word is invalid or corrupted.
 *
 * @return Pointer to persistent state block in RTC Slow Memory.
 */
orch_persisted_state_t *orch_state_get(void);

/**
 * @brief Reset persisted state in RTC Slow Memory to clean factory defaults.
 */
void orch_state_reset(void);

/**
 * @brief Push a new sample into the RTC circular ring buffer.
 *
 * @param[in] sample Pointer to sample struct to store.
 */
void orch_state_push_sample(const orch_tri_node_sample_t *sample);

/**
 * @brief Retrieve the most recent sample from the ring buffer.
 *
 * @param[out] out_sample Destination struct for sample copy. Must not be NULL.
 *
 * @return True if a sample was retrieved, false if ring buffer is empty.
 */
bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample);

/**
 * @brief Retrieve the most recent thermally settled, valid sample from the ring buffer.
 *
 * @param[out] out_sample Destination struct for sample copy. Must not be NULL.
 *
 * @return True if a valid settled sample was located, false otherwise.
 */
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample);

#ifdef __cplusplus
}
#endif
