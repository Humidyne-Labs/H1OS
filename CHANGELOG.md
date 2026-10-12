# Changelog & Code Modification Ledger

All notable changes to the ESP32-S3 Board Support Package (BSP), firmware architecture, and demonstration applications are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [2.1.0-alpha] - 2026-10-12

### 🚀 Added
- **SSD1681 E-Paper Maintenance & Scheduled Refresh Policy** (`sub_display.cpp/.h`, `orch_state.c/.h`, `orch_display_sync.c/.h`, `h1os_lvgl.cpp`, `h1os_lifecycle.c`, `Kconfig`):
  - Added anti-ghosting quota tracking (`epd_partial_refresh_count`) in persistent RTC Slow memory, automatically triggering a full OTP refresh after every 6 partial updates (`CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT`, default 6; guarantees full refresh $\le 24\text{h}$ at 4h max sleep) to reset residual DC bias.
  - Added long-term storage panel neutralization: implemented `sub_display_clear_to_white_full()` in Layer 2 and `h1os_shutdown_for_storage()` in Layer 4, driving the display to clean white (`0xFF`) before cutting power (`CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN`) to protect microcapsule chemistry against permanent dye migration.
- **Full Typography Suite Bold Weight & Strong Autohinting** (`tools/generate_1bpp_fonts.py`, `components/h1os/CMakeLists.txt`):
  - Updated font generator to discover and prioritize `Montserrat-Bold.ttf` across all point sizes (`14`, `16`, `18`, `20`, `24`, `32`).
  - Added `--autohint-strong` to all bilevel rasterization invocations across both Montserrat and DejaVu suites, generating solid 2-to-3-pixel stems and eliminating hairline dropouts and stroke erosion on 188 DPI monochrome electrophoretic glass.
- **Asynchronous Audio Worker Subsystem** (`sub_audio.c/.h`):
  - Dedicated FreeRTOS background task (`h1os_audio_worker`, 4 KB stack, priority 5) with thread-safe FreeRTOS command queue (`audio_cmd_t`).
  - Decoupled tone synthesis and chime presentation from the LVGL render loop, eliminating UI stutter and render blocking.
  - Added non-blocking asynchronous APIs: `sub_audio_play_tone_async()`, `sub_audio_play_chime_async()`, and `sub_audio_play_pcm_async()`.
  - Added raw 16-bit signed PCM audio clip playback (`sub_audio_play_pcm()` and `sub_audio_play_pcm_async()`) supporting dynamic sample rates, chunked I2S DMA streaming, and soft-mute ramps.
  - Added audio state queries and synchronization: `sub_audio_is_busy()`, `sub_audio_wait_idle()`, and `sub_audio_is_ready()`.
- **Dynamic Session Intervals** (`h1os.h`, `orch_state.c/.h`, `h1os_lifecycle.c`):
  - Added user-configurable `flow_a_period_sec` and `flow_b_period_sec` fields to `h1os_lifecycle_t.session` and `orch_persisted_state_t`.
  - Replaced hardcoded sleep timeouts with dynamic runtime intervals for Flow A telemetry sprints and Flow B UI presentation sessions.

### 🛠️ Fixed & Refactored
- **Deep Sleep Premature Wakeup & Dual-Period Sleep Policy** (`hal_io.c`, `orch_flow.c`):
  - Configured persistent RTC IO pull-ups (`rtc_gpio_init`, `rtc_gpio_set_direction(INPUT_ONLY)`, `rtc_gpio_pullup_en`, `rtc_gpio_pulldown_dis`) on `HAL_PIN_RTC_INT` (GPIO 5), `HAL_PIN_BUTTON_BOOT` (GPIO 0), and `HAL_PIN_BUTTON_POWER` (GPIO 18) during deep sleep pad isolation (`hal_io_isolate_sleep_pads()`). Because standard digital GPIO pull-ups lose power when `VDD3P3_CPU` drops, the open-drain PCF85063A INT pin previously floated LOW within seconds, triggering false `ESP_SLEEP_WAKEUP_EXT1` wakeups (<10s).
  - De-initialized RTC GPIO domain on wake in `hal_io_release_pad_holds()` (`rtc_gpio_deinit()`) to seamlessly restore pins to standard digital GPIO peripherals.
  - Implemented Dual-Period deep sleep coordination in `orch_flow_transition_to_sleep()`: the external PCF85063A is armed for the full display interval (`sleep_sec`), while the internal ESP32 timer is armed for the sub-interval telemetry period (`sample_interval_sec < sleep_sec`).
  - Implemented Sub-Sprint Truncation Discard Policy in `orch_flow_execute_sub_sprint()`: the internal timer rearms *only* if the next sprint timeout lands before external RTC countdown expiry (`next_sample_sec < rem_sec`). If the next sample lands at or after RTC expiry, rearming is discarded (`internal_sleep_sec = 0`), allowing the external PCF85063A interrupt line to trigger the main UI refresh cleanly without runt micro-wakes.
- **OS Diagnostics Typography Polish & Dual-Period Log Clarification** (`screen_diagnostics.c`, `orch_flow.c`):
  - Standardized Screen 4 (OS Diagnostics) to use high-contrast bilevel bold typography (`H1OS_FONT_14` Montserrat Bold) across all diagnostic rows (Reset reason, Wake causes, ULP, Heap, Stack HWM, Wakes counter, CPU/DFS), eliminating thin 1-pixel hairline stems from DejaVu regular.
  - Added explicit deep sleep log output distinguishing between the external RTC UI wake countdown (`sleep_sec` = 120s) and the internal headless sensor sprint timer (`internal_sleep_sec` = 60s).
