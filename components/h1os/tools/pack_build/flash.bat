@echo off
setlocal EnableDelayedExpansion
title H1OS Firmware ^& Ecosystem Control Deck (Zero-Dependency)
color 0A

rem =========================================================================
rem  H1OS Firmware & Ecosystem Control Deck
rem  Hardware: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
rem  Zero-Dependency Native USB SLIP Engine (VID_303A:PID_1001)
rem =========================================================================

set "ENGINE=%~dp0engine\flasher.ps1"
if not exist "%ENGINE%" if exist "%~dp0flasher.ps1" set "ENGINE=%~dp0flasher.ps1"

set "PART_BIN=%~dp0bins\partition-table.bin"
set "BOOT_BIN=%~dp0bins\bootloader.bin"
set "OTA_DATA=%~dp0bins\ota_data_initial.bin"
set "APP_BIN=%~dp0h1os.bin"
set "FACTORY_BIN=%~dp0bins\factory_init.bin"

rem -------------------------------------------------------------------------
rem CLI Command Aliases & Parameter Passthrough
rem -------------------------------------------------------------------------
if not "%~1"=="" (
    if /i "%~1"=="update"   goto :cmd_update
    if /i "%~1"=="app"      goto :cmd_app
    if /i "%~1"=="factory"  goto :cmd_factory
    if /i "%~1"=="nvs-wipe" goto :cmd_nvs_wipe
    if /i "%~1"=="inspect"  goto :cmd_inspect

    rem Forward any other arguments directly to flasher.ps1
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%ENGINE%" %*
    exit /b !ERRORLEVEL!
)

:menu
cls
echo ===============================================================================
echo                 H1OS ESP32-S3 Firmware ^& Ecosystem Control Deck
echo           Target Hardware: Waveshare ESP32-S3 ePaper 1.54" V2 (8MB DIO)
echo             Zero-Dependency Native USB SLIP Engine (VID_303A:PID_1001)
echo ===============================================================================
echo.
echo   --- PRIMARY FIRMWARE ACTIONS ---
echo   [1] Standard Update (Keep Settings ^& NVS) [Default - Press Enter]
echo       Updates Bootloader, Partition Table, OTA data, ^& ota_0 App;
echo       preserves Wi-Fi, NVS calibration, SPIFFS storage, ^& e-Paper buffer.
echo.
echo   [2] Fast App-Only Update
echo       Flashes ota_0 App (0x20000) only; leaves all other partitions untouched.
echo.
echo   [3] Full Factory Restore
echo       Erases entire 8MB flash die to 0xFF, then writes fresh factory binaries.
echo.
echo   [4] Reset Device Settings (Wipe NVS)
echo       Erases NVS (0x9000) and PHY calibration (0x1F000) without flashing.
echo.
echo   --- ADVANCED PARTITION ^& HARDWARE UTILITIES ---
echo   [5] Advanced Console (Dual-OTA, Storage, Custom, Live MD5)
echo   [6] Live On-Chip Partition Map ^& MD5 Inspector
echo   [Q] Quit
echo ===============================================================================
set "CHOICE=1"
set /p "CHOICE=Select option [1-6, Q, Enter=1]: "

if "%CHOICE%"=="1" goto :cmd_update
if "%CHOICE%"=="2" goto :cmd_app
if "%CHOICE%"=="3" goto :cmd_factory
if "%CHOICE%"=="4" goto :cmd_nvs_wipe
if "%CHOICE%"=="5" goto :advanced_menu
if "%CHOICE%"=="6" goto :cmd_inspect
if /i "%CHOICE%"=="Q" exit /b 0

echo [ERROR] Invalid selection "%CHOICE%".
pause
goto :menu

:cmd_update
echo.
echo [*] Executing Standard Firmware Update (Keep Settings ^& NVS)...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Write '0x0=%BOOT_BIN%', '0x8000=%PART_BIN%', '0x1D000=%OTA_DATA%', '0x20000=%APP_BIN%'"
goto :action_done

:cmd_app
echo.
echo [*] Executing Fast App-Only Update...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Write '0x20000=%APP_BIN%'"
goto :action_done

