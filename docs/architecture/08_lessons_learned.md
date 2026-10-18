# Lessons Learned: What Worked, What Failed, and Architectural Rationale

This document captures the engineering decisions, dead ends, and post-mortem analysis from developing the Waveshare ESP32-S3 ePaper 1.54" V2 BSP into **H1OS**. It serves as the primary rationale for why the Clean-Slate H1OS architecture is designed the way it is.

---

## 1. What Failed & Why

### 1.1 The Scaffolding Trap (Conflating Scaffolding with Finished Architecture)
- **What Happened:** During early migration, legacy BSP files (`bsp_common.c`, `bsp_power.c`, `bsp_button.c`, `bsp_sdcard.c`) were kept and patched in place under the assumption that they were "needed" to maintain build viability. This created confusing hybrid architectures where clean-slate HAL/subsystem designs collided with obsolete monolithic implementations.
- **Root Cause:** Treating temporary scaffolding as permanent architecture. Labeling defunct code as "needed" falsely implied that the clean-slate architecture was flawed or missing critical peripheral solutions.
- **H1OS Fix:** Explicit 4-stage construction doctrine ("The Bones", "Housekeeping & Purge", "The Muscle", "The Vanity"). Scaffolding is strictly recognized as disposable bring-up bracing. Once the architectural bones and HAL contracts are drafted, legacy scaffolding is purged completely. Deficiencies are solved in the clean-slate layers (`hal_*` and `sub_*`), not by clinging to legacy relics.

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
  2. **ES8311 Bus Clamping:** Cutting power to the audio codec while keeping the I2C bus pulled up causes the unpowered ES8311's internal ESD protection diodes to forward-bias, pulling the shared SDA/SCL lines to ground and clamping the entire I2C bus!
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
| **RTC Slow Memory Use** | ~5200 bytes (Over capacity) | **< 256 bytes** (Minimal footprint) |
| **Flash Write Timing** | On every partial/full flush | **Deferred** to sleep and shutdown only |
| **Sub-Execution Budget** | ~15–25 ms (checking locks & math) | **Fast burst** (pure HAL raw read + integer gate) |
| **Public API** | Fragmented across `bsp_*.h` headers | Unified `h1os.h` (`h1os_app_start`, `sleep`, `shutdown`) |

---

## 4. Production Lessons Learned: Thermal & Silicon Invariants

### 4.1 Audio Codec Thermal Oscillation (26°C – 32°C)
- **The Issue:** Overnight thermal imaging revealed periodic temperature cycling oscillating between 26°C and 32°C across the PCB enclosure.
- **Root Cause:** When periodic wakes did not differentiate between unattended RTC updates and physical user button taps, the audio codec (ES8311) and Class-D amplifier (NS4168) were repeatedly initialized and taken out of standby. Even with zero audio output, powering the amplifier rails dissipates quiescent current directly into the internal enclosure volume.
- **The Solution:** Audio initialization is strictly gated behind physical user presence (`is_user_wake = (!is_wake) || button_woke`). Unattended RTC countdown wakeups leave the audio hardware in complete <1 µA standby.

### 4.2 The Danger of Silent Fallback Defaults
- **The Issue:** Functions in the lifecycle engine contained silent magic fallback defaults (e.g. `if (sleep_sec == 0) sleep_sec = 300;` or `if (timeout_sec == 0) timeout_sec = 30;`).
- **Why It Fails:** Silent fallbacks hide contract violations and configuration errors from the developer. If an application fails to configure a timer, silently substituting synthetic delays masks broken state machines and prevents proper testing.
- **The Standard:** All silent fallbacks have been replaced with strict error logs (`ESP_LOGE`) and clean aborts (`ESP_ERR_INVALID_ARG`), forcing explicit contractual configuration at the application layer.

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

### 4.6 Clock Domain Crossing (CDC) Timing Rules & Internal RC Oscillator
- **The Issue:** Intermittent deep sleep re-entry freezes and missed RTC GPIO edge transitions.
- **Root Cause:** Level clear pulses on `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` were asserted for too short a duration ($50\ \mu\text{s}$). Furthermore, the board has no physical 32.768 kHz quartz crystal (pins `GPIO 15` and `GPIO 16` are dedicated to I2S audio codec routing), so the RTC domain runs on the internal ~136 kHz RC oscillator (`CONFIG_RTC_CLK_SRC_INT_RC=y`). The ESP32-S3 TRM mandates that CDC clear signals must be held for $\ge 3$ slow clock cycles to be sampled by the internal synchronizers.
- **The Solution:** All wake latch clearing pulses in both ULP firmware and main application code are explicitly delayed for $\ge 120\ \mu\text{s}$ ($> 16$ cycles on the 136 kHz internal RC clock), guaranteeing deterministic synchronization across domains.

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



