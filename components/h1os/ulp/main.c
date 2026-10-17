/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ePaper BSP - Minimal Proof-of-Life ULP Coprocessor
 *
 * Dedicated proof-of-life test:
 * Validates dual-wake arbitration (GPIO interrupts + periodic sleep timer)
 * without complex application dependencies.
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
volatile uint32_t dispatch_reason = 0;

/* Battery Calibration Parameters (Preserved for linker compatibility) */
volatile uint32_t cal_scale        = 1000;
volatile int32_t  cal_offset       = 0;
volatile uint32_t last_vbat_mv     = 4000;
volatile uint32_t vbat_critical_mv = 3250;

/* Button State Tracking */
volatile uint32_t boot_btn_events = 0;
volatile uint32_t last_wake_btn   = 0; /* 0: None/RTC/Timer, 1: BOOT (GPIO 0), 2: POWER (GPIO 18) */
volatile uint32_t cycles_per_ms   = 17500;

/* Telemetry & Observability */
volatile uint32_t last_wake_cause   = 0; /* 1: BOOT, 2: POWER, 3: TIMER, 4: RTC INT */
volatile uint32_t gpio_status_raw   = 0; /* RTC_GPIO_STATUS_INT */
volatile uint32_t hold_duration_ms  = 0;
volatile uint32_t loop_sample_count = 0;
volatile uint32_t entry_ccount      = 0;
volatile uint32_t exit_ccount       = 0;

#define ULP_TRACE_MAX 16
volatile uint32_t trace_count = 0;
volatile uint32_t trace_step[ULP_TRACE_MAX] = {0};
volatile uint32_t trace_val1[ULP_TRACE_MAX] = {0};
volatile uint32_t trace_val2[ULP_TRACE_MAX] = {0};

int main(void)
{
    /* 1. IMMEDIATELY snapshot RTC GPIO interrupt status upon core wake */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    gpio_status_raw = rtcio_int_st;
    wake_counter++;
    entry_ccount = ULP_RISCV_GET_CCOUNT();
    cycles_per_ms = 17500;
    hold_duration_ms = 0;
    loop_sample_count = 0;
    cal_scale = 1000;
    cal_offset = 0;
    vbat_critical_mv = 3250;
    last_vbat_mv = 4000;
    trace_count = 0;
    trace_step[0] = 0;
    trace_val1[0] = 0;
    trace_val2[0] = 0;

    /* 2. Configure input buffers to read live pin levels */
    ulp_riscv_gpio_init(GPIO_NUM_0);
    ulp_riscv_gpio_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_pullup_disable(GPIO_NUM_0);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_0);

    ulp_riscv_gpio_init(GPIO_NUM_18);
    ulp_riscv_gpio_input_enable(GPIO_NUM_18);
    ulp_riscv_gpio_pullup_disable(GPIO_NUM_18);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_18);

    ulp_riscv_gpio_init(GPIO_NUM_5);
    ulp_riscv_gpio_input_enable(GPIO_NUM_5);
    ulp_riscv_gpio_pullup(GPIO_NUM_5);
    ulp_riscv_gpio_pulldown_disable(GPIO_NUM_5);

    int boot_btn = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int pwr_btn  = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int rtc_int  = ulp_riscv_gpio_get_level(GPIO_NUM_5);

    /* 3. Determine wake cause */
    if (((rtcio_int_st & BIT(0)) != 0) || boot_btn == 0) {
        last_wake_cause = 1; /* BOOT Button (GPIO 0) */
        last_wake_btn   = 1;
        dispatch_reason = 2;
    } else if (((rtcio_int_st & BIT(18)) != 0) || pwr_btn == 0) {
        last_wake_cause = 2; /* POWER Button (GPIO 18) */
        last_wake_btn   = 2;
        dispatch_reason = 2;
    } else if (((rtcio_int_st & BIT(5)) != 0) || rtc_int == 0) {
        last_wake_cause = 4; /* RTC Alarm (GPIO 5) */
        last_wake_btn   = 0;
        dispatch_reason = 2;
    } else {
        last_wake_cause = 3; /* Periodic Timer Wake */
        last_wake_btn   = 0;
        dispatch_reason = 1;
    }

    /* 4. Clear status latch and ULP GPIO wake trigger */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

    /* 5. Wake Main CPU to verify proof-of-life */
    exit_ccount = ULP_RISCV_GET_CCOUNT();
    ulp_riscv_wakeup_main_processor();
    ulp_riscv_halt();
    return 0;
}
