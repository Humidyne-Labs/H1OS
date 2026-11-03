# H1OS ESP32-S3 Firmware Release Package

* **Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)
* **Flash Memory:** 8 MB Dual-I/O (DIO) SPI Flash @ 80 MHz
* **PSRAM Memory:** 8 MB Octal PSRAM @ 80 MHz
* **USB Interface:** Native ESP32-S3 USB CDC (`VID_303A:PID_1001`)
* **Flasher Architecture:** Zero-Dependency Windows PowerShell + Inline C# SLIP Engine (No Python, `esptool.py`, or third-party drivers required)

---

## 1. Quick Start: Firmware Flashing

Double-click `flash.bat` in the release root directory to launch the interactive Control Deck:

```text
===============================================================================
                H1OS ESP32-S3 Firmware & Ecosystem Control Deck
          Target Hardware: Waveshare ESP32-S3 ePaper 1.54" V2 (8MB DIO)
            Zero-Dependency Native USB SLIP Engine (VID_303A:PID_1001)
===============================================================================

  --- PRIMARY FIRMWARE ACTIONS ---
  [1] Standard Update (Keep Settings & NVS) [Default - Press Enter]
  [2] Fast App-Only Update
  [3] Full Factory Restore
  [4] Reset Device Settings (Wipe NVS)

  --- ADVANCED PARTITION & HARDWARE UTILITIES ---
  [5] Advanced Console (Dual-OTA, Storage, Custom, Live MD5)
  [6] Live On-Chip Partition Map & MD5 Inspector
  [Q] Quit
```

### Action Reference

| Option | Action Name | Flash Operations | Preserved Regions |
| :--- | :--- | :--- | :--- |
| **`[1]`** | **Standard Update** *(Default)* | Writes `bootloader.bin` (`0x0`), `partition-table.bin` (`0x8000`), `ota_data_initial.bin` (`0x1D000`), and `h1os.bin` (`0x20000`). | Preserves `nvs` (Wi-Fi, calibration), `storage` (SPIFFS), and `epd_frame` (retained e-Paper buffer). |
| **`[2]`** | **Fast App-Only Update** | Writes `h1os.bin` (`0x20000`) only. Fastest routine development cycle. | Preserves bootloader, partition table, NVS, and all storage partitions. |
| **`[3]`** | **Full Factory Restore** | Scrubs the entire 8 MB flash die to `0xFF`, then writes clean factory binaries. | Performs total factory reset; wipes all persistent settings and calibrations. |
| **`[4]`** | **Reset Settings (Wipe NVS)** | Erases `nvs` (`0x9000`, 80 KB) and `phy_init` (`0x1F000`, 4 KB). | Preserves all application firmware slots and user SPIFFS storage. |
| **`[5]`** | **Advanced Console** | Submenu for Dual-OTA slot flashing (`ota_1` at `0x320000`), erasing SPIFFS (`0x620000`), clearing the e-Paper buffer (`0x7FC000`), or flashing custom `.bin` files. | User-selectable per operation. |
| **`[6]`** | **Live MD5 Inspector** | Queries on-chip hardware via SLIP to compute MD5 checksums across all partitions and audits against bundled images. | Read-only inspection; non-destructive. |

---

## 2. Release Package File Hierarchy

```text
├── flash.bat                  # Root hardware & ecosystem launcher (Interactive menu & CLI)
├── h1os.bin                   # Primary application binary (ota_0 slot)
├── README.md                  # Release documentation (GitHub Flavored Markdown)
├── README.txt                 # Plain-text quick start manual for terminal / Notepad
├── checksums.sha256           # SHA-256 integrity digests for all bundled files
├── bins/                      # Modular partition binaries
│   ├── bootloader.bin         # ESP-IDF 2nd-stage bootloader (0x0000)
│   ├── partition-table.bin    # Binary partition table with embedded MD5 (0x8000)
│   ├── ota_data_initial.bin   # Dual-slot OTA boot selector (0x1D000)
│   ├── h1os.bin              # Primary application image copy (0x20000)
│   └── h1os-v*-factory.bin    # Monolithic single-binary image (0x0000)
└── engine/
    └── flasher.ps1            # Generic zero-dependency ESP32-S3 ROM SLIP engine
```

