# Lessons Learned: What Worked, What Failed, and Architectural Rationale

This document captures the engineering decisions, dead ends, and post-mortem analysis from developing the Waveshare ESP32-S3 ePaper 1.54" V2 BSP into **H1OS**. It serves as the primary rationale for why the Clean-Slate H1OS architecture is designed the way it is.

---

## 1. What Failed & Why

### 1.0 The Cardinal Rule of Engineering Metrology: Never Claim a Measurement You Did Not Take ("Don't Spec Numbers Without Proof")
- **What Happened:** During early debugging of the audio power-rail issue and sleep dissipation, documentation and errata asserted that cutting `PA_EN` caused internal ESD diodes to forward-bias and clamp the shared I2C bus down to "~0.7V", and quoted hypothetical unmeasured sleep currents. In physical reality, no multimeter or oscilloscope had touched the bus lines during those initial tests; the tester simply observed that I2C communication failed when the codec power was cut.
- **Root Cause:** Speculating on unverified voltages and claiming measured numbers without actual instrumented physical verification. Confusing a theoretical mental model (e.g. forward-biased silicon diode drops) with an empirical physical measurement.
- **Why It Fails:** Fabricating or guessing numbers when you don't have proof damages engineering credibility, misleads root-cause investigations, and introduces false architectural assumptions. It sent investigators down rabbit holes searching for phantom clamping diodes in a datasheet that doesn't even mention ESD protection, rather than focusing on the verified empirical reality: gating unbuffered ICs on a shared bus pulls down the lines.
- **H1OS Architectural Mandate:** Never spec numbers if you don't have physical proof they exist. Document exactly what was tested and observed—nothing more, nothing less. If a bus went down, state that the bus went down. If a voltage was not probed on an oscilloscope, explicitly state that it is unmeasured. Keep hypotheses clearly labeled as hypotheses, and keep empirical observations unassailable.

---

### 1.1 The Scaffolding Trap (Conflating Scaffolding with Finished Architecture)
- **What Happened:** During early migration, legacy BSP files (`bsp_common.c`, `bsp_power.c`, `bsp_button.c`, `bsp_sdcard.c`) were kept and patched in place under the assumption that they were "needed" to maintain build viability. This created confusing hybrid architectures where clean-slate HAL/subsystem designs collided with obsolete monolithic implementations.
- **Root Cause:** Treating temporary scaffolding as permanent architecture. Labeling defunct code as "needed" falsely implied that the clean-slate architecture was flawed or missing critical peripheral solutions.
- **H1OS Fix:** Explicit 4-stage construction process (Stage 1 Core Architecture & Contracts, Stage 2 Legacy Deprecation & Cleanup, Stage 3 Subsystem Integration & Drivers, Stage 4 Application & Presentation). Scaffolding is strictly recognized as disposable bring-up bracing. Once the HAL interfaces and API contracts are drafted, legacy scaffolding is removed completely. Deficiencies are solved in the clean-slate layers (`hal_*` and `sub_*`), not by clinging to legacy relics.

---

### 1.2 Circular Header Inclusions (`bsp.h` $\leftrightarrow$ `bsp_audio.h` $\leftrightarrow$ `bsp_splash.h`)
- **What Happened:** Callbacks defined in `bsp.h` (`bsp_splash_cb_t`, `bsp_chime_cb_t`) required enum types declared in subsystem headers (`bsp_chime_type_t`). Including those subsystem headers back into `bsp.h` caused circular inclusion loops, leading to unknown type name compiler errors.
- **Root Cause:** Failure to separate pure data types from subsystem control APIs.
- **H1OS Fix:** All primitive enums, masks, error codes, and coordinate types live at Layer 1 in `hal_types.h`. Subsystems and lifecycle layers include down, never across.

---

### 1.3 Callback Slot Overwriting (`s_shutdown_cb` Collision)
- **What Happened:** Legacy display drivers registered an internal shutdown hook into power management to sync the framebuffer to flash before power off. Seconds later, user application startup registered the user's `on_power_off` lifecycle callback into the very same function pointer, silently clobbering the display's hook!
- **Root Cause:** Treating internal hardware teardown routines as generic, single-slot user callbacks.
- **H1OS Fix:** Layer 2 subsystems **never** register callbacks with each other. The Layer 3 Orchestrator defines the strict, un-overridable hardware teardown sequence (`App Hook` -> `Splash` -> `Chime` -> `Sync Frame` -> `Cut Power`). User callbacks belong 100% to the user.

---

