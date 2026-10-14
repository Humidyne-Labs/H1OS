/**
 * @file sub_display.cpp
 * @brief Layer 2: SSD1681 1.54" E-Paper Display Manager Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_display.h"
#include "h1os/orch_state.h"
#include "h1os/hal_spi.h"
#include "h1os/hal_types.h"
#include "h1os/hal_io.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "esp_timer.h"
#include <string.h>

static const char *TAG = "sub_display";

/* Ping-Pong Framebuffers in DMA-capable internal SRAM */
static uint8_t s_current_frame[EPD_BUFFER_SIZE];
static uint8_t s_previous_frame[EPD_BUFFER_SIZE];

static SemaphoreHandle_t s_busy_sem = NULL;

static bool s_inited = false;

/* Factory-calibrated 159-byte Partial LUT */
static const uint8_t WF_PARTIAL_1IN54[159] = {
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00,
    0x02, 0x17, 0x41, 0xB0, 0x32, 0x28
};

static void IRAM_ATTR epd_busy_isr_handler(void* arg)
{
    BaseType_t high_task_wakeup = pdFALSE;
    if (s_busy_sem != NULL) {
        xSemaphoreGiveFromISR(s_busy_sem, &high_task_wakeup);
        portYIELD_FROM_ISR(high_task_wakeup);
    }
}

static void epd_reset_pulse(void)
{
    gpio_set_level(HAL_PIN_EPD_RST, 0);
    esp_rom_delay_us(10000);
    gpio_set_level(HAL_PIN_EPD_RST, 1);
    esp_rom_delay_us(10000);
}

esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
{
    /* Brief settle delay in case a command (0x20 / 0x12) was just clocked out over SPI */
    esp_rom_delay_us(200);

    TickType_t start_ticks = xTaskGetTickCount();
    while (gpio_get_level(HAL_PIN_EPD_BUSY) == 1) {
        TickType_t elapsed = xTaskGetTickCount() - start_ticks;
        if (elapsed >= timeout_ticks) {
            ESP_LOGW(TAG, "SSD1681 BUSY wait timed out");
            return ESP_ERR_TIMEOUT;
        }
        if (s_busy_sem != NULL) {
            TickType_t remain = timeout_ticks - elapsed;
            TickType_t step = pdMS_TO_TICKS(20);
            if (step == 0) step = 1;
            if (remain < step) step = remain;
            if (xSemaphoreTake(s_busy_sem, step) == pdTRUE && gpio_get_level(HAL_PIN_EPD_BUSY) == 0) {
                /* Re-give token so any concurrent waiter (e.g. sleep transition waiting on LVGL flush) wakes immediately */
                xSemaphoreGive(s_busy_sem);
                return ESP_OK;
            }
        } else {
            esp_rom_delay_us(1000);
        }
    }

    return ESP_OK;
}

static void epd_configure_base_registers(void)
{
    /* Driver output control: 200 mux lines (0xC7, 0x00, 0x00) */
    uint8_t d_drv[] = { 0xC7, 0x00, 0x00 };
    hal_spi_write_cmd(0x01);
    hal_spi_write_data(d_drv, sizeof(d_drv));

    /* Data entry mode: X inc, Y inc */
    uint8_t d_entry[] = { 0x03 };
    hal_spi_write_cmd(0x11);
    hal_spi_write_data(d_entry, sizeof(d_entry));

    /* Set RAM X address window: 0 to 24 (200 pixels / 8 = 25 bytes) */
    uint8_t d_xwin[] = { 0x00, 0x18 };
    hal_spi_write_cmd(0x44);
    hal_spi_write_data(d_xwin, sizeof(d_xwin));

    /* Set RAM Y address window: 0 to 199 (0x0000 to 0x00C7) */
    uint8_t d_ywin[] = { 0x00, 0x00, 0xC7, 0x00 };
    hal_spi_write_cmd(0x45);
    hal_spi_write_data(d_ywin, sizeof(d_ywin));

    /* Border waveform: factory default for full OTP refresh */
    uint8_t d_border[] = { 0x05 };
    hal_spi_write_cmd(0x3C);
    hal_spi_write_data(d_border, sizeof(d_border));
}

