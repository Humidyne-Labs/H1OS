# ⚡ TOKYO-BLOODLINE :: Lite Edition (Zero-Blob / Auditable)

The **Lite Edition** of `TOKYO-BLOODLINE` is engineered for strict enterprise environments, security auditing, and clean version control. It contains **0% binary or Base64 blobs**—every line of PowerShell and C# is 100% human-readable UTF-8 source code.

---

## 📦 Directory Contents

| File                                  | Description                                                               |
| :---                                  | :---                                                                      |
| **`tokyo_bloodline_lite.ps1`**        | Pure human-readable PowerShell script containing no embedded binary data. |
| **`tokyo_bloodline_synth.mp3`**       | Standalone master audio track (`tokyo_bloodline_synth` by Humiditron).    |
| **`tokyo_bloodline_lite.bat`**        | Administrative UAC launcher (audio enabled).                              |
| **`tokyo_bloodline_lite_silent.bat`** | Administrative UAC launcher starting the app muted (`-NoAudio`).          |

---

## 💡 Key Characteristics

* **100% Auditable Source:** Clean diffs in Git. Corporate security scanners, SOC analysts, and code auditors can inspect the entirety of the script without flagging binary payload anomalies or base64 blobs.
* **Dynamic Asset Resolution:** On startup, if audio is enabled, the script dynamically probes the local directory for:
  1. `tokyo_bloodline_synth.mp3`
  2. Any `.mp3` file in the folder
  3. Any `.wav` file in the folder
* **Graceful Degradation:** If no audio asset is present in the working directory, the script automatically initializes in muted mode without throwing errors or breaking hardware recovery features.
* **Custom Soundtrack Support:** You can drop in any custom `.mp3` or `.wav` track into this folder to use your own background audio.

---

## 🚀 Execution & Usage

### Method A: Admin Batch Launchers (Recommended)
Double-click either batch file:
* **`tokyo_bloodline_lite.bat`** — Elevates via UAC and loads the local soundtrack.
* **`tokyo_bloodline_lite_silent.bat`** — Elevates via UAC and bypasses audio loading entirely (`-NoAudio`).

### Method B: Direct PowerShell Execution
Run from an elevated PowerShell terminal:

```powershell
# Standard execution (Scans directory for audio)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File ".\tokyo_bloodline_lite.ps1"

# Silent execution (Skips audio initialization)
powershell.exe -NoProfile -ExecutionPolicy Bypass -File ".\tokyo_bloodline_lite.ps1" -NoAudio
```

---

## 🔒 Security & Code Review Verification

To verify that `tokyo_bloodline_lite.ps1` contains no hidden binary arrays or base64 strings:

```powershell
# Verify no long base64 chunks exist in the Lite script
Select-String -Path ".\tokyo_bloodline_lite.ps1" -Pattern "[A-Za-z0-9+/=]{100,}"
```
*(The above command will return zero results, proving the script is entirely plain text).*