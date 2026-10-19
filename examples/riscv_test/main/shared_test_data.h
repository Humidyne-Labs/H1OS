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

#define ULP_TEST_MAGIC   0x554C5032U /**< Magic validation word for ULP verification tests. */

#define ULP_LOG_BUF_SIZE 1024U       /**< Capacity of ULP text log ring buffer in bytes. */
#define ULP_LOG_BUF_MASK (ULP_LOG_BUF_SIZE - 1U) /**< Bitmask for fast circular indexing. */

/**
 * @brief Ring buffer structure for passing debug logs from ULP to Xtensa host.
 */
typedef struct {
    uint32_t head;                     /**< Write head index updated by ULP. */
    uint32_t tail;                     /**< Read tail index updated by Xtensa. */
    char     buffer[ULP_LOG_BUF_SIZE]; /**< Raw circular character buffer. */
} ulp_log_ring_buf_t;

/**
 * @brief Operating test verification mode opcodes.
 */
typedef enum {
    TEST_MODE_UNINITIALIZED = 0, /**< Harness uninitialized. */
    TEST_MODE_TIMER_ONLY    = 1, /**< Verify hardware timer wake only. */
    TEST_MODE_EVENT_ONLY    = 2, /**< Verify GPIO event interrupt wake only. */
    TEST_MODE_DUAL_BOTH     = 3, /**< Verify combined timer + event wakes. */
    TEST_MODE_COMPLETE      = 4  /**< Test execution complete. */
} ulp_test_mode_t;

#define ULP_CP_ENTERED_MAIN     1 /**< Checkpoint: ULP entered main function. */
#define ULP_CP_ISR_REGISTERED   2 /**< Checkpoint: GPIO interrupt handler registered. */
#define ULP_CP_PINS_SAMPLED     3 /**< Checkpoint: Initial wake pin state sampled. */
#define ULP_CP_WAITING_RDY      4 /**< Checkpoint: Waiting for Xtensa handoff ready. */
#define ULP_CP_RDY_CONFIRMED    5 /**< Checkpoint: Ready handshake confirmed. */
#define ULP_CP_WAKE_SIGNALED    6 /**< Checkpoint: Wake signal dispatched to main core. */
#define ULP_CP_CDC_CLEARED      7 /**< Checkpoint: Interrupt status cleared. */
#define ULP_CP_HALTED           8 /**< Checkpoint: ULP coprocessor halted. */

/**
 * @brief Shared memory communication block between Xtensa and ULP-RISC-V cores.
 */
typedef struct {
    uint32_t           magic;                 /**< Validation magic word (ULP_TEST_MAGIC). */
    uint32_t           test_stage;            /**< Active test stage index. */
    uint32_t           ulp_entry_count;       /**< Total entries into ULP code. */
    uint32_t           ulp_gpio_wake_count;   /**< Total wakes triggered by GPIO interrupt. */
    uint32_t           ulp_timer_wake_count;  /**< Total wakes triggered by RTC timer. */
    uint32_t           ulp_isr_fired_count;   /**< Total interrupt service routine executions. */
    uint32_t           ulp_last_isr_source;   /**< Interrupt source register snapshot. */
    uint32_t           ulp_last_gpio_status;  /**< Raw GPIO interrupt status bits. */
    uint32_t           ulp_pin_levels;        /**< Sampled pin logic levels bitmap. */
    uint32_t           ulp_cycle_count;       /**< Monotonic execution cycle counter. */
    uint32_t           ulp_step_checkpoint;   /**< Most recent step checkpoint (ULP_CP_*). */
    uint32_t           ulp_rdy_timeout;       /**< Handshake timeout countdown. */
    uint32_t           ulp_completed;         /**< Test pass/completion flag. */
    uint32_t           sleep_start_rtc_ticks; /**< RTC slow clock timestamp at sleep entry. */
    uint32_t           ulp_elapsed_rtc_ticks; /**< Measured sleep duration in RTC ticks. */
    uint32_t           ulp_reg_timer_val;     /**< Snapshot of PCF85063 timer register. */
    ulp_log_ring_buf_t log_buf;               /**< Embedded debug log ring buffer. */
} test_shared_data_t;