esp_err_t sub_display_init(bool is_wake_cycle)
{
    if (s_inited) return ESP_OK;

    /* 1. Init SPI and GPIO */
    hal_spi_init();

    /* 2. Configure BUSY interrupt pin (RST is handled by hal_spi_init) */
    gpio_config_t busy_conf = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_NEGEDGE, /* High -> Low when idle */
    };
    gpio_config(&busy_conf);

    if (s_busy_sem == NULL) {
        s_busy_sem = xSemaphoreCreateBinary();
    }
    gpio_install_isr_service(0);
    gpio_isr_handler_add(HAL_PIN_EPD_BUSY, epd_busy_isr_handler, NULL);

    /* 3. Hardware Reset Pulse */
    epd_reset_pulse();
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    /* 4. SSD1681 Initialization Sequence */
    hal_spi_write_cmd(0x12); /* Software Reset */
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    /* 4b. Pre-Display Glass Temperature Capture (Command 0x1B):
     * Strictly read BEFORE any RAM write, LUT load, or charge-pump activation
     * to prevent display refresh heat from offsetting the glass thermistor. */
    uint8_t temp_raw[2] = {0};
    if (hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw)) == ESP_OK) {
        if (temp_raw[0] != 0x00 && temp_raw[0] != 0xFF) {
            int8_t temp_int  = (int8_t)temp_raw[0];
            int16_t frac_c   = (temp_raw[1] & 0x80) ? 50 : 0;
            int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);
            if (glass_cc >= -4000 && glass_cc <= 8500) {
                orch_state_get()->last_glass_temp_centi_c = glass_cc;
            }
        }
    }

    epd_configure_base_registers();

    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);

    s_inited = true;
    return ESP_OK;
}

uint8_t* sub_display_get_framebuffer(void)
{
    return s_current_frame;
}

void sub_display_clear(uint8_t color)
{
    memset(s_current_frame, color, EPD_BUFFER_SIZE);
}

static void set_ram_counters(void)
{
    uint8_t d_x[] = { 0x00 };
    hal_spi_write_cmd(0x4E);
    hal_spi_write_data(d_x, sizeof(d_x));
    uint8_t d_y[] = { 0x00, 0x00 };
    hal_spi_write_cmd(0x4F);
    hal_spi_write_data(d_y, sizeof(d_y));
}

esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame)
{
    if (prev_frame == NULL) return ESP_ERR_INVALID_ARG;

    memcpy(s_previous_frame, prev_frame, EPD_BUFFER_SIZE);
    memcpy(s_current_frame, prev_frame, EPD_BUFFER_SIZE);

    set_ram_counters();
    hal_spi_write_cmd(0x26);
    hal_spi_write_frame_dma(s_previous_frame);

    ESP_LOGI(TAG, "SSD1681 RAM 0x26 synchronized with prior frame for differential scan");
    return ESP_OK;
}

