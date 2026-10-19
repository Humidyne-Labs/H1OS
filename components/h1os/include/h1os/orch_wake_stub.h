/**
 * @file orch_wake_stub.h
 * @brief Layer 3: RTC Fast Memory deep sleep wake stub (<3ms Flow A sample burst)
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Install the deep sleep wake stub into RTC Fast Memory.
 *
 * Registers bsp_wake_stub() with esp_set_deep_sleep_wake_stub().
 */
void orch_wake_stub_install(void);

/**
 * @brief Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.
 *
 * Executes fast sub-3ms Flow A sensor bursts using bitbanged I2C without booting the main
 * ESP-IDF OS or spinning up the 160/240 MHz PLL clocks.
 */
void bsp_wake_stub(void);

#ifdef __cplusplus
}
#endif
