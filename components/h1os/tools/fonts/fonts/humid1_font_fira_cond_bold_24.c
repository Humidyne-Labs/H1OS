/*******************************************************************************
 * Font: humid1_font_fira_cond_bold_24 (fira_cond bold)
 * Size: 24 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_fira_sans_bold_24 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_FIRA_COND_BOLD_24
#define HUMID1_FONT_FIRA_COND_BOLD_24 1
#endif

#if HUMID1_FONT_FIRA_COND_BOLD_24

extern const lv_font_t humid1_font_fira_sans_bold_24;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x16) */
    0xff, 0xff, 0xff, 0xff, 0xee, 0x00, 0xef, 0xfe,
    /* U+0022 "" (8x7) */
    0xf7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0023 "#" (12x16) */
    0x1c, 0xe1, 0xce, 0x1c, 0xe7, 0xff, 0x7f, 0xf7, 0xff, 0x3d, 0xe3, 0x9e,
    0x39, 0xc3, 0x9c, 0xff, 0xef, 0xfe, 0xff, 0xe7, 0xbc, 0x73, 0xc7, 0x38,
    /* U+0024 "$" (12x23) */
    0x07, 0x00, 0x70, 0x07, 0x00, 0xf0, 0x3f, 0xe7, 0xfe, 0x78, 0xc7, 0x80,
    0x7c, 0x07, 0xf0, 0x3f, 0xc1, 0xfe, 0x03, 0xe0, 0x1f, 0x01, 0xf6, 0x1f,
    0xff, 0xe7, 0xfc, 0x3f, 0x80, 0x70, 0x07, 0x00, 0x70, 0x07, 0x00,
    /* U+0025 "%" (18x16) */
    0x3c, 0x0c, 0x3f, 0x87, 0x8f, 0xe3, 0xc3, 0x9c, 0xe0, 0xe7, 0x78, 0x3f,
    0x9c, 0x0f, 0xee, 0x00, 0xf7, 0xbc, 0x01, 0xff, 0x80, 0xef, 0xe0, 0x7b,
    0xbc, 0x1c, 0xc7, 0x0e, 0x31, 0xc7, 0x8e, 0xe1, 0xc3, 0xf8, 0x70, 0x3c,
    /* U+0026 "&" (15x16) */
    0x1f, 0x80, 0x7f, 0x81, 0xff, 0x83, 0xcf, 0x07, 0x9e, 0x0f, 0x38, 0x0f,
    0xf0, 0x0f, 0xc0, 0x3f, 0x9e, 0xff, 0xbb, 0xef, 0xf7, 0xcf, 0xcf, 0x8f,
    0x8f, 0xff, 0xdf, 0xff, 0x8f, 0x84,
    /* U+0027 "'" (4x7) */
    0xfe, 0xee, 0xee, 0xe0,
    /* U+0028 "(" (7x24) */
    0x0c, 0x3c, 0xf1, 0xe3, 0x8f, 0x1e, 0x3c, 0xf9, 0xe3, 0xc7, 0x8f, 0x1e,
    0x3e, 0x3c, 0x78, 0xf1, 0xe1, 0xe3, 0xc3, 0xc3, 0x84,
    /* U+0029 ")" (7x24) */
    0x71, 0xe1, 0xe3, 0xc3, 0xc7, 0x8f, 0x0f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    0xc7, 0x8f, 0x3c, 0x78, 0xf3, 0xc7, 0x9e, 0x1c, 0x10,
    /* U+002A "" (10x10) */
    0x1e, 0x03, 0x84, 0xc9, 0xfe, 0xff, 0xcf, 0xc3, 0xf1, 0xfe, 0x33, 0x04,
    0x80,
    /* U+002B "+" (10x10) */
    0x1e, 0x07, 0x81, 0xe3, 0xff, 0xff, 0xff, 0xf1, 0xe0, 0x78, 0x1e, 0x07,
    0x80,
    /* U+002C "," (4x8) */
    0xef, 0xff, 0xee, 0xcc,
    /* U+002D "-" (7x3) */
    0xff, 0xff, 0xf8,
    /* U+002E "." (4x4) */
    0xef, 0xfe,
    /* U+002F "/" (9x22) */
    0x07, 0x83, 0xc1, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x3c, 0x1e, 0x0f, 0x07,
    0x87, 0x83, 0xc1, 0xe0, 0xf0, 0xf0, 0x78, 0x3c, 0x1e, 0x0e, 0x0f, 0x00,
    0x80,
    /* U+0030 "0" (11x16) */
    0x1f, 0x07, 0xf1, 0xff, 0x3c, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xfe, 0x3f, 0xc7, 0xf8, 0xf7, 0x9e, 0xff, 0x8f, 0xf0, 0xf8,
    /* U+0031 "1" (9x16) */
    0x0f, 0x8f, 0xdf, 0xff, 0xf7, 0x79, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1,
    0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f,
    /* U+0032 "2" (11x16) */
    0x1f, 0x0f, 0xf3, 0xff, 0x31, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x3e, 0x07,
    0x81, 0xe0, 0x78, 0x1e, 0x07, 0x81, 0xff, 0xff, 0xff, 0xfe,
    /* U+0033 "3" (11x16) */
    0x1f, 0x0f, 0xf3, 0xff, 0x31, 0xe0, 0x3c, 0x07, 0x83, 0xe0, 0xf8, 0x1f,
    0xc0, 0x7c, 0x07, 0x80, 0xf6, 0x3f, 0xff, 0x9f, 0xe1, 0xf8,
    /* U+0034 "4" (12x16) */
    0x0e, 0x00, 0xf0, 0x1e, 0x01, 0xe0, 0x1e, 0x03, 0xc0, 0x3d, 0xe3, 0xde,
    0x79, 0xe7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1e, 0x01, 0xe0, 0x1e,
    /* U+0035 "5" (11x16) */
    0x7f, 0xef, 0xf9, 0xff, 0x3c, 0x07, 0x80, 0xff, 0x1f, 0xf3, 0xff, 0x01,
    0xe0, 0x3c, 0x07, 0x80, 0xf6, 0x3f, 0xff, 0x9f, 0xf0, 0xf8,
    /* U+0036 "6" (11x16) */
    0x0f, 0x83, 0xf8, 0xfe, 0x3c, 0x07, 0x81, 0xef, 0x3f, 0xf7, 0xff, 0xf9,
    0xfe, 0x3f, 0xc7, 0xf8, 0xff, 0x9e, 0xff, 0x8f, 0xf0, 0xf8,
    /* U+0037 "7" (10x16) */
    0xff, 0xff, 0xff, 0xfc, 0x0f, 0x07, 0x81, 0xe0, 0xf8, 0x3c, 0x0f, 0x07,
    0x81, 0xe0, 0x78, 0x3c, 0x0f, 0x07, 0xc0, 0xe0,
    /* U+0038 "8" (12x16) */
    0x0f, 0x83, 0xfe, 0x7f, 0xf7, 0x8f, 0x78, 0xf7, 0x8f, 0x3f, 0xe1, 0xfc,
    0x3f, 0xe7, 0x9f, 0x78, 0xff, 0x8f, 0x78, 0xf7, 0xff, 0x3f, 0xe1, 0xf8,
    /* U+0039 "9" (12x17) */
    0x0f, 0x83, 0xfc, 0x7f, 0xe7, 0x9f, 0x78, 0xff, 0x8f, 0xf8, 0xf7, 0x9f,
    0x7f, 0xf3, 0xff, 0x1f, 0xf0, 0x1e, 0x03, 0xe0, 0xfc, 0x3f, 0x83, 0xe0,
    0x38, 0x00,
    /* U+003A ":" (4x12) */
    0xef, 0xfe, 0x00, 0x00, 0xef, 0xfe,
    /* U+003B ";" (4x16) */
    0xef, 0xfe, 0x00, 0x00, 0xef, 0xff, 0xee, 0xcc,
    /* U+003C "<" (10x12) */
    0x00, 0x80, 0xe1, 0xfd, 0xfe, 0xfc, 0x3c, 0x0f, 0x03, 0xf0, 0x7f, 0x87,
    0xf0, 0x78, 0x02,
    /* U+003D "=" (10x9) */
    0xff, 0xbf, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0xfb, 0xff, 0xff, 0xc0,
    /* U+003E ">" (10x12) */
    0x40, 0x3c, 0x0f, 0xc1, 0xfc, 0x1f, 0xc1, 0xf0, 0x7c, 0x7f, 0x7f, 0x3f,
    0x0f, 0x01, 0x00,
    /* U+003F "?" (10x16) */
    0x3e, 0x3f, 0xef, 0xf9, 0x9f, 0x07, 0x83, 0xe1, 0xf0, 0xf8, 0x3c, 0x0f,
    0x00, 0x00, 0x00, 0x18, 0x0f, 0x03, 0xc0, 0xe0,
    /* U+0040 "@" (20x21) */
    0x01, 0xfc, 0x00, 0x7f, 0xf0, 0x1f, 0xff, 0x83, 0xf0, 0x3c, 0x3c, 0xf9,
    0xe7, 0x9f, 0xcf, 0x73, 0xfc, 0xff, 0x39, 0xc7, 0xf7, 0x9c, 0x7f, 0x79,
    0xc7, 0xf7, 0x9c, 0x7f, 0x79, 0xcf, 0xf7, 0x9e, 0xff, 0x3f, 0xfe, 0xf3,
    0xf7, 0xc7, 0x9e, 0x38, 0x7c, 0x00, 0x03, 0xe0, 0x00, 0x1f, 0xfe, 0x00,
    0xff, 0xf0, 0x01, 0xfc, 0x00,
    /* U+0041 "A" (13x16) */
    0x0f, 0x80, 0x7e, 0x07, 0xf0, 0x3f, 0x81, 0xdc, 0x0e, 0xf0, 0xf7, 0x87,
    0xbc, 0x38, 0xe3, 0xc7, 0x9f, 0xfc, 0xff, 0xe7, 0xff, 0xfc, 0x3f, 0xc1,
    0xfe, 0x0f,
    /* U+0042 "B" (12x16) */
    0xff, 0x8f, 0xfc, 0xff, 0xef, 0x1e, 0xf1, 0xef, 0x1e, 0xff, 0xcf, 0xf8,
    0xff, 0xef, 0x1f, 0xf0, 0xff, 0x0f, 0xf1, 0xff, 0xff, 0xff, 0xef, 0xf8,
    /* U+0043 "C" (11x16) */
    0x0f, 0x87, 0xfd, 0xff, 0xbc, 0x2f, 0x81, 0xe0, 0x3c, 0x07, 0x80, 0xf0,
    0x1e, 0x03, 0xc0, 0x7c, 0x07, 0x84, 0xff, 0xcf, 0xf8, 0x7c,
    /* U+0044 "D" (13x16) */
    0xff, 0x07, 0xfe, 0x3f, 0xf9, 0xe3, 0xef, 0x0f, 0x78, 0x7f, 0xc3, 0xfe,
    0x1f, 0xf0, 0xff, 0x87, 0xfc, 0x3d, 0xe1, 0xef, 0x1f, 0x7f, 0xf3, 0xff,
    0x1f, 0xe0,
    /* U+0045 "E" (10x16) */
    0xff, 0xff, 0xff, 0xfb, 0xc0, 0xf0, 0x3c, 0x0f, 0xfb, 0xfe, 0xff, 0xbc,
    0x0f, 0x03, 0xc0, 0xf0, 0x3f, 0xff, 0xff, 0xff,
    /* U+0046 "F" (9x16) */
    0xff, 0xff, 0xff, 0xfe, 0x0f, 0x07, 0x83, 0xc1, 0xff, 0xff, 0xff, 0xbc,
    0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xe0,
    /* U+0047 "G" (12x16) */
    0x0f, 0xc3, 0xff, 0x7f, 0xf7, 0xc2, 0xf8, 0x0f, 0x00, 0xf3, 0xff, 0x3f,
    0xf1, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf8, 0xf7, 0xff, 0x3f, 0xf0, 0xfc,
    /* U+0048 "H" (12x16) */
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    /* U+0049 "I" (4x16) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+004A "J" (6x20) */
    0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x7f, 0xef, 0x38,
    /* U+004B "K" (13x16) */
    0xf0, 0x7f, 0x87, 0xbc, 0x3d, 0xe3, 0xcf, 0x3c, 0x79, 0xe3, 0xde, 0x1f,
    0xf0, 0xf7, 0xc7, 0x9e, 0x3c, 0xf9, 0xe3, 0xcf, 0x1f, 0x78, 0x7b, 0xc3,
    0xfe, 0x0f,
    /* U+004C "L" (10x16) */
    0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c,
    0x0f, 0x03, 0xc0, 0xf0, 0x3f, 0xff, 0xff, 0xff,
    /* U+004D "M" (16x16) */
    0x7c, 0x7e, 0x7c, 0x7e, 0xfc, 0x7e, 0xfc, 0x7e, 0xfe, 0x7e, 0xfe, 0x7e,
    0xfe, 0xfe, 0xfe, 0xee, 0xfe, 0xee, 0xf6, 0xee, 0xf7, 0xce, 0xf7, 0xcf,
    0xf7, 0xcf, 0xf7, 0xcf, 0xf3, 0xcf, 0xf0, 0x0f,
    /* U+004E "N" (12x16) */
    0xfc, 0xff, 0xcf, 0xfc, 0xff, 0xcf, 0xfe, 0xff, 0xef, 0xfe, 0xff, 0xff,
    0xf7, 0x7f, 0x7f, 0xf7, 0xff, 0x7f, 0xf3, 0xff, 0x3f, 0xf3, 0xff, 0x1f,
    /* U+004F "O" (14x16) */
    0x0f, 0x80, 0xff, 0x87, 0xff, 0x1e, 0x3e, 0xf8, 0x7b, 0xc1, 0xef, 0x07,
    0xbc, 0x1f, 0xf0, 0x7f, 0xc1, 0xef, 0x07, 0xbe, 0x1e, 0xf8, 0xf9, 0xff,
    0xc3, 0xfe, 0x03, 0xe0,
    /* U+0050 "P" (12x16) */
    0xff, 0x0f, 0xfc, 0xff, 0xef, 0x1f, 0xf1, 0xff, 0x0f, 0xf1, 0xff, 0x1e,
    0xff, 0xef, 0xfc, 0xff, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00,
    /* U+0051 "Q" (14x19) */
    0x0f, 0x80, 0xff, 0x87, 0xff, 0x3e, 0x3e, 0xf8, 0x7b, 0xc1, 0xef, 0x07,
    0xbc, 0x1f, 0xf0, 0x7f, 0xc1, 0xef, 0x07, 0xbe, 0x1e, 0xf8, 0xf1, 0xff,
    0x83, 0xfe, 0x03, 0xff, 0x00, 0x7c, 0x00, 0xf0, 0x01, 0x80,
    /* U+0052 "R" (13x16) */
    0xff, 0x87, 0xfe, 0x3f, 0xf9, 0xe3, 0xef, 0x1f, 0x78, 0xfb, 0xc7, 0xdf,
    0xfc, 0xff, 0xc7, 0xfc, 0x3c, 0xf1, 0xe7, 0x8f, 0x1e, 0x78, 0xfb, 0xc3,
    0xde, 0x1f,
    /* U+0053 "S" (12x16) */
    0x0f, 0x83, 0xfe, 0x7f, 0xf7, 0x86, 0x78, 0x07, 0xc0, 0x7f, 0x03, 0xfc,
    0x0f, 0xe0, 0x3f, 0x01, 0xf0, 0x0f, 0x71, 0xff, 0xff, 0x7f, 0xe1, 0xf8,
    /* U+0054 "T" (12x16) */
    0xff, 0xff, 0xff, 0xff, 0xf0, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0,
    /* U+0055 "U" (12x16) */
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f,
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x0f, 0xf9, 0xf7, 0xfe, 0x7f, 0xe1, 0xf8,
    /* U+0056 "V" (13x16) */
    0xf0, 0x7f, 0x87, 0xfe, 0x3f, 0xf1, 0xe7, 0x8f, 0x3c, 0x79, 0xe3, 0xcf,
    0xbc, 0x3d, 0xe1, 0xef, 0x0f, 0x78, 0x7f, 0x81, 0xfc, 0x0f, 0xe0, 0x7f,
    0x03, 0xf0,
    /* U+0057 "W" (18x16) */
    0xf1, 0xf3, 0xfc, 0x7c, 0xff, 0x9f, 0x3d, 0xe7, 0xcf, 0x79, 0xf3, 0xde,
    0xfc, 0xf7, 0xbb, 0x3d, 0xee, 0xcf, 0x7b, 0xbb, 0x9e, 0xee, 0xe3, 0xb3,
    0xf8, 0xfc, 0xfe, 0x3f, 0x3f, 0x8f, 0xcf, 0xe3, 0xf1, 0xf8, 0xfc, 0x7c,
    /* U+0058 "X" (13x16) */
    0xf8, 0xfb, 0xc7, 0x9f, 0x7c, 0x7b, 0xc3, 0xfe, 0x0f, 0xe0, 0x7f, 0x01,
    0xf0, 0x1f, 0xc0, 0xfe, 0x0f, 0xf8, 0x7b, 0xc7, 0xdf, 0x3c, 0x7b, 0xe3,
    0xff, 0x1f,
    /* U+0059 "Y" (13x16) */
    0xf8, 0x7f, 0xc3, 0xde, 0x3c, 0xf9, 0xe3, 0xcf, 0x1e, 0xf0, 0x7f, 0x83,
    0xf8, 0x0f, 0xc0, 0x7c, 0x03, 0xe0, 0x1f, 0x00, 0xf8, 0x07, 0xc0, 0x3e,
    0x01, 0xf0,
    /* U+005A "Z" (12x16) */
    0x7f, 0xe7, 0xfe, 0x7f, 0xe0, 0x3e, 0x03, 0xc0, 0x7c, 0x0f, 0x80, 0xf8,
    0x1f, 0x01, 0xe0, 0x3e, 0x07, 0xc0, 0x78, 0x0f, 0xff, 0xff, 0xef, 0xfe,
    /* U+005B "[" (7x22) */
    0xff, 0xff, 0xff, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e,
    0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0xff, 0xff, 0xc0,
    /* U+005C "" (9x23) */
    0x10, 0x78, 0x3c, 0x0f, 0x07, 0x83, 0xc1, 0xe0, 0x78, 0x3c, 0x1e, 0x0f,
    0x03, 0xc1, 0xe0, 0xf0, 0x78, 0x1e, 0x0f, 0x07, 0x83, 0xc0, 0xf0, 0x78,
    0x3c, 0x18,
    /* U+005D "]" (7x22) */
    0xff, 0xff, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xff, 0xc0,
    /* U+005E "^" (12x7) */
    0x0f, 0x81, 0xf8, 0x1f, 0xc3, 0xdc, 0x39, 0xe7, 0x8e, 0xf0, 0xf0,
    /* U+005F "_" (11x3) */
    0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+0060 "`" (6x5) */
    0x41, 0xcf, 0x9f, 0x0c,
    /* U+0061 "a" (11x13) */
    0x1f, 0x8f, 0xf8, 0xff, 0x81, 0xf0, 0x1e, 0x3f, 0xdf, 0xfb, 0xcf, 0xf9,
    0xff, 0x7d, 0xff, 0xbf, 0xf3, 0xc6,
    /* U+0062 "b" (11x18) */
    0xf0, 0x1e, 0x03, 0xc0, 0x78, 0x0f, 0x01, 0xe7, 0x3f, 0xf7, 0xff, 0xf9,
    0xfe, 0x3f, 0xc7, 0xf8, 0xff, 0x1f, 0xe3, 0xfe, 0x7f, 0xff, 0xff, 0xde,
    0xf0,
    /* U+0063 "c" (9x13) */
    0x1f, 0x1f, 0xdf, 0xff, 0x2f, 0x07, 0x83, 0xc1, 0xe0, 0xf0, 0x7c, 0x1f,
    0xef, 0xf1, 0xf0,
    /* U+0064 "d" (11x18) */
    0x01, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x1e, 0x7b, 0xdf, 0xff, 0xff, 0xf9,
    0xfe, 0x3f, 0xc7, 0xf8, 0xff, 0x1f, 0xe3, 0xfe, 0xff, 0xff, 0x7f, 0xe7,
    0xbc,
    /* U+0065 "e" (11x13) */
    0x1f, 0x0f, 0xf1, 0xff, 0x79, 0xef, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0x1e, 0x11, 0xff, 0x3f, 0xe1, 0xf0,
    /* U+0066 "f" (10x18) */
    0x0f, 0x87, 0xf3, 0xf8, 0xf0, 0x3c, 0x3f, 0xcf, 0xf3, 0xfc, 0x3c, 0x0f,
    0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x00,
    /* U+0067 "g" (12x19) */
    0x00, 0x71, 0xff, 0x3f, 0xf7, 0xfc, 0x79, 0xef, 0x9e, 0x79, 0xe7, 0xfe,
    0x3f, 0xc3, 0xf8, 0x78, 0x07, 0xfc, 0x7f, 0xe3, 0xff, 0x00, 0xff, 0x0f,
    0xff, 0xf7, 0xfe, 0x3f, 0x80,
    /* U+0068 "h" (11x18) */
    0x70, 0x1e, 0x03, 0xc0, 0x78, 0x0f, 0x01, 0xe7, 0x3f, 0xf7, 0xfe, 0xfb,
    0xde, 0x7f, 0xcf, 0xf9, 0xff, 0x3f, 0xe7, 0xfc, 0xff, 0x9f, 0xf3, 0xfe,
    0x7c,
    /* U+0069 "i" (4x20) */
    0x6f, 0xff, 0x60, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+006A "j" (6x25) */
    0x18, 0xf3, 0xcf, 0x18, 0x00, 0x0f, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf,
    0x3c, 0xf3, 0xcf, 0x7f, 0xff, 0xbc, 0x40,
    /* U+006B "k" (12x18) */
    0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x1e, 0xf1, 0xef, 0x3c,
    0xf3, 0xcf, 0x78, 0xff, 0x8f, 0xf8, 0xf7, 0x8f, 0x7c, 0xf3, 0xcf, 0x3e,
    0xf1, 0xef, 0x1f,
    /* U+006C "l" (6x18) */
    0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3e,
    0xfd, 0xf0,
    /* U+006D "m" (16x13) */
    0xf7, 0x9e, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xef, 0xf3, 0xcf, 0xf3, 0xcf,
    0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf, 0xf3, 0xcf,
    0xf3, 0xcf,
    /* U+006E "n" (10x13) */
    0xf3, 0xbf, 0xff, 0xff, 0xef, 0xf1, 0xfc, 0x7f, 0x1f, 0xc7, 0xf1, 0xfc,
    0x7f, 0x1f, 0xc7, 0xf1, 0xc0,
    /* U+006F "o" (11x13) */
    0x1f, 0x0f, 0xf9, 0xff, 0x79, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xfe, 0x7f, 0xff, 0x3f, 0xe1, 0xf0,
    /* U+0070 "p" (11x18) */
    0xf7, 0x9f, 0xfb, 0xff, 0xfc, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xff, 0x3f, 0xff, 0xff, 0xef, 0x79, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x1c,
    0x00,
    /* U+0071 "q" (11x18) */
    0x3d, 0xef, 0xff, 0xff, 0xfc, 0xff, 0x1f, 0xe3, 0xfc, 0x7f, 0x8f, 0xf1,
    0xff, 0x7f, 0xff, 0xbf, 0xf3, 0xde, 0x03, 0xc0, 0x78, 0x0f, 0x01, 0xe0,
    0x3c,
    /* U+0072 "r" (8x13) */
    0xf3, 0xf7, 0xff, 0xfe, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
    0xf0,
    /* U+0073 "s" (10x13) */
    0x1f, 0x1f, 0xf7, 0xf9, 0xe2, 0x78, 0x1f, 0xc3, 0xf8, 0x3f, 0x03, 0xd8,
    0xff, 0xff, 0xfe, 0x3f, 0x00,
    /* U+0074 "t" (9x16) */
    0x7c, 0x3e, 0x1f, 0x1f, 0xef, 0xf7, 0xf9, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f,
    0x0f, 0x87, 0xc1, 0xf8, 0xfe, 0x3e,
    /* U+0075 "u" (10x13) */
    0xf3, 0xfc, 0xff, 0x3f, 0xcf, 0xf3, 0xfc, 0xff, 0x3f, 0xcf, 0xf3, 0xfc,
    0xff, 0xfd, 0xff, 0x79, 0xc0,
    /* U+0076 "v" (12x13) */
    0xf1, 0xff, 0x1e, 0xf9, 0xe7, 0x9e, 0x79, 0xc7, 0x9c, 0x3b, 0xc3, 0xbc,
    0x3f, 0x83, 0xf8, 0x1f, 0x81, 0xf8, 0x1f, 0x00,
    /* U+0077 "w" (17x13) */
    0xf3, 0xc7, 0xf9, 0xf3, 0xbc, 0xf9, 0xce, 0x7d, 0xe7, 0x3e, 0xf3, 0xdf,
    0x79, 0xed, 0xbc, 0xfe, 0xdc, 0x3f, 0x7e, 0x1f, 0xbf, 0x0f, 0x9f, 0x87,
    0xcf, 0xc3, 0xe3, 0xe0,
    /* U+0078 "x" (12x13) */
    0xf9, 0xe7, 0xbc, 0x7b, 0xc3, 0xf8, 0x3f, 0x81, 0xf0, 0x1f, 0x03, 0xf8,
    0x3f, 0x87, 0xbc, 0x7b, 0xef, 0x9e, 0xf1, 0xf0,
    /* U+0079 "y" (12x18) */
    0xf0, 0xff, 0x1e, 0xf1, 0xe7, 0x9e, 0x79, 0xe7, 0x9c, 0x7b, 0xc3, 0xbc,
    0x3b, 0xc3, 0xf8, 0x3f, 0x81, 0xf8, 0x1f, 0x00, 0xf0, 0x1f, 0x07, 0xe0,
    0x7c, 0x07, 0x00,
    /* U+007A "z" (10x13) */
    0x7f, 0xdf, 0xf7, 0xfc, 0x1e, 0x0f, 0x87, 0xc1, 0xe0, 0xf8, 0x7c, 0x1e,
    0x0f, 0xff, 0xff, 0xff, 0xc0,
    /* U+007B "{" (7x23) */
    0x1e, 0x7c, 0xfb, 0xe7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xe7, 0x8f, 0x8f,
    0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xe3, 0xe7, 0xc7, 0x80,
    /* U+007C "|" (4x22) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (7x23) */
    0xf1, 0xf3, 0xe3, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf8, 0x73, 0xe7,
    0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xef, 0x9f, 0x3c, 0x00,
    /* U+007E "~" (10x4) */
    0x78, 0xbf, 0xff, 0xfb, 0x3c,
    /* U+00B0 "" (8x8) */
    0x7c, 0xfe, 0xe7, 0xc7, 0xe7, 0xfe, 0x7e, 0x3c,
    /* U+00B1 "" (10x15) */
    0x1e, 0x07, 0x81, 0xe3, 0xff, 0xff, 0xff, 0xf1, 0xe0, 0x78, 0x1e, 0x07,
    0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfc,
    /* U+00B2 "" (7x10) */
    0x7d, 0xfd, 0x78, 0x71, 0xe7, 0x9e, 0x78, 0xff, 0xfc,
    /* U+00B3 "" (7x10) */
    0x7d, 0xfd, 0x38, 0x73, 0xc7, 0x83, 0xa7, 0xfe, 0xf8,
    /* U+00B5 "" (11x18) */
    0xf3, 0xde, 0x7b, 0xcf, 0x79, 0xef, 0x3d, 0xe7, 0xbc, 0xf7, 0x9e, 0xf3,
    0xde, 0x7b, 0xff, 0xff, 0xff, 0xdf, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x1e,
    0x00,
    /* U+00B7 "" (4x4) */
    0xef, 0xfe,
    /* U+00D7 "" (9x9) */
    0x63, 0x79, 0xdf, 0xef, 0xe3, 0xe1, 0xf9, 0xff, 0xef, 0x63, 0x80,
    /* U+00F7 "" (10x16) */
    0x1c, 0x07, 0x81, 0xe0, 0x70, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0xff,
    0xf0, 0x00, 0x00, 0x1c, 0x07, 0x81, 0xe0, 0x70,
    /* U+0394 "" (14x16) */
    0x0f, 0x80, 0x3f, 0x01, 0xfc, 0x07, 0xf0, 0x1d, 0xe0, 0x77, 0x83, 0xde,
    0x0f, 0x38, 0x3c, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0x7b, 0xff,
    0xef, 0xff, 0xbf, 0xff,
    /* U+03A9 "" (13x16) */
    0x0f, 0x81, 0xff, 0x1f, 0xfd, 0xf1, 0xff, 0x07, 0xf8, 0x3f, 0xc1, 0xfe,
    0x0f, 0xf0, 0x7f, 0x83, 0xfc, 0x1e, 0xe0, 0xe3, 0x8e, 0x7e, 0xff, 0xf7,
    0xff, 0xbf,
    /* U+03B1 "" (12x13) */
    0x1c, 0xe7, 0xee, 0xff, 0xef, 0x3e, 0xf3, 0xcf, 0x1c, 0xf1, 0xcf, 0x1c,
    0xf3, 0xcf, 0x3e, 0xff, 0xf7, 0xee, 0x3c, 0x60,
    /* U+03B2 "" (12x23) */
    0x1f, 0x07, 0xf8, 0x7f, 0xcf, 0x3e, 0xf1, 0xef, 0x1c, 0xf3, 0xcf, 0x78,
    0xf7, 0x8f, 0x7e, 0xf1, 0xef, 0x0f, 0xf0, 0xff, 0x0f, 0xf1, 0xff, 0xfe,
    0xff, 0xef, 0x78, 0xf0, 0x0f, 0x00, 0xf0, 0x0f, 0x00, 0xe0, 0x00,
    /* U+03B3 "" (11x18) */
    0x71, 0xfe, 0x3f, 0xe7, 0xbc, 0xf7, 0x9c, 0x77, 0x8e, 0xf1, 0xfc, 0x1f,
    0x83, 0xf0, 0x7c, 0x0f, 0x80, 0xf0, 0x1c, 0x07, 0x80, 0xf0, 0x1e, 0x01,
    0xc0,
    /* U+03B4 "" (11x18) */
    0x1f, 0x07, 0xf9, 0xfe, 0x3c, 0x07, 0x80, 0xf8, 0x0f, 0xc1, 0xfe, 0x7f,
    0xde, 0x7f, 0xc7, 0xf8, 0xff, 0x1f, 0xe3, 0xfc, 0xff, 0xfe, 0x7f, 0x83,
    0xe0,
    /* U+03B5 "" (9x13) */
    0x3f, 0x3f, 0xff, 0xfe, 0x0f, 0x03, 0xf0, 0xf9, 0xfc, 0xf0, 0x78, 0x3f,
    0xff, 0xf3, 0xf0,
    /* U+03B8 "" (11x18) */
    0x1e, 0x07, 0xf1, 0xfe, 0x79, 0xef, 0x1d, 0xc3, 0xb8, 0x7f, 0x0f, 0xff,
    0xff, 0xff, 0x87, 0xf0, 0xff, 0x1d, 0xe3, 0xbc, 0xf3, 0xfc, 0x3f, 0x83,
    0xc0,
    /* U+03BB "" (12x18) */
    0x38, 0x07, 0xe0, 0x3f, 0x00, 0xf0, 0x07, 0x81, 0xf8, 0x1f, 0x81, 0xf8,
    0x1f, 0x83, 0xfc, 0x3b, 0xc3, 0xbc, 0x79, 0xe7, 0x9e, 0x79, 0xe7, 0x9f,
    0xf0, 0xf3, 0x0c,
    /* U+03BC "" (11x18) */
    0xf3, 0xde, 0x7b, 0xcf, 0x79, 0xef, 0x3d, 0xe7, 0xbc, 0xf7, 0x9e, 0xf3,
    0xde, 0x7b, 0xff, 0xff, 0xff, 0xdf, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x1e,
    0x00,
    /* U+03C0 "" (13x13) */
    0xff, 0xff, 0xff, 0xff, 0xfe, 0x79, 0xe3, 0xcf, 0x1e, 0x78, 0xf3, 0xc7,
    0x9e, 0x3c, 0xf1, 0xe7, 0x8f, 0x3e, 0x79, 0xe3, 0xc7, 0x00,
    /* U+03C3 "" (12x13) */
    0x1f, 0xf7, 0xff, 0x7f, 0xff, 0x9c, 0xf1, 0xef, 0x1e, 0xf1, 0xef, 0x1e,
    0xf1, 0xef, 0x3e, 0x7f, 0xc7, 0xfc, 0x1f, 0x00,
    /* U+03C4 "" (11x13) */
    0xff, 0xff, 0xff, 0xff, 0x8f, 0x01, 0xe0, 0x3c, 0x07, 0x80, 0xf0, 0x1f,
    0x03, 0xe0, 0x3c, 0x07, 0x80, 0x20,
    /* U+03C6 "" (15x18) */
    0x78, 0xf1, 0xe3, 0xfb, 0xcf, 0xf7, 0x9c, 0xff, 0x79, 0xfe, 0xf3, 0xfd,
    0xe7, 0xfb, 0xcf, 0xf7, 0x9f, 0xef, 0x3f, 0xfe, 0xf3, 0xff, 0xe3, 0xff,
    0x81, 0xf8, 0x01, 0xe0, 0x03, 0xc0, 0x07, 0x80, 0x0f, 0x00,
    /* U+03C9 "" (15x13) */
    0x70, 0x3d, 0xe0, 0x3b, 0xc0, 0x7f, 0x80, 0xff, 0x39, 0xfe, 0x73, 0xfc,
    0xe7, 0xf9, 0xcf, 0xf3, 0x9f, 0xef, 0x3f, 0xff, 0xfb, 0xf7, 0xe3, 0xc7,
    0x80,
    /* U+2013 "" (11x3) */
    0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+2014 "" (17x3) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,
    /* U+2018 "" (4x7) */
    0x37, 0x6e, 0xff, 0x60,
    /* U+2019 "" (4x7) */
    0xef, 0xfe, 0xec, 0xc0,
    /* U+201C "" (9x7) */
    0x31, 0xb9, 0xd8, 0xdc, 0xef, 0x7f, 0xbd, 0x8c,
    /* U+201D "" (9x7) */
    0xe3, 0x7b, 0xfd, 0xfc, 0x6e, 0x36, 0x3b, 0x18,
    /* U+2022 "" (6x7) */
    0x7b, 0xff, 0xff, 0xff, 0xf7, 0x80,
    /* U+2026 "" (15x4) */
    0xe3, 0x8d, 0xef, 0x3f, 0xde, 0x7f, 0x1c, 0xe0,
    /* U+2030 "" (26x16) */
    0x3c, 0x0c, 0x00, 0x3f, 0x87, 0x80, 0x0f, 0xe3, 0xc0, 0x03, 0x9c, 0xe0,
    0x00, 0xe7, 0x78, 0x00, 0x3f, 0x9c, 0x00, 0x0f, 0xee, 0x00, 0x00, 0xf7,
    0xbc, 0x3c, 0x01, 0xff, 0x9f, 0x80, 0xef, 0xe7, 0xf0, 0x7b, 0xbf, 0x9c,
    0x1c, 0xc7, 0xe7, 0x0e, 0x31, 0xf9, 0xc7, 0x8e, 0xef, 0x71, 0xc3, 0xf9,
    0xf8, 0x70, 0x3c, 0x3c,
    /* U+2190 "" (18x16) */
    0x03, 0x00, 0x00, 0xe0, 0x00, 0x7c, 0x00, 0x3e, 0x00, 0x1f, 0x00, 0x0f,
    0x80, 0x07, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xe3, 0xc0,
    0x00, 0x7c, 0x00, 0x0f, 0x00, 0x03, 0xe0, 0x00, 0x78, 0x00, 0x0c, 0x00,
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
    {.bitmap_index = 0, .adv_w = 77, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 88, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 168, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 15, .adv_w = 199, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 194, .box_w = 12, .box_h = 23, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 74, .adv_w = 307, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 270, .box_w = 15, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 144, .adv_w = 116, .box_w = 7, .box_h = 24, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 165, .adv_w = 116, .box_w = 7, .box_h = 24, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 186, .adv_w = 161, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 199, .adv_w = 189, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 212, .adv_w = 87, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 216, .adv_w = 145, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 219, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 180, .box_w = 9, .box_h = 22, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 246, .adv_w = 213, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 166, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 180, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 184, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 201, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 192, .box_w = 11, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 204, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 166, .box_w = 10, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 206, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 203, .box_w = 12, .box_h = 17, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 468, .adv_w = 89, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 89, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 482, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 497, .adv_w = 183, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 509, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 524, .adv_w = 172, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 355, .box_w = 20, .box_h = 21, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 597, .adv_w = 211, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 216, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 204, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 230, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 181, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 169, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 228, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 230, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 104, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 113, .box_w = 6, .box_h = 20, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 804, .adv_w = 228, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 180, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 850, .adv_w = 278, .box_w = 16, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 228, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 906, .adv_w = 242, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 934, .adv_w = 212, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 242, .box_w = 14, .box_h = 19, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 992, .adv_w = 217, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 203, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 191, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1066, .adv_w = 225, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1090, .adv_w = 203, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1116, .adv_w = 299, .box_w = 18, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1152, .adv_w = 209, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 213, .box_w = 13, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 192, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1228, .adv_w = 114, .box_w = 7, .box_h = 22, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1248, .adv_w = 180, .box_w = 9, .box_h = 23, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1274, .adv_w = 114, .box_w = 7, .box_h = 22, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1294, .adv_w = 198, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 12},
    {.bitmap_index = 1305, .adv_w = 181, .box_w = 11, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1310, .adv_w = 127, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 15},
    {.bitmap_index = 1314, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1332, .adv_w = 209, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1357, .adv_w = 168, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1372, .adv_w = 210, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1397, .adv_w = 196, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1415, .adv_w = 129, .box_w = 10, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1438, .adv_w = 194, .box_w = 12, .box_h = 19, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1467, .adv_w = 200, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1492, .adv_w = 100, .box_w = 4, .box_h = 20, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1502, .adv_w = 100, .box_w = 6, .box_h = 25, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1521, .adv_w = 200, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1548, .adv_w = 106, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1562, .adv_w = 292, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1588, .adv_w = 200, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1605, .adv_w = 206, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1623, .adv_w = 209, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1648, .adv_w = 210, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1673, .adv_w = 142, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1686, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1703, .adv_w = 138, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1721, .adv_w = 199, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1738, .adv_w = 183, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1758, .adv_w = 268, .box_w = 17, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1786, .adv_w = 183, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1806, .adv_w = 186, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1833, .adv_w = 163, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1850, .adv_w = 113, .box_w = 7, .box_h = 23, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1871, .adv_w = 125, .box_w = 4, .box_h = 22, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1882, .adv_w = 113, .box_w = 7, .box_h = 23, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1903, .adv_w = 185, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1908, .adv_w = 179, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1916, .adv_w = 189, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1935, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1944, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1953, .adv_w = 202, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1978, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1980, .adv_w = 183, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1991, .adv_w = 183, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2011, .adv_w = 214, .box_w = 14, .box_h = 16, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2039, .adv_w = 238, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2065, .adv_w = 211, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2085, .adv_w = 214, .box_w = 12, .box_h = 23, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2120, .adv_w = 182, .box_w = 11, .box_h = 18, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 2145, .adv_w = 203, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2170, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2185, .adv_w = 196, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2210, .adv_w = 190, .box_w = 12, .box_h = 18, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2237, .adv_w = 202, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2262, .adv_w = 216, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2284, .adv_w = 212, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2304, .adv_w = 171, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2322, .adv_w = 268, .box_w = 15, .box_h = 18, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 2356, .adv_w = 269, .box_w = 15, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2381, .adv_w = 183, .box_w = 11, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2386, .adv_w = 279, .box_w = 17, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 2393, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2397, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2401, .adv_w = 172, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2409, .adv_w = 172, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 2417, .adv_w = 130, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 2423, .adv_w = 266, .box_w = 15, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2431, .adv_w = 445, .box_w = 26, .box_h = 16, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2483, .adv_w = 346, .box_w = 18, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2519, .adv_w = 346, .box_w = 16, .box_h = 17, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2553, .adv_w = 346, .box_w = 18, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2589, .adv_w = 346, .box_w = 16, .box_h = 17, .ofs_x = 3, .ofs_y = -1}
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
    2, 32, 3, 4, 3, 13, 3, 15, 3, 16, 3, 17, 3, 21, 3, 23,
    3, 25, 3, 33, 3, 34, 3, 43, 3, 59, 3, 64, 3, 66, 3, 68,
    3, 69, 3, 70, 3, 80, 3, 82, 3, 84, 3, 91, 3, 104, 3, 106,
    3, 109, 3, 110, 3, 112, 3, 115, 3, 117, 3, 118, 3, 126, 4, 11,
    4, 24, 4, 64, 4, 87, 4, 90, 4, 108, 5, 18, 5, 61, 5, 64,
    6, 3, 6, 8, 6, 11, 6, 18, 6, 32, 6, 61, 6, 121, 6, 122,
    6, 123, 6, 124, 7, 3, 7, 6, 7, 8, 7, 11, 7, 16, 7, 18,
    7, 21, 7, 22, 7, 24, 7, 26, 7, 32, 7, 33, 7, 53, 7, 55,
    7, 56, 7, 58, 7, 61, 7, 71, 7, 87, 7, 88, 7, 90, 7, 108,
    7, 114, 7, 116, 7, 121, 7, 122, 7, 123, 7, 124, 7, 125, 7, 127,
    8, 4, 8, 13, 8, 15, 8, 16, 8, 17, 8, 21, 8, 23, 8, 25,
    8, 33, 8, 34, 8, 43, 8, 59, 8, 64, 8, 66, 8, 68, 8, 69,
    8, 70, 8, 80, 8, 82, 8, 84, 8, 91, 8, 104, 8, 106, 8, 109,
    8, 110, 8, 112, 8, 115, 8, 117, 8, 118, 8, 126, 9, 43, 9, 64,
    9, 75, 11, 2, 11, 13, 11, 15, 11, 16, 11, 18, 11, 19, 11, 21,
    11, 24, 11, 33, 11, 34, 11, 64, 11, 71, 11, 85, 11, 87, 11, 88,
    11, 90, 11, 98, 11, 99, 11, 104, 11, 108, 11, 114, 11, 116, 11, 126,
    12, 5, 12, 6, 12, 7, 12, 13, 12, 15, 12, 16, 12, 18, 12, 19,
    12, 20, 12, 24, 12, 32, 12, 52, 12, 53, 12, 55, 12, 57, 12, 58,
    12, 59, 12, 61, 12, 64, 12, 66, 12, 71, 12, 89, 12, 91, 12, 112,
    12, 116, 12, 126, 12, 127, 13, 3, 13, 6, 13, 8, 13, 11, 13, 12,
    13, 14, 13, 18, 13, 20, 13, 22, 13, 32, 13, 34, 13, 53, 13, 55,
    13, 58, 13, 59, 13, 61, 13, 62, 13, 84, 13, 89, 13, 91, 13, 95,
    13, 98, 13, 99, 13, 101, 13, 103, 13, 104, 13, 116, 13, 119, 13, 120,
    13, 121, 13, 122, 13, 123, 13, 124, 13, 127, 14, 5, 14, 7, 14, 13,
    14, 15, 14, 16, 14, 18, 14, 19, 14, 20, 14, 24, 14, 32, 14, 52,
    14, 53, 14, 57, 14, 58, 14, 59, 14, 61, 14, 64, 14, 89, 14, 91,
    14, 112, 14, 126, 15, 3, 15, 6, 15, 7, 15, 8, 15, 11, 15, 12,
    15, 14, 15, 17, 15, 18, 15, 21, 15, 23, 15, 26, 15, 32, 15, 36,
    15, 40, 15, 48, 15, 50, 15, 53, 15, 54, 15, 55, 15, 56, 15, 58,
    15, 61, 15, 68, 15, 69, 15, 70, 15, 71, 15, 72, 15, 80, 15, 82,
    15, 85, 15, 86, 15, 87, 15, 88, 15, 90, 15, 95, 15, 98, 15, 99,
    15, 101, 15, 103, 15, 106, 15, 108, 15, 109, 15, 111, 15, 114, 15, 115,
    15, 116, 15, 117, 15, 118, 15, 119, 15, 120, 15, 121, 15, 122, 15, 123,
    15, 124, 15, 127, 16, 7, 16, 12, 16, 13, 16, 14, 16, 15, 16, 16,
    16, 18, 16, 19, 16, 21, 16, 26, 16, 27, 16, 28, 16, 32, 16, 33,
    16, 64, 16, 66, 16, 68, 16, 69, 16, 70, 16, 80, 16, 82, 16, 95,
    16, 101, 16, 103, 16, 106, 16, 109, 16, 110, 16, 112, 16, 114, 16, 115,
    16, 116, 16, 117, 16, 118, 16, 119, 16, 120, 16, 126, 20, 16, 20, 18,
    20, 19, 20, 24, 20, 26, 20, 32, 20, 53, 20, 58, 20, 61, 20, 64,
    21, 3, 21, 5, 21, 6, 21, 8, 21, 11, 21, 12, 21, 14, 21, 16,
    21, 18, 21, 19, 21, 20, 21, 22, 21, 24, 21, 26, 21, 32, 21, 43,
    21, 52, 21, 53, 21, 55, 21, 56, 21, 58, 21, 61, 21, 71, 21, 87,
    21, 89, 21, 90, 21, 95, 21, 101, 21, 103, 21, 108, 21, 114, 21, 116,
    21, 119, 21, 120, 21, 121, 21, 122, 21, 123, 21, 124, 21, 127, 22, 3,
    22, 8, 22, 18, 22, 24, 22, 53, 22, 55, 22, 58, 22, 61, 22, 116,
    22, 121, 22, 122, 22, 123, 22, 124, 23, 3, 23, 8, 23, 11, 23, 16,
    23, 18, 23, 24, 23, 26, 23, 32, 23, 53, 23, 55, 23, 58, 23, 61,
    23, 64, 23, 116, 23, 121, 23, 122, 23, 123, 23, 124, 24, 2, 24, 3,
    24, 6, 24, 8, 24, 11, 24, 13, 24, 15, 24, 16, 24, 24, 24, 64,
    24, 96, 24, 98, 24, 99, 24, 121, 24, 122, 24, 123, 24, 124, 24, 126,
    24, 127, 25, 18, 25, 32, 25, 53, 25, 58, 25, 61, 25, 64, 25, 116,
    26, 5, 26, 13, 26, 15, 26, 16, 26, 18, 26, 19, 26, 20, 26, 32,
    26, 34, 26, 43, 26, 52, 26, 53, 26, 58, 26, 59, 26, 61, 26, 64,
    26, 66, 26, 104, 26, 112, 26, 126, 27, 18, 27, 21, 27, 24, 27, 32,
    27, 53, 27, 55, 27, 58, 27, 61, 28, 18, 28, 21, 28, 24, 28, 32,
    28, 53, 28, 55, 28, 58, 28, 61, 32, 4, 32, 7, 32, 12, 32, 13,
    32, 14, 32, 15, 32, 16, 32, 21, 32, 32, 32, 64, 32, 95, 32, 101,
    32, 103, 32, 119, 32, 120, 32, 126, 33, 11, 33, 13, 33, 15, 33, 18,
    33, 24, 33, 32, 33, 53, 33, 57, 33, 58, 33, 61, 33, 64, 33, 126,
    34, 3, 34, 8, 34, 11, 34, 18, 34, 19, 34, 32, 34, 53, 34, 58,
    34, 62, 34, 94, 34, 116, 34, 121, 34, 122, 34, 123, 34, 124, 35, 3,
    35, 5, 35, 8, 35, 11, 35, 18, 35, 19, 35, 21, 35, 22, 35, 24,
    35, 26, 35, 32, 35, 34, 35, 43, 35, 52, 35, 53, 35, 55, 35, 56,
    35, 57, 35, 58, 35, 59, 35, 61, 35, 64, 35, 89, 35, 104, 35, 116,
    35, 121, 35, 122, 35, 123, 35, 124, 36, 7, 36, 12, 36, 14, 36, 17,
    36, 18, 36, 21, 36, 23, 36, 25, 36, 26, 36, 29, 36, 30, 36, 31,
    36, 33, 36, 36, 36, 40, 36, 43, 36, 48, 36, 50, 36, 58, 36, 61,
    36, 68, 36, 69, 36, 70, 36, 71, 36, 72, 36, 75, 36, 80, 36, 82,
    36, 85, 36, 86, 36, 87, 36, 88, 36, 90, 36, 95, 36, 101, 36, 102,
    36, 103, 36, 105, 36, 106, 36, 108, 36, 109, 36, 110, 36, 111, 36, 114,
    36, 115, 36, 116, 36, 117, 36, 118, 36, 119, 36, 120, 36, 125, 37, 58,
    37, 64, 38, 11, 38, 116, 39, 4, 39, 5, 39, 7, 39, 12, 39, 13,
    39, 14, 39, 15, 39, 16, 39, 17, 39, 18, 39, 19, 39, 21, 39, 22,
    39, 23, 39, 25, 39, 26, 39, 27, 39, 28, 39, 29, 39, 30, 39, 31,
    39, 33, 39, 34, 39, 36, 39, 40, 39, 43, 39, 46, 39, 48, 39, 50,
    39, 52, 39, 58, 39, 59, 39, 64, 39, 66, 39, 67, 39, 68, 39, 69,
    39, 70, 39, 71, 39, 72, 39, 73, 39, 74, 39, 75, 39, 76, 39, 77,
    39, 78, 39, 79, 39, 80, 39, 81, 39, 82, 39, 83, 39, 84, 39, 85,
    39, 86, 39, 87, 39, 88, 39, 89, 39, 90, 39, 91, 39, 95, 39, 100,
    39, 101, 39, 102, 39, 103, 39, 104, 39, 105, 39, 106, 39, 107, 39, 108,
    39, 109, 39, 110, 39, 112, 39, 113, 39, 114, 39, 115, 39, 116, 39, 117,
    39, 118, 39, 119, 39, 120, 39, 126, 40, 18, 44, 12, 44, 14, 44, 18,
    44, 62, 44, 95, 44, 101, 44, 103, 44, 116, 44, 119, 44, 120, 45, 3,
    45, 8, 45, 11, 45, 12, 45, 14, 45, 18, 45, 24, 45, 26, 45, 32,
    45, 36, 45, 40, 45, 48, 45, 50, 45, 53, 45, 55, 45, 56, 45, 58,
    45, 61, 45, 71, 45, 87, 45, 88, 45, 90, 45, 95, 45, 98, 45, 99,
    45, 101, 45, 103, 45, 108, 45, 119, 45, 120, 45, 121, 45, 122, 45, 123,
    45, 124, 45, 125, 48, 53, 48, 58, 48, 64, 49, 7, 49, 13, 49, 15,
    49, 16, 49, 21, 49, 32, 49, 34, 49, 43, 49, 57, 49, 58, 49, 59,
    49, 61, 49, 64, 49, 66, 49, 104, 49, 112, 49, 126, 50, 53, 50, 58,
    50, 62, 50, 64, 50, 94, 51, 5, 51, 7, 51, 12, 51, 14, 51, 18,
    51, 21, 51, 24, 51, 26, 51, 32, 51, 36, 51, 40, 51, 43, 51, 48,
    51, 50, 51, 52, 51, 53, 51, 54, 51, 55, 51, 58, 51, 59, 51, 61,
    51, 66, 51, 68, 51, 69, 51, 70, 51, 72, 51, 80, 51, 82, 51, 95,
    51, 101, 51, 103, 51, 106, 51, 109, 51, 110, 51, 115, 51, 117, 51, 118,
    51, 119, 51, 120, 51, 125, 52, 3, 52, 5, 52, 8, 52, 18, 52, 19,
    52, 24, 52, 26, 52, 32, 52, 46, 52, 52, 52, 53, 52, 55, 52, 56,
    52, 58, 52, 59, 52, 61, 52, 64, 52, 71, 52, 87, 52, 90, 52, 91,
    52, 98, 52, 99, 52, 108, 52, 121, 52, 122, 52, 123, 52, 124, 53, 4,
    53, 5, 53, 7, 53, 12, 53, 13, 53, 14, 53, 15, 53, 16, 53, 17,
    53, 21, 53, 22, 53, 23, 53, 25, 53, 26, 53, 27, 53, 28, 53, 33,
    53, 34, 53, 36, 53, 40, 53, 46, 53, 48, 53, 50, 53, 52, 53, 61,
    53, 64, 53, 66, 53, 68, 53, 69, 53, 70, 53, 71, 53, 72, 53, 75,
    53, 78, 53, 79, 53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 85,
    53, 86, 53, 87, 53, 88, 53, 89, 53, 90, 53, 91, 53, 95, 53, 100,
    53, 101, 53, 103, 53, 104, 53, 105, 53, 106, 53, 108, 53, 109, 53, 110,
    53, 112, 53, 113, 53, 115, 53, 116, 53, 117, 53, 118, 53, 119, 53, 120,
    53, 125, 53, 126, 54, 64, 55, 4, 55, 5, 55, 7, 55, 12, 55, 13,
    55, 14, 55, 15, 55, 16, 55, 18, 55, 21, 55, 22, 55, 25, 55, 27,
    55, 28, 55, 33, 55, 34, 55, 52, 55, 59, 55, 64, 55, 66, 55, 68,
    55, 69, 55, 70, 55, 71, 55, 72, 55, 78, 55, 79, 55, 80, 55, 81,
    55, 82, 55, 83, 55, 84, 55, 86, 55, 89, 55, 91, 55, 95, 55, 100,
    55, 101, 55, 103, 55, 104, 55, 106, 55, 109, 55, 110, 55, 112, 55, 113,
    55, 115, 55, 117, 55, 118, 55, 119, 55, 120, 55, 125, 55, 126, 56, 5,
    56, 7, 56, 13, 56, 15, 56, 18, 56, 21, 56, 22, 56, 33, 56, 52,
    56, 59, 56, 64, 56, 66, 56, 68, 56, 69, 56, 70, 56, 72, 56, 80,
    56, 82, 56, 84, 56, 86, 56, 89, 56, 91, 56, 106, 56, 109, 56, 112,
    56, 115, 56, 117, 56, 118, 56, 126, 57, 12, 57, 14, 57, 18, 57, 21,
    57, 29, 57, 30, 57, 31, 57, 32, 57, 33, 57, 62, 57, 95, 57, 101,
    57, 102, 57, 103, 57, 116, 57, 119, 57, 120, 57, 125, 58, 3, 58, 4,
    58, 7, 58, 8, 58, 12, 58, 13, 58, 14, 58, 15, 58, 16, 58, 21,
    58, 23, 58, 25, 58, 26, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36,
    58, 40, 58, 48, 58, 50, 58, 62, 58, 64, 58, 66, 58, 68, 58, 69,
    58, 70, 58, 71, 58, 72, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82,
    58, 83, 58, 84, 58, 86, 58, 87, 58, 89, 58, 90, 58, 91, 58, 95,
    58, 100, 58, 101, 58, 103, 58, 104, 58, 106, 58, 108, 58, 109, 58, 110,
    58, 113, 58, 115, 58, 116, 58, 117, 58, 118, 58, 119, 58, 120, 58, 121,
    58, 122, 58, 123, 58, 124, 58, 125, 58, 126, 59, 12, 59, 14, 59, 21,
    59, 23, 59, 36, 59, 40, 59, 48, 59, 50, 59, 61, 59, 72, 59, 95,
    59, 101, 59, 103, 59, 116, 59, 119, 59, 120, 59, 125, 60, 18, 60, 34,
    60, 43, 60, 55, 60, 57, 60, 58, 60, 64, 60, 75, 60, 89, 60, 104,
    61, 3, 61, 6, 61, 7, 61, 8, 61, 11, 61, 12, 61, 14, 61, 18,
    61, 24, 61, 26, 61, 32, 61, 53, 61, 58, 61, 61, 61, 75, 61, 95,
    61, 96, 61, 98, 61, 99, 61, 101, 61, 103, 61, 116, 61, 119, 61, 120,
    61, 121, 61, 122, 61, 123, 61, 124, 61, 127, 64, 3, 64, 6, 64, 8,
    64, 10, 64, 11, 64, 12, 64, 14, 64, 18, 64, 21, 64, 32, 64, 36,
    64, 40, 64, 43, 64, 48, 64, 50, 64, 53, 64, 55, 64, 56, 64, 58,
    64, 61, 64, 62, 64, 72, 64, 75, 64, 94, 64, 95, 64, 98, 64, 99,
    64, 101, 64, 103, 64, 116, 64, 119, 64, 120, 64, 121, 64, 122, 64, 123,
    64, 124, 64, 127, 66, 18, 66, 24, 66, 32, 66, 61, 67, 18, 67, 24,
    67, 32, 67, 61, 67, 116, 68, 7, 68, 12, 68, 14, 68, 17, 68, 18,
    68, 21, 68, 24, 68, 25, 68, 29, 68, 30, 68, 31, 68, 32, 68, 33,
    68, 61, 68, 66, 68, 68, 68, 69, 68, 70, 68, 72, 68, 80, 68, 82,
    68, 86, 68, 95, 68, 101, 68, 102, 68, 103, 68, 106, 68, 109, 68, 110,
    68, 111, 68, 115, 68, 117, 68, 118, 68, 119, 68, 120, 68, 125, 70, 18,
    70, 24, 70, 32, 70, 61, 70, 116, 71, 2, 71, 3, 71, 6, 71, 8,
    71, 10, 71, 11, 71, 13, 71, 15, 71, 16, 71, 18, 71, 19, 71, 20,
    71, 22, 71, 24, 71, 26, 71, 32, 71, 61, 71, 62, 71, 64, 71, 93,
    71, 94, 71, 98, 71, 99, 71, 121, 71, 122, 71, 123, 71, 124, 71, 126,
    71, 127, 73, 3, 73, 8, 73, 18, 73, 24, 73, 32, 73, 58, 73, 61,
    73, 87, 73, 90, 73, 98, 73, 99, 73, 108, 73, 114, 73, 116, 73, 121,
    73, 122, 73, 123, 73, 124, 76, 7, 76, 12, 76, 14, 76, 17, 76, 18,
    76, 21, 76, 22, 76, 23, 76, 26, 76, 29, 76, 30, 76, 31, 76, 32,
    76, 33, 76, 61, 76, 66, 76, 68, 76, 69, 76, 70, 76, 72, 76, 80,
    76, 82, 76, 84, 76, 86, 76, 95, 76, 101, 76, 102, 76, 103, 76, 106,
    76, 109, 76, 110, 76, 115, 76, 117, 76, 118, 76, 119, 76, 120, 76, 125,
    77, 3, 77, 8, 77, 11, 77, 12, 77, 14, 77, 18, 77, 24, 77, 32,
    77, 61, 77, 87, 77, 90, 77, 95, 77, 98, 77, 99, 77, 101, 77, 103,
    77, 108, 77, 119, 77, 120, 77, 121, 77, 122, 77, 123, 77, 124, 77, 125,
    78, 58, 79, 3, 79, 8, 79, 18, 79, 24, 79, 32, 79, 58, 79, 61,
    79, 87, 79, 90, 79, 98, 79, 99, 79, 108, 79, 114, 79, 116, 79, 121,
    79, 122, 79, 123, 79, 124, 80, 18, 80, 19, 80, 20, 80, 24, 80, 32,
    80, 61, 80, 64, 80, 116, 81, 18, 81, 24, 81, 32, 81, 61, 81, 116,
    82, 75, 83, 4, 83, 7, 83, 11, 83, 12, 83, 13, 83, 14, 83, 15,
    83, 16, 83, 20, 83, 21, 83, 32, 83, 61, 83, 64, 83, 66, 83, 68,
    83, 69, 83, 70, 83, 80, 83, 82, 83, 95, 83, 98, 83, 99, 83, 101,
    83, 103, 83, 106, 83, 109, 83, 110, 83, 112, 83, 115, 83, 117, 83, 118,
    83, 119, 83, 120, 83, 126, 84, 3, 84, 8, 84, 12, 84, 14, 84, 18,
    84, 22, 84, 24, 84, 26, 84, 32, 84, 61, 84, 64, 84, 87, 84, 88,
    84, 89, 84, 90, 84, 95, 84, 101, 84, 103, 84, 108, 84, 119, 84, 120,
    84, 121, 84, 122, 84, 123, 84, 124, 85, 3, 85, 4, 85, 8, 85, 12,
    85, 14, 85, 17, 85, 18, 85, 21, 85, 23, 85, 24, 85, 32, 85, 33,
    85, 61, 85, 66, 85, 68, 85, 69, 85, 70, 85, 72, 85, 77, 85, 80,
    85, 82, 85, 95, 85, 101, 85, 103, 85, 106, 85, 109, 85, 110, 85, 115,
    85, 117, 85, 118, 85, 119, 85, 120, 85, 121, 85, 122, 85, 123, 85, 124,
    85, 125, 87, 2, 87, 11, 87, 27, 87, 28, 87, 98, 87, 99, 88, 13,
    88, 15, 88, 32, 88, 61, 88, 64, 88, 66, 88, 126, 89, 2, 89, 11,
    89, 13, 89, 15, 89, 27, 89, 28, 89, 62, 89, 94, 89, 98, 89, 99,
    89, 126, 90, 7, 90, 12, 90, 13, 90, 14, 90, 15, 90, 19, 90, 20,
    90, 21, 90, 32, 90, 61, 90, 64, 90, 66, 90, 68, 90, 69, 90, 70,
    90, 80, 90, 82, 90, 84, 90, 95, 90, 101, 90, 103, 90, 106, 90, 109,
    90, 110, 90, 112, 90, 115, 90, 117, 90, 118, 90, 119, 90, 120, 90, 126,
    91, 32, 91, 61, 92, 34, 92, 43, 92, 64, 92, 75, 92, 89, 92, 104,
    95, 5, 95, 6, 95, 7, 95, 13, 95, 15, 95, 16, 95, 18, 95, 19,
    95, 20, 95, 21, 95, 22, 95, 24, 95, 26, 95, 32, 95, 34, 95, 43,
    95, 52, 95, 53, 95, 55, 95, 57, 95, 58, 95, 59, 95, 61, 95, 64,
    95, 66, 95, 71, 95, 75, 95, 85, 95, 87, 95, 89, 95, 90, 95, 91,
    95, 104, 95, 108, 95, 112, 95, 114, 95, 116, 95, 126, 95, 127, 96, 2,
    96, 3, 96, 8, 96, 11, 96, 12, 96, 13, 96, 14, 96, 15, 96, 16,
    96, 27, 96, 28, 96, 32, 96, 61, 96, 64, 96, 95, 96, 101, 96, 103,
    96, 119, 96, 120, 96, 121, 96, 122, 96, 123, 96, 124, 96, 126, 98, 13,
    98, 15, 98, 16, 98, 34, 98, 64, 98, 66, 98, 104, 98, 126, 99, 13,
    99, 15, 99, 16, 99, 34, 99, 64, 99, 66, 99, 104, 99, 126, 100, 18,
    100, 24, 100, 32, 100, 61, 101, 5, 101, 6, 101, 7, 101, 13, 101, 15,
    101, 16, 101, 18, 101, 19, 101, 20, 101, 21, 101, 22, 101, 24, 101, 26,
    101, 32, 101, 34, 101, 43, 101, 52, 101, 53, 101, 55, 101, 57, 101, 58,
    101, 59, 101, 61, 101, 64, 101, 66, 101, 71, 101, 75, 101, 85, 101, 87,
    101, 89, 101, 90, 101, 91, 101, 104, 101, 108, 101, 112, 101, 114, 101, 116,
    101, 126, 101, 127, 103, 13, 103, 15, 103, 16, 103, 18, 103, 19, 103, 20,
    103, 24, 103, 32, 103, 53, 103, 58, 103, 61, 103, 64, 103, 126, 104, 2,
    104, 13, 104, 15, 104, 18, 104, 19, 104, 27, 104, 28, 104, 53, 104, 58,
    104, 62, 104, 94, 104, 126, 105, 24, 105, 32, 105, 53, 105, 58, 105, 61,
    106, 32, 106, 61, 107, 18, 107, 116, 108, 2, 108, 11, 108, 13, 108, 15,
    108, 27, 108, 28, 108, 98, 108, 99, 108, 126, 109, 3, 109, 8, 109, 11,
    109, 13, 109, 15, 109, 18, 109, 19, 109, 20, 109, 22, 109, 24, 109, 26,
    109, 32, 109, 61, 109, 64, 109, 89, 109, 112, 109, 114, 109, 116, 109, 121,
    109, 122, 109, 123, 109, 124, 109, 126, 110, 7, 110, 12, 110, 14, 110, 17,
    110, 18, 110, 21, 110, 22, 110, 23, 110, 24, 110, 25, 110, 26, 110, 32,
    110, 33, 110, 61, 110, 66, 110, 68, 110, 69, 110, 70, 110, 72, 110, 80,
    110, 82, 110, 86, 110, 95, 110, 101, 110, 103, 110, 106, 110, 109, 110, 110,
    110, 111, 110, 115, 110, 117, 110, 118, 110, 119, 110, 120, 110, 125, 112, 3,
    112, 8, 112, 11, 112, 12, 112, 14, 112, 18, 112, 32, 112, 61, 112, 87,
    112, 90, 112, 95, 112, 98, 112, 99, 112, 101, 112, 103, 112, 108, 112, 114,
    112, 116, 112, 119, 112, 120, 112, 121, 112, 122, 112, 123, 112, 124, 112, 125,
    113, 18, 113, 24, 113, 32, 113, 61, 114, 12, 114, 14, 114, 16, 114, 19,
    114, 22, 114, 32, 114, 33, 114, 61, 114, 68, 114, 69, 114, 70, 114, 80,
    114, 82, 114, 86, 114, 95, 114, 101, 114, 103, 114, 106, 114, 109, 114, 110,
    114, 112, 114, 115, 114, 116, 114, 117, 114, 118, 114, 119, 114, 120, 115, 11,
    115, 61, 115, 64, 115, 98, 115, 99, 116, 4, 116, 7, 116, 12, 116, 13,
    116, 14, 116, 15, 116, 16, 116, 19, 116, 20, 116, 21, 116, 22, 116, 24,
    116, 25, 116, 32, 116, 33, 116, 61, 116, 64, 116, 66, 116, 68, 116, 69,
    116, 70, 116, 75, 116, 80, 116, 82, 116, 84, 116, 95, 116, 101, 116, 103,
    116, 106, 116, 109, 116, 110, 116, 112, 116, 115, 116, 117, 116, 118, 116, 119,
    116, 120, 116, 126, 117, 18, 117, 19, 117, 20, 117, 24, 117, 32, 117, 61,
    117, 64, 117, 89, 117, 112, 117, 114, 117, 116, 118, 18, 118, 19, 118, 20,
    118, 24, 118, 32, 118, 61, 118, 64, 118, 112, 118, 114, 118, 116, 119, 13,
    119, 15, 119, 16, 119, 18, 119, 19, 119, 20, 119, 24, 119, 32, 119, 53,
    119, 58, 119, 61, 119, 64, 119, 126, 120, 13, 120, 15, 120, 16, 120, 18,
    120, 19, 120, 20, 120, 24, 120, 32, 120, 53, 120, 58, 120, 61, 120, 64,
    120, 126, 121, 4, 121, 13, 121, 15, 121, 16, 121, 17, 121, 21, 121, 23,
    121, 25, 121, 33, 121, 34, 121, 43, 121, 59, 121, 64, 121, 66, 121, 68,
    121, 69, 121, 70, 121, 80, 121, 82, 121, 84, 121, 91, 121, 104, 121, 106,
    121, 109, 121, 110, 121, 112, 121, 115, 121, 117, 121, 118, 121, 126, 122, 4,
    122, 13, 122, 15, 122, 16, 122, 17, 122, 21, 122, 23, 122, 25, 122, 33,
    122, 34, 122, 43, 122, 59, 122, 64, 122, 66, 122, 68, 122, 69, 122, 70,
    122, 80, 122, 82, 122, 84, 122, 91, 122, 104, 122, 106, 122, 109, 122, 110,
    122, 112, 122, 115, 122, 117, 122, 118, 122, 126, 123, 4, 123, 13, 123, 15,
    123, 16, 123, 21, 123, 25, 123, 33, 123, 34, 123, 43, 123, 64, 123, 66,
    123, 104, 123, 112, 123, 126, 124, 4, 124, 13, 124, 15, 124, 16, 124, 21,
    124, 25, 124, 33, 124, 34, 124, 43, 124, 64, 124, 66, 124, 104, 124, 112,
    124, 126, 125, 16, 125, 18, 125, 19, 125, 20, 125, 24, 125, 32, 125, 53,
    125, 57, 125, 58, 125, 59, 125, 61, 126, 3, 126, 6, 126, 7, 126, 8,
    126, 11, 126, 12, 126, 14, 126, 17, 126, 18, 126, 21, 126, 23, 126, 26,
    126, 32, 126, 36, 126, 40, 126, 48, 126, 50, 126, 53, 126, 54, 126, 55,
    126, 56, 126, 58, 126, 61, 126, 68, 126, 69, 126, 70, 126, 71, 126, 72,
    126, 80, 126, 82, 126, 85, 126, 86, 126, 87, 126, 88, 126, 90, 126, 95,
    126, 98, 126, 99, 126, 101, 126, 103, 126, 106, 126, 108, 126, 109, 126, 111,
    126, 114, 126, 115, 126, 116, 126, 117, 126, 118, 126, 119, 126, 120, 126, 121,
    126, 122, 126, 123, 126, 124, 126, 127, 127, 3, 127, 8, 127, 11, 127, 18,
    127, 32, 127, 61, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -6, -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4, -38, -6, -4,
    -4, -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4, -4, -38, 8,
    3, -31, 4, 4, 4, -15, -12, -12, -23, -23, -19, -23, -23, -23, -23, -23,
    -23, -23, -31, -15, -31, -15, -15, -30, -8, -8, -12, -8, -31, -8, -30, -18,
    -7, -30, -38, -8, -8, -8, -8, -8, -8, -19, -31, -31, -31, -31, -8, -15,
    -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4, -38, -6, -4, -4,
    -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4, -4, -38, 8, 7,
    28, 7, -38, -38, -31, 7, 7, -12, 7, -12, -12, -38, 7, 7, 9, 7,
    9, 7, 7, -12, 9, 9, 7, -38, -14, -8, -12, -19, -19, -23, -27, -17,
    -23, -23, -23, -14, -19, -8, -15, -23, -12, -23, -31, -6, -6, -13, -12, -12,
    -8, -19, -8, -38, -38, -38, -38, -19, -19, -38, 7, 4, -19, 3, -23, -19,
    -38, 3, -54, 3, 3, 3, 3, -19, -19, -19, -19, -19, 3, -31, -19, -19,
    -38, -38, -38, -38, -38, -14, -12, -19, -19, -23, -27, -17, -23, -23, -23, -14,
    -19, -15, -23, -12, -23, -31, -13, -12, -12, -19, -38, -38, -4, -38, -38, -19,
    -19, -5, -38, -7, -4, -8, -19, -8, -8, -8, -8, -23, -4, -19, -12, -38,
    -54, -4, -4, -4, -7, -4, -4, -4, -12, -4, -15, -8, -15, -19, -19, -19,
    -19, -19, -4, -15, -4, -4, -12, -4, -31, -4, -4, -19, -19, -38, -38, -38,
    -38, -38, -19, -23, -54, -23, -54, -46, -23, -15, -19, -15, -19, -19, -23, -19,
    -46, -19, -19, -19, -19, -19, -19, -23, -23, -23, -19, -19, -19, -15, -15, -19,
    -23, -19, -19, -23, -23, -54, -8, -7, -3, -2, -3, -4, -8, -8, -8, -8,
    -19, -8, -15, -19, -15, -2, -2, -8, -27, -4, -4, -4, -8, -7, -19, -3,
    -8, -19, -8, -4, -23, -19, -2, -4, -4, -4, -2, -2, -2, -4, -4, -12,
    -2, -2, -19, -19, -19, -19, -15, -12, -12, -22, -9, -15, -12, -15, -12, -10,
    -12, -12, -12, -12, -8, -8, -8, -8, -20, -7, -5, -12, -19, -8, -17, -12,
    -8, -12, -8, -8, -8, -8, 8, 7, 4, 7, 7, -31, -31, -15, 2, -38,
    4, 9, 9, 7, 7, 7, 7, -31, 4, -8, -8, -8, -15, -10, -8, -8,
    -4, -20, -20, -15, -6, -5, -8, -8, -4, -4, -4, -8, -15, -8, -15, -38,
    -4, -4, -4, -20, -12, -2, -10, -15, -15, -4, -23, -19, -12, -2, -10, -15,
    -15, -4, -23, -19, -10, -15, -16, -38, -16, -38, -31, -6, -9, -38, -16, -16,
    -16, -16, -16, -38, -12, -12, -12, -12, -12, -15, -19, -12, -16, -19, -19, -12,
    -12, -12, -12, -19, 6, -12, -19, -22, 7, 7, -12, -12, -12, -12, -12, -4,
    -8, -4, -4, -15, -5, -4, -4, -10, -8, -8, -2, -9, -8, -8, -6, -3,
    -8, -11, -4, -8, -8, -5, -2, -4, -4, -4, -4, -4, -6, -31, -31, -8,
    -23, -16, -12, -8, -12, -20, -20, -20, -8, -8, -8, -7, -8, -8, -7, -8,
    -8, -8, -8, -8, -10, -5, -8, -8, -12, -6, -19, -12, -19, -31, -31, -20,
    -31, -6, -8, -19, -8, -6, -10, -12, -8, -38, -8, -8, -31, -31, -23, -15,
    -15, 3, -15, -12, -8, -12, -4, -31, -4, -31, -19, -4, -12, -2, -13, -8,
    -6, -10, -8, -8, -8, -5, -5, -5, -8, -19, -7, -7, -5, -11, -7, -7,
    -8, -2, -6, -38, -23, -4, -13, -13, -13, -13, -13, -4, -8, -12, -4, -4,
    -13, -13, -13, -13, -13, -13, -14, -7, -13, -13, -10, -23, -13, -19, -4, -13,
    -4, -5, -4, -19, -12, -13, -4, -13, -13, -13, -19, -13, -12, -13, -15, -13,
    -13, -4, -4, -31, -15, -15, -15, -18, 7, -15, -15, -15, -26, -15, -15, -38,
    -38, -31, -38, -38, -46, -16, -21, -31, -16, -16, -16, -16, -37, -33, -15, -35,
    -45, -15, -28, -19, -28, -38, -38, -38, -38, -38, -28, -38, -38, -38, -38, -38,
    -38, -31, -13, -15, -15, -18, -46, -46, -19, -16, -15, -23, -15, -17, -15, -13,
    -19, -38, -18, -23, -23, -46, -13, -15, 12, -15, 12, -3, -4, -11, -11, -3,
    -8, -6, -2, -8, -5, -5, -4, -5, -5, -3, -8, -3, -3, -13, -3, -8,
    -4, -6, -6, -6, -4, -6, -6, -11, -11, -11, -6, -6, -2, -6, -6, -6,
    -11, -11, -8, -4, -4, -4, -15, -4, -6, -6, -8, -4, -4, -8, -8, -4,
    -8, -6, -12, -12, -4, -4, -4, -4, -8, -8, -4, -4, -4, -4, -4, -19,
    -8, -15, -19, -23, -19, -23, -19, -12, -19, -8, -15, -8, -8, -15, -15, -19,
    -19, -13, -13, -8, -13, -13, -8, -12, -19, -19, -21, -21, -21, -15, -19, -12,
    -12, -12, -21, -12, -21, -12, -19, -12, -15, -15, -12, -15, -15, -15, -19, -12,
    -19, -19, -19, -11, -21, -15, -21, -19, -17, -12, -21, -19, -21, -21, -19, -19,
    -19, -23, -12, -4, -6, -8, -8, -19, -8, -19, -8, -8, -8, -4, -4, -4,
    -4, -6, -7, -6, -4, -19, -15, -10, -10, -10, -4, -12, -4, -4, -10, -4,
    -10, -4, -8, -8, -7, -9, -8, -4, -8, -8, -7, -10, -10, -6, -10, -4,
    -10, -10, -10, -8, -8, -4, -19, -4, -4, -12, -12, -6, -4, -4, -4, -4,
    -8, -23, -12, -4, -4, -4, -4, -4, -4, -4, -4, -4, -5, -4, -4, -8,
    -4, -4, -4, -12, -15, -15, -18, -12, -12, -12, -12, -12, -12, 7, -15, -15,
    -12, -15, -26, -15, -15, -11, 4, -19, -19, 4, -23, -38, -23, -38, -23, -19,
    -19, -15, -15, -23, -23, -16, -22, -15, -15, -15, -15, 7, -31, -34, -26, -26,
    -26, -15, -19, -22, -22, -26, -22, -26, -22, -23, -22, -17, -20, -17, -23, -23,
    -22, -23, -23, -22, -26, -17, -26, -26, -22, -26, -19, -26, -26, -23, -23, 4,
    4, 4, 4, -18, -38, -20, -20, -12, -10, -10, -10, -10, -10, -15, -10, -20,
    -20, -20, -15, -20, -20, -15, -15, 7, 9, 10, 7, 7, 7, 24, 7, 7,
    -38, -23, -23, -38, -31, -23, -23, -22, -15, -15, -31, -19, -23, -46, 8, -23,
    -31, -27, -27, -23, -23, -19, -23, -23, -38, -38, -38, -38, -23, -38, -31, -38,
    7, -38, -31, -31, -38, -46, -31, -15, -15, 11, -15, -15, -19, -19, -23, -31,
    -46, 7, 9, 28, 7, -31, -31, -31, -31, -31, -31, -31, -31, -38, -38, -38,
    -38, -31, -19, -10, -12, -15, -19, -15, -15, -19, -13, -6, -14, -14, -4, -2,
    -12, -8, -4, -3, -3, -3, -13, -8, -12, -4, -8, -8, -8, -4, -8, -8,
    -3, -14, -14, -3, -14, -8, -8, -6, -2, -8, -8, -8, -14, -14, -10, -19,
    -15, -15, -19, -13, 25, 27, 8, 27, 31, 19, -19, -19, -11, 10, 10, 11,
    8, 23, 8, 19, 9, 28, -12, 7, 28, 13, 13, 27, 27, 27, 27, -19,
    8, -4, -4, -12, -8, -12, -15, -12, -2, -2, -2, -2, -2, -2, -4, -4,
    -4, -4, -4, -8, -13, -13, -3, -2, -6, -4, -4, -4, -6, -6, -6, -10,
    -4, -8, -6, -5, -5, -5, -3, -5, -5, -2, -3, -13, -13, -6, -13, -5,
    -5, -4, -5, -5, -5, -13, -13, -6, -6, -6, -4, -4, -4, -11, -7, -6,
    -8, -4, -4, -4, -6, -6, -4, -4, -4, -4, -4, -6, -6, -6, -6, -4,
    -15, -4, -4, -12, -8, -12, -15, -12, -2, -2, -2, -2, -2, -2, -4, -4,
    -4, -4, -4, -19, -8, -8, -15, -15, -19, -8, -13, -19, -15, -15, -19, -13,
    7, -8, -13, 11, -10, -31, -10, -31, -23, -8, -12, -12, -19, -31, -11, -10,
    -10, -10, -10, -10, -10, 10, 10, -10, -10, -10, -10, -8, -19, -10, -10, -10,
    -10, -10, -31, -6, -6, -4, -4, -12, -4, -10, -4, -12, -12, -8, -5, -3,
    -4, -5, -4, -4, -4, -5, -4, -4, -6, -6, -6, -6, -6, -4, -6, -15,
    -15, -4, -4, -8, -4, -6, -12, -4, -15, -4, -7, -7, -7, -6, -4, -7,
    -7, -15, -15, -15, -7, -7, -4, -7, -7, -7, -15, -15, -6, -6, -6, -6,
    -8, 7, 9, 3, 3, 7, 7, -8, -8, -8, -8, -8, -7, -8, 3, 5,
    3, 3, 3, 3, 7, 7, 3, 3, 3, -7, -4, -15, -4, -15, -4, -7,
    -4, -12, -8, -12, -8, -3, -3, -3, -3, -3, -3, -4, -4, -4, -3, -3,
    -4, -11, -3, -3, -3, -4, -4, -15, -12, -12, 7, 9, 7, 23, 7, 7,
    -14, -8, -12, -19, -19, -23, -27, -17, -23, -4, -4, -23, -4, -23, -4, -5,
    -14, -19, -8, -15, -23, -12, -23, -31, -6, -6, -4, -2, -4, -13, -4, -12,
    -4, -4, -12, -4, -8, -19, -8, -24, -31, -31, -24, -35, -77, -35, -77, -62,
    -35, -35, -35, -31, -38, -35, -35, -35, -35, -35, -31, -31, -31, -31, -77, -19,
    -19, -23, -6, -31, -8, -6, -19, -19, -19, -23, -6, -31, -8, -6, -19, -4,
    -8, -8, -8, -14, -8, -12, -19, -19, -23, -27, -17, -23, -4, -4, -23, -4,
    -23, -4, -5, -14, -19, -8, -15, -23, -12, -23, -31, -6, -6, -4, -2, -4,
    -13, -4, -12, -4, -4, -12, -4, -8, -19, -8, -19, -19, -23, -27, -17, -23,
    -23, -23, -19, -23, -23, -31, -19, 2, 3, 3, -19, 6, 3, 3, -19, -22,
    7, 7, 3, -8, -8, -11, -8, -8, -12, -18, -15, -17, 7, 9, -15, -15,
    3, 3, 7, 7, -15, -4, -4, -4, -4, -4, -19, -8, -8, -4, -15, -4,
    -15, -19, -8, -5, -6, -6, -13, -4, -4, -4, -4, -4, -6, -13, -13, -6,
    -6, -10, -4, -8, -12, -6, -6, -15, -8, -12, -8, -10, -10, -10, -6, -10,
    -10, -4, -13, -13, -13, -10, -10, -6, -6, -10, -10, -10, -13, -13, -8, -23,
    -23, -15, -11, -11, -23, -18, -23, -11, -11, -11, -12, -12, -11, -11, -11, -9,
    -20, -11, -11, -23, -23, -23, -23, -8, -4, -8, -8, -8, -4, -4, -8, -4,
    -4, -8, -2, -12, -4, -4, -4, -4, -4, -2, -4, -4, -4, -4, -4, -4,
    -6, -4, -2, -4, -4, -4, -4, 10, -19, -19, 9, 9, -8, -12, -8, -23,
    -8, -23, -12, -8, -8, -12, -4, -12, -8, -15, -12, -12, -23, -12, -10, -10,
    -10, -5, -10, -10, -6, -8, -8, -8, -10, -10, -10, -15, -10, -10, -10, -8,
    -8, -23, -19, -8, -8, -15, -15, -19, -8, -5, -6, -6, -13, -19, -8, -8,
    -15, -15, -19, -8, -6, -6, -13, -19, -19, -23, -27, -17, -23, -23, -23, -19,
    -23, -23, -31, -19, -19, -19, -23, -27, -17, -23, -23, -23, -19, -23, -23, -31,
    -19, -12, -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4, -38, -6, -4,
    -4, -4, -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4, -4, -38, -12,
    -38, -38, -38, -4, -15, -4, -6, -8, -12, -8, -4, -38, -6, -4, -4, -4,
    -4, -4, -4, -4, -12, -4, -4, -4, -8, -4, -4, -4, -38, -12, -38, -38,
    -38, -15, -6, -8, -12, -8, -38, -6, -12, -8, -38, -12, -38, -38, -38, -15,
    -6, -8, -12, -8, -38, -6, -12, -8, -38, -12, -17, -16, -19, -23, -15, -19,
    -11, -18, -15, -12, -38, -38, -4, -38, -38, -19, -19, -5, -38, -7, -4, -8,
    -19, -8, -8, -8, -8, -23, -4, -19, -12, -38, -54, -4, -4, -4, -7, -4,
    -4, -4, -12, -4, -15, -8, -15, -19, -19, -19, -19, -19, -4, -15, -4, -4,
    -12, -4, -31, -4, -4, -19, -19, -38, -38, -38, -38, -38, -31, -31, -19, -38,
    -23, -23, -31, -31, -31, -31,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 2006,
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

const lv_font_t humid1_font_fira_cond_bold_24 = {
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
    .fallback = &humid1_font_fira_sans_bold_24,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_FIRA_COND_BOLD_24 */
