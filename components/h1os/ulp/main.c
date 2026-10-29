/**
 * @file main.c
 * @brief Pure event-mode ULP-RISC-V coprocessor hardware monitor
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/sens_reg.h"
#include "ulp_riscv.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_utils.h"
#include "orch_state.h"

#include <stdbool.h>
#include <stdint.h>

// clang-format off

volatile uint32_t wake_counter    = 0;
volatile uint32_t last_wake_cause = 0;
volatile uint32_t last_wake_btn   = 0;
volatile uint32_t slice_counter   = 0;
volatile uint32_t overflow_limit  = 5;
volatile uint32_t remainder_sec   = 0;
volatile uint32_t rtc_int_stuck   = 0;
volatile uint32_t dispatch_reason = 0;
volatile uint32_t gpio_status_raw = 0;

volatile uint32_t cal_scale       = 8601;
volatile int32_t  cal_offset      = 0;
volatile uint32_t last_vbat_mv    = 4000;
volatile uint32_t vbat_raw_adc    = 0;
volatile uint32_t usb_connected   = 0;

#define ULP_VBAT_RING_SIZE 8
volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};
volatile uint32_t vbat_ring_head  = 0;
volatile uint32_t vbat_ring_count = 0;

#define RTC_INT_PIN                    GPIO_NUM_5
#define RTC_INT_TIMEOUT_US             50000
#define RTC_INT_POLL_US                100

#define BUTTON_DEBOUNCE_US             30000
#define BUTTON_HOLD_US                 2500000
#define BUTTON_TAP_MIN_MS              30
#define BUTTON_TAP_MAX_MS              2500
#define BUTTON_POLL_US                 5000
#define BUTTON_RELEASE_TIMEOUT_US      50000

#define PMU_RDY_SPIN_MAX               50000
#define ADC_CONV_SPIN_MAX              10000
#define SAR1_XPD_SETTLE_US             40
#define SAR1_START_PULSE_US            2
// clang-format on

/**
 * @brief Full RISC-V device I/O and memory fence barrier (`fence iorw, iorw`).
 *
 * @details ESP-IDF compiles the ULP-RISC-V target with `-Os`. Issuing `fence iorw, iorw`
 * with a `"memory"` clobber forces both the compiler and the RV32IMC load/store unit to
 * drain all preceding MMIO peripheral register writes across the RTC/SENS bus before
 * executing subsequent register writes or status reads (`PIT-03-B`).
 */
static inline void ulp_reg_barrier(void)
{
    asm volatile("fence iorw, iorw" ::: "memory");
}

/**
 * @brief Converts raw ADC tick value to battery voltage in millivolts.
 *
 * @param[in]    raw             Raw ADC reading.
 *
 * @return Calibrated voltage in millivolts.
 */
static inline uint32_t ulp_raw_to_mv(int32_t raw)
{
    if (raw <= 0) {
        return 0;
    }

    int32_t vbat = (int32_t)(((uint32_t)raw * cal_scale) >> 12) + cal_offset;
    if (vbat < 0) {
        return 0;
    }
    return (uint32_t)vbat;
}

/**
 * @brief Clear latched RTC GPIO status and ULP wakeup flip-flop.
 */
static inline void ulp_clear_gpio_wakeup_latch(void)
{
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    asm volatile("fence" ::: "memory");
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    asm volatile("fence" ::: "memory");
    ulp_riscv_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    asm volatile("fence" ::: "memory");
}

/**
 * @brief Disarm ULP GPIO wakeup and trigger main Xtensa processor wakeup once PMU is ready.
 */
static inline void ulp_disarm_and_wake_main(void)
{
    /* Strictly gate off ULP GPIO wakeups while main CPU owns the system (Rule 5) */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    ulp_clear_gpio_wakeup_latch();

    uint32_t rdy_timeout = PMU_RDY_SPIN_MAX;
    while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_timeout > 0) {
    }

    asm volatile("fence" ::: "memory");
    ulp_riscv_wakeup_main_processor();
}

/**
 * @brief Perform a timeout-bounded SAR ADC1 read on ADC1_CHANNEL_3 (GPIO 4).
 *
 * @param[out]   out_raw         Raw 12-bit ADC value on success.
 *
 * @return true if conversion completed within timeout, false if timed out.
 */
