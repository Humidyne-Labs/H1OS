# ==============================================================================
# reset_coms.ps1 - Rescan and reset ESP32, USB Serial, and Unknown PnP devices
# ==============================================================================

# 1. Ensure the script runs with Administrator privileges
$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole(
    [Security.Principal.WindowsBuiltInRole]::Administrator
)

if (-not $isAdmin) {
    Write-Host "[!] Admin rights required to reset hardware drivers. Attempting elevation..." -ForegroundColor Yellow
    try {
        Start-Process powershell.exe -Verb RunAs -ArgumentList ("-NoProfile -ExecutionPolicy Bypass -File `"$PSCommandPath`"")
        exit
    } catch {
        Write-Host "[!] Could not automatically elevate. Please run this script in an Administrator PowerShell window:" -ForegroundColor Red
        Write-Host "    Right-click PowerShell -> 'Run as Administrator', then run:" -ForegroundColor Yellow
        Write-Host "    & `"$PSCommandPath`"`n" -ForegroundColor Gray
        exit 1
    }
}

Write-Host "=== Windows Serial & USB Bus Reset Tool ===" -ForegroundColor Cyan

# 2. Trigger initial hardware scan for Plug and Play changes
Write-Host "[*] Triggering initial Windows PnP bus rescan..." -ForegroundColor Cyan
pnputil /scan-devices | Out-Null
Start-Sleep -Milliseconds 600

# 3. Locate connected (Present = True) target devices
# A. Known serial / ESP32 / JTAG interfaces
$serialDevices = @(Get-PnpDevice -PresentOnly | Where-Object {
    ($_.Class -in @('Ports', 'USB')) -and
    ($_.FriendlyName -match 'Espressif|ESP32|CP210|CH34|FTDI|Silicon Labs|USB Serial Device|JTAG|WCH')
})

# B. Unknown, error, degraded, or descriptor-failed devices on USB / Ports / Unknown buses
$unknownDevices = @(Get-PnpDevice -PresentOnly | Where-Object {
    (
        ($_.Class -in @('Unknown', 'USB', 'Ports') -or [string]::IsNullOrEmpty($_.Class)) -and
        (
            ($_.Class -eq 'Unknown') -or
            ($_.FriendlyName -match 'Unknown|Unrecognized|Descriptor Request Failed|Port Reset Failed|Failed') -or
            ($_.Status -in @('Error', 'Degraded', 'Unknown')) -or
            ($_.Problem -notin @('CM_PROB_NONE', $null, 0))
        ) -and
        ($_.InstanceId -match '^USB\\|^FTDIBUS\\|^USBSTOR\\|^HID\\')
    ) -and
    (@($serialDevices.InstanceId) -notcontains $_.InstanceId)
})

$totalFound = ($serialDevices.Count + $unknownDevices.Count)

if ($totalFound -eq 0) {
    Write-Host "`n[!] No active ESP32, USB-Serial, or unknown/error devices detected on the bus." -ForegroundColor Red
    Write-Host "    If using ESP32-S3 native USB:" -ForegroundColor Yellow
    Write-Host "    1. Hold BOOT (GPIO 0)"
    Write-Host "    2. Press and release RESET (EN)"
    Write-Host "    3. Release BOOT"
    Write-Host "    4. Run this script again once Windows plays the connect chime.`n"
} else {
    $needsRescan = $false

    # 4A. Restart known ESP32 & Serial driver stacks
    if ($serialDevices.Count -gt 0) {
        Write-Host "`n[*] Found $($serialDevices.Count) connected Serial/ESP32 device(s):" -ForegroundColor Green
        foreach ($dev in $serialDevices) {
            Write-Host "  -> $($dev.FriendlyName) [$($dev.InstanceId)]" -ForegroundColor Gray
        }

        Write-Host "`n[*] Restarting serial driver stack(s)..." -ForegroundColor Cyan
        foreach ($dev in $serialDevices) {
            Write-Host "  Restarting: $($dev.FriendlyName)..." -NoNewline
            $result = pnputil /restart-device "$($dev.InstanceId)" 2>&1
            if ($LASTEXITCODE -eq 0) {
                Write-Host " [OK]" -ForegroundColor Green
            } else {
                Write-Host " [FAILED] Attempting power-cycle remove/rescan..." -ForegroundColor Yellow
                pnputil /remove-device "$($dev.InstanceId)" 2>&1 | Out-Null
                $needsRescan = $true
            }
        }
    }

    # 4B. Reset & re-enumerate Unknown / Error devices
    if ($unknownDevices.Count -gt 0) {
        Write-Host "`n[*] Found $($unknownDevices.Count) Unknown or Faulted device(s):" -ForegroundColor Yellow
        foreach ($dev in $unknownDevices) {
            $probText = if ($dev.Problem) { " (Problem: $($dev.Problem))" } else { "" }
            Write-Host "  [!] $($dev.FriendlyName)$probText [$($dev.InstanceId)]" -ForegroundColor Magenta
        }

        Write-Host "`n[*] Recovering Unknown / Faulted device(s)..." -ForegroundColor Cyan
        foreach ($dev in $unknownDevices) {
            Write-Host "  Recovering: $($dev.FriendlyName)..." -NoNewline
            
            # For Code 43 (Descriptor Request Failed), restarting keeps the broken descriptor.
            # Removing the node forces the USB hub to cut port power and renegotiate hardware enumeration.
            if ($dev.Problem -eq 'CM_PROB_FAILED_POST_START' -or $dev.FriendlyName -match 'Descriptor Request Failed') {
                Write-Host " [REMOVING FAULTED NODE]..." -NoNewline -ForegroundColor Yellow
                $removeRes = pnputil /remove-device "$($dev.InstanceId)" 2>&1
                if ($LASTEXITCODE -eq 0) {
                    Write-Host " [REMOVED]" -ForegroundColor Green
                    $needsRescan = $true
                } else {
                    Write-Host " [FAILED: $removeRes]" -ForegroundColor Red
                }
            } else {
                # Try soft restart first
                $result = pnputil /restart-device "$($dev.InstanceId)" 2>&1
                if ($LASTEXITCODE -eq 0) {
                    Write-Host " [RESTARTED]" -ForegroundColor Green
                } else {
                    Write-Host " [RESTART FAILED -> REMOVING NODE]..." -NoNewline -ForegroundColor Yellow
                    pnputil /remove-device "$($dev.InstanceId)" 2>&1 | Out-Null
                    $needsRescan = $true
                }
            }
        }
    }

    # 5. Follow-up bus rescan if any nodes were removed/reset
    if ($needsRescan -or ($unknownDevices.Count -gt 0)) {
        Write-Host "`n[*] Rescanning bus for re-enumerated hardware..." -ForegroundColor Cyan
        Start-Sleep -Milliseconds 500
        pnputil /scan-devices | Out-Null
        Start-Sleep -Milliseconds 800
    }
}

# 6. Output active COM ports currently registered in Windows
Start-Sleep -Milliseconds 500
Write-Host "`n[*] Currently registered COM ports:" -ForegroundColor Cyan
$activePorts = [System.IO.Ports.SerialPort]::GetPortNames()

if ($activePorts) {
    foreach ($port in ($activePorts | Sort-Object)) {
        Write-Host "  [+] $port" -ForegroundColor Green
    }
} else {
    Write-Host "  [-] No active COM ports registered." -ForegroundColor Yellow
}

Write-Host "`nDone." -ForegroundColor Cyan