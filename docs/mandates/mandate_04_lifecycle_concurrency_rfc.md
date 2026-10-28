# RFC: MANDATE-04 — Lifecycle State Machine, Wake Reason Architecture & LVGL Concurrency

## 1. Overview & Context

This dedicated discussion artifact captures **`MANDATE-04`** from `docs/audits/_docs/` for separate, in-depth evaluation. 

The mandate addresses two interrelated design aspects in the H1OS application lifecycle:
1. **Wake Reason & State Ambiguity:** How downstream applications determine whether a boot was an interactive user session, an unattended periodic display/network wake, or a cold power-on.
2. **LVGL Concurrency Window:** Whether and how `h1os_lvgl_lock()` should interact with application-defined network operations inside `on_wake()`.

---

## 2. Topic A: Lifecycle Wake State & State Counters

### Current Implementation
In `h1os.h`, `h1os_wake_context_t` exposes:
```c
typedef struct {
    esp_reset_reason_t reset_reason;
    uint32_t wakeup_causes;
    uint32_t boot_count;
    uint32_t deep_sleep_count;
    bool woke_from_button;
    uint8_t wake_button;
    uint32_t sleep_duration_sec;
    void *user_data;
} h1os_wake_context_t;
```

### The Problem
When the PCF85063A countdown alarm triggers Flow B (display/cloud wake), `woke_from_button` is `false`. However, `wakeup_causes` contains a raw ESP-IDF bitmask (`BIT(ESP_SLEEP_WAKEUP_ULP)` or `BIT(ESP_SLEEP_WAKEUP_EXT0)`), and the application has to deduce whether the wake was Flow B by inspecting internal variables or checking `!woke_from_button`.

### Architectural Proposals for Discussion
* **Option 1: Explicit Lifecycle State Enum**
  Add `h1os_wake_state_t` directly into `h1os_wake_context_t`:
  ```c
  typedef enum {
      H1OS_WAKE_STATE_BOOT = 0,            /**< Initial power-on / hardware reset.       */
      H1OS_WAKE_STATE_INTERACTIVE_SESSION, /**< User button actuation (BOOT/POWER key).  */
      H1OS_WAKE_STATE_RTC_FLOW_B,          /**< Unattended periodic RTC countdown wake.  */
  } h1os_wake_state_t;
  ```
* **Option 2: Explicit Monotonic State Counters**
  Provide dedicated counters for each wake domain:
  - `st->boot_count` (monotonic power-on count)
  - `st->wake_count` (monotonic deep sleep wake count)
  - `st->flow_b_counter` (monotonic Flow B display/cloud wake count)
  - `st->button_wake_count` (monotonic interactive button wake count)

---

## 3. Topic B: LVGL Concurrency & Network Burst Interaction

### Current Implementation
In `h1os_lifecycle.c:423–437`:
```c
h1os_lvgl_lock(1000);
s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
h1os_lvgl_unlock();

h1os_lvgl_start(5, 1);
```

### Key Technical Observations
1. **Core 1 Task Isn't Running Yet:** The LVGL worker task on Core 1 is spawned on line 436 (`h1os_lvgl_start`). During `on_wake()`, only Core 0 is executing; there is no secondary task mutating or rendering widgets.
2. **Network Burst Duration:** In a connected IoT application (like `humid1-os`), `on_wake()` on Flow B powers on Wi-Fi, performs SNTP sync, establishes an MQTTS TLS handshake, and publishes telemetry. This network sequence typically requires 2 to 5 seconds.
3. **Mutex Contention:** Holding `h1os_lvgl_lock(1000)` across `on_wake()` holds the UI mutex for the entire multi-second network duration. If an asynchronous timer or MQTT thread attempts `h1os_lvgl_lock(200)` to update a Wi-Fi or battery status icon, it fails due to timeout.

### Proposals for Future Resolution
* **Proposal A: Application-Managed UI Locking:**
  Do not acquire `h1os_lvgl_lock()` around `on_wake()`. Since the LVGL task is not running yet during initial widget setup, initial setup requires no lock. Any subsequent background mutations acquire `h1os_lvgl_lock(200)` explicitly.
* **Proposal B: Two-Phase Lifecycle Callback:**
  Split unattended wakes into two callbacks:
  1. `on_sync(&ctx, user_data)`: Runs network bursts on Core 0 with zero LVGL locks.
  2. `on_render(&ctx, user_data)`: Runs UI presentation updates under short, bounded LVGL locks.

---

## 4. Status

This RFC is reserved for standalone evaluation once the core self-containment, audio, timing, and storage mandates are finalized.
