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

/* eFuse Linear Battery Calibration (scale & offset) */
volatile uint32_t cal_scale        = 3100;
volatile int32_t  cal_offset       = 0;
volatile uint32_t last_vbat_mv     = 4000;
volatile uint32_t vbat_raw_adc     = 0;
volatile uint32_t usb_connected    = 0; /* 1 if Main CPU confirmed USB VBUS active */

#define RTC_INT_PIN         GPIO_NUM_5
#define RTC_INT_TIMEOUT_US  50000   /* >3x the ~15.6ms PCF85063A pulse */
#define RTC_INT_POLL_US     100

#define BUTTON_DEBOUNCE_US  30000   /* 30ms glitch filter */
#define BUTTON_HOLD_US      2500000 /* 2.5s hold threshold */
#define BUTTON_TAP_MIN_MS   50
#define BUTTON_TAP_MAX_MS   800
#define BUTTON_POLL_US      10000   /* 10ms sampling interval */

/* Dispatch reason constants matching orch_state.h */
#define ULP_DISPATCH_NONE              0
#define ULP_DISPATCH_SENSOR_SAMPLE     1
#define ULP_DISPATCH_MAIN_WAKE         2
#define ULP_DISPATCH_CRITICAL_SHUTDOWN 3
#define ULP_DISPATCH_BOOTLOADER_JUMP   4
#define ULP_DISPATCH_POWER_OFF         5

static inline uint32_t ulp_raw_to_mv(int32_t raw)
{
    if (raw <= 0) return 0;
    /* Linear calibration formula: V_bat = ((raw * cal_scale) / 4096) * 2 + cal_offset */
    uint32_t v_adc = ((uint32_t)raw * cal_scale) >> 12;
    int32_t vbat = (int32_t)(v_adc * 2) + cal_offset;
    if (vbat < 0) return 0;
    return (uint32_t)vbat;
}

