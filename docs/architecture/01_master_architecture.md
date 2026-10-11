# Master Architecture Blueprint: Clean-Slate ESP32-S3 ePaper BSP

- **Target Silicon:** ESP32-S3-WROOM-1 / ESP32-S3-PICO-1-N8R8 (Xtensa dual-core LX7, 8MB Octal SPI Flash, 8MB Octal PSRAM).
- **Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2.
- **Framework:** ESP-IDF v5.4+ / v6.x (FreeRTOS SMP, ESP-IDF Driver V2 APIs, Clangd-compatible).
- **Architecture Philosophy:** Strict unidirectional dependency layering, zero circular inclusion, hardware determinism, deep sleep ultra-low-power duty cycling (<15 µA base quiescent).

---

## 1. High-Level 4-Layer Hierarchy

```
 ┌─────────────────────────────────────────────────────────────────────────┐
 │                   LAYER 4: USER APPLICATION LIFECYCLE                   │
 │                bsp_app_start() | bsp_app_sleep() | bsp_app_off()        │
 └────────────────────────────────────┬────────────────────────────────────┘
                                      │ configures & controls
 ┌────────────────────────────────────▼────────────────────────────────────┐
 │                LAYER 3: SYSTEM PIPELINE & ORCHESTRATOR                  │
 │  Flow Orchestrator | Telemetry & Math Ring Buffer | RTC Memory Manager  │
 └────────────────────────────────────┬────────────────────────────────────┘
                                      │ commands
 ┌────────────────────────────────────▼────────────────────────────────────┐
 │                  LAYER 2: HARDWARE SUBSYSTEM MANAGERS                   │
 │   Display Driver | Sensor Driver | RTC Driver | Power & PM Manager      │
 └────────────────────────────────────┬────────────────────────────────────┘
                                      │ utilizes
 ┌────────────────────────────────────▼────────────────────────────────────┐
 │                 LAYER 1: LOW-LEVEL HAL & BUS DRIVERS                    │
 │     GPIO / Latch / Pad Holds | I2C Master | SPI Master | Flash Partition│
 └─────────────────────────────────────────────────────────────────────────┘
```

### Invariant Rules of Layer Separation
1. **Unidirectional Control:** Higher layers may `#include` and call lower layers. Lower layers **NEVER** include or call higher layers.
2. **No Hardware Subsystem Cross-Calls in Layer 2:** `sub_display` never talks to `sub_power`; `sub_sensor` never checks power states. Inter-subsystem coordination is strictly the responsibility of Layer 3 Orchestrator.
3. **Common Data Types Rooted at Base:** All shared enums, error types, coordinate structs, and math definitions live in `bsp_types.h` at the HAL level.

---

## 2. Layer Definitions & Component Breakdown

