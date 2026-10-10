/**
 * @file bsp_boot_hook.c
 * @brief Early 2nd-Stage Bootloader Power Hold Hook for Waveshare ESP32-S3 ePaper 1.54 V2
 *
 * Runs in the 2nd stage bootloader before application decompression/loading to assert
 * BAT_CTRL (GPIO 17) HIGH in < 25ms of power-up.
 *
 * SPDX-License-Identifier: MIT
 */

#include "esp_rom_gpio.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_num.h"
#include "hal/gpio_ll.h"

#define BSP_PIN_POWER_HOLD 17
#define BSP_PIN_EPD_3V3_EN 6
#define BSP_PIN_PA_EN      42

void bootloader_before_init(void)
{
    // 1. Configure GPIO 17 as Output, drive HIGH, and lock with RTC pad hold latch (< 25ms from power-up)
    esp_rom_gpio_pad_select_gpio(BSP_PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(BSP_PIN_POWER_HOLD, BASE_OUTPUT_CTRL_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)BSP_PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)BSP_PIN_POWER_HOLD);
    gpio_ll_hold_en(&GPIO, (gpio_num_t)BSP_PIN_POWER_HOLD);

    // 2. Configure GPIO 6 (EPD_3V3_EN) as Output, drive LOW (0 = ON), and lock with pad hold latch
    esp_rom_gpio_pad_select_gpio(BSP_PIN_EPD_3V3_EN);
    esp_rom_gpio_connect_out_signal(BSP_PIN_EPD_3V3_EN, BASE_OUTPUT_CTRL_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)BSP_PIN_EPD_3V3_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)BSP_PIN_EPD_3V3_EN);
    gpio_ll_hold_en(&GPIO, (gpio_num_t)BSP_PIN_EPD_3V3_EN);

    // 3. Configure GPIO 42 (PA_EN) as Output, drive LOW (0 = ON), and lock with pad hold latch
    esp_rom_gpio_pad_select_gpio(BSP_PIN_PA_EN);
    esp_rom_gpio_connect_out_signal(BSP_PIN_PA_EN, BASE_OUTPUT_CTRL_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)BSP_PIN_PA_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)BSP_PIN_PA_EN);
    gpio_ll_hold_en(&GPIO, (gpio_num_t)BSP_PIN_PA_EN);
}

