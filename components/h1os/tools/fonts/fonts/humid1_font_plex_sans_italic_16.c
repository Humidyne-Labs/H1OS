/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_16 (sans italic)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_16
#define HUMID1_FONT_PLEX_SANS_ITALIC_16 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x11) */
    0x37, 0x66, 0x64, 0x40, 0xcc, 0xc0,
    /* U+0022 "" (6x5) */
    0x4f, 0x3d, 0xb6, 0xd8,
    /* U+0023 "#" (11x11) */
    0x04, 0x41, 0x98, 0x22, 0x1f, 0xf1, 0x90, 0x22, 0x04, 0xc7, 0xfc, 0x26,
    0x0c, 0x81, 0x10, 0x00,
    /* U+0024 "$" (9x15) */
    0x06, 0x03, 0x07, 0xc6, 0xb6, 0x43, 0x20, 0xf0, 0x3c, 0x0b, 0x05, 0x82,
    0xdb, 0x67, 0xc0, 0x80, 0x40,
    /* U+0025 "%" (12x11) */
    0x70, 0x6d, 0x8c, 0x99, 0x89, 0xb0, 0x92, 0x0e, 0x6e, 0x0d, 0xb1, 0x93,
    0x33, 0x36, 0x32, 0x41, 0xc0,
    /* U+0026 "&" (10x11) */
    0x1e, 0x0c, 0xc3, 0x30, 0xd8, 0x3c, 0x0e, 0x0c, 0xdf, 0x3c, 0xc6, 0x33,
    0xc7, 0xb8,
    /* U+0027 "'" (2x5) */
    0x7f, 0xc0,
    /* U+0028 "(" (6x14) */
    0x0c, 0x63, 0x18, 0x61, 0x0c, 0x30, 0xc3, 0x0c, 0x10, 0x60, 0x80,
    /* U+0029 ")" (6x14) */
    0x30, 0x60, 0x83, 0x0c, 0x30, 0xc3, 0x08, 0x61, 0x0c, 0x63, 0x00,
    /* U+002A "" (7x7) */
    0x18, 0x23, 0xff, 0xf7, 0x9f, 0x32, 0x00,
    /* U+002B "+" (8x7) */
    0x0c, 0x18, 0x18, 0xff, 0x18, 0x30, 0x30,
    /* U+002C "," (3x5) */
    0x6d, 0xa8,
    /* U+002D "-" (5x2) */
    0xff, 0x80,
    /* U+002E "." (2x3) */
    0xfc,
    /* U+002F "/" (9x14) */
    0x01, 0x81, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c,
    0x0c, 0x04, 0x06, 0x00,
    /* U+0030 "0" (8x11) */
    0x1e, 0x33, 0x63, 0xe3, 0xc3, 0xc3, 0xc3, 0xc7, 0xc6, 0xcc, 0x78,
    /* U+0031 "1" (7x11) */
    0x1e, 0x7d, 0x9a, 0x60, 0xc1, 0x83, 0x06, 0x18, 0x33, 0xf8,
    /* U+0032 "2" (9x11) */
    0x1f, 0x19, 0xc0, 0x60, 0x30, 0x38, 0x18, 0x18, 0x10, 0x30, 0x30, 0x3f,
    0xc0,
    /* U+0033 "3" (8x11) */
    0x3e, 0x67, 0x03, 0x03, 0x06, 0x3c, 0x06, 0x06, 0x06, 0xce, 0xf8,
    /* U+0034 "4" (9x11) */
    0x03, 0x83, 0xc1, 0xc1, 0xe1, 0xb1, 0x98, 0x8c, 0xc6, 0xff, 0x83, 0x01,
    0x80,
    /* U+0035 "5" (8x11) */
    0x3f, 0x20, 0x60, 0x60, 0x7c, 0x66, 0x07, 0x07, 0x06, 0xce, 0xf8,
    /* U+0036 "6" (8x11) */
    0x0e, 0x18, 0x30, 0x60, 0x7c, 0xe6, 0xc3, 0xc3, 0xc6, 0xc6, 0x78,
    /* U+0037 "7" (8x11) */
    0xff, 0xc6, 0xc6, 0x8c, 0x0c, 0x18, 0x38, 0x30, 0x60, 0x60, 0xc0,
    /* U+0038 "8" (8x11) */
    0x1e, 0x33, 0x63, 0x63, 0x66, 0x3c, 0xc6, 0xc6, 0xc6, 0xc6, 0x78,
    /* U+0039 "9" (8x11) */
    0x1e, 0x63, 0x63, 0xe3, 0x63, 0x67, 0x3e, 0x06, 0x0c, 0x18, 0x70,
    /* U+003A ":" (3x9) */
    0x6d, 0x80, 0x36, 0xc0,
    /* U+003B ";" (4x11) */
    0x33, 0x30, 0x00, 0x66, 0x64, 0xc0,
    /* U+003C "<" (7x9) */
    0x02, 0x1c, 0xf7, 0x8c, 0x1c, 0x1e, 0x0c, 0x08,
    /* U+003D "=" (8x4) */
    0x7f, 0x00, 0x00, 0xfe,
    /* U+003E ">" (7x9) */
    0x20, 0xe0, 0xe0, 0x70, 0x63, 0x9e, 0x70, 0x80,
    /* U+003F "?" (7x11) */
    0x7d, 0x8c, 0x18, 0x31, 0xc7, 0x0c, 0x00, 0x60, 0xc1, 0x80,
    /* U+0040 "@" (12x13) */
    0x07, 0xc1, 0x86, 0x20, 0x36, 0x79, 0x49, 0x9d, 0x89, 0x99, 0x99, 0x99,
    0x99, 0xac, 0xdc, 0x40, 0x06, 0x00, 0x1f, 0x00,
    /* U+0041 "A" (9x11) */
    0x07, 0x07, 0x83, 0xc3, 0x61, 0xb1, 0xcc, 0xc6, 0xff, 0x61, 0xe0, 0xf0,
    0x60,
    /* U+0042 "B" (9x11) */
    0x3f, 0x30, 0xd8, 0x6c, 0x36, 0x33, 0xf3, 0x0d, 0x86, 0xc3, 0x61, 0xbf,
    0x80,
    /* U+0043 "C" (9x11) */
    0x1f, 0x18, 0xd8, 0x0c, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x31, 0x8f,
    0x80,
    /* U+0044 "D" (9x11) */
    0x3e, 0x31, 0xd8, 0x6c, 0x36, 0x1b, 0x0f, 0x07, 0x83, 0xc3, 0x63, 0x3f,
    0x00,
    /* U+0045 "E" (9x11) */
    0x3f, 0xb0, 0x18, 0x0c, 0x06, 0x03, 0xf3, 0x01, 0x80, 0xc0, 0x60, 0x3f,
    0x80,
    /* U+0046 "F" (8x11) */
    0x3f, 0x60, 0x60, 0x60, 0x60, 0x7e, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (9x11) */
    0x1f, 0x18, 0xd8, 0x0c, 0x0c, 0x06, 0x3f, 0x07, 0x83, 0xc3, 0xb3, 0x8f,
    0xc0,
    /* U+0048 "H" (10x11) */
    0x30, 0xd8, 0x36, 0x0d, 0x83, 0x61, 0x9f, 0xec, 0x1b, 0x06, 0xc3, 0xb0,
    0xcc, 0x30,
    /* U+0049 "I" (7x11) */
    0x3e, 0x30, 0x60, 0xc1, 0x83, 0x0c, 0x18, 0x30, 0x63, 0xe0,
    /* U+004A "J" (8x11) */
    0x1f, 0x03, 0x03, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0xcc, 0x78,
    /* U+004B "K" (11x11) */
    0x38, 0xe6, 0x38, 0xce, 0x1b, 0x83, 0xe0, 0xfc, 0x1f, 0x83, 0xb8, 0x63,
    0x0c, 0x73, 0x86, 0x00,
    /* U+004C "L" (6x11) */
    0x31, 0x86, 0x18, 0x61, 0x8c, 0x30, 0xc3, 0x0f, 0xc0,
    /* U+004D "M" (12x11) */
    0x30, 0x77, 0x0f, 0x78, 0xe7, 0x9e, 0x7b, 0x66, 0xf6, 0xce, 0x6c, 0xcc,
    0xc0, 0xcc, 0x0c, 0x80, 0xc0,
    /* U+004E "N" (10x11) */
    0x30, 0xdc, 0x37, 0x8d, 0xe3, 0x69, 0x93, 0x6c, 0xdb, 0x1e, 0xc7, 0xb1,
    0xc8, 0x30,
    /* U+004F "O" (10x11) */
    0x1f, 0x0c, 0x66, 0x19, 0x83, 0xc1, 0xf0, 0x7c, 0x1b, 0x06, 0xc3, 0x19,
    0xc3, 0xc0,
    /* U+0050 "P" (9x11) */
    0x3f, 0x30, 0xd8, 0x6c, 0x36, 0x33, 0xf3, 0x01, 0x80, 0xc0, 0x60, 0x30,
    0x00,
    /* U+0051 "Q" (10x13) */
    0x1f, 0x0c, 0x66, 0x19, 0x83, 0xc1, 0xf0, 0x7c, 0x1b, 0x06, 0xc3, 0x19,
    0xc3, 0xc0, 0x60, 0x1c, 0x00,
    /* U+0052 "R" (9x11) */
    0x3f, 0x30, 0xd8, 0x6c, 0x36, 0x33, 0xf3, 0x39, 0x8c, 0xc6, 0x63, 0x31,
    0xc0,
    /* U+0053 "S" (9x11) */
    0x0f, 0x18, 0xcc, 0x06, 0x03, 0x00, 0xf0, 0x0c, 0x06, 0x03, 0x71, 0x8f,
    0x00,
    /* U+0054 "T" (8x11) */
    0xff, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60, 0x60, 0x60,
    /* U+0055 "U" (10x11) */
    0x30, 0xd8, 0x36, 0x19, 0x86, 0x61, 0xb8, 0x6c, 0x1b, 0x0c, 0xc3, 0x19,
    0x83, 0xc0,
    /* U+0056 "V" (9x11) */
    0xc1, 0xe1, 0xb0, 0xd8, 0xcc, 0x66, 0x63, 0x30, 0xb0, 0x78, 0x38, 0x1c,
    0x00,
    /* U+0057 "W" (13x11) */
    0xc7, 0x1e, 0x38, 0xf3, 0xc7, 0x9e, 0x6c, 0xb3, 0x6d, 0xb3, 0x4d, 0x9e,
    0x68, 0xf3, 0xc7, 0x1e, 0x38, 0x60,
    /* U+0058 "X" (11x11) */
    0x30, 0xe7, 0x18, 0x66, 0x0f, 0x80, 0xe0, 0x1c, 0x07, 0x81, 0xb0, 0x73,
    0x0c, 0x63, 0x0e, 0x00,
    /* U+0059 "Y" (9x11) */
    0xc3, 0xe1, 0xb1, 0x8d, 0x86, 0xc3, 0xc0, 0xc0, 0x60, 0x30, 0x30, 0x18,
    0x00,
    /* U+005A "Z" (10x11) */
    0x3f, 0xc0, 0x60, 0x30, 0x1c, 0x0e, 0x03, 0x01, 0x80, 0xc0, 0x70, 0x18,
    0x0f, 0xf0,
    /* U+005B "[" (6x14) */
    0x1c, 0x43, 0x0c, 0x30, 0x82, 0x18, 0x61, 0x86, 0x10, 0xc3, 0x80,
    /* U+005C "" (4x14) */
    0xcc, 0x44, 0x66, 0x66, 0x66, 0x22, 0x23,
    /* U+005D "]" (5x14) */
    0x38, 0xc6, 0x31, 0x88, 0xc6, 0x31, 0x08, 0xc6, 0x70,
    /* U+005E "^" (8x6) */
    0x0c, 0x1e, 0x36, 0x36, 0x63, 0xc3,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (2x3) */
    0xd4,
    /* U+0061 "a" (8x8) */
    0x3b, 0x67, 0xc6, 0xc6, 0xc6, 0xc6, 0xce, 0x76,
    /* U+0062 "b" (9x12) */
    0x18, 0x18, 0x0c, 0x06, 0x03, 0x71, 0x99, 0xc6, 0xc3, 0x63, 0x31, 0x99,
    0xdf, 0x80,
    /* U+0063 "c" (7x8) */
    0x3c, 0xcf, 0x06, 0x0c, 0x18, 0x33, 0x3c,
    /* U+0064 "d" (9x12) */
    0x01, 0x81, 0x80, 0xc0, 0x63, 0xb3, 0x3b, 0x19, 0x8c, 0xc6, 0x63, 0x33,
    0x8e, 0xc0,
    /* U+0065 "e" (7x8) */
    0x3c, 0xcf, 0x1f, 0xcc, 0x18, 0xb3, 0x3c,
    /* U+0066 "f" (8x15) */
    0x07, 0x0c, 0x0c, 0x0c, 0x3e, 0x18, 0x18, 0x18, 0x10, 0x30, 0x30, 0x30,
    0x30, 0x20, 0xe0,
    /* U+0067 "g" (9x13) */
    0x01, 0x80, 0x07, 0xc6, 0x66, 0x33, 0x19, 0x98, 0x78, 0x40, 0x3f, 0x20,
    0xd8, 0xef, 0xc0,
    /* U+0068 "h" (8x12) */
    0x18, 0x30, 0x30, 0x30, 0x37, 0x33, 0x73, 0x63, 0x63, 0x63, 0x63, 0xc3,
    /* U+0069 "i" (4x12) */
    0x27, 0x60, 0x66, 0x4c, 0xcc, 0xcc,
    /* U+006A "j" (6x15) */
    0x0c, 0x70, 0x80, 0x18, 0x61, 0x0c, 0x30, 0xc3, 0x08, 0x61, 0x8c, 0x00,
    /* U+006B "k" (9x12) */
    0x18, 0x18, 0x0c, 0x06, 0x03, 0x39, 0xb9, 0xb8, 0xf8, 0x7c, 0x36, 0x19,
    0x98, 0xe0,
    /* U+006C "l" (4x12) */
    0x36, 0x66, 0x66, 0xcc, 0xcc, 0xce,
    /* U+006D "m" (13x8) */
    0x37, 0x71, 0x9c, 0xdc, 0xc6, 0xc6, 0x36, 0x31, 0xb1, 0x99, 0x98, 0xd8,
    0xc7,
    /* U+006E "n" (8x8) */
    0x37, 0x33, 0x73, 0x63, 0x63, 0x63, 0x63, 0xc3,
    /* U+006F "o" (7x8) */
    0x3c, 0xcf, 0x1e, 0x3c, 0x78, 0xf3, 0x3c,
    /* U+0070 "p" (9x11) */
    0x37, 0x19, 0x9c, 0x6c, 0x36, 0x33, 0x19, 0x9d, 0xf8, 0xc0, 0x60, 0x30,
    0x00,
    /* U+0071 "q" (8x11) */
    0x3b, 0x67, 0xc6, 0xc6, 0xc6, 0xc6, 0xce, 0x7c, 0x0c, 0x0c, 0x0c,
    /* U+0072 "r" (6x8) */
    0x3c, 0xc6, 0x18, 0x61, 0x86, 0x30,
    /* U+0073 "s" (7x8) */
    0x3e, 0xcd, 0x83, 0xc1, 0xe0, 0xf3, 0xbe,
    /* U+0074 "t" (5x11) */
    0x31, 0x19, 0xf6, 0x31, 0x98, 0xc6, 0x38,
    /* U+0075 "u" (8x8) */
    0x63, 0x66, 0xc6, 0xc6, 0xc6, 0xc6, 0xcc, 0xe6,
    /* U+0076 "v" (7x8) */
    0xc7, 0x8f, 0x36, 0x6d, 0x8f, 0x1c, 0x38,
    /* U+0077 "w" (12x8) */
    0xc6, 0x3c, 0xe6, 0xce, 0x6d, 0xac, 0xd2, 0xcf, 0x38, 0xe3, 0x86, 0x30,
    /* U+0078 "x" (8x8) */
    0x63, 0x37, 0x3e, 0x1c, 0x38, 0x7c, 0x6c, 0xc6,
    /* U+0079 "y" (8x11) */
    0x63, 0x63, 0x66, 0x66, 0x6c, 0x2c, 0x38, 0x38, 0x30, 0x20, 0xc0,
    /* U+007A "z" (8x8) */
    0x7f, 0x06, 0x0c, 0x18, 0x38, 0x70, 0x60, 0xfe,
    /* U+007B "{" (6x14) */
    0x0c, 0x61, 0x84, 0x10, 0xc6, 0x10, 0xe1, 0x86, 0x18, 0x61, 0xc0,
    /* U+007C "|" (4x14) */
    0x13, 0x33, 0x32, 0x66, 0x64, 0x4c, 0xcc,
    /* U+007D "}" (5x14) */
    0x38, 0xc6, 0x31, 0x0c, 0x61, 0x19, 0x88, 0xc6, 0x60,
    /* U+007E "~" (7x2) */
    0x71, 0x1c,
    /* U+00B0 "" (5x6) */
    0x76, 0x63, 0x1d, 0xb8,
    /* U+00B1 "" (9x10) */
    0x06, 0x03, 0x01, 0x07, 0xf0, 0xc0, 0x60, 0x30, 0x10, 0x00, 0x7f, 0x80,
    /* U+00B2 "" (5x6) */
    0x72, 0xc6, 0x6c, 0x78,
    /* U+00B3 "" (5x6) */
    0x70, 0xdc, 0x29, 0x70,
    /* U+00B5 "" (9x11) */
    0x31, 0x98, 0xd8, 0xcc, 0x66, 0x33, 0x19, 0x9d, 0xf6, 0xc0, 0x60, 0x30,
    0x00,
    /* U+00B7 "" (2x3) */
    0xfc,
    /* U+00D7 "" (8x7) */
    0x22, 0x77, 0x3e, 0x1c, 0x3c, 0xee, 0xc6,
    /* U+00F7 "" (8x7) */
    0x0c, 0x08, 0x00, 0xff, 0x00, 0x10, 0x30,
    /* U+0394 "" (9x11) */
    0x07, 0x07, 0x83, 0xc3, 0xf1, 0x99, 0xcc, 0xc6, 0xe3, 0x61, 0xf0, 0xff,
    0xe0,
    /* U+03A9 "" (11x11) */
    0x0f, 0x83, 0x18, 0xc1, 0x18, 0x36, 0x0e, 0xc1, 0xd8, 0x31, 0x8e, 0x33,
    0x9e, 0x63, 0xcf, 0x00,
    /* U+03BC "" (9x11) */
    0x31, 0x98, 0xd8, 0xcc, 0x66, 0x33, 0x19, 0x9d, 0xf6, 0xc0, 0x60, 0x30,
    0x00,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (11x1) */
    0xff, 0xe0,
    /* U+2018 "" (3x5) */
    0x6b, 0x6c,
    /* U+2019 "" (3x5) */
    0x7f, 0x28,
    /* U+201C "" (6x5) */
    0x65, 0x2c, 0xf7, 0xc8,
    /* U+201D "" (6x5) */
    0x6f, 0xbe, 0xd3, 0x98,
    /* U+2022 "" (5x4) */
    0x77, 0xfe, 0xe0,
    /* U+2026 "" (11x3) */
    0xc4, 0x79, 0x8e, 0x31, 0x80,
    /* U+2030 "" (18x11) */
    0x70, 0x60, 0x36, 0x30, 0x09, 0x98, 0x02, 0x6c, 0x00, 0x92, 0x00, 0x39,
    0xb8, 0xe0, 0xdb, 0x6c, 0x64, 0xd3, 0x33, 0x34, 0xd8, 0x49, 0x24, 0x1c,
    0x70,
    /* U+2190 "" (12x7) */
    0x18, 0x03, 0x80, 0x70, 0x0f, 0xff, 0x70, 0x03, 0x80, 0x18, 0x00,
    /* U+2191 "" (6x10) */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (11x5) */
    0x01, 0x80, 0x1f, 0xff, 0x80, 0x70, 0x18,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x3f, 0x78, 0xc0,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 60, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 77, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 119, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 10, .adv_w = 167, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 145, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 238, .box_w = 12, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 65, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 76, .adv_w = 89, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 89, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 98, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 105, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 112, .adv_w = 76, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 114, .adv_w = 101, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 116, .adv_w = 76, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 115, .box_w = 9, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 133, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 81, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 81, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 268, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 226, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 306, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 147, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 104, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 165, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 129, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 204, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 177, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 530, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 145, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 172, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 235, .box_w = 13, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 161, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 156, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 146, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 82, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 666, .adv_w = 115, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 673, .adv_w = 82, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 682, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 688, .adv_w = 140, .box_w = 8, .box_h = 1, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 689, .adv_w = 151, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 690, .adv_w = 151, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 87, .box_w = 8, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 755, .adv_w = 135, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 770, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 69, .box_w = 6, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 800, .adv_w = 138, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 71, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 222, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 833, .adv_w = 148, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 841, .adv_w = 140, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 861, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 872, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 125, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 129, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 907, .adv_w = 199, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 131, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 938, .adv_w = 123, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 90, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 957, .adv_w = 94, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 964, .adv_w = 90, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 973, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 975, .adv_w = 117, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 979, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 995, .adv_w = 86, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 999, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1012, .adv_w = 87, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 1013, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1020, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1027, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1040, .adv_w = 176, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1056, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1069, .adv_w = 148, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1070, .adv_w = 196, .box_w = 11, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1072, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1074, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1076, .adv_w = 129, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1080, .adv_w = 129, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1084, .adv_w = 105, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1087, .adv_w = 220, .box_w = 11, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1092, .adv_w = 336, .box_w = 18, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1117, .adv_w = 224, .box_w = 12, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1128, .adv_w = 224, .box_w = 6, .box_h = 10, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 224, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1143, .adv_w = 224, .box_w = 6, .box_h = 10, .ofs_x = 4, .ofs_y = 1}
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

const lv_font_t humid1_font_plex_sans_italic_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_16 */
