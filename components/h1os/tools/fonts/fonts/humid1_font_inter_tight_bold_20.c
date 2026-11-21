/*******************************************************************************
 * Font: humid1_font_inter_tight_bold_20 (inter_tight bold)
 * Size: 20 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_20 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_INTER_TIGHT_BOLD_20
#define HUMID1_FONT_INTER_TIGHT_BOLD_20 1
#endif

#if HUMID1_FONT_INTER_TIGHT_BOLD_20

extern const lv_font_t humid1_icon_fa7_solid_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x15) */
    0x7f, 0x77, 0x77, 0x77, 0x77, 0x00, 0x7f, 0x70,
    /* U+0022 "" (8x7) */
    0xe7, 0xef, 0xe7, 0xe7, 0xe7, 0xe7, 0xe6,
    /* U+0023 "#" (13x15) */
    0x0c, 0x60, 0xe3, 0x07, 0x38, 0x39, 0xc7, 0xff, 0xbf, 0xf8, 0xf7, 0x87,
    0x18, 0x39, 0xc7, 0xff, 0xbf, 0xfc, 0xf7, 0x83, 0x18, 0x38, 0xc1, 0xce,
    0x00,
    /* U+0024 "$" (12x18) */
    0x02, 0x00, 0xf8, 0x3f, 0xe7, 0xff, 0x7a, 0xf7, 0xa7, 0x7a, 0x07, 0xf0,
    0x3f, 0xe0, 0xff, 0x03, 0xf7, 0x2f, 0xf2, 0xf7, 0xff, 0x3f, 0xe1, 0xfc,
    0x02, 0x00, 0x20,
    /* U+0025 "%" (15x16) */
    0x3c, 0x08, 0xfc, 0x33, 0x98, 0xc7, 0x33, 0x0e, 0x66, 0x0f, 0xd8, 0x0f,
    0x60, 0x00, 0xc0, 0x03, 0x38, 0x0c, 0xf8, 0x1b, 0xb8, 0x66, 0x71, 0x8c,
    0xe3, 0x1d, 0x8c, 0x1f, 0x00, 0x08,
    /* U+0026 "&" (13x15) */
    0x0e, 0x00, 0xfc, 0x0f, 0xf0, 0x73, 0x83, 0x9c, 0x1d, 0xc0, 0xfe, 0x03,
    0xc0, 0x3f, 0x3b, 0xff, 0xfc, 0xfd, 0xe3, 0xe7, 0xbf, 0x3f, 0xf8, 0xfd,
    0xe0,
    /* U+0027 "'" (3x7) */
    0xff, 0xff, 0xf8,
    /* U+0028 "(" (6x18) */
    0x3c, 0xe7, 0x9e, 0x73, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf1, 0xc7, 0x9e,
    0x38, 0x70,
    /* U+0029 ")" (5x18) */
    0xe7, 0xbc, 0xe7, 0x3d, 0xef, 0x7b, 0xde, 0xf7, 0xbb, 0xde, 0xe7, 0x00,
    /* U+002A "" (7x9) */
    0x10, 0x33, 0x7f, 0xf7, 0xdf, 0xf7, 0x8c, 0x10,
    /* U+002B "+" (11x10) */
    0x0e, 0x01, 0xc0, 0x38, 0x07, 0x0f, 0xff, 0xff, 0xdf, 0xf0, 0x70, 0x0e,
    0x01, 0xc0,
    /* U+002C "," (4x7) */
    0x7f, 0xfe, 0xee, 0xc0,
    /* U+002D "-" (7x2) */
    0xff, 0xfc,
    /* U+002E "." (4x3) */
    0x7f, 0x70,
    /* U+002F "/" (7x17) */
    0x0e, 0x1c, 0x38, 0x71, 0xc3, 0x87, 0x0e, 0x38, 0x70, 0xe3, 0xc7, 0x0e,
    0x1c, 0x70, 0xe0,
    /* U+0030 "0" (12x15) */
    0x0f, 0x03, 0xfc, 0x7f, 0xef, 0x9e, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x1f, 0x7f, 0xe3, 0xfc, 0x1f, 0x80,
    /* U+0031 "1" (8x15) */
    0x0e, 0x3f, 0x7f, 0xff, 0xef, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
    0x0f, 0x0f, 0x0f,
    /* U+0032 "2" (12x15) */
    0x0f, 0x03, 0xfc, 0x7f, 0xe7, 0x9e, 0xf0, 0xf0, 0x0e, 0x01, 0xe0, 0x3c,
    0x07, 0xc0, 0xf8, 0x1e, 0x03, 0xe0, 0x7f, 0xf7, 0xff, 0x7f, 0xf0,
    /* U+0033 "3" (11x15) */
    0x1e, 0x0f, 0xf3, 0xff, 0x78, 0xfe, 0x1e, 0x03, 0xc3, 0xf0, 0x7c, 0x0f,
    0xc0, 0x3c, 0x07, 0xf8, 0xff, 0xfe, 0xff, 0x8f, 0xe0,
    /* U+0034 "4" (12x15) */
    0x03, 0xc0, 0x7c, 0x0f, 0xc0, 0xfc, 0x1f, 0xc3, 0xdc, 0x39, 0xc7, 0x9c,
    0xf1, 0xcf, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1c, 0x01, 0xc0,
    /* U+0035 "5" (11x15) */
    0x7f, 0xcf, 0xf9, 0xff, 0x78, 0x0f, 0x01, 0xee, 0x3f, 0xf7, 0xff, 0x71,
    0xe0, 0x3c, 0x03, 0xf8, 0xff, 0xbe, 0xff, 0x8f, 0xe0,
    /* U+0036 "6" (12x15) */
    0x0f, 0x03, 0xfc, 0x7f, 0xe7, 0x9e, 0xf0, 0xef, 0x30, 0xef, 0xcf, 0xfe,
    0xf1, 0xef, 0x0e, 0xf0, 0xff, 0x0e, 0x7b, 0xe7, 0xfc, 0x1f, 0x80,
    /* U+0037 "7" (11x15) */
    0x7f, 0xff, 0xff, 0xff, 0x80, 0xf0, 0x1c, 0x07, 0x80, 0xe0, 0x3c, 0x07,
    0x01, 0xe0, 0x38, 0x0f, 0x01, 0xc0, 0x78, 0x0e, 0x00,
    /* U+0038 "8" (12x15) */
    0x0f, 0x03, 0xfc, 0x7f, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0x7f, 0xc3, 0xf8,
    0x7f, 0xcf, 0x1e, 0xf0, 0xff, 0x0f, 0xf9, 0xe7, 0xfc, 0x3f, 0x80,
    /* U+0039 "9" (11x15) */
    0x1e, 0x0f, 0xf1, 0xff, 0x78, 0xfe, 0x1f, 0xc1, 0xfc, 0x7f, 0xdf, 0x7f,
    0xe7, 0x9c, 0x03, 0xf8, 0xff, 0xfc, 0xff, 0x0f, 0xc0,
    /* U+003A ":" (4x10) */
    0x7f, 0x70, 0x00, 0x07, 0xf7,
    /* U+003B ";" (4x14) */
    0x77, 0x70, 0x00, 0x07, 0x7f, 0xee, 0xec,
    /* U+003C "<" (11x11) */
    0x00, 0xe0, 0x7c, 0x7f, 0xbf, 0x8f, 0xc1, 0xf0, 0x1f, 0xc0, 0xfe, 0x07,
    0xe0, 0x3c, 0x00, 0x80,
    /* U+003D "=" (11x8) */
    0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    /* U+003E ">" (11x10) */
    0xe0, 0x1f, 0x01, 0xfc, 0x0f, 0xe0, 0x3e, 0x07, 0xc3, 0xfb, 0xfc, 0xfc,
    0x1e, 0x00,
    /* U+003F "?" (10x15) */
    0x3e, 0x1f, 0xcf, 0xfb, 0x8f, 0xe3, 0xc1, 0xe0, 0xf8, 0x7c, 0x1c, 0x07,
    0x01, 0x80, 0x00, 0x3c, 0x0f, 0x01, 0xc0,
    /* U+0040 "@" (19x19) */
    0x00, 0xe0, 0x00, 0xff, 0xc0, 0x7f, 0xfc, 0x1e, 0x03, 0xc7, 0x80, 0x1c,
    0xe7, 0xfb, 0xb9, 0xff, 0x3f, 0x38, 0xe7, 0xee, 0x1c, 0xfd, 0xc1, 0x9f,
    0xb8, 0x33, 0xf7, 0x0e, 0x7e, 0x73, 0xef, 0xcf, 0xff, 0x9c, 0xfb, 0xe3,
    0xc0, 0x00, 0x3e, 0x0c, 0x03, 0xff, 0x80, 0x1f, 0xf0, 0x00,
    /* U+0041 "A" (15x15) */
    0x07, 0xc0, 0x0f, 0x80, 0x3f, 0x80, 0x7f, 0x00, 0xfe, 0x03, 0xde, 0x07,
    0xbc, 0x0e, 0x38, 0x3c, 0x78, 0x7f, 0xf0, 0xff, 0xe3, 0xff, 0xe7, 0x83,
    0xcf, 0x07, 0xbc, 0x07, 0x80,
    /* U+0042 "B" (12x15) */
    0xfe, 0x0f, 0xfc, 0xff, 0xef, 0x3e, 0xf1, 0xef, 0x1e, 0xff, 0xcf, 0xf8,
    0xff, 0xef, 0x1e, 0xf0, 0xff, 0x1f, 0xff, 0xef, 0xfe, 0xff, 0x80,
    /* U+0043 "C" (13x15) */
    0x07, 0x81, 0xff, 0x1f, 0xfc, 0xf1, 0xff, 0x07, 0xf8, 0x1f, 0xc0, 0x1c,
    0x00, 0xe0, 0x07, 0x80, 0x3c, 0x1f, 0xf0, 0xf7, 0xff, 0x1f, 0xf0, 0x7f,
    0x00,
    /* U+0044 "D" (12x15) */
    0xfc, 0x0f, 0xf8, 0xff, 0xef, 0x3e, 0xe0, 0xfe, 0x0f, 0xe0, 0x7e, 0x07,
    0xe0, 0x7e, 0x07, 0xe0, 0xfe, 0x1f, 0xff, 0xef, 0xfc, 0xff, 0x00,
    /* U+0045 "E" (10x15) */
    0xff, 0xff, 0xff, 0xff, 0xc0, 0xf0, 0x3c, 0x0f, 0xfb, 0xff, 0xff, 0xfc,
    0x0f, 0x03, 0xc0, 0xff, 0xff, 0xff, 0xfc,
    /* U+0046 "F" (10x15) */
    0xff, 0xff, 0xff, 0xff, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xfe, 0xff, 0xbf,
    0xef, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x00,
    /* U+0047 "G" (13x15) */
    0x07, 0x80, 0xff, 0x1f, 0xfc, 0xf1, 0xff, 0x07, 0xf8, 0x03, 0xc0, 0x1c,
    0x3f, 0xe1, 0xff, 0x8f, 0xfc, 0x1f, 0xf0, 0xf7, 0xff, 0x1f, 0xf0, 0x7f,
    0x00,
    /* U+0048 "H" (13x15) */
    0xe0, 0x77, 0x83, 0xfc, 0x1f, 0xe0, 0xff, 0x07, 0xf8, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x83, 0xfc, 0x1f, 0xe0, 0xff, 0x07, 0xf8, 0x3f, 0xc1,
    0xe0,
    /* U+0049 "I" (4x15) */
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+004A "J" (10x15) */
    0x01, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xc0,
    0x70, 0x1f, 0xc7, 0xff, 0xdf, 0xe3, 0xf0,
    /* U+004B "K" (12x15) */
    0xe0, 0xfe, 0x1f, 0xe1, 0xee, 0x3c, 0xe7, 0x8e, 0x78, 0xff, 0x0f, 0xf0,
    0xff, 0x8f, 0xf8, 0xf3, 0xce, 0x3c, 0xe1, 0xee, 0x1f, 0xe0, 0xf0,
    /* U+004C "L" (10x15) */
    0xe0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c,
    0x0f, 0x03, 0xc0, 0xff, 0xbf, 0xff, 0xfc,
    /* U+004D "M" (16x15) */
    0xf0, 0x0f, 0xf8, 0x1f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x3f,
    0xfe, 0x7f, 0xee, 0x77, 0xee, 0x77, 0xe7, 0xe7, 0xe7, 0xe7, 0xe3, 0xc7,
    0xe3, 0xc7, 0xe3, 0xc7, 0xe1, 0x87,
    /* U+004E "N" (12x15) */
    0xe0, 0x7f, 0x07, 0xf0, 0x7f, 0x87, 0xf8, 0x7f, 0xc7, 0xfe, 0x7e, 0xe7,
    0xe7, 0xfe, 0x3f, 0xe3, 0xfe, 0x1f, 0xe0, 0xfe, 0x0f, 0xe0, 0x70,
    /* U+004F "O" (14x15) */
    0x07, 0x80, 0xff, 0x87, 0xff, 0x1e, 0x3e, 0xf0, 0x7b, 0xc0, 0xef, 0x03,
    0xf8, 0x0f, 0xe0, 0x3f, 0xc0, 0xff, 0x07, 0xbe, 0x1e, 0x7f, 0xf0, 0xff,
    0x81, 0xfc, 0x00,
    /* U+0050 "P" (11x15) */
    0xfe, 0x1f, 0xf3, 0xff, 0x79, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x9f, 0xff,
    0xdf, 0xf3, 0xc0, 0x78, 0x0f, 0x01, 0xe0, 0x3c, 0x00,
    /* U+0051 "Q" (14x16) */
    0x07, 0x80, 0xff, 0x87, 0xff, 0x1e, 0x3e, 0xf0, 0x7b, 0xc0, 0xef, 0x03,
    0xf8, 0x0f, 0xe0, 0x3f, 0xc0, 0xff, 0x3f, 0xbe, 0x7e, 0x7f, 0xf0, 0xff,
    0xc1, 0xff, 0x00, 0x0e,
    /* U+0052 "R" (11x15) */
    0xfe, 0x1f, 0xf3, 0xff, 0x79, 0xfe, 0x1f, 0xc3, 0xf8, 0x7f, 0xff, 0xff,
    0xdf, 0xf3, 0x9e, 0x71, 0xee, 0x3d, 0xc3, 0xf8, 0x78,
    /* U+0053 "S" (12x15) */
    0x0f, 0x83, 0xfe, 0x7f, 0xf7, 0x8f, 0x78, 0x77, 0x80, 0x7f, 0x03, 0xfe,
    0x0f, 0xf0, 0x1f, 0x70, 0xff, 0x0f, 0x7f, 0xf3, 0xfe, 0x1f, 0xc0,
    /* U+0054 "T" (13x15) */
    0x7f, 0xf7, 0xff, 0xff, 0xfe, 0x0f, 0x00, 0x70, 0x03, 0x80, 0x1c, 0x00,
    0xe0, 0x07, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x80, 0x1c,
    0x00,
    /* U+0055 "U" (12x15) */
    0xe0, 0x7f, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xff, 0xf7, 0xfe, 0x3f, 0xc0,
    /* U+0056 "V" (14x15) */
    0xe0, 0x3b, 0xc1, 0xff, 0x07, 0xbc, 0x1e, 0x78, 0x79, 0xe3, 0xc7, 0x8f,
    0x0e, 0x3c, 0x3d, 0xe0, 0xf7, 0x81, 0xde, 0x07, 0xf0, 0x1f, 0xc0, 0x3f,
    0x00, 0xf8, 0x00,
    /* U+0057 "W" (21x15) */
    0x70, 0x70, 0x77, 0x83, 0x83, 0xde, 0x3e, 0x3c, 0xf1, 0xf1, 0xe7, 0x8f,
    0x8f, 0x1c, 0x7c, 0x70, 0xe7, 0xf7, 0x87, 0xbb, 0xbc, 0x3d, 0xdd, 0xe0,
    0xfc, 0x7e, 0x07, 0xe3, 0xf0, 0x3f, 0x1f, 0x80, 0xf8, 0xf8, 0x07, 0x83,
    0xc0, 0x3c, 0x1e, 0x00,
    /* U+0058 "X" (13x15) */
    0xe0, 0x77, 0x87, 0x9e, 0x3c, 0xf3, 0xc3, 0xde, 0x1f, 0xe0, 0x7e, 0x01,
    0xf0, 0x1f, 0x80, 0xfe, 0x0f, 0xf0, 0xf3, 0xc7, 0x9f, 0x78, 0x7b, 0xc1,
    0xe0,
    /* U+0059 "Y" (14x15) */
    0xf0, 0x3d, 0xe0, 0xf7, 0x87, 0x8f, 0x1e, 0x3c, 0xf0, 0x7b, 0xc1, 0xfe,
    0x03, 0xf8, 0x0f, 0xc0, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e,
    0x00, 0x78, 0x00,
    /* U+005A "Z" (11x15) */
    0xff, 0xff, 0xff, 0xff, 0x81, 0xf0, 0x3c, 0x0f, 0x03, 0xe0, 0x78, 0x1e,
    0x07, 0x80, 0xf0, 0x3c, 0x0f, 0xff, 0xff, 0xff, 0xf8,
    /* U+005B "[" (6x18) */
    0xff, 0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3e,
    0xff, 0xe0,
    /* U+005C "" (8x17) */
    0xe0, 0xe0, 0x70, 0x70, 0x70, 0x78, 0x38, 0x38, 0x38, 0x3c, 0x1c, 0x1c,
    0x1c, 0x0e, 0x0e, 0x0e, 0x0f,
    /* U+005D "]" (5x18) */
    0xff, 0xde, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xf7, 0xbd, 0xff, 0xff, 0xc0,
    /* U+005E "^" (8x6) */
    0x38, 0x3c, 0x6c, 0x6e, 0xe6, 0xc7,
    /* U+005F "_" (10x3) */
    0xff, 0xff, 0xff, 0xf8,
    /* U+0060 "`" (4x3) */
    0xee, 0x70,
    /* U+0061 "a" (11x11) */
    0x1f, 0x8f, 0xf9, 0xef, 0x08, 0xf0, 0xfe, 0xff, 0xdf, 0x7f, 0x8f, 0xf3,
    0xef, 0xfd, 0xf7, 0x80,
    /* U+0062 "b" (11x15) */
    0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e, 0x79, 0xff, 0xbf, 0xf7, 0x8f, 0xe1,
    0xfc, 0x3f, 0x87, 0xf8, 0xff, 0xbd, 0xff, 0xb9, 0xe0,
    /* U+0063 "c" (11x11) */
    0x1f, 0x87, 0xf9, 0xff, 0xbc, 0xff, 0x01, 0xe0, 0x3c, 0x03, 0x8f, 0x79,
    0xe7, 0xf8, 0x7e, 0x00,
    /* U+0064 "d" (12x15) */
    0x00, 0xe0, 0x0f, 0x00, 0xf0, 0x0f, 0x1e, 0xf7, 0xff, 0x7f, 0xf7, 0x9f,
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x9f, 0x7f, 0xf7, 0xff, 0x3e, 0xf0,
    /* U+0065 "e" (11x11) */
    0x1f, 0x87, 0xf9, 0xef, 0xb8, 0xff, 0xff, 0xff, 0xfc, 0x03, 0x80, 0x79,
    0xe7, 0xf8, 0x7e, 0x00,
    /* U+0066 "f" (8x15) */
    0x1f, 0x3e, 0x3c, 0x78, 0xfe, 0xfe, 0xfe, 0x78, 0x78, 0x78, 0x78, 0x78,
    0x78, 0x78, 0x78,
    /* U+0067 "g" (12x15) */
    0x1e, 0xf3, 0xff, 0x7f, 0xf7, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xf7, 0x9f,
    0x7f, 0xf3, 0xff, 0x1e, 0xf0, 0x0f, 0x79, 0xe7, 0xfe, 0x3f, 0xc0,
    /* U+0068 "h" (11x15) */
    0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e, 0x79, 0xff, 0xbf, 0xf7, 0x8f, 0xf1,
    0xfe, 0x3f, 0xc7, 0xf8, 0xff, 0x1f, 0xe3, 0xfc, 0x78,
    /* U+0069 "i" (3x15) */
    0xfd, 0x8f, 0xff, 0xff, 0xff, 0xf8,
    /* U+006A "j" (5x19) */
    0x39, 0xc6, 0x03, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x7f, 0xfc,
    /* U+006B "k" (10x15) */
    0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe3, 0xf9, 0xee, 0x7b, 0xfc, 0xfe, 0x3f,
    0x8f, 0xf3, 0xfc, 0xe7, 0xb8, 0xfe, 0x3c,
    /* U+006C "l" (4x15) */
    0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+006D "m" (16x11) */
    0xe7, 0x1e, 0xff, 0xbf, 0xff, 0xff, 0xf3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7,
    0xe3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7,
    /* U+006E "n" (10x11) */
    0xe7, 0xbf, 0xff, 0xff, 0xc7, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1c,
    /* U+006F "o" (12x11) */
    0x1f, 0x83, 0xfc, 0x7f, 0xe7, 0x9e, 0xf0, 0xef, 0x0f, 0xf0, 0xe7, 0x1e,
    0x79, 0xe3, 0xfc, 0x1f, 0x80,
    /* U+0070 "p" (11x15) */
    0xe7, 0x9f, 0xfb, 0xff, 0x78, 0xfe, 0x1f, 0xc3, 0xf8, 0x7f, 0x8f, 0xfb,
    0xdf, 0xfb, 0x9e, 0x70, 0x0e, 0x01, 0xc0, 0x38, 0x00,
    /* U+0071 "q" (12x15) */
    0x1e, 0xf7, 0xff, 0x7f, 0xf7, 0x9f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x9f,
    0x7f, 0xf7, 0xff, 0x3e, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    /* U+0072 "r" (7x11) */
    0xef, 0xff, 0xff, 0x8e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x80,
    /* U+0073 "s" (11x11) */
    0x3f, 0x8f, 0xf9, 0xef, 0x38, 0x07, 0xe0, 0xff, 0x87, 0xf8, 0x0f, 0xf9,
    0xef, 0xf8, 0xfe, 0x00,
    /* U+0074 "t" (7x14) */
    0x38, 0xf1, 0xe7, 0xff, 0xff, 0xde, 0x3c, 0x78, 0xf1, 0xe3, 0xe3, 0xe3,
    0xc0,
    /* U+0075 "u" (10x11) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0xc7, 0xff, 0xff,
    0xf7, 0xdc,
    /* U+0076 "v" (11x11) */
    0xf0, 0xfe, 0x3d, 0xc7, 0xbc, 0xe7, 0x9c, 0x77, 0x8e, 0xe1, 0xfc, 0x1f,
    0x83, 0xe0, 0x7c, 0x00,
    /* U+0077 "w" (17x11) */
    0xf1, 0xc7, 0xf9, 0xe3, 0x9c, 0xf9, 0xce, 0x7c, 0xe7, 0x3e, 0xf3, 0xdb,
    0x70, 0xfd, 0xf8, 0x7e, 0xfc, 0x3e, 0x7e, 0x1f, 0x1e, 0x07, 0x8f, 0x00,
    /* U+0078 "x" (11x11) */
    0x71, 0xef, 0x38, 0xef, 0x1f, 0xc1, 0xf8, 0x3e, 0x07, 0xe1, 0xfc, 0x3b,
    0xcf, 0x3b, 0xc7, 0x80,
    /* U+0079 "y" (11x15) */
    0xf0, 0xfe, 0x3d, 0xc7, 0xbc, 0xe7, 0x9c, 0x77, 0x8e, 0xe1, 0xfc, 0x1f,
    0x83, 0xe0, 0x7c, 0x07, 0x81, 0xe0, 0xfc, 0x1f, 0x00,
    /* U+007A "z" (9x11) */
    0xff, 0xff, 0xff, 0xe1, 0xe1, 0xe0, 0xf0, 0xf0, 0xf0, 0xff, 0xff, 0xff,
    0xe0,
    /* U+007B "{" (8x18) */
    0x1f, 0x1f, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0xf8, 0xf0, 0xf8, 0x3c, 0x3c,
    0x3c, 0x3c, 0x3c, 0x1f, 0x1f, 0x07,
    /* U+007C "|" (4x24) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    /* U+007D "}" (7x18) */
    0xf1, 0xf1, 0xe1, 0xc3, 0x87, 0x0e, 0x1f, 0x0e, 0x3c, 0xf1, 0xc3, 0x87,
    0x1e, 0x7c, 0xf1, 0x80,
    /* U+007E "~" (11x4) */
    0x78, 0xef, 0xdf, 0xff, 0xf3, 0xe0,
    /* U+00B0 "" (7x7) */
    0x30, 0xfb, 0xfe, 0x3c, 0xff, 0xdf, 0x00,
    /* U+00B1 "" (11x11) */
    0x0e, 0x01, 0xc3, 0xff, 0xff, 0xf7, 0xfe, 0x1c, 0x03, 0x80, 0x00, 0xff,
    0xff, 0xfd, 0xff, 0x00,
    /* U+00B2 "" (8x9) */
    0x3c, 0x7e, 0xe7, 0x07, 0x0e, 0x1c, 0x78, 0x7f, 0x7f,
    /* U+00B3 "" (8x9) */
    0x3e, 0x7f, 0x67, 0x1e, 0x1e, 0x07, 0xe7, 0x7f, 0x3c,
    /* U+00B5 "" (11x15) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x8f, 0xff,
    0xff, 0xff, 0xbb, 0xf0, 0x0e, 0x01, 0xc0, 0x38, 0x00,
    /* U+00B7 "" (4x3) */
    0x7f, 0x70,
    /* U+00D7 "" (11x10) */
    0x20, 0xce, 0x3d, 0xef, 0x1f, 0xc1, 0xf0, 0x3e, 0x0f, 0xe3, 0xfe, 0xf1,
    0xec, 0x18,
    /* U+00F7 "" (11x12) */
    0x04, 0x01, 0xc0, 0x3c, 0x07, 0x00, 0x01, 0xff, 0xff, 0xfb, 0xfe, 0x06,
    0x01, 0xc0, 0x3c, 0x07, 0x00,
    /* U+0394 "" (15x15) */
    0x07, 0xc0, 0x0f, 0x80, 0x3f, 0x80, 0x7f, 0x00, 0xfe, 0x03, 0xde, 0x07,
    0xbc, 0x0e, 0x38, 0x3c, 0x78, 0x78, 0xf0, 0xf1, 0xe3, 0xc1, 0xe7, 0xff,
    0xcf, 0xff, 0xbf, 0xff, 0x80,
    /* U+03A9 "" (15x15) */
    0x07, 0xc0, 0x3f, 0xe0, 0xff, 0xe3, 0xe3, 0xe7, 0x83, 0xcf, 0x03, 0xfc,
    0x07, 0xf8, 0x0f, 0x70, 0x1e, 0xf0, 0x79, 0xe0, 0xf1, 0xe3, 0xc7, 0xe7,
    0xff, 0xcf, 0xff, 0x9f, 0x80,
    /* U+03B1 "" (12x11) */
    0x1e, 0x73, 0xf7, 0x7f, 0xe7, 0x0e, 0x70, 0xef, 0x0e, 0x70, 0xe7, 0x1e,
    0x7b, 0xf3, 0xf7, 0x1e, 0x70,
    /* U+03B2 "" (11x19) */
    0x1e, 0x0f, 0xf3, 0xfe, 0x79, 0xee, 0x3d, 0xc7, 0xb9, 0xe7, 0x7c, 0xef,
    0xdc, 0x3b, 0x87, 0xf8, 0xff, 0xfd, 0xff, 0xbf, 0xe7, 0x00, 0xe0, 0x1c,
    0x03, 0x80, 0x00,
    /* U+03B3 "" (10x15) */
    0xf1, 0xfc, 0x77, 0x3d, 0xce, 0x7b, 0x8e, 0xe3, 0xf0, 0xfc, 0x1f, 0x07,
    0x81, 0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0,
    /* U+03B4 "" (11x15) */
    0x1f, 0x87, 0xf0, 0xe0, 0x1c, 0x03, 0xf0, 0x3f, 0x0f, 0xf3, 0x8f, 0x70,
    0xfe, 0x1f, 0xc3, 0xb8, 0xf7, 0xbe, 0x7f, 0x87, 0xe0,
    /* U+03B5 "" (11x11) */
    0x3f, 0x8f, 0xf9, 0xef, 0xb8, 0x07, 0xe0, 0x7c, 0x1f, 0x87, 0x80, 0xf1,
    0xef, 0xf8, 0xfe, 0x00,
    /* U+03B8 "" (10x15) */
    0x1e, 0x1f, 0xc7, 0xfb, 0xcf, 0xe3, 0xf8, 0x7f, 0xff, 0xff, 0xff, 0xf8,
    0x7e, 0x1f, 0xcf, 0xff, 0x9f, 0xe3, 0xf0,
    /* U+03BB "" (12x15) */
    0x78, 0x07, 0xc0, 0x3e, 0x00, 0xe0, 0x0f, 0x00, 0xf0, 0x1f, 0x01, 0xf8,
    0x1f, 0x83, 0xf8, 0x3b, 0xc7, 0x9c, 0x79, 0xe7, 0x1f, 0xf0, 0xf0,
    /* U+03BC "" (11x15) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x8f, 0xff,
    0xff, 0xff, 0xbb, 0xf0, 0x0e, 0x01, 0xc0, 0x38, 0x00,
    /* U+03C0 "" (13x11) */
    0x7f, 0xff, 0xff, 0xcf, 0x3c, 0x79, 0xc3, 0xce, 0x1e, 0x70, 0xf3, 0x87,
    0x9c, 0x3c, 0xf1, 0xe7, 0xcf, 0x1e,
    /* U+03C3 "" (12x11) */
    0x07, 0xe3, 0xff, 0x7f, 0xf7, 0x1c, 0xf1, 0xcf, 0x1e, 0xf1, 0xe7, 0x1e,
    0x7b, 0xc3, 0xfc, 0x1f, 0x80,
    /* U+03C4 "" (10x11) */
    0xff, 0xff, 0xff, 0xfc, 0x70, 0x1c, 0x07, 0x01, 0xc0, 0x70, 0x1e, 0x07,
    0xc0, 0xf0,
    /* U+03C6 "" (15x15) */
    0x30, 0xf8, 0xf3, 0xf9, 0xef, 0xfb, 0x9e, 0x7f, 0x3c, 0xfe, 0x79, 0xdc,
    0xf3, 0xbd, 0xef, 0x7f, 0xfe, 0x7f, 0xf8, 0x3f, 0xc0, 0x1e, 0x00, 0x3c,
    0x00, 0x78, 0x00, 0xf0, 0x00,
    /* U+03C9 "" (15x11) */
    0x70, 0x1c, 0xe0, 0x3b, 0x8e, 0x7f, 0x1c, 0x7e, 0x38, 0xfc, 0x71, 0xf8,
    0xe3, 0xf3, 0xc7, 0xf7, 0xde, 0xff, 0xf8, 0xf1, 0xe0,
    /* U+2013 "" (10x3) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+2014 "" (20x3) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+2018 "" (4x7) */
    0x27, 0x6e, 0xee, 0xe0,
    /* U+2019 "" (4x7) */
    0x77, 0x77, 0x7e, 0x60,
    /* U+201C "" (9x7) */
    0x21, 0xb9, 0xd8, 0xfc, 0x7e, 0x77, 0x3b, 0x9c,
    /* U+201D "" (9x7) */
    0x33, 0xb9, 0xdc, 0xee, 0x76, 0x37, 0x39, 0x8c,
    /* U+2022 "" (6x6) */
    0x7b, 0xff, 0xff, 0xfd, 0xe0,
    /* U+2026 "" (13x3) */
    0xe7, 0x7f, 0x7b, 0xf9, 0xce,
    /* U+2030 "" (19x15) */
    0x3c, 0x08, 0x0f, 0xc3, 0x03, 0x98, 0xc0, 0x73, 0x18, 0x0e, 0x66, 0x00,
    0xfd, 0x80, 0x0f, 0x60, 0x00, 0x0c, 0x00, 0x03, 0x00, 0x00, 0xcf, 0xf8,
    0x1b, 0xbf, 0x86, 0x67, 0x31, 0x8c, 0xe6, 0x31, 0xff, 0xcc, 0x1e, 0xf0,
    /* U+2190 "" (14x14) */
    0x03, 0x80, 0x1e, 0x00, 0xf0, 0x07, 0x80, 0x3c, 0x01, 0xff, 0xff, 0xff,
    0xdf, 0xff, 0x38, 0x00, 0x70, 0x00, 0xe0, 0x01, 0xc0, 0x03, 0x80, 0x04,
    0x00,
    /* U+2191 "" (13x14) */
    0x07, 0x00, 0x7c, 0x07, 0xf0, 0x7f, 0xc7, 0xff, 0x7b, 0xbf, 0x9c, 0xe8,
    0xe2, 0x07, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x80,
    /* U+2192 "" (15x14) */
    0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x80, 0x07, 0x9f, 0xff, 0xbf,
    0xff, 0xff, 0xfe, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e, 0x00, 0x38,
    0x00, 0x20, 0x00,
    /* U+2193 "" (13x15) */
    0x06, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x03, 0x80, 0x1c, 0x18,
    0xe6, 0xe7, 0x7b, 0xbf, 0x8f, 0xf8, 0x3f, 0x80, 0xf8, 0x03, 0x80, 0x08,
    0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 59, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 109, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 185, .box_w = 8, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 15, .adv_w = 202, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 203, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 67, .adv_w = 273, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 97, .adv_w = 212, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 108, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 125, .adv_w = 115, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 139, .adv_w = 115, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 151, .adv_w = 182, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 159, .adv_w = 212, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 173, .adv_w = 112, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 177, .adv_w = 143, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 179, .adv_w = 107, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 121, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 196, .adv_w = 221, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 134, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 197, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 206, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 214, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 205, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 210, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 182, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 211, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 210, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 107, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 109, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 422, .adv_w = 212, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 212, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 449, .adv_w = 212, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 463, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 335, .box_w = 19, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 528, .adv_w = 241, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 205, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 236, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 225, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 190, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 179, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 238, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 231, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 84, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 178, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 218, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 174, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 288, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 224, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 245, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 201, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 245, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 914, .adv_w = 204, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 203, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 209, .box_w = 13, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 223, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 241, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1033, .adv_w = 335, .box_w = 21, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 230, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 232, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1125, .adv_w = 211, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 115, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1160, .adv_w = 121, .box_w = 8, .box_h = 17, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1177, .adv_w = 115, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1189, .adv_w = 150, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1195, .adv_w = 148, .box_w = 10, .box_h = 3, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1199, .adv_w = 145, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 1201, .adv_w = 181, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1217, .adv_w = 197, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 183, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1254, .adv_w = 197, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 185, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1293, .adv_w = 120, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1308, .adv_w = 197, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1331, .adv_w = 197, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1352, .adv_w = 84, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1358, .adv_w = 84, .box_w = 5, .box_h = 19, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1370, .adv_w = 183, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1389, .adv_w = 84, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1397, .adv_w = 290, .box_w = 16, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1419, .adv_w = 197, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1433, .adv_w = 190, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1450, .adv_w = 197, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1471, .adv_w = 197, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1494, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1504, .adv_w = 177, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1520, .adv_w = 119, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1533, .adv_w = 197, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1547, .adv_w = 183, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1563, .adv_w = 269, .box_w = 17, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1587, .adv_w = 180, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1603, .adv_w = 183, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1624, .adv_w = 179, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1637, .adv_w = 150, .box_w = 8, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1655, .adv_w = 118, .box_w = 4, .box_h = 24, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 1667, .adv_w = 150, .box_w = 7, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1683, .adv_w = 212, .box_w = 11, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1689, .adv_w = 139, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1696, .adv_w = 212, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1712, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1721, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1730, .adv_w = 211, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1751, .adv_w = 107, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1753, .adv_w = 212, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1767, .adv_w = 212, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1784, .adv_w = 241, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1813, .adv_w = 243, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1842, .adv_w = 202, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1859, .adv_w = 189, .box_w = 11, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1886, .adv_w = 168, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1905, .adv_w = 217, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1926, .adv_w = 178, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1942, .adv_w = 189, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1961, .adv_w = 189, .box_w = 12, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1984, .adv_w = 211, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2005, .adv_w = 228, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2023, .adv_w = 190, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2040, .adv_w = 184, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2054, .adv_w = 254, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 2083, .adv_w = 271, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2104, .adv_w = 160, .box_w = 10, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 2108, .adv_w = 320, .box_w = 20, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 2116, .adv_w = 114, .box_w = 4, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 2120, .adv_w = 114, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2124, .adv_w = 197, .box_w = 9, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 2132, .adv_w = 193, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 2140, .adv_w = 117, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 2145, .adv_w = 244, .box_w = 13, .box_h = 3, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2150, .adv_w = 348, .box_w = 19, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2186, .adv_w = 297, .box_w = 14, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 2211, .adv_w = 297, .box_w = 13, .box_h = 14, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2234, .adv_w = 297, .box_w = 15, .box_h = 14, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 2261, .adv_w = 297, .box_w = 13, .box_h = 15, .ofs_x = 3, .ofs_y = 0}
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
    3, 7, 3, 13, 3, 15, 3, 21, 3, 34, 3, 43, 3, 104, 3, 126,
    5, 34, 6, 121, 6, 122, 6, 123, 6, 124, 7, 53, 7, 55, 7, 56,
    7, 58, 7, 61, 7, 121, 7, 123, 8, 7, 8, 13, 8, 15, 8, 21,
    8, 34, 8, 43, 8, 104, 8, 126, 11, 13, 11, 15, 11, 21, 11, 34,
    11, 43, 11, 64, 11, 104, 11, 126, 12, 57, 13, 1, 13, 3, 13, 8,
    13, 17, 13, 18, 13, 23, 13, 24, 13, 25, 13, 32, 13, 53, 13, 58,
    13, 65, 13, 122, 13, 124, 14, 24, 14, 53, 14, 57, 14, 58, 14, 121,
    14, 123, 15, 1, 15, 2, 15, 3, 15, 8, 15, 17, 15, 18, 15, 20,
    15, 23, 15, 24, 15, 25, 15, 26, 15, 32, 15, 53, 15, 58, 15, 65,
    15, 122, 15, 124, 16, 13, 16, 15, 16, 43, 16, 126, 17, 13, 17, 15,
    17, 24, 17, 58, 17, 64, 17, 121, 17, 123, 17, 126, 18, 64, 20, 13,
    20, 15, 20, 126, 22, 13, 22, 15, 22, 126, 23, 64, 24, 4, 24, 7,
    24, 13, 24, 15, 24, 21, 24, 24, 24, 29, 24, 34, 24, 43, 24, 64,
    24, 66, 24, 68, 24, 69, 24, 70, 24, 72, 24, 80, 24, 82, 24, 104,
    24, 106, 24, 109, 24, 110, 24, 111, 24, 115, 24, 117, 24, 118, 24, 126,
    26, 58, 26, 64, 26, 121, 26, 123, 27, 53, 27, 55, 27, 61, 27, 121,
    27, 123, 28, 53, 28, 55, 28, 61, 28, 121, 28, 123, 30, 34, 30, 55,
    30, 56, 30, 57, 30, 58, 30, 61, 30, 87, 30, 90, 30, 121, 30, 123,
    31, 24, 31, 34, 31, 53, 31, 55, 31, 56, 31, 57, 31, 58, 31, 59,
    31, 61, 31, 121, 31, 123, 32, 34, 32, 104, 34, 3, 34, 8, 34, 11,
    34, 18, 34, 29, 34, 30, 34, 32, 34, 36, 34, 40, 34, 48, 34, 50,
    34, 53, 34, 55, 34, 56, 34, 58, 34, 61, 34, 63, 34, 85, 34, 87,
    34, 88, 34, 90, 34, 96, 34, 97, 34, 101, 34, 121, 34, 122, 34, 123,
    34, 124, 36, 57, 36, 64, 37, 13, 37, 15, 37, 16, 37, 34, 37, 53,
    37, 55, 37, 57, 37, 58, 37, 61, 37, 64, 37, 121, 37, 123, 37, 126,
    39, 13, 39, 15, 39, 34, 39, 43, 39, 68, 39, 69, 39, 70, 39, 72,
    39, 80, 39, 82, 39, 106, 39, 115, 39, 117, 39, 126, 40, 34, 40, 53,
    40, 55, 40, 58, 40, 61, 40, 74, 40, 75, 41, 64, 42, 64, 43, 13,
    43, 15, 43, 16, 43, 64, 43, 126, 44, 12, 44, 14, 44, 29, 44, 30,
    44, 36, 44, 40, 44, 48, 44, 50, 44, 68, 44, 69, 44, 70, 44, 72,
    44, 80, 44, 82, 44, 86, 44, 87, 44, 88, 44, 90, 44, 95, 44, 97,
    44, 100, 44, 101, 44, 103, 44, 106, 44, 115, 44, 117, 44, 130, 45, 3,
    45, 8, 45, 11, 45, 12, 45, 14, 45, 18, 45, 36, 45, 40, 45, 48,
    45, 50, 45, 53, 45, 55, 45, 56, 45, 58, 45, 61, 45, 63, 45, 85,
    45, 87, 45, 90, 45, 95, 45, 96, 45, 101, 45, 103, 45, 121, 45, 122,
    45, 123, 45, 124, 45, 130, 46, 64, 47, 64, 48, 13, 48, 15, 48, 58,
    48, 126, 49, 7, 49, 12, 49, 13, 49, 14, 49, 15, 49, 34, 49, 43,
    49, 66, 49, 68, 49, 69, 49, 70, 49, 72, 49, 80, 49, 82, 49, 95,
    49, 101, 49, 103, 49, 106, 49, 115, 49, 117, 49, 126, 49, 130, 50, 13,
    50, 15, 50, 58, 50, 126, 51, 55, 51, 58, 51, 61, 52, 34, 53, 7,
    53, 13, 53, 15, 53, 16, 53, 21, 53, 27, 53, 28, 53, 29, 53, 34,
    53, 36, 53, 40, 53, 43, 53, 48, 53, 50, 53, 64, 53, 66, 53, 68,
    53, 69, 53, 70, 53, 72, 53, 78, 53, 79, 53, 80, 53, 81, 53, 82,
    53, 83, 53, 84, 53, 86, 53, 87, 53, 88, 53, 90, 53, 91, 53, 100,
    53, 106, 53, 107, 53, 115, 53, 117, 53, 126, 54, 13, 54, 15, 54, 16,
    54, 64, 54, 126, 55, 7, 55, 13, 55, 15, 55, 16, 55, 21, 55, 27,
    55, 28, 55, 29, 55, 30, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43,
    55, 48, 55, 50, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72,
    55, 80, 55, 82, 55, 84, 55, 97, 55, 102, 55, 106, 55, 115, 55, 117,
    55, 126, 56, 7, 56, 13, 56, 15, 56, 16, 56, 21, 56, 27, 56, 28,
    56, 29, 56, 30, 56, 34, 56, 36, 56, 40, 56, 43, 56, 48, 56, 50,
    56, 66, 56, 68, 56, 69, 56, 70, 56, 72, 56, 78, 56, 79, 56, 80,
    56, 81, 56, 82, 56, 83, 56, 84, 56, 97, 56, 106, 56, 107, 56, 115,
    56, 117, 56, 126, 57, 29, 57, 30, 57, 97, 58, 7, 58, 12, 58, 13,
    58, 14, 58, 15, 58, 21, 58, 27, 58, 28, 58, 29, 58, 30, 58, 34,
    58, 36, 58, 40, 58, 43, 58, 48, 58, 50, 58, 66, 58, 68, 58, 69,
    58, 70, 58, 72, 58, 74, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82,
    58, 83, 58, 84, 58, 86, 58, 95, 58, 97, 58, 100, 58, 101, 58, 102,
    58, 103, 58, 106, 58, 107, 58, 115, 58, 117, 58, 126, 58, 130, 59, 29,
    61, 3, 61, 5, 61, 8, 61, 11, 61, 18, 61, 29, 61, 30, 61, 32,
    61, 36, 61, 40, 61, 48, 61, 50, 61, 52, 61, 53, 61, 55, 61, 56,
    61, 58, 61, 61, 61, 63, 61, 68, 61, 69, 61, 70, 61, 71, 61, 72,
    61, 80, 61, 82, 61, 84, 61, 85, 61, 87, 61, 88, 61, 90, 61, 96,
    61, 97, 61, 101, 61, 106, 61, 108, 61, 115, 61, 117, 61, 121, 61, 122,
    61, 123, 61, 124, 63, 13, 63, 15, 63, 21, 63, 34, 63, 43, 63, 64,
    63, 104, 63, 126, 64, 11, 64, 17, 64, 18, 64, 20, 64, 21, 64, 22,
    64, 23, 64, 25, 64, 26, 64, 36, 64, 40, 64, 48, 64, 50, 64, 53,
    64, 54, 64, 55, 64, 61, 64, 63, 64, 74, 64, 75, 64, 78, 64, 79,
    64, 81, 64, 83, 64, 87, 64, 90, 64, 96, 64, 107, 64, 108, 64, 121,
    64, 123, 66, 53, 66, 55, 66, 56, 66, 58, 66, 61, 66, 121, 66, 123,
    67, 53, 67, 55, 67, 56, 67, 58, 67, 61, 67, 121, 67, 123, 68, 53,
    68, 55, 68, 56, 68, 58, 68, 61, 68, 121, 68, 123, 69, 64, 70, 10,
    70, 34, 70, 53, 70, 55, 70, 56, 70, 57, 70, 58, 70, 61, 70, 62,
    70, 87, 70, 88, 70, 89, 70, 90, 70, 94, 70, 121, 70, 123, 71, 12,
    71, 13, 71, 14, 71, 15, 71, 16, 71, 21, 71, 34, 71, 43, 71, 64,
    71, 66, 71, 68, 71, 69, 71, 70, 71, 72, 71, 80, 71, 82, 71, 84,
    71, 95, 71, 101, 71, 102, 71, 103, 71, 106, 71, 115, 71, 117, 71, 125,
    71, 126, 71, 130, 72, 53, 72, 64, 72, 75, 73, 53, 73, 55, 73, 56,
    73, 58, 73, 61, 73, 121, 73, 123, 74, 10, 74, 55, 74, 56, 74, 61,
    74, 62, 74, 64, 74, 94, 75, 10, 75, 55, 75, 56, 75, 61, 75, 62,
    75, 64, 75, 94, 76, 29, 76, 53, 76, 87, 76, 90, 77, 64, 78, 18,
    78, 53, 78, 55, 78, 56, 78, 58, 78, 61, 78, 121, 78, 123, 79, 53,
    79, 55, 79, 56, 79, 58, 79, 61, 79, 121, 79, 123, 80, 34, 80, 53,
    80, 55, 80, 56, 80, 57, 80, 58, 80, 61, 80, 121, 80, 123, 81, 53,
    81, 55, 81, 56, 81, 58, 81, 61, 81, 121, 81, 123, 82, 53, 82, 64,
    82, 75, 83, 13, 83, 15, 83, 29, 83, 34, 83, 43, 83, 53, 83, 59,
    83, 71, 83, 85, 83, 126, 84, 53, 84, 55, 84, 56, 84, 58, 84, 61,
    84, 121, 84, 123, 85, 35, 85, 37, 85, 38, 85, 39, 85, 41, 85, 42,
    85, 44, 85, 45, 85, 46, 85, 47, 85, 49, 85, 51, 85, 67, 85, 73,
    85, 76, 85, 77, 85, 93, 85, 122, 85, 124, 86, 53, 86, 58, 86, 122,
    86, 124, 87, 16, 87, 34, 87, 43, 87, 64, 87, 122, 87, 124, 88, 7,
    88, 13, 88, 15, 88, 34, 88, 43, 88, 53, 88, 59, 88, 122, 88, 124,
    88, 126, 90, 16, 90, 34, 90, 43, 90, 64, 90, 122, 90, 124, 92, 75,
    93, 64, 95, 57, 96, 7, 96, 13, 96, 15, 96, 21, 96, 34, 96, 36,
    96, 40, 96, 43, 96, 48, 96, 50, 96, 64, 96, 104, 96, 126, 97, 34,
    97, 55, 97, 56, 97, 57, 97, 58, 97, 61, 97, 87, 97, 90, 97, 121,
    97, 123, 99, 13, 99, 15, 99, 21, 99, 34, 99, 43, 99, 85, 99, 104,
    99, 114, 99, 116, 99, 126, 100, 29, 100, 53, 100, 58, 100, 104, 100, 121,
    100, 122, 100, 123, 100, 124, 101, 19, 101, 24, 101, 34, 101, 43, 101, 53,
    101, 55, 101, 56, 101, 57, 101, 58, 101, 61, 101, 89, 101, 121, 101, 123,
    102, 53, 102, 55, 102, 58, 102, 61, 103, 57, 104, 3, 104, 8, 104, 11,
    104, 18, 104, 32, 104, 63, 104, 96, 104, 108, 104, 109, 104, 111, 104, 116,
    104, 118, 104, 121, 104, 122, 104, 123, 104, 124, 106, 12, 106, 14, 106, 16,
    106, 29, 106, 95, 106, 101, 106, 103, 106, 104, 106, 121, 106, 123, 106, 130,
    107, 121, 107, 123, 108, 12, 108, 13, 108, 14, 108, 15, 108, 16, 108, 29,
    108, 64, 108, 95, 108, 101, 108, 103, 108, 104, 108, 112, 108, 121, 108, 123,
    108, 126, 108, 130, 109, 116, 109, 121, 109, 123, 111, 121, 111, 123, 112, 18,
    112, 108, 112, 109, 112, 114, 112, 116, 112, 118, 114, 121, 114, 123, 115, 13,
    115, 15, 115, 16, 115, 104, 115, 112, 115, 121, 115, 123, 115, 126, 116, 109,
    116, 121, 116, 123, 117, 34, 117, 53, 117, 55, 117, 56, 117, 57, 117, 58,
    117, 61, 117, 121, 117, 123, 118, 121, 118, 123, 121, 7, 121, 13, 121, 15,
    121, 16, 121, 21, 121, 34, 121, 43, 121, 104, 121, 126, 122, 4, 122, 7,
    122, 13, 122, 15, 122, 16, 122, 17, 122, 21, 122, 23, 122, 25, 122, 27,
    122, 28, 122, 29, 122, 30, 122, 33, 122, 34, 122, 43, 122, 64, 122, 66,
    122, 68, 122, 69, 122, 70, 122, 72, 122, 80, 122, 82, 122, 84, 122, 85,
    122, 86, 122, 87, 122, 90, 122, 97, 122, 100, 122, 104, 122, 106, 122, 109,
    122, 110, 122, 111, 122, 115, 122, 117, 122, 118, 122, 126, 123, 7, 123, 13,
    123, 15, 123, 16, 123, 21, 123, 34, 123, 43, 123, 104, 123, 126, 124, 4,
    124, 7, 124, 13, 124, 15, 124, 16, 124, 17, 124, 21, 124, 23, 124, 25,
    124, 27, 124, 28, 124, 29, 124, 30, 124, 33, 124, 34, 124, 43, 124, 64,
    124, 66, 124, 68, 124, 69, 124, 70, 124, 72, 124, 80, 124, 82, 124, 84,
    124, 86, 124, 87, 124, 90, 124, 97, 124, 100, 124, 104, 124, 106, 124, 109,
    124, 110, 124, 111, 124, 115, 124, 117, 124, 118, 124, 126, 126, 3, 126, 8,
    126, 18, 126, 32, 126, 58, 126, 65, 126, 122, 126, 124, 128, 19, 128, 24,
    128, 53, 128, 55, 128, 56, 128, 57, 128, 58, 128, 61, 128, 89, 128, 121,
    128, 123,
};

