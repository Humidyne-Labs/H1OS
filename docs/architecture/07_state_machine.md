# Application Execution Flow & State Machine

This document models the end-to-end execution flow of **H1OS** across deep sleep, the reactive ULP Monitor, isolated Flow A sensor pulses, and the Flow B interactive user session (with a developer-configurable inactivity timeout defaulting to 30 seconds).

---

## 1. Master System Flowchart

```mermaid
graph TD;
    DeepSleep["Hardware Deep Sleep Standby"] --> ULP_Wake{"ULP Hardware Event"};

    subgraph ULP_Monitor ["ULP-RISC-V Reactive Monitor"]
        ULP_Wake -- "Internal Timer Expired" --> LaunchFlowA["Set DISPATCH_SENSOR_SAMPLE (Wake Core 0 into Flow A)"];
        ULP_Wake -- "External Interrupt (GPIO 5)" --> LaunchFlowB_Alarm["Set DISPATCH_MAIN_WAKE (Wake Dual-Core into Flow B)"];
        ULP_Wake -- "Button Edge (GPIO 0 or 18)" --> CheckHold{"Hold Duration"};
        CheckHold -- "Short Tap Release" --> LaunchFlowB_Tap["Set DISPATCH_MAIN_WAKE (Wake Dual-Core into Flow B)"];
        CheckHold -- "BOOT Hold > 2.5s" --> LaunchBL["Set DISPATCH_BOOTLOADER_JUMP (ROM Bootloader)"];
        CheckHold -- "POWER Hold > 2.5s" --> LaunchPowerOff["Set DISPATCH_POWER_OFF (Execute Power Cut)"];
        ULP_Wake -- "Battery Guard (GPIO 4)" --> CheckVbat{"Vbat < 3.25V?"};
        CheckVbat -- "YES (and > 100mV)" --> LaunchCritical["Set DISPATCH_CRITICAL_SHUTDOWN"];
        CheckVbat -- "Vbat == 0mV (USB)" --> KeepSleeping["Bypass Shutdown and Return to Sleep"];
    end

    subgraph FlowA ["FLOW A: Headless Sensor Pulse"]
        LaunchFlowA --> StubExec["esp_wake_stub on Core 0 at 80MHz (Core 1 Gated, Flash Unpowered)"];
        StubExec --> StubI2C["Read SHTC3 Normal Mode and MCU Die TSENS"];
        StubI2C --> StubMath["Compute Dew Point, Vapor Pressure, and EWMA"];
        StubMath --> StubCommit["Append to 32-slot Ring in RTC Slow Memory"];
        StubCommit --> StubRearm["Re-arm Periodic RTC Timer"];
        StubRearm --> StubSleep["Return Immediately to Deep Sleep"];
    end
    StubSleep --> DeepSleep;

    subgraph FlowB ["FLOW B: Dual-Core Screen Refresh and Interaction"]
        LaunchFlowB_Alarm --> Bootloader2["2nd-Stage Bootloader (h1os_boot_hook: Latch BAT_CTRL HIGH)"];
        LaunchFlowB_Tap --> Bootloader2;
        Boot["Initial Power On / Boot"] --> Bootloader2;
        Bootloader2 --> BootFreeRTOS["Initialize FreeRTOS SMP Dual-Core LX7"];
        BootFreeRTOS --> TurboRender["240 MHz Turbo PM Lock: Read Telemetry and Blit LVGL Screen"];
        TurboRender --> WakeSource{"Wake Source?"};
        WakeSource -- "RTC Countdown Timer" --> SleepStart["Initiate Sleep Transition"];
        WakeSource -- "User Tap or Boot" --> LVGL_Active["Interactive Session (LVGL Owns Display and Buttons)"];
        LVGL_Active --> UserClick{"User Button Click?"};
        UserClick -- "BOOT or POWER Click" --> ScreenToggle["Cycle Screen and Reset Inactivity Timer"];
        ScreenToggle --> LVGL_Active;
        UserClick -- "No Interaction (Idle)" --> DFSDrop["Dynamic Frequency Scaling: Drop CPU to 80 MHz"];
        DFSDrop --> InactivityTimer{"Inactivity Timer Expired?"};
        InactivityTimer -- "NO" --> UserClick;
        InactivityTimer -- "YES" --> SleepStart;
    end

    subgraph Sleep_Transition_Seq ["Coordinated Sleep Transition Sequence"]
        SleepStart --> PreSleepHook["1. Invoke user on_pre_sleep hook"];
        PreSleepHook --> DrainLVGL["2. Drain LVGL Buffer and Finish Draw Tasks"];
        DrainLVGL --> WaitBusy["3. Wait for SSD1681 BUSY release at 80 MHz"];
        WaitBusy --> SettleDelay["4. 250ms Microcapsule Settling Delay"];
        SettleDelay --> CheckDirty{"Frame Marked Dirty?"};
        CheckDirty -- "YES" --> FlashSync["5. Commit 5000B to epd_frame flash"];
        CheckDirty -- "NO" --> SkipSync["5. Skip Flash Write"];
        FlashSync --> PanelSleep["6. Put SSD1681 into Deep Sleep Mode 1"];
        SkipSync --> PanelSleep;
        PanelSleep --> ClearTF["7. Clear PCF85063A TF Flag in Control_2"];
        ClearTF --> GateCheck{"8. Zero-Hour Lookahead Overshoot?"};
        GateCheck -- "YES" --> ArmExtOnly["Arm ONLY GPIO 5 RTC_INT and Buttons"];
        GateCheck -- "NO" --> ArmAll["Arm Internal Periodic Timer and EXTINT"];
        ArmExtOnly --> EnterSleep["9. Enter Hardware Deep Sleep"];
        ArmAll --> EnterSleep;
    end
    EnterSleep --> DeepSleep;

    LaunchBL --> ROM_Bootloader["ROM Download Bootloader Mode"];
    LaunchPowerOff --> CutLatch["Flush Frame and Release GPIO 17 Latch"];
    LaunchCritical --> EmergencySplash["Draw Low Battery Icon and Cut Latch"];
```

