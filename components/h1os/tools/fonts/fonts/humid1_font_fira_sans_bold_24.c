/*******************************************************************************
 * Font: humid1_font_fira_sans_bold_24 (fira_sans bold)
 * Size: 24 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_24 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_FIRA_SANS_BOLD_24
#define HUMID1_FONT_FIRA_SANS_BOLD_24 1
#endif

#if HUMID1_FONT_FIRA_SANS_BOLD_24

extern const lv_font_t humid1_icon_fa7_solid_24;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x16) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0xff, 0xf6,
    /* U+0022 "" (9x7) */
    0xf7, 0xfb, 0xfd, 0xfc, 0xee, 0x73, 0x39, 0x8c,
    /* U+0023 "#" (13x16) */
    0x1e, 0x70, 0xf3, 0x87, 0x9c, 0xff, 0xf7, 0xff, 0xbf, 0xfc, 0xf3, 0xc7,
    0x9c, 0x3c, 0xe1, 0xe7, 0x3f, 0xfd, 0xff, 0xef, 0xff, 0x1c, 0xf1, 0xe7,
    0x0f, 0x38,
    /* U+0024 "$" (13x23) */
    0x07, 0x00, 0x38, 0x01, 0xc0, 0x1f, 0x03, 0xff, 0x3f, 0xf9, 0xf1, 0x8f,
    0x00, 0x7c, 0x03, 0xfc, 0x0f, 0xf8, 0x3f, 0xe0, 0x3f, 0x80, 0x7c, 0x03,
    0xee, 0x1f, 0xff, 0xf3, 0xff, 0x07, 0xf0, 0x0e, 0x00, 0x70, 0x03, 0x80,
    0x1c, 0x00,
    /* U+0025 "%" (19x16) */
    0x3c, 0x06, 0x0f, 0xc1, 0xe3, 0xfc, 0x38, 0x73, 0x8f, 0x0e, 0x73, 0xc1,
    0xfe, 0xf0, 0x3f, 0x9c, 0x01, 0xe7, 0xbc, 0x01, 0xef, 0xc0, 0x7b, 0xfc,
    0x0f, 0x73, 0x83, 0xcc, 0x70, 0xf1, 0xce, 0x1c, 0x3f, 0xc7, 0x83, 0xf0,
    0x60, 0x3c,
    /* U+0026 "&" (17x16) */
    0x0f, 0x80, 0x1f, 0xf0, 0x0f, 0xfc, 0x0f, 0x9e, 0x07, 0x8f, 0x01, 0xef,
    0x00, 0xff, 0x80, 0x3f, 0x00, 0x3f, 0xc7, 0x3f, 0xf7, 0x9e, 0x7f, 0x9f,
    0x1f, 0x8f, 0xc7, 0xe3, 0xff, 0xf8, 0xff, 0xfe, 0x3f, 0x0c,
    /* U+0027 "'" (4x7) */
    0xff, 0xfe, 0xe6, 0x60,
    /* U+0028 "(" (7x24) */
    0x0e, 0x3c, 0x79, 0xe3, 0xcf, 0x9e, 0x3c, 0x79, 0xf3, 0xe7, 0xcf, 0x9f,
    0x3e, 0x3c, 0x78, 0xf0, 0xf1, 0xe1, 0xe3, 0xc3, 0x82,
    /* U+0029 ")" (7x24) */
    0x71, 0xe1, 0xe3, 0xe3, 0xc7, 0x87, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    0xc7, 0x8f, 0x1e, 0x78, 0xf1, 0xe7, 0x9e, 0x1c, 0x10,
    /* U+002A "" (11x10) */
    0x0e, 0x01, 0xc1, 0xbb, 0x3f, 0xef, 0xfe, 0x3e, 0x0f, 0xc3, 0xfc, 0x3b,
    0x82, 0x20,
    /* U+002B "+" (11x11) */
    0x0e, 0x01, 0xc0, 0x38, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x70, 0x0e,
    0x01, 0xc0, 0x38, 0x00,
    /* U+002C "," (4x8) */
    0x6f, 0xff, 0xee, 0xec,
    /* U+002D "-" (8x3) */
    0xff, 0xff, 0xff,
    /* U+002E "." (4x5) */
    0x6f, 0xff, 0x60,
    /* U+002F "/" (9x23) */
    0x04, 0x03, 0xc1, 0xe1, 0xe0, 0xf0, 0x78, 0x3c, 0x3c, 0x1e, 0x0f, 0x07,
    0x87, 0x83, 0xc1, 0xe1, 0xe0, 0xf0, 0x78, 0x3c, 0x3c, 0x1e, 0x0f, 0x07,
    0x80, 0x80,
    /* U+0030 "0" (12x16) */
    0x0f, 0x83, 0xfc, 0x7f, 0xe7, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0x79, 0xf7, 0xfe, 0x3f, 0xc0, 0xf8,
    /* U+0031 "1" (10x16) */
    0x07, 0xc7, 0xf7, 0xff, 0xff, 0x7f, 0xc9, 0xf0, 0x7c, 0x1f, 0x07, 0xc1,
    0xf0, 0x7c, 0x1f, 0x07, 0xc1, 0xf0, 0x7c, 0x1f,
    /* U+0032 "2" (12x16) */
    0x1f, 0x87, 0xfc, 0xff, 0xe7, 0x1e, 0x21, 0xf0, 0x1f, 0x01, 0xe0, 0x3e,
    0x07, 0xc0, 0xf8, 0x1f, 0x03, 0xe0, 0x7c, 0x07, 0xff, 0x7f, 0xf7, 0xff,
    /* U+0033 "3" (12x16) */
    0x1f, 0x87, 0xfc, 0xff, 0xe6, 0x1e, 0x01, 0xe0, 0x1e, 0x0f, 0xc0, 0xf8,
    0x0f, 0xe0, 0x1f, 0x00, 0xf0, 0x0f, 0x61, 0xff, 0xfe, 0x7f, 0xc1, 0xf8,
    /* U+0034 "4" (12x16) */
    0x0e, 0x01, 0xf0, 0x1e, 0x03, 0xe0, 0x3c, 0x03, 0xc0, 0x79, 0xe7, 0x9e,
    0xf9, 0xef, 0x3e, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3e, 0x03, 0xe0, 0x3e,
    /* U+0035 "5" (12x16) */
    0x7f, 0xf7, 0xfe, 0x7f, 0xe7, 0x80, 0x78, 0x07, 0xfc, 0x7f, 0xe7, 0xff,
    0x31, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x71, 0xff, 0xfe, 0x7f, 0xc1, 0xf8,
    /* U+0036 "6" (12x16) */
    0x0f, 0xc1, 0xfe, 0x3f, 0xc7, 0xc0, 0x78, 0x0f, 0xfc, 0xff, 0xef, 0xff,
    0xf9, 0xff, 0x0f, 0xf0, 0xff, 0x8f, 0xf9, 0xf7, 0xfe, 0x3f, 0xc1, 0xf8,
    /* U+0037 "7" (11x16) */
    0xff, 0xff, 0xff, 0xff, 0x81, 0xf0, 0x3c, 0x0f, 0x81, 0xe0, 0x3c, 0x0f,
    0x81, 0xe0, 0x7c, 0x0f, 0x03, 0xe0, 0x78, 0x1f, 0x01, 0xe0,
    /* U+0038 "8" (13x16) */
    0x1f, 0x81, 0xff, 0x1f, 0xfd, 0xf3, 0xef, 0x0f, 0x7c, 0x79, 0xff, 0x87,
    0xf8, 0x7f, 0xe7, 0xcf, 0xbc, 0x3d, 0xe1, 0xff, 0x8f, 0x7f, 0xf9, 0xff,
    0x83, 0xf0,
    /* U+0039 "9" (12x17) */
    0x1f, 0x87, 0xfc, 0x7f, 0xef, 0x9f, 0xf1, 0xff, 0x0f, 0xf0, 0xff, 0x1f,
    0xff, 0xf7, 0xff, 0x3d, 0xe0, 0x3e, 0x07, 0xe1, 0xfc, 0x7f, 0x87, 0xe0,
    0x78, 0x00,
    /* U+003A ":" (4x13) */
    0x6f, 0xff, 0x60, 0x00, 0x6f, 0xff, 0x60,
    /* U+003B ";" (4x17) */
    0x6f, 0xff, 0x60, 0x00, 0x06, 0xff, 0xfe, 0xee, 0xc0,
    /* U+003C "<" (11x12) */
    0x00, 0xc0, 0x78, 0x3f, 0xbf, 0xef, 0xe1, 0xf0, 0x3e, 0x07, 0xf0, 0x7f,
    0xc1, 0xfc, 0x0f, 0x00, 0x60,
    /* U+003D "=" (11x9) */
    0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff,
    0xe0,
    /* U+003E ">" (11x12) */
    0x40, 0x1f, 0x03, 0xf8, 0x3f, 0xc0, 0xfe, 0x07, 0xc0, 0xf8, 0xff, 0x7f,
    0x9f, 0xc3, 0xe0, 0x20, 0x00,
    /* U+003F "?" (10x16) */
    0x3f, 0x3f, 0xff, 0xfd, 0x8f, 0x03, 0xc3, 0xf1, 0xf8, 0x78, 0x3c, 0x00,
    0x00, 0x00, 0x70, 0x3c, 0x0f, 0x83, 0xc0, 0x70,
    /* U+0040 "@" (22x21) */
    0x00, 0xfe, 0x00, 0x1f, 0xff, 0x00, 0xff, 0xfe, 0x07, 0xe0, 0x7c, 0x3e,
    0x7c, 0x79, 0xe3, 0xfc, 0xf7, 0x9f, 0xf3, 0xfc, 0xfb, 0xc7, 0xf3, 0xcf,
    0x1f, 0xcf, 0x3c, 0x7f, 0x3c, 0xf1, 0xfc, 0xf3, 0xcf, 0xf3, 0xcf, 0x3f,
    0xc7, 0xff, 0xe7, 0x9f, 0xbf, 0x1e, 0x3c, 0x78, 0x3c, 0x00, 0x00, 0x7c,
    0x00, 0x00, 0xff, 0xf8, 0x01, 0xff, 0xe0, 0x00, 0xff, 0x00,
    /* U+0041 "A" (15x16) */
    0x0f, 0xc0, 0x1f, 0x80, 0x3f, 0x80, 0xff, 0x01, 0xfe, 0x03, 0xde, 0x0f,
    0x3c, 0x1e, 0x78, 0x3c, 0xf0, 0x79, 0xf1, 0xff, 0xe3, 0xff, 0xc7, 0xff,
    0xdf, 0x0f, 0xbe, 0x0f, 0x78, 0x1f,
    /* U+0042 "B" (13x16) */
    0xff, 0xc7, 0xff, 0xbf, 0xfd, 0xf1, 0xff, 0x8f, 0xfc, 0x7b, 0xff, 0x9f,
    0xf8, 0xff, 0xf7, 0xc7, 0xfe, 0x1f, 0xf0, 0xff, 0x8f, 0xff, 0xff, 0xff,
    0xdf, 0xf8,
    /* U+0043 "C" (12x16) */
    0x07, 0xc1, 0xff, 0x3f, 0xf7, 0xc6, 0xf8, 0x0f, 0x80, 0xf0, 0x0f, 0x00,
    0xf0, 0x0f, 0x00, 0xf8, 0x0f, 0x80, 0x7c, 0x37, 0xff, 0x1f, 0xf0, 0xfc,
    /* U+0044 "D" (14x16) */
    0xff, 0x83, 0xff, 0x8f, 0xff, 0x3e, 0x3e, 0xf8, 0x7f, 0xe1, 0xff, 0x87,
    0xfe, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0x87, 0xfe, 0x1e, 0xf8, 0xfb, 0xff,
    0xcf, 0xfe, 0x3f, 0xe0,
    /* U+0045 "E" (11x16) */
    0xff, 0xff, 0xff, 0xff, 0xfc, 0x0f, 0x81, 0xf0, 0x3f, 0xf7, 0xfe, 0xff,
    0xdf, 0x03, 0xe0, 0x7c, 0x0f, 0x81, 0xff, 0xff, 0xff, 0xff,
    /* U+0046 "F" (11x16) */
    0xff, 0xff, 0xfb, 0xff, 0x7c, 0x0f, 0x81, 0xf0, 0x3e, 0x07, 0xfe, 0xff,
    0xdf, 0xfb, 0xe0, 0x7c, 0x0f, 0x81, 0xf0, 0x3e, 0x07, 0xc0,
    /* U+0047 "G" (14x16) */
    0x07, 0xe0, 0x7f, 0xe3, 0xff, 0x9f, 0x0c, 0xf8, 0x03, 0xe0, 0x0f, 0x1f,
    0xfc, 0x7f, 0xf1, 0xff, 0xc1, 0xff, 0x07, 0xfe, 0x1f, 0x7c, 0x7d, 0xff,
    0xf3, 0xff, 0x83, 0xf8,
    /* U+0048 "H" (14x16) */
    0xf8, 0x7f, 0xe1, 0xff, 0x87, 0xfe, 0x1f, 0xf8, 0x7f, 0xe1, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0x87, 0xfe, 0x1f, 0xf8, 0x7f, 0xe1,
    0xff, 0x87, 0xfe, 0x1f,
    /* U+0049 "I" (5x16) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+004A "J" (6x20) */
    0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x7f, 0xef, 0xb8,
    /* U+004B "K" (15x16) */
    0xf8, 0x7d, 0xf0, 0xf3, 0xe3, 0xe7, 0xcf, 0x8f, 0x9e, 0x1f, 0x7c, 0x3e,
    0xf0, 0x7f, 0xe0, 0xff, 0xc1, 0xf7, 0xc3, 0xe7, 0xc7, 0xcf, 0x8f, 0x8f,
    0x9f, 0x1f, 0x3e, 0x1f, 0x7c, 0x3f,
    /* U+004C "L" (11x16) */
    0xf8, 0x1f, 0x03, 0xe0, 0x7c, 0x0f, 0x81, 0xf0, 0x3e, 0x07, 0xc0, 0xf8,
    0x1f, 0x03, 0xe0, 0x7c, 0x0f, 0x81, 0xff, 0xff, 0xff, 0xff,
    /* U+004D "M" (17x16) */
    0x7c, 0x3f, 0x3f, 0x1f, 0x9f, 0x8f, 0xcf, 0xc7, 0xef, 0xe3, 0xf7, 0xf1,
    0xff, 0xfd, 0xdf, 0xee, 0xef, 0xf7, 0x77, 0xfb, 0xfb, 0xfc, 0xf9, 0xfe,
    0x7c, 0xff, 0x3e, 0x7f, 0x9f, 0x3f, 0xc0, 0x1f, 0xe0, 0x0f,
    /* U+004E "N" (13x16) */
    0xfc, 0x3f, 0xe1, 0xff, 0x8f, 0xfc, 0x7f, 0xe3, 0xff, 0x9f, 0xdc, 0xfe,
    0xe7, 0xf7, 0xbf, 0x9d, 0xfc, 0xff, 0xe7, 0xff, 0x1f, 0xf8, 0xff, 0xc7,
    0xfe, 0x1f,
    /* U+004F "O" (15x16) */
    0x0f, 0xc0, 0x7f, 0xe1, 0xff, 0xe3, 0xe3, 0xef, 0x83, 0xde, 0x07, 0xfc,
    0x0f, 0xf8, 0x1f, 0xf0, 0x3f, 0xe0, 0x7f, 0xe0, 0xff, 0xc1, 0xe7, 0xc7,
    0xcf, 0xff, 0x0f, 0xfc, 0x07, 0xe0,
    /* U+0050 "P" (13x16) */
    0xff, 0xc7, 0xff, 0x3f, 0xfd, 0xf1, 0xff, 0x8f, 0xfc, 0x7f, 0xe3, 0xff,
    0x1f, 0xff, 0xf7, 0xff, 0x3f, 0xf1, 0xf0, 0x0f, 0x80, 0x7c, 0x03, 0xe0,
    0x1f, 0x00,
    /* U+0051 "Q" (16x19) */
    0x0f, 0xc0, 0x3f, 0xf0, 0x7f, 0xf8, 0x7c, 0x7c, 0xf8, 0x3c, 0xf0, 0x3e,
    0xf0, 0x3e, 0xf0, 0x3e, 0xf0, 0x3e, 0xf0, 0x3e, 0xf8, 0x3e, 0xf8, 0x3c,
    0x7c, 0x78, 0x7f, 0xf0, 0x3f, 0xf0, 0x0f, 0xfe, 0x00, 0x3f, 0x00, 0x1e,
    0x00, 0x04,
    /* U+0052 "R" (14x16) */
    0xff, 0xc3, 0xff, 0xcf, 0xff, 0xbe, 0x3e, 0xf8, 0xfb, 0xe3, 0xef, 0x8f,
    0xbf, 0xfc, 0xff, 0xe3, 0xff, 0x0f, 0xbe, 0x3e, 0x78, 0xf9, 0xf3, 0xe3,
    0xef, 0x8f, 0xbe, 0x1f,
    /* U+0053 "S" (13x16) */
    0x0f, 0xc1, 0xff, 0x9f, 0xfe, 0xf8, 0xe7, 0x80, 0x3e, 0x01, 0xfe, 0x07,
    0xfc, 0x0f, 0xf8, 0x0f, 0xc0, 0x3e, 0x00, 0xf7, 0x0f, 0xff, 0xfd, 0xff,
    0xc3, 0xf8,
    /* U+0054 "T" (13x16) */
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0x00, 0xf8, 0x07, 0xc0, 0x3e, 0x01,
    0xf0, 0x0f, 0x80, 0x7c, 0x03, 0xe0, 0x1f, 0x00, 0xf8, 0x07, 0xc0, 0x3e,
    0x01, 0xf0,
    /* U+0055 "U" (13x16) */
    0xf0, 0x7f, 0x83, 0xfc, 0x1f, 0xe0, 0xff, 0x07, 0xf8, 0x3f, 0xc1, 0xfe,
    0x0f, 0xf0, 0x7f, 0x83, 0xfc, 0x1f, 0xf0, 0xf7, 0x8f, 0xbf, 0xf8, 0xff,
    0xc1, 0xf8,
    /* U+0056 "V" (14x16) */
    0xf0, 0x3f, 0xe1, 0xff, 0x87, 0xde, 0x1e, 0x78, 0x79, 0xe1, 0xe7, 0xcf,
    0x0f, 0x3c, 0x3c, 0xf0, 0xf3, 0xc1, 0xee, 0x07, 0xf8, 0x1f, 0xe0, 0x7f,
    0x80, 0xfc, 0x03, 0xf0,
    /* U+0057 "W" (20x16) */
    0xf8, 0xf8, 0xff, 0x8f, 0x8f, 0x78, 0xf8, 0xf7, 0x9f, 0x8f, 0x79, 0xf8,
    0xf7, 0x9f, 0x9e, 0x79, 0xdd, 0xe7, 0x9d, 0xde, 0x79, 0xdd, 0xe3, 0xf9,
    0xde, 0x3f, 0x9d, 0xe3, 0xf9, 0xfc, 0x3f, 0x9f, 0xc3, 0xf8, 0xfc, 0x3f,
    0x8f, 0xc1, 0xf0, 0xfc,
    /* U+0058 "X" (14x16) */
    0xf8, 0x7d, 0xf1, 0xe3, 0xcf, 0x8f, 0x3c, 0x1f, 0xe0, 0x7f, 0x80, 0xfc,
    0x03, 0xf0, 0x0f, 0xc0, 0x7f, 0x81, 0xfe, 0x0f, 0x3c, 0x3c, 0xf9, 0xf3,
    0xe7, 0x87, 0xfe, 0x1f,
    /* U+0059 "Y" (15x16) */
    0xf8, 0x3e, 0xf0, 0x79, 0xf1, 0xe1, 0xe3, 0xc3, 0xcf, 0x03, 0xde, 0x07,
    0xf8, 0x07, 0xf0, 0x0f, 0xc0, 0x0f, 0x80, 0x1e, 0x00, 0x3c, 0x00, 0x78,
    0x00, 0xf0, 0x01, 0xe0, 0x03, 0xc0,
    /* U+005A "Z" (13x16) */
    0x7f, 0xfb, 0xff, 0xdf, 0xfe, 0x03, 0xe0, 0x3f, 0x01, 0xf0, 0x1f, 0x01,
    0xf0, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xfc, 0x07, 0xc0, 0x7f, 0xff, 0xff,
    0xff, 0xfe,
    /* U+005B "[" (8x22) */
    0xff, 0xff, 0xff, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
    0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff,
    /* U+005C "" (9x22) */
    0xf0, 0x78, 0x3c, 0x1e, 0x07, 0x83, 0xc1, 0xe0, 0xf0, 0x3c, 0x1e, 0x0f,
    0x07, 0x81, 0xe0, 0xf0, 0x78, 0x1e, 0x0f, 0x07, 0x83, 0xc0, 0xf0, 0x78,
    0x20,
    /* U+005D "]" (7x22) */
    0xff, 0xff, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xff, 0xc0,
    /* U+005E "^" (12x8) */
    0x0e, 0x01, 0xf0, 0x1f, 0x83, 0xfc, 0x7b, 0xc7, 0x9e, 0xf1, 0xef, 0x0f,
    /* U+005F "_" (12x3) */
    0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+0060 "`" (7x5) */
    0x61, 0xe3, 0xf3, 0xf0, 0xc0,
    /* U+0061 "a" (12x13) */
    0x3f, 0x07, 0xfc, 0x7f, 0xc0, 0x3e, 0x01, 0xe3, 0xfe, 0x7f, 0xef, 0x1e,
    0xf1, 0xef, 0x3e, 0xff, 0xff, 0xee, 0x3c, 0x60,
    /* U+0062 "b" (13x18) */
    0x70, 0x07, 0x80, 0x3c, 0x01, 0xe0, 0x0f, 0x00, 0x79, 0xe3, 0xff, 0x9f,
    0xfe, 0xf9, 0xf7, 0x87, 0xbc, 0x3f, 0xe1, 0xff, 0x0f, 0xf8, 0x7b, 0xe7,
    0xdf, 0xfe, 0xff, 0xe7, 0xbe, 0x00,
    /* U+0063 "c" (10x13) */
    0x0f, 0x8f, 0xf7, 0xff, 0xe2, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3e,
    0x27, 0xfc, 0xff, 0x1f, 0x80,
    /* U+0064 "d" (12x18) */
    0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf1, 0xef, 0x7f, 0xf7, 0xff,
    0xf9, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf9, 0xff, 0xff,
    0x7f, 0xf3, 0xef,
    /* U+0065 "e" (12x13) */
    0x1f, 0x03, 0xfc, 0x7f, 0xef, 0x9e, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf0, 0x0f, 0x84, 0x7f, 0xe3, 0xfe, 0x1f, 0x80,
    /* U+0066 "f" (10x18) */
    0x0f, 0xc7, 0xf3, 0xfc, 0xf0, 0x3c, 0x3f, 0xef, 0xfb, 0xfe, 0x3c, 0x0f,
    0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x00,
    /* U+0067 "g" (13x19) */
    0x00, 0x38, 0x7f, 0xcf, 0xfe, 0xff, 0xc7, 0x8f, 0x3c, 0x79, 0xe3, 0xcf,
    0xfe, 0x3f, 0xe1, 0xfe, 0x0e, 0x00, 0xff, 0xc3, 0xff, 0x0f, 0xfc, 0x01,
    0xfe, 0x1f, 0xff, 0xfb, 0xff, 0x87, 0xf0,
    /* U+0068 "h" (12x18) */
    0x70, 0x0f, 0x80, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0xbc, 0xff, 0xef, 0xfe,
    0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f,
    0xf9, 0xff, 0x9f,
    /* U+0069 "i" (5x20) */
    0x77, 0xff, 0xf7, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf0,
    /* U+006A "j" (7x25) */
    0x1c, 0x7c, 0xf9, 0xf1, 0xc0, 0x00, 0x1f, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7,
    0xcf, 0x9f, 0x3e, 0x7c, 0xf9, 0xe7, 0xdf, 0xbe, 0x78, 0x40,
    /* U+006B "k" (13x18) */
    0xf8, 0x07, 0xc0, 0x3e, 0x01, 0xf0, 0x0f, 0x80, 0x7c, 0x7b, 0xe7, 0xdf,
    0x3c, 0xfb, 0xc7, 0xfe, 0x3f, 0xe1, 0xff, 0x0f, 0xfc, 0x7d, 0xf3, 0xef,
    0x9f, 0x3e, 0xf9, 0xf7, 0xc7, 0xc0,
    /* U+006C "l" (6x18) */
    0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0xbf,
    0x7c, 0xf0,
    /* U+006D "m" (18x13) */
    0xf3, 0xcf, 0xbf, 0xff, 0xef, 0xff, 0xff, 0xe7, 0xdf, 0xf9, 0xe3, 0xfe,
    0x78, 0xff, 0x9e, 0x3f, 0xe7, 0x8f, 0xf9, 0xe3, 0xfe, 0x78, 0xff, 0x9e,
    0x3f, 0xe7, 0x8f, 0xf9, 0xe3, 0xc0,
    /* U+006E "n" (12x13) */
    0xf3, 0xcf, 0xfe, 0xff, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f,
    0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xf0,
    /* U+006F "o" (12x13) */
    0x1f, 0x83, 0xfc, 0x7f, 0xef, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x9f, 0x7f, 0xe3, 0xfc, 0x1f, 0x80,
    /* U+0070 "p" (13x18) */
    0xf3, 0xc7, 0xff, 0x3f, 0xfd, 0xf1, 0xef, 0x8f, 0x78, 0x7f, 0xc3, 0xfe,
    0x1f, 0xf0, 0xf7, 0xcf, 0xbf, 0xfd, 0xff, 0xcf, 0x38, 0x78, 0x03, 0xc0,
    0x1e, 0x00, 0xf0, 0x07, 0x80, 0x00,
    /* U+0071 "q" (12x18) */
    0x1e, 0xf7, 0xff, 0x7f, 0xff, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x9f, 0xff, 0xf7, 0xff, 0x3e, 0xf0, 0x0f, 0x00, 0xf0, 0x0f,
    0x00, 0xf0, 0x0f,
    /* U+0072 "r" (9x13) */
    0xf3, 0xfb, 0xff, 0xff, 0xef, 0xc7, 0xc3, 0xe1, 0xf0, 0xf8, 0x7c, 0x3e,
    0x1f, 0x0f, 0x80,
    /* U+0073 "s" (10x13) */
    0x3f, 0x1f, 0xff, 0xfb, 0xc6, 0xf8, 0x3f, 0x87, 0xf8, 0x7f, 0x03, 0xf0,
    0xff, 0xff, 0xfe, 0x3e, 0x00,
    /* U+0074 "t" (9x16) */
    0x3c, 0x1e, 0x0f, 0x1f, 0xff, 0xff, 0xf8, 0xf0, 0x78, 0x3c, 0x1e, 0x0f,
    0x07, 0x83, 0xc1, 0xfc, 0x7e, 0x1f,
    /* U+0075 "u" (11x13) */
    0xf1, 0xfe, 0x3f, 0xc7, 0xf8, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xff, 0x7f, 0xff, 0xbf, 0xf3, 0xce,
    /* U+0076 "v" (13x13) */
    0xf0, 0xff, 0xc7, 0x9e, 0x3c, 0xf1, 0xe7, 0x9e, 0x3c, 0xf0, 0xf7, 0x87,
    0xb8, 0x3d, 0xc0, 0xfe, 0x07, 0xf0, 0x3f, 0x00, 0xf8, 0x00,
    /* U+0077 "w" (18x13) */
    0xf1, 0xe3, 0xfc, 0x78, 0xf7, 0x9f, 0x3d, 0xe7, 0xcf, 0x7b, 0xf3, 0x9e,
    0xfd, 0xe7, 0xbb, 0x78, 0xec, 0xde, 0x3f, 0x3f, 0x8f, 0xcf, 0xc3, 0xf3,
    0xf0, 0xfc, 0xfc, 0x1f, 0x1f, 0x00,
    /* U+0078 "x" (13x13) */
    0xf8, 0xf3, 0xcf, 0x1f, 0x78, 0x7f, 0x81, 0xfc, 0x0f, 0xc0, 0x7e, 0x03,
    0xf8, 0x3f, 0xc1, 0xef, 0x1e, 0x78, 0xf3, 0xef, 0x0f, 0x80,
    /* U+0079 "y" (13x18) */
    0xf0, 0xff, 0xc7, 0xbe, 0x3c, 0xf1, 0xe7, 0x8e, 0x3c, 0xf0, 0xf7, 0x87,
    0xb8, 0x3d, 0xc0, 0xfe, 0x07, 0xf0, 0x3f, 0x01, 0xf8, 0x03, 0xc0, 0x3c,
    0x0f, 0xc0, 0x7c, 0x03, 0x80, 0x00,
    /* U+007A "z" (11x13) */
    0x7f, 0xef, 0xfd, 0xff, 0x83, 0xe0, 0x78, 0x1f, 0x07, 0xc1, 0xf0, 0x7c,
    0x0f, 0x83, 0xff, 0xff, 0xff, 0xfe,
    /* U+007B "{" (7x23) */
    0x0e, 0x7c, 0xf9, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0xf3, 0xe7, 0x8f, 0x8f,
    0x0f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xe7, 0xc3, 0x80,
    /* U+007C "|" (4x22) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (8x23) */
    0xf0, 0xfc, 0xfc, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3e, 0x1f, 0x0f,
    0x1f, 0x3e, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xfc, 0xf8, 0xf0,
    /* U+007E "~" (11x4) */
    0x7c, 0x5f, 0xff, 0xff, 0x63, 0xc0,
    /* U+00B0 "" (9x8) */
    0x3e, 0x3f, 0xb9, 0xdc, 0x7e, 0x3f, 0x39, 0xfc, 0x78,
    /* U+00B1 "" (11x16) */
    0x0e, 0x01, 0xc0, 0x38, 0x07, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x70, 0x0e,
    0x01, 0xc0, 0x38, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
    /* U+00B2 "" (8x10) */
    0x7c, 0xfe, 0x4f, 0x0f, 0x0e, 0x1c, 0x38, 0x70, 0xff, 0xff,
    /* U+00B3 "" (8x10) */
    0x7e, 0xfe, 0x0e, 0x1e, 0x3e, 0x0f, 0x07, 0x4f, 0xfe, 0x7c,
    /* U+00B5 "" (12x18) */
    0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e,
    0xf1, 0xef, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0xff, 0x00, 0xf0, 0x0f, 0x00,
    0xf0, 0x0f, 0x00,
    /* U+00B7 "" (4x5) */
    0x6f, 0xff, 0x60,
    /* U+00D7 "" (10x9) */
    0x21, 0x9c, 0xf7, 0xfc, 0xfe, 0x1f, 0x0f, 0xe7, 0xfb, 0xef, 0x71, 0x80,
    /* U+00F7 "" (11x17) */
    0x0e, 0x03, 0xc0, 0x7c, 0x0f, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff,
    0xff, 0xff, 0xff, 0x80, 0x00, 0xe0, 0x3c, 0x07, 0xc0, 0xf0, 0x0e, 0x00,
    /* U+0394 "" (15x16) */
    0x0f, 0xc0, 0x1f, 0x80, 0x3f, 0x80, 0xff, 0x01, 0xee, 0x03, 0xde, 0x0f,
    0x3c, 0x1e, 0x78, 0x3c, 0xf8, 0x78, 0xf1, 0xe1, 0xe3, 0xc3, 0xe7, 0x87,
    0xdf, 0xff, 0xbf, 0xff, 0xff, 0xff,
    /* U+03A9 "" (15x16) */
    0x0f, 0xc0, 0x3f, 0xe1, 0xff, 0xe3, 0xe3, 0xef, 0x83, 0xde, 0x07, 0xfc,
    0x0f, 0xf8, 0x1f, 0xf0, 0x3f, 0xe0, 0x7f, 0xc0, 0xf3, 0xc1, 0xc3, 0x87,
    0x1f, 0x9f, 0xbf, 0x3f, 0x7e, 0x7e,
    /* U+03B1 "" (13x13) */
    0x1e, 0x7b, 0xfb, 0x9f, 0xfd, 0xf3, 0xef, 0x1e, 0x78, 0xf3, 0xc3, 0x9e,
    0x3c, 0xf1, 0xe7, 0xdf, 0xbf, 0xfe, 0xfe, 0xe3, 0xc3, 0x00,
    /* U+03B2 "" (13x23) */
    0x1f, 0x81, 0xfe, 0x1f, 0xf9, 0xf3, 0xef, 0x0f, 0x78, 0x7b, 0xc7, 0x9e,
    0xf8, 0xf7, 0x87, 0xbf, 0xbc, 0x3f, 0xe0, 0xff, 0x07, 0xf8, 0x3f, 0xe3,
    0xff, 0xfe, 0xff, 0xf7, 0xbe, 0x3c, 0x01, 0xe0, 0x0f, 0x00, 0x78, 0x03,
    0x80, 0x00,
    /* U+03B3 "" (12x18) */
    0x70, 0xff, 0x0f, 0xf8, 0xf7, 0x9f, 0x79, 0xe3, 0xde, 0x3d, 0xc1, 0xfc,
    0x1f, 0xc1, 0xf8, 0x0f, 0x80, 0xf8, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    0x0f, 0x00, 0xf0,
    /* U+03B4 "" (12x18) */
    0x1f, 0x83, 0xfe, 0x7f, 0xc7, 0x88, 0x78, 0x07, 0xe0, 0x3f, 0x81, 0xfc,
    0x7b, 0xef, 0x1f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf9, 0xf7, 0xfe,
    0x7f, 0xc1, 0xf8,
    /* U+03B5 "" (10x13) */
    0x3f, 0x1f, 0xff, 0xff, 0xe2, 0xf8, 0x1f, 0xc3, 0xe3, 0xf8, 0xf0, 0x3c,
    0x2f, 0xff, 0xff, 0x3f, 0x80,
    /* U+03B8 "" (12x18) */
    0x1f, 0x03, 0xfc, 0x7f, 0xc7, 0x9e, 0xf1, 0xef, 0x0f, 0xf0, 0xff, 0x0f,
    0xff, 0xff, 0xff, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x1e, 0x79, 0xe7, 0xfc,
    0x3f, 0xc1, 0xf0,
    /* U+03BB "" (13x18) */
    0x38, 0x01, 0xf0, 0x0f, 0xc0, 0x1f, 0x00, 0x78, 0x07, 0xc0, 0x7f, 0x03,
    0xf8, 0x1f, 0xc0, 0xfe, 0x0f, 0x78, 0x7b, 0xc3, 0x9e, 0x3c, 0xf9, 0xe3,
    0xcf, 0x1f, 0xf8, 0xf9, 0x83, 0x00,
    /* U+03BC "" (12x18) */
    0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e,
    0xf1, 0xef, 0x9f, 0xff, 0xff, 0xff, 0xfc, 0xff, 0x00, 0xf0, 0x0f, 0x00,
    0xf0, 0x0f, 0x00,
    /* U+03C0 "" (14x13) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0xcf, 0x1f, 0x3c, 0x38,
    /* U+03C3 "" (13x13) */
    0x1f, 0xf9, 0xff, 0xdf, 0xff, 0xf1, 0xef, 0x0f, 0x78, 0x7b, 0xc3, 0xde,
    0x1e, 0xf0, 0xf7, 0xcf, 0x9f, 0xf8, 0x7f, 0x81, 0xf8, 0x00,
    /* U+03C4 "" (12x13) */
    0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    0x0f, 0x00, 0xf8, 0x0f, 0x80, 0x70, 0x03, 0x00,
    /* U+03C6 "" (17x18) */
    0x78, 0x7c, 0x3c, 0xff, 0x3c, 0x7f, 0xde, 0x79, 0xef, 0x3c, 0xf7, 0x9e,
    0x7b, 0xcf, 0x3f, 0xe7, 0x9f, 0xf3, 0xcf, 0x79, 0xe7, 0xbe, 0xf7, 0xcf,
    0xff, 0xc3, 0xff, 0xc0, 0x3f, 0x00, 0x0f, 0x00, 0x07, 0x80, 0x03, 0xc0,
    0x01, 0xe0, 0x00,
    /* U+03C9 "" (17x13) */
    0x78, 0x0f, 0x3c, 0x07, 0xbc, 0x03, 0xde, 0x01, 0xff, 0x3c, 0x7f, 0x9e,
    0x3f, 0xcf, 0x1f, 0xe7, 0x8f, 0xf3, 0xc7, 0xf9, 0xf7, 0xff, 0xff, 0xcf,
    0xef, 0xc3, 0xe3, 0xc0,
    /* U+2013 "" (12x3) */
    0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+2014 "" (19x3) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+2018 "" (4x8) */
    0x37, 0x76, 0xff, 0xf6,
    /* U+2019 "" (4x8) */
    0x6f, 0xff, 0x6e, 0xcc,
    /* U+201C "" (9x8) */
    0x31, 0xb8, 0xdc, 0xec, 0x7f, 0x7f, 0xbf, 0xde, 0xc6,
    /* U+201D "" (9x8) */
    0x63, 0x7b, 0xfd, 0xfe, 0xf6, 0x3f, 0x3b, 0x1d, 0x8c,
    /* U+2022 "" (7x7) */
    0x79, 0xfb, 0xff, 0xff, 0xff, 0x9e, 0x00,
    /* U+2026 "" (16x5) */
    0x63, 0x8e, 0xf3, 0xdf, 0xf7, 0xdf, 0xf3, 0xdf, 0x63, 0x8e,
    /* U+2030 "" (29x16) */
    0x3c, 0x06, 0x00, 0x03, 0xf0, 0x78, 0x00, 0x3f, 0xc3, 0x80, 0x01, 0xce,
    0x3c, 0x00, 0x0e, 0x73, 0xc0, 0x00, 0x7f, 0xbc, 0x00, 0x03, 0xf9, 0xc0,
    0x00, 0x07, 0x9e, 0xf0, 0x78, 0x01, 0xff, 0xc7, 0xf0, 0x1e, 0xff, 0x7f,
    0x80, 0xf7, 0x3b, 0x9e, 0x0f, 0x31, 0xdc, 0x70, 0xf1, 0xce, 0xe7, 0x87,
    0x0f, 0xf7, 0xf8, 0x78, 0x3f, 0x1f, 0xc1, 0x80, 0xf0, 0x78,
    /* U+2190 "" (18x16) */
    0x03, 0x00, 0x00, 0xe0, 0x00, 0x78, 0x00, 0x3e, 0x00, 0x1f, 0x00, 0x0f,
    0x80, 0x07, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xe3, 0xc0,
    0x00, 0x78, 0x00, 0x0f, 0x00, 0x03, 0xe0, 0x00, 0x78, 0x00, 0x0c, 0x00,
    /* U+2191 "" (16x17) */
    0x01, 0x80, 0x03, 0xc0, 0x07, 0xe0, 0x0f, 0xf0, 0x1f, 0xf8, 0x3f, 0xfc,
    0xfb, 0xfe, 0xf3, 0xdf, 0xe3, 0xce, 0x43, 0xc4, 0x03, 0xc0, 0x03, 0xc0,
    0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
    /* U+2192 "" (18x16) */
    0x00, 0x20, 0x00, 0x1c, 0x00, 0x0f, 0x80, 0x01, 0xf0, 0x00, 0x3e, 0x00,
    0x07, 0xcf, 0xff, 0xfb, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01,
    0xf0, 0x00, 0xf8, 0x00, 0x7c, 0x00, 0x3e, 0x00, 0x0f, 0x00, 0x00, 0x80,
    /* U+2193 "" (16x17) */
    0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0,
    0x03, 0xc0, 0x03, 0xc0, 0x63, 0xc6, 0xf3, 0xdf, 0xfb, 0xde, 0x7f, 0xfc,
    0x3f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 88, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 92, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 174, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 16, .adv_w = 218, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 213, .box_w = 13, .box_h = 23, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 80, .adv_w = 334, .box_w = 19, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 296, .box_w = 17, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 94, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 156, .adv_w = 125, .box_w = 7, .box_h = 24, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 177, .adv_w = 125, .box_w = 7, .box_h = 24, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 198, .adv_w = 174, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 212, .adv_w = 207, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 228, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 232, .adv_w = 157, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 235, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 200, .box_w = 9, .box_h = 23, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 264, .adv_w = 228, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 182, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 201, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 202, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 221, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 210, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 220, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 182, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 227, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 219, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 502, .adv_w = 92, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 92, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 518, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 535, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 548, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 565, .adv_w = 187, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 392, .box_w = 22, .box_h = 21, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 643, .adv_w = 229, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 238, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 222, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 251, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 201, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 187, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 249, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 254, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 113, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 123, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 876, .adv_w = 248, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 906, .adv_w = 199, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 303, .box_w = 17, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 252, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 988, .adv_w = 265, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 232, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 265, .box_w = 16, .box_h = 19, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1082, .adv_w = 238, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1110, .adv_w = 223, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 210, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 248, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1188, .adv_w = 221, .box_w = 14, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1216, .adv_w = 328, .box_w = 20, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1256, .adv_w = 228, .box_w = 14, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1284, .adv_w = 233, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1314, .adv_w = 211, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1340, .adv_w = 124, .box_w = 8, .box_h = 22, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1362, .adv_w = 200, .box_w = 9, .box_h = 22, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1387, .adv_w = 124, .box_w = 7, .box_h = 22, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1407, .adv_w = 217, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 12},
    {.bitmap_index = 1419, .adv_w = 200, .box_w = 12, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1424, .adv_w = 135, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 15},
    {.bitmap_index = 1429, .adv_w = 211, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 230, .box_w = 13, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1479, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1496, .adv_w = 230, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1523, .adv_w = 213, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1543, .adv_w = 139, .box_w = 10, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 215, .box_w = 13, .box_h = 19, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1597, .adv_w = 221, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1624, .adv_w = 108, .box_w = 5, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1637, .adv_w = 108, .box_w = 7, .box_h = 25, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1659, .adv_w = 217, .box_w = 13, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1689, .adv_w = 115, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1703, .adv_w = 323, .box_w = 18, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1733, .adv_w = 221, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1753, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1773, .adv_w = 230, .box_w = 13, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1803, .adv_w = 230, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1830, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1845, .adv_w = 187, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1862, .adv_w = 151, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1880, .adv_w = 218, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1898, .adv_w = 200, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1920, .adv_w = 291, .box_w = 18, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1950, .adv_w = 200, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1972, .adv_w = 202, .box_w = 13, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2002, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2020, .adv_w = 124, .box_w = 7, .box_h = 23, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2041, .adv_w = 141, .box_w = 4, .box_h = 22, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 2052, .adv_w = 124, .box_w = 8, .box_h = 23, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2075, .adv_w = 200, .box_w = 11, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2081, .adv_w = 200, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 2090, .adv_w = 208, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2112, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2122, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2132, .adv_w = 223, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2159, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2162, .adv_w = 201, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 2174, .adv_w = 201, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2198, .adv_w = 232, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2228, .adv_w = 265, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2258, .adv_w = 231, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2280, .adv_w = 234, .box_w = 13, .box_h = 23, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2318, .adv_w = 198, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2345, .adv_w = 222, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2372, .adv_w = 186, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2389, .adv_w = 215, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2416, .adv_w = 208, .box_w = 13, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2446, .adv_w = 223, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2473, .adv_w = 237, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2496, .adv_w = 233, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2518, .adv_w = 187, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2538, .adv_w = 292, .box_w = 17, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2577, .adv_w = 297, .box_w = 17, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2605, .adv_w = 200, .box_w = 12, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2610, .adv_w = 306, .box_w = 19, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2618, .adv_w = 95, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2622, .adv_w = 95, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2626, .adv_w = 177, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2635, .adv_w = 177, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2644, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2651, .adv_w = 278, .box_w = 16, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2661, .adv_w = 485, .box_w = 29, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2719, .adv_w = 346, .box_w = 18, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2755, .adv_w = 346, .box_w = 16, .box_h = 17, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2789, .adv_w = 346, .box_w = 18, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2825, .adv_w = 346, .box_w = 16, .box_h = 17, .ofs_x = 3, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0308, 0x030b, 0x030c, 0x0310, 0x0313,
    0x0314, 0x0316, 0x0319, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72,
    0x1f76, 0x1f80, 0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 36, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    2, 32, 3, 4, 3, 13, 3, 15, 3, 16, 3, 21, 3, 33, 3, 34,
    3, 43, 3, 64, 3, 104, 3, 112, 3, 126, 4, 5, 4, 7, 4, 12,
    4, 13, 4, 14, 4, 15, 4, 32, 4, 34, 4, 36, 4, 40, 4, 48,
    4, 50, 4, 52, 4, 57, 4, 58, 4, 59, 4, 61, 4, 64, 4, 66,
    4, 68, 4, 69, 4, 70, 4, 72, 4, 75, 4, 80, 4, 82, 4, 84,
    4, 86, 4, 91, 4, 95, 4, 101, 4, 103, 4, 104, 4, 106, 4, 109,
    4, 115, 4, 117, 4, 118, 4, 119, 4, 120, 4, 125, 4, 126, 5, 18,
    6, 3, 6, 8, 6, 11, 6, 18, 6, 32, 6, 61, 6, 121, 6, 122,
    6, 123, 6, 124, 7, 3, 7, 6, 7, 8, 7, 11, 7, 16, 7, 18,
    7, 21, 7, 22, 7, 24, 7, 26, 7, 32, 7, 33, 7, 43, 7, 53,
    7, 55, 7, 56, 7, 58, 7, 59, 7, 61, 7, 66, 7, 71, 7, 87,
    7, 88, 7, 90, 7, 108, 7, 114, 7, 116, 7, 121, 7, 122, 7, 123,
    7, 124, 7, 125, 7, 127, 8, 4, 8, 13, 8, 15, 8, 16, 8, 21,
    8, 33, 8, 34, 8, 43, 8, 64, 8, 104, 8, 112, 8, 126, 9, 18,
    9, 75, 11, 4, 11, 13, 11, 15, 11, 16, 11, 21, 11, 33, 11, 34,
    11, 64, 11, 66, 11, 104, 11, 126, 12, 5, 12, 6, 12, 7, 12, 13,
    12, 15, 12, 16, 12, 18, 12, 19, 12, 20, 12, 24, 12, 32, 12, 52,
    12, 53, 12, 55, 12, 57, 12, 58, 12, 59, 12, 61, 12, 64, 12, 89,
    12, 91, 12, 112, 12, 116, 12, 126, 12, 127, 13, 3, 13, 6, 13, 8,
    13, 11, 13, 12, 13, 14, 13, 17, 13, 18, 13, 21, 13, 26, 13, 32,
    13, 36, 13, 40, 13, 48, 13, 50, 13, 53, 13, 55, 13, 56, 13, 58,
    13, 61, 13, 71, 13, 85, 13, 87, 13, 88, 13, 90, 13, 95, 13, 98,
    13, 99, 13, 101, 13, 103, 13, 108, 13, 114, 13, 116, 13, 119, 13, 120,
    13, 121, 13, 122, 13, 123, 13, 124, 13, 127, 14, 5, 14, 6, 14, 7,
    14, 13, 14, 15, 14, 16, 14, 18, 14, 19, 14, 20, 14, 24, 14, 32,
    14, 52, 14, 53, 14, 55, 14, 57, 14, 58, 14, 59, 14, 61, 14, 64,
    14, 66, 14, 71, 14, 89, 14, 91, 14, 112, 14, 116, 14, 126, 14, 127,
    15, 3, 15, 6, 15, 8, 15, 11, 15, 12, 15, 14, 15, 17, 15, 18,
    15, 21, 15, 26, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53,
    15, 55, 15, 56, 15, 58, 15, 61, 15, 71, 15, 85, 15, 87, 15, 88,
    15, 90, 15, 95, 15, 98, 15, 99, 15, 101, 15, 103, 15, 108, 15, 114,
    15, 116, 15, 119, 15, 120, 15, 121, 15, 122, 15, 123, 15, 124, 15, 127,
    16, 4, 16, 6, 16, 7, 16, 12, 16, 13, 16, 14, 16, 15, 16, 16,
    16, 17, 16, 18, 16, 19, 16, 20, 16, 21, 16, 22, 16, 23, 16, 25,
    16, 26, 16, 27, 16, 28, 16, 32, 16, 33, 16, 34, 16, 36, 16, 40,
    16, 48, 16, 50, 16, 57, 16, 59, 16, 64, 16, 66, 16, 68, 16, 69,
    16, 70, 16, 71, 16, 72, 16, 78, 16, 79, 16, 80, 16, 81, 16, 82,
    16, 83, 16, 84, 16, 85, 16, 86, 16, 87, 16, 88, 16, 89, 16, 90,
    16, 91, 16, 95, 16, 100, 16, 101, 16, 103, 16, 104, 16, 105, 16, 106,
    16, 108, 16, 109, 16, 110, 16, 112, 16, 113, 16, 114, 16, 115, 16, 116,
    16, 117, 16, 118, 16, 119, 16, 120, 16, 125, 16, 126, 16, 127, 19, 12,
    19, 14, 19, 18, 19, 20, 19, 21, 19, 24, 19, 26, 19, 32, 19, 36,
    19, 40, 19, 43, 19, 48, 19, 50, 19, 53, 19, 55, 19, 56, 19, 58,
    19, 61, 19, 66, 19, 68, 19, 69, 19, 70, 19, 72, 19, 80, 19, 82,
    19, 87, 19, 90, 19, 95, 19, 101, 19, 103, 19, 106, 19, 108, 19, 109,
    19, 114, 19, 115, 19, 116, 19, 117, 19, 118, 19, 119, 19, 120, 20, 16,
    20, 18, 20, 19, 20, 26, 20, 32, 20, 53, 20, 58, 20, 61, 20, 64,
    21, 3, 21, 5, 21, 6, 21, 8, 21, 11, 21, 16, 21, 18, 21, 19,
    21, 20, 21, 24, 21, 26, 21, 32, 21, 52, 21, 53, 21, 55, 21, 58,
    21, 61, 21, 116, 21, 121, 21, 122, 21, 123, 21, 124, 21, 127, 22, 3,
    22, 8, 22, 18, 22, 24, 22, 53, 22, 55, 22, 58, 22, 61, 22, 121,
    22, 122, 22, 123, 22, 124, 23, 3, 23, 8, 23, 11, 23, 16, 23, 18,
    23, 19, 23, 24, 23, 26, 23, 32, 23, 53, 23, 55, 23, 58, 23, 61,
    23, 64, 23, 116, 23, 121, 23, 122, 23, 123, 23, 124, 24, 2, 24, 3,
    24, 6, 24, 8, 24, 11, 24, 13, 24, 15, 24, 16, 24, 21, 24, 64,
    24, 96, 24, 98, 24, 99, 24, 121, 24, 122, 24, 123, 24, 124, 24, 126,
    24, 127, 25, 18, 25, 58, 26, 5, 26, 13, 26, 15, 26, 16, 26, 18,
    26, 19, 26, 20, 26, 21, 26, 24, 26, 32, 26, 34, 26, 43, 26, 52,
    26, 53, 26, 58, 26, 59, 26, 61, 26, 64, 26, 66, 26, 104, 26, 112,
    26, 126, 27, 18, 27, 24, 27, 32, 27, 53, 27, 58, 27, 61, 28, 18,
    28, 24, 28, 32, 28, 53, 28, 58, 28, 61, 29, 18, 29, 20, 29, 26,
    29, 32, 29, 43, 29, 57, 29, 59, 29, 89, 30, 18, 30, 20, 30, 26,
    30, 32, 30, 43, 30, 57, 30, 59, 30, 89, 31, 18, 31, 20, 31, 26,
    31, 32, 31, 43, 31, 57, 31, 59, 31, 89, 32, 4, 32, 7, 32, 12,
    32, 13, 32, 14, 32, 15, 32, 16, 32, 21, 32, 32, 32, 64, 32, 95,
    32, 101, 32, 103, 32, 119, 32, 120, 32, 126, 33, 3, 33, 7, 33, 8,
    33, 11, 33, 13, 33, 15, 33, 18, 33, 19, 33, 20, 33, 24, 33, 26,
    33, 27, 33, 28, 33, 32, 33, 53, 33, 55, 33, 56, 33, 57, 33, 58,
    33, 59, 33, 61, 33, 64, 33, 84, 33, 89, 33, 91, 33, 114, 33, 116,
    33, 121, 33, 122, 33, 123, 33, 124, 33, 126, 34, 13, 34, 15, 34, 18,
    34, 19, 34, 27, 34, 28, 34, 53, 34, 58, 34, 62, 34, 94, 34, 126,
    35, 5, 35, 18, 35, 24, 35, 26, 35, 32, 35, 43, 35, 52, 35, 53,
    35, 57, 35, 58, 35, 61, 35, 64, 36, 12, 36, 14, 36, 17, 36, 18,
    36, 21, 36, 23, 36, 25, 36, 26, 36, 29, 36, 30, 36, 31, 36, 33,
    36, 36, 36, 40, 36, 43, 36, 48, 36, 50, 36, 58, 36, 61, 36, 68,
    36, 69, 36, 70, 36, 71, 36, 72, 36, 75, 36, 80, 36, 82, 36, 85,
    36, 87, 36, 88, 36, 90, 36, 95, 36, 101, 36, 102, 36, 103, 36, 106,
    36, 108, 36, 109, 36, 111, 36, 114, 36, 115, 36, 116, 36, 117, 36, 118,
    36, 119, 36, 120, 36, 125, 37, 13, 37, 15, 37, 18, 37, 19, 37, 20,
    37, 24, 37, 32, 37, 34, 37, 43, 37, 53, 37, 57, 37, 58, 37, 59,
    37, 61, 37, 64, 37, 66, 37, 89, 37, 91, 37, 104, 37, 110, 37, 112,
    37, 116, 37, 126, 38, 5, 38, 12, 38, 14, 38, 17, 38, 18, 38, 21,
    38, 23, 38, 25, 38, 26, 38, 33, 38, 36, 38, 40, 38, 43, 38, 48,
    38, 50, 38, 52, 38, 58, 38, 59, 38, 61, 38, 66, 38, 68, 38, 69,
    38, 70, 38, 71, 38, 72, 38, 77, 38, 78, 38, 79, 38, 80, 38, 81,
    38, 82, 38, 83, 38, 84, 38, 85, 38, 86, 38, 87, 38, 88, 38, 90,
    38, 95, 38, 100, 38, 101, 38, 103, 38, 105, 38, 106, 38, 108, 38, 109,
    38, 110, 38, 111, 38, 112, 38, 113, 38, 114, 38, 115, 38, 116, 38, 117,
    38, 118, 38, 119, 38, 120, 38, 125, 39, 4, 39, 5, 39, 7, 39, 12,
    39, 13, 39, 14, 39, 15, 39, 16, 39, 17, 39, 18, 39, 19, 39, 21,
    39, 22, 39, 23, 39, 25, 39, 26, 39, 27, 39, 28, 39, 29, 39, 30,
    39, 31, 39, 33, 39, 34, 39, 36, 39, 40, 39, 43, 39, 46, 39, 48,
    39, 50, 39, 52, 39, 59, 39, 64, 39, 66, 39, 67, 39, 68, 39, 69,
    39, 70, 39, 71, 39, 72, 39, 73, 39, 74, 39, 75, 39, 76, 39, 77,
    39, 78, 39, 79, 39, 80, 39, 81, 39, 82, 39, 83, 39, 84, 39, 85,
    39, 86, 39, 87, 39, 88, 39, 89, 39, 90, 39, 91, 39, 95, 39, 100,
    39, 101, 39, 102, 39, 103, 39, 104, 39, 105, 39, 106, 39, 107, 39, 108,
    39, 109, 39, 110, 39, 112, 39, 113, 39, 114, 39, 115, 39, 116, 39, 117,
    39, 118, 39, 119, 39, 120, 39, 126, 40, 3, 40, 8, 40, 18, 40, 19,
    40, 24, 40, 26, 40, 32, 40, 43, 40, 53, 40, 57, 40, 58, 40, 59,
    40, 61, 40, 121, 40, 122, 40, 123, 40, 124, 43, 64, 44, 5, 44, 7,
    44, 12, 44, 14, 44, 17, 44, 18, 44, 21, 44, 23, 44, 25, 44, 26,
    44, 29, 44, 30, 44, 31, 44, 32, 44, 33, 44, 36, 44, 40, 44, 43,
    44, 48, 44, 50, 44, 52, 44, 54, 44, 61, 44, 66, 44, 68, 44, 69,
    44, 70, 44, 71, 44, 72, 44, 75, 44, 80, 44, 82, 44, 85, 44, 86,
    44, 87, 44, 88, 44, 90, 44, 95, 44, 98, 44, 99, 44, 101, 44, 102,
    44, 103, 44, 105, 44, 106, 44, 108, 44, 109, 44, 110, 44, 115, 44, 116,
    44, 117, 44, 118, 44, 119, 44, 120, 44, 125, 45, 3, 45, 8, 45, 11,
    45, 12, 45, 14, 45, 18, 45, 24, 45, 26, 45, 32, 45, 36, 45, 40,
    45, 48, 45, 50, 45, 53, 45, 55, 45, 58, 45, 61, 45, 87, 45, 88,
    45, 90, 45, 95, 45, 98, 45, 99, 45, 101, 45, 103, 45, 108, 45, 119,
    45, 120, 45, 121, 45, 122, 45, 123, 45, 124, 45, 125, 46, 58, 48, 13,
    48, 15, 48, 18, 48, 19, 48, 20, 48, 24, 48, 32, 48, 34, 48, 43,
    48, 46, 48, 53, 48, 55, 48, 57, 48, 58, 48, 59, 48, 61, 48, 64,
    48, 66, 48, 89, 48, 91, 48, 104, 48, 110, 48, 112, 48, 116, 48, 126,
    49, 4, 49, 5, 49, 7, 49, 12, 49, 13, 49, 14, 49, 15, 49, 16,
    49, 18, 49, 19, 49, 20, 49, 21, 49, 22, 49, 23, 49, 24, 49, 25,
    49, 26, 49, 27, 49, 28, 49, 32, 49, 33, 49, 34, 49, 43, 49, 46,
    49, 52, 49, 53, 49, 55, 49, 56, 49, 57, 49, 58, 49, 59, 49, 61,
    49, 64, 49, 66, 49, 67, 49, 68, 49, 69, 49, 70, 49, 71, 49, 72,
    49, 73, 49, 75, 49, 76, 49, 77, 49, 78, 49, 79, 49, 80, 49, 81,
    49, 82, 49, 83, 49, 84, 49, 85, 49, 86, 49, 87, 49, 88, 49, 89,
    49, 90, 49, 91, 49, 95, 49, 100, 49, 101, 49, 103, 49, 104, 49, 105,
    49, 106, 49, 107, 49, 108, 49, 109, 49, 110, 49, 112, 49, 113, 49, 115,
    49, 116, 49, 117, 49, 118, 49, 119, 49, 120, 49, 126, 50, 13, 50, 15,
    50, 18, 50, 19, 50, 20, 50, 24, 50, 32, 50, 34, 50, 43, 50, 46,
    50, 53, 50, 55, 50, 57, 50, 58, 50, 59, 50, 61, 50, 64, 50, 66,
    50, 89, 50, 91, 50, 104, 50, 110, 50, 112, 50, 116, 50, 126, 51, 12,
    51, 14, 51, 18, 51, 21, 51, 32, 51, 53, 51, 58, 51, 61, 51, 95,
    51, 101, 51, 103, 51, 119, 51, 120, 51, 125, 52, 18, 52, 24, 52, 32,
    52, 53, 52, 55, 52, 58, 52, 61, 52, 64, 52, 98, 52, 99, 53, 4,
    53, 7, 53, 12, 53, 13, 53, 14, 53, 15, 53, 16, 53, 17, 53, 21,
    53, 23, 53, 27, 53, 28, 53, 33, 53, 34, 53, 36, 53, 40, 53, 48,
    53, 50, 53, 61, 53, 62, 53, 64, 53, 66, 53, 68, 53, 69, 53, 70,
    53, 71, 53, 72, 53, 75, 53, 78, 53, 79, 53, 80, 53, 81, 53, 82,
    53, 83, 53, 84, 53, 85, 53, 86, 53, 87, 53, 88, 53, 89, 53, 90,
    53, 91, 53, 95, 53, 100, 53, 101, 53, 103, 53, 104, 53, 105, 53, 106,
    53, 108, 53, 109, 53, 110, 53, 112, 53, 113, 53, 115, 53, 116, 53, 117,
    53, 118, 53, 119, 53, 120, 53, 125, 53, 126, 54, 5, 54, 13, 54, 15,
    54, 16, 54, 34, 54, 43, 54, 52, 54, 57, 54, 59, 54, 64, 54, 66,
    54, 84, 54, 91, 54, 104, 54, 112, 54, 126, 55, 5, 55, 7, 55, 12,
    55, 13, 55, 14, 55, 15, 55, 16, 55, 18, 55, 21, 55, 33, 55, 34,
    55, 52, 55, 59, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72,
    55, 80, 55, 82, 55, 84, 55, 86, 55, 89, 55, 91, 55, 95, 55, 101,
    55, 103, 55, 104, 55, 106, 55, 109, 55, 110, 55, 112, 55, 115, 55, 117,
    55, 118, 55, 119, 55, 120, 55, 126, 56, 5, 56, 7, 56, 13, 56, 15,
    56, 18, 56, 21, 56, 22, 56, 33, 56, 43, 56, 52, 56, 59, 56, 64,
    56, 66, 56, 68, 56, 69, 56, 70, 56, 71, 56, 72, 56, 78, 56, 79,
    56, 80, 56, 81, 56, 82, 56, 83, 56, 84, 56, 85, 56, 86, 56, 89,
    56, 91, 56, 100, 56, 105, 56, 106, 56, 109, 56, 112, 56, 113, 56, 115,
    56, 117, 56, 118, 56, 126, 57, 12, 57, 14, 57, 18, 57, 62, 57, 95,
    57, 101, 57, 103, 57, 116, 57, 119, 57, 120, 58, 4, 58, 5, 58, 7,
    58, 12, 58, 13, 58, 14, 58, 15, 58, 16, 58, 17, 58, 18, 58, 19,
    58, 20, 58, 21, 58, 22, 58, 23, 58, 25, 58, 26, 58, 27, 58, 28,
    58, 33, 58, 34, 58, 36, 58, 40, 58, 43, 58, 46, 58, 48, 58, 50,
    58, 52, 58, 59, 58, 64, 58, 66, 58, 67, 58, 68, 58, 69, 58, 70,
    58, 71, 58, 72, 58, 73, 58, 75, 58, 76, 58, 77, 58, 78, 58, 79,
    58, 80, 58, 81, 58, 82, 58, 83, 58, 84, 58, 85, 58, 86, 58, 87,
    58, 88, 58, 89, 58, 90, 58, 91, 58, 95, 58, 100, 58, 101, 58, 103,
    58, 104, 58, 105, 58, 106, 58, 107, 58, 108, 58, 109, 58, 110, 58, 112,
    58, 113, 58, 115, 58, 116, 58, 117, 58, 118, 58, 119, 58, 120, 58, 125,
    58, 126, 59, 12, 59, 14, 59, 21, 59, 61, 59, 95, 59, 101, 59, 103,
    59, 116, 59, 119, 59, 120, 59, 125, 60, 18, 60, 75, 61, 3, 61, 6,
    61, 7, 61, 8, 61, 11, 61, 12, 61, 14, 61, 18, 61, 20, 61, 21,
    61, 23, 61, 24, 61, 26, 61, 32, 61, 33, 61, 53, 61, 55, 61, 58,
    61, 59, 61, 61, 61, 66, 61, 71, 61, 85, 61, 95, 61, 96, 61, 98,
    61, 99, 61, 101, 61, 103, 61, 116, 61, 119, 61, 120, 61, 121, 61, 122,
    61, 123, 61, 124, 61, 125, 61, 127, 64, 3, 64, 5, 64, 6, 64, 7,
    64, 8, 64, 11, 64, 12, 64, 14, 64, 17, 64, 18, 64, 21, 64, 23,
    64, 25, 64, 32, 64, 33, 64, 36, 64, 40, 64, 48, 64, 50, 64, 52,
    64, 53, 64, 54, 64, 55, 64, 56, 64, 58, 64, 61, 64, 64, 64, 66,
    64, 68, 64, 69, 64, 70, 64, 71, 64, 75, 64, 77, 64, 80, 64, 82,
    64, 85, 64, 86, 64, 87, 64, 88, 64, 90, 64, 95, 64, 98, 64, 99,
    64, 101, 64, 103, 64, 106, 64, 108, 64, 109, 64, 110, 64, 111, 64, 114,
    64, 115, 64, 116, 64, 117, 64, 118, 64, 119, 64, 120, 64, 121, 64, 122,
    64, 123, 64, 124, 64, 127, 66, 18, 66, 24, 66, 32, 66, 61, 67, 18,
    67, 24, 67, 32, 67, 61, 68, 7, 68, 12, 68, 14, 68, 17, 68, 18,
    68, 21, 68, 24, 68, 25, 68, 29, 68, 30, 68, 31, 68, 32, 68, 33,
    68, 61, 68, 66, 68, 68, 68, 69, 68, 70, 68, 72, 68, 80, 68, 82,
    68, 86, 68, 95, 68, 101, 68, 102, 68, 103, 68, 106, 68, 109, 68, 110,
    68, 111, 68, 115, 68, 116, 68, 117, 68, 118, 68, 119, 68, 120, 68, 125,
    70, 18, 70, 24, 70, 32, 70, 61, 71, 2, 71, 3, 71, 7, 71, 8,
    71, 10, 71, 11, 71, 12, 71, 13, 71, 14, 71, 15, 71, 16, 71, 24,
    71, 32, 71, 33, 71, 62, 71, 64, 71, 66, 71, 68, 71, 69, 71, 70,
    71, 80, 71, 82, 71, 91, 71, 94, 71, 95, 71, 101, 71, 103, 71, 106,
    71, 109, 71, 115, 71, 117, 71, 118, 71, 119, 71, 120, 71, 121, 71, 122,
    71, 123, 71, 124, 71, 126, 72, 64, 73, 18, 73, 24, 73, 32, 73, 58,
    73, 61, 76, 7, 76, 12, 76, 14, 76, 17, 76, 18, 76, 21, 76, 22,
    76, 23, 76, 26, 76, 29, 76, 30, 76, 31, 76, 32, 76, 33, 76, 61,
    76, 66, 76, 68, 76, 69, 76, 70, 76, 72, 76, 80, 76, 82, 76, 84,
    76, 86, 76, 95, 76, 101, 76, 102, 76, 103, 76, 106, 76, 109, 76, 110,
    76, 115, 76, 117, 76, 118, 76, 119, 76, 120, 76, 125, 78, 18, 78, 32,
    78, 58, 78, 61, 79, 18, 79, 24, 79, 32, 79, 58, 79, 61, 80, 18,
    80, 24, 80, 32, 80, 61, 80, 116, 81, 18, 81, 24, 81, 32, 81, 61,
    82, 75, 83, 4, 83, 7, 83, 12, 83, 13, 83, 14, 83, 15, 83, 16,
    83, 20, 83, 21, 83, 32, 83, 33, 83, 61, 83, 64, 83, 66, 83, 68,
    83, 69, 83, 70, 83, 80, 83, 82, 83, 95, 83, 101, 83, 103, 83, 106,
    83, 109, 83, 110, 83, 112, 83, 115, 83, 117, 83, 118, 83, 119, 83, 120,
    83, 126, 84, 3, 84, 8, 84, 12, 84, 14, 84, 18, 84, 19, 84, 22,
    84, 24, 84, 26, 84, 32, 84, 61, 84, 64, 84, 66, 84, 87, 84, 89,
    84, 90, 84, 95, 84, 98, 84, 99, 84, 101, 84, 103, 84, 108, 84, 119,
    84, 120, 84, 121, 84, 122, 84, 123, 84, 124, 85, 2, 85, 13, 85, 15,
    85, 27, 85, 28, 85, 62, 85, 126, 86, 18, 86, 24, 86, 32, 86, 61,
    87, 7, 87, 12, 87, 13, 87, 14, 87, 15, 87, 19, 87, 20, 87, 21,
    87, 32, 87, 61, 87, 64, 87, 66, 87, 68, 87, 69, 87, 70, 87, 72,
    87, 80, 87, 82, 87, 84, 87, 95, 87, 101, 87, 103, 87, 106, 87, 109,
    87, 110, 87, 112, 87, 115, 87, 117, 87, 118, 87, 119, 87, 120, 87, 126,
    88, 11, 89, 7, 89, 12, 89, 14, 89, 17, 89, 18, 89, 21, 89, 22,
    89, 23, 89, 26, 89, 29, 89, 30, 89, 31, 89, 32, 89, 33, 89, 61,
    89, 66, 89, 68, 89, 69, 89, 70, 89, 72, 89, 80, 89, 82, 89, 84,
    89, 86, 89, 95, 89, 101, 89, 102, 89, 103, 89, 106, 89, 109, 89, 110,
    89, 115, 89, 117, 89, 118, 89, 119, 89, 120, 89, 125, 90, 7, 90, 12,
    90, 13, 90, 14, 90, 15, 90, 19, 90, 20, 90, 21, 90, 32, 90, 61,
    90, 64, 90, 66, 90, 68, 90, 69, 90, 70, 90, 80, 90, 82, 90, 84,
    90, 95, 90, 101, 90, 103, 90, 106, 90, 109, 90, 110, 90, 112, 90, 115,
    90, 117, 90, 118, 90, 119, 90, 120, 90, 126, 91, 12, 91, 14, 91, 32,
    91, 61, 91, 95, 91, 101, 91, 103, 91, 119, 91, 120, 92, 75, 95, 5,
    95, 6, 95, 7, 95, 13, 95, 15, 95, 16, 95, 18, 95, 19, 95, 20,
    95, 21, 95, 22, 95, 24, 95, 26, 95, 32, 95, 34, 95, 43, 95, 52,
    95, 53, 95, 55, 95, 57, 95, 58, 95, 59, 95, 61, 95, 64, 95, 66,
    95, 71, 95, 75, 95, 85, 95, 87, 95, 89, 95, 90, 95, 91, 95, 104,
    95, 108, 95, 112, 95, 114, 95, 116, 95, 126, 95, 127, 96, 2, 96, 3,
    96, 8, 96, 11, 96, 12, 96, 13, 96, 14, 96, 15, 96, 16, 96, 27,
    96, 28, 96, 32, 96, 61, 96, 64, 96, 95, 96, 101, 96, 103, 96, 119,
    96, 120, 96, 121, 96, 122, 96, 123, 96, 124, 96, 126, 98, 13, 98, 15,
    98, 16, 98, 34, 98, 57, 98, 64, 98, 66, 98, 104, 98, 126, 99, 13,
    99, 15, 99, 16, 99, 34, 99, 57, 99, 64, 99, 66, 99, 104, 99, 126,
    100, 18, 100, 24, 100, 32, 100, 61, 101, 5, 101, 6, 101, 7, 101, 13,
    101, 15, 101, 16, 101, 18, 101, 19, 101, 20, 101, 24, 101, 32, 101, 43,
    101, 52, 101, 53, 101, 55, 101, 57, 101, 58, 101, 59, 101, 61, 101, 64,
    101, 66, 101, 71, 101, 89, 101, 91, 101, 112, 101, 116, 101, 126, 101, 127,
    102, 18, 102, 20, 102, 26, 102, 32, 102, 43, 102, 57, 102, 59, 102, 89,
    103, 5, 103, 6, 103, 7, 103, 13, 103, 15, 103, 16, 103, 18, 103, 19,
    103, 20, 103, 21, 103, 22, 103, 24, 103, 26, 103, 32, 103, 34, 103, 43,
    103, 52, 103, 53, 103, 55, 103, 57, 103, 58, 103, 59, 103, 61, 103, 64,
    103, 66, 103, 71, 103, 75, 103, 85, 103, 87, 103, 89, 103, 90, 103, 91,
    103, 104, 103, 108, 103, 112, 103, 114, 103, 116, 103, 126, 103, 127, 104, 3,
    104, 8, 104, 11, 104, 12, 104, 14, 104, 18, 104, 21, 104, 24, 104, 26,
    104, 32, 104, 36, 104, 40, 104, 48, 104, 50, 104, 53, 104, 54, 104, 55,
    104, 58, 104, 61, 104, 95, 104, 98, 104, 99, 104, 101, 104, 103, 104, 114,
    104, 116, 104, 119, 104, 120, 104, 121, 104, 122, 104, 123, 104, 124, 104, 125,
    105, 18, 105, 19, 105, 20, 105, 24, 105, 32, 105, 53, 105, 55, 105, 56,
    105, 57, 105, 58, 105, 59, 105, 61, 105, 116, 106, 61, 107, 3, 107, 8,
    107, 11, 107, 18, 107, 19, 107, 24, 107, 26, 107, 32, 107, 61, 107, 64,
    107, 87, 107, 90, 107, 98, 107, 99, 107, 108, 107, 112, 107, 114, 107, 116,
    107, 121, 107, 122, 107, 123, 107, 124, 108, 2, 108, 11, 108, 13, 108, 15,
    108, 27, 108, 28, 108, 98, 108, 99, 108, 126, 109, 18, 109, 19, 109, 20,
    109, 24, 109, 32, 109, 61, 109, 64, 109, 116, 110, 7, 110, 12, 110, 14,
    110, 17, 110, 18, 110, 21, 110, 22, 110, 23, 110, 24, 110, 25, 110, 26,
    110, 32, 110, 33, 110, 61, 110, 66, 110, 68, 110, 69, 110, 70, 110, 72,
    110, 80, 110, 82, 110, 86, 110, 95, 110, 101, 110, 103, 110, 106, 110, 109,
    110, 110, 110, 111, 110, 115, 110, 116, 110, 117, 110, 118, 110, 119, 110, 120,
    110, 125, 111, 98, 111, 99, 112, 3, 112, 8, 112, 11, 112, 12, 112, 13,
    112, 14, 112, 15, 112, 18, 112, 27, 112, 28, 112, 32, 112, 61, 112, 87,
    112, 90, 112, 95, 112, 98, 112, 99, 112, 101, 112, 103, 112, 108, 112, 114,
    112, 116, 112, 119, 112, 120, 112, 121, 112, 122, 112, 123, 112, 124, 112, 126,
    113, 18, 113, 24, 113, 32, 113, 61, 114, 16, 114, 32, 114, 61, 114, 112,
    115, 7, 115, 13, 115, 15, 115, 16, 115, 32, 115, 61, 115, 64, 115, 112,
    115, 126, 116, 4, 116, 7, 116, 12, 116, 13, 116, 14, 116, 15, 116, 16,
    116, 19, 116, 20, 116, 21, 116, 22, 116, 24, 116, 25, 116, 32, 116, 33,
    116, 61, 116, 64, 116, 66, 116, 68, 116, 69, 116, 70, 116, 75, 116, 80,
    116, 82, 116, 84, 116, 95, 116, 101, 116, 103, 116, 106, 116, 109, 116, 110,
    116, 112, 116, 115, 116, 117, 116, 118, 116, 119, 116, 120, 116, 126, 117, 18,
    117, 24, 117, 32, 117, 61, 117, 116, 118, 3, 118, 8, 118, 11, 118, 13,
    118, 15, 118, 18, 118, 19, 118, 20, 118, 22, 118, 24, 118, 26, 118, 32,
    118, 61, 118, 64, 118, 66, 118, 87, 118, 89, 118, 90, 118, 91, 118, 98,
    118, 99, 118, 108, 118, 112, 118, 114, 118, 116, 118, 121, 118, 122, 118, 123,
    118, 124, 118, 126, 119, 5, 119, 6, 119, 7, 119, 13, 119, 15, 119, 16,
    119, 18, 119, 19, 119, 20, 119, 21, 119, 22, 119, 24, 119, 26, 119, 32,
    119, 34, 119, 43, 119, 52, 119, 53, 119, 55, 119, 57, 119, 58, 119, 59,
    119, 61, 119, 64, 119, 66, 119, 71, 119, 75, 119, 85, 119, 87, 119, 89,
    119, 90, 119, 91, 119, 104, 119, 108, 119, 112, 119, 114, 119, 116, 119, 126,
    119, 127, 120, 5, 120, 7, 120, 13, 120, 15, 120, 16, 120, 18, 120, 19,
    120, 20, 120, 24, 120, 32, 120, 52, 120, 53, 120, 57, 120, 58, 120, 59,
    120, 61, 120, 64, 120, 89, 120, 91, 120, 112, 120, 126, 121, 4, 121, 13,
    121, 15, 121, 16, 121, 21, 121, 33, 121, 34, 121, 43, 121, 64, 121, 104,
    121, 112, 121, 126, 122, 4, 122, 13, 122, 15, 122, 16, 122, 21, 122, 33,
    122, 34, 122, 43, 122, 64, 122, 104, 122, 112, 122, 126, 123, 4, 123, 13,
    123, 15, 123, 16, 123, 21, 123, 24, 123, 34, 123, 64, 123, 104, 123, 126,
    124, 4, 124, 13, 124, 15, 124, 16, 124, 21, 124, 24, 124, 34, 124, 64,
    124, 104, 124, 126, 125, 5, 125, 7, 125, 16, 125, 18, 125, 19, 125, 20,
    125, 22, 125, 24, 125, 32, 125, 34, 125, 52, 125, 53, 125, 55, 125, 57,
    125, 58, 125, 59, 125, 61, 125, 66, 125, 89, 125, 91, 125, 104, 125, 112,
    126, 3, 126, 6, 126, 8, 126, 11, 126, 12, 126, 14, 126, 18, 126, 20,
    126, 22, 126, 32, 126, 34, 126, 53, 126, 55, 126, 58, 126, 59, 126, 61,
    126, 62, 126, 84, 126, 87, 126, 89, 126, 90, 126, 91, 126, 95, 126, 98,
    126, 99, 126, 101, 126, 103, 126, 104, 126, 108, 126, 116, 126, 119, 126, 120,
    126, 121, 126, 122, 126, 123, 126, 124, 126, 127, 127, 3, 127, 8, 127, 11,
    127, 18, 127, 32, 127, 61, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -8, -12, -38, -38, -38, -15, -8, -12, -8, -38, -12, -8, -38, -6, -8, -8,
    -15, -8, -15, -8, -4, -6, -6, -6, -6, -6, -4, -4, -6, -8, -31, -8,
    -6, -6, -6, -4, -4, -6, -6, -6, -4, -4, -8, -8, -8, -4, -6, -6,
    -6, -6, -6, -8, -8, -8, -15, -15, -23, -23, -19, -23, -23, -23, -23, -23,
    -23, -23, -31, -15, -31, -15, -15, -30, -8, -8, -12, -8, -31, -8, -5, -30,
    -18, -7, -30, -4, -38, -6, -8, -8, -8, -8, -8, -8, -19, -31, -31, -31,
    -31, -8, -15, -12, -38, -38, -38, -15, -8, -12, -8, -38, -12, -8, -38, -8,
    28, -8, -38, -38, -31, -12, -12, -12, -38, -8, -12, -38, -14, -8, -12, -19,
    -19, -23, -27, -17, -23, -23, -23, -14, -19, -8, -15, -23, -12, -23, -31, -13,
    -12, -12, -8, -19, -8, -38, -38, -38, -38, -19, -19, -5, -38, -7, -8, -19,
    -8, -8, -8, -8, -23, -19, -12, -38, -54, -7, -12, -15, -8, -15, -19, -19,
    -19, -19, -19, -15, -12, -31, -19, -19, -38, -38, -38, -38, -38, -14, -8, -12,
    -19, -19, -23, -27, -17, -23, -23, -23, -14, -19, -8, -15, -23, -12, -23, -31,
    -6, -6, -13, -12, -12, -8, -19, -8, -38, -38, -38, -38, -19, -19, -5, -38,
    -7, -8, -19, -8, -8, -8, -8, -23, -19, -12, -38, -54, -7, -12, -15, -8,
    -15, -19, -19, -19, -19, -19, -15, -12, -31, -19, -19, -38, -38, -38, -38, -38,
    -8, -8, -19, -23, -54, -23, -54, -46, -4, -23, -15, -12, -19, -8, -12, -10,
    -15, -19, -19, -23, -19, -8, -8, -8, -8, -8, -8, -8, -46, -19, -19, -19,
    -19, -12, -12, -12, -12, -19, -12, -19, -12, -12, -12, -12, -8, -8, -12, -8,
    -12, -23, -12, -23, -23, -8, -8, -19, -8, -19, -19, -15, -12, -15, -19, -23,
    -19, -19, -23, -23, -12, -54, -8, -5, -5, -8, -2, -11, -4, -4, -4, -4,
    -4, -6, -4, -4, -8, -4, -2, -12, -8, -4, -8, -8, -8, -8, -8, -8,
    -4, -4, -5, -5, -5, -8, -4, -8, -4, -8, -4, -8, -8, -5, -5, -8,
    -8, -4, -4, -4, -8, -8, -8, -8, -19, -8, -15, -19, -15, -8, -29, -8,
    -6, -11, -8, -19, -8, -19, -8, -23, -19, -12, -19, -19, -19, -19, -15, -12,
    -12, -22, -11, -15, -12, -15, -12, -12, -12, -12, -12, -8, -8, -8, -8, -22,
    -5, -10, -6, -12, -19, -8, -17, -12, -8, -12, -8, -8, -8, -8, 8, 7,
    4, 7, 7, -31, -31, -15, -15, -38, 4, 7, 7, 7, 7, 7, 7, -31,
    4, -12, -15, -4, -20, -20, -15, -8, -8, -8, -4, -4, -8, -4, -4, -4,
    -8, -15, -8, -15, -38, -4, -4, -4, -20, -12, -10, -15, -15, -23, -19, -12,
    -10, -15, -15, -23, -19, -8, -12, -4, -15, -5, -12, -8, -6, -8, -12, -4,
    -15, -5, -12, -8, -6, -8, -12, -4, -15, -5, -12, -8, -6, -12, -15, -16,
    -38, -16, -38, -31, -6, -9, -38, -16, -16, -16, -16, -16, -38, -8, -8, -8,
    -12, -12, -12, -12, -8, -8, -12, -4, -6, -6, -15, -19, -6, -4, -12, -16,
    -8, -19, -19, -4, -4, -4, -2, -8, -8, -8, -8, -8, -12, 3, 3, -19,
    4, 3, 3, -19, -22, 7, 7, 3, -8, -15, -12, -8, -8, -9, -8, -8,
    -8, -11, -8, -8, -31, -31, -8, -23, -16, -12, -8, -12, -20, -20, -20, -8,
    -8, -8, -7, -8, -8, -7, -8, -8, -8, -8, -8, -12, -7, -8, -8, -12,
    -19, -12, -19, -31, -31, -20, -31, -8, -19, -8, -10, -12, -8, -38, -8, -8,
    -31, -31, -23, -8, -8, -5, -10, -8, -8, -8, -4, -7, -13, -7, -15, -10,
    -8, -15, -4, -4, -4, -4, -4, -5, -4, -8, -4, -8, -8, -4, -11, -8,
    -6, -4, -6, -4, -5, -5, -5, -5, -5, -4, -2, -4, -12, -4, -8, -8,
    -8, -8, -8, -3, -4, -4, -8, -4, -8, -4, -2, -7, -6, -8, -4, -8,
    -8, -4, -8, -8, -4, -8, -8, -8, -4, -4, -4, -4, -4, -8, -15, -8,
    -8, -8, -8, -4, -12, -8, -12, -4, -31, -4, -31, -19, -4, -12, -4, -15,
    -8, -6, -10, -8, -8, -8, -5, -5, -5, -8, -19, -7, -7, -5, -11, -7,
    -7, -8, -8, -38, -23, -4, -13, -13, -13, -15, -17, -4, -10, -12, -4, -4,
    -13, -13, -13, -13, -13, -13, -17, -7, -13, -13, -10, -23, -13, -19, -4, -13,
    -4, -5, -4, -19, -12, -13, -4, -13, -13, -13, -19, -13, -12, -13, -15, -13,
    -13, -4, -4, -31, -4, -4, -15, -4, -7, -4, -4, -3, -9, -3, -11, -2,
    -6, -4, -4, -4, -4, -8, -4, -4, -15, -15, -3, -18, -12, -8, -5, -4,
    -12, -12, -12, -12, -12, -7, -7, -3, -7, -7, -4, -3, -8, -3, -7, -7,
    -7, -7, -6, -4, -7, -7, -5, -5, -7, -3, -7, -15, -5, -5, -15, -12,
    -15, -4, -7, -7, -7, -6, -7, -26, -7, -7, -15, -15, -11, -38, -38, -31,
    -38, -38, -46, -18, -23, -31, -16, -16, -16, -16, -37, -37, -35, -45, -30, -19,
    -30, -38, -38, -38, -38, -38, -30, -38, -38, -38, -38, -38, -38, -31, -9, -8,
    -8, -5, -10, -8, -8, -8, -4, -7, -3, -13, -2, -7, -15, -10, -8, -15,
    -4, -4, -4, -4, -4, -5, -4, -8, -12, -6, -18, -4, -46, -4, -46, -19,
    -7, -8, -8, -16, -6, -4, -8, -8, -2, -2, -2, -15, -12, -23, -15, -12,
    -6, -10, -8, -4, -15, -15, -13, -19, -38, -20, -8, -12, -12, -12, -2, -10,
    -8, -8, -8, -4, -8, -8, -12, -8, -12, -8, -10, -2, -10, -2, -2, -6,
    -2, -12, -4, -8, -4, -4, -23, -4, -12, -8, -2, -12, -12, -23, -8, -12,
    -4, -12, -12, -4, -4, -46, -8, -8, -5, -10, -8, -8, -8, -4, -7, -3,
    -13, -2, -7, -15, -10, -8, -15, -4, -4, -4, -4, -4, -5, -4, -8, -11,
    -11, -7, -8, -8, -8, -13, -8, -11, -11, -11, -11, -11, -8, -15, -8, -8,
    -8, -8, -8, -12, -12, -8, -8, -19, -15, -19, -23, -19, -23, -19, -12, -19,
    -15, -15, -15, -19, -19, -13, -13, -13, -13, -12, 7, -19, -19, -21, -21, -21,
    -15, -19, -12, -12, -12, -21, -12, -21, -12, -19, -15, -15, -15, -12, -15, -15,
    -15, -19, -12, -19, -19, -19, -11, -21, -15, -21, -19, -17, -12, -21, -19, -21,
    -21, -19, -19, -19, -23, -2, -4, -4, -4, -4, -3, -2, -3, -4, -12, -2,
    -2, -3, -4, -4, -4, -6, -8, -8, -19, -8, -19, -8, -8, -8, -6, -7,
    -6, -8, -19, -15, -10, -10, -10, -12, -10, -10, -8, -8, -7, -9, -8, -8,
    -8, -7, -10, -10, -6, -10, -10, -10, -10, -8, -8, -19, -4, -4, -12, -12,
    -8, -4, -4, -4, -3, -4, -8, -23, -12, -4, -4, -4, -2, -4, -2, -2,
    -4, -2, -4, -2, -4, -2, -4, -4, -5, -2, -2, -4, -4, -8, -2, -4,
    -4, -4, -12, -15, -15, -18, 7, -15, -15, -15, -26, -15, -15, -19, -8, -19,
    -23, -38, -23, -38, -23, -8, -15, -8, -8, -19, -8, -19, -15, -15, -23, -23,
    -16, -22, -15, -15, -7, -9, -15, -15, -8, -6, -31, -34, -4, -26, -26, -26,
    -15, -19, -4, -8, -4, -4, -22, -22, -26, -22, -26, -22, -23, -11, -22, -19,
    -12, -22, -19, -23, -23, -22, -23, -23, -22, -8, -26, -4, -19, -26, -26, -12,
    -22, -26, -19, -26, -26, -23, -23, -18, -38, -20, -20, -12, -15, -20, -20, -20,
    -19, -20, -20, -15, -15, 24, -38, -23, -23, -38, -31, -23, -23, -22, -12, -8,
    -8, -15, -15, -31, -12, -19, -8, -23, -8, -46, -8, -12, -8, -23, -31, -27,
    -27, -23, -23, -19, -23, -23, -38, -38, -38, -38, -12, -23, -38, -8, -31, -12,
    -38, -38, -31, -31, -12, -38, -46, -12, -8, -31, -12, -15, -15, -15, -15, -8,
    -19, -12, -19, -23, -31, -46, -4, -8, -8, -8, -8, -8, 28, -4, -8, -8,
    -8, -8, -12, -8, -12, -31, -31, -31, -31, -31, -8, -12, -8, -8, -12, -12,
    -8, -31, -8, -8, -31, -31, -38, -38, -38, -38, -31, -19, -12, -12, -15, -19,
    -15, -15, -19, -6, -14, -14, -4, -3, -12, -12, -4, -5, -5, -5, -13, -8,
    -12, -4, -8, -8, -8, -4, -8, -8, -4, -14, -14, -5, -14, -8, -8, -6,
    -4, -8, -2, -8, -8, -14, -14, -10, -19, -15, -15, -19, 25, 27, -4, 27,
    31, 19, -8, -19, -8, -19, -11, 23, 19, -6, 28, -12, -9, -4, -4, -4,
    -4, -4, -4, 28, -8, -8, -8, -4, -4, -4, -4, -4, -8, -8, 27, 27,
    27, 27, -19, 3, -12, -8, -12, -15, -12, -8, -13, -13, -3, -4, -6, -4,
    -4, -4, -6, -6, -6, -10, -4, -8, -6, -5, -5, -5, -3, -5, -5, -2,
    -3, -13, -13, -6, -13, -5, -5, -4, -5, -5, -5, -13, -13, -6, -12, -12,
    -15, -12, -12, -8, -12, -15, -12, -19, -15, -15, -19, -13, -19, -15, -15, -19,
    7, -8, -15, -10, -31, -10, -31, -23, -8, -12, -12, -6, -19, -31, -13, -12,
    -12, -12, -12, -12, -10, -10, -10, -12, -12, -8, -19, -12, -12, -12, -10, -10,
    -31, -6, -6, -4, -4, -12, -4, -4, -10, -4, -12, -12, -8, -4, -7, -4,
    -7, -4, -4, -4, -4, -4, -7, -4, -4, -6, -6, -6, -6, 3, 3, 3,
    3, 3, 4, 3, -8, -8, -8, -8, -7, -4, -15, -4, -15, -4, -7, -4,
    -12, -8, -12, -9, -3, -3, -3, -2, -3, -3, -3, -4, -4, -4, -3, -3,
    -4, -11, -3, -3, -3, -4, -4, -15, 7, -8, -13, -13, -3, -4, -6, -4,
    -4, -4, -6, -6, -6, -10, -4, -8, -6, -5, -5, -5, -3, -5, -5, -2,
    -3, -13, -13, -6, -13, -5, -5, -4, -5, -5, -5, -13, -13, -6, -7, -4,
    -15, -4, -15, -4, -7, -4, -12, -8, -12, -9, -3, -3, -3, -3, -3, -3,
    -4, -4, -4, -3, -3, -4, -11, -3, -3, -3, -4, -4, -15, -12, -12, -12,
    -12, -12, -12, -12, -12, -12, 21, -14, -8, -12, -19, -19, -23, -27, -17, -23,
    -4, -4, -23, -4, -23, -4, -5, -14, -19, -8, -15, -23, -12, -23, -31, -6,
    -6, -4, -2, -4, -13, -4, -12, -4, -4, -12, -4, -8, -19, -8, -24, -31,
    -31, -24, -35, -77, -35, -77, -62, -39, -39, -38, -31, -38, -35, -35, -35, -35,
    -35, -31, -31, -31, -31, -77, -19, -19, -23, -6, -5, -31, -8, -6, -19, -19,
    -19, -23, -6, -5, -31, -8, -6, -19, -8, -8, -8, -8, -14, -8, -12, -19,
    -19, -23, -27, -17, -23, -23, -23, -5, -14, -19, -8, -15, -23, -12, -23, -31,
    -6, -6, -13, -12, -12, -8, -19, -8, -8, -12, -4, -15, -5, -12, -8, -6,
    -14, -8, -12, -19, -19, -23, -27, -17, -23, -4, -4, -23, -4, -23, -4, -5,
    -14, -19, -8, -15, -23, -12, -23, -31, -6, -6, -4, -2, -4, -13, -4, -12,
    -4, -4, -12, -4, -8, -19, -8, -12, -12, -12, -4, -4, -19, -8, -8, -4,
    -12, -4, -4, -4, -4, -19, -4, -7, -22, -8, -4, -6, -6, -4, -4, -2,
    -12, -4, -4, -12, -12, -12, -12, -4, -6, -6, -6, -8, -8, -11, -2, -2,
    -4, -8, -4, -8, -6, -18, -8, -8, -8, -15, -4, -7, -4, -12, -12, -12,
    -5, -5, -4, -4, -5, -5, -3, -17, -8, -8, -8, -8, 7, 7, -15, -15,
    3, 3, 7, 7, -15, -19, -8, -8, -15, -15, -19, -8, -13, -6, -13, -13,
    -6, -6, -10, -4, -8, -12, -6, -6, -15, -8, -12, -8, -10, -10, -10, -6,
    -10, -10, -4, -13, -13, -13, -10, -10, -6, -6, -10, -4, -10, -10, -13, -13,
    -8, 3, 3, -23, -23, -15, -11, 8, -11, 8, -23, 8, 8, -18, -23, -11,
    -11, -11, -12, -12, -11, -11, -11, -9, -22, -11, -11, -23, -23, -23, -23, 8,
    -8, -8, -8, -8, -8, -8, -12, -6, -6, -11, -11, -8, -8, -19, -19, -9,
    -11, -8, -12, -8, -23, -8, -23, -12, -8, -8, -12, -4, -12, -8, -15, -12,
    -12, -23, -15, -10, -10, -10, -6, -10, -10, -8, -8, -8, -8, -10, -10, -10,
    -15, -10, -10, -10, -8, -8, -23, -19, -15, -15, -19, -13, -4, -4, -4, -4,
    -4, -19, -8, -8, -4, -15, -4, -15, -19, -8, -4, -3, -5, -3, -3, -2,
    -2, -3, -6, -6, -13, -4, -4, -4, -4, -4, -14, -8, -12, -19, -19, -23,
    -27, -17, -23, -4, -4, -23, -4, -23, -4, -5, -14, -19, -8, -15, -23, -12,
    -23, -31, -6, -6, -4, -2, -4, -13, -4, -12, -4, -4, -12, -4, -8, -19,
    -8, -14, -12, -19, -19, -23, -27, -17, -23, -23, -23, -14, -19, -15, -23, -12,
    -23, -31, -13, -12, -12, -19, -12, -38, -38, -38, -15, -8, -12, -8, -38, -12,
    -8, -38, -12, -38, -38, -38, -15, -8, -12, -8, -38, -12, -8, -38, -12, -38,
    -38, -38, -15, 7, -12, -38, -12, -38, -12, -38, -38, -38, -15, 7, -12, -38,
    -12, -38, -10, -8, -12, -17, -16, -19, -4, -23, -15, -4, -10, -19, -4, -11,
    -18, -15, -12, -4, -6, -2, -4, -8, -38, -38, -38, -38, -19, -19, -38, 7,
    4, -19, 3, -23, -19, -38, 3, -54, 3, 3, -15, 3, -15, 3, -19, -19,
    -19, -19, -19, 3, -15, -31, -19, -19, -38, -38, -38, -38, -38, -31, -31, -19,
    -38, -23, -23, -31, -31, -31, -31,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 2311,
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

const lv_font_t humid1_font_fira_sans_bold_24 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 30,
    .base_line = 7,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 16,
    .x_height = 13,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_24,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_FIRA_SANS_BOLD_24 */
