# Technical Note: Chamber RH Delta & Equilibrium Analysis

**Test Setup:** Sealed chamber test with a $69\%$ nominal Boveda salt pack  
**Devices Under Test (DUT):** Humidyne Labs custom monitor (Sensirion SHTC3, polycarbonate enclosure) vs. Klaro Valet reference hygrometer  
**Duration Analyzed:** $17\text{ hr } 37\text{ min}$ (Cycle #25 to Cycle #234)

---

## 1. Observed Test Data

| Timestamp / Cycle | DUT Temp | Ref Temp | DUT RH | Ref RH | $\Delta\text{RH}$ | Notes |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **02:02 AM** (#25) | $72.7^\circ\text{F}$ | $72.3^\circ\text{F}$ | $50.7\%$ | $63.0\%$ | $-12.3\%$ | Initial stabilization phase |
| **07:05 AM** (#85) | $72.0^\circ\text{F}$ | $72.1^\circ\text{F}$ | $64.3\%$ | $67.0\%$ | $-2.7\%$ | Active inward diffusion / sorption |
| **07:39 PM** (#234)| $71.7^\circ\text{F}$ | $71.7^\circ\text{F}$ | $66.8\%$ | $69.0\%$ | $-2.2\%$ | Zero thermal delta ($0.0^\circ\text{F}$) |

---

## 2. Why Enclosure Venting Does Not Explain the Persistent Delta

While restrictive enclosure slot geometry induces **transient diffusion lag**, it cannot physically maintain a static concentration difference in a closed, steady-state environment:

* **Fick’s First Law of Diffusion:**
  $$J = -D \frac{dC}{dx}$$
  In stagnant air, water vapor has a diffusion coefficient of $D \approx 0.25\text{ cm}^2/\text{s}$. Across a vent path spanning several millimeters, concentration gradients ($dC/dx$) equalize via molecular diffusion within an hour.
* **Conservation of Mass:** In a sealed isothermal vessel, passive mechanical geometry cannot maintain a permanent $2\%$ to $3\%$ lower partial pressure of water vapor without an active moisture sink or chemical reaction continuously consuming vapor inside the housing.

---

## 3. Primary Drivers of the Remaining $\sim 2.2\%$ Delta

### A. Hygroscopic Material Sinks (Internal Dead-Volume Sorption)
While the outer enclosure is molded/machined from **polycarbonate** (which exhibits negligible moisture absorption of $<0.2\%$), the internal cavity contains hygroscopic materials:
* **FR4 PCB Laminate:** The epoxy-glass matrix exhibits very slow moisture diffusion ($D \approx 10^{-8}\text{ to } 10^{-9}\text{ cm}^2/\text{s}$). Full core saturation across a standard $1.6\text{ mm}$ board takes multiple days.
* **Internal Components:** E-paper display carrier tape, adhesive layers, soldermask, and battery jacketing continuously draw water vapor out of the internal air pocket until bulk equilibrium is reached.

Between 07:05 AM ($64.3\%$) and 07:39 PM ($66.8\%$), the DUT gained $+2.5\%$ RH despite an identical external temperature, confirming that the internal cavity had not yet reached its asymptotic plateau.

### B. Hardware Tolerance Stacking
The $2.2\%$ delta falls squarely within nominal production tolerances:
* **Sensirion SHTC3 Specification:** $\pm 2.0\%\text{ RH}$ typical accuracy across the $20\%\text{ to } 80\%$ band.
* **Klaro Valet Reference:** Commercial consumer hygrometers carry typical limits of $\pm 2.0\%\text{ to }\pm 3.0\%\text{ RH}$.

If the true chamber ambient held by the $69\%$ pack is $68.0\%\text{ RH}$:
* **DUT Reading ($66.8\%$):** $-1.2\%\text{ RH}$ error (within spec)
* **Klaro Reading ($69.0\%$):** $+1.0\%\text{ RH}$ error (within spec)

### C. Localized Micro-Thermal Die Dissipation
Calculated relative humidity is inversely proportional to temperature through the saturation vapor pressure $e_s(T)$ governed by the Clausius-Clapeyron relation:

$$\Delta\text{RH} \approx -\text{RH} \times \left( \frac{L_v}{R_v T^2} \right) \Delta T$$

At $22.0^\circ\text{C}$ ($71.7^\circ\text{F}$) and $\sim 68\%\text{ RH}$:
* A die temperature rise of only $\Delta T = +0.3^\circ\text{C}$ ($+0.54^\circ\text{F}$) depresses the calculated RH by approximately **$-1.8\%\text{ to }-2.0\%\text{ RH}$**.
* Even though both display panels register an identical $71.7^\circ\text{F}$ due to display rounding and ambient probe placement, minor localized heat dissipation on the ground plane during I2C sampling or MCU wake bursts can depress the SHTC3 measurement without showing on the rounded tenth-degree display.

---

## 4. Conclusion & Next Steps

1. **Leave Vent Geometry Unchanged:** Modifying slot size will accelerate initial ramp rates during the first 2 hours, but will not change the steady-state asymptote.
2. **Extended Undisturbed Soak:** Allow the chamber to soak for another 24 to 48 hours without opening.
   * If the DUT continues creeping toward $\sim 68.5\%$, the delta was purely internal dead-volume sorption lag.
   * If the DUT plateaus firmly at $\sim 67.0\%$, the difference is accounted for by factory sensor tolerance stacking and sub-tenth micro-thermal die offsets.