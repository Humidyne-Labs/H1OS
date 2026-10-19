/**
 * @file shared_test_data.h
 * @brief Shared test data definitions between Xtensa and ULP
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>

#define ULP_TEST_MAGIC 0x554C5032U

#define ULP_LOG_BUF_SIZE 1024U
#define ULP_LOG_BUF_MASK (ULP_LOG_BUF_SIZE - 1U)

typedef struct {
    uint32_t head;
    uint32_t tail;
    char buffer[ULP_LOG_BUF_SIZE];
} ulp_log_ring_buf_t;

typedef enum {
    TEST_MODE_UNINITIALIZED = 0,
    TEST_MODE_TIMER_ONLY = 1,
    TEST_MODE_EVENT_ONLY = 2,
    TEST_MODE_DUAL_BOTH = 3,
    TEST_MODE_COMPLETE = 4
} ulp_test_mode_t;

#define ULP_CP_ENTERED_MAIN 1
#define ULP_CP_ISR_REGISTERED 2
#define ULP_CP_PINS_SAMPLED 3
#define ULP_CP_WAITING_RDY 4
#define ULP_CP_RDY_CONFIRMED 5
#define ULP_CP_WAKE_SIGNALED 6
#define ULP_CP_CDC_CLEARED 7
#define ULP_CP_HALTED 8

typedef struct {
    uint32_t magic;
    uint32_t test_stage;
    uint32_t ulp_entry_count;
    uint32_t ulp_gpio_wake_count;
    uint32_t ulp_timer_wake_count;
    uint32_t ulp_isr_fired_count;
    uint32_t ulp_last_isr_source;
    uint32_t ulp_last_gpio_status;
    uint32_t ulp_pin_levels;
    uint32_t ulp_cycle_count;
    uint32_t ulp_step_checkpoint;
    uint32_t ulp_rdy_timeout;
    uint32_t ulp_completed;
    uint32_t sleep_start_rtc_ticks;
    uint32_t ulp_elapsed_rtc_ticks;
    uint32_t ulp_reg_timer_val;
    ulp_log_ring_buf_t log_buf;
} test_shared_data_t;
