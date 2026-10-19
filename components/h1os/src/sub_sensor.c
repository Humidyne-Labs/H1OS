/**
 * @file sub_sensor.c
 * @brief Layer 2: Sensirion SHTC3 & ESP32-S3 Internal TSENS Implementation
 *
 * Implements pristine physical sensor transactions over hal_i2c and esp_driver_tsens.
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_sensor.h"

#include "driver/temperature_sensor.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"

static const char *TAG = "sub_sensor";

/* SHTC3 16-bit Commands */
#define SHTC3_CMD_WAKEUP 0x3517
#define SHTC3_CMD_SLEEP 0xB098
#define SHTC3_CMD_MEAS_NORMAL_T_FIRST 0x7866
#define SHTC3_CMD_MEAS_LOWPWR_T_FIRST 0x609C

static temperature_sensor_handle_t s_tsens_handle = NULL;

static bool s_tsens_inited = false;

/* Sensirion standard CRC-8 polynomial (x^8 + x^5 + x^4 + 1, init 0xFF) */
static uint8_t shtc3_calc_crc(const uint8_t *data, size_t len)
{
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

esp_err_t sub_sensor_init(void)
{
    if (s_tsens_inited && s_tsens_handle != NULL) {
        return ESP_OK;
    }

    temperature_sensor_config_t tsens_cfg = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    esp_err_t                   ret       = temperature_sensor_install(&tsens_cfg, &s_tsens_handle);
    if (ret == ESP_OK) {
        ret = temperature_sensor_enable(s_tsens_handle);
        if (ret == ESP_OK) {
            s_tsens_inited = true;
            return ESP_OK;
        }
        temperature_sensor_uninstall(s_tsens_handle);
        s_tsens_handle = NULL;
    }
    ESP_LOGW(TAG, "TSENS install/enable returned %s", esp_err_to_name(ret));
    return ret;
}

esp_err_t sub_sensor_deinit(void)
{
    if (s_tsens_inited && s_tsens_handle != NULL) {
        temperature_sensor_disable(s_tsens_handle);
        temperature_sensor_uninstall(s_tsens_handle);
        s_tsens_handle = NULL;
        s_tsens_inited = false;
    }
    return ESP_OK;
}

esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power)
{
    if (out_raw_temp == NULL || out_raw_rh == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* 1. Wakeup SHTC3 */
    uint8_t   wake_cmd[2] = {(uint8_t)(SHTC3_CMD_WAKEUP >> 8), (uint8_t)(SHTC3_CMD_WAKEUP & 0xFF)};
    esp_err_t err =
        hal_i2c_write(HAL_I2C_ADDR_SHTC3, wake_cmd, sizeof(wake_cmd), pdMS_TO_TICKS(50));
    if (err != ESP_OK) {
        return err;
    }
    esp_rom_delay_us(250);

    /* 2. Send Measurement Command (T-first) */
    uint16_t cmd = low_power ? SHTC3_CMD_MEAS_LOWPWR_T_FIRST : SHTC3_CMD_MEAS_NORMAL_T_FIRST;
    uint8_t  meas_cmd[2] = {(uint8_t)(cmd >> 8), (uint8_t)(cmd & 0xFF)};
    err = hal_i2c_write(HAL_I2C_ADDR_SHTC3, meas_cmd, sizeof(meas_cmd), pdMS_TO_TICKS(50));
    if (err != ESP_OK) {
        /* Put sensor back to sleep if command failed */
        uint8_t sleep_cmd[2] = {(uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF)};
        hal_i2c_write(HAL_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd), pdMS_TO_TICKS(20));
        return err;
    }

    /* 3. Conversion Delay */
    if (low_power) {
        esp_rom_delay_us(1000);
    } else {
        if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
            vTaskDelay(pdMS_TO_TICKS(15) + 1);
        } else {
            esp_rom_delay_us(15000);
        }
    }

    /* 4. Read 6-Byte Payload: [T_MSB, T_LSB, T_CRC, RH_MSB, RH_LSB, RH_CRC] */
    uint8_t rx_buf[6] = {0};
    err               = hal_i2c_read(HAL_I2C_ADDR_SHTC3, rx_buf, sizeof(rx_buf), pdMS_TO_TICKS(50));

    /* 5. Sleep SHTC3 immediately to eliminate sensor self-heating */
    uint8_t sleep_cmd[2] = {(uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF)};
    hal_i2c_write(HAL_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd), pdMS_TO_TICKS(20));

    if (err != ESP_OK) {
        return err;
    }

    /* 6. Verify Sensirion CRC-8 checksums */
    if (shtc3_calc_crc(&rx_buf[0], 2) != rx_buf[2] || shtc3_calc_crc(&rx_buf[3], 2) != rx_buf[5]) {
        ESP_LOGE(TAG, "SHTC3 CRC check failed: [T: 0x%02x != 0x%02x, RH: 0x%02x != 0x%02x]",
                 rx_buf[2], shtc3_calc_crc(&rx_buf[0], 2), rx_buf[5],
                 shtc3_calc_crc(&rx_buf[3], 2));
        return ESP_ERR_INVALID_CRC;
    }

    *out_raw_temp = ((uint16_t)rx_buf[0] << 8) | rx_buf[1];
    *out_raw_rh   = ((uint16_t)rx_buf[3] << 8) | rx_buf[4];
    return ESP_OK;
}

void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float *out_temp_c,
                                    float *out_rh_pct)
{
    if (out_temp_c != NULL) {
        /* T [°C] = -45 + 175 * (raw_temp / 2^16) */
        *out_temp_c = -45.0f + 175.0f * ((float)raw_temp / 65536.0f);
    }
    if (out_rh_pct != NULL) {
        /* RH [%] = 100 * (raw_rh / 2^16) */
        float rh = 100.0f * ((float)raw_rh / 65536.0f);
        if (rh < 0.0f)
            rh = 0.0f;
        if (rh > 100.0f)
            rh = 100.0f;
        *out_rh_pct = rh;
    }
}

esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c)
{
    if (out_die_temp_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!s_tsens_inited || s_tsens_handle == NULL) {
        esp_err_t err = sub_sensor_init();
        if (err != ESP_OK) {
            *out_die_temp_c = 0.0f; /* 0.0 C indicates sensor uninitialized / NA */
            return err;
        }
    }

    esp_err_t ret = temperature_sensor_get_celsius(s_tsens_handle, out_die_temp_c);
    if (ret != ESP_OK) {
        *out_die_temp_c = 0.0f; /* 0.0 C indicates sensor uninitialized / NA */
    }
    return ret;
}
