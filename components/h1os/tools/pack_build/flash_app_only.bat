@echo off
setlocal
title H1OS Fast App-Only Update [Keeps Bootloader, PartTable ^& NVS Intact]
color 0B

rem =========================================================================
rem  Control Vector 2: Fast Application-Only Update (ota_0 @ 0x20000)
rem  Flashes: h1os.bin -> ota_0 (0x20000) and updates otadata (0x1D000).
rem  Preserves: bootloader (0x0), partition-table (0x8000), nvs (0x9000),
rem             ota_1 (0x320000), storage SPIFFS (0x620000), epd_frame
rem =========================================================================

set "PS_SCRIPT=%~dp0flasher.ps1"
if not exist "%PS_SCRIPT%" if exist "%~dp0engine\flasher.ps1" set "PS_SCRIPT=%~dp0engine\flasher.ps1"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Profile AppOnly -KeepPartitionTable -KeepNvs %*
set "EXIT_CODE=%ERRORLEVEL%"

if "%H1OS_SUBCALL%"=="1" exit /b %EXIT_CODE%
if not "%EXIT_CODE%"=="0" ( pause & exit /b %EXIT_CODE% )
timeout /t 4
exit /b 0
