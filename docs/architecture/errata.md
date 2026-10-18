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

---

## ERR-002: ES8311 Unpowered Codec Forward-Bias I2C Bus Clamp

- **Component:** Everest Semiconductor ES8311 Audio Codec
- **Subsystem:** Audio Subsystem / Shared I2C0 Bus (`GPIO 47` SDA, `GPIO 48` SCL)
- **Affects:** Waveshare ESP32-S3 ePaper 1.54" V2 Hardware Revision
- **Severity:** Critical (entire I2C bus locks up at 0.7 V, freezing all sensors and RTC)

### Description
The audio power rail (`PA_EN` on `GPIO 42`) controls the main 3.3V supply to both the ES8311 low-power audio codec and the NS4168 Class-D amplifier.

When `PA_EN` is driven HIGH to cut power to the audio section, the `DVDD`/`AVDD` pins of the ES8311 drop to 0 V. However, the shared I2C bus (`GPIO 47` and `GPIO 48`) remains pulled up to 3.3 V by external 4.7 kΩ resistors to support the SHTC3 environmental sensor and PCF85063A RTC.

Under this unpowered condition, the 3.3 V bus pull-up voltage forward-biases the ES8311's internal ESD protection clamping diodes on its SDA and SCL pins. The ESD diodes shunt current directly into the unpowered power rail, clamping both SDA and SCL to $\approx 0.7\text{ V}$. This completely disables the I2C bus, causing all subsequent transactions to the SHTC3 or PCF85063A to time out and crash the system.

### Mitigation & Architecture Mandate
1. **Keep Audio Rail Powered:** `PA_EN` (`GPIO 42`) is active-low (`0 = ON`). It must be driven LOW in the 2nd-stage bootloader hook (`h1os_boot_hook.c`) and permanently held LOW across runtime and deep-sleep sessions via digital pad hold (`RTC_CNTL_DIG_PAD_HOLD_REG`).
2. **Software Standby Power Down:** Rather than cutting physical power, the ES8311 is placed into **Software Standby** by writing `0x00` to Register `0x0D` and powering down the DAC analog stage (Register `0x12 = 0x02`). In this state, quiescent leakage is $<1.0\ \mu\text{A}$ while the I2C ESD clamping diodes remain reverse-biased.
3. **Hardware Amplifier Mute:** The NS4168 Class-D amplifier is held in hardware shutdown by holding `PA_CTRL` (`GPIO 46`) LOW (`0 = Mute/Shutdown`).

---

## ERR-003: ES8311 Register 0x37 Uncalibrated Digital EQ Filter Distortion

- **Component:** Everest Semiconductor ES8311 Audio Codec
- **Subsystem:** Audio DAC Signal Path
- **Affects:** ES8311 Silicon Revisions
- **Severity:** Medium (severe audio buzzing, acoustic distortion, and phase clipping)

### Description
The manufacturer datasheet states that the internal digital equalizer (EQ) block is disabled by default upon reset.

In physical silicon, failing to write `0x08` to Register `0x37` leaves the hardware EQ filter active in the digital DAC path. Because no valid biquad coefficients are loaded, the uncalibrated filter stages severely distort and clip the output, producing harsh acoustic buzzing and harsh clipping during tone synthesis.

### Mitigation & Architecture Mandate
During codec initialization in `sub_audio.c`:
1. Write `0x08` to Register `0x37` unconditionally to disable the digital volume fade ramp and bypass/disable the uncalibrated digital EQ filter block.
2. Program Register `0x0F` to `0x80` to configure Low-Power DAC mode, which provides substantial battery power savings with imperceptible audio impact through the NS4168 amplifier.

---

## ERR-004: ESP32-S3 XTAL32K Clock Domain Crossing (CDC) Wake Latch Bounce

- **Component:** ESP32-S3 Low-Power Controller (RTC IO / PMU)
- **Subsystem:** ULP Coprocessor Wake Latch (`RTC_CNTL_ULP_CP_TIMER_REG`)
- **Affects:** ESP32-S3 with external 32.768 kHz quartz crystal (`CONFIG_RTC_CLK_SRC_EXT_CRYS`)
- **Severity:** High (intermittent sleep re-entry freeze and runaway spurious wakes)

### Description
When clearing the ULP coprocessor wake latch via `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR`, the RTC state machine operates on the slow clock domain ($f_{\text{slow}} = 32.768\text{ kHz}$, period $T_{\text{cycle}} \approx 30.517\ \mu\text{s}$).

Per the ESP32-S3 Technical Reference Manual, synchronizing level-clearing pulses across the slow clock domain requires the clear signal to be asserted for **$\ge 3$ slow clock cycles** ($\ge 91.55\ \mu\text{s}$). If pulsed for less than this duration (e.g. $50\ \mu\text{s}$), the clear signal is missed by the synchronizer flip-flops. Furthermore, if `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` is left asserted while the ULP halts, or if `RTC_GPIO_STATUS_W1TC_REG` is cleared *after* the controller pulse, the active status latch immediately re-triggers the wake gate.

