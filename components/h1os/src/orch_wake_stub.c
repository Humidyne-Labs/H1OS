/**
 * @file orch_wake_stub.c
 * @brief Layer 3: RTC Fast Memory deep sleep wake stub implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_wake_stub.h"

#include "esp32s3/rom/rtc.h"
#include "esp_attr.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "esp_wake_stub.h"
#include "h1os/hal_types.h"
#include "h1os/orch_math.h"
#include "h1os/orch_state.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/sens_reg.h"
#include "soc/soc.h"
#include "ulp_h1os.h"

#ifndef SENS_SAR_PERI_CLK_GATE_CONF_REG
#define SENS_SAR_PERI_CLK_GATE_CONF_REG (DR_REG_SENS_BASE + 0x104)
#endif
#ifndef SENS_TSENS_CLK_EN
#define SENS_TSENS_CLK_EN (1UL << 29)
#endif

// clang-format off
#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))
#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))

#define I2C_ADDR_SHTC3     0x70
#define I2C_ADDR_PCF85063  0x51
#define RTC_REG_CONTROL_2  0x01
#define RTC_REG_TIMER_VAL  0x10
#define RTC_REG_TIMER_MODE 0x11

#define RTC_TIMER_CLK_1_HZ    (2 << 3)
#define RTC_TIMER_CLK_1_60_HZ (3 << 3)
#define RTC_TIMER_INT_EN_BIT  (1 << 1)
#define RTC_TIMER_PULSE_BIT   (1 << 0)

#define RTC_TIMER_TE_BIT      (1 << 2)
#define RTC_TIMER_TCF_MASK    (3 << 3)
#define RTC_TIMER_TCF_MIN     (3 << 3)
#define RTC_CTRL2_COF_OFF      0x07
// clang-format on

static inline void RTC_IRAM_ATTR i2c_delay(void)
{
    esp_rom_delay_us(5);
}

static inline void RTC_IRAM_ATTR sda_high(void)
{
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SDA_BIT_MASK);
}

static inline void RTC_IRAM_ATTR sda_low(void)
{
    REG_WRITE(GPIO_OUT1_W1TC_REG, SDA_BIT_MASK);
    REG_WRITE(GPIO_ENABLE1_W1TS_REG, SDA_BIT_MASK);
}

static inline void RTC_IRAM_ATTR scl_high(void)
{
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SCL_BIT_MASK);
}

static inline void RTC_IRAM_ATTR scl_low(void)
{
    REG_WRITE(GPIO_OUT1_W1TC_REG, SCL_BIT_MASK);
    REG_WRITE(GPIO_ENABLE1_W1TS_REG, SCL_BIT_MASK);
}

static inline uint8_t RTC_IRAM_ATTR sda_read(void)
{
    return (REG_READ(GPIO_IN1_REG) & SDA_BIT_MASK) ? 1 : 0;
}

static void RTC_IRAM_ATTR i2c_start(void)
{
    sda_high();
    scl_high();
    i2c_delay();
    sda_low();
    i2c_delay();
    scl_low();
    i2c_delay();
}

static void RTC_IRAM_ATTR i2c_stop(void)
{
    sda_low();
    i2c_delay();
    scl_high();
    i2c_delay();
    sda_high();
    i2c_delay();
}

static bool RTC_IRAM_ATTR i2c_write_byte(uint8_t byte)
{
    for (int i = 7; i >= 0; i--) {
        if ((byte >> i) & 1) {
            sda_high();
        } else {
            sda_low();
        }
        i2c_delay();
        scl_high();
        i2c_delay();
        scl_low();
        i2c_delay();
    }

    sda_high();
    i2c_delay();
    scl_high();
    i2c_delay();
    bool ack = (sda_read() == 0);
    scl_low();
    i2c_delay();
    return ack;
}

static uint8_t RTC_IRAM_ATTR i2c_read_byte(bool ack)
{
    uint8_t byte = 0;
    sda_high();

    for (int i = 7; i >= 0; i--) {
        i2c_delay();
        scl_high();
        i2c_delay();
        if (sda_read()) {
            byte |= (1 << i);
        }
        scl_low();
    }

    if (ack) {
        sda_low();
    } else {
        sda_high();
    }
    i2c_delay();
    scl_high();
    i2c_delay();
    scl_low();
    i2c_delay();
    sda_high();

    return byte;
}

static uint8_t RTC_IRAM_ATTR shtc3_crc8(const uint8_t *data, size_t len)
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

/**
 * @brief Read internal ESP32-S3 SAR temperature sensor in centi-degrees Celsius using Q12 fixed-point math.
 *
 * @param[in]    offset_centi_c   Pre-computed intercept (2052 + tsens_cal_centi_c).
 * @param[in]    fallback_centi_c Fallback temperature if conversion fails.
 *
 * @return Sampled die temperature in centi-°C.
 */
