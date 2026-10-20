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
#define SDA_BIT_MASK       (1UL << (HAL_PIN_I2C_SDA - 32))
#define SCL_BIT_MASK       (1UL << (HAL_PIN_I2C_SCL - 32))

#define I2C_ADDR_SHTC3     0x70
#define I2C_ADDR_PCF85063  0x51
#define RTC_REG_TIMER_VAL  0x10

#define RTC_TIMER_TE_BIT   (1 << 2)
#define RTC_TIMER_TCF_MASK (3 << 3)
#define RTC_TIMER_TCF_MIN  (3 << 3)
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

static int16_t RTC_IRAM_ATTR wake_stub_read_die_temp_centi_c(int16_t cal_centi_c, int16_t fallback_centi_c)
{
    REG_SET_BIT(SENS_SAR_PERI_CLK_GATE_CONF_REG, SENS_TSENS_CLK_EN);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 1);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_POWER_UP_FORCE | SENS_TSENS_POWER_UP);

    esp_rom_delay_us(300);

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

    int32_t t_centi = (((4386 * (int32_t)raw) - 205200) / 100) - (int32_t)cal_centi_c;
    if (t_centi < -4000 || t_centi > 12500) {
        return fallback_centi_c;
    }
    return (int16_t)t_centi;
}

static void RTC_IRAM_ATTR shtc3_send_sleep(void)
{
    i2c_start();
    if (i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_write_byte(0xB0);
        i2c_write_byte(0x98);
    }
    i2c_stop();
}

void RTC_IRAM_ATTR bsp_wake_stub(void)
{
    PIN_FUNC_SELECT(IO_MUX_GPIO3_REG, PIN_FUNC_GPIO);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << HAL_PIN_STATUS_LED));
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));

    uint32_t cause = esp_wake_stub_get_wakeup_cause();

    if (ulp_dispatch_reason != ULP_DISPATCH_SENSOR_SAMPLE && cause != TIMER_EXPIRE) {
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }

    orch_persisted_state_t *st = orch_state_get();

    PIN_FUNC_SELECT(IO_MUX_GPIO47_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO47_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO47_REG);

    PIN_FUNC_SELECT(IO_MUX_GPIO48_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO48_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO48_REG);

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
        uint16_t raw_t = ((uint16_t)rx[0] << 8) | rx[1];
        uint16_t raw_rh = ((uint16_t)rx[3] << 8) | rx[4];

        int16_t temp_centi_c = (int16_t)(-4500 + (int32_t)((17500LL * raw_t) / 65535LL));
        uint16_t rh_centi_pct = (uint16_t)((10000LL * raw_rh) / 65535LL);
        int16_t die_centi_c = wake_stub_read_die_temp_centi_c(st->tsens_cal_centi_c, temp_centi_c);

        uint8_t q_flags = 0;
        if (st->total_samples == 0) {
            q_flags = 0;
            st->valid_trend = 0;
        } else {
            uint8_t prev_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
            int16_t prev_t = st->ring[prev_idx].shtc3_temp_centi_c;
            int16_t diff = temp_centi_c - prev_t;
            if (diff < 0)
                diff = -diff;

            if (diff <= SAMPLE_DELTA_GATE_CENTI_C) {
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
            .mcu_tsens_centi_c = die_centi_c,
            .epd_glass_centi_c = st->last_glass_temp_centi_c,
            .timestamp_sec = 0,
            .quality_flags = q_flags,
        };
        orch_state_push_sample(&sample);
    }

    st->wake_count++;
    st->ulp_dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;

    /* Acknowledge PCF85063A timer interrupt flag (TF in Control_2) */
    i2c_start();
    if (i2c_write_byte(I2C_ADDR_PCF85063 << 1)) {
        i2c_write_byte(0x01); /* RTC_REG_CONTROL_2 */
        i2c_write_byte(0x00); /* Clear TF & AF, COF off */
    }
    i2c_stop();

    /* Clean up ULP and RTC controller interrupt flags to prevent sleep rejection */
    CLEAR_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG,
                      RTC_CNTL_SLP_REJECT_INT_CLR | RTC_CNTL_SLP_WAKEUP_INT_CLR |
                      RTC_CNTL_COCPU_INT_CLR | RTC_CNTL_COCPU_TRAP_INT_CLR | RTC_CNTL_ULP_CP_INT_CLR);
    REG_SET_BIT(RTC_CNTL_STATE0_REG, RTC_CNTL_SLP_REJECT_CAUSE_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

    /* Re-arm ULP GPIO wakeup */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    esp_rom_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));

    esp_wake_stub_sleep(&bsp_wake_stub);
}

void orch_wake_stub_install(void)
{
    esp_set_deep_sleep_wake_stub(bsp_wake_stub);
}
