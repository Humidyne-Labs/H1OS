/**
 * @file h1os_version.h
 * @brief H1OS Semantic Version Information & Inline Getters
 *
 * Provides standardized version macros, comparison gates, build metadata,
 * and lightweight inline getters for application and middleware layers.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================
 * Semantic Version Components
 * ========================================================================= */
#define H1OS_VERSION_MAJOR 2
#define H1OS_VERSION_MINOR 1
#define H1OS_VERSION_PATCH 0
#define H1OS_VERSION_TAG "alpha"
#define H1OS_VERSION_STRING "2.1.0-alpha"

#define H1OS_NAME "H1OS"
#define H1OS_SUBTITLE "E-Class Environmental Operating System"

/**
 * @brief Helper macro to compute a 32-bit numeric version code.
 */
#define H1OS_VERSION_VAL(major, minor, patch)                                                      \
    (((uint32_t)(major) << 16) | ((uint32_t)(minor) << 8) | (uint32_t)(patch))

/**
 * @brief Current H1OS version encoded as a single 32-bit unsigned integer:
 * (MAJOR << 16) | (MINOR << 8) | PATCH
 * Example: 2.1.0 => 0x00020100
 */
#define H1OS_VERSION_CODE                                                                          \
    H1OS_VERSION_VAL(H1OS_VERSION_MAJOR, H1OS_VERSION_MINOR, H1OS_VERSION_PATCH)

/**
 * @brief Compile-time version check macro: true if current version >= specified version.
 */
#define H1OS_VERSION_CHECK(major, minor, patch)                                                    \
    (H1OS_VERSION_CODE >= H1OS_VERSION_VAL(major, minor, patch))

/* =========================================================================
 * Build Metadata
 * ========================================================================= */
#define H1OS_BUILD_DATE __DATE__
#define H1OS_BUILD_TIME __TIME__

/* =========================================================================
 * Quick Inline Version Getters
 * ========================================================================= */

/**
 * @brief Retrieve major version number (e.g. 2).
 */
static inline uint32_t h1os_version_get_major(void)
{
    return H1OS_VERSION_MAJOR;
}

/**
 * @brief Retrieve minor version number (e.g. 1).
 */
static inline uint32_t h1os_version_get_minor(void)
{
    return H1OS_VERSION_MINOR;
}

/**
 * @brief Retrieve patch version number (e.g. 0).
 */
static inline uint32_t h1os_version_get_patch(void)
{
    return H1OS_VERSION_PATCH;
}

/**
 * @brief Retrieve version tag string (e.g. "alpha", "prod", "rc1").
 */
static inline const char *h1os_version_get_tag(void)
{
    return H1OS_VERSION_TAG;
}

/**
 * @brief Retrieve full semantic version string (e.g. "2.1.0-alpha").
 */
static inline const char *h1os_version_get_string(void)
{
    return H1OS_VERSION_STRING;
}

/**
 * @brief Retrieve 32-bit numeric version code.
 */
static inline uint32_t h1os_version_get_code(void)
{
    return H1OS_VERSION_CODE;
}

/**
 * @brief Retrieve compiler build date string (e.g. "Oct 18 2026").
 */
static inline const char *h1os_version_get_build_date(void)
{
    return H1OS_BUILD_DATE;
}

/**
 * @brief Retrieve compiler build time string (e.g. "21:45:00").
 */
static inline const char *h1os_version_get_build_time(void)
{
    return H1OS_BUILD_TIME;
}

#ifdef __cplusplus
}
#endif