static int16_t RTC_IRAM_ATTR wake_stub_read_die_temp_centi_c(int16_t offset_centi_c, int16_t fallback_centi_c)
{
    REG_SET_BIT(SENS_SAR_PERI_CLK_GATE_CONF_REG, SENS_TSENS_CLK_EN);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_RESET);
    REG_CLR_BIT(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_RESET);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_CLK_DIV, 6);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 1);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_POWER_UP_FORCE | SENS_TSENS_POWER_UP);

    esp_rom_delay_us(400);

    REG_CLR_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT);
    int timeout = 100;
    while (((REG_READ(SENS_SAR_TSENS_CTRL_REG) & SENS_TSENS_READY) == 0) && (--timeout > 0)) {
        esp_rom_delay_us(5);
    }
    uint32_t raw = REG_GET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_OUT);

    REG_CLR_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT | SENS_TSENS_POWER_UP_FORCE | SENS_TSENS_POWER_UP);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 0);
    REG_CLR_BIT(SENS_SAR_PERI_CLK_GATE_CONF_REG, SENS_TSENS_CLK_EN);

    if (timeout <= 0 || raw == 0 || raw == 0xFF) {
        return fallback_centi_c;
    }

    /* Division-free Q12 fixed-point transfer: 43.86 * 4096 = 179651 */
    int32_t t_centi = (((int32_t)raw * 179651) >> 12) - (int32_t)offset_centi_c;
    if (t_centi < -4000 || t_centi > 12500) {
        return fallback_centi_c;
    }
    return (int16_t)t_centi;
}

/**
 * @brief Write a register to PCF85063A over bit-banged I2C with up to 3 attempts.
 */
static bool RTC_IRAM_ATTR rtc_write_reg_retry(uint8_t reg, uint8_t val)
{
    for (int attempt = 0; attempt < 3; attempt++) {
        bool ok = false;
        i2c_start();
        if (i2c_write_byte(I2C_ADDR_PCF85063 << 1)) {
            if (i2c_write_byte(reg) && i2c_write_byte(val)) {
                ok = true;
            }
        }
        i2c_stop();
        if (ok) {
            return true;
        }
        esp_rom_delay_us(20);
    }
    return false;
}

/**
 * @brief Re-arm PCF85063A countdown timer in RTC Fast IRAM for remainder interval.
 *
 * @param[in]    seconds         Remaining countdown interval in seconds.
 */
static void RTC_IRAM_ATTR rtc_rearm_countdown_stub(uint32_t seconds)
{
    if (seconds == 0) return;

    uint8_t timer_val = 0;
    uint8_t clk_src = 0;

    if (seconds <= 255) {
        clk_src = RTC_TIMER_CLK_1_HZ;
        timer_val = (uint8_t)seconds;
    } else {
        clk_src = RTC_TIMER_CLK_1_60_HZ;
        timer_val = (uint8_t)((seconds + 59) / 60);
    }

    uint8_t stop_mode  = clk_src   | RTC_TIMER_INT_EN_BIT | RTC_TIMER_PULSE_BIT;
    uint8_t start_mode = stop_mode | RTC_TIMER_TE_BIT;

    /* 1. Stop timer */
    rtc_write_reg_retry(RTC_REG_TIMER_MODE, stop_mode);

    /* 2. Write countdown value */
    rtc_write_reg_retry(RTC_REG_TIMER_VAL, timer_val);

    /* 3. Acknowledge and clear TF & AF in Control_2, COF off (0x07 = high-Z) */
    rtc_write_reg_retry(RTC_REG_CONTROL_2, RTC_CTRL2_COF_OFF);

    /* 4. Start timer */
    rtc_write_reg_retry(RTC_REG_TIMER_MODE, start_mode);
}

