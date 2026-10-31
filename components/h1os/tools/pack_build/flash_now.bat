@echo off
setlocal EnableDelayedExpansion
title H1OS Master Firmware ^& Partition Control Deck (Zero-Dependency)
color 0A

rem =========================================================================
rem  H1OS Master Interactive Launcher & Control-Vector Dispatcher
rem  - If CLI arguments are passed (e.g. flash_now.bat -Profile AppOnly),
rem    forwards them directly to flasher.ps1 for automated/scripted runs.
rem  - Otherwise presents the hierarchical menu that dispatches to each
rem    modular control-vector batch file or opens the Partition/NVS Manager.
rem =========================================================================

set "PS_SCRIPT=%~dp0flasher.ps1"
if not exist "%PS_SCRIPT%" if exist "%~dp0engine\flasher.ps1" set "PS_SCRIPT=%~dp0engine\flasher.ps1"

if not "%~1"=="" (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" %*
    exit /b !ERRORLEVEL!
)

:menu
cls
echo ===============================================================================
echo                 H1OS ESP32-S3 Firmware ^& Partition Control Deck
echo           Target Hardware: Waveshare ESP32-S3 ePaper 1.54" V2 (8MB DIO)
echo             Zero-Dependency Native USB SLIP Engine (VID_303A^&PID_1001)
echo ===============================================================================
echo.
echo   --- TURNKEY CONTROL VECTORS (Calls Modular .bat Launchers) ---
echo   [1] Standard Update (Keep NVS)   - Calls flash_update_keep_nvs.bat [Default]
echo                                      Updates Bootloader, PartTable ^& ota_0 App;
echo                                      keeps NVS (0x9000), SPIFFS ^& epd_frame
echo   [2] Fast App-Only Update         - Calls flash_app_only.bat
echo                                      Updates ota_0 App (0x20000) only; keeps
echo                                      Bootloader, PartTable, NVS ^& SPIFFS intact
echo   [3] Full Factory POR Restore     - Calls flash_factory.bat
echo                                      Scrubs full 8MB flash die to 0xFF, then
echo                                      performs a clean factory installation
echo   [4] Wipe NVS Settings Only       - Calls flash_nvs_wipe.bat
echo                                      Resets nvs (0x9000) ^& phy_init (0x1F000)
echo                                      without re-flashing firmware or SPIFFS
echo.
echo   --- ADVANCED PARTITION, DUAL-OTA ^& NVS MANAGER (Direct PS1 Engine) ---
echo   [5] Open Interactive Partition, Dual-OTA ^& NVS Manager Console
echo       (Flash ota_1 / Dual-OTA, Switch Boot Slot, Wipe SPIFFS/epd_frame,
echo        Flash Custom .bin to Any Partition, or Live-Inspect On-Chip MD5s)
echo   [6] Live On-Chip Partition Map ^& MD5 Inspector
echo   [Q] Quit
echo ===============================================================================
set "CHOICE=1"
set /p "CHOICE=Select option [1-6, Q, Enter=1]: "

set "H1OS_SUBCALL=1"
echo.
if "%CHOICE%"=="1" (
    call "%~dp0flash_update_keep_nvs.bat"
    goto :done
)
if "%CHOICE%"=="2" (
    call "%~dp0flash_app_only.bat"
    goto :done
)
if "%CHOICE%"=="3" (
    call "%~dp0flash_factory.bat"
    goto :done
)
if "%CHOICE%"=="4" (
    call "%~dp0flash_nvs_wipe.bat"
    goto :done
)
if "%CHOICE%"=="5" (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Interactive
    goto :done
)
if "%CHOICE%"=="6" (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Profile Inspect
    goto :done
)
if /i "%CHOICE%"=="Q" exit /b 0

echo [ERROR] Invalid selection "%CHOICE%".
pause
goto :menu

:done
echo.
pause
exit /b %ERRORLEVEL%
