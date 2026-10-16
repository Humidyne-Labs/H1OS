/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ePaper BSP - Layer 3: ULP-RISC-V Coprocessor Hardware Monitor
 *
 * Runs autonomously in RTC Slow SRAM during Deep Sleep.
 * Responsibilities:
 *  1. Autonomous Battery ADC sampling (GPIO 4 / ADC1 Channel 3) with brownout threshold (<3.25V).
 *  2. Hardware RTC arbitration (GPIO 5 / PCF85063A INT line) eliminating Zero-Hour wake races.
 *  3. Hardware button debounce and event classification (GPIO 0 / BOOT, GPIO 18 / BAT_KEY).
 */

#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_adc_ulp_core.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"

/* Exported variables accessible by the main Xtensa core via ulp_<var> */
volatile uint32_t wake_counter    = 0;
volatile uint32_t dispatch_reason = 0; /* 0: None, 1: Sensor Sample, 2: Main Wake, 3: Critical Shutdown, 4: BL Jump, 5: Power Off */

/* Battery Calibration Parameters (Provided by main core from eFuses) */
volatile uint32_t cal_scale        = 1000;
volatile int32_t  cal_offset       = 0;
volatile uint32_t last_vbat_mv     = 4000;
volatile uint32_t vbat_critical_mv = 3250; /* Critical brownout threshold (< 3.25V) */

/* Button State Tracking */
volatile uint32_t boot_btn_events = 0;
volatile uint32_t last_wake_btn   = 0; /* 0: None/RTC, 1: BOOT (GPIO 0), 2: POWER (GPIO 18) */

/* Clock/Delay calibration: ESP32-S3 ULP multi-cycle instruction execution requires ~8 clock cycles
 * per rdcycle loop iteration. 17500 / 8 = 2188 cycles per millisecond.
 */
volatile uint32_t cycles_per_ms   = 2188;

/* Telemetry & Debug Observability */
volatile uint32_t last_wake_cause   = 0; /* 0: None, 1: RTC GPIO INT status, 2: Live LOW level, 3: Soft timer, 4: RTC Alarm */
volatile uint32_t gpio_status_raw   = 0; /* Raw RTC_GPIO_STATUS_REG captured at entry */
volatile uint32_t hold_duration_ms  = 0; /* Exact ms duration measured during button hold */
volatile uint32_t loop_sample_count = 0; /* Total loop iterations executed in while() */
volatile uint32_t entry_ccount      = 0; /* Cycle counter reading at entry to main() */
volatile uint32_t exit_ccount       = 0; /* Cycle counter reading at exit from main() */

/*
 * ULP Execution Entry Point:
 * The ULP coprocessor is woken from deep sleep reactively:
 *   - On external RTC Alarm / Timer INT (GPIO 5 falling edge / LOW)
 *   - On external Button Press (GPIO 0 BOOT or GPIO 18 POWER falling edge / LOW)
 *   - On periodic ULP coprocessor sleep timer (configured by sub_power_init_ulp)
 *
 * Once woken, main() runs autonomously in RTC slow SRAM to arbitrate the wake cause,
 * debounce button presses, and only wake the main Xtensa processor when a valid event occurs.
 */
