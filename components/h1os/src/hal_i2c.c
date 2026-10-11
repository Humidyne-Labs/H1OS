/**
 * @file hal_i2c.c
 * @brief Layer 1 HAL Shared I2C Master Bus Driver Implementation
 * 
 * SPDX-License-Identifier: MIT
 */

#include "h1os/hal_i2c.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

static const char *TAG = "HAL_I2C";

static i2c_master_bus_handle_t s_bus_handle = NULL;
static SemaphoreHandle_t s_i2c_mutex = NULL;
static bool s_is_inited = false;

esp_err_t hal_i2c_init(void)
{
    if (s_is_inited) {
        return ESP_OK;
    }

    if (!s_i2c_mutex) {
        s_i2c_mutex = xSemaphoreCreateRecursiveMutex();
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
        .flags = {
            .enable_internal_pullup = 0, // External 4.7k pullups present on PCB
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

esp_err_t hal_i2c_deinit(void)
{
    if (!s_is_inited) {
        return ESP_OK;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(100)) == pdTRUE) {
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

esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms)
{
    if (!s_is_inited || !s_bus_handle || !write_data || write_len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = dev_addr,
        .scl_speed_hz = HAL_I2C_FREQ_HZ,
    };

    i2c_master_dev_handle_t dev_handle = NULL;
    esp_err_t ret = i2c_master_bus_add_device(s_bus_handle, &dev_cfg, &dev_handle);
    if (ret == ESP_OK) {
        ret = i2c_master_transmit(dev_handle, write_data, write_len, timeout_ms);
        i2c_master_bus_rm_device(dev_handle);
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms)
{
    if (!s_is_inited || !s_bus_handle || !read_data || read_len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = dev_addr,
        .scl_speed_hz = HAL_I2C_FREQ_HZ,
    };

    i2c_master_dev_handle_t dev_handle = NULL;
    esp_err_t ret = i2c_master_bus_add_device(s_bus_handle, &dev_cfg, &dev_handle);
    if (ret == ESP_OK) {
        ret = i2c_master_receive(dev_handle, read_data, read_len, timeout_ms);
        i2c_master_bus_rm_device(dev_handle);
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

esp_err_t hal_i2c_write_read(uint8_t dev_addr,
                             const uint8_t *write_data, size_t write_len,
                             uint8_t *read_data, size_t read_len,
                             uint32_t timeout_ms)
{
    if (!s_is_inited || !s_bus_handle || !write_data || write_len == 0 || !read_data || read_len == 0) {
        return ESP_ERR_INVALID_STATE;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = dev_addr,
        .scl_speed_hz = HAL_I2C_FREQ_HZ,
    };

    i2c_master_dev_handle_t dev_handle = NULL;
    esp_err_t ret = i2c_master_bus_add_device(s_bus_handle, &dev_cfg, &dev_handle);
    if (ret == ESP_OK) {
        ret = i2c_master_transmit_receive(dev_handle, write_data, write_len, read_data, read_len, timeout_ms);
        i2c_master_bus_rm_device(dev_handle);
    }

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

esp_err_t hal_i2c_probe(uint8_t dev_addr)
{
    if (!s_is_inited || !s_bus_handle) {
        return ESP_ERR_INVALID_STATE;
    }

    if (xSemaphoreTakeRecursive(s_i2c_mutex, pdMS_TO_TICKS(50)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    esp_err_t ret = i2c_master_probe(s_bus_handle, dev_addr, 50);

    xSemaphoreGiveRecursive(s_i2c_mutex);
    return ret;
}

