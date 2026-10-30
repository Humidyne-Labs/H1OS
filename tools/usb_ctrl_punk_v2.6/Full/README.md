# ⚡ TOKYO-BLOODLINE :: Full Edition (Embedded Audio)

The **Full Edition** of `TOKYO-BLOODLINE` is packaged as an all-in-one, single-file deployable utility. The soundtrack (`tokyo_bloodline_synth` by Humiditron) is embedded directly into the script as an inline Base64 data stream and decoded into memory at runtime.

---

## 📦 Directory Contents

| File                                  | Description                                                                                         |
| :---                                  | :---                                                                                                |
| **`tokyo_bloodline.ps1`**             | Complete, zero-external-dependency PowerShell script with embedded audio stream and GUI visualizer. |
| **`tokyo_bloodline_full.bat`**        | Administrative launcher with automatic UAC elevation prompt and background console hiding.          |
| **`tokyo_bloodline_full_silent.bat`** | Administrative launcher invoking the script with `-NoAudio` for instant silent startup.             |

---

## 💡 Key Characteristics

* **Single-File Portability:** You only need `tokyo_bloodline.ps1` to have 100% of the UI, hardware recovery engine, and audio capabilities.
* **In-Memory Audio Decoupling:** Does not write temporary media files to disk; streams directly via in-memory sound structures.
* **Field-Ready:** Ideal for copying to USB flash drives, field diagnostic kits, or technician recovery partitions where secondary assets might get lost or separated.

---

## 🚀 Execution & Usage

### Method A: Admin Batch Launchers (Recommended)
Double-click either batch file:
* **`tokyo_bloodline_full.bat`** — Elevates via UAC and plays audio immediately.
* **`tokyo_bloodline_full_silent.bat`** — Elevates via UAC with audio muted (`-NoAudio`).

### Method B: Direct PowerShell Execution
Run from an elevated PowerShell terminal:

```powershell
# Standard execution (Audio Enabled)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File ".\tokyo_bloodline.ps1"

# Silent execution (Muted)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File ".\tokyo_bloodline.ps1" -NoAudio
```

*Note: If executed from a non-elevated console, the script automatically triggers a self-elevation UAC prompt and passes through any sound parameters.*

---

## 🎛 On-Screen Controls
* **`[ AUDIO: ON / OFF ]`**: Click at any time in the upper-right title bar to toggle music playback.
* **`[ NFO ]`**: Expands/collapses the underground release notes banner.
* **`[ X ]`**: Gracefully terminates runspaces, halts IOCTL threads, and closes the application.