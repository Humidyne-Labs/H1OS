/**
 * @file sub_rtc.c
 * @brief Layer 2: PCF85063A real-time clock driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_rtc.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"

#include <string.h>

static const char *TAG = "sub_rtc";

#define RTC_REG_CONTROL_1   0x00
#define RTC_REG_CONTROL_2   0x01
#define RTC_REG_OFFSET      0x02
#define RTC_REG_RAM_BYTE    0x03
#define RTC_REG_SECONDS     0x04
#define RTC_REG_MINUTES     0x05
#define RTC_REG_HOURS       0x06
#define RTC_REG_DAYS        0x07
#define RTC_REG_WEEKDAYS    0x08
#define RTC_REG_MONTHS      0x09
#define RTC_REG_YEARS       0x0A
#define RTC_REG_ALARM_SEC   0x0B
#define RTC_REG_TIMER_VALUE 0x10
#define RTC_REG_TIMER_MODE  0x11

#define CTRL1_STOP_MASK      (1 << 5)
#define CTRL1_12_24_MASK     (1 << 1)
#define CTRL1_CAP_SEL_12_5PF (1 << 0)
#define CTRL1_SW_RESET_CMD    0x58

#define CTRL2_AF_MASK  (1 << 6)
#define CTRL2_TF_MASK  (1 << 3)
#define CTRL2_AIE_MASK (1 << 7)
#define CTRL2_COF_OFF   0x07

#define TIMER_CLK_4096_HZ    (0 << 3)
#define TIMER_CLK_64_HZ      (1 << 3)
#define TIMER_CLK_1_HZ       (2 << 3)
#define TIMER_CLK_1_60_HZ    (3 << 3)
#define TIMER_ENABLE_BIT     (1 << 2)
#define TIMER_INT_ENABLE_BIT (1 << 1)
#define TIMER_PULSE_MODE_BIT (1 << 0)

/**
 * @brief Bcd2dec.
 *
 * @param[in]    val             Parameter val.
 *
 * @return Return value of type static inline uint8_t.
 */
static inline uint8_t bcd2dec(uint8_t val)
{
    return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));
}

/**
 * @brief Dec2bcd.
 *
 * @param[in]    val             Parameter val.
 *
 * @return Return value of type static inline uint8_t.
 */
static inline uint8_t dec2bcd(uint8_t val)
{
    return (uint8_t)(((val / 10) << 4) | (val % 10));
}

/**
 * @brief Pcf85063 read reg.
 *
 * @param[in]    reg             Parameter reg.
 * @param[in]    val             Parameter val.
 * @param[in]    len             Parameter len.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t pcf85063_read_reg(uint8_t reg, uint8_t *val, size_t len)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_PCF85063, &reg, 1, val, len, pdMS_TO_TICKS(50));
}

/**
 * @brief Pcf85063 write reg.
 *
 * @param[in]    reg             Parameter reg.
 * @param[in]    val             Parameter val.
 * @param[in]    len             Parameter len.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t pcf85063_write_reg(uint8_t reg, const uint8_t *val, size_t len)
{
    uint8_t buf[16];
    if (len + 1 > sizeof(buf)) {
        return ESP_ERR_INVALID_SIZE;
    }

    buf[0] = reg;
    memcpy(&buf[1], val, len);
    return hal_i2c_write(HAL_I2C_ADDR_PCF85063, buf, len + 1, pdMS_TO_TICKS(50));
}

/**
 * @brief Pcf85063 write reg u8.
 *
 * @param[in]    reg             Parameter reg.
 * @param[in]    val             Parameter val.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t pcf85063_write_reg_u8(uint8_t reg, uint8_t val)
{
    return pcf85063_write_reg(reg, &val, 1);
}

/**
 * @brief Initialize PCF85063A RTC.
 *
 * @details Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.
 *
 * @return ESP_OK on success, or an I2C communication error.
 */
