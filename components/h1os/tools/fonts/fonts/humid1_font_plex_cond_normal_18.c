/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_18 (cond normal)
 * Size: 18 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_18 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_18
#define HUMID1_FONT_PLEX_COND_NORMAL_18 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_18

extern const lv_font_t humid1_font_plex_sans_normal_18;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x13) */
    0xff, 0xf5, 0x47, 0xc0,
    /* U+0022 "" (5x5) */
    0xde, 0xe5, 0x29, 0x00,
    /* U+0023 "#" (10x13) */
    0x09, 0x02, 0x41, 0x90, 0x64, 0x7f, 0xc4, 0xc1, 0x20, 0x48, 0xff, 0x8d,
    0x82, 0x60, 0x98, 0x24, 0x00,
    /* U+0024 "$" (7x15) */
    0x10, 0x21, 0xfe, 0xa9, 0x1a, 0x3c, 0x1e, 0x1e, 0x2c, 0x4c, 0xbf, 0xc2,
    0x04, 0x00,
    /* U+0025 "%" (11x13) */
    0x60, 0x9e, 0x32, 0x44, 0x49, 0x89, 0x21, 0x2d, 0xa5, 0x7b, 0xe9, 0x09,
    0x23, 0x24, 0x44, 0x88, 0xf2, 0x0c,
    /* U+0026 "&" (10x13) */
    0x38, 0x1b, 0x04, 0x41, 0x10, 0x2c, 0x0e, 0x07, 0x8f, 0x32, 0x86, 0xa0,
    0xec, 0x33, 0xbe, 0x7c, 0xc0,
    /* U+0027 "'" (2x5) */
    0xfa, 0x80,
    /* U+0028 "(" (3x16) */
    0x2d, 0x6d, 0xa4, 0x92, 0x6c, 0x99,
    /* U+0029 ")" (3x16) */
    0x99, 0x36, 0xc9, 0x25, 0xb6, 0xb4,
    /* U+002A "" (7x8) */
    0x10, 0x20, 0x47, 0xf7, 0xc7, 0x1b, 0x36,
    /* U+002B "+" (8x9) */
    0x10, 0x10, 0x10, 0x18, 0xff, 0x38, 0x10, 0x10, 0x10,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (2x3) */
    0x7c,
    /* U+002F "/" (6x13) */
    0x0c, 0x30, 0x86, 0x18, 0x43, 0x0c, 0x21, 0x86, 0x10, 0xc0,
    /* U+0030 "0" (7x13) */
    0x38, 0xdb, 0x1e, 0x3c, 0x38, 0x70, 0xe1, 0xc3, 0x8f, 0x1b, 0x63, 0x80,
    /* U+0031 "1" (4x13) */
    0x37, 0xfb, 0x33, 0x33, 0x33, 0x33, 0x30,
    /* U+0032 "2" (8x13) */
    0x7c, 0xee, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x1c, 0x18, 0x30, 0x60, 0xe0,
    0xff,
    /* U+0033 "3" (8x13) */
    0x7c, 0xee, 0x06, 0x06, 0x0e, 0x7c, 0x0e, 0x06, 0x03, 0x03, 0x06, 0xce,
    0xfc,
    /* U+0034 "4" (9x13) */
    0x07, 0x03, 0x83, 0xc3, 0x61, 0xb1, 0x98, 0x8c, 0xc6, 0xff, 0xff, 0xc0,
    0xc0, 0x60, 0x30,
    /* U+0035 "5" (7x13) */
    0x7c, 0x83, 0x06, 0x0c, 0x1f, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x7f, 0xc0,
    /* U+0036 "6" (7x13) */
    0x3e, 0xe1, 0x86, 0x0c, 0x1f, 0xb9, 0xe3, 0xc3, 0x87, 0x1b, 0x73, 0xc0,
    /* U+0037 "7" (7x13) */
    0xfe, 0x0c, 0x18, 0x30, 0xc1, 0x82, 0x0c, 0x18, 0x60, 0xc1, 0x86, 0x00,
    /* U+0038 "8" (7x13) */
    0x38, 0xfb, 0xde, 0x3c, 0xef, 0x8e, 0x36, 0xc7, 0x87, 0x0b, 0x33, 0xc0,
    /* U+0039 "9" (7x13) */
    0x38, 0xdb, 0x1e, 0x3c, 0x38, 0xf1, 0xbf, 0x06, 0x0c, 0x38, 0xe7, 0x80,
    /* U+003A ":" (2x10) */
    0xf4, 0x01, 0xf0,
    /* U+003B ";" (3x13) */
    0xdd, 0x00, 0x00, 0xdb, 0x68,
    /* U+003C "<" (7x9) */
    0x02, 0x0c, 0x73, 0x8c, 0x1c, 0x0f, 0x07, 0x02,
    /* U+003D "=" (7x5) */
    0xfe, 0x00, 0x00, 0x0f, 0xe0,
    /* U+003E ">" (7x9) */
    0x81, 0xc1, 0xc0, 0xe0, 0x61, 0xce, 0x70, 0x80,
    /* U+003F "?" (6x13) */
    0xfb, 0x70, 0xc3, 0x0c, 0x63, 0x18, 0x60, 0x06, 0x18, 0x60,
    /* U+0040 "@" (12x14) */
    0x0f, 0x83, 0x8e, 0x20, 0x24, 0x7b, 0xcd, 0x9d, 0x99, 0x91, 0x99, 0x19,
    0x99, 0xb8, 0xee, 0xc0, 0x04, 0x00, 0x30, 0x81, 0xf8,
    /* U+0041 "A" (10x13) */
    0x0c, 0x03, 0x80, 0xe0, 0x68, 0x1b, 0x04, 0xc3, 0x10, 0xfe, 0x3f, 0x98,
    0x26, 0x0d, 0x03, 0xc0, 0x40,
    /* U+0042 "B" (9x13) */
    0xfe, 0x73, 0xb0, 0xd8, 0x6c, 0x36, 0x1b, 0xf9, 0xce, 0xc3, 0x60, 0xf0,
    0xdc, 0xef, 0xe0,
    /* U+0043 "C" (9x13) */
    0x1f, 0x18, 0xd8, 0x08, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x70, 0x18,
    0x06, 0x21, 0xf0,
    /* U+0044 "D" (9x13) */
    0xf8, 0x67, 0x20, 0xd0, 0x68, 0x14, 0x0e, 0x07, 0x03, 0x81, 0x41, 0xa0,
    0xd9, 0xcf, 0x80,
    /* U+0045 "E" (7x13) */
    0xff, 0xc3, 0x06, 0x0c, 0x18, 0x3f, 0xf0, 0xc1, 0x83, 0x07, 0x0f, 0xe0,
    /* U+0046 "F" (7x13) */
    0xff, 0xc3, 0x06, 0x0c, 0x18, 0x3f, 0xf0, 0xc1, 0x83, 0x06, 0x0c, 0x00,
    /* U+0047 "G" (9x13) */
    0x0f, 0x18, 0x98, 0x08, 0x0c, 0x06, 0x03, 0x1f, 0x83, 0xc1, 0xe0, 0xd8,
    0x66, 0x31, 0xf8,
    /* U+0048 "H" (10x13) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7f, 0xff, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xe1, 0xc0,
    /* U+0049 "I" (4x13) */
    0xff, 0x66, 0x66, 0x66, 0x66, 0x6e, 0xf0,
    /* U+004A "J" (4x16) */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,
    /* U+004B "K" (8x13) */
    0x83, 0x86, 0x8c, 0x98, 0x98, 0xb0, 0xf0, 0xd8, 0x98, 0x8c, 0x86, 0x86,
    0x83,
    /* U+004C "L" (7x13) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0xff, 0xe0,
    /* U+004D "M" (11x13) */
    0xc0, 0x7c, 0x1f, 0x83, 0xf0, 0x7f, 0x1f, 0x63, 0xec, 0x5c, 0xdb, 0x9b,
    0x73, 0xce, 0x39, 0xc7, 0x38, 0xc6,
    /* U+004E "N" (9x13) */
    0xc1, 0xe0, 0xf8, 0x7e, 0x3b, 0x1c, 0xce, 0x67, 0x1b, 0x8d, 0xc3, 0xe1,
    0xf0, 0x78, 0x18,
    /* U+004F "O" (10x13) */
    0x1e, 0x0c, 0xe6, 0x0f, 0x03, 0xc0, 0xf0, 0x1c, 0x07, 0x01, 0xc0, 0xf0,
    0x36, 0x0c, 0xce, 0x1e, 0x00,
    /* U+0050 "P" (7x13) */
    0xf9, 0x1a, 0x1c, 0x38, 0x70, 0xe3, 0x7c, 0xc1, 0x02, 0x04, 0x08, 0x00,
    /* U+0051 "Q" (11x16) */
    0x1f, 0x06, 0x31, 0x83, 0x60, 0x2c, 0x07, 0x80, 0xf0, 0x1e, 0x03, 0xc0,
    0x78, 0x09, 0x83, 0x19, 0xc1, 0xf0, 0x06, 0x00, 0x60, 0x06,
    /* U+0052 "R" (8x13) */
    0xf8, 0xcc, 0x86, 0x86, 0x86, 0x8c, 0xf8, 0x98, 0x8c, 0x8c, 0x86, 0x86,
    0x83,
    /* U+0053 "S" (7x13) */
    0x3e, 0xcf, 0x06, 0x0c, 0x0e, 0x0f, 0x07, 0x06, 0x0c, 0x1e, 0x7f, 0x80,
    /* U+0054 "T" (9x13) */
    0xff, 0x8e, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06,
    0x03, 0x01, 0x80,
    /* U+0055 "U" (9x13) */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xe0, 0xd8,
    0x6e, 0xe3, 0xe0,
    /* U+0056 "V" (10x13) */
    0xc0, 0xf0, 0x36, 0x19, 0x86, 0x61, 0x8c, 0xc3, 0x30, 0xcc, 0x1e, 0x07,
    0x81, 0xe0, 0x30, 0x0c, 0x00,
    /* U+0057 "W" (15x13) */
    0xc3, 0x86, 0x87, 0x0d, 0x8e, 0x33, 0x1c, 0x66, 0x6c, 0xcc, 0xd9, 0x8d,
    0xb2, 0x1b, 0x2c, 0x3c, 0x78, 0x78, 0xf0, 0x71, 0xe0, 0xc1, 0x81, 0x83,
    0x00,
    /* U+0058 "X" (9x13) */
    0x61, 0xb0, 0xcc, 0xc6, 0x61, 0xe0, 0xe0, 0x30, 0x3c, 0x16, 0x19, 0x98,
    0xcc, 0x3c, 0x18,
    /* U+0059 "Y" (9x13) */
    0xc1, 0xb0, 0xd8, 0xc6, 0x63, 0x61, 0xf0, 0x70, 0x38, 0x0c, 0x06, 0x03,
    0x01, 0x80, 0xc0,
    /* U+005A "Z" (8x13) */
    0xfe, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60, 0xc0, 0xc0,
    0xff,
    /* U+005B "[" (4x15) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,
    /* U+005C "" (6x13) */
    0xc1, 0x06, 0x18, 0x20, 0xc3, 0x04, 0x18, 0x60, 0x83, 0x0c,
    /* U+005D "]" (4x15) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,
    /* U+005E "^" (7x8) */
    0x10, 0x70, 0xa3, 0x64, 0x48, 0xb1, 0xc1,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0xdd, 0x80,
    /* U+0061 "a" (7x10) */
    0x7c, 0xd8, 0x18, 0x37, 0xfc, 0xf1, 0xe3, 0xce, 0xe4,
    /* U+0062 "b" (8x14) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xf6, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3,
    0xf6, 0xdc,
    /* U+0063 "c" (6x10) */
    0x3d, 0x9c, 0x30, 0xc3, 0x0c, 0x30, 0x64, 0xf0,
    /* U+0064 "d" (8x14) */
    0x03, 0x03, 0x03, 0x03, 0x3b, 0x6f, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0x6f, 0x3b,
    /* U+0065 "e" (8x10) */
    0x3c, 0x66, 0xc2, 0xc3, 0xff, 0xc0, 0xc0, 0xc0, 0x76, 0x3e,
    /* U+0066 "f" (6x14) */
    0x1c, 0xc3, 0x0c, 0xfd, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+0067 "g" (8x14) */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3f, 0x03, 0x03,
    0x46, 0x7c,
    /* U+0068 "h" (8x14) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xf7, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,
    /* U+0069 "i" (2x14) */
    0xf0, 0xff, 0xff, 0xf0,
    /* U+006A "j" (4x18) */
    0x33, 0x00, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,
    /* U+006B "k" (8x14) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xdc, 0xf8, 0xf0, 0xf8, 0xdc, 0xcc,
    0xc6, 0xc7,
    /* U+006C "l" (2x14) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+006D "m" (13x10) */
    0xdc, 0xf7, 0xbd, 0xf8, 0xc7, 0x86, 0x3c, 0x31, 0xe1, 0x8f, 0x0c, 0x78,
    0x63, 0xc3, 0x1e, 0x18, 0xc0,
    /* U+006E "n" (8x10) */
    0xdc, 0xf7, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+006F "o" (8x10) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0070 "p" (8x14) */
    0xdc, 0xf6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3, 0xf6, 0xfc, 0xc0, 0xc0,
    0xc0, 0xc0,
    /* U+0071 "q" (8x14) */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3b, 0x03, 0x03,
    0x03, 0x03,
    /* U+0072 "r" (5x10) */
    0xdf, 0xb9, 0x8c, 0x63, 0x18, 0xc6, 0x00,
    /* U+0073 "s" (6x10) */
    0x7f, 0x3c, 0x30, 0x70, 0xf0, 0xc3, 0xcf, 0xe0,
    /* U+0074 "t" (6x13) */
    0x20, 0x86, 0x3f, 0x71, 0x86, 0x18, 0x61, 0x86, 0x0c, 0x3c,
    /* U+0075 "u" (8x10) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3f,
    /* U+0076 "v" (8x10) */
    0xc1, 0x43, 0x63, 0x62, 0x66, 0x36, 0x34, 0x3c, 0x1c, 0x18,
    /* U+0077 "w" (13x10) */
    0xc7, 0x1a, 0x38, 0x99, 0xcc, 0xce, 0x66, 0xdb, 0x16, 0xd0, 0xf7, 0x87,
    0x1c, 0x38, 0xe1, 0xc6, 0x00,
    /* U+0078 "x" (7x10) */
    0xc7, 0x8d, 0xb3, 0xc3, 0x87, 0x1e, 0x36, 0xc7, 0x8c,
    /* U+0079 "y" (8x14) */
    0xc3, 0x43, 0x63, 0x66, 0x26, 0x36, 0x34, 0x1c, 0x1c, 0x18, 0x18, 0x18,
    0x30, 0xe0,
    /* U+007A "z" (6x10) */
    0xfc, 0x71, 0x86, 0x30, 0x86, 0x30, 0xc3, 0xf0,
    /* U+007B "{" (6x16) */
    0x0c, 0x63, 0x0c, 0x30, 0xc3, 0x38, 0x30, 0xc3, 0x0c, 0x30, 0xc1, 0x87,
    /* U+007C "|" (1x18) */
    0xff, 0xff, 0xc0,
    /* U+007D "}" (6x16) */
    0xe1, 0xc3, 0x0c, 0x30, 0xc3, 0x87, 0x18, 0xc3, 0x0c, 0x30, 0xc3, 0x38,
    /* U+007E "~" (7x2) */
    0xf1, 0x3c,
    /* U+00B0 "" (5x6) */
    0x76, 0xe3, 0x1c, 0xb8,
    /* U+00B1 "" (8x11) */
    0x10, 0x10, 0x10, 0x18, 0xff, 0x38, 0x10, 0x10, 0x10, 0xfe, 0xff,
    /* U+00B2 "" (5x8) */
    0x72, 0xc2, 0x31, 0x99, 0x9f,
    /* U+00B3 "" (6x8) */
    0x79, 0x61, 0x9e, 0x18, 0x30, 0xfe,
    /* U+00B5 "" (8x14) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xef, 0xfb, 0xc0, 0xc0,
    0xc0, 0xc0,
    /* U+00B7 "" (2x3) */
    0x7c,
    /* U+00D7 "" (7x7) */
    0xc6, 0xd8, 0xe1, 0xc3, 0x8d, 0xb1, 0x80,
    /* U+00F7 "" (7x8) */
    0x10, 0x20, 0x07, 0xf0, 0x00, 0x04, 0x08,
    /* U+0394 "" (9x13) */
    0x0c, 0x0e, 0x07, 0x83, 0xc1, 0x61, 0x90, 0xcc, 0x46, 0x61, 0x30, 0xd8,
    0x7f, 0xff, 0xf8,
    /* U+03A9 "" (11x13) */
    0x1f, 0x0e, 0x71, 0x83, 0x60, 0x6c, 0x0d, 0x80, 0xb0, 0x16, 0x06, 0xc0,
    0xcc, 0x19, 0x86, 0x19, 0xcf, 0x3e,
    /* U+03BC "" (8x14) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xef, 0xfb, 0xc0, 0xc0,
    0xc0, 0xc0,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (15x1) */
    0xff, 0xfe,
    /* U+2018 "" (3x5) */
    0x6d, 0xfc,
    /* U+2019 "" (3x5) */
    0x6d, 0xec,
    /* U+201C "" (6x4) */
    0x65, 0x34, 0xb6,
    /* U+201D "" (6x5) */
    0x6d, 0xb6, 0xb6, 0xd8,
    /* U+2022 "" (4x5) */
    0x6f, 0xff, 0x60,
    /* U+2026 "" (11x3) */
    0x44, 0x59, 0x9f, 0x11, 0x00,
    /* U+2030 "" (17x13) */
    0x60, 0x80, 0x78, 0xc0, 0x24, 0x40, 0x12, 0x60, 0x09, 0x20, 0x04, 0xb6,
    0x3a, 0x55, 0xb4, 0xfa, 0x53, 0x09, 0x28, 0x84, 0x94, 0x44, 0x4a, 0x62,
    0x3c, 0xa2, 0x0c, 0x70,
    /* U+2190 "" (13x5) */
    0x30, 0x03, 0x00, 0x3f, 0xfe, 0xc0, 0x03, 0x00, 0x00,
    /* U+2191 "" (6x12) */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c,
    /* U+2192 "" (12x5) */
    0x00, 0x40, 0x06, 0xff, 0xf0, 0x06, 0x00, 0x40,
    /* U+2193 "" (4x3) */
    0xf6, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 66, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 69, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 108, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 8, .adv_w = 163, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 148, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 39, .adv_w = 213, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 188, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 60, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 76, .adv_w = 79, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 82, .adv_w = 79, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 88, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 95, .adv_w = 144, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 104, .adv_w = 69, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 105, .adv_w = 81, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 106, .adv_w = 69, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 97, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 144, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 148, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 69, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 71, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 245, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 253, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 258, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 266, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 226, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 297, .adv_w = 165, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 166, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 163, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 185, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 133, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 183, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 189, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 90, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 73, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 430, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 135, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 233, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 196, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 198, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 201, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 539, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 142, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 142, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 186, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 155, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 238, .box_w = 15, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 147, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 145, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 83, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 687, .adv_w = 97, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 83, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 705, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 712, .adv_w = 109, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 713, .adv_w = 75, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 715, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 159, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 156, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 91, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 159, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 795, .adv_w = 160, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 69, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 69, .box_w = 4, .box_h = 18, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 822, .adv_w = 139, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 69, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 240, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 159, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 891, .adv_w = 159, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 905, .adv_w = 107, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 97, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 930, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 950, .adv_w = 202, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 967, .adv_w = 137, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 976, .adv_w = 133, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 990, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 998, .adv_w = 100, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1010, .adv_w = 139, .box_w = 1, .box_h = 18, .ofs_x = 4, .ofs_y = -4},
    {.bitmap_index = 1013, .adv_w = 100, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1025, .adv_w = 144, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1027, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1031, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1047, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1053, .adv_w = 160, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1067, .adv_w = 67, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1068, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1075, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1082, .adv_w = 150, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1097, .adv_w = 197, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1115, .adv_w = 157, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1129, .adv_w = 126, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1130, .adv_w = 252, .box_w = 15, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1132, .adv_w = 48, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1134, .adv_w = 48, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1136, .adv_w = 98, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 1139, .adv_w = 94, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1143, .adv_w = 99, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1146, .adv_w = 199, .box_w = 11, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1151, .adv_w = 301, .box_w = 17, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1179, .adv_w = 229, .box_w = 13, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1188, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1197, .adv_w = 229, .box_w = 12, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1205, .adv_w = 126, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72, 0x1f76, 0x1f80,
    0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

static const lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
};

/*-----------------
 *  PUBLIC FONT (LVGL >= 9.6.0)
 *----------------*/

const lv_font_t humid1_font_plex_cond_normal_18 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 26,
    .base_line = 6,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 13,
    .x_height = 10,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_18,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_18 */
