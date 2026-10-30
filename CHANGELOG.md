# Changelog & Code Modification Ledger

All notable changes to the ESP32-S3 Board Support Package (BSP), firmware architecture, and demonstration applications are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.4.7-dev] - 2026-10-29

### 🛡️ Fixed & Hardened (Post-Audit `TST_005` Codec Sleep Persistence & Acoustic Playback Truncation Remediation)

* **Authoritative Espressif `es8311_suspend()` Register Sequence & Post-Button-Wake Deep Standby Persistence (`ERR-S8` / `S0`)** (`sub_audio.c`, `docs/drivers/03_audio.md`, `ERRATA.md`):
  * Resolved the post-audit hardware defect observed in `TST_005_IMGS_POST-AUDIT-THERMAL` (`IMG261029161459.bmp` – `IMG261029161752.bmp` and `internal_thermal_note.md`) where the ES8311 codec (`U10`) entered low-power sleep after Cold Boot (`28.5°C` $ightarrow$ `26.2°C` floor) but remained awake at `30.2°C–32.1°C` after a tactile button wake's 30-second inactivity timeout and across subsequent Flow B cycles.
  * **Root Cause 1 (CSM Reset `0x00 = 0x1F` Reverting `Reg 0x0D` to `0xFA`):** Cross-referencing `s_es8311_deinit[]` against the official Espressif reference driver (`_3rd_party_ref_codec/es8311.c:222-240`, `es8311_suspend()`) revealed that when `REG00` is `0x80` (`CSM_ON = 1`), writing `{0x0D, 0xFC}` *before* `{0x00, 0x1F}` causes the internal Chip State Machine (`CSM`) reset transition (`0x00 = 0x1F`, `RST_DIG = 1`) to revert `Reg 0x0D` back to its pre-charge state (`0xFA`: `PDN_VREF = 0`, `VMIDSEL = 10b` active VMID reference). `s_es8311_deinit[]` now strictly follows `es8311_suspend()`: it writes `{0x0D, 0xFA}`, executes the CSM reset and clock gating handshake (`{0x02, 0x10}` $ightarrow$ `{0x00, 0x00}` $ightarrow$ `{0x00, 0x1F}` $ightarrow$ `{0x01, 0x30}` $ightarrow$ `{0x01, 0x00}`), and writes `{0x45, 0x03}`, **`{0x0D, 0xFC}`**, and `{0x02, 0x00}` **after** `{0x00, 0x1F}` and `{0x01, 0x00}`, holds `MCLK` for `2 ms`, and then disables `s_tx_chan`.
  * **Root Cause 2 (Unattended Flow B Bypass & Unclocked Re-Init Elimination):** Removed the I2C readback re-init trigger in `sub_audio_standby()` on unattended Flow B wakes (`!s_audio_inited && s_rtc_codec_in_standby && esp_reset_reason() == ESP_RST_DEEPSLEEP`). When `Reg 0x0D` reverted to `0xFA` in `v2.4.6-dev`, `sub_audio_standby()` attempted to re-write `s_es8311_deinit[]` on every unattended Flow B wake while `s_tx_chan == NULL` (no `MCLK`). Unattended Flow B wakes now completely bypass both `sub_audio_init()` and `sub_audio_standby()` I2C traffic, allowing the `<1.0 µA` codec sleep state to persist undisturbed across all sleep cycles (`internal_thermal_note.md` Item B).
  * **Default Low-Power Mode & Unused Microphone Power-Down (`internal_thermal_note.md` Item C):** Verified that `sub_audio_init()` starts the ES8311 in low-power operating mode (`s_low_power_mode = true`, `Reg 0x0F = 0xFF`) with the unused analog/digital microphone path powered off and muted (`Reg 0x0E = 0x62` [`PDN_PGA = 1, PDN_MOD = 1`], `Reg 0x14 = 0x00` [`LINSEL = 0, DMIC_ON = 0, PGAGAIN = 0`], `Reg 0x17 = 0x00`, `Reg 0x0A = 0x4C` [`SDPOUT_MUTE = 1`]).
* **Elimination of `50 ms` Button Chirp & Cold Boot Chime Acoustic Truncation (`ERR-S8` / `S0`)** (`sub_audio.c`):
  * Resolved the objective audio truncation reported in `internal_thermal_note.md` where `50 ms` tactile button chirps (`1046 Hz`) were cut off mid-tone and the first note (`523 Hz, 70 ms`) of the Cold Boot chime was clipped at the start.
  * **Root Cause 1 (`64 ms` I2S DMA Ring Buffer vs. `50 ms` Chirp & Premature `PA_CTRL` Shutdown):** The I2S TX channel uses `4` DMA descriptors of `256` samples each (`1024 samples = 64 ms` at `16 kHz`). A `50 ms` chirp (`800 samples`) is copied into the empty DMA descriptors in `< 1 ms`. In `v2.4.6-dev`, `sub_audio_flush_frame()` queued only `1` silent frame (`16 ms`) + `20 ms` delay (`36 ms` total drain) before `audio_worker_task()` called `sub_audio_standby()`, which pulled `PA_CTRL` (`GPIO 46`) LOW after only `~36 ms` and severed the final `14–30 ms` of every `50 ms` chirp still in the DMA buffer.
  * **Root Cause 2 (On-Demand Cold-Start VMID Ramp Latency):** Waking the codec from `0x0D = 0xFC` (`VMID = 0V`) inside `sub_audio_prepare_and_unmute()` using `{0x0D, 0x31}` (`VMIDSEL = 1` slow normal-speed charge on `C114 = 1 µF`) without `{0x44, 0x58}` or `sub_audio_wait_until_ready()` clipped the leading edge of the `70 ms` first note of `H1OS_CHIME_BOOT`.
  * **Fix 1 (Session-Scoped Warm Readiness):** `sub_audio_init()` now configures `s_es8311_init_pre_charge` (including `{0x44, 0x58}` internal reference routing) and `s_es8311_init_post_charge` (`{0x0D, 0x01}` fast VMID reference enable and `{0x37, 0x08}` `DAC_RAMPRATE = 0` soft-start ramp OFF, `DAC_EQBYPASS = 1`), waits for `sub_audio_wait_until_ready(100)` (`CSM != S0`), sets the perceptual volume (`Reg 0x32`), and enables the NS4150B Class-D amplifier (`PA_CTRL = 1`, `120 ms` turn-on delay) *before* returning from `sub_audio_init()`. Removed the per-tone `sub_audio_standby()` call from `audio_worker_task()` so the codec and amplifier stay warm for zero-latency chirps during the 30-second interactive session and enter `<1.0 µA` standby when the 30-second session expires (`orch_flow_quiesce_peripherals()` $ightarrow$ `sub_audio_standby()`).
  * **Fix 2 (Full 4-Descriptor `64 ms` I2S DMA Drain):** Updated `sub_audio_flush_frame()` to write `SUB_AUDIO_DMA_DESC_NUM` (`4`) zero-filled `256-sample` frames (`1024 samples = 64 ms`) through `i2s_channel_write()` followed by a `20 ms` serializer drain delay, guaranteeing that 100% of all queued tone samples physically exit the I2S peripheral and DAC interpolator before playback completes or `sub_audio_standby()` is called on sleep entry.

### 📄 Documentation & Qualification Archives

* **Post-Audit Thermal Analysis & `v2.4.7-dev` Certification Archive** (`TST_005/TST_005_results.md`, `docs/audits/h1os_thermal_and_sleep_audit_report_v2_4_7.md`, `ERRATA.md`, `docs/drivers/03_audio.md`):
  * Appended Section 9 (`v2.4.6-dev` Post-Audit Bench Verification & `v2.4.7-dev` Remediation) to `TST_005/TST_005_results.md` and generated the formal `v2.4.7-dev` audit report.
  * Synchronized semantic version strings across all four authoritative locations (`h1os_version.h`, `components/h1os/idf_component.yml`, `README.md`, `CHANGELOG.md`) to `2.4.7-dev`.

### 🛠️ Developer Tooling & Hardware Recovery

