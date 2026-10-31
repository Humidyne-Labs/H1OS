# ⚡ H1 // TOKYO-BLOODLINE :: USB CTRL PUNK (v2.6)

A zero-dependency Windows hardware USB bus controller, **Turbo Port Whacker**, and Single-Ended Zero (SE0) port-cycling utility (**The USB Hammer**) engineered for embedded hardware development (ESP32-S3 USB-JTAG/Serial, ULP coprocessors, CP210x, CH34x, FTDI, and custom silicon). Features an underground **app-phreak aesthetic** and the **`tokyo_bloodline_synth`** soundtrack by **Humiditron** (**Humidyne Labs**, 2026).

---

## 📂 Repository & Folder Architecture

The repository is structured into two dedicated distribution editions matching distinct deployment, audit, and operational requirements:

```
.
├── README.md                                                      # Master Root Documentation
│
├── Full/                                                          # [EDITION 01] Standalone / Embedded Audio
│   ├── README.md                                                  # Full edition manual & architecture
│   ├── tokyo_bloodline.ps1                                        # GUI script with embedded base64 audio
│   ├── tokyo_bloodline_full.bat                                   # Admin UAC launcher (audio enabled)
│   └── tokyo_bloodline_full_silent.bat                            # Admin UAC launcher (muted: -NoAudio)
│
├── Lite/                                                          # [EDITION 02] Zero-Blob / Auditable Source
│   ├── README.md                                                  # Lite edition manual & dynamic asset docs
│   ├── tokyo_bloodline_lite.bat                                   # Admin UAC launcher (audio enabled)
│   ├── tokyo_bloodline_lite.ps1                                   # Pure human-readable script (zero binary blobs)
│   ├── tokyo_bloodline_lite_silent.bat                            # Admin UAC launcher (muted: -NoAudio)
│   └── tokyo_bloodline_synth.mp3                                  # External master audio track
│
└── tokyo_bloodline_dist/                                          # Distribution archive & analysis reports
    ├── usb_ctrl_punk_v2.6.zip                                     # Release archive
    └── reports/                                                   # Verification reports
        ├── hash-report-b890755f-3ef7-4524-a450-3a064522f4dd.pdf   # Hash-File.Online v3.14.16
        └── usb_ctrl_punk_v2.6.zip.pdf                             # METADEFENDER.com (MetaDefender Cloud)
```

---

## ⚡ Edition Matrix & Comparison

| Feature / Attribute       | `Full/` (Embedded Audio)                                        | `Lite/` (Zero-Blob / Auditable)                              |
| :---                      | :---                                                            | :---                                                         |
| **Primary Use Case**      | Single-file portability, field flash drives, air-gapped drop-in | Corporate workstations, security auditing, Git diff review   |
| **Binary Blobs**          | Contains inline base64 audio blob                               | **Strictly 0% binary blobs** (100% plain UTF-8 text)         |
| **Audio Asset Source**    | In-memory stream decoded directly to RAM                        | Local directory scan (`tokyo_bloodline_synth.mp3` or `.wav`) |
| **File Dependency**       | Completely self-contained in `tokyo_bloodline.ps1`              | Requires audio file in folder for sound (silent without it)  |
| **Execution Performance** | Identical 30 FPS GDI+ non-blocking async runspace               | Identical 30 FPS GDI+ non-blocking async runspace            |
| **Hardware IOCTL Engine** | Win32 `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`)                   | Win32 `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`)                |

---

## 🚀 Quick Launch Guide

### 1. Full Edition (`Full/`)
* **Standard (With Audio):** Double-click `Full/tokyo_bloodline_full.bat`
* **Muted (Silent Startup):** Double-click `Full/tokyo_bloodline_full_silent.bat`
* **CLI (PowerShell):**
  ```powershell
  powershell.exe -NoProfile -ExecutionPolicy Bypass -File "Full\tokyo_bloodline.ps1"
  ```

### 2. Lite Edition (`Lite/`)
* **Standard (With Audio):** Double-click `Lite/tokyo_bloodline_lite.bat`
* **Muted (Silent Startup):** Double-click `Lite/tokyo_bloodline_lite_silent.bat`
* **CLI (PowerShell):**
  ```powershell
  powershell.exe -NoProfile -ExecutionPolicy Bypass -File "Lite\tokyo_bloodline_lite.ps1"
  ```

### Universal Startup Flags
Both editions accept the following command-line flags to mute sound on launch:
`-NoAudio`, `-Mute`, `-Silent`, `-SoundOff`, `-NoSound`, `-DisableAudio`.

---

## 🛠 Hardware Recovery Subsystem

Both editions run an identical Win32/C# background worker decoupled from the 30 FPS GDI+ rendering engine:

1. **`>> [1] PATCH PORT (SE0 REPLUG) <<`**  
   Issues `IOCTL_USB_HUB_CYCLE_PORT` (`0x220444`) directly to the upstream USB root hub or external controller, forcing an electrical Single-Ended Zero state (both D+ and D- grounded) to simulate a physical unplug/replug event.
2. **`>> [2] RESTART DRIVER (PNP TOGGLE) <<`**  
   Performs a programmatic DevNode cycle via PnP management APIs and `pnputil /restart-device`.
3. **`>> [3] PURGE FAULTED NODE (CODE 43) <<`**  
   Tears down corrupt or stuck DevNodes (`Code 43 - Device Descriptor Request Failed`) via `pnputil /remove-device` and initiates an immediate bus sweep.
4. **`>> [4] SCAN FOR HARDWARE CHANGES <<`**  
   Directs the Windows Plug-and-Play manager (`pnputil /scan-devices`) to re-enumerate the device tree.

---

## 📜 Credits & Licensing
* **Engine & Visualizer:** Humidyne Labs / Underground Hardware Division (2026)
* **Soundtrack:** `tokyo_bloodline_synth` by **Humiditron**