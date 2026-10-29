# Master Rule: LVGL 9 Bilevel UI Design & E-Paper Constraints Specification (`v2.4.5-dev`)

## 1. Hardware & Silicon Display Constraints

All graphical user interfaces on the platform target the Waveshare ESP32-S3 ePaper 1.54" V2 panel. All UI development MUST strictly obey the physical constraints of the display controller:

* **Controller & Driver:** Solomon Systech SSD1681 active matrix electrophoretic display driver.
* **Resolution:** 200 x 200 pixels (1:1 square aspect ratio).
* **Pixel Density (DPI):** 188 DPI (1 physical pixel ≈ 0.135 mm).
* **Color Depth:** 1-bit Monochrome (`LV_COLOR_FORMAT_I1`). Pure black (`lv_color_black()`) and pure white (`lv_color_white()`).
* **Frame Draw Buffer:** Exactly 5,000 pixel bytes ($200 \times 200 \div 8\text{ bits}$) plus the 8-byte LVGL v9 `LV_COLOR_FORMAT_I1` palette header.
* **Non-Touch Interface:** No touch controller exists on the board. All user interaction is driven exclusively via physical tactile buttons (BOOT on `GPIO 0`, POWER on `GPIO 18`).

---

## 2. Bilevel Visual Styling Constraints

Because electrophoretic microcapsules physically migrate under electrostatic voltage, standard graphical anti-aliasing and translucency do not apply:

1. **Strict 100% Opacity (No Alpha Blending):**
   - Opacity MUST always be set to `LV_OPA_COVER` (100%).
   - Partial opacities (`LV_OPA_50`, `LV_OPA_TRANSP`, alpha blending) are **STRICTLY PROHIBITED**. They produce corrupt pseudo-random dither noise on 1-bit buffers.
2. **Sharp Borders & Geometry:**
   - Use 1 px solid black borders (`lv_color_black()`, `width = 1`).
   - Prefer sharp corners (`radius = 0`) or subtle corners (`radius = 2..4 px`).
3. **Contrast Hierarchy:**
   - Body backgrounds are pure white (`lv_color_white()`).
   - Emphasized telemetry cards or headers may invert to a solid black box (`lv_color_black()`) with white text (`lv_color_white()`).

---

## 3. Spatial Budget & Vertical Layout Allocation (200 px Total)

Every pixel row is accounted for in the canonical 3-tier vertical grid:

```
Y = 0 px   +-------------------------------------------------------+
           | 1. HEADER REGION (Height: 20 px, Y = 0..20)           |
           | Title, status flag, or category (14pt Bold Centered)  |
Y = 20 px  |-------------------------------------------------------| (1 px Solid Border)
           |                                                       |
           | 2. MAIN BODY CONTENT REGION (Height: 128 px)          |
           | Available: Y = 22 to 148 px                           |
           |                                                       |
           | Telemetry values, psychrometric dew point, gauge arc, |
           | QR provisioning canvas, or multi-field sensor rows.   |
           |                                                       |
Y = 148 px |-------------------------------------------------------|
           | 3. FOOTER / ACTION REGION (Height: 50 px)             |
           | Y = 150 px: Primary Status / Value                    |
           | Y = 170 px: Secondary Physical Button Action Hint    |
Y = 200 px +-------------------------------------------------------+
```

* **Header:** Maintain a 1 px solid bottom border (`LV_BORDER_SIDE_BOTTOM`).
* **Clearance:** Maintain a minimum 4 px vertical clearance between stacked labels to prevent ink bleeding.
* **Padding:** Provide at least 6 px horizontal margin from left/right screen edges (`X = 6..194 px`, max string width $\le 188.0\text{ px}$).

---

## 4. Typography & Font Constraints

1. **Minimum Readable Font Size Mandate (≥ 14 px Height):**
   - **Minimum font height is 14 pixels** (e.g. `LV_FONT_MONTSERRAT_14` / `H1OS_FONT_14`).
   - Fonts smaller than 14 px (e.g. 8pt, 10pt, 12pt) are **STRICTLY FORBIDDEN**. At 188 DPI, glyph strokes narrower than 2 physical pixels blur into illegibility during differential partial updates.
