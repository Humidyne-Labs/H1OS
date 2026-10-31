@echo off
setlocal
title H1OS Targeted NVS ^& RF Calibration Wipe [Keeps App ^& SPIFFS Intact]
color 0D

rem =========================================================================
rem  Control Vector 4: Targeted NVS & PHY Calibration Reset
rem  Erases: nvs (0x009000, 80 KB) and phy_init (0x01F000, 4 KB) -> 0xFF.
rem  Preserves: Bootloader, Partition Table, ota_0, ota_1, storage, epd_frame
rem =========================================================================

set "PS_SCRIPT=%~dp0flasher.ps1"
if not exist "%PS_SCRIPT%" if exist "%~dp0engine\flasher.ps1" set "PS_SCRIPT=%~dp0engine\flasher.ps1"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Profile WipeNvs %*
set "EXIT_CODE=%ERRORLEVEL%"

if "%H1OS_SUBCALL%"=="1" exit /b %EXIT_CODE%
if not "%EXIT_CODE%"=="0" ( pause & exit /b %EXIT_CODE% )
timeout /t 4
exit /b 0
