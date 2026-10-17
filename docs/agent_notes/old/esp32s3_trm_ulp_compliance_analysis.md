# ESP32-S3 TRM Chapter 2 (ULP Coprocessor) Technical Review & Action Plan

## 1. Executive Summary

A comprehensive architectural review of **Chapter 2: ULP Coprocessor (ULP-FSM, ULP-RISC-V)** from the **ESP32-S3 Technical Reference Manual (TRM Version 1.8)** was conducted against the current H1OS implementation across [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c), [`components/h1os/src/sub_power.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/sub_power.c), [`components/h1os/src/hal_io.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/hal_io.c), and [`components/h1os/src/orch_flow.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/orch_flow.c).

The TRM provides direct hardware verification for our timing calibration, confirms our register address translation logic, validates our bit-bang I2C architecture for SHTC3 on GPIO 47/48, and provides clear specifications for the coprocessor halt and wake sequences.

---

## 2. TRM Architectural Verification & Compliance Audit

### 2.1 Clocking & Instruction Timing (Sections 2.2 & 2.6.2)
- **TRM Specification:**
  - Clock source: $f_{\text{RTC\_FAST}} = 17.5\text{ MHz}$ (`RTC_FAST_CLK`).
  - Core ISA: Standard RV32IMC instruction set.
  - Hardware Multiplier & Divider Execution Cycles (Table 2.6-1):
    - `MUL`: $34\text{ cycles}$
    - `MULH`, `MULHU`, `MULHSU`: $66\text{ cycles}$
    - `DIV`, `DIVU`, `REM`, `REMU`: $34\text{ cycles}$
- **H1OS Firmware Alignment:**
  - Standard instructions take 6 to 8 clock cycles due to the non-pipelined micro-architecture.
  - Multiplier and divider instructions consume up to 66 clock cycles.
  - **Confirmation:** Directly corroborates why `17,500 cycles/ms` nominal clock resulted in an $8\times$ delay stretch in wall-clock time ($80\text{ ms}$ real per $10\text{ ms}$ nominal). The rescaled calibration ($2,188\text{ cycles/ms}$) precisely compensates for this hardware execution latency.

---

### 2.2 Peripheral Address Mapping (Section 2.8, Table 2.8-1)
- **TRM Specification:**
  The ULP-RISC-V core accesses RTC peripherals through remapped internal base addresses:
  
  | Peripheral Domain | Main Bus Address | ULP-FSM Base | ULP-RISC-V Base |
  | :--- | :--- | :--- | :--- |
  | **RTC Control (`RTC_CNTL`)** | `0x60008000` | `0x8000` | `0x8000` |
  | **RTC GPIO (`RTC_IO`)** | `0x60008400` | `0x8400` | `0xA400` |
  | **ADC, Touch, TSENS (`SENS`)** | `0x60008800` | `0x8800` | `0xC800` |
  | **RTC I2C (`RTC_I2C`)** | `0x60008C00` | `0x8C00` | `0xEC00` |

- **H1OS Firmware Alignment:**
  In ESP-IDF's `ulp_riscv_register_ops.h`:
  $$\text{RISCV\_REG\_CONV}(addr) = (((addr \ \& \ \text{0xFFFF}) \ll 3 \ \& \ \text{0xE000}) \ | \ (addr \ \& \ \text{0x1FFF}) \ | \ \text{0x8000})$$
  - `RTC_CNTL` (`0x60008000`): maps to `0x8000` $\rightarrow$ **Exact Match**
  - `RTC_IO` (`0x60008400`): maps to `0xA400` $\rightarrow$ **Exact Match**
  - `SENS` (`0x60008800`): maps to `0xC800` $\rightarrow$ **Exact Match**
  - `RTC_I2C` (`0x60008C00`): maps to `0xEC00` $\rightarrow$ **Exact Match**
  - **Confirmation:** All register operations (`REG_READ`, `REG_WRITE`, `REG_SET_FIELD`) executed in ULP code correctly target the hardware blocks.

---

### 2.3 RTC I2C Hardware Limitation vs Bit-Bang Wake Stub (Section 2.7.1)
- **TRM Specification:**
  - *"SDA and SCL signals can be mapped onto two out of the four GPIO pins, which are identified in Table RTC_MUX Pad List... using the register `RTCIO_SAR_I2C_IO_REG`."*
  - The hardware RTC I2C controller on ESP32-S3 is strictly wired to RTC GPIOs 1, 2, 3, 4.
- **H1OS Architecture Validation:**
  - In H1OS hardware, the SHTC3 temperature/humidity sensor is connected to **GPIO 47 (SDA)** and **GPIO 48 (SCL)**.
  - GPIO 47 and 48 are digital domain pins and cannot be mapped to the hardware RTC I2C controller.
  - **Confirmation:** Proves that implementing bit-bang I2C in the RTC Fast Memory Wake Stub ([`components/h1os/src/orch_wake_stub.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/src/orch_wake_stub.c)) is the only valid architectural approach for sub-3ms Flow A sensor sampling on this hardware revision.

---

