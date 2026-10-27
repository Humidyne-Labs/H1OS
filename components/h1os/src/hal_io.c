/**
 * @file hal_io.c
 * @brief Layer 1: Base pin, pad hold, GPIO ISR dispatcher, and power rail driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_io.h"

#include "driver/gpio.h"
#include "driver/gpio_filter.h"
#include "driver/ledc.h"
#include "driver/rtc_io.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_private/io_mux.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/rtc_io_reg.h"
#include "soc/usb_serial_jtag_reg.h"

static const char *TAG = "HAL_IO";

#define HAL_IO_DEFAULT_BREATH_PERIOD_MS 2000U  /**< Default LED breath period in ms (2s).        */
#define HAL_IO_BTN_DEBOUNCE_US          15000U /**< Tactile button debounce window (15 ms).      */

static esp_timer_handle_t        s_btn_debounce_timer = NULL;
static gpio_glitch_filter_handle_t s_boot_glitch_flt  = NULL;
static gpio_glitch_filter_handle_t s_pwr_glitch_flt   = NULL;
static volatile hal_btn_mask_t   s_debounced_btn_mask = HAL_BTN_NONE;
static volatile bool             s_btn_isr_installed  = false;
static hal_io_button_cb_t        s_btn_user_cb        = NULL;
static void                     *s_btn_user_arg       = NULL;

/**
 * @brief Sample instantaneous raw GPIO levels of BOOT and POWER tactile buttons.
 */
static inline hal_btn_mask_t hal_io_sample_raw_buttons(void)
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
 * @brief One-shot esp_timer debounce callback for tactile button state transitions.
 */
static void hal_io_btn_debounce_timer_cb(void *arg)
{
    (void)arg;
    hal_btn_mask_t prev = s_debounced_btn_mask;
    hal_btn_mask_t curr = hal_io_sample_raw_buttons();
    s_debounced_btn_mask = curr;

    if (curr != prev && s_btn_user_cb != NULL) {
        s_btn_user_cb(curr, s_btn_user_arg);
    }
}

/**
 * @brief IRAM GPIO edge interrupt handler for BOOT (GPIO 0) and POWER (GPIO 18) buttons.
 */
static void IRAM_ATTR hal_io_btn_gpio_isr_handler(void *arg)
{
    (void)arg;
    if (s_btn_debounce_timer != NULL) {
        (void)esp_timer_stop(s_btn_debounce_timer);
        (void)esp_timer_start_once(s_btn_debounce_timer, HAL_IO_BTN_DEBOUNCE_US);
    }
}

/**
 * @brief Register an asynchronous callback invoked when tactile buttons change state after 15 ms esp_timer debounce.
 */
esp_err_t hal_io_register_button_cb(hal_io_button_cb_t cb, void *arg)
{
    s_btn_user_arg = arg;
    s_btn_user_cb  = cb;
    return ESP_OK;
}

/**
 * @brief Early boot initialization of non-latched application pins and GPIO ISR service.
 *
 * @details Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46),
 *          status LED (GPIO 3), buttons (GPIO 0/18 with edge interrupts and hardware glitch filters),
 *          and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN)
 *          are strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).
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

    /* Install global per-pin GPIO ISR dispatcher (safe if already installed) */
    esp_err_t isr_err = gpio_install_isr_service(0);
    if (isr_err != ESP_OK && isr_err != ESP_ERR_INVALID_STATE) {
        ESP_LOGW(TAG, "gpio_install_isr_service returned: %s", esp_err_to_name(isr_err));
    }

    gpio_config_t pa_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_PA_CTRL),
        .mode         = GPIO_MODE_INPUT_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_CTRL, 0);

    gpio_config_t led_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_STATUS_LED),
        .mode         = GPIO_MODE_OUTPUT_OD,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&led_cfg);
    gpio_set_level(HAL_PIN_STATUS_LED, 1);

    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_ANYEDGE,
    };
    gpio_config(&btn_cfg);

    /* Enable ESP32-S3 hardware pin glitch filters on tactile button inputs */
    if (s_boot_glitch_flt == NULL) {
        gpio_pin_glitch_filter_config_t flt_boot = {
            .clk_src  = GLITCH_FILTER_CLK_SRC_DEFAULT,
            .gpio_num = HAL_PIN_BUTTON_BOOT,
        };
        if (gpio_new_pin_glitch_filter(&flt_boot, &s_boot_glitch_flt) == ESP_OK) {
            (void)gpio_glitch_filter_enable(s_boot_glitch_flt);
        }
    }
    if (s_pwr_glitch_flt == NULL) {
        gpio_pin_glitch_filter_config_t flt_pwr = {
            .clk_src  = GLITCH_FILTER_CLK_SRC_DEFAULT,
            .gpio_num = HAL_PIN_BUTTON_POWER,
        };
        if (gpio_new_pin_glitch_filter(&flt_pwr, &s_pwr_glitch_flt) == ESP_OK) {
            (void)gpio_glitch_filter_enable(s_pwr_glitch_flt);
        }
    }

    s_debounced_btn_mask = hal_io_sample_raw_buttons();

    if (s_btn_debounce_timer == NULL) {
        const esp_timer_create_args_t timer_args = {
            .callback        = &hal_io_btn_debounce_timer_cb,
            .arg             = NULL,
            .dispatch_method = ESP_TIMER_TASK,
            .name            = "hal_btn_dbnc",
            .skip_unhandled_events = true,
        };
        (void)esp_timer_create(&timer_args, &s_btn_debounce_timer);
    }

    if (!s_btn_isr_installed) {
        (void)gpio_isr_handler_add(HAL_PIN_BUTTON_BOOT, hal_io_btn_gpio_isr_handler, NULL);
        (void)gpio_isr_handler_add(HAL_PIN_BUTTON_POWER, hal_io_btn_gpio_isr_handler, NULL);
        s_btn_isr_installed = true;
    }

    gpio_config_t rtc_int_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_RTC_INT),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&rtc_int_cfg);

    ESP_LOGD(TAG, "Early IO configuration complete (GPIO ISR service and button glitch filters active).");
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

