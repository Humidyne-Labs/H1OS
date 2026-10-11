/**
 * @file hal_io.h
 * @brief Layer 1 HAL Base Pin, Power Latch, and Sleep Isolation Controller
 * 
 * Invariant Rule: Implements the "Keep All Gates Open" strategy.
 * Latches BAT_CTRL (GPIO 17) and EPD_3V3_EN (GPIO 6) via RTC pad holds to eliminate
 * ES8311 I2C bus clamping, capacitor inrush brownouts, and PCF85063A POR resets.
 * 
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "h1os/hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Early boot initialization of essential system pins.
 * 
 * Releases RTC pad holds on buttons/interrupts, asserts BAT_CTRL HIGH immediately,
 * asserts EPD_3V3_EN LOW (rail on), and ensures audio amp is muted/cut.
 * 
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_io_early_init(void);

/**
 * @brief Asserts and locks the battery LDO enable latch (GPIO 17).
 * 
 * @param enable True to drive HIGH and lock; False to drive LOW (power cut).
 * @return ESP_OK on success.
 */
esp_err_t hal_io_lock_power_latch(bool enable);

/**
 * @brief Controls the 3.3V switched peripheral rail (GPIO 6, Active LOW).
 * 
 * @param enable True to turn rail ON (drive 0); False to turn OFF (drive 1).
 * @return ESP_OK on success.
 */
esp_err_t hal_io_set_sensor_rail(bool enable);

/**
 * @brief Controls user status LED (GPIO 3, Active LOW).
 * 
 * @param on True to turn LED ON (drive 0); False to turn OFF (drive 1).
 * @return ESP_OK on success.
 */
esp_err_t hal_io_set_led(bool on);

/**
 * @brief Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.
 * 
 * @return ESP_OK on success.
 */
static inline esp_err_t hal_io_release_power_latch(void)
{
    return hal_io_lock_power_latch(false);
}

/**
 * @brief Samples instantaneous state of hardware tactile buttons.
 * 
 * @return Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).
 */
hal_btn_mask_t hal_io_read_buttons(void);

/**
 * @brief Stateless check if a specific button pin is actively held down (Active LOW).
 * 
 * @param pin GPIO_NUM_0 (BOOT) or GPIO_NUM_18 (POWER)
 * @return true if depressed, false otherwise
 */
static inline bool hal_io_button_is_pressed(gpio_num_t pin)
{
    return gpio_get_level(pin) == 0;
}

/**
 * @brief Configures and locks all lines subject to parasitic leakage prior to deep sleep.
 * 
 * - Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
 * - Cuts audio power: GPIO 42 (PA_EN) = HIGH, GPIO 46 (PA_CTRL) = LOW.
 * - Protects SD bus: GPIO 39-41 set to High-Z with pull-ups.
 * - Freezes BAT_CTRL (GPIO 17) HIGH and EPD_3V3_EN (GPIO 6) LOW with RTC pad holds.
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_io_isolate_sleep_pads(void);

/**
 * @brief Releases RTC pad holds upon waking from deep sleep.
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_io_release_pad_holds(void);

#ifdef __cplusplus
}
#endif
