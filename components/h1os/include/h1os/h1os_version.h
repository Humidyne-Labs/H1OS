/**
 * @file h1os_version.h
 * @brief H1OS semantic version information and inline getters
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define H1OS_VERSION_MAJOR   2             /**< Major version number (breaking API changes).          */
#define H1OS_VERSION_MINOR   4             /**< Minor version number (backward-compatible features).  */
#define H1OS_VERSION_PATCH   2             /**< Patch version number (backward-compatible bug fixes). */
#define H1OS_VERSION_TAG     "dev"         /**< Pre-release release track tag.                        */
#define H1OS_VERSION_STRING  "2.4.2-dev"   /**< Full human-readable semantic version string.          */

#define H1OS_NAME            "H1OS"                                   /**< Primary operating system designation. */
#define H1OS_SUBTITLE        "E-Class Environmental Operating System" /**< System commercial subtitle.           */

/**
 * @brief Helper macro to compute a 32-bit numeric version code.
 */
#define H1OS_VERSION_VAL(major, minor, patch) (((uint32_t)(major) << 16) | ((uint32_t)(minor) << 8) | (uint32_t)(patch))

/**
 * @brief Current H1OS version encoded as a single 32-bit unsigned integer: (MAJOR << 16) | (MINOR << 8) | PATCH
 * Example: 2.1.0 => 0x00020100.
 */
#define H1OS_VERSION_CODE    H1OS_VERSION_VAL(H1OS_VERSION_MAJOR, H1OS_VERSION_MINOR, H1OS_VERSION_PATCH)

/**
 * @brief Compile-time version check macro: true if current version >= specified version.
 */
#define H1OS_VERSION_CHECK(major, minor, patch) (H1OS_VERSION_CODE >= H1OS_VERSION_VAL(major, minor, patch))

#define H1OS_BUILD_DATE      __DATE__  /**< Compilation build date string. */
#define H1OS_BUILD_TIME      __TIME__  /**< Compilation build time string. */

/**
 * @brief Get major version integer.
 * @return Major version.
 */
static inline uint32_t h1os_version_get_major(void)
{
    return H1OS_VERSION_MAJOR;
}

/**
 * @brief Get minor version integer.
 * @return Minor version.
 */
static inline uint32_t h1os_version_get_minor(void)
{
    return H1OS_VERSION_MINOR;
}

/**
 * @brief Get patch version integer.
 * @return Patch version.
 */
static inline uint32_t h1os_version_get_patch(void)
{
    return H1OS_VERSION_PATCH;
}

/**
 * @brief Get version tag string.
 * @return Release tag string (e.g. "alpha").
 */
static inline const char *h1os_version_get_tag(void)
{
    return H1OS_VERSION_TAG;
}

/**
 * @brief Get complete version string.
 * @return Full version string (e.g. "2.4.0-dev").
 */
static inline const char *h1os_version_get_string(void)
{
    return H1OS_VERSION_STRING;
}

/**
 * @brief Get 32-bit packed numeric version code.
 * @return 32-bit version code.
 */
static inline uint32_t h1os_version_get_code(void)
{
    return H1OS_VERSION_CODE;
}

/**
 * @brief Get build date string.
 * @return Build date string.
 */
static inline const char *h1os_version_get_build_date(void)
{
    return H1OS_BUILD_DATE;
}

/**
 * @brief Get build time string.
 * @return Build time string.
 */
static inline const char *h1os_version_get_build_time(void)
{
    return H1OS_BUILD_TIME;
}

#ifdef __cplusplus
}
#endif
