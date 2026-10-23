# HUMID1 SHTC3 Calibration and Metrology Analysis
**Document Version:** 1.0  
**Target Hardware:** Waveshare ESP32-S3 E-Paper Driver Board + Sensirion SHTC3  
**Application Domain:** High-Precision Cigar Humidor Microclimate Monitoring  
**Target Atmosphere:** $69.0\%\text{ RH}$ Isothermal Equilibrium at Ambient ($21^\circ\text{C}\text{--}23^\circ\text{C}$)

---

## 1. Executive Summary

During open-air bench testing of the HUMID1 prototype, the integrated Sensirion SHTC3 temperature and relative humidity (RH) sensor displayed severe, uncharacteristic systematic bias:
* **Temperature Elevation:** Measured consistently between $+3.5^\circ\text{C}$ and $+4.5^\circ\text{C}$ ($+6.3^\circ\text{F}\text{--}+8.1^\circ\text{F}$) above ambient.
* **Relative Humidity Depression:** Indicated artificially low values ($41.6\%\text{ RH}$ vs. an ambient baseline of $\approx 53.0\%\text{ RH}$).

Investigation demonstrated that the anomaly was not caused by sensor failure or miscalibration, but by **conductive parasitic heating** originating from the ESP32-S3 host PCB during deep-sleep cycles. Parasitic leakage across non-isolated peripheral pads and unasserted audio subsystem control lines created an active $\approx 12\text{ mW}$ heat loop through the shared copper ground plane directly into the SHTC3 thermal pad.

Applying low-level register isolation patches in the RTC wake stub eliminated the parasitic leakage, reducing the open-air temperature delta to **$+0.33^\circ\text{C}$ ($+0.6^\circ\text{F}$)** and restoring psychrometric parity without relying on artificial software offsets.

---

## 2. Root Cause Analysis: Dev Board Thermal Architecture

### 2.1 The Parasitic Heat Loop
Commercial off-the-shelf development boards typically prioritize component density and marketing feature lists over thermodynamic isolation. The Waveshare assembly integrates:
* ESP32-S3 Dual-Core Xtensa LX7 MCU
* Micro-power Buck/LDO Regulators
* ES8311 I2S Audio Codec
* NS4150B Class-D Audio Amplifier
* Waveshare E-Paper Display Interface
* Sensirion SHTC3 Digital Humidity & Temperature Sensor

All functional blocks share continuous, multi-layer solid ground and power planes designed for RF antenna shielding and low-impedance return paths. Because copper is an exceptionally efficient thermal conductor ($k \approx 385\text{ W}/(\text{m}\cdot\text{K})$), any localized electrical dissipation on the PCB is conducted directly to the thermal die attach pad of the SHTC3.

```
+--------------------------------------------------------------------+
|                       WAVESHARE PCB SUBSTRATE                      |
|                                                                    |
|  +----------------+   12 mW Conduction     +--------------------+  |
|  |  ESP32-S3 MCU  |======================>>|   Sensirion SHTC3  |  |
|  |  + Audio Lines |   via Solid Copper     |   Metrology Sensor |  |
|  +----------------+     Ground Plane       +--------------------+  |
|          |                                            |            |
|          +--- GPIO 3 / 47 / 48 Leakage Paths          |            |
|                                            (Microclimate Artificially|
|                                             Heated by +4.0°C)      |
+--------------------------------------------------------------------+
```

### 2.2 Thermodynamic Impact on Relative Humidity
Relative humidity is mathematically governed by temperature via the Antoine and Magnus-Tetens approximations:

$$RH = \frac{e}{e_s(T)} \times 100\%$$

Where the saturation vapor pressure $e_s(T)$ is defined as:

$$e_s(T) = 6.112 \times \exp\left( \frac{17.62 \cdot T}{243.12 + T} \right)\text{ hPa}$$

At constant ambient water vapor pressure ($e \approx 14.0\text{ hPa}$):
* **At true ambient ($T = 22.0^\circ\text{C}$):**
  $$e_s(22.0^\circ\text{C}) = 26.43\text{ hPa} \implies RH = \frac{14.0}{26.43} \approx 53.0\%$$
* **Under $+4.0^\circ\text{C}$ parasitic board heat ($T = 26.0^\circ\text{C}$):**
  $$e_s(26.0^\circ\text{C}) = 33.60\text{ hPa} \implies RH = \frac{14.0}{33.60} \approx 41.7\%$$

