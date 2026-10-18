### Implementation Plan Audit: Audio Handshake & External RTC/ULP Wake

The implementation plan provides a well-reasoned architectural foundation, but it contains **four critical silicon/hardware discrepancies** and **three firmware edge cases** that will cause runtime lockups, sleep blinding, or coprocessor wake storms on the ESP32-S3 and PCF85063A.

Approval should be **withheld** until the modifications detailed below are incorporated into `plan_audio_handshake_and_rtc_wake_remedy.md`.

---

### Critical Silicon & Firmware Defects

#### 1. ULP Wake Storm on Intermediate Slices (Phase 3 & Phase 4)

* **The Defect:** In Phase 3.2, the bounded drain loop (`while (gpio_get_level(HAL_PIN_RTC_INT) == 0)`) is added **only** to `orch_flow_transition_to_sleep()` on the main Xtensa core.
* **Silicon Reality:** On intermediate slices (ticks 1–4 of Flow A), the main CPU remains in deep sleep. The external PCF85063A pulse mode holds `GPIO 5` LOW for $\approx 15.625\text{ ms}$ ($1/64\text{ s}$ when clocked at 1 Hz or $1/60\text{ Hz}$). The ULP-RISC-V coprocessor wakes up, executes its C routine in $\approx 15\text{ to }30\ \mu\text{s}$, increments `slice_counter`, and shuts down.
* **Failure Mode:** Because deep sleep RTCIO wakeups are strictly level-sensitive (`GPIO_INTR_LOW_LEVEL`), if the ULP clears the interrupt and returns to sleep while the physical line is still LOW ($15.6\text{ ms}$ remaining), the PMU will immediately re-trigger the ULP thousands of times in a continuous loop. `ulp_slice_counter` will blow through ticks 1 through 5 in less than 20 ms.
* **Required Plan Modification:** In Section 3 (Phase 4.2), explicitly require the ULP assembly/C loop in `components/h1os/ulp/main.c` to poll `GPIO 5` until it returns HIGH (with a bounded loop count) before re-arming the wakeup comparator and calling `ulp_riscv_shutdown()`.

---

#### 2. APB-to-RTC Slow Clock Domain Crossing Under-Delay (Phase 4.1 & Diagram Step C6)

* **The Defect:** Diagram Step `C6` and Section 3 (Phase 4.1) specify: `Pulse RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR (10us hold)`.
* **Silicon Reality:** The main CPU core accesses registers over the APB bus (80 MHz), whereas the low-power latch logic resides in the `RTC_SLOW_CLK` domain. If using an external 32.768 kHz crystal, one slow clock cycle is $30.51\ \mu\text{s}$ (or $\approx 6.7\text{ to }7.4\ \mu\text{s}$ on the internal 136–150 kHz RC oscillator).
* **Failure Mode:** A $10\ \mu\text{s}$ pulse does not guarantee the minimum 2 slow-clock-cycle window required for CDC synchronizers. The edge latch will frequently fail to clear, leading to stale interrupt states.
* **Required Plan Modification:** Update the pulse hold time from $10\ \mu\text{s}$ to `esp_rom_delay_us(50)` across both the diagram and Phase 4.1 text.

---

#### 3. Automatic Disabling of `WAKEUP_ENA` on Clear (Phase 4.2)

* **The Defect:** Phase 4.2 instructs the ULP: *"When waking main processor, pulse WAKEUP_CLR and clear RTC_GPIO_STATUS_W1TC_REG to ensure clean handoff."*
* **Silicon Reality:** Per ESP32-S3 TRM Section 2.4, asserting `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` automatically clears `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` in hardware.
* **Failure Mode:** If the ULP pulses `WAKEUP_CLR` on an intermediate tick without re-asserting `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA = 1`, all subsequent GPIO wakeups to the ULP are permanently disabled.
* **Required Plan Modification:** Explicitly document that:
1. On intermediate slices handled solely by ULP, ULP must set `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA = 1` after releasing `WAKEUP_CLR` and waiting for line HIGH.
2. On full wakes handed off to Xtensa, Xtensa's `sub_power_enter_deep_sleep_mode()` is responsible for re-asserting `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA = 1`.



---

#### 4. Sleep Pad Isolation & Input Buffer Blinding (Section 2 & Phase 4)

