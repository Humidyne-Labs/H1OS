/**
 * @file sub_rtc.c
 * @brief Layer 2: PCF85063A Real-Time Clock Subsystem Driver Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_rtc.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

static const char *TAG = "sub_rtc";

/* PCF85063A Register Map */
#define RTC_REG_CONTROL_1      0x00
#define RTC_REG_CONTROL_2      0x01
#define RTC_REG_OFFSET         0x02
#define RTC_REG_RAM_BYTE       0x03
#define RTC_REG_SECONDS        0x04
#define RTC_REG_MINUTES        0x05
#define RTC_REG_HOURS          0x06
#define RTC_REG_DAYS           0x07
#define RTC_REG_WEEKDAYS       0x08
#define RTC_REG_MONTHS         0x09
#define RTC_REG_YEARS          0x0A
#define RTC_REG_ALARM_SEC      0x0B
#define RTC_REG_TIMER_VALUE    0x10
#define RTC_REG_TIMER_MODE     0x11

/* Control_1 Register Bitmasks */
#define CTRL1_STOP_MASK        (1 << 5)
#define CTRL1_12_24_MASK       (1 << 1)
#define CTRL1_CAP_SEL_12_5PF   (1 << 0)
#define CTRL1_SW_RESET_CMD     0x58

/* Control_2 Register Bitmasks */
#define CTRL2_AF_MASK          (1 << 6)
#define CTRL2_TF_MASK          (1 << 3)
#define CTRL2_AIE_MASK         (1 << 7)
#define CTRL2_COF_OFF          0x07

/* Timer Mode Register (0x11) Bitmasks - TCF[1:0] in bits [4:3] */
#define TIMER_CLK_4096_HZ      (0 << 3)
#define TIMER_CLK_64_HZ        (1 << 3)
#define TIMER_CLK_1_HZ         (2 << 3)
#define TIMER_CLK_1_60_HZ      (3 << 3)
#define TIMER_ENABLE_BIT       (1 << 2)
#define TIMER_INT_ENABLE_BIT   (1 << 1)

/* BCD Conversion Helpers */
static inline uint8_t bcd2dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

static inline uint8_t dec2bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

static esp_err_t pcf85063_read_reg(uint8_t reg, uint8_t *val, size_t len)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_PCF85063, &reg, 1, val, len, pdMS_TO_TICKS(50));
}

static esp_err_t pcf85063_write_reg(uint8_t reg, const uint8_t *val, size_t len)
{
    uint8_t buf[16];
    if (len + 1 > sizeof(buf)) return ESP_ERR_INVALID_SIZE;
    buf[0] = reg;
    memcpy(&buf[1], val, len);
    return hal_i2c_write(HAL_I2C_ADDR_PCF85063, buf, len + 1, pdMS_TO_TICKS(50));
}

static esp_err_t pcf85063_write_reg_u8(uint8_t reg, uint8_t val)
{
    return pcf85063_write_reg(reg, &val, 1);
}

esp_err_t sub_rtc_init(void)
{
    /* 1. Configure Control_1 (12.5pF crystal capacitance, STOP=0, 24h mode) */
    uint8_t ctrl1 = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_CONTROL_1, &ctrl1, 1);
    if (err == ESP_OK) {
        ctrl1 = (ctrl1 & ~CTRL1_STOP_MASK) | CTRL1_CAP_SEL_12_5PF;
        pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);
    } else {
        ESP_LOGE(TAG, "Failed to read Control_1: %s", esp_err_to_name(err));
        return err;
    }

    /* 2. Disable CLKOUT push-pull square wave (Control_2 bits COF[2:0] = 111) to eliminate parasitic trace leakage */
    uint8_t ctrl2 = 0;
    err = pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read Control_2: %s", esp_err_to_name(err));
        return err;
    }

    /* Set COF[2:0] = 0x07 (bits 2:0 in Control_2: 0b00000111) and clear pending flags */
    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;

    err = pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure Control_2: %s", esp_err_to_name(err));
        return err;
    }

    /* 3. Check Oscillator Stop flag in Seconds register (bit 7) */
    uint8_t sec_reg = 0;
    err = pcf85063_read_reg(RTC_REG_SECONDS, &sec_reg, 1);
    if (err == ESP_OK && (sec_reg & 0x80)) {
        ESP_LOGW(TAG, "PCF85063A oscillator integrity lost (initial battery boot). Time is uncalibrated.");
    }

    return ESP_OK;
}

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

    out_time->tm_sec  = bcd2dec(data[0] & 0x7F);
    out_time->tm_min  = bcd2dec(data[1] & 0x7F);
    out_time->tm_hour = bcd2dec(data[2] & 0x3F);
    out_time->tm_mday = bcd2dec(data[3] & 0x3F);
    out_time->tm_wday = data[4] & 0x07;
    out_time->tm_mon  = bcd2dec(data[5] & 0x1F) - 1; /* POSIX is 0-11 */
    out_time->tm_year = bcd2dec(data[6]) + 100;     /* POSIX is years since 1900 (2000 = 100) */
    out_time->tm_isdst = -1;

    return ESP_OK;
}

