# Application Execution Flow & State Machine

This document models the end-to-end execution flow of **H1OS** across deep sleep, the Pure Event Mode ULP-RISC-V Monitor, isolated Flow A wake stub sensor pulses, and the Flow B interactive user session (with a developer-configurable inactivity timeout defaulting to 30 seconds).

---

## 1. Master System Flowchart

```mermaid
graph TD;
    DeepSleep["Hardware Deep Sleep Standby (Pure Event Mode)"] --> ULP_Wake{"ULP RTC GPIO Event"};

    subgraph ULP_Monitor ["ULP-RISC-V Reactive Monitor"]
        ULP_Wake -- "Non-Button Event" --> SampleADC["Sample SAR ADC1_CH3 (GPIO 4) -> Push to vbat_ring[8]"];
        SampleADC --> CheckVbat{"!usb_connected && 100 <= Vbat < 3250 mV?"};
        CheckVbat -- "YES" --> LaunchCritical["Set ULP_DISPATCH_CRITICAL_SHUTDOWN"];
        CheckVbat -- "NO (Normal / USB)" --> CheckPin{"Evaluate RTC GPIO Trigger"};
        ULP_Wake -- "Button Edge (GPIO 0 or 18)" --> CheckHold{"Debounce 30ms & Measure Hold"};
        CheckHold -- "Short Tap Release (30..2500ms)" --> LaunchFlowB_Tap["Set ULP_DISPATCH_MAIN_WAKE (Wake Dual-Core into Flow B)"];
        CheckHold -- "BOOT Hold >= 2.5s" --> LaunchBL["Set ULP_DISPATCH_BOOTLOADER_JUMP (ROM Bootloader)"];
        CheckHold -- "POWER Hold >= 2.5s" --> LaunchPowerOff["Set ULP_DISPATCH_POWER_OFF (Execute Power Cut)"];
        CheckPin -- "RTC_INT Low (GPIO 5)" --> SliceCheck{"++slice_counter < overflow_limit?"};
        SliceCheck -- "YES (Intermediate Slice)" --> LaunchFlowA["Set ULP_DISPATCH_SENSOR_SAMPLE (Wake Core 0 into Flow A Stub)"];
        SliceCheck -- "NO (Overflow Reached)" --> LaunchFlowB_Alarm["Reset slice_counter=0, Set ULP_DISPATCH_MAIN_WAKE"];
    end

    subgraph FlowA ["FLOW A: Headless Sensor Pulse (<16ms in RTC Fast IRAM)"]
        LaunchFlowA --> StubExec["bsp_wake_stub on Core 0 (Main OS & Flash Unpowered)"];
        StubExec --> StubI2C["Read SHTC3 Normal Mode (0x7866) and Q12 MCU Die TSENS"];
        StubI2C --> StubGate["Evaluate Plateau Gate (|T2 - T1| <= 0.20 C) & Back-Mark Valid"];
        StubGate --> StubCommit["Append to 32-slot Ring in RTC Slow Memory & Add Runtime Counters"];
        StubCommit --> StubRearm["Clear PCF85063A TF (0x07) or Rearm Remainder Slice, Drain /INT HIGH"];
        StubRearm --> StubSleep["Re-arm ULP GPIO Wakeup & Return Immediately to Deep Sleep"];
    end
    StubSleep --> DeepSleep;

    subgraph FlowB ["FLOW B: Dual-Core Screen Refresh and Interaction"]
        LaunchFlowB_Alarm --> Bootloader2["2nd-Stage Bootloader (h1os_boot_hook: Latch Master Rails)"];
        LaunchFlowB_Tap --> Bootloader2;
        Boot["Initial Power On / Boot"] --> Bootloader2;
        Bootloader2 --> BootFreeRTOS["Initialize FreeRTOS SMP, Sync PCF85063A -> POSIX Clock"];
        BootFreeRTOS --> TurboRender["Read Pre-Display Glass Temp (0x1B), Evaluate Telemetry & Render LVGL Screen"];
        TurboRender --> WakeSource{"Wake Source?"};
        WakeSource -- "RTC Countdown Overflow" --> SleepStart["Initiate Immediate Sleep Transition (Audio Skipped)"];
        WakeSource -- "User Button Tap or Boot" --> LVGL_Active["Interactive Session (Audio Ready, LVGL Owns Display and Buttons)"];
        LVGL_Active --> UserClick{"User Button Click?"};
        UserClick -- "BOOT (Fwd) or POWER (Rev) Click" --> ScreenToggle["Play 50ms Nav Tone, Cycle Screen & Reset Inactivity Timer"];
        ScreenToggle --> LVGL_Active;
        UserClick -- "POWER / BOOT Hold >= 2.0s" --> LaunchPowerOff;
        UserClick -- "No Interaction (Idle)" --> DFSDrop["Dynamic Frequency Scaling: Drop CPU to 80 MHz"];
        DFSDrop --> InactivityTimer{"Inactivity Timer Expired?"};
        InactivityTimer -- "NO" --> UserClick;
        InactivityTimer -- "YES" --> SleepStart;
    end

    subgraph Sleep_Transition_Seq ["Coordinated Sleep Transition Sequence"]
        SleepStart --> PreSleepHook["1. Trigger Sleep Chime/Splash & Invoke user on_pre_sleep hook"];
        PreSleepHook --> DrainLVGL["2. Drain LVGL Pipeline & Stop Core 1 LVGL Task"];
        DrainLVGL --> QuiesceAudio["3. Wait Audio Idle & Place ES8311 + NS4168 in <1uA Standby"];
        QuiesceAudio --> WaitBusy["4. Wait for SSD1681 BUSY release at 80 MHz"];
        WaitBusy --> CheckDirty{"5. Frame Marked Dirty?"};
        CheckDirty -- "YES" --> FlashSync["Commit 5000B to epd_frame flash"];
        CheckDirty -- "NO" --> SkipSync["Skip Flash Write"];
        FlashSync --> PanelSleep["6. Put SSD1681 into Deep Sleep Mode 1 (0x10=0x01)"];
        SkipSync --> PanelSleep;
        PanelSleep --> ArmRTC["7. Arm PCF85063A Countdown Slice & Install bsp_wake_stub"];
        ArmRTC --> EnterSleep["8. Save Runtimes to NVS, Isolate Pads, Drain Wake Pins HIGH & Enter Deep Sleep"];
    end
    EnterSleep --> DeepSleep;

    LaunchBL --> ROM_Bootloader["ROM Download Bootloader Mode"];
    LaunchPowerOff --> CutLatch["Save Runtimes to NVS, Flush Frame & Release GPIO 17 Latch"];
    LaunchCritical --> CutLatch;
```

