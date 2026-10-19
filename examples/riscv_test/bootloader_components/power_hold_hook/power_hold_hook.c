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

void bootloader_hooks_include(void)
{
}

void bootloader_before_init(void)
{
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
    esp_rom_gpio_pad_select_gpio(PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(PIN_POWER_HOLD, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)PIN_POWER_HOLD);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
}
