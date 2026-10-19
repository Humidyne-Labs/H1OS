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

#define H1OS_VERSION_MAJOR 2
#define H1OS_VERSION_MINOR 1
#define H1OS_VERSION_PATCH 0
#define H1OS_VERSION_TAG "alpha"
#define H1OS_VERSION_STRING "2.1.0-alpha"

#define H1OS_NAME "H1OS"
#define H1OS_SUBTITLE "E-Class Environmental Operating System"

#define H1OS_VERSION_VAL(major, minor, patch) (((uint32_t)(major) << 16) | ((uint32_t)(minor) << 8) | (uint32_t)(patch))

#define H1OS_VERSION_CODE H1OS_VERSION_VAL(H1OS_VERSION_MAJOR, H1OS_VERSION_MINOR, H1OS_VERSION_PATCH)

#define H1OS_VERSION_CHECK(major, minor, patch) (H1OS_VERSION_CODE >= H1OS_VERSION_VAL(major, minor, patch))

#define H1OS_BUILD_DATE __DATE__
#define H1OS_BUILD_TIME __TIME__

static inline uint32_t h1os_version_get_major(void)
{
    return H1OS_VERSION_MAJOR;
}

static inline uint32_t h1os_version_get_minor(void)
{
    return H1OS_VERSION_MINOR;
}

static inline uint32_t h1os_version_get_patch(void)
{
    return H1OS_VERSION_PATCH;
}

static inline const char *h1os_version_get_tag(void)
{
    return H1OS_VERSION_TAG;
}

static inline const char *h1os_version_get_string(void)
{
    return H1OS_VERSION_STRING;
}

static inline uint32_t h1os_version_get_code(void)
{
    return H1OS_VERSION_CODE;
}

static inline const char *h1os_version_get_build_date(void)
{
    return H1OS_BUILD_DATE;
}

static inline const char *h1os_version_get_build_time(void)
{
    return H1OS_BUILD_TIME;
}

#ifdef __cplusplus
}
#endif