---

## 2. Event-Mode RTC Slicing & Zero-Hour Conflict Elimination

```mermaid
sequenceDiagram
    autonumber
    participant App as Orchestrator (Flow B)
    participant RTC as PCF85063A (GPIO 5)
    participant ULP as ULP Monitor
    participant Stub as Core 0 Wake Stub (Flow A)

    Note over App: Sleep Transition (e.g. Flow A = 60s, Flow B = 300s -> overflow = 5)
    App->>RTC: Arm Countdown Timer for 60s (1 Hz pulse mode)
    App->>ULP: Set slice_counter = 0, overflow_limit = 5, remainder_sec = 0
    App->>App: Isolate Pads & Enter Deep Sleep

    loop Slices 1..4 (Intermediate Flow A Bursts)
        RTC-->>ULP: GPIO 5 falls LOW (60s elapsed)
        ULP->>ULP: Sample ADC1_CH3 (Quiet Vbat) -> vbat_ring[8]
        ULP->>ULP: slice_counter++ (< 5) -> Set ULP_DISPATCH_SENSOR_SAMPLE
        ULP->>Stub: Wake Core 0 into bsp_wake_stub()
        Stub->>Stub: Read SHTC3 (0x7866) + Q12 Die TSENS -> Push to ring[32]
        Stub->>RTC: Clear TF in Control_2 (0x07) & Wait GPIO 5 HIGH
        Stub->>ULP: Re-arm ULP GPIO Wakeup & Return to Deep Sleep
    end

    RTC-->>ULP: GPIO 5 falls LOW (Slice 5 == overflow_limit)
    ULP->>ULP: Sample ADC1_CH3 (Quiet Vbat) -> vbat_ring[8]
    ULP->>ULP: slice_counter == 5 -> Reset slice_counter = 0, Set ULP_DISPATCH_MAIN_WAKE
    ULP->>App: Wake Dual-Core Xtensa into Flow B UI Refresh
```

