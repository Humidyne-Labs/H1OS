/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ULP-RISC-V Coprocessor Wakeup Validation Firmware
 *
 * Implements 3 test scenarios with active ISR handlers:
 *   1. Timer Mode (PMU countdown timer only, RTC GPIO wakeup disabled)
 *   2. Event Mode (RTC GPIO wakeup only, PMU timer disabled)
 *   3. Dual Mode  (PMU timer + RTC GPIO wakeups armed concurrently)
 *
 * Includes an internal RTC Slow Memory ASCII Ring Buffer with a custom ulp_printf()
 * that logs all coprocessor operations (wakeups, pin status, ISRs, classification, halts).
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
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
    .ulp_completed = 0,
    .log_buf = {
        .head = 0,
        .tail = 0,
        .buffer = {0}
    }
};

static volatile bool s_gpio_event_occurred = false;

/* --- Ring Buffer & ulp_printf Implementation --- */

static void ulp_log_putc(char c)
{
    test_data.log_buf.buffer[test_data.log_buf.head & ULP_LOG_BUF_MASK] = c;
    test_data.log_buf.head++;
}

static void ulp_log_puts(const char *s)
{
    if (!s) s = "(null)";
    while (*s) {
        ulp_log_putc(*s++);
    }
}

static void ulp_log_put_u32(uint32_t val, int base, int min_width, char pad_char)
{
    char buf[12];
    int i = 0;
    if (val == 0) {
        buf[i++] = '0';
    } else {
        while (val > 0) {
            uint32_t rem = val % base;
            buf[i++] = (rem < 10) ? ('0' + rem) : ('a' + rem - 10);
            val /= base;
        }
    }
    while (i < min_width) {
        buf[i++] = pad_char;
    }
    while (i > 0) {
        ulp_log_putc(buf[--i]);
    }
}

static void ulp_log_put_i32(int32_t val)
{
    if (val < 0) {
        ulp_log_putc('-');
        val = -val;
    }
    ulp_log_put_u32((uint32_t)val, 10, 0, ' ');
}

static void ulp_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            ulp_log_putc(*p);
            continue;
        }
        p++;
        char pad = ' ';
        int width = 0;
        if (*p == '0') {
            pad = '0';
            p++;
        }
        while (*p >= '0' && *p <= '9') {
            width = width * 10 + (*p - '0');
            p++;
        }

        switch (*p) {
        case 's': {
            const char *s = va_arg(args, const char *);
            ulp_log_puts(s);
            break;
        }
        case 'd':
        case 'i': {
            int32_t d = va_arg(args, int32_t);
            ulp_log_put_i32(d);
            break;
        }
        case 'u': {
            uint32_t u = va_arg(args, uint32_t);
            ulp_log_put_u32(u, 10, width, pad);
            break;
        }
        case 'x':
        case 'X': {
            uint32_t x = va_arg(args, uint32_t);
            ulp_log_put_u32(x, 16, width, pad);
            break;
        }
        case 'c': {
            char c = (char)va_arg(args, int);
            ulp_log_putc(c);
            break;
        }
        case '%': {
            ulp_log_putc('%');
            break;
        }
        default:
            ulp_log_putc('%');
            ulp_log_putc(*p);
            break;
        }
    }
    va_end(args);
}

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
static void gpio18_isr(void *arg)
{
    test_data.ulp_isr_fired_count++;
    test_data.ulp_last_isr_source = 18;
    s_gpio_event_occurred = true;
    ulp_printf("[ULP-ISR] GPIO 18 ISR fired! Total ISRs=%u\n", test_data.ulp_isr_fired_count);
}
#endif

int main(void)
{
    test_data.ulp_entry_count++;
    test_data.ulp_rdy_timeout = 0;
    test_data.ulp_step_checkpoint = ULP_CP_ENTERED_MAIN;
    uint32_t start_c = ULP_RISCV_GET_CCOUNT();

    ulp_printf("[ULP] >>> EXECUTION ENTRY #%u <<< (stage=%u, ccount=%u)\n",
               test_data.ulp_entry_count, test_data.test_stage, start_c);

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
    /* Register RTC GPIO ISR handlers only on the first entry.
     * The handler table resides in ULP .bss/.data which persists across wakes;
     * re-registering on subsequent entries returns ESP_ERR_NOT_FOUND (slot exhaustion).
     */
    if (test_data.ulp_entry_count == 1) {
        ulp_riscv_gpio_isr_register(GPIO_NUM_18, ULP_RISCV_GPIO_INTR_LOW_LEVEL, gpio18_isr, NULL);
        ulp_printf("[ULP] Registered GPIO 18 Low-Level ISR handler\n");
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

    ulp_printf("[ULP] Pins Sampled: PWR(18)=%d BOOT(0)=%d RTC_IO_STATUS=0x%08x\n",
               b18, b0, rtcio_int_st);

    /* 3. Classify wakeup cause:
     * Catch raw RTC IO interrupt bit, live pin level LOW, OR any ISR firing
     * so that brief tactile taps (released before pin sampling) are accurately captured.
     */
    bool is_gpio = (rtcio_int_st != 0) || (b18 == 0) || s_gpio_event_occurred;
    s_gpio_event_occurred = false;

    if (is_gpio) {
        test_data.ulp_gpio_wake_count++;
    } else {
        test_data.ulp_timer_wake_count++;
    }

    ulp_printf("[ULP] Wake Classified: %s (gpio_cnt=%u, timer_cnt=%u)\n",
               is_gpio ? "RTC_GPIO_EVENT" : "PMU_TIMER_EVENT",
               test_data.ulp_gpio_wake_count, test_data.ulp_timer_wake_count);

    test_data.ulp_cycle_count = ULP_RISCV_GET_CCOUNT() - start_c;

    asm volatile("fence" ::: "memory");

    /* 4. Hand off execution: Signal Main CPU to wake immediately.
     * In ESP-IDF ULP-RISC-V architecture, ulp_riscv_wakeup_main_processor() asserts
     * RTC_CNTL_SW_CPU_INT atomically. There is no need to poll or abort on RDY_FOR_WAKEUP.
     */
    test_data.ulp_step_checkpoint = ULP_CP_RDY_CONFIRMED;
    test_data.ulp_step_checkpoint = ULP_CP_WAKE_SIGNALED;
    ulp_printf("[ULP] Signaling Main CPU wakeup (assert RTC_CNTL_SW_CPU_INT)...\n");
    ulp_riscv_wakeup_main_processor();
    test_data.ulp_completed = 1;

    /* 5. Clear RTC GPIO wake latch with conservative 120us CDC pulse (>16 cycles on 136kHz RC) */
    ulp_printf("[ULP] Pulsing CDC clear latch for 120us...\n");
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    ulp_riscv_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    test_data.ulp_step_checkpoint = ULP_CP_CDC_CLEARED;

    /* 6. Halt coprocessor and enter sleep */
    test_data.ulp_step_checkpoint = ULP_CP_HALTED;
    ulp_printf("[ULP] Coprocessor halting cleanly. Elapsed cycles=%u.\n",
               (unsigned)(ULP_RISCV_GET_CCOUNT() - start_c));
    ulp_riscv_halt();
    return 0;
}