### 1.4 RTC Slow Memory Exhaustion (5000-Byte Frame in RTC SRAM)
- **What Happened:** Attempting to store the 200x200 1-bit framebuffer (5,000 bytes) in RTC Slow Memory (`RTC_DATA_ATTR static uint8_t s_rtc_frame_buffer[5000]`).
- **Root Cause:** ESP32-S3 has only 8,192 bytes (8 KB) of total RTC Slow Memory. Allocating 5,000 bytes consumed ~61% of total RTC SRAM, triggering link errors and starving ULP programs, bootloader state, and telemetry ring buffers.
- **H1OS Fix:** The 5,000-byte framebuffer is persisted exclusively to the dedicated SPI flash partition (`epd_frame`, 16 KB). RTC Slow Memory stores **only state flags** (`ORCH_FLAG_EPD_FRAME_VALID`, <256 bytes total).

---

### 1.5 Flash Write Spamming on Active Flushes
- **What Happened:** Writing the 5,000-byte frame to flash on every call to `bsp_display_flush()` or partial refresh.
- **Root Cause:** No dirty-tracking. During active runtime, buttons or animations refreshed the screen repeatedly, causing erase/write cycles on SPI flash that burned CPU cycles (~15ms) and threatened SPI flash write endurance.
- **H1OS Fix:** In-memory dirty tracking (`s_dirty = true`). Flash is erased and written **only once** upon entering sleep (`h1os_app_sleep`) or during shutdown (`h1os_app_shutdown`).

---

### 1.6 "Zero-Hour" Collision Between Sub-Execution and Main Wake
- **What Happened:** A device scheduled for a 10-minute main wake (external PCF85063A countdown timer) woke up at 9 minutes and 55 seconds on an internal sub-execution timer. It sampled the sensor, scheduled another 60s sub-exec timer, and went back to sleep—only for the external RTC to fire 5 seconds later. The MCU woke up twice in 5 seconds.
- **Root Cause:** The sub-execution timer had no awareness of the remaining duration on the external hardware RTC timer, or main Xtensa was forced to juggle competing clocks.
- **H1OS Fix:** Zero-Hour collision elimination by the reactive ULP Monitor and Layer 3 Orchestrator. When GPIO 5 (PCF85063A alarm) fires or is imminent, Flow B is launched directly and Flow A is suppressed.

---

### 1.7 Sensor Ingestion Architecture Violations
- **What Happened:** A function called `read_sensor()` was taking internal power-domain locks, running Magnus psychrometric equations, reading die temperature, and calculating sliding window dynamics. Sub-execution was burning hundreds of unnecessary clock cycles.
- **Root Cause:** Conflating pure physical sensor acquisition with mathematical evaluation and power policy.
- **H1OS Fix:** Strict separation:
  - `sub_sensor_read_shtc3_raw()`: Reads physical I2C words. Nothing else.
  - `orch_math_calc_psychrometrics()`: Pure math function. Takes raw readings, calculates dew point, vapor pressure, absolute humidity, and EWMA. Zero I2C bus traffic.

---

### 1.8 ULP I2C Impossibility & Hardware Bus Clamping
- **What Happened:** Exploring running periodic SHTC3 acquisition via the ULP-RISC-V coprocessor in deep sleep, and cutting power to peripherals to save current.
- **Root Cause (The Hardware Traps):**
  1. **ULP Routing:** The shared I2C bus is routed to **GPIO 47 (SDA) and GPIO 48 (SCL)**. On the ESP32-S3, the RTC IO domain is strictly limited to `RTCIO 0..21` (GPIOs 0–21). GPIO 47 and 48 are standard digital matrix pins and **cannot be accessed by the ULP or RTC-I2C controller when the digital core is power-gated in deep sleep**.
  2. **ES8311 Bus Clamping:** Cutting power to the audio codec while keeping the I2C bus pulled up brings down the shared SDA/SCL lines, failing all communication on the I2C bus!
  3. **EPD 3.3V Power Rail (`GPIO 6`):** Cutting the EPD power rail drops panel charge and can corrupt display RAM. Instead of cutting power to the display, placing the SSD1681 into **Deep Sleep Mode 1 (`0x10, 0x01`)** drops display quiescent current to nominal sleep levels while preserving RAM and image state without rail cycling.
- **H1OS Fix:**
  - Keep the 3.3V peripheral rail powered and let peripherals sleep natively in low-leakage state (SHTC3 in sleep `0xB098`, ES8311 register `0x0D` power-down, SSD1681 in Deep Sleep Mode 1).
  - Use **Flow A (Xtensa Sub-Execution Sample Burst)** for periodic sampling: wakes at 80 MHz, performs I2C transaction, updates RTC Slow SRAM, and returns to deep sleep without clamping the bus or fighting RTC domain routing.

---

