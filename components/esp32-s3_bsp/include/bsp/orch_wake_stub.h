/**
 * @file orch_wake_stub.h
 * @brief Layer 3: RTC Fast Memory Deep Sleep Wake Stub (<3ms Flow A Sensor Sprint)
 *
 * Runs immediately upon deep sleep wakeup before the 2nd-stage bootloader
 * or FreeRTOS initializes. Captures SHTC3 telemetry in ~2.5ms and returns
 * directly to deep sleep, bypassing flash cache and dual-core startup.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Install the RTC deep sleep wake stub.
 * Called before entering deep sleep to arm the ultra-fast wake stub handler.
 */
void orch_wake_stub_install(void);

/**
 * @brief Master RTC Wake Stub entry function.
 * Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.
 */
void bsp_wake_stub(void);

#ifdef __cplusplus
}
#endif
