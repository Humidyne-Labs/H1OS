# H1OS Turnkey Application Boilerplate

Minimal starter template for building custom applications atop the **H1OS Class-E Environmental Telemetry Operating System** on the Waveshare ESP32-S3 ePaper 1.54" V2.

> [!NOTE]
> *H1OS is an independent open-source embedded software framework by Humidyne Labs and is not affiliated with or endorsed by Waveshare Electronics.*

## Features
- **Declarative Lifecycle Engine:** Single-entry `h1os_start()` lifecycle with `on_boot`, `on_wake`, `on_sync`, `on_pre_sleep`, and `on_error` hooks.
- **Cross-Core UI Mutation Actor Queue:** Thread-safe `h1os_ui_post()` non-blocking actor pattern from Core 0 to Core 1.
- **200x200 Bilevel LVGL v9 UI:** Pure 1-bit monochrome display pipeline with custom typography (`H1OS_FONT_14` & `H1OS_FONT_20`).
- **Zero RF & Ultra-Low-Power Ready:** Radio-stripped footprint (`CONFIG_BT_ENABLED=n`, `CONFIG_ESP_WIFI_ENABLED=n`), ULP Pure Event Mode coprocessor wake stub, and power domain pad isolation.
- **Isolated Build Presets:** Fully segregated `dev` (`build_dev`) and `prod` (`build_prod`) configurations with zero sdkconfig collisions.

## Building and Flashing

From the `examples/boilerplate` directory:

### 1. Development Profile (Debug Symbols & Diagnostics)
```powershell
idf.py -B build_dev --preset dev build
idf.py -B build_dev --preset dev flash monitor
```

### 2. Production Profile (Size-Optimized Release)
```powershell
idf.py -B build_prod --preset prod build
idf.py -B build_prod --preset prod flash monitor
```

### 3. Developer Menu & Tooling Console
```powershell
idf.py h1os_menu
```
Or use the Flash Partition Manager:
```powershell
idf.py h1os_part --map
idf.py h1os_part --live-usage
```
