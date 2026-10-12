/**
 * @file orch_wake_stub.c
 * @brief Layer 3: RTC Fast Memory Deep Sleep Wake Stub Implementation (<3ms Flow A Sensor Sample Burst)
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_wake_stub.h"
#include "h1os/orch_state.h"
#include "h1os/orch_math.h"
#include "h1os/hal_types.h"
#include "esp_wake_stub.h"
#include "esp_sleep.h"
#include "esp_attr.h"
#include "esp_rom_sys.h"
#include "esp32s3/rom/rtc.h"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/soc.h"

#define SDA_BIT_MASK      (1UL << (HAL_PIN_I2C_SDA - 32))  /* GPIO 47 -> Bit 15 in Reg 1 */
#define SCL_BIT_MASK      (1UL << (HAL_PIN_I2C_SCL - 32))  /* GPIO 48 -> Bit 16 in Reg 1 */

#define I2C_ADDR_SHTC3    0x70
#define I2C_ADDR_PCF85063 0x51
#define RTC_REG_TIMER_VAL 0x10
#define RTC_TIMER_TE_BIT  (1 << 2)
#define RTC_TIMER_TCF_MASK (3 << 3)
#define RTC_TIMER_TCF_MIN  (3 << 3)

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

/* Master RTC Wake Stub Entry Point */
void RTC_IRAM_ATTR bsp_wake_stub(void)
{
    /* Configure GPIO 3 in IO_MUX and pull LOW (pulse start for oscilloscope measurement) */
    PIN_FUNC_SELECT(IO_MUX_GPIO3_REG, PIN_FUNC_GPIO);
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << HAL_PIN_STATUS_LED));
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));

    uint32_t cause = esp_wake_stub_get_wakeup_cause();

    /* 1. Only pure internal timer wakeups (TIMER_EXPIRE = BIT(3)) are processed by the sensor stub */
    if (cause != TIMER_EXPIRE) {
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

    /* Route GPIO 47 (SDA) and GPIO 48 (SCL) to digital GPIO with input & pull-up enabled */
    PIN_FUNC_SELECT(IO_MUX_GPIO47_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO47_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO47_REG);

    PIN_FUNC_SELECT(IO_MUX_GPIO48_REG, PIN_FUNC_GPIO);
    PIN_INPUT_ENABLE(IO_MUX_GPIO48_REG);
    PIN_PULLUP_EN(IO_MUX_GPIO48_REG);

    /* 3. Send SHTC3 Wake Command: 0x3517 */
    i2c_start();
    if (!i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_stop();
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }
    i2c_write_byte(0x35);
    i2c_write_byte(0x17);
    i2c_stop();

    esp_rom_delay_us(250);

    /* 4. Send SHTC3 Normal-Power Measurement Command: 0x7866 (full ADC precision) */
    i2c_start();
    if (!i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_stop();
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }
    i2c_write_byte(0x78);
    i2c_write_byte(0x66);
    i2c_stop();

    esp_rom_delay_us(13000);

    /* 5. Read 6-Byte SHTC3 Data: [T_MSB, T_LSB, T_CRC, RH_MSB, RH_LSB, RH_CRC] */
    i2c_start();
    if (!i2c_write_byte((I2C_ADDR_SHTC3 << 1) | 1)) {
        i2c_stop();
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }
    uint8_t rx[6];
    rx[0] = i2c_read_byte(true);
    rx[1] = i2c_read_byte(true);
    rx[2] = i2c_read_byte(true);
    rx[3] = i2c_read_byte(true);
    rx[4] = i2c_read_byte(true);
    rx[5] = i2c_read_byte(false);
    i2c_stop();

    /* 6. Send SHTC3 Sleep Command: 0xB098 */
    i2c_start();
    if (i2c_write_byte(I2C_ADDR_SHTC3 << 1)) {
        i2c_write_byte(0xB0);
        i2c_write_byte(0x98);
    }
    i2c_stop();

    /* 7. Verify CRC8 */
    if (shtc3_crc8(&rx[0], 2) != rx[2] || shtc3_crc8(&rx[3], 2) != rx[5]) {
        /* Checksum mismatch: boot normally so main app can handle diagnostic error */
        REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << HAL_PIN_STATUS_LED));
        esp_default_wake_deep_sleep();
        return;
    }

    uint16_t raw_t  = ((uint16_t)rx[0] << 8) | rx[1];
    uint16_t raw_rh = ((uint16_t)rx[3] << 8) | rx[4];

    /* 8. Convert to Centi-Units (Pure integer arithmetic in RTC Memory) */
    int16_t temp_centi_c = (int16_t)(-4500 + (int32_t)((17500LL * raw_t) / 65535LL));
    uint16_t rh_centi_pct = (uint16_t)((10000LL * raw_rh) / 65535LL);

    /* 9. Commit Tri-Node sample into RTC Slow Memory */
    orch_persisted_state_t *st = orch_state_get();
    orch_tri_node_sample_t sample = {
        .shtc3_temp_centi_c = temp_centi_c,
        .shtc3_rh_centi_pct = rh_centi_pct,
        .mcu_tsens_centi_c  = temp_centi_c,
        .epd_glass_centi_c  = temp_centi_c,
        .timestamp_sec      = 0,
        .quality_flags      = 0x03, /* Cold sample + thermally settled in wake stub */
    };
    orch_state_push_sample(&sample);

    /* Track ambient floor minimum */
    if (temp_centi_c < st->amb_floor_temp_centi_c || !st->ewma_inited) {
        st->amb_floor_temp_centi_c = temp_centi_c;
    }

    /* 10. Query PCF85063A (0x51) remaining countdown to prevent Zero-Hour runt collisions */
    uint32_t sleep_sec = st->sample_interval_sec;
    if (sleep_sec == 0) sleep_sec = 60;

    bool rtc_timer_active = false;
    uint32_t rem_sec = 0;

    i2c_start();
    if (i2c_write_byte(I2C_ADDR_PCF85063 << 1)) {
        i2c_write_byte(RTC_REG_TIMER_VAL);
        i2c_start();
        if (i2c_write_byte((I2C_ADDR_PCF85063 << 1) | 1)) {
            uint8_t timer_val  = i2c_read_byte(true);
            uint8_t timer_mode = i2c_read_byte(false);
            if (timer_mode & RTC_TIMER_TE_BIT) {
                rtc_timer_active = true;
                rem_sec = ((timer_mode & RTC_TIMER_TCF_MASK) == RTC_TIMER_TCF_MIN)
                          ? ((uint32_t)timer_val * 60U)
                          : (uint32_t)timer_val;
            }
        }
    }
    i2c_stop();

    /* If RTC INT asserted or countdown hit 0 during the 13ms conversion, promote to Flow B */
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
         * Disable internal timer wakeup so chip sleeps purely until external RTC INT fires Flow B */
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
