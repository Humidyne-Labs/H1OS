/**
 * @file hal_io.c
 * @brief Layer 1 HAL Base Pin & Power Rail Driver Implementation
 * 
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_io.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "driver/ledc.h"
#include "soc/usb_serial_jtag_reg.h"
#include "esp_sleep.h"
#include "esp_rom_sys.h"
#include "esp_private/io_mux.h"
#include "soc/rtc_io_reg.h"

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
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_CTRL, 0); // Standby Mute

    // 3. User Status LED (GPIO 3: Open-Drain, 1 = OFF)
    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode         = GPIO_MODE_OUTPUT_OD,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1); // LED OFF

    // 4. Tactile Buttons (GPIO 0 & GPIO 18: Inputs with external 10k pull-ups)
    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&btn_cfg);

    // 5. RTC INT (GPIO 5: Input with internal pull-up)
    gpio_config_t rtc_int_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_RTC_INT),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
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

#define HAL_LEDC_TIMER       LEDC_TIMER_0
#define HAL_LEDC_MODE        LEDC_LOW_SPEED_MODE
#define HAL_LEDC_CHANNEL     LEDC_CHANNEL_0
#define HAL_LEDC_DUTY_RES    LEDC_TIMER_10_BIT /* 0..1023 */
#define HAL_LEDC_FREQUENCY   5000              /* 5 kHz */

static bool s_led_pwm_active = false;

esp_err_t hal_led_pwm_init(void)
{
    if (s_led_pwm_active) {
        return ESP_OK;
    }

    ledc_timer_config_t timer_cfg = {
        .speed_mode      = HAL_LEDC_MODE,
        .duty_resolution = HAL_LEDC_DUTY_RES,
        .timer_num       = HAL_LEDC_TIMER,
        .freq_hz         = HAL_LEDC_FREQUENCY,
        .clk_cfg         = LEDC_AUTO_CLK,
        .deconfigure     = false,
    };
    esp_err_t err = ledc_timer_config(&timer_cfg);
    if (err != ESP_OK) return err;

    ledc_channel_config_t ch_cfg = {
        .gpio_num   = HAL_PIN_STATUS_LED,
        .speed_mode = HAL_LEDC_MODE,
        .channel    = HAL_LEDC_CHANNEL,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = HAL_LEDC_TIMER,
        .duty       = 0,
        .hpoint     = 0,
        .flags      = {
            .output_invert = 1, /* Invert for Active LOW / Open-Drain: Duty 0 = Output 1 (OFF), Duty 1023 = Output 0 (ON) */
        },
    };
    err = ledc_channel_config(&ch_cfg);
    if (err != ESP_OK) return err;

    ledc_fade_func_install(0);
    s_led_pwm_active = true;
    ESP_LOGD(TAG, "LEDC PWM initialized on GPIO 3 (Active LOW).");
    return ESP_OK;
}

esp_err_t hal_led_set_brightness(uint8_t brightness_pct)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) return err;
    }

    if (brightness_pct > 100) brightness_pct = 100;
    uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;
    ledc_set_duty(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, duty);
    return ledc_update_duty(HAL_LEDC_MODE, HAL_LEDC_CHANNEL);
}

esp_err_t hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) return err;
    }

    if (target_pct > 100) target_pct = 100;
    uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;
    ledc_set_fade_with_time(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, target_duty, duration_ms);
    return ledc_fade_start(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, LEDC_FADE_NO_WAIT);
}

static TaskHandle_t s_breath_task = NULL;
static volatile bool s_breathing_running = false;
static uint32_t s_breath_period_ms = 2000;

static void led_breath_task(void *arg)
{
    while (s_breathing_running) {
        uint32_t half = s_breath_period_ms / 2;
        if (half < 100) half = 100;

        /* Fade in: 0% -> 100% */
        hal_led_fade_to(100, half);
        TickType_t start = xTaskGetTickCount();
        TickType_t duration = pdMS_TO_TICKS(half);
        while (s_breathing_running && (xTaskGetTickCount() - start < duration)) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        if (!s_breathing_running) break;

        /* Fade out: 100% -> 0% */
        hal_led_fade_to(0, half);
        start = xTaskGetTickCount();
        while (s_breathing_running && (xTaskGetTickCount() - start < duration)) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }

    if (s_led_pwm_active) {
        hal_led_set_brightness(0);
    }
    s_breath_task = NULL;
    vTaskDelete(NULL);
}

esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) return err;
    }

    if (cycle_period_ms == 0) {
        cycle_period_ms = 2000;
    }
    s_breath_period_ms = cycle_period_ms;

    if (s_breathing_running && s_breath_task != NULL) {
        return ESP_OK;
    }

    s_breathing_running = true;
    BaseType_t res = xTaskCreate(led_breath_task, "led_breath", 2048, NULL, 1, &s_breath_task);
    if (res != pdPASS) {
        s_breathing_running = false;
        s_breath_task = NULL;
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t hal_led_stop_breathing(void)
{
    if (!s_breathing_running && s_breath_task == NULL) {
        return ESP_OK;
    }
    s_breathing_running = false;
    int wait_cycles = 15;
    while (s_breath_task != NULL && wait_cycles-- > 0) {
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    if (s_breath_task != NULL) {
        vTaskDelete(s_breath_task);
        s_breath_task = NULL;
    }
    if (s_led_pwm_active) {
        hal_led_set_brightness(0);
    }
    return ESP_OK;
}

bool hal_led_is_breathing(void)
{
    return s_breathing_running;
}

esp_err_t hal_led_pwm_deinit(void)
{
    hal_led_stop_breathing();

    if (!s_led_pwm_active) {
        return ESP_OK;
    }

    ledc_stop(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, 0);
    ledc_fade_func_uninstall();
    s_led_pwm_active = false;

    // Restore to static open-drain GPIO
    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode         = GPIO_MODE_OUTPUT_OD,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1);
    return ESP_OK;
}

esp_err_t hal_io_set_led(bool on)
{
    if (s_breathing_running) {
        hal_led_stop_breathing();
    }
    if (s_led_pwm_active) {
        return hal_led_set_brightness(on ? 100 : 0);
    }
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

    // 3. Configure RTC IO domain pull-ups, LP IO sampling clock, and ULP wakeup triggers.
    // Digital domain pull-ups vanish when VDD3P3_CPU powers down in deep sleep.
    // RTC IO pull-ups maintain HIGH level so floating pads do not trigger false wakes.
    // On ESP32-S3, LP IO clock must be explicitly enabled to sample RTC IO wake signals.
    rtc_gpio_init(HAL_PIN_RTC_INT);
    rtc_gpio_set_direction(HAL_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_RTC_INT);
    rtc_gpio_pulldown_dis(HAL_PIN_RTC_INT);
    io_mux_enable_lp_io_clock(HAL_PIN_RTC_INT, true);
    rtc_gpio_wakeup_enable(HAL_PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);

    rtc_gpio_init(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(HAL_PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_BOOT);
    io_mux_enable_lp_io_clock(HAL_PIN_BUTTON_BOOT, true);
    rtc_gpio_wakeup_enable(HAL_PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);

    rtc_gpio_init(HAL_PIN_BUTTON_POWER);
    rtc_gpio_set_direction(HAL_PIN_BUTTON_POWER, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
    io_mux_enable_lp_io_clock(HAL_PIN_BUTTON_POWER, true);
    rtc_gpio_wakeup_enable(HAL_PIN_BUTTON_POWER, GPIO_INTR_LOW_LEVEL);

    // Clear any pending/stale RTC GPIO interrupt status flags before sleeping
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

    // 4. Ensure User Status LED is turned OFF and latched in deep sleep
    if (s_led_pwm_active) {
        hal_led_pwm_deinit();
    }
    gpio_set_level(HAL_PIN_STATUS_LED, 1);
    gpio_hold_en(HAL_PIN_STATUS_LED);

    // 5. Enable deep sleep hold on all held pads
    gpio_deep_sleep_hold_en();

    // 5. Force RTC Peripherals domain to remain powered ON during deep sleep so RTC pad holds stay active
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGD(TAG, "Sleep pads isolated and latched.");
    return ESP_OK;
}

esp_err_t hal_io_release_pad_holds(void)
{
    // Disable RTC wakeup triggers, release LP IO clock, and de-init RTC GPIO function to return wake pins to standard digital GPIO domain
    rtc_gpio_wakeup_disable(HAL_PIN_RTC_INT);
    rtc_gpio_wakeup_disable(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_wakeup_disable(HAL_PIN_BUTTON_POWER);
    io_mux_enable_lp_io_clock(HAL_PIN_RTC_INT, false);
    io_mux_enable_lp_io_clock(HAL_PIN_BUTTON_BOOT, false);
    io_mux_enable_lp_io_clock(HAL_PIN_BUTTON_POWER, false);
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
    gpio_hold_dis(HAL_PIN_STATUS_LED);
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