/**
 * @file hal_io.c
 * @brief Layer 1: Base pin, pad hold, and power rail driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_io.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/rtc_io.h"
#include "esp_log.h"
#include "esp_private/io_mux.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/rtc_io_reg.h"
#include "soc/usb_serial_jtag_reg.h"

static const char *TAG = "HAL_IO";

#define HAL_IO_TASK_STACK_BREATH        2048U /**< LED breath PWM animation task stack.  */
#define HAL_IO_TASK_PRIO_BREATH         1     /**< Idle-level priority for LED breath.   */
#define HAL_IO_DEFAULT_BREATH_PERIOD_MS 2000U /**< Default LED breath period in ms (2s). */

/**
 * @brief Early boot initialization of non-latched application pins.
 *
 * @details Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_io_early_init(void)
{
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("ledc", ESP_LOG_WARN);
    esp_log_level_set("h1os_lifecycle", ESP_LOG_DEBUG);
    esp_log_level_set("orch_flow", ESP_LOG_DEBUG);
    esp_log_level_set("orch_display_sync", ESP_LOG_DEBUG);
    esp_log_level_set("HAL_IO", ESP_LOG_DEBUG);
    esp_log_level_set("HAL_FLASH", ESP_LOG_DEBUG);
    esp_log_level_set("sub_power", ESP_LOG_DEBUG);
    esp_log_level_set("sub_sdcard", ESP_LOG_DEBUG);
    esp_log_level_set("sub_audio", ESP_LOG_DEBUG);
    esp_log_level_set("sub_display", ESP_LOG_DEBUG);
    esp_log_level_set("h1os_demo", ESP_LOG_DEBUG);

    gpio_set_level(HAL_PIN_PA_CTRL, 0);
    hal_io_release_pad_holds();

    gpio_config_t pa_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_PA_CTRL),
        .mode = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_CTRL, 0);

    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1);

    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&btn_cfg);

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

/**
 * @brief Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.
 *
 * @details Strictly for system shutdown; assertion of GPIO 17 is handled exclusively by the 2nd-stage bootloader.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_io_release_power_latch(void)
{
    gpio_deep_sleep_hold_dis();
    gpio_hold_dis(HAL_PIN_POWER_HOLD);
    gpio_set_direction(HAL_PIN_POWER_HOLD, GPIO_MODE_OUTPUT);
    gpio_set_level(HAL_PIN_POWER_HOLD, 0);
    return ESP_OK;
}

#define HAL_LEDC_TIMER     LEDC_TIMER_0
#define HAL_LEDC_MODE      LEDC_LOW_SPEED_MODE
#define HAL_LEDC_CHANNEL   LEDC_CHANNEL_0
#define HAL_LEDC_DUTY_RES  LEDC_TIMER_10_BIT
#define HAL_LEDC_FREQUENCY 5000

static bool s_led_pwm_active = false;

/**
 * @brief Initializes LEDC hardware PWM controller for user LED on GPIO 3.
 *
 * @details Enables 10-bit hardware brightness resolution (0..100%) and hardware smooth fading.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_pwm_init(void)
{
    if (s_led_pwm_active) {
        return ESP_OK;
    }

    esp_log_level_set("ledc", ESP_LOG_WARN);

    gpio_reset_pin(HAL_PIN_STATUS_LED);

    ledc_timer_config_t timer_cfg = {
        .speed_mode = HAL_LEDC_MODE,
        .duty_resolution = HAL_LEDC_DUTY_RES,
        .timer_num = HAL_LEDC_TIMER,
        .freq_hz = HAL_LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK,
        .deconfigure = false,
    };
    esp_err_t err = ledc_timer_config(&timer_cfg);
    if (err != ESP_OK) {
        return err;
    }

    ledc_channel_config_t ch_cfg = {
        .gpio_num = HAL_PIN_STATUS_LED,
        .speed_mode = HAL_LEDC_MODE,
        .channel = HAL_LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = HAL_LEDC_TIMER,
        .duty = 0,
        .hpoint = 0,
        .flags =
            {
                .output_invert = 1,
            },
    };
    err = ledc_channel_config(&ch_cfg);
    if (err != ESP_OK) {
        return err;
    }

    ledc_fade_func_install(0);
    s_led_pwm_active = true;
    ESP_LOGD(TAG, "LEDC PWM initialized on GPIO 3 (Active LOW).");
    return ESP_OK;
}

/**
 * @brief Sets user LED brightness percentage using hardware PWM (0..100%).
 *
 * @param[in]    brightness_pct  Brightness percentage: 0 = OFF, 100 = Maximum.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_set_brightness(uint8_t brightness_pct)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) {
            return err;
        }
    }

    if (brightness_pct > 100) {
        brightness_pct = 100;
    }
    uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;
    ledc_set_duty(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, duty);
    return ledc_update_duty(HAL_LEDC_MODE, HAL_LEDC_CHANNEL);
}

/**
 * @brief Smoothly fades user LED to target brightness using hardware fade engine.
 *
 * @details Non-blocking: hardware timer interpolates duty cycle with zero CPU overhead.
 *
 * @param[in]    target_pct      Target brightness percentage (0..100%).
 * @param[in]    duration_ms     Duration of fade transition in milliseconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) {
            return err;
        }
    }

    if (target_pct > 100) {
        target_pct = 100;
    }
    uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;
    ledc_set_fade_with_time(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, target_duty, duration_ms);
    return ledc_fade_start(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, LEDC_FADE_NO_WAIT);
}

static volatile TaskHandle_t s_breath_task = NULL;
static volatile bool s_breathing_running = false;
static volatile uint32_t s_breath_period_ms = HAL_IO_DEFAULT_BREATH_PERIOD_MS;

/**
 * @brief Led breath task.
 *
 * @param[in]    arg             Parameter arg.
 *
 * @return Return value of type static void.
 */