:cmd_factory
echo.
echo [!] WARNING: Full Factory Restore will erase the entire 8MB flash die!
echo [!] All Wi-Fi credentials, runtime statistics, and persistent frames will be lost.
set "CONFIRM=N"
set /p "CONFIRM=Are you sure you want to proceed with full erase? [y/N]: "
if /i not "%CONFIRM%"=="Y" (
    echo [*] Factory restore aborted by user.
    goto :action_done
)
echo.
echo [*] Executing Full Factory Restore...
if exist "%FACTORY_BIN%" (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -EraseAll -Write '0x0=%BOOT_BIN%', '0x8000=%PART_BIN%', '0x10000=%FACTORY_BIN%', '0x1D000=%OTA_DATA%', '0x20000=%APP_BIN%'"
) else (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -EraseAll -Write '0x0=%BOOT_BIN%', '0x8000=%PART_BIN%', '0x1D000=%OTA_DATA%', '0x20000=%APP_BIN%'"
)
goto :action_done

:cmd_nvs_wipe
echo.
echo [*] Resetting Device Settings (Wiping NVS 0x9000 and PHY 0x1F000)...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -EraseRegions '0x9000=0x14000', '0x1F000=0x1000'"
goto :action_done

:cmd_inspect
echo.
echo [*] Auditing On-Chip Hardware Telemetry ^& Partition MD5s...
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Inspect -PartitionTable '%PART_BIN%'"
goto :action_done

:advanced_menu
cls
echo ===============================================================================
echo                 H1OS Advanced Partition ^& Diagnostics Console
echo ===============================================================================
echo.
echo   [1] Flash Dual-OTA Secondary Slot (ota_1 at 0x320000)
echo   [2] Flash Both OTA Slots Identically (ota_0 at 0x20000 + ota_1 at 0x320000)
echo   [3] Reset User Storage Partition (storage at 0x620000, 1904 KB)
echo   [4] Clear e-Paper Frame Buffer (epd_frame at 0x7FC000, 16 KB)
echo   [5] Live Hardware MD5 Inspection
echo   [6] Custom Binary Flash (Specify custom address ^& file)
echo   [B] Back to Main Menu
echo ===============================================================================
set "ADV_CHOICE=B"
set /p "ADV_CHOICE=Select advanced option [1-6, B]: "

if "%ADV_CHOICE%"=="1" (
    echo.
    echo [*] Flashing ota_1 secondary slot at 0x320000...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Write '0x320000=%APP_BIN%'"
    goto :action_done
)
if "%ADV_CHOICE%"=="2" (
    echo.
    echo [*] Flashing both ota_0 (0x20000) and ota_1 (0x320000) slots identically...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Write '0x20000=%APP_BIN%', '0x320000=%APP_BIN%'"
    goto :action_done
)
if "%ADV_CHOICE%"=="3" (
    echo.
    echo [*] Resetting storage partition at 0x620000 (1904 KB)...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -EraseRegions '0x620000=0x1DC000'"
    goto :action_done
)
if "%ADV_CHOICE%"=="4" (
    echo.
    echo [*] Clearing e-Paper frame partition at 0x7FC000 (16 KB)...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -EraseRegions '0x7FC000=0x4000'"
    goto :action_done
)
if "%ADV_CHOICE%"=="5" (
    echo.
    echo [*] Auditing On-Chip Hardware Telemetry ^& Partition MD5s...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Inspect -PartitionTable '%PART_BIN%'"
    goto :action_done
)
if "%ADV_CHOICE%"=="6" (
    echo.
    set "CUSTOM_ADDR="
    set /p "CUSTOM_ADDR=Enter destination flash offset in hex (e.g. 0x20000): "
    set "CUSTOM_FILE="
    set /p "CUSTOM_FILE=Enter path to binary file to flash: "
    if not defined CUSTOM_ADDR goto :advanced_menu
    if not exist "!CUSTOM_FILE!" (
        echo [ERROR] File "!CUSTOM_FILE!" not found.
        pause
        goto :advanced_menu
    )
    echo [*] Flashing "!CUSTOM_FILE!" to !CUSTOM_ADDR!...
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "& '%ENGINE%' -Write '!CUSTOM_ADDR!=!CUSTOM_FILE!'"
    goto :action_done
)
if /i "%ADV_CHOICE%"=="B" goto :menu

echo [ERROR] Invalid selection "%ADV_CHOICE%".
pause
goto :advanced_menu

:action_done
set "ERR=!ERRORLEVEL!"
echo.
if !ERR! equ 0 (
    echo [OK] Operation completed successfully.
) else (
    echo [ERROR] Operation failed with exit code !ERR!.
)
echo.
pause
goto :menu