### 1.9 Redundant Button Handlers vs. LVGL Input Subsystem
- **What Happened:** Building a monolithic, bespoke `sub_button` driver with custom queues, debouncers, and callbacks running concurrently with LVGL.
- **Root Cause:** Reinventing the wheel. LVGL v9 already contains a battle-tested keypad/encoder input subsystem (`lv_indev_t`).
- **H1OS Fix:** Eliminate bespoke button subsystem. During deep sleep, the ULP RISC-V monitor acts as the hardware gatekeeper. During active wake (Flow B), buttons are owned directly by LVGL via `LV_INDEV_TYPE_KEYPAD`. HAL provides stateless pin readers (`hal_io_get_button_boot()`, `hal_io_get_button_pwr()`) queried by LVGL's read callback.

---

### 1.10 ULP Polling vs. Event-Driven Wake & App Gating
- **What Happened:** Early ULP designs proposed running a continuous polling loop or state machine while the main application was running, leading to state conflicts and bus contention.
- **Root Cause:** Violating single-owner hardware principles.
- **H1OS Fix:**
  1. **Purely Event-Driven (No Polling):** ULP sleeps by default on RTC slow clock. It wakes **only** on: (a) periodic timer for Flow A sample burst, or (b) external hardware interrupt on GPIO 5 (PCF85063A Alarm INT), GPIO 0/18 (button press), or GPIO 4 (ADC threshold).
  2. **Application Gating:** The ULP runs **only while the main processor is actively in deep sleep**. Once Flow B wakes, the main Xtensa core owns all hardware exclusively. The ULP is never armed while the interactive session is running.

---

## 2. What Worked & Must Be Kept

### 2.1 Hardware Power Latch Locking (`BAT_CTRL` GPIO 17)
- **The Design:** In the 2nd-stage bootloader (`h1os_boot_hook`), `GPIO 17` is driven HIGH and locked with RTC IO pad holds (`rtc_gpio_hold_en`).
- **Why It Works:** Prevents the battery LDO enable pin from floating LOW during deep sleep transitions or soft resets, which would otherwise abruptly drop power to the board. Release is strictly centralized in `hal_io_release_power_latch()`.

---

### 2.2 SSD1681 Ping-Pong RAM Partial Waveform Differential Scanning
- **The Design:** Using SSD1681 RAM `0x24` (New) and `0x26` (Old) with custom 159-byte partial LUT (`WF_PARTIAL_1IN54`) and Differential Ping-Pong Display Option (`0x37`).
- **Why It Works:** Delivers rapid partial refreshes with zero visible screen flash, while eliminating ghosting and preserving particle stability on electrophoretic glass.

---

### 2.3 1-Bit Monochrome Dedicated Fonts (`lv_font_conv --bpp 1`)
- **The Design:** Generating 1-bit packed binary fonts (`MONTSERRAT_14_1BPP`, `MONTSERRAT_20_1BPP`) and disabling subpixel anti-aliasing.
- **Why It Works:** Eliminates grey levels on a strictly monochrome 1-bit panel. Prevents font color inversion bugs and drastically cuts flash consumption.

---

### 2.4 Headless Sub-Execution
- **The Design:** Waking from deep sleep, taking an efficient raw SHTC3 sample in normal power mode, checking integer gate, and returning directly to deep sleep.
- **Why It Works:** Minimizes wake duration while continuously capturing environmental trends in the background.

---

### 2.5 Zero-Volt Cable Guard
- **The Design:** If the battery voltage reads $\approx 0\text{mV}$ while `BAT_CTRL` is latched HIGH, the system recognizes it is running on USB power without a battery.
- **Why It Works:** Prevents spurious low-battery shutdowns and keeps the system operational on the bench without a physical LiPo cell attached.

---

## 3. Architecture Comparison Matrix

