# RFC: Application Error Propagation & Battery Safe-Shutdown Architecture

## 1. Overview & Problem Statement

In battery-powered embedded systems like H1OS (ESP32-S3), fatal initialization failures in `app_main()` or `h1os_start()` pose severe hardware hazards if not handled defensively:
* If `h1os_start()` encounters an unrecoverable configuration or peripheral error and returns an `esp_err_t` without further action, `app_main()` terminates in FreeRTOS.
* The Xtensa CPU and peripheral rails remain powered at 80/240 MHz (drawing 30–50 mA continuously).
* On an unmonitored LiPo battery, this causes complete cell depletion down to 0V within hours, permanently damaging or bricking the battery.

This document isolates the discussion and future design for structured error propagation, lifecycle error hooks, and emergency safe-shutdown fallbacks.

---

## 2. Immediate Policy & Developer Contract

> **Contractual Mandate:** Always check return values.
> 
> In H1OS, functions returning `esp_err_t` must never have their return values discarded. If `h1os_start()` returns an error, the application has failed bringup. Callers must assert or safely halt:
> ```c
> esp_err_t err = h1os_start(&lifecycle);
> if (err != ESP_OK) {
>     ESP_LOGE(TAG, "Fatal H1OS lifecycle bringup failure: %s", esp_err_to_name(err));
>     // Application-specific emergency halt or power release
> }
> ```

---

## 3. Future Architectural Proposals for Discussion

### Proposal 1: Lifecycle Error Callback (`on_error`)
Add an optional callback to `h1os_lifecycle_t`:
```c
typedef void (*h1os_error_hook_t)(esp_err_t error_code, const char *error_phase, void *user_data);

typedef struct {
    h1os_session_config_t session;
    h1os_presentation_config_t presentation;
    h1os_wake_hook_t on_wake;
    h1os_pre_sleep_hook_t on_pre_sleep;
    h1os_shutdown_hook_t on_shutdown;
    h1os_error_hook_t on_error; /**< Optional: Dispatched on fatal startup failure. */
    void *user_data;
} h1os_lifecycle_t;
```
**Benefits:** Allows applications to record diagnostics to an SD card panic file, drive an error blink code, or push telemetry before shutdown.

### Proposal 2: Hardware Battery Protection Fallback
If `h1os_start()` encounters a fatal bringup error on battery power (USB disconnected):
* Clear all display and peripheral rails.
* Release the `BAT_CTRL` (GPIO 17) power latch to immediately cut system power, or enter low-power deep sleep (e.g. 1 hour retry) to prevent LiPo over-discharge.

### Proposal 3: Dedicated Error Module (`h1os_error.c` / `h1os_error.h`)
Encapsulate error codes, human-readable fault descriptions, and panic dumps into a dedicated module rather than cluttering `h1os_lifecycle.c`.

---

## 4. Status & Roadmap
* **Status:** Parked for future milestone review.
* **Current Focus:** Completion of `MANDATE-02` (Dynamic Flow Periods API & Single Variable Time Architecture).
