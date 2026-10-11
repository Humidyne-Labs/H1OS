/**
 * @file bsp_sensors.c
 * @brief Sensirion SHTC3 Class-E Environmental Hygrometer & Thermal Gating Engine Implementation
 *
 * @version 1.3.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Peripheral Driver Basis: Waveshare Electronics SHTC3 Sensor Code & Datasheet
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temperature_sensor.h"
#include "bsp/bsp_i2c.h"
#include "bsp/bsp_display.h"
#include "bsp/bsp_sensors.h"
#include "bsp/bsp_power.h"
#include "bsp/bsp_equ_math.h"
#include "bsp/bsp_rtc_mem.h"
#include "bsp/bsp_env_telemetry.h"

static const char *TAG = "bsp_sensors";

#define SHTC3_AMBIENT_DRIFT_CONSTANT      2.5f

// SHTC3 16-bit Command Words
#define SHTC3_CMD_WAKEUP                  0x3517
#define SHTC3_CMD_SLEEP                   0xB098
#define SHTC3_CMD_SWRST                   0x805D
#define SHTC3_CMD_READ_ID                 0xEFC8
#define SHTC3_CMD_MEAS_NORMAL_T_FIRST     0x7866
#define SHTC3_CMD_MEAS_LOWPWR_T_FIRST     0x609C

#define THERMAL_LOCKOUT_DEFAULT_US        (30ULL * 1000000ULL) /* 30 seconds post-wake cooldown */

// Sliding Window & Invariant Engine State
typedef struct {
    float            ewma_temp;
    float            ewma_rh;
    bool             ewma_inited;
    int64_t          wake_timestamp_us;
    bsp_shtc3_data_t cached_cold_reading;
    bool             cached_valid;
    uint16_t         latest_raw_temp_u16;
    uint16_t         latest_raw_rh_u16;
    bool             has_raw_sample;
    bool             sub_exec_armed;
    uint32_t         sub_exec_interval_sec;
} psychrometric_state_t;

RTC_DATA_ATTR static psychrometric_state_t s_psy_state = {
    .sub_exec_armed        = false,
    .sub_exec_interval_sec = 60,
};

// TSENS Hardware Driver Handle
static temperature_sensor_handle_t s_tsens_handle = NULL;
static bool                        s_tsens_inited = false;

// Persistent Environmental Telemetry History in RTC Slow Memory (288 Bytes)
RTC_DATA_ATTR static bsp_env_telemetry_history_t s_env_history = {
    .magic                      = BSP_ENV_TELEMETRY_MAGIC,
    .ctrl_flags                 = BSP_ENV_FLAG_IDLE,
    .head_index                 = 0,
    .total_samples              = 0,
    .last_sample_timestamp_sec  = 0,
    .window_clean_mask          = 0ULL,
};

/* =========================================================================
 * Persistent Telemetry State & Sample History APIs
 * ========================================================================= */
const bsp_env_telemetry_history_t *bsp_sensors_get_telemetry_history(void) {
    return &s_env_history;
}

uint32_t bsp_sensors_get_sample_count(void) {
    return s_env_history.total_samples;
}

/* =========================================================================
 * Sensirion CRC-8 Polynomial Calculation
 * ========================================================================= */
static uint8_t shtc3_crc8(const uint8_t *data, size_t len)
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

/* =========================================================================
 * Internal TSENS Driver Management
 * ========================================================================= */
esp_err_t init_tsens_driver(void) {
    if (s_tsens_inited && s_tsens_handle != NULL) return ESP_OK;

    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    esp_err_t ret = temperature_sensor_install(&temp_sensor_config, &s_tsens_handle);
    if (ret == ESP_OK) {
        ret = temperature_sensor_enable(s_tsens_handle);
        if (ret == ESP_OK) {
            s_tsens_inited = true;
            ESP_LOGI(TAG, "Internal TSENS Die Temperature Sensor enabled");
            return ESP_OK;
        }
    }
    ESP_LOGW(TAG, "Failed to initialize TSENS driver: %s", esp_err_to_name(ret));
    return ret;
}

