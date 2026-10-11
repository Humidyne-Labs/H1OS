/**
 * @file bsp_env_telemetry.h
 * @brief Persistent Environmental Telemetry & Sample Ring Buffer in RTC Slow Memory
 *
 * Defines the persistent sample ring buffer and raw sensor telemetry structures retained in
 * RTC Slow SRAM across deep sleep cycles.
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_ENV_TELEMETRY_H
#define BSP_ENV_TELEMETRY_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_ENV_SAMPLE_RING_CAPACITY 64
#define BSP_ENV_TELEMETRY_MAGIC      0x56415052 /* "VAPR" */

/**
 * @brief Environmental Telemetry and Thermal State Flags
 */
typedef enum {
    BSP_ENV_FLAG_IDLE            = 0,
    BSP_ENV_FLAG_VALID_SAMPLE    = (1 << 0), ///< Sample passed CRC validation and acquisition checks
    BSP_ENV_FLAG_SUBSTRATE_HOT   = (1 << 1), ///< Board substrate temperature perturbed above ambient
    BSP_ENV_FLAG_LOCKOUT_ACTIVE  = (1 << 2), ///< Thermal lockout window active
    BSP_ENV_FLAG_CLEAN_SLOT      = (1 << 3), ///< Thermally settled clean slot (|Delta T| <= margin)
    BSP_ENV_FLAG_ENV_SPIKE       = (1 << 4), ///< Environmental transient verified by on-glass sensor
} bsp_env_sample_flags_t;

/**
 * @brief 4-Byte Compact Raw Sensor Sample in RTC Slow Memory
 */
typedef struct __attribute__((packed)) {
    uint16_t raw_temp_u16;      ///< SHTC3 Raw 16-bit Temperature word
    uint16_t raw_rh_u16;        ///< SHTC3 Raw 16-bit Relative Humidity word
} bsp_env_compact_sample_t;

/**
 * @brief Persistent Environmental Telemetry History in RTC Slow Memory (288 Bytes Total)
 */
typedef struct __attribute__((packed)) {
    uint32_t magic;                                                 ///< Validation token (BSP_ENV_TELEMETRY_MAGIC)
    volatile uint32_t ctrl_flags;                                   ///< Substrate & Lockout State Flags
    uint32_t head_index;                                            ///< Next write index in circular buffer (0..63)
    uint32_t total_samples;                                         ///< Total monotonic samples captured
    uint32_t poll_interval_sec;                                     ///< Configured sampling cadence in seconds (default 60)
    uint32_t last_sample_timestamp_sec;                             ///< Epoch or uptime seconds of newest sample
    uint64_t window_clean_mask;                                     ///< 64-bit mask: Bit i = 1 if slot i is cold & settled
    bsp_env_compact_sample_t samples[BSP_ENV_SAMPLE_RING_CAPACITY]; ///< 64 slots * 4 bytes = 256 bytes
} bsp_env_telemetry_history_t;

#ifdef __cplusplus
}
#endif

#endif /* BSP_ENV_TELEMETRY_H */
