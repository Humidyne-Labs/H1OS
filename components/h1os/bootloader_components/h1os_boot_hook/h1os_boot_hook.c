/**
 * @file h1os_boot_hook.c
 * @brief Early 2nd-stage bootloader power hold hook for ESP32-S3
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "esp_attr.h"
#include "esp_log.h"
#include "esp_rom_gpio.h"
#include "hal/gpio_ll.h"
#include "soc/gpio_num.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_sig_map.h"
#include "soc/io_mux_reg.h"
#include "soc/rtc_cntl_reg.h"

#define H1OS_PIN_POWER_HOLD 17
#define H1OS_PIN_EPD_3V3_EN 6
#define H1OS_PIN_PA_EN 42

static const char *TAG __unused = "H1OS_BOOT_HOOK";

/**
 * @brief Dummy symbol to enforce linker inclusion of 2nd-stage bootloader hooks.
 */
void bootloader_hooks_include(void)
{
	// Empty
}

/**
 * @brief FIRST HOOK: Executes before any bootloader hardware initialization.
 *
 * @details * Flash cache is DOWN, console is not configured (do NOT call ESP_LOG here).
 * Immediately latches BAT_CTRL (GPIO 17) HIGH in < 25ms.
 * Explicitly connects SIG_GPIO_OUT_IDX to prevent reliance on reset defaults.
 */
void bootloader_before_init(void)
{
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_POWER_HOLD, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));

    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_EPD_3V3_EN));
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_EPD_3V3_EN);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_EPD_3V3_EN, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_EPD_3V3_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_EPD_3V3_EN);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_EPD_3V3_EN));

    gpio_ll_hold_dis(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_PA_EN);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_PA_EN, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
    gpio_ll_hold_en(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
}

/**
 * @brief SECOND HOOK: Executes after standard bootloader initialization.
 *
 * @details * Console, SPI Flash cache, and clocks are now valid; ESP_LOG is operational.
 */
void bootloader_after_init(void)
{
    uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> H1OS_PIN_POWER_HOLD) & 1U;
    uint32_t g17_out = (REG_READ(GPIO_OUT_REG) >> H1OS_PIN_POWER_HOLD) & 1U;
    uint32_t g6_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> H1OS_PIN_EPD_3V3_EN) & 1U;

    if (g17_hold == 0 || g17_out == 0) {
        ESP_LOGE(TAG, "[FATAL] BAT_CTRL (GPIO 17) power latch failed! [out=%lu, hold=%lu]", (unsigned long)g17_out,
                 (unsigned long)g17_hold);

        gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD, 1);
        gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD);
        REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));
    } else {
        ESP_LOGD(TAG, "Hardware master rails verified [BAT_CTRL=%lu (hold=%lu), EPD_EN_HOLD=%lu]",
                 (unsigned long)g17_out, (unsigned long)g17_hold, (unsigned long)g6_hold);
    }
}