static bool __attribute__((noinline)) ulp_read_vbat_adc_bounded(int32_t *out_raw)
{
#if defined(SENS_SAR_MEAS1_CTRL2_REG) && defined(SENS_MEAS1_DONE_SAR_M)
    /* Verify RTC controller owns SAR1 before starting conversion */
    if (REG_GET_FIELD(SENS_SAR_MEAS1_MUX_REG, SENS_SAR1_DIG_FORCE) != 0) {
        return false;
    }

    /* 1. Force SAR1 analog power-up and explicitly enforce 12 dB attenuation (0x3) on ADC1_CH3 (bits [7:6]) */
    REG_SET_FIELD(SENS_SAR_POWER_XPD_SAR_REG, SENS_FORCE_XPD_SAR, 0x3U);
    ulp_reg_barrier();

    SET_PERI_REG_BITS(SENS_SAR_ATTEN1_REG, 0x3U, 0x3U, (ADC_CHANNEL_3 * 2));
    ulp_reg_barrier();

    REG_SET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_SAR1_EN_PAD_FORCE, 1U);
    ulp_reg_barrier();

    REG_SET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_MEAS1_START_FORCE, 1U);
    ulp_reg_barrier();

    REG_SET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_SAR1_EN_PAD, (1U << ADC_CHANNEL_3));
    ulp_reg_barrier();

    /* Allow SAR1 internal voltage reference and 12 dB capacitive attenuator network to settle */
    ulp_riscv_delay_us(SAR1_XPD_SETTLE_US);

    /* 2. Strobe SENS_MEAS1_START_SAR 0 -> 1 with explicit I/O fence and hold delay */
    REG_SET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_MEAS1_START_SAR, 0);
    ulp_reg_barrier();
    ulp_riscv_delay_us(SAR1_START_PULSE_US);

    REG_SET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_MEAS1_START_SAR, 1);
    ulp_reg_barrier();

    uint32_t spin = ADC_CONV_SPIN_MAX;
    while (REG_GET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_MEAS1_DONE_SAR) == 0) {
        asm volatile("" : "+r"(spin));
        if (--spin == 0) {
            REG_SET_FIELD(SENS_SAR_POWER_XPD_SAR_REG, SENS_FORCE_XPD_SAR, 0x0U);
            ulp_reg_barrier();
            return false;
        }
    }

    ulp_reg_barrier();
    *out_raw = (int32_t)REG_GET_FIELD(SENS_SAR_MEAS1_CTRL2_REG, SENS_MEAS1_DATA_SAR);

    /* 3. Return SAR1 power control to hardware FSM for low-power deep sleep */
    REG_SET_FIELD(SENS_SAR_POWER_XPD_SAR_REG, SENS_FORCE_XPD_SAR, 0x0U);
    ulp_reg_barrier();
    return true;
#else
    *out_raw = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_3);
    return (*out_raw > 0);
#endif
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
 */
