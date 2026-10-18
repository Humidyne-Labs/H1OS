# Plan: User-Comment Remediation, Blit Optimization & Battery Hardening

> **Status:** Revised per User Comments — Ready for Execution  
> **Source Files Under Review:**  
> - [`components/h1os/src/h1os_lvgl.cpp`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_lvgl.cpp)  
> - [`components/h1os/src/h1os_time.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_time.c)  
> - [`components/h1os/src/sub_power.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_power.c)  
> - [`components/h1os/include/h1os/sub_power.h`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/include/h1os/sub_power.h)  
> - [`components/h1os/include/h1os/orch_state.h`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/include/h1os/orch_state.h)  
> - [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c)  

---

## 1. Overview & Scope

This plan focuses strictly on runtime hardening, graphics performance optimization, and battery monitoring enhancements based on direct review comments:
1. **LVGL Framebuffer Blit Optimization (`h1os_lvgl.cpp`):** Replace per-pixel bit extraction loops with standard `memcpy()` on aligned scans and an 8-pixel-per-cycle streaming barrel shifter on unaligned scans.
2. **Time Services Hardening (`h1os_time.c`):** Harden input parameter validation, timezone string boundary checks, and safe error propagation without introducing test harness bloat into production sources.
3. **Cross-Processor Battery Buffer & Rapid Discharge Guard:** Leverage ULP piecewise-calibrated readings alongside Flow B updates into a shared circular buffer (`vbat_ring[8]`), equipped with an instantaneous $\Delta V$ rapid discharge hazard detector.

---

## 2. Workstream 1: LVGL 1-BPP Framebuffer Blit Optimization

### 2.1 Problem Analysis
In [`h1os_lvgl_flush_cb`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/h1os_lvgl.cpp#L98-L136):
- Fast path performs manual 32-bit copy loops with per-line pointer multiplication.
- Unaligned fallback processes individual pixels through nested loops with division (`px / 8`), modulo (`px % 8`), and read-modify-write memory operations.

### 2.2 Optimized Implementation Design
- **Fast Path (`(area->x1 & 7) == 0 && (area_w & 7) == 0`):**
  - Incremental pointer stepping: `src += src_stride`, `dst += epd_stride`.
  - Direct standard `memcpy(dst, src, bytes_per_line)`.
- **Unaligned Fallback:**
  - Upfront Y and X coordinate clipping against `EPD_WIDTH` and `EPD_HEIGHT`.
  - Shift-streaming accumulator:
    $$\text{val} = (\text{carry} \ll (8 - \text{shift})) \mid (\text{next} \gg \text{shift})$$
  - Merges edge bits via precomputed left and right bitmasks.

---

## 3. Workstream 2: System Time Services Hardening (`h1os_time.c`)

### 3.1 Hardening Invariants
1. **`h1os_time_set_timezone(const char *tz_str)`:**
   - Null and empty check: fall back cleanly to `"UTC"`.
   - Length validation: reject strings exceeding POSIX `TZ` buffer limits ($\le 64$ bytes).
2. **`h1os_time_register_sync_cb(cb, user_data)`:**
   - Allow safe dynamic registration and unregistration (passing `NULL` clears registration).
3. **`h1os_time_sync_now(timeout_ms)`:**
   - Return `ESP_ERR_NOT_SUPPORTED` cleanly when `s_sync_cb == NULL`.
   - Protect against re-entrant sync invocations with a lightweight atomic guard.
4. **`h1os_time_get_formatted()`:**
   - Enforce destination buffer null checks and `max_len > 0`.
   - Ensure strings are guaranteed null-terminated even on truncated output.

---

## 4. Workstream 3: Cross-Processor Battery Buffer & Discharge Detector

### 4.1 Cross-Processor Buffer Architecture
In [`orch_persisted_state_t`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/include/h1os/orch_state.h):
- Add a dedicated circular telemetry array:
  ```c
  #define ORCH_VBAT_RING_CAPACITY 8
  uint16_t vbat_ring[ORCH_VBAT_RING_CAPACITY];
  uint8_t  vbat_ring_head;
  uint8_t  vbat_samples_count;
  ```
- **ULP Updates:** On every Flow A tick and sleep-wake cycle, ULP samples ADC1 Channel 3, computes millivolts via `vbat_lut`, and writes into `vbat_ring[vbat_ring_head]`.
- **Flow B Updates:** When Flow B runs, the main CPU takes a single fast reading or reads ULP cache, appending to `vbat_ring`.

### 4.2 Rapid Discharge Detector (Hardware Brownout Guard)
- Compare the newest sample $V_{\text{new}}$ against the running average of previous valid samples $\bar{V}_{\text{prev}}$:
  $$\Delta V = \bar{V}_{\text{prev}} - V_{\text{new}}$$
- If $\Delta V > K_{\text{discharge}}$ (e.g. $> 150\text{ mV}$ within one polling window) while not on USB power:
  - System flags `ORCH_FLAG_BATTERY_FAULT`.
  - Triggers graceful shutdown or safe-state display warning to protect LiPo cells from deep destructive collapse.

---

## 5. Verification Matrix

| Check | Target | Verification Method |
| :--- | :--- | :--- |
| **Blit Speedup** | `h1os_lvgl.cpp` | Verify clean partial and full flushes without visual tearing or artifacting. |
| **Time Hardening** | `h1os_time.c` | Verify safe return codes on NULL callback and edge timezone inputs. |
| **Battery Tracking** | `sub_power.c` | Validate `vbat_ring` updates across Flow A and Flow B cycles. |
| **Compilation** | `build_prod` | 0 compiler warnings, 0 errors. |