* **Retro USB Port Recovery Utility (`usb_ctrl_punk // tokyo_bloodline edition`)** (`tools/usb_ctrl_punk_v2.6/`, `tools/usb_ctrl_punk_v2.6/Full/`, `tools/usb_ctrl_punk_v2.6/Lite/`):
  * Deployed `usb_ctrl_punk` (v2.6) featuring an underground app-phreak aesthetic, decoupled 30 FPS GDI+ runspace rendering, and the integrated `tokyo_bloodline_synth` soundtrack by Humiditron.
  * **Win32 Kernel Port Cycling:** Drives hardware Single-Ended Zero (SE0) bus resets directly against upstream USB hubs via `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`), simulating a physical cable re-plug to instantly recover stalled ESP32-S3 USB-JTAG/Serial endpoints, stuck ROM download modes, and faulted DevNodes (`Code 43`) without physical intervention.
  * **Dual Distribution Model:**
    * `Full/`: Zero-dependency, single-file portable script (`tokyo_bloodline.ps1`) with in-memory base64 audio payload and one-click elevated UAC launch wrappers (`tokyo_bloodline_full.bat` / `tokyo_bloodline_full_silent.bat`).
    * `Lite/`: 100% human-auditable UTF-8 script (`tokyo_bloodline_lite.ps1`) stripped of binary blobs for enterprise security auditability, loading `tokyo_bloodline_synth.mp3` dynamically from the local directory.
  * Integrated multi-tier PnP recovery actions: `[1] PATCH PORT (SE0 REPLUG)`, `[2] RESTART DRIVER (PNP TOGGLE)`, `[3] PURGE FAULTED NODE (CODE 43)`, and `[4] SCAN FOR HARDWARE CHANGES`.
  * Inspired by [USB Device Tree Viewer](https://www.uwe-sieber.de/usbtreeview_e.html), observed hardware behavior after a `Device Restart` directly inspired the tools creation.

## [2.4.6-dev] - 2026-10-29

### 🛡️ Fixed & Hardened (`TST_005` Thermal Offset & Low-Power Sleep Remediation Audit)

* **ES8311 Audio Codec (`U10`) Standby Register Map & Datasheet Note 4/5 Clock Sequencing (`RC-01` / `RC-02` / `S0`)** (`sub_audio.c`):
  * Resolved the primary `+3.5°C to +4.5°C` localized codec thermal hotspot (`26.8°C–28.9°C` on `U10` in `TST_005_IMGS_THERMAL`, driving a `+0.84°C` SHTC3 chamber offset and `4.58 mA` average draw across 12.0 hours) caused by a mis-mapped de-initialization table (`s_es8311_deinit[]`) and un-gated active session bias.
  * **Register `0x0E` (`ES8311_REG_SYS_PDN_MOD`) Restoration (`0xFF` $\rightarrow$ `0x6A`):** Corrected `s_es8311_deinit[]` from `{0x0E, 0xFF}` to the authoritative hardware power-on-reset default `{0x0E, 0x6A}` (`es8311_user_guide_v8.pdf` p. 18: `PDN_PGA = 1`, `PDN_MOD = 1`, `RST_MOD = 0`, `VROI = 1`). Writing `0xFF` previously forced undocumented internal analog control bits `[7]` and `[0]` HIGH (`1`) and held `RST_MOD = 1`.
  * **Register `0x45` (`ES8311_REG_GP_CTRL`) Pull-Up Disarm (`0x00` $\rightarrow$ `0x03`) & Register `0x07` Tri-State (`0x30`):** Per `es8311_user_guide_v8.pdf` pp. 28–29, Bit 0 (`PULLUP_SE`) of `Reg 0x45` defaults to `0` (`BCLK/LRCK pullup ON`). Leaving `0x45 = 0x00` during standby kept the ES8311 internal pull-ups to `PVDD` (`3.3V`) enabled on Pin 6 (`BCLK`) and Pin 8 (`LRCK`) while the ESP32-S3 held `GPIO 15` (`SCLK`) and `GPIO 38` (`LRCK`) LOW (`0V`), creating a continuous DC current path through `U10` during 100% of deep sleep. `s_es8311_deinit[]` now writes `{0x45, 0x03}` (`PULLDOWN_ADCDAT = 1`, `PULLUP_SE = 1` pull-ups OFF), `{0x07, 0x30}` (`TRI_BLRCK = 1`, `TRI_ADCDAT = 1`), and `{0x09, 0x4C}` / `{0x0A, 0x4C}` (`SDPIN_MUTE = 1`, `SDPOUT_MUTE = 1`).
  * **Register `0x00` (`ES8311_REG_RESET`) DAC Digital Reset (`0x1E` $\rightarrow$ `0x1F`):** Restored Bit 0 (`RST_DAC_DIG = 1`) in `s_es8311_deinit[]` (`{0x00, 0x1F}`, p. 14). A prior revision misidentified Bit 0 of `Reg 0x00` as `RST_REG` (register reset `INI_REG` is actually Bit 0 of `Reg 0xFA`, p. 29, while Bit 4 `RST_DIG` resets digital *"except control port block"*), leaving the DAC digital interpolator/modulator un-reset (`0`) during sleep.
  * **Complete Analog Bias & Filter Restoration (`0x0F`, `0x10`, `0x11`, `0x16`, `0x1B`, `0x1C`, `0x44`):** Added explicit standby restoration for `{0x0F, 0xFF}` (all 8 low-power reference/DAC/PGA bits enabled), `{0x10, 0x13}` (clearing `VX2OFF = 1` and `VY1SEL = 3` set by `{0x10, 0x1F}` during pre-charge), `{0x11, 0x7C}` (clearing internal bits `[1:0]` set by `{0x11, 0x7F}`), `{0x16, 0x04}`, `{0x1B, 0x0C}`, `{0x1C, 0x4C}` (`ADC_EQBYPASS = 1`, replacing `{0x1C, 0x00}` which enabled the ADC EQ), and `{0x44, 0x00}` (clearing `ADCDAT_SEL`). Also kept the unused analog microphone PGA and ADC modulator powered down during active DAC playback (`{0x0E, 0x62}`, `{0x14, 0x00}`, `{0x0D, 0x31}`).
  * **Datasheet Note 4/5 Clock-Sequenced Standby & On-Demand Session Parking:** Per `es8311_pb_v16.pdf` Page 8 Note 4 (*"entering low power through control register setting, then stopping input clock"*), `sub_audio_standby()` now ensures `MCLK`/`LRCK` are active while writing the analog power-down registers, holds `2 ms` (`SUB_AUDIO_CSM_QUIESCE_DELAY_US`) for the Chip State Machine (`CSM`) to settle into `S0`, writes `{0x00, 0x1F}` and `{0x01, 0x00}`, and then disables the I2S TX channel (`i2s_channel_disable()`). Both `sub_audio_init()` and `audio_worker_task()` (upon queue drain) immediately park the codec and NS4150B amplifier (`PA_CTRL = 0`) in `<1 µA` standby, eliminating continuous `8–12 mA` idle dissipation during 30-second interactive sessions.
* **Glitch-Free 2nd-Stage Bootloader `PA_EN` (`GPIO 42`) Pad Hold Sequencing & Self-Healing Wake Verification (`RC-04` / `S0`)** (`h1os_boot_hook.c`, `sub_audio.c`):
  * Resolved the interaction between the `v2.4.5-dev` Flow B wake fix (`PIT-02`/`PIT-03`) and `bootloader_before_init()` (`h1os_boot_hook.c`). When Flow B woke from deep sleep every 300 seconds (143 times in `TST_005`), the digital GPIO peripheral woke in its post-reset default (`GPIO 42` = JTAG `MTMS` input with internal pull-up HIGH). Calling `gpio_ll_hold_dis(&GPIO, 42)` *before* driving the output level (`0`) and output enable (`1`) caused `PA_EN` (`GPIO 42`, active-LOW P-MOSFET gate) to glitch HIGH on every Flow B wake, POR-resetting the ES8311 out of standby while `sub_audio_standby()` skipped re-initialization because `s_rtc_codec_in_standby` in `RTC_SLOW_MEM` remained `true`.
  * `bootloader_before_init()` now configures the pad mux, disables internal pull-ups/pull-downs, sets the output level, and enables the output driver *while* the existing pad hold latch freezes the physical pin, and only then refreshes the pad hold (`hold_dis` $\rightarrow$ `hold_en`) across `GPIO 17` (`BAT_CTRL`), `GPIO 6` (`EPD_3V3_EN`), `GPIO 42` (`PA_EN`), and `GPIO 46` (`PA_CTRL`).
  * Added a fast 2-register I2C verification check in `sub_audio_standby()` on unattended deep-sleep wakes (`Reg 0x0D == 0xFC && Reg 0x45 == 0x03`): if intact, redundant writes are skipped; if any power rail transient reset the codec, `sub_audio_standby()` automatically re-applies the full standby map.
* **I2S Sleep Pad Internal Pull-Up Leakage (`~367 µA`) & `ASDOUT` Output Contention Elimination (`RC-03` / `S1`)** (`hal_io.c`):
  * Replaced the `gpio_reset_pin()` loop in `hal_io_isolate_sleep_pads()` with `hal_io_quiesce_i2s_pads()`. In ESP-IDF, `gpio_reset_pin()` enables the ESP32-S3 internal `~45 kΩ` pull-up resistor (`.pull_up_en = true`), so driving all 5 I2S pins (`GPIO 14, 15, 16, 38, 45`) LOW without calling `gpio_pullup_dis()` created `~367 µA` (`5 × 73 µA`) of continuous internal pull-up leakage across deep sleep, while driving `GPIO 16` (`HAL_PIN_I2S_ASDOUT`) as `GPIO_MODE_OUTPUT` LOW caused push-pull contention against ES8311 Pin 7 (`ASDOUT` output).
  * `hal_io_quiesce_i2s_pads()` configures the 4 MCU-to-codec inputs (`MCLK`, `SCLK`, `LRCK`, `DSDIN`) as `GPIO_MODE_OUTPUT` driven `0` with both pull-up and pull-down disabled, configures `ASDOUT` (`GPIO 16`) as `GPIO_MODE_INPUT` with pull-up disabled and pull-down enabled, and parks all 5 pins deterministically in both `hal_io_early_init()` (for unattended Flow B wakes) and `hal_io_isolate_sleep_pads()`.
* **Cold-Boot ULP Sleep-Gating Enforcement & Layer 2 Hierarchy Cleanup (`RC-05` / `S1`)** (`sub_power.c`):
  * Removed premature `SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA)` from `sub_power_init_ulp()` during active cold-boot bringup so the ULP coprocessor remains strictly disarmed while the Xtensa cores execute the 30-second interactive session (`A1_master_blueprint.md` §1 Rule 5), arming `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` exclusively inside `sub_power_enter_deep_sleep_mode()`.
  * Removed the upward `#include "h1os/orch_state.h"` and `orch_state_get()` call introduced in Layer 2 `sub_power.c` during the interim wake revision, restoring 100% Four-Layer Unidirectional Hierarchy compliance (`Gate 2`).

### 📄 Documentation & Qualification Archives

* **Run #5 (`TST_005`) Qualification Ledger & Formal Thermal Audit Archive** (`TST_005/TST_005_results.md`, `docs/audits/h1os_thermal_and_sleep_audit_report_v2_4_6.md`, `docs/audits/h1os_audit_certification_report_v2_4_6.md`, `ERRATA.md`, `C2_lessons_learned.md`):
  * Authored the complete Run #5 environmental chamber metrology and radiometric thermal imaging ledger (`TST_005/TST_005_results.md`) and formal `v2.4.6-dev` audit reports.
  * Synchronized semantic version strings across all four authoritative locations (`h1os_version.h`, `components/h1os/idf_component.yml`, `README.md`, `CHANGELOG.md`) to `2.4.6-dev`.

## [2.4.5-dev] - 2026-10-29

### 🚀 Added (Dual-Core Parallel Lifecycle Concurrency, Dynamic Flow Slicing & Subsystem Enhancements)

* **Dynamic Flow Periods API & Silicon Prescaler Overlap Engine (`MANDATE-02`)** (`h1os.h`, `h1os_lifecycle.c`, `sub_power.c`, `orch_flow.c`, `A5_orchestrator.md`, `B1_api_and_services.md`, `B2_state_machine.md`):
  * Added public API `h1os_set_flow_periods(flow_a_sec, flow_b_sec)` and internal validator enforcing all silicon timing invariants: Flow A range [60s..14400s / 4h], Flow B range [300s..86400s / 24h], prescaler whole-minute alignment for durations >255s, strict ordering ($B > A$), remainder floor $\ge 60\text{s}$, and prescaler alignment on remainders.
  * Consolidated timing state to single-variable authority in RTC Slow Memory (`sample_interval_sec`, `flow_b_period_sec`), eliminating duplicate static variables and heuristic fallbacks.
* **Pure Celsius-Derived Metric Conversions & Native Kelvin Telemetry (`MANDATE-03`)** (`h1os.h`, `h1os_lifecycle.c`):
  * Added conversion macros `H1OS_CELSIUS_TO_KELVIN(c)` and `H1OS_CELSIUS_TO_FAHRENHEIT(c)`.
  * Added native Kelvin telemetry fields `ambient_temp_k` and `dew_point_k` to `h1os_telemetry_t`.
* **Deterministic Compile-Time RTC Validation (`MANDATE-05`)** (`h1os_time.h`, `h1os_time.c`):
  * Added `H1OS_BUILD_EPOCH` (derived from `__DATE__` and `__TIME__`) and `h1os_time_is_valid()` to deterministically reject stopped oscillators or pre-compile dates.
* **Public Subsystem Wrappers for Audio, Storage & Display** (`h1os.h`, `h1os_lifecycle.c`):
  * Added asynchronous audio dispatch APIs `h1os_audio_play_raw()`, `h1os_audio_play_tone()`, and `h1os_audio_play_chime()`.
  * Added MicroSD card state inspection APIs `h1os_sdcard_is_mounted()` and `h1os_sdcard_get_capacity_mb()`.
  * Added driver-level display clear and waveform scrub API `h1os_display_force_clear()`.
* **Self-Contained Typography Pipeline & Asset Pruning (`MANDATE-01`)** (`components/h1os/tools/fonts/`, `CMakeLists.txt`):
  * Relocated font generation script and required Montserrat/FontAwesome typography assets directly into `components/h1os/tools/fonts/`.
  * Pruned >1 MB of unused font bloat (`DejaVuSans`, `unscii-8`).
  * Enforced fatal CMake configuration diagnostics if typography assets are missing.
* **Dual-Core Concurrency Review Package & Transport Archive** (`docs/mandates/concurrency_review_package/`, `docs/mandates/concurrency_review_package.zip`):
  * Created complete architectural review package and zip archive for external review of the dual-core lifecycle concurrency and sleep barrier models.
* **Dual-Core Parallel Synchronization Phase & Static `EventGroup` Sleep Barrier (`MANDATE-04`)** (`h1os.h`, `h1os_lifecycle.c`, `h1os_lvgl.h`, `h1os_lvgl.cpp`, `examples/public/main/main.c`):
  * Added optional `h1os_sync_cb_t on_sync` hook to `h1os_lifecycle_t`, dispatched on Core 0 *after* `h1os_lvgl_start(5, 1)` spawns the Core 1 LVGL presentation task so network/bus I/O overlaps in parallel with the SSD1681 e-Paper display refresh ($\max(T_{\text{net}}, T_{\text{disp}})$ instead of $T_{\text{net}} + T_{\text{disp}}$).
  * Implemented a statically allocated FreeRTOS `EventGroup` sleep barrier (`xEventGroupCreateStatic(&s_sleep_barrier_buf)`, `BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`) with public coordination primitives `h1os_sync_hold()`, `h1os_sync_notify_complete()`, and `h1os_display_notify_quiescent()`.
  * Added configurable `session.sync_wait_ms` (inbound pre-flush coalescing gate, default `0 ms` for immediate outbound flush) and `session.sync_timeout_ms` (maximum barrier wait for asynchronous sync tasks, default `5000 ms`) to `h1os_lifecycle_t.session`, preventing double e-Paper refreshes on both outbound and inbound telemetry flows.
* **Lock-Free Core 0 $\rightarrow$ Core 1 UI Actor Mutation Queue (`h1os_ui_post`)** (`h1os_lvgl.h`, `h1os_lvgl.cpp`):
  * Added `h1os_ui_post(h1os_ui_fn_t fn, void *arg, uint32_t timeout_ms)` backed by a 16-slot statically allocated FreeRTOS queue (`xQueueCreateStatic`, `s_ui_queue_storage`), allowing Core 0 tasks and network callbacks to post non-blocking UI updates that wake Core 1 immediately via `xTaskNotifyGive()` and execute inside Core 1's `h1os_lvgl_lock(100)` critical section prior to `lv_timer_handler()`.
* **Explicit Wake State Classification & Monotonic Domain Counters (`MANDATE-04` Topic A)** (`h1os.h`, `orch_state.h`, `orch_flow.c`, `h1os_lifecycle.c`, `screen_diagnostics.c`):
  * Added `h1os_wake_state_t` (`H1OS_WAKE_STATE_BOOT = 0`, `H1OS_WAKE_STATE_INTERACTIVE_SESSION = 1`, `H1OS_WAKE_STATE_RTC_FLOW_B = 2`) and dedicated monotonic `RTC_SLOW_MEM` counters (`flow_b_counter`, `button_wake_count`) to `orch_persisted_state_t`, `h1os_wake_context_t`, and `h1os_telemetry_t`.
* **Fatal Startup Error Hook & Battery Power Latch Protection (`MANDATE-06`)** (`h1os.h`, `h1os_lifecycle.c`, `examples/public/main/main.c`):
  * Added `h1os_error_cb_t on_error` to `h1os_lifecycle_t` and implemented `h1os_handle_fatal_startup_error()` in `h1os_lifecycle.c` to invoke `on_error`, place audio and display subsystems into low-power standby, and cut the `GPIO 17` (`BAT_CTRL`) battery power latch (or enter emergency `EXT0` deep sleep on `GPIO 18` when USB VBUS is attached) whenever `h1os_start()` encounters a fatal validation or hardware initialization failure.

### 🛡️ Fixed & Hardened (`H1OS-STD-001` Codebase Review & Invariant Audit)

* **Deep Sleep Wake Failure After First Flow B Cycle (`PIT-02` / `PIT-03` / `S0`)** (`sub_power.c`, `orch_wake_stub.c`, `h1os_lifecycle.c`, `ulp/main.c`):
  * Resolved a defect where the device accepted tactile button wakes during the first Flow B period (0..300 s) but became unresponsive to both the PCF85063A countdown and the `GPIO 0` / `GPIO 18` buttons after the first scheduled Flow B wake.
  * **Root Cause 1 (Latched `RTC_CNTL_SW_CPU_INT`):** The ULP wakes the main CPU by asserting `RTC_CNTL_SW_CPU_INT`. The Flow A wake stub cleared it, but the Flow B path never did, so `esp_deep_sleep_start()` was entered with the software wake interrupt still asserted. `sub_power_enter_deep_sleep_mode()`, the `esp_default_wake_deep_sleep()` path in `bsp_wake_stub()`, and `h1os_early_system_bringup()` now clear `RTC_CNTL_SW_CPU_INT`, `RTC_CNTL_SLP_REJECT_INT_CLR`, `RTC_CNTL_SLP_WAKEUP_INT_CLR`, and `RTC_CNTL_SLP_REJECT_CAUSE_CLR` with `memw` barriers.
  * **Root Cause 2 (ULP `RDY_FOR_WAKEUP` Race):** When the ULP was triggered during the main CPU sleep-entry window and timed out waiting on `RTC_CNTL_RDY_FOR_WAKEUP`, it cleared `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` before halting, leaving the SoC in deep sleep with all ULP GPIO wake sources disabled. The ULP now clears the trigger latch only and leaves the wake enable armed.
  * Moved `s_cached_flow_a_sec` / `s_cached_flow_b_sec` in `sub_power.c` to `RTC_DATA_ATTR` with recovery-mode hydration from `orch_state` so slice periods survive deep sleep (`PIT-05`).
  * Verified on hardware (`TST_005`): autonomous Flow B wake and button wake both operate past the 5-minute boundary.
* **Battery ADC Calibration Trim (`SUB_POWER_VBAT_TRIM_OFFSET_MV`)** (`sub_power.h`, `sub_power.c`, `ulp/main.c`):
  * Added a configurable `+80 mV` trim offset (`SUB_POWER_VBAT_TRIM_OFFSET_MV`, overridable at compile time) folded into the ULP linear calibration offset in `sub_power_get_ulp_cal_params()` (eFuse curve-fit and nominal default paths), with a matching `ULP_VBAT_TRIM_OFFSET_MV` default for `cal_offset` in the ULP image. Trim value derived from bench comparison against a reference meter on the DUT.

* **Deterministic Error Propagation & Gated RTC POSIX Clock Sync (`PIT-08`)** (`h1os_lifecycle.c`):
  * Eliminated all `(void)` casts on error-returning calls across `h1os_lifecycle.c` (`sub_power_init_dfs`, `hal_io_early_init`, `hal_i2c_init`, `sub_rtc_init`, `sub_nvs_init`, `sub_power_init_ulp`, `h1os_lvgl_init`, `h1os_lvgl_start`, `sub_rtc_get_and_clear_interrupts`, `sub_rtc_cancel_countdown`, `h1os_sleep`, and `h1os_get_telemetry_history`).
  * Gated PCF85063A RTC to POSIX system clock synchronization strictly behind `sub_rtc_is_oscillator_valid()`, preventing uncalibrated or stopped RTC registers on cold boot from corrupting the internal system clock.
  * Refactored `h1os_early_system_bringup()` to return `esp_err_t` and output flow via pointer, allowing `h1os_start()` to deterministically propagate bringup faults directly back to `app_main()`.
* **Cold-Boot Flow Period Initialization Order Blocker (`REV-01` / `S0`)** (`h1os_lifecycle.c`):
  * Resolved an initialization ordering bug introduced in `MANDATE-02` where `h1os_start()` committed `sample_interval_sec` and `flow_b_period_sec` to `RTC_SLOW_MEM` *before* `h1os_early_system_bringup()` called `orch_flow_determine_wakeup()`. On every cold boot, `orch_flow_determine_wakeup()` invoked `orch_state_reset()`, wiping `sample_interval_sec` back to `0` and causing `sub_power_init_ulp(0)` to fail with `ESP_ERR_INVALID_ARG`, while on deep-sleep wakes it overwrote runtime `h1os_set_flow_periods()` intervals and zeroed `ulp_slice_counter` prior to `debug_dump_ulp_telemetry()`.
  * Split validation (`h1os_validate_flow_periods()`) from `RTC_SLOW_MEM` commit (`h1os_apply_flow_periods()`), validating at entry to `h1os_start()` and committing after `orch_flow_determine_wakeup()` and `debug_dump_ulp_telemetry()`.
* **Scoped Lifecycle Hook Locking (`REV-02` / `S0`)** (`h1os_lifecycle.c`):
  * Removed the coarse-grained outer `h1os_lvgl_lock(1000)` wrapper around `on_boot()`, `on_wake()`, `on_pre_sleep()`, and `on_shutdown()` in `h1os_lifecycle.c` while preserving scoped `h1os_lvgl_lock(1000)` inside `h1os_trigger_splash()`, preventing non-UI peripheral operations (such as SD card unmounting or NVS/RTC calls) from holding the LVGL mutex across cores.
* **ULP-RISC-V SAR ADC1 Full-Scale Saturation Resolution (`ERR-S6` / `REV-09` / `S0`)** (`sub_power.c`, `ulp/main.c`, `hal_io.c`, `sub_display.cpp`, `ERRATA.md`, `C2_lessons_learned.md`):
  * Resolved a hardware/driver initialization defect where ULP-RISC-V battery ADC sampling (`ADC1_CHANNEL_3` on `GPIO 4`) consistently returned full-scale saturation (`raw = 4095` / `0xFFF`, `vbat = 6917 mV` at `scale = 6758, offset = 161 mV`, silently masked to `4000 mV` by the `> 4500 mV` clamp in `sub_power_get_battery_status()`).
  * **Root Cause 1 (`ulp_adc_init` vs. `adc_oneshot_new_unit`):** `sub_power_init()` previously called `adc_oneshot_new_unit()` (`ulp_mode = ADC_ULP_MODE_RISCV`) and `adc_oneshot_config_channel()` (`ADC_ATTEN_DB_12`) directly instead of ESP-IDF's `ulp_adc_init()`. Because `adc_oneshot_config_channel()` defers loading the eFuse hardware reference calibration code (`adc_set_hw_calibration_code(ADC_UNIT_1, ADC_ATTEN_DB_12)`) into the SAR ADC1 internal analog `reg_i2c` registers until `adc_oneshot_read()` is called on the main CPU (which H1OS never calls), the uncalibrated SAR1 internal reference saturated at `raw = 4095` for any input above $\sim 1.1\text{ V}$ (whereas the $200\text{ k}\Omega / 200\text{ k}\Omega$ divider tap sits at $2.05\text{–}2.10\text{ V}$ for a $4.10\text{–}4.20\text{ V}$ AntPow `AP502535` 400 mAh LiPo cell) and omitted `esp_sleep_enable_adc_tsens_monitor(true)`. Replaced with `ulp_adc_init(&ulp_adc_cfg)` and `ulp_adc_deinit()`.
  * **Root Cause 2 (ULP Register Enforcement):** Updated `ulp_read_vbat_adc_bounded()` in `ulp/main.c` to explicitly assert `SENS_FORCE_XPD_SAR = 0x3` (force SAR analog power on during conversion, returning to `0x0` FSM control on completion), `SET_PERI_REG_BITS(SENS_SAR_ATTEN1_REG, 0x3U, 0x3U, (ADC_CHANNEL_3 * 2))` (`12 dB` attenuation on `ADC1_CH3`), `SENS_SAR1_EN_PAD_FORCE = 1`, and `SENS_MEAS1_START_FORCE = 1` with explicit RISC-V I/O fences (`ulp_reg_barrier()` / `asm volatile("fence iorw, iorw" ::: "memory")`), a `40 µs` analog reference settling window (`SAR1_XPD_SETTLE_US`), and a `2 µs` `START_SAR` strobe hold (`SAR1_START_PULSE_US`) under `-Os` compilation, and enabled ULP ADC sampling across all ULP wakes (including tactile button wakes while main cores remain in deep sleep).
  * **Root Cause 3 (Analog Pad Mux Preservation & GPIO ISR Service Cleanup):** Removed the post-init `rtc_gpio_init(HAL_PIN_BATTERY_ADC)` call in `sub_power_enter_deep_sleep_mode()` that overwrote `ulp_adc_init()`'s analog pad mux setup, removed `rtc_gpio_deinit(HAL_PIN_BATTERY_ADC)` from `hal_io_release_pad_holds()` so the digital CMOS input buffer is never reconnected to the $2.08\text{ V}$ mid-rail divider tap during Flow B, and guarded `gpio_install_isr_service(0)` in `sub_display.cpp` (`epd_ensure_busy_sync_ready()`) to eliminate the duplicate `E (1389) gpio: gpio_install_isr_service(568): GPIO isr service already installed` diagnostic on boot/wake.
* **Mandatory 250 ms Post-Refresh Electrophoretic Settling Window (`REV-04` / `S0`)** (`sub_display.cpp`):
  * Recorded completion timestamps (`s_last_refresh_done_us`) in `sub_display_refresh_full()` and `sub_display_refresh_partial()` and enforced the mandatory `250 ms` post-`BUSY` electrophoretic microcapsule settling guard in `sub_display_enter_deep_sleep()` prior to issuing SSD1681 Deep Sleep Mode 1 (`0x10 = 0x01`), satisfying `AGENTS.md` Section 3 Step 4 after the microsecond-immediate `GPIO_INTR_NEGEDGE` `BUSY` ISR optimization.
* **100% Static FreeRTOS Primitive Allocation (`REV-05` / JPL Rule 3 / `PIT-04-C`) & Cooperative Audio Teardown (`REV-06` / `PIT-01-E`)** (`hal_i2c.c`, `sub_audio.c`):
  * Replaced dynamic `xSemaphoreCreateRecursiveMutex()` in `hal_i2c.c` with `xSemaphoreCreateRecursiveMutexStatic(&s_i2c_mutex_buf)` and dynamic `xQueueCreate()` in `sub_audio.c` with `xQueueCreateStatic()`.
  * Hardened `sub_audio_deinit()` to call `sub_audio_wait_idle(1000)` and dispatch a cooperative `AUDIO_CMD_STOP` join (`s_audio_stop_sem`) before disabling and deleting `s_tx_chan`, eliminating mid-transfer I2S use-after-free and mutex/PM-lock leaks.
* **Strict Four-Layer Unidirectional Hierarchy & Coding Standards (`REV-07`, `REV-08`)** (`hal_types.h`, `sub_power.c`, `sub_audio.c`, `sub_sdcard.c`, `orch_flow.c`, `h1os_lifecycle.c`, `h1os_time.c`, `Kconfig`, `sdkconfig.defaults`, `examples/public/**`):
  * Removed upward `#include "h1os/orch_state.h"` from Layer 1 `hal_types.h` and Layer 2 `sub_power.c`, removed upward `#include "h1os/h1os.h"` from Layer 2 `sub_power.c`, `sub_audio.c`, and `sub_sdcard.c`, and relocated Layer 4 public wrappers (`h1os_audio_play_*`, `h1os_sdcard_*`, `h1os_led_*`) to `h1os_lifecycle.c`.
  * Updated `examples/public/main/main.c`, `screen_diagnostics.c`, and `screen_system_health.c` to consume Layer 4 `h1os_*` APIs and `h1os_telemetry_t` fields exclusively.
  * Replaced remaining naked `int` variables in `h1os_time.c` and `sub_power.c` with `int32_t`, replaced prohibited vocabulary in `components/h1os/Kconfig` per `AGENTS.md` Section 2, and synchronized `examples/public/main/idf_component.yml` to `>=6.1.0`.

## [2.4.4-dev] - 2026-10-27

### 🚀 Added (Production Humidor Telemetry Middleware Primitives)

* **Chronological Telemetry History Export API** (`h1os.h`, `orch_state.h`, `orch_state.c`, `h1os_lifecycle.c`, `docs/architecture/B1_api_and_services.md`):
  * Added `h1os_get_telemetry_history(orch_tri_node_sample_t *out_samples, size_t max_samples, size_t *out_count)` and `orch_state_get_ring_chronological()` to export up to 32 historical Tri-Node samples in chronological order (oldest to newest) directly from RTC Slow SRAM without exposing Layer 3 internal storage to the application layer.
  * Enables single-shot batch cloud publishing (Wi-Fi MQTT / HTTPS) and BLE GATT history synchronization for the production humidor application.
* **Configurable Humidor RH Target Alert Bounds** (`h1os.h`, `orch_state.h`, `orch_wake_stub.c`, `h1os_lifecycle.c`):
  * Added `h1os_set_rh_alert_bounds(uint16_t rh_low_centi_pct, uint16_t rh_high_centi_pct)`, persistent RTC Slow SRAM thresholds (`rh_alert_low_centi_pct`, `rh_alert_high_centi_pct`), `ORCH_FLAG_RH_ALERT_ACTIVE`, and `h1os_telemetry_t.is_rh_alert_active`.
  * Evaluates settled SHTC3 relative humidity against configured humidor boundaries inside `bsp_wake_stub()` during Flow A deep-sleep sample bursts.

### 🛡️ Fixed & Hardened (`H1OS-STD-001` Audit & `-O2` Wake Stub Register Protections)

* **ESP-IDF Component Manifest & Hardware Attribution Notices** (`components/h1os/idf_component.yml`, `README.md`, `ERRATA.md`, `docs/guide.md`, `examples/boilerplate/README.md`):
  * Formatted `maintainers` as a valid sequence and resolved `discussion` URL in `idf_component.yml` to satisfy ESP-IDF v6.1 Component Manager schema validation.
  * Added clear hardware non-affiliation notices and collaboration/sponsorship invitation callouts across public README and documentation entry points.
* **Event-Driven Timer, GPIO ISR & Static Semaphore Architecture (`esp_timer` / `GPIO_INTR` Refactor)** (`hal_io.c`, `hal_io.h`, `sub_display.cpp`, `h1os_lifecycle.c`, `h1os_lvgl.cpp`, `h1os_lvgl.h`, `sub_sdcard.c`, `sub_audio.c`):
  * **SSD1681 `EPD_BUSY` (`GPIO 8`) Falling-Edge Interrupt Synchronization (`sub_display.cpp`):** Replaced the `10 ms` `vTaskDelay()` polling loop in `sub_display_wait_busy()` with a `GPIO_INTR_NEGEDGE` ISR (`epd_busy_falling_isr_handler()`) and a static binary semaphore (`s_busy_idle_sem`), eliminating 58–141 context switches per e-Paper refresh and releasing Core 1 the microsecond the display finishes driving microcapsules.
  * **One-Shot `esp_timer` Interactive Session Monitor (`h1os_lifecycle.c`):** Replaced the dedicated `h1os_sess` FreeRTOS polling task (`4,096 B` stack waking every `500 ms`) with a hardware-backed one-shot `esp_timer` (`s_session_timer`, `esp_timer_start_once()` / `esp_timer_restart()`), reclaiming `4 KB` of internal SRAM and eliminating periodic idle wakes.
  * **Periodic `esp_timer` LED Breathing & Hardware Glitch-Filtered Button ISRs (`hal_io.c`, `hal_io.h`):** Replaced the `led_breath` FreeRTOS polling task (`2,048 B` stack waking every `50 ms`) with a periodic `esp_timer` callback (`hal_led_breath_timer_cb()`) driving the hardware LEDC fade unit, saving an additional `2 KB` of SRAM (`6 KB` total stack savings). Configured `GPIO 0` (`BOOT`) and `GPIO 18` (`POWER`) with ESP32-S3 hardware pin glitch filters (`gpio_new_pin_glitch_filter()`), `GPIO_INTR_ANYEDGE` interrupts, and a `15 ms` one-shot `esp_timer` debounce filter (`hal_io_register_button_cb()`) that wakes the LVGL keypad handler immediately via `xTaskNotifyGive()`.
  * **Zero-Polling Semaphore Teardown & Drain Joins (`h1os_lvgl.cpp`, `sub_sdcard.c`, `sub_audio.c`):** Replaced the `10–20 ms` pre-sleep polling `while` loops in `h1os_quiesce_lvgl_pipeline()`, `h1os_lvgl_stop()`, `sub_sdcard_unmount()`, and `sub_audio_wait_idle()` with static binary semaphores (`s_lvgl_idle_sem`, `s_lvgl_stop_sem`, `s_mount_done_sem`, `s_audio_idle_sem`) and `ulTaskNotifyTake()`.
* **RTC Wake Stub `-O2` Loop Unrolling, Stack Memset & Register Barrier Hardening** (`orch_wake_stub.c`, `orch_state.c`, `ulp/main.c`, `ERRATA.md`):
  * Guarded `i2c_write_byte()`, `i2c_read_byte()`, `wake_stub_read_die_temp_centi_c()`, `rtc_write_reg_retry()`, and `i2c_recover_stuck_bus()` with `__attribute__((noinline))` and inline assembly loop register barriers (`asm volatile("" : "+r"(i))`), preventing `-O2` loop unrolling across bit-banged I2C call sites and eliminating back-to-back GPIO store coalescing.
  * Prevented `-O2` `-ftree-loop-distribute-patterns` from replacing byte loops and struct zero-initializations (`uint8_t rx[6] = {0}`, `orch_tri_node_sample_t sample = {...}`, and `orch_state_reset()`) with implicit calls to Flash-resident `memset` by using explicit field assignments and `asm volatile("" : "+m"(p[i]))` memory barriers.
  * Added `rtc_reg_barrier()` (`asm volatile("memw" ::: "memory")`) between every sequential `SENS_SAR_TSENS_*`, `SENS_SAR_PERI_*`, `RTC_CNTL_*`, and `RTC_GPIO_*` register write in `orch_wake_stub.c`, and added `asm volatile("fence" ::: "memory")` around `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` in `ulp/main.c` (`PIT-03-B`, `PIT-03-C`).
  * Implemented `scl_high_wait()` with bounded 2,000 µs clock-stretch / RC rise verification (`ORCH_SENSOR_ERR_SCL_STUCK = 7`) and 9-clock I2C bus recovery (`i2c_recover_stuck_bus()`) for stuck SDA lines.
  * Fixed I2C master read protocol violation in `bsp_wake_stub()` where the 6th (final) byte of the SHTC3 measurement frame (`rx[5]`) was read with `ACK` (`true`) instead of `NACK` (`false`), preventing the SHTC3 from holding SDA low during the subsequent `STOP` condition.
* **Bounded LVGL Mutex & SPI Read Buffer Overflow Prevention** (`h1os_lvgl.cpp`, `h1os_lvgl.h`, `hal_spi.c`, `sub_power.c`, `orch_flow.c`):
  * Implemented bounded recursive mutex acquisition in `h1os_lvgl_lock(uint32_t timeout_ms)` via static `xSemaphoreCreateRecursiveMutexStatic()` instead of discarding `timeout_ms` (`(void)timeout_ms;`), satisfying `PIT-01-B` and `PIT-07-B`.
  * Added `len > 4` bounds validation in `hal_spi_read_data()` (`hal_spi.c`) to prevent overflowing the 4-byte `spi_transaction_t.rx_data[4]` inline buffer when `SPI_TRANS_USE_RXDATA` is set.
  * Guarded `s_flow_b_sec / s_flow_a_sec` against division-by-zero in `sub_power_enter_deep_sleep_mode()` (`sub_power.c`) when `h1os_shutdown()` enters standby prior to `orch_flow_execute_sleep()`.
  * Fixed cold-boot `orch_flow_scan_ring_metrics()` (`orch_flow.c`) to zero out `window_low_temp_centi_c` and `window_high_temp_centi_c` when `valid_cnt == 0`, preventing `+327.67°C` (`INT16_MAX`) / `-327.68°C` (`INT16_MIN`) display artifacts.
  * Replaced naked `int` parameters in `h1os_lvgl_start()` with `int32_t` (`B3_firmware_standards.md` Rule 1) and aligned `h1os_constants.h` SPDX license header to `MIT`.
* **Browser Thermal Simulator (`tools/thermal_sim/index.html`) 60 FPS Optimization**:
  * Eliminated 60 Hz DOM table reconstruction (`renderPartsTable()` `innerHTML` rebuild on 26 rows every animation frame) by gating updates to 4 Hz only when the `26-Part Thermal Table` tab is active.
  * Replaced `JSON.parse(JSON.stringify(srcObj))` inside `getFlowBForCycle()` and `Array.find()` inside `accumulateActionWindow()` with zero-allocation pre-indexed lookup tables, and reused a pre-allocated `Float64Array(1680)` (`s_cellHeatInW`) across all finite-volume sub-steps.
  * Pre-computed a 1,024-entry `Uint8Array` thermal RGB colormap LUT and batched isotherm contour rectangles into a single `beginPath()` / `stroke()` pass, reducing `stepSimulation(9000)` preset load latency by >15x.
* **Documentation & Architecture Synchronization** (`README.md`, `ERRATA.md`, `AGENTS.md`, `_agent_rules/lifecycle.md`, `docs/guide.md`, `docs/pinout.md`, `docs/drivers/*`, `docs/architecture/*`, `tools/usb/README.md`):
  * Synchronized `h1os_lifecycle_t` examples (`on_pre_sleep`, `clk_mode = SYS_CLK_MODE_DYNAMIC`), battery divider values (`200kΩ / 200kΩ`), SHTC3 wake stub timings (`500 µs` wake, `18.0 ms` conversion budget), 5-screen carousel numbering, and `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`).

