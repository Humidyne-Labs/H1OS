/**
 * @file hal_io.c
 * @brief Layer 1 HAL Base Pin & Power Rail Driver Implementation
 * 
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_io.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "soc/usb_serial_jtag_reg.h"
#include "esp_sleep.h"
#include "esp_rom_sys.h"

static const char *TAG = "HAL_IO";

esp_err_t hal_io_early_init(void)
{
    // 1. Release sleep pad holds on dynamic peripheral & wake inputs
    // Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN)
    // are latched exclusively in the 2nd-stage bootloader (h1os_boot_hook.c).
    hal_io_release_pad_holds();

    // 2. Ensure Audio Amplifier is muted (GPIO 46 = 0)
    gpio_config_t pa_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_PA_CTRL),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_CTRL, 0); // Standby Mute

    // 3. User Status LED (GPIO 3: Open-Drain, 1 = OFF)
    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1); // LED OFF

    // 4. Tactile Buttons (GPIO 0 & GPIO 18: Inputs with external 100k pull-ups and internal pull-ups in parallel)
    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&btn_cfg);

    // 5. RTC INT (GPIO 5: Input with internal pull-up)
    gpio_config_t rtc_int_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_RTC_INT),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&rtc_int_cfg);

    ESP_LOGD(TAG, "Early IO configuration complete (power rails held by 2nd-stage bootloader).");
    return ESP_OK;
}

esp_err_t hal_io_release_power_latch(void)
{
    /* Strictly for system shutdown: release holds FIRST so GPIO 17 can be driven LOW */
    gpio_deep_sleep_hold_dis();
    gpio_hold_dis(HAL_PIN_POWER_HOLD);
    gpio_set_direction(HAL_PIN_POWER_HOLD, GPIO_MODE_OUTPUT);
    gpio_set_level(HAL_PIN_POWER_HOLD, 0);
    return ESP_OK;
}

esp_err_t hal_io_set_led(bool on)
{
    // Open-Drain: 0 = ON, 1 = OFF
    return gpio_set_level(HAL_PIN_STATUS_LED, on ? 0 : 1);
}

hal_btn_mask_t hal_io_read_buttons(void)
{
    hal_btn_mask_t mask = HAL_BTN_NONE;
    if (gpio_get_level(HAL_PIN_BUTTON_BOOT) == 0) {
        mask |= HAL_BTN_BOOT;
    }
    if (gpio_get_level(HAL_PIN_BUTTON_POWER) == 0) {
        mask |= HAL_BTN_POWER;
    }
    return mask;
}

esp_err_t hal_io_isolate_sleep_pads(void)
{
    // Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN)
    // remain untouched and held by the 2nd-stage bootloader.

    // 1. Display SPI line isolation: Hold CS and RST HIGH
    gpio_set_level(HAL_PIN_EPD_CS, 1);
    gpio_hold_en(HAL_PIN_EPD_CS);

    gpio_set_level(HAL_PIN_EPD_RST, 1);
    gpio_hold_en(HAL_PIN_EPD_RST);

    // 2. Keep PA muted (0 = Mute) during sleep
    gpio_set_level(HAL_PIN_PA_CTRL, 0);
    gpio_hold_en(HAL_PIN_PA_CTRL);

    // 3. Configure RTC IO domain pull-ups for EXT1 wake sources.
    // Digital domain pull-ups vanish when VDD3P3_CPU powers down in deep sleep.
    // RTC IO pull-ups maintain HIGH level so floating pads do not trigger false EXT1 wakes.
    rtc_gpio_init(HAL_PIN_RTC_INT);
    rtc_gpio_set_direction(HAL_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_RTC_INT);
    rtc_gpio_pulldown_dis(HAL_PIN_RTC_INT);

    rtc_gpio_init(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(HAL_PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_BOOT);

    rtc_gpio_init(HAL_PIN_BUTTON_POWER);
    rtc_gpio_set_direction(HAL_PIN_BUTTON_POWER, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);

    // 4. Enable deep sleep hold on all held pads
    gpio_deep_sleep_hold_en();

    // 5. Force RTC Peripherals domain to remain powered ON during deep sleep so RTC pad holds stay active
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGD(TAG, "Sleep pads isolated and latched.");
    return ESP_OK;
}

esp_err_t hal_io_release_pad_holds(void)
{
    // De-init RTC GPIO function to return wake pins to standard digital GPIO domain
    rtc_gpio_deinit(HAL_PIN_RTC_INT);
    rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_deinit(HAL_PIN_BUTTON_POWER);

    // Release holds only on dynamic peripheral/wake pins (never touch GPIO 17, GPIO 6, or GPIO 42)
    gpio_hold_dis(HAL_PIN_BUTTON_BOOT);
    gpio_hold_dis(HAL_PIN_BUTTON_POWER);
    gpio_hold_dis(HAL_PIN_RTC_INT);
    gpio_hold_dis(HAL_PIN_EPD_CS);
    gpio_hold_dis(HAL_PIN_EPD_RST);
    gpio_hold_dis(HAL_PIN_PA_CTRL);
    return ESP_OK;
}

bool hal_check_usb_ll(void)
{
    /* Check whether USB Serial/JTAG is receiving active Start-Of-Frame (SOF) packets.
     * On USB Full-Speed (12 Mbps), an active host transmits an SOF packet every 1.0 ms.
     * 1. Clear the raw SOF interrupt latch bit.
     * 2. Delay 1500 µs (1.5 ms) to span at least one SOF period.
     * 3. Check if the hardware raised the SOF raw interrupt bit. */
    REG_WRITE(USB_SERIAL_JTAG_INT_CLR_REG, USB_SERIAL_JTAG_SOF_INT_CLR);
    esp_rom_delay_us(1500);
    if ((REG_READ(USB_SERIAL_JTAG_INT_RAW_REG) & USB_SERIAL_JTAG_SOF_INT_RAW) != 0) {
        return true;
    }

    /* Fallback: Check if the 11-bit SOF frame counter ticks over 1.5 ms */
    uint32_t f1 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
    esp_rom_delay_us(1500);
    uint32_t f2 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
    return (f1 != f2);
}