/*******************************************************************************
 * Font: humid1_font_bitter_bold_20 (bitter bold)
 * Size: 20 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_fira_sans_bold_20 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef HUMID1_FONT_BITTER_BOLD_20
#define HUMID1_FONT_BITTER_BOLD_20 1
#endif

#if HUMID1_FONT_BITTER_BOLD_20

extern const lv_font_t humid1_font_fira_sans_bold_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x14) */
    0xff, 0xff, 0xff, 0xf7, 0x70, 0x0f, 0xff,
    /* U+0022 "" (8x6) */
    0xe6, 0xef, 0xee, 0xee, 0xe6, 0xe6,
    /* U+0023 "#" (13x14) */
    0x1e, 0x70, 0xf3, 0x87, 0x3c, 0xff, 0xf7, 0xff, 0x8e, 0x70, 0x73, 0x87,
    0x9c, 0x3d, 0xe7, 0xff, 0x9f, 0xfc, 0x73, 0x83, 0x9c, 0x1c, 0xe0,
    /* U+0024 "$" (10x20) */
    0x0c, 0x03, 0x00, 0xc0, 0xfe, 0x7f, 0xfc, 0xff, 0x1f, 0xc0, 0xfc, 0x1f,
    0xe3, 0xfc, 0x1f, 0xc3, 0xf0, 0xff, 0x7f, 0xfe, 0x7e, 0x03, 0x00, 0xc0,
    0x30,
    /* U+0025 "%" (17x14) */
    0x3e, 0x1e, 0x3f, 0x8e, 0x19, 0xce, 0x1c, 0xe7, 0x06, 0x77, 0x03, 0xf7,
    0x00, 0xf3, 0x80, 0x03, 0xbe, 0x03, 0xbf, 0x81, 0xdd, 0xc1, 0xce, 0xe1,
    0xc7, 0x70, 0xe3, 0xf8, 0xe0, 0xf8,
    /* U+0026 "&" (12x14) */
    0x3f, 0xc7, 0xfc, 0xf1, 0xcf, 0x18, 0xf0, 0x07, 0xc0, 0x3f, 0xf7, 0xfe,
    0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x3c, 0xff, 0xc3, 0xf0,
    /* U+0027 "'" (3x6) */
    0xff, 0xff, 0xc0,
    /* U+0028 "(" (6x21) */
    0x08, 0x73, 0xce, 0x79, 0xe7, 0x1c, 0xf3, 0xcf, 0x3c, 0xf1, 0xc7, 0x1e,
    0x78, 0xe3, 0xc7, 0x08,
    /* U+0029 ")" (6x21) */
    0x63, 0x87, 0x1e, 0x78, 0xe3, 0xcf, 0x3c, 0xf1, 0xcf, 0x3c, 0xf3, 0xce,
    0x79, 0xe7, 0x38, 0x60,
    /* U+002A "" (7x6) */
    0x30, 0x63, 0xfb, 0x47, 0x8d, 0x80,
    /* U+002B "+" (10x10) */
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0xff, 0xff, 0xf0, 0xe0, 0x38, 0x0e, 0x03,
    0x80,
    /* U+002C "," (4x7) */
    0xef, 0xfe, 0xec, 0x80,
    /* U+002D "-" (7x3) */
    0xff, 0xff, 0xf0,
    /* U+002E "." (5x3) */
    0x77, 0xdc,
    /* U+002F "/" (7x18) */
    0x06, 0x1c, 0x38, 0x71, 0xc3, 0x87, 0x0c, 0x38, 0x70, 0xc3, 0x87, 0x0e,
    0x18, 0x70, 0xe1, 0x80,
    /* U+0030 "0" (11x14) */
    0x3f, 0x8f, 0xfb, 0xcf, 0x78, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xfe, 0x3f, 0xc7, 0xfd, 0xe7, 0xfc, 0x7e, 0x00,
    /* U+0031 "1" (9x14) */
    0x1e, 0x3f, 0x3f, 0x8f, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x07,
    0x83, 0xc7, 0xfb, 0xfc,
    /* U+0032 "2" (10x14) */
    0xff, 0x3f, 0xee, 0x7f, 0x0f, 0x03, 0xc1, 0xf0, 0x78, 0x3c, 0x1f, 0x0f,
    0x8f, 0xc3, 0xff, 0xff, 0xff, 0xf0,
    /* U+0033 "3" (10x14) */
    0xff, 0xbf, 0xec, 0x7f, 0x0f, 0x03, 0xc3, 0xe3, 0xf0, 0xfe, 0x03, 0xc0,
    0xf0, 0x3f, 0x1f, 0xff, 0xbf, 0xc0,
    /* U+0034 "4" (13x14) */
    0x07, 0xe0, 0x3f, 0x03, 0xf8, 0x3f, 0xc1, 0xfe, 0x1e, 0xf1, 0xe7, 0x8f,
    0x3c, 0xff, 0xf7, 0xff, 0xff, 0xfe, 0x03, 0xc0, 0x1e, 0x00, 0xf0,
    /* U+0035 "5" (11x14) */
    0x7f, 0xcf, 0xf9, 0xf0, 0x3c, 0x07, 0x80, 0xfe, 0x1f, 0xf3, 0xfe, 0x03,
    0xe0, 0x7c, 0x0f, 0xbb, 0xef, 0xfc, 0xff, 0x00,
    /* U+0036 "6" (12x14) */
    0x0f, 0xc1, 0xfc, 0x3e, 0x07, 0x80, 0x78, 0x07, 0xf8, 0xff, 0xef, 0xfe,
    0xf9, 0xf7, 0x8f, 0x79, 0xf7, 0xde, 0x3f, 0xe1, 0xf8,
    /* U+0037 "7" (11x14) */
    0xff, 0xff, 0xff, 0xff, 0xf1, 0xf0, 0x3c, 0x07, 0x81, 0xe0, 0x3c, 0x0f,
    0x81, 0xe0, 0x7c, 0x0f, 0x03, 0xe0, 0x7c, 0x00,
    /* U+0038 "8" (12x14) */
    0x1f, 0xc7, 0xfe, 0x79, 0xe7, 0x9e, 0x79, 0xe7, 0xfc, 0x3f, 0xc3, 0xfe,
    0x79, 0xef, 0x0f, 0xf0, 0xf7, 0x9e, 0x7f, 0xe3, 0xf8,
    /* U+0039 "9" (11x14) */
    0x3f, 0x8f, 0xf9, 0xe7, 0xf8, 0xff, 0x1f, 0xf3, 0xdf, 0xfb, 0xff, 0x1d,
    0xe0, 0x3c, 0x0f, 0x83, 0xe3, 0xf8, 0xfe, 0x00,
    /* U+003A ":" (5x10) */
    0x77, 0xdc, 0x00, 0x00, 0x0e, 0xfb, 0x80,
    /* U+003B ";" (5x14) */
    0x73, 0xdc, 0x00, 0x00, 0x0e, 0xfb, 0x9c, 0xee, 0x20,
    /* U+003C "<" (10x10) */
    0x01, 0x81, 0xf1, 0xf9, 0xf8, 0xf8, 0x3f, 0x07, 0xf0, 0x7f, 0x03, 0xc0,
    0x20,
    /* U+003D "=" (10x6) */
    0xff, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xf0,
    /* U+003E ">" (9x9) */
    0x40, 0x78, 0x3f, 0x87, 0xf0, 0xf8, 0x7c, 0xfd, 0xf8, 0xe0, 0x00,
    /* U+003F "?" (9x14) */
    0xff, 0x3f, 0xc1, 0xe0, 0xf0, 0x78, 0xf8, 0xf0, 0x78, 0x38, 0x00, 0x00,
    0x07, 0x83, 0xc1, 0xe0,
    /* U+0040 "@" (16x15) */
    0x0f, 0xf0, 0x3f, 0xf8, 0x78, 0x1c, 0x73, 0xce, 0xe7, 0xef, 0xe0, 0xe7,
    0xe0, 0xe7, 0xe7, 0xe7, 0xee, 0xe7, 0xee, 0xe6, 0xef, 0xfe, 0xe6, 0x38,
    0x70, 0x00, 0x3f, 0xc0, 0x1f, 0xc0,
    /* U+0041 "A" (14x14) */
    0x07, 0xc0, 0x1f, 0x00, 0xfc, 0x03, 0xf8, 0x0f, 0xe0, 0x77, 0x81, 0xcf,
    0x0f, 0x3c, 0x3f, 0xf0, 0xff, 0xe7, 0x87, 0x9e, 0x1e, 0xf8, 0xff, 0xf3,
    0xf0,
    /* U+0042 "B" (12x14) */
    0xff, 0xc7, 0xfe, 0x3d, 0xf3, 0xcf, 0x3c, 0xf3, 0xde, 0x3f, 0xc3, 0xfe,
    0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xdf, 0x7f, 0xff, 0xfc,
    /* U+0043 "C" (11x14) */
    0x1f, 0xcf, 0xfd, 0xe3, 0xf8, 0x7f, 0x01, 0xe0, 0x3c, 0x07, 0x80, 0xf0,
    0x1e, 0x03, 0xe0, 0x3e, 0xe7, 0xfe, 0x3f, 0x00,
    /* U+0044 "D" (14x14) */
    0xff, 0xc1, 0xff, 0xc3, 0xcf, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xf3, 0xc7,
    0xcf, 0x1f, 0x3c, 0x7c, 0xf1, 0xe3, 0xc7, 0x8f, 0x7c, 0x7f, 0xe3, 0xff,
    0x00,
    /* U+0045 "E" (11x14) */
    0xff, 0xef, 0xfc, 0xf3, 0x9e, 0x33, 0xc0, 0x78, 0x0f, 0xe1, 0xfc, 0x3c,
    0x07, 0x80, 0xf1, 0x9e, 0x77, 0xff, 0xff, 0xc0,
    /* U+0046 "F" (11x14) */
    0xff, 0xef, 0xfc, 0xf3, 0x9e, 0x33, 0xc0, 0x78, 0x0f, 0xe1, 0xfc, 0x3c,
    0x07, 0x80, 0xf0, 0x1e, 0x07, 0xe1, 0xfc, 0x00,
    /* U+0047 "G" (14x14) */
    0x0f, 0xf0, 0xff, 0xe3, 0xe7, 0x9f, 0x0e, 0x78, 0x01, 0xe0, 0x0f, 0x80,
    0x3e, 0x3f, 0x78, 0xf9, 0xe1, 0xe7, 0xc7, 0x8f, 0xbe, 0x3f, 0xf8, 0x3f,
    0xc0,
    /* U+0048 "H" (15x14) */
    0xfe, 0x7e, 0xfc, 0xfc, 0xf0, 0xf1, 0xe1, 0xe3, 0xc3, 0xc7, 0x87, 0x8f,
    0xff, 0x1f, 0xfe, 0x3c, 0x3c, 0x78, 0x78, 0xf0, 0xf1, 0xe1, 0xe7, 0xe7,
    0xff, 0xcf, 0xc0,
    /* U+0049 "I" (7x14) */
    0xfe, 0xfc, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0xff,
    0xc0,
    /* U+004A "J" (8x18) */
    0x7f, 0x7f, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e,
    0x3e, 0x3e, 0x3c, 0xfc, 0xf8, 0xe0,
    /* U+004B "K" (14x14) */
    0xfe, 0xfd, 0xfb, 0xf3, 0xc7, 0x0f, 0x3c, 0x3c, 0xe0, 0xf7, 0x83, 0xfc,
    0x0f, 0xf8, 0x3d, 0xe0, 0xf3, 0xc3, 0xcf, 0x0f, 0x1e, 0x7e, 0xff, 0xfb,
    0xf0,
    /* U+004C "L" (11x14) */
    0xfe, 0x0f, 0xc0, 0xf0, 0x1e, 0x03, 0xc0, 0x78, 0x0f, 0x01, 0xe0, 0x3c,
    0x07, 0x80, 0xf3, 0x9e, 0x77, 0xff, 0xff, 0xc0,
    /* U+004D "M" (16x14) */
    0xfc, 0x3f, 0xfc, 0x3e, 0x7c, 0x7c, 0x7e, 0x7c, 0x7e, 0xfc, 0x7e, 0xfc,
    0x77, 0xdc, 0x77, 0xdc, 0x77, 0x9c, 0x73, 0x9c, 0x70, 0x1c, 0x70, 0x1c,
    0xf8, 0x3e, 0xf8, 0x3f,
    /* U+004E "N" (15x14) */
    0xfe, 0x7e, 0xfc, 0xfc, 0xfc, 0xf1, 0xf9, 0xe3, 0xf3, 0xc7, 0xf7, 0x8e,
    0xef, 0x1d, 0xfe, 0x39, 0xfc, 0x73, 0xf8, 0xe7, 0xf1, 0xc7, 0xe7, 0xcf,
    0xdf, 0x8f, 0x80,
    /* U+004F "O" (13x14) */
    0x1f, 0xc3, 0xff, 0x1e, 0x7d, 0xe1, 0xef, 0x07, 0xf8, 0x3f, 0xc1, 0xfe,
    0x0f, 0xf0, 0x7f, 0x87, 0xfc, 0x3d, 0xf3, 0xe7, 0xfe, 0x0f, 0xc0,
    /* U+0050 "P" (12x14) */
    0xff, 0xc7, 0xfe, 0x3d, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3d, 0xf3, 0xfe,
    0x3f, 0xc3, 0xc0, 0x3c, 0x03, 0xc0, 0x7e, 0x0f, 0xe0,
    /* U+0051 "Q" (15x18) */
    0x1f, 0xc0, 0xff, 0xc1, 0xe3, 0xc7, 0x87, 0x8f, 0x07, 0x9e, 0x0f, 0x3c,
    0x1e, 0x78, 0x3c, 0xf0, 0x79, 0xe0, 0xf3, 0xc3, 0xc3, 0xcf, 0x87, 0xfe,
    0x03, 0xf8, 0x00, 0xf0, 0x00, 0xff, 0x00, 0xfe, 0x00, 0x78,
    /* U+0052 "R" (13x14) */
    0xff, 0xe3, 0xff, 0x8f, 0x3c, 0x79, 0xf3, 0xcf, 0x9e, 0x78, 0xff, 0xc7,
    0xf8, 0x3f, 0xc1, 0xef, 0x0f, 0x3c, 0x79, 0xe7, 0xe7, 0xff, 0x3c,
    /* U+0053 "S" (11x14) */
    0x3f, 0xdf, 0xfb, 0xc7, 0x78, 0xef, 0x01, 0xfc, 0x1f, 0xe1, 0xfe, 0x07,
    0xd8, 0x7f, 0x07, 0xf1, 0xef, 0xfd, 0xfe, 0x00,
    /* U+0054 "T" (13x14) */
    0xff, 0xff, 0xff, 0xfb, 0xff, 0xde, 0x70, 0xf0, 0x07, 0x80, 0x3c, 0x01,
    0xe0, 0x0f, 0x00, 0x78, 0x03, 0xc0, 0x1e, 0x01, 0xfc, 0x0f, 0xe0,
    /* U+0055 "U" (15x14) */
    0xfe, 0xff, 0xf9, 0xf9, 0xe1, 0xe3, 0xc3, 0xc7, 0x87, 0x8f, 0x0f, 0x1e,
    0x1e, 0x3c, 0x3c, 0x78, 0x78, 0xf0, 0xf0, 0xf1, 0xe1, 0xe7, 0xc3, 0xff,
    0x01, 0xfc, 0x00,
    /* U+0056 "V" (15x14) */
    0xfe, 0x7f, 0xf8, 0xf9, 0xf0, 0xe3, 0xe3, 0xc3, 0xc7, 0x87, 0x8e, 0x0f,
    0xbc, 0x0f, 0x78, 0x1e, 0xe0, 0x3f, 0xc0, 0x3f, 0x80, 0x7e, 0x00, 0xfc,
    0x00, 0xf8, 0x00,
    /* U+0057 "W" (20x14) */
    0xfc, 0xf1, 0xff, 0xcf, 0x9f, 0x78, 0xf8, 0xe7, 0x8f, 0x8e, 0x3d, 0xf9,
    0xe3, 0xdf, 0xdc, 0x3d, 0xfd, 0xc3, 0xdd, 0xdc, 0x1f, 0x9f, 0xc1, 0xf9,
    0xf8, 0x1f, 0x9f, 0x81, 0xf8, 0xf8, 0x0f, 0x0f, 0x00, 0xf0, 0xf0,
    /* U+0058 "X" (14x14) */
    0xfe, 0x7d, 0xf9, 0xf3, 0xc7, 0x8f, 0x9c, 0x1f, 0xe0, 0x3f, 0x00, 0x7c,
    0x01, 0xf0, 0x0f, 0xe0, 0x77, 0xc3, 0xcf, 0x0e, 0x1e, 0xfc, 0xff, 0xf3,
    0xf0,
    /* U+0059 "Y" (13x14) */
    0xfc, 0xff, 0xe7, 0xde, 0x3c, 0x79, 0xc3, 0xce, 0x0f, 0xe0, 0x7f, 0x01,
    0xf0, 0x0f, 0x80, 0x7c, 0x03, 0xe0, 0x1f, 0x01, 0xfc, 0x0f, 0xe0,
    /* U+005A "Z" (12x14) */
    0x7f, 0xf7, 0xff, 0x71, 0xf6, 0x3e, 0x03, 0xc0, 0x78, 0x0f, 0x80, 0xf0,
    0x1e, 0x03, 0xe0, 0x7c, 0x77, 0xc7, 0xff, 0xff, 0xff,
    /* U+005B "[" (6x19) */
    0xff, 0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xff, 0xc0,
    /* U+005C "" (8x18) */
    0xe0, 0xe0, 0x60, 0x70, 0x70, 0x70, 0x38, 0x38, 0x38, 0x18, 0x1c, 0x1c,
    0x1c, 0x0e, 0x0e, 0x0e, 0x06, 0x07,
    /* U+005D "]" (6x19) */
    0xff, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x3f, 0xff, 0xc0,
    /* U+005E "^" (10x7) */
    0x0e, 0x07, 0xc1, 0xf0, 0xfe, 0x3b, 0x9c, 0xff, 0x1c,
    /* U+005F "_" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+0060 "`" (6x5) */
    0x43, 0x8f, 0x8f, 0x08,
    /* U+0061 "a" (11x11) */
    0x3f, 0x8f, 0xf9, 0xcf, 0x39, 0xe0, 0x3c, 0x7f, 0x9f, 0xf7, 0x9e, 0xf3,
    0xcf, 0xfd, 0xf7, 0x80,
    /* U+0062 "b" (12x16) */
    0x38, 0x0f, 0x80, 0x78, 0x07, 0x80, 0x78, 0x07, 0xb8, 0x7f, 0xe7, 0xde,
    0x79, 0xe7, 0x8f, 0x78, 0xf7, 0x8f, 0x79, 0xe7, 0x9e, 0x7f, 0xc7, 0xf8,
    /* U+0063 "c" (10x11) */
    0x1f, 0x8f, 0xf7, 0x9d, 0xe7, 0xf0, 0x3c, 0x0f, 0x01, 0xe0, 0x78, 0x8f,
    0xf1, 0xf8,
    /* U+0064 "d" (12x16) */
    0x01, 0xe0, 0x3e, 0x01, 0xe0, 0x1e, 0x01, 0xe1, 0xfe, 0x3f, 0xe7, 0xde,
    0x79, 0xef, 0x9e, 0xf1, 0xef, 0x1e, 0xf9, 0xe7, 0x9e, 0x7f, 0xf3, 0xef,
    /* U+0065 "e" (11x11) */
    0x1f, 0x07, 0xf9, 0xef, 0x38, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xc0, 0x78,
    0xcf, 0xf8, 0x7e, 0x00,
    /* U+0066 "f" (9x16) */
    0x0f, 0x8f, 0xcf, 0xc7, 0x83, 0x83, 0xf3, 0xfc, 0xf8, 0x38, 0x1c, 0x0e,
    0x07, 0x03, 0x81, 0xc1, 0xf8, 0xfc,
    /* U+0067 "g" (12x16) */
    0x1f, 0xe7, 0xfe, 0x7b, 0xef, 0x1e, 0xf1, 0xe7, 0xbc, 0x7f, 0xc3, 0xf0,
    0x70, 0x07, 0xfc, 0x7f, 0xe7, 0xff, 0xe0, 0xff, 0x1e, 0xff, 0xe3, 0xf8,
    /* U+0068 "h" (13x16) */
    0x78, 0x07, 0xc0, 0x1e, 0x00, 0xf0, 0x07, 0x80, 0x3d, 0xe1, 0xff, 0x8f,
    0xfe, 0x78, 0xf3, 0xc7, 0x9e, 0x3c, 0xf1, 0xe7, 0x8f, 0x3c, 0x7b, 0xf7,
    0xff, 0xbf,
    /* U+0069 "i" (7x16) */
    0x38, 0xf9, 0xf1, 0xc0, 0x0f, 0x3e, 0x3c, 0x38, 0x70, 0xe1, 0xc3, 0x87,
    0x1f, 0x7f,
    /* U+006A "j" (6x21) */
    0x18, 0xf3, 0xc6, 0x01, 0xf7, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x3c, 0xff, 0xfe, 0xe0,
    /* U+006B "k" (12x16) */
    0x38, 0x0f, 0x80, 0x78, 0x07, 0x80, 0x78, 0x07, 0x9f, 0x79, 0xf7, 0x9e,
    0x79, 0xc7, 0xf8, 0x7f, 0x87, 0xbc, 0x79, 0xc7, 0x9e, 0xfc, 0xff, 0xcf,
    /* U+006C "l" (6x16) */
    0x7b, 0xe7, 0x9e, 0x79, 0xe7, 0x9e, 0x79, 0xe7, 0x9e, 0x79, 0xef, 0xff,
    /* U+006D "m" (19x11) */
    0x79, 0xc7, 0x1f, 0xff, 0xf1, 0xf7, 0xff, 0x1c, 0x79, 0xe3, 0x8f, 0x3c,
    0x71, 0xe7, 0x8e, 0x3c, 0xf1, 0xc7, 0x9e, 0x38, 0xf3, 0xcf, 0xbe, 0xff,
    0xf7, 0xdf, 0x80,
    /* U+006E "n" (12x11) */
    0xf3, 0x8f, 0xfc, 0xfb, 0xe7, 0x1e, 0x71, 0xe7, 0x1e, 0x71, 0xe7, 0x1e,
    0x71, 0xef, 0xbf, 0xfb, 0xf0,
    /* U+006F "o" (11x11) */
    0x1f, 0x87, 0xf9, 0xef, 0xbc, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0xcf, 0x79,
    0xef, 0xf8, 0xfe, 0x00,
    /* U+0070 "p" (12x16) */
    0xf3, 0xcf, 0xfe, 0x7d, 0xf7, 0x8f, 0x78, 0xf7, 0x8f, 0x78, 0xf7, 0x8f,
    0x79, 0xe7, 0xfe, 0x7f, 0xc7, 0x80, 0x78, 0x07, 0xc0, 0xfe, 0x07, 0xc0,
    /* U+0071 "q" (12x16) */
    0x0f, 0xe3, 0xfe, 0x7d, 0xe7, 0x9e, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x9e,
    0x79, 0xe7, 0xfe, 0x3f, 0xe0, 0x1e, 0x01, 0xe0, 0x1e, 0x03, 0xf0, 0x3f,
    /* U+0072 "r" (8x11) */
    0xf3, 0xff, 0xff, 0x73, 0x70, 0x70, 0x70, 0x70, 0x70, 0xfc, 0xfc,
    /* U+0073 "s" (9x11) */
    0x3f, 0x7f, 0xbd, 0xde, 0x0f, 0xc7, 0xf8, 0xfe, 0x1f, 0xc7, 0xff, 0xbf,
    0x80,
    /* U+0074 "t" (8x14) */
    0x08, 0x78, 0x78, 0x7f, 0xff, 0x7c, 0x78, 0x78, 0x78, 0x78, 0x78, 0x7c,
    0x3f, 0x3f,
    /* U+0075 "u" (13x11) */
    0xf9, 0xe7, 0xdf, 0x9e, 0x7c, 0xf1, 0xe7, 0x8f, 0x3c, 0x79, 0xe3, 0xcf,
    0x1e, 0x7d, 0xf3, 0xff, 0xcf, 0xbe,
    /* U+0076 "v" (11x11) */
    0xf9, 0xff, 0x7d, 0xe7, 0xbc, 0xe7, 0x9c, 0xf7, 0x8e, 0xe1, 0xfc, 0x3f,
    0x83, 0xe0, 0x7c, 0x00,
    /* U+0077 "w" (17x11) */
    0xf9, 0xe7, 0xfc, 0xf3, 0xdc, 0xf9, 0xef, 0x7e, 0xe7, 0xbf, 0x73, 0xdb,
    0xb8, 0xfd, 0xf8, 0x7e, 0xfc, 0x3f, 0x3e, 0x1f, 0x1f, 0x07, 0x8f, 0x00,
    /* U+0078 "x" (11x11) */
    0x7c, 0xff, 0xbd, 0xf7, 0x1f, 0xc1, 0xf8, 0x3e, 0x07, 0xc1, 0xfc, 0x3b,
    0xde, 0x7f, 0xdf, 0x80,
    /* U+0079 "y" (12x16) */
    0xf9, 0xff, 0x9f, 0x79, 0xe7, 0x9c, 0x39, 0xc3, 0xdc, 0x3f, 0x81, 0xf8,
    0x1f, 0x80, 0xf0, 0x0f, 0x00, 0xf0, 0x0e, 0x07, 0xe0, 0xfc, 0x0f, 0x00,
    /* U+007A "z" (9x11) */
    0xff, 0xff, 0xf3, 0xd9, 0xe1, 0xe1, 0xe0, 0xf0, 0xf3, 0xf3, 0xff, 0xff,
    0xe0,
    /* U+007B "{" (7x19) */
    0x1e, 0x7c, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0xf9, 0xe3, 0xe1, 0xc3, 0x87,
    0x0e, 0x1c, 0x38, 0x7c, 0x78,
    /* U+007C "|" (4x18) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (8x19) */
    0xf8, 0xf8, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x1e, 0x0f, 0x1e, 0x3c,
    0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xf8, 0xf8,
    /* U+007E "~" (10x4) */
    0x78, 0xbf, 0xfd, 0xf8, 0x0c,
    /* U+00B0 "" (8x7) */
    0x3c, 0x7e, 0x67, 0xe7, 0x67, 0x7e, 0x1c,
    /* U+00B1 "" (9x12) */
    0x1c, 0x0e, 0x07, 0x1f, 0xff, 0xff, 0xfc, 0x70, 0x38, 0x1c, 0x00, 0x3f,
    0xff, 0xf0,
    /* U+00B2 "" (7x9) */
    0x7d, 0xff, 0xb8, 0x71, 0xe7, 0x9e, 0x7f, 0xfe,
    /* U+00B3 "" (7x9) */
    0x7d, 0xff, 0x38, 0x73, 0xc7, 0xc3, 0xbf, 0xfc,
    /* U+00B5 "" (13x16) */
    0xf9, 0xf7, 0xcf, 0x9e, 0x3c, 0xf1, 0xe7, 0x8f, 0x3c, 0x79, 0xe3, 0xcf,
    0x1e, 0x7d, 0xf3, 0xff, 0xdf, 0xbe, 0xf0, 0x07, 0x80, 0x3c, 0x01, 0xe0,
    0x07, 0x00,
    /* U+00B7 "" (5x3) */
    0x77, 0xdc,
    /* U+00D7 "" (8x8) */
    0xc3, 0xe7, 0x7e, 0x7c, 0x3c, 0x7e, 0xe7, 0xc3,
    /* U+00F7 "" (10x10) */
    0x1e, 0x07, 0x81, 0xe0, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x78, 0x1e, 0x07,
    0x80,
    /* U+0394 "" (13x14) */
    0x07, 0x80, 0x7c, 0x03, 0xf0, 0x1f, 0x81, 0xfc, 0x0e, 0xf0, 0xf7, 0x87,
    0x1e, 0x38, 0xf3, 0x87, 0x9c, 0x1f, 0xe0, 0xff, 0xff, 0xff, 0xfc,
    /* U+03A9 "" (13x14) */
    0x1f, 0xc1, 0xff, 0x9e, 0x3c, 0xf0, 0xff, 0x07, 0xf8, 0x3f, 0xc1, 0xfe,
    0x0f, 0xf0, 0x7f, 0x83, 0xde, 0x3c, 0x71, 0xcf, 0xdf, 0xfe, 0xfc,
    /* U+03BC "" (13x16) */
    0xf9, 0xf7, 0xcf, 0x9e, 0x3c, 0xf1, 0xe7, 0x8f, 0x3c, 0x79, 0xe3, 0xcf,
    0x1e, 0x7d, 0xf3, 0xff, 0xdf, 0xbe, 0xf0, 0x07, 0x80, 0x3c, 0x01, 0xe0,
    0x07, 0x00,
    /* U+03C0 "" (13x11) */
    0x7f, 0xf7, 0xff, 0xdf, 0xfc, 0x71, 0xc3, 0x8e, 0x1c, 0x70, 0xe3, 0x87,
    0x1c, 0x38, 0xf3, 0xe7, 0xff, 0x1e,
    /* U+2013 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2014 "" (15x2) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+2018 "" (4x7) */
    0x13, 0x76, 0xff, 0x60,
    /* U+2019 "" (4x7) */
    0x77, 0x77, 0x6e, 0x40,
    /* U+201C "" (9x7) */
    0x11, 0x99, 0x99, 0xdc, 0xef, 0x77, 0xb8, 0x88,
    /* U+201D "" (8x7) */
    0x66, 0xff, 0xf7, 0x67, 0xe6, 0xcc, 0x80,
    /* U+2022 "" (8x7) */
    0x18, 0x7e, 0xfe, 0xff, 0xff, 0xfe, 0x7c,
    /* U+2026 "" (16x3) */
    0x73, 0xce, 0xfb, 0xdf, 0x73, 0xce,
    /* U+2030 "" (25x14) */
    0x3e, 0x1e, 0x00, 0x3f, 0x8e, 0x00, 0x19, 0xce, 0x00, 0x1c, 0xe7, 0x00,
    0x06, 0x77, 0x00, 0x03, 0xf7, 0x00, 0x00, 0xf3, 0x80, 0x00, 0x03, 0xbe,
    0x3e, 0x03, 0xbf, 0x9f, 0x81, 0xdd, 0xdc, 0xc1, 0xce, 0x6e, 0x61, 0xc7,
    0x77, 0x30, 0xe3, 0xfb, 0xf8, 0xe0, 0xf8, 0xf8,
    /* U+2190 "" (14x13) */
    0x0c, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0xff, 0xff, 0xff,
    0xfe, 0x00, 0x78, 0x00, 0xf0, 0x01, 0xc0, 0x03, 0x80, 0x04, 0x00,
    /* U+2191 "" (14x14) */
    0x07, 0x00, 0x3f, 0x01, 0xfe, 0x0f, 0xfc, 0x7f, 0xfb, 0xde, 0xf6, 0x79,
    0x81, 0xe0, 0x07, 0x80, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e,
    0x00,
    /* U+2192 "" (14x13) */
    0x01, 0x80, 0x0f, 0x00, 0x1e, 0x00, 0x3c, 0x00, 0x7b, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x78, 0x03, 0xc0, 0x1e, 0x00, 0xf0, 0x01, 0x80,
    /* U+2193 "" (14x14) */
    0x07, 0x80, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e, 0x00, 0x78,
    0x19, 0xe6, 0xf7, 0xbd, 0xff, 0xe3, 0xfe, 0x03, 0xf0, 0x07, 0x80, 0x0c,
    0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 52, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 100, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 153, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 13, .adv_w = 216, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 189, .box_w = 10, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 61, .adv_w = 284, .box_w = 17, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 210, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 86, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 115, .adv_w = 103, .box_w = 6, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 131, .adv_w = 103, .box_w = 6, .box_h = 21, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 147, .adv_w = 139, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 153, .adv_w = 168, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 166, .adv_w = 84, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 170, .adv_w = 139, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 173, .adv_w = 81, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 116, .box_w = 7, .box_h = 18, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 191, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 145, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 186, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 186, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 202, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 179, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 190, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 182, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 193, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 191, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 81, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 82, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 404, .adv_w = 170, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 417, .adv_w = 165, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 425, .adv_w = 169, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 436, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 276, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 482, .adv_w = 229, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 207, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 198, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 226, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 191, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 179, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 223, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 250, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 119, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 113, .box_w = 8, .box_h = 18, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 696, .adv_w = 232, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 180, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 274, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 241, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 231, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 200, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 231, .box_w = 15, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 874, .adv_w = 216, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 193, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 204, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 236, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 967, .adv_w = 232, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 994, .adv_w = 326, .box_w = 20, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1029, .adv_w = 231, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 209, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1077, .adv_w = 201, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 112, .box_w = 6, .box_h = 19, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1113, .adv_w = 122, .box_w = 8, .box_h = 18, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1131, .adv_w = 112, .box_w = 6, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1146, .adv_w = 174, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 1155, .adv_w = 156, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1158, .adv_w = 121, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 1162, .adv_w = 183, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 192, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 166, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1216, .adv_w = 196, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1240, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1256, .adv_w = 127, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1274, .adv_w = 188, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1298, .adv_w = 206, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1324, .adv_w = 108, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1338, .adv_w = 99, .box_w = 6, .box_h = 21, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1354, .adv_w = 198, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1378, .adv_w = 106, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1390, .adv_w = 305, .box_w = 19, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1417, .adv_w = 209, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1434, .adv_w = 185, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1450, .adv_w = 198, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1474, .adv_w = 192, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1498, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1509, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1522, .adv_w = 136, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1536, .adv_w = 205, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1554, .adv_w = 179, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1570, .adv_w = 276, .box_w = 17, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 186, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1610, .adv_w = 186, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1634, .adv_w = 168, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1647, .adv_w = 122, .box_w = 7, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1664, .adv_w = 95, .box_w = 4, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1673, .adv_w = 122, .box_w = 8, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1692, .adv_w = 183, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1697, .adv_w = 140, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1704, .adv_w = 180, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1718, .adv_w = 122, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1726, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1734, .adv_w = 212, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1760, .adv_w = 81, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1762, .adv_w = 158, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1770, .adv_w = 165, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1783, .adv_w = 216, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1806, .adv_w = 244, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1829, .adv_w = 212, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1855, .adv_w = 214, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1873, .adv_w = 190, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1876, .adv_w = 270, .box_w = 15, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1880, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 1884, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 1888, .adv_w = 149, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 1896, .adv_w = 149, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1903, .adv_w = 149, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1910, .adv_w = 255, .box_w = 16, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1916, .adv_w = 414, .box_w = 25, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1960, .adv_w = 247, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1983, .adv_w = 222, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2008, .adv_w = 247, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2031, .adv_w = 222, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x0310, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72, 0x1f76,
    0x1f80, 0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 25, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    3, 13, 3, 15, 3, 33, 3, 34, 3, 36, 3, 40, 3, 48, 3, 50,
    3, 57, 3, 66, 3, 68, 3, 69, 3, 70, 3, 80, 3, 82, 3, 84,
    3, 104, 3, 105, 3, 115, 5, 13, 5, 15, 5, 34, 5, 53, 5, 55,
    5, 56, 5, 57, 5, 58, 5, 71, 5, 74, 5, 78, 5, 79, 5, 81,
    5, 83, 5, 87, 5, 88, 5, 89, 5, 90, 5, 104, 5, 107, 5, 115,
    7, 55, 7, 56, 7, 57, 7, 58, 8, 34, 8, 35, 8, 37, 8, 38,
    8, 39, 8, 41, 8, 42, 8, 44, 8, 45, 8, 46, 8, 47, 8, 49,
    8, 51, 8, 53, 8, 55, 8, 56, 8, 67, 8, 73, 8, 76, 8, 77,
    8, 84, 8, 104, 9, 16, 9, 43, 9, 61, 9, 64, 9, 72, 9, 75,
    13, 3, 13, 8, 13, 17, 13, 24, 13, 34, 13, 43, 13, 53, 13, 55,
    13, 56, 13, 58, 13, 87, 13, 88, 13, 90, 13, 104, 13, 110, 13, 111,
    13, 112, 13, 113, 14, 18, 14, 20, 14, 22, 14, 24, 14, 26, 14, 34,
    14, 53, 14, 55, 14, 56, 14, 57, 14, 89, 14, 90, 14, 104, 15, 3,
    15, 8, 15, 17, 15, 24, 15, 33, 15, 36, 15, 40, 15, 43, 15, 48,
    15, 50, 15, 53, 15, 55, 15, 56, 15, 58, 15, 87, 15, 88, 15, 90,
    15, 105, 15, 110, 15, 111, 15, 112, 15, 113, 16, 10, 16, 16, 16, 43,
    16, 54, 16, 55, 16, 56, 16, 58, 16, 61, 16, 62, 16, 67, 16, 73,
    16, 76, 16, 77, 16, 94, 17, 13, 17, 15, 17, 18, 17, 96, 17, 115,
    18, 96, 20, 3, 20, 8, 20, 13, 20, 15, 20, 20, 20, 32, 20, 33,
    20, 34, 20, 35, 20, 36, 20, 37, 20, 38, 20, 39, 20, 40, 20, 41,
    20, 42, 20, 44, 20, 45, 20, 46, 20, 47, 20, 48, 20, 49, 20, 50,
    20, 51, 20, 53, 20, 55, 20, 56, 20, 57, 20, 58, 20, 59, 20, 66,
    20, 71, 20, 72, 20, 74, 20, 75, 20, 78, 20, 79, 20, 81, 20, 83,
    20, 86, 20, 87, 20, 88, 20, 89, 20, 90, 20, 91, 20, 104, 20, 105,
    20, 106, 20, 107, 20, 110, 20, 111, 20, 112, 20, 113, 20, 115, 21, 24,
    21, 96, 23, 96, 24, 13, 24, 15, 24, 18, 24, 24, 24, 96, 24, 115,
    25, 13, 25, 15, 25, 34, 25, 53, 25, 55, 25, 56, 25, 57, 25, 58,
    25, 89, 25, 104, 25, 115, 26, 13, 26, 15, 26, 115, 27, 55, 27, 56,
    27, 58, 33, 20, 33, 55, 33, 56, 33, 57, 34, 3, 34, 8, 34, 13,
    34, 15, 34, 16, 34, 32, 34, 53, 34, 54, 34, 55, 34, 56, 34, 58,
    34, 62, 34, 89, 34, 94, 34, 110, 34, 111, 34, 112, 34, 113, 34, 115,
    35, 13, 35, 15, 35, 34, 35, 53, 35, 55, 35, 56, 35, 57, 35, 58,
    35, 59, 35, 89, 35, 104, 35, 115, 36, 3, 36, 8, 36, 110, 36, 111,
    36, 112, 36, 113, 37, 13, 37, 15, 37, 20, 37, 55, 37, 56, 37, 57,
    37, 115, 38, 53, 38, 55, 38, 56, 38, 57, 38, 87, 38, 88, 39, 13,
    39, 15, 39, 27, 39, 28, 39, 34, 39, 68, 39, 69, 39, 70, 39, 80,
    39, 82, 39, 104, 39, 115, 40, 55, 40, 56, 40, 57, 40, 58, 41, 5,
    41, 34, 41, 52, 41, 53, 41, 55, 41, 56, 41, 57, 41, 58, 41, 59,
    41, 66, 41, 68, 41, 69, 41, 70, 41, 72, 41, 75, 41, 80, 41, 82,
    41, 84, 41, 87, 41, 88, 41, 89, 41, 90, 41, 104, 42, 3, 42, 8,
    42, 16, 42, 110, 42, 111, 42, 112, 42, 113, 43, 34, 43, 89, 43, 104,
    44, 2, 44, 3, 44, 5, 44, 8, 44, 13, 44, 14, 44, 15, 44, 32,
    44, 33, 44, 34, 44, 35, 44, 36, 44, 37, 44, 38, 44, 39, 44, 40,
    44, 41, 44, 42, 44, 43, 44, 44, 44, 45, 44, 46, 44, 47, 44, 48,
    44, 49, 44, 50, 44, 51, 44, 52, 44, 53, 44, 54, 44, 55, 44, 56,
    44, 57, 44, 58, 44, 59, 44, 66, 44, 68, 44, 69, 44, 70, 44, 71,
    44, 72, 44, 74, 44, 75, 44, 78, 44, 79, 44, 80, 44, 81, 44, 82,
    44, 83, 44, 84, 44, 85, 44, 86, 44, 87, 44, 88, 44, 90, 44, 91,
    44, 101, 44, 104, 44, 105, 44, 106, 44, 107, 44, 108, 44, 109, 44, 110,
    44, 111, 44, 112, 44, 113, 44, 115, 45, 53, 45, 55, 45, 56, 45, 58,
    45, 87, 45, 88, 45, 90, 48, 16, 48, 75, 49, 5, 49, 13, 49, 14,
    49, 15, 49, 16, 49, 32, 49, 33, 49, 34, 49, 35, 49, 36, 49, 37,
    49, 38, 49, 39, 49, 40, 49, 41, 49, 42, 49, 43, 49, 44, 49, 45,
    49, 46, 49, 47, 49, 48, 49, 49, 49, 50, 49, 51, 49, 52, 49, 53,
    49, 54, 49, 55, 49, 56, 49, 57, 49, 58, 49, 59, 49, 62, 49, 66,
    49, 67, 49, 68, 49, 69, 49, 70, 49, 71, 49, 72, 49, 73, 49, 74,
    49, 75, 49, 76, 49, 77, 49, 78, 49, 79, 49, 80, 49, 81, 49, 82,
    49, 83, 49, 84, 49, 85, 49, 86, 49, 89, 49, 91, 49, 94, 49, 101,
    49, 104, 49, 105, 49, 106, 49, 107, 49, 108, 49, 109, 49, 115, 50, 10,
    50, 16, 50, 27, 50, 28, 50, 43, 50, 62, 50, 64, 50, 75, 50, 93,
    50, 94, 51, 33, 51, 34, 51, 36, 51, 40, 51, 48, 51, 50, 51, 53,
    51, 54, 51, 55, 51, 56, 51, 57, 51, 58, 51, 59, 51, 66, 51, 68,
    51, 69, 51, 70, 51, 71, 51, 72, 51, 74, 51, 75, 51, 78, 51, 79,
    51, 80, 51, 81, 51, 82, 51, 83, 51, 85, 51, 86, 51, 87, 51, 88,
    51, 89, 51, 90, 51, 104, 51, 105, 51, 106, 51, 107, 52, 55, 52, 56,
    52, 57, 52, 58, 52, 89, 53, 5, 53, 13, 53, 14, 53, 15, 53, 16,
    53, 27, 53, 28, 53, 33, 53, 34, 53, 35, 53, 36, 53, 37, 53, 38,
    53, 39, 53, 40, 53, 41, 53, 42, 53, 44, 53, 45, 53, 46, 53, 47,
    53, 48, 53, 49, 53, 50, 53, 51, 53, 52, 53, 57, 53, 59, 53, 66,
    53, 68, 53, 69, 53, 70, 53, 72, 53, 80, 53, 82, 53, 84, 53, 89,
    53, 91, 53, 101, 53, 104, 53, 105, 53, 108, 53, 109, 53, 115, 54, 34,
    54, 57, 54, 59, 54, 66, 54, 72, 54, 84, 54, 87, 54, 88, 54, 89,
    54, 90, 54, 91, 54, 104, 55, 2, 55, 5, 55, 7, 55, 13, 55, 14,
    55, 15, 55, 16, 55, 20, 55, 25, 55, 27, 55, 28, 55, 33, 55, 34,
    55, 35, 55, 36, 55, 37, 55, 38, 55, 39, 55, 40, 55, 41, 55, 42,
    55, 43, 55, 44, 55, 45, 55, 46, 55, 47, 55, 48, 55, 49, 55, 50,
    55, 51, 55, 52, 55, 53, 55, 54, 55, 57, 55, 59, 55, 62, 55, 66,
    55, 68, 55, 69, 55, 70, 55, 71, 55, 72, 55, 74, 55, 75, 55, 78,
    55, 79, 55, 80, 55, 81, 55, 82, 55, 83, 55, 84, 55, 85, 55, 86,
    55, 87, 55, 88, 55, 89, 55, 90, 55, 91, 55, 94, 55, 101, 55, 104,
    55, 105, 55, 106, 55, 107, 55, 108, 55, 109, 55, 115, 56, 3, 56, 8,
    56, 13, 56, 14, 56, 15, 56, 34, 56, 55, 56, 56, 56, 58, 56, 66,
    56, 68, 56, 69, 56, 70, 56, 72, 56, 80, 56, 82, 56, 84, 56, 89,
    56, 90, 56, 91, 56, 101, 56, 104, 56, 108, 56, 109, 56, 110, 56, 111,
    56, 112, 56, 113, 56, 115, 57, 14, 57, 16, 57, 101, 57, 108, 57, 109,
    58, 5, 58, 13, 58, 15, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36,
    58, 40, 58, 48, 58, 50, 58, 52, 58, 66, 58, 68, 58, 69, 58, 70,
    58, 71, 58, 72, 58, 74, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82,
    58, 83, 58, 84, 58, 86, 58, 87, 58, 88, 58, 89, 58, 90, 58, 91,
    58, 104, 58, 105, 58, 106, 58, 107, 58, 115, 59, 5, 59, 33, 59, 34,
    59, 35, 59, 36, 59, 37, 59, 38, 59, 39, 59, 40, 59, 41, 59, 42,
    59, 44, 59, 45, 59, 46, 59, 47, 59, 48, 59, 49, 59, 50, 59, 51,
    59, 52, 59, 53, 59, 54, 59, 55, 59, 56, 59, 57, 59, 58, 59, 68,
    59, 69, 59, 70, 59, 71, 59, 72, 59, 74, 59, 78, 59, 79, 59, 80,
    59, 81, 59, 82, 59, 83, 59, 84, 59, 85, 59, 86, 59, 87, 59, 88,
    59, 89, 59, 90, 59, 104, 59, 105, 59, 106, 59, 107, 60, 16, 60, 43,
    60, 61, 60, 64, 60, 75, 61, 43, 64, 16, 64, 43, 64, 75, 66, 3,
    66, 8, 66, 13, 66, 15, 66, 16, 66, 110, 66, 111, 66, 112, 66, 113,
    66, 115, 67, 3, 67, 8, 67, 89, 67, 110, 67, 111, 67, 112, 67, 113,
    68, 3, 68, 8, 68, 110, 68, 111, 68, 112, 68, 113, 69, 16, 69, 62,
    69, 94, 70, 89, 71, 2, 71, 3, 71, 8, 71, 10, 71, 11, 71, 13,
    71, 15, 71, 32, 71, 61, 71, 62, 71, 67, 71, 73, 71, 76, 71, 77,
    71, 94, 71, 110, 71, 111, 71, 112, 71, 113, 71, 115, 72, 68, 72, 69,
    72, 70, 72, 75, 72, 80, 72, 82, 72, 89, 73, 3, 73, 8, 73, 87,
    73, 88, 73, 90, 73, 110, 73, 111, 73, 112, 73, 113, 74, 3, 74, 8,
    74, 87, 74, 88, 74, 90, 74, 110, 74, 111, 74, 112, 74, 113, 75, 75,
    76, 14, 76, 16, 76, 101, 76, 108, 76, 109, 77, 3, 77, 8, 77, 87,
    77, 88, 77, 89, 77, 90, 77, 110, 77, 111, 77, 112, 77, 113, 78, 3,
    78, 8, 78, 90, 78, 110, 78, 111, 78, 112, 78, 113, 79, 3, 79, 8,
    79, 90, 79, 110, 79, 111, 79, 112, 79, 113, 80, 3, 80, 8, 80, 13,
    80, 15, 80, 32, 80, 87, 80, 88, 80, 89, 80, 90, 80, 110, 80, 111,
    80, 112, 80, 113, 80, 115, 81, 16, 82, 64, 82, 75, 83, 13, 83, 15,
    83, 16, 83, 66, 83, 115, 84, 3, 84, 8, 84, 110, 84, 111, 84, 112,
    84, 113, 85, 66, 85, 67, 85, 68, 85, 69, 85, 70, 85, 72, 85, 73,
    85, 75, 85, 76, 85, 77, 85, 80, 85, 82, 85, 84, 85, 87, 85, 88,
    85, 89, 85, 90, 87, 13, 87, 15, 87, 85, 87, 87, 87, 88, 87, 90,
    87, 115, 88, 13, 88, 15, 88, 85, 88, 86, 88, 87, 88, 88, 88, 90,
    88, 106, 88, 115, 89, 14, 89, 32, 89, 33, 89, 36, 89, 40, 89, 48,
    89, 50, 89, 66, 89, 67, 89, 68, 89, 69, 89, 70, 89, 71, 89, 72,
    89, 73, 89, 74, 89, 75, 89, 76, 89, 77, 89, 78, 89, 79, 89, 80,
    89, 81, 89, 82, 89, 83, 89, 84, 89, 85, 89, 86, 89, 91, 89, 101,
    89, 105, 89, 106, 89, 107, 89, 108, 89, 109, 90, 13, 90, 14, 90, 15,
    90, 27, 90, 28, 90, 33, 90, 36, 90, 40, 90, 48, 90, 50, 90, 66,
    90, 68, 90, 69, 90, 70, 90, 72, 90, 80, 90, 82, 90, 84, 90, 91,
    90, 101, 90, 105, 90, 108, 90, 109, 90, 115, 91, 67, 91, 73, 91, 76,
    91, 77, 91, 84, 91, 87, 91, 88, 91, 89, 91, 90, 92, 43, 92, 53,
    92, 75, 100, 16, 101, 18, 101, 22, 101, 24, 101, 53, 101, 55, 101, 56,
    101, 57, 101, 89, 104, 2, 104, 3, 104, 5, 104, 8, 104, 14, 104, 32,
    104, 33, 104, 35, 104, 36, 104, 37, 104, 38, 104, 39, 104, 40, 104, 41,
    104, 42, 104, 43, 104, 44, 104, 45, 104, 46, 104, 47, 104, 48, 104, 49,
    104, 50, 104, 51, 104, 52, 104, 53, 104, 54, 104, 55, 104, 56, 104, 57,
    104, 58, 104, 59, 104, 66, 104, 67, 104, 68, 104, 69, 104, 70, 104, 71,
    104, 72, 104, 73, 104, 74, 104, 75, 104, 76, 104, 77, 104, 78, 104, 79,
    104, 80, 104, 81, 104, 82, 104, 83, 104, 84, 104, 85, 104, 86, 104, 87,
    104, 88, 104, 90, 104, 91, 104, 101, 104, 105, 104, 106, 104, 107, 104, 108,
    104, 109, 104, 110, 104, 111, 104, 112, 104, 113, 105, 20, 105, 55, 105, 56,
    105, 57, 106, 16, 107, 16, 108, 18, 108, 20, 108, 22, 108, 24, 108, 34,
    108, 53, 108, 55, 108, 56, 108, 57, 108, 89, 108, 90, 108, 104, 109, 18,
    109, 20, 109, 22, 109, 24, 109, 34, 109, 53, 109, 55, 109, 56, 109, 57,
    109, 89, 109, 90, 109, 104, 110, 13, 110, 15, 110, 34, 110, 68, 110, 69,
    110, 70, 110, 80, 110, 82, 110, 84, 110, 104, 110, 115, 111, 13, 111, 15,
    111, 34, 111, 68, 111, 69, 111, 70, 111, 80, 111, 82, 111, 84, 111, 104,
    111, 115, 112, 13, 112, 15, 112, 34, 112, 53, 112, 67, 112, 73, 112, 76,
    112, 77, 112, 84, 112, 104, 112, 115, 113, 13, 113, 15, 113, 34, 113, 53,
    113, 67, 113, 73, 113, 76, 113, 77, 113, 84, 113, 104, 113, 115, 115, 3,
    115, 8, 115, 17, 115, 24, 115, 33, 115, 36, 115, 40, 115, 43, 115, 48,
    115, 50, 115, 53, 115, 55, 115, 56, 115, 58, 115, 87, 115, 88, 115, 90,
    115, 105, 115, 110, 115, 111, 115, 112, 115, 113,
};