---

## 3. Human-Machine Interaction & Power Policies

### 3.1 Two-Stage Click Interaction
To prevent unintended audio chirps and spurious screen skipping while deep sleeping:
1. **First Click in Deep Sleep (Wake Interaction):**
   - Intercepted by the ULP-RISC-V coprocessor in RTC domain.
   - ULP debounces the press (`30 ms`), waits for release (`30..2500 ms`), records `ulp_last_wake_btn`, and wakes the main processor into Flow B.
   - Flow B boots, detects the user button wake, initializes LVGL and audio, and renders the screen with the **inverted awake badge**.
   - **No page advance or audio tick occurs on the wake click**, guaranteeing that waking the screen does not skip the user's current view.
2. **Second Click in Flow B (Active Navigation):**
   - The user is now looking at the awakened UI.
   - Subsequent clicks are received directly by the running LVGL keypad driver (`keypad_event_cb`): `BOOT` advances forward (`1046 Hz`, `50 ms` tone), `POWER` navigates backward (`880 Hz`, `50 ms` tone), and either button resets the 30-second inactivity session timer.

### 3.2 Audio Codec Standby Gating (<1 µA Invariant)
- **Unattended Wakes (RTC Countdown Timer):**
  - Environmental display refresh wakes bypass the ES8311 codec and NS4168 amplifier initialization entirely.
  - Furthermore, `sub_audio_standby()` tracks `s_rtc_codec_in_standby` in `RTC_DATA_ATTR` so unattended wakes skip redundant I2C deinit writes when the codec is already parked in `<1 µA` standby.
- **User Wakes (Cold Boot or Tactile Button):**
  - Audio subsystem initializes only when `is_user_wake` is true, setting volume strictly from `presentation.volume_pct`.

### 3.3 Strict Lifecycle Contract Validation & Timing Parameter Bounds
- **Single Variable Authority:** All time logic across all layers derives strictly from `st->sample_interval_sec` (Flow A) and `st->flow_b_period_sec` (Flow B) in RTC Slow Memory. Duplicate file-static variables and ternary fallbacks have been removed.
- **Timing Bounds Law:**
  - Flow A (`sample_interval_sec`): $60\text{s} \le A \le 14,400\text{s}$ ($4\text{ hours}$). Must be an exact multiple of $60\text{s}$ if $> 255\text{s}$.
  - Flow B (`flow_b_period_sec`): $300\text{s} \le B \le 86,400\text{s}$ ($24\text{ hours}$). Must be strictly greater than $A$.
  - Remainder Floor: If $\text{remainder} = B \bmod A > 0$, it must be $\ge 60\text{s}$ to justify the re-arm cycle.
- **Unified Setter Enforcement:** Both `h1os_start()` and `h1os_set_flow_periods()` funnel strictly through `h1os_set_flow_periods_internal()`. If parameters violate any bound or invariant, the call fails immediately with `ESP_ERR_INVALID_ARG`.
- Silent fallback magic numbers (`300s`, `120s`, `30s`) are strictly prohibited across the codebase.