## [2.4.3-dev] - 2026-10-26

### 🛡️ Fixed & Hardened (Compiler Flash Table Synthesis Resolution & TSENS Silicon Hardening)

* **Compiler Flash Lookup Table Synthesis Elimination in RTC Wake Stub** (`orch_wake_stub.c`, `ERRATA.md`, `C2_lessons_learned.md`):
  * Resolved critical `-O2` compiler optimization defect (`ERR-SW1`) where GCC's loop optimizer auto-synthesized an unrolled 256-byte CRC-8 lookup table into unpowered SPI NOR Flash (`.rodata` at `0x3C0A379C`). During deep sleep wake stub execution, SPI Flash is unpowered and the Flash cache MMU is offline, loading floating bus noise / `0xFF` and triggering 100% CRC failure (`ORCH_SENSOR_ERR_CRC_FAIL` / `E4`).
  * Guarded `shtc3_crc8()` with `__attribute__((noinline))` and an empty inline assembly register clobber `asm volatile("" : "+r"(crc));` to force in-register bitwise execution within `.rtc.text` (`0x600feb6c`), eliminating all Flash MMU accesses and restoring pristine CRC verification under `-O2`.
* **Internal MCU Die Temperature Sensor (TSENS) Silicon Hardening** (`orch_wake_stub.c`, `orch_wake_stub.h`, `ERRATA.md`, `C2_lessons_learned.md`):
  * Corrected TSENS reset target register from `SENS_SAR_TSENS_CTRL2_REG` (where bit 29 is unmapped) to the authoritative `SENS_SAR_PERI_RESET_CONF_REG` (`0x60008908`), ensuring proper hardware reset before analog sampling (`ERR-SW2`).
  * Corrected `SENS_TSENS_XPD_FORCE` from `3` (which commanded hardware forced power-down per ESP32-S3 TRM) to canonical `1` (which disables force power-down, allowing `tsens_power_up = 1` to energize analog bias), clearing to `0` on sleep.
  * Implemented hardware latch sequence: assert `tsens_dump_out`, poll `tsens_ready` with expanded 1000-cycle (5 ms) ceiling, de-assert `tsens_dump_out` to latch result, and read `tsens_out`.
* **I2C Protocol & ULP Pipeline Hardening** (`orch_state.h`, `orch_wake_stub.c`):
  * Added `ORCH_SENSOR_ERR_NACK_SLEEP = 6` to `orch_sensor_err_t` and verified SHTC3 sleep command (`0xB098`) return status in `bsp_wake_stub()`.
  * Added trailing `asm volatile("memw" ::: "memory");` pipeline memory barrier after `CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA)` to prevent write buffer latency from allowing concurrent ULP wakeups during wake stub execution.
  * Added trailing `memw` barrier before `esp_wake_stub_sleep(&bsp_wake_stub)`.
* **NVS Wear-Leveling Documentation & Throttle** (`A4_subsystems.md`, `A8_battery_and_power_management.md`):
  * Documented 1-hour unattended sleep throttle (`ORCH_NVS_AUTONOMY_COMMIT_INTERVAL_SEC = 3600U`) reducing flash wear cycles by 98.3%, and detailed the 12-byte packed struct layout (`orch_nvs_runtime_blob_t` under key `"pwr_lap_st"`).
* **Display Bounds Verification** (`tools/check_string_width.py`, main screens):
  * Audited all 63 UI layout strings via `check_string_width.py --audit-screens`; 100% pass rate with zero $W \le 188.0\text{ px}$ breaches.

### 🔄 Changed
* **Semantic Version Bump (`2.4.3-dev`)** (`h1os_version.h`, `idf_component.yml`, `README.md`, `CHANGELOG.md`):
  * Synchronized semantic version strings across all 4 authoritative project files to `2.4.3-dev`.

## [2.4.2-dev] - 2026-10-25

### 🛡️ Fixed & Hardened (Cycle-Accurate Wake Stub Assembly & USB Recovery Tool Hardening)

* **Cycle-Accurate Xtensa Assembly Timing Engine & Memory Barriers** (`orch_wake_stub.c`, `ERRATA.md`, `C2_lessons_learned.md`):
  * Resolved critical `-O2` compiler optimization timing collapse in Flow A wake stub (`ERR-S4`). Replaced software loop calls (`esp_rom_delay_us`) with hardware-cycle-counter based delay (`rtc_delay_us_exact`) querying Xtensa LX7 `rsr.ccount` at 80 MHz, rendering bit-bang timing 100% immune to compiler optimization flags.
  * Preserved all existing hardware timing budgets (5 µs I2C bit clock = 400 cycles, 250 µs SHTC3 wake pulse = 20,000 cycles, 14,050 µs post-TSENS remainder = 1,124,000 cycles).
  * Inserted Xtensa `memw` (Memory Wait) pipeline memory barriers across `sda_high()`, `sda_low()`, `scl_high()`, `scl_low()`, and `sda_read()` to guarantee peripheral bus store completion before subsequent instruction scheduling.
  * Formally documented root cause and side-by-side C vs. Assembly code comparisons in `ERRATA.md` (`ERR-S4`) and `docs/architecture/C2_lessons_learned.md` (Section 4.11).
* **Sensor Error Telemetry Console Propagation** (`orch_flow.c`):
  * Updated `Flow A Ring:` informational console logging in `orch_flow.c` to format `fails=%lu err=%u`, exposing `sensor_fail_count` and `last_sensor_error` over serial during wake and interactive telemetry queries.
* **USB Recovery Terminal & Port Cycler Hardening** (`tools/usb/term_usb_toolbox.ps1`, `tools/usb/README.md`):
  * Corrected Win32 kernel control code from invalid `0x220414` to canonical `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`), eliminating `ERROR_INSUFFICIENT_BUFFER` (122).
  * Formulated valid Win32 device interface class links (`\\?\$pHash#{f18a0e88-c30c-11d0-8815-00a0c906bed8}`), resolving `ERROR_FILE_NOT_FOUND` (2) when opening handles to upstream parent hubs.
  * Implemented canonical 1-based port index resolution via `DEVPKEY_Device_Address`, with multi-tiered fallbacks to `DEVPKEY_Device_LocationInfo` and `DEVPKEY_Device_LocationPaths`.
  * Added UsbTreeView-style graceful fallback to elevated PnP DevNode reset and removal upon hardware port cycle failure on passive hubs.
  * Renamed UI action controls to clear, self-explanatory operator labels: `POWER CYCLE PORT (REPLUG)`, `RESTART DRIVER (DISABLE/ENABLE)`, `UNINSTALL FAULTED DEVICE (CODE 43)`, and `SCAN FOR HARDWARE CHANGES`.

### 🔄 Changed & Removed

* **Removed Legacy Utility** (`tools/usb/reset_coms.ps1`):
  * Removed obsolete stand-alone script `reset_coms.ps1`, fully superseded by the hardened GUI recovery terminal.
* **Semantic Version Bump (`2.4.2-dev`)** (`h1os_version.h`, `idf_component.yml`, `README.md`, `CHANGELOG.md`):
  * Synchronized semantic version strings across all core locations to `2.4.2-dev`.
  * Regenerated markdown API reference (`docs/api.md`) via Doxygen and Moxygen.

## [2.4.1-dev] - 2026-10-25

### 🛡️ Fixed & Hardened (Chamber Post-Mortem, Typography Suite & Display Bounds Verification)

* **Lean Sensor Error Tracking & Telemetry Propagation** (`orch_state.h`, `h1os.h`, `h1os_lifecycle.c`, `orch_wake_stub.c`, `screen_diagnostics.c`):
  * Added `orch_sensor_err_t` enum (`ORCH_SENSOR_ERR_NONE = 0`, `ORCH_SENSOR_ERR_NACK_WAKE = 1`, `ORCH_SENSOR_ERR_NACK_MEASURE = 2`, `ORCH_SENSOR_ERR_NACK_ADDR_RD = 3`, `ORCH_SENSOR_ERR_CRC_FAIL = 4`, `ORCH_SENSOR_ERR_BUS_STUCK = 5`) and persistent RTC Slow Memory fields `sensor_fail_count` and `last_sensor_error`.
  * Preserved the 0.0°C / 0.0% RH baseline invariant on Screen 1 while propagating fail metrics to Screen 4 Line 6 (`Wakes: %lu (Fail: %lu)`) and Line 7 dual columns (`CPU: %luMHz` on left, `SHT: OK` or `SHT: ERR_%u` on right).
* **200px UI Layout Bounds Hardening** (`screen_system_health.c`, `screen_diagnostics.c`, `screen_env_hero.c`):
  * Eliminated horizontal text clipping on the 200x200 display panel (<= 188.0 px usable boundary) by tightening string padding from variable whitespace to single-space delimiter layouts (e.g. `Power: CHARGED 4.00V` [175.81 px], `Autonomy: EXT USB` [147.81 px]).
* **Kerning-Aware Font Metrics Suite & Automated Screen Auditing** (`tools/extract_font_metrics.py`, `tools/check_string_width.py`, `tools/fonts/`):
  * Built font metric extraction engine generating character advance widths and 3,400+ class kerning pairs into CSV tables across all 6 Montserrat 1bpp sizes (14, 16, 18, 20, 24, 32).
  * Implemented automated screen template audit (`--audit-screens`) verifying all 35 screen label templates pass within <= 188.0 px under worst-case parameter replacements.
  * Verified DuckDB MCP querying directly on disk CSV metrics.
* **Master Agent Specification & Build Invariant Enforcement** (`AGENTS.md`, `.agents/rules/`, `h1os-build/SKILL.md`, `lvgl-ui/SKILL.md`):
  * Generated unified repository root `AGENTS.md` (22,039 bytes) automatically bound to agent active memory on turn 1, integrating architecture blueprints, documentation laws, and the zero-judgment conversational boundary.
  * Added mandatory `sdkconfig` removal invariant in `h1os-build/SKILL.md` before preset reconfiguring.
  * Created dedicated `lvgl-ui/SKILL.md` skill documenting layout bounds, font CSV tables, and width checker tooling.


### 🔄 Changed & Refactored (Header Abstraction, Zero-Init & Fail-Fast Validation)

* **Repository Identity & Documentation Synchronization** (`idf_component.yml`, `README.md`, `docs/api.md`):
  * Synchronized semantic version strings across all four core locations (`h1os_version.h`, `idf_component.yml`, `README.md`, `CHANGELOG.md`) to `2.4.1-dev`.
  * Updated upstream GitHub repository and documentation URLs in `idf_component.yml` to `https://github.com/Humidyne-Labs/H1OS`.
  * Regenerated markdown API reference (`docs/api.md`) via Doxygen 1.18.0 and Moxygen.
* **ULP Coprocessor Wake Cause & Button Enumeration** (`orch_state.h`, `hal_types.h`, `ulp/main.c`, `h1os_lifecycle.c`, `sub_power.c`):
  * Replaced magic numeric codes (`1` through `6`) for `last_wake_cause` with strongly-typed `ulp_wake_cause_t` enumerators in portable header `orch_state.h`.
  * Replaced magic numeric button IDs (`0`, `1`, `2`) for `last_wake_btn` with strongly-typed `h1os_wake_btn_t` (`H1OS_WAKE_BTN_NONE = 0`, `H1OS_WAKE_BTN_BOOT = 1`, `H1OS_WAKE_BTN_POWER = 2`), relocating the type to `orch_state.h` so it is shared identically by the RISC-V ULP toolchain and main Xtensa CPU.
  * Unified ULP wake cause semantics across ULP-RISC-V firmware, power management, and application lifecycle logging: `ULP_WAKE_CAUSE_BOOT_BTN (1)`, `ULP_WAKE_CAUSE_PWR_BTN (2)`, `ULP_WAKE_CAUSE_LONG_OVERFLOW (3)`, `ULP_WAKE_CAUSE_SENSOR_TICK (4)`, `ULP_WAKE_CAUSE_RTC_INT_STUCK (5)`, and `ULP_WAKE_CAUSE_CRITICAL_BATTERY (6)`.
  * Deduplicated dispatch action definitions by sharing `orch_ulp_dispatch_t` directly between ULP coprocessor and main CPU translation units.
