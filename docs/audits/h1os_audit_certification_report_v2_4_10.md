# H1OS Audit Certification Report: 2026-11-19-v2.4.10-dev-release-audit

* **Audit Standard:** `H1OS-STD-001 (Rev 2.1)`
* **Target Version / IDF:** `v2.4.10-dev` (`H1OS_VERSION_CODE = 0x0002040A`) | ESP-IDF `v6.1.1`
* **Target Commit / Range:** `92ab5ac..E-Class-Dev-003_audit` (`f216eba` + `v2.4.10-dev` working tree pre-merge)
* **Audited Modules:** `components/h1os/src/`, `components/h1os/include/`, `components/h1os/tools/`, `examples/H1OS/main/`, `examples/boilerplate/main/`, `examples/riscv_test/`, `tools/agent/`, `docs/architecture/`, `docs/api.md`
* **Auditor:** Autonomous Firmware Engineering Audit (`H1OS-STD-001 Rev 2.1`)
* **Final Disposition:** **PASS WITH WAIVERS** (`0` open `S0`/`S1`/`S2` defects; documented benign static-analyzer waivers in §4)

---

## 1. Automated Gate Telemetry (Steps 2 & 4)

* **Build `examples/H1OS` (`dev` & `prod`):** **PASS** — `idf.py -B build_dev --preset dev build` exited `0` (`h1os.bin`: `0xd35b0` bytes, `72%` free; `0` project warnings/errors, `0` `LWIP_*RECVMBOX_SIZE` notices); `idf.py -B build_prod --preset prod build` exited `0` (`h1os.bin`: `0xb5550` bytes, `76%` free; `0` project warnings/errors, `0` `LWIP_*RECVMBOX_SIZE` notices).
* **Additional Examples (`boilerplate`, `riscv_test`):** **PASS** — `examples/boilerplate` (`idf.py -B build_prod --preset prod build`) exited `0` (`h1os_boilerplate.bin`: `0x9d9c0` bytes, `79%` free; `0` project warnings/errors); `examples/riscv_test` (`idf.py build`) exited `0` (`riscv_test.bin`: `0x2c8e0` bytes, `83%` free; `0` project warnings/errors).
* **Semgrep Multi-Language Scan:** **PASS WITH WAIVERS** — Scanned `65` tracked files (`360` rules via `p/c`, `p/security-audit`, `p/secrets`, `p/0xdea`, `p/trailofbits`, `p/python`), exited `0` with `107` raw findings (`94` informational `raptor-typos` / `raptor-interesting-api-calls` noise, `13` filtered findings, `0` secrets, `0` Python findings). Separate `--no-git-ignore` scan of new `tools/agent/bump_version.py` (`277` rules): `0` findings. Previous `h1os_lvgl.cpp` signed/unsigned findings cleared; remaining `13` findings verified benign / accepted in §4.
* **Clang-Tidy AST Sweep (Read-Only):** **PASS WITH WAIVERS** — Executed `clang-tidy.exe` (`esp-21.1.3_20260408`) against sanitized `compile_commands.json` (`--checks="-*,bugprone-*,clang-analyzer-*,misc-unused-*,cert-*"`, `0` compile/header errors):
  * `examples/H1OS/main/` (`8` files) + `components/h1os/src/` (`18` files): `26` files analyzed, exit `0`, `84` raw findings (`47` style/MMIO noise: `18` `DeprecatedOrUnsafeBufferHandling`, `15` `bugprone-easily-swappable-parameters`, `14` `FixedAddressDereference`; `37` non-noise findings all inside `components/h1os/src/`, `0` findings in `examples/H1OS/main/`). Prior `screen_diagnostics.c:99` DeadStores finding cleared.
  * `examples/boilerplate/main/main.c`: `1` file analyzed, exit `0`, `0` warnings, `0` errors.
* **`H1OS-STD-001` Step 2.1 Regex Sweeps:** **PASS** — `0` dynamic heap calls (`malloc`/`calloc`/`realloc`/`free`/`strdup`/`heap_caps_malloc`) across `components/h1os/` and all 3 examples; `0` invalid `REG_(GET|SET)_BIT(..., _S|_V)` macro mismatches; `1` `portMAX_DELAY` in `components/h1os/src/sub_audio.c:1017` (event-driven `xQueueReceive(s_audio_queue, ...)` exited cleanly via `AUDIO_CMD_STOP`).
* **EPD 1-BPP Typography Audit (`epd-font` v1.0.23):** **PASS** — `string_info.py --audit-screens`:
  * `examples/H1OS/main/screens`: `62/62` lines across `6` files PASS `<= 188 px` (`0` overflows).
  * `examples/boilerplate/main`: `14/14` lines across `1` file PASS `<= 188 px` (`0` overflows).