| Architectural Feature | Legacy Scaffolding | Clean-Slate H1OS Architecture |
| :--- | :--- | :--- |
| **Identity & Scope** | Legacy BSP mixed with app code | **H1OS** (Strict E-Class environmental telemetry OS) |
| **Dependency Structure** | Entangled, circular inclusions | Strict 4-layer unidirectional hierarchy |
| **Common Data Types** | Scattered across subsystem headers | Consolidated at base in `hal_types.h` |
| **Button Management** | Bespoke `bsp_button.c` background task | **LVGL native `lv_indev` (Keypad)**; ULP during sleep |
| **ULP Operation** | Theoretical continuous polling | **Purely event-driven monitor**; gated during main app run |
| **Zero-Hour Conflict** | None (woke twice in rapid succession) | **ULP arbiter** suppresses Flow A when RTC alarm fires |
| **MicroSD Architecture**| Complex unfinished subsystem | Minimal **`sub_sdcard`** (file I/O, format, capacity) |
| **Interactive Session** | Ad-hoc unmanaged loop | **Configurable session** with 80MHz DFS power droop at idle |
| **Power Latch** | Scattered across app & drivers | **`h1os_boot_hook`** asserts latch; HAL releases on shutdown |
| **No-Battery Operation** | Spurious shutdown on $0\text{mV}$ | **Zero-Volt Cable Guard** (bypasses shutdown on USB) |
| **Framebuffer Storage** | RTC memory (failed) $\to$ flash partition | SPI flash partition (`epd_frame`, 16KB) only |
| **RTC Slow Memory Use** | ~5200 bytes (Over capacity) | **648 bytes** (`orch_persisted_state_t`, including 512B 32-slot ring buffer) |
| **Flash Write Timing** | On every partial/full flush | **Deferred** to sleep and shutdown only |
| **Sub-Execution Budget** | ~15–25 ms (checking locks & math) | **Fast burst** (pure HAL raw read + integer gate) |
| **Public API** | Fragmented across `bsp_*.h` headers | Unified `h1os.h` (`h1os_app_start`, `sleep`, `shutdown`) |

---

## 4. Production Lessons Learned: Thermal & Silicon Invariants

### 4.1 Audio Codec Thermal Oscillation (26°C – 32°C)
- **The Issue:** Overnight thermal imaging revealed periodic temperature cycling oscillating between 26°C and 32°C across the PCB enclosure.
- **Root Cause:** When periodic wakes did not differentiate between unattended RTC updates and physical user button taps, the audio codec (ES8311) and Class-D amplifier (NS4168) were repeatedly initialized and taken out of standby. Even with zero audio output, powering the amplifier rails dissipates quiescent current directly into the internal enclosure volume.
- **The Solution:** Audio initialization is strictly gated behind physical user presence (`is_user_wake = (!is_wake) || button_woke`). Unattended RTC countdown wakeups leave the audio hardware in complete <1 µA standby.

### 4.2 The Danger of Silent Default Substitutions
- **The Issue:** Functions in the lifecycle engine contained silent magic defaults (e.g. `if (sleep_sec == 0) sleep_sec = 300;` or `if (timeout_sec == 0) timeout_sec = 30;`).
- **Why It Fails:** Silent substitutions hide contract violations and configuration errors from the developer. If an application fails to configure a timer, silently substituting synthetic delays masks broken state machines and prevents proper testing.
- **The Standard:** All silent substitutions have been replaced with strict error logs (`ESP_LOGE`) and clean aborts (`ESP_ERR_INVALID_ARG`), forcing explicit contractual configuration at the application layer.

### 4.3 Telemetry Cold Boot Conventions
- Initializing persistent memory to synthetic room temperature (`25.0°C`) created false confidence and corrupted historical EWMA baselines during early boot.
- All telemetry structures now strictly zero-out uninitialized state (`0.0°C` / `0` centi-units), allowing UI screens and downstream logic to unambiguously recognize uninitialized/NA conditions.

### 4.4 ES8311 Register 0x37 Digital Equalizer Silicon Errata & Low-Power Default
- **The Issue:** Severe harmonic distortion and intolerable acoustic buzzing ("sounds like death on 3 wheels") during synthesized audio tone playback.
- **Root Cause:** The Everest Semiconductor ES8311 datasheet incorrectly states that the internal digital equalizer (EQ) block defaults to disabled. In physical silicon, failing to explicitly write `0x08` to Register `0x37` leaves the hardware EQ filter active in the audio signal path. With no biquad coefficients loaded, the uncalibrated filter stages severely distort and clip the output.
- **The Solution:**
  1. Register `0x37` must be explicitly written with `0x08` during codec initialization, bypassing/disabling the uncalibrated digital EQ block and disabling the digital fade-in/out ramp.
  2. Default to Low-Power DAC mode (`0x0F = 0x80`). The noise floor difference through the NS4168 Class-D amplifier is completely negligible while delivering valuable energy savings.

### 4.5 The Cross-Core Spinlock Trap & Peterson Algorithm Lockup
- **The Issue:** The main application froze indefinitely on deep sleep re-entry, with the FreeRTOS task watchdog timer (`task_wdt`) resetting Core 0.
- **Root Cause:** A Peterson software spinlock was introduced between Core 0 and the ULP-RISC-V core to guard shared RTC Slow Memory. When the ULP coprocessor suffered a trap/crash (due to missing `CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y`), it died with its spinlock flag permanently asserted. Core 0 spun indefinitely attempting to acquire the lock before entering sleep.
- **The Solution:** Eliminate complex cross-core software spinlocks entirely. The ULP and dual-core Xtensa CPUs are naturally mutually exclusive by architecture: the ULP executes *only* while the main CPU is in deep sleep. Shared variables are updated cleanly using memory fences (`asm volatile("fence" ::: "memory")`), and execution is strictly handed off via `ulp_riscv_wakeup_main_processor()` and `ulp_riscv_halt()`.

