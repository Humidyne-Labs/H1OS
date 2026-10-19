/**
 * @file main.c
 * @brief Pure event-mode ULP-RISC-V coprocessor hardware monitor
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "ulp_riscv.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_utils.h"

#include <stdbool.h>
#include <stdint.h>

// clang-format off

volatile uint32_t wake_counter    = 0;
volatile uint32_t last_wake_cause = 0;
volatile uint32_t last_wake_btn   = 0;
volatile uint32_t slice_counter   = 0;
volatile uint32_t overflow_limit  = 5;
volatile uint32_t rtc_int_stuck   = 0;
volatile uint32_t dispatch_reason = 0;
volatile uint32_t gpio_status_raw = 0;
volatile uint32_t entry_ccount    = 0;
volatile uint32_t exit_ccount     = 0;

volatile uint32_t cal_scale       = 3100;
volatile int32_t  cal_offset      = 0;
volatile uint32_t last_vbat_mv    = 4000;
volatile uint32_t vbat_raw_adc    = 0;
volatile uint32_t usb_connected   = 0;

#define RTC_INT_PIN         GPIO_NUM_5
#define RTC_INT_TIMEOUT_US  50000
#define RTC_INT_POLL_US     100

#define BUTTON_DEBOUNCE_US  30000
#define BUTTON_HOLD_US      2500000
#define BUTTON_TAP_MIN_MS   50
#define BUTTON_TAP_MAX_MS   800
#define BUTTON_POLL_US      10000

#define ULP_DISPATCH_NONE              0
#define ULP_DISPATCH_SENSOR_SAMPLE     1
#define ULP_DISPATCH_MAIN_WAKE         2
#define ULP_DISPATCH_CRITICAL_SHUTDOWN 3
#define ULP_DISPATCH_BOOTLOADER_JUMP   4
#define ULP_DISPATCH_POWER_OFF         5
// clang-format on

/**
 * @brief Converts raw ADC tick value to battery voltage in millivolts.
 *
 * @param[in]    raw             Raw ADC reading.
 *
 * @return Calibrated voltage in millivolts.
 */
static inline uint32_t ulp_raw_to_mv(int32_t raw)
{
    if (raw <= 0)
        return 0;

    uint32_t v_adc = ((uint32_t)raw * cal_scale) >> 12;
    int32_t vbat = (int32_t)(v_adc * 2) + cal_offset;
    if (vbat < 0)
        return 0;
    return (uint32_t)vbat;
}

/**
 * @brief Evaluates wakeup triggers and arbitrates wake/shutdown dispatch.
 *
 * @details Handles button debounce, long-press detection, RTC countdown slicing, and critical battery cut.
 *
 * @param[in]    rtcio_int_st    Raw RTC IO interrupt status bitmask.
 * @param[in]    boot_btn        BOOT0 button state (0 = pressed).
 * @param[in]    pwr_btn         POWER button state (0 = pressed).
 * @param[in]    rtc_int         RTC INT line state (0 = active).
 * @param[in]    vbat_mv         Current battery voltage in millivolts.
 *
 * @return Return value of type static void.
 */
