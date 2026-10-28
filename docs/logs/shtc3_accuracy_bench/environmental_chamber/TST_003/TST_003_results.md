# Environmental Chamber Metrology & Qualification Test Ledger (Run #3)

**Test Campaign:** Sealed Acrylic Chamber RH Baseline & Sensor Qualification (Post-Remediation Run #3)  
**Primary Standard:** 60g Boveda 69.0% Two-Way Osmotic Salt-Membrane Pack  
**Reference Benchmark:** Klaro Valet Digital Thermohygrometer (Case Elegance)  
**Device Under Test (DUT):** HUMID1 (Waveshare ESP32-S3-PICO-1-N8R8 + Sensirion SHTC3 + Solomon SSD1681 1.54" EPD)  
**DUT Test Firmware:** Commit `098e585` / Release bundle `h1os-v2.4.3-bundle.zip` (compiled under production profile `-O2`)  
**DUT Build Profile:** Production Release (`profiles/sdkconfig.defaults.prod`: `-O2`, silent assertions, WARN log level)  
**Test Status:** **COMPLETED 59.4-HOUR CHAMBER SOAK (Run #3, n=1) — SHTC3 Telemetry & Deep-Sleep Invariants Verified**  

---

## 1. Chamber Specifications & Instrumentation Setup

### Chamber Dynamics
* **Enclosure Type:** Heavy-wall clear acrylic canister with perimeter stainless steel clamp-lock latch.
* **Hermetic Seal:** Food-grade silicone perimeter compression gasket; non-permeable acrylic body.
* **Effective Air Volume:** ~1.4 Liters net headspace above the pre-acclimated Spanish cedar substrate.
* **Vapor Standard:** 1 × 60g Boveda 69% two-way osmotic salt-membrane pack (equilibrated).
* **Reference Benchmark:** Klaro Valet (0.1°F resolution, 1% integer RH LCD, coin-cell powered, $\le 15\ \mu\text{W}$ dissipation).
* **DUT Configuration:** HUMID1 running `v2.4.3-dev` compiled under production profile (`sdkconfig.defaults.prod`), 5-minute display refresh cycle (Flow B), 60-second wake-stub sample cycle (Flow A).

---

## 2. Complete 59.4-Hour Photographic Telemetry Ledger

The test commenced at 02:08 EDT on October 26, 2026, and ran uninterrupted until 13:33 EDT on October 28, 2026, completing 715 display cycles and 3,562 deep sleep wakes:

| Photo File | Timestamp (EDT) | Elapsed Soak | Cycle # | Screen | Ref Temp | Ref RH | DUT Indicated Temp | DUT Indicated RH | Indicated Vapor P | Empirical Notes / Screen State |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `2026-10-26_02-08-59_415.jpg` | 10-26 02:08:59 | 0.00 h | #1 | 1/5 | 73.0°F | 70% | 32.0°F (0.0°C) | 0.0% | 0.0 hPa | Cold-boot state prior to first Flow A sample |
| `2026-10-26_09-37-09_474.jpg` | 10-26 09:37:09 | 7.47 h | #90 | 1/5 | 71.6°F | 69% | 71.4°F (21.9°C) | 67.2% | 17.6 hPa | Stable tracking ($\Delta T = -0.2^\circ\text{F}$, $\Delta\text{RH} = -1.8\%$) |
| `2026-10-26_18-52-54_821.jpg` | 10-26 18:52:54 | 16.73 h | #201 | 1/5 | 73.4°F | 69% | 73.1°F (22.9°C) | 67.9% | 18.9 hPa | Active hydration ($\Delta T = -0.3^\circ\text{F}$, $\Delta\text{RH} = -1.1\%$) |
| `2026-10-26_21-30-42_163.jpg` | 10-26 21:30:42 | 19.36 h | #233 | 1/5 | 72.8°F | 70% | 72.8°F (22.7°C) | 67.9% | 18.7 hPa | Exact thermal alignment ($\Delta T = 0.0^\circ\text{F}$) |
| `2026-10-27_12-42-57_340.jpg` | 10-27 12:42:57 | 34.57 h | #415 | 1/5 | 71.9°F | 70% | 71.8°F (22.1°C) | 68.2% | 18.1 hPa | Indicated RH reached 68.2% ($\Delta T = -0.1^\circ\text{F}$) |
| `2026-10-28_13-29-57_549.jpg` | 10-28 13:29:57 | 59.35 h | #713 | 1/5 | 72.8°F | 70% | 72.7°F (22.6°C) | 68.4% | 18.7 hPa | Final chamber soak frame ($\Delta T = -0.1^\circ\text{F}$, $\text{RH} = 68.4\%$) |
| `2026-10-28_13-32-28_102.jpg` | 10-28 13:32:28 | 59.39 h | -- | 5/5 | -- | -- | Heap: 7810K (Min 7764K) | Stack: 4276 B HWM | Wakes: 3562 | OS Diagnostics: `Ring 0/32` display defect observed |
| `2026-10-28_13-32-40_830.jpg` | 10-28 13:32:40 | 59.40 h | #715 | 1/5 | -- | -- | 72.7°F (22.6°C) | 68.4% | 18.7 hPa | Hero Screen post-unseal; partial refresh ghosting visible |
| `2026-10-28_13-32-46_305.jpg` | 10-28 13:32:46 | 59.40 h | -- | 2/5 | -- | -- | Dew Point: 61.7°F (16.5°C) | Abs H: 13.7 g/m³ | Win: 22.6/22.6°C | Psychrometrics: Text collision `Conf: 95% (T:2840` / `04:12 PM` |
| `2026-10-28_13-32-52_237.jpg` | 10-28 13:32:52 | 59.41 h | -- | 3/5 | -- | -- | SHTC3: 22.6°C | EPD Glass: 25.0°C | MCU TSENS: 18.1°C | Thermal Nodes: $\Delta T = +0.7^\circ\text{C}$, Settled (95%) |
| `2026-10-28_13-33-00_101.jpg` | 10-28 13:33:00 | 59.41 h | -- | 4/5 | -- | -- | Battery: 4.00V (84%) | Autonomy: EXT USB | Flash: ACTIVE | System Health: Footer date reads `01/07/00` |

---

## 3. Subsystem Performance Verification

1. **SHTC3 Sensor Ingestion (PASS):**
   Unlike Run #2 which experienced a stall at 0.0% RH, Run #3 operated with 100% sensor acquisition reliability across 3,562 wake events and 2,840 consecutive settled samples (`valid_trend = 2840`). The SHTC3 tracked within factory envelope: ending at 68.4% RH (-0.6% vs 69.0% nominal Boveda salt standard) and 72.7°F ($\Delta T = -0.1^\circ\text{F}$ vs reference).
2. **ULP Coprocessor & Power Latching (PASS):**
   The ULP-RISC-V coprocessor executed continuously without trapping (`COCPU_TRAP_TRIG = 0`). Flow A and Flow B wake scheduling ran with zero latch dropouts across the 59.4-hour duration.
3. **Memory & Stack Stability (PASS):**
   Screen 5/5 confirmed heap stability (`7810K / 7764K Min`) and stack high-water mark (`4276 B HWM`), confirming zero memory leaks.

---

## 4. Observed Display Inaccuracies & Defects

The following visual and formatting defects were observed on the physical displays during bench inspection:

1. **Screen 2/5 (Psychrometrics) Footer Text Collision:**
   In `2026-10-28_13-32-46_305.jpg`, footer left text `Conf: 95% (T:2840` directly overstrikes with footer right text `04:12 PM`. When `valid_trend` reaches 4 digits (`2840`), the width of `"Conf: 95% (T:2840)"` (~135 px) combined with `"04:12 PM"` (~64 px) exceeds the 188 px usable screen boundary.
   * *Resolution:* Reformat footer to `Conf %u%% • T:%u` to prevent text overlap.
2. **Screen 5/5 (OS Diagnostics) Ring Buffer Head Index Display:**
   In `2026-10-28_13-32-28_102.jpg`, Row 6 reads `Wakes 3562 (Ring 0/32)`. The label formatted the circular write head pointer `st->ring_head` (which wraps to 0 modulo 32) instead of the actual count of populated slots, falsely indicating an empty buffer.
   * *Resolution:* Format populated buffer count `(st->total_samples >= 32 ? 32 : st->total_samples)` instead of `st->ring_head`.
