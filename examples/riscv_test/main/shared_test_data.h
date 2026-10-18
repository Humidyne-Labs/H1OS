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

/* Checkpoints for breadcrumb debugging inside ULP firmware */
#define ULP_CP_ENTERED_MAIN      1
#define ULP_CP_ISR_REGISTERED    2
#define ULP_CP_PINS_SAMPLED      3
#define ULP_CP_WAITING_RDY       4
#define ULP_CP_RDY_CONFIRMED     5
#define ULP_CP_WAKE_SIGNALED     6
#define ULP_CP_CDC_CLEARED       7
#define ULP_CP_HALTED            8

typedef struct {
    uint32_t magic;
    uint32_t test_stage;            /* 1: Event, 2: Timer, 3: Dual */
    uint32_t ulp_entry_count;       /* Total times ULP executed main() */
    uint32_t ulp_gpio_wake_count;   /* Wakes with non-zero RTC GPIO status */
    uint32_t ulp_timer_wake_count;  /* Wakes with zero RTC GPIO status (timer) */
    uint32_t ulp_isr_fired_count;   /* Total times registered ISR executed */
    uint32_t ulp_last_isr_source;   /* GPIO number that triggered the last ISR */
    uint32_t ulp_last_gpio_status;  /* Raw RTC_GPIO_STATUS_REG */
    uint32_t ulp_pin_levels;        /* Bit 0: GPIO18 (PWR), Bit 1: GPIO0 (BOOT) */
    uint32_t ulp_cycle_count;       /* Execution duration in core cycles */
    uint32_t ulp_step_checkpoint;   /* Breadcrumb checkpoint reaching within ULP main */
    uint32_t ulp_rdy_timeout;       /* 1 if RDY_FOR_WAKEUP poll timed out */
    uint32_t ulp_completed;         /* Set to 1 when ULP successfully ran dispatch */
} test_shared_data_t;
