/**
 * @file power_hold_hook.c
 * @brief Early 2nd-stage bootloader hook to latch BAT_CTRL (GPIO 17) HIGH in < 25ms
 */

#include "esp_rom_gpio.h"
#include "soc/gpio_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/gpio_sig_map.h"
#include "hal/gpio_ll.h"

#define PIN_POWER_HOLD 17

void bootloader_hooks_include(void)
{
    //Empty
}

void bootloader_before_init(void)
{
    /* Latch BAT_CTRL (GPIO 17) HIGH and freeze with RTC pad hold in < 25ms */
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
    esp_rom_gpio_pad_select_gpio(PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(PIN_POWER_HOLD, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)PIN_POWER_HOLD);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(PIN_POWER_HOLD));
}
