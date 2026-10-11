# Lessons Learned: What Worked, What Failed, and Architectural Rationale

This document captures the engineering decisions, dead ends, and post-mortem analysis from developing the Waveshare ESP32-S3 ePaper 1.54" V2 BSP. It serves as the primary rationale for why the Clean-Slate architecture is designed the way it is.

---

## 1. What Failed & Why

### 1.1 Circular Header Inclusions (`bsp.h` $\leftrightarrow$ `bsp_audio.h` $\leftrightarrow$ `bsp_splash.h`)
- **What Happened:** Callbacks defined in `bsp.h` (`bsp_splash_cb_t`, `bsp_chime_cb_t`) required enum types declared in subsystem headers (`bsp_chime_type_t`). Including those subsystem headers back into `bsp.h` caused circular inclusion loops, leading to unknown type name compiler errors.
- **Root Cause:** Failure to separate pure data types from subsystem control APIs.
- **Clean Slate Fix:** All primitive enums, masks, error codes, and coordinate types live at Layer 1 in `hal_types.h`. Subsystems and lifecycle layers include down, never across.

---

### 1.2 Callback Slot Overwriting (`s_shutdown_cb` Collision)
- **What Happened:** `bsp_display.cpp` registered an internal shutdown hook into `bsp_power` to sync the framebuffer to flash before power off. Seconds later, `bsp_app_start()` registered the user's `on_power_off` lifecycle callback into the very same function pointer, silently clobbering the display's hook!
- **Root Cause:** Treating internal hardware teardown routines as generic, single-slot user callbacks.
- **Clean Slate Fix:** Layer 2 subsystems **never** register callbacks with each other. The Layer 3 Orchestrator defines the strict, un-overridable hardware teardown sequence (`App Hook` -> `Splash` -> `Chime` -> `Sync Frame` -> `Cut Power`). User callbacks belong 100% to the user.

---

### 1.3 RTC Slow Memory Exhaustion (5000-Byte Frame in RTC SRAM)
- **What Happened:** Attempting to store the 200x200 1-bit framebuffer (5,000 bytes) in RTC Slow Memory (`RTC_DATA_ATTR static uint8_t s_rtc_frame_buffer[5000]`).
- **Root Cause:** ESP32-S3 has only 8,192 bytes (8 KB) of total RTC Slow Memory. Allocating 5,000 bytes consumed ~61% of total RTC SRAM, triggering link errors and starving ULP programs, bootloader state, and telemetry ring buffers.
- **Clean Slate Fix:** The 5,000-byte framebuffer is persisted exclusively to the dedicated SPI flash partition (`epd_frame`, 16 KB). RTC Slow Memory stores **only state flags** (`ORCH_FLAG_EPD_FRAME_VALID`, <256 bytes total).

---

### 1.4 Flash Write Spamming on Active Flushes
- **What Happened:** Writing the 5,000-byte frame to flash on every call to `bsp_display_flush()` or `bsp_display_flush_partial_area()`.
- **Root Cause:** No dirty-tracking. During active runtime, buttons or animations refreshed the screen repeatedly, causing erase/write cycles on SPI flash that burned CPU cycles (~15ms) and threatened SPI flash write endurance.
- **Clean Slate Fix:** In-memory dirty tracking (`s_dirty = true`). Flash is erased and written **only once** upon entering sleep (`bsp_app_sleep`) or during shutdown (`bsp_app_shutdown`).

---

### 1.5 "Zero-Hour" Collision Between Sub-Execution and Main Wake
- **What Happened:** A device scheduled for a 10-minute main wake (external PCF85063A countdown timer) woke up at 9 minutes and 55 seconds on an internal sub-execution timer. It sampled the sensor, scheduled another 60s sub-exec timer, and went back to sleep—only for the external RTC to fire 5 seconds later. The MCU woke up twice in 5 seconds.
- **Root Cause:** The sub-execution timer had no awareness of the remaining duration on the external hardware RTC timer.
- **Clean Slate Fix:** Zero-Hour collision math in Layer 3. Before rearming the sub-execution timer, the BSP reads `Timer_val` from PCF85063A. If $\Delta t_{\text{remaining}} \le T_{\text{sub}}$, the internal timer wake is suppressed, and the MCU sleeps directly for the external RTC interrupt.

---

### 1.6 Sensor Ingestion Architecture Violations
- **What Happened:** A function called `read_sensor()` was taking internal power-domain locks, running Magnus psychrometric equations, reading die temperature, and calculating sliding window dynamics. Sub-execution was burning hundreds of unnecessary clock cycles.
- **Root Cause:** Conflating pure physical sensor acquisition with mathematical evaluation and power policy.
- **Clean Slate Fix:** Strict separation:
  - `sub_sensor_read_shtc3_raw()`: Reads physical I2C words. Nothing else.
  - `orch_math_calc_psychrometrics()`: Pure math function. Takes raw readings, calculates dew point, vapor pressure, absolute humidity, and EWMA. Zero I2C bus traffic.

### 1.7 ULP I2C Impossibility & Hardware Bus Clamping
- **What Happened:** Exploring running periodic SHTC3 acquisition via the ULP-RISC-V coprocessor in deep sleep, and cutting power to peripherals to save current.
- **Root Cause (The Hardware Traps):**
  1. **ULP Routing:** The shared I2C bus is routed to **GPIO 47 (SDA) and GPIO 48 (SCL)**. On the ESP32-S3, the RTC IO domain is strictly limited to `RTCIO 0..21` (GPIOs 0–21). GPIO 47 and 48 are standard digital matrix pins and **cannot be accessed by the ULP or RTC-I2C controller when the digital core is power-gated in deep sleep**.
  2. **ES8311 Bus Clamping:** Cutting power to the audio codec while keeping the I2C bus pulled up causes the unpowered ES8311's internal ESD protection diodes to forward-bias, pulling the shared SDA/SCL lines to ground and clamping the entire I2C bus!
  3. **EPD 3.3V Power Rail (`GPIO 6`):** Cutting the EPD power rail can drop panel charge and corrupt display RAM. Instead of cutting power to the display, placing the SSD1681 into **Deep Sleep Mode 1 (`0x10, 0x01`)** drops display quiescent current to **1.0 µA** while preserving RAM and image state without rail cycling.
