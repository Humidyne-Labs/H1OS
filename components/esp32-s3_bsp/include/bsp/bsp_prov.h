/**
 * @file bsp_prov.h
 * @brief Turnkey BLE GATT Wi-Fi Provisioning & QR Code Generator
 *
 * Features:
 *  - BLE GATT Wi-Fi Provisioning with automatic device name / PoP generation
 *  - Standard QR Code payload builder for mobile / Chrome web dashboards
 *  - Direct LVGL QR Code Widget Renderer on 200x200 1-bit E-Paper Display
 *  - UI Status Callbacks (Start, Credentials Received, Success, Failure)
 *
 * Hardware Target:
 *  - Microcontroller: Espressif Systems ESP32-S3-PICO-1-N8R8
 *  - Target Board: Waveshare ESP32-S3 ePaper 1.54 V2
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_PROV_H
#define BSP_PROV_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provisioning Event Types
 */
typedef enum {
    BSP_PROV_EVENT_STARTED        = 0, ///< BLE advertising started
    BSP_PROV_EVENT_CRED_RECEIVED  = 1, ///< Wi-Fi SSID / Password received from client
    BSP_PROV_EVENT_CRED_SUCCESS   = 2, ///< Station successfully associated
    BSP_PROV_EVENT_CRED_FAILED    = 3, ///< Station association failed
    BSP_PROV_EVENT_FINISHED       = 4, ///< Provisioning ended, BLE de-initialized
} bsp_prov_event_t;

/**
 * @brief Provisioning Status Callback
 */
typedef void (*bsp_prov_event_cb_t)(bsp_prov_event_t event, void *event_data, void *user_data);

/**
 * @brief Start BLE GATT Wi-Fi Provisioning Service
 *
 * @param[in] custom_service_name Optional custom name (pass NULL for default "PROV_ESP32S3-XXXX")
 * @param[in] pop Optional Proof-of-Possession string (pass NULL for open pairing)
 * @param[in] cb Event callback function pointer
 * @param[in] user_data Optional user context
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_prov_start(const char *custom_service_name, const char *pop, bsp_prov_event_cb_t cb, void *user_data);

/**
 * @brief Check if Provisioning is currently active
 *
 * @return true if BLE is advertising/provisioning
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
bool bsp_prov_is_running(void);

/**
 * @brief Stop Provisioning Service and release Bluetooth memory
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
void bsp_prov_stop(void);

/**
 * @brief Generate JSON QR Code Payload string for standard Espressif Provisioning apps
 *
 * @param[in] pop Proof-of-Possession PIN (or NULL)
 * @param[out] dest Destination string buffer
 * @param[in] max_len Buffer size
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_prov_get_qr_payload(const char *pop, char *dest, size_t max_len);

#ifdef __cplusplus
}
#endif

#endif /* BSP_PROV_H */
