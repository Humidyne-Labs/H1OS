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

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).
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
 * @brief Configure EXT1 wake sources and enter deep sleep.
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

#ifdef __cplusplus
}
#endif
