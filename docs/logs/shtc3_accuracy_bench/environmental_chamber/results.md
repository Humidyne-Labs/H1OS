# Environmental Chamber & Instrumentation Setup

### Chamber Specifications & Dynamics
* **Enclosure Type:** Heavy-wall clear acrylic humidor canister with stainless steel clamp-lock latch.
* **Hermetic Seal:** Food-grade silicone perimeter compression gasket; non-permeable acrylic body (zero vapor loss through chamber walls).
* **Physical Dimensions:** External: 8.1" H × 4.0" Dia (4.3" D with clamp mechanism). Internal usable: ~7.5" H × ~3.75" Dia.
* **Effective Air Volume:** ~1.4 Liters (~83 cu in) net air volume above the cedar disc.
* **Internal Substrate:** Removable Spanish cedar disc at base.
* **Vapor Standard:** 1 × 60g Boveda 69% two-way osmotic salt-membrane pack (freshly hydrated, nominal factory stability $\pm 1.0\%\text{ RH}$ at $20^\circ\text{C}\text{--}25^\circ\text{C}$).
* **Vapor Load Ratio:** 60g pack servicing ~1.4 L headspace (substantially over-buffered for rapid, uniform diffusion).
* **Auxiliary Display:** Built-in mechanical dial hygrometer (uncalibrated; ignored for metrology).

### Reference & Test Instruments

* **Secondary Calibration Benchmark:** [Klaro Valet (Case Elegance)](https://caseelegance.com/products/klaro-valet)[subscription😞](https://caseelegance.com/products/klaro-app-only-subscription)
  * *Metrological Profile:* Purpose-built humidor digital thermohygrometer; high-stability capacitive sensor element tuned for narrow-band equilibration ($60\%\text{--}75\%\text{ RH}$).
  * *Thermal Footprint:* Micro-power coin cell architecture; negligible internal power dissipation ($\le 15\ \mu\text{W}$ quiescent), ensuring zero self-heating interference within small, stagnant air volumes.
  * *Function in Protocol:* Provides traceable secondary validation alongside the primary Boveda 69% osmotic vapor standard.

* **Device Under Test (DUT):** HUMID1 (Waveshare ESP32-S3 + Sensirion SHTC3)
  * *Firmware Profile:* Audited `orch_wake_stub.c` utilizing deep-sleep pad isolation (GPIO 3 tri-stated, GPIO 47/48 isolated) to eliminate PCB ground-plane thermal conduction.
  * *Display & UI:* 200×200 1-bit bi-tonal EPD with persistent status metrics (`Status: SETTLED`, psychrometric Vapor Pressure calculations).

# Validation Protocol & Metrology Gates

### 1. Initial State Baseline

* **DUT Open-Air Settled Baseline:** $72.2^\circ\text{F}$ ($22.3^\circ\text{C}$), $50.5\%\text{ RH}$, $13.6\text{ hPa}$ vapor pressure.
* **Klaro Valet Baseline:** ~~Log open-air temperature and RH immediately prior to securing the clasp.~~ Klaro Valet was removed from a low humidity environment prior to testing, $72.2^\circ\text{F}$ ($22.3^\circ\text{C}$), $64.0\%\text{ RH}$.

### 2. Chamber Soak Telemetry Log

| Timestamp    | Phase                | Klaro Valet (Ref) | HUMID1 SHTC3 (DUT) | Net $\Delta$ | Status / Phase Target                     |
|:------------ |:-------------------- |:----------------- |:------------------ |:------------ |:----------------------------------------- |
| **08:50 PM** | Chamber Latch (T+0)  | ___°F / ___%      | 72.2°F / 50.5%     | —            | Gasket compressed, clasp locked           |
| **09:20 PM** | Inflection (T+30m)   | ___°F / ___%      | ___°F / ___%       | —            | RH rising past $60.0\%$                   |
| **09:50 PM** | Intermediate (T+60m) | ___°F / ___%      | ___°F / ___%       | —            | RH approaching $65.0\%\text{--}67.0\%$    |
| **10:50 PM** | Equilibrium (T+120m) | ___°F / ___%      | ___°F / ___%       | —            | Target: $67.5\%\text{--}70.5\%\text{ RH}$ |

---

# Results

### Equilibrium Telemetry (Post-120 Min Soak)

* **DUT Temperature ($T_{\text{DUT}}$):** `[ Pending 10:50 PM log ]`
* **DUT Indicated RH ($\%RH_{\text{DUT}}$):** `[ Pending 10:50 PM log ]`
* **DUT Vapor Pressure ($e_{\text{DUT}}$):** `[ Pending 10:50 PM log ]`
* **Klaro Valet Ref ($T_{\text{ref}} / \%RH_{\text{ref}}$):** `[ Pending 10:50 PM log ]`

### Metrological Acceptance Criteria

1. **RH Saturation Target:** SHTC3 indicated relative humidity settles between **$67.5\%$ and $70.5\%\text{ RH}$** ($\pm 1.5\%\text{ to }\pm 2.0\%$ Sensirion factory tolerance centered on the $69.0\%$ Boveda pack).
2. **Parasitic Heat Confinement Check:** In an airtight, non-ventilated acrylic container with low thermal conductivity, any unmitigated board dissipation will rapidly trap heat. Internal temperature must hold steady ($\Delta T \le 0.15^\circ\text{C}$ between consecutive wake cycles), confirming the deep-sleep pad isolation holds without thermal runaway in a dead air space.
3. **Equilibrium Vapor Pressure:** At $72.0^\circ\text{F}\text{--}72.5^\circ\text{F}$ ($22.2^\circ\text{C}\text{--}22.5^\circ\text{C}$) and $69.0\%\text{ RH}$, indicated vapor pressure must report **$18.5\text{ to }18.8\text{ hPa}$**.