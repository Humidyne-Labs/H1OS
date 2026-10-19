/**
 * @file sub_display.cpp
 * @brief Layer 2: SSD1681 e-Paper display manager implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_display.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "h1os/hal_io.h"
#include "h1os/hal_spi.h"
#include "h1os/hal_types.h"
#include "h1os/orch_state.h"

#include <string.h>

static const char *TAG = "sub_display";

static uint8_t s_current_frame[EPD_BUFFER_SIZE];
static uint8_t s_previous_frame[EPD_BUFFER_SIZE];

static bool s_inited = false;

static const uint8_t WF_PARTIAL_1IN54[159] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};

static void epd_reset_pulse(void)
{
    gpio_set_level(HAL_PIN_EPD_RST, 0);
    esp_rom_delay_us(10000);
    gpio_set_level(HAL_PIN_EPD_RST, 1);
    esp_rom_delay_us(10000);
}

esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
{
    esp_rom_delay_us(200);

    TickType_t start_ticks = xTaskGetTickCount();
    while (gpio_get_level(HAL_PIN_EPD_BUSY) == 1) {
        TickType_t elapsed = xTaskGetTickCount() - start_ticks;
        if (elapsed >= timeout_ticks) {
            ESP_LOGW(TAG, "SSD1681 BUSY wait timed out");
            return ESP_ERR_TIMEOUT;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return ESP_OK;
}

static void epd_configure_base_registers(void)
{
    uint8_t d_drv[] = {0xC7, 0x00, 0x00};
    hal_spi_write_cmd(0x01);
    hal_spi_write_data(d_drv, sizeof(d_drv));

    uint8_t d_entry[] = {0x03};
    hal_spi_write_cmd(0x11);
    hal_spi_write_data(d_entry, sizeof(d_entry));

    uint8_t d_xwin[] = {0x00, 0x18};
    hal_spi_write_cmd(0x44);
    hal_spi_write_data(d_xwin, sizeof(d_xwin));

    uint8_t d_ywin[] = {0x00, 0x00, 0xC7, 0x00};
    hal_spi_write_cmd(0x45);
    hal_spi_write_data(d_ywin, sizeof(d_ywin));

    uint8_t d_border[] = {0x05};
    hal_spi_write_cmd(0x3C);
    hal_spi_write_data(d_border, sizeof(d_border));
}

esp_err_t sub_display_init(bool is_wake_cycle)
{
    if (s_inited)
        return ESP_OK;

    hal_spi_init();

    gpio_config_t busy_conf = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&busy_conf);

    epd_reset_pulse();
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    hal_spi_write_cmd(0x12);
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50;
    uint8_t temp_raw[2] = {0};

    hal_spi_write_cmd(0x18);
    uint8_t t_sel[] = {0x80};
    hal_spi_write_data(t_sel, sizeof(t_sel));

    hal_spi_write_cmd(0x22);
    uint8_t t_load[] = {0xB1};
    hal_spi_write_data(t_load, sizeof(t_load));

    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(100));

    if (hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw)) == ESP_OK) {
        if (temp_raw[0] != 0x00 && temp_raw[0] != 0xFF) {
            int8_t temp_int = (int8_t)temp_raw[0];
            int16_t frac_c = (temp_raw[1] & 0x80) ? SSD1681_TEMP_HALF_DEG_CENTI_C : 0;
            int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);
            if (glass_cc >= -4000 && glass_cc <= 8500) {
                orch_state_get()->last_glass_temp_centi_c = glass_cc;
                ESP_LOGI(TAG, "SSD1681 Pre-display Glass Temp acquired: %.2f C (Raw: 0x%02X 0x%02X)",
                         (double)glass_cc / 100.0, temp_raw[0], temp_raw[1]);
            }
        }
    }

    epd_configure_base_registers();

    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);

    s_inited = true;
    return ESP_OK;
}

uint8_t *sub_display_get_framebuffer(void)
{
    return s_current_frame;
}

void sub_display_clear(uint8_t color)
{
    memset(s_current_frame, color, EPD_BUFFER_SIZE);
}

static void epd_commit_ram_dma(uint8_t ram_cmd, const uint8_t *frame_data)
{
    static const uint8_t d_x[] = {0x00};
    static const uint8_t d_y[] = {0x00, 0x00};

    hal_spi_write_cmd(0x4E);
    hal_spi_write_data(d_x, sizeof(d_x));
    hal_spi_write_cmd(0x4F);
    hal_spi_write_data(d_y, sizeof(d_y));

    hal_spi_write_cmd(ram_cmd);
    hal_spi_write_frame_dma(frame_data);
}

esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame)
{
    if (prev_frame == NULL)
        return ESP_ERR_INVALID_ARG;

    memcpy(s_previous_frame, prev_frame, EPD_BUFFER_SIZE);
    memcpy(s_current_frame, prev_frame, EPD_BUFFER_SIZE);

    epd_commit_ram_dma(0x26, s_previous_frame);

    ESP_LOGI(TAG, "SSD1681 RAM 0x26 synchronized with prior frame for differential scan");
    return ESP_OK;
}

esp_err_t sub_display_refresh_full(void)
{
    int64_t t_start = esp_timer_get_time();

    hal_spi_write_cmd(0x12);
    sub_display_wait_busy(pdMS_TO_TICKS(1000));
    epd_configure_base_registers();

    epd_commit_ram_dma(0x24, s_current_frame);

    epd_commit_ram_dma(0x26, s_current_frame);

    uint8_t d_upd[] = {0xF7};
    hal_spi_write_cmd(0x22);
    hal_spi_write_data(d_upd, sizeof(d_upd));

    hal_spi_write_cmd(0x20);

    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Full OTP Refresh completed in %lld ms", t_elapsed_ms);

    return ESP_OK;
}

esp_err_t sub_display_clear_to_white_full(void)
{
    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);
    ESP_LOGI(TAG, "Clearing e-Paper display to pure white for storage / burn-in protection...");
    return sub_display_refresh_full();
}

static void epd_load_custom_lut(const uint8_t *lut_buffer)
{
    if (lut_buffer == NULL)
        return;

    hal_spi_write_cmd(0x32);
    hal_spi_write_data(&lut_buffer[0], 153);

    hal_spi_write_cmd(0x3F);
    hal_spi_write_data(&lut_buffer[153], 1);

    hal_spi_write_cmd(0x03);
    hal_spi_write_data(&lut_buffer[154], 1);

    hal_spi_write_cmd(0x04);
    hal_spi_write_data(&lut_buffer[155], 3);

    hal_spi_write_cmd(0x2C);
    hal_spi_write_data(&lut_buffer[158], 1);
}

esp_err_t sub_display_refresh_partial(void)
{
    int64_t t_start = esp_timer_get_time();

    epd_commit_ram_dma(0x24, s_current_frame);

    epd_load_custom_lut(WF_PARTIAL_1IN54);

    static const uint8_t disp_option[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};
    hal_spi_write_cmd(0x37);
    hal_spi_write_data(disp_option, sizeof(disp_option));

    uint8_t d_border[] = {0x80};
    hal_spi_write_cmd(0x3C);
    hal_spi_write_data(d_border, sizeof(d_border));

    uint8_t d_upd[] = {0xCF};
    hal_spi_write_cmd(0x22);
    hal_spi_write_data(d_upd, sizeof(d_upd));

    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(2000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", t_elapsed_ms);

    return ESP_OK;
}

esp_err_t sub_display_read_glass_temp(float *out_temp_c)
{
    if (out_temp_c == NULL)
        return ESP_ERR_INVALID_ARG;

    if (s_inited) {
        *out_temp_c = (float)orch_state_get()->last_glass_temp_centi_c / 100.0f;
        return ESP_OK;
    }

    uint8_t temp_raw[2] = {0};

    hal_spi_write_cmd(0x18);
    uint8_t t_sel[] = {0x80};
    hal_spi_write_data(t_sel, sizeof(t_sel));

    hal_spi_write_cmd(0x22);
    uint8_t t_load[] = {0xB1};
    hal_spi_write_data(t_load, sizeof(t_load));

    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(100));

    esp_err_t err = hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw));
    if (err == ESP_OK) {
        int8_t temp_int = (int8_t)temp_raw[0];
        float temp_frac = (temp_raw[1] & 0x80) ? 0.5f : 0.0f;
        float glass_temp = (float)temp_int + ((temp_int >= 0) ? temp_frac : -temp_frac);

        if (glass_temp < -40.0f || glass_temp > 85.0f || temp_raw[0] == 0xFF || temp_raw[0] == 0x00) {
            *out_temp_c = (float)orch_state_get()->last_glass_temp_centi_c / 100.0f;
            return ESP_ERR_INVALID_RESPONSE;
        }
        orch_state_get()->last_glass_temp_centi_c = (int16_t)(glass_temp * 100.0f);
        *out_temp_c = glass_temp;
    } else {
        *out_temp_c = (float)orch_state_get()->last_glass_temp_centi_c / 100.0f;
    }
    return err;
}

esp_err_t sub_display_enter_deep_sleep(void)
{
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    uint8_t d_sleep[] = {0x01};
    hal_spi_write_cmd(0x10);
    hal_spi_write_data(d_sleep, sizeof(d_sleep));
    return ESP_OK;
}