---

## 3. Flash Memory Partition Map (8 MB Flash Die)

The 8 MB flash layout enforces ESP-IDF boundary alignments (4 KB sector alignment for data, 64 KB block alignment for app):

| \# | Partition Name | Type | SubType | Start Offset | End Offset | Size (Hex) | Size (KB) | Description |
| :---: | :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| **1** | `bootloader` | `system` | `boot` | `0x000000` | `0x007FFF` | `0x008000` | 32.0 KB | ESP-IDF 2nd-stage bootloader (`bins/bootloader.bin`) |
| **2** | `partition-table` | `system` | `part` | `0x008000` | `0x008FFF` | `0x001000` | 4.0 KB | Binary partition table with MD5 (`bins/partition-table.bin`) |
| **3** | `nvs` | `data` | `nvs` | `0x009000` | `0x01CFFF` | `0x014000` | 80.0 KB | Non-Volatile Storage (Wi-Fi, calibration, statistics) |
| **4** | `otadata` | `data` | `ota` | `0x01D000` | `0x01EFFF` | `0x002000` | 8.0 KB | Dual-sector OTA boot slot selector (`bins/ota_data_initial.bin`) |
| **5** | `phy_init` | `data` | `phy` | `0x01F000` | `0x01FFFF` | `0x001000` | 4.0 KB | RF PHY calibration data |
| **6** | `ota_0` | `app` | `ota_0` | `0x020000` | `0x31FFFF` | `0x300000` | 3,072.0 KB | Primary Application Slot 0 (`h1os.bin`) |
| **7** | `ota_1` | `app` | `ota_1` | `0x320000` | `0x61FFFF` | `0x300000` | 3,072.0 KB | Secondary Application Slot 1 (OTA default / staging) |
| **8** | `storage` | `data` | `spiffs` | `0x620000` | `0x7FBFFF` | `0x1DC000` | 1,904.0 KB | User SPIFFS filesystem partition |
| **9** | `epd_frame` | `data` | `custom` | `0x7FC000` | `0x7FFFFF` | `0x004000` | 16.0 KB | Retained 200x200 monochrome e-Paper framebuffer |

---

## 4. Automation & Command-Line Interface (CLI)

`flash.bat` supports headless execution for CI/CD pipelines and automated testing:

```cmd
:: Standard firmware update (Bootloader + PartTable + App)
flash.bat update

:: Fast app-only update (ota_0 at 0x20000)
flash.bat app

:: Full factory erase and clean re-flash
flash.bat factory

:: Erase NVS settings without modifying application code
flash.bat nvs-wipe

:: Audit live hardware partition MD5s against local binaries
flash.bat inspect
```

For advanced scriptable operations, the underlying SLIP engine can be called directly:

```powershell
# Flash custom binary to a specific offset
powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -Write "0x20000=h1os.bin"

# Erase specific partition range
powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -EraseRegions "0x620000=0x1DC000"

# Inspect on-chip hardware and compute partition MD5s
powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -Inspect -PartitionTable "bins\partition-table.bin"
```

---

## 5. Pre-Flight Hardware Invariants

`flash.bat` enforces hardware verification before issuing any SPI commands:
* **Silicon Family:** Queries Mask ROM opcode `0x14` (`GET_SECURITY_INFO`) to ensure `chip_id == 9` (ESP32-S3).
* **Hardware SiP Verification:** Reads factory eFuses (`0x60007050..0x60007058`) to verify:
  1. Package is `ESP32-S3-PICO-1 (LGA56)`
  2. Flash is `8 MB Embedded Flash`
  3. RAM is `8 MB Embedded PSRAM`
* Connecting an incompatible devkit (such as a 4 MB Flash / non-PSRAM board) halts execution with an explicit error to prevent soft-bricking the device.
