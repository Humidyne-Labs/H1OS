# Architecture & Implementation Plan: Pure ULP-Mediated Wakeup System

## 1. Executive Summary & Root Cause Analysis

### The User Directive
> *"this is not correct. the associated docs 'should' state, only the ulp can wake the main application, report the wake type, so the main app can function."*

In accordance with [`docs/architecture/05_ulp.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/05_ulp.md), H1OS enforces a strict silicon boundary:
1. **The dual-core Xtensa CPU never wakes directly from raw GPIO lines or EXT1.**
2. **The ULP-RISC-V Coprocessor is the sole arbiter of all external and temporal wake sources during deep sleep.**
3. The ULP monitors hardware events, debounces buttons in RTC SRAM, enforces the **Wake-on-Release Rule**, and reports the exact event type via `ulp_dispatch_reason`.
4. Only when a valid, classified event occurs does the ULP call `ulp_riscv_wakeup_main_processor()` to wake the main application (`ESP_SLEEP_WAKEUP_ULP`).

### Why the ULP Was "Stuck Sound Asleep"
In previous commits, when direct EXT1 was suppressed, the ULP failed to wake on button presses due to three hardware configuration omissions:
1. **ULP Wakeup Source MUX Misconfiguration:** In `sub_power.c`, `ulp_riscv_config_and_run(&cfg)` was passed `ULP_RISCV_WAKEUP_SOURCE_TIMER`. In ESP-IDF, this initializes only the timer wakeup bit and leaves the hardware GPIO wakeup path disabled.
2. **Missing Pad Hold (`gpio_hold_en`):** On ESP32-S3, waking the ULP from deep sleep on GPIO lines requires pad isolation holds (`gpio_hold_en`) to keep the RTC IO sensing logic active while the digital core is unpowered.
3. **Missing Wakeup Latch Clear (`ulp_riscv_gpio_wakeup_clear()`):** In `components/h1os/ulp/main.c`, the level interrupt clear register `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` was never asserted, preventing subsequent edge/level detections.

---

## 2. Proposed Technical Changes

### A. Subsystem Power & Sleep Setup (`components/h1os/src/sub_power.c`)
1. **Configure Dual ULP Wakeup Sources:**
   Configure `RTC_CNTL_ULP_CP_TIMER_REG` with both `RTC_CNTL_ULP_CP_SLP_TIMER_EN` (for periodic Flow A sample intervals) and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` (for reactive button/RTC interrupts).
2. **Initialize Wakeup RTC GPIOs:**
   Configure `GPIO 0` (BOOT), `GPIO 18` (POWER), and `GPIO 5` (PCF85063A INT) with pullups and level wakeups:
   ```c
   gpio_config_t cfg = {
       .pin_bit_mask = (1ULL << HAL_PIN_BUTTON_BOOT) |
                       (1ULL << HAL_PIN_BUTTON_POWER) |
                       (1ULL << HAL_PIN_RTC_INT),
       .mode = GPIO_MODE_INPUT,
       .pull_up_en = GPIO_PULLUP_ENABLE,
       .pull_down_en = GPIO_PULLDOWN_DISABLE,
       .intr_type = GPIO_INTR_LOW_LEVEL,
   };
   gpio_config(&cfg);
   gpio_wakeup_enable(HAL_PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
   gpio_wakeup_enable(HAL_PIN_BUTTON_POWER, GPIO_INTR_LOW_LEVEL);
   gpio_wakeup_enable(HAL_PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);
   gpio_hold_en(HAL_PIN_BUTTON_BOOT);
   gpio_hold_en(HAL_PIN_BUTTON_POWER);
   gpio_hold_en(HAL_PIN_RTC_INT);
   ```
3. **Deep Sleep Entry:**
   - Call `esp_sleep_enable_ulp_wakeup()`.
   - Purge `esp_sleep_enable_ext1_wakeup()` entirely from deep sleep entry.
   - Keep RTC power domain powered (`ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON`).

### B. ULP Coprocessor Firmware (`components/h1os/ulp/main.c`)
1. **Interrupt Latch Management:**
   Call `ulp_riscv_gpio_wakeup_clear()` upon wake and release to ensure RTC hardware registers reset cleanly.
2. **Enforce Wake-on-Release Rule:**
   - Glitch filter: Ignore pulses $< 30\text{ms}$.
   - Short tap release ($30\text{ms} - 2500\text{ms}$): Wait until button transitions back to HIGH (released), set `ulp_dispatch_reason = ULP_DISPATCH_MAIN_WAKE` (2), record `ulp_last_wake_btn`, and wake main processor.
   - Hold $> 2.5\text{s}$ on BOOT0: Set `ulp_dispatch_reason = ULP_DISPATCH_BOOTLOADER_JUMP` (4) and wake main processor.
   - Hold $> 2.5\text{s}$ on POWER: Set `ulp_dispatch_reason = ULP_DISPATCH_POWER_OFF` (5) and wake main processor.
3. **Periodic Timer & Battery Checks:**
   - Check PCF85063A INT line (`GPIO 5` LOW) $\rightarrow$ `ULP_DISPATCH_MAIN_WAKE` (2).
   - Check Battery ADC: If $< 3.25\text{V}$ and not USB-powered $\rightarrow$ `ULP_DISPATCH_CRITICAL_SHUTDOWN` (3).
   - If timer expired with no button activity $\rightarrow$ `ULP_DISPATCH_SENSOR_SAMPLE` (1) for Flow A.

### C. Execution Flow Arbiter (`components/h1os/src/orch_flow.c`)
1. **Eliminate Raw EXT1 Handling:**
   Remove `causes & BIT(ESP_SLEEP_WAKEUP_EXT1)` block completely from `orch_flow_determine_wakeup()`.
2. **Pure ULP Dispatcher:**
   Evaluate wakeups strictly via `causes & BIT(ESP_SLEEP_WAKEUP_ULP)` and map `st->ulp_dispatch_reason`:
   - `ULP_DISPATCH_SENSOR_SAMPLE` $\rightarrow$ `ORCH_FLOW_A_SAMPLE` (Fast sensor burst in deep sleep).
   - `ULP_DISPATCH_MAIN_WAKE` $\rightarrow$ `ORCH_FLOW_B_MAIN_WAKE` (Interactive LVGL session).
   - `ULP_DISPATCH_BOOTLOADER_JUMP` $\rightarrow$ `ORCH_FLOW_BOOTLOADER_JUMP` (`RTC_CNTL_FORCE_DOWNLOAD_BOOT` + `esp_restart()`).
   - `ULP_DISPATCH_CRITICAL_SHUTDOWN` / `ULP_DISPATCH_POWER_OFF` $\rightarrow$ `ORCH_FLOW_CRITICAL_OFF`.

---

## 3. Implementation Checklist

| Phase | File | Planned Changes |
| :--- | :--- | :--- |
| **1** | `components/h1os/src/sub_power.c` | Configure dual ULP wakeup (timer + GPIO wakeup enable & pad holds). Remove EXT1 calls. |
| **2** | `components/h1os/ulp/main.c` | Add `ulp_riscv_gpio_wakeup_clear()`, enforce wake-on-release loop and button hold classification. |
| **3** | `components/h1os/src/orch_flow.c` | Remove `ESP_SLEEP_WAKEUP_EXT1` logic. Ensure only `ESP_SLEEP_WAKEUP_ULP` dispatches Flow B / Flow A / Bootloader. |
| **4** | Build & Verification | Clean build of `build_prod` and `build_dev`, size diagnostics, verify zero compiler errors or symbol warnings. |