esp_err_t bsp_mcu_die_temp_read(float *out_temp_c) {
    if (out_temp_c == NULL) return ESP_ERR_INVALID_ARG;
    if (!s_tsens_inited || s_tsens_handle == NULL) {
        esp_err_t err = init_tsens_driver();
        if (err != ESP_OK) {
            *out_temp_c = 25.0f;
            return err;
        }
    }
    return temperature_sensor_get_celsius(s_tsens_handle, out_temp_c);
}

/* =========================================================================
 * Direct Physical SHTC3 Hardware Routine (Wake -> Read -> Sleep)
 * ========================================================================= */
esp_err_t bsp_shtc3_read_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power)
{
    if (out_raw_temp == NULL || out_raw_rh == NULL) return ESP_ERR_INVALID_ARG;

    // 1. Wake SHTC3
    uint8_t wake_cmd[2] = { (uint8_t)(SHTC3_CMD_WAKEUP >> 8), (uint8_t)(SHTC3_CMD_WAKEUP & 0xFF) };
    esp_err_t err = bsp_i2c_write(BSP_I2C_ADDR_SHTC3, wake_cmd, sizeof(wake_cmd));
    if (err != ESP_OK) return err;
    esp_rom_delay_us(250);

    // 2. Send Measurement Command (Normal 0x7866 or Low-Power 0x609C)
    uint16_t cmd = low_power ? SHTC3_CMD_MEAS_LOWPWR_T_FIRST : SHTC3_CMD_MEAS_NORMAL_T_FIRST;
    uint8_t meas_cmd[2] = { (uint8_t)(cmd >> 8), (uint8_t)(cmd & 0xFF) };
    err = bsp_i2c_write(BSP_I2C_ADDR_SHTC3, meas_cmd, sizeof(meas_cmd));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send measurement command 0x%04X: %s", cmd, esp_err_to_name(err));
        // Sleep SHTC3 before returning
        uint8_t sleep_cmd[2] = { (uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF) };
        bsp_i2c_write(BSP_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd));
        return err;
    }

    // 3. Conversion Delay (15ms for Normal NIST, 1000µs for Low-Power)
    if (low_power) {
        esp_rom_delay_us(1000);
    } else {
        vTaskDelay(pdMS_TO_TICKS(15) + 1);
    }

    // 4. Read 6-Byte Payload
    uint8_t rx_buf[6] = {0};
    err = bsp_i2c_read(BSP_I2C_ADDR_SHTC3, rx_buf, sizeof(rx_buf));

    // 5. Sleep SHTC3 immediately to eliminate sensor self-heating
    uint8_t sleep_cmd[2] = { (uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF) };
    bsp_i2c_write(BSP_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd));

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read SHTC3 data: %s", esp_err_to_name(err));
        return err;
    }

    // 6. CRC-8 Validation
    if (shtc3_crc8(&rx_buf[0], 2) != rx_buf[2] || shtc3_crc8(&rx_buf[3], 2) != rx_buf[5]) {
        ESP_LOGE(TAG, "SHTC3 CRC check failed");
        return ESP_ERR_INVALID_CRC;
    }

    // 7. Output Raw 16-Bit Integer Words
    *out_raw_temp = ((uint16_t)rx_buf[0] << 8) | rx_buf[1];
    *out_raw_rh   = ((uint16_t)rx_buf[3] << 8) | rx_buf[4];
    return ESP_OK;
}

/* =========================================================================
 * Public Sensor Lifecycle & Initializer APIs
 * ========================================================================= */
