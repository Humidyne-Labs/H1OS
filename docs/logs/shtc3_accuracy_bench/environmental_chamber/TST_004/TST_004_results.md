
# Environmental Chamber Metrology & Qualification Test Ledger (Run #4)

**Test Campaign:** Sealed Acrylic Chamber RH Baseline & Sensor Qualification (Post-Remediation Run #4)  
**Primary Standard:** 60g Boveda 69.0% Two-Way Osmotic Salt-Membrane Pack  
**Reference Benchmark:** Klaro Valet Digital Thermohygrometer (Case Elegance)  
**Device Under Test (DUT):** HUMID1 (Waveshare ESP32-S3-PICO-1-N8R8 + Sensirion SHTC3 + Solomon SSD1681 1.54" EPD)  
**DUT Test Firmware:** Commit `xxx` / Release bundle `h1os-v2.4.5-bundle.zip` (compiled under production profile `-O2`)  
**DUT Build Profile:** Production Release (`profiles/sdkconfig.defaults.prod`: `-O2`, silent assertions, WARN log level)  
**Test Status:** **ABORTED**  

---

## 1. Chamber Specifications & Instrumentation Setup

### Chamber Dynamics
* **Enclosure Type:** Heavy-wall clear acrylic canister with perimeter stainless steel clamp-lock latch.
* **Hermetic Seal:** Food-grade silicone perimeter compression gasket; non-permeable acrylic body.
* **Effective Air Volume:** ~1.4 Liters net headspace above the pre-acclimated Spanish cedar substrate.
* **Vapor Standard:** 1 × 60g Boveda 69% two-way osmotic salt-membrane pack (equilibrated).
* **Reference Benchmark:** Klaro Valet (0.1°F resolution, 1% integer RH LCD, coin-cell powered, $\le 15\ \mu\text{W}$ dissipation).
* **DUT Configuration:** HUMID1 running `v2.4.5-dev` compiled under production profile (`sdkconfig.defaults.prod`), 5-minute display refresh cycle (Flow B), 60-second wake-stub sample cycle (Flow A).

---

## Results

### Runtime Failure

DUT **FAILED** to wake due to an issue with uncleared interrupt flags. Please see followup tests for more conclusive runtime sampling. Thank you for your attention in-regards to this failure. 
