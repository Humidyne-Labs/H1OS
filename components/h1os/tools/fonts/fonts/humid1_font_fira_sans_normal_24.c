/*******************************************************************************
 * Font: humid1_font_fira_sans_normal_24 (fira_sans normal)
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

#ifndef HUMID1_FONT_FIRA_SANS_NORMAL_24
#define HUMID1_FONT_FIRA_SANS_NORMAL_24 1
#endif

#if HUMID1_FONT_FIRA_SANS_NORMAL_24

extern const lv_font_t humid1_icon_fa7_solid_24;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x17) */
    0xee, 0xee, 0xee, 0xee, 0x66, 0x60, 0x06, 0xff, 0x60,
    /* U+0022 "" (8x6) */
    0xe7, 0xe7, 0xe7, 0xe7, 0x67, 0x67,
    /* U+0023 "#" (13x17) */
    0x1c, 0x70, 0xe3, 0x07, 0x18, 0x38, 0xc7, 0xff, 0xbf, 0xfc, 0xe3, 0x83,
    0x1c, 0x38, 0xe1, 0xc6, 0x0e, 0x31, 0xff, 0xef, 0xff, 0x1c, 0xe0, 0xc7,
    0x06, 0x38, 0x71, 0xc0,
    /* U+0024 "$" (11x23) */
    0x0e, 0x01, 0xc0, 0x38, 0x07, 0x03, 0xf8, 0xff, 0xbc, 0x37, 0x00, 0xe0,
    0x1e, 0x01, 0xf8, 0x1f, 0xc0, 0xfc, 0x03, 0xc0, 0x38, 0x07, 0x40, 0xfe,
    0x7f, 0xff, 0x1f, 0x80, 0xe0, 0x1c, 0x03, 0x80,
    /* U+0025 "%" (18x17) */
    0x3c, 0x06, 0x1f, 0x83, 0x8e, 0x70, 0xc3, 0x0c, 0x70, 0xc3, 0x38, 0x30,
    0xce, 0x0e, 0x77, 0x01, 0xfb, 0x80, 0x18, 0xe0, 0x00, 0x73, 0xe0, 0x39,
    0xfc, 0x0e, 0xe3, 0x07, 0x38, 0xc3, 0x8e, 0x30, 0xe1, 0xdc, 0x70, 0x7e,
    0x18, 0x0f, 0x00,
    /* U+0026 "&" (15x17) */
    0x1f, 0x00, 0x7f, 0x01, 0xef, 0x03, 0x8e, 0x07, 0x1c, 0x0e, 0x38, 0x0f,
    0xe0, 0x1f, 0x80, 0x3e, 0x0c, 0xfe, 0x3b, 0xce, 0x77, 0x0f, 0xce, 0x0f,
    0x9c, 0x0f, 0x3e, 0x7f, 0x3f, 0xef, 0x1f, 0x0c,
    /* U+0027 "'" (3x6) */
    0xff, 0xf6, 0xc0,
    /* U+0028 "(" (6x23) */
    0x0c, 0x73, 0x8e, 0x71, 0xce, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38,
    0xe1, 0xc7, 0x0e, 0x38, 0x71, 0xc0,
    /* U+0029 ")" (6x23) */
    0xc3, 0x87, 0x1c, 0x38, 0xe3, 0x87, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7,
    0x38, 0xe3, 0x9c, 0x73, 0x8c, 0x00,
    /* U+002A "" (9x9) */
    0x1c, 0x0e, 0x26, 0x3f, 0xff, 0xf9, 0xe0, 0xf8, 0xee, 0x66, 0x00,
    /* U+002B "+" (10x10) */
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0xff, 0xff, 0xf1, 0xe0, 0x38, 0x0e, 0x03,
    0x80,
    /* U+002C "," (4x8) */
    0x6f, 0xf7, 0x6e, 0xcc,
    /* U+002D "-" (8x2) */
    0xff, 0xff,
    /* U+002E "." (4x4) */
    0x6f, 0xf6,
    /* U+002F "/" (8x21) */
    0x07, 0x07, 0x07, 0x07, 0x0e, 0x0e, 0x0e, 0x0c, 0x1c, 0x1c, 0x1c, 0x18,
    0x38, 0x38, 0x38, 0x30, 0x70, 0x70, 0x70, 0xe0, 0xe0,
    /* U+0030 "0" (12x17) */
    0x0f, 0x03, 0xfc, 0x79, 0xc7, 0x0e, 0x70, 0xee, 0x0e, 0xe0, 0xee, 0x0f,
    0xe0, 0x7e, 0x0f, 0xe0, 0xee, 0x0e, 0x70, 0xe7, 0x0e, 0x79, 0xc3, 0xfc,
    0x0f, 0x00,
    /* U+0031 "1" (7x17) */
    0x0e, 0x3d, 0xff, 0xfe, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60,
    0xc1, 0x83, 0x06,
    /* U+0032 "2" (10x17) */
    0x3e, 0x1f, 0xee, 0x7b, 0x0f, 0x01, 0xc0, 0x70, 0x3c, 0x0e, 0x07, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0f, 0x03, 0xff, 0xff, 0xc0,
    /* U+0033 "3" (11x17) */
    0x1f, 0x0f, 0xf9, 0xcf, 0x00, 0xf0, 0x0e, 0x03, 0x80, 0x70, 0x7c, 0x0f,
    0x80, 0x78, 0x03, 0x80, 0x70, 0x0e, 0x81, 0xfc, 0xf3, 0xfe, 0x1f, 0x00,
    /* U+0034 "4" (12x16) */
    0x0e, 0x00, 0xe0, 0x1c, 0x01, 0xc0, 0x38, 0x03, 0x80, 0x79, 0xc7, 0x1c,
    0x71, 0xce, 0x1c, 0xff, 0xff, 0xff, 0x03, 0xc0, 0x1c, 0x01, 0xc0, 0x1c,
    /* U+0035 "5" (11x17) */
    0x7f, 0xcf, 0xf9, 0xc0, 0x30, 0x06, 0x00, 0xc0, 0x1f, 0xc3, 0xfc, 0x73,
    0xc0, 0x38, 0x07, 0x00, 0xf0, 0x1c, 0x83, 0xb9, 0xf7, 0xfc, 0x3e, 0x00,
    /* U+0036 "6" (11x17) */
    0x0f, 0x83, 0xf8, 0xf2, 0x3c, 0x07, 0x00, 0xe0, 0x39, 0xe7, 0xfe, 0xf9,
    0xfe, 0x1f, 0x83, 0xf0, 0x7f, 0x0e, 0xe1, 0xde, 0x71, 0xfe, 0x1f, 0x00,
    /* U+0037 "7" (10x16) */
    0xff, 0xff, 0xf0, 0x1c, 0x07, 0x03, 0x80, 0xe0, 0x78, 0x1c, 0x07, 0x03,
    0x80, 0xe0, 0x70, 0x1c, 0x0f, 0x03, 0x80, 0xe0,
    /* U+0038 "8" (12x17) */
    0x1f, 0x03, 0xfc, 0x79, 0xe7, 0x0e, 0x70, 0xe7, 0x0e, 0x79, 0xc3, 0xf8,
    0x3f, 0x87, 0x3e, 0xe0, 0xee, 0x0f, 0xe0, 0x7e, 0x0f, 0x79, 0xe7, 0xfc,
    0x1f, 0x80,
    /* U+0039 "9" (11x17) */
    0x1f, 0x07, 0xf1, 0xef, 0x70, 0xfe, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xfb,
    0xef, 0xfc, 0xf7, 0x80, 0xe0, 0x3c, 0x0f, 0x07, 0xc3, 0xf0, 0x70, 0x00,
    /* U+003A ":" (4x13) */
    0x6f, 0xf6, 0x00, 0x00, 0x06, 0xff, 0x60,
    /* U+003B ";" (4x17) */
    0x6f, 0xf6, 0x00, 0x00, 0x06, 0xff, 0x76, 0xec, 0xc0,
    /* U+003C "<" (10x10) */
    0x01, 0xc1, 0xf3, 0xf3, 0xf0, 0xf0, 0x3c, 0x0f, 0xc0, 0xfc, 0x07, 0xc0,
    0x70,
    /* U+003D "=" (10x6) */
    0xff, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xf0,
    /* U+003E ">" (10x10) */
    0x60, 0x3f, 0x03, 0xf0, 0x3f, 0x03, 0xc0, 0x70, 0xfc, 0xfc, 0xfc, 0x18,
    0x00,
    /* U+003F "?" (10x17) */
    0x3e, 0x1f, 0xee, 0x39, 0x07, 0x03, 0xc0, 0xe0, 0xf0, 0x78, 0x1c, 0x06,
    0x01, 0x80, 0x00, 0x00, 0x06, 0x03, 0xc0, 0xf0, 0x18, 0x00,
    /* U+0040 "@" (22x22) */
    0x00, 0xfe, 0x00, 0x0f, 0xff, 0x00, 0xfc, 0x7e, 0x07, 0x80, 0x3c, 0x3c,
    0x00, 0x78, 0xe1, 0xf8, 0xe7, 0x0f, 0xf1, 0xdc, 0x71, 0xc7, 0x71, 0xc7,
    0x1f, 0x8e, 0x1c, 0x7e, 0x38, 0x71, 0xf8, 0xe1, 0xc7, 0xe3, 0x87, 0x1d,
    0xce, 0x1c, 0x67, 0x1c, 0xfb, 0x9c, 0x7e, 0xfc, 0x38, 0xf1, 0xe0, 0xf0,
    0x00, 0x01, 0xe0, 0x00, 0x03, 0xf0, 0xe0, 0x07, 0xff, 0x80, 0x03, 0xfc,
    0x00,
    /* U+0041 "A" (14x17) */
    0x07, 0x80, 0x1e, 0x00, 0xfc, 0x03, 0xf0, 0x0d, 0xc0, 0x73, 0x81, 0xce,
    0x07, 0x38, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0x0f, 0xfc, 0x7f, 0xf9, 0xc0,
    0xe7, 0x03, 0xbc, 0x0f, 0xe0, 0x1c,
    /* U+0042 "B" (12x17) */
    0xff, 0x0f, 0xfc, 0xe3, 0xee, 0x0e, 0xe0, 0xee, 0x0e, 0xe1, 0xcf, 0xf8,
    0xff, 0xce, 0x3e, 0xe0, 0xfe, 0x0f, 0xe0, 0xfe, 0x0f, 0xe3, 0xef, 0xfe,
    0xff, 0x80,
    /* U+0043 "C" (12x17) */
    0x07, 0xc1, 0xff, 0x3c, 0x67, 0x80, 0x70, 0x0f, 0x00, 0xf0, 0x0e, 0x00,
    0xe0, 0x0e, 0x00, 0xf0, 0x0f, 0x00, 0x70, 0x07, 0x80, 0x3c, 0x71, 0xff,
    0x07, 0xc0,
    /* U+0044 "D" (13x17) */
    0xff, 0x07, 0xfe, 0x38, 0xf9, 0xc1, 0xee, 0x0f, 0x70, 0x3b, 0x81, 0xdc,
    0x0f, 0xe0, 0x7f, 0x03, 0xf8, 0x1d, 0xc0, 0xee, 0x0f, 0x70, 0x73, 0x8f,
    0x9f, 0xf8, 0xff, 0x00,
    /* U+0045 "E" (10x17) */
    0xff, 0xff, 0xff, 0xfb, 0x80, 0xe0, 0x38, 0x0e, 0x03, 0xfc, 0xff, 0xbf,
    0xee, 0x03, 0x80, 0xe0, 0x38, 0x0f, 0xfb, 0xff, 0xff, 0xc0,
    /* U+0046 "F" (9x17) */
    0xff, 0xff, 0xff, 0xfc, 0x0e, 0x07, 0x03, 0x81, 0xfe, 0xff, 0x7f, 0xb8,
    0x1c, 0x0e, 0x07, 0x03, 0x81, 0xc0, 0xe0, 0x00,
    /* U+0047 "G" (13x17) */
    0x07, 0xe0, 0xff, 0x8f, 0x9c, 0xf0, 0x07, 0x00, 0x78, 0x03, 0xc0, 0x1c,
    0x3f, 0xe1, 0xff, 0x01, 0xfc, 0x0f, 0xe0, 0x77, 0x03, 0xbc, 0x1c, 0xf3,
    0xe3, 0xff, 0x0f, 0xe0,
    /* U+0048 "H" (12x17) */
    0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x70,
    /* U+0049 "I" (3x17) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
    /* U+004A "J" (6x20) */
    0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x39, 0xef, 0x38,
    /* U+004B "K" (13x17) */
    0xe0, 0x77, 0x07, 0x38, 0x79, 0xc7, 0x8e, 0x38, 0x73, 0x83, 0xbc, 0x1f,
    0xc0, 0xfe, 0x07, 0x78, 0x39, 0xe1, 0xcf, 0x0e, 0x3c, 0x70, 0xf3, 0x87,
    0x9c, 0x1e, 0xe0, 0x78,
    /* U+004C "L" (10x17) */
    0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x38,
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0x0f, 0xff, 0xff, 0xff, 0xc0,
    /* U+004D "M" (17x17) */
    0x7c, 0x1e, 0x3e, 0x0f, 0x9f, 0x07, 0xcf, 0x87, 0xe7, 0xe3, 0xf3, 0xf1,
    0xb9, 0xd8, 0xdc, 0xec, 0xee, 0x77, 0x77, 0x3b, 0xb3, 0x9c, 0xd9, 0xce,
    0x7c, 0xee, 0x3e, 0x77, 0x1e, 0x3b, 0x87, 0x1d, 0xc0, 0x0f, 0xe0, 0x03,
    0x80,
    /* U+004E "N" (12x17) */
    0xf0, 0x7f, 0x87, 0xf8, 0x7f, 0x87, 0xfc, 0x7f, 0xc7, 0xee, 0x7e, 0xe7,
    0xef, 0x7e, 0x77, 0xe7, 0x7e, 0x3f, 0xe3, 0xfe, 0x1f, 0xe1, 0xfe, 0x1f,
    0xe0, 0xf0,
    /* U+004F "O" (15x17) */
    0x07, 0xc0, 0x3f, 0xe0, 0xf3, 0xe3, 0xc1, 0xc7, 0x01, 0xde, 0x03, 0xb8,
    0x07, 0x70, 0x0e, 0xe0, 0x1f, 0xc0, 0x3b, 0x80, 0x77, 0x80, 0xe7, 0x01,
    0xcf, 0x07, 0x0f, 0x3e, 0x0f, 0xf8, 0x07, 0xc0,
    /* U+0050 "P" (12x17) */
    0xff, 0x0f, 0xfc, 0xe3, 0xee, 0x0e, 0xe0, 0xfe, 0x0f, 0xe0, 0xfe, 0x0e,
    0xe1, 0xef, 0xfc, 0xff, 0x8e, 0x00, 0xe0, 0x0e, 0x00, 0xe0, 0x0e, 0x00,
    0xe0, 0x00,
    /* U+0051 "Q" (15x19) */
    0x07, 0xc0, 0x3f, 0xe0, 0xf1, 0xe3, 0xc1, 0xc7, 0x01, 0xde, 0x03, 0xb8,
    0x07, 0x70, 0x0e, 0xe0, 0x1d, 0xc0, 0x3b, 0x80, 0x77, 0x80, 0xe7, 0x01,
    0xcf, 0x07, 0x0f, 0x1c, 0x0f, 0xf0, 0x07, 0xfc, 0x00, 0x7c, 0x00, 0x30,
    /* U+0052 "R" (12x17) */
    0xff, 0x0f, 0xfc, 0xe3, 0xee, 0x0e, 0xe0, 0xee, 0x0e, 0xe0, 0xee, 0x1e,
    0xff, 0xcf, 0xf8, 0xe7, 0x8e, 0x38, 0xe3, 0xce, 0x1c, 0xe1, 0xee, 0x0f,
    0xe0, 0xf0,
    /* U+0053 "S" (12x17) */
    0x1f, 0x87, 0xfe, 0x79, 0xef, 0x04, 0xe0, 0x0f, 0x00, 0x7c, 0x07, 0xf8,
    0x1f, 0xc0, 0x7e, 0x01, 0xe0, 0x0f, 0x00, 0xf4, 0x0e, 0xf3, 0xef, 0xfc,
    0x3f, 0x00,
    /* U+0054 "T" (13x17) */
    0xff, 0xff, 0xff, 0x81, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x80, 0x1c, 0x00,
    0xe0, 0x07, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x80, 0x1c,
    0x00, 0xe0, 0x07, 0x00,
    /* U+0055 "U" (12x17) */
    0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x0f, 0x79, 0xe7, 0xfc,
    0x1f, 0x80,
    /* U+0056 "V" (13x17) */
    0xe0, 0x3f, 0x81, 0xdc, 0x0e, 0xe0, 0x77, 0x07, 0x1c, 0x38, 0xe1, 0xc7,
    0x0c, 0x38, 0xe0, 0xe7, 0x07, 0x38, 0x39, 0x80, 0xdc, 0x07, 0xe0, 0x3e,
    0x01, 0xf0, 0x07, 0x80,
    /* U+0057 "W" (19x17) */
    0xe1, 0xe0, 0xfc, 0x3c, 0x3b, 0x87, 0x87, 0x70, 0xf0, 0xee, 0x1f, 0x1d,
    0xc7, 0xe3, 0x98, 0xcc, 0x73, 0x99, 0x8c, 0x73, 0x33, 0x8e, 0x66, 0x71,
    0xdc, 0xee, 0x3b, 0x0d, 0xc3, 0x61, 0xb0, 0x7c, 0x3e, 0x0f, 0x87, 0xc1,
    0xf0, 0xf8, 0x3e, 0x1f, 0x00,
    /* U+0058 "X" (13x17) */
    0x70, 0x7b, 0xc3, 0x8e, 0x3c, 0x79, 0xc1, 0xde, 0x0f, 0xe0, 0x3e, 0x01,
    0xf0, 0x0f, 0x80, 0x7e, 0x07, 0xf0, 0x3b, 0xc3, 0xce, 0x1c, 0x79, 0xe1,
    0xce, 0x0f, 0xf0, 0x38,
    /* U+0059 "Y" (14x17) */
    0xf0, 0x3d, 0xc0, 0xe7, 0x87, 0x8e, 0x1c, 0x38, 0xf0, 0x73, 0x81, 0xce,
    0x03, 0xf0, 0x0f, 0xc0, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e,
    0x00, 0x78, 0x01, 0xe0, 0x07, 0x80,
    /* U+005A "Z" (11x17) */
    0xff, 0xff, 0xfc, 0x07, 0x80, 0xe0, 0x3c, 0x0f, 0x01, 0xc0, 0x78, 0x0e,
    0x03, 0x80, 0xf0, 0x1c, 0x07, 0x81, 0xe0, 0x3c, 0x07, 0xff, 0xff, 0xe0,
    /* U+005B "[" (6x22) */
    0xff, 0xfe, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38,
    0xe3, 0x8e, 0x38, 0xff, 0xf0,
    /* U+005C "" (8x21) */
    0xe0, 0xe0, 0x70, 0x70, 0x70, 0x30, 0x38, 0x38, 0x38, 0x18, 0x1c, 0x1c,
    0x1c, 0x0c, 0x0e, 0x0e, 0x0e, 0x06, 0x07, 0x07, 0x07,
    /* U+005D "]" (6x22) */
    0xff, 0xf1, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7,
    0x1c, 0x71, 0xcf, 0xff, 0xf0,
    /* U+005E "^" (11x8) */
    0x04, 0x01, 0xe0, 0x7c, 0x1d, 0xc3, 0xb8, 0xe3, 0x9c, 0x3f, 0x07,
    /* U+005F "_" (12x2) */
    0xff, 0xff, 0xff,
    /* U+0060 "`" (6x4) */
    0xe3, 0xe3, 0xc2,
    /* U+0061 "a" (11x13) */
    0x3f, 0x0f, 0xf1, 0x8f, 0x00, 0xe0, 0x1c, 0x7f, 0x9f, 0xf7, 0x8e, 0xe1,
    0xdc, 0x3b, 0xcf, 0xbf, 0x73, 0xc6,
    /* U+0062 "b" (11x18) */
    0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e, 0x01, 0xde, 0x3f, 0xf7, 0xde, 0xe1,
    0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xf8, 0x7f, 0x9e, 0xff, 0x9d,
    0xe0,
    /* U+0063 "c" (10x13) */
    0x0f, 0x0f, 0xf7, 0x99, 0xc0, 0xf0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x1c,
    0x07, 0x98, 0xff, 0x0f, 0x00,
    /* U+0064 "d" (11x18) */
    0x00, 0x60, 0x0c, 0x01, 0x80, 0x30, 0x06, 0x3c, 0xcf, 0xfb, 0xcf, 0x70,
    0xfe, 0x0f, 0x81, 0xf0, 0x3e, 0x07, 0xc0, 0xdc, 0x3b, 0xcf, 0x3f, 0xe3,
    0xcc,
    /* U+0065 "e" (11x13) */
    0x1f, 0x07, 0xf9, 0xe7, 0x38, 0x7e, 0x0f, 0xff, 0xff, 0xff, 0x00, 0xe0,
    0x0e, 0x01, 0xe3, 0x1f, 0xe1, 0xf8,
    /* U+0066 "f" (10x18) */
    0x0f, 0x87, 0xf3, 0xc8, 0xe0, 0x38, 0x3f, 0xcf, 0xf0, 0xf0, 0x38, 0x0e,
    0x03, 0x80, 0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x38, 0x0e, 0x00,
    /* U+0067 "g" (13x19) */
    0x00, 0x30, 0x7f, 0xcf, 0xf8, 0xf3, 0xc7, 0x0e, 0x38, 0x31, 0xc3, 0x87,
    0x3c, 0x3f, 0xc0, 0xfc, 0x0c, 0x00, 0x70, 0x03, 0xfe, 0x0f, 0xf8, 0x01,
    0xdc, 0x0e, 0x70, 0xf3, 0xff, 0x07, 0xf0,
    /* U+0068 "h" (10x18) */
    0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x39, 0xcf, 0xff, 0xef, 0xf1, 0xf8,
    0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x70,
    /* U+0069 "i" (3x19) */
    0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+006A "j" (5x24) */
    0x39, 0xce, 0x70, 0x00, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x77, 0x7b, 0x90,
    /* U+006B "k" (11x18) */
    0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e, 0x01, 0xc3, 0xb8, 0xe7, 0x1c, 0xe7,
    0x1d, 0xc3, 0xf8, 0x7f, 0x0e, 0xe1, 0xce, 0x39, 0xe7, 0x1c, 0xe3, 0xdc,
    0x3c,
    /* U+006C "l" (5x18) */
    0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xfb, 0xc0,
    /* U+006D "m" (17x13) */
    0xef, 0x1e, 0x7f, 0xdf, 0xbe, 0xf9, 0xdc, 0x38, 0xfe, 0x1c, 0x3f, 0x0e,
    0x1f, 0x87, 0x0f, 0xc3, 0x87, 0xe1, 0xc3, 0xf0, 0xe1, 0xf8, 0x70, 0xfc,
    0x38, 0x7e, 0x1c, 0x38,
    /* U+006E "n" (10x13) */
    0xe7, 0xbf, 0xff, 0xbf, 0xc7, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xe1, 0xc0,
    /* U+006F "o" (12x13) */
    0x0f, 0x83, 0xfc, 0x79, 0xe7, 0x0e, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x77, 0x0e, 0x79, 0xe3, 0xfc, 0x1f, 0x00,
    /* U+0070 "p" (11x18) */
    0xef, 0x9f, 0xfb, 0xef, 0x70, 0xfe, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x3f, 0xcf, 0x7f, 0xce, 0xf1, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c,
    0x00,
    /* U+0071 "q" (11x18) */
    0x1e, 0x67, 0xfd, 0xe7, 0xb8, 0x7f, 0x07, 0xc0, 0xf8, 0x1f, 0x03, 0xe0,
    0x6e, 0x1d, 0xe7, 0x9f, 0xf1, 0xe6, 0x00, 0xc0, 0x18, 0x03, 0x00, 0x60,
    0x0c,
    /* U+0072 "r" (7x13) */
    0xe7, 0xdf, 0xff, 0x8f, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0x0e, 0x00,
    /* U+0073 "s" (10x13) */
    0x3e, 0x1f, 0xef, 0x3b, 0x80, 0xf0, 0x1f, 0x03, 0xf0, 0x1e, 0x03, 0xc0,
    0x7e, 0x7b, 0xfe, 0x3e, 0x00,
    /* U+0074 "t" (9x16) */
    0x38, 0x1c, 0x0e, 0x1f, 0xef, 0xf1, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e,
    0x07, 0x03, 0x81, 0xe8, 0x7e, 0x1e,
    /* U+0075 "u" (10x13) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0xff, 0x7f, 0xff, 0x79, 0xc0,
    /* U+0076 "v" (12x13) */
    0xf0, 0x7f, 0x0f, 0x70, 0xe7, 0x0e, 0x78, 0xe3, 0x9c, 0x39, 0xc3, 0x9c,
    0x1d, 0x81, 0xf8, 0x1f, 0x80, 0xf0, 0x0f, 0x00,
    /* U+0077 "w" (17x13) */
    0xe1, 0xe3, 0xb8, 0xf1, 0xdc, 0x78, 0xee, 0x3c, 0x77, 0x3e, 0x33, 0x9b,
    0xb8, 0xcc, 0xdc, 0x76, 0x6e, 0x3b, 0x37, 0x1f, 0x9f, 0x07, 0x8f, 0x83,
    0xc7, 0xc1, 0xe1, 0xe0,
    /* U+0078 "x" (12x13) */
    0x70, 0xe7, 0x9e, 0x39, 0xc3, 0xf8, 0x1f, 0x80, 0xf0, 0x0f, 0x01, 0xf8,
    0x1f, 0x83, 0x9c, 0x79, 0xe7, 0x0e, 0xf0, 0xf0,
    /* U+0079 "y" (12x18) */
    0xe0, 0x77, 0x07, 0x70, 0xe7, 0x0e, 0x70, 0xe3, 0x9c, 0x39, 0xc3, 0x9c,
    0x19, 0x81, 0xf8, 0x1f, 0x80, 0xf0, 0x0f, 0x00, 0x70, 0x0e, 0x01, 0xe0,
    0x7c, 0x07, 0x00,
    /* U+007A "z" (10x13) */
    0x7f, 0xdf, 0xf0, 0x3c, 0x0e, 0x07, 0x03, 0xc0, 0xe0, 0x70, 0x3c, 0x1e,
    0x07, 0x03, 0xff, 0xff, 0xc0,
    /* U+007B "{" (7x23) */
    0x1e, 0x7c, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x73, 0xc7, 0x87, 0x87,
    0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0xc3, 0xc3, 0x80,
    /* U+007C "|" (3x22) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (6x23) */
    0xf3, 0xc7, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe1, 0xc7, 0x3c, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x7b, 0xce, 0x00,
    /* U+007E "~" (10x4) */
    0x38, 0x3f, 0x3c, 0xfc, 0x1e,
    /* U+00B0 "" (8x8) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,
    /* U+00B1 "" (10x14) */
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0xff, 0xff, 0xf0, 0xe0, 0x38, 0x0e, 0x03,
    0x80, 0x00, 0x00, 0xff, 0xff, 0xf0,
    /* U+00B2 "" (7x10) */
    0x7d, 0xfd, 0x38, 0x30, 0xe3, 0x8e, 0x38, 0xff, 0xfc,
    /* U+00B3 "" (8x11) */
    0x7c, 0xfe, 0x46, 0x06, 0x0e, 0x1c, 0x1e, 0x06, 0x4f, 0xfe, 0x3c,
    /* U+00B5 "" (10x18) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0xff, 0x7f, 0xff, 0xfc, 0xf8, 0x0e, 0x03, 0x80, 0xe0, 0x38, 0x00,
    /* U+00B7 "" (4x4) */
    0x6f, 0xf6,
    /* U+00D7 "" (9x9) */
    0x43, 0x73, 0xff, 0xcf, 0xc3, 0xc3, 0xf3, 0xfd, 0xcf, 0xc3, 0x00,
    /* U+00F7 "" (10x15) */
    0x0c, 0x07, 0x81, 0xe0, 0x30, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0,
    0x00, 0x00, 0x30, 0x1e, 0x07, 0x80, 0xc0,
    /* U+0394 "" (14x17) */
    0x07, 0x80, 0x1f, 0x00, 0xfc, 0x03, 0xf0, 0x0e, 0xc0, 0x73, 0x81, 0xce,
    0x07, 0x38, 0x18, 0x70, 0xe1, 0xc3, 0x87, 0x0e, 0x0e, 0x70, 0x39, 0xc0,
    0xe7, 0x03, 0xff, 0xff, 0xff, 0xfc,
    /* U+03A9 "" (14x17) */
    0x07, 0xc0, 0x7f, 0xc3, 0xc7, 0x9e, 0x0e, 0x70, 0x1f, 0xc0, 0x7e, 0x01,
    0xf8, 0x07, 0xe0, 0x1f, 0x80, 0x7e, 0x01, 0xdc, 0x07, 0x70, 0x1c, 0xe0,
    0xe3, 0xc7, 0x1f, 0x3f, 0x7c, 0xfc,
    /* U+03B1 "" (12x13) */
    0x1e, 0x73, 0xf7, 0x7b, 0xf7, 0x1e, 0xe0, 0xee, 0x0e, 0xe0, 0xee, 0x0e,
    0xe0, 0xef, 0x1e, 0x7b, 0x77, 0xf7, 0x1e, 0x30,
    /* U+03B2 "" (12x23) */
    0x1f, 0x07, 0xf8, 0xf3, 0xce, 0x1c, 0xe1, 0xce, 0x1c, 0xe3, 0xce, 0xf0,
    0xef, 0x8e, 0x3e, 0xe0, 0xee, 0x0f, 0xe0, 0x7e, 0x0f, 0xe0, 0xef, 0x1e,
    0xff, 0xce, 0xf8, 0xe0, 0x0e, 0x00, 0xe0, 0x0e, 0x00, 0xc0, 0x00,
    /* U+03B3 "" (12x18) */
    0x60, 0x6e, 0x0f, 0x70, 0xe7, 0x0e, 0x39, 0xc3, 0x9c, 0x39, 0xc1, 0xd8,
    0x1f, 0x81, 0xf0, 0x0f, 0x00, 0xf0, 0x0e, 0x00, 0xe0, 0x0e, 0x00, 0xe0,
    0x0e, 0x00, 0xe0,
    /* U+03B4 "" (12x18) */
    0x0f, 0x83, 0xfc, 0x39, 0xc7, 0x00, 0x38, 0x03, 0xc0, 0x1f, 0x01, 0xfc,
    0x31, 0xe7, 0x0e, 0xe0, 0xfe, 0x07, 0xe0, 0x7e, 0x0f, 0xf0, 0xe7, 0x9e,
    0x3f, 0xc1, 0xf0,
    /* U+03B5 "" (10x13) */
    0x1f, 0x1f, 0xe7, 0x99, 0xc0, 0x70, 0x0f, 0x83, 0xe1, 0xc0, 0xe0, 0x38,
    0x0f, 0x99, 0xff, 0x1f, 0x00,
    /* U+03B8 "" (12x18) */
    0x0f, 0x03, 0xf8, 0x79, 0xc7, 0x0e, 0x60, 0xee, 0x0e, 0xe0, 0x6e, 0x0e,
    0xff, 0xff, 0xff, 0xe0, 0x6e, 0x06, 0xe0, 0xe6, 0x0e, 0x70, 0xe7, 0x9c,
    0x3f, 0x80, 0xf0,
    /* U+03BB "" (11x18) */
    0x70, 0x0f, 0x00, 0x70, 0x07, 0x00, 0xe0, 0x3c, 0x07, 0xc1, 0xf8, 0x3f,
    0x07, 0x61, 0xce, 0x39, 0xc7, 0x38, 0xe3, 0xb8, 0x77, 0x0f, 0xe0, 0xf8,
    0x18,
    /* U+03BC "" (10x18) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0xff, 0x7f, 0xff, 0xfc, 0xf8, 0x0e, 0x03, 0x80, 0xe0, 0x38, 0x00,
    /* U+03C0 "" (14x13) */
    0x7f, 0xff, 0xff, 0xf3, 0xc7, 0x07, 0x1c, 0x1c, 0x70, 0x71, 0xc1, 0xc7,
    0x07, 0x1c, 0x1c, 0x70, 0x71, 0xc1, 0xc7, 0x87, 0x0e, 0x1c, 0x38,
    /* U+03C3 "" (13x13) */
    0x0f, 0xf9, 0xff, 0xdf, 0x38, 0xe1, 0xce, 0x07, 0x70, 0x3b, 0x81, 0xdc,
    0x0e, 0xe0, 0x73, 0x87, 0x1e, 0x78, 0x7f, 0x80, 0xf0, 0x00,
    /* U+03C4 "" (11x13) */
    0xff, 0xff, 0xfc, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e,
    0x01, 0xc0, 0x3c, 0x03, 0x80, 0x20,
    /* U+03C6 "" (16x18) */
    0x70, 0x78, 0x71, 0xfc, 0x71, 0xce, 0x71, 0x8e, 0xe3, 0x87, 0xe3, 0x87,
    0xe3, 0x87, 0xe3, 0x87, 0xe3, 0x87, 0x73, 0x8e, 0x73, 0x8e, 0x3f, 0xfc,
    0x1f, 0xf8, 0x03, 0xc0, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80,
    /* U+03C9 "" (16x13) */
    0x30, 0x0e, 0x70, 0x06, 0x70, 0x07, 0x70, 0x07, 0xe1, 0xc7, 0xe1, 0xc7,
    0xe1, 0xc7, 0xe1, 0xc7, 0xe1, 0xc7, 0x71, 0xc7, 0x7b, 0xef, 0x7f, 0x7e,
    0x1e, 0x3c,
    /* U+2013 "" (11x2) */
    0xff, 0xff, 0xfc,
    /* U+2014 "" (19x3) */
    0x7f, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+2018 "" (4x7) */
    0x36, 0x6e, 0xef, 0x60,
    /* U+2019 "" (4x7) */
    0x6f, 0xf6, 0xec, 0xc0,
    /* U+201C "" (8x7) */
    0x33, 0x63, 0x63, 0xe7, 0xe7, 0xf7, 0x67,
    /* U+201D "" (8x7) */
    0x67, 0xf7, 0xf7, 0x67, 0xe6, 0xc6, 0xc4,
    /* U+2022 "" (6x6) */
    0x7b, 0xff, 0xff, 0xfd, 0xe0,
    /* U+2026 "" (16x4) */
    0x61, 0x86, 0xf3, 0xcf, 0xf3, 0xcf, 0x61, 0x86,
    /* U+2030 "" (27x17) */
    0x3c, 0x06, 0x00, 0x0f, 0xc1, 0xc0, 0x03, 0x9c, 0x30, 0x00, 0x61, 0x8e,
    0x00, 0x0c, 0x33, 0x80, 0x01, 0x86, 0x70, 0x00, 0x39, 0xdc, 0x00, 0x03,
    0xf7, 0x00, 0x00, 0x18, 0xe0, 0x00, 0x00, 0x39, 0xf0, 0xf8, 0x0e, 0x7f,
    0x3f, 0x81, 0xdc, 0x6e, 0x30, 0x73, 0x8d, 0xc6, 0x1c, 0x71, 0xb8, 0xc3,
    0x87, 0x77, 0xb8, 0xe0, 0xfc, 0x7e, 0x18, 0x0f, 0x07, 0x80,
    /* U+2190 "" (16x15) */
    0x07, 0x00, 0x0f, 0x00, 0x1e, 0x00, 0x3c, 0x00, 0x38, 0x00, 0x70, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x78, 0x00, 0x3c, 0x00, 0x1e, 0x00,
    0x0f, 0x00, 0x07, 0x00, 0x02, 0x00,
    /* U+2191 "" (15x16) */
    0x01, 0x80, 0x07, 0x80, 0x3f, 0x80, 0xff, 0x83, 0xfb, 0x8f, 0x73, 0xfc,
    0xe3, 0xb1, 0xc3, 0x03, 0x80, 0x07, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x38,
    0x00, 0x70, 0x00, 0xe0, 0x01, 0xc0,
    /* U+2192 "" (16x15) */
    0x00, 0xc0, 0x00, 0xe0, 0x00, 0x70, 0x00, 0x78, 0x00, 0x3c, 0x00, 0x1e,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x1e, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x70,
    0x00, 0xf0, 0x00, 0xe0, 0x00, 0x40,
    /* U+2193 "" (15x17) */
    0x01, 0x80, 0x07, 0x00, 0x0e, 0x00, 0x1c, 0x00, 0x38, 0x00, 0x70, 0x00,
    0xe0, 0x01, 0xc0, 0x43, 0x85, 0xc7, 0x1f, 0xce, 0x79, 0xdd, 0xe1, 0xff,
    0x81, 0xfe, 0x01, 0xf8, 0x01, 0xe0, 0x01, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 93, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 162, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 15, .adv_w = 207, .box_w = 13, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 208, .box_w = 11, .box_h = 23, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 75, .adv_w = 324, .box_w = 18, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 286, .box_w = 15, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 88, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 149, .adv_w = 124, .box_w = 6, .box_h = 23, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 167, .adv_w = 124, .box_w = 6, .box_h = 23, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 185, .adv_w = 170, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 196, .adv_w = 198, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 209, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 213, .adv_w = 156, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 215, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 200, .box_w = 8, .box_h = 21, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 238, .adv_w = 220, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 173, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 195, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 196, .box_w = 11, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 211, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 200, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 211, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 175, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 417, .adv_w = 218, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 209, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 92, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 92, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 483, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 496, .adv_w = 196, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 504, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 517, .adv_w = 181, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 392, .box_w = 22, .box_h = 22, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 600, .adv_w = 224, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 235, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 218, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 249, .box_w = 13, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 204, .box_w = 10, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 188, .box_w = 9, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 245, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 258, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 113, .box_w = 3, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 120, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 828, .adv_w = 235, .box_w = 13, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 194, .box_w = 10, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 300, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 915, .adv_w = 258, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 265, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 227, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 999, .adv_w = 265, .box_w = 15, .box_h = 19, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1035, .adv_w = 235, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1061, .adv_w = 215, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 204, .box_w = 13, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1115, .adv_w = 252, .box_w = 12, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1141, .adv_w = 217, .box_w = 13, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1169, .adv_w = 321, .box_w = 19, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1210, .adv_w = 216, .box_w = 13, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 220, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1268, .adv_w = 205, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 124, .box_w = 6, .box_h = 22, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1309, .adv_w = 200, .box_w = 8, .box_h = 21, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1330, .adv_w = 124, .box_w = 6, .box_h = 22, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1347, .adv_w = 211, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 13},
    {.bitmap_index = 1358, .adv_w = 200, .box_w = 12, .box_h = 2, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1361, .adv_w = 124, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 15},
    {.bitmap_index = 1364, .adv_w = 210, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1382, .adv_w = 229, .box_w = 11, .box_h = 18, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1407, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1424, .adv_w = 230, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 211, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1467, .adv_w = 133, .box_w = 10, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1490, .adv_w = 206, .box_w = 13, .box_h = 19, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1521, .adv_w = 223, .box_w = 10, .box_h = 18, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1544, .adv_w = 108, .box_w = 3, .box_h = 19, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1552, .adv_w = 108, .box_w = 5, .box_h = 24, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1567, .adv_w = 205, .box_w = 11, .box_h = 18, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1592, .adv_w = 113, .box_w = 5, .box_h = 18, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1604, .adv_w = 326, .box_w = 17, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1632, .adv_w = 223, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1649, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1669, .adv_w = 229, .box_w = 11, .box_h = 18, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 1694, .adv_w = 230, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1719, .adv_w = 151, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 183, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1748, .adv_w = 144, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1766, .adv_w = 222, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1783, .adv_w = 194, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1803, .adv_w = 282, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1831, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1851, .adv_w = 194, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1878, .adv_w = 172, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1895, .adv_w = 124, .box_w = 7, .box_h = 23, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1916, .adv_w = 149, .box_w = 3, .box_h = 22, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 1925, .adv_w = 124, .box_w = 6, .box_h = 23, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1943, .adv_w = 193, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1948, .adv_w = 200, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1956, .adv_w = 199, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1974, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1983, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1994, .adv_w = 225, .box_w = 10, .box_h = 18, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 2017, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2019, .adv_w = 196, .box_w = 9, .box_h = 9, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 2030, .adv_w = 196, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 2049, .adv_w = 227, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2079, .adv_w = 265, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2109, .adv_w = 229, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2129, .adv_w = 232, .box_w = 12, .box_h = 23, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 2164, .adv_w = 190, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2191, .adv_w = 222, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2218, .adv_w = 182, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2235, .adv_w = 218, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2262, .adv_w = 196, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2287, .adv_w = 225, .box_w = 10, .box_h = 18, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 2310, .adv_w = 232, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2333, .adv_w = 229, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2355, .adv_w = 181, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2373, .adv_w = 286, .box_w = 16, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2409, .adv_w = 298, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2435, .adv_w = 200, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 2438, .adv_w = 305, .box_w = 19, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2446, .adv_w = 91, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2450, .adv_w = 91, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2454, .adv_w = 165, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2461, .adv_w = 165, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2468, .adv_w = 129, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2473, .adv_w = 281, .box_w = 16, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2481, .adv_w = 468, .box_w = 27, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2539, .adv_w = 346, .box_w = 16, .box_h = 15, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2569, .adv_w = 346, .box_w = 15, .box_h = 16, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2599, .adv_w = 346, .box_w = 16, .box_h = 15, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2629, .adv_w = 346, .box_w = 15, .box_h = 17, .ofs_x = 3, .ofs_y = -1}
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
    2, 32, 3, 4, 3, 13, 3, 15, 3, 16, 3, 21, 3, 34, 3, 64,
    3, 104, 3, 126, 4, 7, 4, 12, 4, 13, 4, 14, 4, 15, 4, 32,
    4, 61, 4, 64, 4, 66, 4, 95, 4, 101, 4, 103, 4, 119, 4, 120,
    4, 125, 4, 126, 5, 18, 5, 61, 5, 64, 6, 3, 6, 8, 6, 11,
    6, 18, 6, 32, 6, 61, 6, 121, 6, 122, 6, 123, 6, 124, 7, 3,
    7, 6, 7, 8, 7, 11, 7, 16, 7, 18, 7, 21, 7, 22, 7, 24,
    7, 26, 7, 32, 7, 33, 7, 53, 7, 55, 7, 58, 7, 61, 7, 71,
    7, 87, 7, 88, 7, 90, 7, 108, 7, 114, 7, 116, 7, 121, 7, 122,
    7, 123, 7, 124, 7, 125, 7, 127, 8, 4, 8, 13, 8, 15, 8, 16,
    8, 17, 8, 21, 8, 23, 8, 25, 8, 33, 8, 34, 8, 43, 8, 59,
    8, 64, 8, 66, 8, 68, 8, 69, 8, 70, 8, 80, 8, 82, 8, 84,
    8, 91, 8, 104, 8, 106, 8, 109, 8, 110, 8, 112, 8, 115, 8, 117,
    8, 118, 8, 126, 9, 18, 9, 75, 11, 4, 11, 13, 11, 15, 11, 16,
    11, 21, 11, 33, 11, 34, 11, 64, 11, 66, 11, 68, 11, 69, 11, 70,
    11, 80, 11, 82, 11, 104, 11, 106, 11, 109, 11, 115, 11, 117, 11, 118,
    11, 126, 12, 5, 12, 13, 12, 15, 12, 16, 12, 18, 12, 19, 12, 20,
    12, 24, 12, 32, 12, 52, 12, 53, 12, 58, 12, 61, 12, 64, 12, 126,
    13, 3, 13, 6, 13, 7, 13, 8, 13, 11, 13, 12, 13, 14, 13, 17,
    13, 18, 13, 21, 13, 26, 13, 32, 13, 36, 13, 40, 13, 48, 13, 50,
    13, 53, 13, 55, 13, 56, 13, 58, 13, 61, 13, 71, 13, 85, 13, 87,
    13, 88, 13, 90, 13, 95, 13, 98, 13, 99, 13, 101, 13, 103, 13, 108,
    13, 114, 13, 116, 13, 119, 13, 120, 13, 121, 13, 122, 13, 123, 13, 124,
    13, 127, 14, 5, 14, 6, 14, 7, 14, 13, 14, 15, 14, 16, 14, 18,
    14, 19, 14, 20, 14, 24, 14, 32, 14, 52, 14, 53, 14, 55, 14, 57,
    14, 58, 14, 59, 14, 61, 14, 64, 14, 66, 14, 71, 14, 89, 14, 91,
    14, 112, 14, 114, 14, 116, 14, 126, 14, 127, 15, 3, 15, 6, 15, 7,
    15, 8, 15, 11, 15, 12, 15, 14, 15, 17, 15, 18, 15, 21, 15, 26,
    15, 32, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 55, 15, 56,
    15, 58, 15, 61, 15, 71, 15, 85, 15, 87, 15, 88, 15, 90, 15, 95,
    15, 98, 15, 99, 15, 101, 15, 103, 15, 108, 15, 114, 15, 116, 15, 119,
    15, 120, 15, 121, 15, 122, 15, 123, 15, 124, 15, 127, 16, 4, 16, 6,
    16, 7, 16, 12, 16, 13, 16, 14, 16, 15, 16, 16, 16, 17, 16, 18,
    16, 19, 16, 20, 16, 21, 16, 22, 16, 23, 16, 25, 16, 26, 16, 27,
    16, 28, 16, 32, 16, 33, 16, 34, 16, 36, 16, 40, 16, 48, 16, 50,
    16, 57, 16, 59, 16, 64, 16, 66, 16, 68, 16, 69, 16, 70, 16, 71,
    16, 72, 16, 78, 16, 79, 16, 80, 16, 81, 16, 82, 16, 83, 16, 84,
    16, 85, 16, 86, 16, 87, 16, 88, 16, 89, 16, 90, 16, 91, 16, 95,
    16, 100, 16, 101, 16, 103, 16, 104, 16, 105, 16, 106, 16, 108, 16, 109,
    16, 110, 16, 112, 16, 113, 16, 114, 16, 115, 16, 116, 16, 117, 16, 118,
    16, 119, 16, 120, 16, 125, 16, 126, 16, 127, 17, 13, 17, 15, 17, 18,
    17, 24, 17, 32, 17, 53, 17, 58, 17, 64, 17, 126, 18, 18, 19, 58,
    21, 3, 21, 6, 21, 8, 21, 11, 21, 18, 21, 32, 21, 53, 21, 58,
    21, 61, 21, 116, 21, 121, 21, 122, 21, 123, 21, 124, 21, 127, 22, 3,
    22, 5, 22, 6, 22, 8, 22, 11, 22, 16, 22, 18, 22, 19, 22, 20,
    22, 22, 22, 24, 22, 26, 22, 32, 22, 43, 22, 52, 22, 53, 22, 55,
    22, 56, 22, 58, 22, 59, 22, 61, 22, 64, 22, 84, 22, 85, 22, 87,
    22, 88, 22, 89, 22, 90, 22, 91, 22, 96, 22, 98, 22, 99, 22, 108,
    22, 112, 22, 114, 22, 116, 22, 121, 22, 122, 22, 123, 22, 124, 22, 127,
    23, 18, 23, 32, 23, 53, 23, 58, 23, 61, 23, 116, 24, 4, 24, 5,
    24, 7, 24, 12, 24, 13, 24, 14, 24, 15, 24, 16, 24, 21, 24, 23,
    24, 27, 24, 28, 24, 33, 24, 34, 24, 43, 24, 52, 24, 64, 24, 66,
    24, 68, 24, 69, 24, 70, 24, 72, 24, 80, 24, 82, 24, 84, 24, 91,
    24, 95, 24, 101, 24, 103, 24, 104, 24, 105, 24, 106, 24, 109, 24, 110,
    24, 112, 24, 115, 24, 117, 24, 118, 24, 119, 24, 120, 24, 125, 24, 126,
    25, 3, 25, 5, 25, 8, 25, 18, 25, 19, 25, 24, 25, 26, 25, 32,
    25, 43, 25, 52, 25, 53, 25, 55, 25, 57, 25, 58, 25, 61, 25, 64,
    25, 87, 25, 90, 25, 108, 25, 112, 25, 116, 25, 121, 25, 122, 25, 123,
    25, 124, 26, 13, 26, 15, 26, 16, 26, 58, 26, 61, 26, 64, 26, 126,
    27, 18, 27, 24, 27, 32, 27, 53, 27, 58, 27, 61, 28, 18, 28, 24,
    28, 32, 28, 53, 28, 58, 28, 61, 29, 20, 29, 32, 30, 20, 30, 32,
    31, 20, 31, 32, 32, 7, 32, 11, 32, 12, 32, 13, 32, 14, 32, 15,
    32, 16, 32, 64, 32, 87, 32, 90, 32, 95, 32, 98, 32, 99, 32, 101,
    32, 103, 32, 108, 32, 119, 32, 120, 32, 126, 33, 3, 33, 7, 33, 8,
    33, 11, 33, 13, 33, 15, 33, 18, 33, 19, 33, 20, 33, 24, 33, 26,
    33, 27, 33, 28, 33, 32, 33, 53, 33, 55, 33, 56, 33, 57, 33, 58,
    33, 59, 33, 61, 33, 64, 33, 84, 33, 89, 33, 91, 33, 114, 33, 116,
    33, 121, 33, 122, 33, 123, 33, 124, 33, 126, 34, 3, 34, 8, 34, 11,
    34, 18, 34, 32, 34, 53, 34, 58, 34, 61, 34, 116, 34, 121, 34, 122,
    34, 123, 34, 124, 35, 3, 35, 5, 35, 8, 35, 11, 35, 18, 35, 19,
    35, 21, 35, 22, 35, 24, 35, 26, 35, 32, 35, 43, 35, 52, 35, 53,
    35, 55, 35, 57, 35, 58, 35, 59, 35, 61, 35, 64, 35, 116, 35, 121,
    35, 122, 35, 123, 35, 124, 36, 5, 36, 7, 36, 12, 36, 14, 36, 17,
    36, 18, 36, 21, 36, 22, 36, 23, 36, 24, 36, 25, 36, 26, 36, 29,
    36, 30, 36, 31, 36, 33, 36, 36, 36, 40, 36, 43, 36, 48, 36, 50,
    36, 52, 36, 53, 36, 54, 36, 58, 36, 59, 36, 61, 36, 66, 36, 67,
    36, 68, 36, 69, 36, 70, 36, 71, 36, 72, 36, 73, 36, 75, 36, 76,
    36, 77, 36, 78, 36, 79, 36, 80, 36, 81, 36, 82, 36, 83, 36, 84,
    36, 85, 36, 86, 36, 87, 36, 88, 36, 89, 36, 90, 36, 95, 36, 98,
    36, 99, 36, 100, 36, 101, 36, 102, 36, 103, 36, 105, 36, 106, 36, 107,
    36, 108, 36, 109, 36, 110, 36, 111, 36, 112, 36, 113, 36, 114, 36, 115,
    36, 116, 36, 117, 36, 118, 36, 119, 36, 120, 36, 125, 37, 13, 37, 15,
    37, 18, 37, 19, 37, 20, 37, 24, 37, 32, 37, 34, 37, 43, 37, 46,
    37, 53, 37, 55, 37, 57, 37, 58, 37, 59, 37, 61, 37, 64, 37, 66,
    37, 89, 37, 91, 37, 104, 37, 110, 37, 112, 37, 116, 37, 126, 38, 12,
    38, 14, 38, 18, 38, 21, 38, 23, 38, 26, 38, 36, 38, 40, 38, 48,
    38, 50, 38, 61, 38, 68, 38, 69, 38, 70, 38, 71, 38, 72, 38, 80,
    38, 82, 38, 85, 38, 86, 38, 87, 38, 90, 38, 95, 38, 101, 38, 103,
    38, 106, 38, 108, 38, 109, 38, 115, 38, 116, 38, 117, 38, 118, 38, 119,
    38, 120, 39, 4, 39, 5, 39, 7, 39, 13, 39, 15, 39, 16, 39, 18,
    39, 21, 39, 22, 39, 23, 39, 25, 39, 26, 39, 27, 39, 28, 39, 29,
    39, 30, 39, 31, 39, 33, 39, 34, 39, 36, 39, 40, 39, 46, 39, 48,
    39, 50, 39, 52, 39, 59, 39, 64, 39, 66, 39, 68, 39, 69, 39, 70,
    39, 71, 39, 72, 39, 74, 39, 75, 39, 78, 39, 79, 39, 80, 39, 81,
    39, 82, 39, 83, 39, 84, 39, 85, 39, 86, 39, 87, 39, 88, 39, 89,
    39, 90, 39, 91, 39, 100, 39, 102, 39, 104, 39, 105, 39, 106, 39, 108,
    39, 109, 39, 110, 39, 112, 39, 113, 39, 114, 39, 115, 39, 116, 39, 117,
    39, 118, 39, 126, 43, 64, 44, 5, 44, 7, 44, 12, 44, 14, 44, 18,
    44, 21, 44, 23, 44, 25, 44, 26, 44, 29, 44, 30, 44, 31, 44, 32,
    44, 33, 44, 36, 44, 40, 44, 48, 44, 50, 44, 52, 44, 61, 44, 68,
    44, 69, 44, 70, 44, 71, 44, 72, 44, 75, 44, 80, 44, 82, 44, 85,
    44, 86, 44, 87, 44, 90, 44, 95, 44, 98, 44, 99, 44, 101, 44, 102,
    44, 103, 44, 105, 44, 106, 44, 108, 44, 109, 44, 110, 44, 115, 44, 116,
    44, 117, 44, 118, 44, 119, 44, 120, 44, 125, 45, 3, 45, 8, 45, 11,
    45, 12, 45, 14, 45, 17, 45, 18, 45, 21, 45, 23, 45, 24, 45, 26,
    45, 29, 45, 30, 45, 31, 45, 32, 45, 36, 45, 40, 45, 48, 45, 50,
    45, 53, 45, 55, 45, 56, 45, 58, 45, 61, 45, 71, 45, 87, 45, 88,
    45, 90, 45, 95, 45, 98, 45, 99, 45, 101, 45, 102, 45, 103, 45, 105,
    45, 108, 45, 119, 45, 120, 45, 121, 45, 122, 45, 123, 45, 124, 45, 125,
    46, 5, 46, 18, 46, 52, 46, 53, 46, 58, 48, 13, 48, 15, 48, 18,
    48, 19, 48, 20, 48, 24, 48, 32, 48, 34, 48, 43, 48, 46, 48, 53,
    48, 55, 48, 57, 48, 58, 48, 59, 48, 61, 48, 64, 48, 66, 48, 89,
    48, 91, 48, 104, 48, 110, 48, 112, 48, 116, 48, 126, 49, 4, 49, 7,
    49, 13, 49, 15, 49, 16, 49, 21, 49, 32, 49, 33, 49, 34, 49, 43,
    49, 46, 49, 57, 49, 58, 49, 59, 49, 61, 49, 64, 49, 66, 49, 68,
    49, 69, 49, 70, 49, 80, 49, 82, 49, 84, 49, 91, 49, 104, 49, 106,
    49, 109, 49, 110, 49, 112, 49, 115, 49, 117, 49, 118, 49, 126, 50, 13,
    50, 15, 50, 18, 50, 19, 50, 20, 50, 24, 50, 32, 50, 34, 50, 43,
    50, 46, 50, 53, 50, 55, 50, 57, 50, 58, 50, 59, 50, 61, 50, 64,
    50, 66, 50, 89, 50, 91, 50, 104, 50, 110, 50, 112, 50, 116, 50, 126,
    51, 7, 51, 12, 51, 14, 51, 18, 51, 21, 51, 24, 51, 32, 51, 36,
    51, 40, 51, 43, 51, 48, 51, 50, 51, 53, 51, 58, 51, 61, 51, 66,
    51, 68, 51, 69, 51, 70, 51, 72, 51, 80, 51, 82, 51, 95, 51, 101,
    51, 103, 51, 106, 51, 109, 51, 115, 51, 117, 51, 118, 51, 119, 51, 120,
    51, 125, 53, 4, 53, 5, 53, 7, 53, 12, 53, 13, 53, 14, 53, 15,
    53, 16, 53, 17, 53, 18, 53, 21, 53, 22, 53, 23, 53, 25, 53, 26,
    53, 27, 53, 28, 53, 33, 53, 34, 53, 36, 53, 40, 53, 43, 53, 46,
    53, 48, 53, 50, 53, 52, 53, 59, 53, 61, 53, 64, 53, 66, 53, 68,
    53, 69, 53, 70, 53, 71, 53, 72, 53, 75, 53, 78, 53, 79, 53, 80,
    53, 81, 53, 82, 53, 83, 53, 84, 53, 85, 53, 86, 53, 87, 53, 88,
    53, 89, 53, 90, 53, 91, 53, 95, 53, 100, 53, 101, 53, 103, 53, 104,
    53, 105, 53, 106, 53, 108, 53, 109, 53, 110, 53, 112, 53, 113, 53, 115,
    53, 116, 53, 117, 53, 118, 53, 119, 53, 120, 53, 125, 53, 126, 54, 64,
    55, 4, 55, 5, 55, 7, 55, 12, 55, 13, 55, 14, 55, 15, 55, 16,
    55, 18, 55, 21, 55, 22, 55, 23, 55, 25, 55, 26, 55, 27, 55, 28,
    55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 46, 55, 48, 55, 50,
    55, 52, 55, 59, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 71,
    55, 72, 55, 75, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82, 55, 83,
    55, 84, 55, 85, 55, 86, 55, 87, 55, 88, 55, 89, 55, 90, 55, 91,
    55, 95, 55, 100, 55, 101, 55, 103, 55, 104, 55, 105, 55, 106, 55, 108,
    55, 109, 55, 110, 55, 112, 55, 113, 55, 115, 55, 117, 55, 118, 55, 119,
    55, 120, 55, 125, 55, 126, 56, 13, 56, 15, 56, 64, 56, 66, 56, 126,
    57, 5, 57, 7, 57, 12, 57, 14, 57, 17, 57, 18, 57, 21, 57, 23,
    57, 25, 57, 26, 57, 29, 57, 30, 57, 31, 57, 32, 57, 33, 57, 36,
    57, 40, 57, 43, 57, 48, 57, 50, 57, 52, 57, 54, 57, 61, 57, 66,
    57, 68, 57, 69, 57, 70, 57, 71, 57, 72, 57, 75, 57, 80, 57, 82,
    57, 85, 57, 86, 57, 87, 57, 88, 57, 90, 57, 95, 57, 98, 57, 99,
    57, 101, 57, 102, 57, 103, 57, 105, 57, 106, 57, 108, 57, 109, 57, 110,
    57, 115, 57, 116, 57, 117, 57, 118, 57, 119, 57, 120, 57, 125, 58, 4,
    58, 5, 58, 7, 58, 12, 58, 13, 58, 14, 58, 15, 58, 16, 58, 17,
    58, 18, 58, 19, 58, 20, 58, 21, 58, 22, 58, 23, 58, 25, 58, 26,
    58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40, 58, 43, 58, 46,
    58, 48, 58, 50, 58, 52, 58, 59, 58, 64, 58, 66, 58, 68, 58, 69,
    58, 70, 58, 71, 58, 72, 58, 75, 58, 78, 58, 79, 58, 80, 58, 81,
    58, 82, 58, 83, 58, 84, 58, 85, 58, 86, 58, 87, 58, 88, 58, 89,
    58, 90, 58, 91, 58, 95, 58, 100, 58, 101, 58, 103, 58, 104, 58, 105,
    58, 106, 58, 108, 58, 109, 58, 110, 58, 112, 58, 113, 58, 115, 58, 116,
    58, 117, 58, 118, 58, 119, 58, 120, 58, 125, 58, 126, 59, 5, 59, 7,
    59, 12, 59, 14, 59, 18, 59, 21, 59, 22, 59, 23, 59, 25, 59, 26,
    59, 29, 59, 30, 59, 31, 59, 33, 59, 36, 59, 40, 59, 48, 59, 50,
    59, 52, 59, 61, 59, 68, 59, 69, 59, 70, 59, 71, 59, 72, 59, 77,
    59, 80, 59, 82, 59, 85, 59, 86, 59, 87, 59, 89, 59, 90, 59, 91,
    59, 95, 59, 101, 59, 102, 59, 103, 59, 105, 59, 106, 59, 108, 59, 109,
    59, 115, 59, 116, 59, 117, 59, 118, 59, 119, 59, 120, 59, 125, 60, 18,
    60, 75, 61, 3, 61, 6, 61, 7, 61, 8, 61, 11, 61, 12, 61, 14,
    61, 18, 61, 20, 61, 21, 61, 23, 61, 24, 61, 26, 61, 32, 61, 33,
    61, 53, 61, 55, 61, 58, 61, 59, 61, 61, 61, 66, 61, 71, 61, 85,
    61, 95, 61, 96, 61, 98, 61, 99, 61, 101, 61, 103, 61, 116, 61, 119,
    61, 120, 61, 121, 61, 122, 61, 123, 61, 124, 61, 125, 61, 127, 64, 3,
    64, 5, 64, 6, 64, 7, 64, 8, 64, 11, 64, 12, 64, 14, 64, 17,
    64, 18, 64, 21, 64, 23, 64, 25, 64, 32, 64, 33, 64, 36, 64, 40,
    64, 48, 64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56, 64, 58,
    64, 61, 64, 64, 64, 66, 64, 68, 64, 69, 64, 70, 64, 71, 64, 75,
    64, 77, 64, 80, 64, 82, 64, 85, 64, 86, 64, 87, 64, 88, 64, 90,
    64, 95, 64, 98, 64, 99, 64, 101, 64, 103, 64, 106, 64, 108, 64, 109,
    64, 110, 64, 111, 64, 114, 64, 115, 64, 116, 64, 117, 64, 118, 64, 119,
    64, 120, 64, 121, 64, 122, 64, 123, 64, 124, 64, 127, 66, 18, 66, 24,
    66, 32, 66, 61, 67, 18, 67, 24, 67, 32, 67, 61, 68, 7, 68, 12,
    68, 14, 68, 17, 68, 18, 68, 21, 68, 24, 68, 25, 68, 29, 68, 30,
    68, 31, 68, 32, 68, 33, 68, 61, 68, 66, 68, 68, 68, 69, 68, 70,
    68, 72, 68, 80, 68, 82, 68, 86, 68, 95, 68, 101, 68, 102, 68, 103,
    68, 106, 68, 109, 68, 110, 68, 111, 68, 115, 68, 116, 68, 117, 68, 118,
    68, 119, 68, 120, 68, 125, 70, 18, 70, 24, 70, 32, 70, 61, 70, 116,
    71, 2, 71, 3, 71, 6, 71, 8, 71, 10, 71, 11, 71, 13, 71, 15,
    71, 18, 71, 19, 71, 20, 71, 22, 71, 24, 71, 26, 71, 27, 71, 28,
    71, 32, 71, 61, 71, 62, 71, 94, 71, 98, 71, 99, 71, 121, 71, 122,
    71, 123, 71, 124, 71, 126, 71, 127, 72, 32, 72, 61, 72, 66, 72, 68,
    72, 69, 72, 70, 72, 80, 72, 82, 72, 106, 72, 109, 72, 115, 72, 117,
    72, 118, 73, 18, 73, 24, 73, 32, 73, 58, 73, 61, 76, 7, 76, 12,
    76, 14, 76, 21, 76, 29, 76, 30, 76, 31, 76, 32, 76, 61, 76, 66,
    76, 95, 76, 101, 76, 102, 76, 103, 76, 119, 76, 120, 76, 125, 77, 18,
    78, 58, 79, 18, 79, 24, 79, 32, 79, 58, 79, 61, 80, 18, 80, 24,
    80, 32, 80, 61, 80, 116, 81, 18, 81, 24, 81, 32, 81, 61, 82, 75,
    83, 3, 83, 8, 83, 11, 83, 13, 83, 15, 83, 16, 83, 18, 83, 27,
    83, 28, 83, 61, 83, 64, 83, 98, 83, 99, 83, 112, 83, 121, 83, 122,
    83, 123, 83, 124, 83, 126, 85, 12, 85, 14, 85, 32, 85, 61, 85, 95,
    85, 101, 85, 103, 85, 119, 85, 120, 86, 18, 86, 24, 86, 32, 86, 61,
    87, 13, 87, 15, 87, 32, 87, 64, 87, 126, 88, 13, 88, 15, 88, 20,
    88, 32, 88, 61, 88, 64, 88, 66, 88, 126, 89, 12, 89, 14, 89, 32,
    89, 95, 89, 101, 89, 103, 89, 119, 89, 120, 90, 13, 90, 15, 90, 32,
    90, 64, 90, 126, 91, 7, 91, 12, 91, 14, 91, 21, 91, 32, 91, 61,
    91, 66, 91, 95, 91, 101, 91, 103, 91, 110, 91, 119, 91, 120, 92, 75,
    95, 5, 95, 7, 95, 13, 95, 15, 95, 16, 95, 18, 95, 19, 95, 20,
    95, 24, 95, 32, 95, 52, 95, 53, 95, 57, 95, 58, 95, 59, 95, 61,
    95, 64, 95, 89, 95, 91, 95, 112, 95, 126, 96, 2, 96, 3, 96, 8,
    96, 11, 96, 12, 96, 13, 96, 14, 96, 15, 96, 16, 96, 27, 96, 28,
    96, 32, 96, 61, 96, 64, 96, 95, 96, 101, 96, 103, 96, 119, 96, 120,
    96, 121, 96, 122, 96, 123, 96, 124, 96, 126, 98, 13, 98, 15, 98, 16,
    98, 34, 98, 57, 98, 64, 98, 66, 98, 104, 98, 126, 99, 13, 99, 15,
    99, 16, 99, 34, 99, 57, 99, 64, 99, 66, 99, 104, 99, 126, 101, 5,
    101, 6, 101, 7, 101, 13, 101, 15, 101, 16, 101, 18, 101, 19, 101, 20,
    101, 24, 101, 32, 101, 52, 101, 53, 101, 55, 101, 57, 101, 58, 101, 59,
    101, 61, 101, 64, 101, 66, 101, 71, 101, 89, 101, 91, 101, 112, 101, 114,
    101, 116, 101, 126, 101, 127, 102, 20, 102, 32, 103, 5, 103, 13, 103, 15,
    103, 16, 103, 18, 103, 19, 103, 20, 103, 24, 103, 32, 103, 52, 103, 53,
    103, 57, 103, 58, 103, 61, 103, 64, 103, 89, 103, 126, 104, 3, 104, 8,
    104, 11, 104, 18, 104, 32, 104, 53, 104, 58, 104, 62, 104, 94, 104, 116,
    104, 121, 104, 122, 104, 123, 104, 124, 105, 18, 105, 19, 105, 20, 105, 24,
    105, 32, 105, 53, 105, 55, 105, 56, 105, 57, 105, 58, 105, 59, 105, 61,
    105, 116, 106, 61, 107, 3, 107, 8, 107, 11, 107, 18, 107, 19, 107, 24,
    107, 26, 107, 32, 107, 61, 107, 64, 107, 87, 107, 88, 107, 89, 107, 90,
    107, 98, 107, 99, 107, 108, 107, 112, 107, 114, 107, 116, 107, 121, 107, 122,
    107, 123, 107, 124, 108, 13, 108, 15, 108, 32, 108, 61, 108, 64, 108, 66,
    108, 112, 108, 126, 109, 18, 109, 19, 109, 20, 109, 24, 109, 32, 109, 61,
    109, 64, 109, 116, 110, 32, 111, 13, 111, 15, 111, 16, 111, 32, 111, 61,
    111, 64, 111, 112, 111, 116, 111, 126, 112, 2, 112, 3, 112, 8, 112, 11,
    112, 13, 112, 15, 112, 18, 112, 27, 112, 28, 112, 32, 112, 61, 112, 116,
    112, 121, 112, 122, 112, 123, 112, 124, 112, 126, 114, 12, 114, 14, 114, 16,
    114, 19, 114, 22, 114, 32, 114, 33, 114, 61, 114, 68, 114, 69, 114, 70,
    114, 80, 114, 82, 114, 86, 114, 95, 114, 101, 114, 103, 114, 106, 114, 109,
    114, 110, 114, 112, 114, 115, 114, 116, 114, 117, 114, 118, 114, 119, 114, 120,
    115, 11, 115, 61, 115, 64, 115, 98, 115, 99, 116, 2, 116, 3, 116, 8,
    116, 11, 116, 13, 116, 15, 116, 27, 116, 28, 116, 32, 116, 64, 116, 66,
    116, 98, 116, 99, 116, 112, 116, 121, 116, 122, 116, 123, 116, 124, 116, 126,
    117, 18, 117, 19, 117, 20, 117, 24, 117, 32, 117, 61, 117, 64, 117, 116,
    118, 3, 118, 8, 118, 11, 118, 13, 118, 15, 118, 18, 118, 19, 118, 20,
    118, 22, 118, 24, 118, 26, 118, 32, 118, 61, 118, 64, 118, 66, 118, 89,
    118, 91, 118, 112, 118, 114, 118, 116, 118, 121, 118, 122, 118, 123, 118, 124,
    118, 126, 119, 5, 119, 6, 119, 7, 119, 13, 119, 15, 119, 16, 119, 18,
    119, 19, 119, 20, 119, 21, 119, 22, 119, 24, 119, 26, 119, 32, 119, 34,
    119, 43, 119, 52, 119, 53, 119, 55, 119, 57, 119, 58, 119, 59, 119, 61,
    119, 64, 119, 66, 119, 71, 119, 75, 119, 85, 119, 87, 119, 89, 119, 90,
    119, 91, 119, 104, 119, 108, 119, 112, 119, 114, 119, 116, 119, 126, 119, 127,
    120, 5, 120, 7, 120, 13, 120, 15, 120, 16, 120, 18, 120, 19, 120, 20,
    120, 24, 120, 32, 120, 52, 120, 53, 120, 57, 120, 58, 120, 59, 120, 61,
    120, 64, 120, 89, 120, 91, 120, 112, 120, 126, 121, 4, 121, 13, 121, 15,
    121, 16, 121, 17, 121, 21, 121, 23, 121, 25, 121, 33, 121, 34, 121, 43,
    121, 59, 121, 64, 121, 66, 121, 68, 121, 69, 121, 70, 121, 80, 121, 82,
    121, 84, 121, 91, 121, 104, 121, 106, 121, 109, 121, 110, 121, 112, 121, 115,
    121, 117, 121, 118, 121, 126, 122, 4, 122, 13, 122, 15, 122, 16, 122, 17,
    122, 21, 122, 23, 122, 25, 122, 33, 122, 34, 122, 43, 122, 59, 122, 64,
    122, 66, 122, 68, 122, 69, 122, 70, 122, 80, 122, 82, 122, 84, 122, 91,
    122, 104, 122, 106, 122, 109, 122, 110, 122, 112, 122, 115, 122, 117, 122, 118,
    122, 126, 123, 11, 123, 13, 123, 15, 123, 16, 123, 21, 123, 24, 123, 53,
    123, 55, 123, 58, 123, 62, 123, 64, 123, 85, 123, 94, 123, 116, 123, 126,
    124, 11, 124, 13, 124, 15, 124, 16, 124, 21, 124, 24, 124, 53, 124, 55,
    124, 58, 124, 62, 124, 64, 124, 85, 124, 94, 124, 116, 124, 126, 125, 5,
    125, 16, 125, 18, 125, 19, 125, 20, 125, 24, 125, 32, 125, 52, 125, 53,
    125, 58, 125, 59, 125, 61, 126, 3, 126, 6, 126, 7, 126, 8, 126, 11,
    126, 12, 126, 14, 126, 17, 126, 18, 126, 21, 126, 23, 126, 26, 126, 32,
    126, 36, 126, 40, 126, 48, 126, 50, 126, 53, 126, 54, 126, 55, 126, 56,
    126, 58, 126, 61, 126, 68, 126, 69, 126, 70, 126, 71, 126, 72, 126, 80,
    126, 82, 126, 85, 126, 86, 126, 87, 126, 88, 126, 90, 126, 95, 126, 98,
    126, 99, 126, 101, 126, 103, 126, 106, 126, 108, 126, 109, 126, 111, 126, 114,
    126, 115, 126, 116, 126, 117, 126, 118, 126, 119, 126, 120, 126, 121, 126, 122,
    126, 123, 126, 124, 126, 127, 127, 3, 127, 8, 127, 11, 127, 18, 127, 32,
    127, 61, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -8, -12, -38, -38, -38, -15, -12, -38, -12, -38, -9, -8, -15, -8, -15, -8,
    -8, -31, -8, -8, -8, -8, -8, -8, -8, -15, -13, -12, -12, -23, -23, -19,
    -23, -23, -23, -23, -23, -23, -23, -31, -15, -31, -15, -15, -28, -8, -8, -12,
    -8, -31, -8, -30, -17, -28, -38, -8, -8, -8, -8, -8, -8, -19, -31, -31,
    -31, -31, -8, -15, -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4,
    -38, -6, -4, -4, -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4,
    -4, -38, -8, 20, -8, -38, -38, -31, -12, -12, -12, -38, -8, -4, -4, -4,
    -4, -4, -12, -4, -4, -4, -4, -4, -38, -15, -19, -19, -23, -27, -21, -23,
    -23, -23, -15, -19, -22, -23, -31, -19, -38, -38, -5, -38, -38, -19, -19, -5,
    -38, -10, -9, -19, -8, -8, -8, -8, -23, -19, -12, -36, -54, -6, -12, -15,
    -8, -15, -19, -19, -19, -19, -19, -15, -12, -31, -19, -19, -38, -38, -38, -38,
    -38, -15, -8, -12, -19, -19, -23, -27, -21, -23, -23, -23, -15, -19, -9, -14,
    -22, -12, -23, -31, -6, -6, -13, -12, -12, -5, -8, -19, -8, -38, -38, -5,
    -38, -38, -19, -19, -5, -38, -10, -9, -19, -8, -8, -8, -8, -23, -19, -12,
    -36, -54, -6, -12, -15, -8, -15, -19, -19, -19, -19, -19, -15, -12, -31, -19,
    -19, -38, -38, -38, -38, -38, -8, -8, -19, -23, -54, -23, -54, -46, -4, -23,
    -15, -12, -19, -8, -12, -10, -15, -19, -19, -23, -19, -10, -8, -8, -8, -8,
    -8, -8, -46, -19, -19, -19, -19, -12, -12, -12, -12, -19, -12, -19, -12, -12,
    -12, -12, -8, -8, -12, -8, -12, -23, -12, -23, -23, -10, -8, -19, -8, -19,
    -19, -15, -12, -15, -19, -23, -19, -19, -23, -23, -12, -54, -8, -5, -5, -9,
    -8, -8, -12, -8, -12, -5, -6, -12, -19, -15, -19, -15, -25, -19, -19, -23,
    -19, -12, -19, -19, -19, -19, -15, -12, -6, -8, -12, -8, -8, -21, -5, -3,
    -2, -10, -6, -8, -2, -6, -15, -12, -8, -15, -6, -12, -8, -4, -3, -4,
    -1, -4, -4, -3, -4, -4, -4, -4, -6, -4, -10, -12, -12, -12, -12, -8,
    -20, -12, -19, -17, -12, -12, -8, -8, -8, -13, -33, -13, -33, -15, -15, -8,
    -10, -10, -8, -12, -8, -8, -38, -12, -12, -12, -12, -10, -12, -12, -10, -8,
    -13, -13, -13, -12, -8, -12, -12, -8, -12, -12, -12, -12, -13, -13, -9, -33,
    -6, -4, -6, -12, -4, -6, -6, -8, -4, -4, -8, -4, -4, -15, -10, -8,
    -3, -3, -3, -4, -8, -6, -6, -6, -6, -20, -20, -15, -14, -15, -38, -20,
    -14, -10, -13, -15, -22, -19, -14, -10, -13, -15, -22, -19, -13, -15, -13, -15,
    -13, -15, -15, 5, -18, -38, -18, -38, -31, -38, 5, 5, -18, 5, 5, -18,
    -18, 5, -18, -18, -38, -8, -8, -8, -12, -12, -12, -12, -8, -8, -12, -4,
    -6, -6, -15, -19, -6, -4, -12, -17, -8, -19, -19, -4, -4, -4, -2, -8,
    -8, -8, -8, -8, -12, -12, -12, -12, -19, -12, -19, -20, -10, -12, -12, -12,
    -12, -12, -4, -8, -4, -4, -15, -6, -4, -4, -12, -8, -8, -7, -8, -8,
    -6, -6, -10, -6, -8, -8, -4, -4, -4, -4, -4, -4, -6, -31, -31, -8,
    -22, -18, -4, -12, -4, -8, -12, -20, -20, -20, -8, -8, -8, -5, -8, -8,
    -4, -4, -4, -7, -4, -8, -4, -4, -8, -8, -8, -8, -12, -4, -6, -4,
    -4, -5, -5, -8, -5, -8, -5, -4, -12, -6, -19, -12, -6, -19, -31, -4,
    -4, -5, -31, -20, -31, -6, -8, -4, -19, -8, -6, -10, -4, -5, -12, -8,
    -38, -8, -8, -31, -31, -23, -8, -8, -5, -10, -8, -8, -8, -4, -5, -3,
    -13, -2, -6, -13, -10, -8, -15, -4, -4, -4, -4, -4, -5, -4, -8, -8,
    -8, -10, -10, -6, -6, -5, -5, -5, -5, -12, -8, -8, -8, -8, -8, -8,
    -8, -6, -6, -8, -8, -8, -8, -8, -8, -8, -8, -8, -15, -8, -8, -8,
    -8, -12, -8, -12, -31, -31, -19, -12, -15, -8, -6, -10, -8, -8, -8, -7,
    -7, -7, -8, -19, -7, -7, -9, -7, -7, -8, -8, -38, -23, -13, -13, -13,
    -15, -17, -12, -12, -13, -13, -13, -13, -13, -13, -17, -6, -14, -13, -10, -23,
    -13, -19, -13, -7, -19, -12, -13, -13, -13, -13, -19, -13, -12, -13, -15, -13,
    -13, -31, -8, -4, -4, -14, -14, -17, -12, -8, -4, -4, -12, -12, -12, -12,
    -12, -6, -6, -6, -6, -4, -8, -6, -6, -6, -6, -6, -4, -6, -6, -4,
    -4, -5, -5, -14, -4, -4, -14, -12, -14, -4, -6, -5, -6, -6, -6, -24,
    -6, -6, -14, -14, -10, -38, -38, -31, -38, -38, -12, -46, -13, -12, -15, -23,
    -12, -12, -12, -31, -17, -17, -17, -17, -34, -33, -15, -35, -43, -13, -28, -18,
    -28, -38, -38, -38, -38, -12, -38, -13, -28, -38, -38, -38, -38, -38, -38, -31,
    -6, -6, -6, -6, -7, -8, -8, -5, -10, -8, -8, -8, -4, -5, -3, -13,
    -2, -6, -13, -10, -8, -15, -4, -4, -4, -4, -4, -5, -4, -8, -12, -17,
    -46, -46, -19, -17, -15, -12, -23, -13, -12, -13, -15, -14, -19, -38, -20, -12,
    -12, -12, -12, -12, -12, -12, -23, -12, -12, -13, -22, -12, -12, -12, -46, -8,
    -8, -5, -10, -8, -8, -8, -4, -5, -3, -13, -2, -6, -13, -10, -8, -15,
    -4, -4, -4, -4, -4, -5, -4, -8, -4, -10, -10, -6, -8, -6, -8, -4,
    -4, -4, -4, -4, -8, -11, -8, -4, -6, -6, -6, -4, -6, -6, -10, -10,
    -10, -6, -6, -6, -6, -6, -10, -10, -8, -19, -8, -15, -19, -23, -19, -23,
    -19, -12, -8, -19, -8, -15, -8, -8, -15, -15, -19, -19, -13, -13, -6, -8,
    -13, -13, -8, -8, -12, -19, -19, -21, -21, -21, -15, -19, -12, -12, -12, -21,
    -12, -21, -12, -19, -15, -15, -15, -12, -14, -15, -15, -19, -12, -19, -19, -19,
    -10, -21, -15, -21, -19, -17, -12, -21, -19, -21, -21, -19, -19, -19, -23, -12,
    -4, -6, -8, -9, -19, -9, -19, -10, -8, -8, -4, -2, -4, -2, -4, -4,
    -6, -6, -2, -2, -2, -3, -2, -2, -6, -8, -19, -15, -10, -10, -10, -4,
    -12, -2, -4, -4, -10, -4, -10, -4, -8, -4, -8, -3, -2, -7, -3, -8,
    -9, -4, -9, -9, -6, -2, -10, -3, -10, -6, -10, -4, -10, -10, -10, -9,
    -9, -4, -19, -12, -12, -23, -12, -12, -4, -4, -14, -14, -2, -17, -12, -8,
    -4, -4, -12, -12, -12, -12, -12, -6, -6, -2, -6, -6, -4, -3, -8, -3,
    -6, -6, -6, -6, -6, -4, -6, -6, -4, -4, -5, -2, -5, -14, -4, -4,
    -14, -12, -14, -4, -6, -5, -6, -6, -6, -24, -6, -6, -14, -14, -10, -19,
    -8, -19, -22, -36, -22, -36, -23, -8, -13, -8, -8, -19, -8, -19, -13, -15,
    -22, -22, -17, -20, -13, -13, -5, -7, -13, -13, -8, -6, -31, -32, -24, -24,
    -24, -13, -19, -8, -20, -20, -24, -20, -24, -20, -22, -10, -20, -19, -12, -20,
    -19, -22, -22, -20, -22, -22, -20, -8, -24, -19, -24, -24, -12, -20, -24, -19,
    -24, -24, -22, -22, -17, -36, -6, -8, -20, -20, -8, -12, -6, -10, -6, -7,
    -10, -10, -10, -8, -10, -10, -10, -10, -6, -15, -8, -8, -8, -8, -10, -6,
    -8, -8, -8, -7, -6, -8, -6, -6, -20, -20, -10, -20, -8, -8, -6, -8,
    -8, -19, -8, -8, -20, -20, -15, -13, 17, -38, -23, -23, -38, -31, -23, -23,
    -20, -12, -8, -8, -15, -15, -31, -12, -19, -10, -23, -8, -46, -8, -12, -8,
    -23, -33, -27, -27, -23, -23, -19, -23, -23, -38, -38, -38, -38, -12, -23, -38,
    -8, -31, -12, -38, -38, -31, -31, -12, -38, -46, -12, -8, -31, -12, -15, -15,
    -15, -15, -8, -19, -12, -19, -23, -31, -46, -4, -8, -8, -8, -8, -8, 20,
    -4, -8, -8, -8, -8, -12, -8, -12, -31, -31, -31, -31, -31, -8, -12, -8,
    -8, -12, -12, -8, -31, -8, -8, -31, -31, -38, -38, -38, -38, -31, -19, -12,
    -12, -15, -19, -15, -15, -19, -6, -15, -15, -4, -4, -12, -12, -4, -7, -7,
    -7, -13, -8, -12, -4, -8, -8, -8, -4, -8, -8, -4, -15, -15, -7, -15,
    -8, -8, -6, -4, -8, -2, -8, -8, -15, -15, -10, -19, -15, -15, -19, -13,
    21, 27, 8, 27, 31, 19, -19, -19, 8, 8, 10, 8, 23, 8, 3, 3,
    19, 5, 20, 20, 12, 12, 27, 27, 27, 27, -19, 8, -8, -8, -8, -7,
    -7, -7, -7, -7, -7, -7, -7, -7, -7, -12, -8, -12, -15, -13, -8, -13,
    -13, -6, -6, -6, -6, -10, -8, -6, -13, -13, -6, -13, -13, -13, -7, -10,
    -15, -12, -8, -12, -15, -13, -19, -15, -15, -19, -13, -19, -15, -15, -19, 5,
    2, 2, 9, -31, -31, -23, 4, 4, 4, -19, -31, 8, 8, -19, 2, 2,
    2, 2, -31, -15, -15, -12, -15, -15, -15, -15, -15, -15, -8, -8, -8, -9,
    -15, -15, -12, -12, -15, -8, -8, -4, -8, -8, -8, -5, -8, -13, -13, -10,
    -13, -13, -13, -13, -13, -15, -15, -12, -12, -15, -8, -13, -13, -9, -12, -12,
    -6, -13, -13, -13, -5, -13, -13, 15, -15, -12, -19, -19, -23, -27, -21, -23,
    -23, -23, -15, -19, -14, -22, -12, -23, -31, -13, -12, -12, -19, -26, -31, -31,
    -26, -35, -77, -35, -77, -64, -41, -41, -38, -33, -38, -35, -35, -35, -35, -35,
    -31, -31, -31, -31, -77, -19, -19, -23, -6, -4, -31, -9, -6, -19, -19, -19,
    -23, -6, -4, -31, -9, -6, -19, -15, -8, -12, -19, -19, -23, -27, -21, -23,
    -23, -23, -15, -19, -9, -14, -22, -12, -23, -31, -6, -6, -13, -12, -12, -5,
    -8, -19, -8, -13, -15, -15, -19, -19, -23, -27, -21, -23, -23, -23, -15, -19,
    -14, -22, -23, -31, -13, -19, -12, -12, -12, -19, -12, -19, -20, 5, 5, -12,
    -12, -12, -12, -12, -6, -6, -6, -8, -8, -10, -2, -2, -4, -8, -4, -8,
    -6, -17, -8, -8, -8, -14, -4, -6, -4, -12, -12, -12, -4, -1, -2, -4,
    -4, -4, -4, -4, -2, -15, -8, -8, -8, -8, -15, -15, -12, -8, -12, -7,
    -9, -15, -19, -8, -8, -15, -15, -19, -8, -13, -15, -4, -4, -4, -4, -4,
    -12, -5, -4, -4, 5, -23, -23, -15, 8, 8, -23, 8, 8, -17, -23, -17,
    -23, -23, -23, -23, 8, -5, -5, -8, -4, -4, -8, -2, -12, -4, -4, -4,
    -4, -4, -2, -5, -5, -5, -4, -4, -4, -6, -4, -4, -4, -4, -5, -5,
    7, -19, -19, 5, 5, 8, 4, 4, 6, -23, -23, 4, 4, -15, -23, -15,
    5, 5, -15, 4, 4, 4, 4, -23, -19, -8, -8, -15, -15, -19, -8, -13,
    -4, -4, -4, -4, -4, -19, -8, -8, -4, -15, -4, -15, -19, -8, -4, -4,
    -3, -6, -6, -13, -4, -4, -4, -4, -4, -15, -8, -12, -19, -19, -23, -27,
    -21, -23, -4, -4, -23, -4, -23, -4, -4, -15, -19, -9, -14, -22, -12, -23,
    -31, -6, -6, -4, -2, -4, -13, -4, -12, -4, -4, -12, -5, -8, -19, -8,
    -15, -12, -19, -19, -23, -27, -21, -23, -23, -23, -15, -19, -14, -22, -12, -23,
    -31, -13, -12, -12, -19, -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8,
    -4, -38, -6, -4, -4, -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4,
    -4, -4, -38, -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4, -38,
    -6, -4, -4, -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4, -4,
    -38, 4, -38, -38, -38, -15, 5, 4, 4, 4, 4, -38, 4, 4, 4, -38,
    4, -38, -38, -38, -15, 5, 4, 4, 4, 4, -38, 4, 4, 4, -38, -10,
    -12, -20, -18, -19, -23, -15, -10, -19, -17, -15, -12, -38, -38, -5, -38, -38,
    -19, -19, -5, -38, -10, -4, -9, -19, -8, -8, -8, -8, -23, -4, -19, -12,
    -36, -54, -4, -4, -4, -6, -4, -4, -4, -12, -4, -15, -8, -15, -19, -19,
    -19, -19, -19, -4, -15, -4, -4, -12, -4, -31, -4, -4, -19, -19, -38, -38,
    -38, -38, -38, -31, -31, -19, -36, -23, -23, -31, -31, -31, -31,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 2125,
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

const lv_font_t humid1_font_fira_sans_normal_24 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 30,
    .base_line = 7,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 17,
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

#endif /* #if HUMID1_FONT_FIRA_SANS_NORMAL_24 */
