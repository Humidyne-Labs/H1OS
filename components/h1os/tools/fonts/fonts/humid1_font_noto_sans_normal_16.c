/*******************************************************************************
 * Font: humid1_font_noto_sans_normal_16 (noto_sans normal)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#elif defined(__has_include)
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#ifndef HUMID1_FONT_NOTO_SANS_NORMAL_16
#define HUMID1_FONT_NOTO_SANS_NORMAL_16 1
#endif

#if HUMID1_FONT_NOTO_SANS_NORMAL_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xff, 0xf5, 0x0f,
    /* U+0022 "" (5x4) */
    0xde, 0xe5, 0x00,
    /* U+0023 "#" (10x12) */
    0x09, 0x82, 0x41, 0x90, 0x64, 0x7f, 0xc4, 0xc1, 0x23, 0xfe, 0x36, 0x0d,
    0x82, 0x60, 0x98,
    /* U+0024 "$" (7x13) */
    0x10, 0x71, 0xfc, 0x8d, 0x0e, 0x0f, 0x0b, 0x13, 0x2f, 0xf0, 0x81, 0x00,
    /* U+0025 "%" (11x12) */
    0x60, 0x9a, 0x32, 0x44, 0x49, 0x89, 0x21, 0x2d, 0x9d, 0x48, 0x49, 0x09,
    0x22, 0x24, 0x46, 0x90, 0x60,
    /* U+0026 "&" (10x12) */
    0x3c, 0x19, 0x04, 0x61, 0x90, 0x2c, 0x0e, 0x07, 0x8f, 0x32, 0x87, 0xa0,
    0xec, 0x79, 0xf3,
    /* U+0027 "'" (2x4) */
    0xfa,
    /* U+0028 "(" (3x14) */
    0x2d, 0x6d, 0x24, 0x93, 0x64, 0xc0,
    /* U+0029 ")" (3x14) */
    0x99, 0x36, 0x49, 0x25, 0xb5, 0x80,
    /* U+002A "" (7x7) */
    0x10, 0x22, 0x4f, 0xf3, 0x8d, 0x1b, 0x00,
    /* U+002B "+" (8x8) */
    0x10, 0x10, 0x10, 0xff, 0x18, 0x10, 0x10, 0x10,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x12) */
    0x0c, 0x30, 0x86, 0x10, 0xc3, 0x08, 0x61, 0x84, 0x30,
    /* U+0030 "0" (7x12) */
    0x38, 0xcb, 0x1e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x8d, 0x91, 0xc0,
    /* U+0031 "1" (4x12) */
    0x37, 0xfb, 0x33, 0x33, 0x33, 0x33,
    /* U+0032 "2" (8x12) */
    0x7c, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xff,
    /* U+0033 "3" (8x12) */
    0x7c, 0xc6, 0x06, 0x06, 0x06, 0x7c, 0x0e, 0x02, 0x03, 0x06, 0x8e, 0xfc,
    /* U+0034 "4" (9x12) */
    0x07, 0x03, 0x83, 0xc3, 0x61, 0x31, 0x99, 0x8c, 0x86, 0xff, 0x83, 0x80,
    0xc0, 0x60,
    /* U+0035 "5" (7x12) */
    0x7e, 0x83, 0x06, 0x0c, 0x1f, 0x81, 0x83, 0x02, 0x0c, 0x3f, 0xe0,
    /* U+0036 "6" (8x12) */
    0x3e, 0x70, 0x40, 0xc0, 0xfc, 0xe6, 0xc2, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0037 "7" (8x12) */
    0xff, 0x06, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x10, 0x30, 0x30, 0x60,
    /* U+0038 "8" (7x12) */
    0x3c, 0xff, 0xde, 0x34, 0xef, 0x9f, 0x63, 0xc3, 0x87, 0x99, 0xe0,
    /* U+0039 "9" (7x12) */
    0x39, 0xdb, 0x1e, 0x1c, 0x38, 0xdf, 0x81, 0x06, 0x1c, 0x73, 0xc0,
    /* U+003A ":" (2x9) */
    0xf0, 0x03, 0xc0,
    /* U+003B ";" (2x11) */
    0xf0, 0x03, 0xf8,
    /* U+003C "<" (7x7) */
    0x06, 0x39, 0x86, 0x07, 0x01, 0xc0, 0x80,
    /* U+003D "=" (8x4) */
    0xff, 0x00, 0x00, 0xff,
    /* U+003E ">" (7x7) */
    0xc0, 0x60, 0x30, 0x31, 0xde, 0x20, 0x00,
    /* U+003F "?" (6x12) */
    0xfa, 0x70, 0xc3, 0x1c, 0xe3, 0x18, 0x60, 0x06, 0x18,
    /* U+0040 "@" (12x13) */
    0x0f, 0x83, 0x8e, 0x60, 0x34, 0x79, 0xcd, 0x99, 0x89, 0x98, 0x99, 0x99,
    0x99, 0x9c, 0xee, 0x40, 0x03, 0x00, 0x1f, 0x80,
    /* U+0041 "A" (10x12) */
    0x0c, 0x03, 0x80, 0xe0, 0x68, 0x13, 0x0c, 0x43, 0x18, 0xfe, 0x61, 0x98,
    0x34, 0x0f, 0x01,
    /* U+0042 "B" (8x12) */
    0xfc, 0x86, 0x86, 0x86, 0x86, 0xfc, 0x86, 0x83, 0x83, 0x83, 0x86, 0xfc,
    /* U+0043 "C" (9x12) */
    0x1f, 0x18, 0xd8, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x30, 0x0c,
    0x03, 0xe0,
    /* U+0044 "D" (9x12) */
    0xfc, 0x43, 0x20, 0xd0, 0x28, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0x41, 0xa1,
    0x9f, 0x00,
    /* U+0045 "E" (7x12) */
    0xff, 0xc3, 0x06, 0x0c, 0x1f, 0xf8, 0x60, 0xc1, 0x83, 0x87, 0xf0,
    /* U+0046 "F" (7x12) */
    0xff, 0xc3, 0x06, 0x0c, 0x18, 0x3f, 0xf0, 0xc1, 0x83, 0x06, 0x00,
    /* U+0047 "G" (9x12) */
    0x0f, 0x98, 0x58, 0x08, 0x0c, 0x06, 0x03, 0x1f, 0x81, 0xc0, 0xb0, 0x4c,
    0x63, 0xf0,
    /* U+0048 "H" (10x12) */
    0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xff, 0xfe, 0x1f, 0x03, 0xc0, 0xf0,
    0x3c, 0x0f, 0x03,
    /* U+0049 "I" (4x12) */
    0xf6, 0x66, 0x66, 0x66, 0x66, 0x6f,
    /* U+004A "J" (4x15) */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,
    /* U+004B "K" (8x12) */
    0x83, 0x86, 0x8c, 0x98, 0xb0, 0xf0, 0xf0, 0x98, 0x8c, 0x8e, 0x86, 0x83,
    /* U+004C "L" (7x12) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xff, 0xf0,
    /* U+004D "M" (11x12) */
    0xc0, 0x78, 0x1f, 0x83, 0xf0, 0x7b, 0x1b, 0x62, 0x64, 0x4c, 0xd9, 0x9a,
    0x31, 0xc6, 0x38, 0xc6, 0x10,
    /* U+004E "N" (9x12) */
    0xc1, 0xe0, 0xf8, 0x76, 0x3b, 0x1c, 0xce, 0x37, 0x1b, 0x87, 0xc3, 0xe0,
    0xf0, 0x30,
    /* U+004F "O" (11x12) */
    0x1f, 0x0e, 0x31, 0x83, 0x60, 0x6c, 0x05, 0x80, 0xf0, 0x1e, 0x02, 0xc0,
    0xcc, 0x19, 0xc6, 0x0f, 0x80,
    /* U+0050 "P" (8x12) */
    0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (11x14) */
    0x1f, 0x06, 0x31, 0x83, 0x60, 0x2c, 0x07, 0x80, 0xf0, 0x1e, 0x03, 0xc0,
    0x4c, 0x18, 0xc6, 0x0f, 0x80, 0x30, 0x03, 0x00,
    /* U+0052 "R" (8x12) */
    0xf8, 0x8c, 0x86, 0x86, 0x86, 0x8c, 0xf8, 0x98, 0x8c, 0x84, 0x86, 0x83,
    /* U+0053 "S" (7x12) */
    0x3f, 0xcf, 0x06, 0x0e, 0x0f, 0x07, 0x83, 0x06, 0x0e, 0x1f, 0xc0,
    /* U+0054 "T" (9x12) */
    0xff, 0x8c, 0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+0055 "U" (9x12) */
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0x40, 0xb0, 0xdc,
    0xc3, 0xc0,
    /* U+0056 "V" (10x12) */
    0xc0, 0xd0, 0x26, 0x19, 0x86, 0x21, 0x0c, 0xc3, 0x30, 0x48, 0x1e, 0x07,
    0x80, 0xc0, 0x30,
    /* U+0057 "W" (15x12) */
    0xc1, 0x86, 0x87, 0x0d, 0x8e, 0x13, 0x1c, 0x66, 0x6c, 0xc4, 0xd9, 0x8d,
    0x92, 0x1a, 0x3c, 0x3c, 0x78, 0x38, 0xf0, 0x60, 0xc0, 0xc1, 0x80,
    /* U+0058 "X" (9x12) */
    0x61, 0xb0, 0xcc, 0xc6, 0x41, 0xe0, 0x60, 0x70, 0x3c, 0x33, 0x11, 0x98,
    0x78, 0x30,
    /* U+0059 "Y" (9x12) */
    0xc1, 0xb0, 0xd8, 0xc6, 0x63, 0x60, 0xf0, 0x70, 0x18, 0x0c, 0x06, 0x03,
    0x01, 0x80,
    /* U+005A "Z" (8x12) */
    0xff, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xff,
    /* U+005B "[" (4x14) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,
    /* U+005C "" (6x12) */
    0xc1, 0x06, 0x18, 0x20, 0xc3, 0x04, 0x18, 0x20, 0xc3,
    /* U+005D "]" (4x14) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (7x7) */
    0x10, 0x70, 0xa3, 0x24, 0x58, 0x60, 0x80,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0xc9, 0x80,
    /* U+0061 "a" (7x9) */
    0x7c, 0x9c, 0x18, 0x37, 0xf8, 0xf1, 0xe7, 0x72,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xde, 0xe7, 0xc3, 0xc3, 0xc1, 0xc3, 0xc3, 0xe7, 0xde,
    /* U+0063 "c" (6x9) */
    0x3d, 0x9c, 0x30, 0xc3, 0x0c, 0x18, 0x3c,
    /* U+0064 "d" (8x12) */
    0x03, 0x03, 0x03, 0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3b,
    /* U+0065 "e" (8x9) */
    0x3c, 0x66, 0xc2, 0xff, 0xc0, 0xc0, 0xc0, 0x62, 0x3e,
    /* U+0066 "f" (6x12) */
    0x1c, 0xc3, 0x3f, 0x30, 0x82, 0x08, 0x20, 0x82, 0x08,
    /* U+0067 "g" (8x13) */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3f, 0x03, 0x03, 0x46,
    0x7c,
    /* U+0068 "h" (8x12) */
    0xc0, 0xc0, 0xc0, 0xde, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+0069 "i" (2x12) */
    0xf3, 0xff, 0xff,
    /* U+006A "j" (4x16) */
    0x33, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,
    /* U+006B "k" (8x12) */
    0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf8, 0xf8, 0xd8, 0xcc, 0xc6, 0xc7,
    /* U+006C "l" (2x12) */
    0xff, 0xff, 0xff,
    /* U+006D "m" (13x9) */
    0xde, 0xf7, 0x3d, 0xf0, 0xc7, 0x86, 0x3c, 0x31, 0xe1, 0x8f, 0x0c, 0x78,
    0x63, 0xc3, 0x18,
    /* U+006E "n" (8x9) */
    0xde, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+006F "o" (8x9) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0070 "p" (8x13) */
    0xde, 0xe7, 0xc3, 0xc3, 0xc1, 0xc3, 0xc3, 0xe7, 0xfe, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+0071 "q" (8x13) */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3b, 0x03, 0x03, 0x03,
    0x03,
    /* U+0072 "r" (6x9) */
    0xdf, 0xce, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+0073 "s" (6x9) */
    0x7f, 0x1c, 0x38, 0x78, 0x30, 0x63, 0xf8,
    /* U+0074 "t" (6x11) */
    0x20, 0x8f, 0xd8, 0x61, 0x86, 0x18, 0x60, 0xc3, 0xc0,
    /* U+0075 "u" (8x9) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3f,
    /* U+0076 "v" (8x9) */
    0xc1, 0x43, 0x63, 0x66, 0x26, 0x34, 0x3c, 0x1c, 0x18,
    /* U+0077 "w" (13x9) */
    0xc7, 0x1a, 0x38, 0x99, 0xcc, 0xca, 0x66, 0xdb, 0x16, 0xd0, 0xe3, 0x87,
    0x1c, 0x38, 0xc0,
    /* U+0078 "x" (7x9) */
    0xc7, 0x89, 0xb1, 0xc3, 0x87, 0x1b, 0x63, 0xc6,
    /* U+0079 "y" (8x13) */
    0xc3, 0x43, 0x63, 0x66, 0x26, 0x36, 0x3c, 0x1c, 0x18, 0x18, 0x18, 0x30,
    0xe0,
    /* U+007A "z" (6x9) */
    0xfc, 0x31, 0x84, 0x31, 0x84, 0x30, 0xfc,
    /* U+007B "{" (6x14) */
    0x0c, 0x63, 0x0c, 0x30, 0xce, 0x0c, 0x30, 0xc3, 0x0c, 0x18, 0x70,
    /* U+007C "|" (1x16) */
    0xff, 0xff,
    /* U+007D "}" (6x14) */
    0xe0, 0xc3, 0x0c, 0x30, 0xe1, 0xc6, 0x30, 0xc3, 0x0c, 0x33, 0x80,
    /* U+007E "~" (7x2) */
    0xf1, 0x3c,
    /* U+00B0 "" (5x5) */
    0x76, 0xe3, 0x97, 0x00,
    /* U+00B1 "" (8x10) */
    0x10, 0x10, 0x10, 0xff, 0x18, 0x10, 0x10, 0x10, 0x00, 0xff,
    /* U+00B2 "" (5x7) */
    0x7a, 0x42, 0x33, 0x33, 0xe0,
    /* U+00B3 "" (4x7) */
    0xf1, 0x1f, 0x11, 0xf0,
    /* U+00B5 "" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0xff, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x6) */
    0xc2, 0xc8, 0xe1, 0xc3, 0xc8, 0xc0,
    /* U+00F7 "" (7x8) */
    0x10, 0x20, 0x00, 0x0f, 0xe0, 0x04, 0x08,
    /* U+0394 "" (9x12) */
    0x0c, 0x06, 0x07, 0x02, 0xc1, 0x21, 0x90, 0x8c, 0x46, 0x61, 0x20, 0xd8,
    0x7f, 0xf0,
    /* U+03A9 "" (11x12) */
    0x1f, 0x0e, 0x31, 0x83, 0x60, 0x2c, 0x07, 0x80, 0xf0, 0x1e, 0x02, 0x40,
    0xcc, 0x10, 0xc6, 0x79, 0xf0,
    /* U+03BC "" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0xff, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (16x1) */
    0xff, 0xff,
    /* U+2018 "" (3x4) */
    0x6d, 0x60,
    /* U+2019 "" (3x4) */
    0x6f, 0x60,
    /* U+201C "" (6x4) */
    0x65, 0x34, 0xb6,
    /* U+201D "" (6x4) */
    0x6d, 0xbd, 0xb6,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (11x2) */
    0xcc, 0x78, 0x8c,
    /* U+2030 "" (17x12) */
    0x60, 0x80, 0x68, 0xc0, 0x24, 0x40, 0x12, 0x60, 0x09, 0x20, 0x04, 0xb6,
    0x39, 0xd4, 0x96, 0x12, 0x59, 0x09, 0x2c, 0x88, 0x96, 0x44, 0x69, 0x64,
    0x18, 0xe0,
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
    {.bitmap_index = 0, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 110, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 151, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 33, .adv_w = 217, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 191, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 66, .adv_w = 80, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 72, .adv_w = 80, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 85, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 93, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 94, .adv_w = 82, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 95, .adv_w = 70, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 99, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 146, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 70, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 73, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 223, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 230, .adv_w = 146, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 234, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 241, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 230, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 270, .adv_w = 168, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 168, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 166, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 188, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 186, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 91, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 74, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 390, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 236, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 199, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 204, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 493, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 145, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 189, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 242, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 150, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 84, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 629, .adv_w = 99, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 84, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 645, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 652, .adv_w = 111, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 653, .adv_w = 76, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 655, .adv_w = 147, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 92, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 725, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 70, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 748, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 243, .box_w = 13, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 162, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 809, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 822, .adv_w = 109, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 99, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 162, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 134, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 205, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 136, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 899, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 906, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 917, .adv_w = 141, .box_w = 1, .box_h = 16, .ofs_x = 4, .ofs_y = -4},
    {.bitmap_index = 919, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 930, .adv_w = 146, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 932, .adv_w = 114, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 936, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 951, .adv_w = 94, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 955, .adv_w = 163, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 968, .adv_w = 69, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 969, .adv_w = 146, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 975, .adv_w = 146, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 982, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 996, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1026, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1027, .adv_w = 256, .box_w = 16, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1029, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1031, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1033, .adv_w = 99, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1036, .adv_w = 96, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1039, .adv_w = 100, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1041, .adv_w = 202, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 305, .box_w = 17, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1070, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1077, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1084, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1091, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_noto_sans_normal_16 = {
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
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_NOTO_SANS_NORMAL_16 */