### 4.6 ULP GPIO Wake Latch Semantics & Level-Triggered Clear Ordering (Formerly Misattributed as `ERR-S3`)
- **The Issue:** Intermittent deep sleep re-entry freezes and runaway spurious re-wakes during early ULP bringup.
- **Root Cause (ESP-IDF / Register Semantics Misunderstanding, Not Silicon CDC Defect):** Early bringup code treated `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` (bit 30 of `RTC_CNTL_ULP_CP_TIMER_REG`) as a self-clearing write-1-to-clear (`W1TC`) strobe, or pulsed it *before* clearing `RTC_GPIO_STATUS_W1TC_REG` while a `GPIO_INTR_LOW_LEVEL` wake pin (`GPIO 5` `/INT` or button) was still physically LOW. Because `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` is a synchronous `R/W` reset bit rather than `W1TC`, leaving it set held the ULP wake gate in permanent reset, while clearing it before the level-sensitive pin returned HIGH caused `RTC_GPIO_STATUS_REG` to immediately re-assert the wake request.
- **The Solution:** Wait for level-low inputs (`GPIO 5` `/INT` and buttons) to release HIGH first, write `RTC_GPIO_STATUS_W1TC_REG` to clear the peripheral status register, and then explicitly assert and de-assert `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR`.

### 4.7 Silicon Invariant: Hardware Timer Suppression of RTC GPIO Wakeups (ERR-001)
- **The Issue:** Exploring whether the ESP32-S3 internal ULP sleep timer and external RTC GPIO wakeups can run concurrently to handle periodic sampling and tactile key responsiveness simultaneously.
- **The Empirical Reality:** Rigorous empirical testing on silicon (`examples/riscv_test`) definitively confirmed that **the internal PMU timer suppresses RTC GPIO comparator wakeups**.
  - In **Stage 2 (Pure Event Mode, `0x20000000`)**, tapping GPIO 18 woke the coprocessor in 1.3 seconds (`ticks=178866`, `ULP GPIO Wake Count = 1`).
  - In **Stage 3 (Dual Mode, `0xA0000000`)**, with `TIMER_EN=1` and `GPIO_ENA=1` armed concurrently and `CLR=0` verified in hardware registers, tactile button presses were completely masked from releasing ULP core clock gating. The core remained halted for the full 15.96s countdown (`ticks=2170788`, `ULP GPIO Wake Count = 0`), waking solely on timer expiration.
- **The Architectural Mandate:**
  1. The ULP must operate exclusively in **Pure Event Mode** (`ULP_RISCV_WAKEUP_SOURCE_GPIO`).
  2. All periodic intervals are offloaded to the external PCF85063A RTC on `GPIO 5`, which pulses as a peer GPIO event under `GPIO_WAKEUP_ENA`.
  3. Main-CPU sleep timers (`esp_sleep_enable_timer_wakeup()`) remain an independent, unaffected safety watchdog.

### 4.8 Pre-Sleep Open-Drain Pulse Draining
- **The Issue:** Bare-metal Flow A wake stub executions triggered immediate false wake loops upon re-entering deep sleep.
- **Root Cause:** The PCF85063A generates an active-low open-drain pulse on `/INT` (`GPIO 5`) lasting $\approx 15.625\text{ ms}$. Because the Flow A wake stub completes in $<3.0\text{ ms}$, calling deep sleep at $t \approx 3\text{ ms}$ finds `GPIO 5` still physically LOW, immediately re-triggering the level-low wake detector.
- **The Solution:** An atomic pulse drain barrier is placed before deep sleep entry. Both ULP (on intermediate slices) and Main CPU (on Flow A / Flow B sleep entry) actively verify that `GPIO 5` has released and returned HIGH before enabling wake detectors and executing `esp_deep_sleep_start()`.

### 4.9 Stripping Wake Chimes & Wake Splashes for Thermal Cavity Integrity
- **The Issue:** Excessive battery consumption and thermal cavity offsets during periodic wake transitions.
- **Root Cause:** Playing acoustic chimes and rendering intermediate splash screens on every wake forced the audio amplifier and display charge pumps to run right before sensor sampling.
- **The Solution:** Wake chimes (`H1OS_CHIME_WAKE`) and wake splashes (`H1OS_SPLASH_WAKE`) are permanently eliminated from the automatic wake execution sequence. Acoustic feedback is preserved strictly for physical power events (boot and shutdown), and display updates immediately show the telemetry dashboard without intermediate logos.

