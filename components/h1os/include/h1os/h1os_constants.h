/**
 * @file h1os_constants.h
 * @brief Public architectural constants and default lifecycle presets for H1OS.
 *
 * @details Centralizes constants that cross multiple translation units or form
 *          part of the public application-facing operating system configuration contract.
 *          Component-internal operational parameters remain encapsulated within their
 *          respective driver source files.
 *
 * Copyright (c) 2026 Humidyne Labs
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @defgroup H1OS_Default_Config Default Presets for Application Lifecycle Configuration
 * @{
 */
#define H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC   30U    /**< Recommended default interactive session inactivity sleep timeout in seconds. */
#define H1OS_DEFAULT_FLOW_A_PERIOD_SEC        60U    /**< Recommended default Flow A headless sensor sample burst period in seconds.    */
#define H1OS_DEFAULT_FLOW_B_PERIOD_SEC        300U   /**< Recommended default Flow B unattended presentation refresh period in seconds. */
/** @} */

#ifdef __cplusplus
}
#endif
