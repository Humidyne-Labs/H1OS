# H1OS Turnkey Application Boilerplate

Minimal starter template for building custom applications atop the **H1OS Class-E Environmental Telemetry Operating System** on the Waveshare ESP32-S3 ePaper 1.54" V2.

## Features
- **Event-Driven Lifecycle:** Connects directly into `h1os_start()` with `on_boot`, `on_wake`, `on_pre_sleep`, and `on_shutdown` callbacks.
- **200x200 Monochrome LVGL v9 UI:** Uses packed 1-bit Montserrat typography (`H1OS_FONT_14` & `H1OS_FONT_20`).
- **Zero RF & Ultra-Low-Power Ready:** Preconfigured for <15µA deep sleep, ULP coprocessor wake stub, and power domain pad isolation.

## Building and Flashing

From the `examples/boilerplate` directory:
```bash
idf.py set-target esp32s3
idf.py build
idf.py -p COMx flash monitor
```