### 4.10 Floating LiPo ADC Voltage on USB Power
- **The Issue:** When operating on the bench without a physical LiPo battery installed, the unit continually entered `[CRITICAL LOW POWER SHUTDOWN]` upon boot.
- **Root Cause:** The 200kΩ/200kΩ battery voltage divider on `GPIO 4` floats to $\approx 1.97\text{ V}$ when unpowered by a battery. The ULP brownout detector interpreted $1972\text{ mV}$ as an emergency depleted battery (falling between $100\text{ mV}$ and $3250\text{ mV}$) and commanded immediate shutdown.
- **The Solution:** Implement the **Zero-Volt Cable Guard**: when the power latch is held HIGH and the USB VBUS line is active (`hal_check_usb_ll() == true`), the battery is forced to 4200 mV (100%), and the ULP brownout trip is suppressed.


### 4.11 The Optimization Level (-O2) Timing Collapse Trap (Debug vs. Release Invariants)
- **The Issue:** Bit-bang I2C sensor acquisition in the Flow A wake stub operated with 100% reliability under `-Og` (Debug), but completely failed to ingest samples under `-O2` (Release), leaving the ring buffer empty (`Ring: 0/32`) and telemetry trapped at zero across 625 cycles in chamber test `TST_002`.
- **Root Cause:**
  1. Under `-Og`, function calling overhead, un-inlined helpers (`sda_high()`, `scl_low()`), and stack frame manipulation inadvertently provided the necessary $\approx 1\text{–}2\ \mu\text{s}$ settling times required by physical pull-up resistors and bus trace capacitance.
  2. Under `-O2`, aggressive compiler inlining and loop scheduling flattened the I2C routines into consecutive machine cycles without adequate line-settling margins. Furthermore, `esp_rom_delay_us()` relies on software loops that can execute faster than nominal at 80 MHz in RTC memory.
- **The Solution:**
  1. **Hardware Cycle Counter Delay (`rsr.ccount`):** Replaced all software delay loops with `rtc_delay_us_exact()`, reading the Xtensa hardware `ccount` register. Each microsecond is evaluated against exactly 80 clock cycles at 80 MHz, making delay loops physically immune to compiler optimization flags.
  2. **Pipeline Memory Barriers (`memw`):** Inserted `memw` instructions after all GPIO direction and level manipulations, ensuring hardware bus transactions are committed to the peripheral registers before the pipeline evaluates bus state.
  3. **Passive Error Visibility:** Telemetry structures were updated to persist `sensor_fail_count` and `last_sensor_error` to RTC Slow Memory and display them on Screen 4 (`Wakes: <wakes> (Fail: <fails>)` and `SHT: OK / ERR_<n>`), eliminating silent telemetry dropouts.

### 4.12 The Compiler Flash Table Synthesis Trap in RTC Wake Stubs (-O2 Release Failure)
- **The Issue:** SHTC3 sensor acquisition consistently succeeded in Debug (`-Og`), but failed 100% of cyclic deep sleep wake-stub executions in Release (`-O2`), returning error code `E4` (`ORCH_SENSOR_ERR_CRC_FAIL`) across every wake.
- **Root Cause (Binary Disassembly Discovery):**
  1. In GCC under `-O2`, the compiler's loop optimizer analyzed the fixed-polynomial bitwise calculation inside `shtc3_crc8()` (polynomial `0x31`) and automatically synthesized a 256-byte precomputed lookup table.
  2. Because constant data without explicit RTC attributes defaults to the `.rodata` section, the linker placed the synthesized table in external SPI NOR Flash at MMU address `0x3C0A379C`.
  3. **The Silicon Invariant:** During deep sleep, the ESP32-S3 powers down external SPI Flash, and the Flash MMU cache controller is offline. When `bsp_wake_stub()` invoked `shtc3_crc8()`, the CPU executed `l32r a10, (0x3c0a379c)` followed by `l8ui a8, a8, 0`, attempting to load bytes from unpowered Flash.
  4. Reading unpowered Flash returned floating bus noise / `0xFF`, corrupting the computed CRC and triggering `ORCH_SENSOR_ERR_CRC_FAIL` on 100% of wake cycles.
  5. In Debug (`-Og`), loop optimization was disabled; GCC executed the bitwise shift/XOR operations directly in CPU registers inside RTC Fast Memory (`.rtc.text`), masking the defect during development.
- **The Solution:**
  1. Guarded `shtc3_crc8()` with `__attribute__((noinline))` and an empty inline assembly register clobber `asm volatile("" : "+r"(crc));`.
  2. This clobber forces GCC to keep `crc` in a physical CPU register and strictly prevents the optimizer from synthesizing a lookup table in external `.rodata`.
  3. Disassembly of `h1os.elf` verified that `shtc3_crc8$constprop$0` executes 100% bitwise operations from `.rtc.text` (`0x600feb6c`), eliminating all Flash MMU references (`0x3C...`) from the RTC wake stub.