esp_err_t sub_display_refresh_full(void)
{
    int64_t t_start = esp_timer_get_time();

    /* 1. Reset SSD1681 out of any prior custom partial LUT (0x32) or Ping-Pong
     *    differential mode (0x37 = 0x40) so 0x22 = 0xF7 reloads the factory OTP LUT. */
    hal_spi_write_cmd(0x12); /* Software Reset */
    sub_display_wait_busy(pdMS_TO_TICKS(1000));
    epd_configure_base_registers();

    /* 2. Write to RAM 0x24 (Current Frame) */
    set_ram_counters();
    hal_spi_write_cmd(0x24);
    hal_spi_write_frame_dma(s_current_frame);

    /* 3. Write to RAM 0x26 (Previous Frame) */
    set_ram_counters();
    hal_spi_write_cmd(0x26);
    hal_spi_write_frame_dma(s_current_frame);

    /* 4. Display Update Control 2: Full OTP refresh sequence (0xF7) */
    uint8_t d_upd[] = { 0xF7 };
    hal_spi_write_cmd(0x22);
    hal_spi_write_data(d_upd, sizeof(d_upd));

    /* 5. Master Activation */
    hal_spi_write_cmd(0x20);

    /* 6. Wait for panel completion */
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    /* 7. Sync shadow buffer */
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
    if (lut_buffer == NULL) return;

    /* 1. Core Look-Up Tables 0-4 and Timing Groups 0-11 (153 bytes) */
    hal_spi_write_cmd(0x32);
    hal_spi_write_data(&lut_buffer[0], 153);

    /* 2. End of Frame Pulse Timing (EOPT) (1 byte) */
    hal_spi_write_cmd(0x3F);
    hal_spi_write_data(&lut_buffer[153], 1);

    /* 3. Gate Driving Voltage (1 byte) */
    hal_spi_write_cmd(0x03);
    hal_spi_write_data(&lut_buffer[154], 1);

    /* 4. Source Driving Voltages (VSH1, VSH2, VSL) (3 bytes) */
    hal_spi_write_cmd(0x04);
    hal_spi_write_data(&lut_buffer[155], 3);

    /* 5. VCOM Modulation Voltage (1 byte) */
    hal_spi_write_cmd(0x2C);
    hal_spi_write_data(&lut_buffer[158], 1);
}

esp_err_t sub_display_refresh_partial(void)
{
    int64_t t_start = esp_timer_get_time();

    /* 1. Write New Frame to RAM 0x24 (DO NOT overwrite 0x26 in differential mode!) */
    set_ram_counters();
    hal_spi_write_cmd(0x24);
    hal_spi_write_frame_dma(s_current_frame);

    /* 2. Load SSD1681 Partial LUT partitioned across 5 registers */
    epd_load_custom_lut(WF_PARTIAL_1IN54);

    /* 3. Configure Display Option (0x37) & Border Waveform (0x3C) for Differential Scan */
    static const uint8_t disp_option[10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00 };
    hal_spi_write_cmd(0x37);
    hal_spi_write_data(disp_option, sizeof(disp_option));

    uint8_t d_border[] = { 0x80 }; // Border Floating / LUT0
    hal_spi_write_cmd(0x3C);
    hal_spi_write_data(d_border, sizeof(d_border));

    /* 4. Trigger Partial Display Update (0x22 0xCF + 0x20) */
    uint8_t d_upd[] = { 0xCF };
    hal_spi_write_cmd(0x22);
    hal_spi_write_data(d_upd, sizeof(d_upd));

    /* Master Activation */
    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(2000));

    /* 5. Sync shadow buffer */
    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", t_elapsed_ms);

    return ESP_OK;
}

esp_err_t sub_display_read_glass_temp(float *out_temp_c)
{
    if (out_temp_c == NULL) return ESP_ERR_INVALID_ARG;

    /* If display is already initialized, return the pristine pre-display glass reading
     * captured at the start of sub_display_init() before any charge-pump refresh heat. */
    if (s_inited) {
        *out_temp_c = (float)orch_state_get()->last_glass_temp_centi_c / 100.0f;
        return ESP_OK;
    }

    uint8_t temp_raw[2] = {0};
    /* SSD1681 Command 0x1B: Read Temperature Sensor */
    esp_err_t err = hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw));
    if (err == ESP_OK) {
        int8_t temp_int   = (int8_t)temp_raw[0];
        float  temp_frac  = (temp_raw[1] & 0x80) ? 0.5f : 0.0f;
        float  glass_temp = (float)temp_int + ((temp_int >= 0) ? temp_frac : -temp_frac);

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
    /* Ensure panel is completely finished before issuing sleep command */
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    /* Deep Sleep Mode 1: Keeps RAM retained @ 1.0 µA */
    uint8_t d_sleep[] = { 0x01 };
    hal_spi_write_cmd(0x10);
    hal_spi_write_data(d_sleep, sizeof(d_sleep));
    return ESP_OK;
}
