/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ULP-RISC-V Coprocessor Wakeup Validation Firmware
 *
 * Implements 3 test scenarios with active ISR handlers:
 *   1. Timer Mode (PMU countdown timer only, RTC GPIO wakeup disabled)
 *   2. Event Mode (RTC GPIO wakeup only, PMU timer disabled)
 *   3. Dual Mode  (PMU timer + RTC GPIO wakeups armed concurrently)
 */

#include <stdint.h>
#include <stdbool.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_interrupt.h"
#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "shared_test_data.h"

/* Exported shared telemetry structure (accessible via ulp_test_data on Main CPU) */
volatile test_shared_data_t test_data = {
    .magic = ULP_TEST_MAGIC,
    .test_stage = TEST_MODE_UNINITIALIZED,
    .ulp_entry_count = 0,
    .ulp_gpio_wake_count = 0,
    .ulp_timer_wake_count = 0,
    .ulp_isr_fired_count = 0,
    .ulp_last_isr_source = 0xFF,
    .ulp_last_gpio_status = 0,
    .ulp_pin_levels = 0,
    .ulp_cycle_count = 0,
    .ulp_step_checkpoint = 0,
    .ulp_rdy_timeout = 0,
    .ulp_completed = 0
};

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
static void gpio18_isr(void *arg)
{
    test_data.ulp_isr_fired_count++;
    test_data.ulp_last_isr_source = 18;
}
#endif

int main(void)
{
    test_data.ulp_entry_count++;
    test_data.ulp_rdy_timeout = 0;
    test_data.ulp_step_checkpoint = ULP_CP_ENTERED_MAIN;
    uint32_t start_c = ULP_RISCV_GET_CCOUNT();

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
    /* Register RTC GPIO ISR handlers only on the first entry.
     * The handler table resides in ULP .bss/.data which persists across wakes;
     * re-registering on subsequent entries returns ESP_ERR_NOT_FOUND (slot exhaustion).
     */
    if (test_data.ulp_entry_count == 1) {
        ulp_riscv_gpio_isr_register(GPIO_NUM_18, ULP_RISCV_GPIO_INTR_LOW_LEVEL, gpio18_isr, NULL);
    }
    test_data.ulp_step_checkpoint = ULP_CP_ISR_REGISTERED;
#endif

    /* 1. Snapshot raw RTC IO interrupt status register */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    test_data.ulp_last_gpio_status = rtcio_int_st;

    /* 2. Sample live levels of tested RTC GPIO lines:
     *    Bit 0: GPIO 18 (PWR button)
     *    Bit 1: GPIO 0  (BOOT button - monitoring only)
     */
    int b18 = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    int b0  = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    test_data.ulp_pin_levels = ((b18 ? 1U : 0U) | ((b0 ? 1U : 0U) << 1));
    test_data.ulp_step_checkpoint = ULP_CP_PINS_SAMPLED;

    /* 3. Classify wakeup cause */
    if (rtcio_int_st != 0 || b18 == 0) {
        test_data.ulp_gpio_wake_count++;
    } else {
        test_data.ulp_timer_wake_count++;
    }

    test_data.ulp_cycle_count = ULP_RISCV_GET_CCOUNT() - start_c;

    asm volatile("fence" ::: "memory");

    /* 4. Hand off execution: Wait for Main CPU ready with bounded timeout and idle check.
     * Prevents infinite loop if main CPU was awake or low power state is delayed.
     */
    test_data.ulp_step_checkpoint = ULP_CP_WAITING_RDY;
    uint32_t t0 = ULP_RISCV_GET_CCOUNT();
    while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)) {
        if (REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_MAIN_STATE_IN_IDLE)
            || (ULP_RISCV_GET_CCOUNT() - t0) > 1000000) {
            test_data.ulp_completed = 2; /* "woke too early / main not sleeping" signature */
            test_data.ulp_rdy_timeout = 1;
            ulp_riscv_halt();
            return 0;
        }
    }

    test_data.ulp_step_checkpoint = ULP_CP_RDY_CONFIRMED;
    test_data.ulp_step_checkpoint = ULP_CP_WAKE_SIGNALED;
    ulp_riscv_wakeup_main_processor();
    test_data.ulp_completed = 1;

    /* 5. Clear RTC GPIO wake latch with conservative 120us CDC pulse (>16 cycles on 136kHz RC) */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    ulp_riscv_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    test_data.ulp_step_checkpoint = ULP_CP_CDC_CLEARED;

    /* 6. Halt coprocessor and enter sleep */
    test_data.ulp_step_checkpoint = ULP_CP_HALTED;
    ulp_riscv_halt();
    return 0;
}
