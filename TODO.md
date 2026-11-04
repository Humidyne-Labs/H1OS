# H1OS Engineering Action Plan & Display Typography TODO

## Current Silicon & Display Issues (`v2.4.9-dev`)

During physical hardware bench testing on the Waveshare 1.54" V2 e-Paper (SSD1681 driver, 200×200 resolution, 188.3 DPI), two visual rendering issues were identified:

1. **Icon Render Failure (Placeholder Box `▯`):**
   - Font Awesome UI and telemetry symbols (`LV_SYMBOL_TINT`, `LV_SYMBOL_REFRESH`, `LV_SYMBOL_BATTERY_*`, `LV_SYMBOL_CHARGE`, `LV_SYMBOL_USB`) render as missing glyph boxes (`▯`).
   - **Root Cause:** Screen widgets format compound strings (e.g. `LV_SYMBOL_TINT " %.1f%%"`) and assign the typography font `HUMID1_FONT_UI_HEADER` (IBM Plex Sans) to the entire label. Because IBM Plex Sans only contains ASCII, Latin-1, Greek, and Math glyphs, and has no `.fallback` pointer configured to the modular icon font (`humid1_icon_fa7_solid_20`), LVGL fails glyph lookup and renders the fallback missing box (`▯`).
   - **Catalog Status:** The glyphs for Droplet (`0xF043`), Refresh (`0xF021`), Bolt (`0xF0E7`), and Battery 0–4 (`0xF240`–`0xF244`) **already exist** inside `humid1_icon_fa7_solid_14.c` and `humid1_icon_fa7_solid_20.c`.
   - **USB Trident Status:** In Font Awesome 7 Free, `fa-usb` (`U+F287`) is classified under `Brands`, not `Solid`. Because `h1os_full.scheme.json` only rasterized `"style": "solid"`, `0xF287` was skipped during TrueType rasterization.

2. **Hairline Alphanumeric Stroke Weight:**
   - Text rendered with `HUMID1_FONT_UI_BODY` (`&humid1_font_plex_sans_normal_14`) is difficult to read under ambient lighting.
   - **Root Cause:** `IBMPlexSans-Regular.ttf` (`wght: 400`) renders with 1-pixel hairline vertical stems (~0.135 mm wide at 188.3 DPI).
   - **Empirical Ground Truth:** FreeType testing confirms that `IBMPlexSans-Medium.ttf` (`wght: 500`) naturally expands vertical stems to **solid 2-pixel strokes (`##....##`, ~0.27 mm wide)** while maintaining open, unclogged interior apertures on lowercase letters (`'e'`, `'a'`, `'o'`).

---

## Formal Resolution Plan

### Phase 1: Upstream Scheme Configuration (`epd-font`)
- [ ] **Configure Font Weight Scaling:**
  - In `C:\Users\Matt\Documents\GitHub\epd-font\scripts\h1os-build-distro\h1os_full.scheme.json`:
  - Set `"normal_weight": 500` under `"raster_config"` (maps `sans normal`, `mono normal`, and `cond normal` to `IBMPlex*-Medium.ttf`).
- [ ] **Configure Fallback Chaining:**
  - Set `sans normal` `"fallback": "humid1_icon_fa7_solid_{size}"`.
  - Set `sans bold` `"fallback": "humid1_font_plex_sans_normal_{size}"` (cascades automatically to FA7 solid).
  - Ensures compound strings (`LV_SYMBOL_*` + text) resolve both typography and icons from a single font pointer without splitting widgets.
- [ ] **Incorporate Font Awesome Brands for USB (`0xF287`):**
  - Add strike for `"family": "icon_fa7", "style": "brands"` (or merge `FontAwesome7-Brands.ttf` glyphs into `FontAwesome7-Solid.ttf`) to include `0xF287` (`usb`).

### Phase 2: Distro Regeneration (`epd-font`)
- [ ] Run `scripts\h1os-build-distro\99_run_full_pipeline.bat` (or execute `tools\fonts\humid1_generate_1bpp.py` via Python).
- [ ] Verify generated C strike files in `dist/h1os_distro/fonts/`:
  - Confirm `humid1_font_plex_sans_normal_*.c` contains `.fallback = &humid1_icon_fa7_solid_*`.
  - Confirm `humid1_icon_fa7_solid_*.c` (or brands) contains `0xF287`.
- [ ] Copy `dist/h1os_distro/` into `H1OS/components/h1os/tools/fonts/`.

### Phase 3: Downstream Firmware Integration & Quality Assurance (`H1OS`)
- [ ] Rebuild firmware and verify zero compiler warnings:
  - `idf.py -B build_dev --preset dev build`
  - `idf.py -B build_prod --preset prod build`
- [ ] Validate layout margin budgets against the 188 px width ceiling:
  - `python tools/agent/check_string_width.py --audit-screens`
- [ ] Verify repository sanitization:
  - `python tools/agent/sanitize.py --check` (enforce 0 identity / workstation path leaks).
- [ ] Flash to ESP32-S3 and physically inspect the SSD1681 electrophoretic panel:
  - Verify solid 2px text legibility.
  - Verify droplet, battery, refresh, and USB icons render crisply.

---

## Active Repository Tasks Completed
- [x] Audited all 5 H1OS showcase screens for typography and icon call sites.
- [x] Verified math and scientific symbols (`°`, `³`, `•`, `Δ`) are intact in IBM Plex Sans.
- [x] Replaced legacy font directory with modern `epd-font` distro (`h1os_distro`).
- [x] Updated all screens to semantic `HUMID1_FONT_*` macros.
- [x] Cleaned repository of local path references and verified `sanitize.py --check` passes cleanly.