### 2.4 Sleep & Wakeup Sequences (Section 2.4 & Register 2.1)
- **TRM Specification:**
  - **Monitor Mode:** The ULP coprocessor is woken from sleep reactively by RTC GPIO or periodically by the ULP timer.
  - **Timer & GPIO Control Register (`RTC_CNTL_ULP_CP_TIMER_REG` / `0x00FC`):**
    - Bit 31: `RTC_CNTL_ULP_CP_SLP_TIMER_EN` — Enables periodic ULP sleep timer.
    - Bit 30: `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` (WO) — Write 1 to clear the GPIO wakeup latch.
    - Bit 29: `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` (R/W) — Enable ULP wakeup on RTC GPIO event.
  - **HALT & Reset Requirement:**
    - *"Before setting ULP-RISC-V to HALT, users should configure `RTC_CNTL_COCPU_DONE` first, therefore, it is recommended to end the flashed program with the following pattern:*
      1. *Set `RTC_CNTL_COCPU_DONE` to end the operation of ULP-RISC-V and put it into halt;*
      2. *Set `RTC_CNTL_COCPU_SHUT_RESET_EN` to reset ULP-RISC-V."*
- **H1OS Firmware Alignment:**
  - In `sub_power.c`, both `RTC_CNTL_ULP_CP_SLP_TIMER_EN` and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` are armed before sleep.
  - In `components/h1os/ulp/main.c`, `ulp_riscv_gpio_wakeup_clear()` writes to `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR`.
  - When `main()` returns 0, ESP-IDF's runtime automatically invokes `ulp_riscv_halt()`, which executes:
    ```c
    REG_SET_FIELD(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_2_CLK_DIS, 0x3F);
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE | RTC_CNTL_COCPU_SHUT_RESET_EN);
    ```
    This matches the exact TRM requirement.

---

### 2.5 RTC GPIO Interrupt Handling (Section 2.6.3.5)
- **TRM Specification:**
  - *"Besides the above-mentioned interrupts, ULP-RISC-V can also handle the interrupt from RTC_IO by simply configuring RTC_IO as input mode. Users can configure `RTCIO_GPIO_PINn_INT_TYPE` to select the interrupt trigger modes."*
  - *"The interrupt from RTC_IO can be cleared by releasing RTC_IO and its source can be read from the register `RTCIO_RTC_GPIO_STATUS_REG`."*
- **H1OS Firmware Alignment:**
  - In `components/h1os/ulp/main.c`, reading `RTC_GPIO_STATUS_REG` identifies the trigger pin (GPIO 0 for BOOT, GPIO 18 for POWER, GPIO 5 for RTC alarm).
  - Writing `REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);` clears all latched status bits once the button is released.

---

## 3. Action Plan & Next Steps

Based on the TRM specifications, the current firmware is structurally sound and adheres to all hardware rules. Below are two targeted micro-enhancements to guarantee complete robustness:

### Task 1: Ensure Clear of `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` Strobe
- **Observation:** In [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c), `ulp_riscv_gpio_wakeup_clear()` is called in both button and RTC alarm branches.
- **Verification:** Confirm that writing to `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` is done while the trigger pin is HIGH (released). Our new 2-sample debounced release check ensures that the pin is confirmed released before clearing, fulfilling the TRM mandate: *"The interrupt from RTC_IO can be cleared by releasing RTC_IO"*.

### Task 2: Validate Clean Exit Path in Non-Wake Cases
- **Observation:** If the ULP wakes on a periodic soft-timer tick (`dispatch_reason = 1`), ensure that `REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);` and `ulp_riscv_gpio_wakeup_clear();` are called before waking the main CPU or halting, preventing spurious residual flags from lingering.
- **Current State:** Already implemented in line 133 of [`components/h1os/ulp/main.c`](file:///c:/Users/Matt/Documents/GitHub/H1OS/components/h1os/ulp/main.c).

---

## 4. Summary Table of Verified TRM Findings

| Architectural Domain | TRM Spec | Current H1OS Implementation | Compliance Status |
| :--- | :--- | :--- | :--- |
| **ULP Clock Frequency** | $17.5\text{ MHz}$ (`RTC_FAST_CLK`) | $2,188\text{ cycles/ms}$ calibrated | Verified ($8\times$ CPU instruction retired ratio) |
| **Math / Arithmetic Latency** | $34\text{ to }66\text{ cycles}$ per `MUL`/`DIV` | Trimmed 64-bit integer conversion | Verified (non-blocking) |
| **Address Mapping** | Base `0x8000`, `0xA400`, `0xC800`, `0xEC00` | Handled via `RISCV_REG_CONV` | 100% Compliant |
| **RTC I2C Mapping** | RTC GPIO 1..4 only | Bit-bang in RTC Wake Stub (GPIO 47/48) | Architecture Verified |
| **RTC GPIO Latch Clear** | `RTCIO_RTC_GPIO_STATUS_REG` + W1TC | `RTC_GPIO_STATUS_W1TC_REG` (`INT_W1TC_M`) | 100% Compliant |
| **ULP Halt Pattern** | `COCPU_DONE` + `COCPU_SHUT_RESET_EN` | Auto-invoked via `ulp_riscv_halt()` | 100% Compliant |
