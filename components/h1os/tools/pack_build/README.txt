================================================================================
                    H1OS ESP32-S3 Firmware Release Package
================================================================================

Target Hardware : Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
Flash Memory    : 8 MB Dual-I/O (DIO) SPI Flash @ 80 MHz
PSRAM Memory    : 8 MB Octal PSRAM @ 80 MHz
USB Interface   : Native ESP32-S3 USB CDC (VID_303A:PID_1001)
Architecture    : Zero-Dependency Windows PowerShell + Inline C# SLIP Engine
                  (No Python, esptool.py, or third-party drivers required)

--------------------------------------------------------------------------------
1. QUICK START: FLASHING FIRMWARE
--------------------------------------------------------------------------------

Simply double-click `flash.bat` in this directory to open the interactive
Control Deck:

  [1] Standard Update (Keep Settings & NVS) [Default - Press Enter]
      Refreshes the bootloader, partition table, and primary app image
      (ota_0). Preserves Wi-Fi credentials, runtime statistics, calibration,
      retained e-Paper framebuffer, and user storage.

  [2] Fast App-Only Update
      Quick-flashes the application partition (ota_0 at 0x20000) only.
      Fastest cycle for routine firmware updates.

  [3] Full Factory Restore
      Scrubs the entire 8 MB flash die to 0xFF, then writes fresh factory
      binaries. Used for initial unboxing or recovering from corrupted flash.

  [4] Reset Device Settings (Wipe NVS)
      Erases the NVS partition (0x9000, 80 KB) and PHY calibration (0x1F000)
      to restore factory defaults without re-flashing firmware.

  [5] Advanced Console
      Provides direct control for secondary Dual-OTA slot flashing (ota_1),
      clearing the e-Paper framebuffer (epd_frame), erasing storage, or flashing
      custom binaries.

  [6] Live On-Chip Partition Map & MD5 Inspector
      Queries the ESP32-S3 hardware via ROM SLIP commands to verify on-chip MD5
      checksums against binary images in bins/.

--------------------------------------------------------------------------------
2. RELEASE PACKAGE CONTENTS
--------------------------------------------------------------------------------

  flash.bat                   Hardware & ecosystem launcher (Interactive menu & CLI)
  h1os.bin                    Primary application binary (ota_0)
  README.md                   Release documentation (GitHub Flavored Markdown)
  README.txt                  Release documentation (Plain text for Notepad)
  checksums.sha256            SHA-256 integrity digests for all bundled files
  engine/
    flasher.ps1               Generic zero-dependency ESP32-S3 ROM SLIP engine
  bins/
    bootloader.bin            ESP-IDF 2nd-stage bootloader (0x0000)
    partition-table.bin       Binary partition table with MD5 validation (0x8000)
    ota_data_initial.bin      Dual-slot OTA boot selector (0x1D000)
    h1os-v*-factory.bin       Monolithic single-binary image (0x0000)

--------------------------------------------------------------------------------
3. FLASH MEMORY PARTITION MAP (8 MB Flash Die)
--------------------------------------------------------------------------------

  Offset      Size        Name             Type    SubType    Description
  ------------------------------------------------------------------------------
  0x000000    32 KB       bootloader       sys     boot       2nd-stage bootloader
  0x008000    4 KB        partition-table  sys     part       Binary partition map
  0x009000    80 KB       nvs              data    nvs        Settings & calibration
  0x01D000    8 KB        otadata          data    ota        OTA boot selector
  0x01F000    4 KB        phy_init         data    phy        RF PHY calibration
  0x020000    3072 KB     ota_0            app     ota_0      Primary application
  0x320000    3072 KB     ota_1            app     ota_1      Secondary OTA slot
  0x620000    1904 KB     storage          data    spiffs     User SPIFFS filesystem
  0x7FC000    16 KB       epd_frame        data    custom     Retained e-Paper frame

--------------------------------------------------------------------------------
4. COMMAND-LINE USAGE & AUTOMATION
--------------------------------------------------------------------------------

You can invoke `flash.bat` directly from the command prompt or CI/CD scripts:

  flash.bat update            Standard update (Bootloader + PartTable + App)
  flash.bat app               Fast app-only update (ota_0 at 0x20000)
  flash.bat factory           Full factory restore (Erase 8MB + Full write)
  flash.bat nvs-wipe          Wipe NVS settings partition
  flash.bat inspect           Audit live on-chip hardware partition MD5s

For custom or scriptable operations, invoke the engine directly:

  powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -Write "0x20000=h1os.bin"
  powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -EraseAll
  powershell -ExecutionPolicy Bypass -File .\engine\flasher.ps1 -Inspect -PartitionTable "bins\partition-table.bin"

--------------------------------------------------------------------------------
5. PRE-FLIGHT HARDWARE INVARIANTS
--------------------------------------------------------------------------------

`flash.bat` queries the ROM and eFuses before sending any SPI flash commands:
  * Silicon Family : Verified as ESP32-S3 (Chip ID 9).
  * Hardware SiP   : Verified as ESP32-S3-PICO-1 (LGA56) with 8MB Embedded Flash
                     and 8MB Embedded PSRAM.
Connecting a mismatched devkit halts execution immediately to protect the board.
================================================================================
