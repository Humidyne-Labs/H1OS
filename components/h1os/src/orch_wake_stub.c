/**
 * @file orch_wake_stub.c
 * @brief Layer 3: RTC Fast Memory Deep Sleep Wake Stub Implementation (<3ms Flow A Sensor Sample
 * Burst)
 *
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

#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32)) /* GPIO 47 -> Bit 15 in Reg 1 */
#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32)) /* GPIO 48 -> Bit 16 in Reg 1 */

#define I2C_ADDR_SHTC3 0x70
#define I2C_ADDR_PCF85063 0x51
#define RTC_REG_TIMER_VAL 0x10

#define RTC_TIMER_TE_BIT (1 << 2)
#define RTC_TIMER_TCF_MASK (3 << 3)
#define RTC_TIMER_TCF_MIN (3 << 3)

/* Fast Bit-Bang I2C Primitives running from RTC Fast Memory */
static inline void RTC_IRAM_ATTR i2c_delay(void)
{
    esp_rom_delay_us(5);
}

static inline void RTC_IRAM_ATTR sda_high(void)
{
    /* Float SDA to high (pulled up by external 4.7k resistor) */
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SDA_BIT_MASK);
}

static inline void RTC_IRAM_ATTR sda_low(void)
{
    /* Drive SDA low */
    REG_WRITE(GPIO_OUT1_W1TC_REG, SDA_BIT_MASK);
    REG_WRITE(GPIO_ENABLE1_W1TS_REG, SDA_BIT_MASK);
}

static inline void RTC_IRAM_ATTR scl_high(void)
{
    /* Float SCL to high */
    REG_WRITE(GPIO_ENABLE1_W1TC_REG, SCL_BIT_MASK);
}

static inline void RTC_IRAM_ATTR scl_low(void)
{
    /* Drive SCL low */
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

    /* Read ACK */
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

    /* Send ACK/NACK */
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

/* SHTC3 CRC-8 Polynomial Calculation */
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

/* Low-power MCU Die TSENS readout via RTC SAR registers on ESP32-S3 (Centigrade * 100) */
static int16_t RTC_IRAM_ATTR wake_stub_read_die_temp_centi_c(int16_t cal_centi_c, int16_t fallback_centi_c)
{
    REG_SET_BIT(SENS_SAR_PERI_CLK_GATE_CONF_REG, SENS_TSENS_CLK_EN);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 1);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_POWER_UP_FORCE | SENS_TSENS_POWER_UP);
    /* Allow ~300 us for the TSENS oscillator and counter window to settle */
    esp_rom_delay_us(300);

    /* Trigger conversion by toggling DUMP_OUT and waiting for READY */
    REG_CLR_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT);
    REG_SET_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT);
    int timeout = 100;
    while (((REG_READ(SENS_SAR_TSENS_CTRL_REG) & SENS_TSENS_READY) == 0) && (--timeout > 0)) {
        esp_rom_delay_us(5);
    }
    uint32_t raw = REG_GET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_OUT);

    /* Shut down TSENS immediately to minimize deep-sleep leakage */
    REG_CLR_BIT(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_DUMP_OUT | SENS_TSENS_POWER_UP_FORCE | SENS_TSENS_POWER_UP);
    REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 0);
    REG_CLR_BIT(SENS_SAR_PERI_CLK_GATE_CONF_REG, SENS_TSENS_CLK_EN);

    if (timeout <= 0 || raw == 0 || raw == 0xFF) {
        return fallback_centi_c;
    }

    /* Default I2C_SARADC_TSENS_DAC index 2 (reg_val = 15, range -10..80 C -> offset = 0):
     * T_uncal_centi = (0.4386 * raw - (0 * 27.88) - 20.52) * 100
     *               = (4386 * raw - 205200) / 100
     * T_centi       = T_uncal_centi - cal_centi_c (per-die eFuse temp_calib) */
    int32_t t_centi = (((4386 * (int32_t)raw) - 205200) / 100) - (int32_t)cal_centi_c;
    if (t_centi < -4000 || t_centi > 12500) {
        return fallback_centi_c;
    }
    return (int16_t)t_centi;
}

/* Unconditionally put SHTC3 back into low-power sleep (0xB098) */
static void RTC_IRAM_ATTR shtc3_send_sleep(void)
{
    i2c_start();
    if (i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_write_byte(0xB0);
        i2c_write_byte(0x98);
    }
    i2c_stop();
}

