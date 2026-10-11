/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ePaper BSP - Layer 3: ULP-RISC-V Coprocessor Hardware Sentinel
 *
 * Runs autonomously in RTC Slow SRAM during Deep Sleep.
 * Responsibilities:
 *  1. Autonomous Battery ADC sampling (GPIO 4 / ADC1 Channel 3) with brownout tripwire (<3.25V).
 *  2. Hardware RTC arbitration (GPIO 5 / PCF85063A INT line) eliminating Zero-Hour wake races.
 *  3. Hardware button debounce and event classification (GPIO 0 / BOOT, GPIO 18 / BAT_KEY).
 */

#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_adc_ulp_core.h"

/* Exported variables accessible by the main Xtensa core via ulp_<var> */
uint32_t wake_counter = 0;
uint32_t dispatch_reason = 0; /* 0: None, 1: Sensor Sprint, 2: Main Wake, 3: Critical Shutdown */

/* Battery Calibration Parameters (Provided by main core from eFuses) */
uint32_t cal_scale = 1000;
int32_t  cal_offset = 0;
uint32_t last_vbat_mv = 4000;
uint32_t vbat_critical_mv = 3250; /* Critical tripwire (< 3.25V) */

/* Button State Tracking */
uint32_t boot_btn_events = 0;

int main(void)
{
    wake_counter++;

    /* 1. Hardware RTC Arbitration (GPIO 5 / PCF85063A Alarm INT) */
    /* PCF85063A INT is Active LOW */
    int rtc_int_level = ulp_riscv_gpio_get_level(GPIO_NUM_5);
    if (rtc_int_level == 0) {
        /* Alarm expired! Prompt main core straight into Full UI Refresh */
        dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
        ulp_riscv_wakeup_main_processor();
        return 0;
    }

    /* 2. Battery ADC Guard (GPIO 4 / ADC1 Channel 3) */
    /* Read ADC1 Channel 3 */
    int32_t raw_adc = ulp_riscv_adc_read_channel(0, 3);
    if (raw_adc > 0) {
        /* Vbat = (raw * cal_scale / 4096) * 2 + cal_offset */
        uint32_t v_div_mv = (uint32_t)((raw_adc * (int64_t)cal_scale) / 4096);
        uint32_t v_bat_mv = (v_div_mv * 2) + cal_offset;
        last_vbat_mv = v_bat_mv;

        if (v_bat_mv < vbat_critical_mv) {
            /* Brownout tripwire triggered! Wake CPU immediately to show emergency screen & latch off */
            dispatch_reason = 3; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
            ulp_riscv_wakeup_main_processor();
            return 0;
        }
    }

    /* 3. Button Debounce Check (GPIO 0: BOOT0, GPIO 18: BAT_KEY) */
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn = ulp_riscv_gpio_get_level(GPIO_NUM_18);

    if (boot_btn == 0 || pwr_btn == 0) {
        boot_btn_events++;
        dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
        ulp_riscv_wakeup_main_processor();
        return 0;
    }

    /* Default: Sensor sprint wake stub */
    dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SPRINT */
    ulp_riscv_wakeup_main_processor();

    return 0;
}
