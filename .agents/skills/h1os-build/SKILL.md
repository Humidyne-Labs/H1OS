---
name: h1os-build
description: Authoritative build instructions, environment configuration, and execution commands for H1OS and ESP32-S3 firmware. Eliminates exploratory tool searching by providing the exact Espressif v6.1 profile script, paths, and build targets.
---

# H1OS & ESP32-S3 Firmware Build Guide (`v2.4.5-dev`)

This skill defines the canonical build procedures, paths, and environment activation for **H1OS** on ESP32-S3.

> [!IMPORTANT]
> **Strict Agent Directive: Zero Exploratory Searching**
> Do not spend turns searching for `idf.py`, python virtual environments, or export scripts. All tooling is located at the exact fixed paths specified below.

---

## 1. Environment & Path Specifications

- **Target Chip:** ESP32-S3 (`esp32s3`)
- **ESP-IDF Version:** v6.1 (`C:\esp\v6.1\esp-idf`)
- **Host Tools Root:** `C:\Espressif\tools`
- **Active Python Virtualenv:** `C:\Espressif\tools\python\v6.1\venv`
- **Canonical Profile Script:** `C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1`
- **Project Working Directory:** `examples\H1OS`

> [!WARNING]
> On Windows, running `idf.py` requires access to `C:\Espressif\tools`. In AI agent terminals, commands running ESP-IDF builds MUST set `BypassSandbox: true`.

---

## 2. Canonical One-Liner Commands

All commands must be executed in `examples\H1OS` using PowerShell:

> [!IMPORTANT]
> **CMakePresets Mandate:**
> When `CMakePresets.json` exists in the application directory (e.g. `examples/H1OS`), always use the `--preset` argument (`--preset prod` or `--preset dev`). `idf.py` automatically binds the preset's target binary directory (`build_prod` or `build_dev`) and Kconfig defaults files.

### Production Build (Default)
Compiles `bootloader.bin`, `ulp_h1os.bin`, and `h1os.bin` into `build_prod` via the `prod` preset:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod --preset prod build
```

### Development Build
Compiles with debug symbols into `build_dev` via the `dev` preset:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev --preset dev build
```

### Reconfigure / CMake Refresh & Preset Switching
Forces a clean CMake re-generation applying the exact preset configs:

> [!CRITICAL]
> **Mandatory `sdkconfig` Removal Invariant:**
> ESP-IDF's Kconfig defaults policy prioritizes an existing `examples/H1OS/sdkconfig`. When switching presets (e.g. from `dev` to `prod` or vice versa), **YOU MUST ERASE `sdkconfig` AND `sdkconfig.old` FIRST**!
> Failing to remove `sdkconfig` causes CMake to retain old settings (e.g. `-Og`, debug log levels, heap poisoning) rather than applying the target preset defaults.

```powershell
# 1. Remove project sdkconfig before reconfiguring:
Remove-Item -Force -ErrorAction SilentlyContinue sdkconfig, sdkconfig.old

# 2. Reconfigure target preset:
# Development profile (debug symbols, dev sdkconfig):
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev --preset dev reconfigure

# Production profile (size-optimized, production sdkconfig):
Remove-Item -Force -ErrorAction SilentlyContinue sdkconfig, sdkconfig.old
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod --preset prod reconfigure
```

### Firmware Memory Size Breakdown
Reports DRAM, IRAM, DIRAM, and Flash footprint:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod size
```

### Comprehensive Size Diagnostic (`h1os_size`)
Generates deep per-component, per-file, binary header breakdown and partition headroom summary without triggering Ninja builds (instant, 0% CPU):
```powershell
# Instant direct inspection via idf.py CLI extension:
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod h1os_size

# Direct script execution from application root:
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; python ../../components/h1os/tools/audit_size/h1os_size.py -B build_prod

# Optional: Force a full firmware rebuild before measuring:
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; python ../../components/h1os/tools/audit_size/h1os_size.py -B build_prod --rebuild
```

### Packaging Production Release Bundle (`h1os_pack`)
Generates the monolithic factory binary and bundles modular batch control vectors and flasher into `dist/`:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod h1os_pack
```

### Full Clean
Removes all build artifacts if switching major SDK or toolchain versions:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod fullclean
```

### Flash Firmware to Device
Flashes the bootloader, partition table, and application over USB-Serial:
```powershell
& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod flash
```

---

## 3. Directory Invariants

| Directory | Purpose |
| :--- | :--- |
| `examples\H1OS` | **Main CMake showcase project root**. All `idf.py` commands run from here. |
| `components\h1os` | **Core H1OS component library** (HAL, subsystems, orchestrator, lifecycle, ULP). |
| `examples\H1OS\build_prod` | **Production build output** (`h1os.bin`, `ulp_h1os.bin`, `bootloader.bin`). Target for `--preset prod`. |
| `examples\H1OS\build_dev` | **Development build output**. Target for `--preset dev`. |