* **The Defect:** The plan clears RTCIO registers but does not audit pad sleep settings (`SLP_IE` vs. `FUN_IE`) or verify that pad hold is released on wakeup inputs.
* **Silicon Reality:** When deep sleep pad isolation is engaged (`hal_io_isolate_sleep_pads()` / `esp_sleep_enable_gpio_switch()`), pads switch to their sleep configuration (`SLP_SEL = 1`). In this state, input buffers default to disabled (`SLP_IE = 0`). Furthermore, if `rtc_gpio_hold_en()` is active on `GPIO 5`, external voltage transitions cannot propagate to the RTC comparator.
* **Required Plan Modification:** Add an explicit requirement in Phase 4.1:
```c
/* Ensure pad hold is disabled and input buffer stays powered during sleep */
rtc_gpio_hold_dis(HAL_PIN_RTC_INT);
SET_PERI_REG_MASK(RTC_IO_TOUCH_PAD5_REG, RTC_IO_TOUCH_PAD5_FUN_IE_M | RTC_IO_TOUCH_PAD5_SLP_IE_M);
CLEAR_PERI_REG_MASK(RTC_IO_TOUCH_PAD5_REG, RTC_IO_TOUCH_PAD5_SLP_SEL_M);

```



---

### Logic & Configuration Refinements

| Component | Current Plan Statement | Issue / Silicon Constraint | Corrective Action |
| --- | --- | --- | --- |
| **PCF85063A Prescaler** | Flowchart R6: `Start Timer: clk_src | TE | TIE | TI_TP (0x17)` | `0x17` only applies to 1 Hz (`TCF=10b`). For $T > 255\text{ s}$ ($1/60\text{ Hz}$, `TCF=11b`), the value is `0x1F`. | Change label in flowchart and text to dynamically reference `(clk_src | 0x07)` instead of hardcoded `(0x17)`. |
| **Audio Init Timeout** | Phase 1.2: If `ulTaskNotifyTake` times out, log `ESP_LOGE` and fail safely. | If timeout occurs after task creation, the worker task remains active on Core 1 referencing a potentially deleted queue or invalid context. | Call `vTaskDelete(s_audio_task_handle)` and reset the handle to `NULL` before returning `ESP_ERR_TIMEOUT`. |
| **Control_2 Overwrite** | Root Cause B / Phase 2: `ctrl2 = (ctrl2 & ~(CTRL2_TF_MASK | CTRL2_AF_MASK)) | CTRL2_COF_OFF;` | Forcing `CTRL2_COF_OFF` during countdown re-arm unnecessarily modifies peripheral clock output registers. | Preserve bits 2:0 as read, clearing only bit 3 (`TF`) and bit 6 (`AF`), or ensure `CTRL2_COF_OFF` is an isolated compile-time macro (`0x07`). |
| **Peterson Spinlock** | Phase 4.2: Peterson lock on shared variables. | The Xtensa LX7 and ULP-RISC-V compilers handle memory ordering differently across the RTC Slow RAM interface. | Mark all Peterson flags and telemetry indices as `volatile uint32_t` and place memory barriers (`asm volatile("memw" ::: "memory")` on Xtensa; `asm volatile("fence" ::: "memory")` on RISC-V). |

---

### Verification and Approval Checklist

Before approving this implementation plan, update Section 4 of the Markdown to include the following concrete validation gates:

```markdown
- [ ] **CDC Hold Verification:** Scope or logic trace confirms `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` remains asserted for ≥ 50 µs.
- [ ] **ULP Drain Verification:** ULP firmware samples `GPIO 5 == 1` before re-enabling `WAKEUP_ENA` and executing `ulp_riscv_shutdown()`.
- [ ] **Pad State Audit:** Confirm `rtc_gpio_hold_dis()` is enforced on GPIO 5, 18, and 0 prior to `esp_deep_sleep_start()`.
- [ ] **Orphan Task Prevention:** Induce forced timeout in `sub_audio_init()` unit test; confirm memory and task handle are freed cleanly.
- [ ] **Prescaler Math Check:** Unit test `sub_rtc_arm_countdown()` across boundary values: 60s (`0x17`), 255s (`0x17`), and 300s (`0x1F`).

```

### Actionable Next Steps

1. Apply the text and diagram corrections for the $50\ \mu\text{s}$ CDC delay, dynamic prescaler mask, and ULP line-drain loop directly to `plan_audio_handshake_and_rtc_wake_remedy.md`.
2. Proceed with implementation in `components/h1os/src/sub_audio.c`, `sub_rtc.c`, `sub_power.c`, and `components/h1os/ulp/main.c`.