static const int8_t kern_pair_values[] = {
    -11, -29, -29, -20, -25, -53, -25, -29, -5, -20, -22, -20, -22, -18, -20, -13,
    -24, -20, -29, -29, -11, -29, -29, -20, -25, -53, -25, -29, -44, -44, -15, -31,
    -31, -22, -25, -44, -13, -11, -32, -32, -9, -29, -9, -9, -9, -33, -11, -22,
    -44, -32, -32, -9, -9, -13, -10, -8, -8, -11, -4, -32, -32, -9, -29, -7,
    -9, -9, -9, -4, -33, -11, -22, -44, -32, -32, -13, -13, -20, -13, -9, -9,
    -6, -11, -15, -15, -15, -9, 11, -7, -7, -7, -7, -7, -7, -15, -18, -15,
    -40, -40, -19, 6, -29, -35, -31, -51, -15, -16, -16, -16, -16, -16, -16, -35,
    -16, -16, -16, -16, -16, -16, -16, -40, -11, -15, -15, -15, -11, -20, -20, -15,
    -15, -11, -20, -20, -15, -15, -16, -22, -20, -16, -31, -22, -13, -13, -18, -18,
    -24, -14, -25, -24, -24, -18, -29, -20, -24, -31, -31, -20, -20, -25, -25, -31,
    -11, -14, -16, -20, -12, -12, -12, -12, -29, -29, -24, -24, -29, -31, -11, -22,
    -22, -22, -31, -16, -11, -42, -33, -42, -33, -5, -13, -15, -15, -13, -12, -10,
    -13, -11, -14, -13, -13, -11, -11, -15, -13, -13, -29, -22, -13, -13, -13, -13,
    -13, -13, -13, -13, -13, -13, -7, -10, -7, -9, -7, 11, 11, 11, 11, -11,
    -11, -18, -16, -11, -14, -14, -22, -11, -13, -13, -13, -13, -13, -13, -13, -13,
    -13, -13, -11, -13, -20, -13, -14, -11, -11, -14, -14, -13, -13, -13, -14, -29,
    -29, -42, -11, -11, -15, -9, -9, -9, -9, -29, -25, -13, -30, -25, -42, -7,
    -22, -22, -11, -42, -11, -11, -27, -13, -27, -13, -11, 11, 11, -15, -15, -14,
    -15, -11, -6, -13, -6, -13, -27, -31, -5, -3, -3, -3, -3, -3, -3, -6,
    -6, -6, -3, -3, -3, -13, -6, -15, -15, -14, -15, -6, -10, -6, -5, -11,
    -11, -11, -25, -22, -11, -11, -25, -29, -10, -10, -29, -10, -10, -18, -24, -25,
    -25, -25, -25, -18, -18, -25, -18, -25, -18, -24, -24, -20, -20, -20, -15, -24,
    -25, -18, -25, -25, -11, -11, -11, -18, -16, -11, -16, -31, -31, -21, -11, -20,
    -20, -24, -20, -11, -29, -13, -13, -31, -13, -13, -25, -19, -20, -20, -20, -20,
    -20, -20, -15, -20, -13, -20, -20, -20, -31, -16, -31, -31, -11, -11, -16, -16,
    -24, -20, -24, -9, -9, -20, -9, -9, -19, -16, -16, -16, -16, -11, -11, -16,
    -11, -16, -11, -11, -20, -16, -11, -16, -16, -31, -18, -16, -16, -20, -10, -22,
    -10, -22, -22, -20, -20, -33, -31, -24, -14, -14, -11, -14, -14, -34, -36, -36,
    -36, -36, -3, -13, -13, -36, -13, -36, -13, -22, -13, -10, -31, -13, -10, -15,
    -10, -36, -13, -36, -36, -22, -10, -20, -25, -5, -25, -31, -11, -14, -16, -20,
    -12, -12, -12, -12, -5, -29, -29, -24, -24, -29, -31, -8, -8, -8, -3, -8,
    -8, -8, -4, -11, -22, -22, -22, -31, -16, -11, -8, -16, -8, -8, -42, -33,
    -42, -33, -44, -44, -15, -31, -31, -22, -25, -44, -22, -15, -35, -15, -18, -15,
    -15, -15, -15, -13, -13, -13, -13, -18, -13, -25, -25, -22, 11, 31, 15, 15,
    15, 15, -25, -25, -22, 15, -18, -13, -13, -15, -16, -16, -32, -16, -15, -15,
    -25, -20, -16, -37, -20, -20, -20, -25, -20, -16, -37, -20, -20, -20, 11, -4,
    -11, -25, -20, -16, -9, -37, -20, -4, -6, -4, -6, -6, -4, -20, -20, -6,
    -18, -6, -18, -4, -20, -11, -20, -5, -6, -6, -6, -6, -6, -6, -6, -6,
    -6, -6, -6, -6, -6, -6, -6, -6, -18, -6, -16, 11, 3, -15, -16, -16,
    -32, -16, -15, -15, 11, 11, 11, 11, 11, 13, 11, 11, 11, 11, 11, 11,
    13, 11, -27, -18, 3, 3, 11, -13, -15, -16, -16, -32, -16, -15, -15, -15,
    -16, -16, -32, -16, -15, -15, -11, -25, -20, -16, -9, -37, -20, -20, -20, -25,
    -20, -16, -37, -20, -20, -20, -16, 11, 3, -20, -20, -13, -13, -18, -18, -11,
    9, 9, -20, -24, -15, -11, -24, -15, -16, -16, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8, -16, -18, 5,
    5, -18, -22, -20, -25, 10, 10, -11, -24, -24, -22, -18, -16, -11, 14, 14,
    -24, -18, -22, -20, -25, 10, 10, 4, 11, -13, -11, -44, -44, -15, -31, -6,
    -6, -31, -6, -6, -22, -25, -44, -16, -22, -20, -16, -31, -22, -13, -13, -18,
    -18, -35, -35, -18, -29, -36, 11, -29, 11, 11, -35, -13, -16, -18, -13, -13,
    5, -13, 5, -6, -9, -11, -15, -9, -7, -7, -13, -10, -7, -7, -8, -8,
    -18, -13, -15, -13, -13, -31, -31, -25, -11, -20, -25, -25, -22, -11, -13, -16,
    -11, -44, -31, -44, -31, -5, -5, -11, -13, -5, -5, -5, -13, -16, -16, -5,
    -20, -20, -5, -24, -5, -24, -11, -13, -13, -5, -5, -5, -22, -13, -20, -20,
    -24, -5, -11, -20, -20, -20, -20, -18, -18, -13, -22, -31, -13, -13, -13, -24,
    -24, -11, -13, -22, -13, -13, -24, -13, -13, -13, -11, -25, -20, -16, -9, -37,
    -20, -20, -20, -20, -20, -20, -35, -35, -31, -20, -31, -47, -31, -35, -40, -22,
    -42, -42, -45, -15, -31, -15, -13, -18, -18, -31, -18, -18, -44, -40, -13, -18,
    -20, -20, -20, -20, -20, -20, -22, 6, -13, 7, 7, -18, -13, -42, -20, -20,
    -20, -22, -20, -20, -20, -42, -20, -35, -35, -31, -20, -31, -47, -31, -35, -40,
    -22, -42, -42, -45, -15, -31, -15, -13, -18, -18, -31, -18, -18, -44, -40, -13,
    -18, -20, -20, -20, -20, -20, -20, -22, -13, 7, 7, -18, -13, -42, -20, -20,
    -20, -22, -20, -20, -20, -42, -32, -32, -29, -33, -22, -44, -32, -32, -6, -9,
    -9, -7, -7, -13, -10, -7, -7, -8, -8,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1001,
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

const lv_font_t humid1_font_inter_tight_bold_20 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 25,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 15,
    .x_height = 11,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -3,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_20,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_INTER_TIGHT_BOLD_20 */
