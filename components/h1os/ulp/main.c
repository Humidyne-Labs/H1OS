/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ePaper BSP - Pure Event Mode ULP Coprocessor
 *
 * Implements deterministic time slicing using external PCF85063A pulsed ticks on GPIO 5:
 *   - Tactile Buttons (GPIO 0 / GPIO 18): Immediate wake of Main CPU into Flow B (Interactive UI).
 *   - RTC INT Pulse (GPIO 5):
 *       * slice_counter < overflow_limit: Sensor poll tick (Flow A prep/sample), halts without waking Main CPU.
 *       * slice_counter == overflow_limit: Periodic overflow reached, wake Main CPU for Flow B display update.
 *       * slice_counter > overflow_limit: Post-overflow clamp, discard trailing ticks until Main CPU re-arms.
 *   - Remainder Fraction: Fractional remainder (T_flow_b % T_flow_a) is discarded on Main CPU.
 */

#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"

/* Exported symbols accessible by Main CPU via ulp_h1os.h */
volatile uint32_t wake_counter     = 0;
volatile uint32_t last_wake_cause  = 0; /* 1: BOOT, 2: POWER, 3: LONG OVERFLOW, 4: SENSOR TICK, 5: STUCK, 6: CRITICAL_BATTERY */
volatile uint32_t last_wake_btn    = 0;
volatile uint32_t slice_counter    = 0;
volatile uint32_t overflow_limit   = 5; /* Dynamic overflow limit set by Main CPU (e.g. 300s / 60s = 5) */
volatile uint32_t rtc_int_stuck    = 0; /* 1 if GPIO 5 failed to return HIGH within 50ms */
volatile uint32_t dispatch_reason  = 0; /* 1: SENSOR_SAMPLE, 2: MAIN_WAKE, 5: CRITICAL_SHUTDOWN */
volatile uint32_t gpio_status_raw  = 0;
volatile uint32_t entry_ccount     = 0;
volatile uint32_t exit_ccount      = 0;

/* 17-Point Piecewise Linear Battery Calibration LUT (17 x 32-bit words in RTC Slow RAM) */
volatile uint32_t vbat_lut[17]     = {0};
volatile uint32_t last_vbat_mv     = 4000;
volatile uint32_t vbat_raw_adc     = 0;

#define RTC_INT_PIN        GPIO_NUM_5
#define RTC_INT_TIMEOUT_US 50000   /* >3x the ~15.6ms PCF85063A pulse */
#define RTC_INT_POLL_US    100

static inline uint32_t ulp_raw_to_mv(int32_t raw)
{
    if (raw <= 0) return vbat_lut[0];
    if (raw >= 4095) return vbat_lut[16];

    uint32_t idx = (uint32_t)raw >> 8;       /* Segment index (0..15) */
    uint32_t rem = (uint32_t)raw & 0xFF;     /* Remainder within segment (0..255) */

    uint32_t y0 = vbat_lut[idx];
    uint32_t y1 = vbat_lut[idx + 1];

    /* Hardware integer multiply on RV32IMC, shift by 8 (/256) */
    return y0 + (((y1 - y0) * rem) >> 8);
}

int main(void)
{
    wake_counter++;
    entry_ccount = ULP_RISCV_GET_CCOUNT();

    /* 1. Sample Battery ADC (ADC1_CHANNEL_3 / GPIO 4) & Interpolate Millivolts */
    int32_t raw_adc = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_3);
    vbat_raw_adc = (uint32_t)raw_adc;
    uint32_t vbat_mv = ulp_raw_to_mv(raw_adc);
    last_vbat_mv = vbat_mv;

    /* 2. Snapshot interrupt status register immediately */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;

    /* 3. Sample live levels (pads already configured by main CPU) */
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    bool wake_main = false;

    /* 4. Battery Brownout Guard:
     * - If vbat_mv < 100 mV: Zero-Volt USB Guard (operating on USB VBUS without battery) -> Bypass shutdown.
     * - If 100 mV <= vbat_mv < 3250 mV: Critical low battery -> Immediate emergency wake to cut latch! */
    if (vbat_mv >= 100 && vbat_mv < 3250) {
        last_wake_cause = 6; /* CRITICAL_BATTERY_FAULT */
        last_wake_btn   = 0;
        dispatch_reason = 5; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
        wake_main       = true;
    } else if (((rtcio_int_st & BIT(0)) != 0) || boot_btn == 0) {
        /* BOOT Button (GPIO 0) pressed: Immediate tactile wake */
        last_wake_cause = 1;
        last_wake_btn   = 1;
        dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
        wake_main       = true;
    } else if (((rtcio_int_st & BIT(18)) != 0) || pwr_btn == 0) {
        /* POWER Button (GPIO 18) pressed: Immediate tactile wake */
        last_wake_cause = 2;
        last_wake_btn   = 2;
        dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
        wake_main       = true;
    } else if (((rtcio_int_st & BIT(5)) != 0) || rtc_int == 0) {
        /* External PCF85063A Periodic Pulse Tick (GPIO 5) */
        slice_counter++;

        if (slice_counter < overflow_limit) {
            /* Short period: Sensor poll tick, wake Main CPU for Flow A sample */
            last_wake_cause = 4; /* SENSOR TICK */
            last_wake_btn   = 0;
            dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */
            wake_main       = true;
        } else if (slice_counter == overflow_limit) {
            /* Long period reached: Main app overflow wake for Flow B */
            slice_counter   = 0;
            last_wake_cause = 3; /* LONG OVERFLOW WAKE */
            last_wake_btn   = 0;
            dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
            wake_main       = true;
        } else {
            /* Post-overflow clamp: Discard trailing wakes until Main CPU re-arms */
            wake_main       = false;
        }
    } else {
        /* Spurious or unlatched trigger: clear and sleep */
        wake_main = false;
    }

    exit_ccount = ULP_RISCV_GET_CCOUNT();

    /* 5. Strict Latch Clear, Re-Arm & Wakeup Execution */
    if (wake_main) {
        /* Step A: Spin until RTC controller is ready for wakeup (TRM requirement) */
        while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP));

        /* Step B: Wake Main CPU */
        ulp_riscv_wakeup_main_processor();

        /* Step C: Clear RTC controller wake latch & peripheral status */
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

        /* Step D: DO NOT re-arm GPIO_WAKEUP_ENA here: physical line is still LOW.
         * The Main CPU will wake up, de-assert holds, handle debounce,
         * and re-arm GPIO_WAKEUP_ENA before entering its next sleep session. */
    } else {
        /* Unhandled or clamped tick: wait for external PCF85063A pulse to return HIGH before re-arming. */
        uint32_t waited_us = 0;
        while ((ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0) &&
               (waited_us < RTC_INT_TIMEOUT_US)) {
            ulp_riscv_delay_us(RTC_INT_POLL_US);
            waited_us += RTC_INT_POLL_US;
        }
        rtc_int_stuck = (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0);

        /* Clear peripheral interrupt flag & controller latch */
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        ulp_riscv_gpio_wakeup_clear();

        if (rtc_int_stuck) {
            /* Line is stuck LOW: DO NOT re-arm GPIO_WAKEUP_ENA to prevent runaway wake loops.
             * Wake Main CPU to log hardware fault and service PCF85063A over I2C. */
            while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP));
            last_wake_cause = 5; /* RTC_INT_STUCK_FAULT */
            dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
            ulp_riscv_wakeup_main_processor();
        } else {
            /* Line is clean HIGH: Re-arm GPIO wakeup for subsequent events */
            SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
        }
    }

    ulp_riscv_shutdown();
    return 0;
}