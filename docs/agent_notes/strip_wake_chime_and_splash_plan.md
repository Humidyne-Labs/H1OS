# 📋 Architecture & Implementation Plan: Strip Wake Chime and Wake Splash

> [!IMPORTANT]
> **Directive:** Strip `wake_chime` (`H1OS_CHIME_WAKE`) and `wake_splash` (`H1OS_SPLASH_WAKE`) from the wake sequence to prevent unnecessary battery drain, thermal enclosure contamination, and delay during wake transitions.

---

## 1. Technical Analysis & Rationale

1. **Power Consumption & Thermal Penalty:**
   - On wake from deep sleep, playing a presentation chime (`H1OS_CHIME_WAKE`) requires powering the Class-D amplifier rail and running multi-tone acoustic synthesis.
   - Drawing heavy amplifier current directly heats the internal cavity right before quiescent sensor telemetry operations, biasing humidity and temperature measurements.
   - Presenting an extra wake splash image on the electrophoretic display (EPD) triggers additional full or partial particle refresh transitions, wasting battery energy on a redundant graphical intermediate when the user simply wants the active telemetry dashboard immediately.

2. **Presentation Contract:**
   - `H1OS_CHIME_BOOT` and `H1OS_CHIME_SHUTDOWN` remain preserved for tactile power events.
   - `H1OS_SPLASH_BOOT` remains preserved for the cold-boot logo presentation.
   - `H1OS_CHIME_WAKE` and `H1OS_SPLASH_WAKE` are removed from the automatic wake execution flow in `h1os_lifecycle.c`.

---

## 2. Proposed Changes

### Target 1: `components/h1os/src/h1os_lifecycle.c`
In `h1os_start()` (lines 350-354):
```c
// Current:
} else if (s_app_lifecycle.on_wake) {
    if (is_user_wake) {
        h1os_trigger_chime(H1OS_CHIME_WAKE);
        h1os_trigger_splash(H1OS_SPLASH_WAKE);
    }
    h1os_wake_context_t ctx = { ... };
    s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
}
```

```c
// Proposed:
} else if (s_app_lifecycle.on_wake) {
    /* Wake chime and wake splash stripped to protect thermal settling and conserve power */
    h1os_wake_context_t ctx = { ... };
    s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
}
```

### Target 2: `components/h1os/src/sub_audio.c`
- Deprecate or remove `case 1: /* H1OS_CHIME_WAKE */` from `sub_audio_exec_chime()`, or return `ESP_OK` / no-op if invoked.

### Target 3: `examples/H1OS/main/main.c`
- Clean up the presentation configuration in `app_main()`:
  - Remove commented-out `// (1 << H1OS_CHIME_WAKE)` line from `.chime_mask`.
- In `app_on_splash()`:
  - Maintain only `H1OS_SPLASH_BOOT` handling.

---

## 3. Verification Steps

1. **Build Verification:**
   - Execute dev build: `idf.py -B build_dev build`
   - Execute prod build: `idf.py -B build_prod build`
   - Verify 0 errors, 0 warnings.
2. **Runtime Verification:**
   - Cold boot: Boot splash and Boot chime play.
   - Sleep: System enters deep sleep cleanly.
   - Button Wake: System transitions directly to active screen with zero wake chime and zero wake splash overhead. Keypad tones continue to respond instantaneously.