static const int8_t kern_pair_values[] = {
    -14, -14, -5, -31, -5, -5, -5, -5, -4, -6, -7, -7, -7, -7, -7, -17,
    -31, -5, -14, -7, -7, -9, -9, -13, -13, -17, -16, -7, -7, -7, -7, -7,
    -7, -9, -9, -10, -8, -9, -7, -7, -12, -12, -11, -13, -31, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 2, 2, 7, 7, 7, 7,
    -17, -31, 13, 23, 9, 12, 6, 21, -27, -27, -14, -18, 4, 16, -23, -25,
    -25, -25, -20, -20, -23, 4, -27, -27, -27, -27, -15, -7, -10, -18, -5, -7,
    -21, -16, -16, -27, -18, -9, -7, -27, -27, -14, -18, -12, -12, -12, 16, -12,
    -12, -23, -25, -25, -25, -20, -20, -23, -12, -27, -27, -27, -27, 9, -14, 5,
    4, 4, 4, 4, 13, 9, 9, 9, 9, 9, 9, -15, -15, -2, -3, -15,
    -13, -5, -5, -12, -12, -5, -5, -3, -11, -7, -3, -7, -7, -7, -3, -7,
    -7, -7, -7, -7, -7, -3, -7, -3, -7, -12, -17, -17, -15, -14, -9, -4,
    -5, -3, -5, -3, -5, -5, -5, -5, -3, -5, -5, -11, -7, -5, -11, -3,
    -3, -5, -5, -5, -5, -5, -12, -4, -13, -10, -31, -31, 4, 2, 10, -31,
    -12, -12, -11, -12, -17, -17, -15, -14, -11, -11, -12, -17, -17, -17, -10, -10,
    -10, -13, -13, -13, -14, -31, -31, 4, 4, 3, -14, -25, -15, -27, -27, -22,
    3, 3, 3, -31, -31, -31, -31, 4, -12, -12, -11, -12, -17, -17, -15, -14,
    -9, -11, -11, -12, 3, 3, 3, 3, 3, 3, -12, -12, -13, -13, -13, -14,
    -12, -12, -9, -9, -11, -9, -9, -36, -36, -12, -12, -21, -13, -13, -13, -13,
    -13, -21, -36, -12, -12, -11, -13, -5, -6, -5, -6, -5, -5, -8, -4, -4,
    -4, -3, -3, -3, -4, -3, -3, -3, -4, -6, -6, -8, -7, -6, 2, 2,
    3, 2, 2, 2, 2, -15, -10, -15, -3, -4, -5, -4, -5, -27, -5, -4,
    -14, -2, -8, -14, -8, -8, -8, -14, -8, -8, -3, -8, -8, -8, -8, -14,
    -8, -14, -8, -5, -9, -11, -6, -6, -3, -6, -7, -9, -10, -10, -10, -3,
    -9, -3, -5, -3, -3, -10, -3, -10, -3, -9, -9, -9, -11, -11, -14, -1,
    -27, -2, -14, -9, -3, -27, -27, -4, -4, -4, -4, -5, -21, -25, -25, -28,
    -13, -13, -15, 1, 2, -2, -47, -9, -47, -10, -4, -2, -18, -6, -2, -6,
    -6, -6, -2, -6, -6, -3, -6, -6, -6, -6, -2, -6, -2, -6, -2, -3,
    -4, -9, -9, -11, -7, -6, -3, -6, -2, -3, -3, -3, -2, -4, -2, -2,
    -3, -2, -2, -2, -2, -3, -2, -3, -2, -2, -2, -2, -3, -5, -3, -9,
    -18, -2, -2, -2, -9, -9, -47, 23, 1, 23, 23, 47, 22, 30, 2, 11,
    22, -6, -2, -6, -6, -6, -6, -7, -5, -15, -15, -5, -16, -2, -3, -6,
    -6, -6, -2, -2, -2, -1, -2, -2, -6, -2, -6, -2, -4, -4, -7, -7,
    -3, -6, -2, -6, -4, -2, -13, -13, -17, -16, -10, -7, -26, -21, -26, -10,
    -10, -10, -7, -25, -6, -7, -6, -6, -6, -7, -6, -6, -6, -6, -6, -6,
    -7, -6, -7, -6, -7, -9, -9, -12, -13, -13, -13, -15, -13, -13, -13, -7,
    -9, -21, -25, -7, -21, -21, -26, -15, -9, -6, -6, -6, -6, -7, -7, -10,
    -7, -6, -15, -5, -14, -9, -34, -16, -34, -14, -8, -9, -11, -11, -11, -27,
    -5, -11, -5, -5, -5, -11, -5, -5, -3, -5, -5, -5, -5, -11, -5, -11,
    -5, -14, -3, -1, -5, -10, -2, -22, -21, -21, -21, -11, -20, -11, -10, -11,
    -11, -21, -11, -21, -11, -20, -9, -13, -9, -9, -20, -17, -23, -2, -16, -27,
    -11, -13, -11, -16, -16, -34, 2, 2, -34, -16, -34, -27, 2, 2, 2, -22,
    -21, -21, -21, -20, -21, -21, -20, -20, -17, -23, -16, -27, -16, -16, 2, 2,
    2, 2, -34, -27, 1, -27, -27, -27, -11, -35, -35, -13, -13, -11, -22, -11,
    -11, -11, -11, -11, -22, -19, -19, -19, -13, -18, -13, -13, -13, -19, -13, -19,
    -13, -17, -12, -14, -14, -18, -12, -14, -22, -11, -12, -13, -35, -6, -7, -5,
    -4, -7, -4, -4, -4, -7, -4, -4, -4, -4, -4, -4, -7, -4, -7, -4,
    -6, -6, -5, -7, -7, -8, -7, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -3, -6, -6, -7, -7, -3, -9, -5, -7, -6, -2, 13, 19,
    9, 10, 15, 21, 13, 20, 18, -17, -17, 4, 4, 6, -17, -17, -17, -17,
    4, -14, -14, -10, -14, -14, -14, -14, 2, 2, 2, 2, 2, 2, 9, 4,
    4, -9, 18, 14, 14, 20, 22, -10, -10, 12, 23, 30, 18, 18, 18, 18,
    30, 14, 14, 14, 14, -10, -5, -5, -5, 17, -5, -5, -5, -17, -17, -8,
    -8, -10, -17, -17, -17, -17, -7, -7, -5, -5, -5, -7, -7, -7, -7, 9,
    -18, 5, -18, -18, -18, -7, -7, -5, -5, -3, -5, -7, -7, -7, -7, -17,
    -17, -10, -17, -17, -17, -17, -17, -17, -10, -17, -17, -17, -17, -14, -14, -6,
    -6, -2, -4, -4, -10, -5, -14, -14, -14, -14, -6, 4, 13, 31, -23, -23,
    -7, -9, -23, -13, -13, -13, -13, -13, -13, -3, -2, -5, -5, -5, -4, -2,
    -1, -2, -2, -5, -5, -3, -3, -3, -2, -2, -22, -22, 6, 6, 6, 6,
    -22, -22, -22, 6, 4, 6, 6, 6, 4, -22, -18, -6, -5, -5, -5, -5,
    -5, -7, -3, -10, -10, -10, -4, -8, -3, -4, -5, -3, -3, -4, -4, -10,
    -4, -10, -4, -6, -3, -4, -5, -18, -5, -4, -4, -18, -18, -22, -5, -22,
    -3, -3, -3, -3, -3, -3, -3, -6, -4, -4, -4, -5, -4, -4, -7, -4,
    -5, -3, -5, -5, -22, -2, -2, -2, -2, -3, -5, -5, -5, -5, 19, -3,
    15, 7, -15, -10, -18, -21, -16, -16, -27, -18, -2, -31, -6, -31, -7, -14,
    -7, -6, -7, -6, -6, -6, -7, -6, -6, -4, -6, -6, -6, -6, -7, -6,
    -7, -6, -6, -25, -15, -27, -27, -2, -22, -3, -4, -1, -5, -5, -5, -3,
    -6, -1, -3, -3, -1, -1, -3, -3, -5, -3, -5, -3, -3, -7, -8, -12,
    -12, -13, -5, -7, -7, -8, -3, -7, -7, -31, -31, -31, -31, -13, -13, -13,
    -14, 7, 7, -15, -7, -10, -18, -7, -21, -16, -16, -27, -18, -9, -7, -15,
    -7, -10, -18, -7, -21, -16, -16, -27, -18, -9, -7, -14, -14, -31, -7, -7,
    -7, -7, -7, -17, -31, -14, -14, -14, -31, -7, -7, -7, -7, -7, -17, -31,
    -14, -14, -14, -31, 5, 7, 7, 7, 7, -17, -31, -14, -14, -14, -31, 5,
    7, 7, 7, 7, -17, -31, -14, -27, -27, -14, -18, -12, -12, -12, 16, -12,
    -12, -23, -25, -25, -25, -20, -20, -23, -12, -27, -27, -27, -27,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1181,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

static const lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
};

/*-----------------
 *  PUBLIC FONT (LVGL >= 9.6.0)
 *----------------*/

const lv_font_t humid1_font_bitter_bold_20 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 25,
    .base_line = 6,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 14,
    .x_height = 11,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_fira_sans_bold_20,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_BITTER_BOLD_20 */
