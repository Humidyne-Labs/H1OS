# H1OS v2.4.7 Firmware Release & Flash Operations Manual

* **Target Hardware**: Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`, 8 MB DIO SPI Flash @ 80 MHz)

* **USB Interface**: Native ESP32-S3 USB-Serial/JTAG (`VID_303A&PID_1001`, Windows inbox `usbser.sys` CDC driver)

* **Flasher Architecture**: Zero-Dependency PowerShell + Inline C# Mask ROM SLIP Engine (`flasher.ps1`) — **No Python, `esptool`, or third-party USB drivers required**

## 1. Control-Vector Hierarchy & Script Guide

The release bundle uses a modular two-tier hierarchy: **`flasher.ps1`** contains the complete Mask ROM SLIP protocol engine, partition parser, Dual-OTA manager, and NVS/SPIFFS tooling, while lightweight **`.bat` control vectors** invoke `flasher.ps1` with preset parameters.

| Script / File | Role in Hierarchy | Equivalent CLI Command | What It Touches / Preserves | 
| ----- | ----- | ----- | ----- | 
| **`flash_now.bat`** | **Master Interactive Hub** | Calls `[1]`–`[4]` `.bat` vectors or `flasher.ps1 -Interactive` | Interactive menu dispatching to turnkey batch vectors or the Advanced Partition, Dual-OTA & NVS Manager. | 
| **`flash_update_keep_nvs.bat`** | **Control Vector 1**: Standard Firmware Update | `flasher.ps1 -Profile KeepNvs` | **Writes**: `bootloader` (`0x0`), `partition-table` (`0x8000`), `otadata` (`0x1D000`), `ota_0` (`0x20000`). **Preserves**: `nvs` (`0x9000`), `ota_1` (`0x320000`), `storage` (`0x620000`), `epd_frame` (`0x7FC000`). | 
| **`flash_app_only.bat`** | **Control Vector 2**: Fast App-Only Update | `flasher.ps1 -Profile AppOnly -KeepPartitionTable -KeepNvs` | **Writes**: `ota_0` (`0x20000`) + `otadata` (`0x1D000`). **Preserves**: `bootloader`, `partition-table`, `nvs`, `ota_1`, `storage`, `epd_frame`. | 
| **`flash_factory.bat`** | **Control Vector 3**: Full Factory POR Restore | `flasher.ps1 -Profile Factory` | **Scrubs**: Entire 8 MB NOR flash (`0x000000..0x7FFFFF` -> `0xFF`). **Writes**: Clean `bootloader`, `partition-table`, `otadata`, and `ota_0`. | 
| **`flash_nvs_wipe.bat`** | **Control Vector 4**: Targeted NVS Reset | `flasher.ps1 -Profile WipeNvs` | **Scrubs**: `nvs` (`0x9000`, 80 KB) and `phy_init` (`0x1F000`, 4 KB) -> `0xFF`. **Preserves**: All app slots, bootloader, and `storage`. | 
| **`flasher.ps1`** | **Core Engine & Partition Manager** | Direct PowerShell CLI | Implements SLIP framing, USB-JTAG DTR/RTS reset, `partitions.csv` / `partition-table.bin` (`0x50AA`) parsing, Dual-OTA slot switching, and hardware `ESP_SPI_FLASH_MD5` (`0x13`) verification. | 

## 2. ESP32-S3 8MB Dual-Slot OTA Partition Map (`partitions.csv`)

Every partition offset is aligned to ESP-IDF hardware boundaries (4 KB sectors for `data`, 64 KB blocks for `app`), totaling exactly 8,388,608 bytes (`0x800000`):

| \# | Partition Name | Type | SubType | Start Offset | End Offset | Size (Hex) | Size (KB) | Description & Binary Source | 
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | 
| **1** | `bootloader` | `system` | `boot` | `0x000000` | `0x007FFF` | `0x008000` | 32.0 KB | 2nd-stage ESP-IDF Bootloader (`bins/bootloader.bin`) | 
| **2** | `partition-table` | `system` | `part` | `0x008000` | `0x008FFF` | `0x001000` | 4.0 KB | Binary Partition Table (`bins/partition-table.bin`) | 
| **3** | `nvs` | `data` | `nvs` | `0x009000` | `0x01CFFF` | `0x014000` | 80.0 KB | Non-Volatile Storage (user settings, Wi-Fi/BLE keys) | 
| **4** | `otadata` | `data` | `ota` | `0x01D000` | `0x01EFFF` | `0x002000` | 8.0 KB | Dual-sector OTA boot selector (`bins/ota_data_initial.bin`) | 
| **5** | `phy_init` | `data` | `phy` | `0x01F000` | `0x01FFFF` | `0x001000` | 4.0 KB | RF PHY calibration data | 
| **6** | `ota_0` | `app` | `ota_0` | `0x020000` | `0x31FFFF` | `0x300000` | 3,072.0 KB | Primary Application Slot 0 (`h1os.bin` / `bins/h1os.bin`) | 
| **7** | `ota_1` | `app` | `ota_1` | `0x320000` | `0x61FFFF` | `0x300000` | 3,072.0 KB | Secondary Application Slot 1 (OTA fallback / test image) | 
| **8** | `storage` | `data` | `spiffs` | `0x620000` | `0x7FBFFF` | `0x1DC000` | 1,904.0 KB | SPIFFS filesystem partition | 
| **9** | `epd_frame` | `data` | `undefined` | `0x7FC000` | `0x7FFFFF` | `0x004000` | 16.0 KB | Waveshare 1.54" V2 ePaper retained framebuffer | 

## 3. Manual CLI Operations & Hacking Cookbook

You can call `flasher.ps1` directly from PowerShell or `flash_now.bat <args>` to target specific partitions, test secondary OTA slots, or inspect live flash contents:

* **Inspect live on-chip MD5 checksums across all 9 partitions (compares against `bins/` and `0xFF` blank state)**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile Inspect`

* **Flash `h1os.bin` into secondary slot `ota_1` (`0x320000`) and switch active boot to `ota_1`**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile AppOnly -TargetSlot ota_1`

* **Clone `h1os.bin` into BOTH `ota_0` (`0x20000`) and `ota_1` (`0x320000`) for redundant failover**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile DualOta`

* **Switch active boot slot between `ota_0` and `ota_1` in `otadata` (`0x1D000`) without re-flashing the 3 MB app**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile SetBootSlot -TargetSlot ota_1`

* **Update firmware while keeping BOTH the existing on-chip Partition Table (`0x8000`) and NVS (`0x9000`) intact**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile KeepNvs -KeepPartitionTable`

* **Flash a custom SPIFFS image (`my_spiffs.bin`) or ePaper framebuffer (`splash.bin`) by partition name**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile CustomWrite -TargetPartition storage -Binary .\my_spiffs.bin`

* **Erase only the SPIFFS `storage` (`0x620000`) or `epd_frame` (`0x7FC000`) partition to `0xFF`**:
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile WipeStorage`
  `powershell -ExecutionPolicy Bypass -File .\flasher.ps1 -Profile WipeEpdFrame`