- **Flow B Wake Cycle Differential Partial Refresh** (`h1os_lifecycle.c`, `h1os_lvgl.cpp/.h`, `sub_display.cpp/.h`, `orch_display_sync.c/.h`):
  - Implemented `sub_display_sync_previous_frame()` in Layer 2 to pre-synchronize SSD1681 hardware RAM `0x26` (Red / Previous RAM) with the pre-sleep frame over SPI DMA.
  - Linked `orch_display_sync_restore_to_framebuffer()` in Layer 3 into `h1os_lifecycle.c` Flow B wake dispatch, restoring the 5000-byte pre-sleep frame from flash partition `epd_frame`.
  - Configured `s_first_boot_flush = !is_wake_cycle` in `h1os_lvgl.cpp`, ensuring cold boots perform a full OTP wiping sequence while deep sleep wake cycles trigger silent ~300 ms differential partial refreshes with zero whole-screen flashing.
- **ES8311 Ready State Polling & Audio Clipping Remediation** (`sub_audio.c`):
  - Implemented `sub_audio_wait_until_ready()` validating Chip ID (`0xFD` = `0x83`, `0xFE` = `0x11`) and polling Register `0xFC` (`FLAG_CSM_CHIP`) bits 6:4 until the Chip State Machine exits state `S0` (Power Down).
  - Eliminates audio blips and clipped initial transients caused by streaming I2S frames before internal PLL and analog bias circuitry stabilize.
- **Hardware-Clean Pop-Free Audio Teardown** (`sub_audio.c`):
  - Implemented 5-step clean teardown sequence: 5 ms group delay drain $\rightarrow$ soft-mute (`0x31` `DAC_DSMMUTE = 0x40`) $\rightarrow$ 15 ms `DAC_RAMPRATE` volume ramp-down $\rightarrow$ `PA_CTRL` Class D amplifier mute (`GPIO 46` = 0) $\rightarrow$ ultra-low-power silicon standby (`<1.0 µA`).
  - Added `sub_audio_wait_idle()` synchronization to `h1os_shutdown()` and `orch_flow_transition_to_sleep()` to guarantee all audio pipelines drain and mute before battery latch release or sleep entry.
- **Keypad Long-Press Shutdown vs Navigation Remediation** (`main.c`):
  - Separated LVGL keypad events: `LV_EVENT_SHORT_CLICKED` exclusively advances screen navigation carousel with non-blocking feedback tones (`sub_audio_play_tone_async()`).
  - `LV_EVENT_LONG_PRESSED` triggers graceful power off (`h1os_shutdown()`) with atomic state latching to prevent re-entrant navigation loops.
- **Thermal Mitigation & Presentation Chime Masking** (`main.c`, `h1os_lifecycle.c`):
  - Restricted sleep/wake chime triggers strictly to Flow B application presentation cycles.
  - Defaulted `chime_mask` in `main.c` to boot and shutdown chimes only (`(1 << H1OS_CHIME_BOOT) | (1 << H1OS_CHIME_SHUTDOWN)`), suppressing sensor cavity self-heating during periodic sleep/wake cycles.
- **I2S Channel State Collision Remediation** (`sub_audio.c/.h`):
  - Added hardware state tracker `s_i2s_chan_enabled` and guarded all `i2s_channel_enable()` and `i2s_channel_disable()` transitions.
  - Guaranteed `sub_audio_standby()` is entered immediately after boot-time ES8311 register initialization, silencing audio clocks and preventing the `E (2871) i2s_common: i2s_channel_enable(1485): the channel has already enabled` fault on navigation click tones.
  - Added `sub_audio_deinit()` for complete teardown of worker tasks, command queues, and I2S peripherals.
- **Hardware SOF-Based USB Host & Charger Detection** (`hal_io.c/.h`, `sub_power.c/.h`, `h1os_lifecycle.c`):
  - Implemented Layer 1 `hal_check_usb_ll()` verifying live USB Full-Speed Start-Of-Frame (SOF) raw interrupt pulses and frame counter deltas over 1.5 ms.
  - Removed high-overhead `esp_driver_usb_serial_jtag` component dependency and tick hook overhead.
  - Combined USB host detection with Zero-Volt Cable Guard (`< 100 mV`) in `h1os_get_telemetry()`, preventing phantom 100% battery readings on UI when running on external USB power without an attached cell.

---

## [2.0.0-alpha] - 2026-10-10