### 4.13 Internal MCU Die TSENS Power-Down & Reset Register Traps
- **The Issue:** The internal ESP32-S3 die temperature sensor (`wake_stub_read_die_temp_centi_c`) consistently returned default 0 centi-°C in Release (`-O2`).
- **Root Cause:**
  1. **Reset Register Mismatch:** The code attempted to assert `SENS_TSENS_RESET` (Bit 29) into `SENS_SAR_TSENS_CTRL2_REG` (`0x60008854`). In ESP32-S3 silicon, `CTRL2` does not contain a reset bit at Bit 29; the actual temperature sensor reset line is mapped to `SENS_SAR_PERI_RESET_CONF_REG` (`0x60008908`). The analog sensor was never reset.
  2. **Force Power-Down Misconfiguration (`SENS_TSENS_XPD_FORCE`):** Per the ESP32-S3 Technical Reference Manual (Table *TSENS_CTRL2_REG*), `tsens_xpd_force[1:0]` is a 2-bit power control field:
     - `0`: Disable force power up function
     - `1`: Disable force power down function
     - `2`: Enable force power up
     - `3`: **Enable force power down**
     Writing `3` explicitly commanded the silicon to force power-down the analog sensor! The correct operational value is `1` (disabling force power-down to allow `tsens_power_up = 1` to energize the sensor) followed by `0` on sleep.
  3. **Missing Latch Sequence & Polling Bound:** In ESP-IDF hardware logic, `tsens_dump_out` must be asserted to start measurement, polled until `tsens_ready` asserts, and then **de-asserted to latch the result** before reading `tsens_out`. Under `-O2`, the 100-cycle loop timed out before the analog clock divider asserted `ready`.
- **The Solution:**
  - Directed `SENS_TSENS_RESET` to `SENS_SAR_PERI_RESET_CONF_REG`.
  - Configured `SENS_TSENS_XPD_FORCE = 1` during sample and `0` on sleep.
  - Implemented the de-assert latch step (`DUMP_OUT = 1` $\rightarrow$ poll `READY` $\rightarrow$ `DUMP_OUT = 0` $\rightarrow$ read `OUT`).
  - Increased `ORCH_TSENS_READY_TIMEOUT_CYCLES` to `1000U` (5 ms ceiling).

### 4.14 Cold-Boot Flow Period Initialization Order Trap (`v2.4.5-dev` / `MANDATE-02` / `REV-01`)
- **The Issue:** User-configured `session.flow_a_period_sec` and `session.flow_b_period_sec` (e.g., `60 s` / `300 s`) were silently overwritten with default fallback periods (`60 s` / `900 s`) on every cold power-on reset (`ORCH_FLOW_BOOT`).
- **Root Cause:** `h1os_start()` called `h1os_set_flow_periods_internal()` *before* `orch_flow_init()`. On cold boot, `orch_flow_init()` saw `st->magic != ORCH_RTC_MAGIC` and invoked `orch_state_reset()`, which wiped `st->sample_interval_sec = 60` and `st->flow_b_period_sec = 900`, clobbering the values written microseconds earlier.
- **The Solution:** Split flow-period handling into `h1os_validate_flow_periods()` (called before `orch_flow_init()` to fail fast on invalid arguments before touching hardware) and `h1os_apply_flow_periods()` (called *after* `orch_flow_init()` / `orch_state_reset()` so configured periods are written to the initialized `RTC_SLOW_MEM` block and armed into the ULP and PCF85063A).

### 4.15 Dual-Core Concurrency, `h1os_ui_post` Lock Protection & `EventGroup` Sleep Barrier (`v2.4.5-dev` / `MANDATE-04` / `REV-02`)
- **The Issue:** Executing network/peripheral I/O (`on_wake`) sequentially before starting Core 1 LVGL wasted 350–1500 ms of battery-active time per Flow B wake, while proposed drafts that drained `h1os_ui_post()` outside `h1os_lvgl_lock()` or held `h1os_lvgl_lock(1000)` across `on_wake`/`on_pre_sleep` introduced data races and deadlocks.
- **The Solution:**
  1. Start Core 1 LVGL (`h1os_lvgl_start(5, 1)`) immediately after `on_wake()` returns, then invoke `on_sync()` on Core 0 in parallel with the SSD1681 display refresh.
  2. Drain all queued `h1os_ui_post()` callbacks on Core 1 **strictly inside `h1os_lvgl_lock(100)`** immediately prior to `lv_timer_handler()` (`REV-02`), and remove outer `h1os_lvgl_lock(1000)` wrappers around `on_boot`, `on_wake`, `on_pre_sleep`, and `on_shutdown`.
  3. Coordinate sleep entry using a static FreeRTOS `EventGroup` barrier (`BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`) with `h1os_sync_hold()` / `h1os_sync_notify_complete()` and an optional `session.sync_wait_ms` inbound pre-flush gate to coalesce `on_wake` + `on_sync` updates into a single physical e-Paper refresh.