- **Clean Slate Fix:**
  - Keep the 3.3V peripheral rail powered and let peripherals sleep natively in low-leakage state (SHTC3 in sleep `0xB098` @ 0.3 µA, ES8311 register `0x0D` power-down @ <1.0 µA, SSD1681 in Deep Sleep Mode 1 @ 1.0 µA).
  - Use **Flow A (Xtensa Sub-Execution Sprint)** for periodic sampling: wakes at 80 MHz, performs I2C transaction in <1 ms, updates RTC Slow SRAM, and returns to deep sleep in <8 ms total without clamping the bus or fighting RTC domain routing.

---

### 1.8 The ULP Coprocessor as Real-Time Hardware Sentinel & Zero-Hour Solver
- **The Breakthrough:** While ULP cannot access GPIO 47/48, it has native hardware domain access to **`RTCIO 4` (Battery ADC)**, **`RTCIO 5` (External PCF85063A RTC INT)**, **`RTCIO 0 & 18` (Buttons)**, and the **Internal TSENS silicon register**.
- **The Zero-Hour Problem Solved:** Instead of having the main Xtensa core juggle multiple competing wake timers (internal timer vs external RTC alarm), the **ULP Coprocessor acts as the master arbiter in deep sleep**:
  - The ULP runs periodically on the RTC Slow Clock.
  - It monitors `GPIO 5` (`RTC_INT`).
  - When the ULP decides it's time for a sensor sample, it first checks `GPIO 5`. If the external RTC alarm is imminent or active, the ULP **suppresses the sub-sprint completely** and wakes the Xtensa core directly into Flow B (Main UI Wake).
  - When a sub-sprint is needed, the ULP triggers `ulp_riscv_wakeup_main_processor()`, prompting the Xtensa core into a targeted <5ms Flow A sprint.
  - **Net Result:** Zero-Hour conflicts are eliminated at the hardware level in the RTC domain. The main application never has to guess or juggle timers.

---

## 2. What Worked & Must Be Kept

### 2.1 Hardware Power Latch Locking (`BAT_CTRL` GPIO 17)
- **The Design:** In the 2nd-stage bootloader and in `hal_io_early_init`, `GPIO 17` is driven HIGH and locked with RTC IO pad holds (`rtc_gpio_hold_en`).
- **Why It Works:** Prevents the battery LDO enable pin from floating LOW during deep sleep transitions or soft resets, which would otherwise abruptly drop power to the board.

---

### 2.2 SSD1681 Ping-Pong RAM Partial Waveform Differential Scanning
- **The Design:** Using SSD1681 RAM `0x24` (New) and `0x26` (Old) with custom 159-byte partial LUT (`WF_PARTIAL_1IN54`) and Differential Ping-Pong Display Option (`0x37`).
- **Why It Works:** Delivers ultra-fast partial refreshes (~300ms) with zero visible screen flash, while eliminating ghosting and preserving particle stability on electrophoretic glass.

---

### 2.3 1-Bit Monochrome Dedicated Fonts (`lv_font_conv --bpp 1`)
- **The Design:** Generating 1-bit packed binary fonts (`MONTSERRAT_14_1BPP`, `MONTSERRAT_20_1BPP`) and disabling subpixel anti-aliasing.
- **Why It Works:** Eliminates grey levels on a strictly monochrome 1-bit panel. Prevents font color inversion bugs and drastically cuts flash consumption.

---

### 2.4 Headless Sub-Execution (<10ms Budget)
- **The Design:** Waking from deep sleep, taking an ultra-fast raw SHTC3 sample (<1ms read time), checking integer gate, and returning directly to deep sleep in 6–8 ms.
- **Why It Works:** Keeps average system power draw under 20 µA while continuously capturing high-frequency environmental trends in the background.

---

## 3. Architecture Comparison Matrix

| Architectural Feature | Legacy Codebase | Clean-Slate Architecture |
| :--- | :--- | :--- |
| **Dependency Structure** | Entangled, circular inclusions | Strict 4-layer unidirectional hierarchy |
| **Common Data Types** | Scattered across subsystem headers | Consolidated at base in `hal_types.h` |
| **Framebuffer Storage** | RTC memory (failed) $\to$ flash partition | SPI flash partition (`epd_frame`, 16KB) only |
| **RTC Slow Memory Use** | ~5200 bytes (Over capacity) | **< 256 bytes** (Minimal footprint) |
| **Flash Write Timing** | On every partial/full flush | **Deferred** to sleep and shutdown only |
| **Teardown Callbacks** | Shared global slots (risk of overwriting) | Dedicated Orchestrator flow; user callbacks isolated |
| **Sub-Execution Budget** | ~15–25 ms (checking locks & math) | **6–8 ms** (pure HAL raw read + integer gate) |
| **Zero-Hour Conflict** | None (woke up twice in rapid succession) | Integrated PCF85063A remaining time evaluation |
| **User-Facing API** | Fragmented across `bsp.h`, `bsp_power.h`, etc. | Unified `bsp.h` (`bsp_app_start`, `bsp_app_sleep`, `bsp_app_shutdown`) |