static void ulp_dispatch_and_wake(uint32_t rtcio_int_st, int boot_btn, int pwr_btn, int rtc_int, uint32_t vbat_mv)
{
    bool wake_main = false;

    /* 1. Battery Brownout Guard:
     * - Only active when running on battery (not USB).
     * - If 100 mV <= vbat_mv < 3250 mV, trigger emergency brownout shutdown.
     * - If vbat_mv < 100 mV, Zero-Volt Cable Guard bypasses shutdown (USB cable power). */
    if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {
        last_wake_cause = 6; /* CRITICAL_BATTERY_FAULT */
        last_wake_btn   = 0;
        dispatch_reason = ULP_DISPATCH_CRITICAL_SHUTDOWN;
        wake_main       = true;
    } else if (((rtcio_int_st & (BIT(0) | BIT(18))) != 0) || boot_btn == 0 || pwr_btn == 0) {
        /* 2. Tactile Button Glitch Filter (30 ms debounce) */
        ulp_riscv_delay_us(BUTTON_DEBOUNCE_US);

        int boot_now = ulp_riscv_gpio_get_level(GPIO_NUM_0);
        int pwr_now  = ulp_riscv_gpio_get_level(GPIO_NUM_18);

        if (boot_now == 0 || pwr_now == 0) {
            /* Line held LOW >= 30ms: Valid button press */
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
                /* Long hold detected (>2.5s) */
                if (is_boot) {
                    last_wake_cause = 1; /* BOOT */
                    last_wake_btn   = 1;
                    dispatch_reason = ULP_DISPATCH_BOOTLOADER_JUMP;
                    wake_main       = true;
                } else {
                    last_wake_cause = 2; /* POWER */
                    last_wake_btn   = 2;
                    dispatch_reason = ULP_DISPATCH_POWER_OFF;
                    wake_main       = true;
                }
            } else {
                uint32_t hold_ms = elapsed_us / 1000;
                if (hold_ms >= BUTTON_TAP_MIN_MS && hold_ms <= BUTTON_TAP_MAX_MS) {
                    /* Wake-on-Release Rule: Finger is lifted (pin returned HIGH) */
                    last_wake_cause = is_boot ? 1 : 2;
                    last_wake_btn   = is_boot ? 1 : 2;
                    dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
                    wake_main       = true;
                } else {
                    /* Noise (<50ms) or ambiguous hold (800ms - 2.5s): drop */
                    wake_main = false;
                }
            }
        } else {
            /* Noise pulse < 30ms: discard */
            wake_main = false;
        }
    } else if (((rtcio_int_st & BIT(5)) != 0) || rtc_int == 0) {
        /* External PCF85063A Periodic Pulse Tick (GPIO 5) */
        slice_counter++;

        if (slice_counter < overflow_limit) {
            /* Short period: Sensor poll tick, wake Main CPU for Flow A sample */
            last_wake_cause = 4; /* SENSOR TICK */
            last_wake_btn   = 0;
            dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;
            wake_main       = true;
        } else {
            /* Overflow reached (or exceeded due to skipped cycle): Wake Main CPU for Flow B display update */
            slice_counter   = 0;
            last_wake_cause = 3; /* LONG OVERFLOW WAKE */
            last_wake_btn   = 0;
            dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
            wake_main       = true;
        }
    } else {
        /* Spurious or unlatched trigger: clear and sleep */
        wake_main = false;
    }

    /* 3. Strict CDC Latch Clear, Re-Arm & Wakeup Execution */
    if (wake_main) {
        /* Step 1: Clear peripheral interrupt status register first (CDC order) */
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

        /* Step 2: Spin until RTC controller is ready for wakeup (TRM requirement, bounded) */
        uint32_t rdy_timeout = 50000;
        while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_timeout > 0);

        /* Step 3: Wake Main CPU */
        ulp_riscv_wakeup_main_processor();

        /* Step 4: Pulse RTC controller wake latch for >= 120us (>= 3.9 slow-clock cycles on XTAL32K) */
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_delay_us(120);
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

        /* Step 5: DO NOT re-arm GPIO_WAKEUP_ENA here.
         * The Main CPU will wake up, de-assert holds, handle session,
         * and re-arm GPIO_WAKEUP_ENA before entering its next sleep session. */
    } else {
        /* Unhandled or clamped tick: wait for external PCF85063A pulse to return HIGH before re-arming */
        uint32_t waited_us = 0;
        while ((ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0) &&
               (waited_us < RTC_INT_TIMEOUT_US)) {
            ulp_riscv_delay_us(RTC_INT_POLL_US);
            waited_us += RTC_INT_POLL_US;
        }
        rtc_int_stuck = (ulp_riscv_gpio_get_level(RTC_INT_PIN) == 0);

        /* Clear peripheral interrupt flag first & pulse controller latch with 120us CDC delay */
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
        ulp_riscv_delay_us(120);
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

        if (rtc_int_stuck) {
            /* Line is stuck LOW: DO NOT re-arm GPIO_WAKEUP_ENA to prevent runaway wake loops.
             * Wake Main CPU to log hardware fault and service PCF85063A over I2C. */
            uint32_t rdy_timeout = 50000;
            while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP) && --rdy_timeout > 0);
            last_wake_cause = 5; /* RTC_INT_STUCK_FAULT */
            dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
            ulp_riscv_wakeup_main_processor();
        } else {
            /* Line is clean HIGH: Re-arm GPIO wakeup for subsequent events if inputs idle */
            if (ulp_riscv_gpio_get_level(GPIO_NUM_0) == 1 &&
                ulp_riscv_gpio_get_level(GPIO_NUM_18) == 1 &&
                ulp_riscv_gpio_get_level(RTC_INT_PIN) == 1) {
                SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
            }
        }
    }
}

int main(void)
{
    /* 0. Guard against execution while Main CPU is awake (e.g. cold-boot init pass):
     * When sub_power_init_ulp() calls ulp_riscv_config_and_run(), the coprocessor starts
     * immediately. If the Main CPU has not yet entered deep sleep, RDY_FOR_WAKEUP is 0.
     * Halt cleanly without triggering spurious wakes or spinning on unready controllers. */
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

    /* 1. Snapshot interrupt status register immediately */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;

    /* 2. Sample live levels (pads already configured by main CPU) */
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    /* 3. Evaluate ADC & publish fresh values to shared RTC RAM before wake */
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

    /* 4. Dispatch, evaluate triggers, and execute wake sub-function */
    ulp_dispatch_and_wake(rtcio_int_st, boot_btn, pwr_btn, rtc_int, vbat_mv);
    asm volatile("fence" ::: "memory");

    ulp_riscv_halt();
    return 0;
}