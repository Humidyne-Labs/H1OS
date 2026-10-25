/**
 * @file sub_display.cpp
 * @brief Layer 2: SSD1681 e-Paper display manager implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_display.h"
#include "h1os_constants.h"

#include "driver/gpio.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "h1os/hal_io.h"
#include "h1os/hal_spi.h"
#include "h1os/hal_types.h"

#include <string.h>

static const char *TAG = "sub_display";

static uint8_t s_current_frame[EPD_BUFFER_SIZE];
static uint8_t s_previous_frame[EPD_BUFFER_SIZE];

static bool s_inited = false;
static bool s_in_deep_sleep = false;
static int16_t s_last_glass_temp_centi_c = 0;

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

/**
 * @brief Epd reset pulse.
 *
 * @details Wakes SSD1681 out of Deep Sleep Mode 1 (0x10 = 0x01) and resets state machine.
 *
 * @return Return value of type static void.
 */
static void epd_reset_pulse(void)
{
    gpio_set_level(HAL_PIN_EPD_RST, 0);
    esp_rom_delay_us(2000);
    gpio_set_level(HAL_PIN_EPD_RST, 1);
    esp_rom_delay_us(2000);
    s_in_deep_sleep = false;
}

/**
 * @brief Synchronously wait for EPD panel to finish driving electrophoretic particles.
 *
 * @details Waits up to 15 ms for the SSD1681 state machine to assert BUSY HIGH (1) after
 *          a command (e.g. 0x20 Master Activation or 0x12 SW Reset), then polls until
 *          BUSY drops back LOW (0).
 *
 * @param[in]    timeout_ticks   Max FreeRTOS ticks to wait.
 *
 * @return ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.
 */
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
{
    /* Wait up to 15 ms for BUSY (GPIO 8) to assert HIGH after command issue */
    for (int32_t i = 0; i < (int32_t)H1OS_DISPLAY_IDLE_POLL_BOUND; i++) {
        if (gpio_get_level(HAL_PIN_EPD_BUSY) == 1) {
            break;
        }
        esp_rom_delay_us(250);
    }

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

/**
 * @brief Epd configure base registers.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_configure_base_registers(void)
{
    uint8_t d_drv[] = {0xC7, 0x00, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x01), TAG, "SPI cmd 0x01 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_drv, sizeof(d_drv)), TAG, "SPI data 0x01 failed");

    uint8_t d_entry[] = {0x03};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x11), TAG, "SPI cmd 0x11 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_entry, sizeof(d_entry)), TAG, "SPI data 0x11 failed");

    uint8_t d_xwin[] = {0x00, 0x18};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x44), TAG, "SPI cmd 0x44 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_xwin, sizeof(d_xwin)), TAG, "SPI data 0x44 failed");

    uint8_t d_ywin[] = {0x00, 0x00, 0xC7, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x45), TAG, "SPI cmd 0x45 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_ywin, sizeof(d_ywin)), TAG, "SPI data 0x45 failed");

    uint8_t d_border[] = {0x05};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");
    return ESP_OK;
}

/**
 * @brief Initialize SSD1681 display controller.
 *
 * @details Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization.
 *
 * @param[in]    is_wake_cycle   True if resuming from deep sleep with persistent framebuffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_init(bool is_wake_cycle)
{
    (void)is_wake_cycle;
    if (s_inited) {
        if (s_in_deep_sleep) {
            epd_reset_pulse();
            sub_display_wait_busy(pdMS_TO_TICKS(1000));
            hal_spi_write_cmd(0x12);
            sub_display_wait_busy(pdMS_TO_TICKS(1000));
            epd_configure_base_registers();
        }
        return ESP_OK;
    }

    hal_spi_init();

    gpio_config_t busy_conf = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
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
                s_last_glass_temp_centi_c = glass_cc;
                ESP_LOGI(TAG, "SSD1681 Pre-display Glass Temp acquired: %.2f C (Raw: 0x%02X 0x%02X)",
                         (double)((float)glass_cc / 100.0f), temp_raw[0], temp_raw[1]);
            }
        }
    }

    epd_configure_base_registers();

    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);

    s_inited = true;
    return ESP_OK;
}

/**
 * @brief Deinitialize SSD1681 display subsystem and release SPI bus resources.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_deinit(void)
{
    if (!s_inited) {
        return ESP_OK;
    }

    sub_display_enter_deep_sleep();
    hal_spi_deinit();
    s_inited = false;
    return ESP_OK;
}

uint8_t *sub_display_get_framebuffer(void)
{
    return s_current_frame;
}

/**
 * @brief Clear active working framebuffer.
 *
 * @param[in]    color           0xFF for White, 0x00 for Black.
 */
void sub_display_clear(uint8_t color)
{
    memset(s_current_frame, color, EPD_BUFFER_SIZE);
}

/**
 * @brief Epd commit ram dma.
 *
 * @param[in]    ram_cmd         Parameter ram_cmd.
 * @param[in]    frame_data      Parameter frame_data.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_commit_ram_dma(uint8_t ram_cmd, const uint8_t *frame_data)
{
    static const uint8_t d_x[] = {0x00};
    static const uint8_t d_y[] = {0x00, 0x00};

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4E), TAG, "SPI cmd 0x4E failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_x, sizeof(d_x)), TAG, "SPI data 0x4E failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4F), TAG, "SPI cmd 0x4F failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_y, sizeof(d_y)), TAG, "SPI data 0x4F failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(ram_cmd), TAG, "SPI ram_cmd failed");
    return hal_spi_write_frame_dma(frame_data);
}

/**
 * @brief Synchronize previous frame into shadow buffer and hardware RAM 0x26.
 *
 * @details Essential on deep sleep wake to enable differential partial scanning against the glass.
 *
 * @param[in]    prev_frame      Pointer to 5000-byte pre-sleep image buffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame)
{
    if (prev_frame == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memcpy(s_previous_frame, prev_frame, EPD_BUFFER_SIZE);
    memcpy(s_current_frame, prev_frame, EPD_BUFFER_SIZE);

    epd_commit_ram_dma(0x26, s_previous_frame);

    ESP_LOGI(TAG, "SSD1681 RAM 0x26 synchronized with prior frame for differential scan");
    return ESP_OK;
}

/**
 * @brief Execute full display refresh (OTP factory waveform LUT).
 *
 * @details Synchronizes old frame RAM (0x26) with new frame RAM (0x24).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_full(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }

    int64_t t_start = esp_timer_get_time();

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x12), TAG, "SPI cmd 0x12 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(1000));
    ESP_RETURN_ON_ERROR(epd_configure_base_registers(), TAG, "Base registers config failed");

    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");
    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x26, s_current_frame), TAG, "Commit RAM 0x26 failed");

    uint8_t d_upd[] = {0xF7};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Full OTP Refresh completed in %lld ms", (long long)t_elapsed_ms);

    return ESP_OK;
}

/**
 * @brief Clear display to pure white and trigger full OTP refresh.
 *
 * @details Clears and discharges electrophoretic microcapsules to protect against permanent burn-in.
 *          Ensures SPI2 and SSD1681 are initialized and awake even when invoked directly from
 *          deep-sleep ULP power-off wakes (ORCH_FLOW_CRITICAL_OFF).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_clear_to_white_full(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }
    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);
    ESP_LOGI(TAG, "Clearing e-Paper display to pure white for storage / burn-in protection...");
    return sub_display_refresh_full();
}

/**
 * @brief Epd load custom lut.
 *
 * @param[in]    lut_buffer      Parameter lut_buffer.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_load_custom_lut(const uint8_t *lut_buffer)
{
    if (lut_buffer == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x32), TAG, "SPI cmd 0x32 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3F), TAG, "SPI cmd 0x3F failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[153], 1), TAG, "SPI data 0x3F failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x03), TAG, "SPI cmd 0x03 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[154], 1), TAG, "SPI data 0x03 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x04), TAG, "SPI cmd 0x04 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x2C), TAG, "SPI cmd 0x2C failed");
    return hal_spi_write_data(&lut_buffer[158], 1);
}

/**
 * @brief Execute fast partial refresh (~300ms) with software LUT.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_partial(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }

    int64_t t_start = esp_timer_get_time();

    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");

    ESP_RETURN_ON_ERROR(epd_load_custom_lut(WF_PARTIAL_1IN54), TAG, "Custom LUT load failed");

    static const uint8_t disp_option[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x37), TAG, "SPI cmd 0x37 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(disp_option, sizeof(disp_option)), TAG, "SPI data 0x37 failed");

    uint8_t d_border[] = {0x80};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");

    uint8_t d_upd[] = {0xCF};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(2000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);

    return ESP_OK;
}

/**
 * @brief Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.
 *
 * @return Cached glass temperature in centi-°C (0 if not yet sampled).
 */
int16_t sub_display_get_glass_temp_centi_c(void)
{
    return s_last_glass_temp_centi_c;
}

/**
 * @brief Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).
 *
 * @param[out]   out_temp_c      Surface glass temperature in Celsius.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_read_glass_temp(float *out_temp_c)
{
    if (out_temp_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (s_inited) {
        *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
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
            *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
            return ESP_ERR_INVALID_RESPONSE;
        }
        s_last_glass_temp_centi_c = (int16_t)(glass_temp * 100.0f);
        *out_temp_c = glass_temp;
    } else {
        *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
    }
    return err;
}

/**
 * @brief Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).
 *
 * @details Crucially retains RAM contents while the 3.3V rail remains held.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_enter_deep_sleep(void)
{
    if (!s_inited || s_in_deep_sleep) {
        return ESP_OK;
    }

    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    uint8_t d_sleep[] = {0x01};
    hal_spi_write_cmd(0x10);
    hal_spi_write_data(d_sleep, sizeof(d_sleep));
    s_in_deep_sleep = true;
    return ESP_OK;
}
