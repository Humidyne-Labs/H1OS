/**
 * @file h1os_boot_hook.c
 * @brief Early 2nd-Stage Bootloader Power Hold Hook for H1OS (Waveshare ESP32-S3 ePaper 1.54 V2)
 *
 * Runs in the 2nd stage bootloader before application decompression/loading to assert
 * BAT_CTRL (GPIO 17) HIGH in < 25ms of power-up.
 *
 * SPDX-License-Identifier: MIT
 */

#include "esp_rom_gpio.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/gpio_num.h"
#include "soc/gpio_sig_map.h"
#include "soc/rtc_cntl_reg.h"
#include "hal/gpio_ll.h"

#define H1OS_PIN_POWER_HOLD  17
#define H1OS_PIN_EPD_3V3_EN  6
#define H1OS_PIN_PA_EN       42

static const char *TAG __unused = "H1OS_BOOT_HOOK";

/* Mandatory symbol to force the GNU linker to pull this translation unit (-u bootloader_hooks_include) */
void bootloader_hooks_include(void)
{
    /* Keep empty */
}

/**
 * FIRST HOOK: Executes before any bootloader hardware initialization.
 * - Flash cache is DOWN, console is not configured (do NOT call ESP_LOG here).
 * - Immediately latches BAT_CTRL (GPIO 17) HIGH in < 25ms.
 * - Explicitly connects SIG_GPIO_OUT_IDX to prevent reliance on reset defaults.
 */
void bootloader_before_init(void)
{
    /* 1. Configure GPIO 17 (BAT_CTRL / RTC_GPIO17) as Output, drive HIGH, and lock RTC pad hold (< 25ms) */
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_POWER_HOLD);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_POWER_HOLD, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD, 1);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));

    /* 2. Configure GPIO 6 (EPD_3V3_EN / RTC_GPIO6) as Output, drive LOW (0 = ON), and lock RTC pad hold */
    REG_CLR_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_EPD_3V3_EN));
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_EPD_3V3_EN);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_EPD_3V3_EN, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_EPD_3V3_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_EPD_3V3_EN);
    REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_EPD_3V3_EN));

    /* 3. Configure GPIO 42 (PA_EN) as Output, drive LOW (0 = ON), and lock digital pad hold */
    gpio_ll_hold_dis(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
    esp_rom_gpio_pad_select_gpio(H1OS_PIN_PA_EN);
    esp_rom_gpio_connect_out_signal(H1OS_PIN_PA_EN, SIG_GPIO_OUT_IDX, false, false);
    gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN, 0);
    gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
    gpio_ll_hold_en(&GPIO, (gpio_num_t)H1OS_PIN_PA_EN);
}

/**
 * SECOND HOOK: Executes after standard bootloader initialization.
 * - Console, SPI Flash cache, and clocks are now valid; ESP_LOG is operational.
 */
void bootloader_after_init(void)
{
    /* Validate critical battery power latch (GPIO 17 / BAT_CTRL) */
    uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> H1OS_PIN_POWER_HOLD) & 1U;
    uint32_t g17_out  = (REG_READ(GPIO_OUT_REG)          >> H1OS_PIN_POWER_HOLD) & 1U;
    uint32_t g6_hold  = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> H1OS_PIN_EPD_3V3_EN) & 1U;

    if (g17_hold == 0 || g17_out == 0) {
        ESP_LOGE(TAG, "[FATAL] BAT_CTRL (GPIO 17) power latch failed! [out=%lu, hold=%lu]",
                 (unsigned long)g17_out, (unsigned long)g17_hold);
        /* Re-assert latch immediately to prevent impending brownout drop */
        gpio_ll_set_level(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD, 1);
        gpio_ll_output_enable(&GPIO, (gpio_num_t)H1OS_PIN_POWER_HOLD);
        REG_SET_BIT(RTC_CNTL_PAD_HOLD_REG, BIT(H1OS_PIN_POWER_HOLD));
    } else {
        ESP_LOGD(TAG, "Hardware master rails verified [BAT_CTRL=%lu (hold=%lu), EPD_EN_HOLD=%lu]",
                 (unsigned long)g17_out, (unsigned long)g17_hold, (unsigned long)g6_hold);
    }
}