int main(void)
{
    entry_ccount = ULP_RISCV_GET_CCOUNT();
    wake_counter++;
    loop_sample_count = 0;
    hold_duration_ms = 0;

    /* Initialize and enable input buffers for RTC GPIOs in the ULP domain */
    ulp_riscv_gpio_init(GPIO_NUM_5);
    ulp_riscv_gpio_input_enable(GPIO_NUM_5);
    ulp_riscv_gpio_init(GPIO_NUM_0);
    ulp_riscv_gpio_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_init(GPIO_NUM_18);
    ulp_riscv_gpio_input_enable(GPIO_NUM_18);

    /* Read RTC GPIO interrupt status and live pin levels immediately */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    /* Determine root wake trigger for diagnostic observability */
    if ((rtcio_int_st & (BIT(0) | BIT(18))) != 0) {
        last_wake_cause = 1; /* Hardware RTC GPIO status interrupt latch */
    } else if (boot_btn == 0 || pwr_btn == 0) {
        last_wake_cause = 2; /* Live GPIO pin held LOW */
    } else if (((rtcio_int_st & BIT(5)) != 0) || (rtc_int == 0)) {
        last_wake_cause = 4; /* External PCF85063A RTC timer/alarm interrupt */
    } else {
        last_wake_cause = 3; /* Periodic ULP coprocessor sleep timer tick */
    }

    /* =========================================================================
     * 1. Physical Tactile Button Arbitration (GPIO 0: BOOT0, GPIO 18: BAT_KEY)
     * ========================================================================= */
    /* Check if a button was pressed (latched in RTC_GPIO_STATUS_REG or currently LOW) */
    bool boot_pressed = ((rtcio_int_st & BIT(0)) != 0) || (boot_btn == 0);
    bool pwr_pressed  = ((rtcio_int_st & BIT(18)) != 0) || (pwr_btn == 0);

    if (boot_pressed || pwr_pressed) {
        int pressed_btn = 0;
        if (boot_pressed && !pwr_pressed) {
            pressed_btn = 1;
        } else if (pwr_pressed && !boot_pressed) {
            pressed_btn = 2;
        } else {
            /* Both flagged: prioritize whichever is actively held LOW, default to BOOT */
            pressed_btn = (pwr_btn == 0 && boot_btn != 0) ? 2 : 1;
        }

        /* If button is still held down, measure hold duration up to 2.5s */
        uint32_t hold_ms = 0;
        while (hold_ms < 2500) {
            loop_sample_count++;
            boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
            pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
            if ((pressed_btn == 1 && boot_btn != 0) || (pressed_btn == 2 && pwr_btn != 0)) {
                /* Confirm button is truly released with a 2nd sample after 5ms to reject contact bounce */
                ulp_riscv_delay_cycles(cycles_per_ms * 5);
                int confirm_level = (pressed_btn == 1) ? ulp_riscv_gpio_get_level(GPIO_NUM_0)
                                                       : ulp_riscv_gpio_get_level(GPIO_NUM_18);
                if (confirm_level != 0) {
                    /* Confirmed release: User released the button */
                    break;
                }
            }
            ulp_riscv_delay_cycles(cycles_per_ms * 10);
            hold_ms += 10;
        }
        hold_duration_ms = hold_ms;

        /* Debounce stabilization: if pin is still depressed, wait briefly */
        if (boot_btn == 0 || pwr_btn == 0) {
            ulp_riscv_delay_cycles(cycles_per_ms * 20);
        }

        /* Clear RTC GPIO status and ULP wakeup latch */
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        ulp_riscv_gpio_wakeup_clear();

        if (hold_ms >= 2500) {
            if (pressed_btn == 1) {
                /* BOOT held >= 2.5s: Prime ROM Bootloader jump */
                dispatch_reason = 4; /* ULP_DISPATCH_BOOTLOADER_JUMP */
            } else {
                /* POWER held >= 2.5s: Prime Power Off */
                dispatch_reason = 5; /* ULP_DISPATCH_POWER_OFF */
            }
            last_wake_btn = pressed_btn;
            exit_ccount = ULP_RISCV_GET_CCOUNT();
            ulp_riscv_wakeup_main_processor();
            return 0;
        } else {
            /* Any tap released < 2.5s: Wake Flow B Interactive Session */
            boot_btn_events++;
            last_wake_btn   = pressed_btn;
            dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
            exit_ccount = ULP_RISCV_GET_CCOUNT();
            ulp_riscv_wakeup_main_processor();
            return 0;
        }
    }

    /* =========================================================================
     * 2. External RTC Timer/Alarm Arbitration (GPIO 5 / PCF85063A INT line)
     * ========================================================================= */
    /* PCF85063A INT is Active LOW, open-drain */
    if (((rtcio_int_st & BIT(5)) != 0) || (rtc_int == 0)) {
        REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
        ulp_riscv_gpio_wakeup_clear();
        last_wake_btn   = 0; /* Woken by external RTC timer */
        dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
        exit_ccount = ULP_RISCV_GET_CCOUNT();
        ulp_riscv_wakeup_main_processor();
        return 0;
    }

    /* Clear any other stray RTC GPIO status bits */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    ulp_riscv_gpio_wakeup_clear();

    /* =========================================================================
     * 3. Periodic Soft-Timer Telemetry & Guard (Flow A, e.g. 60s)
     * ========================================================================= */
    /* Battery ADC Guard (GPIO 4 / ADC1 Channel 3) */
    int32_t raw_adc = ulp_riscv_adc_read_channel(0, 3);
    if (raw_adc > 0) {
        uint32_t v_div_mv = (uint32_t)((raw_adc * (int64_t)cal_scale) / 4096);
        uint32_t v_bat_mv = (v_div_mv * 2) + cal_offset;
        last_vbat_mv = v_bat_mv;

        /* Zero-Volt Cable Guard: if v_bat_mv < 100mV, powered exclusively by USB VBUS without battery */
        if (v_bat_mv >= 100 && v_bat_mv < vbat_critical_mv) {
            dispatch_reason = 3; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
            exit_ccount = ULP_RISCV_GET_CCOUNT();
            ulp_riscv_wakeup_main_processor();
            return 0;
        }
    }

    /* Flow A Periodic Sensor Sample Burst */
    last_wake_btn   = 0;
    dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */
    exit_ccount = ULP_RISCV_GET_CCOUNT();
    ulp_riscv_wakeup_main_processor();

    return 0;
}