esp_err_t sub_rtc_init(void)
{
    /* Probe Bus for Device */
    esp_err_t err0 = hal_i2c_probe(HAL_I2C_ADDR_PCF85063);
    if (err0 != ESP_OK) {
        ESP_LOGE(TAG, "Device Not Found: %s", esp_err_to_name(err0));
        return ESP_ERR_NOT_FOUND;
    }

    uint8_t ctrl1 = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_CONTROL_1, &ctrl1, 1);
    if (err == ESP_OK) {
        ctrl1 = (ctrl1 & ~CTRL1_STOP_MASK) | CTRL1_CAP_SEL_12_5PF;
        pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);
    } else {
        ESP_LOGE(TAG, "Failed to read Control_1: %s", esp_err_to_name(err));
        return err;
    }

    uint8_t ctrl2 = 0;
    err = pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read Control_2: %s", esp_err_to_name(err));
        return err;
    }

    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;

    err = pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure Control_2: %s", esp_err_to_name(err));
        return err;
    }

    uint8_t sec_reg = 0;
    err = pcf85063_read_reg(RTC_REG_SECONDS, &sec_reg, 1);
    if (err == ESP_OK && (sec_reg & 0x80)) {
        ESP_LOGW(TAG, "PCF85063A oscillator integrity lost (initial battery boot). Time is uncalibrated.");
    }

    return ESP_OK;
}

