/**
 * @file power_hold_hook.c
 * @brief Early 2nd-stage bootloader power hold hook for test app
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "esp_rom_gpio.h"
#include "hal/gpio_ll.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_sig_map.h"
#include "soc/rtc_cntl_reg.h"

#define PIN_POWER_HOLD 17

/**
 * @brief Dummy symbol to enforce linker inclusion of 2nd-stage bootloader hooks.
 */
void bootloader_hooks_include(void)
{
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
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
    esp_rom_gpio_pad_select_gpio(PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(PIN_POWER_HOLD, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)PIN_POWER_HOLD);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
}
