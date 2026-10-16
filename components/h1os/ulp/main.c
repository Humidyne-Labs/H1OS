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

/* Exported variables accessible by the main Xtensa core via ulp_<var> */
uint32_t wake_counter    = 0;
uint32_t dispatch_reason = 0; /* 0: None, 1: Sensor Sample, 2: Main Wake, 3: Critical Shutdown */

/* Battery Calibration Parameters (Provided by main core from eFuses) */
uint32_t cal_scale        = 1000;
int32_t  cal_offset       = 0;
uint32_t last_vbat_mv     = 4000;
uint32_t vbat_critical_mv = 3250; /* Critical brownout threshold (< 3.25V) */

/* Button State Tracking */
uint32_t boot_btn_events = 0;
uint32_t last_wake_btn   = 0; /* 0: None/RTC, 1: BOOT (GPIO 0), 2: POWER (GPIO 18) */

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
    wake_counter++;

    /* Initialize and enable input buffers for RTC GPIOs in the ULP domain */
    ulp_riscv_gpio_init(GPIO_NUM_5);
    ulp_riscv_gpio_input_enable(GPIO_NUM_5);
    ulp_riscv_gpio_init(GPIO_NUM_0);
    ulp_riscv_gpio_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_init(GPIO_NUM_18);
    ulp_riscv_gpio_input_enable(GPIO_NUM_18);

    /* 1. Hardware RTC Arbitration (GPIO 5 / PCF85063A Alarm INT) */
    /* PCF85063A INT is Active LOW */
    int rtc_int_level = ulp_riscv_gpio_get_level(GPIO_NUM_5);
    if (rtc_int_level == 0) {
        /* Alarm expired! Prompt main core straight into Full UI Refresh */
        last_wake_btn   = 0; /* Woken by external RTC  */
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

        /* Zero-Volt Cable Guard: if v_bat_mv < 100mV, powered exclusively by USB VBUS without battery */
        if (v_bat_mv >= 100 && v_bat_mv < vbat_critical_mv) {
            /* Brownout threshold reached! Wake CPU immediately to show emergency screen & latch off */
            dispatch_reason = 3; /* ULP_DISPATCH_CRITICAL_SHUTDOWN */
            ulp_riscv_wakeup_main_processor();
            return 0;
        }
    }

    /* 3. Button Check (GPIO 0: BOOT0, GPIO 18: BAT_KEY) */
    /* Wake-on-Release Rule: Wake Xtensa strictly when the button transitions back HIGH */
    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);

    if (boot_btn == 0 || pwr_btn == 0) {
        /* Record which button was depressed initially */
        int pressed_btn = (boot_btn == 0) ? 1 : 2;

        /* Button is held down. Track hold duration and wait for release. */
        uint32_t hold_ms = 0;
        while (hold_ms < 2600) {
            ulp_riscv_delay_cycles(10 * ULP_RISCV_CYCLES_PER_MS); /* 10ms poll while depressed */
            hold_ms += 10;
            boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
            pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
            if (boot_btn != 0 && pwr_btn != 0) {
                /* Clean release detected! */
                break;
            }
        }

        if (hold_ms >= 2500) {
            if (pressed_btn == 1) {
                /* BOOT held > 2.5s: Prime ROM Bootloader jump */
                dispatch_reason = 4; /* ULP_DISPATCH_BOOTLOADER_JUMP */
            } else {
                /* POWER held > 2.5s: Prime Power Off */
                dispatch_reason = 5; /* ULP_DISPATCH_POWER_OFF */
            }
            ulp_riscv_wakeup_main_processor();
            return 0;
        } else if (hold_ms >= 30) {
            /* Valid short tap released between 30ms and 2500ms -> Wake Flow B with clean released state */
            boot_btn_events++;
            last_wake_btn   = pressed_btn;
            dispatch_reason = 2; /* ULP_DISPATCH_MAIN_WAKE */
            ulp_riscv_wakeup_main_processor();
            return 0;
        }
        /* Pulse < 30ms discarded as glitch */
        return 0;
    }

    /* Default: Sensor sample wake stub */
    dispatch_reason = 1; /* ULP_DISPATCH_SENSOR_SAMPLE */
    ulp_riscv_wakeup_main_processor();

    return 0;
}