/* Master RTC Wake Stub Entry Point */
void RTC_IRAM_ATTR bsp_wake_stub(void)
{
    /* Configure GPIO 3 in IO_MUX and pull LOW (pulse start for oscilloscope measurement) */
    PIN_FUNC_SELECT(IO_MUX_GPIO3_REG, PIN_FUNC_GPIO);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << HAL_PIN_STATUS_LED));
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));

    uint32_t cause = esp_wake_stub_get_wakeup_cause();

    /* 1. Only sensor sample triggers (ULP_DISPATCH_SENSOR_SAMPLE or internal TIMER_EXPIRE)
     * are processed by the fast RTC wake stub. User buttons, RTC overflow, or critical
     * faults promote immediately to full OS boot. */
    if (ulp_dispatch_reason != ULP_DISPATCH_SENSOR_SAMPLE && cause != TIMER_EXPIRE) {
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }

    /* 2. Zero-Hour Check: Inspect RTC GPIO 5 (PCF85063A Alarm/Timer INT, Active LOW) */
    if (((REG_READ(RTC_GPIO_IN_REG) >> (RTC_GPIO_IN_NEXT_S + HAL_PIN_RTC_INT)) & 1U) == 0) {
        /* External RTC alarm triggered! Promote cleanly to Flow B full UI wake */
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }

    orch_persisted_state_t *st = orch_state_get();

    /* Route GPIO 47 (SDA) and GPIO 48 (SCL) to digital GPIO with input & pull-up enabled */
    PIN_FUNC_SELECT(IO_MUX_GPIO47_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO47_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO47_REG);

    PIN_FUNC_SELECT(IO_MUX_GPIO48_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO48_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO48_REG);

    /* 3. Send SHTC3 Wake Command: 0x3517 */
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

    /* 4. Send SHTC3 Normal-Power Measurement Command: 0x7866 (full ADC precision) */
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

    /* 5. Read 6-Byte SHTC3 Data: [T_MSB, T_LSB, T_CRC, RH_MSB, RH_LSB, RH_CRC] */
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
        /* 6. Unconditionally Send SHTC3 Sleep Command: 0xB098 */
        shtc3_send_sleep();
    }

    /* 7. Verify CRC8 and Commit Sample */
    if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {
        uint16_t raw_t = ((uint16_t)rx[0] << 8) | rx[1];
        uint16_t raw_rh = ((uint16_t)rx[3] << 8) | rx[4];

        /* 8. Convert to Centi-Units (Pure integer arithmetic in RTC Memory) */
        int16_t temp_centi_c = (int16_t)(-4500 + (int32_t)((17500LL * raw_t) / 65535LL));
        uint16_t rh_centi_pct = (uint16_t)((10000LL * raw_rh) / 65535LL);
        int16_t die_centi_c = wake_stub_read_die_temp_centi_c(st->tsens_cal_centi_c, temp_centi_c);

        /* 9. Successive-Sample Thermal Delta Gate & Trend Back-Marking:
         *    - Case 0 (total_samples == 0): First sample cannot prove stability alone -> VALID_COLD
         * = 0, valid_trend = 0.
         *    - Case 1 (total_samples > 0 && |T_new - T_prev| <= 20 centi-C):
         *      Back-mark previous sample VALID_COLD = 1, mark new sample VALID_COLD = 1,
         *      and set valid_trend = 2 (if starting streak) or valid_trend++ (if continuing).
         *    - Case 2 (total_samples > 0 && |T_new - T_prev| > 20 centi-C):
         *      Mark new sample VALID_COLD = 0 and reset valid_trend = 0. */
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
                /* Back-mark the preceding sample as valid and mark current sample as valid */
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

    /* 10. Query PCF85063A (0x51) remaining countdown to prevent Zero-Hour runt collisions */
    uint32_t sleep_sec = st->sample_interval_sec;
    if (sleep_sec == 0)
        sleep_sec = 60;

    bool rtc_timer_active = false;
    uint32_t rem_sec = 0;

    i2c_start();
    if (i2c_write_byte(I2C_ADDR_PCF85063 << 1)) {
        i2c_write_byte(RTC_REG_TIMER_VAL);
        i2c_start();
        if (i2c_write_byte((I2C_ADDR_PCF85063 << 1) | 1)) {
            uint8_t timer_val = i2c_read_byte(true);
            uint8_t timer_mode = i2c_read_byte(false);
            if (timer_mode & RTC_TIMER_TE_BIT) {
                rtc_timer_active = true;
                rem_sec = ((timer_mode & RTC_TIMER_TCF_MASK) == RTC_TIMER_TCF_MIN) ? ((uint32_t)timer_val * 60U)
                                                                                   : (uint32_t)timer_val;
            }
        }
    }
    i2c_stop();

    /* If RTC INT asserted or countdown hit 0 during the 15ms conversion, promote to Flow B */
    if (((REG_READ(RTC_GPIO_IN_REG) >> (RTC_GPIO_IN_NEXT_S + HAL_PIN_RTC_INT)) & 1U) == 0 ||
        (rtc_timer_active && rem_sec == 0)) {
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }

    /* Increment wake counter for this completed Flow A wake stub execution */
    st->wake_count++;
    st->ulp_dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;

    if (!rtc_timer_active || sleep_sec < rem_sec) {
        /* Next Flow A sample lands strictly before external RTC expires -> Rearm internal timer */
        esp_wake_stub_set_wakeup_time((uint64_t)sleep_sec * 1000000ULL);
    } else {
        /* Next sample lands at or after external RTC expiry -> Discard runt timer rearm!
         * Disable internal timer wakeup so chip sleeps purely until external RTC INT fires Flow B
         */
        uint32_t wake_ena = REG_GET_FIELD(RTC_CNTL_WAKEUP_STATE_REG, RTC_CNTL_WAKEUP_ENA);
        REG_SET_FIELD(RTC_CNTL_WAKEUP_STATE_REG, RTC_CNTL_WAKEUP_ENA, wake_ena & ~((uint32_t)TIMER_EXPIRE));
    }

    /* Turn off status pin pulse right before re-entering sleep */
    REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));

    esp_wake_stub_sleep(&bsp_wake_stub);
}

void orch_wake_stub_install(void)
{
    esp_set_deep_sleep_wake_stub(bsp_wake_stub);
}
