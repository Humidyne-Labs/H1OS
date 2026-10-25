# Environmental Chamber Metrology & Qualification Test Ledger (Run #2)

**Test Campaign:** Sealed Acrylic Chamber RH Baseline & Sensor Verification (Post-Remediation Run #2)  
**Primary Standard:** 60g Boveda 69.0% Two-Way Osmotic Salt-Membrane Pack  
**Reference Benchmark:** Klaro Valet Digital Thermohygrometer (Case Elegance)  
**Device Under Test (DUT):** HUMID1 (Waveshare ESP32-S3-PICO-1-N8R8 + Sensirion SHTC3 + Solomon SSD1681 1.54" EPD)  
**DUT Test Firmware:** Commit `025373f` (`v2.4.1-dev` audit remediations AUD-01 through AUD-08)  
**Test Status:** **ABORTED AT 10.4 HOURS (Run #2, n=1) — Zero SHTC3 Telemetry Ingestion / Firmware Malfunction**  

---

## 1. Test Campaign Objectives & Chamber Setup

### Test Intent
Following the completion of the 56.4-hour board hydration soak in **Run #1** (`TST_001`), the enclosure, PCB substrate, and adhesives had achieved moisture equilibrium. Run #2 was commissioned as the formal qualification baseline on the newly hardened `v2.4.1-dev` production firmware (commit `025373f`), targeting:
1. Verification of rapid settling ($\le 2\text{ hours}$) to $68.0\% \pm 0.5\%\text{ RH}$ on the pre-hydrated board without material sorption lag.
2. Long-term verification of the AUD-01 through AUD-08 audit remediations under continuous deep-sleep cycling.
3. Establishing the stable baseline prior to the Run #3 step-response and hysteresis qualification.

### Chamber Instrumentation
* **Enclosure Type:** Heavy-wall clear acrylic canister with perimeter stainless steel clamp-lock latch.
* **Hermetic Seal:** Food-grade silicone perimeter compression gasket; non-permeable acrylic body.
* **Effective Air Volume:** ~1.4 Liters net headspace above the pre-acclimated Spanish cedar substrate.
* **Vapor Standard:** 1 × 60g Boveda 69% two-way osmotic salt-membrane pack (equilibrated).
* **Reference Benchmark:** Klaro Valet (0.1°F resolution, 1% integer RH LCD, coin-cell powered, $\le 15\ \mu\text{W}$ dissipation).
* **DUT Configuration:** HUMID1 running `v2.4.1-dev` test build, 5-minute display refresh cycle (Flow B), 60-second wake-stub sample cycle (Flow A).

---

## 2. Photographic Telemetry Ledger & Inspection

The test was initiated at 03:57 EDT on October 25, 2026, and terminated early at 14:22 EDT after 10 hours and 25 minutes of soak when telemetry confirmed zero SHTC3 data ingestion:

| Photo File | Timestamp (EDT) | Elapsed Soak | Ref Temp | Ref RH | DUT Indicated Temp | DUT Indicated RH | Indicated Vapor P | Screen / Cycle State | Diagnostic Notes |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `2026-10-25_03-57-38_154.png` | 10-25 03:57:38 | 0.00 h | 71.7°F | 69% | 32.0°F (0.0°C) | 0.0% | 0.0 hPa | Screen 1 / Cycle #1 | Initial chamber lock. Zero reading displayed immediately on boot. |
| `2026-10-25_14-17-16_856.png` | 10-25 14:17:16 | 10.33 h | 70.8°F | 69% | 32.0°F (0.0°C) | 0.0% | 0.0 hPa | Screen 1 / Cycle #124 | Chamber pre-unseal readout. Indicated telemetry static at zero throughout entire soak. |
| `2026-10-25_14-22-16_636.png` | 10-25 14:22:16 | 10.42 h | N/A | N/A | 32.0°F (0.0°C) | 0.0% | 0.0 hPa | Screen 1/4 / Cycle #125 | Post-unseal inspection on bench. Hero screen confirms `Status: SETTLING (0%)`. |
| `2026-10-25_14-22-33_453.png` | 10-25 14:22:33 | 10.42 h | N/A | N/A | Dew Point: 32.0°F | Abs H: 0.0 g/m³ | Win: 0.0/0.0°C | Screen 2/4 (Psychrometrics) | EPD Glass reads **22.5°C** (valid SPI telemetry). Conf: 0% (T:0). |
| `2026-10-25_14-22-40_231.png` | 10-25 14:22:40 | 10.42 h | N/A | N/A | MCU Die: 0.0°C | TriNode ΔT: +0.0°C | Power: 4.00V | Screen 3/4 (System Health) | VBUS connected (EXTERNAL USB). MCU Die sensor uninitialized (reads 0.0°C). |
| `2026-10-25_14-22-49_534.png` | 10-25 14:22:49 | 10.42 h | N/A | N/A | Heap: 7811K / 7765K | Stack: 4272 B HWM | Wakes: 625 (Ring: 0/32) | Screen 4/4 (OS Diagnostics) | **Critical symptom: `Ring: 0/32` after 625 wake events.** Zero ring samples logged. |

---

## 3. Subsystem Performance & Malfunction Decomposition

### Subsystems Operating Correctly (Green)
1. **ULP-RISC-V Coprocessor Execution:**
   The coprocessor operated continuously across the entire soak without crashing or trapping (`COCPU_TRAP_TRIG = 0`). It executed 625 wake events, accurately slicing the 60-second PCF85063A timer interrupts and dispatching `MAIN_WAKE` exactly every 5 slices ($625 / 5 = 125\text{ display cycles}$ over 625 minutes = 10.4 hours).
2. **E-Paper Display & SPI Interface:**
   The Solomon Systech SSD1681 1.54" display performed 125 full 5-minute refreshes cleanly without ghosting, panel lockup, or power latch drops.
3. **EPD Glass Temperature Telemetry:**
   Screen 2/4 confirmed `EPD Glass: 22.5°C`, acquired directly from the SSD1681 internal temperature sensor over SPI during panel refresh. This proves the board was physically at normal room temperature ($\approx 72.5^\circ\text{F}$) throughout the test.
4. **FreeRTOS Task Memory & Heap Integrity:**
   Screen 4/4 reported `Heap: 7811K / 7765K Min` and `Stack: 4272 B HWM`, demonstrating zero memory leaks and stable FreeRTOS task stacks under the `v2.4.1-dev` AUD-01 stack enlargement.

### Subsystems Malfunctioning (Red)
1. **Complete Loss of SHTC3 Telemetry:**
   Screen 1 displayed `32.0°F (0.0°C ambient)` and `0.0% Relative Humidity`, accompanied by `Status: SETTLING (0%)` and `Vapor P: 0.0 hPa`.
2. **Zero Ingestion into Ring Buffer (`Ring: 0/32`):**
   Despite 625 total wakes recorded in `st->wake_count`, the circular ring buffer write head remained at `0` (`st->ring_head = 0`) and `st->total_samples = 0`. Not a single environmental sample was ever pushed to `orch_state`.
3. **Cold-Boot Telemetry Blindness:**
   On initial power-on (Cycle #1), the main application OS did not execute an immediate synchronous SHTC3 I2C acquisition, initializing `st->total_samples` to `0` and relying exclusively on wake-stub background execution to populate data. Because the wake stub failed to record samples, the UI remained trapped in the default zero-state indefinitely.
4. **MCU Die Temperature Dropout:**
   Screen 3/4 showed `MCU Die: 0.0°C` and Screen 2 showed `Dew Point: 32.0°F (0.0°C)`, resulting from uninitialized fallback structs when querying an empty ring buffer.


