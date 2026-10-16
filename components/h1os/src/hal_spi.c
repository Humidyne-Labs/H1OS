/**
 * @file hal_spi.c
 * @brief Layer 1 HAL SPI Master Bus Driver Implementation
 * 
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_spi.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "HAL_SPI";

static spi_device_handle_t s_spi_dev      = NULL;
static spi_device_handle_t s_spi_read_dev = NULL;

static bool s_is_inited = false;

static inline void epd_set_cs(uint8_t level) {
    gpio_set_level(HAL_PIN_EPD_CS, level);
}

static inline void epd_set_dc(uint8_t level) {
    gpio_set_level(HAL_PIN_EPD_DC, level);
}

esp_err_t hal_spi_init(void)
{
    if (s_is_inited) {
        return ESP_OK;
    }

    // 1. Configure DC, RST, and CS GPIO pins as manual outputs
    gpio_config_t epd_ctrl_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_DC) | (1ULL << HAL_PIN_EPD_RST) | (1ULL << HAL_PIN_EPD_CS),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&epd_ctrl_cfg);
    gpio_set_level(HAL_PIN_EPD_RST, 1);
    gpio_set_level(HAL_PIN_EPD_DC, 1);
    gpio_set_level(HAL_PIN_EPD_CS, 1);

    // 2. Configure BUSY GPIO pin as input
    gpio_config_t busy_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&busy_cfg);

    // 3. Initialize SPI Master Bus
    spi_bus_config_t buscfg = {
        .mosi_io_num     = HAL_PIN_EPD_MOSI,
        .miso_io_num     = -1,
        .sclk_io_num     = HAL_PIN_EPD_SCK,
        .quadwp_io_num   = -1,
        .quadhd_io_num   = -1,
        .max_transfer_sz = HAL_EPD_FRAME_SIZE_BYTES + 8,
    };

    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "spi_bus_initialize failed: %d", ret);
        return ret;
    }

    // 4. Fast Transmit Device (20 MHz, Mode 0)
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 20 * 1000 * 1000, // 20 MHz write speed
        .mode           = 0,                // CPOL=0, CPHA=0
        .spics_io_num   = -1,               // Manual CS
        .queue_size     = 7,
    };

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &s_spi_dev);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "spi_bus_add_device failed: %d", ret);
        spi_bus_free(SPI2_HOST);
        return ret;
    }

    // 5. Half-Duplex 3-Wire Read Device (2 MHz, Mode 0) for on-glass temp readout
    spi_device_interface_config_t rdevcfg = {
        .clock_speed_hz = 2 * 1000 * 1000,  // 2 MHz read speed
        .mode           = 0,
        .spics_io_num   = -1,               // Manual CS
        .flags          = SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_3WIRE,
        .queue_size     = 1,
    };

    ret = spi_bus_add_device(SPI2_HOST, &rdevcfg, &s_spi_read_dev);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "spi_bus_add_device (read) failed: %d", ret);
    }

    s_is_inited = true;
    ESP_LOGD(TAG, "SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, SCK=%d, MOSI=%d",
             HAL_PIN_EPD_CS, HAL_PIN_EPD_SCK, HAL_PIN_EPD_MOSI);
    return ESP_OK;
}

esp_err_t hal_spi_deinit(void)
{
    if (!s_is_inited) {
        return ESP_OK;
    }

    if (s_spi_read_dev) {
        spi_bus_remove_device(s_spi_read_dev);
        s_spi_read_dev = NULL;
    }

    if (s_spi_dev) {
        spi_bus_remove_device(s_spi_dev);
        s_spi_dev = NULL;
    }

    spi_bus_free(SPI2_HOST);
    s_is_inited = false;
    return ESP_OK;
}

esp_err_t hal_spi_write_cmd(uint8_t cmd)
{
    if (!s_is_inited || !s_spi_dev) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(0); // DC = 0 for command
    epd_set_cs(0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.flags = SPI_TRANS_USE_TXDATA;
    t.length = 8;
    t.tx_data[0] = cmd;

    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t);
    epd_set_cs(1);
    return ret;
}

esp_err_t hal_spi_write_data(const uint8_t *data, size_t len)
{
    if (!s_is_inited || !s_spi_dev || !data || len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(1); // DC = 1 for data
    epd_set_cs(0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = len * 8;
    t.tx_buffer = data;

    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t);
    epd_set_cs(1);
    return ret;
}

esp_err_t hal_spi_write_frame_dma(const uint8_t *frame_buffer)
{
    if (!s_is_inited || !s_spi_dev || !frame_buffer) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(1); // DC = 1 for data
    epd_set_cs(0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = HAL_EPD_FRAME_SIZE_BYTES * 8;
    t.tx_buffer = frame_buffer;

    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t);
    epd_set_cs(1);
    return ret;
}

esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t *out_data, size_t len)
{
    if (!s_is_inited || !s_spi_dev || !s_spi_read_dev || !out_data || len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    // 1. Assert CS# continuously across entire Command + Data Read phases
    epd_set_cs(0);

    // 2. Command Phase: D/C# = 0
    epd_set_dc(0);
    spi_transaction_t t_cmd;
    memset(&t_cmd, 0, sizeof(t_cmd));
	
    t_cmd.flags      = SPI_TRANS_USE_TXDATA;
    t_cmd.length     = 8;
    t_cmd.tx_data[0] = cmd;
	
    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t_cmd);
    if (ret != ESP_OK) {
        epd_set_cs(1);
        return ret;
    }

    // 3. Data Read Phase: D/C# = 1 (Hardware SPI half-duplex 3-wire read on SDA)
    // Hold CD line firmly HIGH before and during read data phase
    epd_set_dc(1);
    esp_rom_delay_us(5);
    spi_transaction_t t_read;
    memset(&t_read, 0, sizeof(t_read));
	
    t_read.flags    = SPI_TRANS_USE_RXDATA;
    t_read.rxlength = len * 8;
	
    ret = spi_device_polling_transmit(s_spi_read_dev, &t_read);

    // 4. De-assert CS#
    epd_set_cs(1);

    if (ret == ESP_OK) {
        memcpy(out_data, t_read.rx_data, len);
    }
    return ret;
}
