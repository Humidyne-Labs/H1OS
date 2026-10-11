/**
 * @file bsp_display.cpp
 * @brief SSD1681 1.54" 200x200 Monochrome e-Paper Display Driver Implementation
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Peripheral Driver Basis: Waveshare Electronics 1.54" V2 SPI e-Paper Display Codebase
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_rom_gpio.h"
#include "soc/gpio_sig_map.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "bsp/pinout.h"
#include "bsp/bsp_display.h"
#include "bsp/bsp_rtc_mem.h"
#include "bsp/bsp.h"

static const char *TAG = "bsp_display";

// SSD1681 Factory-calibrated 159-byte Partial LUT (Datasheet Figure 6-6 layout)
static const uint8_t WF_PARTIAL_1IN54[159] = {
    // 000..011: LUT0 (Black -> Black)
    0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 012..023: LUT1 (Black -> White)
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 024..035: LUT2 (White -> Black)
    0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 036..047: LUT3 (White -> White)
    0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 048..059: LUT4 (VCOM Modulation)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 060..143: Timing Groups 0 to 11 (TP, SR, RP)
    0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 0 (TP0A = 15 frames)
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 1
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 3
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 5
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 6
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 7
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 8
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 9
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 10
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Group 11
    // 144..149: Frame Rates (FR0..FR11 = 50Hz) & 150..152: XON
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00,
    // 153..158: EOPT (0x3F), Gate (0x03), Source (0x04), VCOM (0x2C)
    0x02, 0x17, 0x41, 0xB0, 0x32, 0x28
};

static spi_device_handle_t s_spi_handle            = NULL;
static spi_device_handle_t s_spi_read_handle       = NULL;
static uint8_t             *s_frame_buffer         = NULL;
static uint8_t             *s_prev_frame_buffer    = NULL;

static uint32_t s_partial_refresh_count = 0;
static bool     s_frame_dirty           = false;

static inline void epd_set_cs (uint8_t level) { gpio_set_level((gpio_num_t)BSP_PIN_EPD_CS,  level); }
static inline void epd_set_dc (uint8_t level) { gpio_set_level((gpio_num_t)BSP_PIN_EPD_DC,  level); }
static inline void epd_set_rst(uint8_t level) { gpio_set_level((gpio_num_t)BSP_PIN_EPD_RST, level); }

static inline bool display_power_enable(bool enable) { 
	gpio_set_level((gpio_num_t)BSP_PIN_EPD_3V3_EN, enable ? 0 : 1);
	return (gpio_get_level((gpio_num_t)BSP_PIN_EPD_3V3_EN) == 0);
}

esp_err_t bsp_display_wait_busy(uint32_t timeout_ms) {
    // Ensure display controller has time to assert BUSY high
    vTaskDelay(pdMS_TO_TICKS(20));
    TickType_t start_tick    = xTaskGetTickCount();
    TickType_t timeout_ticks = pdMS_TO_TICKS(timeout_ms);

    while (gpio_get_level(BSP_PIN_EPD_BUSY) == 1) {
        if ((xTaskGetTickCount() - start_tick) > timeout_ticks)
			return ESP_ERR_TIMEOUT;
        vTaskDelay(pdMS_TO_TICKS(10));
    } return ESP_OK;
}

#include "esp_memory_utils.h"

static uint8_t *s_dma_bounce_buf = NULL;

static void epd_send_byte(uint8_t data) {
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.flags      = SPI_TRANS_USE_TXDATA;
    t.length     = 8;
    t.tx_data[0] = data;
    spi_device_polling_transmit(s_spi_handle, &t);
}

static void epd_send_cmd(uint8_t cmd) {
    epd_set_dc    (0);
    epd_set_cs    (0);
    epd_send_byte (cmd);
    epd_set_cs    (1);
}

static void epd_send_data(uint8_t data) {
    epd_set_dc    (1);
    epd_set_cs    (0);
    epd_send_byte (data);
    epd_set_cs    (1);
}

static void epd_write_bytes(const uint8_t *data, size_t len)
{
    if (len == 0 || data == NULL) return;
	
    epd_set_dc(1); epd_set_cs(0);

    if (esp_ptr_dma_capable(data)) {
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));
        t.length    = 8 * len;
        t.tx_buffer = data;
        spi_device_polling_transmit(s_spi_handle, &t);
    } else {
        if (s_dma_bounce_buf == NULL) {
            s_dma_bounce_buf = (uint8_t *)heap_caps_malloc(256, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
        }
        size_t remaining = len;
        const uint8_t *ptr = data;
        while (remaining > 0) {
            size_t chunk = (remaining > 256) ? 256 : remaining;
            if (s_dma_bounce_buf) {
                memcpy(s_dma_bounce_buf, ptr, chunk);
                spi_transaction_t t;
                memset(&t, 0, sizeof(t));
                t.length    = 8 * chunk;
                t.tx_buffer = s_dma_bounce_buf;
                spi_device_polling_transmit(s_spi_handle, &t);
            } else {
                for (size_t i = 0; i < chunk; i++) {
                    epd_send_byte(ptr[i]);
                }
            }
            ptr       += chunk;
            remaining -= chunk;
        }
    }
    epd_set_cs(1);
}

static void epd_set_windows(uint16_t x_start_byte, uint16_t y_start, uint16_t x_end_byte, uint16_t y_end) {
    epd_send_cmd (0x44);
    epd_send_data(x_start_byte   & 0xFF);
    epd_send_data(x_end_byte     & 0xFF);

    epd_send_cmd (0x45);
    epd_send_data( y_start       & 0xFF);
    epd_send_data((y_start >> 8) & 0xFF);
    epd_send_data( y_end         & 0xFF);
    epd_send_data((y_end   >> 8) & 0xFF);
}

static void epd_set_cursor(uint16_t x_start_byte, uint16_t y_start) {
    epd_send_cmd (0x4E);
    epd_send_data(x_start_byte & 0xFF);

    epd_send_cmd (0x4F);
    epd_send_data( y_start       & 0xFF);
    epd_send_data((y_start >> 8) & 0xFF);
}

static void epd_load_custom_lut(const uint8_t *lut_buffer) {
    if (lut_buffer == NULL) return;

    epd_send_cmd (0x32); epd_write_bytes(lut_buffer, 153);
    epd_send_cmd (0x3F); epd_send_data(lut_buffer[153]);
    epd_send_cmd (0x03); epd_send_data(lut_buffer[154]);

    epd_send_cmd (0x04);
    epd_send_data(lut_buffer[155]);
    epd_send_data(lut_buffer[156]);
    epd_send_data(lut_buffer[157]);

    epd_send_cmd (0x2C);
    epd_send_data(lut_buffer[158]);
}

static void epd_apply_core_registers(bool is_wake_init) {
    epd_send_cmd   (0x01);
    epd_send_data  (( BSP_DISPLAY_HEIGHT - 1)       & 0xFF);
    epd_send_data  (((BSP_DISPLAY_HEIGHT - 1) >> 8) & 0xFF);
    epd_send_data  (0x00);

    epd_send_cmd   (0x11);
    epd_send_data  (0x03); // Increment X, Increment Y

    epd_send_cmd   (0x18);
    epd_send_data  (0x80); // Internal temperature sensor

    epd_set_windows(0, 0, (BSP_DISPLAY_WIDTH / 8) - 1, BSP_DISPLAY_HEIGHT - 1);
    epd_set_cursor (0, 0);

    epd_send_cmd   (0x3C);
    epd_send_data  (0x05); // Border waveform for full OTP mode

    epd_send_cmd   (0x22);
    epd_send_data  (0xB1);
    epd_send_cmd   (0x20); // Master Activation for Clock & Temp load
	
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);
}

esp_err_t bsp_display_init(void)
{
	if(display_power_enable(true) != true) return ESP_ERR_INVALID_STATE;
	
    if (s_frame_buffer == NULL) {
        s_frame_buffer = (uint8_t *)heap_caps_malloc(BSP_DISPLAY_BUFFER_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
        if (s_frame_buffer == NULL) s_frame_buffer = (uint8_t *)malloc(BSP_DISPLAY_BUFFER_SIZE);
        if (s_frame_buffer == NULL) return ESP_ERR_NO_MEM;
    }

    if (s_prev_frame_buffer == NULL) {
        s_prev_frame_buffer = (uint8_t *)heap_caps_malloc(BSP_DISPLAY_BUFFER_SIZE, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
        if (s_prev_frame_buffer == NULL) s_prev_frame_buffer = (uint8_t *)malloc(BSP_DISPLAY_BUFFER_SIZE);
        if (s_prev_frame_buffer == NULL) return ESP_ERR_NO_MEM;
    }

    bool is_wake = bsp_rtc_mem_has_display_frame();
    if (is_wake) {
        bsp_rtc_mem_load_display_frame(s_prev_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
        memcpy(s_frame_buffer, s_prev_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
        ESP_LOGI(TAG, "Restored previous EPD frame (5000B) from 'epd_frame' flash partition");
    } else {
        memset(s_frame_buffer,      0xFF, BSP_DISPLAY_BUFFER_SIZE);
        memset(s_prev_frame_buffer, 0xFF, BSP_DISPLAY_BUFFER_SIZE);
    }

    // 2. Initialize SPI Master Bus (GPIO 12 SCLK, GPIO 13 MOSI)
    if (s_spi_handle == NULL) {
        spi_bus_config_t buscfg = {};
        buscfg.mosi_io_num      = BSP_PIN_EPD_MOSI;
        buscfg.miso_io_num      = -1;
        buscfg.sclk_io_num      = BSP_PIN_EPD_SCK;
        buscfg.quadwp_io_num    = -1;
        buscfg.quadhd_io_num    = -1;
        buscfg.max_transfer_sz  = BSP_DISPLAY_BUFFER_SIZE + 8;

        spi_device_interface_config_t devcfg = {};
        devcfg.mode           = 0;
        devcfg.clock_speed_hz = 20 * 1000 * 1000;
        devcfg.spics_io_num   = -1;
        devcfg.queue_size     = 7;

        esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
        if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) return ret;

        ret = spi_bus_add_device(SPI2_HOST, &devcfg, &s_spi_handle);
        if (ret != ESP_OK) return ret;

        // Register half-duplex 3-wire SPI device handle for hardware sensor readout (No runtime bit-banging)
        spi_device_interface_config_t rdevcfg = {};
        rdevcfg.mode           = 0;
        rdevcfg.clock_speed_hz = 2 * 1000 * 1000;
        rdevcfg.spics_io_num   = -1;
        rdevcfg.flags          = SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_3WIRE;
        rdevcfg.queue_size     = 1;

        spi_bus_add_device(SPI2_HOST, &rdevcfg, &s_spi_read_handle);
    }

    // Full hardware reset pulse to cleanly wake SSD1681 from deep sleep mode 1
    epd_set_rst          (1); vTaskDelay(pdMS_TO_TICKS(10));
    epd_set_rst          (0); vTaskDelay(pdMS_TO_TICKS(10));
    epd_set_rst          (1); vTaskDelay(pdMS_TO_TICKS(10));
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);

    epd_send_cmd         (0x12); // SW Reset
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);

    epd_apply_core_registers(is_wake);

    if (is_wake) {
        // Pre-synchronize SSD1681 0x26 (Old RAM) with the restored frame from before sleep for differential scan
        epd_set_windows(0, 0, (BSP_DISPLAY_WIDTH / 8) - 1, BSP_DISPLAY_HEIGHT - 1);

        epd_set_cursor (0, 0);
        epd_send_cmd   (0x26);
        epd_write_bytes(s_prev_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
    }

    ESP_LOGI(TAG, "SSD1681 1.54-inch EPD initialized successfully (%s mode)", is_wake ? "wake" : "cold");
    return ESP_OK;
}

void bsp_display_clear(void) {
    if (s_frame_buffer != NULL) memset(s_frame_buffer, 0xFF, BSP_DISPLAY_BUFFER_SIZE);
}

void bsp_display_flush(void) {
    if (s_frame_buffer == NULL || s_prev_frame_buffer == NULL) return;

    epd_set_windows(0, 0, (BSP_DISPLAY_WIDTH / 8) - 1, BSP_DISPLAY_HEIGHT - 1);

    epd_set_cursor (0, 0);
    epd_send_cmd   (0x24);
    epd_write_bytes(s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);

    epd_set_cursor (0, 0);
    epd_send_cmd   (0x26);
    epd_write_bytes(s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);

    epd_send_cmd (0x3C);
    epd_send_data(0x05);

    epd_send_cmd         (0x22);
    epd_send_data        (0xC7);
    epd_send_cmd         (0x20);
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);

    memcpy(s_prev_frame_buffer, s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
    s_frame_dirty = true;
    s_partial_refresh_count = 0;
}

void bsp_display_flush_partial(void) {
    bsp_display_flush_partial_area(0, 0, BSP_DISPLAY_WIDTH - 1, BSP_DISPLAY_HEIGHT - 1);
}

void bsp_display_flush_partial_area(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
    if (s_frame_buffer == NULL || s_prev_frame_buffer == NULL) return;

    // Full 200x200 window mapping ensures perfect RAM address pointer alignment without row-by-row CS toggling
    epd_set_windows(0, 0, (BSP_DISPLAY_WIDTH / 8) - 1, BSP_DISPLAY_HEIGHT - 1);

    // 1. Write New RAM (0x24) with updated frame buffer (DO NOT overwrite 0x26 in Ping-Pong mode!)
    epd_set_cursor (0, 0);
    epd_send_cmd   (0x24);
    epd_write_bytes(s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);

    // 2. Load SSD1681 Partial LUT (159-byte waveform)
    epd_load_custom_lut(WF_PARTIAL_1IN54);

    // 3. Configure Display Option (0x37) & Border Waveform (0x3C) for Differential Ping-Pong Scan
    static const uint8_t disp_option[10] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00 };
    epd_send_cmd   (0x37);
    epd_write_bytes(disp_option, sizeof(disp_option));

    epd_send_cmd (0x3C);
    epd_send_data(0x80); // Border Floating / LUT0

    // 4. Trigger Partial Display Update (0x22 0xCF + 0x20 for differential pattern display)
    epd_send_cmd         (0x22);
    epd_send_data        (0xCF);
    epd_send_cmd         (0x20);
    bsp_display_wait_busy(EPD_PARTIAL_REFRESH_TIMEOUT_MS);

    // 5. Synchronize local frame buffer and mark dirty for deferred flash sync
    memcpy(s_prev_frame_buffer, s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
    s_frame_dirty = true;

    s_partial_refresh_count++;
}

esp_err_t bsp_display_sync_partition_frame(void)
{
    if (!s_frame_dirty || s_frame_buffer == NULL) {
        return ESP_OK; // Clean frame; skip flash write to preserve write endurance
    }

    ESP_LOGI(TAG, "Syncing dirty 1-bit EPD frame to 'epd_frame' flash partition before power-down/sleep...");
    esp_err_t err = bsp_rtc_mem_save_display_frame(s_frame_buffer, BSP_DISPLAY_BUFFER_SIZE);
    if (err == ESP_OK) {
        s_frame_dirty = false;
    }
    return err;
}

esp_err_t bsp_display_write_frame(const uint8_t *buffer) {
    if (buffer == NULL) return ESP_ERR_INVALID_ARG;
    if (s_frame_buffer == NULL) {
        esp_err_t ret = bsp_display_init();
        if (ret != ESP_OK) return ret;
    }
    memcpy(s_frame_buffer, buffer, BSP_DISPLAY_BUFFER_SIZE);
    return ESP_OK;
}

esp_err_t bsp_display_refresh(bool partial_mode) {
    if (partial_mode) { bsp_display_flush_partial(); } 
	else              { bsp_display_flush();         }
    return ESP_OK;
}

void bsp_display_deep_sleep(void) {
	// Display not 'ON'
	if(display_power_enable(true) != true) return;
	// Display SPI not initialized
    if (s_spi_handle == NULL) return; // (in minimal hot-wake mode)
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);
    epd_send_cmd         (0x10);
    epd_send_data        (0x01);
}

void bsp_display_draw_pixel(uint16_t x, uint16_t y, bsp_display_color_t color) {
    if (x >= BSP_DISPLAY_WIDTH || y >= BSP_DISPLAY_HEIGHT || s_frame_buffer == NULL) return;
    uint32_t index = y * (BSP_DISPLAY_WIDTH / 8) + (x >> 3);
    uint8_t  bit   = 7 - (x & 0x07);

    if (color == BSP_DISPLAY_COLOR_WHITE) { s_frame_buffer[index] |=  (1 << bit); } // set bit (1)
	else                                  { s_frame_buffer[index] &= ~(1 << bit); } // clr bit (0)
}

uint8_t *bsp_display_get_buffer(void) {
    return s_frame_buffer;
}

esp_err_t bsp_display_read_temp(float *out_temp_c)
{
    if (out_temp_c == NULL) return ESP_ERR_INVALID_ARG;

    // Return quietly if display SPI is not initialized (e.g. during headless hot-wake mode)
    if (s_spi_handle == NULL || s_spi_read_handle == NULL) {
        *out_temp_c = 99.9f; return ESP_ERR_NOT_SUPPORTED;
    }

    // Check if display power rail is enabled (GPIO 6 is Active-LOW: 0=ON)
    if (gpio_get_level((gpio_num_t)BSP_PIN_EPD_3V3_EN) != 0) {
        *out_temp_c = 99.9f; return ESP_ERR_INVALID_STATE;
    }

    // 1. Assert CS# continuously across entire Command + Data Read phases (SSD1681 4-wire SPI protocol)
    epd_set_cs(0);

    // 2. Command Phase: D/C# = 0 (Command 0x1B: Read Temperature Sensor)
    epd_set_dc   (0);
    epd_send_byte(0x1B);

    // 3. Data Read Phase: D/C# = 1 (Hardware SPI half-duplex read of 2 bytes on SDA)
    epd_set_dc(1);
    spi_transaction_t t = {};
    t.flags             = SPI_TRANS_USE_RXDATA;
    t.rxlength          = 16; // 2 bytes = 16 bits
    esp_err_t ret       = spi_device_polling_transmit(s_spi_read_handle, &t);

    // 4. De-assert CS#
    epd_set_cs(1);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Hardware SPI read temperature failed: %s", esp_err_to_name(ret));
        return ret;
    }

    uint8_t raw_bytes[2] = {t.rx_data[0], t.rx_data[1]};

    // Convert raw reading: Signed 8-bit integer + fractional 0.5°C
    int8_t temp_int   = (int8_t)raw_bytes[0];
    float  temp_frac  = (raw_bytes[1] & 0x80) ? 0.5f : 0.0f;
    float  glass_temp = (float)temp_int + ((temp_int >= 0) ? temp_frac : -temp_frac);

    // Sanity range check for physical glass panel (-40°C to +85°C)
    if (glass_temp < -40.0f || glass_temp > 85.0f || raw_bytes[0] == 0xFF || raw_bytes[0] == 0x00) {
        // Fallback default if panel is uncalibrated / sleep
        *out_temp_c = 99.9f;
        return ESP_ERR_INVALID_RESPONSE;
    }

    *out_temp_c = glass_temp;
    ESP_LOGD(TAG, "SSD1681 On-Glass Temp Read (Hardware SPI): %.1f °C (0x%02X 0x%02X)", glass_temp, raw_bytes[0], raw_bytes[1]);
    return ESP_OK;
}

uint32_t bsp_display_get_partial_count(void) {
    return s_partial_refresh_count;
}

bool bsp_display_is_busy(void) {
    return (gpio_get_level((gpio_num_t)BSP_PIN_EPD_BUSY) == 1);
}