static bool               s_led_pwm_active    = false;
static esp_timer_handle_t s_breath_timer      = NULL;
static volatile bool      s_breathing_running = false;
static volatile bool      s_breath_phase_high = false;
static volatile uint32_t  s_breath_half_ms    = HAL_IO_DEFAULT_BREATH_PERIOD_MS / 2U;

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
        .speed_mode      = HAL_LEDC_MODE,
        .duty_resolution = HAL_LEDC_DUTY_RES,
        .timer_num       = HAL_LEDC_TIMER,
        .freq_hz         = HAL_LEDC_FREQUENCY,
        .clk_cfg         = LEDC_AUTO_CLK,
        .deconfigure     = false,
    };
    esp_err_t err = ledc_timer_config(&timer_cfg);
    if (err != ESP_OK) {
        return err;
    }

    ledc_channel_config_t ch_cfg = {
        .gpio_num   = HAL_PIN_STATUS_LED,
        .speed_mode = HAL_LEDC_MODE,
        .channel    = HAL_LEDC_CHANNEL,
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = HAL_LEDC_TIMER,
        .duty       = 0,
        .hpoint     = 0,
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

/**
 * @brief Periodic esp_timer callback driving hardware LEDC fade-in / fade-out half-cycles.
 */
static void hal_led_breath_timer_cb(void *arg)
{
    (void)arg;
    if (!s_breathing_running || !s_led_pwm_active) {
        return;
    }
    s_breath_phase_high = !s_breath_phase_high;
    (void)hal_led_fade_to(s_breath_phase_high ? 100U : 0U, s_breath_half_ms);
}

/**
 * @brief Starts an asynchronous periodic esp_timer to "breathe" (fade in and fade out) the status LED.
 *
 * @details Uses hardware LEDC PWM fading paced by a periodic esp_timer alarm (eliminating dedicated FreeRTOS task stack and 50 ms polling).
 *
 * @param[in]    cycle_period_ms Total duration of one breathe cycle in ms (fade-in + fade-out). Default: 2000 ms if 0.
 *
 * @return ESP_OK on success, or error code if timer creation fails.
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
    uint32_t half = cycle_period_ms / 2U;
    if (half < 100U) {
        half = 100U;
    }
    s_breath_half_ms = half;

    if (s_breath_timer == NULL) {
        const esp_timer_create_args_t timer_args = {
            .callback        = &hal_led_breath_timer_cb,
            .arg             = NULL,
            .dispatch_method = ESP_TIMER_TASK,
            .name            = "hal_led_breath",
            .skip_unhandled_events = true,
        };
        esp_err_t err = esp_timer_create(&timer_args, &s_breath_timer);
        if (err != ESP_OK) {
            return err;
        }
    } else {
        (void)esp_timer_stop(s_breath_timer);
    }

    s_breathing_running = true;
    s_breath_phase_high = true;
    (void)hal_led_fade_to(100U, half);
    return esp_timer_start_periodic(s_breath_timer, (uint64_t)half * 1000ULL);
}

/**
 * @brief Stops the asynchronous LED breathing timer and turns the LED off immediately.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_led_stop_breathing(void)
{
    s_breathing_running = false;
    if (s_breath_timer != NULL) {
        (void)esp_timer_stop(s_breath_timer);
    }
    if (s_led_pwm_active) {
        hal_led_set_brightness(0);
    }
    return ESP_OK;
}

/**
 * @brief Queries whether the asynchronous LED breathing timer is actively running.
 *
 * @return True if breathing timer is active, false otherwise.
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

    if (s_breath_timer != NULL) {
        (void)esp_timer_delete(s_breath_timer);
        s_breath_timer = NULL;
    }

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
    hal_btn_mask_t raw = hal_io_sample_raw_buttons();
    s_debounced_btn_mask = raw;
    return raw;
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
    /* Disarm tactile button GPIO ISRs and debounce timer before switching pins to RTC IO domain */
    if (s_btn_isr_installed) {
        (void)gpio_isr_handler_remove(HAL_PIN_BUTTON_BOOT);
        (void)gpio_isr_handler_remove(HAL_PIN_BUTTON_POWER);
        s_btn_isr_installed = false;
    }
    if (s_btn_debounce_timer != NULL) {
        (void)esp_timer_stop(s_btn_debounce_timer);
    }
    if (s_boot_glitch_flt != NULL) {
        (void)gpio_glitch_filter_disable(s_boot_glitch_flt);
        (void)gpio_del_glitch_filter(s_boot_glitch_flt);
        s_boot_glitch_flt = NULL;
    }
    if (s_pwr_glitch_flt != NULL) {
        (void)gpio_glitch_filter_disable(s_pwr_glitch_flt);
        (void)gpio_del_glitch_filter(s_pwr_glitch_flt);
        s_pwr_glitch_flt = NULL;
    }

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