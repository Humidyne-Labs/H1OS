/**
 * @file sub_power.h
 * @brief Layer 2: Battery ADC Monitoring & Deep Sleep Hardware Driver
 *
 * Dedicated battery voltage readout with 12 dB hardware attenuation, eFuse curve fitting,
 * multi-sample outlier rejection, and deep sleep entry with RTC pad holds.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse
 * cal).
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init(void);

/**
 * @brief Deinitialize ADC handles.
 * @return ESP_OK on success.
 */
esp_err_t sub_power_deinit(void);

/**
 * @brief Sample calibrated battery voltage with 16-sample trimmed outlier filtering.
 *
 * @param[out] out_mv Battery voltage in millivolts (e.g. 3850 mV).
 * @param[out] out_pct Estimated state of charge (0 to 100%).
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);

/**
 * @brief Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.
 *
 * @param[out] out_scale Multiplier scaled by 4096.
 * @param[out] out_offset_mv Voltage offset in millivolts.
 * @return ESP_OK on success.
 */
esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv);

/**
 * @brief Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.
 * Loads the binary into RTC Slow SRAM on cold boot, passes ADC eFuse calibration,
 * configures the periodic wake timer (Flow A period), and arms the coprocessor.
 *
 * @param[in] flow_a_period_sec Periodic wake interval for Flow A telemetry in seconds.
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec);

typedef enum {
    SUB_POWER_SLEEP_FULL_CYCLE = 0, /**< Normal Flow B sleep: arms PCF85063A countdown & resets slice_counter */
    SUB_POWER_SLEEP_FLOW_A_BURST /**< Flow A sample sleep: preserves running PCF85063A countdown &
                                    slice_counter */
} sub_power_sleep_mode_t;

/**
 * @brief Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.
 * Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.
 *
 * @param[in] sleep_seconds Timer duration in seconds (0 = timer disabled).
 * @param[in] ext1_pins_mask Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5).
 * @param[in] mode Full cycle or Flow A burst mode.
 * @return Does not return on success (enters deep sleep).
 */
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);

/**
 * @brief Configure EXT1 wake sources and enter deep sleep (defaults to SUB_POWER_SLEEP_FULL_CYCLE).
 * Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.
 *
 * @param[in] sleep_seconds Timer duration in seconds (0 = timer disabled).
 * @param[in] ext1_pins_mask Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5).
 * @return Does not return on success (enters deep sleep).
 */
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);

/**
 * @brief Power off system completely by releasing battery power latch (GPIO 17).
 * Used for critical low-battery shutdown or explicit user power-off.
 */
void sub_power_cut_power_latch(void);

/**
 * @brief Check to see if USB is connected.
 * Used for charger detection.
 *
 * @return true if usb is connected, or false if disconnected.
 */
bool sub_power_connected_usb(void);

/**
 * @brief Initialize Dynamic Frequency Scaling (DFS) power management.
 * Gates CPU cores to 80 MHz baseline during quiescent and interactive periods,
 * while allowing transient 240 MHz turbo scaling during heavy UI/compute bursts.
 *
 * @param[in] enable_dfs Enable DFS scaling (true = 80MHz base / 240MHz max; false = locked 80MHz).
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init_dfs(bool enable_dfs);

/**
 * @brief Acquire 240 MHz CPU performance lock (e.g. during LVGL rendering blitz).
 * Boosts CPU cores from 80 MHz baseline to 240 MHz turbo clock.
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_acquire(void);

/**
 * @brief Release 240 MHz CPU performance lock.
 * Allows CPU cores to gate back down to 80 MHz baseline.
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_release(void);

#ifdef __cplusplus
}
#endif