---

## 2. Zero-Hour Conflict Elimination Sequence

```mermaid
sequenceDiagram
    autonumber
    participant App as Orchestrator
    participant RTC as PCF85063A
    participant ULP as ULP Monitor
    participant Xtensa as Xtensa Flow B

    Note over App: Inactivity Timeout or h1os_sleep()
    alt Next Sleep Accumulator Overshoots External Timer
        Note over App: Do NOT arm internal periodic timer
        App->>ULP: Arm EXTINT only (GPIO 5 Countdown Timer and Buttons)
        App->>App: Enter Deep Sleep
        RTC-->>ULP: GPIO 5 falls LOW (Countdown Timer Reaches Zero)
        ULP->>Xtensa: Catch RTC Timer Interrupt and Wake into Flow B
    else Next Sleep Accumulator Within Window
        Note over App: Window is clear, arm both timers
        App->>ULP: Arm internal periodic timer and EXTINT
        App->>App: Enter Deep Sleep
        ULP->>App: Timer expires and Wakes Core 0 into Flow A
    end
```

---

## 3. Human-Machine Interaction & Power Policies

### 3.1 Two-Stage Click Interaction
To prevent unintended audio chirps and spurious screen skipping while deep sleeping:
1. **First Click in Deep Sleep (Wake Interaction):**
   - Intercepted by the ULP-RISC-V coprocessor in RTC domain.
   - ULP debounces the release, records `ulp_last_wake_btn`, and wakes the main processor into Flow B.
   - Flow B boots, detects the user button wake, initializes LVGL, and renders the screen with the **inverted awake badge**.
   - **No page advance or audio tick occurs on the wake click**, guaranteeing that waking the screen does not skip the user's current view.
2. **Second Click in Flow B (Active Navigation):**
   - The user is now looking at the awakened UI.
   - The second click is received directly by the running LVGL keypad driver (`keypad_event_cb`).
   - LVGL dispatches the page switch, plays the tactile 15ms audio tick, and resets the 30-second inactivity session timer.

### 3.2 Audio Codec Standby Gating (<1 µA Invariant)
- **Unattended Wakes (RTC Countdown Timer):**
  - Environmental display refresh wakes bypass the ES8311 codec and NS4168 amplifier initialization entirely.
  - The codec remains in hardware standby / power-down state (<1 µA).
  - This eliminates parasitic heat injection into the enclosure and maximizes battery longevity.
- **User Wakes (Cold Boot or Tactile Button):**
  - Audio subsystem initializes only when `is_user_wake` is true.
  - Initial volume is set strictly from `presentation.volume_pct` (defaulting to 0% / muted if unconfigured).

### 3.3 Strict Lifecycle Contract Validation
- Silent fallback magic numbers (`300s`, `120s`, `30s`) have been removed from `h1os_lifecycle.c`.
- If an unconfigured duration or timeout of `0` is passed to `h1os_sleep()`, `inactivity_timeout_sec`, or `flow_b_period_sec`, the system logs an explicit `ESP_LOGE` error detailing the contract violation and triggers clean shutdown rather than silently injecting synthetic delays.