* **Repository Footprint Sanitization & Transient Audit Tool Pruning** (`tools/`, `docs/agent_notes/audits/`):
  * Following completion of the hardcoded literal audit and single-file macro dissolution, removed temporary Python analysis scripts (`tools/scan_hardcoded_integers.py`, `tools/audit_literals_degrees.py`, `tools/analyze_macro_scope.py`) and interim audit ledgers (`docs/agent_notes/audits/hardcoded_integers_audit.md`, `docs/agent_notes/audits/literal_integers_degree_audit.md`) to maintain repository cleanliness and avoid workspace inflation.
* **Macro Scope Partitioning & Single-File Constant Dissolution** (`h1os_constants.h`, `orch_state.h`, `orch_wake_stub.h`, `h1os_lifecycle.c`, `h1os_lvgl.cpp`, `hal_io.c`, `orch_flow.c`, `orch_wake_stub.c`, `sub_audio.c`, `sub_display.cpp`, `sub_power.c`, `sub_sdcard.c`):
  * Created automated macro scope analyzer (`tools/analyze_macro_scope.py`) mapping repository macro usage across translation units.
  * Refactored `h1os_constants.h` to strictly encapsulate public, multi-file configuration contracts (`H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC`, `H1OS_DEFAULT_FLOW_A_PERIOD_SEC`, `H1OS_DEFAULT_FLOW_B_PERIOD_SEC`).
  * Dissolved single-file operational constants out of `h1os_constants.h` back into their respective translation units as private local definitions (`LIFECYCLE_*`, `LVGL_*`, `HAL_IO_*`, `ORCH_*`, `SUB_POWER_*`, `SUB_SDCARD_*`, `SUB_AUDIO_*`, `SUB_DISPLAY_*`), preventing global namespace pollution and unneeded cross-component compilation dependencies.
  * Restored self-contained RTC memory and wake stub parameters directly in `orch_state.h` and `orch_wake_stub.h`.

* **Architectural Constants Abstraction (`h1os_constants.h`)** (`h1os_constants.h`, `h1os.h`, `orch_state.h`, `orch_wake_stub.h`):
  * Created centralized `h1os_constants.h` header defining traceable system-wide timing budgets (`H1OS_TSENS_SETTLING_DELAY_US = 400U`, `H1OS_TSENS_READY_POLL_INTERVAL_US = 5U`, `H1OS_TSENS_READY_TIMEOUT_CYCLES = 100U`, `H1OS_SHTC3_CONVERSION_TOTAL_US = 14500U`, `H1OS_TSENS_ESTIMATED_SAMPLE_US = 450U`, `H1OS_SHTC3_POST_TSENS_DELAY_US = 14050U`), autonomy wear-level intervals (`H1OS_NVS_AUTONOMY_COMMIT_INTERVAL_SEC = 3600U`), ring buffer capacity (`H1OS_TELEMETRY_RING_CAPACITY = 32U`), default TSENS intercept (`H1OS_TSENS_DEFAULT_INTERCEPT_CENTI_C = 2052`), and application lifecycle configuration defaults (`H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC = 30U`, `H1OS_DEFAULT_FLOW_A_PERIOD_SEC = 60U`, `H1OS_DEFAULT_FLOW_B_PERIOD_SEC = 300U`).
  * Added `H1OS_LIFECYCLE_DEFAULT_CONFIG()` convenience macro for clean compound-literal lifecycle initialization in `h1os.h`.
* **Zero-Initialization Architecture & Fail-Fast Input Validation** (`orch_wake_stub.c`, `orch_flow.c`, `orch_state.c`, `sub_power.c`, `h1os_lifecycle.c`):
  * Eliminated runtime ternary fallback operators (`(val > 0) ? val : DEFAULT`) across `orch_wake_stub.c`, `orch_flow.c`, `sub_power.c`, and `h1os_lifecycle.c`. Telemetry getters (`h1os_get_telemetry()`) now truthfully report the configured flow periods without masking unconfigured (zero) values.
  * Replaced defensive ternary fallbacks in `orch_flow_execute_sleep()` and `sub_power_init_ulp()` with strict boundary validation that logs errors and fails fast (`ESP_ERR_INVALID_STATE` / `ESP_ERR_INVALID_ARG`) if unconfigured (`0`) flow intervals are passed.
  * Simplified `orch_state_reset()` to strict memory zeroing retaining only the `ORCH_RTC_MAGIC` word and `H1OS_TSENS_DEFAULT_INTERCEPT_CENTI_C`.
* **Elapsed-Time Autonomy NVS Wear Gating** (`sub_power.c`, `orch_state.h`):
  * Replaced cycle-modulo NVS commits (`wake_count % 12`) with monotonic elapsed deep-sleep tracking via `st->last_nvs_commit_sec`. Commits to NVS only execute after at least `H1OS_NVS_AUTONOMY_COMMIT_INTERVAL_SEC` (3600 seconds) of sleep have elapsed, rendering wear-leveling independent of custom user flow cadences.
* **Dead Macro Elimination & Constant Linting** (`orch_state.h`):
  * Removed unreferenced legacy macros `ORCH_DEFAULT_FLOW_A_PERIOD_SEC` and `ORCH_DEFAULT_FLOW_B_PERIOD_SEC` following the elimination of runtime ternary fallbacks.
* **Codebase Literal Integer Extraction & 3-Degree Risk Classifier** (`tools/scan_hardcoded_integers.py`, `tools/audit_literals_degrees.py`, `docs/agent_notes/audits/literal_integers_degree_audit.md`):
  * Added recursive integer scanner utilities that tokenize space-delimited C/C++ tokens, parse numeric decimal and hex literals, and categorize findings into 1st Degree (structural/bitmasks/pins/enums: 65.2%), 2nd Degree (metrological/polynomial math/curve tables: 11.1%), and 3rd Degree (operational magic numbers/timeouts: 23.7%) with actionable markdown review ledgers.
* **System-Wide Operational Magic Number Elimination** (`h1os_constants.h`, `h1os_lifecycle.c`, `h1os_lvgl.cpp`, `sub_power.c`, `sub_sdcard.c`, `sub_audio.c`, `hal_io.c`, `orch_flow.c`, `orch_wake_stub.c`, `sub_display.cpp`):
  * Centralized operational magic numbers into `h1os_constants.h` across RTOS task stack floors (`H1OS_TASK_STACK_*`, `H1OS_TASK_PRIO_*`), peripheral drain/busy timeouts (`H1OS_LVGL_DRAIN_*`, `H1OS_ORCH_I2C_RECOVERY_*`, `H1OS_SUB_POWER_RTC_INT_DRAIN_*`, `H1OS_SUB_SDCARD_COMMAND_TIMEOUT_MS`, `H1OS_SUB_AUDIO_AMP_*`), electrical cutoff and charging thresholds (`H1OS_BATTERY_CRITICAL_CUTOFF_MV = 3250U`, `H1OS_BATTERY_FULL_CHARGE_THRESHOLD_MV = 4180U`, `H1OS_BATTERY_REBOUND_GATE_TENTHS_PCT = 30U`), and peripheral loop bounds (`H1OS_RTC_ARM_RETRY_LIMIT`, `H1OS_POWER_KEY_POLL_CYCLES`).
  * Completely eliminated actionable magic numbers in `h1os_lifecycle.c`, `sub_display.h`, `orch_display_sync.c`, `h1os_boot_hook.c`, and `orch_state.c`.

### Added & Verified (50-Hour Environmental Chamber Metrology Certification)