### Mitigation & Architecture Mandate
1. **120 µs Clear Pulse Duration:** Any pulse on `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` must be delayed for $\ge 120\ \mu\text{s}$ (`ulp_riscv_delay_us(120)` in ULP, `esp_rom_delay_us(120)` in Xtensa core), guaranteeing $\approx 3.93$ cycles on XTAL32K.
2. **Explicit Deassertion:** `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` must be explicitly cleared (`CLEAR_PERI_REG_MASK`) after the delay.
3. **Peripheral Status Clear Order:** `RTC_GPIO_STATUS_W1TC_REG` must be written *first*, followed by the controller pulse, ensuring the level comparator is unasserted before resetting the controller latch.

---

## ERR-005: PCF85063A Open-Drain Pulse Duration Pre-Sleep Race

- **Component:** NXP / Nexperia PCF85063A Real-Time Clock
- **Subsystem:** Countdown Timer `/INT` Output on `GPIO 5`
- **Affects:** Waveshare ESP32-S3 ePaper 1.54" V2 Hardware Revision
- **Severity:** High (immediate false wakeups and missed edge transitions on sleep re-entry)

### Description
When configured in pulsed timer mode (`TI_TP = 1` in Register `0x11`), the PCF85063A generates an active-low open-drain pulse on `/INT` (`GPIO 5`) with a fixed hardware duration of $1/64\text{ s} \approx 15.625\text{ ms}$.

Flow A bare-metal sensor sample bursts (`bsp_wake_stub()`) execute in $<3.0\text{ ms}$. If Flow A attempts to re-enter deep sleep while the physical `/INT` line is still held LOW by the RTC chip ($t < 15.6\text{ ms}$), the RTC IO level comparator detects a continuous LOW state upon sleep arming, causing immediate false re-triggers, skipped cycles, or PMU state machine aborts.

### Mitigation & Architecture Mandate
1. **Dual-Sided Pulse Drain Barrier:**
   - **In ULP:** On intermediate tick slices, the ULP waits in a polling loop (`ulp_riscv_gpio_get_level(GPIO_NUM_5) == 0`) with a 50 ms timeout until the line returns HIGH before clearing latches and re-arming `GPIO_WAKEUP_ENA`.
   - **In Main CPU:** In `sub_power_enter_deep_sleep_mode()`, the Main CPU executes an atomic hardware wait:
     ```c
     uint32_t drain_wait_us = 0;
     while (gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 25000) {
         esp_rom_delay_us(500);
         drain_wait_us += 500;
     }
     ```
2. **Stuck-Line Fault Trap:** If `GPIO 5` fails to return HIGH within 50 ms, the ULP logs `rtc_int_stuck = 1`, bypasses `GPIO_WAKEUP_ENA` re-arming to prevent runaway infinite wake loops, and wakes the Main CPU to report hardware failure.

---

## ERR-006: ADC1 Oneshot Multi-Unit Driver Collision (`ESP_ERR_NOT_FOUND`)

- **Component:** ESP-IDF `adc_oneshot` Driver
- **Subsystem:** ADC1 Controller (`GPIO 4` Battery ADC)
- **Affects:** ESP32-S3 ESP-IDF v5.4 & v6.1
- **Severity:** Medium (battery readout failure and uncalibrated LUT fallbacks)

### Description
When the ULP coprocessor uses ADC1 for battery voltage monitoring, `ulp_riscv_adc_init()` claims the hardware unit lock in ESP-IDF (`s_adc_unit_claim(0) = true`).

If the main application later attempts to initialize `adc_oneshot_new_unit()` with default settings (`.ulp_mode = ADC_ULP_MODE_DISABLE`), the driver returns `ESP_ERR_NOT_FOUND` because ADC1 is already claimed. Furthermore, initializing the ULP before the main ADC driver prevents factory eFuse calibration curves from being generated.

### Mitigation & Architecture Mandate
1. **Shared ULP Mode Allocation:** `sub_power_init()` must configure `adc_oneshot_unit_init_cfg_t` with `.ulp_mode = ADC_ULP_MODE_RISCV`.
2. **Initialization Sequence:** `sub_power_init()` must execute *before* `sub_power_init_ulp()`, ensuring the eFuse calibration curve handle (`s_cali_handle`) is valid before any battery calculation parameters are passed to the ULP coprocessor.
3. **Eliminate Redundant Allocation:** `ulp_riscv_adc_init()` is not called separately if `sub_power_init()` has already configured ADC1 unit and channel 3 for shared operation.
