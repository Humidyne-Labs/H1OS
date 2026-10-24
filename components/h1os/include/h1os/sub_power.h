/**
 * @file sub_power.h
 * @brief Layer 2: Battery ADC monitoring, dynamic frequency scaling, and deep sleep engine
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "h1os/hal_types.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Deep sleep cycle execution modes.
 */
typedef enum {
    SUB_POWER_SLEEP_FULL_CYCLE = 0,   /**< Normal Flow B sleep: arms PCF85063A countdown & resets slice_counter.       */
    SUB_POWER_SLEEP_FLOW_A_BURST      /**< Flow A sample sleep: preserves running PCF85063A countdown & slice_counter. */
} sub_power_sleep_mode_t;

/**
 * @brief Battery operational state machine.
 */
typedef enum {
    H1OS_BATTERY_DISCHARGING = 0, /**< Normal autonomous battery discharge.       */
    H1OS_BATTERY_CHARGING,        /**< Voltage rising over consecutive reads.      */
    H1OS_BATTERY_CHARGED,         /**< Saturated voltage (>=4180 mV) or USB host.  */
} h1os_battery_state_t;

/**
 * @brief Empirical battery autonomy metrics over total elapsed runtime.
 */
typedef struct {
    float avg_draw_ma;          /**< Average current draw over total elapsed runtime in mA.       */
    float autonomy_days;        /**< Remaining days at current duty cycle (-1.0f if calibrating). */
    float mah_spent_lap;        /**< Total mAh consumed since initial_soc_x10.                    */
} h1os_autonomy_metrics_t;

/**
 * @brief Retrieve calibrated resting battery voltage, SoC percentage, and charge state.
 *
 * @param[out] out_mv    Battery terminal voltage in millivolts.
 * @param[out] out_pct   State-of-charge percentage (0..100%).
 * @param[out] out_state Battery operational state (DISCHARGING, CHARGING, CHARGED).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_get_battery_status(uint16_t *out_mv,
                                       uint8_t *out_pct,
                                       h1os_battery_state_t *out_state);

/**
 * @brief Map battery terminal voltage to State-of-Charge in tenths of a percent (0..1000 = 0.0%..100.0%).
 *
 * @param[in] mv Terminal voltage in millivolts.
 *
 * @return State of charge in tenths of a percent (0 to 1000).
 */
uint16_t sub_power_mv_to_soc_tenths(uint16_t mv);

/**
 * @brief Calculate empirical battery autonomy metrics over total elapsed runtime.
 *
 * @param[in]  initial_soc_x10 Starting SoC for the current discharge lap in tenths of a % (0..1000).
 * @param[in]  current_soc_x10 Current evaluated SoC in tenths of a % (0..1000).
 * @param[in]  total_sleep_sec Cumulative deep sleep time in seconds.
 * @param[in]  total_app_ms    Cumulative main processor active runtime in milliseconds.
 * @param[out] out_metrics     Destination structure for calculated autonomy metrics.
 */
void sub_power_calc_autonomy(uint16_t initial_soc_x10,
                             uint16_t current_soc_x10,
                             uint32_t total_sleep_sec,
                             uint32_t total_app_ms,
                             h1os_autonomy_metrics_t *out_metrics);

/**
 * @brief Initialize battery ADC channel and calibration engine.
 *
 * Configures ADC1 Channel 3 on GPIO 4 with curve fitting calibration.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_init(void);

/**
 * @brief Deinitialize battery ADC driver.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_deinit(void);

/**
 * @brief Sample current battery terminal voltage and calculate state-of-charge.
 *
 * @param[out] out_mv  Pointer to store sampled voltage in millivolts.
 * @param[out] out_pct Pointer to store state-of-charge percentage (0..100%).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);

/**
 * @brief Retrieve two-point calibration parameters for ULP coprocessor ADC readings.
 *
 * @param[out] out_scale     Pointer to store scale multiplier.
 * @param[out] out_offset_mv Pointer to store offset in millivolts.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv);

/**
 * @brief Initialize ULP-RISC-V coprocessor firmware for background monitoring.
 *
 * @param[in] flow_a_period_sec Headless sensor burst interval in seconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec);

/**
 * @brief Configure ULP slice parameters prior to entering deep sleep.
 *
 * @param[in] flow_a_sec    Flow A sample interval in seconds.
 * @param[in] flow_b_sec    Flow B display refresh interval in seconds.
 * @param[in] overflow      Total slice overflow threshold.
 * @param[in] remainder_sec Final remainder slice duration in seconds.
 */
void sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec);

/**
 * @brief Enter target deep sleep mode with wake pin configuration.
 *
 * @param[in] sleep_seconds  Sleep duration in seconds.
 * @param[in] ext1_pins_mask Bitmask of GPIOs to configure for EXT1 wake.
 * @param[in] mode           Sleep mode (SUB_POWER_SLEEP_FULL_CYCLE or SUB_POWER_SLEEP_FLOW_A_BURST).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);

/**
 * @brief Enter full cycle deep sleep with wake pin configuration.
 *
 * @param[in] sleep_seconds  Sleep duration in seconds.
 * @param[in] ext1_pins_mask Bitmask of GPIOs for EXT1 wake.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);

/**
 * @brief Cut master power latch (releases GPIO 17 BAT_CTRL).
 */
void sub_power_cut_power_latch(void);

/**
 * @brief Check if USB VBUS connection is actively present.
 *
 * @return True if connected to USB power.
 */
bool sub_power_connected_usb(void);

/**
 * @brief Initialize Dynamic Frequency Scaling (DFS) power management.
 *
 * @param[in] mode Clock scaling mode (SYS_CLK_MODE_DYNAMIC, FIXED_MAX, FIXED_MIN).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode);

/**
 * @brief Acquire CPU frequency lock at 240 MHz for compute/display intensive operations.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_acquire(void);

/**
 * @brief Release CPU frequency lock, allowing DFS to downclock to 80 MHz.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_release(void);

#ifdef __cplusplus
}
#endif