esp_err_t sub_rtc_set_time(const struct tm *time)
{
    if (time == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Stop clock during setting */
    uint8_t ctrl1 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_1, &ctrl1, 1);
    ctrl1 |= (1 << 5); /* STOP bit */
    pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);

    uint8_t data[7];
    data[0] = dec2bcd((uint8_t)time->tm_sec) & 0x7F; /* Clear OS bit */
    data[1] = dec2bcd((uint8_t)time->tm_min) & 0x7F;
    data[2] = dec2bcd((uint8_t)time->tm_hour) & 0x3F;
    data[3] = dec2bcd((uint8_t)time->tm_mday) & 0x3F;
    data[4] = (uint8_t)time->tm_wday & 0x07;
    data[5] = dec2bcd((uint8_t)(time->tm_mon + 1)) & 0x1F;
    data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));

    esp_err_t err = pcf85063_write_reg(RTC_REG_SECONDS, data, sizeof(data));

    /* Restart clock */
    ctrl1 &= ~(1 << 5);
    pcf85063_write_reg_u8(RTC_REG_CONTROL_1, ctrl1);

    return err;
}

esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
{
    if (seconds == 0 || seconds > 15300) {
        return ESP_ERR_INVALID_ARG;
    }

    /* 1. Stop timer while configuring */
    pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, 0);

    /* 2. Clear any pending flags in Control_2 so INT pin is deasserted (HIGH) */
    uint8_t ctrl2 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;
    pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);

    /* 3. Select 1Hz (seconds) or 1/60Hz (minutes) clock source */
    uint8_t timer_value = 0;
    uint8_t clk_src = 0;

    if (seconds <= 255) {
        clk_src = TIMER_CLK_1_HZ;
        timer_value = (uint8_t)seconds;
    } else {
        clk_src = TIMER_CLK_1_60_HZ;
        timer_value = (uint8_t)((seconds + 59) / 60);
    }

    /* 4. Write timer countdown reload value */
    esp_err_t err = pcf85063_write_reg_u8(RTC_REG_TIMER_VALUE, timer_value);
    if (err != ESP_OK) return err;

    /* 5. Start timer in Timer_mode (0x11): TE = 1, TIE = 1 */
    uint8_t timer_mode = clk_src | TIMER_ENABLE_BIT | TIMER_INT_ENABLE_BIT;
    return pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, timer_mode);
}

esp_err_t sub_rtc_cancel_countdown(void)
{
    /* 1. Disable timer */
    pcf85063_write_reg_u8(RTC_REG_TIMER_MODE, 0);

    /* 2. Clear flags while preserving COF_OFF */
    uint8_t ctrl2 = 0;
    pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;
    return pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
}

esp_err_t sub_rtc_get_remaining_seconds(uint32_t *out_sec)
{
    if (out_sec == NULL) return ESP_ERR_INVALID_ARG;

    uint8_t timer_mode = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_TIMER_MODE, &timer_mode, 1);
    if (err != ESP_OK) return err;

    if (!(timer_mode & TIMER_ENABLE_BIT)) {
        *out_sec = 0;
        return ESP_OK;
    }

    uint8_t timer_val = 0;
    err = pcf85063_read_reg(RTC_REG_TIMER_VALUE, &timer_val, 1);
    if (err != ESP_OK) return err;

    /* Check clock source (TCF bits [4:3]) */
    uint8_t clk_src = timer_mode & (3 << 3);
    if (clk_src == TIMER_CLK_1_60_HZ) {
        *out_sec = (uint32_t)timer_val * 60;
    } else {
        *out_sec = timer_val;
    }

    return ESP_OK;
}

esp_err_t sub_rtc_get_and_clear_interrupts(bool *out_alarm, bool *out_timer)
{
    uint8_t ctrl2 = 0;
    esp_err_t err = pcf85063_read_reg(RTC_REG_CONTROL_2, &ctrl2, 1);
    if (err != ESP_OK) return err;

    if (out_alarm) *out_alarm = (ctrl2 & CTRL2_AF_MASK) != 0;
    if (out_timer) *out_timer = (ctrl2 & CTRL2_TF_MASK) != 0;

    /* Clear flags while preserving COF_OFF and AIE */
    ctrl2 = (ctrl2 & ~(CTRL2_AF_MASK | CTRL2_TF_MASK)) | CTRL2_COF_OFF;
    return pcf85063_write_reg_u8(RTC_REG_CONTROL_2, ctrl2);
}
