@echo off
setlocal
title H1OS Full Factory POR Restore [8MB Die Scrub + Clean Install]
color 0E

rem =========================================================================
rem  Control Vector 3: Full Factory POR Restore (8MB NOR Flash Scrub -> 0xFF)
rem  Scrubs: Entire 8MB flash die (0x000000 .. 0x7FFFFF -> 0xFF), purging
rem          nvs, otadata, phy_init, ota_0, ota_1, storage, and epd_frame.
rem  Flashes: Fresh bootloader, partition-table, otadata, and ota_0 firmware.
rem =========================================================================

set "PS_SCRIPT=%~dp0flasher.ps1"
if not exist "%PS_SCRIPT%" if exist "%~dp0engine\flasher.ps1" set "PS_SCRIPT=%~dp0engine\flasher.ps1"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Profile Factory %*
set "EXIT_CODE=%ERRORLEVEL%"

if "%H1OS_SUBCALL%"=="1" exit /b %EXIT_CODE%
if not "%EXIT_CODE%"=="0" ( pause & exit /b %EXIT_CODE% )
timeout /t 4
exit /b 0