static void ulp_dispatch_and_wake(uint32_t rtcio_int_st, int32_t boot_btn, int32_t pwr_btn, int32_t rtc_int, uint32_t vbat_mv)
{
    bool wake_main = false;

    /* 1. Critical battery brownout guard (requires 2 consecutive samples to reject ADC noise) */
    static uint32_t s_low_vbat_count = 0;
    if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {
        s_low_vbat_count++;
        if (s_low_vbat_count >= 2) {
            last_wake_cause = ULP_WAKE_CAUSE_CRITICAL_BATTERY;
            last_wake_btn   = H1OS_WAKE_BTN_NONE;
            dispatch_reason = ULP_DISPATCH_CRITICAL_SHUTDOWN;
            wake_main       = true;
        }
    } else {
        s_low_vbat_count = 0;
    }

    /* 2. Tactile button evaluation (BOOT0 = GPIO 0, POWER = GPIO 18) */
    if (!wake_main && (((rtcio_int_st & (BIT(0) | BIT(18))) != 0) || boot_btn == 0 || pwr_btn == 0)) {
        ulp_riscv_delay_us(BUTTON_DEBOUNCE_US);

        int32_t boot_now = (int32_t)ulp_riscv_gpio_get_level(GPIO_NUM_0);
        int32_t pwr_now  = (int32_t)ulp_riscv_gpio_get_level(GPIO_NUM_18);

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
                    last_wake_cause = ULP_WAKE_CAUSE_BOOT_BTN;
                    last_wake_btn   = H1OS_WAKE_BTN_BOOT;
                    dispatch_reason = ULP_DISPATCH_BOOTLOADER_JUMP;
                    wake_main       = true;
                } else {
                    last_wake_cause = ULP_WAKE_CAUSE_PWR_BTN;
                    last_wake_btn   = H1OS_WAKE_BTN_POWER;
                    dispatch_reason = ULP_DISPATCH_POWER_OFF;
                    wake_main       = true;
                }
            } else {
                /* Wait for contact bounce on button release to settle HIGH (Wake-on-Release rule) */
                ulp_riscv_delay_us(BUTTON_DEBOUNCE_US);
                if (ulp_riscv_gpio_get_level(pin) != 0) {
                    uint32_t hold_ms = elapsed_us / 1000U;
                    if (hold_ms >= BUTTON_TAP_MIN_MS && hold_ms < BUTTON_TAP_MAX_MS) {
                        last_wake_cause = is_boot ? ULP_WAKE_CAUSE_BOOT_BTN : ULP_WAKE_CAUSE_PWR_BTN;
                        last_wake_btn   = is_boot ? H1OS_WAKE_BTN_BOOT : H1OS_WAKE_BTN_POWER;
                        dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
                        wake_main       = true;
                    }
                }
            }
        }
    }

    /* 3. External PCF85063A RTC countdown interrupt evaluation (independent of button glitches) */
    if (!wake_main) {
        int32_t rtc_int_now = (int32_t)ulp_riscv_gpio_get_level(RTC_INT_PIN);
        if (((rtcio_int_st & BIT(5)) != 0) || rtc_int == 0 || rtc_int_now == 0) {
            slice_counter++;

            if (slice_counter < overflow_limit) {
                last_wake_cause = ULP_WAKE_CAUSE_SENSOR_TICK;
                last_wake_btn   = H1OS_WAKE_BTN_NONE;
                dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;
                wake_main       = true;
            } else {
                slice_counter   = 0;
                remainder_sec   = 0;
                last_wake_cause = ULP_WAKE_CAUSE_LONG_OVERFLOW;
                last_wake_btn   = H1OS_WAKE_BTN_NONE;
                dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
                wake_main       = true;
            }
        }
    }

    /* 4. Execute main CPU wake or clean re-arm */
    if (wake_main) {
        ulp_disarm_and_wake_main();
    } else {
        /* Wait for any transient low pulse on RTC_INT to release */
        uint32_t waited_us = 0;
        while ((ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0) && (waited_us < RTC_INT_TIMEOUT_US)) {
            ulp_riscv_delay_us(RTC_INT_POLL_US);
            waited_us += RTC_INT_POLL_US;
        }
        rtc_int_stuck = (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0);

        /* Wait for any lingering button release or contact bounce to settle high */
        uint32_t btn_wait_us = 0;
        while ((ulp_riscv_gpio_get_level(GPIO_NUM_0)  == 0 || 
		        ulp_riscv_gpio_get_level(GPIO_NUM_18) == 0) &&
               (btn_wait_us < BUTTON_RELEASE_TIMEOUT_US)) {
            ulp_riscv_delay_us(RTC_INT_POLL_US);
            btn_wait_us += RTC_INT_POLL_US;
        }

        if (rtc_int_stuck) {
            last_wake_cause = ULP_WAKE_CAUSE_RTC_INT_STUCK;
            last_wake_btn   = H1OS_WAKE_BTN_NONE;
            dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
            ulp_disarm_and_wake_main();
        } else {
            ulp_clear_gpio_wakeup_latch();
            SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
        }
    }
}

/**
 * @brief Main ULP-RISC-V entry point.
 *
 * @return 0 on halt.
 */
int main(void)
{
    /* If woken during final microsecond of PMU sleep entry, wait briefly for RDY_FOR_WAKEUP */
    uint32_t rdy_spin = PMU_RDY_SPIN_MAX;
    while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_spin > 0) {
    }

    if (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)) {
        /* Main processor is actively entering sleep; clear trigger latch only and halt, keeping GPIO wake enabled */
        ulp_clear_gpio_wakeup_latch();
        ulp_riscv_halt();
        return 0;
    }

    wake_counter++;
    asm volatile("fence" ::: "memory");

    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;

    int32_t boot_btn = (int32_t)ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int32_t pwr_btn  = (int32_t)ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int32_t rtc_int  = (int32_t)ulp_riscv_gpio_get_level(GPIO_NUM_5);

    /* Main Xtensa cores are still in deep sleep here; sample resting battery voltage on every ULP wake */
    uint32_t vbat_mv = last_vbat_mv;
    int32_t  raw_adc = 0;
    if (ulp_read_vbat_adc_bounded(&raw_adc) && raw_adc > 0) {
        vbat_raw_adc              = (uint32_t)raw_adc;
        vbat_mv                   = ulp_raw_to_mv(raw_adc);
        last_vbat_mv              = vbat_mv;
        vbat_ring[vbat_ring_head] = vbat_mv;
        vbat_ring_head            = (vbat_ring_head + 1) % ULP_VBAT_RING_SIZE;
        if (vbat_ring_count < ULP_VBAT_RING_SIZE) {
            vbat_ring_count++;
        }
    }

    ulp_dispatch_and_wake(rtcio_int_st, boot_btn, pwr_btn, rtc_int, vbat_mv);
    asm volatile("fence" ::: "memory");

    ulp_riscv_halt();
    return 0;
}