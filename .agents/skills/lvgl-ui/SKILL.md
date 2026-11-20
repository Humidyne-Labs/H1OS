---
name: lvgl-ui
description: Authoritative design guidelines, bilevel e-paper constraints, layout grids, font CSV paths, kerning metrics, cross-core h1os_ui_post actor queue, and string width validation tools for LVGL v9 on SSD1681.
---

# LVGL v9 Bilevel UI Design & E-Paper Font Validation (`v2.4.10-dev`)

This skill defines the canonical constraints, design patterns, font metric tables, and automated validation tools for developing LVGL v9 user interfaces on the **Waveshare ESP32-S3 ePaper 1.54" V2** (SSD1681) panel.

---

## 1. Hardware, Silicon Display & Dual-Core Concurrency Constraints

- **Resolution:** 200 x 200 pixels (1:1 square aspect ratio).
- **Usable Margin:** $X = 6\text{ px}$ to $194\text{ px}$ ($\le 188.0\text{ px}$ maximum string width).
- **Color Depth:** 1-bit Monochrome (`LV_COLOR_FORMAT_I1`), pure black and pure white.
- **Draw Buffer:** Exactly 5,000 pixel bytes ($200 \times 200 \div 8\text{ bits}$) plus the 8-byte LVGL v9 palette header.
- **Opacity Mandate:** Strict 100% opacity (`LV_OPA_COVER`). No alpha blending or partial opacities.
- **Thread Safety & Cross-Core Actor Queue (`v2.4.10-dev`):**
  - The LVGL presentation task (`h1os_lvgl`) is pinned to **Core 1** at FreeRTOS priority **5** (`LVGL_TASK_PRIO_PORT = 5`).
  - During `on_boot()` and `on_wake()`, Core 1 has not yet started (`h1os_lvgl_start(5, 1)` runs immediately after `on_wake()` returns), so initial screen construction requires no outer mutex lock.
  - Once Core 1 is running, Core 0 `on_sync()` and background tasks should post UI updates via `h1os_ui_post(fn, arg, timeout_ms)` (16-slot static queue drained on Core 1 inside `h1os_lvgl_lock(100)` before `lv_timer_handler()`), or wrap synchronous LVGL operations in `if (h1os_lvgl_lock(timeout_ms)) { ... h1os_lvgl_unlock(); }`.

---

## 2. Spatial Budget & Vertical Layout Allocation (200 px Total)

```
Y = 0 px   +-------------------------------------------------------+
           | 1. HEADER REGION (Height: 20 px, Y = 0..20)           |
           | Title, status flag, or category (14pt Bold Centered)  |
Y = 20 px  |-------------------------------------------------------| (1 px Solid Border)
           |                                                       |
           | 2. MAIN BODY CONTENT REGION (Height: 128 px)          |
           | Available: Y = 22 to 148 px                           |
           | Telemetry values, psychrometric dew point, gauge arc, |
           | QR provisioning canvas, or multi-field sensor rows.   |
           |                                                       |
Y = 148 px |-------------------------------------------------------|
           | 3. FOOTER / ACTION REGION (Height: 50 px)             |
           | Y = 150 px: Primary Status / Value                    |
           | Y = 170 px: Secondary Physical Button Action Hint    |
Y = 200 px +-------------------------------------------------------+
```

---

## 3. Packaged Font Metric CSV Tables (`components/h1os/tools/fonts/metrics/`)

IBM Plex Sans is a **proportional (variable-width)** font with 4-bit fractional advance widths (`adv_w_fp4`, exact LVGL v9 step `(adv_w_fp4 + kern_fp4 + 8) >> 4`), while IBM Plex Mono & Terminus provide fixed tabular widths for aligned readouts. Never use multiple spaces for proportional horizontal alignment—use separate column labels or tabular mono strikes.

### Active Metric Manifests & Strike Vault
- **108 Advance Width & BBox CSVs:** `components/h1os/tools/fonts/metrics/char_widths_<symbol>.csv` (e.g., `char_widths_humid1_font_plex_sans_normal_14.csv`, `char_widths_humid1_font_plex_mono_bold_20.csv`).
- **108 Kerning CSVs:** `components/h1os/tools/fonts/metrics/kern_pairs_<symbol>.csv`.
- **Headers & Vault:** `components/h1os/tools/fonts/fonts/{humid1_fonts.h,h1os_fonts.h}` (`HUMID1_FONT_*`, `H1OS_FONT_*`) and `components/h1os/tools/fonts/humid1_epd_vault.json.gz`.

---

## 4. Layout Verification (`embedded-ops` MCP & `epd-typography` Skill)

### A. Single String / Two-Column Row Budget (`embedded-ops/epd_string_budget`)
Evaluates exact LVGL v9 pixel width and clearance against the `188 px` budget:
```text
embedded-ops/epd_string_budget(
  strike="humid1_font_plex_sans_normal_14",
  text="Power: CHARGED 4.00V",
  workspace_dir="<workspace_root>"
)
```

### B. Automated Screen File Audit (`embedded-ops/epd_audit_screens`)
Scans all C screen files in `examples/H1OS/main/screens/`, resolves `lv_obj_set_style_text_font` + `HUMID1_FONT_*`/`H1OS_FONT_*` macros, simulates worst-case `printf` expansion, and flags any line exceeding `188 px`:
```text
embedded-ops/epd_audit_screens(workspace_dir="<workspace_root>")
```

### C. Regenerate Font Assets (`epd-font` v1.0.23)
Regenerate in `<epd-font-repo>` via `scripts\h1os-build-distro\02_build_fonts.bat` and `07_package_distro.bat`, then sync `dist\h1os_distro\` into `components\h1os\tools\fonts\`.

### D. Query Metrics via DuckDB SQL
Query glyph or kerning metrics using DuckDB MCP:
```sql
-- Widest ASCII characters in IBM Plex Sans 14px:
SELECT char, width_px FROM read_csv_auto('components/h1os/tools/fonts/metrics/char_widths_humid1_font_plex_sans_normal_14.csv') WHERE unicode_dec < 128 ORDER BY width_px DESC LIMIT 8;

-- Negative kerning adjustments (tighter pairs):
SELECT left_char, right_char, kern_px FROM read_csv_auto('components/h1os/tools/fonts/metrics/kern_pairs_humid1_font_plex_sans_normal_14.csv') WHERE kern_px < 0 ORDER BY kern_px ASC LIMIT 10;
```