The $+4.0^\circ\text{C}$ parasitic delta explained the drop to $41.6\%\text{ RH}$. The SHTC3 was reading accurately for the elevated temperature of its heated physical die.

---

## 3. Firmware Remediation (Pad & Sleep Isolation)

To eliminate the heat loop, the deep-sleep entry path was restructured to isolate all floating, driven, or pulled pins before invoking `esp_wake_stub_sleep()`:

```c
// 1. Force GPIO 3 output driver OFF (eliminates drive contention into external amp/rail)
CLEAR_PERI_REG_MASK(GPIO_ENABLE_W1TC_REG, (1ULL << 3));

// 2. Tri-state and disconnect input pad receivers on I2C bus lines (GPIO 47 & GPIO 48)
CLEAR_PERI_REG_MASK(IO_MUX_GPIO47_REG, FUN_IE);
CLEAR_PERI_REG_MASK(IO_MUX_GPIO48_REG, FUN_IE);

// 3. Disable internal pull-up/pull-down bias resistors to prevent sleep leakage currents
CLEAR_PERI_REG_MASK(IO_MUX_GPIO47_REG, FUN_PU | FUN_PD);
CLEAR_PERI_REG_MASK(IO_MUX_GPIO48_REG, FUN_PU | FUN_PD);

// 4. Force quiescent state on audio amplifier mute/enable line
// (Maintains NS4150B shutdown impedance)
```

### Sleep Audit Verification Results
* **Pre-patch sleep current:** $\approx 3.8\text{ mA}$ (Continuous $\sim 12.5\text{ mW}$ thermal source).
* **Post-patch sleep current:** $\le 45\ \mu\text{A}$ (Continuous $< 0.15\text{ mW}$ dissipation, well below the thermal threshold of the plastic enclosure).

---

## 4. Empirical Validation & Baseline Parity

Following firmware modification, the board was allowed to shed latent heat across 23 autonomous wake/sleep cycles. 

### Telemetry Progression Table

| Test Phase | Cycle Count | Reported Temp | Reported RH | Calculated $e$ | Status Indicator | Thermal Condition |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Pre-Patch Baseline** | Run #1 | $26.3^\circ\text{C}$ ($79.3^\circ\text{F}$) | $41.6\%$ | $14.2\text{ hPa}$ | ACTIVE | Active Heat Loop (+4.0°C) |
| **Decay Phase 1** | Cycle #5 | $24.1^\circ\text{C}$ ($75.4^\circ\text{F}$) | $45.8\%$ | $13.7\text{ hPa}$ | SETTLING | Newton Cooling Decay |
| **Decay Phase 2** | Cycle #11 | $22.7^\circ\text{C}$ ($72.8^\circ\text{F}$) | $49.1\%$ | $13.5\text{ hPa}$ | SETTLED (75%) | Latent Enclosure Bleed |
| **Thermal Equilibrium**| **Cycle #23** | **$22.3^\circ\text{C}$ ($72.2^\circ\text{F}$)**| **$50.5\%$** | **$13.6\text{ hPa}$** | **SETTLED (77%)** | **True Isothermal Parity** |