### 🚀 Added
- **Clean-Slate 4-Layer Unidirectional Architecture**:
  - **Layer 1: HAL** (`hal_types.h`, `hal_io.c/.h`, `hal_i2c.c/.h`, `hal_spi.c/.h`, `hal_flash.c/.h`): Fixed-width types, RTC pad holds, thread-safe mutexed I2C Driver V2 on GPIO 47/48, 20 MHz DMA SPI Master, sector-aligned raw partition read/write for `epd_frame` (16 KB).
  - **Layer 2: Hardware Subsystem Managers** (`sub_display.cpp/.h`, `sub_sensor.c/.h`, `sub_rtc.c/.h`, `sub_power.c/.h`, `sub_audio.c/.h`): SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26), partial waveform LUT (0x32), GPIO 8 BUSY semaphore ISR synchronization, glass thermistor read (0x1B), SHTC3 NIST physical read with CRC-8, MCU TSENS silicon temperature, PCF85063A POSIX timekeeping & countdown timer, 12 dB attenuated battery ADC with 16-sample trimmed outlier filtering, ES8311 software standby (<1.0 µA @ Reg 0x0D).
  - **Layer 3: System Pipeline & Orchestrator** (`orch_state.c/.h`, `orch_math.c/.h`, `orch_flow.c/.h`, `orch_display_sync.c/.h`): RTC Slow SRAM state (<512 B), 32-slot Tri-Node ring buffer, August-Roche-Magnus invariant psychrometric equations, continuous recursive EWMA filter, Flow A/B arbiter with Zero-Hour collision hand-off, Thermal Lockout MUX, deferred dirty flash frame sync engine.
  - **Layer 3: ULP-RISC-V Coprocessor Hardware Monitor** (`ulp/main.c`, `ulp/CMakeLists.txt`): Coprocessor firmware running autonomously in RTC Slow SRAM for battery ADC threshold monitoring (`ADC1_CH3`), hardware RTC arbitration (`GPIO 5`), and button debounce (`GPIO 0/18`), embedded via `ulp_embed_binary()`.
  - **Layer 3: RTC Fast Memory Deep Sleep Wake Stub** (`orch_wake_stub.c/.h`): `RTC_IRAM_ATTR` wake stub running directly from RTC Fast Memory (<3ms execution) on deep sleep timer wake, executing register-level bit-bang I2C sensor sampling without powering flash cache or booting FreeRTOS.
  - **Layer 4: Application Lifecycle API** (`bsp.h`, `bsp_common.c`): `bsp_app_start()`, `bsp_app_sleep()`, `bsp_app_shutdown()`, and unified getter `bsp_app_get_telemetry()`.
- **Thick 14pt Montserrat Font** (`bsp_font_montserrat_14_1bpp.c`):
  - Re-rasterized using `npx lv_font_conv` from `Montserrat-Bold.ttf` with fast-kern tables and FontAwesome icons, resolving thin 1-pixel stroke illegibility on 200x200 monochrome e-paper.

### 🛠️ Fixed & Refactored
- **Keep All Gates Open Policy Enforced**:
  - Permanently asserted `BAT_CTRL` (`GPIO 17` = 1) and `EPD_3V3_EN` (`GPIO 6` = 0) with RTC pad holds during sleep.
  - Audio Domain `PA_EN` (`GPIO 42` = 0) kept held LOW across sleep to prevent ES8311 ESD protection diodes from forward-biasing and clamping shared I2C bus (`GPIO 47/48`) to ~0.7V. ES8311 enters software standby (<1.0 µA) without hard power cut.
- **Deep Sleep Wake Lifecycle Dispatch**:
  - Fixed legacy bug in `bsp_app_start()` where `ESP_RST_DEEPSLEEP` fell into `bsp_power_off()`; now correctly restores dirty frame buffer and dispatches `on_wake()`.
- **Legacy Code Purged (Component Cleansing)**:
  - Completely purged 16 obsolete legacy duplicate source and header files from `components/esp32-s3_bsp/`:
    `bsp_sensors.c/.h`, `bsp_equ_math.c/.h`, `bsp_env_telemetry.h`, `bsp_rtc.c/.h`, `bsp_rtc_mem.c/.h`, `bsp_i2c.c/.h`, `bsp_display.cpp/.h`, `bsp_audio.c/.h`, `pinout.h`.
  - Decoupled and rewired remaining higher-level modules (`bsp_common.c`, `bsp_power.c`, `bsp_button.c`, `bsp_sdcard.c`, `bsp_time.c`, `bsp_lvgl.cpp`) to Layer 1 HAL primitives (`hal_types.h`, `hal_io.h`, `hal_i2c.h`), Layer 2 Subsystems (`sub_sensor`, `sub_rtc`, `sub_display`, `sub_power`, `sub_audio`), and Layer 3 Orchestrators (`orch_state`, `orch_flow`, `orch_display_sync`).
  - Preserved historical code in `legacy_reference/` as an immutable reference backup.
- **H1OS Transition & Architecture Elevation**:
  - Formally rebranded platform to **H1OS** (Class-E Environmental Operating System) under Semantic Versioning `1.0.0-alpha`.
  - Introduced primary master umbrella header [`h1os/h1os.h`](components/esp32-s3_bsp/include/h1os/h1os.h) exposing declarative lifecycle entry points (`h1os_start()`, `h1os_get_telemetry()`, `h1os_sleep()`, `h1os_shutdown()`).
  - Migrated flagship demonstration application to `examples/H1OS` with `project(h1os)`.
  - Rewrote `examples/H1OS/main/main.c` to consume telemetry exclusively through `bsp_app_get_telemetry(&telem)` and log H1OS startup branding.
  - Successfully compiled and linked `h1os.elf` with Ninja under ESP-IDF v6.1 dev profile (`build_dev/`).
