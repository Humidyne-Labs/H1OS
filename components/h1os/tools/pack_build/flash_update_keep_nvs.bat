@echo off
setlocal
title H1OS Standard Update [Keeps NVS, SPIFFS ^& Framebuffer Intact]
color 0A

rem =========================================================================
rem  Control Vector 1: Standard Firmware Update (Keeps NVS & User Data)
rem  Flashes: bootloader (0x0), partition-table (0x8000), otadata (0x1D000),
rem           and H1OS App -> ota_0 (0x20000).
rem  Preserves: nvs (0x9000), ota_1 (0x320000), storage (0x620000), epd_frame
rem =========================================================================

set "PS_SCRIPT=%~dp0flasher.ps1"
if not exist "%PS_SCRIPT%" if exist "%~dp0engine\flasher.ps1" set "PS_SCRIPT=%~dp0engine\flasher.ps1"

powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%PS_SCRIPT%" -Profile KeepNvs %*
set "EXIT_CODE=%ERRORLEVEL%"

if "%H1OS_SUBCALL%"=="1" exit /b %EXIT_CODE%
if not "%EXIT_CODE%"=="0" ( pause & exit /b %EXIT_CODE% )
timeout /t 4
exit /b 0