### Layer 1: Hardware Abstraction Layer (HAL)
Pure C, dumb hardware adapters. No RTOS policies, no state machines, no math.
- [`hal_types.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/01_layer1_hal.md): Fixed-width types, error codes, pinout constants, bitmasks.
- [`hal_io.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/01_layer1_hal.md): GPIO configuration, RTC pad holds, power latch locks (`BAT_CTRL` GPIO 17), EPD rail switch (`EPD_3V3_EN` GPIO 6).
- [`hal_i2c.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/01_layer1_hal.md): Thread-safe, mutex-protected I2C bus driver (`ESP-IDF i2c_master`), supporting both blocking and ISR-safe operations.
- [`hal_spi.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/01_layer1_hal.md): High-speed DMA SPI bus driver (20 MHz write, 2 MHz 3-wire read).
- [`hal_flash.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/01_layer1_hal.md): Raw sector erase/read/write routines mapped to partition labels (`epd_frame`, `storage`).

### Layer 2: Hardware Subsystem Managers
Self-contained peripheral drivers. Expose clean APIs with state encapsulated locally.
- [`sub_display.cpp/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/02_layer2_subsystems.md): SSD1681 200x200 1-bit driver, Ping-Pong buffer RAM management (0x24/0x26), partial waveform LUT, panel busy synchronization, on-glass surface thermistor read (SPI Cmd 0x1B). Implements Deep Sleep Mode 1 (`0x10, 0x01` @ 1.0 µA) without dropping 3.3V rail.
- [`sub_sensor.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/02_layer2_subsystems.md): Tri-Node sensing primitives: SHTC3 raw I2C communications (`Wake` -> `Read` -> `Sleep`), internal MCU TSENS die driver (`esp_timer`/analog), and SSD1681 glass thermal bridge. Pure physical reads—no artificial curve fudging.
- [`sub_rtc.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/02_layer2_subsystems.md): PCF85063A driver for timekeeping, countdown timer, alarms, and interrupt line clearing (`GPIO 5`).
- [`sub_power.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/02_layer2_subsystems.md): Battery ADC curve fitting, dynamic CPU frequency scaling (`esp_pm`), wakeup pin configuration (`EXT1`), deep sleep entry, and asymmetric core management (Core 1 gating during Flow A).
- [`sub_audio.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/02_layer2_subsystems.md): ES8311 software standby power-down (Reg 0x0D @ <1.0 µA) to prevent unpowered I2C bus clamping, synthesized tone generation, amplifier standby management.

### Layer 3: System Pipeline & Orchestrator
The central intelligence of the BSP. Houses persistent RTC memory, FreeRTOS synchronization, math algorithms, and execution flows.
- [`orch_state.h/.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/03_layer3_orchestrator.md): Shared RTC Slow Memory structure (<512 bytes), boot/wake counters, flags, Tri-Node sliding ring buffer (SHTC3 + TSENS die + SSD1681 glass), dynamic ambient floor tracking.
- [`orch_math.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/03_layer3_orchestrator.md): Class-E psychrometrics: Magnus vapor pressure invariant, dew point reconstruction, continuous EWMA filtering, integer centi-degree slope stability gating, dynamic thermal confidence scoring.
- [`orch_flow.c/.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/clean_slate_architecture/03_layer3_orchestrator.md): Single Unified Binary Execution Arbiter. Arbitrates between **Flow A: Core 0 Isolated RTC Wake Stub / Sprint (<8ms @ 80MHz, Core 1 gated off)** and **Flow B: Full Application Dual-Core Wake/Boot (FreeRTOS, LVGL UI)**. Houses the Thermal Lockout MUX gatekeeper to prevent reading hot sensor silicon during active wake.

### Layer 4: Application Lifecycle API
The minimal public interface exposed to application developers (`bsp.h`).
- Declarative structure: `bsp_app_config_t` with explicit lifecycle hooks (`on_boot`, `on_wake`, `on_pre_sleep`, `on_shutdown`).
- High-level control: `bsp_app_start()`, `bsp_app_sleep()`, `bsp_app_shutdown()`.
- Telemetry ingestion: `bsp_app_get_telemetry()` (automatically serves cached cold readings when Thermal Lockout MUX is active).

---

## 3. Real-Time & Hardware Primitives

1. **FreeRTOS Synchronization**:
   - I2C bus protected by recursive mutex (`xSemaphoreCreateRecursiveMutex`).
   - Display flushing synchronizes against an e-Paper BUSY binary semaphore / task notification triggered by GPIO ISR.
2. **Interrupt Service Routines (ISRs)**:
   - `GPIO 5` (RTC INT): Low-level edge/level ISR dispatches unblocking notification to power task.
   - `GPIO 0` (BOOT) & `GPIO 14` (PWR): Hardware debounce filtering using FreeRTOS tick timers.
3. **Hardware Watchdog (TWDT / RTC WDT)**:
   - Task Watchdog Timer configured for 10s timeout during full display flushes.
   - RTC Watchdog enabled during deep sleep to catch brownout latch anomalies.
4. **Thermal Cooldown Window**:
   - Software locks prevent main CPU heat from polluting sensor ring buffer during active 240MHz spikes.