* **50.2-Hour Hermetic Chamber Soak & Zero-Calibration SHTC3 Verification** (`orch_wake_stub.c`, `orch_flow.c`, `orch_math.c`, `docs/architecture/A7_sensor_psychrometrics.md`):
  * Certified 50 hours, 10 minutes (602 consecutive 5-minute Flow B cycles / 3,010 Flow A sample bursts) of continuous autonomous operation inside a 1.4 L hermetic acrylic chamber regulated by a 69.0% Boveda two-way osmotic standard alongside a Klaro Valet reference benchmark.
  * Verified dead-on steady-state temperature agreement (`73.0°F` / `22.8°C` DUT vs. `73.0°F` Ref, `ΔT = 0.0°F`) and asymptotic relative humidity convergence from `50.5% RH` open-air baseline to `68.0% RH` (Cycle #530, `ΔRH = -1.0%`) and `67.8% RH` (Cycle #602, `ΔRH = -1.2%`, `Vapor P = 18.7 hPa`), passing all metrological acceptance gates (`67.5%–70.5% RH` and `18.5–18.8 hPa`) with zero synthetic software offsets.
  * Confirmed `H1OS-STD-001` Invariant 2 (`PIT-06-A`) compliance by rejecting re-introduction of `die_tare_centi_c` and retaining `ORCH_TRINODE_SPAN_C = 15.0f` in `orch_flow.c`.

### Fixed & Hardened (H1OS-STD-001 Rev 2.0 Codebase Audit Remediation)

* **Wake Stub Pre-Spin Die Temperature Acquisition (`AUD-03` / `PIT-06-D`)** (`orch_wake_stub.c`):
  * Relocated `wake_stub_read_die_temp_centi_c()` inside `bsp_wake_stub()` to execute immediately after transmitting the SHTC3 measurement command (`0x7866`), overlapping the 400 µs TSENS settling delay within the 14.5 ms SHTC3 conversion window (`450 µs` TSENS read + `14,050 µs` wait). Eliminates 15 ms of pre-sample CPU busy-wait self-heating on the silicon die and reduces Flow A wake stub active duration by 400 µs.
  * Corrected `SENS_TSENS_XPD_FORCE` register field configuration in `wake_stub_read_die_temp_centi_c()`.
* **Task Stack Floor Compliance & Checked Task Creation (`AUD-01` / `PIT-05-C`, `PIT-08-A`)** (`h1os_lifecycle.c`, `sub_sdcard.c`):
  * Increased `h1os_session_monitor_task` (`h1os_sess`) stack allocation from `3072` to `4096` bytes in `h1os_lifecycle.c` and `sdcard_mount_worker_task` (`sd_mount`) from `3584` to `4096` bytes in `sub_sdcard.c`, satisfying the `H1OS-STD-001` 4 KB stack floor for tasks executing VFS, NVS, flash partition erase/write, and formatted logging call chains.
  * Added explicit `BaseType_t` return status verification on `xTaskCreatePinnedToCore()` for `h1os_sess` with safe fallback to sleep transition on allocation failure.
* **Cross-Core Volatile Coherency & Atomic Session Expiry (`AUD-02` / `PIT-01-A`, `PIT-01-E`)** (`h1os_lifecycle.c`, `hal_io.c`, `h1os_lvgl.cpp`):
  * Qualified cross-task shared handles and flags (`s_session_expiry_us`, `s_session_running`, `s_session_task_handle`, `s_breath_task`, `s_breath_period_ms`, and `s_lvgl_task_handle`) with `volatile` and protected 64-bit `s_session_expiry_us` mutations across Core 0 and Core 1 with a critical section spinlock.
* **LVGL Lock Timeout Enforcement & Splash Refresh 80 MHz Droop (`AUD-04` / `PIT-01-B`, `PIT-07-B`)** (`h1os_lvgl.cpp`, `sub_display.cpp`):
  * Decoupled unconditional 240 MHz PM lock retention from `h1os_lvgl_lock()` so synchronous full OTP refreshes during boot splash (`lv_refr_now`) drop CPU frequency to 80 MHz during the ~1,400 ms `sub_display_wait_busy()` polling window while retaining 240 MHz `CpuMaxTurboScope` acceleration during pixel packing and SPI DMA frame commits.
* **Atomic NVS Runtime Blob Commit & Flash Wear Reduction (`AUD-05` / `PIT-05-D`)** (`orch_state.c`, `sub_power.c`):
  * Consolidated the three separate `sub_nvs_set_u32()` open/commit/close transactions in `orch_state_save_runtimes_to_nvs()` into a single atomic NVS commit, preventing torn multi-key state on brownout and reducing NVS flash wear.
* **SDMMC Block Timeout Margin & Checked Driver Return Codes (`AUD-06`, `AUD-07`, `AUD-08` / `PIT-04-D`, `PIT-08-A`)** (`sub_sdcard.c`, `sub_rtc.c`, `sub_audio.c/.h`, `sub_nvs.c`, `sub_display.cpp`, `orch_flow.c`, `h1os_lifecycle.c`):
  * Increased `host.command_timeout_ms` in `sub_sdcard_mount()` from `20 ms` to `100 ms` per `PIT-04-D` to prevent premature block write timeouts on mounted MicroSD media.
  * Added explicit `esp_err_t` return checking in `sub_rtc_set_time()`, `sub_rtc_cancel_countdown()`, `sub_audio_set_volume()`, and `sub_nvs_*()` initialization paths, and synchronized `sub_audio.h` Doxygen comments and `orch_flow.c` Pure Event Mode sleep logs.
* **Kconfig Banner Formatting & Spurious `kconfgen_tmp` Warning Elimination** (`sdkconfig.defaults*`):
  * Resolved recurring `NOTE: .../kconfgen_tmp... line was updated to ...n` notifications during CMake configuration by replacing trailing `=` characters in comment separator banners with `-` across all profile and component `sdkconfig.defaults` files. Upstream Espressif `kconfgen` mistakenly interpreted `# =========================================================================` as an empty key-value assignment (`CONFIG_FOO=`) due to an unconditional `line.endswith("=")` heuristic.
* **Kconfig Option Linting & Disabled Dependency Pruning** (`components/h1os/sdkconfig.defaults`, `examples/H1OS/sdkconfig.defaults.dev`, `examples/H1OS/sdkconfig.defaults.ci`, `profiles/sdkconfig.defaults.dev`, `profiles/sdkconfig.defaults.ci`, `examples/riscv_test/sdkconfig.defaults`):
  * Removed deprecated and obsolete LVGL 8 symbols (`CONFIG_LV_USE_OBJ`, `CONFIG_LV_USE_DEMO_TRANSFORM`, `CONFIG_LV_USE_DEMO_SCROLL`) and pruned 9 redundant `CONFIG_LV_USE_DEMO_*=n` sub-options that triggered Kconfig "disabled dependency" notifications while `CONFIG_LV_BUILD_DEMOS=n`.
  * Replaced non-existent `CONFIG_COMPILER_OPTIMIZATION_ASSERTION_LEVEL_DEBUG=y` with standard ESP-IDF v6.1 `CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE=y`.
  * Removed `CONFIG_ESP_SYSTEM_USE_EH_FRAME=y` from ESP32-S3 configuration profiles as runtime DWARF unwinding is strictly a RISC-V architectural choice (`depends on IDF_TARGET_ARCH_RISCV`) and invisible on Xtensa LX7.

## [2.4.0-dev] - 2026-10-24

### 🚀 Added & Architectural Evolution

* **Consolidated Elapsed-Runtime Empirical Battery Autonomy Engine & Exclusive ULP Resting Acquisition** (`sub_power.h/.c`, `orch_state.h/.c`, `orch_wake_stub.c`, `ulp/main.c`, `h1os_lifecycle.c`, `h1os_version.h`, `screen_system_health.c`, `docs/architecture/A8_battery_and_power_management.md`):
  * **Semantic Version Bump (`2.4.0-dev`):** Bumped minor version from `2.3.x` to `2.4.0-dev` following the consolidation of battery autonomy math directly into the `h1os` core (`sub_power`) and removal of external example battery estimators (`battery_estimator.c/.h`).
  * **Single-Level Elapsed Runtime Average Current (`avg_draw_ma`):** Removed redundant Level 2 active ratio/cycle tracking (`f_ulp`, `f_stub`, `f_app`, `active_draw_ma`, `total_ulp_ms`, `total_wake_stub_ms`, `ulp_entry_ccount`, `ulp_exit_ccount`, `ulp_total_cycles`, and `rdcycle` CSR reads) in favor of a lean, single-level elapsed runtime average current calculation (`avg_draw_ma`, `autonomy_days`, `mah_spent_lap`) over total elapsed time (`elapsed_sec = total_sleep_sec + total_app_run_ms / 1000.0f`).
  * **Gump Naming Rule & Lexicon Enforcement:** Renamed non-literal `wall_draw_ma` / `wall-clock` identifiers to literal, Gump-proof `avg_draw_ma` (`elapsed_sec`, `elapsed_hours`) and replaced informal jargon across headers and sources per `naming.md` and `lexicon.md`.
  * **Zero Hardcoded Currents & Dynamic Schedules:** Eliminated speculative current constants (0.045 mA, 28 mA, 36 mA) and dynamically integrates user-configured Flow A (`sample_interval_sec`) and Flow B (`flow_b_period_sec`) intervals.
  * **Exclusive ULP ADC & 8-Entry Ring Buffer:** Retired main CPU ADC reads during active execution to eliminate $I \cdot R$ load sag. The ULP-RISC-V coprocessor samples battery ADC exclusively during quiet deep sleep into an 8-entry circular ring buffer in RTC Slow SRAM (`ulp_vbat_ring[8]`).
  * **Folded Factor-of-2 Divider in ULP Calibration Handoff:** Pre-computed linear calibration parameters folding the $2\times$ divider directly into slope ($m_{\text{vbat}}$) and offset ($b_{\text{vbat}}$) using raw counts 2000 and 3000, allowing the ULP coprocessor to evaluate resting $V_{\text{BAT}}$ via a single shift and add.
  * **Diurnal Thermal Rebound Guard & Tenths-of-a-Percent SoC Resolution:** Upgraded `initial_soc_x10` and `current_soc_x10` to tenths of a percent ($0..1000 = 0.0\%..100.0\%$) and restricted discharge lap resets strictly to uninitialized boots, charger unplug transitions (`s_prev_bat_state` in `RTC_DATA_ATTR`), or $\ge 3.0\%$ SoC increases.
  * **Hardware Errata Review (`ERR-S3` Reclassified) & Rev B Pogo Interface (`E10`–`E15`):** Reclassified `ERR-S3` in `ERRATA.md` as an ESP-IDF / register semantics misunderstanding (`R/W` vs `W1TC` on `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` and level-low comparator clear ordering) rather than a silicon CDC defect, and added **Errata E15** specifying a 3-pin symmetrical center-hot (`[GND] [VBUS +5V] [GND]`) magnetic pogo-pin charging interface for 100% geometric reverse-polarity protection.

### 🛡️ Fixed & Hardened (Firmware Safety Invariants Audit)

* **ULP, Sleep/Wake & Subsystem Audit Remediation**:
  * Fixed `REG_GET_BIT` bitmask vs shift bug on `RTC_CNTL_RDY_FOR_WAKEUP` in `ulp/main.c` (`main()`) by using `REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)`.
  * Expanded ULP button tap detection window from `50..800 ms` to `30..2500 ms` (`BUTTON_TAP_MIN_MS = 30`, `BUTTON_TAP_MAX_MS = 2500`) with a 30 ms release-debounce check in `ulp/main.c`, eliminating the 800..2500 ms dead zone.
  * Added Zero-Volt Cable Guard in `sub_power_get_battery_status()` (`usb_conn && vbat < 3300U -> 4200 mV`) and fixed 2-cycle ULP ring buffer lookback (`lookback = (count >= 3) ? 2 : 1`).
  * Fixed NVS runtime load ordering in `h1os_early_system_bringup()` so `orch_state_load_runtimes_from_nvs()` executes after `orch_flow_determine_wakeup()` on cold boot, and added NVS runtime persistence on `execute_system_shutdown()`.
  * Fixed `sub_power_init_ulp()` invocation on wake flows and computed final Flow B sleep slice duration dynamically from `st->flow_b_period_sec` and `st->sample_interval_sec`.
  * Populated `sample.timestamp_sec` on each Flow A burst in `orch_wake_stub.c` and persisted `s_prev_bat_state` in `RTC_DATA_ATTR` in `h1os_lifecycle.c`.
  * Added `sub_rtc_init()` and `h1os_time_sync_rtc_to_system()` to `h1os_early_system_bringup()` so POSIX system time is synchronized with the PCF85063A hardware RTC and 32.768 kHz `CLKOUT` is disabled.
  * Fixed nested `h1os_lvgl_lock()` and 240 MHz CPU lock retention across the 2-second boot splash delay in `main/main.c` (`app_on_splash`).
  * Cached `i2c_master_dev_handle_t` handles in `hal_i2c.c` to eliminate runtime heap allocation/free on I2C register transactions; synchronized `sub_sdcard_unmount()` with in-flight async mount tasks; guarded `h1os_lvgl_has_pending_tasks()` with `lv_lock()`/`lv_unlock()`; wired `sub_audio_flush_frame()` on queue drain in `sub_audio.c`; isolated `HAL_PIN_EPD_DC` in `hal_io.c`; and aligned `ORCH_TRINODE_SPAN_C` (`15.0f`) in `orch_flow.c`.

* **Deterministic Static IPC Semaphores & Stack Relief** (`sub_audio.c`, `orch_flow.c`):
  * Replaced dynamic heap semaphore allocation (`xSemaphoreCreateBinary()`) in `sub_audio_send_command()` with static allocation via `xSemaphoreCreateBinaryStatic(&s_cmd_sync_sem_buffer)` and bounded 500 ms timeout.
  * Relieved 512-byte audio DMA frame buffers and 512-byte debug telemetry arrays (`shtc3T_ring`, `shtc3RH_ring`, `mcuT_ring`, `epdT_ring`) from task stacks into static `.bss` storage.

* **Inter-Core Volatile Coherency, FPU32 Discipline & Defensive Enum Trapping** (`orch_state.h/.c`, `orch_flow.c`, `sub_power.c`, `h1os_lifecycle.c`):
  * Qualified persistent RTC Slow Memory state block as `volatile orch_persisted_state_t s_persisted_state`.
  * Replaced double-precision literals `/ 100.0` with `/ 100.0f` across telemetry conversion routines, converted naked `int` declarations to explicit fixed-width types, and added a `default:` trap to `h1os_log_flow_banner()`.

## [2.3.2-dev] - 2026-10-21

### 🚀 Added

* **Zero-Calibration Steady-State SHTC3 Trust & Tri-Node Range Verification** (`orch_flow.c`, `orch_wake_stub.c`, `orch_math.h/.c`, `orch_state.h/.c`, `h1os.h`, `h1os_lifecycle.c`):

  * Enforced the **Zero-Calibration Hardware Principle**: removed all synthetic temperature offsets, ambient RH reconstitutions (`orch_math_reconstruct_ambient_rh`), slice trimming, fallback sensor substitutions (`orch_flow_evaluate_ambient_selection`), and MCU die taring (`die_tare_centi_c`).

  * Trusted the factory-calibrated Sensirion SHTC3 (`±0.2°C`, `±2% RH`) directly once consecutive Flow A deep-sleep samples satisfy the steady-state plateau gate (`|temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C` / `0.20°C` in `orch_math_is_plateau_settled()`), feeding the settled SHTC3 temperature and relative humidity directly into `orch_math_calc_psychrometrics(t_valid, rh_valid, &vp, &dew)`.

  * Scoped the SSD1681 on-glass sensor (`t_glass`) and ESP32-S3 internal SAR die sensor (`t_die`) strictly as **cross-node range verification sensors** (`trinode_temp_c`, `trinode_delta_c`, `trinode_confidence_pct`) to confirm the SHTC3 is operating within a normal thermal envelope without ever offsetting or overriding the SHTC3 reading.

  * Added `vapor_pressure_hpa`, `boot_vbat_mv`, `flow_a_period_sec`, and `flow_b_period_sec` to `h1os_telemetry_t` (`h1os.h`), eliminating direct Layer 3 (`orch_state.h`) header inclusion from Layer 4 UI screens (`screen_env_hero.c`, `screen_psychrometrics.c`, `screen_system_health.c`).

* **Schedule-Aware & Empirical Battery Autonomy Estimator** (`battery_estimator.h/.c`, `sub_power.c`, `screen_system_health.c`, `orch_state.h`):

  * Unified the 13-point LiPo Open-Circuit Voltage (OCV) lookup curve across `sub_power.c` (`s_lipo_table`) and `battery_estimator.c` (`s_lipo_ocv_lut` in basis points `0..10000`), resolving the 14.3% SoC discrepancy between Screen 3 battery percentage and autonomy calculations.

  * Added `battery_estimate_schedule_current_ma(flow_a_sec, flow_b_sec)` to compute baseline average current from configured sleep/wake intervals instead of a hardcoded `0.35 mA` constant, blending with empirical voltage-drop current (`battery_estimate_avg_current_ma`) once >= 1 hour of battery runtime has elapsed.

* **Explicit CPU Clock & Power Profile Scaling (`sys_clk_mode_t`)** (`hal_types.h`, `sub_power.h/.c`, `h1os.h`, `h1os_lifecycle.c`):

  * Defined `sys_clk_mode_t` in `hal_types.h` (`SYS_CLK_MODE_DYNAMIC = 0`, `SYS_CLK_MODE_FIXED_MAX = 1`, `SYS_CLK_MODE_FIXED_MIN = 2`) to make clock scaling explicit and prevent C struct zero-initialization from clamping CPU clock to 80 MHz.

  * Replaced ambiguous `bool enable_dfs_80mhz` in `h1os_lifecycle_t.session` with `sys_clk_mode_t clk_mode`.

* **Division-Free Q12 Fixed-Point Die Temperature Math** (`orch_wake_stub.c`, `orch_flow.c`, `orch_state.h/.c`):

  * Pre-computed `tsens_offset_centi_c` (`2052 + tsens_cal_centi_c`) from factory eFuse calibration on cold boot and replaced 32-bit integer division in `wake_stub_read_die_temp_centi_c()` with a single-cycle `Q12` fixed-point multiply-shift (`((int32_t)raw * 179651) >> 12`).

  * Explicitly configured `SENS_TSENS_CLK_DIV = 6` with a hardware `SENS_TSENS_RESET` pulse and 400 µs settling window in `orch_wake_stub.c` (removed legacy ESP32-S2 `SENS_TSENS_DAC` bitfield not present in ESP32-S3 `SENS_SAR_TSENS_CTRL2_REG`).

* **Layer 2-to-Layer 3 Decoupling Primitives** (`sub_display.h/.cpp`, `sub_power.h/.c`, `hal_types.h`):

  * Added `sub_display_get_glass_temp_centi_c()` in `sub_display.h/.cpp` and `orch_display_sync_latch_glass_temp()` in `orch_display_sync.c`.

  * Added `sub_power_set_sleep_slices()` in `sub_power.h/.c` so Layer 3 (`orch_flow_execute_sleep()`) computes Flow A/B slices, arms the external RTC, and installs the wake stub before invoking Layer 2 deep sleep entry.

  * Promoted `h1os_chime_type_t` and `h1os_wake_btn_t` to `hal_types.h` (Layer 1 shared types).

### 🔄 Changed

* **Dynamic Frequency Scaling Driver Refactor & Config Alignment** (`sub_power.h/.c`):

  * Refactored `sub_power_init_dfs()` to accept `sys_clk_mode_t`, dynamically setting `max_freq_mhz` to `CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ` (240 MHz) and `min_freq_mhz` based on the selected mode instead of hardcoded 240/80 MHz.

* **Strict 4-Layer Architectural Separation** (`sub_audio.c`, `sub_display.cpp`, `sub_power.c`, `orch_flow.c`, `h1os_lifecycle.c`):

  * Eliminated all upward and horizontal `#include` dependencies across Layer 2 (`sub_audio.c`, `sub_display.cpp`, `sub_power.c`) and Layer 3 (`orch_flow.c`), enforcing strictly downward `Layer 4 -> Layer 3 -> Layer 2 -> Layer 1` header inclusion.

  * Replaced cross-subsystem `sub_power_cpu_max_acquire()` calls in `sub_audio.c` with a dedicated `sub_audio` `esp_pm_lock_handle_t` (`ESP_PM_CPU_FREQ_MAX`).

* **Direct Psychrometric Math & 32-Bit SHTC3 Division** (`orch_math.h/.c`, `orch_wake_stub.c`):

  * Simplified `orch_math_calc_psychrometrics(temp_c, rh_pct, &vp, &dew)` to compose `orch_math_calc_vapor_pressure()` and `orch_math_calc_dew_point()` directly from settled SHTC3 readings without synthetic ambient RH reconstitution.

  * Corrected `orch_math_is_plateau_settled()` to evaluate `|initial - current| <= gate_threshold`, marked it `RTC_IRAM_ATTR`, and wired it into `bsp_wake_stub()`.

  * Replaced 64-bit software division (`65535LL`) in `bsp_wake_stub()` with 32-bit unsigned hardware division (`65535U`, single-cycle `quou`).

### 🗑️ Removed

* **Synthetic Sensor Calibration, Reconstitution & Tare Logic** (`orch_flow.c`, `orch_wake_stub.c`, `orch_math.h/.c`, `orch_state.h/.c`, `h1os.h`):

  * Removed `orch_flow_calc_pcb_thermal_offset()`, `orch_flow_evaluate_ambient_selection()`, `orch_math_reconstruct_ambient_rh()`, `die_tare_centi_c`, `pcb_thermal_offset_c`, and `amb_floor_temp_centi_c`.

* **Redundant Host-Mode Sensor Driver & Legacy Symbols** (`sub_sensor.c/.h`, `CMakeLists.txt`, `hal_types.h`, `orch_state.h`, `Kconfig`):

  * Removed unused `sub_sensor.c` and `sub_sensor.h` (along with `esp_driver_tsens` in `CMakeLists.txt`), as all environmental sampling executes exclusively in Flow A (`orch_wake_stub.c`) and Cold Boot intentionally reports `0.0` until settled Flow A samples arrive.

  * Removed unpopulated `HAL_PIN_SD_DET` (`GPIO 16`) and pre-mount GPIO polling in `sub_sdcard.c` (MicroSD `CD` pin is not wired to the ESP32-S3; all SDMMC lines use external pull-ups).

  * Pruned unused fields (`wake_timestamp_epoch`, `ulp_vbat_scale`, `ulp_vbat_offset_mv`, `app_stage`, `scratchpad_len`, `scratchpad[32]`) from `orch_persisted_state_t` and removed 7 orphaned `BSP_*` options from `Kconfig`.

### 🛠️ Fixed

* **ES8311 Standby Register Reset Bug (`0x00 = 0x1F` -> `0x1E`) & Unattended Wake Isolation** (`sub_audio.c`, `hal_io.c`, `h1os_boot_hook.c`):

  * Fixed critical silicon bug in `s_es8311_deinit[]` (`sub_audio.c`) where writing `{0x00, 0x1F}` (`ES8311_REG_RESET` with Bit 0 `RST_REG = 1`) immediately after `{0x0D, 0xFC}` reset all ES8311 control registers (`0x01..0x45`) back to Power-On-Reset active defaults (`0x0D = 0x01`), leaving the codec drawing \~3.5–4.5 mA continuously in deep sleep and heating both the codec and PCB. Changed `REG00` standby write to `{0x00, 0x1E}` (`CSM_ON = 0`, `RST_DIG/DAC/ADC/CSM = 1`, `RST_REG = 0`) and added `{0x13, 0x00}` and `{0x1C, 0x00}` to power down internal analog and MIC bias generators.

  * Added `RTC_DATA_ATTR static bool s_rtc_codec_in_standby` in `sub_audio.c` so `sub_audio_standby()` skips redundant I2C register writes on unattended deep-sleep RTC wakes when the codec is already parked in `< 1.0 µA` standby.

  * Fixed `HAL_PIN_PA_CTRL` (`GPIO 46`) readback bug where configuring `GPIO 46` as `GPIO_MODE_OUTPUT` (input buffer disabled) caused `gpio_get_level(HAL_PIN_PA_CTRL)` to return `0` even when driven HIGH, preventing `sub_audio_park_warm(true)` from pulling `PA_CTRL` LOW. Configured `HAL_PIN_PA_CTRL` as `GPIO_MODE_INPUT_OUTPUT` in `hal_io.c` and latched `GPIO 46 = 0` in `h1os_boot_hook.c`.

  * Enforced hardware startup/shutdown timing for the NS4168 Class-D amplifier (`120 ms` unmute turn-on delay `NS4168_STARTUP_DELAY_MS`, `80 ms` mute turn-off delay `NS4168_SHUTDOWN_DELAY_MS` in `sub_audio.c`), keeping the amplifier unmuted across active 30-second user sessions (`sub_audio_park_warm(false)` in `sub_audio_init()`) with a single silent I2S DMA frame flush (`sub_audio_flush_frame()`) after queue drain so short `50 ms` navigation tones and initial chime notes are never clipped.

* **Storage-Mode White Screen Shutdown (`CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN`) & EPD `BUSY` Synchronization** (`h1os_lvgl.cpp`, `h1os_lifecycle.c`, `sub_display.cpp`):

  * Fixed task self-deletion bug in `h1os_lvgl_stop()` (`h1os_lvgl.cpp`) when `h1os_shutdown()` is called from inside an LVGL `LV_EVENT_LONG_PRESSED` callback on the `h1os_lvgl` thread (`xTaskGetCurrentTaskHandle() == s_lvgl_task_handle`), which previously terminated the executing thread before `sub_display_clear_to_white_full()` could run.

  * Guarded `lv_lock()` and `lv_unlock()` in `h1os_lvgl_lock()` / `h1os_lvgl_unlock()` (`h1os_lvgl.cpp`) with `if (s_lv_display != NULL)` so ULP deep-sleep power-off (`ORCH_FLOW_CRITICAL_OFF`) does not dereference an uninitialized LVGL mutex prior to `lv_init()`.

  * Updated `sub_display_clear_to_white_full()` (`sub_display.cpp`) to wake and initialize the SSD1681 (`sub_display_init(false)`) when invoked while the panel is asleep or uninitialized.

  * Updated `sub_display_wait_busy()` (`sub_display.cpp`) to poll up to `15 ms` for the SSD1681 `BUSY` rising edge before returning early when `HAL_PIN_EPD_BUSY` reads LOW, ensuring `sub_display_wait_busy()` accurately reflects actual panel refresh duration (`~582 ms` partial, `~1404 ms` full OTP).

  * Gated `h1os_reset_session_timer()` inside the button state-transition check (`if (btns != s_prev_logged_btns && btns != 0)`) in `lvgl_keypad_read_cb()` (`h1os_lvgl.cpp`), eliminating 33 ms log spam while holding `BOOT` or `POWER` for a 2-second long-press.

* **ESP32-S3 Wake Thermal Soak & 240 MHz EPD Busy-Wait Elimination** (`h1os_lvgl.cpp`, `sub_display.cpp`, `orch_flow.c`, `h1os_lifecycle.c`, `hal_io.c`, `screen_diagnostics.c`, `sdkconfig*`):

  * Scoped `CpuMaxTurboScope` (`240 MHz` PM lock) in `lvgl_display_flush_cb()` strictly around the `< 2 ms` 1-bit pixel packing loop and removed the outer `sub_power_cpu_max_acquire()` wrapper around `lv_timer_handler()` in `h1os_lvgl_port_task()`, allowing the ESP32-S3 to drop to `80 MHz` during the `300 ms` (partial) to `2,200 ms` (full OTP) mechanical `sub_display_wait_busy()` polling window.

  * Disabled `CONFIG_SPIRAM_MEMTEST` and enabled `CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP=y` across `sdkconfig` profiles to eliminate the \~300 ms 8 MB Octal PSRAM march test at 240 MHz on every deep-sleep Flow B wake.

  * Reduced `epd_reset_pulse()` active spin-wait in `sub_display.cpp` from `20 ms` (`10 ms + 10 ms`) to `4 ms` (`2 ms + 2 ms`), reduced pre-sleep handoff delay in `h1os_lifecycle.c` from `50 ms` to `10 ms`, streamlined `hal_check_usb_ll()` in `hal_io.c` from `3.0 ms` to `1.1 ms`, removed the redundant `vTaskDelay(pdMS_TO_TICKS(250))` after `sub_display_wait_busy()` in `orch_flow_quiesce_peripherals()`, and disabled the internal pull-up on `HAL_PIN_EPD_BUSY` (`GPIO 8`) to eliminate `73 µA` continuous deep-sleep leakage.

  * Sampled `esp_clk_cpu_freq()` in `screen_diagnostics_render()` (`screen_diagnostics.c`) prior to acquiring `h1os_lvgl_lock(100)` so Screen 4 displays the true baseline CPU clock (`80MHz` in `SYS_CLK_MODE_DYNAMIC`) rather than the transient 240 MHz LVGL render lock frequency.

* **DFS Baseline Underclocking Trap on Default Lifecycle Config** (`sub_power.c`, `h1os_lifecycle.c`, `examples/H1OS/main/main.c`):

  * Fixed issue where omitting `.enable_dfs_80mhz` in application lifecycle config zero-initialized the parameter to `false`, causing `sub_power_init_dfs()` to force `max_freq_mhz = 80` and lock CPU cores permanently to 80 MHz despite `CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ=240`.

* **EWMA Historical Baseline Protection on UI Redraws (BUG-01)** (`orch_flow.c`, `orch_state.h`):

  * Gated `temp_historical_c` / `rh_historical_pct` EWMA updates and UART ring-buffer debug dumps behind `st->total_samples != st->last_ewma_sample_seq`, preventing interactive carousel navigation from corrupting historical trends.

* **LVGL Lock Symmetry & Non-Recursive Screen Refresh (BUG-02, BUG-03)** (`screen_base.c`, `screen_env_hero.c`, `screen_psychrometrics.c`, `screen_system_health.c`, `screen_diagnostics.c`):

  * Moved `h1os_lvgl_lock(100)` out of `screen_base_create()` to the top of each `screen_*_render()` function (matching `h1os_lvgl_unlock()`) and removed recursive `lv_refr_now(NULL)` calls inside keypad event callbacks.

* **Audio PCM Buffer Over-Read & Standby Chip-ID Check (BUG-04, BUG-05)** (`sub_audio.c`):

  * Fixed `SUB_AUDIO_PCM` in `sub_audio_play()` to divide byte length `len` by `sizeof(int16_t)`, preventing a 2x buffer over-read in `sub_audio_render_pcm_samples()`.

  * Removed the `!s_i2s_chan_enabled` rejection in `sub_audio_read_chip_id()` and added automatic DAC register re-initialization when waking the ES8311 from software standby.

* **Wake Context & Standby Wakeup Alignment (BUG-07, BUG-08)** (`h1os_lifecycle.c`, `h1os_lvgl.cpp`):

  * Fixed `ctx.sleep_duration_sec` in `on_wake` to report `flow_b_period_sec` on full-cycle RTC wakes and replaced deprecated `esp_sleep_enable_ext1_wakeup(..., ESP_EXT1_WAKEUP_ANY_LOW)` in `execute_system_shutdown()` with `esp_sleep_enable_ext0_wakeup(HAL_PIN_BUTTON_POWER, 0)`.

## [2.3.1-dev] - 2026-10-20

### 🛠️ Fixed & Refactored

* **EPD Quiesce Timeout & Core 0/1 Flush Collision Resolution** (`h1os_lvgl.cpp`, `orch_flow.c`, `sub_display.cpp`):

  * Increased peripheral drain timeout in `orch_flow_quiesce_peripherals()` from 2500 ms to 6000 ms to fully accommodate periodic full OTP waveform refreshes (\~2.2–2.8s) on Flow B Cycle 7.

  * Added explicit invocation of `h1os_lvgl_stop()` prior to `sub_display_wait_busy()` and display sleep transitions, preventing Core 0 from isolating pads (`gpio_hold_en` on `EPD_CS`/`EPD_RST`) and issuing sleep commands (`0x10`) while Core 1 is actively executing SPI DMA transfers.

* **Thread-Safe LVGL Multi-Core Synchronization** (`h1os_lvgl.cpp`, `h1os_lifecycle.c`):

  * Wrapped `lv_timer_handler()` in `h1os_lvgl_port_task()` on Core 1 with `lv_lock()` and `lv_unlock()`.

  * Guarded lifecycle callbacks (`on_boot`, `on_wake`, `on_splash`, `on_pre_sleep`) called from Core 0 with `h1os_lvgl_lock()` / `h1os_lvgl_unlock()` to eliminate concurrent invalidation area (`inv_p`) corruption and state deadlocks.

* **PCF85063A RTC Driver & Wake Stub Clock Stability** (`sub_rtc.c`, `sub_power.c`, `orch_wake_stub.c`):

  * Corrected `RTC_REG_CONTROL_2` clock output configuration in `orch_wake_stub.c` (lines 282, 406) from `0x00` to `0x07` (`CTRL2_COF_OFF`), stopping unwanted continuous 32.768 kHz `CLKOUT` oscillation on Flow A wakes.

  * Added retry handling to `sub_rtc_arm_countdown()` inside `sub_power_enter_deep_sleep_mode()` to prevent entering deep sleep with the countdown timer halted (`TE=0`) after transient I2C write failures.

  * Added 3-attempt I2C retry when clearing `RTC_REG_CONTROL_2` prior to awaiting `HAL_PIN_RTC_INT` line release.

* **ULP Coprocessor Stabilization & ADC Isolation** (`ulp/main.c`, `hal_io.c`, `sub_power.c`):

  * Recomposed `ulp/main.c` to immediately disarm `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` when waking the main Xtensa core, eliminating thousands of redundant re-wakes during active INT low pulses.

  * Replaced the hard abort at `main.c:206` (`!RDY_FOR_WAKEUP`) with a bounded wait loop to prevent dropping valid wake events during deep-sleep entry sequences.

  * Decoupled button level validation from `RTC_INT` evaluation and added timeouts to `ulp_riscv_adc_read_channel()` conversion loops.

  * Configured `HAL_PIN_BATTERY_ADC` to `RTC_GPIO_MODE_DISABLED` in `sub_power_enter_deep_sleep_mode()` and released RTC IO pin configurations to avoid digital input buffer interference on ADC1.

  * Gated `sub_audio_is_busy()` and `sub_audio_standby()` behind wake-cycle audio initialization checks to avoid unnecessary peripheral querying during non-audio sprints.

## [2.3.0-dev] - 2026-10-18

### 🚀 Added

* **Standardized Hybrid Component Configuration Baseline** (`components/h1os/sdkconfig.defaults`, `CMakeLists.txt`, `CMakePresets.json`):

  * Created component-level `sdkconfig.defaults` establishing the single source of truth for all hardware and silicon invariants (ESP32-S3-PICO-1-N8R8, 8MB QIO Flash @ 80MHz, 8MB Octal PSRAM @ 80MHz, ULP RISC-V coprocessor, FreeRTOS 1000Hz, and 1-bit monochrome LVGL v9 display engine).

  * Wired chained `SDKCONFIG_DEFAULTS` in `examples/H1OS/CMakeLists.txt`, `examples/boilerplate/CMakeLists.txt`, and `CMakePresets.json` (`components/h1os/sdkconfig.defaults;sdkconfig.defaults`).

  * Pruned `examples/H1OS/sdkconfig.defaults` (from 199 to 58 lines) and `examples/boilerplate/sdkconfig.defaults` (from 125 to 17 lines) to strictly application-specific overrides.

* **Dynamic Frequency Scaling (DFS) & Turbo Execution Invariants** (`sub_power.h/.c`, `h1os_lifecycle.c`, `h1os_lvgl.cpp`, `sub_audio.c`, `B3_firmware_standards.md`):

  * **80 MHz Quiescent Baseline:** Enabled automatic DFS gating with CPU cores constrained to 80 MHz during interactive standby, input polling, FreeRTOS idle, and sensor acquisition (`sub_power_init_dfs`).

  * **240 MHz LVGL Blitz:** Integrated RAII `CpuMaxTurboScope` and task-level turbo boost (`sub_power_cpu_max_acquire()`) during LVGL rendering, font glyph rasterization, 1-bit pixel packing, and SSD1681 differential SPI frame transfer, dropping cores back to 80 MHz immediately upon flush completion.

  * **240 MHz I2S Audio Clock Invariant:** Integrated turbo clock locks into `sub_audio_init()` and `audio_worker_task()`, preventing APB frequency droop during DFS from reducing I2S MCLK/BCLK dividers and ensuring chimes/tones never shift octaves lower or cause DMA underruns.

  * Formalized Rule 11 in `B3_firmware_standards.md` and `.agents/skills/h1os-firmware-standards/SKILL.md`.

* **API Versioning Header & Query Primitives** (`components/h1os/include/h1os/h1os_version.h`):

  * Introduced unified versioning header with semantic version macros (`MAJOR`, `MINOR`, `PATCH`, `TAG`, `STRING`, `CODE`, `CHECK`) and inline getters (`h1os_version_get_string()`, `_major()`, `_minor()`, `_patch()`, `_build_date()`, `_build_time()`, `_code()`).

  * Integrated dynamic version reporting into `examples/H1OS/main/main.c`, `screens/screen_diagnostics.c`, and `examples/boilerplate/main/main.c`.

* **Three-Tier Firmware Engineering & Safety Standards** (`.clang-format`, `tools/check_format.py`, `.agents/skills/h1os-firmware-standards/SKILL.md`, `docs/architecture/B3_firmware_standards.md`):

  * **Layer 1 (Automated Formatting):** Deployed root `.clang-format` (LLVM base, C++17, Linux braces, 4-space indent, 100-col limit, right-aligned pointers, scoped consecutive alignment) with automated CLI formatting tool `tools/check_format.py` supporting both in-place formatting and `--check` CI dry-run validation.

  * **Layer 2 (10 Embedded Safety Rules):** Formalized strict safety invariants across firmware layers: fixed-width types (`<stdint.h>`), FPU32 single-precision discipline, zero runtime `malloc`, guard-clause early exit pattern, checked return codes (`[[nodiscard]]`), bounded stacks, non-blocking ISRs, inter-core volatile coherency for RTC Slow Memory, exhaustive enum default trapping, and pointer sanitization.

  * **Layer 3 (Compiler Hardening):** Injected private compiler flags on `${COMPONENT_LIB}` in `components/h1os/CMakeLists.txt` (`-Wall`, `-Wextra`, `-Werror`, `-Wshadow`, `-Wdouble-promotion`, `-Wformat=2`, `-Wno-format-nonliteral`, `-Wstrict-prototypes`, `-Wno-missing-field-initializers`), transforming embedded best practices into automated build-time blockers.

  * **Agent Skill Integration:** Created `.agents/skills/h1os-firmware-standards/SKILL.md` to equip AI coding assistants with authoritative firmware constraints, compile flag rationale, and architectural rules.

* **Three-Series Architecture Taxonomy (Option 2)** (`docs/architecture/`):

  * Reorganized internal engineering documentation into a clean 3-series taxonomy:

    * **Series A (Silicon & Hardware):** `A0_system_governance.md` – `A7_sensor_psychrometrics.md`.

    * **Series B (Developer & Application Layer):** `B1_api_and_services.md`, `B2_state_machine.md`, `B3_firmware_standards.md`.

    * **Series C (Operations & Governance):** `C1_benchmarks_and_verification.md` – `C4_changelog_policy.md`.

  * Resolved filename collisions and cross-linked references across `README.md` and architecture manifests.

### 🛠️ Fixed & Refactored

* **Codebase Consolidation & Pruning (Phases 1–5)**:

  * **Phase 1 (Cold-Boot & ULP Hardening):** Enforced 30 ms ULP glitch filter, Wake-on-Release rule, CDC power latch ordering, eFuse linear battery scaling ($M \cdot X + B$), and bootloader GPIO 17 latch validation.

  * **Phase 2 (Fast Wake Stub & Drain Centralization):** Installed Flow A wake stub in `sub_power.c` and centralized the PCF85063A 50 ms drain barrier. Deleted legacy `orch_flow_execute_sensor_sample()` and FreeRTOS Flow A branch.

  * **Phase 3 (Audio Dispatch Consolidation & Backward-Compatibility Purge):** Consolidated acoustic playback into a single typed entry point `sub_audio_play(type, data, len)` (`SUB_AUDIO_TONE`, `SUB_AUDIO_CHIME`, `SUB_AUDIO_PCM`). Completely removed deprecated backwards-compatible wrappers (`sub_audio_play_tone`, `sub_audio_play_chime`, `sub_audio_play_pcm`, `sub_audio_play_tone_async`, etc.) for a clean, forward-moving developer API.

  * **Phase 4 (Algorithmic Optimization & DMA Streamlining):** Replaced $O(N^2)$ bubble sort in `sub_power_read_battery()` with $O(N)$ in-place insertion sort. Unified psychrometric reconstruction in `orch_math_calc_psychrometrics()` with single-pass Magnus evaluation (1 `expf` and 1 `logf`). Consolidated 4 duplicate SPI transaction sequences into `epd_commit_ram_dma()`.

  * **Phase 5 (Modular Sizing & Monolith Decomposition):** Decomposed `h1os_start()` (reduced from 120 lines to 8 lines), `orch_flow_transition_to_sleep()`, and `orch_flow_query_telemetry()`. Replaced 30+ separate ES8311 init calls with table-driven register arrays (`s_es8311_init_pre_charge`, `s_es8311_init_post_charge`).

* **Telemetry Logging Double-Promotion Remediation** (`orch_flow.c`, `sub_display.cpp`):

  * Explicitly cast float arguments to `(double)` in `ESP_LOGI` variadic formatters, eliminating `-Wdouble-promotion` errors while retaining single-precision FPU execution on arithmetic expressions.

* **Example Boilerplate Alignment** (`examples/H1OS/main/main.c`, `screens/screen_diagnostics.c`):

  * Updated `main.c` to evaluate `h1os_start()` return status per Rule 5 checked return code standards.

  * Expanded ULP dispatch reason rendering in `screen_diagnostics.c` with an exhaustive `switch` block covering `BOOTLOADER` and `POWER_OFF` dispatch modes.

  * Synchronized H1OS semantic version definitions in `h1os.h` to `2.1.0-alpha`.

## [2.2.0-prod] - 2026-10-16

### 🚀 Added

* **ULP-RISC-V Autonomous Reactive Coprocessor & Dual-Wake Engine** (`components/h1os/ulp/main.c`, `sub_power.c/.h`, `hal_io.c`):

  * Established dual-wake architecture in `RTC_CNTL_ULP_CP_TIMER_REG` with simultaneous `RTC_CNTL_ULP_CP_SLP_TIMER_EN` (60s Flow A soft-timer) and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` (instantaneous RTC GPIO wake).

  * Explicitly enabled low-power IO sampling clock (`io_mux_enable_lp_io_clock()`) on ESP32-S3 for `HAL_PIN_RTC_INT` (GPIO 5), `HAL_PIN_BUTTON_BOOT` (GPIO 0), and `HAL_PIN_BUTTON_POWER` (GPIO 18) during sleep pad isolation, resolving silicon clock-gating of RTC level sampling.

  * Implemented pure ULP wake to Xtensa CPU (`ESP_SLEEP_WAKEUP_ULP`) with zero CPU digital interrupt matrix exposure (`.intr_type = GPIO_INTR_DISABLE`), completely eliminating CPU watchdog panics.

  * Implemented autonomous button hold classification in ULP: short tap ($30\text{ms}-2500\text{ms}$) wakes Flow B (`ULP_DISPATCH_MAIN_WAKE`), BOOT held $>2.5\text{s}$ triggers ROM bootloader jump (`ULP_DISPATCH_BOOTLOADER_JUMP`), and POWER held $>2.5\text{s}$ executes clean power-off (`ULP_DISPATCH_POWER_OFF`).

* **Two-Stage Tactile Click Interaction** (`main.c`, `h1os_lifecycle.c`):

  * Stage 1 (Deep Sleep Wake): First click is caught by ULP, waking Flow B to toggle the inverted awake badge in the UI without advancing the page or firing an audio tone.

  * Stage 2 (Active Navigation): Second click is handled by running LVGL keypad event loop, triggering a 15ms audio tick and cycling the carousel.

* **Canonical Build Skill & Tooling Harness Upgrade** (`.agents/skills/h1os-build/SKILL.md`, `idf_build_mcp_server.py`):

  * Created `.agents/skills/h1os-build/SKILL.md` eliminating environment discovery loops and standardizing one-liner builds via `Microsoft.v6.1.PowerShell_profile.ps1`.

  * Upgraded MCP server with dynamic workspace detection, `build_dir` (`build_prod`/`build_dev`) support, and automatic Espressif v6.1 profile execution.

### 🛠️ Fixed & Refactored

* **ULP Spurious 0ms Wake Elimination & Mandatory Glitch Filter** (`components/h1os/ulp/main.c`, `components/h1os/src/hal_io.c`):

  * Added a 100 µs settling delay in `hal_io_isolate_sleep_pads()` following LP IO clock enabling (`io_mux_enable_lp_io_clock()`) before clearing `RTC_GPIO_STATUS_W1TC_REG`, ensuring input buffers synchronize the external 3.3V high level from hardware pull-up resistors and preventing `0x040001` from immediately re-latching.

  * Made the ULP glitch filter strictly mandatory (`hold_ms < 20`): spurious wakes with 0ms hold or unheld pins are immediately recorded as `GLITCH_FILTERED`, clearing RTC interrupt flags and halting without waking the main processor.

  * Prioritized actively held LOW levels (`boot_btn == 0` or `pwr_btn == 0`) during ULP button arbitration over stale interrupt latch status bits.

* **Active Flow B Direct Button Monitor & Session Keepalive** (`components/h1os/src/h1os_lifecycle.c`, `components/h1os/src/h1os_lvgl.cpp`):

  * Integrated 50 ms direct polling of `hal_io_read_buttons()` inside `h1os_session_monitor_task`, logging hardware button transitions (`[HAL_BTN]`) and resetting the interactive session timer directly on COM3, completely decoupling button event visibility from LVGL display flush delays.

  * Explicitly bound LVGL keypad indev to the active display (`lv_indev_set_display(s_lv_keypad_indev, s_lv_display)`).

  * Streamlined `h1os_lvgl_port_task` loop by removing redundant outer recursive locks around `lv_timer_handler()` and clamping delay to 30 ms.

* **Audio Codec Sleep Isolation & Thermal Mitigation** (`h1os_lifecycle.c`, `sub_audio.c`):

  * Strictly gated ES8311 codec and NS4168 amplifier initialization behind user presence (`is_user_wake = (!is_wake) || button_woke`).

  * Unattended periodic RTC wakes completely bypass audio initialization, keeping the codec in <1.0 µA standby and eliminating 26°C–32°C enclosure thermal oscillation.

  * Bound audio volume strictly to lifecycle presentation settings (`volume_pct`), defaulting to `0` (muted) until explicitly initialized.

* **Telemetry NA Standard & Elimination of Hardcoded Fallbacks** (`orch_state.c`, `sub_sensor.c`, `h1os_lifecycle.c`):

  * Zeroed out all persistent metrics on cold boot (`amb_floor_temp_centi_c`, `window_low_temp_centi_c`, `window_high_temp_centi_c`, `last_glass_temp_centi_c` set to `0`), establishing `0.0°C` / `0%` as the unambiguous indicator for uninitialized / NA telemetry.

  * Changed `sub_sensor_read_mcu_die_temp()` error fallback from synthetic `25.0f` to `0.0f`.

  * Removed silent fallback timeouts (`300s`, `120s`, `30s`, `60%`) in `h1os_lifecycle.c`, enforcing strict error logging (`ESP_LOGE`) and clean aborts on unconfigured contract parameters.

* **Diagnostic Modularity & Target-Scoped Build Cleanliness** (`orch_flow.c`, `examples/H1OS/CMakeLists.txt`):

  * Extracted inline ring buffer serial hexdump into a modular static helper: `orch_flow_dump_ring_debug()`.

  * Added target-scoped compiler warning suppression for `__idf_lvgl__lvgl` (`PRIVATE -w` and `SYSTEM TRUE`), eliminating FreeRTOS atomic header unused function warnings without relaxing diagnostics on application code.

## [2.1.0-alpha] - 2026-10-12

### 🚀 Added

* **SSD1681 E-Paper Maintenance & Scheduled Refresh Policy** (`sub_display.cpp/.h`, `orch_state.c/.h`, `orch_display_sync.c/.h`, `h1os_lvgl.cpp`, `h1os_lifecycle.c`, `Kconfig`):

  * Added anti-ghosting quota tracking (`epd_partial_refresh_count`) in persistent RTC Slow memory, automatically triggering a full OTP refresh after every 6 partial updates (`CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT`, default 6; guarantees full refresh $\le 24\text{h}$ at 4h max sleep) to reset residual DC bias.

  * Added long-term storage panel neutralization: implemented `sub_display_clear_to_white_full()` in Layer 2 and `h1os_shutdown_for_storage()` in Layer 4, driving the display to clean white (`0xFF`) before cutting power (`CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN`) to protect microcapsule chemistry against permanent dye migration.

* **Full Typography Suite Bold Weight & Strong Autohinting** (`tools/generate_1bpp_fonts.py`, `components/h1os/CMakeLists.txt`):

  * Updated font generator to discover and prioritize `Montserrat-Bold.ttf` across all point sizes (`14`, `16`, `18`, `20`, `24`, `32`).

  * Added `--autohint-strong` to all bilevel rasterization invocations across both Montserrat and DejaVu suites, generating solid 2-to-3-pixel stems and eliminating hairline dropouts and stroke erosion on 188 DPI monochrome electrophoretic glass.

* **Asynchronous Audio Worker Subsystem** (`sub_audio.c/.h`):

  * Dedicated FreeRTOS background task (`h1os_audio_worker`, 4 KB stack, priority 5) with thread-safe FreeRTOS command queue (`audio_cmd_t`).

  * Decoupled tone synthesis and chime presentation from the LVGL render loop, eliminating UI stutter and render blocking.

  * Added non-blocking asynchronous APIs: `sub_audio_play_tone_async()`, `sub_audio_play_chime_async()`, and `sub_audio_play_pcm_async()`.

  * Added raw 16-bit signed PCM audio clip playback (`sub_audio_play_pcm()` and `sub_audio_play_pcm_async()`) supporting dynamic sample rates, chunked I2S DMA streaming, and soft-mute ramps.

  * Added audio state queries and synchronization: `sub_audio_is_busy()`, `sub_audio_wait_idle()`, and `sub_audio_is_ready()`.

* **Dynamic Session Intervals** (`h1os.h`, `orch_state.c/.h`, `h1os_lifecycle.c`):

  * Added user-configurable `flow_a_period_sec` and `flow_b_period_sec` fields to `h1os_lifecycle_t.session` and `orch_persisted_state_t`.

  * Replaced hardcoded sleep timeouts with dynamic runtime intervals for Flow A telemetry sample bursts and Flow B UI presentation sessions.

### 🛠️ Fixed & Refactored

* **Deep Sleep Premature Wakeup & Dual-Period Sleep Policy** (`hal_io.c`, `orch_flow.c`):

  * Configured persistent RTC IO pull-ups (`rtc_gpio_init`, `rtc_gpio_set_direction(INPUT_ONLY)`, `rtc_gpio_pullup_en`, `rtc_gpio_pulldown_dis`) on `HAL_PIN_RTC_INT` (GPIO 5), `HAL_PIN_BUTTON_BOOT` (GPIO 0), and `HAL_PIN_BUTTON_POWER` (GPIO 18) during deep sleep pad isolation (`hal_io_isolate_sleep_pads()`). Because standard digital GPIO pull-ups lose power when `VDD3P3_CPU` drops, the open-drain PCF85063A INT pin previously floated LOW within seconds, triggering false `ESP_SLEEP_WAKEUP_EXT1` wakeups (<10s).

  * De-initialized RTC GPIO domain on wake in `hal_io_release_pad_holds()` (`rtc_gpio_deinit()`) to seamlessly restore pins to standard digital GPIO peripherals.

  * Implemented Dual-Period deep sleep coordination in `orch_flow_transition_to_sleep()`: the external PCF85063A is armed for the full display interval (`sleep_sec`), while the internal ESP32 timer is armed for the sub-interval telemetry period (`sample_interval_sec < sleep_sec`).

  * Implemented Sub-Sample Truncation Discard Policy in `orch_flow_execute_sensor_sample()`: the internal timer rearms *only* if the next sample timeout lands before external RTC countdown expiry (`next_sample_sec < rem_sec`). If the next sample lands at or after RTC expiry, rearming is discarded (`internal_sleep_sec = 0`), allowing the external PCF85063A interrupt line to trigger the main UI refresh cleanly without runt micro-wakes.

* **OS Diagnostics Typography Polish & Dual-Period Log Clarification** (`screen_diagnostics.c`, `orch_flow.c`):

  * Standardized Screen 4 (OS Diagnostics) to use high-contrast bilevel bold typography (`H1OS_FONT_14` Montserrat Bold) across all diagnostic rows (Reset reason, Wake causes, ULP, Heap, Stack HWM, Wakes counter, CPU/DFS), eliminating thin 1-pixel hairline stems from DejaVu regular.

  * Added explicit deep sleep log output distinguishing between the external RTC UI wake countdown (`sleep_sec` = 120s) and the internal headless sensor sample timer (`internal_sleep_sec` = 60s).

* **Flow B Wake Cycle Differential Partial Refresh** (`h1os_lifecycle.c`, `h1os_lvgl.cpp/.h`, `sub_display.cpp/.h`, `orch_display_sync.c/.h`):

  * Implemented `sub_display_sync_previous_frame()` in Layer 2 to pre-synchronize SSD1681 hardware RAM `0x26` (Red / Previous RAM) with the pre-sleep frame over SPI DMA.

  * Linked `orch_display_sync_restore_to_framebuffer()` in Layer 3 into `h1os_lifecycle.c` Flow B wake dispatch, restoring the 5000-byte pre-sleep frame from flash partition `epd_frame`.

  * Configured `s_first_boot_flush = !is_wake_cycle` in `h1os_lvgl.cpp`, ensuring system boots perform a full OTP wiping sequence while deep sleep wake cycles trigger silent \~300 ms differential partial refreshes with zero whole-screen flashing.

* **ES8311 Ready State Polling & Audio Clipping Remediation** (`sub_audio.c`):

  * Implemented `sub_audio_wait_until_ready()` validating Chip ID (`0xFD` = `0x83`, `0xFE` = `0x11`) and polling Register `0xFC` (`FLAG_CSM_CHIP`) bits 6:4 until the Chip State Machine exits state `S0` (Power Down).

  * Eliminates audio blips and clipped initial transients caused by streaming I2S frames before internal PLL and analog bias circuitry stabilize.

* **Hardware-Clean Pop-Free Audio Teardown** (`sub_audio.c`):

  * Implemented 5-step clean teardown sequence: 5 ms group delay drain $\rightarrow$ soft-mute (`0x31` `DAC_DSMMUTE = 0x40`) $\rightarrow$ 15 ms `DAC_RAMPRATE` volume ramp-down $\rightarrow$ `PA_CTRL` Class D amplifier mute (`GPIO 46` = 0) $\rightarrow$ ultra-low-power silicon standby (`<1.0 µA`).

  * Added `sub_audio_wait_idle()` synchronization to `h1os_shutdown()` and `orch_flow_transition_to_sleep()` to guarantee all audio pipelines drain and mute before battery latch release or sleep entry.

* **Keypad Long-Press Shutdown vs Navigation Remediation** (`main.c`):

  * Separated LVGL keypad events: `LV_EVENT_SHORT_CLICKED` exclusively advances screen navigation carousel with non-blocking feedback tones (`sub_audio_play_tone_async()`).

  * `LV_EVENT_LONG_PRESSED` triggers graceful power off (`h1os_shutdown()`) with atomic state latching to prevent re-entrant navigation loops.

* **Thermal Mitigation & Presentation Chime Masking** (`main.c`, `h1os_lifecycle.c`):

  * Restricted sleep/wake chime triggers strictly to Flow B application presentation cycles.

  * Defaulted `chime_mask` in `main.c` to boot and shutdown chimes only (`(1 << H1OS_CHIME_BOOT) | (1 << H1OS_CHIME_SHUTDOWN)`), suppressing sensor cavity self-heating during periodic sleep/wake cycles.

* **I2S Channel State Collision Remediation** (`sub_audio.c/.h`):

  * Added hardware state tracker `s_i2s_chan_enabled` and guarded all `i2s_channel_enable()` and `i2s_channel_disable()` transitions.

  * Guaranteed `sub_audio_standby()` is entered immediately after boot-time ES8311 register initialization, silencing audio clocks and preventing the `E (2871) i2s_common: i2s_channel_enable(1485): the channel has already enabled` fault on navigation click tones.

  * Added `sub_audio_deinit()` for complete teardown of worker tasks, command queues, and I2S peripherals.

* **Hardware SOF-Based USB Host & Charger Detection** (`hal_io.c/.h`, `sub_power.c/.h`, `h1os_lifecycle.c`):

  * Implemented Layer 1 `hal_check_usb_ll()` verifying live USB Full-Speed Start-Of-Frame (SOF) raw interrupt pulses and frame counter deltas over 1.5 ms.

  * Removed high-overhead `esp_driver_usb_serial_jtag` component dependency and tick hook overhead.

  * Combined USB host detection with Zero-Volt Cable Guard (`< 100 mV`) in `h1os_get_telemetry()`, preventing phantom 100% battery readings on UI when running on external USB power without an attached cell.

## [2.0.0-alpha] - 2026-10-10

### 🚀 Added

* **Clean-Slate 4-Layer Unidirectional Architecture**:

  * **Layer 1: HAL** (`hal_types.h`, `hal_io.c/.h`, `hal_i2c.c/.h`, `hal_spi.c/.h`, `hal_flash.c/.h`): Fixed-width types, RTC pad holds, thread-safe mutexed I2C Driver V2 on GPIO 47/48, 20 MHz DMA SPI Master, sector-aligned raw partition read/write for `epd_frame` (16 KB).

  * **Layer 2: Hardware Subsystem Managers** (`sub_display.cpp/.h`, `sub_sensor.c/.h`, `sub_rtc.c/.h`, `sub_power.c/.h`, `sub_audio.c/.h`): SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26), partial waveform LUT (0x32), GPIO 8 BUSY semaphore ISR synchronization, glass thermistor read (0x1B), SHTC3 NIST physical read with CRC-8, MCU TSENS silicon temperature, PCF85063A POSIX timekeeping & countdown timer, 12 dB attenuated battery ADC with 16-sample trimmed outlier filtering, ES8311 software standby (<1.0 µA @ Reg 0x0D).

  * **Layer 3: System Pipeline & Orchestrator** (`orch_state.c/.h`, `orch_math.c/.h`, `orch_flow.c/.h`, `orch_display_sync.c/.h`): RTC Slow SRAM state (<512 B), 32-slot Tri-Node ring buffer, August-Roche-Magnus invariant psychrometric equations, continuous recursive EWMA filter, Flow A/B arbiter with Zero-Hour collision hand-off, Thermal Lockout MUX, deferred dirty flash frame sync engine.

  * **Layer 3: ULP-RISC-V Coprocessor Hardware Monitor** (`ulp/main.c`, `ulp/CMakeLists.txt`): Coprocessor firmware running autonomously in RTC Slow SRAM for battery ADC threshold monitoring (`ADC1_CH3`), hardware RTC arbitration (`GPIO 5`), and button debounce (`GPIO 0/18`), embedded via `ulp_embed_binary()`.

  * **Layer 3: RTC Fast Memory Deep Sleep Wake Stub** (`orch_wake_stub.c/.h`): `RTC_IRAM_ATTR` wake stub running directly from RTC Fast Memory (<3ms execution) on deep sleep timer wake, executing register-level bit-bang I2C sensor sampling without powering flash cache or booting FreeRTOS.

  * **Layer 4: Application Lifecycle API** (`bsp.h`, `bsp_common.c`): `bsp_app_start()`, `bsp_app_sleep()`, `bsp_app_shutdown()`, and unified getter `bsp_app_get_telemetry()`.

* **Thick 14pt Montserrat Font** (`bsp_font_montserrat_14_1bpp.c`):

  * Re-rasterized using `npx lv_font_conv` from `Montserrat-Bold.ttf` with fast-kern tables and FontAwesome icons, resolving thin 1-pixel stroke illegibility on 200x200 monochrome e-paper.

### 🛠️ Fixed & Refactored

* **Keep All Gates Open Policy Enforced**:

  * Permanently asserted `BAT_CTRL` (`GPIO 17` = 1) and `EPD_3V3_EN` (`GPIO 6` = 0) with RTC pad holds during sleep.

  * Audio Domain `PA_EN` (`GPIO 42` = 0) kept held LOW across sleep to prevent ES8311 ESD protection diodes from forward-biasing and clamping shared I2C bus (`GPIO 47/48`) to \~0.7V. ES8311 enters software standby (<1.0 µA) without hard power cut.

* **Deep Sleep Wake Lifecycle Dispatch**:

  * Fixed legacy bug in `bsp_app_start()` where `ESP_RST_DEEPSLEEP` fell into `bsp_power_off()`; now correctly restores dirty frame buffer and dispatches `on_wake()`.

* **Legacy Code Purged (Component Cleansing)**:

  * Completely purged 16 obsolete legacy duplicate source and header files from `components/esp32-s3_bsp/`:
    `bsp_sensors.c/.h`, `bsp_equ_math.c/.h`, `bsp_env_telemetry.h`, `bsp_rtc.c/.h`, `bsp_rtc_mem.c/.h`, `bsp_i2c.c/.h`, `bsp_display.cpp/.h`, `bsp_audio.c/.h`, `pinout.h`.

  * Decoupled and rewired remaining higher-level modules (`bsp_common.c`, `bsp_power.c`, `bsp_button.c`, `bsp_sdcard.c`, `bsp_time.c`, `bsp_lvgl.cpp`) to Layer 1 HAL primitives (`hal_types.h`, `hal_io.h`, `hal_i2c.h`), Layer 2 Subsystems (`sub_sensor`, `sub_rtc`, `sub_display`, `sub_power`, `sub_audio`), and Layer 3 Orchestrators (`orch_state`, `orch_flow`, `orch_display_sync`).

  * Preserved historical code in `legacy_reference/` as an immutable reference backup.

* **H1OS Transition & Architecture Elevation**:

  * Formally rebranded platform to **H1OS** (Class-E Environmental Operating System) under Semantic Versioning `1.0.0-alpha`.

  * Introduced primary master umbrella header [h1os/h1os.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/h1os/h1os.h) exposing declarative lifecycle entry points (`h1os_start()`, `h1os_get_telemetry()`, `h1os_sleep()`, `h1os_shutdown()`).

  * Migrated flagship demonstration application to `examples/H1OS` with `project(h1os)`.

  * Rewrote `examples/H1OS/main/main.c` to consume telemetry exclusively through `bsp_app_get_telemetry(&telem)` and log H1OS startup branding.

  * Successfully compiled and linked `h1os.elf` with Ninja under ESP-IDF v6.1 dev profile (`build_dev/`).

* **Low-Level Peripheral Verification & Register Truth Audit**:

  * Created `docs/perf_and_drivers/` with 8 comprehensive physical hardware specifications documenting every IC's init, deinit, runtime, sleep, and register parameters.

  * **PCF85063A (`sub_rtc.c`)**: Corrected countdown timer clock frequency prescaler (`TCF`) bit shifting into bits `[4:3]` (`(2 << 3)` for 1Hz and `(3 << 3)` for 1/60Hz); removed incorrect `TIE` bitmask from `Control_2` (bit 2 is `COF[2]`); added 12.5pF crystal capacitance selection (`CTRL1_CAP_SEL_12_5PF`) in `Control_1`.

  * **SSD1681 (`sub_display.cpp` & `hal_spi.c`)**: Properly split factory 159-byte partial LUT across registers `0x32` (153B), `0x3F` (1B), `0x03` (1B), `0x04` (3B), and `0x2C` (1B); configured display option `0x37` and border waveform `0x3C` (`0x80`); used differential refresh sequence `0xCF`; added 2 MHz 3-wire half-duplex SPI device handle and continuous CS hold for on-glass thermistor readout (`0x1B`).

  * **ES8311 & NS4168 (`sub_audio.c`)**: Implemented complete 22-register reference clock tree and analog bias initialization; enforced `PA_EN` (`GPIO 42` = 0) and muted `PA_CTRL` (`GPIO 46` = 0); ported 15-register zero-heat deep standby sequence (<1.0 µA); documented I2S root clock `PLL_160M` dependency and verified that ESP-IDF's automatic `ESP_PM_APB_FREQ_MAX` lock prevents DFS pitch drops and sample rate stretching during active tone streaming.

  * **Power & Battery (`sub_power.c` & `hal_io.c`)**: Aligned 13-point LiPo OCV lookup table with calibrated hardware reference; enforced RTC peripheral power domain retention (`ESP_PD_DOMAIN_RTC_PERIPH`) across deep sleep to lock `BAT_CTRL` latch (`GPIO 17` = 1).

  * **Hardware Pull-Up Alignment**: Formally documented external 100 kΩ pull-ups on `GPIO 0` (BOOT) and `GPIO 18` (POWER) in `docs/perf_and_drivers/07_tactile_buttons_and_led.md` and `hal_io.c`; verified external 4.7 kΩ pull-ups on `GPIO 47/48` (I2C) with internal pull-ups disabled in `hal_i2c.c`.

## [1.3.1] - 2026-10-09

### 🛠️ Fixed & Refactored

* **Deterministic Two-Flow Cadence & Sleep Freeze Remediation** ([bsp_power.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_power.c), [bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * **Eliminated Unbounded Button Release Loop**: Fixed the 5-minute device hang where `bsp_enter_sleep()` executed an unbounded `while (gpio_get_level(BOOT) == 0 || gpio_get_level(POWER) == 0)` loop on headless sprints without configured digital input buffers. Bypassed button checking completely for Flow A (`BSP_INIT_MODE_MINIMAL`) and bounded Flow B checking to a hard 200 ms timeout (max 4 iterations $\times$ 50 ms).

  * **Zero-Hour Collision & Handoff Resolution**: When both Flow A (internal timer: 60s) and Flow B (external PCF85063A countdown timer: 120s / IRL) arrive at zero hour, the $<10\,\text{ms}$ cold sensor sprint always executes first out of deep sleep, queries the PCF85063A over I2C, and promotes cleanly to Flow B.

  * **Flow B Timer Invalidation**: Whenever Flow B wakes (via external RTC alarm, button press, or sprint promotion), it immediately cancels Flow A's internal sleep timer via `esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER)`, preventing premature timer interrupts.

  * **Pure I2C Headless Sprint**: Stripped unnecessary GPIO ISR registration and button sampling from `bsp_hot_wake_sprint_init()`. The sensor sprint exclusively manages I2C and SHTC3/PCF85063A registers, leaving button GPIO configuration strictly to `bsp_io_early_init()` in Flow B.

  * **Preserved Bootloader Power Ownership**: Maintained authoritative bootloader control of power gates (`GPIO 17` Power Hold, `GPIO 6` EPD/Sensor 3.3V, `GPIO 42` Audio) with pad holds in $<25\,\text{ms}$, allowing only `bsp_power_off()` to de-assert `GPIO 17 = 0` on intentional shutdown.

## [1.3.0] - 2026-10-09

### 🚀 Added

* **Class-E Environmental Hygrometer Architecture** ([bsp_sensors.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [bsp_sensors.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_sensors.c)):

  * Redesigned the environmental sensing subsystem into an ultra-low-power **Class-E Hygrometer** with strict zero runtime I2C polling during active UI and Turbo execution.

  * Implemented 1-cycle integer raw ADC differential gating (`SHTC3_RAW_IS_SETTLED`: 562 LSB counts / $1.50^\circ\text{C}$ margin) executing in $<10\,\text{ms}$ on 60s hot-wakes.

  * Added 64-bit clean window bitmask (`window_clean_mask`) tracking cold, unperturbed sample slots across the ring buffer.

  * Added complete Kelvin outputs (`ambient_temp_k`, `dew_point_k`) alongside Celsius and Fahrenheit for cloud telemetry.

  * Exposed universal temperature conversion macros: `C_TO_F`, `F_TO_C`, `C_TO_K`, `K_TO_C`, `K_TO_F`.

* **4-Byte Packed Sample Ring Buffer** ([bsp_env_telemetry.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_env_telemetry.h)):

  * Optimized sample storage into 4-byte packed struct (`bsp_env_compact_sample_t` with `raw_temp_u16` and `raw_rh_u16`).

  * Reduced total 64-sample telemetry struct footprint in RTC Slow Memory to 288 bytes (saving 480 bytes vs legacy 12-byte struct).

* **Consolidated Psychrometrics & Sliding Window Math Engine** ([bsp_equ_math.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_equ_math.h), [bsp_equ_math.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_equ_math.c)):

  * Added `bsp_math_calc_sliding_window_metrics()` calculating average temperature ($T_{\text{avg}}$), baseline floor ($T_{\text{floor}}$), ceiling ($T_{\text{ceiling}}$), $\text{RH}_{\min}$, $\text{RH}_{\max}$, and clean settled sample rate ($0\dots 60\,\text{smp/h}$) across clean slots.

  * Dual EWMA smoothing ($\alpha = 0.35$) for high-stability display and cloud reporting.

* **Non-Blocking PXE Button Engine & ROM Bootloader Jump** ([main.c](https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c), [bsp_power.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_power.h)):

  * `app_on_pxe()` only clocks GPIO levels if pins are actively held LOW, eliminating cold-boot latency ($0\,\text{ms}$ overhead on released buttons).

  * BOOT0 (`GPIO 0`) held $\ge 1.2\,\text{s}$ cleanly forces reboot into silicon ROM Download Bootloader (`bsp_system_reboot_to_bootloader()`).

  * BOOT0 short press ($< 400\,\text{ms}$) immediately toggles active dashboard screens ($1/2 \leftrightarrow 2/2$).

  * POWER (`GPIO 18`) held $\ge 1.2\,\text{s}$ initiates graceful shutdown (`bsp_power_off()`).

### 🛠️ Fixed & Refactored

* **Automated LVGL Display Refresh Gating** ([bsp_lvgl.cpp](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_lvgl.cpp)):

  * Automatic full OTP vs. differential partial refresh arbitration in `lvgl_display_flush_cb()` based on `s_first_boot_flush` and `bsp_display_get_partial_count() >= PARTIAL_REFRESH_LIMIT` (30).

* **Nomenclature & API Modernization**:

  * Completely excised legacy 'tri-node' and 'windex' terminology from headers, sources, and UI demos in favor of the clean Class-E unified sensor API (`bsp_sensors_read()`, `bsp_sensors_sample_raw()`) and clean window gating (`window_clean_mask`, `is_clean_window`, `"Gate: PASS (Window: CLEAN)"`).

  * Screen 2 dashboard updated to display live Clean Window status, clean sample count, and settled rate per hour.

## [1.2.2] - 2026-10-08

### 🚀 Added

* **Multi-Rail Bootloader Latch System** ([bsp_boot_hook.c](https://www.google.com/search?q=components/esp32-s3_bsp/bootloader_components/bsp_boot_hook/bsp_boot_hook.c)):

  * Extended 2nd-stage bootloader hook (`bootloader_before_init()`) to assert and latch all primary board power gates in $< 25\,\text{ms}$ of initial power-up:

    * `BSP_PIN_POWER_HOLD` (`GPIO 17`): Driven HIGH (`1`) with RTC pad latch.

    * `BSP_PIN_EPD_3V3_EN` (`GPIO 6`): Driven LOW (`0` = 3.3V ON) with pad latch.

    * `BSP_PIN_PA_EN` (`GPIO 42`): Driven LOW (`0` = Audio Domain ON) with pad latch to prevent I2C clamping on codec reset.

* **SHTC3 Turbo Mode Interlock & Strict Thermal Lockout Gatekeeper** ([bsp_sensors.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_sensors.c), [bsp_power.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_power.c), [bsp_power.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_power.h)):

  * Added `bsp_pm_is_turbo_active()` to query CPU 240 MHz scaling lock status.

  * Implemented strict hardware interlock in `shtc3_execute_raw_acquisition()`, `bsp_sensors_read_tri_node()`, and `bsp_shtc3_read_lp()` that **blocks all physical SHTC3 I2C polling while the CPU is in Turbo mode** (`ESP_ERR_INVALID_STATE` or cached fallback).

  * Enforced strict thermal gating against ungated live sampling: during active wake / thermal lockout (`bsp_sensors_is_in_thermal_lockout()`), live I2C acquisition is intercepted and transparently serves the pristine unperturbed cold reading from RTC memory.

* **SHTC3 Decoupled Hot-Wake Sampling & Buffered Psychrometrics** ([bsp_sensors.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_sensors.c), [bsp_sensors.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * Added `bsp_sensors_hot_wake_sample()` for headless 60s hot-wake sprints: performs fast raw SHTC3 I2C acquisition, CRC-8 verification, and commits raw readings to RTC Slow Memory in $<12\,\text{ms}$ without CPU-intensive floating-point psychrometrics.

  * Deferred all psychrometric derivations (Dew Point, Absolute Humidity, Ambient Reconstructed RH, Thermal Delta, and Confidence Score) to full UI wake inside `bsp_sensors_read_tri_node()`, consuming the buffered sample and cross-referencing TSENS die and on-glass temperatures.

* **Dual-Page Interactive Dashboard** ([main.c](https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c)):

  * Implemented multi-screen UI with instant toggling via **BOOT0 button click** and state persistence across deep sleep wakes in RTC Slow RAM (`s_app_state.active_page`):

    * **Screen 1 (1/2)**: `HUMIDYNE LABS 1/2` header, primary ambient temperature (°F / °C) and humidity (%RH), psychrometric calculations (Dew Point, Absolute Humidity), and full multi-node temperatures in both Celsius and Fahrenheit (`Glass: 25.1°C Die: 23.8°C`, `Glass: 77.2°F Die: 74.8°F`).

    * **Screen 2 (2/2)**: `HUMIDYNE LABS 2/2` header, primary calibrated battery voltage & SoC percentage, discharge rate (`mV/h`), calculated sleep average current draw (`uA`), and acquisition sample rates (`smp/h`).

* **PXE BOOT0 Long-Press ROM Download Bootloader Jump** ([bsp_power.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_power.h), [bsp_power.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_power.c), [main.c](https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c)):

  * Added `bsp_system_reboot_to_bootloader()` which sets the hardware `RTC_CNTL_FORCE_DOWNLOAD_BOOT` register flag (`RTC_CNTL_OPTION1_REG`) and restarts, forcing the silicon ROM bootloader directly into **USB/UART Download Bootloader Mode** when BOOT0 is held for $\ge 1.5\,\text{s}$ upon waking or booting.

* **Manual Rail Control & Override APIs** ([bsp_power.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp_power.h), [bsp_power.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_power.c)):

  * Added user-level functions `bsp_power_set_latch(bool)`, `bsp_power_set_epd_rail(bool)`, and `bsp_power_set_pa_rail(bool)` for programmatic assertion/deassertion of power rails with automatic digital and RTC pad hold management.

### 🛠️ Fixed & Refactored

* **Active-LOW Display Power Gate Inversion** ([bsp_display.cpp](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_display.cpp)):

  * Fixed logic inverted bug in `display_power_enable(bool enable)` where `enable == true` was driving `1` (shutting OFF power to the SSD1681 and SHTC3) and returning `true` only when the rail was disabled. Corrected to drive `0` (ON) and verify level is `0`.

* **Synchronous LVGL Render Enforcement** ([main.c](https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c)):

  * Uncommented `lv_refr_now(NULL)` in `render_environmental_ui()` and `render_shutdown_ui()` to ensure LVGL renders widgets to the SSD1681 framebuffer immediately before deep sleep entry.

* **Persistent RTC GPIO 17 Hold in Early IO** ([bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * Reinforced `bsp_io_early_init()` to explicitly drive `GPIO 17` HIGH, disable sleep isolation (`gpio_sleep_sel_dis`), and lock with `rtc_gpio_hold_en()` during application runtime.

## [1.2.1] - 2026-10-08

### 🚀 Added

* **Zero-Management Bootloader Power Latch Hook** ([bsp_boot_hook.c](https://www.google.com/search?q=components/esp32-s3_bsp/bootloader_components/bsp_boot_hook/bsp_boot_hook.c), [CMakeLists.txt](https://www.google.com/search?q=components/esp32-s3_bsp/CMakeLists.txt)):

  * Built-in 2nd-stage bootloader hook (`bootloader_before_init()`) asserting `GPIO 17` (`BSP_PIN_POWER_HOLD`) HIGH and engaging the hardware RTC pad hold latch (`gpio_ll_hold_en`) within $\approx 25\,\text{ms}$ of power-on.

  * Automatically registered into the ESP-IDF bootloader build system via `BOOTLOADER_EXTRA_COMPONENT_DIRS`, eliminating application-level bootloader configuration and preventing battery LDO brownouts.

* **Modular Hot-Wake Build-Up & Clean-Up Lifecycle** ([bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * Implemented `bsp_hot_wake_sprint_init()` and `bsp_hot_wake_sprint_deinit()` to cleanly isolate hot-wake peripheral resources (I2C + SHTC3 + promotion ISRs) and restore hardware to a pristine POR state before sleep entry or promotion to full UI wake.

* **Pre-Execution (PXE) Lifecycle Hook** ([bsp.h](https://www.google.com/search?q=components/esp32-s3_bsp/include/bsp/bsp.h), [bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * Added `.on_pxe(btn_mask, user_data)` callback and `bsp_button_mask_t` (`BSP_BUTTON_MASK_NONE`, `BSP_BUTTON_MASK_BOOT`, `BSP_BUTTON_MASK_POWER`, `BSP_BUTTON_MASK_BOTH`) for instant boot-time tactile button state detection before subsystem initialization.

### 🛠️ Fixed & Refactored

* **Automatic Shutdown Callback Registration** ([bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c), [bsp_power.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_power.c)):

  * Fixed bug where `lifecycle.on_shutdown` was never wired to `bsp_power_register_shutdown_cb()`. `bsp_power_off()` now executes the application's shutdown hook, rendering the persistent shutdown splash screen on the EPD glass before releasing the power latch.

* **Two-Phase IO Bring-Up Decoupling** ([bsp_common.c](https://www.google.com/search?q=components/esp32-s3_bsp/src/bsp_common.c)):

  * Separated Phase 1 Early Base IO (`bsp_io_early_init()`) for button pull-up configuration from Phase 2 Master IO (`bsp_init_io()`) for peripheral rails, removing redundant runtime manipulation of the latched power hold pin.

## [1.2.0] - 2026-10-07

### 🚀 Added

* **Tri-Node Thermal Sensing Architecture** (bsp_sensors.c, bsp_sensors.h):

  * Integrated three physical sensing nodes: Node 1 (PCB-mounted SHTC3), Node 2 (SSD1681 on-glass thermal sensor), and Node 3 (ESP32-S3 internal TSENS silicon die).

  * Multi-node thermal sanity cross-checking and dynamic thermal confidence scoring ($0\dots 100\%$).

* **Thermodynamic Psychrometric Invariant Engine** (bsp_equ_math.c, bsp_equ_math.h):

  * Standalone mathematical processing module based on vapor pressure conservation ($\gamma(T, RH)$, Magnus-Tetens dew point calculation, and ambient RH reconstruction).

  * Absolute humidity calculations ($g/m^3$) and Exponentially Weighted Moving Average (EWMA $\alpha = 0.25$) filtering.

* **Dynamic Frequency Scaling (DFS) & Turbo PM Locks** (bsp_power.c, bsp_power.h):

  * Established 80 MHz quiet baseline CPU operating frequency (`CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_80=y`, `CONFIG_PM_ENABLE=y`) dropping active current from \~80 mA down to \~28 mA.

  * Implemented `bsp_pm_turbo_acquire()` and `bsp_pm_turbo_release()` using `ESP_PM_CPU_FREQ_MAX` PM locks to burst Xtensa to 240 MHz exclusively during compute-heavy LVGL rendering and E-Paper SPI transfers.

* **Pure Hardware Countdown Timer & Bounded Sleep Engine** (bsp_power.c, bsp_power.h, bsp_rtc.c):

  * Replaced calendar time-of-day alarm matching with the dedicated **PCF85063A Hardware Countdown Timer** (`bsp_rtc_set_countdown_timer()`), operating purely on the 32.768 kHz quartz crystal with zero dependency on calendar time, POSIX clock state, or 24-hour rollover math.

  * Defined and enforced global BSP hardware sleep duration bounds: **120 seconds** (`BSP_SLEEP_MIN_DURATION_SEC = 120` / 2 min) up to **4 hours** (`BSP_SLEEP_MAX_DURATION_SEC = 14400` / 240 min) via 1/60Hz prescaling.

  * Automatically clamps out-of-bounds user sleep requests within `[120s, 14400s]` with informative log warnings.

* **Display Driver NULL SPI Handle Safety Guard** (bsp_display.cpp):

  * Added strict `if (s_spi_handle == NULL) return;` guard to `bsp_display_deep_sleep()`, preventing kernel panics and crash-reboot loops when returning to deep sleep during minimal headless hot-wake sprints (`BSP_INIT_MODE_MINIMAL`).

* **Internalized 60s Hot-Wake Sprint Engine & Hardware GPIO ISR Promotion** (bsp_common.c, bsp_sensors.h, https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c):

  * Fully internalized the 60-second headless hot-wake sensor sprint inside `bsp_app_start()`, autonomously capturing NIST SHTC3/Tri-Node samples into RTC Slow Memory without invoking application-level wake hooks or activating the EPD display.

  * Implemented the **Hardware GPIO ISR Promotion Engine**: arms negative-edge ISR handlers on `RTC_INT` (`GPIO 5`), `BOOT` (`GPIO 0`), and `POWER` (`GPIO 18`) throughout the active SHTC3 I2C transaction. After clean sprint deinit and sensor sleep, checks the atomic promotion flag to immediately promote any concurrent alarm or button event to `BSP_INIT_MODE_FAST` for guaranteed **zero lost wakeups**.

  * Documented SHTC3 PCB ground plane self-heating physics ($+1.5^\circ\text{C}\dots +3.0^\circ\text{C}$) directly in `bsp_sensors.h` developer guidance.

* **Dual-Wake & Two-Branch Firmware Architecture** (bsp_power.c, bsp_common.c, bsp_rtc_mem.h, https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c):

  * Implemented simultaneous dual deep-sleep wake triggers: Internal 60s RTC timer (`ESP_SLEEP_WAKEUP_TIMER`) reserved exclusively for hot-wake sprints + External PCF85063A RTC Alarm (`ESP_SLEEP_WAKEUP_EXT1`) reserved for user application scheduling.

  * Added `BSP_INIT_MODE_MINIMAL` to bypass SPI display and FreeRTOS LVGL tasks during headless 60s sensor sprints.

* **Sub-15ms Firmware "Sleep-Sprint" Engine** (bsp_power.c, https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c):

  * Enabled deep sleep fast wake stub (`esp_set_deep_sleep_wake_stub_default_entry()` / `esp_deep_sleep_disable_rom_logging()`) for ultra-rapid resume.

  * SHTC3 fast-mode acquisition (`0x44DE`) delivering sub-15ms raw sensor reads with total energy $< 1.5\text{ mJ}$ ($< 0.005^\circ\text{C}$ ground plane rise), eliminating PCB thermal soak.

* **SSD1681 Hardware On-Glass Temperature Readout** (bsp_display.cpp):

  * Half-duplex 4-wire SPI read driver implementing SSD1681 command `0x1B` via dedicated `s_spi_read_handle`.

* **Unified Environmental Monitor Demo** (examples/Unified_Environmental_Demo/):

  * Dedicated demonstration application featuring pure physical telemetry: directly measured $V_{\text{bat}}$ (V / %), active CPU wake execution latency (ms), exact PCF85063A POSIX uptime, sample cycle counter, and tri-node environmental metrics.

  * Built-in `CONFIG_ENABLE_DEV_CONTINUOUS_MODE` switch to bypass deep sleep with FreeRTOS delays for uninterrupted serial logging during development.

  * Automatic critical battery shutdown guard ($\le 10\%$ SoC / $< 3400\text{ mV}$).

### 🛠️ Changed & Refactored

* **Persistent Environmental Telemetry Modernization** (bsp_env_telemetry.h, bsp_sensors.c, bsp_sensors.h):

  * Replaced obsolete `bsp_ulp_shared.h` with `bsp_env_telemetry.h`, modernizing the persistent 64-entry RTC Slow Memory sample ring buffer (`bsp_env_telemetry_history_t`, `bsp_env_raw_sample_t`).

  * Standardized public telemetry APIs to `bsp_sensors_get_telemetry_history()` and `bsp_sensors_get_sample_count()`.

* **EPD UI Gated Sample Counter** (https://www.google.com/search?q=examples/Unified_Environmental_Demo/main/main.c):

  * Replaced the transient `Sprint: %lums` badge on Row 1 ($y=140$) with a verified **Thermal-Gated Sample Counter** (`SMP: %lu`) reflecting verified environmental acquisitions logged in the RTC ring buffer.

* **EPD Partial Refresh Overhaul & Differential Erase Fix** (bsp_display.cpp, bsp_lvgl.cpp):

  * Aligned SSD1681 partial update command sequence to use `0x22 0xCF` (Pattern Display Mode 2) and Ping-Pong differential scanning (`0x37 = 0x40`, `0x3C = 0x80`, `WF_PARTIAL_1IN54`), writing to `0x24` (New RAM) only.

  * Eliminated the cumulative "typewriter newspaper" text overlay bug by ensuring the hardware differential comparator drives previous black pixels cleanly back to white (`LUT1` $0 \to 1$).

  * Restricted OTP master activation (`0x22 0xB1` + `0x20`) strictly to cold boot; suppressed `0x20` on wake boot to eliminate whole-screen flashing.

* **Power Management & Shutdown State Cleanliness** (bsp_power.c, bsp_button.c):

  * Refactored `bsp_power_off()` to de-assert latch `GPIO 17 = 0`, release all GPIO holds, clear PCF85063A countdown timers and alarms, wipe RTC Slow Memory state via `bsp_rtc_mem_reset()`, and ensure next power-up starts fresh in cold boot.

  * Fixed power button long-press detection and initial boot wait-for-release state (`STATE_BOOT_WAIT_RELEASE`).

* **Audio Subsystem Zero-Heat Standby** (bsp_audio.c):

  * Configured zero-heat software power-down sequence for ES8311 codec and NS4150B amplifier ($\le 1\,\mu\text{A}$ quiescent draw) while maintaining active 3.3V rail on GPIO 42 (`PA_EN = 0`) to prevent clamping on shared I2C lines.

* **RTC Memory Re-Partitioning** (bsp_rtc_mem.c):

  * Relocated 5,000-byte E-Paper frame buffer to RTC Fast Memory (`RTC_FAST_ATTR`), freeing 61% (5 KB) of RTC Slow SRAM for clean sensor ring buffers.

### 🗑️ Removed & Deprecated

* **Purged Obsolete ULP MUX Arbitration Routines** (bsp_sensors.h, bsp_sensors.c):

  * Deleted `bsp_ulp_mux_set_app_active()`, `bsp_ulp_mux_set_bus_locked()`, `bsp_ulp_mux_is_app_active()`, and `bsp_ulp_mux_set_substrate_hot()`.

* **Decommissioned ULP RISC-V Coprocessor Subsystem**:

  * Permanently removed the ULP toolchain embedding and coprocessor loader due to physical hardware routing constraint (Waveshare SHTC3 bus is hardwired to digital `GPIO 47/48`, outside the ESP32-S3 `RTCIO 0..21` power domain). Replaced with zero-heat 80 MHz DFS Fast-Boot Sleep-Sprint engine.

* **Removed Synthetic Calibration**: Purged obsolete synthetic thermal divider heuristic (`bsp_sensor_cal.c` / `bsp_sensor_cal.h`) in favor of physics-based psychrometric invariant engine.

* **Removed Speculative Math**: Eliminated assumed 280 µA current consumption modeling and estimated battery runtime days from UI in favor of directly measurable physical telemetry.

## [1.1.0] - 2026-10-02

### 🚀 Added

* **Structured Application Lifecycle Engine** (bsp_common.c):

  * Added `bsp_app_start()` with structured callbacks (`on_cold_boot`, `on_wake`, `on_before_sleep`, `on_shutdown`).

* **Hardware Profile Init Engine**:

  * Modular init modes: `BSP_INIT_MODE_FULL`, `BSP_INIT_MODE_FAST`, `BSP_INIT_MODE_SENSORS_ONLY`, `BSP_INIT_MODE_OFFLINE`.

* **Audio Tone Synthesis & Chime System** (bsp_audio.c):

  * 256-point sine table with attack/decay envelope smoothing.

* **Fast Wi-Fi Reconnect & BLE Provisioning** (bsp_wifi.c, bsp_prov.c):

  * RTC Slow Memory state caching for sub-400ms Wi-Fi reconnection.

  * BLE GATT provisioning compatible with Chrome Web Bluetooth.

* **ThingsBoard MQTT & HTTPS OTA** (bsp_tb.c, bsp_ota.c):

  * Telemetry publishing, 6-8 character claiming key workflow, and remote firmware OTA state machine.

## [1.0.0] - 2026-09-25

### 🚀 Added

* Initial baseline BSP release for Waveshare ESP32-S3-Touch-ePaper-1.54 V2 (`ESP32-S3-PICO-1-N8R8`).

* Basic drivers for SSD1681 e-Paper, SHTC3 sensor, PCF85063A RTC, ES8311 Audio Codec, FT6336 Capacitive Touch, SD Card SPI, and NVS Storage.