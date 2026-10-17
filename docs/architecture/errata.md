# H1OS Hardware & Silicon Errata

## ERR-001: ESP32-S3 PMU Dual-Wake Coprocessor Block

- **Component:** ESP32-S3 Low-Power Controller (PMU / RTC Controller)
- **Subsystem:** ULP-RISC-V Coprocessor Wakeup Logic
- **Affects:** ESP32-S3-PICO-1-N8R8 (all silicon revisions)
- **Severity:** High (architectural blocking if unmitigated)

### Description
In ESP-IDF and the ESP32-S3 Technical Reference Manual, the ULP-RISC-V coprocessor supports two primary wakeup sources controlled via `RTC_CNTL_ULP_CP_TIMER_REG`:
1. `RTC_CNTL_ULP_CP_SLP_TIMER_EN` (bit 31) — Periodic countdown timer in `RTC_SLOW_CLK` ticks.
2. `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` (bit 29) — External RTC GPIO comparator edge/level event.

Hardware characterization reveals that when both bits are asserted simultaneously (`SLP_TIMER_EN | GPIO_WAKEUP_ENA`), the internal PMU state machine enters an internal arbitration lockup. While deep sleeping, the internal PMU timer countdown overrides and suppresses external RTC GPIO edge wakeups from releasing core clock gating during halt. As a consequence, the coprocessor responds solely to periodic timer ticks and ignores tactile button presses on GPIO 0 and GPIO 18.

### Mitigation & Architecture Mandate
To ensure deterministic sub-millisecond tactile wakeups and eliminate PMU timer collisions:
1. **Pure Event Mode:** The ULP coprocessor is configured and operated exclusively in **Event Mode** (`ULP_RISCV_WAKEUP_SOURCE_GPIO`).
2. **Internal PMU Timer Disabled:** `RTC_CNTL_ULP_CP_SLP_TIMER_EN` remains strictly set to `0`.
3. **External Quartz Timebase:** All periodic sleep intervals are offloaded to the external PCF85063A RTC on `GPIO 5`.
4. **Pulsed Auto-Reload:** The PCF85063A countdown timer is configured in repetitive pulsed mode (`TI_TP = 1` in register `0x11`), generating a self-clearing active-low pulse ($1/64\text{ s} \approx 15.6\text{ ms}$) on `/INT` that re-arms automatically without requiring I2C bus traffic.
5. **ULP Slice Counter:** The ULP counts periodic time slices:
   - `slice_counter == (N - 1)`: Executes sensor reading / ADC battery sample (Flow A preparation).
   - `slice_counter >= N`: Wakes the Main CPU for display refresh and orchestrator execution.