- **Low-Level Peripheral Verification & Register Truth Audit**:
  - Created `docs/perf_and_drivers/` with 8 comprehensive physical hardware specifications documenting every IC's init, deinit, runtime, sleep, and register parameters.
  - **PCF85063A (`sub_rtc.c`)**: Corrected countdown timer clock frequency prescaler (`TCF`) bit shifting into bits `[4:3]` (`(2 << 3)` for 1Hz and `(3 << 3)` for 1/60Hz); removed incorrect `TIE` bitmask from `Control_2` (bit 2 is `COF[2]`); added 12.5pF crystal capacitance selection (`CTRL1_CAP_SEL_12_5PF`) in `Control_1`.
  - **SSD1681 (`sub_display.cpp` & `hal_spi.c`)**: Properly split factory 159-byte partial LUT across registers `0x32` (153B), `0x3F` (1B), `0x03` (1B), `0x04` (3B), and `0x2C` (1B); configured display option `0x37` and border waveform `0x3C` (`0x80`); used differential refresh sequence `0xCF`; added 2 MHz 3-wire half-duplex SPI device handle and continuous CS hold for on-glass thermistor readout (`0x1B`).
  - **ES8311 & NS4168 (`sub_audio.c`)**: Implemented complete 22-register reference clock tree and analog bias initialization; enforced `PA_EN` (`GPIO 42` = 0) and muted `PA_CTRL` (`GPIO 46` = 0); ported 15-register zero-heat deep standby sequence (<1.0 µA); documented I2S root clock `PLL_160M` dependency and verified that ESP-IDF's automatic `ESP_PM_APB_FREQ_MAX` lock prevents DFS pitch drops and sample rate stretching during active tone streaming.
  - **Power & Battery (`sub_power.c` & `hal_io.c`)**: Aligned 13-point LiPo OCV lookup table with calibrated hardware reference; enforced RTC peripheral power domain retention (`ESP_PD_DOMAIN_RTC_PERIPH`) across deep sleep to lock `BAT_CTRL` latch (`GPIO 17` = 1).
  - **Hardware Pull-Up Alignment**: Formally documented external 100 kΩ pull-ups on `GPIO 0` (BOOT) and `GPIO 18` (POWER) in `docs/perf_and_drivers/07_tactile_buttons_and_led.md` and `hal_io.c`; verified external 4.7 kΩ pull-ups on `GPIO 47/48` (I2C) with internal pull-ups disabled in `hal_i2c.c`.

---

## [1.3.1] - 2026-10-09

