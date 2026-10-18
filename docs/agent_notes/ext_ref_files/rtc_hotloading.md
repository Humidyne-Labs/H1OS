Rearming the PCF85063A external RTC requires resetting its internal latching interrupt flags via $\text{I}^2\text{C}$ transactions to register `Control_2` (`0x01`) and correctly handling the countdown timer or calendar alarm registers.

---

### 1. Register Architecture: `Control_2` (`0x01`)

The $\overline{\text{INT}}$ pin (Pin 3/4) is an open-drain output tied to the internal flags inside `Control_2` (`0x01`):

| Bit | Name | Type | Reset | Function & Flag Behavior |
| --- | --- | --- | --- | --- |
| **Bit 7** | `AIE` | R/W | 0 | **Alarm Interrupt Enable:** $0 =$ disabled, $1 =$ asserts $\overline{\text{INT}}$ when `AF` is set.

 |
| **Bit 6** | `AF` | R/W (AND) | 0 | **Alarm Flag:** Sets to $1$ on calendar match. **Write $0$ to clear; write $1$ leaves unchanged**.

 |
| **Bit 5** | `MI` | R/W | 0 | **Minute Interrupt Enable:** Generates periodic 1/64 s pulses every minute.

 |
| **Bit 4** | `HMI` | R/W | 0 | **Half-Minute Interrupt Enable:** Generates periodic 1/64 s pulses every 30 s.

 |
| **Bit 3** | `TF` | R/W (AND) | 0 | **Timer Flag:** Sets to $1$ when countdown finishes. **Write $0$ to clear; write $1$ leaves unchanged**.

 |
| **Bit 2:0** | `COF[2:0]` | R/W | 000 | **CLKOUT Control:** Configures frequency on the CLKOUT pin ($111 =$ high-Z / off).

 |

#### Hardware Logic AND on Writes

The flag bits `AF` (bit 6) and `TF` (bit 3) implement **logic AND** filtering on incoming $\text{I}^2\text{C}$ write data:

$$\text{New Flag State} = \text{Current Flag State} \ \text{AND} \ \text{Written Bit Value}$$

* Writing a `0` clears the flag to `0`.

* Writing a `1` leaves the flag unchanged (does not accidentally set or reset it).

* **Risk:** Bits 7, 5, 4, and 2:0 are standard R/W configuration registers. Writing raw `0x00` to `0x01` clears the flags, but it also disables `AIE`, `MI`, and `HMI`, while resetting `COF` to `000` (which turns CLKOUT ON at 32.768 kHz, increasing current draw).

---

### 2. Rearming the Countdown Timer Engine

The countdown timer operation is dictated by the `TI_TP` bit (bit 0) in `Timer_mode` (`0x11`).

```
                +-----------------------------------------------------+
                | PCF85063A Countdown Timer Engine                    |
                |                                                     |
                | Counter reaches 0x00                                |
                |       │                                             |
                |       ├───> TF (Bit 3, 0x01) latches HIGH           |
                |       │                                             |
                +───────┼─────────────────────────────────────────────+
                        │
         Is TI_TP = 0 or TI_TP = 1?
         /                      \
   [TI_TP = 0 (Level)]      [TI_TP = 1 (Pulsed)]
        │                                │
  /INT clamps LOW                  /INT pulses LOW for 1/64 s,
  Timer HALTS                      then self-releases HIGH.
        │                          Timer auto-reloads & runs.
  Must clear TF via I2C                  │
  to release line & restart.       TF stays 1 until cleared
                                   (rearm needed only for polling).

```

#### Case A: Level Interrupt Mode (`TI_TP = 0` in `0x11`)

1. **Behavior:** When `Timer_value` decrements from `0x01` to `0x00`, `TF` is set to `1` and $\overline{\text{INT}}$ clamps LOW indefinitely.

2. **Deadlock condition:** If `TF` is not cleared before the next timer interval, **the timer stops permanently** and will not generate subsequent ticks.

3. **Rearm sequence:**
* Read register `0x01`.

* Mask bit 3 to `0` while retaining `AIE`, `MI`, `HMI`, and `COF`:

