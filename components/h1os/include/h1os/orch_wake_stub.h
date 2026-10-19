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

void orch_wake_stub_install(void);

void bsp_wake_stub(void);

#ifdef __cplusplus
}
#endif