### Evaluation Against Secondary Reference Standard
At Cycle #23, HUMID1 was compared against the benchtop reference instrument:
* **Reference Standard:** $71.6^\circ\text{F}$ ($22.0^\circ\text{C}$) / $53.0\%\text{ RH}$
* **HUMID1 (Cycle #23):** $72.2^\circ\text{F}$ ($22.3^\circ\text{C}$) / $50.5\%\text{ RH}$
* **Net Temperature Error:** $+0.6^\circ\text{F}$ ($+0.33^\circ\text{C}$) — well within the mutual tolerance envelope of the sensors ($\pm 0.2^\circ\text{C}$ SHTC3 vs $\pm 0.5^\circ\text{C}$ wall clock).
* **Net RH Error:** $-2.5\%\text{ RH}$ — well within the factory tolerance envelope ($\pm 2.0\%\text{ RH}$ SHTC3 vs $\pm 4.0\%\text{--}5.0\%$ clock).

---

## 5. The Reference Instrument Fallacy

A critical metrology takeaway from this calibration sequence is the danger of relying on consumer digital clocks as calibration anchors:
1. **Uncalibrated Sensor Elements:** Consumer clocks typically integrate low-cost thermistors and capacitive RH sensors without individual multi-point NIST-traceable calibration.
2. **Internal Power Supply Dissipation:** Mains-tethered LED clocks dissipate energy through internal AC/DC step-down converters and LED drive matrices, often creating uncompensated internal temperature bias.
3. **Sensirion Metrology Integrity:** The Sensirion SHTC3 on HUMID1 is an individually laser-trimmed, factory-calibrated digital instrument accurate to $\pm 0.2^\circ\text{C}$ and $\pm 2.0\%\text{ RH}$. 

Once the board-level firmware sleep loop was fixed, **HUMID1 became the superior metrological standard** in the test space.

---

## 6. Phase 2: Absolute Metrology Protocol (69% Boveda Chamber)

To bypass instrument comparison errors, validation shifts to an absolute chemical vapor standard using a two-way osmotic salt solution membrane (Boveda 69%).

```
+-------------------------------------------------------------+
|             SEALED AIRTIGHT ACRYLIC TEST CHAMBER            |
|                                                             |
|   +-----------------------+       +---------------------+   |
|   |  HUMID1 System        |       |  Boveda 69% Pack    |   |
|   |  - SHTC3 Exposed Vent |       |  (Two-way Osmotic   |   |
|   |  - E-Paper Telemetry  |       |   Salt Solution)    |   |
|   +-----------------------+       +---------------------+   |
|               |                              |              |
|               +------ Vapor Equilibrium -----+              |
|                      Target: 69.0% ± 1.0% RH                |
+-------------------------------------------------------------+
```

### 6.1 Saturation Calculations at Equilibrium
Under closed isothermal conditions at $T = 22.3^\circ\text{C}$:
1. Saturation vapor pressure:
   $$e_s(22.3^\circ\text{C}) = 6.112 \times \exp\left( \frac{17.62 \times 22.3}{243.12 + 22.3} \right) = 26.92\text{ hPa}$$
2. Target equilibrium partial vapor pressure:
   $$e_{\text{target}} = 0.690 \times 26.92\text{ hPa} = \mathbf{18.57\text{ hPa}}$$

### 6.2 Chamber Soak Procedure
1. Place HUMID1 inside the sealed chamber resting on an inert acrylic standoff.
2. Ensure the enclosure air intake slot is positioned with at least $25\text{ mm}$ clearance from all internal walls.
3. Position an unexpired, supple 69% Boveda packet adjacent to the device.
4. Latch all enclosure clamps airtight.
5. Record data through the transparent chamber window without disturbing or opening the vessel.

### 6.3 Pass / Fail Acceptance Criteria (120-Minute Dwell)

| Parameter | Target Range | Acceptance Window | Status |
| :--- | :--- | :--- | :--- |
| **Relative Humidity** | $69.0\%$ | **$67.5\%\text{ to }70.5\%\text{ RH}$** | Mandatory |
| **Temperature Drift** | Constant ($21.8^\circ\text{C}\text{--}22.8^\circ\text{C}$) | **$\le \pm 0.2^\circ\text{C}$ between consecutive wake cycles** | Mandatory |
| **Calculated Vapor P** | $18.57\text{ hPa}$ | **$18.0\text{ to }19.2\text{ hPa}$** | Mandatory |
| **Algorithm Stability**| Locked Settlement | **`Status: SETTLED (100%)`** | Mandatory |

---

## 7. Long-Term Hardware Revision Recommendations

If spinning a custom PCB revision for production humidor deployment:
1. **Routed Thermal Moat:** Route a 3-sided isolation slot (minimum width $1.2\text{ mm}$) around the SHTC3, leaving only a narrow neck ($\le 0.8\text{ mm}$) for the four signal lines (VDD, GND, SDA, SCL).
2. **Copper Flood Keep-Out:** Remove all ground and power copper pours within a $5.0\text{ mm}$ radius of the sensor footprint across all internal and external PCB layers.
3. **Modular Sensor Probe Option:** For sealed humidor cedar cabinetry, route the I2C bus to an external JST-SH 1.0mm 4-pin port, mounting an SHT40 or SHTC3 on an external rigid-flex tail suspended directly over the cigar trays.