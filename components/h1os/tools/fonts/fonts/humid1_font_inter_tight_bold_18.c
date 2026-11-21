/*******************************************************************************
 * Font: humid1_font_inter_tight_bold_18 (inter_tight bold)
 * Size: 18 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_18 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_INTER_TIGHT_BOLD_18
#define HUMID1_FONT_INTER_TIGHT_BOLD_18 1
#endif

#if HUMID1_FONT_INTER_TIGHT_BOLD_18

extern const lv_font_t humid1_icon_fa7_solid_18;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x13) */
    0xff, 0xff, 0xff, 0xff, 0x70, 0x6f, 0x70,
    /* U+0022 "" (8x6) */
    0xf7, 0xf7, 0x77, 0x67, 0x67, 0x66,
    /* U+0023 "#" (11x13) */
    0x1c, 0xc3, 0x18, 0x67, 0x3f, 0xf7, 0xfe, 0x73, 0x8e, 0x61, 0xdc, 0xff,
    0xff, 0xf8, 0xce, 0x39, 0x87, 0x30,
    /* U+0024 "$" (11x16) */
    0x04, 0x00, 0xc0, 0x7e, 0x3f, 0xe7, 0xfe, 0xe9, 0xdf, 0x03, 0xf8, 0x3f,
    0xc0, 0xfc, 0x17, 0xfa, 0x77, 0xfe, 0xff, 0x87, 0xe0, 0x30,
    /* U+0025 "%" (13x14) */
    0x30, 0x03, 0xe1, 0xbb, 0x19, 0x99, 0x8c, 0xcc, 0x3e, 0xc0, 0xec, 0x00,
    0x60, 0x06, 0xf0, 0x6f, 0xc2, 0x66, 0x33, 0x33, 0x1d, 0x90, 0x78,
    /* U+0026 "&" (12x13) */
    0x1f, 0x03, 0xf0, 0x3b, 0x83, 0x38, 0x3f, 0x03, 0xf0, 0x3e, 0x67, 0xe6,
    0x77, 0xef, 0x3e, 0xf3, 0xc7, 0xfe, 0x3f, 0xf0,
    /* U+0027 "'" (4x6) */
    0xff, 0xf7, 0x66,
    /* U+0028 "(" (5x16) */
    0x39, 0xdc, 0xe7, 0x7b, 0x9c, 0xe7, 0x39, 0xe7, 0x39, 0xc7,
    /* U+0029 ")" (5x16) */
    0xe3, 0x9c, 0xf3, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0xbd, 0xce,
    /* U+002A "" (6x7) */
    0x32, 0xdf, 0xde, 0xfe, 0xd3, 0x00,
    /* U+002B "+" (10x9) */
    0x0c, 0x03, 0x00, 0xc0, 0x78, 0xff, 0xff, 0xf0, 0xc0, 0x30, 0x0c, 0x00,
    /* U+002C "," (4x6) */
    0xfe, 0xee, 0xcc,
    /* U+002D "-" (6x3) */
    0xff, 0xff, 0xc0,
    /* U+002E "." (4x3) */
    0x6f, 0x60,
    /* U+002F "/" (7x16) */
    0x0e, 0x1c, 0x30, 0xe1, 0xc3, 0x8e, 0x1c, 0x38, 0x61, 0xc3, 0x87, 0x0c,
    0x38, 0x70,
    /* U+0030 "0" (11x13) */
    0x3f, 0x0f, 0xf3, 0xcf, 0x78, 0xee, 0x1f, 0xc3, 0xf8, 0x7f, 0x0f, 0xe1,
    0xfe, 0x3b, 0xef, 0x3f, 0xc3, 0xf0,
    /* U+0031 "1" (6x13) */
    0x3f, 0xff, 0xe7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c,
    /* U+0032 "2" (11x13) */
    0x3f, 0x8f, 0xf9, 0xcf, 0x78, 0xe0, 0x1c, 0x07, 0x80, 0xe0, 0x78, 0x1e,
    0x07, 0x81, 0xf0, 0x3f, 0xf7, 0xfe,
    /* U+0033 "3" (10x13) */
    0x3f, 0x1f, 0xef, 0x3b, 0x8f, 0x03, 0x87, 0xe1, 0xf0, 0x1e, 0x03, 0xf8,
    0xff, 0x3f, 0xfe, 0x3f, 0x00,
    /* U+0034 "4" (12x13) */
    0x07, 0xc0, 0x7c, 0x0f, 0xc0, 0xfc, 0x1d, 0xc3, 0xdc, 0x39, 0xc7, 0x1c,
    0x7f, 0xef, 0xff, 0x7f, 0xf0, 0x1c, 0x01, 0xc0,
    /* U+0035 "5" (10x13) */
    0xff, 0xbf, 0xef, 0x03, 0x80, 0xee, 0x3f, 0xef, 0xf8, 0x0f, 0x01, 0xf8,
    0x7f, 0x3d, 0xfe, 0x3f, 0x00,
    /* U+0036 "6" (10x13) */
    0x3f, 0x1f, 0xe7, 0x3f, 0x87, 0xe6, 0x3f, 0xef, 0xff, 0xc7, 0xe1, 0xf8,
    0x7f, 0x3d, 0xfe, 0x3f, 0x00,
    /* U+0037 "7" (10x13) */
    0xff, 0xff, 0xf0, 0x3c, 0x0e, 0x07, 0x81, 0xc0, 0xf0, 0x38, 0x1e, 0x07,
    0x03, 0xc0, 0xe0, 0x78, 0x00,
    /* U+0038 "8" (10x13) */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xf3, 0xdf, 0xe3, 0xf3, 0xdf, 0xe1, 0xf8,
    0x7f, 0x3f, 0xfe, 0x3f, 0x00,
    /* U+0039 "9" (10x13) */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0xff, 0xfd, 0xf7, 0x11, 0xf8,
    0xff, 0x79, 0xfe, 0x3e, 0x00,
    /* U+003A ":" (4x9) */
    0x6f, 0x60, 0x00, 0x6f, 0x60,
    /* U+003B ";" (4x13) */
    0x6f, 0x70, 0x00, 0x0f, 0xee, 0xec, 0xc0,
    /* U+003C "<" (10x10) */
    0x01, 0xc1, 0xf1, 0xfb, 0xf8, 0xf0, 0x3f, 0x07, 0xf0, 0x3f, 0x03, 0xc0,
    0x10,
    /* U+003D "=" (10x7) */
    0x7f, 0xbf, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xfc,
    /* U+003E ">" (10x10) */
    0xe0, 0x3e, 0x07, 0xe0, 0x7e, 0x03, 0xc3, 0xf3, 0xf3, 0xf0, 0xf0, 0x20,
    0x00,
    /* U+003F "?" (9x13) */
    0x7e, 0x7f, 0xb9, 0xd8, 0xf0, 0x70, 0xf8, 0x70, 0x70, 0x38, 0x00, 0x0e,
    0x07, 0x03, 0x80,
    /* U+0040 "@" (17x17) */
    0x07, 0xf0, 0x0f, 0xfe, 0x0f, 0x07, 0x8e, 0x00, 0xe6, 0x7f, 0xbf, 0x7f,
    0xdf, 0xb8, 0xe7, 0x98, 0x73, 0xcc, 0x39, 0xe6, 0x1d, 0xfb, 0x8e, 0xfd,
    0xff, 0xe7, 0x7d, 0xe3, 0xc0, 0x00, 0xf8, 0xe0, 0x3f, 0xf0, 0x03, 0xe0,
    0x00,
    /* U+0041 "A" (13x13) */
    0x0f, 0x80, 0x7e, 0x03, 0xf0, 0x3f, 0x81, 0xde, 0x0e, 0x70, 0xf3, 0x87,
    0x9e, 0x3f, 0xf3, 0xff, 0x9e, 0x1e, 0xe0, 0xff, 0x03, 0x80,
    /* U+0042 "B" (10x13) */
    0xff, 0x3f, 0xee, 0x3f, 0x8f, 0xe3, 0xbf, 0xef, 0xf3, 0x8f, 0xe1, 0xf8,
    0x7e, 0x3f, 0xfe, 0xff, 0x00,
    /* U+0043 "C" (11x13) */
    0x1f, 0x8f, 0xf9, 0xe7, 0xf8, 0x7e, 0x07, 0xc0, 0x38, 0x07, 0x00, 0xe0,
    0x7e, 0x1d, 0xef, 0xbf, 0xe1, 0xf8,
    /* U+0044 "D" (11x13) */
    0xff, 0x1f, 0xf3, 0x9f, 0x70, 0xfe, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe1,
    0xfc, 0x3b, 0xff, 0x7f, 0xcf, 0xe0,
    /* U+0045 "E" (9x13) */
    0xff, 0xff, 0xf8, 0x1c, 0x0e, 0x07, 0xfb, 0xfd, 0xfe, 0xe0, 0x70, 0x38,
    0x1f, 0xff, 0xf8,
    /* U+0046 "F" (9x13) */
    0xff, 0xff, 0xf8, 0x1c, 0x0e, 0x07, 0x03, 0xfd, 0xfe, 0xe0, 0x70, 0x38,
    0x1c, 0x0e, 0x00,
    /* U+0047 "G" (12x13) */
    0x1f, 0x87, 0xfc, 0x79, 0xef, 0x0e, 0xe0, 0x0e, 0x00, 0xe3, 0xfe, 0x3f,
    0xe0, 0xff, 0x0e, 0x79, 0xe3, 0xfc, 0x1f, 0x80,
    /* U+0048 "H" (11x13) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0e,
    /* U+0049 "I" (4x13) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+004A "J" (9x13) */
    0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0xf1, 0xfd,
    0xef, 0xe3, 0xe0,
    /* U+004B "K" (11x13) */
    0xe1, 0xfc, 0x7b, 0x9e, 0x73, 0x8e, 0xf1, 0xfc, 0x3f, 0x87, 0xf8, 0xf7,
    0x1c, 0xf3, 0x8f, 0x71, 0xee, 0x1e,
    /* U+004C "L" (10x13) */
    0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c,
    0x0f, 0xfb, 0xff, 0xff, 0xc0,
    /* U+004D "M" (14x13) */
    0xf0, 0x3f, 0xc0, 0xff, 0x87, 0xfe, 0x1f, 0xfc, 0x7f, 0xf3, 0xfe, 0xcf,
    0xfb, 0xf7, 0xef, 0xdf, 0x9e, 0x7e, 0x79, 0xf8, 0xe7, 0xe3, 0x1c,
    /* U+004E "N" (11x13) */
    0xe0, 0xfe, 0x1f, 0xc3, 0xfc, 0x7f, 0x8f, 0xf9, 0xfb, 0xbf, 0x3f, 0xe7,
    0xfc, 0x7f, 0x87, 0xf0, 0xfe, 0x0e,
    /* U+004F "O" (12x13) */
    0x1f, 0x87, 0xfc, 0x79, 0xef, 0x0f, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x7f, 0x0f, 0x7b, 0xe3, 0xfc, 0x1f, 0x80,
    /* U+0050 "P" (10x13) */
    0xff, 0x3f, 0xee, 0x7f, 0x8f, 0xe1, 0xf8, 0xff, 0xff, 0xfe, 0xfe, 0x38,
    0x0e, 0x03, 0x80, 0xe0, 0x00,
    /* U+0051 "Q" (12x14) */
    0x1f, 0x87, 0xfc, 0x79, 0xef, 0x0f, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe6, 0xff, 0x3f, 0x7b, 0xe3, 0xfc, 0x1f, 0xe0, 0x07,
    /* U+0052 "R" (10x13) */
    0xff, 0x3f, 0xee, 0x7f, 0x8f, 0xe1, 0xf8, 0xff, 0xfb, 0xfc, 0xef, 0x39,
    0xee, 0x3b, 0x8f, 0xe1, 0xc0,
    /* U+0053 "S" (11x13) */
    0x1f, 0x8f, 0xf9, 0xe7, 0xb8, 0x77, 0x80, 0xfe, 0x0f, 0xf0, 0x3f, 0x01,
    0xfe, 0x1d, 0xe7, 0xbf, 0xe1, 0xf8,
    /* U+0054 "T" (12x13) */
    0xff, 0xff, 0xff, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00,
    /* U+0055 "U" (11x13) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x3f, 0xef, 0x3f, 0xe3, 0xf0,
    /* U+0056 "V" (13x13) */
    0xf0, 0x7b, 0x83, 0xde, 0x1e, 0xf0, 0xe3, 0x8f, 0x1e, 0x78, 0xf3, 0x83,
    0xbc, 0x1d, 0xe0, 0xfe, 0x03, 0xf0, 0x1f, 0x80, 0xf8, 0x00,
    /* U+0057 "W" (19x13) */
    0xf0, 0xe1, 0xfe, 0x3c, 0x39, 0xc7, 0xcf, 0x3c, 0xf9, 0xe7, 0x9f, 0x3c,
    0x77, 0xe7, 0x0e, 0xee, 0xe1, 0xdd, 0xfc, 0x3f, 0x3f, 0x03, 0xe3, 0xe0,
    0x7c, 0x7c, 0x0f, 0x8f, 0x00, 0xe0, 0xe0,
    /* U+0058 "X" (11x13) */
    0xe0, 0xfe, 0x3d, 0xef, 0x1d, 0xc3, 0xf8, 0x3e, 0x07, 0xc0, 0xf8, 0x3f,
    0x8f, 0x71, 0xc7, 0x78, 0xfe, 0x0e,
    /* U+0059 "Y" (13x13) */
    0xf0, 0x7b, 0xc7, 0x9e, 0x3c, 0x7b, 0xc1, 0xdc, 0x0f, 0xe0, 0x3e, 0x01,
    0xf0, 0x07, 0x00, 0x38, 0x01, 0xc0, 0x0e, 0x00, 0x70, 0x00,
    /* U+005A "Z" (10x13) */
    0xff, 0xff, 0xf0, 0x7c, 0x1e, 0x0f, 0x03, 0xc1, 0xe0, 0xf0, 0x38, 0x1e,
    0x0f, 0xff, 0xff, 0xff, 0xc0,
    /* U+005B "[" (5x16) */
    0xff, 0xfd, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0xff,
    /* U+005C "" (7x16) */
    0xe1, 0xc3, 0x83, 0x87, 0x0e, 0x0c, 0x1c, 0x38, 0x70, 0x60, 0xe1, 0xc3,
    0x83, 0x87,
    /* U+005D "]" (4x16) */
    0xff, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0xff,
    /* U+005E "^" (7x6) */
    0x38, 0xf1, 0xf7, 0x6c, 0xf8, 0xc0,
    /* U+005F "_" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+0060 "`" (4x3) */
    0xe6, 0x30,
    /* U+0061 "a" (9x10) */
    0x1e, 0x3f, 0xdc, 0xe0, 0x73, 0xfb, 0xff, 0xcf, 0xc7, 0x7f, 0xbf, 0xc0,
    /* U+0062 "b" (10x13) */
    0xe0, 0x38, 0x0e, 0x03, 0xbc, 0xff, 0xbd, 0xee, 0x3f, 0x8f, 0xe3, 0xf8,
    0xff, 0x7b, 0xfe, 0xef, 0x00,
    /* U+0063 "c" (10x10) */
    0x1f, 0x0f, 0xe7, 0xbd, 0xc7, 0xf0, 0x3c, 0x07, 0x1d, 0xcf, 0x7f, 0x87,
    0xc0,
    /* U+0064 "d" (10x13) */
    0x01, 0xc0, 0x70, 0x1c, 0x77, 0x7f, 0xde, 0xf7, 0x1f, 0xc7, 0xf1, 0xfc,
    0x77, 0xbd, 0xff, 0x3d, 0xc0,
    /* U+0065 "e" (10x10) */
    0x1f, 0x0f, 0xe7, 0x3d, 0xc7, 0xff, 0xff, 0xf7, 0x01, 0xc7, 0x7f, 0x87,
    0xc0,
    /* U+0066 "f" (7x14) */
    0x1c, 0x7d, 0xf3, 0xcf, 0xdf, 0x9e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x8f,
    0x00,
    /* U+0067 "g" (10x14) */
    0x1d, 0xdf, 0xf7, 0xbd, 0xc7, 0xf1, 0xfc, 0x7f, 0x1d, 0xef, 0x7f, 0xc7,
    0x70, 0x1d, 0xcf, 0x7f, 0x87, 0xc0,
    /* U+0068 "h" (9x13) */
    0xe0, 0x70, 0x38, 0x1d, 0xef, 0xff, 0xff, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7e, 0x38,
    /* U+0069 "i" (3x14) */
    0xdf, 0x8f, 0xff, 0xff, 0xff, 0xc0,
    /* U+006A "j" (5x18) */
    0x31, 0xcc, 0x03, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xef, 0xf6, 0x00,
    /* U+006B "k" (9x13) */
    0xe0, 0x70, 0x38, 0x1c, 0x7e, 0x77, 0x7b, 0xf9, 0xf8, 0xfe, 0x7f, 0x3b,
    0xdc, 0xfe, 0x78,
    /* U+006C "l" (4x13) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+006D "m" (15x10) */
    0xee, 0x39, 0xfe, 0xfb, 0xff, 0xf7, 0x1c, 0xfe, 0x39, 0xfc, 0x73, 0xf8,
    0xe7, 0xf1, 0xcf, 0xe3, 0x9f, 0xc7, 0x3c,
    /* U+006E "n" (9x10) */
    0xef, 0x7f, 0xff, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xc0,
    /* U+006F "o" (10x10) */
    0x1f, 0x0f, 0xe7, 0xbd, 0xc7, 0xf1, 0xfc, 0x77, 0x1d, 0xcf, 0x7f, 0x87,
    0xc0,
    /* U+0070 "p" (10x14) */
    0xef, 0x3f, 0xef, 0x7b, 0x8f, 0xe3, 0xf8, 0xfe, 0x3f, 0xde, 0xff, 0xbb,
    0xce, 0x03, 0x80, 0xe0, 0x38, 0x00,
    /* U+0071 "q" (10x14) */
    0x1d, 0xdf, 0xf7, 0xbd, 0xc7, 0xf1, 0xfc, 0x7f, 0x1d, 0xef, 0x7f, 0xcf,
    0x70, 0x1c, 0x07, 0x01, 0xc0, 0x70,
    /* U+0072 "r" (6x10) */
    0xef, 0xff, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0x80,
    /* U+0073 "s" (10x10) */
    0x3e, 0x1f, 0xe7, 0x39, 0xc0, 0x7f, 0x0f, 0xe0, 0x3f, 0xcf, 0x7f, 0x8f,
    0xc0,
    /* U+0074 "t" (6x12) */
    0x79, 0xef, 0xff, 0x79, 0xe7, 0x9e, 0x79, 0xe3, 0xcf,
    /* U+0075 "u" (9x10) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xef, 0xff, 0xbd, 0xc0,
    /* U+0076 "v" (10x10) */
    0xe1, 0xfc, 0x77, 0x3d, 0xce, 0x73, 0x8e, 0xe3, 0xf0, 0xfc, 0x1f, 0x07,
    0x80,
    /* U+0077 "w" (15x10) */
    0xe3, 0x8f, 0xe7, 0x1d, 0xcf, 0x7b, 0xbe, 0xe7, 0x7d, 0xce, 0xdb, 0x8f,
    0xbe, 0x1f, 0x7c, 0x3c, 0x78, 0x78, 0xf0,
    /* U+0078 "x" (10x10) */
    0x71, 0xdc, 0xe7, 0xb8, 0xfc, 0x1f, 0x07, 0x83, 0xf0, 0xfe, 0x73, 0xbc,
    0x70,
    /* U+0079 "y" (10x14) */
    0xe1, 0xfc, 0x77, 0x3d, 0xce, 0x73, 0x8e, 0xe3, 0xf0, 0xfc, 0x1f, 0x07,
    0x81, 0xe0, 0xf0, 0x7c, 0x1c, 0x00,
    /* U+007A "z" (8x10) */
    0xff, 0xff, 0x0f, 0x1e, 0x1c, 0x3c, 0x78, 0xf0, 0xff, 0xff,
    /* U+007B "{" (7x16) */
    0x0e, 0x3c, 0xf1, 0xc3, 0x87, 0x1e, 0x78, 0xe1, 0xf0, 0xe1, 0xc3, 0x87,
    0x0f, 0x8f,
    /* U+007C "|" (3x21) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    /* U+007D "}" (6x16) */
    0xc3, 0xc7, 0x1c, 0x71, 0xc3, 0x8f, 0x1c, 0xf7, 0x9c, 0x71, 0xcf, 0x38,
    /* U+007E "~" (10x4) */
    0x79, 0xff, 0xfe, 0xfb, 0x0c,
    /* U+00B0 "" (6x6) */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0,
    /* U+00B1 "" (10x10) */
    0x0c, 0x07, 0x0f, 0xff, 0xff, 0x1e, 0x03, 0x00, 0x03, 0xff, 0xff, 0xdf,
    0xe0,
    /* U+00B2 "" (7x7) */
    0x7d, 0xdc, 0x18, 0x63, 0x8e, 0x1f, 0x80,
    /* U+00B3 "" (7x8) */
    0x7c, 0xcc, 0x38, 0xe0, 0x7c, 0xdf, 0x88,
    /* U+00B5 "" (10x14) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0xff, 0xfb,
    0x7e, 0x03, 0x80, 0xe0, 0x30, 0x00,
    /* U+00B7 "" (4x3) */
    0x6f, 0x60,
    /* U+00D7 "" (10x9) */
    0x61, 0x3c, 0xf7, 0xf8, 0xfc, 0x1e, 0x0f, 0xc7, 0xfb, 0xcf, 0x61, 0x80,
    /* U+00F7 "" (10x10) */
    0x1c, 0x07, 0x80, 0xc0, 0x00, 0xff, 0xff, 0xf0, 0x00, 0x30, 0x1e, 0x03,
    0x00,
    /* U+0394 "" (13x13) */
    0x0f, 0x80, 0x7e, 0x03, 0xf0, 0x3f, 0x81, 0xde, 0x0e, 0x70, 0xf3, 0x87,
    0x1e, 0x38, 0xf3, 0xc3, 0x9e, 0x1e, 0xff, 0xff, 0xff, 0x80,
    /* U+03A9 "" (13x13) */
    0x0f, 0xc1, 0xff, 0x1f, 0x3c, 0xf0, 0xf7, 0x03, 0xf8, 0x1f, 0xc0, 0xee,
    0x07, 0x70, 0x79, 0xc7, 0x8f, 0x3d, 0xf9, 0xff, 0xcf, 0x80,
    /* U+03B1 "" (11x10) */
    0x1c, 0xe7, 0xfd, 0xef, 0x38, 0xef, 0x1d, 0xe3, 0x9c, 0x73, 0xde, 0x7f,
    0xe7, 0xdc,
    /* U+03B2 "" (9x17) */
    0x3e, 0x7f, 0xbd, 0xfc, 0x7e, 0x3f, 0x7b, 0xbd, 0xcf, 0xe3, 0xf1, 0xfd,
    0xff, 0xff, 0xf7, 0x03, 0x81, 0xc0, 0xe0, 0x00,
    /* U+03B3 "" (9x14) */
    0xe3, 0xf9, 0xdc, 0xee, 0x67, 0x71, 0xb8, 0xf8, 0x7c, 0x1e, 0x0e, 0x07,
    0x03, 0x81, 0xc0, 0xe0,
    /* U+03B4 "" (10x14) */
    0x0e, 0x0f, 0xc7, 0xf1, 0xe0, 0x3e, 0x07, 0xc7, 0xf9, 0xcf, 0xe1, 0xf8,
    0x7f, 0x1d, 0xcf, 0x7f, 0x8f, 0xc0,
    /* U+03B5 "" (9x10) */
    0x1f, 0x3f, 0xdc, 0xee, 0x03, 0xe1, 0xf1, 0xc1, 0xe3, 0x7f, 0x9f, 0x80,
    /* U+03B8 "" (9x13) */
    0x3e, 0x3f, 0xb9, 0xdc, 0x7e, 0x3f, 0xff, 0xff, 0xff, 0xe3, 0xf1, 0xf9,
    0xcf, 0xe3, 0xe0,
    /* U+03BB "" (10x13) */
    0x78, 0x1f, 0x01, 0xc0, 0x38, 0x1e, 0x07, 0xc1, 0xf0, 0xfc, 0x3b, 0x9e,
    0xe7, 0x3d, 0xc7, 0xf1, 0xc0,
    /* U+03BC "" (10x14) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0xff, 0xfb,
    0x7e, 0x03, 0x80, 0xe0, 0x30, 0x00,
    /* U+03C0 "" (12x10) */
    0x7f, 0xff, 0xff, 0x39, 0xe3, 0x9c, 0x39, 0xc3, 0x9c, 0x39, 0xc3, 0x9e,
    0x39, 0xf3, 0x8f,
    /* U+03C3 "" (10x10) */
    0x0f, 0xcf, 0xf7, 0xfd, 0xce, 0xf3, 0xf8, 0x7f, 0x3d, 0xce, 0x7f, 0x8f,
    0xc0,
    /* U+03C4 "" (9x10) */
    0xff, 0xff, 0xcf, 0x07, 0x83, 0xc1, 0xe0, 0xf0, 0x38, 0x1e, 0x07, 0x80,
    /* U+03C6 "" (14x14) */
    0x21, 0xe1, 0xcf, 0xe7, 0x3b, 0xbc, 0xe7, 0xf3, 0x9f, 0xce, 0x77, 0x3b,
    0xdf, 0xfe, 0x3f, 0xf8, 0x7f, 0x80, 0x38, 0x00, 0xe0, 0x03, 0x80, 0x0c,
    0x00,
    /* U+03C9 "" (15x10) */
    0x38, 0x18, 0xe0, 0x39, 0xce, 0x73, 0x9c, 0xff, 0x38, 0xfe, 0x71, 0xdc,
    0xe3, 0xbb, 0xee, 0x7f, 0xfc, 0x7d, 0xf0,
    /* U+2013 "" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+2014 "" (18x2) */
    0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+2018 "" (4x6) */
    0x37, 0x77, 0xf6,
    /* U+2019 "" (4x6) */
    0x77, 0x6e, 0xe4,
    /* U+201C "" (9x6) */
    0x33, 0xb9, 0xdc, 0xee, 0xef, 0x73, 0x38,
    /* U+201D "" (9x6) */
    0x77, 0xbb, 0x99, 0xdc, 0xee, 0x62, 0x30,
    /* U+2022 "" (5x6) */
    0x77, 0xff, 0xff, 0x90,
    /* U+2026 "" (12x3) */
    0x67, 0x3f, 0x77, 0x67, 0x70,
    /* U+2030 "" (17x14) */
    0x30, 0x00, 0x3e, 0x18, 0x3b, 0x18, 0x19, 0x88, 0x0c, 0xcc, 0x03, 0xec,
    0x00, 0xe4, 0x00, 0x06, 0x00, 0x06, 0x67, 0x06, 0x7f, 0xc3, 0x66, 0x63,
    0x33, 0x33, 0x1f, 0xd9, 0x87, 0xf8,
    /* U+2190 "" (13x13) */
    0x06, 0x00, 0x78, 0x07, 0x80, 0x78, 0x07, 0x80, 0x7f, 0xff, 0xff, 0xef,
    0x00, 0x38, 0x00, 0xe0, 0x03, 0x80, 0x0e, 0x00, 0x20, 0x00,
    /* U+2191 "" (11x13) */
    0x04, 0x01, 0xc0, 0x7c, 0x1f, 0xc7, 0xfd, 0xdd, 0xf3, 0x98, 0x70, 0x0e,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0,
    /* U+2192 "" (13x13) */
    0x02, 0x00, 0x38, 0x00, 0xe0, 0x03, 0x80, 0x0e, 0x7f, 0xfb, 0xff, 0xe0,
    0x1e, 0x01, 0xe0, 0x0e, 0x00, 0xe0, 0x0e, 0x00, 0x20, 0x00,
    /* U+2193 "" (11x13) */
    0x0e, 0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x33, 0x9f, 0x77, 0x7f,
    0xc7, 0xf0, 0x7c, 0x07, 0x00, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 53, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 98, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 166, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 13, .adv_w = 182, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 183, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 246, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 191, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 97, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 99, .adv_w = 103, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 109, .adv_w = 103, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 164, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 125, .adv_w = 191, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 137, .adv_w = 101, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 140, .adv_w = 129, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 143, .adv_w = 96, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 109, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 159, .adv_w = 199, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 121, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 177, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 185, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 189, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 163, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 190, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 189, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 96, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 98, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 339, .adv_w = 191, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 191, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 361, .adv_w = 191, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 162, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 302, .box_w = 17, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 426, .adv_w = 217, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 212, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 203, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 171, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 161, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 214, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 208, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 75, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 196, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 157, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 259, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 202, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 667, .adv_w = 220, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 181, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 220, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 725, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 183, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 188, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 201, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 217, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 301, .box_w = 19, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 207, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 209, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 190, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 103, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 918, .adv_w = 109, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 932, .adv_w = 103, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 940, .adv_w = 135, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 946, .adv_w = 133, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 949, .adv_w = 130, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 951, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 177, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 165, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 993, .adv_w = 177, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1010, .adv_w = 166, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1023, .adv_w = 108, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1036, .adv_w = 177, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1054, .adv_w = 177, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1069, .adv_w = 75, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 75, .box_w = 5, .box_h = 18, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1087, .adv_w = 165, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1102, .adv_w = 75, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 261, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1128, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1140, .adv_w = 171, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1153, .adv_w = 177, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1171, .adv_w = 177, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1189, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1197, .adv_w = 159, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1210, .adv_w = 107, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 165, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1244, .adv_w = 242, .box_w = 15, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1263, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1276, .adv_w = 165, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1294, .adv_w = 161, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1304, .adv_w = 135, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1318, .adv_w = 106, .box_w = 3, .box_h = 21, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1326, .adv_w = 135, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1338, .adv_w = 191, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1343, .adv_w = 125, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1348, .adv_w = 191, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1361, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1368, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1375, .adv_w = 190, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1393, .adv_w = 96, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1395, .adv_w = 191, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1407, .adv_w = 191, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1420, .adv_w = 217, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1442, .adv_w = 219, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1464, .adv_w = 182, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1478, .adv_w = 170, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1498, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1514, .adv_w = 196, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1532, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1544, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1559, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1576, .adv_w = 190, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1594, .adv_w = 205, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1609, .adv_w = 171, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1622, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1634, .adv_w = 229, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1659, .adv_w = 244, .box_w = 15, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1678, .adv_w = 144, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1681, .adv_w = 288, .box_w = 18, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1686, .adv_w = 102, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1689, .adv_w = 102, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1692, .adv_w = 177, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1699, .adv_w = 173, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1706, .adv_w = 106, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1710, .adv_w = 220, .box_w = 12, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1715, .adv_w = 313, .box_w = 17, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1745, .adv_w = 267, .box_w = 13, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1767, .adv_w = 267, .box_w = 11, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1785, .adv_w = 267, .box_w = 13, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1807, .adv_w = 267, .box_w = 11, .box_h = 13, .ofs_x = 3, .ofs_y = 0}
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
    3, 13, 3, 15, 3, 21, 3, 34, 3, 43, 3, 104, 3, 126, 6, 121,
    6, 122, 6, 123, 6, 124, 7, 3, 7, 8, 7, 53, 7, 55, 7, 56,
    7, 58, 7, 61, 7, 87, 7, 88, 7, 90, 7, 121, 7, 123, 8, 7,
    8, 13, 8, 15, 8, 21, 8, 34, 8, 43, 8, 104, 8, 126, 9, 75,
    11, 13, 11, 15, 11, 21, 11, 34, 11, 43, 11, 64, 11, 104, 11, 126,
    12, 24, 12, 53, 12, 57, 12, 58, 13, 3, 13, 8, 13, 18, 13, 32,
    13, 58, 13, 65, 13, 122, 13, 124, 14, 57, 15, 1, 15, 3, 15, 8,
    15, 18, 15, 32, 15, 53, 15, 58, 15, 65, 15, 122, 15, 124, 16, 13,
    16, 15, 16, 43, 16, 126, 20, 13, 20, 15, 20, 126, 22, 13, 22, 15,
    22, 126, 23, 13, 23, 15, 23, 64, 23, 126, 24, 4, 24, 7, 24, 13,
    24, 15, 24, 21, 24, 24, 24, 29, 24, 34, 24, 43, 24, 64, 24, 66,
    24, 68, 24, 69, 24, 70, 24, 72, 24, 80, 24, 82, 24, 104, 24, 106,
    24, 109, 24, 110, 24, 111, 24, 115, 24, 117, 24, 118, 24, 126, 26, 13,
    26, 15, 26, 24, 26, 58, 26, 64, 26, 121, 26, 123, 26, 126, 27, 53,
    27, 55, 27, 61, 27, 121, 27, 123, 28, 55, 28, 61, 28, 121, 28, 123,
    30, 34, 30, 55, 30, 56, 30, 57, 30, 58, 30, 61, 30, 87, 30, 89,
    30, 90, 30, 121, 30, 123, 31, 24, 31, 34, 31, 53, 31, 55, 31, 56,
    31, 57, 31, 58, 31, 59, 31, 61, 31, 121, 31, 123, 32, 34, 32, 104,
    34, 3, 34, 5, 34, 8, 34, 11, 34, 18, 34, 29, 34, 30, 34, 32,
    34, 36, 34, 40, 34, 48, 34, 50, 34, 52, 34, 53, 34, 55, 34, 56,
    34, 58, 34, 61, 34, 63, 34, 68, 34, 69, 34, 70, 34, 71, 34, 72,
    34, 80, 34, 82, 34, 84, 34, 85, 34, 87, 34, 88, 34, 90, 34, 96,
    34, 97, 34, 101, 34, 106, 34, 115, 34, 117, 34, 121, 34, 122, 34, 123,
    34, 124, 37, 13, 37, 15, 37, 16, 37, 34, 37, 53, 37, 55, 37, 56,
    37, 57, 37, 58, 37, 61, 37, 64, 37, 121, 37, 123, 37, 126, 39, 13,
    39, 15, 39, 34, 39, 43, 39, 64, 39, 68, 39, 69, 39, 70, 39, 72,
    39, 80, 39, 82, 39, 86, 39, 87, 39, 90, 39, 91, 39, 100, 39, 106,
    39, 115, 39, 117, 39, 126, 40, 74, 40, 75, 41, 64, 43, 13, 43, 15,
    43, 16, 43, 64, 43, 126, 44, 29, 44, 74, 44, 88, 45, 3, 45, 8,
    45, 11, 45, 12, 45, 14, 45, 18, 45, 36, 45, 40, 45, 48, 45, 50,
    45, 53, 45, 55, 45, 56, 45, 58, 45, 61, 45, 63, 45, 85, 45, 87,
    45, 90, 45, 95, 45, 96, 45, 101, 45, 103, 45, 121, 45, 122, 45, 123,
    45, 124, 45, 130, 46, 64, 48, 13, 48, 15, 48, 16, 48, 34, 48, 53,
    48, 55, 48, 56, 48, 57, 48, 58, 48, 61, 48, 64, 48, 121, 48, 123,
    48, 126, 49, 34, 49, 43, 50, 13, 50, 15, 50, 16, 50, 34, 50, 53,
    50, 55, 50, 56, 50, 57, 50, 58, 50, 61, 50, 64, 50, 121, 50, 123,
    50, 126, 51, 55, 51, 58, 51, 61, 51, 68, 51, 69, 51, 70, 51, 72,
    51, 80, 51, 82, 51, 106, 51, 115, 51, 117, 53, 7, 53, 12, 53, 13,
    53, 14, 53, 15, 53, 16, 53, 21, 53, 27, 53, 28, 53, 29, 53, 34,
    53, 36, 53, 40, 53, 43, 53, 48, 53, 50, 53, 64, 53, 66, 53, 68,
    53, 69, 53, 70, 53, 72, 53, 78, 53, 79, 53, 80, 53, 81, 53, 82,
    53, 83, 53, 84, 53, 86, 53, 87, 53, 88, 53, 89, 53, 90, 53, 91,
    53, 95, 53, 100, 53, 101, 53, 103, 53, 106, 53, 107, 53, 115, 53, 117,
    53, 126, 53, 130, 54, 13, 54, 15, 54, 16, 54, 64, 54, 126, 55, 7,
    55, 12, 55, 13, 55, 14, 55, 15, 55, 16, 55, 21, 55, 27, 55, 28,
    55, 29, 55, 30, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 48,
    55, 50, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72, 55, 80,
    55, 82, 55, 84, 55, 95, 55, 97, 55, 101, 55, 102, 55, 103, 55, 106,
    55, 115, 55, 117, 55, 126, 55, 130, 56, 7, 56, 12, 56, 13, 56, 14,
    56, 15, 56, 16, 56, 21, 56, 27, 56, 28, 56, 29, 56, 30, 56, 34,
    56, 36, 56, 40, 56, 43, 56, 48, 56, 50, 56, 66, 56, 68, 56, 69,
    56, 70, 56, 72, 56, 78, 56, 79, 56, 80, 56, 81, 56, 82, 56, 83,
    56, 84, 56, 95, 56, 97, 56, 101, 56, 103, 56, 106, 56, 107, 56, 115,
    56, 117, 56, 126, 56, 130, 57, 12, 57, 14, 57, 29, 57, 30, 57, 36,
    57, 40, 57, 48, 57, 50, 57, 68, 57, 69, 57, 70, 57, 72, 57, 80,
    57, 82, 57, 95, 57, 97, 57, 101, 57, 103, 57, 106, 57, 115, 57, 117,
    57, 130, 58, 7, 58, 13, 58, 15, 58, 21, 58, 27, 58, 28, 58, 29,
    58, 30, 58, 34, 58, 36, 58, 40, 58, 43, 58, 48, 58, 50, 58, 66,
    58, 68, 58, 69, 58, 70, 58, 72, 58, 78, 58, 79, 58, 80, 58, 81,
    58, 82, 58, 83, 58, 84, 58, 86, 58, 97, 58, 100, 58, 102, 58, 106,
    58, 107, 58, 115, 58, 117, 58, 126, 59, 29, 59, 36, 59, 40, 59, 48,
    59, 50, 60, 75, 61, 3, 61, 8, 61, 11, 61, 13, 61, 15, 61, 18,
    61, 29, 61, 30, 61, 32, 61, 36, 61, 40, 61, 48, 61, 50, 61, 53,
    61, 55, 61, 56, 61, 58, 61, 61, 61, 63, 61, 68, 61, 69, 61, 70,
    61, 72, 61, 80, 61, 82, 61, 85, 61, 87, 61, 88, 61, 90, 61, 96,
    61, 97, 61, 101, 61, 106, 61, 108, 61, 115, 61, 117, 61, 121, 61, 122,
    61, 123, 61, 124, 61, 126, 63, 13, 63, 15, 63, 34, 63, 43, 63, 64,
    63, 104, 63, 126, 64, 11, 64, 18, 64, 21, 64, 53, 64, 55, 64, 61,
    64, 63, 64, 74, 64, 75, 64, 78, 64, 79, 64, 81, 64, 83, 64, 87,
    64, 90, 64, 96, 64, 107, 64, 108, 66, 53, 66, 55, 66, 56, 66, 58,
    66, 61, 66, 121, 66, 123, 67, 34, 67, 53, 67, 55, 67, 56, 67, 58,
    67, 61, 67, 121, 67, 123, 68, 53, 68, 55, 68, 56, 68, 58, 68, 61,
    68, 121, 68, 123, 69, 64, 70, 53, 70, 55, 70, 58, 70, 61, 70, 121,
    70, 123, 71, 12, 71, 13, 71, 14, 71, 15, 71, 21, 71, 34, 71, 43,
    71, 66, 71, 68, 71, 69, 71, 70, 71, 72, 71, 80, 71, 82, 71, 84,
    71, 95, 71, 101, 71, 102, 71, 103, 71, 106, 71, 115, 71, 117, 71, 125,
    71, 126, 71, 130, 72, 53, 72, 64, 73, 18, 73, 53, 73, 55, 73, 56,
    73, 58, 73, 61, 73, 121, 73, 123, 76, 29, 76, 53, 78, 55, 78, 56,
    78, 58, 78, 61, 79, 18, 79, 53, 79, 55, 79, 56, 79, 58, 79, 61,
    79, 121, 79, 123, 80, 10, 80, 34, 80, 53, 80, 55, 80, 56, 80, 57,
    80, 58, 80, 61, 80, 62, 80, 87, 80, 88, 80, 89, 80, 90, 80, 94,
    80, 121, 80, 123, 81, 34, 81, 53, 81, 55, 81, 56, 81, 58, 81, 61,
    81, 121, 81, 123, 82, 53, 82, 64, 83, 13, 83, 15, 83, 43, 83, 53,
    83, 71, 83, 85, 83, 122, 83, 124, 83, 126, 84, 53, 84, 55, 84, 56,
    84, 58, 84, 61, 84, 121, 84, 123, 85, 12, 85, 14, 85, 29, 85, 53,
    85, 95, 85, 101, 85, 103, 85, 121, 85, 123, 85, 130, 86, 53, 86, 58,
    86, 121, 86, 123, 87, 16, 87, 34, 87, 43, 87, 64, 87, 122, 87, 124,
    88, 13, 88, 15, 88, 34, 88, 43, 88, 53, 88, 122, 88, 124, 88, 126,
    90, 16, 90, 34, 90, 43, 90, 64, 90, 122, 90, 124, 91, 53, 92, 75,
    95, 24, 95, 53, 95, 57, 95, 58, 96, 7, 96, 13, 96, 15, 96, 21,
    96, 34, 96, 43, 96, 64, 96, 104, 96, 126, 97, 34, 97, 55, 97, 56,
    97, 57, 97, 58, 97, 61, 97, 87, 97, 89, 97, 90, 97, 121, 97, 123,
    99, 13, 99, 15, 99, 21, 99, 34, 99, 43, 99, 104, 99, 126, 100, 16,
    100, 29, 100, 53, 100, 58, 100, 64, 100, 104, 100, 121, 100, 123, 101, 34,
    101, 43, 101, 57, 101, 58, 102, 53, 102, 55, 102, 58, 102, 61, 103, 24,
    103, 53, 103, 57, 103, 58, 104, 3, 104, 8, 104, 11, 104, 18, 104, 32,
    104, 63, 104, 96, 104, 108, 104, 109, 104, 111, 104, 116, 104, 118, 104, 121,
    104, 122, 104, 123, 104, 124, 106, 121, 106, 122, 106, 123, 106, 124, 107, 121,
    107, 123, 108, 12, 108, 13, 108, 14, 108, 15, 108, 16, 108, 29, 108, 64,
    108, 95, 108, 101, 108, 103, 108, 104, 108, 112, 108, 121, 108, 123, 108, 126,
    108, 130, 109, 121, 109, 123, 111, 121, 111, 123, 112, 12, 112, 14, 112, 18,
    112, 95, 112, 101, 112, 103, 112, 108, 112, 109, 112, 110, 112, 114, 112, 116,
    112, 118, 112, 130, 114, 109, 114, 121, 114, 123, 115, 13, 115, 15, 115, 16,
    115, 104, 115, 112, 115, 121, 115, 123, 115, 126, 117, 53, 117, 55, 117, 56,
    117, 58, 117, 61, 117, 121, 117, 123, 118, 121, 118, 123, 121, 7, 121, 13,
    121, 15, 121, 16, 121, 21, 121, 34, 121, 43, 121, 104, 121, 126, 122, 4,
    122, 7, 122, 13, 122, 15, 122, 16, 122, 21, 122, 27, 122, 28, 122, 29,
    122, 30, 122, 33, 122, 34, 122, 43, 122, 66, 122, 68, 122, 69, 122, 70,
    122, 72, 122, 80, 122, 82, 122, 84, 122, 85, 122, 87, 122, 90, 122, 97,
    122, 104, 122, 106, 122, 109, 122, 110, 122, 111, 122, 115, 122, 117, 122, 118,
    122, 126, 123, 7, 123, 13, 123, 15, 123, 16, 123, 21, 123, 34, 123, 43,
    123, 104, 123, 126, 124, 4, 124, 7, 124, 12, 124, 13, 124, 14, 124, 15,
    124, 16, 124, 17, 124, 21, 124, 23, 124, 25, 124, 27, 124, 28, 124, 29,
    124, 30, 124, 33, 124, 34, 124, 43, 124, 64, 124, 66, 124, 68, 124, 69,
    124, 70, 124, 72, 124, 78, 124, 79, 124, 80, 124, 81, 124, 82, 124, 83,
    124, 84, 124, 86, 124, 95, 124, 97, 124, 100, 124, 101, 124, 103, 124, 104,
    124, 106, 124, 107, 124, 109, 124, 110, 124, 111, 124, 115, 124, 117, 124, 118,
    124, 126, 124, 130, 126, 1, 126, 3, 126, 8, 126, 17, 126, 18, 126, 20,
    126, 23, 126, 24, 126, 25, 126, 32, 126, 53, 126, 58, 126, 65, 126, 122,
    126, 124, 128, 19, 128, 24, 128, 53, 128, 55, 128, 56, 128, 57, 128, 58,
    128, 61, 128, 89, 128, 121, 128, 123,
};