esp_err_t bsp_shtc3_init(void) {
    ESP_LOGI(TAG, "Initializing SHTC3 Class-E Environmental Sensor Engine...");
    s_psy_state.wake_timestamp_us = esp_timer_get_time();

    // 1. Wake SHTC3
    uint8_t wake_cmd[2] = { (uint8_t)(SHTC3_CMD_WAKEUP >> 8), (uint8_t)(SHTC3_CMD_WAKEUP & 0xFF) };
    esp_err_t err = bsp_i2c_write(BSP_I2C_ADDR_SHTC3, wake_cmd, sizeof(wake_cmd));
    if (err != ESP_OK) return err;
    esp_rom_delay_us(250);

    // 2. Query Device ID
    uint8_t id_cmd[2] = { (uint8_t)(SHTC3_CMD_READ_ID >> 8), (uint8_t)(SHTC3_CMD_READ_ID & 0xFF) };
    err = bsp_i2c_write(BSP_I2C_ADDR_SHTC3, id_cmd, sizeof(id_cmd));
    if (err != ESP_OK) {
        uint8_t sleep_cmd[2] = { (uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF) };
        bsp_i2c_write(BSP_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd));
        return err;
    }

    uint8_t id_buf[3] = {0};
    err = bsp_i2c_read(BSP_I2C_ADDR_SHTC3, id_buf, sizeof(id_buf));
    uint8_t sleep_cmd[2] = { (uint8_t)(SHTC3_CMD_SLEEP >> 8), (uint8_t)(SHTC3_CMD_SLEEP & 0xFF) };
    bsp_i2c_write(BSP_I2C_ADDR_SHTC3, sleep_cmd, sizeof(sleep_cmd));

    if (err != ESP_OK) return err;

    if (shtc3_crc8(id_buf, 2) != id_buf[2]) {
        ESP_LOGE(TAG, "SHTC3 ID CRC failed");
        return ESP_ERR_INVALID_CRC;
    }

    uint16_t id_val = ((uint16_t)id_buf[0] << 8) | id_buf[1];
    ESP_LOGI(TAG, "SHTC3 Sensor Verified (Product ID: 0x%04X)", id_val);

    return ESP_OK;
}

bool bsp_sensors_is_in_thermal_lockout(void) {
    int64_t now = esp_timer_get_time();
    return ((now - s_psy_state.wake_timestamp_us) < (int64_t)THERMAL_LOCKOUT_DEFAULT_US);
}

esp_err_t bsp_sensors_get_ambient_floor(float *out_floor_c) {
    if (out_floor_c == NULL) return ESP_ERR_INVALID_ARG;
    bsp_sliding_window_metrics_t metrics;
    esp_err_t err = bsp_math_calc_sliding_window_metrics(&s_env_history, &metrics);
    if (err != ESP_OK) return err;
    *out_floor_c = metrics.temp_floor_c;
    return ESP_OK;
}

/* =========================================================================
 * Autonomous 60s Sub-Execution Sample & 1-Cycle Integer Gating Engine
 * ========================================================================= */
esp_err_t bsp_sensors_sample_raw(bool low_power) {
    uint16_t raw_t = 0, raw_rh = 0;
    esp_err_t err = bsp_shtc3_read_raw(&raw_t, &raw_rh, low_power);
    if (err != ESP_OK) {
        return err;
    }

    // Buffer raw values for subsequent expansion
    s_psy_state.latest_raw_temp_u16 = raw_t;
    s_psy_state.latest_raw_rh_u16   = raw_rh;
    s_psy_state.has_raw_sample      = true;

    // 1-Cycle Integer Differential Gate Evaluation against Preceding Slot
    uint32_t head_idx = s_env_history.head_index;
    uint32_t prev_idx = (head_idx + BSP_ENV_SAMPLE_RING_CAPACITY - 1) % BSP_ENV_SAMPLE_RING_CAPACITY;

    s_env_history.samples[head_idx].raw_temp_u16 = raw_t;
    s_env_history.samples[head_idx].raw_rh_u16   = raw_rh;

    if (s_env_history.total_samples == 0 || SHTC3_RAW_IS_SETTLED(raw_t, s_env_history.samples[prev_idx].raw_temp_u16)) {
        s_env_history.window_clean_mask |= (1ULL << head_idx); // Thermally settled clean bit set!
    } else {
        s_env_history.window_clean_mask &= ~(1ULL << head_idx); // Unsettled thermal slope
    }

    s_env_history.head_index                 = (head_idx + 1) % BSP_ENV_SAMPLE_RING_CAPACITY;
    s_env_history.total_samples++;
    s_env_history.last_sample_timestamp_sec  = (uint32_t)(esp_timer_get_time() / 1000000ULL);

    return ESP_OK;
}

