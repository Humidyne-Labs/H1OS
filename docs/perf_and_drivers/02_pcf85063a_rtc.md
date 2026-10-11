# NXP PCF85063A Real-Time Clock & Countdown Timer

## 1. Physical Specifications & Hardware Target
- **Manufacturer / IC:** NXP Semiconductors PCF85063A
- **Bus Interface:** Shared Master I2C (`I2C_NUM_0`)
- **7-Bit Slave Address:** `0x51` (Fixed)
- **Interrupt Output:** `GPIO 5` (`HAL_PIN_RTC_INT`), Open-Drain, Active LOW
- **Oscillator Crystal:** 32.768 kHz tuning-fork quartz crystal with **12.5 pF** internal load capacitance selection
- **Power Rail:** Permanent coin-cell / battery backup or 3.3V system rail. Continues counting throughout deep sleep and power-down.

---

## 2. Register Map & Bit Definitions

| Register Address | Name | Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0 | Default / Target Config |
|---|---|---|---|---|---|---|---|---|---|---|
| **0x00** | `Control_1` | EXT_TEST | 0 | **STOP** | SR | 0 | CIE | 12_24 | **CAP_SEL** | Target: `0x01` (STOP=0, 24h, 12.5pF) |
| **0x01** | `Control_2` | **AIE** | **AF** | MI | HMI | **TF** | **COF[2]** | **COF[1]** | **COF[0]** | Target: `0x07` (COF=7 off, flags cleared) |
| **0x02** | `Offset` | MODE | OFFSET[6:0] | Target: `0x00` |
| **0x03** | `RAM_byte` | User RAM (8-bits general storage) |
| **0x04** | `Seconds` | **OS** | SECONDS (BCD 00–59, OS: 1=oscillator stopped) |
| **0x05** | `Minutes` | 0 | MINUTES (BCD 00–59) |
| **0x06** | `Hours` | 0 | 0 | HOURS (BCD 00–23 in 24h mode) |
| **0x07** | `Days` | 0 | 0 | DAYS (BCD 01–31) |
| **0x08** | `Weekdays` | 0 | 0 | 0 | 0 | 0 | WEEKDAYS (0–6) |
| **0x09** | `Months` | 0 | 0 | 0 | MONTHS (BCD 01–12) |
| **0x0A** | `Years` | YEARS (BCD 00–99, offset from 2000) |
| **0x0B..0x0F** | `Alarm_*` | Alarm Second, Minute, Hour, Day, Weekday registers |
| **0x10** | `Timer_val` | COUNT[7:0] (Countdown value: 1–255) |
| **0x11** | `Timer_mode` | 0 | 0 | 0 | **TCF[1]** | **TCF[0]** | **TE** | **TIE** | **TI_TP** | Target: Configured on arm |

---

## 3. Critical Register Bit Operations

### Control_1 (0x00)
- **CAP_SEL (Bit 0):** `0 = 7 pF`, `1 = 12.5 pF`. **Must be set to 1** for the onboard 12.5 pF crystal to maintain timing accuracy.
- **STOP (Bit 5):** `0 = RTC divider runs`, `1 = RTC divider stopped`. Must be cleared during runtime, set temporarily when updating date/time.
- **SR (Bit 4):** Software reset. Write `0x58` to initiate full software reset.

### Control_2 (0x01)
- **COF[2:0] (Bits 2:0):** Clock Output Frequency on the CLKOUT pin.
  - `000` = 32.768 kHz
  - `111` (`0x07`) = **CLKOUT Disabled / High-Z**.
  - **MANDATORY:** Must always be `0x07`. Leaving CLKOUT active oscillates the PCB trace, continuously burning battery power through capacitive parasitic load.
- **AF (Bit 6) / TF (Bit 3):** Alarm Flag and Timer Flag. Active-1 flags that pull `GPIO 5` LOW. Cleared by writing `0` while maintaining `COF[2:0] = 0x07`.
- **AIE (Bit 7):** Alarm Interrupt Enable.

### Timer_mode (0x11)
- **TCF[1:0] (Bits 4:3):** Timer Clock Frequency prescaler.
  - `00` (`0 << 3`): 4096 Hz
  - `01` (`1 << 3`): 64 Hz
  - `10` (`2 << 3` = `0x10`): **1 Hz** (1-second tick, for countdowns 1 to 255 seconds)
  - `11` (`3 << 3` = `0x18`): **1/60 Hz** (1-minute tick, for countdowns 1 to 255 minutes = 60 to 15,300 seconds)
- **TE (Bit 2):** Timer Enable (`1 = Enabled`, `0 = Disabled`).
- **TIE (Bit 1):** Timer Interrupt Enable (`1 = Assert INT pin on timeout`).
- **TI_TP (Bit 0):** Timer Interrupt Mode (`0 = Pulse interrupt`, `1 = Level interrupt`).

---

## 4. Hardware Countdown Timer Arming Algorithm

To reliably arm the hardware countdown timer for deep sleep wakeup:
```
1. Write 0x00 to Timer_mode (0x11) to stop existing timer.
2. Clear TF and AF in Control_2 (0x01): ctrl2 = (ctrl2 & ~(AF | TF)) | 0x07 (COF_OFF).
3. If seconds <= 255:
     timer_val = (uint8_t)seconds;
     mode      = (2 << 3) | (1 << 2) | (1 << 1);  // 1Hz + TE + TIE = 0x16
   Else:
     mins      = (seconds + 59) / 60;
     if (mins > 255) mins = 255;
     timer_val = (uint8_t)mins;
     mode      = (3 << 3) | (1 << 2) | (1 << 1);  // 1/60Hz + TE + TIE = 0x1E
4. Write timer_val to Timer_val (0x10).
5. Write mode to Timer_mode (0x11).
```

---

## 5. Audit & Bug Identification Matrix

| Parameter / Register | Legacy Reference (`bsp_rtc.c`) | Original `sub_rtc.c` (Clean-Slate) | Bug Diagnosis & Required Fix |
|---|---|---|---|
| **Control_1 (0x00) CAP_SEL** | `ctrl1 |= CTRL1_CAP_SEL_12_5PF` (bit 0 = 1) | **Never configured in init!** | **FIXED:** Added `CAP_SEL` configuration in `sub_rtc_init()`. |
| **Control_2 (0x01) TIE bit** | TIE is in Reg `0x11` | Erroneously defined `#define CTRL2_TIE_MASK (1 << 2)` in Reg `0x01`! Bit 2 is `COF[2]`. | **FIXED:** Removed `CTRL2_TIE_MASK` from Control_2; `TIE` belongs exclusively to `Timer_mode` (0x11, bit 1). |
| **Timer Prescaler Bits (TCF)** | `TIMER_MODE_TCF_1HZ = (2 << 3)`<br>`TIMER_MODE_TCF_1_60HZ = (3 << 3)` | `#define TIMER_CLK_1_HZ 0x02`<br>`#define TIMER_CLK_1_60_HZ 0x03` (Unshifted!) | **FIXED:** Shifted `TCF` into bits `[4:3]` (`(2 << 3)` and `(3 << 3)`). |
| **Remaining Seconds Math** | Extracted `mode & (3 << 3)` | Read `mode & 0x03` (bits 1:0 instead of 4:3) | **FIXED:** Corrected mask to `(mode >> 3) & 0x03`. |
| **CLKOUT Disable** | `COF[2:0] = 0x07` | `ctrl2 |= 0x07` | **PASS** |