* **`murdock_memory_budget` (`build_dev` / `build_prod`):** **PASS**
  * `examples/H1OS/build_dev/h1os.elf`: DIRAM `28.2%` (`34,031 B` DRAM used, `245,522 B` DIRAM free <= `85%`), RTC Fast `3,936 B` used (`4,256 B` free), RTC Slow `713 B` used (`3,383 B` free <= `4,096 B`), Flash headroom `75.68%` (`2,380,550 B` free >= `70%`).
  * `examples/H1OS/build_prod/h1os.elf`: DIRAM `23.2%` (`27,084 B` DRAM used, `262,481 B` DIRAM free <= `85%`), RTC Fast `4,120 B` used (`4,072 B` free), RTC Slow `713 B` used (`3,383 B` free <= `4,096 B`), Flash headroom `79.07%` (`2,487,348 B` free >= `70%`).
* **Version Sync (`bump_version.py --check --idf-version 6.1.1`):** **PASS** — `72` version anchors across `38` files (including `h1os_version.h`, `idf_component.yml`, `Doxyfile`, `CHANGELOG.md`, `docs/guide.md`, and all `17` `docs/architecture/*.md` headers) synchronized to `2.4.10-dev` / ESP-IDF `v6.1.1`.
* **Sanitize Check (`sanitize.py --check`):** **PASS** — `664` text/docs files + `2` archives scanned, `0` identity leaks, `0` PDF metadata leaks, `0` git history leaks.

---

## 2. 8-Domain Compliance Matrix (Step 3)

| Domain | Applicable | Pitfalls Evaluated | Evidence & File:Line References | Verdict |
| :--- | :---: | :--- | :--- | :---: |
| **D1: Concurrency & FreeRTOS** | Yes | `PIT-01-A..E` | `examples/H1OS/main/main.c:44,266`: converted static `telem` in `update_active_display()` to stack-local and guarded `h1os_lvgl_lock(1000)` in `app_on_splash()`. `sub_audio.c:1017` `xQueueReceive` `portMAX_DELAY` terminates on `AUDIO_CMD_STOP`. | **PASS** |
| **D2: Sleep, Wake & Power** | Yes | `PIT-02-A..D` | Verified `examples/H1OS/sdkconfig.defaults:29-30` & `profiles/sdkconfig.defaults:29-30` LwIP mbox range (`6`) avoids runtime Kconfig clamping; zero regressions to `orch_flow.c` / `sub_power.c` pad-hold or sleep entry paths. | **PASS** |
| **D3: Coprocessor & CDC** | Yes | `PIT-03-A..D` | Verified `examples/riscv_test` builds cleanly (`0` warnings/errors, `0x2c8e0` B) under ESP-IDF `v6.1.1`; `0` `REG_(GET|SET)_BIT(..., _S|_V)` violations across `components/h1os/`. | **PASS** |
| **D4: Bus Topologies** | Yes | `PIT-04-A..D` | `0` runtime heap allocations across `components/h1os/` and all examples; `hal_i2c.c:180,221,265` bounded timeouts (`< 1000 ms`) verified against ESP-IDF `i2c_master_transmit` signature. | **PASS** |
| **D5: Memory & Persistence** | Yes | `PIT-05-A..D` | `components/h1os/src/hal_flash.c:89`: enforced unsigned sector alignment `(len + 4095U) & ~(size_t)4095U` + partition clamp. `murdock_memory_budget` RTC Slow `713 B` (`s_persisted_state = 648 B`). | **PASS** |
| **D6: Metrology & Precision** | Yes | `PIT-06-A..D` | `components/h1os/src/sub_display.cpp:436`: verified `int16_t` glass temperature calculation over `int8_t` sensor range (`[-12850, 12750]`) cannot overflow `int16_t`; `-Wdouble-promotion` active with `0` compiler warnings. | **PASS** |
| **D7: Display Pipeline** | Yes | `PIT-07-A..C` | `components/h1os/src/h1os_lvgl.cpp:63`: `LVGL_I1_PALETTE_SIZE 8U`; `examples/H1OS/main/screens/screen_base.c:83-118`: refactored `screen_base_set_awake_badge()` to enqueue via `h1os_ui_post(apply_awake_badge_lvgl, ...)` with pre-task direct-lock path (`500 ms`); `examples/boilerplate/main/main.c:80-115`: converted proportional multi-space rows to dual left/right labels (`0` overflows across `62` H1OS + `14` boilerplate strings). | **PASS** |
| **D8: Driver State & Errors** | Yes | `PIT-08-A..C` | Added `telem == NULL` and `!h1os_lvgl_lock(100)` guards in `screen_env_dash.c`, `screen_psychrometrics.c`, `screen_thermal_nodes.c`, `screen_system_health.c`, `screen_diagnostics.c`, and `examples/boilerplate/main/main.c:37`; cleared `screen_system_health.c` placeholder date (`"--/--/--"`) and `screen_diagnostics.c` DeadStores warning. | **PASS** |

---

## 3. Empirical Grounding & Metrology Audit (Invariants 1 & 2)