2. **Emphasis Hierarchy:**
   - Large Telemetry Metric: 24 px to 32 px height.
   - Header & Subtitle: 14 px height bold / uppercase.
   - Action & Button Hints: 14 px regular height.

---

## 5. QR Code Integer Scaling Constraints

When rendering Wi-Fi provisioning or pairing QR codes onto 1-bit e-Paper:

* **Whole-Factor Integer Scaling Mandate:**

$$\text{Canvas Dimension} = (\text{Base Modules} + 8\text{ Quiet Zone}) \times \text{Scale Factor}$$

* **Minimum Module Width:** The scale factor MUST be an exact integer $\ge 3$ pixels per module. (Sub-pixel scaling or float scaling causes black/white module edge collision).
* **Standard JSON Provisioning Dimensioning:**
  - Version 4/5 QR code (41 modules including quiet zone):
    - Scale 3x: **$123 \times 123\text{ px}$ canvas** (Fits centered in Y = 22..148 body region).
    - Scale 4x: **$164 \times 164\text{ px}$ canvas**.

---

## 6. E-Paper Refresh Dynamics & Settling Invariants

1. **Differential Partial Refresh:** Used during active Flow B user sessions for sub-400ms flicker-free blits.
2. **Periodic Full OTP Refresh:** Executed during cold boot or every 5 partial cycles (`SUB_DISPLAY_PARTIAL_QUOTA = 5`) to fully clear residual electrophoretic charge accumulation.
3. **Mandatory 250 ms Microcapsule Settling Delay (`REV-04`):**
   - Inside `sub_display_enter_deep_sleep()`, after the SSD1681 `BUSY` (`GPIO 8`) falling-edge interrupt semaphore releases, the driver enforces a mandatory **250 ms physical settling delay** (`SUB_DISPLAY_SETTLING_WINDOW_MS`) before sending deep sleep command `0x10` (`0x01`).
   - Cutting charge-pump rails while pigment microcapsules are migrating permanently degrades panel contrast.

---

## 7. Thread Safety, Dual-Core Affinity & `h1os_ui_post()` Actor Queue (`v2.4.5-dev`)

* **Core Affinity:** The LVGL presentation task (`h1os_lvgl`) is pinned strictly to **Core 1** at FreeRTOS priority **5** (`LVGL_TASK_PRIO_PORT = 5`). Core 0 handles lifecycle orchestration, `on_sync()` wireless stacks, and background I/O.
* **Lifecycle Hook Context (`on_boot` & `on_wake`):** During `on_boot()` and `on_wake()`, the Core 1 LVGL task has not yet been started (`h1os_lvgl_start(5, 1)` runs immediately after `on_wake()` returns). Initial screen construction inside `on_boot()` and `on_wake()` is therefore inherently single-threaded; `h1os_trigger_splash()` acquires a scoped `h1os_lvgl_lock(1000)` internally.
* **Preferred Cross-Core Mutation (`h1os_ui_post` Actor Queue):** Once `h1os_lvgl_start(5, 1)` is running, Core 0 tasks (`on_sync`, Wi-Fi/BLE callbacks, background workers) should post UI updates via the non-blocking 16-slot static actor queue:
  ```c
  static void ui_apply_remote_temp(void *arg)
  {
      int32_t remote_centi_c = (int32_t)(intptr_t)arg;
      lv_label_set_text_fmt(s_lbl_remote, "Remote: %ld.%02ld C",
                            (long)(remote_centi_c / 100),
                            (long)labs(remote_centi_c % 100));
  }

  /* From Core 0 on_sync() or network callback: */
  ESP_ERROR_CHECK(h1os_ui_post(ui_apply_remote_temp, (void *)(intptr_t)2345, 50));
  ```
  Core 1 wakes immediately via `xTaskNotifyGive()` and drains all queued callbacks **inside `h1os_lvgl_lock(100)`** immediately prior to `lv_timer_handler()`.