$$\text{Write Value} = (\text{Read Value} \ \& \ \text{0xF7})$$

* Write this byte back to `0x01`.

* The $\overline{\text{INT}}$ line releases HIGH, and the countdown timer reloads and starts counting.

#### Case B: Periodic Pulsed Mode (`TI_TP = 1` in `0x11`)

1. **Behavior:** The countdown counter automatically reloads and continues in an unbroken loop. $\overline{\text{INT}}$ produces a fixed pulse width (1/64 s $\approx 15.6\ \text{ms}$ for 1 Hz clocking) and returns HIGH on its own.

2. **Rearm condition:** Hardware interrupts continue generating pulses even if `TF` remains `1`. Rearming is only necessary if your firmware polls `TF` or if changing the countdown interval on the fly.

3. **Dynamic Re-Configuration Sequence:**
* Disable the timer first by clearing `TE` (bit 2) in `Timer_mode` (`0x11`):
```c
// Stop timer to prevent intermediate race periods
i2c_write_reg(0x51, 0x11, current_timer_mode & ~0x04);

```

* Write the new countdown count to `Timer_value` (`0x10`).

* Re-enable `TE` (bit 2 = 1) in `Timer_mode` (`0x11`).

---

### 3. Rearming the Calendar Alarm Engine

The calendar alarm checks `Second_alarm` (`0x0B`) through `Weekday_alarm` (`0x0F`) against the real-time registers. When all enabled fields match, `AF` (bit 6 of `Control_2`) asserts and clamps $\overline{\text{INT}}$ LOW.

```
  Current Time matches Alarm Registers (0x0B - 0x0F)
                         │
                         ▼
             AF (Bit 6, Reg 0x01) = 1
                         │
                         ▼
               /INT Line Clamped LOW
                         │
                         ▼
        Rearm: Write Byte to Reg 0x01 with Bit 6 = 0
                         │
                         ▼
    /INT Line Released HIGH -> Ready for Next Match

```

#### Step-by-Step Rearm Procedure:

1. **Clear `AF` to release the line:**
* Read `0x01`.

* Clear bit 6:

$$\text{Write Value} = (\text{Read Value} \ \& \ \text{0xBF})$$

* Write back to `0x01`. The open-drain output releases and returns to $V_{DD}$ via the external pull-up resistor.

2. **Preventing Double-Trigger Glitches:**
* If an alarm fires at `Second = 00`, and `AF` is cleared at `Second = 00.2`, the RTC match logic will immediately re-assert `AF = 1` because the second counter has not advanced.

* **Mitigation:** Update the next alarm target register (e.g., set `Minute_alarm` or `Second_alarm` to the subsequent target time) **before** clearing `AF`, or disable matching (`AEN_x = 1`) during the transaction.

---

### 4. Implementation Example ($\text{I}^2\text{C}$ Driver C Snippet)

```c
#define PCF85063A_I2C_ADDR      0x51
#define REG_CONTROL_2           0x01
#define CTRL2_AF_MASK           (1 << 6)
#define CTRL2_TF_MASK           (1 << 3)

/**
 * @brief Rearms both Timer and Calendar Alarm flags without corrupting CLKOUT or enables.
 */
esp_err_t pcf85063a_rearm_interrupts(void)
{
    uint8_t ctrl2 = 0;
    esp_err_t err;

    // 1. Read current control 2 configuration
    err = i2c_master_read_register(PCF85063A_I2C_ADDR, REG_CONTROL_2, &ctrl2);
    if (err != ESP_OK) return err;

    // 2. Clear both AF (bit 6) and TF (bit 3) via logic 0
    // Hardware AND logic clears the asserted flags while preserving configuration
    ctrl2 &= ~(CTRL2_AF_MASK | CTRL2_TF_MASK);

    // 3. Write back cleared mask
    return i2c_master_write_register(PCF85063A_I2C_ADDR, REG_CONTROL_2, ctrl2);
}

```

---

### Immediate Verification Checklist

1. **Verify Line State Post-Rearm:**
* Read the voltage on GPIO 5 / $\overline{\text{INT}}$ using a multimeter or scope.
* If $\overline{\text{INT}}$ remains at $0\ \text{V}$ after writing, either `AF`/`TF` was not cleared, or a matching alarm condition is continuously validating.

