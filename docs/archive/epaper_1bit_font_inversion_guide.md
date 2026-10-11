# E-Paper 1-Bit Font Conversion & Inversion Guide

## 1. Problem Statement: Why Inverted Text Breaks on E-Paper

Standard LVGL font assets (such as `lv_font_montserrat_14`) are compiled by default with **4-bpp anti-aliasing** (16 shades of gray).

### The Math Behind Glyph Erosion in 1-Bit Mode (`LV_COLOR_FORMAT_I1`)
1. **Normal Text (Black on White Background)**:
   - Screen background is `1` (White), glyph core is `0` (Black).
   - Semi-transparent edge pixels (anti-aliasing) get thresholded at $\ge 128$. Any value below 128 snaps to `0` (black).
   - This expands/dilates the black characters outward by ~0.5 to 1.0 pixel, making them crisp and legible.

2. **Inverted Text (White on Black Background)**:
   - Screen background is `0` (Black), glyph core is `1` (White).
   - During blending, anti-aliased edge pixels below the 128 threshold snap to `0` (the background color).
   - This **erodes the white character inward from all perimeter edges**.
   - Because a 14pt stroke on a 188 DPI panel is only 1.5 to 2.0 pixels wide, losing 1 pixel from each side collapses the character stroke to **0 or fractional pixels**, causing letters to fragment into unreadable dots.

---

## 2. Solution: Bilevel (1-bpp) Fonts

By compiling font glyphs with `--bpp 1`, every pixel in the font matrix is strictly binary: `0` or `1`. There is no anti-aliasing, no alpha channel, and no intermediate grayscale blending.

### Benefits
- **Symmetric Rendering**: White-on-black and black-on-white render with the **exact same stroke geometry**.
- **50% Flash Savings**:
  - 4-bpp `lv_font_montserrat_14.c`: ~93.6 KB
  - 1-bpp `bsp_font_montserrat_14_1bpp.c`: ~48.3 KB
- **Instant Bit-Blit**: Eliminates CPU cycles spent downsampling grayscale matrices in LVGL's software renderer.

---

## 3. Automated Generation Tool: `tools/generate_1bpp_fonts.py`

The repository includes an automated Python generator: [`tools/generate_1bpp_fonts.py`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/tools/generate_1bpp_fonts.py).

### Prerequisites
- Python 3.8+
- Node.js & npm (comes with `npx` for executing `lv_font_conv`)

### CLI Usage
To generate the default sizes (14px and 20px):
```bash
python tools/generate_1bpp_fonts.py
```

To generate specific sizes (e.g., 12px, 16px, 24px):
```bash
python tools/generate_1bpp_fonts.py --sizes 12 16 24
```

### Script Execution Pipeline
1. **Source Discovery**: Automatically locates the base `Montserrat-Medium.ttf` and `FontAwesome5-Solid+Brands+Regular.woff` font files across standard local folders.
2. **Range Packing**:
   - ASCII Range: `0x20-0x7F` (Basic Latin, numbers, punctuation)
   - Symbols: `0xB0` (Degree symbol `°`), `0x2022` (Bullet `•`)
   - FontAwesome: Essential IoT icons (battery, wifi, alerts, thermometers).
3. **Bilevel Compilation**: Invokes `lv_font_conv --bpp 1 --no-compress --no-prefilter --force-fast-kern-format`.
4. **Header Sanitization**: Replaces multi-platform `#ifdef LV_LVGL_H_INCLUDE_SIMPLE` includes with standard ESP-IDF `#include "lvgl.h"`.
5. **Output**: Writes production files directly to `components/esp32-s3_bsp/src/`.

---

## 4. How to Use 1-bpp Fonts in Code

### Declared Descriptors in `bsp/bsp_lvgl.h`
```c
#include "bsp/bsp_lvgl.h"

// Available 1-bpp font descriptors:
extern const lv_font_t bsp_font_montserrat_14_1bpp;
extern const lv_font_t bsp_font_montserrat_20_1bpp;
```

### Applying to Widgets
```c
lv_obj_t *label = lv_label_create(parent);
lv_label_set_text(label, "72.4°F  58.2% RH");
lv_obj_set_style_text_font(label, &bsp_font_montserrat_14_1bpp, 0);
```

### Inverted Card Containers (`bsp_lvgl_create_card`)
To create a card that inverts upon alarm or threshold breach:
```c
// 1. Create a byte-aligned card (width = 192, height = 50, inverted = true)
lv_obj_t *alert_card = bsp_lvgl_create_card(scr, 192, 50, true);
lv_obj_align(alert_card, LV_ALIGN_CENTER, 0, 0);

// 2. Add text inside card
lv_obj_t *lbl_alert = lv_label_create(alert_card);
lv_label_set_text(lbl_alert, "! HIGH HUMIDITY ALERT !");
lv_obj_set_style_text_font(lbl_alert, &bsp_font_montserrat_14_1bpp, 0);

// 3. Dynamically toggle normal / inverted state at runtime
bsp_lvgl_set_card_inverted(alert_card, is_alarm_active);
```