* **Direct Recursive Mutex Guard (`h1os_lvgl_lock(timeout_ms)`):** When direct synchronous locking is required from another task, always pass an explicit `timeout_ms` argument and check the boolean return value:
  ```c
  if (h1os_lvgl_lock(100)) {
      /* Modify LVGL objects */
      h1os_lvgl_unlock();
  }
  ```

---

## 8. Canonical Screen Construction Pattern

```c
#include "h1os/h1os_lvgl.h"
#include "lvgl.h"

void ui_render_telemetry_screen(const char *title, float temp_c, float rh_pct, float dew_point_c)
{
    if (!h1os_lvgl_lock(200)) {
        return;
    }

    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // 1. Header (200x20 px)
    lv_obj_t *header = lv_obj_create(scr);
    lv_obj_set_size(header, 200, 20);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(header, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(header, lv_color_black(), 0);
    lv_obj_set_style_border_width(header, 1, 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header, 1, 0);

    lv_obj_t *lbl_title = lv_label_create(header);
    lv_label_set_text(lbl_title, title ? title : "TELEMETRY");
    lv_obj_set_style_text_color(lbl_title, lv_color_black(), 0);
    lv_obj_align(lbl_title, LV_ALIGN_CENTER, 0, 0);

    // 2. Main Body Content (Y = 22..148 px)
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f C", temp_c);
    lv_obj_set_style_text_color(lbl_temp, lv_color_black(), 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_MID, 0, 36);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f %% RH  |  Td: %.1f C", rh_pct, dew_point_c);
    lv_obj_set_style_text_color(lbl_rh, lv_color_black(), 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_MID, 0, 80);

    // 3. Footer Action Hint (Y = 150..200 px)
    lv_obj_t *lbl_hint = lv_label_create(scr);
    lv_label_set_text(lbl_hint, "BOOT: Cycle  |  HOLD: Sleep");
    lv_obj_set_style_text_color(lbl_hint, lv_color_black(), 0);
    lv_obj_align(lbl_hint, LV_ALIGN_TOP_MID, 0, 168);

    h1os_lvgl_unlock();
}
```

---

## 9. Font Metric Tables & String Width Verification Tools

To prevent horizontal text clipping and overflow on the 200x200 display (maximum allowable width $\le 188.0\text{ px}$):

### Font Metric CSV Tables (`tools/fonts/`)
- **Character Advance Widths & Bounding Boxes:**
  - `tools/fonts/char_widths_montserrat_14.csv`
  - `tools/fonts/char_widths_montserrat_16.csv`
  - `tools/fonts/char_widths_montserrat_18.csv`
  - `tools/fonts/char_widths_montserrat_20.csv`
  - `tools/fonts/char_widths_montserrat_24.csv`
  - `tools/fonts/char_widths_montserrat_32.csv`
- **Class Kerning Pairs (3,400+ pairs per font):**
  - `tools/fonts/kern_pairs_montserrat_14.csv`
  - `tools/fonts/kern_pairs_montserrat_16.csv`
  - `tools/fonts/kern_pairs_montserrat_18.csv`
  - `tools/fonts/kern_pairs_montserrat_20.csv`
  - `tools/fonts/kern_pairs_montserrat_24.csv`
  - `tools/fonts/kern_pairs_montserrat_32.csv`

### Verification Tools
* **Single String Width Calculation (CLI):**
  ```powershell
  python tools/agent/check_string_width.py --size 14 "Power: CHARGED 4.00V"
  ```
* **Full Screen Template Automated Audit:**
  ```powershell
  python tools/agent/check_string_width.py --audit-screens
  ```
* **Font Metric Extractor:**
  ```powershell
  python tools/agent/extract_font_metrics.py
  ```
* **DuckDB SQL Query:**
  ```sql
  SELECT char, width_px FROM 'tools/fonts/char_widths_montserrat_14.csv' ORDER BY width_px DESC LIMIT 10;
  ```
