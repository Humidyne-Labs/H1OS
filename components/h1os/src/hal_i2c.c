/**
 * @file hal_i2c.c
 * @brief Layer 1: Shared I2C master bus driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_i2c.h"

#include "driver/i2c_master.h"
#include "esp_log.h"

static const char *TAG = "HAL_I2C";

static i2c_master_bus_handle_t s_bus_handle = NULL;
static StaticSemaphore_t s_i2c_mutex_buf;
static SemaphoreHandle_t s_i2c_mutex        = NULL;
static bool s_is_inited                     = false;

static i2c_master_dev_handle_t s_dev_es8311   = NULL;
static i2c_master_dev_handle_t s_dev_pcf85063 = NULL;
static i2c_master_dev_handle_t s_dev_shtc3    = NULL;

/**
 * @brief Retrieve or lazily register a cached I2C device handle for known onboard peripherals.
 */
static esp_err_t hal_i2c_acquire_dev_handle(uint8_t dev_addr, i2c_master_dev_handle_t *out_handle, bool *out_is_temp)
{
    *out_is_temp = false;
    i2c_master_dev_handle_t *slot = NULL;

    if (dev_addr == HAL_I2C_ADDR_ES8311) {
        slot = &s_dev_es8311;
    } else if (dev_addr == HAL_I2C_ADDR_PCF85063) {
        slot = &s_dev_pcf85063;
    } else if (dev_addr == HAL_I2C_ADDR_SHTC3) {
        slot = &s_dev_shtc3;
    }

    if (slot != NULL && *slot != NULL) {
        *out_handle = *slot;
        return ESP_OK;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = dev_addr,
        .scl_speed_hz    = HAL_I2C_FREQ_HZ,
    };

    i2c_master_dev_handle_t handle = NULL;
    esp_err_t ret = i2c_master_bus_add_device(s_bus_handle, &dev_cfg, &handle);
    if (ret != ESP_OK) {
        return ret;
    }

    if (slot != NULL) {
        *slot = handle;
    } else {
        *out_is_temp = true;
    }
    *out_handle = handle;
    return ESP_OK;
}

