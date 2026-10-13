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
 * @brief Early boot initialization of non-latched application pins.
 * 
 * Releases sleep pad holds on dynamic peripheral/wake pins, configures
 * amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5).
 * Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are
 * strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).
 * 
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_io_early_init(void);

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
 * Strictly for system shutdown; assertion of GPIO 17 is handled exclusively by the 2nd-stage bootloader.
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_io_release_power_latch(void);

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
 * @brief Configures and locks dynamic peripheral lines prior to deep sleep.
 * 
 * - Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
 * - Holds amplifier mute GPIO 46 (PA_CTRL) LOW.
 * - Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18).
 * - Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_io_isolate_sleep_pads(void);

/**
 * @brief Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_io_release_pad_holds(void);

/**
 * @brief Check if USB Serial/JTAG is connected to an active host via SOF packets.
 * 
 * @return true if USB host connection detected, false otherwise.
 */
bool hal_check_usb_ll(void);

#ifdef __cplusplus
}
#endif
