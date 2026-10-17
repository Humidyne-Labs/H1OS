# Action Plan: Repository Documentation Synchronization

This plan establishes a structured approach to updating the H1OS technical documentation across `docs/architecture/` and `docs/drivers/`, capturing all recent architectural shifts, hardware discoveries, and power-saving invariants.

---

## 1. Documentation Scope & Target Matrix

| Document | Target Section | Content to Add / Update |
| :--- | :--- | :--- |
| [`docs/architecture/05_ulp.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/05_ulp.md) | ULP Wakeup & State Flow | - Autonomous 24/7 reactive monitoring in RTC slow memory.<br>- Wakeup routing: `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` + `gpio_wakeup_enable()` wakes ULP coprocessor, keeping Xtensa cores asleep.<br>- Wake-on-Release debounce logic: waiting for pin to return HIGH before triggering `ulp_riscv_wakeup_main_processor()`.<br>- Exported RTC variables (`ulp_last_wake_btn`, `ulp_dispatch_reason`, `ulp_wake_counter`, `ulp_last_vbat_mv`). |
| [`docs/architecture/04_orchestrator.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/04_orchestrator.md) | Flow A & Flow B Separation | - Flow A: Fast sensor burst, populates 32-sample RTC ring buffer, sleeps immediately without powering audio codec or display controller.<br>- Flow B: Interactive UI session; never queries SHTC3 over I2C; reads ring buffer and pre-display glass thermistor.<br>- Standardized `0.0` / `0` centi-units as explicit uninitialized / NA telemetry state on cold boot.<br>- Modularity: extracted ring buffer serial hexdump to `orch_flow_dump_ring_debug()`. |
| [`docs/architecture/07_state_machine.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/07_state_machine.md) | Click Interaction & Power Lifecycle | - Two-Stage Click Interaction:<br>  * First Click in Deep Sleep: intercepted by ULP, wakes Flow B, toggles wake badge in UI without chime.<br>  * Second Click in Flow B: handled by LVGL keypad event callback, produces 15ms audio tick and navigates screens.<br>- Codec Sleep Gating: Codec/amp never initialized on unattended RTC wakeups (<1µA preserved).<br>- Strict Lifecycle Guards: Abort with error on `sleep_sec == 0` or `timeout_sec == 0` instead of silent fallback. |
| [`docs/architecture/08_lessons_learned.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/08_lessons_learned.md) | Thermal & Power Invariants | - Codec Heat Oscillation (26°C-32°C): Identified that waking the codec between periodic sample bursts dumped audio amplifier heat into the chassis. Resolved by strictly isolating audio init to user presence.<br>- Silent Fallback Pitfalls: Why hardcoded defaults (`300s`, `120s`, `25.0°C`) mask lifecycle bugs and why strict contract assertions are essential.<br>- Silicon GPIO Routing: Separating ULP RTC IO wakeup from Xtensa SoC wakeup. |
| [`docs/architecture/10_changelog.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/10_changelog.md) | Production Release Notes | - Document all recent improvements: ULP reactive monitor, two-stage click interaction, audio sleep isolation, NA telemetry indicators, and build tooling standardization. |
| [`docs/drivers/03_audio.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/drivers/03_audio.md) | Power Management & Volume | - Codec isolation invariant: ES8311 & NS4168 remain in deep sleep during unattended RTC wakeups.<br>- Volume initialization: tied strictly to lifecycle presentation (`volume_pct`), default `0%` (muted) until configured. |
| [`docs/drivers/04_epaper.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/drivers/04_epaper.md) | Temperature Reading | - Document SSD1681 Command `0x1B` Register Bitfield: Byte 0 (integer °C), Byte 1 Bit 7 ($2^{-1} = 0.5^\circ\text{C}$ fraction bit, 50 centi-degrees).<br>- Read timing: strictly before RAM writes or charge pump LUT operations to prevent refresh heat offset. |
| [`docs/drivers/06_sdcard.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/drivers/06_sdcard.md) | FatFS Mount Options | - Document `allocation_unit_size`: specifies formatting cluster size on blank cards; set to `0` for auto-allocation based on card geometry. |

---

## 2. Work Breakdown Packages

### Package 1: Architecture Core Documentation (`docs/architecture/`)
- Update `05_ulp.md` with complete ULP coprocessor timing, GPIO wakeup registers, and debounce logic.
- Update `04_orchestrator.md` with Flow A/B isolation, telemetry `0.0` NA conventions, and modular debug dumping.
- Update `07_state_machine.md` with two-stage click sequence and strict lifecycle duration guards.
- Update `08_lessons_learned.md` with the codec thermal oscillation root cause and silent fallback eradication.
- Update `10_changelog.md` with the latest release notes.

### Package 2: Peripheral Driver Documentation (`docs/drivers/`)
- Update `03_audio.md` with standby power gating and volume contract.
- Update `04_epaper.md` with SSD1681 Command `0x1B` 0.5°C fractional bit structure.
- Update `06_sdcard.md` with FatFS cluster allocation unit size clarification.

---

## 3. Jules & Multi-Branch Coordination

- Keep all markdown edits modular, additive, and tightly focused on the specific subsystems modified.
- Avoid modifying document headings or index anchors that other documentation branches (e.g. Jules's branch) might link against.
- Follow strict GitHub Flavored Markdown (GFM) as defined in `.agents/skills/gfm/SKILL.md`.

---

## 4. Verification

- Run markdown validation to ensure all internal links and references are valid.
- Verify that all code snippets match the implemented C/C++ and ULP RISC-V code.
