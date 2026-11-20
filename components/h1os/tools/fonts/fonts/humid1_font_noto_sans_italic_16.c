/*******************************************************************************
 * Font: humid1_font_noto_sans_italic_16 (noto_sans italic)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_noto_sans_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_NOTO_SANS_ITALIC_16
#define HUMID1_FONT_NOTO_SANS_ITALIC_16 1
#endif

#if HUMID1_FONT_NOTO_SANS_ITALIC_16

extern const lv_font_t humid1_font_noto_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (5x12) */
    0x39, 0x8c, 0x63, 0x31, 0x8c, 0x00, 0x11, 0x80,
    /* U+0022 "" (5x4) */
    0xde, 0xe5, 0x20,
    /* U+0023 "#" (10x12) */
    0x04, 0x83, 0x20, 0x99, 0xff, 0x7f, 0xc4, 0xc1, 0x31, 0xfe, 0xff, 0x89,
    0x82, 0x40, 0x90,
    /* U+0024 "$" (8x11) */
    0x1f, 0x3f, 0x3f, 0x34, 0x3c, 0x1c, 0x0e, 0x0b, 0x0a, 0xfe, 0x7c,
    /* U+0025 "%" (12x12) */
    0x30, 0x47, 0x8c, 0xd9, 0x8d, 0x90, 0xdb, 0x0d, 0xee, 0xf5, 0xf6, 0xdb,
    0x19, 0x31, 0x12, 0x21, 0xe6, 0x1c,
    /* U+0026 "&" (10x12) */
    0x1e, 0x0f, 0x83, 0x30, 0xd8, 0x3e, 0x0f, 0x07, 0x8f, 0x76, 0xcf, 0x31,
    0xcf, 0xf1, 0xee,
    /* U+0027 "'" (2x4) */
    0xfa,
    /* U+0028 "(" (5x14) */
    0x19, 0x88, 0xc4, 0x63, 0x18, 0x84, 0x21, 0x8c, 0x20,
    /* U+0029 ")" (6x14) */
    0x18, 0x61, 0x83, 0x0c, 0x30, 0x86, 0x18, 0x63, 0x0c, 0x63, 0x00,
    /* U+002A "" (7x7) */
    0x18, 0x23, 0xc3, 0xf7, 0x1b, 0x06, 0x00,
    /* U+002B "+" (8x8) */
    0x10, 0x10, 0x10, 0xfe, 0xff, 0x10, 0x10, 0x10,
    /* U+002C "," (4x4) */
    0x36, 0x6c,
    /* U+002D "-" (5x2) */
    0x7f, 0x80,
    /* U+002E "." (2x2) */
    0x70,
    /* U+002F "/" (7x12) */
    0x06, 0x0c, 0x30, 0x61, 0x83, 0x0c, 0x18, 0x60, 0xc3, 0x06, 0x00,
    /* U+0030 "0" (7x12) */
    0x1c, 0xfd, 0x9e, 0x3c, 0x78, 0xf1, 0xe3, 0xcf, 0x9b, 0xe3, 0x80,
    /* U+0031 "1" (5x12) */
    0x1b, 0xff, 0xb3, 0x18, 0xc6, 0x33, 0x18, 0xc0,
    /* U+0032 "2" (8x12) */
    0x1e, 0x3f, 0x23, 0x03, 0x03, 0x06, 0x0e, 0x1c, 0x38, 0x60, 0xfe, 0xfe,
    /* U+0033 "3" (8x12) */
    0x1e, 0x3f, 0x03, 0x03, 0x07, 0x1e, 0x1e, 0x07, 0x03, 0x06, 0xfe, 0x7c,
    /* U+0034 "4" (8x12) */
    0x03, 0x07, 0x0f, 0x1f, 0x1e, 0x36, 0x66, 0xc6, 0xff, 0xff, 0x0c, 0x0c,
    /* U+0035 "5" (8x12) */
    0x1f, 0x1f, 0x30, 0x30, 0x30, 0x3c, 0x3e, 0x07, 0x03, 0x06, 0xfe, 0x78,
    /* U+0036 "6" (8x12) */
    0x0f, 0x3e, 0x70, 0x60, 0xc0, 0xdc, 0xfe, 0xc6, 0xc6, 0xce, 0xfc, 0x78,
    /* U+0037 "7" (8x12) */
    0x7f, 0xff, 0x06, 0x06, 0x0c, 0x1c, 0x18, 0x30, 0x30, 0x60, 0xe0, 0xc0,
    /* U+0038 "8" (7x12) */
    0x3c, 0xfd, 0x9b, 0x36, 0x67, 0x9f, 0x66, 0x87, 0x9f, 0xf3, 0xc0,
    /* U+0039 "9" (7x12) */
    0x3c, 0xff, 0x9e, 0x3c, 0x79, 0xff, 0xbb, 0x0c, 0x3b, 0xe7, 0x80,
    /* U+003A ":" (4x9) */
    0x33, 0x00, 0x00, 0x04, 0xc0,
    /* U+003B ";" (5x10) */
    0x18, 0xc0, 0x00, 0x01, 0x8c, 0x46, 0x00,
    /* U+003C "<" (8x7) */
    0x06, 0x1c, 0x70, 0xe0, 0x78, 0x1e, 0x03,
    /* U+003D "=" (7x5) */
    0xff, 0xfc, 0x07, 0xff, 0xe0,
    /* U+003E ">" (8x8) */
    0x80, 0xe0, 0x78, 0x1e, 0x07, 0x1c, 0xf0, 0xc0,
    /* U+003F "?" (6x12) */
    0x39, 0xf0, 0x43, 0x0c, 0xe3, 0x18, 0x00, 0x04, 0x30,
    /* U+0040 "@" (12x13) */
    0x0f, 0xc3, 0xfe, 0x70, 0x76, 0x7b, 0xcd, 0x99, 0x91, 0x91, 0x39, 0x32,
    0x9d, 0xcc, 0x00, 0xe0, 0x07, 0xf8, 0x1e, 0x00,
    /* U+0041 "A" (10x12) */
    0x03, 0x81, 0xe0, 0x78, 0x36, 0x0d, 0x86, 0x61, 0x98, 0xfe, 0x3f, 0x98,
    0x36, 0x0f, 0x03,
    /* U+0042 "B" (8x12) */
    0x3e, 0x3f, 0x63, 0x63, 0x63, 0x7e, 0x7e, 0xc6, 0xc7, 0xc6, 0xfe, 0xfc,
    /* U+0043 "C" (9x12) */
    0x0f, 0x1f, 0xdc, 0x0c, 0x0e, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x70, 0x1f,
    0x87, 0xc0,
    /* U+0044 "D" (9x12) */
    0x3e, 0x1f, 0x98, 0xec, 0x36, 0x1b, 0x0d, 0x87, 0x83, 0xc3, 0x63, 0xbf,
    0x9f, 0x00,
    /* U+0045 "E" (8x12) */
    0x3f, 0x3f, 0x60, 0x60, 0x60, 0x7e, 0x7c, 0xc0, 0xc0, 0xc0, 0xfc, 0xfc,
    /* U+0046 "F" (8x12) */
    0x3f, 0x3f, 0x60, 0x60, 0x60, 0x7c, 0x7c, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (9x12) */
    0x0f, 0x9f, 0xdc, 0x0c, 0x0e, 0x06, 0x3f, 0x1f, 0x86, 0xc3, 0x71, 0x9f,
    0xc7, 0xc0,
    /* U+0048 "H" (10x12) */
    0x30, 0xcc, 0x36, 0x0d, 0x86, 0x61, 0x9f, 0xe7, 0xfb, 0x06, 0xc3, 0x30,
    0xcc, 0x33, 0x0c,
    /* U+0049 "I" (7x12) */
    0x3e, 0x78, 0x60, 0xc3, 0x06, 0x0c, 0x18, 0x30, 0xc3, 0xc7, 0x80,
    /* U+004A "J" (8x15) */
    0x03, 0x03, 0x07, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
    0x18, 0xf8, 0x70,
    /* U+004B "K" (9x12) */
    0x31, 0x99, 0xd9, 0xcc, 0xc6, 0xc3, 0xc1, 0xe1, 0xd8, 0xcc, 0x67, 0x31,
    0x98, 0xc0,
    /* U+004C "L" (6x12) */
    0x30, 0xc6, 0x18, 0x61, 0x86, 0x30, 0xc3, 0x0f, 0xff,
    /* U+004D "M" (13x12) */
    0x38, 0x39, 0xc3, 0x9e, 0x1c, 0xf1, 0xe7, 0x8b, 0x24, 0xd9, 0x24, 0x99,
    0x6c, 0xca, 0x66, 0x73, 0x23, 0x19, 0x18, 0x80,
    /* U+004E "N" (11x12) */
    0x30, 0x67, 0x09, 0xe3, 0x3c, 0x66, 0xcc, 0x99, 0x93, 0x26, 0x24, 0xc7,
    0x98, 0xf3, 0x0e, 0x41, 0x80,
    /* U+004F "O" (10x12) */
    0x0f, 0x0f, 0xe7, 0x1d, 0x83, 0xe0, 0xf0, 0x3c, 0x1f, 0x06, 0xc1, 0xb8,
    0xc7, 0xf0, 0xf0,
    /* U+0050 "P" (8x12) */
    0x3e, 0x7f, 0x63, 0x63, 0x63, 0x67, 0x7e, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (10x14) */
    0x0f, 0x0f, 0xe7, 0x19, 0x83, 0xe0, 0xf0, 0x3c, 0x1f, 0x06, 0xc1, 0xb8,
    0xc7, 0xf0, 0xf0, 0x06, 0x01, 0xc0,
    /* U+0052 "R" (8x12) */
    0x3e, 0x3f, 0x63, 0x63, 0x63, 0x63, 0x7e, 0xfc, 0xfc, 0xdc, 0xcc, 0xce,
    /* U+0053 "S" (8x12) */
    0x1f, 0x3f, 0x30, 0x30, 0x30, 0x3c, 0x1c, 0x0e, 0x06, 0x06, 0xfc, 0x78,
    /* U+0054 "T" (8x12) */
    0x7f, 0xff, 0x18, 0x18, 0x18, 0x10, 0x30, 0x30, 0x30, 0x30, 0x60, 0x60,
    /* U+0055 "U" (10x12) */
    0x30, 0xd8, 0x76, 0x19, 0x86, 0x61, 0x98, 0x6c, 0x1b, 0x0c, 0xc3, 0x31,
    0xc7, 0xe0, 0xf0,
    /* U+0056 "V" (8x12) */
    0x83, 0xc3, 0xc6, 0xc6, 0xcc, 0xcc, 0xd8, 0xd8, 0xd0, 0xf0, 0xe0, 0xe0,
    /* U+0057 "W" (14x12) */
    0xc3, 0x0f, 0x0c, 0x34, 0x71, 0x91, 0xc6, 0x45, 0x19, 0x34, 0xc4, 0x93,
    0x16, 0x48, 0x59, 0x61, 0xc7, 0x07, 0x1c, 0x18, 0x70,
    /* U+0058 "X" (11x12) */
    0x18, 0x63, 0x18, 0x37, 0x06, 0xc0, 0xf0, 0x0e, 0x03, 0x80, 0xf8, 0x1b,
    0x06, 0x61, 0x86, 0x70, 0xc0,
    /* U+0059 "Y" (8x12) */
    0xc3, 0xc6, 0xce, 0xcc, 0x78, 0x78, 0x70, 0x60, 0x60, 0x60, 0x60, 0xe0,
    /* U+005A "Z" (9x12) */
    0x3f, 0x9f, 0xc0, 0xc0, 0xc0, 0xe0, 0x60, 0x60, 0x60, 0x70, 0x30, 0x3f,
    0x9f, 0xc0,
    /* U+005B "[" (6x15) */
    0x1c, 0xf3, 0x0c, 0x30, 0x86, 0x18, 0x61, 0x84, 0x30, 0xc3, 0x8e, 0x00,
    /* U+005C "" (3x12) */
    0xdb, 0x6d, 0x93, 0x6d, 0xb0,
    /* U+005D "]" (6x15) */
    0x1c, 0x70, 0xc3, 0x08, 0x21, 0x86, 0x18, 0x43, 0x0c, 0x33, 0xce, 0x00,
    /* U+005E "^" (7x7) */
    0x18, 0x70, 0xb3, 0x24, 0x58, 0xe0, 0x80,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x3) */
    0xb4,
    /* U+0061 "a" (8x9) */
    0x3b, 0x7f, 0x66, 0xc6, 0xc6, 0xc6, 0xce, 0xfc, 0x64,
    /* U+0062 "b" (8x12) */
    0x18, 0x18, 0x30, 0x36, 0x3f, 0x33, 0x63, 0x63, 0x63, 0x67, 0x7e, 0xdc,
    /* U+0063 "c" (6x9) */
    0x3d, 0xfe, 0x30, 0xc3, 0x0c, 0x3e, 0x78,
    /* U+0064 "d" (8x12) */
    0x03, 0x03, 0x03, 0x3b, 0x7f, 0xe6, 0xc6, 0xc6, 0xc6, 0xce, 0xfc, 0x64,
    /* U+0065 "e" (7x9) */
    0x3c, 0xff, 0x9e, 0x3f, 0xdf, 0x30, 0x7e, 0x78,
    /* U+0066 "f" (9x16) */
    0x03, 0x83, 0xc1, 0x81, 0xe1, 0xf0, 0x60, 0x30, 0x18, 0x18, 0x0c, 0x06,
    0x03, 0x01, 0x81, 0x83, 0xc1, 0xc0,
    /* U+0067 "g" (9x13) */
    0x1d, 0x9f, 0xcc, 0xcc, 0x66, 0x33, 0x19, 0x9c, 0xfc, 0x36, 0x03, 0x03,
    0x9f, 0x87, 0x80,
    /* U+0068 "h" (8x12) */
    0x18, 0x18, 0x30, 0x37, 0x3f, 0x33, 0x73, 0x63, 0x63, 0x63, 0x63, 0xc6,
    /* U+0069 "i" (5x12) */
    0x18, 0x80, 0x63, 0x19, 0x8c, 0x63, 0x19, 0x80,
    /* U+006A "j" (7x16) */
    0x06, 0x08, 0x00, 0x60, 0xc1, 0x86, 0x0c, 0x18, 0x30, 0x61, 0x83, 0x06,
    0x3c, 0x70,
    /* U+006B "k" (9x12) */
    0x18, 0x0c, 0x0c, 0x06, 0x33, 0x31, 0xb1, 0xf0, 0xf8, 0x7c, 0x37, 0x19,
    0x98, 0xe0,
    /* U+006C "l" (5x12) */
    0x18, 0xcc, 0x63, 0x19, 0xcc, 0x63, 0x19, 0x80,
    /* U+006D "m" (13x9) */
    0x37, 0x39, 0xfb, 0xcc, 0xe6, 0xe7, 0x36, 0x31, 0xb1, 0x8d, 0x8c, 0x6c,
    0xe6, 0xc6, 0x30,
    /* U+006E "n" (8x9) */
    0x37, 0x3f, 0x33, 0x73, 0x63, 0x63, 0x63, 0x63, 0xc6,
    /* U+006F "o" (7x9) */
    0x3c, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xfe, 0x78,
    /* U+0070 "p" (8x13) */
    0x36, 0x3f, 0x33, 0x63, 0x63, 0x63, 0x67, 0x7e, 0xdc, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+0071 "q" (8x13) */
    0x3b, 0x7f, 0x66, 0xc6, 0xc6, 0xc6, 0xce, 0xfc, 0x6c, 0x0c, 0x0c, 0x0c,
    0x18,
    /* U+0072 "r" (7x9) */
    0x36, 0x7c, 0xe3, 0x86, 0x0c, 0x18, 0x30, 0xc0,
    /* U+0073 "s" (7x9) */
    0x3c, 0xfd, 0x83, 0x83, 0x81, 0x83, 0x7e, 0x78,
    /* U+0074 "t" (5x10) */
    0x23, 0xfe, 0xc6, 0x63, 0x18, 0xf3, 0x80,
    /* U+0075 "u" (8x9) */
    0x63, 0x63, 0x63, 0xc6, 0xc6, 0xc6, 0xce, 0xfe, 0x64,
    /* U+0076 "v" (7x9) */
    0xc7, 0x8f, 0x36, 0x6d, 0x9b, 0x1c, 0x38, 0x60,
    /* U+0077 "w" (12x9) */
    0xc6, 0x3c, 0xe6, 0xca, 0x6d, 0xa4, 0xd2, 0xcd, 0x2c, 0xf3, 0x8e, 0x38,
    0xe3, 0x00,
    /* U+0078 "x" (8x9) */
    0x73, 0x37, 0x3e, 0x1c, 0x18, 0x3c, 0x7c, 0xee, 0xc6,
    /* U+0079 "y" (10x13) */
    0x31, 0xcc, 0x63, 0x30, 0xcc, 0x32, 0x05, 0x81, 0xc0, 0x70, 0x18, 0x06,
    0x03, 0x03, 0xc0, 0xe0, 0x00,
    /* U+007A "z" (7x9) */
    0x3e, 0xfc, 0x30, 0xc1, 0x06, 0x18, 0x7e, 0xfc,
    /* U+007B "{" (6x14) */
    0x0c, 0x71, 0x84, 0x30, 0xce, 0x30, 0x61, 0x86, 0x18, 0x70, 0xc0,
    /* U+007C "|" (2x16) */
    0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (6x14) */
    0x18, 0xe1, 0x86, 0x18, 0x60, 0xc7, 0x38, 0xc3, 0x18, 0xe3, 0x00,
    /* U+007E "~" (8x3) */
    0x70, 0xff, 0x0e,
    /* U+00B0 "" (5x6) */
    0x77, 0xe7, 0x3f, 0xb8,
    /* U+00B1 "" (8x10) */
    0x10, 0x10, 0x10, 0xff, 0xfe, 0x10, 0x10, 0x10, 0xfe, 0xff,
    /* U+00B2 "" (5x7) */
    0x3b, 0xc2, 0x32, 0x3f, 0xe0,
    /* U+00B3 "" (5x7) */
    0x39, 0xce, 0x61, 0xff, 0xc0,
    /* U+00B5 "" (9x13) */
    0x31, 0x98, 0xcc, 0x6c, 0x66, 0x33, 0x19, 0x9c, 0xfe, 0xfa, 0x60, 0x30,
    0x18, 0x0c, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x7) */
    0x8f, 0x77, 0x9c, 0xfb, 0x38, 0x40,
    /* U+00F7 "" (8x8) */
    0x10, 0x10, 0x00, 0xfe, 0xff, 0x00, 0x10, 0x10,
    /* U+0394 "" (8x12) */
    0x06, 0x0e, 0x0f, 0x1b, 0x1b, 0x33, 0x33, 0x63, 0x63, 0xc3, 0xff, 0xff,
    /* U+03A9 "" (11x12) */
    0x0f, 0x83, 0xf8, 0xe3, 0x98, 0x37, 0x06, 0xc0, 0xd8, 0x1b, 0x06, 0x20,
    0xc6, 0x33, 0xcf, 0x79, 0xe0,
    /* U+03BC "" (9x13) */
    0x31, 0x98, 0xcc, 0x6c, 0x66, 0x33, 0x19, 0x9c, 0xfe, 0xfa, 0x60, 0x30,
    0x18, 0x0c, 0x00,
    /* U+2013 "" (7x2) */
    0x7f, 0xfc,
    /* U+2014 "" (14x2) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+2018 "" (3x4) */
    0x2d, 0xe0,
    /* U+2019 "" (3x4) */
    0x6f, 0x60,
    /* U+201C "" (7x4) */
    0x26, 0xd9, 0xb6, 0xc0,
    /* U+201D "" (7x4) */
    0x6e, 0xdb, 0x36, 0xc0,
    /* U+2022 "" (4x5) */
    0x6f, 0xff, 0x60,
    /* U+2026 "" (11x2) */
    0x46, 0x78, 0xcc,
    /* U+2030 "" (18x12) */
    0x30, 0x40, 0x1e, 0x30, 0x0d, 0x98, 0x03, 0x64, 0x00, 0xdb, 0x00, 0x37,
    0xb8, 0xef, 0x5f, 0x79, 0xb6, 0xdb, 0x19, 0x3c, 0x84, 0x4b, 0x62, 0x1e,
    0xf9, 0x87, 0x1c,
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
    {.bitmap_index = 0, .adv_w = 67, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 69, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 111, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 11, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 141, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 37, .adv_w = 215, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 177, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 62, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 71, .adv_w = 83, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 80, .adv_w = 83, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 140, .box_w = 7, .box_h = 7, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 98, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 106, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 108, .adv_w = 82, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 110, .adv_w = 69, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 102, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 141, .box_w = 5, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 69, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 69, .box_w = 5, .box_h = 10, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 247, .adv_w = 146, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 254, .adv_w = 146, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 259, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 267, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 215, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 296, .adv_w = 155, .box_w = 10, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 131, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 177, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 93, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 81, .box_w = 8, .box_h = 15, .ofs_x = -3, .ofs_y = -3},
    {.bitmap_index = 430, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 129, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 221, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 189, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 535, .adv_w = 153, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 132, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 173, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 598, .adv_w = 225, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 148, .box_w = 11, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 137, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 81, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 674, .adv_w = 102, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 81, .box_w = 6, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 691, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 698, .adv_w = 102, .box_w = 6, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 699, .adv_w = 79, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 700, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 91, .box_w = 9, .box_h = 16, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 766, .adv_w = 148, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 781, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 72, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 72, .box_w = 7, .box_h = 16, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 815, .adv_w = 139, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 73, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 228, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 852, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 148, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 882, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 895, .adv_w = 104, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 903, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 198, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 949, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 129, .box_w = 10, .box_h = 13, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 975, .adv_w = 116, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 87, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 994, .adv_w = 141, .box_w = 2, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 998, .adv_w = 87, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1009, .adv_w = 146, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1012, .adv_w = 105, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1016, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1031, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1036, .adv_w = 152, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1051, .adv_w = 73, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1052, .adv_w = 146, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1058, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1066, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 185, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1110, .adv_w = 123, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1112, .adv_w = 246, .box_w = 14, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1116, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1118, .adv_w = 51, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1120, .adv_w = 104, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1124, .adv_w = 104, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1128, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1131, .adv_w = 213, .box_w = 11, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1134, .adv_w = 308, .box_w = 18, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1161, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1168, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1175, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1182, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_noto_sans_italic_16 = {
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
    .fallback = &humid1_font_noto_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_NOTO_SANS_ITALIC_16 */
