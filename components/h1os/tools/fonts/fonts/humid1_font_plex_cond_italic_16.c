/*******************************************************************************
 * Font: humid1_font_plex_cond_italic_16 (cond italic)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_cond_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_ITALIC_16
#define HUMID1_FONT_PLEX_COND_ITALIC_16 1
#endif

#if HUMID1_FONT_PLEX_COND_ITALIC_16

extern const lv_font_t humid1_font_plex_cond_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x12) */
    0x33, 0x32, 0x66, 0x66, 0x00, 0xcc,
    /* U+0022 "" (5x4) */
    0x5a, 0xd7, 0xa0,
    /* U+0023 "#" (9x12) */
    0x09, 0x05, 0x86, 0xcf, 0xf7, 0xf8, 0x90, 0xd9, 0xfe, 0xff, 0x12, 0x0b,
    0x0d, 0x00,
    /* U+0024 "$" (7x11) */
    0x1e, 0x7c, 0xfb, 0x43, 0x87, 0x07, 0x0b, 0x17, 0xf9, 0xe0,
    /* U+0025 "%" (10x12) */
    0x70, 0x9c, 0x4d, 0x32, 0x48, 0x96, 0x2d, 0x7f, 0xbd, 0xed, 0x12, 0x4c,
    0xb2, 0x3d, 0x0e,
    /* U+0026 "&" (8x12) */
    0x1c, 0x3c, 0x24, 0x64, 0x3c, 0x38, 0x71, 0xdb, 0x8e, 0xce, 0xfe, 0x76,
    /* U+0027 "'" (3x4) */
    0x6b, 0x60,
    /* U+0028 "(" (4x14) */
    0x13, 0x64, 0xcc, 0x88, 0x88, 0x88, 0xcc,
    /* U+0029 ")" (5x14) */
    0x10, 0xc6, 0x31, 0x8c, 0x63, 0x10, 0x8c, 0x46, 0x60,
    /* U+002A "" (7x7) */
    0x18, 0x33, 0xc1, 0xf3, 0x8f, 0x12, 0x00,
    /* U+002B "+" (6x8) */
    0x30, 0xc3, 0x3f, 0xfc, 0xc3, 0x0c,
    /* U+002C "," (3x4) */
    0x6d, 0x60,
    /* U+002D "-" (4x2) */
    0x7f,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (7x12) */
    0x06, 0x18, 0x30, 0xc1, 0x86, 0x0c, 0x30, 0x60, 0x83, 0x04, 0x00,
    /* U+0030 "0" (7x12) */
    0x1c, 0x7c, 0xdb, 0x36, 0x6c, 0xd1, 0xe3, 0xc6, 0xd9, 0xf1, 0xc0,
    /* U+0031 "1" (4x12) */
    0x37, 0xfb, 0x32, 0x66, 0x66, 0x64,
    /* U+0032 "2" (7x12) */
    0x1c, 0x7c, 0x98, 0x30, 0x61, 0xc3, 0x0c, 0x30, 0xc3, 0xf7, 0xe0,
    /* U+0033 "3" (7x12) */
    0x1c, 0x7c, 0x18, 0x30, 0x67, 0x8f, 0x03, 0x06, 0x1f, 0xf3, 0xc0,
    /* U+0034 "4" (7x12) */
    0x06, 0x1c, 0x38, 0xf3, 0x64, 0x9b, 0x66, 0xff, 0xfc, 0x30, 0x40,
    /* U+0035 "5" (7x12) */
    0x3e, 0x7c, 0xc1, 0x02, 0x0f, 0x9f, 0x03, 0x06, 0x1b, 0xf3, 0xc0,
    /* U+0036 "6" (6x12) */
    0x1c, 0xf6, 0x10, 0xc3, 0x6f, 0xf3, 0x8f, 0x3f, 0x9e,
    /* U+0037 "7" (7x12) */
    0xff, 0xfc, 0x30, 0x61, 0x83, 0x0c, 0x18, 0x60, 0xc3, 0x06, 0x00,
    /* U+0038 "8" (7x12) */
    0x1c, 0x7c, 0xc9, 0x13, 0x63, 0x8f, 0x33, 0x47, 0x8d, 0xf1, 0xc0,
    /* U+0039 "9" (6x12) */
    0x39, 0xfc, 0xf3, 0xcf, 0x3f, 0xdb, 0x08, 0x6f, 0x38,
    /* U+003A ":" (3x9) */
    0x24, 0x00, 0x06, 0xc0,
    /* U+003B ";" (3x10) */
    0x24, 0x00, 0x36, 0x90,
    /* U+003C "<" (6x7) */
    0x0c, 0xee, 0x30, 0x70, 0x70, 0x40,
    /* U+003D "=" (6x5) */
    0xff, 0xf0, 0x3f, 0xfc,
    /* U+003E ">" (6x7) */
    0xc1, 0xc1, 0xc3, 0x3b, 0x88, 0x00,
    /* U+003F "?" (6x12) */
    0x71, 0xe0, 0xc3, 0x18, 0xe7, 0x18, 0x40, 0x0c, 0x30,
    /* U+0040 "@" (11x13) */
    0x0f, 0x07, 0xf9, 0xc3, 0x27, 0xbd, 0xb7, 0x24, 0xac, 0x95, 0xb6, 0x9b,
    0x98, 0x03, 0x80, 0x3f, 0x03, 0xc0,
    /* U+0041 "A" (9x12) */
    0x07, 0x03, 0x83, 0xc1, 0xe1, 0xb0, 0xd8, 0x64, 0x7e, 0x3f, 0x30, 0xd8,
    0x78, 0x30,
    /* U+0042 "B" (8x12) */
    0x3e, 0x3f, 0x33, 0x33, 0x33, 0x7e, 0x7e, 0x66, 0x63, 0x66, 0x7e, 0xfc,
    /* U+0043 "C" (8x12) */
    0x1e, 0x3f, 0x70, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x7c, 0x3c,
    /* U+0044 "D" (9x12) */
    0x3e, 0x1f, 0x8c, 0xe6, 0x33, 0x19, 0x0d, 0x86, 0xc3, 0x63, 0x33, 0x9f,
    0x9f, 0x80,
    /* U+0045 "E" (8x12) */
    0x3f, 0x3f, 0x30, 0x30, 0x30, 0x3e, 0x7e, 0x60, 0x60, 0x60, 0x7c, 0xfc,
    /* U+0046 "F" (8x12) */
    0x3f, 0x3f, 0x30, 0x30, 0x20, 0x3e, 0x7c, 0x60, 0x60, 0x60, 0x40, 0xc0,
    /* U+0047 "G" (8x12) */
    0x1f, 0x3f, 0x70, 0x60, 0xc0, 0xcf, 0xce, 0xc2, 0xc6, 0xc6, 0x7e, 0x3c,
    /* U+0048 "H" (10x12) */
    0x30, 0xcc, 0x23, 0x18, 0xc6, 0x31, 0x8f, 0xe7, 0xf9, 0x84, 0x63, 0x18,
    0xc4, 0x33, 0x0c,
    /* U+0049 "I" (6x12) */
    0x3c, 0xe3, 0x0c, 0x30, 0xc3, 0x08, 0x61, 0x8e, 0x3c,
    /* U+004A "J" (6x15) */
    0x0c, 0x30, 0xc3, 0x0c, 0x31, 0x86, 0x18, 0x61, 0x8c, 0x33, 0xce, 0x00,
    /* U+004B "K" (9x12) */
    0x31, 0x99, 0xcc, 0xc6, 0xc3, 0xc1, 0xe1, 0xf0, 0xd8, 0x6c, 0x33, 0x11,
    0x98, 0xc0,
    /* U+004C "L" (6x12) */
    0x30, 0xc3, 0x0c, 0x30, 0x86, 0x18, 0x61, 0x87, 0xff,
    /* U+004D "M" (12x12) */
    0x38, 0x73, 0x87, 0x38, 0xf3, 0x8f, 0x28, 0xa6, 0x9e, 0x69, 0x66, 0xb6,
    0x6a, 0x64, 0xe4, 0x4e, 0x4c, 0xcc,
    /* U+004E "N" (10x12) */
    0x38, 0x4e, 0x33, 0x8c, 0xb3, 0x2c, 0xdb, 0x26, 0x49, 0x9e, 0x67, 0x91,
    0xe4, 0x3b, 0x0c,
    /* U+004F "O" (8x12) */
    0x1e, 0x3f, 0x63, 0x61, 0xc1, 0xc1, 0xc3, 0xc3, 0xc3, 0xc6, 0x7e, 0x38,
    /* U+0050 "P" (8x12) */
    0x3e, 0x3f, 0x33, 0x31, 0x33, 0x23, 0x7e, 0x7c, 0x60, 0x60, 0x40, 0xc0,
    /* U+0051 "Q" (8x14) */
    0x1e, 0x3f, 0x63, 0x61, 0xc1, 0xc1, 0xc3, 0xc3, 0xc3, 0xc6, 0x7e, 0x3c,
    0x0c, 0x0e,
    /* U+0052 "R" (8x12) */
    0x3e, 0x3f, 0x33, 0x33, 0x33, 0x23, 0x7e, 0x7e, 0x7c, 0x6c, 0x6e, 0xe6,
    /* U+0053 "S" (7x12) */
    0x1e, 0x7c, 0xc1, 0x03, 0x07, 0x07, 0x06, 0x0c, 0x1b, 0xf3, 0xc0,
    /* U+0054 "T" (7x12) */
    0xff, 0xfc, 0x41, 0x83, 0x06, 0x0c, 0x18, 0x20, 0xc1, 0x83, 0x00,
    /* U+0055 "U" (8x12) */
    0x61, 0x63, 0x63, 0x63, 0x43, 0xc3, 0xc2, 0xc6, 0xc6, 0xc6, 0xfc, 0x78,
    /* U+0056 "V" (8x12) */
    0xc3, 0xc3, 0xc6, 0x46, 0x44, 0x4c, 0x4c, 0x58, 0x78, 0x70, 0x70, 0x60,
    /* U+0057 "W" (12x12) */
    0xc6, 0x1c, 0x63, 0xc6, 0x3c, 0xe2, 0xca, 0x6c, 0xa6, 0xda, 0xcd, 0x2c,
    0xd2, 0x87, 0x38, 0x63, 0x86, 0x30,
    /* U+0058 "X" (9x12) */
    0x31, 0x99, 0x8c, 0xc2, 0xc1, 0xc0, 0xe0, 0x70, 0x78, 0x6c, 0x33, 0x31,
    0x98, 0xc0,
    /* U+0059 "Y" (8x12) */
    0xc3, 0x46, 0x66, 0x6c, 0x68, 0x78, 0x30, 0x30, 0x30, 0x20, 0x60, 0x60,
    /* U+005A "Z" (8x12) */
    0x3f, 0x3f, 0x06, 0x0e, 0x0c, 0x18, 0x38, 0x30, 0x60, 0xe0, 0xfc, 0xfc,
    /* U+005B "[" (5x15) */
    0x39, 0xcc, 0x42, 0x31, 0x8c, 0x42, 0x11, 0x8c, 0x73, 0x80,
    /* U+005C "" (3x12) */
    0x92, 0x6d, 0xb6, 0x49, 0x30,
    /* U+005D "]" (6x15) */
    0x1c, 0xe0, 0x82, 0x18, 0x61, 0x84, 0x10, 0xc3, 0x0c, 0x33, 0x8e, 0x00,
    /* U+005E "^" (6x7) */
    0x10, 0xe2, 0x92, 0x4e, 0x18, 0x40,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (3x3) */
    0xc9, 0x80,
    /* U+0061 "a" (7x9) */
    0x36, 0xff, 0x36, 0x6c, 0xd1, 0xb7, 0x7c, 0xe8,
    /* U+0062 "b" (7x12) */
    0x30, 0x60, 0xc1, 0xf3, 0xee, 0xd8, 0xb3, 0x66, 0xcd, 0xf6, 0xc0,
    /* U+0063 "c" (5x9) */
    0x3b, 0xf1, 0x8c, 0x43, 0x1f, 0x70,
    /* U+0064 "d" (7x12) */
    0x02, 0x0c, 0x19, 0xb7, 0xf9, 0xb3, 0x66, 0x8d, 0xbb, 0xe3, 0x40,
    /* U+0065 "e" (6x9) */
    0x39, 0xfe, 0xf3, 0xff, 0xcc, 0x3e, 0x78,
    /* U+0066 "f" (7x16) */
    0x06, 0x1c, 0x60, 0xe3, 0xc3, 0x04, 0x18, 0x30, 0x60, 0xc1, 0x82, 0x0c,
    0x38, 0x60,
    /* U+0067 "g" (8x13) */
    0x1b, 0x3f, 0x66, 0x66, 0x66, 0x46, 0x66, 0x7c, 0x34, 0x0c, 0x0c, 0xf8,
    0x70,
    /* U+0068 "h" (7x12) */
    0x30, 0x60, 0xc1, 0xf3, 0xee, 0x58, 0xb3, 0x66, 0xcd, 0x1e, 0x30,
    /* U+0069 "i" (4x12) */
    0x33, 0x03, 0x26, 0x66, 0x66, 0xcc,
    /* U+006A "j" (6x16) */
    0x0c, 0x30, 0x03, 0x08, 0x61, 0x86, 0x18, 0x61, 0x0c, 0x30, 0xce, 0x38,
    /* U+006B "k" (8x12) */
    0x30, 0x30, 0x30, 0x33, 0x26, 0x6c, 0x78, 0x78, 0x78, 0x6c, 0x4c, 0xc6,
    /* U+006C "l" (4x12) */
    0x33, 0x33, 0x36, 0x66, 0x66, 0xcc,
    /* U+006D "m" (12x9) */
    0x2e, 0x63, 0xef, 0x77, 0x36, 0x33, 0x66, 0x26, 0x66, 0x66, 0x64, 0x66,
    0xc4, 0x60,
    /* U+006E "n" (7x9) */
    0x2e, 0x7d, 0xcb, 0x16, 0x6c, 0xd9, 0xa3, 0xc6,
    /* U+006F "o" (6x9) */
    0x39, 0xfc, 0xf1, 0xce, 0x3c, 0xfe, 0x78,
    /* U+0070 "p" (7x13) */
    0x2e, 0x7d, 0xdb, 0x16, 0x6c, 0xd9, 0xbe, 0xd9, 0x83, 0x06, 0x08, 0x00,
    /* U+0071 "q" (7x13) */
    0x36, 0xff, 0x36, 0x6c, 0xd1, 0xb7, 0x7c, 0xe8, 0x30, 0x60, 0xc1, 0x80,
    /* U+0072 "r" (6x9) */
    0x2c, 0xf7, 0x18, 0x61, 0x86, 0x10, 0xc0,
    /* U+0073 "s" (6x9) */
    0x3d, 0xf6, 0x18, 0x38, 0x61, 0xbe, 0x70,
    /* U+0074 "t" (5x11) */
    0x21, 0x1f, 0xe4, 0x63, 0x18, 0xc7, 0x38,
    /* U+0075 "u" (7x9) */
    0x46, 0x8f, 0x1e, 0x2c, 0xd9, 0xb3, 0x7e, 0xe8,
    /* U+0076 "v" (7x9) */
    0xcf, 0x9b, 0x36, 0xcd, 0x9e, 0x3c, 0x70, 0x60,
    /* U+0077 "w" (10x9) */
    0xcc, 0xf7, 0x3d, 0xcf, 0x56, 0xf5, 0xbd, 0x4e, 0x73, 0x9c, 0xc6, 0x00,
    /* U+0078 "x" (7x9) */
    0x66, 0x4c, 0xf1, 0xc3, 0x87, 0x1e, 0x66, 0xcc,
    /* U+0079 "y" (8x13) */
    0x31, 0x33, 0x33, 0x36, 0x36, 0x34, 0x1c, 0x18, 0x18, 0x10, 0x30, 0xe0,
    0xc0,
    /* U+007A "z" (6x9) */
    0x7d, 0xf0, 0x86, 0x31, 0x86, 0x3e, 0xf8,
    /* U+007B "{" (6x14) */
    0x0c, 0x61, 0x0c, 0x30, 0xce, 0x30, 0x61, 0x86, 0x18, 0x60, 0x80,
    /* U+007C "|" (1x16) */
    0xff, 0xff,
    /* U+007D "}" (6x14) */
    0x30, 0xe1, 0x86, 0x10, 0x61, 0xc7, 0x30, 0xc2, 0x18, 0xe3, 0x00,
    /* U+007E "~" (6x3) */
    0xe3, 0xf1, 0xc0,
    /* U+00B0 "" (4x6) */
    0x6f, 0x99, 0xf6,
    /* U+00B1 "" (6x10) */
    0x30, 0xc3, 0x3f, 0xfc, 0xc3, 0x0c, 0xff, 0xf0,
    /* U+00B2 "" (5x7) */
    0x73, 0xc6, 0x66, 0x7b, 0xc0,
    /* U+00B3 "" (5x7) */
    0x73, 0xcc, 0xe1, 0x7b, 0x80,
    /* U+00B5 "" (8x13) */
    0x33, 0x23, 0x63, 0x62, 0x66, 0x66, 0x66, 0x7e, 0xf6, 0xc0, 0xc0, 0xc0,
    0x80,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x7) */
    0xc5, 0x37, 0x8c, 0x7b, 0x30, 0x40,
    /* U+00F7 "" (6x8) */
    0x10, 0xc0, 0x3f, 0xfc, 0x01, 0x0c,
    /* U+0394 "" (7x12) */
    0x0c, 0x1c, 0x78, 0xb3, 0x66, 0xc9, 0xb1, 0x63, 0x87, 0xff, 0xf0,
    /* U+03A9 "" (10x12) */
    0x0f, 0x07, 0xe3, 0x19, 0x83, 0x60, 0xd8, 0x36, 0x09, 0x86, 0x21, 0x0c,
    0xcf, 0x7b, 0xde,
    /* U+03BC "" (8x13) */
    0x33, 0x23, 0x63, 0x62, 0x66, 0x66, 0x66, 0x7e, 0xf6, 0xc0, 0xc0, 0xc0,
    0x80,
    /* U+2013 "" (6x2) */
    0x7f, 0xf0,
    /* U+2014 "" (13x2) */
    0x7f, 0xff, 0xff, 0xc0,
    /* U+2018 "" (3x4) */
    0x6f, 0x60,
    /* U+2019 "" (3x4) */
    0x6b, 0x40,
    /* U+201C "" (6x4) */
    0x6d, 0x2d, 0xb6,
    /* U+201D "" (6x4) */
    0x6d, 0x2d, 0xa4,
    /* U+2022 "" (4x5) */
    0x6e, 0xfe, 0x60,
    /* U+2026 "" (10x2) */
    0xcc, 0xf3, 0x30,
    /* U+2030 "" (15x12) */
    0x70, 0x80, 0xe2, 0x03, 0x4c, 0x04, 0x90, 0x09, 0x60, 0x16, 0xb9, 0xfe,
    0xf7, 0xbd, 0xad, 0x12, 0x52, 0x65, 0xac, 0x8f, 0x7a, 0x1c, 0xe0,
    /* U+2190 "" (11x5) */
    0x20, 0x08, 0x03, 0xff, 0xa0, 0x02, 0x00,
    /* U+2191 "" (5x11) */
    0x23, 0xbe, 0x42, 0x10, 0x84, 0x21, 0x08,
    /* U+2192 "" (11x5) */
    0x00, 0x80, 0x1b, 0xff, 0x80, 0x60, 0x08,
    /* U+2193 "" (5x11) */
    0x21, 0x08, 0x42, 0x10, 0x84, 0xfb, 0x88,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 60, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 97, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 33, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 62, .adv_w = 72, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 72, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 123, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 85, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 91, .adv_w = 62, .box_w = 3, .box_h = 4, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 93, .adv_w = 71, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 94, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 89, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 120, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 123, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 120, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 120, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 120, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 123, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 120, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 120, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 60, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 60, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 215, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 221, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 225, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 231, .adv_w = 101, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 188, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 258, .adv_w = 136, .box_w = 9, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 135, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 119, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 115, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 155, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 81, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 71, .box_w = 6, .box_h = 15, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 382, .adv_w = 134, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 113, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 194, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 160, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 476, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 115, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 117, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 129, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 197, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 130, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 122, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 120, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 71, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 600, .adv_w = 89, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 71, .box_w = 6, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 623, .adv_w = 89, .box_w = 5, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 624, .adv_w = 69, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 626, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 634, .adv_w = 130, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 105, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 130, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 80, .box_w = 7, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 683, .adv_w = 130, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 696, .adv_w = 132, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 63, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 63, .box_w = 6, .box_h = 16, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 725, .adv_w = 122, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 63, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 199, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 130, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 784, .adv_w = 130, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 796, .adv_w = 91, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 102, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 810, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 111, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 833, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 113, .box_w = 8, .box_h = 13, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 866, .adv_w = 101, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 76, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 884, .adv_w = 123, .box_w = 1, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 886, .adv_w = 76, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 897, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 900, .adv_w = 92, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 903, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 916, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 921, .adv_w = 133, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 934, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 935, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 941, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 947, .adv_w = 132, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 137, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 986, .adv_w = 108, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 988, .adv_w = 215, .box_w = 13, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 992, .adv_w = 45, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 994, .adv_w = 45, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 996, .adv_w = 91, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 999, .adv_w = 91, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1002, .adv_w = 81, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1005, .adv_w = 187, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1008, .adv_w = 269, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1031, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1038, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1045, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1052, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_cond_italic_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 23,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 12,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_cond_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_ITALIC_16 */