### 🛠️ Fixed & Refactored
- **Deterministic Two-Flow Cadence & Sleep Freeze Remediation** ([`bsp_power.c`](components/esp32-s3_bsp/src/bsp_power.c), [`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - **Eliminated Unbounded Button Release Loop**: Fixed the 5-minute device hang where `bsp_enter_sleep()` executed an unbounded `while (gpio_get_level(BOOT) == 0 || gpio_get_level(POWER) == 0)` loop on headless sprints without configured digital input buffers. Bypassed button checking completely for Flow A (`BSP_INIT_MODE_MINIMAL`) and bounded Flow B checking to a hard 200 ms timeout (max 4 iterations $\times$ 50 ms).
  - **Zero-Hour Collision & Handoff Resolution**: When both Flow A (internal timer: 60s) and Flow B (external PCF85063A countdown timer: 120s / IRL) arrive at zero hour, the $<10\,\text{ms}$ cold sensor sprint always executes first out of deep sleep, queries the PCF85063A over I2C, and promotes cleanly to Flow B.
  - **Flow B Timer Invalidation**: Whenever Flow B wakes (via external RTC alarm, button press, or sprint promotion), it immediately cancels Flow A's internal sleep timer via `esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER)`, preventing premature timer interrupts.
  - **Pure I2C Headless Sprint**: Stripped unnecessary GPIO ISR registration and button sampling from `bsp_hot_wake_sprint_init()`. The sensor sprint exclusively manages I2C and SHTC3/PCF85063A registers, leaving button GPIO configuration strictly to `bsp_io_early_init()` in Flow B.
  - **Preserved Bootloader Power Ownership**: Maintained authoritative bootloader control of power gates (`GPIO 17` Power Hold, `GPIO 6` EPD/Sensor 3.3V, `GPIO 42` Audio) with pad holds in $<25\,\text{ms}$, allowing only `bsp_power_off()` to de-assert `GPIO 17 = 0` on intentional shutdown.

---

## [1.3.0] - 2026-10-09

### 🚀 Added
- **Class-E Environmental Hygrometer Architecture** ([`bsp_sensors.h`](components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [`bsp_sensors.c`](components/esp32-s3_bsp/src/bsp_sensors.c)):
  - Redesigned the environmental sensing subsystem into an ultra-low-power **Class-E Hygrometer** with strict zero runtime I2C polling during active UI and Turbo execution.
  - Implemented 1-cycle integer raw ADC differential gating (`SHTC3_RAW_IS_SETTLED`: 562 LSB counts / $1.50^\circ\text{C}$ margin) executing in $<10\,\text{ms}$ on 60s hot-wakes.
  - Added 64-bit clean window bitmask (`window_clean_mask`) tracking cold, unperturbed sample slots across the ring buffer.
  - Added complete Kelvin outputs (`ambient_temp_k`, `dew_point_k`) alongside Celsius and Fahrenheit for cloud telemetry.
  - Exposed universal temperature conversion macros: `C_TO_F`, `F_TO_C`, `C_TO_K`, `K_TO_C`, `K_TO_F`.
- **4-Byte Packed Sample Ring Buffer** ([`bsp_env_telemetry.h`](components/esp32-s3_bsp/include/bsp/bsp_env_telemetry.h)):
  - Optimized sample storage into 4-byte packed struct (`bsp_env_compact_sample_t` with `raw_temp_u16` and `raw_rh_u16`).
  - Reduced total 64-sample telemetry struct footprint in RTC Slow Memory to 288 bytes (saving 480 bytes vs legacy 12-byte struct).
- **Consolidated Psychrometrics & Sliding Window Math Engine** ([`bsp_equ_math.h`](components/esp32-s3_bsp/include/bsp/bsp_equ_math.h), [`bsp_equ_math.c`](components/esp32-s3_bsp/src/bsp_equ_math.c)):
  - Added `bsp_math_calc_sliding_window_metrics()` calculating average temperature ($T_{\text{avg}}$), baseline floor ($T_{\text{floor}}$), ceiling ($T_{\text{ceiling}}$), $\text{RH}_{\min}$, $\text{RH}_{\max}$, and clean settled sample rate ($0\dots 60\,\text{smp/h}$) across clean slots.
  - Dual EWMA smoothing ($\alpha = 0.35$) for high-stability display and cloud reporting.
- **Non-Blocking PXE Button Engine & ROM Bootloader Jump** ([`main.c`](examples/Unified_Environmental_Demo/main/main.c), [`bsp_power.h`](components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - `app_on_pxe()` only clocks GPIO levels if pins are actively held LOW, eliminating cold-boot latency ($0\,\text{ms}$ overhead on released buttons).
  - BOOT0 (`GPIO 0`) held $\ge 1.2\,\text{s}$ cleanly forces reboot into silicon ROM Download Bootloader (`bsp_system_reboot_to_bootloader()`).
  - BOOT0 short press ($< 400\,\text{ms}$) immediately toggles active dashboard screens ($1/2 \leftrightarrow 2/2$).
  - POWER (`GPIO 18`) held $\ge 1.2\,\text{s}$ initiates graceful shutdown (`bsp_power_off()`).

### 🛠️ Fixed & Refactored
- **Automated LVGL Display Refresh Gating** ([`bsp_lvgl.cpp`](components/esp32-s3_bsp/src/bsp_lvgl.cpp)):
  - Automatic full OTP vs. differential partial refresh arbitration in `lvgl_display_flush_cb()` based on `s_first_boot_flush` and `bsp_display_get_partial_count() >= PARTIAL_REFRESH_LIMIT` (30).
- **Nomenclature & API Modernization**:
  - Completely excised legacy 'tri-node' and 'windex' terminology from headers, sources, and UI demos in favor of the clean Class-E unified sensor API (`bsp_sensors_read()`, `bsp_sensors_sample_raw()`) and clean window gating (`window_clean_mask`, `is_clean_window`, `"Gate: PASS (Window: CLEAN)"`).
  - Screen 2 dashboard updated to display live Clean Window status, clean sample count, and settled rate per hour.

---

## [1.2.2] - 2026-10-08

### 🚀 Added
- **Multi-Rail Bootloader Latch System** ([`bsp_boot_hook.c`](components/esp32-s3_bsp/bootloader_components/bsp_boot_hook/bsp_boot_hook.c)):
  - Extended 2nd-stage bootloader hook (`bootloader_before_init()`) to assert and latch all primary board power gates in $< 25\,\text{ms}$ of initial power-up:
    - `BSP_PIN_POWER_HOLD` (`GPIO 17`): Driven HIGH (`1`) with RTC pad latch.
    - `BSP_PIN_EPD_3V3_EN` (`GPIO 6`): Driven LOW (`0` = 3.3V ON) with pad latch.
    - `BSP_PIN_PA_EN` (`GPIO 42`): Driven LOW (`0` = Audio Domain ON) with pad latch to prevent I2C clamping on codec reset.
- **SHTC3 Turbo Mode Interlock & Strict Thermal Lockout Gatekeeper** ([`bsp_sensors.c`](components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_power.c`](components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - Added `bsp_pm_is_turbo_active()` to query CPU 240 MHz scaling lock status.
  - Implemented strict hardware interlock in `shtc3_execute_raw_acquisition()`, `bsp_sensors_read_tri_node()`, and `bsp_shtc3_read_lp()` that **blocks all physical SHTC3 I2C polling while the CPU is in Turbo mode** (`ESP_ERR_INVALID_STATE` or cached fallback).
  - Enforced strict thermal gating against ungated live sampling: during active wake / thermal lockout (`bsp_sensors_is_in_thermal_lockout()`), live I2C acquisition is intercepted and transparently serves the pristine unperturbed cold reading from RTC memory.
- **SHTC3 Decoupled Hot-Wake Sampling & Buffered Psychrometrics** ([`bsp_sensors.c`](components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_sensors.h`](components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - Added `bsp_sensors_hot_wake_sample()` for headless 60s hot-wake sprints: performs fast raw SHTC3 I2C acquisition, CRC-8 verification, and commits raw readings to RTC Slow Memory in $<12\,\text{ms}$ without CPU-intensive floating-point psychrometrics.
  - Deferred all psychrometric derivations (Dew Point, Absolute Humidity, Ambient Reconstructed RH, Thermal Delta, and Confidence Score) to full UI wake inside `bsp_sensors_read_tri_node()`, consuming the buffered sample and cross-referencing TSENS die and on-glass temperatures.
- **Dual-Page Interactive Dashboard** ([`main.c`](examples/Unified_Environmental_Demo/main/main.c)):
  - Implemented multi-screen UI with instant toggling via **BOOT0 button click** and state persistence across deep sleep wakes in RTC Slow RAM (`s_app_state.active_page`):
    - **Screen 1 (1/2)**: `HUMIDYNE LABS 1/2` header, primary ambient temperature (°F / °C) and humidity (%RH), psychrometric calculations (Dew Point, Absolute Humidity), and full multi-node temperatures in both Celsius and Fahrenheit (`Glass: 25.1°C Die: 23.8°C`, `Glass: 77.2°F Die: 74.8°F`).
    - **Screen 2 (2/2)**: `HUMIDYNE LABS 2/2` header, primary calibrated battery voltage & SoC percentage, discharge rate (`mV/h`), calculated sleep average current draw (`uA`), and acquisition sample rates (`smp/h`).
- **PXE BOOT0 Long-Press ROM Download Bootloader Jump** ([`bsp_power.h`](components/esp32-s3_bsp/include/bsp/bsp_power.h), [`bsp_power.c`](components/esp32-s3_bsp/src/bsp_power.c), [`main.c`](examples/Unified_Environmental_Demo/main/main.c)):
  - Added `bsp_system_reboot_to_bootloader()` which sets the hardware `RTC_CNTL_FORCE_DOWNLOAD_BOOT` register flag (`RTC_CNTL_OPTION1_REG`) and restarts, forcing the silicon ROM bootloader directly into **USB/UART Download Bootloader Mode** when BOOT0 is held for $\ge 1.5\,\text{s}$ upon waking or booting.
- **Manual Rail Control & Override APIs** ([`bsp_power.h`](components/esp32-s3_bsp/include/bsp/bsp_power.h), [`bsp_power.c`](components/esp32-s3_bsp/src/bsp_power.c)):
  - Added user-level functions `bsp_power_set_latch(bool)`, `bsp_power_set_epd_rail(bool)`, and `bsp_power_set_pa_rail(bool)` for programmatic assertion/deassertion of power rails with automatic digital and RTC pad hold management.

### 🛠️ Fixed & Refactored
- **Active-LOW Display Power Gate Inversion** ([`bsp_display.cpp`](components/esp32-s3_bsp/src/bsp_display.cpp)):
  - Fixed logic inverted bug in `display_power_enable(bool enable)` where `enable == true` was driving `1` (shutting OFF power to the SSD1681 and SHTC3) and returning `true` only when the rail was disabled. Corrected to drive `0` (ON) and verify level is `0`.
- **Synchronous LVGL Render Enforcement** ([`main.c`](examples/Unified_Environmental_Demo/main/main.c)):
  - Uncommented `lv_refr_now(NULL)` in `render_environmental_ui()` and `render_shutdown_ui()` to ensure LVGL renders widgets to the SSD1681 framebuffer immediately before deep sleep entry.
- **Persistent RTC GPIO 17 Hold in Early IO** ([`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - Reinforced `bsp_io_early_init()` to explicitly drive `GPIO 17` HIGH, disable sleep isolation (`gpio_sleep_sel_dis`), and lock with `rtc_gpio_hold_en()` during application runtime.

---

## [1.2.1] - 2026-10-08

### 🚀 Added
- **Zero-Management Bootloader Power Latch Hook** ([`bsp_boot_hook.c`](components/esp32-s3_bsp/bootloader_components/bsp_boot_hook/bsp_boot_hook.c), [`CMakeLists.txt`](components/esp32-s3_bsp/CMakeLists.txt)):
  - Built-in 2nd-stage bootloader hook (`bootloader_before_init()`) asserting `GPIO 17` (`BSP_PIN_POWER_HOLD`) HIGH and engaging the hardware RTC pad hold latch (`gpio_ll_hold_en`) within $\approx 25\,\text{ms}$ of power-on.
  - Automatically registered into the ESP-IDF bootloader build system via `BOOTLOADER_EXTRA_COMPONENT_DIRS`, eliminating application-level bootloader configuration and preventing battery LDO brownouts.
- **Modular Hot-Wake Build-Up & Clean-Up Lifecycle** ([`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - Implemented `bsp_hot_wake_sprint_init()` and `bsp_hot_wake_sprint_deinit()` to cleanly isolate hot-wake peripheral resources (I2C + SHTC3 + promotion ISRs) and restore hardware to a pristine POR state before sleep entry or promotion to full UI wake.
- **Pre-Execution (PXE) Lifecycle Hook** ([`bsp.h`](components/esp32-s3_bsp/include/bsp/bsp.h), [`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - Added `.on_pxe(btn_mask, user_data)` callback and `bsp_button_mask_t` (`BSP_BUTTON_MASK_NONE`, `BSP_BUTTON_MASK_BOOT`, `BSP_BUTTON_MASK_POWER`, `BSP_BUTTON_MASK_BOTH`) for instant boot-time tactile button state detection before subsystem initialization.

### 🛠️ Fixed & Refactored
- **Automatic Shutdown Callback Registration** ([`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c), [`bsp_power.c`](components/esp32-s3_bsp/src/bsp_power.c)):
  - Fixed bug where `lifecycle.on_shutdown` was never wired to `bsp_power_register_shutdown_cb()`. `bsp_power_off()` now executes the application's shutdown hook, rendering the persistent shutdown splash screen on the EPD glass before releasing the power latch.
- **Two-Phase IO Bring-Up Decoupling** ([`bsp_common.c`](components/esp32-s3_bsp/src/bsp_common.c)):
  - Separated Phase 1 Early Base IO (`bsp_io_early_init()`) for button pull-up configuration from Phase 2 Master IO (`bsp_init_io()`) for peripheral rails, removing redundant runtime manipulation of the latched power hold pin.

---

## [1.2.0] - 2026-10-07

### 🚀 Added
- **Tri-Node Thermal Sensing Architecture** ([`bsp_sensors.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h)):
  - Integrated three physical sensing nodes: Node 1 (PCB-mounted SHTC3), Node 2 (SSD1681 on-glass thermal sensor), and Node 3 (ESP32-S3 internal TSENS silicon die).
  - Multi-node thermal sanity cross-checking and dynamic thermal confidence scoring ($0\dots 100\%$).
- **Thermodynamic Psychrometric Invariant Engine** ([`bsp_equ_math.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_equ_math.c), [`bsp_equ_math.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_equ_math.h)):
  - Standalone mathematical processing module based on vapor pressure conservation ($\gamma(T, RH)$, Magnus-Tetens dew point calculation, and ambient RH reconstruction).
  - Absolute humidity calculations ($g/m^3$) and Exponentially Weighted Moving Average (EWMA $\alpha = 0.25$) filtering.
- **Dynamic Frequency Scaling (DFS) & Turbo PM Locks** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - Established 80 MHz quiet baseline CPU operating frequency (`CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_80=y`, `CONFIG_PM_ENABLE=y`) dropping active current from ~80 mA down to ~28 mA.
  - Implemented `bsp_pm_turbo_acquire()` and `bsp_pm_turbo_release()` using `ESP_PM_CPU_FREQ_MAX` PM locks to burst Xtensa to 240 MHz exclusively during compute-heavy LVGL rendering and E-Paper SPI transfers.
- **Pure Hardware Countdown Timer & Bounded Sleep Engine** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h), [`bsp_rtc.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_rtc.c)):
  - Replaced calendar time-of-day alarm matching with the dedicated **PCF85063A Hardware Countdown Timer** (`bsp_rtc_set_countdown_timer()`), operating purely on the 32.768 kHz quartz crystal with zero dependency on calendar time, POSIX clock state, or 24-hour rollover math.
  - Defined and enforced global BSP hardware sleep duration bounds: **120 seconds** (`BSP_SLEEP_MIN_DURATION_SEC = 120` / 2 min) up to **4 hours** (`BSP_SLEEP_MAX_DURATION_SEC = 14400` / 240 min) via 1/60Hz prescaling.
  - Automatically clamps out-of-bounds user sleep requests within `[120s, 14400s]` with informative log warnings.
- **Display Driver NULL SPI Handle Safety Guard** ([`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp)):
  - Added strict `if (s_spi_handle == NULL) return;` guard to `bsp_display_deep_sleep()`, preventing kernel panics and crash-reboot loops when returning to deep sleep during minimal headless hot-wake sprints (`BSP_INIT_MODE_MINIMAL`).
- **Internalized 60s Hot-Wake Sprint Engine & Hardware GPIO ISR Promotion** ([`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - Fully internalized the 60-second headless hot-wake sensor sprint inside `bsp_app_start()`, autonomously capturing NIST SHTC3/Tri-Node samples into RTC Slow Memory without invoking application-level wake hooks or activating the EPD display.
  - Implemented the **Hardware GPIO ISR Promotion Engine**: arms negative-edge ISR handlers on `RTC_INT` (`GPIO 5`), `BOOT` (`GPIO 0`), and `POWER` (`GPIO 18`) throughout the active SHTC3 I2C transaction. After clean sprint deinit and sensor sleep, checks the atomic promotion flag to immediately promote any concurrent alarm or button event to `BSP_INIT_MODE_FAST` for guaranteed **zero lost wakeups**.
  - Documented SHTC3 PCB ground plane self-heating physics ($+1.5^\circ\text{C}\dots +3.0^\circ\text{C}$) directly in `bsp_sensors.h` developer guidance.
- **Dual-Wake & Two-Branch Firmware Architecture** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c), [`bsp_rtc_mem.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_rtc_mem.h), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - Implemented simultaneous dual deep-sleep wake triggers: Internal 60s RTC timer (`ESP_SLEEP_WAKEUP_TIMER`) reserved exclusively for hot-wake sprints + External PCF85063A RTC Alarm (`ESP_SLEEP_WAKEUP_EXT1`) reserved for user application scheduling.
  - Added `BSP_INIT_MODE_MINIMAL` to bypass SPI display and FreeRTOS LVGL tasks during headless 60s sensor sprints.
- **Sub-15ms Firmware "Sleep-Sprint" Engine** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - Enabled deep sleep fast wake stub (`esp_set_deep_sleep_wake_stub_default_entry()` / `esp_deep_sleep_disable_rom_logging()`) for ultra-rapid resume.
  - SHTC3 fast-mode acquisition (`0x44DE`) delivering sub-15ms raw sensor reads with total energy $< 1.5\text{ mJ}$ ($< 0.005^\circ\text{C}$ ground plane rise), eliminating PCB thermal soak.
- **SSD1681 Hardware On-Glass Temperature Readout** ([`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp)):
  - Half-duplex 4-wire SPI read driver implementing SSD1681 command `0x1B` via dedicated `s_spi_read_handle`.
- **Unified Environmental Monitor Demo** ([`examples/Unified_Environmental_Demo/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/)):
  - Dedicated demonstration application featuring pure physical telemetry: directly measured $V_{\text{bat}}$ (V / %), active CPU wake execution latency (ms), exact PCF85063A POSIX uptime, sample cycle counter, and tri-node environmental metrics.
  - Built-in `CONFIG_ENABLE_DEV_CONTINUOUS_MODE` switch to bypass deep sleep with FreeRTOS delays for uninterrupted serial logging during development.
  - Automatic critical battery shutdown guard ($\le 10\%$ SoC / $< 3400\text{ mV}$).

### 🛠️ Changed & Refactored
- **Persistent Environmental Telemetry Modernization** ([`bsp_env_telemetry.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_env_telemetry.h), [`bsp_sensors.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h)):
  - Replaced obsolete `bsp_ulp_shared.h` with `bsp_env_telemetry.h`, modernizing the persistent 64-entry RTC Slow Memory sample ring buffer (`bsp_env_telemetry_history_t`, `bsp_env_raw_sample_t`).
  - Standardized public telemetry APIs to `bsp_sensors_get_telemetry_history()` and `bsp_sensors_get_sample_count()`.
- **EPD UI Gated Sample Counter** ([`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - Replaced the transient `Sprint: %lums` badge on Row 1 ($y=140$) with a verified **Thermal-Gated Sample Counter** (`SMP: %lu`) reflecting verified environmental acquisitions logged in the RTC ring buffer.
- **EPD Partial Refresh Overhaul & Differential Erase Fix** ([`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp), [`bsp_lvgl.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_lvgl.cpp)):
  - Aligned SSD1681 partial update command sequence to use `0x22 0xCF` (Pattern Display Mode 2) and Ping-Pong differential scanning (`0x37 = 0x40`, `0x3C = 0x80`, `WF_PARTIAL_1IN54`), writing to `0x24` (New RAM) only.
  - Eliminated the cumulative "typewriter newspaper" text overlay bug by ensuring the hardware differential comparator drives previous black pixels cleanly back to white (`LUT1` $0 \to 1$).
  - Restricted OTP master activation (`0x22 0xB1` + `0x20`) strictly to cold boot; suppressed `0x20` on wake boot to eliminate whole-screen flashing.
- **Power Management & Shutdown State Cleanliness** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_button.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_button.c)):
  - Refactored `bsp_power_off()` to de-assert latch `GPIO 17 = 0`, release all GPIO holds, clear PCF85063A countdown timers and alarms, wipe RTC Slow Memory state via `bsp_rtc_mem_reset()`, and ensure next power-up starts fresh in cold boot.
  - Fixed power button long-press detection and initial boot wait-for-release state (`STATE_BOOT_WAIT_RELEASE`).
- **Audio Subsystem Zero-Heat Standby** ([`bsp_audio.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_audio.c)):
  - Configured zero-heat software power-down sequence for ES8311 codec and NS4150B amplifier ($\le 1\,\mu\text{A}$ quiescent draw) while maintaining active 3.3V rail on GPIO 42 (`PA_EN = 0`) to prevent clamping on shared I2C lines.
- **RTC Memory Re-Partitioning** ([`bsp_rtc_mem.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_rtc_mem.c)):
  - Relocated 5,000-byte E-Paper frame buffer to RTC Fast Memory (`RTC_FAST_ATTR`), freeing 61% (5 KB) of RTC Slow SRAM for clean sensor ring buffers.

### 🗑️ Removed & Deprecated
- **Purged Obsolete ULP MUX Arbitration Routines** ([`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [`bsp_sensors.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sensors.c)):
  - Deleted `bsp_ulp_mux_set_app_active()`, `bsp_ulp_mux_set_bus_locked()`, `bsp_ulp_mux_is_app_active()`, and `bsp_ulp_mux_set_substrate_hot()`.
- **Decommissioned ULP RISC-V Coprocessor Subsystem**:
  - Permanently removed the ULP toolchain embedding and coprocessor loader due to physical hardware routing constraint (Waveshare SHTC3 bus is hardwired to digital `GPIO 47/48`, outside the ESP32-S3 `RTCIO 0..21` power domain). Replaced with zero-heat 80 MHz DFS Fast-Boot Sleep-Sprint engine.
- **Removed Synthetic Calibration**: Purged obsolete synthetic thermal divider heuristic (`bsp_sensor_cal.c` / `bsp_sensor_cal.h`) in favor of physics-based psychrometric invariant engine.
- **Removed Speculative Math**: Eliminated assumed 280 µA current consumption modeling and estimated battery runtime days from UI in favor of directly measurable physical telemetry.

---

## [1.1.0] - 2026-10-02

### 🚀 Added
- **Structured Application Lifecycle Engine** ([`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c)):
  - Added `bsp_app_start()` with structured callbacks (`on_cold_boot`, `on_wake`, `on_before_sleep`, `on_shutdown`).
- **Hardware Profile Init Engine**:
  - Modular init modes: `BSP_INIT_MODE_FULL`, `BSP_INIT_MODE_FAST`, `BSP_INIT_MODE_SENSORS_ONLY`, `BSP_INIT_MODE_OFFLINE`.
- **Audio Tone Synthesis & Chime System** ([`bsp_audio.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_audio.c)):
  - 256-point sine table with attack/decay envelope smoothing.
- **Fast Wi-Fi Reconnect & BLE Provisioning** ([`bsp_wifi.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_wifi.c), [`bsp_prov.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_prov.c)):
  - RTC Slow Memory state caching for sub-400ms Wi-Fi reconnection.
  - BLE GATT provisioning compatible with Chrome Web Bluetooth.
- **ThingsBoard MQTT & HTTPS OTA** ([`bsp_tb.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_tb.c), [`bsp_ota.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_ota.c)):
  - Telemetry publishing, 6-8 character claiming key workflow, and remote firmware OTA state machine.

---

## [1.0.0] - 2026-09-25

### 🚀 Added
- Initial baseline BSP release for Waveshare ESP32-S3-Touch-ePaper-1.54 V2 (`ESP32-S3-PICO-1-N8R8`).
- Basic drivers for SSD1681 e-Paper, SHTC3 sensor, PCF85063A RTC, ES8311 Audio Codec, FT6336 Capacitive Touch, SD Card SPI, and NVS Storage.
