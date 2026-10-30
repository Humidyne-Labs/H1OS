@echo off
:: ==============================================================================
:: H1 // TOKYO-BLOODLINE :: USB CTRL PUNK v2.6 — Full Launcher (Audio Enabled)
:: Automatically requests Administrator (UAC) privileges and launches the GUI
:: ==============================================================================
setlocal
set "PS1_PATH=%~dp0tokyo_bloodline.ps1"

if not exist "%PS1_PATH%" (
    echo [ERR] Could not locate tokyo_bloodline.ps1
    pause
    exit /b 1
)

:: Check for Administrator privileges
net session >nul 2>&1
if %errorlevel% == 0 (
    start "" powershell.exe -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%PS1_PATH%"
) else (
    powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Start-Process powershell.exe -Verb RunAs -WindowStyle Hidden -ArgumentList '-NoProfile', '-ExecutionPolicy', 'Bypass', '-WindowStyle', 'Hidden', '-File', '%PS1_PATH%'"
)
exit /b 0