static const int8_t kern_pair_values[] = {
    -26, -26, -18, -23, -47, -23, -26, -18, -20, -18, -20, -10, -10, -16, -18, -11,
    -21, -18, -10, -10, -10, -26, -26, -10, -26, -26, -18, -23, -47, -23, -26, 3,
    -39, -39, -13, -28, -28, -20, -23, -39, -8, -8, -12, -9, -29, -29, -26, -30,
    -20, -39, -29, -29, -12, -10, -29, -29, -26, -30, -10, -20, -39, -29, -29, -11,
    -11, -18, -11, -6, -6, -6, -6, -6, -6, -9, -9, -13, -9, -16, -13, -36,
    -36, -17, 6, -26, -31, -28, -46, -13, -15, -15, -15, -15, -15, -15, -31, -15,
    -15, -15, -15, -15, -15, -15, -36, -8, -8, -6, -10, -13, -13, -13, -8, -10,
    -18, -18, -13, -13, -18, -18, -13, -13, -15, -20, -18, -15, -28, -20, -11, -10,
    -11, -16, -16, -21, -12, -23, -21, -21, -16, -26, -18, -21, -28, -28, -18, -18,
    -23, -5, -23, -28, -10, -12, -15, -18, -11, -11, -11, -11, -5, -26, -26, -21,
    -21, -26, -28, -7, -7, -7, -3, -7, -7, -7, -4, -10, -20, -20, -20, -28,
    -15, -10, -7, -7, -7, -38, -29, -38, -29, -13, -13, -11, -11, -9, -12, -8,
    -10, -13, -12, -11, -10, -10, -13, -11, -11, -26, -20, -10, -11, -11, -11, -11,
    -11, -11, -10, -10, -10, -10, -10, -11, -11, -11, -11, 10, 10, 10, -10, -10,
    -16, -15, -10, -20, 10, -18, -26, -26, -38, -10, -10, -13, -8, -8, -8, -8,
    -26, -22, -12, -27, -22, -38, -6, -20, -20, -10, -38, -10, -10, -24, -11, -24,
    -11, -10, 10, -13, -13, -11, -11, -9, -12, -8, -10, -13, -12, -11, -10, -10,
    -13, -24, -28, -13, -13, -11, -11, -9, -12, -8, -10, -13, -12, -11, -10, -10,
    -13, -6, -9, -6, -3, -3, -3, -3, -3, -3, -3, -3, -3, -10, -8, -10,
    -8, -10, -23, -20, -10, -10, -23, -26, -9, -9, -26, -9, -9, -16, -21, -22,
    -22, -22, -22, -16, -16, -22, -16, -22, -16, -21, -21, -18, -18, -8, -18, -13,
    -8, -21, -8, -8, -22, -16, -22, -22, -10, -8, -10, -10, -16, -15, -10, -15,
    -6, -28, -6, -28, -19, -10, -18, -18, -21, -18, -10, -26, -12, -12, -28, -12,
    -12, -23, -17, -18, -18, -18, -18, -18, -18, -13, -6, -18, -6, -11, -6, -18,
    -18, -18, -28, -6, -15, -6, -28, -6, -28, -10, -10, -15, -15, -21, -18, -21,
    -8, -8, -18, -8, -8, -17, -14, -14, -14, -14, -10, -10, -14, -10, -14, -10,
    -10, -6, -18, -6, -6, -14, -10, -14, -14, -28, -6, -12, -12, -16, -15, -10,
    -10, -10, -10, -8, -8, -8, -8, -8, -8, -12, -15, -12, -12, -8, -8, -8,
    -12, -18, -20, -20, -20, -18, -18, -29, -28, -21, -13, -13, -10, -13, -13, -30,
    -33, -33, -33, -33, -11, -11, -33, -11, -33, -11, -20, -11, -28, -11, -13, -33,
    -11, -33, -33, -20, -18, -10, -10, -10, -10, 3, -23, -23, -28, 11, 11, -10,
    -12, -15, -18, -11, -11, -11, -11, -26, -26, -21, -21, -26, -28, -7, -7, -7,
    -7, -7, -7, -10, -20, -20, -20, -28, -15, -10, -7, -15, -7, -7, -38, -29,
    -38, -29, 11, -39, -39, -28, -28, -20, -23, -39, -20, -31, -16, -16, -23, -23,
    -20, 10, 28, 13, 13, 13, 13, -23, -23, -20, 13, -16, -13, -15, -15, -29,
    -15, -13, -13, -10, -22, -18, -14, -34, -18, -18, -18, -22, -18, -14, -34, -18,
    -18, -18, 10, -22, -18, -34, -18, -18, -18, -6, -16, -6, -16, -18, -10, -18,
    -6, -5, -5, -5, -5, -5, -5, -5, -6, -6, -5, -6, -5, -5, -5, -5,
    -16, -6, -15, 10, -11, -13, -15, -15, -29, -15, -13, -13, -24, -16, -15, -15,
    -29, -15, -11, -13, -15, -15, -29, -15, -13, -13, -4, -10, -22, -18, -14, -8,
    -34, -18, -4, -5, -4, -6, -5, -4, -18, -18, -10, -22, -18, -14, -34, -18,
    -18, -18, -15, 10, -18, -18, -16, -16, 8, 8, 5, 5, -18, -21, -13, -10,
    -21, -13, -15, -15, -5, -5, -8, -10, -5, -5, -5, -11, -11, -5, -15, -16,
    -11, -11, -16, -20, -18, -23, 9, 9, -21, -21, -20, -16, -15, 12, 12, -21,
    -16, -20, -18, -23, 9, 9, -10, 3, -8, -8, -12, -9, -10, -39, -39, -13,
    -28, -28, -20, -23, -39, -15, -20, -18, -15, -28, -20, -11, -10, -11, -16, -16,
    -31, -31, -16, -26, -33, -26, -31, -10, -11, -15, -16, -10, -11, -11, -11, -10,
    -13, -12, -9, -16, -11, -13, -11, -8, -8, -12, -9, -28, -28, -23, -10, -18,
    -23, -23, -20, -10, -11, -15, -10, -39, -28, -39, -28, -15, 10, -15, 10, -18,
    -18, -4, -21, -4, -21, -10, -11, -11, -4, -4, -4, -20, -11, -18, -18, -21,
    -4, -18, -18, -18, -18, -4, -4, -16, -4, -4, -4, -16, -11, -4, -20, -28,
    -11, -4, -10, -11, -11, -21, -21, -10, -11, -20, -11, -11, -21, -22, -18, -14,
    -34, -18, -18, -18, -18, -18, -18, -31, -31, -28, -18, -28, -42, -28, -31, -36,
    -20, -38, -38, -41, -28, -16, -16, -28, -16, -16, -39, -36, -16, -18, -18, -18,
    -18, -18, -18, -20, 5, 6, 6, -16, -38, -18, -18, -18, -20, -18, -18, -18,
    -38, -18, -31, -31, -28, -18, -28, -42, -28, -31, -36, -20, -7, -38, -7, -38,
    -41, -13, -28, -13, -11, -16, -16, -28, -16, -16, -39, -36, -11, -16, -18, -18,
    -18, -18, -6, -6, -18, -6, -18, -6, -20, -11, -7, -16, -11, -7, -7, -38,
    -18, -6, -18, -18, -20, -18, -18, -18, -38, -7, -10, -29, -29, -8, -26, -6,
    -8, -8, -8, -30, -10, -20, -39, -29, -29, -6, -8, -8, -6, -6, -12, -9,
    -6, -6, -7, -7,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 964,
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

const lv_font_t humid1_font_inter_tight_bold_18 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 23,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 13,
    .x_height = 10,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -3,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_18,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_INTER_TIGHT_BOLD_18 */