/**
 * @brief Initializes the shared I2C master bus hardware.
 *
 * @details Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates static recursive mutex.
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_i2c_init(void)
{
    if (s_is_inited) {
        return ESP_OK;
    }

    if (!s_i2c_mutex) {
        s_i2c_mutex = xSemaphoreCreateRecursiveMutexStatic(&s_i2c_mutex_buf);
        if (!s_i2c_mutex) {
            ESP_LOGE(TAG, "Failed to create I2C recursive mutex");
            return ESP_ERR_NO_MEM;
        }
    }

    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = HAL_PIN_I2C_SDA,
        .scl_io_num = HAL_PIN_I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .intr_priority = 0,
        .trans_queue_depth = 0,
        .flags =
            {
                .enable_internal_pullup = 0,
            },
    };

    esp_err_t ret = i2c_new_master_bus(&bus_config, &s_bus_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "i2c_new_master_bus failed on GPIO %d/%d: %d", HAL_PIN_I2C_SDA, HAL_PIN_I2C_SCL, ret);
        return ret;
    }

    s_is_inited = true;
    ESP_LOGD(TAG, "I2C master bus initialized on GPIO 47/48 @ 400kHz");
    return ESP_OK;
}

/**
 * @brief Deinitializes the shared I2C master bus and releases mutex.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_i2c_deinit(void)
{
    if (!s_is_inited) {
        return ESP_OK;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
        if (s_dev_es8311) {
            i2c_master_bus_rm_device(s_dev_es8311);
            s_dev_es8311 = NULL;
        }
        if (s_dev_pcf85063) {
            i2c_master_bus_rm_device(s_dev_pcf85063);
            s_dev_pcf85063 = NULL;
        }
        if (s_dev_shtc3) {
            i2c_master_bus_rm_device(s_dev_shtc3);
            s_dev_shtc3 = NULL;
        }
        if (s_bus_handle) {
            i2c_del_master_bus(s_bus_handle);
            s_bus_handle = NULL;
        }
        s_is_inited = false;
        xSemaphoreGiveRecursive(s_i2c_mutex);
        return ESP_OK;
    }

    return ESP_ERR_TIMEOUT;
}

/**
 * @brief Executes an atomic register write transaction over I2C.
 *
 * @param[in]    dev_addr        7-bit I2C device address.
 * @param[in]    write_data      Pointer to data buffer to transmit.
 * @param[in]    write_len       Length of write buffer in bytes.
 * @param[in]    timeout_ms      Timeout budget in milliseconds.
 *
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms)
{
    if (!s_is_inited) {
        esp_err_t init_ret = hal_i2c_init();
        if (init_ret != ESP_OK) {
            return init_ret;
        }
    }

    if (!s_bus_handle || !write_data || write_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_master_dev_handle_t dev_handle = NULL;
    bool is_temp = false;
    esp_err_t ret = hal_i2c_acquire_dev_handle(dev_addr, &dev_handle, &is_temp);
    if (ret == ESP_OK) {
        ret = i2c_master_transmit(dev_handle, write_data, write_len, timeout_ms);
        if (is_temp) {
            i2c_master_bus_rm_device(dev_handle);
        }
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

/**
 * @brief Executes an atomic register read transaction over I2C.
 *
 * @param[in]    dev_addr        7-bit I2C device address.
 * @param[in]    read_data       Pointer to buffer to receive data.
 * @param[in]    read_len        Number of bytes to read.
 * @param[in]    timeout_ms      Timeout budget in milliseconds.
 *
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms)
{
    if (!s_is_inited) {
        esp_err_t init_ret = hal_i2c_init();
        if (init_ret != ESP_OK) {
            return init_ret;
        }
    }

    if (!s_bus_handle || !read_data || read_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_master_dev_handle_t dev_handle = NULL;
    bool is_temp = false;
    esp_err_t ret = hal_i2c_acquire_dev_handle(dev_addr, &dev_handle, &is_temp);
    if (ret == ESP_OK) {
        ret = i2c_master_receive(dev_handle, read_data, read_len, timeout_ms);
        if (is_temp) {
            i2c_master_bus_rm_device(dev_handle);
        }
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

/**
 * @brief Executes an atomic write-then-read combined transaction (Repeated START).
 *
 * @param[in]    dev_addr        7-bit I2C device address.
 * @param[in]    write_data      Register address or command bytes to write.
 * @param[in]    write_len       Number of bytes to write.
 * @param[in]    read_data       Destination buffer for read bytes.
 * @param[in]    read_len        Number of bytes to read.
 * @param[in]    timeout_ms      Timeout budget in milliseconds.
 *
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint8_t *read_data,
                             size_t read_len, uint32_t timeout_ms)
{
    if (!s_is_inited) {
        esp_err_t init_ret = hal_i2c_init();
        if (init_ret != ESP_OK) {
            return init_ret;
        }
    }

    if (!s_bus_handle || !write_data || write_len == 0 || !read_data || read_len == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_master_dev_handle_t dev_handle = NULL;
    bool is_temp = false;
    esp_err_t ret = hal_i2c_acquire_dev_handle(dev_addr, &dev_handle, &is_temp);
    if (ret == ESP_OK) {
        ret = i2c_master_transmit_receive(dev_handle, write_data, write_len, read_data, read_len, timeout_ms);
        if (is_temp) {
            i2c_master_bus_rm_device(dev_handle);
        }
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

/**
 * @brief Probes if an I2C device with given 7-bit address responds on the bus.
 *
 * @param[in]    dev_addr        7-bit device address.
 *
 * @return ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.
 */
esp_err_t hal_i2c_probe(uint8_t dev_addr)
{
    if (!s_is_inited) {
        esp_err_t init_ret = hal_i2c_init();
        if (init_ret != ESP_OK) {
            return init_ret;
        }
    }

    if (!s_bus_handle) {
        return ESP_ERR_INVALID_STATE;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(50)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    esp_err_t ret = i2c_master_probe(s_bus_handle, dev_addr, 50);

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}