### 4.16 Post-`GPIO_INTR_NEGEDGE` 250 ms Electrophoretic Settling Window & Fatal Startup Latch Cut (`v2.4.5-dev` / `MANDATE-06` / `REV-03` / `REV-04`)
- **The Issue:**
  1. After replacing `sub_display_wait_busy()` polling with a zero-latency `GPIO_INTR_NEGEDGE` interrupt semaphore on `GPIO 8` (`EPD_BUSY`), `sub_display_enter_deep_sleep()` sent command `0x10` (`0x01`) within microseconds of `BUSY` falling low, cutting charge pumps before electrophoretic microcapsules finished mechanical deceleration.
  2. Using `ESP_RETURN_ON_ERROR` inside `h1os_start()` after the 2nd-stage bootloader had already latched `GPIO 17` (`BAT_CTRL = 1`) meant any cold-boot hardware fault returned to `app_main()` with the battery LDO permanently latched on, draining the LiPo cell to brownout.
- **The Solution:**
  1. Enforced a mandatory `250 ms` settling delay (`SUB_DISPLAY_SETTLING_WINDOW_MS`) inside `sub_display_enter_deep_sleep()` between `sub_display_wait_busy()` and command `0x10` (`0x01`) (`REV-04`).
  2. Implemented `h1os_handle_fatal_startup_error()` (`MANDATE-06` / `REV-03`), which invokes `on_error(err, stage)` and immediately releases `GPIO 17` (`hal_io_release_power_latch()`) on battery power (or enters `EXT0` deep sleep on `GPIO 18` when USB power is attached).

### 4.17 ULP-RISC-V SAR ADC1 Full-Scale Saturation Trap (`raw = 4095` / `vbat = 6917 mV`) (`v2.4.5-dev` / `ERR-S6` / `REV-09`)
- **The Issue:** On hardware bench testing with a charged AntPow `AP502535` 400 mAh LiPo cell ($4.10\text{–}4.20\text{ V}$ across the $200\text{ k}\Omega / 200\text{ k}\Omega$ divider + tap filter capacitor on `GPIO 4`), `[ULP TELEMETRY]` reported `vbat=6917 mV (raw=4095)` across every deep sleep wake cycle, while the UI displayed `4.00 V` due to the `> 4500 mV` fallback clamp in `sub_power_get_battery_status()`.
- **Root Cause:**
  1. `sub_power_init()` called `adc_oneshot_new_unit()` (`.ulp_mode = ADC_ULP_MODE_RISCV`) and `adc_oneshot_config_channel()` (`.atten = ADC_ATTEN_DB_12`) directly instead of ESP-IDF's `ulp_adc_init()`. In ESP-IDF, `adc_oneshot_config_channel()` does not load the eFuse hardware reference calibration code (`adc_set_hw_calibration_code(ADC_UNIT_1, ADC_ATTEN_DB_12)`) into the SAR ADC1 internal analog `reg_i2c` registers until `adc_oneshot_read()` is called on the main CPU. Because H1OS never calls `adc_oneshot_read()` on the main CPU, the internal analog reference remained uncalibrated and `esp_sleep_enable_adc_tsens_monitor(true)` was omitted, causing the 12-bit SAR comparator to clip at `4095` for any input above $\sim 1.1\text{ V}$.
  2. `ulp_read_vbat_adc_bounded()` in `ulp/main.c` did not force `SENS_FORCE_XPD_SAR = 0x3` or enforce `ADC_ATTEN_DB_12` (`0x3`) in `SENS_SAR_ATTEN1_REG` before starting conversion, and `sub_power_enter_deep_sleep_mode()` / `hal_io_release_pad_holds()` re-initialized/de-initialized `GPIO 4` (`HAL_PIN_BATTERY_ADC`) after `s_adc_io_init()`.
- **The Solution:** Replaced raw `adc_oneshot_new_unit()` in `sub_power_init()` with `ulp_adc_init(&ulp_adc_cfg)`, enforced `SENS_FORCE_XPD_SAR = 0x3` and `SENS_SAR_ATTEN1_REG` (`12 dB`) inside `ulp_read_vbat_adc_bounded()`, and preserved `GPIO 4`'s analog pad configuration across sleep and wake transitions.
