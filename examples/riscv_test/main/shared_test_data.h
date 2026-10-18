#pragma once
#include <stdint.h>
#include <stdbool.h>

#define ULP_TEST_MAGIC 0x554C5032U /* "ULP2" */

typedef enum {
    TEST_MODE_UNINITIALIZED = 0,
    TEST_MODE_EVENT_ONLY    = 1,   /* Test 1: Pure Event Mode (RTC GPIO) */
    TEST_MODE_TIMER_ONLY    = 2,   /* Test 2: Pure Timer Mode (PMU Countdown) */
    TEST_MODE_DUAL_BOTH     = 3,   /* Test 3: Dual Mode (GPIO + Timer Concurrently) */
    TEST_MODE_COMPLETE      = 4
} ulp_test_mode_t;

typedef struct {
    uint32_t magic;
    uint32_t test_stage;            /* 1: Event, 2: Timer, 3: Dual */
    uint32_t ulp_entry_count;       /* Total times ULP executed main() */
    uint32_t ulp_gpio_wake_count;   /* Wakes with non-zero RTC GPIO status */
    uint32_t ulp_timer_wake_count;  /* Wakes with zero RTC GPIO status (timer) */
    uint32_t ulp_isr_fired_count;   /* Total times registered ISR executed */
    uint32_t ulp_last_isr_source;   /* GPIO number that triggered the last ISR */
    uint32_t ulp_last_gpio_status;  /* Raw RTC_GPIO_STATUS_REG */
    uint32_t ulp_pin_levels;        /* Bit 0: GPIO0, Bit 18: GPIO18 */
    uint32_t ulp_cycle_count;       /* Execution duration in core cycles */
    uint32_t ulp_completed;         /* Set to 1 when ULP successfully ran dispatch */
} test_shared_data_t;