static void led_breath_task(void *arg)
{
    (void)arg;
    while (s_breathing_running) {
        uint32_t half = s_breath_period_ms / 2U;
        if (half < 100U) {
            half = 100U;
        }

        hal_led_fade_to(100, half);
        TickType_t start = xTaskGetTickCount();
        TickType_t duration = pdMS_TO_TICKS(half);
        while (s_breathing_running && (xTaskGetTickCount() - start < duration)) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        if (!s_breathing_running) {
            break;
        }

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

/**
 * @brief Starts an asynchronous background task to "breathe" (fade in and fade out) the status LED.
 *
 * @details Uses hardware LEDC PWM fading with FreeRTOS background pacing. Automatically yields CPU.
 *
 * @param[in]    cycle_period_ms Total duration of one breathe cycle in ms (fade-in + fade-out). Default: 2000 ms if 0.
 *
 * @return ESP_OK on success, or ESP_FAIL if task creation fails.
 */
esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms)
{
    if (!s_led_pwm_active) {
        esp_err_t err = hal_led_pwm_init();
        if (err != ESP_OK) {
            return err;
        }
    }

    if (cycle_period_ms == 0) {
        cycle_period_ms = HAL_IO_DEFAULT_BREATH_PERIOD_MS;
    }
    s_breath_period_ms = cycle_period_ms;

    if (s_breathing_running && s_breath_task != NULL) {
        return ESP_OK;
    }

    s_breathing_running = true;
    BaseType_t res = xTaskCreate(led_breath_task, "led_breath", HAL_IO_TASK_STACK_BREATH, NULL, HAL_IO_TASK_PRIO_BREATH, (TaskHandle_t *)&s_breath_task);
    if (res != pdPASS) {
        s_breathing_running = false;
        s_breath_task = NULL;
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief Stops the asynchronous breathing task and turns the LED off.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_stop_breathing(void)
{
    if (!s_breathing_running && s_breath_task == NULL) {
        return ESP_OK;
    }
    s_breathing_running = false;
    int32_t wait_cycles = 15;
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

/**
 * @brief Queries whether the asynchronous breathing task is actively running.
 *
 * @return True if breathing task is active, false otherwise.
 */
bool hal_led_is_breathing(void)
{
    return s_breathing_running;
}

/**
 * @brief Deinitializes LEDC hardware PWM and restores GPIO 3 to static GPIO mode.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_pwm_deinit(void)
{
    hal_led_stop_breathing();

    if (!s_led_pwm_active) {
        return ESP_OK;
    }

    ledc_stop(HAL_LEDC_MODE, HAL_LEDC_CHANNEL, 0);
    ledc_fade_func_uninstall();
    s_led_pwm_active = false;

    gpio_reset_pin(HAL_PIN_STATUS_LED);

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

/**
 * @brief Controls user status LED (GPIO 3, Active LOW).
 *
 * @param[in]    on              True to turn LED ON (drive 0); False to turn OFF (drive 1).
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_io_set_led(bool on)
{
    if (s_breathing_running) {
        hal_led_stop_breathing();
    }
    if (s_led_pwm_active) {
        return hal_led_set_brightness(on ? 100 : 0);
    }

    return gpio_set_level(HAL_PIN_STATUS_LED, on ? 0 : 1);
}

/**
 * @brief Samples instantaneous state of hardware tactile buttons.
 *
 * @return Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).
 */
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

/**
 * @brief Configures and locks dynamic peripheral lines prior to deep sleep.
 *
 * @details * Latches GPIO 11 (EPD_CS), GPIO 9 (EPD_RST), and GPIO 10 (EPD_DC) HIGH via gpio_hold_en().
 * Holds amplifier mute GPIO 46 (PA_CTRL) LOW.
 * Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18).
 * Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_io_isolate_sleep_pads(void)
{
    gpio_set_level(HAL_PIN_EPD_CS, 1);
    gpio_hold_en(HAL_PIN_EPD_CS);

    gpio_set_level(HAL_PIN_EPD_RST, 1);
    gpio_hold_en(HAL_PIN_EPD_RST);

    gpio_set_level(HAL_PIN_EPD_DC, 1);
    gpio_hold_en(HAL_PIN_EPD_DC);

    gpio_set_level(HAL_PIN_PA_CTRL, 0);
    gpio_hold_en(HAL_PIN_PA_CTRL);

    /* Deinit i2s pins and latch to known state */
    const gpio_num_t i2s_pins[] = {
        HAL_PIN_I2S_MCLK, HAL_PIN_I2S_SCLK,
        HAL_PIN_I2S_LRCK, HAL_PIN_I2S_DSDIN,
        HAL_PIN_I2S_ASDOUT
    };

    for (size_t i = 0; i < sizeof(i2s_pins) / sizeof(i2s_pins[0]); i++) {
        gpio_reset_pin(i2s_pins[i]); /**< Reset State Before Sleep */
        gpio_set_direction(i2s_pins[i], GPIO_MODE_OUTPUT);
        gpio_set_level(i2s_pins[i], 0);
        gpio_hold_en(i2s_pins[i]);
    }

    if (s_led_pwm_active) {
        hal_led_pwm_deinit();
    }
    gpio_set_level(HAL_PIN_STATUS_LED, 1);
    gpio_hold_en(HAL_PIN_STATUS_LED);

    gpio_deep_sleep_hold_en();

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGD(TAG, "Static sleep pads isolated and latched.");
    return ESP_OK;
}

/**
 * @brief Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_io_release_pad_holds(void)
{
    gpio_deep_sleep_hold_dis();

    rtc_gpio_deinit(HAL_PIN_RTC_INT);
    rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT);
    rtc_gpio_deinit(HAL_PIN_BUTTON_POWER);
    rtc_gpio_deinit(HAL_PIN_BATTERY_ADC);

    gpio_hold_dis(HAL_PIN_EPD_CS);
    gpio_hold_dis(HAL_PIN_EPD_RST);
    gpio_hold_dis(HAL_PIN_EPD_DC);
    gpio_hold_dis(HAL_PIN_PA_CTRL);
    gpio_hold_dis(HAL_PIN_STATUS_LED);

    /* Remove IO Latch on Wake */
    gpio_hold_dis(HAL_PIN_I2S_MCLK);
    gpio_hold_dis(HAL_PIN_I2S_SCLK);
    gpio_hold_dis(HAL_PIN_I2S_LRCK);
    gpio_hold_dis(HAL_PIN_I2S_DSDIN);
    gpio_hold_dis(HAL_PIN_I2S_ASDOUT);

    return ESP_OK;
}

/**
 * @brief Check if USB Serial/JTAG is connected to an active host via SOF packets.
 *
 * @details USB Full-Speed hosts transmit a Start-Of-Frame (SOF) packet every 1.000 ms.
 *          Sampling both the SOF interrupt flag and frame counter delta across a single
 *          1100 us window cuts active spin time from 3000 us to 1100 us per check.
 *
 * @return true if USB host connection detected, false otherwise.
 */
bool hal_check_usb_ll(void)
{
    uint32_t f1 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
    REG_WRITE(USB_SERIAL_JTAG_INT_CLR_REG, USB_SERIAL_JTAG_SOF_INT_CLR);
    esp_rom_delay_us(1100);
    if ((REG_READ(USB_SERIAL_JTAG_INT_RAW_REG) & USB_SERIAL_JTAG_SOF_INT_RAW) != 0) {
        return true;
    }
    uint32_t f2 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;
    return (f1 != f2);
}