/**
 * @brief Read current date and time into POSIX struct tm.
 *
 * @param[out]   out_time        Pointer to struct tm populated with current RTC timestamp.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_get_time(struct tm *out_time)
{
    if (out_time == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t data[7] = {0};
    esp_err_t err = pcf85063_read_reg(RTC_REG_SECONDS, data, sizeof(data));
    if (err != ESP_OK) {
        return err;
    }

    out_time->tm_sec = bcd2dec(data[0] & 0x7F);
    out_time->tm_min = bcd2dec(data[1] & 0x7F);
    out_time->tm_hour = bcd2dec(data[2] & 0x3F);
    out_time->tm_mday = bcd2dec(data[3] & 0x3F);
    out_time->tm_wday = data[4] & 0x07;
    out_time->tm_mon = bcd2dec(data[5] & 0x1F) - 1;
    out_time->tm_year = bcd2dec(data[6]) + 100;
    out_time->tm_isdst = -1;

    return ESP_OK;
}

/**
 * @brief Set RTC calendar date and time.
 *
 * @param[in]    time            Pointer to struct tm containing target timestamp.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_set_time(const struct tm *time)
{
    if (time == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t ctrl1 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_1, &ctrl1, 1);
    ctrl1 |= (1 << 5);
    pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);

    uint8_t data[7];
    data[0] = dec2bcd((uint8_t)time->tm_sec) & 0x7F;
    data[1] = dec2bcd((uint8_t)time->tm_min) & 0x7F;
    data[2] = dec2bcd((uint8_t)time->tm_hour) & 0x3F;
    data[3] = dec2bcd((uint8_t)time->tm_mday) & 0x3F;
    data[4] = (uint8_t)time->tm_wday & 0x07;
    data[5] = dec2bcd((uint8_t)(time->tm_mon + 1)) & 0x1F;
    data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));

    esp_err_t err = pcf85063_write_reg(RTC_REG_SECONDS, data, sizeof(data));

    ctrl1 &= ~(1 << 5);
    pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);

    return err;
}

/**
 * @brief Arm hardware countdown timer.
 *
 * @details Drives open-drain interrupt line GPIO 5 LOW upon expiration.
 *
 * @param[in]    seconds         Countdown interval in seconds (1 to 15300s).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
{
    if (seconds == 0 || seconds > 15300) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t timer_value = 0;
    uint8_t clk_src = 0;

    if (seconds <= 255) {
        clk_src = TIMER_CLK_1_HZ;
        timer_value = (uint8_t)seconds;
    } else {
        clk_src = TIMER_CLK_1_60_HZ;
        timer_value = (uint8_t)((seconds + 59) / 60);
    }

    uint8_t stop_mode = clk_src | TIMER_INT_ENABLE_BIT | TIMER_PULSE_MODE_BIT;
    esp_err_t err = pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, stop_mode);
    if (err != ESP_OK) {
        return err;
    }

    err = pcf85063_write_reg_u8(RTC_REG_TIMER_VALUE, timer_value);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t ctrl2 = 0;
    err = pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    if (err != ESP_OK) {
        return err;
    }

    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;
    err = pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t check_ctrl2 = 0xFF;
    for (int32_t retry = 0; retry < 3; retry++) {
        pcf85063_read_reg(RTC_REG_CONTROL_2, &check_ctrl2, 1);
        if (!(check_ctrl2 & (CTRL2_TF_MASK | CTRL2_AF_MASK))) {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    if (check_ctrl2 & (CTRL2_TF_MASK | CTRL2_AF_MASK)) {
        ESP_LOGE(TAG, "Failed to clear PCF85063A interrupt flags in Control_2: 0x%02x", check_ctrl2);
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t timer_mode = clk_src | TIMER_ENABLE_BIT | TIMER_INT_ENABLE_BIT | TIMER_PULSE_MODE_BIT;
    err = pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, timer_mode);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t check_mode = 0;
    pcf85063_read_reg(RTC_REG_TIMER_MODE, &check_mode, 1);
    if ((check_mode & 0x07) != 0x07) {
        ESP_LOGE(TAG, "Timer_mode readback mismatch (expected 0x%02x, got 0x%02x)", timer_mode, check_mode);
        return ESP_ERR_INVALID_STATE;
    }

    ESP_LOGI(TAG, "PCF85063A countdown armed: %lu s (clk_src=0x%02x, val=%u, mode=0x%02x)", (unsigned long)seconds,
             clk_src, timer_value, timer_mode);
    return ESP_OK;
}

/**
 * @brief Cancel and disarm hardware countdown timer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_rtc_cancel_countdown(void)
{
    pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, 0);

    uint8_t ctrl2 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;
    return pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
}

/**
 * @brief Read remaining seconds on the active countdown timer.
 *
 * @details Used for zero-hour collision avoidance.
 *
 * @param[out]   out_sec         Remaining seconds until countdown expiration.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_get_remaining_seconds(uint32_t *out_sec)
{
    if (out_sec == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t timer_mode = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_TIMER_MODE, &timer_mode, 1);
    if (err != ESP_OK) {
        return err;
    }

    if (!(timer_mode & TIMER_ENABLE_BIT)) {
        *out_sec = 0;
        return ESP_OK;
    }

    uint8_t timer_val = 0;
    err = pcf85063_read_reg(RTC_REG_TIMER_VALUE, &timer_val, 1);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t clk_src = timer_mode & (3 << 3);
    if (clk_src == TIMER_CLK_1_60_HZ) {
        *out_sec = (uint32_t)timer_val * 60;
    } else {
        *out_sec = timer_val;
    }

    return ESP_OK;
}

/**
 * @brief Inspect and acknowledge RTC interrupt flags.
 *
 * @details Clears TF (Timer Flag) and AF (Alarm Flag) in Control_2 to deassert GPIO 5.
 *
 * @param[out]   out_alarm       Set to true if an alarm interrupt triggered.
 * @param[out]   out_timer       Set to true if a countdown timer interrupt triggered.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_rtc_get_and_clear_interrupts(bool *out_alarm, bool *out_timer)
{
    uint8_t ctrl2 = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    if (err != ESP_OK) {
        return err;
    }

    if (out_alarm) {
        *out_alarm = (ctrl2 & CTRL2_AF_MASK) != 0;
    }
    if (out_timer) {
        *out_timer = (ctrl2 & CTRL2_TF_MASK) != 0;
    }

    ctrl2 = (ctrl2 & ~(CTRL2_AF_MASK | CTRL2_TF_MASK)) | CTRL2_COF_OFF;
    err = pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t check_ctrl2 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_2, &check_ctrl2, 1);
    if (check_ctrl2 & (CTRL2_AF_MASK | CTRL2_TF_MASK)) {
        ESP_LOGW(TAG, "sub_rtc_get_and_clear_interrupts: flags not cleared (0x%02x)", check_ctrl2);
    }

    return ESP_OK;
}