2. **Read Back `Control_2` (`0x01`):**
* Perform an $\text{I}^2\text{C}$ read of register `0x01` immediately following the write.

* Confirm bits 6 and 3 return `0`.

3. **Verify Open-Drain Pull-Up:**
* Verify an external pull-up resistor ($4.7\ \text{k}\Omega$ to $10\ \text{k}\Omega$) is physically present between $\overline{\text{INT}}$ and $V_{DD}$, as the pin cannot pull itself HIGH.

---

You can physically write a new value $T$ into `Timer_value` (`0x10`) while the countdown timer is actively running in pulse mode (`TI_TP = 1`), and the RTC accepts it immediately; however, **NXP explicitly cautions against doing so** due to internal asynchronous clock-domain hazards.

---

### What Happens Internally During a Hot Load

The countdown counter inside the PCF85063A reloads its internal working counter from the `Timer_value` register (`0x10`).

* **Immediate Effect:** If a new value is written to `0x10` before the current countdown cycle completes, the new value takes immediate effect in the hardware.

* **Asynchronous Clock-Domain Race:** The $\text{I}^2\text{C}$ bus clock ($\text{SCL}$, up to 400 kHz) is completely asynchronous to the internal timer source clock (4.096 kHz, 64 Hz, 1 Hz, or 1/60 Hz).

* **Potential Counter Corruption:** If an internal timer clock tick occurs at the exact moment the parallel latch is loading the new value from the $\text{I}^2\text{C}$ buffer, intermediate bit-switching can cause a **corrupted/indeterminate value** to latch into the internal down-counter.

* **Scope of Impact:**
* The corruption **only affects the first (current) period**.

* The register `Timer_value` (`0x10`) stores the value correctly. Once the first period reaches zero, all **subsequent periods automatically reload cleanly** with your target value.

---

### Hot Load vs. Disable-First Sequence

Depending on how tolerant your system is of a glitch on that first transition, choose between two approaches:

#### Option 1: Direct Hot Load (Tolerates First-Cycle Glitch)

If your firmware is simply shifting between two steady-state pacing intervals and can tolerate an unpredictable interval for a single tick:

1. Write the new count $T$ ($1 \text{ to } 255$) directly to `0x10` over $\text{I}^2\text{C}$.


2. The timer counter updates immediately. The current period may fire early or late, but starting with the second pulse, ticks will strictly adhere to the new period.

#### Option 2: The Recommended Clean Update (Deterministic Timing)

To prevent counter bit corruption and ensure deterministic period lengths, disable the counter momentarily:

```
  Current Period Running (TE = 1)
                │
                ▼
  1. I2C Write to Timer_mode (0x11): Clear TE bit (TE = 0)
                │
                ▼
  2. I2C Write to Timer_value (0x10): Set new T (e.g., 0x05)
                │
                ▼
  3. I2C Write to Timer_mode (0x11): Set TE bit (TE = 1)
                │
                ▼
  Timer starts counting down cleanly with zero risk of bit corruption.

```

```c
// Example: Safely update timer countdown value to 10 ticks
uint8_t timer_mode_val = 0x17; // 1 Hz, TE=1, TIE=1, TI_TP=1

// Step 1: Temporarily clear TE (bit 2) while keeping TCF, TIE, and TI_TP
i2c_write_reg(0x51, 0x11, timer_mode_val & ~0x04);

// Step 2: Write new countdown target
i2c_write_reg(0x51, 0x10, 10);

// Step 3: Re-enable timer (TE = 1)
i2c_write_reg(0x51, 0x11, timer_mode_val);

```

---

### Verification Step

* **Logic Analyzer / Scope Check:** Probe the $\overline{\text{INT}}$ pin when changing intervals.
* If hot-loading directly, check whether the time $\Delta t$ between the write transaction and the subsequent low pulse deviates from your expected timing. If you observe random truncated pulses or extra-long intervals on the transition tick, switch to the 3-step sequence (`TE=0` $\rightarrow$ `T=new` $\rightarrow$ `TE=1`).