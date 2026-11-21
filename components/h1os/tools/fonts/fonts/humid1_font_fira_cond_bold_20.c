/*******************************************************************************
 * Font: humid1_font_fira_cond_bold_20 (fira_cond bold)
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

#ifndef HUMID1_FONT_FIRA_COND_BOLD_20
#define HUMID1_FONT_FIRA_COND_BOLD_20 1
#endif

#if HUMID1_FONT_FIRA_COND_BOLD_20

extern const lv_font_t humid1_font_fira_sans_bold_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x14) */
    0xf7, 0x77, 0x77, 0x77, 0x70, 0x67, 0x76,
    /* U+0022 "" (7x6) */
    0xef, 0xdf, 0xbf, 0x7e, 0xf9, 0xc0,
    /* U+0023 "#" (10x14) */
    0x39, 0xce, 0x63, 0x99, 0xff, 0x7f, 0xdf, 0xf3, 0xb8, 0xce, 0x73, 0xbf,
    0xef, 0xf9, 0xfe, 0x77, 0x1d, 0xc0,
    /* U+0024 "$" (10x20) */
    0x0c, 0x03, 0x00, 0xc0, 0xfc, 0x7f, 0x9c, 0x47, 0x01, 0xe0, 0x7e, 0x0f,
    0xe0, 0xf8, 0x0f, 0x03, 0xd8, 0xff, 0xf9, 0xfc, 0x1e, 0x03, 0x00, 0xc0,
    0x30,
    /* U+0025 "%" (14x14) */
    0x78, 0x33, 0xf1, 0xcf, 0xce, 0x33, 0x38, 0xcd, 0xc3, 0xf6, 0x0f, 0xb8,
    0x01, 0xde, 0x07, 0xfc, 0x3b, 0x31, 0xcc, 0xc7, 0x3f, 0x38, 0xfc, 0xc1,
    0xe0,
    /* U+0026 "&" (12x14) */
    0x3e, 0x07, 0xf0, 0x7f, 0x87, 0x38, 0x77, 0x87, 0xf0, 0x3e, 0x07, 0xe7,
    0xff, 0x7f, 0x7e, 0xf3, 0xef, 0xff, 0x7f, 0xf3, 0xe6,
    /* U+0027 "'" (3x6) */
    0xff, 0xff, 0xc0,
    /* U+0028 "(" (6x20) */
    0x18, 0x73, 0x8e, 0x71, 0xc7, 0x3c, 0xf3, 0xcf, 0x3c, 0xf1, 0xc7, 0x1c,
    0x38, 0xe1, 0xc6,
    /* U+0029 ")" (6x20) */
    0x63, 0x87, 0x1e, 0x38, 0xe3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0x8e,
    0x79, 0xce, 0x18,
    /* U+002A "" (8x8) */
    0x1c, 0x18, 0x7f, 0xff, 0x7e, 0x3e, 0x7e, 0x26,
    /* U+002B "+" (8x9) */
    0x38, 0x38, 0x38, 0xff, 0xff, 0xff, 0x38, 0x38, 0x38,
    /* U+002C "," (4x7) */
    0x6f, 0x77, 0x66, 0x40,
    /* U+002D "-" (6x3) */
    0xfb, 0xff, 0xc0,
    /* U+002E "." (4x4) */
    0x7f, 0xf7,
    /* U+002F "/" (7x18) */
    0x0e, 0x1c, 0x38, 0xf1, 0xc3, 0x87, 0x1e, 0x38, 0x70, 0xe3, 0xc7, 0x0e,
    0x1c, 0x78, 0xe1, 0xc0,
    /* U+0030 "0" (9x14) */
    0x3e, 0x3f, 0xbf, 0xfe, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xfc,
    0xff, 0xf7, 0xf1, 0xf0,
    /* U+0031 "1" (7x14) */
    0x0e, 0x7d, 0xff, 0xf4, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1,
    0xc0,
    /* U+0032 "2" (9x14) */
    0x3e, 0x3f, 0xbf, 0xe8, 0xf0, 0x78, 0x3c, 0x3c, 0x1e, 0x1e, 0x1e, 0x1e,
    0x0f, 0xff, 0xff, 0xfc,
    /* U+0033 "3" (9x14) */
    0x3e, 0x7f, 0x9f, 0xe0, 0xf0, 0x78, 0xf8, 0x78, 0x3e, 0x07, 0x81, 0xc1,
    0xff, 0xff, 0xf1, 0xf0,
    /* U+0034 "4" (10x14) */
    0x1c, 0x07, 0x01, 0xc0, 0xf0, 0x38, 0x0e, 0xe7, 0xb9, 0xce, 0x7f, 0xff,
    0xff, 0xfc, 0x0e, 0x03, 0x80, 0xe0,
    /* U+0035 "5" (9x14) */
    0xff, 0x7f, 0xbf, 0x9c, 0x0e, 0xc7, 0xf3, 0xfd, 0x9e, 0x07, 0x83, 0xc1,
    0xdf, 0xef, 0xe3, 0xe0,
    /* U+0036 "6" (9x14) */
    0x1e, 0x1f, 0x9f, 0x9e, 0x0e, 0x07, 0xfb, 0xff, 0xef, 0xe3, 0xf1, 0xfc,
    0xff, 0xf7, 0xf1, 0xf0,
    /* U+0037 "7" (8x14) */
    0xff, 0xff, 0x0f, 0x07, 0x0f, 0x0e, 0x1e, 0x1c, 0x1c, 0x3c, 0x38, 0x78,
    0x78, 0x10,
    /* U+0038 "8" (10x14) */
    0x1f, 0x0f, 0xe7, 0xfd, 0xc7, 0x73, 0xde, 0xe3, 0xf0, 0xfe, 0x73, 0xfc,
    0x7f, 0x1d, 0xff, 0x7f, 0x87, 0xc0,
    /* U+0039 "9" (10x15) */
    0x1e, 0x0f, 0xe7, 0xf9, 0xcf, 0xf1, 0xfc, 0x77, 0x3d, 0xff, 0x3f, 0xc0,
    0xe0, 0x78, 0x3c, 0x7e, 0x0f, 0x02, 0x00,
    /* U+003A ":" (4x11) */
    0x7f, 0xf7, 0x00, 0x07, 0xff, 0x70,
    /* U+003B ";" (4x15) */
    0x67, 0x76, 0x00, 0x00, 0x6f, 0x77, 0x66, 0x40,
    /* U+003C "<" (9x9) */
    0x03, 0x0f, 0xdf, 0x9f, 0x0f, 0x07, 0xe0, 0xfc, 0x1f, 0x03, 0x00,
    /* U+003D "=" (8x7) */
    0xfe, 0xff, 0xff, 0x00, 0xfe, 0xff, 0xff,
    /* U+003E ">" (8x9) */
    0xe0, 0xf8, 0x7e, 0x1f, 0x07, 0x3f, 0xfe, 0xf0, 0xc0,
    /* U+003F "?" (8x14) */
    0x7c, 0xfe, 0xff, 0x0f, 0x0e, 0x3e, 0x38, 0x38, 0x00, 0x00, 0x30, 0x78,
    0x78, 0x30,
    /* U+0040 "@" (17x18) */
    0x03, 0xf0, 0x07, 0xfc, 0x0f, 0xff, 0x87, 0x3d, 0xc7, 0x7f, 0x77, 0x3f,
    0xbb, 0x99, 0xcf, 0xdc, 0xe7, 0xee, 0x73, 0xf7, 0x39, 0xfb, 0x9d, 0xdc,
    0xff, 0xee, 0x7f, 0xe3, 0x9c, 0xe1, 0xe0, 0x00, 0x7f, 0xe0, 0x1f, 0xf8,
    0x03, 0xf8, 0x00,
    /* U+0041 "A" (11x14) */
    0x1f, 0x03, 0xe0, 0x7c, 0x1f, 0xc3, 0xb8, 0x77, 0x0e, 0xe3, 0xde, 0x7f,
    0xcf, 0xf9, 0xff, 0x78, 0xff, 0x1f, 0xc3, 0xc0,
    /* U+0042 "B" (10x14) */
    0xfe, 0x3f, 0xef, 0xfb, 0xce, 0xf3, 0xbf, 0xef, 0xf3, 0xfe, 0xf3, 0xfc,
    0xff, 0x3f, 0xff, 0xff, 0xbf, 0xc0,
    /* U+0043 "C" (9x14) */
    0x1f, 0x3f, 0xdf, 0xfe, 0x0f, 0x07, 0x03, 0x81, 0xc0, 0xe0, 0x78, 0x3c,
    0x0f, 0xf7, 0xf8, 0xf8,
    /* U+0044 "D" (11x14) */
    0xfe, 0x1f, 0xf3, 0xff, 0x79, 0xef, 0x3d, 0xe3, 0xbc, 0x7f, 0x8f, 0xf1,
    0xde, 0x7b, 0xcf, 0x7f, 0xef, 0xf9, 0xfc, 0x00,
    /* U+0045 "E" (8x14) */
    0xff, 0xff, 0xff, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xf0, 0xf0, 0xf0, 0xff,
    0xff, 0xff,
    /* U+0046 "F" (8x14) */
    0xff, 0xff, 0xfe, 0xf0, 0xf0, 0xf0, 0xfe, 0xfe, 0xfe, 0xf0, 0xf0, 0xf0,
    0xf0, 0xf0,
    /* U+0047 "G" (11x14) */
    0x0f, 0x83, 0xfc, 0xff, 0x3c, 0x07, 0x80, 0xe3, 0xdc, 0xff, 0x9f, 0x70,
    0xee, 0x1d, 0xe3, 0xbf, 0xf3, 0xfe, 0x1f, 0x00,
    /* U+0048 "H" (10x14) */
    0xf3, 0xfc, 0xff, 0x3f, 0xcf, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xfc,
    0xff, 0x3f, 0xcf, 0xf3, 0xfc, 0xf0,
    /* U+0049 "I" (4x14) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+004A "J" (5x17) */
    0x7b, 0xde, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xf7, 0xbf, 0xfe, 0xe0,
    /* U+004B "K" (11x14) */
    0xf1, 0xfe, 0x7b, 0xcf, 0x7b, 0xcf, 0x71, 0xfe, 0x3f, 0xc7, 0xf8, 0xff,
    0x9e, 0xf3, 0xdf, 0x79, 0xef, 0x3f, 0xe3, 0xc0,
    /* U+004C "L" (8x14) */
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xff,
    0xff, 0xff,
    /* U+004D "M" (13x14) */
    0xf8, 0xf7, 0xcf, 0xbe, 0x7d, 0xf3, 0xef, 0x9f, 0x7e, 0xfb, 0xb7, 0xdd,
    0xbf, 0xef, 0x7f, 0x79, 0xfb, 0xcf, 0xde, 0x7e, 0x03, 0xf0, 0x1c,
    /* U+004E "N" (10x14) */
    0xf9, 0xfe, 0x7f, 0x9f, 0xe7, 0xfd, 0xff, 0x7f, 0xdf, 0xbf, 0xef, 0xfb,
    0xfe, 0xff, 0x9f, 0xe7, 0xf9, 0xf0,
    /* U+004F "O" (11x14) */
    0x1f, 0x0f, 0xf1, 0xff, 0x78, 0xfe, 0x1f, 0xc3, 0xf8, 0x7f, 0x0f, 0xe1,
    0xfc, 0x3f, 0xc7, 0xbf, 0xe7, 0xf8, 0x3e, 0x00,
    /* U+0050 "P" (10x14) */
    0xfe, 0x3f, 0xef, 0xfb, 0xcf, 0xf3, 0xfc, 0xff, 0x7f, 0xfe, 0xff, 0x3f,
    0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x00,
    /* U+0051 "Q" (12x16) */
    0x1f, 0x07, 0xf8, 0x7f, 0xcf, 0x1e, 0xe1, 0xee, 0x1e, 0xe1, 0xee, 0x1e,
    0xe1, 0xee, 0x1e, 0xf1, 0xc7, 0xfc, 0x7f, 0x81, 0xfe, 0x01, 0xf0, 0x06,
    /* U+0052 "R" (10x14) */
    0xfe, 0x3f, 0xef, 0xfb, 0xcf, 0xf3, 0xfc, 0xff, 0xfb, 0xfe, 0xff, 0x3f,
    0xcf, 0x7b, 0xde, 0xf3, 0xfc, 0xf0,
    /* U+0053 "S" (10x14) */
    0x1f, 0x1f, 0xf7, 0xf9, 0xc0, 0x78, 0x1f, 0x83, 0xf8, 0x7f, 0x07, 0xc0,
    0xf0, 0x3d, 0xff, 0xff, 0x8f, 0xc0,
    /* U+0054 "T" (10x14) */
    0xff, 0xff, 0xf7, 0xf8, 0x78, 0x1e, 0x07, 0x81, 0xe0, 0x78, 0x1e, 0x07,
    0x81, 0xe0, 0x78, 0x1e, 0x07, 0x80,
    /* U+0055 "U" (10x14) */
    0xe3, 0xf8, 0xfe, 0x3f, 0x8f, 0xe3, 0xf8, 0xfe, 0x3f, 0x8f, 0xe3, 0xf8,
    0xff, 0x3f, 0xff, 0x7f, 0x8f, 0xc0,
    /* U+0056 "V" (11x14) */
    0xe1, 0xfe, 0x3f, 0xc7, 0x78, 0xe7, 0x1c, 0xe7, 0x9e, 0xe3, 0xdc, 0x3b,
    0x87, 0x70, 0xfe, 0x1f, 0x81, 0xf0, 0x3e, 0x00,
    /* U+0057 "W" (15x14) */
    0xf3, 0xcf, 0xe7, 0x9f, 0xcf, 0x3b, 0x9e, 0x77, 0x7c, 0xee, 0xf9, 0xdd,
    0xb7, 0xbb, 0x7e, 0x76, 0xfc, 0xfd, 0xf9, 0xf9, 0xf1, 0xf3, 0xe3, 0xe7,
    0xc7, 0xcf, 0x80,
    /* U+0058 "X" (11x14) */
    0xf1, 0xee, 0x79, 0xef, 0x1d, 0xc3, 0xf0, 0x3e, 0x07, 0xc0, 0xf8, 0x3f,
    0x07, 0xf1, 0xee, 0x39, 0xe7, 0x1d, 0xe3, 0xc0,
    /* U+0059 "Y" (11x14) */
    0xf1, 0xfe, 0x3d, 0xc7, 0x3d, 0xe3, 0xb8, 0x7f, 0x07, 0xc0, 0xf8, 0x0f,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x00,
    /* U+005A "Z" (10x14) */
    0x7f, 0xdf, 0xf7, 0xfc, 0x1e, 0x0f, 0x03, 0xc1, 0xe0, 0x78, 0x3c, 0x1f,
    0x07, 0x83, 0xfe, 0xff, 0xff, 0xe0,
    /* U+005B "[" (6x19) */
    0xff, 0xff, 0xbc, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xfb, 0xff, 0xc0,
    /* U+005C "" (7x18) */
    0xe1, 0xc1, 0xc3, 0x87, 0x0e, 0x1e, 0x1c, 0x38, 0x70, 0xf0, 0xe1, 0xc3,
    0x87, 0x87, 0x0e, 0x1c,
    /* U+005D "]" (6x19) */
    0xff, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x3f, 0xff, 0xc0,
    /* U+005E "^" (10x6) */
    0x1e, 0x07, 0xc3, 0xf1, 0xee, 0x73, 0xbc, 0x70,
    /* U+005F "_" (9x3) */
    0x7f, 0xff, 0xff, 0xe0,
    /* U+0060 "`" (5x3) */
    0xe7, 0x8e,
    /* U+0061 "a" (9x11) */
    0x3e, 0x3f, 0xcf, 0xe0, 0x73, 0xfb, 0xff, 0xcf, 0xe7, 0xff, 0xbf, 0xce,
    0x60,
    /* U+0062 "b" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xf7, 0xfb, 0xff, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7f, 0xff, 0xfb, 0xb8,
    /* U+0063 "c" (9x11) */
    0x1f, 0x1f, 0xdf, 0xce, 0x07, 0x07, 0x83, 0xc0, 0xe0, 0x7f, 0x1f, 0xc7,
    0xc0,
    /* U+0064 "d" (10x15) */
    0x01, 0xc0, 0x70, 0x1c, 0x07, 0x1f, 0xcf, 0xf7, 0xfd, 0xc7, 0x71, 0xfc,
    0x77, 0x1d, 0xc7, 0x7f, 0xdf, 0xf3, 0xdc,
    /* U+0065 "e" (10x11) */
    0x1e, 0x0f, 0xe7, 0xf9, 0xcf, 0x7f, 0xff, 0xf7, 0x01, 0xc0, 0x7f, 0x8f,
    0xe1, 0xf0,
    /* U+0066 "f" (8x15) */
    0x1f, 0x3f, 0x7e, 0x78, 0xfe, 0xfe, 0xfc, 0x78, 0x78, 0x78, 0x78, 0x78,
    0x78, 0x78, 0x78,
    /* U+0067 "g" (10x16) */
    0x00, 0xc7, 0xf7, 0xf9, 0xfe, 0xf3, 0xbc, 0xe7, 0xf8, 0xfc, 0x70, 0x1f,
    0x07, 0xf8, 0xff, 0x03, 0xfc, 0xff, 0xf8, 0xfc,
    /* U+0068 "h" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xf7, 0xfb, 0xff, 0xef, 0xe7, 0xf3, 0xf9,
    0xfc, 0xfe, 0x7f, 0x3f, 0x9e,
    /* U+0069 "i" (3x17) */
    0xff, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xe0,
    /* U+006A "j" (5x21) */
    0x39, 0xce, 0x70, 0x00, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x3b, 0xff,
    0xe4, 0x00,
    /* U+006B "k" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x3f, 0x3f, 0x9d, 0xde, 0xfe, 0x7f, 0x3b,
    0xdd, 0xee, 0x7f, 0x3f, 0x8e,
    /* U+006C "l" (4x15) */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xff, 0x70,
    /* U+006D "m" (13x11) */
    0xee, 0x77, 0xff, 0xff, 0xef, 0xce, 0x7e, 0x73, 0xf3, 0x9f, 0x9c, 0xfc,
    0xe7, 0xe7, 0x3f, 0x39, 0xf9, 0xce,
    /* U+006E "n" (9x11) */
    0xef, 0x7f, 0xbd, 0xfc, 0xfe, 0x7f, 0x3f, 0x9f, 0xcf, 0xe7, 0xf3, 0xf9,
    0xe0,
    /* U+006F "o" (10x11) */
    0x1f, 0x0f, 0xe7, 0xfd, 0xcf, 0xf1, 0xfc, 0x7f, 0x1d, 0xcf, 0x7f, 0xcf,
    0xe1, 0xf0,
    /* U+0070 "p" (9x15) */
    0xef, 0x7f, 0xbf, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xff, 0xff, 0xbb,
    0x9c, 0x0e, 0x07, 0x03, 0x80,
    /* U+0071 "q" (10x15) */
    0x1d, 0xcf, 0xf7, 0xfd, 0xc7, 0x71, 0xfc, 0x77, 0x1d, 0xc7, 0x7f, 0xdf,
    0xf3, 0xdc, 0x07, 0x01, 0xc0, 0x70, 0x1c,
    /* U+0072 "r" (6x11) */
    0xef, 0xff, 0xfc, 0xf3, 0x8e, 0x38, 0xe3, 0x8e, 0x00,
    /* U+0073 "s" (9x11) */
    0x3e, 0x3f, 0x9f, 0xde, 0x07, 0xc1, 0xf8, 0x3c, 0x0f, 0x7f, 0x7f, 0x8f,
    0x80,
    /* U+0074 "t" (7x14) */
    0x10, 0xf1, 0xe7, 0xff, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xe3, 0xe3, 0xe3,
    0xc0,
    /* U+0075 "u" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0x77,
    /* U+0076 "v" (10x11) */
    0xf3, 0xfc, 0xef, 0x39, 0xce, 0x77, 0x9d, 0xc7, 0xf0, 0xfc, 0x3f, 0x0f,
    0x81, 0xe0,
    /* U+0077 "w" (14x11) */
    0xe7, 0x9f, 0xde, 0xff, 0x7b, 0xdd, 0xee, 0x77, 0xb9, 0xde, 0xe7, 0xff,
    0x9f, 0x3e, 0x7c, 0xf0, 0xf3, 0xc3, 0xcf, 0x00,
    /* U+0078 "x" (10x11) */
    0xf3, 0x9d, 0xe7, 0xf0, 0xfc, 0x3e, 0x0f, 0x83, 0xf1, 0xfc, 0x77, 0xbc,
    0xef, 0x3c,
    /* U+0079 "y" (10x15) */
    0xe3, 0xfc, 0xef, 0x39, 0xce, 0x73, 0x9d, 0xc7, 0x70, 0xfc, 0x3f, 0x0f,
    0x83, 0xe0, 0x78, 0x3c, 0x1e, 0x07, 0x00,
    /* U+007A "z" (8x11) */
    0x7f, 0x7f, 0x7f, 0x0e, 0x1e, 0x3c, 0x38, 0x78, 0xff, 0xff, 0xff,
    /* U+007B "{" (6x19) */
    0x3d, 0xf7, 0x9c, 0x71, 0xc7, 0x1c, 0xf3, 0x8f, 0x1c, 0x71, 0xc7, 0x1c,
    0x78, 0xf1, 0xc0,
    /* U+007C "|" (3x18) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (6x19) */
    0xf3, 0xc7, 0x9e, 0x79, 0xe7, 0x8e, 0x3c, 0x73, 0x9e, 0x79, 0xe7, 0x9e,
    0x7b, 0xce, 0x00,
    /* U+007E "~" (8x3) */
    0xff, 0xff, 0x8e,
    /* U+00B0 "" (6x7) */
    0x7b, 0xff, 0xf3, 0xff, 0xf7, 0x80,
    /* U+00B1 "" (8x13) */
    0x38, 0x38, 0x38, 0xff, 0xff, 0xff, 0x38, 0x38, 0x38, 0x00, 0xff, 0xff,
    0xff,
    /* U+00B2 "" (6x9) */
    0x73, 0xe1, 0xc6, 0x39, 0xcf, 0xbf, 0xfc,
    /* U+00B3 "" (6x9) */
    0x73, 0xe1, 0x8e, 0x78, 0x7f, 0xfe, 0x70,
    /* U+00B5 "" (9x15) */
    0xe7, 0xf3, 0xf9, 0xfc, 0xfe, 0x7f, 0x3f, 0x9f, 0xcf, 0xff, 0xff, 0xff,
    0xfc, 0x0e, 0x07, 0x03, 0x80,
    /* U+00B7 "" (4x4) */
    0x7f, 0xf7,
    /* U+00D7 "" (8x8) */
    0x46, 0xef, 0x7e, 0x3c, 0x7c, 0xfe, 0xe6, 0x44,
    /* U+00F7 "" (8x14) */
    0x38, 0x3c, 0x3c, 0x38, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x38, 0x3c,
    0x3c, 0x38,
    /* U+0394 "" (11x14) */
    0x1f, 0x03, 0xe0, 0x7c, 0x1f, 0xc3, 0xb8, 0x77, 0x0e, 0xe3, 0xde, 0x71,
    0xce, 0x39, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xc0,
    /* U+03A9 "" (12x14) */
    0x0f, 0x83, 0xfc, 0x7f, 0xe7, 0x8e, 0x70, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0x70, 0xf7, 0x0e, 0x38, 0xe7, 0x9e, 0x7d, 0xf7, 0xdf,
    /* U+03B1 "" (10x11) */
    0x1c, 0xcf, 0xf7, 0xfd, 0xcf, 0x73, 0xbc, 0xef, 0x39, 0xcf, 0x7f, 0xdf,
    0xf3, 0xcc,
    /* U+03B2 "" (10x19) */
    0x3e, 0x1f, 0xcf, 0xfb, 0x9e, 0xe7, 0xbb, 0xce, 0xe3, 0xbe, 0xe3, 0xb8,
    0xfe, 0x3f, 0x8f, 0xff, 0xbf, 0xef, 0xf3, 0x80, 0xe0, 0x38, 0x0e, 0x00,
    /* U+03B3 "" (9x15) */
    0x63, 0xf9, 0xfc, 0xee, 0x77, 0x71, 0xf8, 0xfc, 0x7c, 0x1e, 0x0f, 0x07,
    0x03, 0x81, 0xc0, 0xe0, 0x70,
    /* U+03B4 "" (10x15) */
    0x1f, 0x0f, 0xe7, 0xf1, 0xe0, 0x3c, 0x0f, 0xc3, 0xf9, 0xef, 0x73, 0xfc,
    0xff, 0x3d, 0xcf, 0x7f, 0xdf, 0xe1, 0xf0,
    /* U+03B5 "" (9x11) */
    0x3e, 0x3f, 0x9f, 0xce, 0x03, 0xe1, 0xe1, 0xf1, 0xe0, 0x7f, 0x3f, 0xcf,
    0xc0,
    /* U+03B8 "" (10x15) */
    0x1e, 0x0f, 0xc7, 0xf9, 0xce, 0x73, 0xdc, 0x7f, 0xff, 0xff, 0xff, 0xdc,
    0x77, 0x3d, 0xce, 0x7f, 0x8f, 0xc1, 0xe0,
    /* U+03BB "" (10x15) */
    0x78, 0x1f, 0x01, 0xe0, 0x38, 0x1e, 0x0f, 0xc3, 0xf0, 0xfc, 0x3f, 0x1d,
    0xe7, 0x79, 0xce, 0x73, 0xfc, 0xf7, 0x18,
    /* U+03BC "" (9x15) */
    0xe7, 0xf3, 0xf9, 0xfc, 0xfe, 0x7f, 0x3f, 0x9f, 0xcf, 0xff, 0xff, 0xff,
    0xfc, 0x0e, 0x07, 0x03, 0x80,
    /* U+03C0 "" (11x11) */
    0xff, 0xff, 0xfd, 0xff, 0x1d, 0xe3, 0xbc, 0x77, 0x8e, 0xf1, 0xce, 0x39,
    0xc7, 0x38, 0xe3, 0x00,
    /* U+03C3 "" (11x11) */
    0x1f, 0xe7, 0xfd, 0xff, 0xb8, 0xef, 0x1d, 0xe3, 0xbc, 0x73, 0x9e, 0x7f,
    0xc7, 0xf0, 0x7c, 0x00,
    /* U+03C4 "" (9x11) */
    0xff, 0xff, 0xdf, 0xc3, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1e, 0x0f, 0x01,
    0x00,
    /* U+03C6 "" (13x16) */
    0x79, 0xe3, 0x9f, 0x9c, 0xfe, 0xef, 0x77, 0x7b, 0xfb, 0xdf, 0xde, 0xee,
    0xf7, 0x77, 0xbb, 0xff, 0xcf, 0xfc, 0x0f, 0x00, 0x78, 0x03, 0xc0, 0x1e,
    0x00, 0x60,
    /* U+03C9 "" (14x11) */
    0x78, 0x79, 0xc0, 0xe7, 0x03, 0x9c, 0xce, 0xf7, 0xbf, 0xde, 0xff, 0x7b,
    0xdd, 0xee, 0x7f, 0xf9, 0xff, 0xe3, 0xcf, 0x00,
    /* U+2013 "" (9x3) */
    0x7f, 0xff, 0xff, 0xe0,
    /* U+2014 "" (14x3) */
    0x7f, 0xff, 0xff, 0xff, 0xff, 0xc0,
    /* U+2018 "" (3x6) */
    0x6f, 0xff, 0xc0,
    /* U+2019 "" (3x6) */
    0xdf, 0xed, 0x00,
    /* U+201C "" (7x6) */
    0x66, 0xcf, 0x1f, 0x7e, 0xfd, 0xc0,
    /* U+201D "" (7x6) */
    0xcf, 0xdf, 0xbe, 0x3c, 0xd1, 0x80,
    /* U+2022 "" (5x6) */
    0x77, 0xff, 0xff, 0xb8,
    /* U+2026 "" (12x4) */
    0xc6, 0x7e, 0xf7, 0xef, 0x7c, 0x67,
    /* U+2030 "" (22x14) */
    0x78, 0x30, 0x03, 0xf1, 0xc0, 0x0f, 0xce, 0x00, 0x33, 0x38, 0x00, 0xcd,
    0xc0, 0x03, 0xf6, 0x00, 0x0f, 0xb8, 0x00, 0x01, 0xde, 0x3e, 0x07, 0xfd,
    0xf8, 0x3b, 0x37, 0x71, 0xcc, 0xd9, 0xc7, 0x3f, 0x7e, 0x38, 0xfc, 0xf8,
    0xc1, 0xe1, 0xc0,
    /* U+2190 "" (14x13) */
    0x06, 0x00, 0x3c, 0x01, 0xe0, 0x0f, 0x00, 0x78, 0x03, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x78, 0x00, 0xf0, 0x01, 0xe0, 0x03, 0x80, 0x04, 0x00,
    /* U+2191 "" (14x14) */
    0x03, 0x00, 0x1e, 0x00, 0xfc, 0x07, 0xf8, 0x3f, 0xf1, 0xff, 0xef, 0x7b,
    0xd9, 0xe6, 0x07, 0x80, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e,
    0x00,
    /* U+2192 "" (14x13) */
    0x01, 0x80, 0x0f, 0x00, 0x1e, 0x00, 0x3c, 0x00, 0x7b, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x00, 0x78, 0x03, 0xc0, 0x1e, 0x00, 0x70, 0x00, 0x80,
    /* U+2193 "" (14x14) */
    0x07, 0x80, 0x1e, 0x00, 0x78, 0x01, 0xe0, 0x07, 0x80, 0x1e, 0x06, 0x79,
    0xbd, 0xef, 0x7f, 0xf8, 0xff, 0xc1, 0xfe, 0x03, 0xf0, 0x07, 0x80, 0x0c,
    0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 64, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 74, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 140, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 13, .adv_w = 166, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 161, .box_w = 10, .box_h = 20, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 56, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 225, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 74, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 105, .adv_w = 97, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 120, .adv_w = 97, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 135, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 143, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 152, .adv_w = 73, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 156, .adv_w = 121, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 159, .adv_w = 74, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 150, .box_w = 7, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 177, .adv_w = 177, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 139, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 150, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 168, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 160, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 170, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 139, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 172, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 169, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 339, .adv_w = 74, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 74, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 353, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 364, .adv_w = 152, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 371, .adv_w = 152, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 380, .adv_w = 144, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 296, .box_w = 17, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 433, .adv_w = 176, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 180, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 170, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 191, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 151, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 141, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 190, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 86, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 94, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 591, .adv_w = 190, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 150, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 231, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 190, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 202, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 176, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 202, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 728, .adv_w = 181, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 169, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 159, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 187, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 169, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 249, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 174, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 178, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 160, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 95, .box_w = 6, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 920, .adv_w = 150, .box_w = 7, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 936, .adv_w = 95, .box_w = 6, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 951, .adv_w = 165, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 959, .adv_w = 151, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 963, .adv_w = 106, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 13},
    {.bitmap_index = 965, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 978, .adv_w = 174, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 140, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1008, .adv_w = 175, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1027, .adv_w = 164, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1041, .adv_w = 108, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1056, .adv_w = 162, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1076, .adv_w = 167, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1093, .adv_w = 83, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1100, .adv_w = 83, .box_w = 5, .box_h = 21, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1114, .adv_w = 167, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1131, .adv_w = 88, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1139, .adv_w = 244, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1157, .adv_w = 167, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1170, .adv_w = 172, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1184, .adv_w = 174, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1201, .adv_w = 175, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1220, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1229, .adv_w = 141, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 115, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 165, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1266, .adv_w = 152, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1280, .adv_w = 223, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1300, .adv_w = 153, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1314, .adv_w = 155, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1333, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1344, .adv_w = 94, .box_w = 6, .box_h = 19, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1359, .adv_w = 104, .box_w = 3, .box_h = 18, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1366, .adv_w = 94, .box_w = 6, .box_h = 19, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1381, .adv_w = 155, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1384, .adv_w = 149, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1390, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1403, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1410, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1417, .adv_w = 168, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1434, .adv_w = 74, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1436, .adv_w = 152, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1444, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1458, .adv_w = 178, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1478, .adv_w = 199, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1499, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1513, .adv_w = 178, .box_w = 10, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1537, .adv_w = 152, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1554, .adv_w = 169, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1573, .adv_w = 142, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1586, .adv_w = 164, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1605, .adv_w = 159, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1624, .adv_w = 168, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1641, .adv_w = 180, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1657, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1673, .adv_w = 142, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1686, .adv_w = 223, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1712, .adv_w = 224, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1732, .adv_w = 152, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1736, .adv_w = 233, .box_w = 14, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1742, .adv_w = 75, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1745, .adv_w = 75, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1748, .adv_w = 143, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1754, .adv_w = 143, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1760, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1764, .adv_w = 222, .box_w = 12, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1770, .adv_w = 371, .box_w = 22, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1809, .adv_w = 288, .box_w = 14, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1832, .adv_w = 288, .box_w = 14, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1857, .adv_w = 288, .box_w = 14, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1880, .adv_w = 288, .box_w = 14, .box_h = 14, .ofs_x = 2, .ofs_y = -1}
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
    2, 32, 3, 4, 3, 13, 3, 15, 3, 16, 3, 21, 3, 25, 3, 33,
    3, 34, 3, 43, 3, 64, 3, 66, 3, 104, 3, 112, 3, 126, 4, 11,
    4, 24, 4, 64, 4, 87, 4, 90, 4, 108, 5, 18, 5, 61, 5, 64,
    6, 3, 6, 8, 6, 11, 6, 18, 6, 32, 6, 61, 6, 121, 6, 122,
    6, 123, 6, 124, 7, 3, 7, 6, 7, 8, 7, 11, 7, 16, 7, 18,
    7, 24, 7, 32, 7, 53, 7, 55, 7, 58, 7, 61, 7, 116, 7, 121,
    7, 122, 7, 123, 7, 124, 7, 127, 8, 4, 8, 13, 8, 15, 8, 16,
    8, 17, 8, 21, 8, 23, 8, 25, 8, 33, 8, 34, 8, 43, 8, 59,
    8, 64, 8, 66, 8, 68, 8, 69, 8, 70, 8, 80, 8, 82, 8, 84,
    8, 91, 8, 104, 8, 106, 8, 109, 8, 110, 8, 112, 8, 115, 8, 117,
    8, 118, 8, 126, 9, 75, 11, 2, 11, 3, 11, 8, 11, 11, 11, 13,
    11, 15, 11, 16, 11, 18, 11, 19, 11, 20, 11, 24, 11, 26, 11, 53,
    11, 55, 11, 56, 11, 64, 11, 71, 11, 85, 11, 87, 11, 88, 11, 89,
    11, 90, 11, 98, 11, 99, 11, 108, 11, 114, 11, 116, 11, 121, 11, 122,
    11, 123, 11, 124, 11, 126, 12, 5, 12, 7, 12, 13, 12, 15, 12, 16,
    12, 18, 12, 19, 12, 20, 12, 24, 12, 32, 12, 52, 12, 53, 12, 55,
    12, 57, 12, 58, 12, 59, 12, 61, 12, 64, 12, 89, 12, 91, 12, 112,
    12, 126, 13, 3, 13, 6, 13, 7, 13, 8, 13, 11, 13, 12, 13, 14,
    13, 17, 13, 18, 13, 21, 13, 23, 13, 26, 13, 32, 13, 36, 13, 40,
    13, 48, 13, 50, 13, 53, 13, 54, 13, 55, 13, 56, 13, 58, 13, 61,
    13, 68, 13, 69, 13, 70, 13, 71, 13, 72, 13, 80, 13, 82, 13, 85,
    13, 86, 13, 87, 13, 88, 13, 90, 13, 95, 13, 98, 13, 99, 13, 101,
    13, 103, 13, 106, 13, 108, 13, 109, 13, 111, 13, 114, 13, 115, 13, 116,
    13, 117, 13, 118, 13, 119, 13, 120, 13, 121, 13, 122, 13, 123, 13, 124,
    13, 127, 14, 5, 14, 6, 14, 7, 14, 13, 14, 15, 14, 16, 14, 18,
    14, 19, 14, 20, 14, 21, 14, 22, 14, 24, 14, 26, 14, 32, 14, 34,
    14, 43, 14, 52, 14, 53, 14, 55, 14, 57, 14, 58, 14, 59, 14, 61,
    14, 64, 14, 66, 14, 71, 14, 75, 14, 85, 14, 87, 14, 89, 14, 90,
    14, 91, 14, 104, 14, 108, 14, 112, 14, 114, 14, 116, 14, 126, 14, 127,
    15, 3, 15, 6, 15, 7, 15, 8, 15, 11, 15, 12, 15, 14, 15, 17,
    15, 18, 15, 21, 15, 23, 15, 26, 15, 32, 15, 36, 15, 40, 15, 48,
    15, 50, 15, 53, 15, 54, 15, 55, 15, 56, 15, 58, 15, 61, 15, 68,
    15, 69, 15, 70, 15, 71, 15, 72, 15, 80, 15, 82, 15, 85, 15, 86,
    15, 87, 15, 88, 15, 90, 15, 95, 15, 98, 15, 99, 15, 101, 15, 103,
    15, 106, 15, 108, 15, 109, 15, 111, 15, 114, 15, 115, 15, 116, 15, 117,
    15, 118, 15, 119, 15, 120, 15, 121, 15, 122, 15, 123, 15, 124, 15, 127,
    16, 7, 16, 12, 16, 13, 16, 14, 16, 15, 16, 16, 16, 18, 16, 21,
    16, 27, 16, 28, 16, 32, 16, 33, 16, 64, 16, 66, 16, 68, 16, 69,
    16, 70, 16, 80, 16, 82, 16, 95, 16, 101, 16, 103, 16, 106, 16, 109,
    16, 110, 16, 115, 16, 116, 16, 117, 16, 118, 16, 119, 16, 120, 16, 126,
    17, 53, 17, 64, 18, 18, 20, 16, 20, 18, 20, 26, 20, 32, 20, 53,
    20, 58, 20, 61, 20, 64, 21, 3, 21, 5, 21, 6, 21, 8, 21, 11,
    21, 12, 21, 14, 21, 16, 21, 18, 21, 19, 21, 20, 21, 22, 21, 24,
    21, 26, 21, 32, 21, 43, 21, 52, 21, 53, 21, 55, 21, 56, 21, 58,
    21, 61, 21, 71, 21, 87, 21, 89, 21, 90, 21, 95, 21, 101, 21, 103,
    21, 108, 21, 114, 21, 116, 21, 119, 21, 120, 21, 121, 21, 122, 21, 123,
    21, 124, 21, 127, 22, 3, 22, 8, 22, 18, 22, 53, 22, 55, 22, 58,
    22, 61, 22, 121, 22, 122, 22, 123, 22, 124, 23, 3, 23, 8, 23, 11,
    23, 16, 23, 18, 23, 19, 23, 24, 23, 26, 23, 32, 23, 43, 23, 53,
    23, 55, 23, 57, 23, 58, 23, 61, 23, 64, 23, 87, 23, 89, 23, 90,
    23, 96, 23, 108, 23, 114, 23, 116, 23, 121, 23, 122, 23, 123, 23, 124,
    24, 4, 24, 5, 24, 7, 24, 12, 24, 13, 24, 14, 24, 15, 24, 16,
    24, 21, 24, 23, 24, 25, 24, 27, 24, 28, 24, 33, 24, 34, 24, 43,
    24, 52, 24, 59, 24, 64, 24, 66, 24, 68, 24, 69, 24, 70, 24, 72,
    24, 80, 24, 82, 24, 84, 24, 86, 24, 91, 24, 95, 24, 101, 24, 103,
    24, 104, 24, 105, 24, 106, 24, 109, 24, 110, 24, 112, 24, 115, 24, 117,
    24, 118, 24, 119, 24, 120, 24, 125, 24, 126, 25, 3, 25, 8, 25, 18,
    25, 32, 25, 53, 25, 58, 25, 61, 25, 64, 25, 116, 25, 121, 25, 122,
    25, 123, 25, 124, 26, 5, 26, 13, 26, 15, 26, 16, 26, 18, 26, 19,
    26, 20, 26, 21, 26, 24, 26, 32, 26, 34, 26, 43, 26, 52, 26, 53,
    26, 55, 26, 57, 26, 58, 26, 59, 26, 61, 26, 64, 26, 66, 26, 104,
    26, 112, 26, 126, 27, 18, 27, 24, 27, 32, 27, 53, 27, 55, 27, 58,
    27, 61, 28, 18, 28, 24, 28, 32, 28, 53, 28, 55, 28, 58, 28, 61,
    29, 18, 29, 20, 29, 26, 29, 32, 29, 43, 29, 57, 29, 59, 29, 89,
    30, 18, 30, 20, 30, 26, 30, 32, 30, 43, 30, 57, 30, 59, 30, 89,
    31, 18, 31, 20, 31, 26, 31, 32, 31, 43, 31, 57, 31, 59, 31, 89,
    32, 7, 32, 12, 32, 13, 32, 14, 32, 15, 32, 16, 32, 64, 32, 95,
    32, 101, 32, 103, 32, 119, 32, 120, 32, 126, 33, 3, 33, 7, 33, 8,
    33, 11, 33, 13, 33, 15, 33, 18, 33, 19, 33, 20, 33, 24, 33, 26,
    33, 27, 33, 28, 33, 32, 33, 53, 33, 55, 33, 56, 33, 57, 33, 58,
    33, 59, 33, 61, 33, 64, 33, 84, 33, 89, 33, 91, 33, 114, 33, 116,
    33, 121, 33, 122, 33, 123, 33, 124, 33, 126, 34, 3, 34, 8, 34, 11,
    34, 18, 34, 32, 34, 53, 34, 58, 34, 116, 34, 121, 34, 122, 34, 123,
    34, 124, 35, 18, 36, 7, 36, 12, 36, 14, 36, 17, 36, 18, 36, 21,
    36, 22, 36, 23, 36, 24, 36, 25, 36, 26, 36, 29, 36, 30, 36, 31,
    36, 33, 36, 36, 36, 40, 36, 43, 36, 48, 36, 50, 36, 53, 36, 54,
    36, 57, 36, 58, 36, 61, 36, 66, 36, 67, 36, 68, 36, 69, 36, 70,
    36, 71, 36, 72, 36, 73, 36, 75, 36, 76, 36, 77, 36, 78, 36, 79,
    36, 80, 36, 81, 36, 82, 36, 83, 36, 85, 36, 86, 36, 87, 36, 88,
    36, 89, 36, 90, 36, 95, 36, 98, 36, 99, 36, 100, 36, 101, 36, 102,
    36, 103, 36, 105, 36, 106, 36, 107, 36, 108, 36, 109, 36, 110, 36, 111,
    36, 113, 36, 114, 36, 115, 36, 116, 36, 117, 36, 118, 36, 119, 36, 120,
    36, 125, 37, 19, 37, 53, 37, 58, 37, 59, 37, 64, 38, 11, 39, 4,
    39, 5, 39, 7, 39, 13, 39, 15, 39, 16, 39, 18, 39, 21, 39, 22,
    39, 25, 39, 26, 39, 27, 39, 28, 39, 33, 39, 34, 39, 36, 39, 40,
    39, 46, 39, 48, 39, 50, 39, 52, 39, 64, 39, 66, 39, 68, 39, 69,
    39, 70, 39, 71, 39, 72, 39, 74, 39, 75, 39, 78, 39, 79, 39, 80,
    39, 81, 39, 82, 39, 83, 39, 84, 39, 85, 39, 86, 39, 87, 39, 88,
    39, 89, 39, 90, 39, 91, 39, 100, 39, 104, 39, 105, 39, 106, 39, 108,
    39, 109, 39, 110, 39, 112, 39, 113, 39, 114, 39, 115, 39, 116, 39, 117,
    39, 118, 39, 126, 40, 18, 40, 53, 40, 58, 44, 12, 44, 14, 44, 18,
    44, 21, 44, 29, 44, 30, 44, 31, 44, 32, 44, 33, 44, 95, 44, 101,
    44, 102, 44, 103, 44, 116, 44, 119, 44, 120, 44, 125, 45, 3, 45, 8,
    45, 11, 45, 12, 45, 14, 45, 18, 45, 26, 45, 32, 45, 53, 45, 55,
    45, 58, 45, 61, 45, 87, 45, 88, 45, 90, 45, 95, 45, 98, 45, 99,
    45, 101, 45, 103, 45, 108, 45, 119, 45, 120, 45, 121, 45, 122, 45, 123,
    45, 124, 45, 125, 48, 13, 48, 15, 48, 18, 48, 19, 48, 20, 48, 24,
    48, 32, 48, 34, 48, 43, 48, 46, 48, 53, 48, 57, 48, 58, 48, 59,
    48, 61, 48, 64, 48, 66, 48, 89, 48, 91, 48, 104, 48, 110, 48, 112,
    48, 116, 48, 126, 49, 4, 49, 7, 49, 13, 49, 15, 49, 16, 49, 21,
    49, 32, 49, 33, 49, 34, 49, 43, 49, 46, 49, 57, 49, 58, 49, 59,
    49, 61, 49, 64, 49, 66, 49, 68, 49, 69, 49, 70, 49, 80, 49, 82,
    49, 104, 49, 106, 49, 109, 49, 110, 49, 112, 49, 115, 49, 117, 49, 118,
    49, 126, 50, 13, 50, 15, 50, 18, 50, 19, 50, 20, 50, 24, 50, 32,
    50, 34, 50, 43, 50, 46, 50, 53, 50, 57, 50, 58, 50, 59, 50, 61,
    50, 64, 50, 66, 50, 89, 50, 91, 50, 104, 50, 110, 50, 112, 50, 116,
    50, 126, 51, 62, 51, 94, 52, 3, 52, 5, 52, 8, 52, 18, 52, 19,
    52, 24, 52, 26, 52, 32, 52, 34, 52, 43, 52, 46, 52, 52, 52, 53,
    52, 55, 52, 56, 52, 57, 52, 58, 52, 59, 52, 61, 52, 64, 52, 71,
    52, 87, 52, 90, 52, 91, 52, 98, 52, 99, 52, 104, 52, 108, 52, 121,
    52, 122, 52, 123, 52, 124, 53, 4, 53, 7, 53, 12, 53, 13, 53, 14,
    53, 15, 53, 16, 53, 17, 53, 21, 53, 23, 53, 27, 53, 28, 53, 33,
    53, 34, 53, 36, 53, 40, 53, 48, 53, 50, 53, 61, 53, 64, 53, 66,
    53, 68, 53, 69, 53, 70, 53, 71, 53, 72, 53, 75, 53, 78, 53, 79,
    53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 85, 53, 86, 53, 87,
    53, 88, 53, 89, 53, 90, 53, 91, 53, 95, 53, 100, 53, 101, 53, 103,
    53, 104, 53, 105, 53, 106, 53, 108, 53, 109, 53, 110, 53, 112, 53, 113,
    53, 115, 53, 116, 53, 117, 53, 118, 53, 119, 53, 120, 53, 125, 53, 126,
    54, 64, 55, 4, 55, 5, 55, 7, 55, 12, 55, 13, 55, 14, 55, 15,
    55, 16, 55, 18, 55, 21, 55, 22, 55, 23, 55, 25, 55, 26, 55, 27,
    55, 28, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 46, 55, 48,
    55, 50, 55, 52, 55, 59, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70,
    55, 71, 55, 72, 55, 75, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82,
    55, 83, 55, 84, 55, 85, 55, 86, 55, 87, 55, 88, 55, 89, 55, 90,
    55, 91, 55, 95, 55, 100, 55, 101, 55, 103, 55, 104, 55, 105, 55, 106,
    55, 108, 55, 109, 55, 110, 55, 112, 55, 113, 55, 115, 55, 117, 55, 118,
    55, 119, 55, 120, 55, 125, 55, 126, 56, 5, 56, 7, 56, 13, 56, 15,
    56, 18, 56, 21, 56, 22, 56, 33, 56, 43, 56, 52, 56, 59, 56, 64,
    56, 66, 56, 68, 56, 69, 56, 70, 56, 71, 56, 72, 56, 78, 56, 79,
    56, 80, 56, 81, 56, 82, 56, 83, 56, 84, 56, 85, 56, 86, 56, 89,
    56, 91, 56, 100, 56, 105, 56, 106, 56, 109, 56, 112, 56, 113, 56, 115,
    56, 117, 56, 118, 56, 126, 57, 12, 57, 14, 57, 18, 57, 21, 57, 29,
    57, 30, 57, 31, 57, 32, 57, 33, 57, 95, 57, 101, 57, 102, 57, 103,
    57, 116, 57, 119, 57, 120, 57, 125, 58, 4, 58, 7, 58, 12, 58, 13,
    58, 14, 58, 15, 58, 16, 58, 18, 58, 21, 58, 23, 58, 25, 58, 26,
    58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40, 58, 48, 58, 50,
    58, 62, 58, 64, 58, 66, 58, 68, 58, 69, 58, 70, 58, 71, 58, 72,
    58, 78, 58, 79, 58, 80, 58, 81, 58, 82, 58, 83, 58, 84, 58, 86,
    58, 87, 58, 89, 58, 90, 58, 91, 58, 95, 58, 100, 58, 101, 58, 103,
    58, 104, 58, 106, 58, 108, 58, 109, 58, 110, 58, 113, 58, 115, 58, 116,
    58, 117, 58, 118, 58, 119, 58, 120, 58, 125, 58, 126, 59, 12, 59, 14,
    59, 21, 59, 61, 59, 95, 59, 101, 59, 103, 59, 116, 59, 119, 59, 120,
    59, 125, 60, 18, 60, 55, 60, 75, 61, 3, 61, 6, 61, 7, 61, 8,
    61, 11, 61, 12, 61, 14, 61, 18, 61, 32, 61, 53, 61, 58, 61, 61,
    61, 75, 61, 95, 61, 96, 61, 98, 61, 99, 61, 101, 61, 103, 61, 116,
    61, 119, 61, 120, 61, 121, 61, 122, 61, 123, 61, 124, 61, 127, 64, 3,
    64, 6, 64, 8, 64, 10, 64, 11, 64, 12, 64, 14, 64, 18, 64, 21,
    64, 32, 64, 43, 64, 53, 64, 55, 64, 56, 64, 58, 64, 61, 64, 62,
    64, 72, 64, 75, 64, 94, 64, 95, 64, 98, 64, 99, 64, 101, 64, 103,
    64, 116, 64, 119, 64, 120, 64, 121, 64, 122, 64, 123, 64, 124, 64, 127,
    66, 18, 66, 32, 66, 61, 67, 18, 67, 24, 67, 32, 67, 61, 67, 116,
    68, 7, 68, 12, 68, 14, 68, 21, 68, 24, 68, 32, 68, 33, 68, 61,
    68, 68, 68, 69, 68, 70, 68, 80, 68, 82, 68, 95, 68, 101, 68, 103,
    68, 106, 68, 109, 68, 110, 68, 115, 68, 117, 68, 118, 68, 119, 68, 120,
    68, 125, 70, 18, 70, 24, 70, 32, 70, 61, 71, 2, 71, 3, 71, 8,
    71, 10, 71, 11, 71, 12, 71, 13, 71, 14, 71, 15, 71, 16, 71, 24,
    71, 32, 71, 33, 71, 62, 71, 64, 71, 66, 71, 94, 71, 95, 71, 101,
    71, 103, 71, 119, 71, 120, 71, 121, 71, 122, 71, 123, 71, 124, 71, 126,
    76, 2, 76, 11, 76, 13, 76, 15, 76, 27, 76, 28, 76, 62, 76, 94,
    76, 98, 76, 99, 76, 126, 77, 3, 77, 8, 77, 11, 77, 12, 77, 14,
    77, 18, 77, 24, 77, 32, 77, 61, 77, 66, 77, 68, 77, 69, 77, 70,
    77, 80, 77, 82, 77, 87, 77, 90, 77, 95, 77, 98, 77, 99, 77, 101,
    77, 103, 77, 106, 77, 108, 77, 109, 77, 115, 77, 117, 77, 118, 77, 119,
    77, 120, 77, 121, 77, 122, 77, 123, 77, 124, 77, 125, 78, 58, 80, 18,
    80, 19, 80, 20, 80, 24, 80, 32, 80, 61, 80, 64, 80, 112, 80, 114,
    80, 116, 81, 18, 81, 24, 81, 32, 81, 61, 81, 116, 83, 3, 83, 8,
    83, 11, 83, 13, 83, 15, 83, 16, 83, 18, 83, 24, 83, 27, 83, 28,
    83, 61, 83, 64, 83, 98, 83, 99, 83, 112, 83, 121, 83, 122, 83, 123,
    83, 124, 83, 126, 84, 18, 84, 24, 84, 32, 84, 61, 84, 64, 85, 12,
    85, 14, 85, 61, 85, 95, 85, 101, 85, 103, 85, 119, 85, 120, 87, 7,
    87, 12, 87, 13, 87, 14, 87, 15, 87, 19, 87, 20, 87, 21, 87, 32,
    87, 61, 87, 64, 87, 66, 87, 68, 87, 69, 87, 70, 87, 72, 87, 80,
    87, 82, 87, 84, 87, 95, 87, 101, 87, 103, 87, 106, 87, 109, 87, 110,
    87, 112, 87, 115, 87, 117, 87, 118, 87, 119, 87, 120, 87, 126, 89, 7,
    89, 12, 89, 14, 89, 17, 89, 18, 89, 21, 89, 22, 89, 23, 89, 26,
    89, 29, 89, 30, 89, 31, 89, 32, 89, 33, 89, 61, 89, 66, 89, 68,
    89, 69, 89, 70, 89, 72, 89, 80, 89, 82, 89, 84, 89, 86, 89, 95,
    89, 101, 89, 102, 89, 103, 89, 106, 89, 109, 89, 110, 89, 115, 89, 117,
    89, 118, 89, 119, 89, 120, 89, 125, 90, 7, 90, 13, 90, 15, 90, 20,
    90, 32, 90, 61, 90, 64, 90, 66, 90, 112, 90, 126, 91, 4, 91, 7,
    91, 12, 91, 14, 91, 18, 91, 21, 91, 23, 91, 24, 91, 32, 91, 33,
    91, 61, 91, 66, 91, 68, 91, 69, 91, 70, 91, 72, 91, 80, 91, 82,
    91, 84, 91, 86, 91, 95, 91, 101, 91, 103, 91, 106, 91, 109, 91, 110,
    91, 115, 91, 117, 91, 118, 91, 119, 91, 120, 91, 125, 92, 75, 95, 5,
    95, 6, 95, 7, 95, 13, 95, 15, 95, 16, 95, 18, 95, 19, 95, 20,
    95, 24, 95, 32, 95, 43, 95, 52, 95, 53, 95, 55, 95, 57, 95, 58,
    95, 59, 95, 61, 95, 64, 95, 66, 95, 71, 95, 89, 95, 91, 95, 112,
    95, 114, 95, 116, 95, 126, 95, 127, 96, 2, 96, 3, 96, 8, 96, 11,
    96, 12, 96, 13, 96, 14, 96, 15, 96, 16, 96, 27, 96, 28, 96, 32,
    96, 61, 96, 64, 96, 95, 96, 101, 96, 103, 96, 119, 96, 120, 96, 121,
    96, 122, 96, 123, 96, 124, 96, 126, 98, 11, 98, 13, 98, 15, 98, 16,
    98, 18, 98, 19, 98, 24, 98, 26, 98, 55, 98, 64, 98, 85, 98, 87,
    98, 88, 98, 89, 98, 90, 98, 108, 98, 111, 98, 114, 98, 116, 98, 126,
    99, 11, 99, 13, 99, 15, 99, 16, 99, 18, 99, 19, 99, 24, 99, 26,
    99, 55, 99, 64, 99, 85, 99, 87, 99, 88, 99, 89, 99, 90, 99, 108,
    99, 111, 99, 114, 99, 116, 99, 126, 100, 18, 100, 24, 100, 32, 100, 61,
    101, 5, 101, 6, 101, 7, 101, 13, 101, 15, 101, 16, 101, 18, 101, 19,
    101, 20, 101, 21, 101, 22, 101, 24, 101, 26, 101, 32, 101, 34, 101, 43,
    101, 52, 101, 53, 101, 55, 101, 57, 101, 58, 101, 59, 101, 61, 101, 64,
    101, 66, 101, 71, 101, 75, 101, 87, 101, 89, 101, 90, 101, 91, 101, 104,
    101, 108, 101, 112, 101, 114, 101, 116, 101, 126, 101, 127, 102, 18, 102, 20,
    102, 26, 102, 32, 102, 43, 102, 57, 102, 59, 102, 89, 103, 5, 103, 6,
    103, 7, 103, 13, 103, 15, 103, 16, 103, 18, 103, 19, 103, 20, 103, 21,
    103, 22, 103, 24, 103, 26, 103, 32, 103, 34, 103, 43, 103, 52, 103, 53,
    103, 55, 103, 57, 103, 58, 103, 59, 103, 61, 103, 64, 103, 66, 103, 71,
    103, 75, 103, 85, 103, 87, 103, 89, 103, 90, 103, 91, 103, 104, 103, 108,
    103, 112, 103, 114, 103, 116, 103, 126, 103, 127, 104, 18, 104, 53, 104, 58,
    104, 62, 104, 94, 106, 32, 106, 61, 107, 18, 107, 116, 108, 7, 108, 12,
    108, 13, 108, 14, 108, 15, 108, 19, 108, 20, 108, 21, 108, 32, 108, 61,
    108, 64, 108, 66, 108, 68, 108, 69, 108, 70, 108, 72, 108, 80, 108, 82,
    108, 84, 108, 95, 108, 101, 108, 103, 108, 106, 108, 109, 108, 110, 108, 112,
    108, 115, 108, 117, 108, 118, 108, 119, 108, 120, 108, 126, 109, 3, 109, 8,
    109, 11, 109, 13, 109, 15, 109, 18, 109, 19, 109, 20, 109, 22, 109, 24,
    109, 26, 109, 32, 109, 61, 109, 64, 109, 66, 109, 87, 109, 89, 109, 90,
    109, 91, 109, 98, 109, 99, 109, 108, 109, 112, 109, 114, 109, 116, 109, 121,
    109, 122, 109, 123, 109, 124, 109, 126, 110, 12, 110, 14, 110, 21, 110, 24,
    110, 32, 110, 61, 110, 68, 110, 69, 110, 70, 110, 80, 110, 82, 110, 95,
    110, 101, 110, 103, 110, 106, 110, 109, 110, 115, 110, 117, 110, 118, 110, 119,
    110, 120, 112, 3, 112, 8, 112, 11, 112, 12, 112, 14, 112, 18, 112, 32,
    112, 61, 112, 87, 112, 90, 112, 95, 112, 98, 112, 99, 112, 101, 112, 103,
    112, 108, 112, 116, 112, 119, 112, 120, 112, 121, 112, 122, 112, 123, 112, 124,
    113, 18, 113, 24, 113, 32, 113, 61, 114, 11, 114, 98, 114, 99, 115, 11,
    115, 13, 115, 15, 115, 61, 115, 64, 115, 126, 116, 7, 116, 13, 116, 15,
    116, 16, 116, 21, 116, 24, 116, 32, 116, 33, 116, 61, 116, 64, 116, 66,
    116, 68, 116, 69, 116, 70, 116, 80, 116, 82, 116, 106, 116, 109, 116, 110,
    116, 112, 116, 115, 116, 117, 116, 118, 116, 126, 117, 18, 117, 24, 117, 32,
    117, 61, 117, 116, 118, 18, 118, 24, 118, 32, 118, 61, 118, 116, 119, 5,
    119, 6, 119, 7, 119, 13, 119, 15, 119, 16, 119, 18, 119, 19, 119, 20,
    119, 21, 119, 22, 119, 24, 119, 26, 119, 32, 119, 34, 119, 43, 119, 52,
    119, 53, 119, 55, 119, 57, 119, 58, 119, 59, 119, 61, 119, 64, 119, 66,
    119, 71, 119, 75, 119, 85, 119, 87, 119, 89, 119, 90, 119, 91, 119, 104,
    119, 108, 119, 112, 119, 114, 119, 116, 119, 126, 119, 127, 120, 5, 120, 6,
    120, 7, 120, 13, 120, 15, 120, 16, 120, 18, 120, 19, 120, 20, 120, 21,
    120, 22, 120, 24, 120, 26, 120, 32, 120, 34, 120, 43, 120, 52, 120, 53,
    120, 55, 120, 57, 120, 58, 120, 59, 120, 61, 120, 64, 120, 66, 120, 71,
    120, 75, 120, 85, 120, 87, 120, 89, 120, 90, 120, 91, 120, 104, 120, 108,
    120, 112, 120, 114, 120, 116, 120, 126, 120, 127, 121, 4, 121, 13, 121, 15,
    121, 16, 121, 21, 121, 25, 121, 33, 121, 34, 121, 43, 121, 64, 121, 66,
    121, 104, 121, 112, 121, 126, 122, 4, 122, 13, 122, 15, 122, 16, 122, 21,
    122, 25, 122, 33, 122, 34, 122, 43, 122, 64, 122, 66, 122, 104, 122, 112,
    122, 126, 123, 4, 123, 13, 123, 15, 123, 16, 123, 21, 123, 34, 123, 64,
    123, 104, 123, 126, 124, 4, 124, 13, 124, 15, 124, 16, 124, 21, 124, 34,
    124, 64, 124, 104, 124, 126, 125, 5, 125, 7, 125, 16, 125, 18, 125, 19,
    125, 20, 125, 24, 125, 32, 125, 52, 125, 53, 125, 57, 125, 58, 125, 59,
    125, 61, 125, 89, 125, 112, 126, 3, 126, 6, 126, 8, 126, 11, 126, 12,
    126, 14, 126, 18, 126, 26, 126, 32, 126, 53, 126, 55, 126, 56, 126, 58,
    126, 61, 126, 85, 126, 87, 126, 90, 126, 95, 126, 98, 126, 99, 126, 101,
    126, 103, 126, 108, 126, 114, 126, 116, 126, 119, 126, 120, 126, 121, 126, 122,
    126, 123, 126, 124, 126, 127, 127, 3, 127, 8, 127, 11, 127, 18, 127, 32,
    127, 61, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -5, -10, -32, -32, -32, -13, -5, -6, -10, -6, -32, -5, -10, -6, -32, 6,
    3, -26, 3, 3, 3, -12, -10, -10, -19, -19, -16, -19, -19, -19, -19, -19,
    -19, -19, -26, -13, -26, -13, -13, -25, -10, -26, -25, -15, -25, -32, -16, -26,
    -26, -26, -26, -13, -10, -32, -32, -32, -3, -13, -3, -5, -6, -10, -6, -3,
    -32, -5, -3, -3, -3, -3, -3, -3, -3, -10, -3, -3, -3, -6, -3, -3,
    -3, -32, 23, 6, 3, 3, 3, -32, -32, -26, 6, 6, 3, 6, 3, 3,
    3, 3, -32, 6, 6, 7, 6, 4, 7, 6, 6, 7, 7, 6, 3, 3,
    3, 3, -32, -12, -10, -16, -16, -19, -22, -14, -19, -19, -19, -12, -16, -7,
    -12, -19, -10, -19, -26, -11, -10, -10, -16, -32, -32, -4, -32, -32, -16, -16,
    -4, -32, -6, -3, -7, -16, -6, -6, -6, -6, -19, -3, -16, -10, -31, -45,
    -3, -3, -3, -6, -3, -3, -3, -10, -3, -13, -6, -13, -16, -16, -16, -16,
    -16, -3, -13, -3, -3, -10, -3, -26, -3, -3, -16, -16, -32, -32, -32, -32,
    -32, -12, -6, -10, -16, -16, -19, -22, -14, -19, -3, -3, -19, -3, -19, -3,
    -4, -12, -16, -7, -12, -19, -10, -19, -26, -5, -5, -3, -2, -3, -11, -3,
    -10, -3, -3, -10, -4, -6, -16, -6, -32, -32, -4, -32, -32, -16, -16, -4,
    -32, -6, -3, -7, -16, -6, -6, -6, -6, -19, -3, -16, -10, -31, -45, -3,
    -3, -3, -6, -3, -3, -3, -10, -3, -13, -6, -13, -16, -16, -16, -16, -16,
    -3, -13, -3, -3, -10, -3, -26, -3, -3, -16, -16, -32, -32, -32, -32, -32,
    -16, -19, -45, -19, -45, -38, -19, -16, -16, -16, -19, -16, -38, -16, -16, -16,
    -16, -16, -16, -19, -19, -19, -16, -16, -16, -16, -19, -16, -16, -19, -19, -45,
    -10, -10, -6, -6, -6, -3, -3, -7, -7, -6, -6, -16, -6, -13, -16, -13,
    -2, -2, -6, -23, -3, -3, -3, -7, -5, -16, -3, -6, -16, -6, -3, -19,
    -16, -2, -3, -3, -3, -2, -2, -2, -3, -3, -10, -2, -2, -16, -16, -16,
    -16, -13, -10, -10, -18, -13, -10, -13, -10, -10, -10, -10, -10, -6, -6, -6,
    -6, -17, -3, -5, -4, -10, -3, -16, -6, -3, -14, -10, -6, -3, -3, -3,
    -3, -3, -3, -10, -6, -6, -6, -6, -6, -5, -6, -9, -26, -9, -26, -13,
    -10, -5, -4, -8, -8, -6, -10, -6, -5, -4, -32, -10, -10, -10, -10, -8,
    -10, -10, -8, -5, -6, -9, -9, -9, -10, -5, -10, -10, -6, -10, -10, -10,
    -10, -9, -9, -7, -26, -5, -5, -7, -6, -6, -13, -8, -6, -6, -5, -5,
    -5, -5, -3, -16, -16, -13, -5, -4, -6, -2, -3, -6, -3, -3, -3, -6,
    -2, -3, -12, -6, -13, -32, -3, -3, -3, -16, -10, -8, -12, -13, -3, -19,
    -16, -10, -8, -12, -13, -3, -19, -16, -5, -10, -3, -13, -4, -10, -7, -5,
    -5, -10, -3, -13, -4, -10, -7, -5, -5, -10, -3, -13, -4, -10, -7, -5,
    -13, -13, -32, -13, -32, -26, -32, -13, -13, -13, -13, -13, -32, -6, -6, -6,
    -10, -10, -10, -10, -6, -6, -10, -3, -5, -5, -13, -16, -5, -3, -10, -13,
    -6, -16, -16, -3, -3, -3, -2, -6, -6, -6, -6, -6, -10, -10, -10, -10,
    -16, -10, -16, -19, -10, -10, -10, -10, -10, -13, -5, -26, -26, -6, -19, -13,
    -3, -10, -3, -6, -10, -16, -16, -16, -6, -6, -6, -6, -6, -6, -3, -3,
    -3, -6, -6, -3, -3, -6, -6, -6, -6, -8, -3, -4, -3, -3, -4, -4,
    -6, -4, -6, -4, -10, -5, -16, -10, -3, -16, -26, -3, -3, -4, -26, -16,
    -26, -5, -6, -3, -16, -6, -5, -8, -4, -10, -6, -32, -6, -6, -26, -26,
    -19, -8, -11, -12, -8, -13, 3, -10, -6, -10, -26, -26, -16, -10, -11, -6,
    -8, -6, -6, -6, -6, -16, -6, -6, -9, -6, -6, -6, -32, -19, -11, -11,
    -11, -11, -11, -6, -10, -11, -11, -11, -11, -11, -11, -12, -6, -11, -11, -8,
    -19, -11, -16, -11, -16, -10, -11, -11, -11, -11, -16, -11, -10, -11, -13, -11,
    -11, -26, -12, -8, -9, -12, -12, -15, -10, -10, -10, -10, -10, -10, -12, -12,
    -10, -12, -22, -12, -12, -9, -32, -32, -26, -32, -32, -38, -18, -26, -31, -28,
    -29, -38, -23, -16, -23, -32, -32, -32, -32, -32, -23, -32, -32, -32, -32, -32,
    -32, -26, -6, -6, -4, -8, -6, -6, -6, -3, -6, -3, -11, -6, -12, -8,
    -6, -13, -3, -3, -3, -3, -3, -4, -3, -6, -10, -15, -38, -38, -16, -13,
    -13, -10, -19, -12, -10, -14, -12, -11, -16, -32, -15, -10, -10, -10, -10, -10,
    -19, -10, -10, -10, -19, -10, -10, -10, -38, -6, -6, -4, -8, -6, -6, -6,
    -3, -6, -3, -11, -6, -12, -8, -6, -13, -3, -3, -3, -3, -3, -4, -3,
    -6, 6, 3, -3, -3, -3, -12, -3, -5, -5, -6, -2, -3, -3, -3, -6,
    -6, -3, -3, -6, -5, -10, -10, -3, -3, -3, -3, -6, -6, -2, -3, -3,
    -3, -3, -3, -16, -13, -16, -19, -16, -19, -16, -10, -16, -13, -13, -13, -16,
    -16, -11, -11, -11, -11, -10, -16, -16, -18, -18, -18, -13, -16, -10, -10, -10,
    -18, -10, -18, -10, -16, -10, -13, -13, -10, -12, -13, -13, -16, -10, -16, -16,
    -16, -9, -18, -13, -18, -16, -14, -10, -18, -16, -18, -18, -16, -16, -16, -19,
    -10, -3, -5, -6, -7, -16, -7, -16, -7, -6, -6, -3, -2, -3, -2, -3,
    -3, -5, -6, -2, -2, -3, -3, -2, -2, -5, -3, -16, -13, -8, -8, -8,
    -3, -10, -2, -3, -3, -8, -3, -8, -3, -6, -2, -6, -2, -2, -6, -2,
    -8, -7, -3, -7, -7, -6, -2, -8, -2, -8, -5, -8, -3, -8, -8, -8,
    -7, -7, -3, -16, -3, -3, -10, -10, -5, -3, -3, -3, -3, -3, -6, -19,
    -10, -3, -3, -3, -2, -3, -2, -2, -3, -2, -3, -2, -3, -2, -3, -3,
    -4, -2, -2, -3, -3, -6, -2, -3, -3, -3, -10, -12, -12, -15, -10, -10,
    -10, -10, -10, -10, -12, -12, -10, -12, -22, -12, -12, -9, -16, -16, -19, -31,
    -19, -31, -19, -11, -16, -16, -12, -13, -19, -19, -13, -19, -12, -12, -12, -12,
    6, -26, -28, -22, -22, -22, -12, -16, -19, -19, -22, -19, -22, -19, -19, -19,
    -14, -17, -14, -19, -19, -19, -19, -19, -19, -22, -14, -22, -22, -19, -22, -16,
    -22, -22, -19, -19, -15, -31, -16, -16, -10, -13, -16, -16, -16, -13, -16, -16,
    -13, -12, 9, 20, -32, -19, -19, -32, -26, -19, -19, -19, -26, -16, -19, -38,
    6, -19, -26, -22, -22, -19, -19, -16, -19, -19, -32, -32, -32, -32, -19, -32,
    -26, -32, 6, -32, -26, -26, -32, -38, -26, 9, -16, -16, -19, -26, -38, 6,
    7, 23, 6, -26, -26, -26, -26, -26, -26, -26, -26, -32, -32, -32, -32, -26,
    -16, -10, -13, -16, -13, -13, -16, -11, -5, -12, -12, -10, -6, -11, -6, -10,
    -6, -6, -6, -6, -6, -12, -12, -12, -6, -6, -5, -6, -6, -6, -12, -12,
    -8, -16, -13, -13, -16, 21, 22, 22, 26, 16, -6, -16, -6, -16, -9, 19,
    16, -5, 23, -10, -7, 23, -6, -6, -6, -6, -6, 22, 22, 22, 22, -16,
    3, 4, 3, 3, 3, 3, 6, 6, 3, 3, 3, -5, -5, -3, -3, -3,
    -9, -6, -5, -6, -2, -2, -2, -2, -2, -2, -3, -3, -3, -5, -5, -3,
    -3, -2, -3, -2, -2, -2, -2, -3, -3, -5, -5, -5, -5, -3, -13, -16,
    -6, -6, -13, -13, -16, -6, -5, -5, -11, -16, -13, -13, -16, -11, 3, 3,
    9, -26, -26, -19, 6, 3, 3, 3, -16, -26, 8, 8, -16, 3, 3, 3,
    3, -26, -10, -8, -10, -10, -6, -13, -13, -13, -13, -13, -13, -13, -13, -6,
    -3, -13, -3, -13, -3, -6, -3, -10, -6, -10, -7, -3, -3, -3, -1, -3,
    -3, -3, -3, -3, -3, -3, -3, -3, -9, -3, -3, -3, -3, -3, -13, -6,
    -11, -11, -3, -2, -5, -3, -3, -3, -5, -5, -5, -8, -3, -6, -5, -4,
    -4, -4, -3, -4, -4, -2, -3, -11, -11, -5, -11, -4, -4, -3, -4, -4,
    -4, -11, -11, -5, -6, -13, -13, -6, -10, -6, -10, -7, -9, -13, -3, -6,
    -8, -8, -2, -5, -3, -2, -10, -3, -10, -3, -3, -3, -3, -2, -3, -3,
    -1, -2, -8, -8, -8, -3, -3, -4, -3, -3, -3, -8, -8, -2, 19, -12,
    -6, -10, -16, -16, -19, -22, -14, -19, -19, -19, -4, -12, -16, -7, -12, -19,
    -10, -19, -26, -5, -5, -11, -10, -10, -4, -6, -16, -6, -20, -26, -26, -20,
    -29, -64, -29, -64, -52, -29, -29, -29, -26, -32, -29, -29, -29, -29, -29, -26,
    -26, -26, -26, -64, 6, -16, -16, -19, 4, 4, 4, 4, 3, -26, 6, 6,
    4, 3, 6, 6, 3, 6, 4, -16, 6, -16, -16, -19, 4, 4, 4, 4,
    3, -26, 6, 6, 4, 3, 6, 6, 3, 6, 4, -16, -3, -6, -6, -7,
    -12, -6, -10, -16, -16, -19, -22, -14, -19, -3, -3, -19, -3, -19, -3, -4,
    -12, -16, -7, -12, -19, -10, -19, -26, -5, -5, -3, -3, -11, -3, -10, -3,
    -3, -10, -4, -6, -16, -6, -5, -10, -3, -13, -4, -10, -7, -5, -12, -6,
    -10, -16, -16, -19, -22, -14, -19, -3, -3, -19, -3, -19, -3, -4, -12, -16,
    -7, -12, -19, -10, -19, -26, -5, -5, -3, -2, -3, -11, -3, -10, -3, -3,
    -10, -4, -6, -16, -6, -16, -16, -19, 6, 6, -10, -15, -12, -14, -6, -3,
    -13, -3, -13, -3, -6, -3, -10, -6, -10, -7, -3, -3, -3, -1, -3, -3,
    -3, -3, -3, -3, -3, -3, -3, -9, -3, -3, -3, -3, -3, -13, -3, -3,
    -3, -3, -3, -16, -6, -6, -3, -13, -3, -13, -16, -6, -3, -3, -4, -3,
    -3, -2, -2, -3, -5, -5, -11, -3, -3, -3, -3, -3, -11, -11, -8, -10,
    -13, -10, -8, -8, -8, -8, -8, -11, -11, -11, -8, -8, -8, -8, -8, -11,
    -11, -19, -19, -13, -9, -9, -19, -15, -19, -9, -9, -9, -10, -10, -9, -9,
    -9, -16, -9, -9, -19, -19, -19, -19, -3, -6, -6, -7, 6, 6, 6, 9,
    -9, -9, -16, -16, -9, -10, -19, -19, -10, -10, -10, -13, -10, -10, -19, -10,
    -8, -8, -8, -8, -8, -8, -8, -8, -13, -8, -8, -8, -19, -16, -13, -13,
    -16, -11, -16, -13, -13, -16, -11, -12, -6, -10, -16, -16, -19, -22, -14, -19,
    -3, -3, -19, -3, -19, -3, -4, -12, -16, -7, -12, -19, -10, -19, -26, -5,
    -5, -3, -2, -3, -11, -3, -10, -3, -3, -10, -4, -6, -16, -6, -12, -6,
    -10, -16, -16, -19, -22, -14, -19, -3, -3, -19, -3, -19, -3, -4, -12, -16,
    -7, -12, -19, -10, -19, -26, -5, -5, -3, -2, -3, -11, -3, -10, -3, -3,
    -10, -4, -6, -16, -6, -10, -32, -32, -32, -13, -5, -6, -10, -6, -32, -5,
    -10, -6, -32, -10, -32, -32, -32, -13, -5, -6, -10, -6, -32, -5, -10, -6,
    -32, -10, -32, -32, -32, -13, -10, -32, -10, -32, -10, -32, -32, -32, -13, -10,
    -32, -10, -32, -8, -6, -10, -14, -13, -16, -19, -13, -8, -16, -9, -15, -13,
    -10, -5, -6, -32, -32, -32, -32, -16, -16, -32, -7, -16, -19, -16, -10, -31,
    -45, -10, -13, -13, -16, -16, -16, -16, -16, -13, -10, -26, -16, -16, -32, -32,
    -32, -32, -32, -26, -26, -16, -31, -19, -19, -26, -26, -26, -26,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1997,
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

const lv_font_t humid1_font_fira_cond_bold_20 = {
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

#endif /* #if HUMID1_FONT_FIRA_COND_BOLD_20 */