* **Physical Claims / Timings Added:** None introduced in `v2.4.10-dev`. Existing datasheet/bench figures in `docs/architecture/` and `AGENTS.md` preserved with standardized specification headers (`v2.4.10-dev` / ESP-IDF `v6.1.1`).
* **Numerical Range Proof:** Verified `components/h1os/src/hal_flash.c:89` sector rounding operates on unsigned `size_t` operands bounded to `s_part->size`, and `examples/boilerplate` / `examples/H1OS` UI label metrics strictly bounded within `188 px` via `epd-font v1.0.23` `string_info.py`.

---

## 4. Defect Log, Remediations & Active Waivers

### Remediated Defects (`v2.4.10-dev`)
* **`DEF-2410-01` | `PIT-07-B` | Class S1:** `examples/H1OS/main/screens/screen_base.c` updated `s_active_badge` polarity by directly taking `h1os_lvgl_lock(100)` instead of posting to the Core 1 actor queue. Refactored to `h1os_ui_post(apply_awake_badge_lvgl, ...)` with bounded `500 ms` lock path if `h1os_ui_post` returns `ESP_ERR_INVALID_STATE` before task startup.
* **`DEF-2410-02` | `PIT-08-B` | Class S2:** `screen_{env_dash,psychrometrics,thermal_nodes,system_health,diagnostics}.c`, `examples/H1OS/main/main.c` (`app_on_splash`), and `examples/boilerplate/main/main.c` had unchecked `h1os_lvgl_lock()` return values or missing `telem == NULL` guards. Added explicit early-return checks and converted `update_active_display()`'s `telem` from `static` to stack-local.
* **`DEF-2410-03` | `PIT-05-D` / Semgrep | Class S2:** `components/h1os/src/hal_flash.c:89` (`4095`) and `components/h1os/src/h1os_lvgl.cpp:63` (`8`) mixed signed literals with `size_t` / unsigned arithmetic. Updated to `4095U`, `~(size_t)4095U`, and `8U`.
* **`DEF-2410-04` | Kconfig / Tooling / Typography | Class S2:** Updated `CONFIG_LWIP_{TCP,UDP}_RECVMBOX_SIZE` from out-of-range `4` to `6` (`[6, 64]` in IDF `v6.1.1`); replaced non-compliant Stack section heading comment in `sdkconfig.defaults.{dev,ci}` with `Stack Guard`; converted 3 multi-space proportional rows in `examples/boilerplate/main/main.c` to dual left/right labels; fixed `bump_version.py` quote padding at column 43 and `optimize_images.py` `--dry-run` unlink guard; harmonized `Evaluation_1.54_EPD_2Bit_Grayscale.pdf` and `EMC.jpg`/`ROHS.jpg` EXIF metadata via `/shrink`.

### Active Documented Waivers (Class S3 / Benign Tool Diagnostics)
* **`WAIV-2410-01` | Semgrep `0xdea` (`13` filtered findings):**
  * `components/h1os/src/h1os_time.c:235-236` (`raptor-format-string-bugs`, `raptor-insecure-api-scanf`): bounded `%3s` + `SCNd32` parsing of compile-time `__DATE__` / `__TIME__` constants.
  * `components/h1os/src/hal_flash.c:89` & `sub_audio.c:790,839` (`raptor-signed-unsigned-conversion`): verified unsigned sector mask (`size_t` / `4095U`) in `hal_flash.c` and static bounded DMA sample conversion/size clamping (`sub_audio.c` audio synthesizer / I2S write).
  * `examples/riscv_test/main/main.c:176,180,212,215,226,227,231` (`raptor-high-entropy-assignment`, `raptor-memory-address-exposure`): ULP-RISC-V bench diagnostic constants and console `printf` register/pointer dumps in standalone test app.
* **`WAIV-2410-02` | Clang-Tidy (`37` non-noise findings in `components/h1os/src/`):**
  * `25` `clang-analyzer-deadcode.DeadStores`: variables formatted solely for `ESP_LOGI`/`ESP_LOGD` (`h1os_lifecycle.c`, `orch_flow.c`, `sub_display.cpp`, `sub_power.c`) compiled out by `prod` preset `CONFIG_LOG_MAXIMUM_LEVEL`; retained intentionally so `dev` logging works without `#if` clutter.
  * `5` `bugprone-narrowing-conversions`: bounded `uint32_t -> int` timeouts in `hal_i2c.c:180,221,265` and `hal_io.c:405` matching ESP-IDF driver signatures, plus bounded `int16_t` glass temperature calculation in `sub_display.cpp:436`.
  * `5` CERT C (`h1os_time.c:68,159,200` `time(&now)` `cert-err33-c`; `:235-236` `sscanf(__DATE__/__TIME__)` `cert-err34-c`).
  * `1` `bugprone-infinite-loop` (`orch_wake_stub.c:72`): inline Xtensa `rsr %0, ccount` register polling loop in bare-metal RTC wake stub (`__asm__ volatile`).
  * `1` `clang-analyzer-security.PointerSub` (`sub_power.c:331`): `_ulp_bin_end - _ulp_bin_start` linker symbol span calculation for ULP binary loading.
