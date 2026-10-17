/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ePaper BSP - Pure Event Mode ULP Coprocessor
 *
 * Implements deterministic time slicing using external PCF85063A 10s pulsed ticks on GPIO 5:
 *   - Tactile Buttons (GPIO 0 / GPIO 18): Immediate wake of Main CPU into Flow B (Interactive UI).
 *   - RTC INT Pulse (GPIO 5):
 *       * slice_counter == (SLICES_OVERFLOW - 1): Pre-main sensor reading (Flow A prep), halt without waking CPU.
 *       * slice_counter >= SLICES_OVERFLOW: Wake Main CPU (Flow A orchestrator / screen refresh).
 *       * Intermediary slices: Clear wake latches and halt; Main CPU stays asleep.
 */

#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"

#define SLICES_OVERFLOW 6 /* 6 slices of 10s = 60s Flow A interval */

/* Exported symbols accessible by Main CPU via ulp_h1os.h */
volatile uint32_t wake_counter     = 0;
volatile uint32_t slice_counter    = 0;
volatile uint32_t dispatch_reason  = 0;
volatile uint32_t last_wake_cause  = 0; /* 1: BOOT, 2: POWER, 3: SENSOR_BURST, 4: MAIN_WAKE */
volatile uint32_t last_wake_btn    = 0;
volatile uint32_t gpio_status_raw  = 0;
volatile uint32_t entry_ccount     = 0;
volatile uint32_t exit_ccount      = 0;

int main(void)
{
    /* 1. Snapshot interrupt status register immediately */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;
    wake_counter++;
    entry_ccount = ULP_RISCV_GET_CCOUNT();

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

        if (slice_counter == (SLICES_OVERFLOW - 1)) {
            /* Overflow - 1: Final sensor sample before main screen refresh */
            last_wake_cause = 3; /* Flow A sensor sample / prep */
            last_wake_btn   = 0;
            dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */
            /* ULP completes preparatory housekeeping and halts without disturbing Main CPU */
            wake_main       = false;
        } else if (slice_counter >= SLICES_OVERFLOW) {
            /* Overflow: Periodic cycle complete (60s), wake Main CPU for display update */
            slice_counter   = 0;
            last_wake_cause = 4; /* Main UI Wake */
            last_wake_btn   = 0;
            dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
            wake_main       = true;
        } else {
            /* Intermediary time slices: Quiescent, Main CPU remains deep asleep */
            wake_main       = false;
        }
    } else {
        /* Spurious or unlatched trigger: clear and sleep */
        wake_main = false;
    }

    /* 4. Clear status latch and re-arm GPIO wakeup option */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    exit_ccount = ULP_RISCV_GET_CCOUNT();

    /* 5. Conditionally wake Main CPU and cleanly shut down ULP */
    if (wake_main) {
        ulp_riscv_wakeup_main_processor();
    }

    ulp_riscv_shutdown();
    return 0;
}