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
#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"

/* Exported symbols accessible by Main CPU via ulp_h1os.h */
volatile uint32_t wake_counter     = 0;
volatile uint32_t last_wake_cause  = 0; /* 1: BOOT, 2: POWER, 3: LONG OVERFLOW, 4: SENSOR TICK */
volatile uint32_t last_wake_btn    = 0;
volatile uint32_t slice_counter    = 0;
volatile uint32_t overflow_limit   = 5; /* Dynamic overflow limit set by Main CPU (e.g. 300s / 60s = 5) */
volatile uint32_t dispatch_reason  = 0;
volatile uint32_t gpio_status_raw  = 0;
volatile uint32_t entry_ccount     = 0;
volatile uint32_t exit_ccount      = 0;

int main(void)
{
    wake_counter++;
    entry_ccount = ULP_RISCV_GET_CCOUNT();

    /* 1. Snapshot interrupt status register immediately */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;

    /* 2. Sample live levels (pads already configured by main CPU) */
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    bool wake_main = false;

    /* 3. Determine wake cause & dispatch logic */
    if (((rtcio_int_st & BIT(0)) != 0) || boot_btn == 0) {
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
            /* Short period: Sensor poll tick, keep Main CPU asleep */
            last_wake_cause = 4; /* SENSOR TICK */
            last_wake_btn   = 0;
            dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */
            wake_main       = false;
        } else if (slice_counter == overflow_limit) {
            /* Long period reached: Main app overflow wake */
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

    /* 4. Strict Latch Clear, Re-Arm & Wakeup Execution */
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
        /* Sensor Poll Tick: keep Main CPU asleep.
         * Wait for external PCF85063A ~15.6ms pulse on GPIO 5 to return HIGH before re-arming,
         * preventing an immediate level-triggered re-wake loop. */
        uint32_t wait_timeout = 500000;
        while ((ulp_riscv_gpio_get_level(GPIO_NUM_5) == 0) && (--wait_timeout > 0));

        /* Clear peripheral interrupt flag & controller latch */
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

        /* Re-arm GPIO wakeup for subsequent events */
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    }

    ulp_riscv_shutdown();
    return 0;
}