bool bsp_sensors_has_clean_samples(void) {
    return (s_env_history.total_samples > 0 && s_env_history.window_clean_mask != 0);
}

/* =========================================================================
 * Mathematical Evaluation Engine: Ingestion + Psychrometrics + Filtering
 * ========================================================================= */
esp_err_t bsp_sensors_eval_samples(float die_temp_c, float glass_temp_c, bsp_shtc3_data_t *out_data)
{
    if (out_data == NULL) return ESP_ERR_INVALID_ARG;

    uint16_t raw_t = 0, raw_rh = 0;

    if (s_psy_state.has_raw_sample) {
        raw_t  = s_psy_state.latest_raw_temp_u16;
        raw_rh = s_psy_state.latest_raw_rh_u16;
    } else if (s_env_history.total_samples > 0) {
        // Use most recent sample from ring buffer
        uint32_t latest_slot = (s_env_history.head_index + BSP_ENV_SAMPLE_RING_CAPACITY - 1) % BSP_ENV_SAMPLE_RING_CAPACITY;
        raw_t  = s_env_history.samples[latest_slot].raw_temp_u16;
        raw_rh = s_env_history.samples[latest_slot].raw_rh_u16;
    } else {
        // Should be cought by bsp_sensors_has_clean_samples() check.
        ESP_LOGI(TAG, "No prior SHTC3 samples available"); 
        return ESP_OK; //return ESP_ERR_NOT_FOUND;
    }

    // 1. Physical SHTC3 Conversions
    float t_sens  = SHTC3_RAW_TO_TEMP_C(raw_t);
    float rh_sens = SHTC3_RAW_TO_RH_PCT(raw_rh);

    // 2. Ambient Reference Selection
    float t_amb = t_sens;
    
    // Compare ambient reference candidates: SHTC3 PCB substrate, EPD glass, and ESP32-S3 die temperature
    if((fabsf(t_amb - die_temp_c)   > SHTC3_AMBIENT_DRIFT_CONSTANT) || // t_sens != die_temp?
       (fabsf(t_amb - glass_temp_c) > SHTC3_AMBIENT_DRIFT_CONSTANT))   // t_sens != glass_temp?
    {
        // If ambient offset > ambient drift margin, use coolist board reading.
        // If the board is at ambient, all sensors should read about the same in C.
        t_amb = (die_temp_c < glass_temp_c) ? die_temp_c : glass_temp_c;    
    }

    // 3. Ambient Thermal Reconstruction (Magnus Invariant e Normalization)
    float rh_reconst = bsp_math_reconstruct_ambient_rh(t_sens, rh_sens, t_amb);

    // 4. Dual EWMA Smoothing Filter (alpha = 0.35)
    if (!s_psy_state.ewma_inited) {
        s_psy_state.ewma_temp   = t_amb;
        s_psy_state.ewma_rh     = rh_reconst;
        s_psy_state.ewma_inited = true;
    } else {
        bsp_math_apply_ewma(t_amb,      &s_psy_state.ewma_temp, 0.35f);
        bsp_math_apply_ewma(rh_reconst, &s_psy_state.ewma_rh,   0.35f);
    }

    // 5. Derive Psychrometric Invariant Table on Smoothed Data
    float vapor_p_hpa    = bsp_math_calc_vapor_pressure_hpa  (s_psy_state.ewma_temp, s_psy_state.ewma_rh);
    float dew_point_c    = bsp_math_calc_dew_point_c         (s_psy_state.ewma_temp, s_psy_state.ewma_rh);
    float abs_humidity_g = bsp_math_calc_absolute_humidity_g (vapor_p_hpa, s_psy_state.ewma_temp);
    uint8_t conf_score   = bsp_math_calc_confidence_score    (t_sens, t_amb);

    // 6. 64-Slot Sliding Window Dynamics Calculation
    bsp_sliding_window_metrics_t metrics = {0};
    bsp_math_calc_sliding_window_metrics(&s_env_history, &metrics);

    // 7. Populate Telemetry Struct
    out_data->temperature_c               = s_psy_state.ewma_temp;
    out_data->temperature_f               = C_TO_F(s_psy_state.ewma_temp);
    out_data->temperature_k               = C_TO_K(s_psy_state.ewma_temp);
    out_data->humidity_percent            = s_psy_state.ewma_rh;

    out_data->dew_point_c                 = dew_point_c;
    out_data->dew_point_f                 = C_TO_F(dew_point_c);
    out_data->dew_point_k                 = C_TO_K(dew_point_c);
    out_data->absolute_humidity_g         = abs_humidity_g;

    out_data->sliding_temp_avg_c          = metrics.temp_avg_c;
    out_data->sliding_temp_avg_f          = C_TO_F(metrics.temp_avg_c);
    out_data->sliding_temp_floor_c        = metrics.temp_floor_c;
    out_data->sliding_temp_floor_f        = C_TO_F(metrics.temp_floor_c);
    out_data->sliding_temp_ceiling_c      = metrics.temp_ceiling_c;
    out_data->sliding_temp_ceiling_f      = C_TO_F(metrics.temp_ceiling_c);
    out_data->sliding_rh_min_pct          = metrics.rh_min_pct;
    out_data->sliding_rh_max_pct          = metrics.rh_max_pct;
    out_data->sliding_trend_rate          = metrics.trend_rate_rh_per_hr;

    out_data->settled_sample_rate_per_hr  = metrics.settled_sample_rate_per_hr;
    out_data->raw_shtc3_temp_c            = t_sens;
    out_data->raw_shtc3_rh_pct            = rh_sens;
    out_data->mcu_die_temp_c              = die_temp_c;
    out_data->epd_glass_temp_c            = glass_temp_c;
    out_data->thermal_delta_c             = fabsf(t_sens - t_amb);
    out_data->confidence_pct              = conf_score;
    out_data->valid                       = true;

    uint32_t latest_slot                  = (s_env_history.head_index + BSP_ENV_SAMPLE_RING_CAPACITY - 1) % BSP_ENV_SAMPLE_RING_CAPACITY;
    out_data->gate_passed                 = (s_env_history.window_clean_mask & (1ULL << latest_slot)) != 0;
    out_data->is_clean_window             = metrics.is_clean_window;

    s_psy_state.cached_cold_reading       = *out_data;
    s_psy_state.cached_valid              = true;

    return ESP_OK;
}

esp_err_t bsp_sensors_arm_sub_execution(uint32_t interval_sec) {
    if (interval_sec == 0) return ESP_ERR_INVALID_ARG;
    s_psy_state.sub_exec_armed        = true;
    s_psy_state.sub_exec_interval_sec = interval_sec;
    ESP_LOGI(TAG, "Autonomous background sub-execution ARMED (Interval: %lu s)", (unsigned long)interval_sec);
    return ESP_OK;
}

esp_err_t bsp_sensors_disarm_sub_execution(void) {
    s_psy_state.sub_exec_armed = false;
    ESP_LOGI(TAG, "Autonomous background sub-execution DISARMED");
    return ESP_OK;
}

bool bsp_sensors_is_sub_execution_armed(void) {
    return s_psy_state.sub_exec_armed;
}

uint32_t bsp_sensors_get_sub_execution_interval(void) {
    return (s_psy_state.sub_exec_interval_sec > 0) ? s_psy_state.sub_exec_interval_sec : 60;
}