static void ulp_dispatch_and_wake(uint32_t rtcio_int_st, int boot_btn, int pwr_btn, int rtc_int, uint32_t vbat_mv)
{
    bool wake_main = false;

    if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {
        last_wake_cause = 6;
        last_wake_btn = 0;
        dispatch_reason = ULP_DISPATCH_CRITICAL_SHUTDOWN;
        wake_main = true;
    } else if (((rtcio_int_st & (BIT(0) | BIT(18))) != 0) || boot_btn == 0 || pwr_btn == 0) {
        ulp_riscv_delay_us(BUTTON_DEBOUNCE_US);

        int boot_now = ulp_riscv_gpio_get_level(GPIO_NUM_0);
        int pwr_now = ulp_riscv_gpio_get_level(GPIO_NUM_18);

        if (boot_now == 0 || pwr_now == 0) {
            bool is_boot = (boot_now == 0);
            gpio_num_t pin = is_boot ? GPIO_NUM_0 : GPIO_NUM_18;

            uint32_t elapsed_us = BUTTON_DEBOUNCE_US;
            bool long_held = false;

            while (ulp_riscv_gpio_get_level(pin) == 0) {
                ulp_riscv_delay_us(BUTTON_POLL_US);
                elapsed_us += BUTTON_POLL_US;
                if (elapsed_us >= BUTTON_HOLD_US) {
                    long_held = true;
                    break;
                }
            }

            if (long_held) {
                if (is_boot) {
                    last_wake_cause = 1;
                    last_wake_btn = 1;
                    dispatch_reason = ULP_DISPATCH_BOOTLOADER_JUMP;
                    wake_main = true;
                } else {
                    last_wake_cause = 2;
                    last_wake_btn = 2;
                    dispatch_reason = ULP_DISPATCH_POWER_OFF;
                    wake_main = true;
                }
            } else {
                uint32_t hold_ms = elapsed_us / 1000;
                if (hold_ms >= BUTTON_TAP_MIN_MS && hold_ms <= BUTTON_TAP_MAX_MS) {
                    last_wake_cause = is_boot ? 1 : 2;
                    last_wake_btn = is_boot ? 1 : 2;
                    dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
                    wake_main = true;
                } else {
                    wake_main = false;
                }
            }
        } else {
            wake_main = false;
        }
    } else if (((rtcio_int_st & BIT(5)) != 0) || rtc_int == 0) {
        slice_counter++;

        if (slice_counter < overflow_limit) {
            last_wake_cause = 4;
            last_wake_btn = 0;
            dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;
            wake_main = true;
        } else {
            slice_counter = 0;
            last_wake_cause = 3;
            last_wake_btn = 0;
            dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
            wake_main = true;
        }
    } else {
        wake_main = false;
    }

    if (wake_main) {
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

        uint32_t rdy_timeout = 50000;
        while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_timeout > 0);

        ulp_riscv_wakeup_main_processor();

        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_delay_us(120);
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

    } else {
        uint32_t waited_us = 0;
        while ((ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0) && (waited_us < RTC_INT_TIMEOUT_US)) {
            ulp_riscv_delay_us(RTC_INT_POLL_US);
            waited_us += RTC_INT_POLL_US;
        }
        rtc_int_stuck = (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0);

        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_delay_us(120);
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

        if (rtc_int_stuck) {
            uint32_t rdy_timeout = 50000;
            while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_timeout > 0);
            last_wake_cause = 5;
            dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
            ulp_riscv_wakeup_main_processor();
        } else {
            if (ulp_riscv_gpio_get_level(GPIO_NUM_0) == 1 && 
					ulp_riscv_gpio_get_level(GPIO_NUM_18) == 1 &&
					ulp_riscv_gpio_get_level(RTC_INT_PIN) == 1) {
				SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
            }
        }
    }
}

/**
 * @brief Main.
 *
 * @return Return value of type int.
 */
int main(void)
{
    if (!REG_GET_BIT(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)) {
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_delay_us(120);
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_halt();
        return 0;
    }

    wake_counter++;
    asm volatile("fence" ::: "memory");

    entry_ccount = ULP_RISCV_GET_CCOUNT();

    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;

    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    uint32_t vbat_mv = last_vbat_mv;
    if (usb_connected) {
        vbat_mv = 4200;
        last_vbat_mv = 4200;
    } else {
        int32_t raw_adc = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_3);
        if (raw_adc > 0) {
            vbat_raw_adc = (uint32_t)raw_adc;
            vbat_mv = ulp_raw_to_mv(raw_adc);
            last_vbat_mv = vbat_mv;
        }
    }

    exit_ccount = ULP_RISCV_GET_CCOUNT();

    ulp_dispatch_and_wake(rtcio_int_st, boot_btn, pwr_btn, rtc_int, vbat_mv);
    asm volatile("fence" ::: "memory");

    ulp_riscv_halt();
    return 0;
}