/**
 * @brief Reliable SHTC3 sleep dispatch with ACK verification.
 *
 * @return True if sleep command was acknowledged, false otherwise.
 */
static bool RTC_IRAM_ATTR shtc3_send_sleep(void)
{
    bool ok = false;
    for (int attempt = 0; attempt < 3; attempt++) {
        i2c_start();
        if (i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
            if (i2c_write_byte(0xB0) && i2c_write_byte(0x98)) {
                ok = true;
            }
        }
        i2c_stop();
        if (ok) break;
        esp_rom_delay_us(50);
    }
    return ok;
}

/**
 * @brief Master RTC Wake Stub entry function.
 *
 * @details Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.
 */
void RTC_IRAM_ATTR bsp_wake_stub(void)
{
    /* Suppress ULP GPIO wakeups while wake stub executes */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    uint32_t cause = esp_wake_stub_get_wakeup_cause();

    if (ulp_dispatch_reason != ULP_DISPATCH_SENSOR_SAMPLE && cause != TIMER_EXPIRE) {
        esp_rom_delay_us(5);
        esp_default_wake_deep_sleep();
        return;
    }

    volatile orch_persisted_state_t *st = orch_state_get();

    /* Account for the elapsed Flow A deep sleep slice that triggered this wake stub */
    st->total_sleep_sec += (st->sample_interval_sec > 0) ? st->sample_interval_sec : 60U;

    PIN_FUNC_SELECT(IO_MUX_GPIO47_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO47_REG); /* I2C SDA */

    PIN_FUNC_SELECT(IO_MUX_GPIO48_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO48_REG); /* I2C SCL */

    bool sample_ok = true;
    i2c_start();
    if (!i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_stop();
        sample_ok = false;
    } else {
        i2c_write_byte(0x35);
        i2c_write_byte(0x17);
        i2c_stop();
        esp_rom_delay_us(250);
    }

    if (sample_ok) {
        i2c_start();
        if (!i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
            i2c_stop();
            shtc3_send_sleep();
            sample_ok = false;
        } else {
            i2c_write_byte(0x78);
            i2c_write_byte(0x66);
            i2c_stop();
            esp_rom_delay_us(14500);
        }
    }

    uint8_t rx[6] = {0};
    if (sample_ok) {
        i2c_start();
        if (!i2c_write_byte((I2C_ADDR_SHTC3 << 1) | 1)) {
            i2c_stop();
            sample_ok = false;
        } else {
            rx[0] = i2c_read_byte(true);
            rx[1] = i2c_read_byte(true);
            rx[2] = i2c_read_byte(true);
            rx[3] = i2c_read_byte(true);
            rx[4] = i2c_read_byte(true);
            rx[5] = i2c_read_byte(false);
            i2c_stop();
        }

        shtc3_send_sleep();
    }

    if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {
        uint16_t raw_t  = ((uint16_t)rx[0] << 8) | rx[1];
        uint16_t raw_rh = ((uint16_t)rx[3] << 8) | rx[4];

        /* Factory-calibrated SHTC3 transfer equations using 32-bit unsigned hardware division (quou) */
        int16_t  temp_centi_c = (int16_t)(-4500 + (int32_t)((17500U * (uint32_t)raw_t) / 65535U));
        uint16_t rh_centi_pct = (uint16_t)((10000U * (uint32_t)raw_rh) / 65535U);
        int16_t  die_centi_c  = wake_stub_read_die_temp_centi_c(st->tsens_offset_centi_c, temp_centi_c);

        uint8_t q_flags = 0;
        if (st->total_samples == 0) {
            q_flags = 0;
            st->valid_trend = 0;
        } else {
            uint8_t prev_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
            int16_t prev_t = st->ring[prev_idx].shtc3_temp_centi_c;

            /* Steady-state gate: when |temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C, board is settled and SHTC3 is trusted */
            if (orch_math_is_plateau_settled(prev_t, temp_centi_c, SAMPLE_DELTA_GATE_CENTI_C)) {
                st->ring[prev_idx].quality_flags |= (SAMPLE_FLAG_VALID_COLD | SAMPLE_FLAG_THERMAL_SETTLED);
                q_flags = SAMPLE_FLAG_VALID_COLD | SAMPLE_FLAG_THERMAL_SETTLED;
                if (st->valid_trend < 2) {
                    st->valid_trend = 2;
                } else {
                    st->valid_trend++;
                }
            } else {
                q_flags = 0;
                st->valid_trend = 0;
            }
        }

        orch_tri_node_sample_t sample = {
            .shtc3_temp_centi_c = temp_centi_c,
            .shtc3_rh_centi_pct = rh_centi_pct,
            .mcu_tsens_centi_c  = die_centi_c,
            .epd_glass_centi_c  = st->last_glass_temp_centi_c,
            .timestamp_sec      = 0,
            .quality_flags      = q_flags,
        };
        orch_state_push_sample(&sample);
    }

    st->wake_count++;
    st->ulp_dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;

    /* 1. Clear TF & AF in PCF85063A Control_2 (or rearm remainder) FIRST so /INT can release */
    esp_rom_delay_us(20);
    if (ulp_slice_counter == (ulp_overflow_limit - 1) && ulp_remainder_sec > 0) {
        rtc_rearm_countdown_stub(ulp_remainder_sec);
    } else {
        /* Acknowledge PCF85063A timer interrupt flag (TF in Control_2) with COF=111 (0x07) */
        rtc_write_reg_retry(RTC_REG_CONTROL_2, RTC_CTRL2_COF_OFF);
    }

    /* 2. Wait for the PCF85063A open-drain /INT line to release back HIGH before clearing status */
    uint32_t timeout_us = 20000;
    while (((REG_READ(RTC_GPIO_IN_REG) >> (RTC_GPIO_IN_NEXT_S + HAL_PIN_RTC_INT)) & 1U) == 0) {
        esp_rom_delay_us(500);
        if (timeout_us <= 500) break;
        timeout_us -= 500;
    }

    /* Clean up ULP and RTC controller interrupt flags to prevent sleep rejection */
    CLEAR_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG,
                      RTC_CNTL_SLP_REJECT_INT_CLR |
                      RTC_CNTL_SLP_WAKEUP_INT_CLR |
                      RTC_CNTL_COCPU_INT_CLR      |
                      RTC_CNTL_COCPU_TRAP_INT_CLR |
                      RTC_CNTL_ULP_CP_INT_CLR);
    REG_SET_BIT(RTC_CNTL_STATE0_REG, RTC_CNTL_SLP_REJECT_CAUSE_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

    /* Re-arm ULP GPIO wakeup */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    esp_rom_delay_us(120);

    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    /* Tear down I2C pads to eliminate deep-sleep leakage */
    PIN_INPUT_DISABLE(IO_MUX_GPIO47_REG);
    PIN_PULLUP_DIS(IO_MUX_GPIO47_REG);
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SDA_BIT_MASK);

    PIN_INPUT_DISABLE(IO_MUX_GPIO48_REG);
    PIN_PULLUP_DIS(IO_MUX_GPIO48_REG);
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SCL_BIT_MASK);

    esp_wake_stub_sleep(&bsp_wake_stub);
}

/**
 * @brief Install the RTC deep sleep wake stub.
 *
 * @details Called before entering deep sleep to arm the ultra-fast wake stub handler.
 */
void orch_wake_stub_install(void)
{
    esp_set_deep_sleep_wake_stub(bsp_wake_stub);
}