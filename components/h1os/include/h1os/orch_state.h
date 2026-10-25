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
#define ORCH_RTC_MAGIC              0x534C4154 /**< RTC state validation magic word ('SLAT').                  */
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

#define SAMPLE_FLAG_VALID_COLD      0x01 /**< Steady-state sample captured during quiescent sleep.   */
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02 /**< Thermal plateau settled indicator.                     */
#define SAMPLE_DELTA_GATE_CENTI_C   20   /**< Maximum allowable drift for steady state (0.20°C).     */
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
 * @brief Compact 12-byte atomic battery autonomy runtime blob committed to Flash NVS.
 */
typedef struct {
    uint32_t total_sleep_sec;   /**< Cumulative seconds spent in deep sleep.                        */
    uint32_t total_app_run_ms;  /**< Cumulative milliseconds executing main processor application.  */
    uint16_t initial_soc_x10;   /**< State of Charge at start of discharge lap in tenths of % (0..1000). */
    uint16_t reserved;          /**< 16-bit alignment padding / reserved.                           */
} orch_nvs_runtime_blob_t;

/**
 * @brief Master persistent state block allocated in RTC Slow SRAM.
 *
 * Retained across all deep sleep cycles and wake stub executions.
 */
typedef struct {
    uint32_t magic;                     /**< State validation magic word (ORCH_RTC_MAGIC).                         */
    uint32_t boot_count;                /**< Total monotonic system boot cycles.                                   */
    uint32_t wake_count;                /**< Monotonic deep sleep wake cycle count.                                */
    uint8_t flags;                      /**< Operating state flags (ORCH_FLAG_*).                                  */
    uint8_t ulp_dispatch_reason;        /**< Reason code from last ULP coprocessor dispatch.                       */
    uint16_t last_vbat_mv;              /**< Last sampled battery terminal voltage in millivolts.                  */
    uint16_t boot_vbat_mv;              /**< Initial non-USB battery voltage captured on boot in millivolts.       */

    uint32_t sample_interval_sec;       /**< Interval between Flow A sensor samples in seconds.                    */
    uint32_t flow_b_period_sec;         /**< Interval between Flow B display refreshes in seconds.                 */
    uint32_t last_ewma_sample_seq;      /**< Sample sequence number of last processed EWMA & ring debug update.    */

    uint16_t epd_partial_refresh_count; /**< Consecutive differential partial refreshes on EPD.                    */
    uint16_t valid_trend;               /**< Monotonic count of consecutive settled steady-state samples.          */

    int16_t window_low_temp_centi_c;    /**< Valid Window Floor (minimum over active window) in centi-°C.          */
    int16_t window_high_temp_centi_c;   /**< Valid Window Ceiling (maximum over active window) in centi-°C.        */
    int16_t last_glass_temp_centi_c;    /**< Last sampled EPD glass temperature in centi-°C.                       */

    float window_avg_shtc3_c;           /**< Short-term valid SHTC3 window average in degrees Celsius.             */
    float window_avg_die_c;             /**< Short-term valid MCU Die window average in degrees Celsius.           */
    float temp_historical_c;            /**< Long-term light EWMA baseline temperature.                            */
    float rh_historical_pct;            /**< Long-term light EWMA baseline relative humidity.                      */

    float ambient_temp_c;               /**< Trusted steady-state SHTC3 ambient temperature in °C.                 */
    float ambient_rh_pct;               /**< Trusted steady-state SHTC3 ambient relative humidity in %.            */
    float dew_point_c;                  /**< Calculated dew point temperature in °C.                               */
    float vapor_pressure_hpa;           /**< Calculated water vapor partial pressure in hPa.                       */

    float trinode_temp_c;               /**< Tri-Node verification average: (T_valid + T_die + T_glass) / 3.0.     */
    float trinode_delta_c;              /**< Cross-sensor verification delta: T_valid - T_trinode.                 */
    uint8_t trinode_confidence_pct;     /**< 0-100% cross-sensor range verification score.                         */
    bool ewma_inited;                   /**< True if EWMA filters have been seeded with initial samples.           */
    int16_t tsens_cal_centi_c;          /**< Factory calibrated TSENS eFuse offset in centi-degrees Celsius.       */
    int16_t tsens_offset_centi_c;       /**< Pre-computed TSENS fixed-point intercept (2052 + tsens_cal_centi_c).  */

    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY]; /**< Circular ring buffer of historical telemetry samples.    */

    uint8_t ring_head;                  /**< Write head index into circular ring buffer (0..ORCH_RING_CAPACITY-1). */
    uint32_t total_samples;             /**< Total lifetime samples recorded across all sessions.                  */

    uint32_t total_sleep_sec;           /**< Cumulative seconds spent in deep sleep.                                */
    uint32_t total_app_run_ms;          /**< Cumulative milliseconds executing main processor application.          */
    uint16_t initial_soc_x10;           /**< State of Charge at start of discharge lap in tenths of % (0..1000).   */
    uint8_t  _pad_soc[2];               /**< Alignment padding to 32-bit boundary.                                  */
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
volatile orch_persisted_state_t *orch_state_get(void);

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

/**
 * @brief Save cumulative battery autonomy runtimes to Flash NVS.
 */
void orch_state_save_runtimes_to_nvs(void);

/**
 * @brief Restore cumulative battery autonomy runtimes from Flash NVS.
 */
void orch_state_load_runtimes_from_nvs(void);

/**
 * @brief Reset discharge lap runtimes on charger unplug or cycle anchor.
 *
 * @param[in] current_soc_x10 Starting SoC in tenths of a percent (0..1000) for the new discharge lap.
 */
void orch_state_reset_discharge_lap(uint16_t current_soc_x10);

#ifdef __cplusplus
}
#endif
