/**
 * @file hal_spi.c
 * @brief Layer 1: SPI master bus driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_spi.h"

#include "esp_log.h"
#include "esp_rom_sys.h"

#include <string.h>

static const char *TAG = "HAL_SPI";

static spi_device_handle_t s_spi_dev      = NULL;
static spi_device_handle_t s_spi_read_dev = NULL;

static bool s_is_inited = false;

/**
 * @brief Epd set cs.
 *
 * @param[in]    level           Parameter level.
 *
 * @return Return value of type static inline void.
 */
static inline void epd_set_cs(uint8_t level)
{
    gpio_set_level(HAL_PIN_EPD_CS, level);
}

/**
 * @brief Epd set dc.
 *
 * @param[in]    level           Parameter level.
 *
 * @return Return value of type static inline void.
 */
static inline void epd_set_dc(uint8_t level)
{
    gpio_set_level(HAL_PIN_EPD_DC, level);
}

/**
 * @brief Initializes SPI2 Master host with DMA channel enabled for display communication.
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_spi_init(void)
{
    if (s_is_inited) {
        return ESP_OK;
    }

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

    gpio_config_t busy_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&busy_cfg);

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

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 20 * 1000 * 1000,
        .mode           = 0,
        .spics_io_num   = -1,
        .queue_size     = 7,
    };

    ret = spi_bus_add_device(SPI2_HOST, &devcfg, &s_spi_dev);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "spi_bus_add_device failed: %d", ret);
        spi_bus_free(SPI2_HOST);
        return ret;
    }

    spi_device_interface_config_t rdevcfg = {
        .clock_speed_hz = 2 * 1000 * 1000,
        .mode           = 0,
        .spics_io_num   = -1,
        .flags          = SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_3WIRE,
        .queue_size     = 1,
    };

    ret = spi_bus_add_device(SPI2_HOST, &rdevcfg, &s_spi_read_dev);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "spi_bus_add_device (read) failed: %d", ret);
    }

    s_is_inited = true;
    ESP_LOGD(TAG,
             "SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "
             "SCK=%d, MOSI=%d",
             HAL_PIN_EPD_CS, HAL_PIN_EPD_SCK, HAL_PIN_EPD_MOSI);
    return ESP_OK;
}

/**
 * @brief Deinitializes SPI2 Master host and releases bus resources.
 *
 * @return ESP_OK on success.
 */
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

/**
 * @brief Transmits a single command byte to the SSD1681 controller (DC = 0).
 *
 * @param[in]    cmd             Command byte.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_cmd(uint8_t cmd)
{
    if (!s_is_inited || !s_spi_dev) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(0);
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

/**
 * @brief Transmits data bytes to the SSD1681 controller (DC = 1).
 *
 * @param[in]    data            Pointer to buffer containing payload.
 * @param[in]    len             Length of data in bytes.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_data(const uint8_t *data, size_t len)
{
    if (!s_is_inited || !s_spi_dev || !data || len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(1);
    epd_set_cs(0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = len * 8;
    t.tx_buffer = data;

    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t);
    epd_set_cs(1);
    return ret;
}

/**
 * @brief Transmits a full 5000-byte frame buffer via DMA transfer.
 *
 * @param[in]    frame_buffer    Pointer to 5000-byte buffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_frame_dma(const uint8_t *frame_buffer)
{
    if (!s_is_inited || !s_spi_dev || !frame_buffer) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_dc(1);
    epd_set_cs(0);

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = HAL_EPD_FRAME_SIZE_BYTES * 8;
    t.tx_buffer = frame_buffer;

    esp_err_t ret = spi_device_transmit(s_spi_dev, &t);
    epd_set_cs(1);
    return ret;
}

/**
 * @brief Reads data from SSD1681 (e.g.
 *
 * @details on-glass thermal sensor Cmd 0x1B).
 *
 * @param[in]    cmd             Command to write before reading.
 * @param[out]   out_data        Buffer to receive read bytes.
 * @param[in]    len             Number of bytes to read.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t *out_data, size_t len)
{
    if (!s_is_inited || !s_spi_dev || !s_spi_read_dev || !out_data || len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    epd_set_cs(0);

    epd_set_dc(0);
    spi_transaction_t t_cmd;
    memset(&t_cmd, 0, sizeof(t_cmd));

    t_cmd.flags = SPI_TRANS_USE_TXDATA;
    t_cmd.length = 8;
    t_cmd.tx_data[0] = cmd;

    esp_err_t ret = spi_device_polling_transmit(s_spi_dev, &t_cmd);
    if (ret != ESP_OK) {
        epd_set_cs(1);
        return ret;
    }

    epd_set_dc(1);
    esp_rom_delay_us(5);
    spi_transaction_t t_read;
    memset(&t_read, 0, sizeof(t_read));

    t_read.flags = SPI_TRANS_USE_RXDATA;
    t_read.rxlength = len * 8;

    ret = spi_device_polling_transmit(s_spi_read_dev, &t_read);

    epd_set_cs(1);

    if (ret == ESP_OK) {
        memcpy(out_data, t_read.rx_data, len);
    }
    return ret;
}
