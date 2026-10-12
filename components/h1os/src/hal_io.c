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
    esp_err_t ret = ESP_OK;

    // 1. Release pad holds on wake inputs
    hal_io_release_pad_holds();

    // 2. Lock BAT_CTRL (GPIO 17) HIGH immediately to hold battery regulator
    ret = hal_io_lock_power_latch(true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to lock power latch GPIO 17: %d", ret);
        return ret;
    }

    // 3. Keep 3.3V EPD & Peripheral rail energized (GPIO 6 = 0)
    ret = hal_io_set_sensor_rail(true);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to energize peripheral rail GPIO 6: %d", ret);
        return ret;
    }

    // 4. Ensure Audio Codec domain is energized (GPIO 42 = 0) to prevent I2C bus clamping, and muted (GPIO 46 = 0)
    gpio_config_t pa_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_PA_EN) | (1ULL << HAL_PIN_PA_CTRL),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_EN, 0);   // Keep Audio Domain ON (Active LOW: 0=ON)
    gpio_set_level(HAL_PIN_PA_CTRL, 0); // Standby Mute

    // 5. User Status LED (GPIO 3: Open-Drain, 1 = OFF)
    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1); // LED OFF

    // 6. Tactile Buttons (GPIO 0 & GPIO 18: Inputs with external 100k pull-ups and internal pull-ups in parallel)
    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&btn_cfg);

    // 7. RTC INT (GPIO 5: Input with internal pull-up)
    gpio_config_t rtc_int_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_RTC_INT),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&rtc_int_cfg);

    ESP_LOGD(TAG, "Early IO configuration and power latch locked.");
    return ESP_OK;
}

esp_err_t hal_io_lock_power_latch(bool enable)
{
    if (!enable) {
        /* Release holds FIRST: a held pad ignores gpio_set_level() */
        gpio_deep_sleep_hold_dis();
        gpio_hold_dis(HAL_PIN_POWER_HOLD);
        gpio_set_level(HAL_PIN_POWER_HOLD, 0);
        return ESP_OK;
    }

    gpio_config_t pwr_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_POWER_HOLD),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&pwr_cfg);
    gpio_set_level(HAL_PIN_POWER_HOLD, 1);
    gpio_hold_en(HAL_PIN_POWER_HOLD);

    return ESP_OK;
}


esp_err_t hal_io_set_sensor_rail(bool enable)
{
    gpio_config_t rail_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_3V3_EN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&rail_cfg);
    // Active LOW: 0 = ON, 1 = OFF
    gpio_set_level(HAL_PIN_EPD_3V3_EN, enable ? 0 : 1);
    gpio_hold_en(HAL_PIN_EPD_3V3_EN);

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
    // 1. Freeze power rails: BAT_CTRL = 1, EPD_3V3_EN = 0
    gpio_set_level(HAL_PIN_POWER_HOLD, 1);
    gpio_hold_en(HAL_PIN_POWER_HOLD);

    gpio_set_level(HAL_PIN_EPD_3V3_EN, 0);
    gpio_hold_en(HAL_PIN_EPD_3V3_EN);

    // 2. Display SPI line isolation: Hold CS and RST HIGH
    gpio_set_level(HAL_PIN_EPD_CS, 1);
    gpio_hold_en(HAL_PIN_EPD_CS);

    gpio_set_level(HAL_PIN_EPD_RST, 1);
    gpio_hold_en(HAL_PIN_EPD_RST);

    // 3. Audio power domain kept ON (0=ON) to prevent I2C clamping, PA muted (0=Mute)
    gpio_set_level(HAL_PIN_PA_EN, 0);
    gpio_hold_en(HAL_PIN_PA_EN);
    gpio_set_level(HAL_PIN_PA_CTRL, 0);
    gpio_hold_en(HAL_PIN_PA_CTRL);

    // 4. Enable deep sleep hold on all held pads
    gpio_deep_sleep_hold_en();

    // 5. Force RTC Peripherals domain to remain powered ON during deep sleep so RTC GPIO 17 keeps latch held
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGD(TAG, "Sleep pads isolated and latched.");
    return ESP_OK;
}

esp_err_t hal_io_release_pad_holds(void)
{
    gpio_hold_dis(HAL_PIN_BUTTON_BOOT);
    gpio_hold_dis(HAL_PIN_BUTTON_POWER);
    gpio_hold_dis(HAL_PIN_RTC_INT);
    gpio_hold_dis(HAL_PIN_EPD_CS);
    gpio_hold_dis(HAL_PIN_EPD_RST);
    gpio_hold_dis(HAL_PIN_PA_EN);
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