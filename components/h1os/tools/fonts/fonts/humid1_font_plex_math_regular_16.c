/*******************************************************************************
 * Font: humid1_font_plex_math_regular_16 (math regular)
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

#ifndef HUMID1_FONT_PLEX_MATH_REGULAR_16
#define HUMID1_FONT_PLEX_MATH_REGULAR_16 1
#endif

#if HUMID1_FONT_PLEX_MATH_REGULAR_16

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
    0xff, 0xd5, 0x0f,
    /* U+0022 "" (4x4) */
    0xd9, 0x99,
    /* U+0023 "#" (10x12) */
    0x09, 0x02, 0x40, 0x90, 0x64, 0x7f, 0xc4, 0xc1, 0x23, 0xfe, 0x32, 0x08,
    0x82, 0x60, 0x90,
    /* U+0024 "$" (7x13) */
    0x10, 0x71, 0xfc, 0x8d, 0x0e, 0x0f, 0x0b, 0x13, 0x2f, 0xf0, 0x81, 0x00,
    /* U+0025 "%" (11x12) */
    0x60, 0x9a, 0x32, 0x44, 0x49, 0x89, 0x21, 0x2d, 0x9d, 0x48, 0x49, 0x09,
    0x22, 0x24, 0x46, 0x90, 0x60,
    /* U+0026 "&" (10x12) */
    0x3c, 0x19, 0x04, 0x61, 0x90, 0x3c, 0x0e, 0x07, 0x8f, 0x32, 0x87, 0xa0,
    0xec, 0x79, 0xf3,
    /* U+0027 "'" (2x4) */
    0xea,
    /* U+0028 "(" (3x14) */
    0x29, 0x69, 0x24, 0x92, 0x64, 0xc0,
    /* U+0029 ")" (3x14) */
    0x99, 0x36, 0x49, 0x25, 0xa5, 0x00,
    /* U+002A "" (7x7) */
    0x10, 0x22, 0x4f, 0xf3, 0x8d, 0x1b, 0x00,
    /* U+002B "+" (8x8) */
    0x10, 0x10, 0x10, 0xff, 0x18, 0x10, 0x10, 0x10,
    /* U+002C "," (2x4) */
    0xfa,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x12) */
    0x0c, 0x21, 0x86, 0x10, 0xc3, 0x08, 0x61, 0x04, 0x30,
    /* U+0030 "0" (7x12) */
    0x38, 0xcb, 0x1c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x8d, 0x91, 0xc0,
    /* U+0031 "1" (4x12) */
    0x37, 0xb3, 0x33, 0x33, 0x33, 0x33,
    /* U+0032 "2" (7x12) */
    0x79, 0x98, 0x18, 0x30, 0x60, 0x83, 0x0c, 0x30, 0xc3, 0x07, 0xf0,
    /* U+0033 "3" (7x12) */
    0x7d, 0x9c, 0x18, 0x30, 0xcf, 0x03, 0x83, 0x02, 0x0e, 0x3f, 0xc0,
    /* U+0034 "4" (9x12) */
    0x06, 0x03, 0x03, 0x83, 0x41, 0x21, 0x11, 0x88, 0x84, 0xff, 0x81, 0x00,
    0x80, 0x40,
    /* U+0035 "5" (7x12) */
    0x7c, 0x81, 0x06, 0x0c, 0x1f, 0x01, 0x81, 0x02, 0x06, 0x3f, 0xc0,
    /* U+0036 "6" (7x12) */
    0x1c, 0xe1, 0x06, 0x0b, 0xdc, 0xf0, 0xc1, 0x83, 0x85, 0x99, 0xe0,
    /* U+0037 "7" (7x12) */
    0xfe, 0x04, 0x18, 0x20, 0xc1, 0x02, 0x0c, 0x10, 0x60, 0x83, 0x00,
    /* U+0038 "8" (7x12) */
    0x3c, 0x8f, 0x0e, 0x36, 0x47, 0x1b, 0x63, 0x83, 0x07, 0x1b, 0xe0,
    /* U+0039 "9" (7x12) */
    0x39, 0x8a, 0x0c, 0x18, 0x38, 0xde, 0x81, 0x06, 0x08, 0x33, 0x80,
    /* U+003A ":" (2x9) */
    0xf0, 0x03, 0xc0,
    /* U+003B ";" (2x11) */
    0xf0, 0x03, 0xe8,
    /* U+003C "<" (7x7) */
    0x06, 0x31, 0x86, 0x07, 0x01, 0x80, 0x80,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (7x7) */
    0xc0, 0x60, 0x30, 0x31, 0xce, 0x20, 0x00,
    /* U+003F "?" (5x12) */
    0xf4, 0xc2, 0x11, 0x98, 0x88, 0x00, 0x18, 0xc0,
    /* U+0040 "@" (12x13) */
    0x0f, 0x83, 0x8e, 0x60, 0x24, 0x79, 0xcd, 0x99, 0x89, 0x90, 0x99, 0x19,
    0x99, 0x9c, 0xee, 0x40, 0x07, 0x00, 0x1f, 0x80,
    /* U+0041 "A" (10x12) */
    0x0c, 0x03, 0x00, 0xe0, 0x68, 0x12, 0x0c, 0xc3, 0x10, 0xfe, 0x61, 0x90,
    0x24, 0x0f, 0x01,
    /* U+0042 "B" (7x12) */
    0xfd, 0x0e, 0x0c, 0x18, 0x7f, 0xa1, 0xc1, 0x83, 0x06, 0x1f, 0xe0,
    /* U+0043 "C" (8x12) */
    0x1f, 0x31, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x71, 0x1f,
    /* U+0044 "D" (9x12) */
    0xf8, 0x43, 0x20, 0xd0, 0x28, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0x41, 0xa1,
    0x9f, 0x00,
    /* U+0045 "E" (7x12) */
    0xff, 0x83, 0x06, 0x0c, 0x1f, 0xf0, 0x60, 0xc1, 0x83, 0x07, 0xf0,
    /* U+0046 "F" (7x12) */
    0xff, 0x83, 0x06, 0x0c, 0x18, 0x3f, 0xe0, 0xc1, 0x83, 0x06, 0x00,
    /* U+0047 "G" (9x12) */
    0x1f, 0x98, 0x58, 0x18, 0x0c, 0x04, 0x03, 0x0f, 0x81, 0xc0, 0xb0, 0x4c,
    0x23, 0xf0,
    /* U+0048 "H" (10x12) */
    0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xff, 0xfc, 0x1f, 0x03, 0xc0, 0xf0,
    0x3c, 0x0f, 0x03,
    /* U+0049 "I" (5x12) */
    0xf9, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8d, 0xf0,
    /* U+004A "J" (4x15) */
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x33, 0xe0,
    /* U+004B "K" (8x12) */
    0x82, 0x84, 0x8c, 0x98, 0xb0, 0xe0, 0xf0, 0x98, 0x88, 0x8c, 0x86, 0x83,
    /* U+004C "L" (7x12) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0xf0,
    /* U+004D "M" (11x12) */
    0xc0, 0x78, 0x1f, 0x83, 0xd0, 0x5a, 0x13, 0x62, 0x64, 0x4c, 0x91, 0x9a,
    0x31, 0xc6, 0x30, 0xc6, 0x10,
    /* U+004E "N" (9x12) */
    0xc1, 0xe0, 0xf8, 0x74, 0x3b, 0x1c, 0xce, 0x27, 0x1b, 0x87, 0xc3, 0xe0,
    0xf0, 0x30,
    /* U+004F "O" (10x12) */
    0x1f, 0x1c, 0x64, 0x0f, 0x01, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xc0, 0x50,
    0x37, 0x18, 0x7c,
    /* U+0050 "P" (7x12) */
    0xf9, 0x1a, 0x1c, 0x38, 0x71, 0xbe, 0x40, 0x81, 0x02, 0x04, 0x00,
    /* U+0051 "Q" (10x14) */
    0x1f, 0x1c, 0x64, 0x0f, 0x01, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xc0, 0x50,
    0x37, 0x18, 0x7c, 0x03, 0x00, 0x60,
    /* U+0052 "R" (7x12) */
    0xf9, 0x1a, 0x1c, 0x38, 0x71, 0xbe, 0x4c, 0x8d, 0x0a, 0x1c, 0x10,
    /* U+0053 "S" (7x12) */
    0x3d, 0x8a, 0x06, 0x0c, 0x0e, 0x07, 0x03, 0x02, 0x0e, 0x17, 0xc0,
    /* U+0054 "T" (9x12) */
    0xff, 0x84, 0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+0055 "U" (9x12) */
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0xc0, 0xa0, 0xdc,
    0xc7, 0xc0,
    /* U+0056 "V" (9x12) */
    0xc0, 0xa0, 0x50, 0x6c, 0x22, 0x11, 0x18, 0xc8, 0x24, 0x16, 0x0e, 0x03,
    0x01, 0x80,
    /* U+0057 "W" (15x12) */
    0xc3, 0x06, 0x87, 0x09, 0x0e, 0x13, 0x14, 0x66, 0x68, 0xc4, 0x99, 0x09,
    0x12, 0x1a, 0x2c, 0x3c, 0x78, 0x30, 0xe0, 0x60, 0xc0, 0xc1, 0x80,
    /* U+0058 "X" (9x12) */
    0x41, 0xb0, 0x88, 0xc6, 0xc1, 0xc0, 0x60, 0x70, 0x2c, 0x32, 0x11, 0x90,
    0x58, 0x30,
    /* U+0059 "Y" (9x12) */
    0xc1, 0xa0, 0x98, 0xc4, 0x43, 0x60, 0xe0, 0x70, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+005A "Z" (8x12) */
    0xfe, 0x06, 0x04, 0x0c, 0x08, 0x18, 0x30, 0x20, 0x60, 0x40, 0xc0, 0xff,
    /* U+005B "[" (4x14) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,
    /* U+005C "" (6x12) */
    0xc1, 0x04, 0x18, 0x20, 0xc3, 0x04, 0x18, 0x60, 0x83,
    /* U+005D "]" (4x14) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (7x7) */
    0x10, 0x70, 0xa2, 0x24, 0x58, 0x60, 0x80,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0x99, 0x80,
    /* U+0061 "a" (7x9) */
    0x7c, 0x98, 0x18, 0x37, 0xf8, 0xe1, 0xe7, 0x72,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0x9c,
    /* U+0063 "c" (6x9) */
    0x3d, 0x8c, 0x20, 0x82, 0x0c, 0x19, 0x3c,
    /* U+0064 "d" (7x12) */
    0x02, 0x04, 0x09, 0xd6, 0x78, 0x60, 0xc1, 0x83, 0x85, 0x99, 0xd0,
    /* U+0065 "e" (7x9) */
    0x38, 0xcb, 0x1c, 0x1f, 0xf8, 0x30, 0x30, 0x3e,
    /* U+0066 "f" (5x12) */
    0x3b, 0x11, 0xe4, 0x21, 0x08, 0x42, 0x10, 0x80,
    /* U+0067 "g" (7x13) */
    0x3a, 0xcf, 0x0c, 0x18, 0x30, 0x70, 0xb3, 0x3a, 0x04, 0x0a, 0x37, 0xc0,
    /* U+0068 "h" (8x12) */
    0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+0069 "i" (2x12) */
    0x43, 0xff, 0xff,
    /* U+006A "j" (4x16) */
    0x31, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,
    /* U+006B "k" (7x12) */
    0xc1, 0x83, 0x06, 0x3c, 0xdb, 0x3c, 0x78, 0xd9, 0x9b, 0x16, 0x30,
    /* U+006C "l" (2x12) */
    0xff, 0xff, 0xff,
    /* U+006D "m" (13x9) */
    0xdc, 0xf7, 0x39, 0xb0, 0xc7, 0x84, 0x3c, 0x21, 0xe1, 0x0f, 0x08, 0x78,
    0x43, 0xc2, 0x18,
    /* U+006E "n" (8x9) */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+006F "o" (8x9) */
    0x3c, 0x66, 0xc2, 0x83, 0x83, 0x83, 0xc2, 0x66, 0x3c,
    /* U+0070 "p" (8x13) */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0xdc, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+0071 "q" (7x13) */
    0x3a, 0xcf, 0x0c, 0x18, 0x30, 0x70, 0xb3, 0x3a, 0x04, 0x08, 0x10, 0x20,
    /* U+0072 "r" (5x9) */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,
    /* U+0073 "s" (6x9) */
    0x7b, 0x28, 0x30, 0x38, 0x30, 0x63, 0xf8,
    /* U+0074 "t" (4x11) */
    0x44, 0xfc, 0x44, 0x44, 0x44, 0x30,
    /* U+0075 "u" (8x9) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x3b,
    /* U+0076 "v" (8x9) */
    0xc3, 0x43, 0x42, 0x66, 0x24, 0x24, 0x3c, 0x18, 0x18,
    /* U+0077 "w" (12x9) */
    0xc6, 0x14, 0x71, 0x47, 0x34, 0xd2, 0x69, 0x22, 0x9a, 0x38, 0xe3, 0x8c,
    0x30, 0xc0,
    /* U+0078 "x" (7x9) */
    0x87, 0x99, 0xa1, 0xc3, 0x07, 0x1a, 0x62, 0x86,
    /* U+0079 "y" (8x13) */
    0xc3, 0x43, 0x42, 0x66, 0x26, 0x34, 0x3c, 0x18, 0x18, 0x18, 0x10, 0x30,
    0xe0,
    /* U+007A "z" (6x9) */
    0xfc, 0x31, 0x84, 0x31, 0x84, 0x30, 0xfc,
    /* U+007B "{" (6x14) */
    0x0c, 0x63, 0x0c, 0x30, 0xc3, 0x38, 0x30, 0xc3, 0x0c, 0x30, 0x70,
    /* U+007C "|" (1x17) */
    0xff, 0xff, 0x80,
    /* U+007D "}" (5x14) */
    0x82, 0x18, 0xc6, 0x30, 0x87, 0x23, 0x18, 0xc6, 0x60,
    /* U+007E "~" (7x2) */
    0xf1, 0x3c,
    /* U+00B0 "" (5x5) */
    0x76, 0xe3, 0x97, 0x00,
    /* U+00B1 "" (8x10) */
    0x10, 0x10, 0x10, 0x10, 0xff, 0x18, 0x10, 0x10, 0x00, 0xff,
    /* U+00B2 "" (5x7) */
    0x7a, 0x42, 0x33, 0x33, 0xe0,
    /* U+00B3 "" (4x7) */
    0xf1, 0x1f, 0x11, 0xf0,
    /* U+00B5 "" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0xfb, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x7) */
    0x82, 0x88, 0xe0, 0xc2, 0x88, 0x80, 0x80,
    /* U+00F7 "" (7x8) */
    0x10, 0x20, 0x00, 0x0f, 0xe0, 0x04, 0x08,
    /* U+0394 "" (9x12) */
    0x08, 0x0e, 0x07, 0x02, 0x83, 0x61, 0x90, 0x88, 0x46, 0x61, 0x20, 0x90,
    0x7f, 0xf0,
    /* U+03A9 "" (11x12) */
    0x1f, 0x0e, 0x31, 0x03, 0x60, 0x2c, 0x05, 0x80, 0xb0, 0x16, 0x02, 0x40,
    0xcc, 0x10, 0xc6, 0x79, 0xf0,
    /* U+03BC "" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0xfb, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+2126 "" (11x12) */
    0x1f, 0x0e, 0x31, 0x03, 0x60, 0x2c, 0x05, 0x80, 0xb0, 0x16, 0x02, 0x40,
    0xcc, 0x10, 0xc6, 0x79, 0xf0,
    /* U+2200 "" (10x12) */
    0x80, 0x70, 0x34, 0x09, 0x86, 0x7f, 0x8c, 0xc3, 0x30, 0x48, 0x12, 0x07,
    0x80, 0xc0, 0x30,
    /* U+2202 "" (7x12) */
    0x3c, 0x4c, 0x08, 0x13, 0xac, 0xf0, 0xe1, 0x87, 0x0b, 0x33, 0xc0,
    /* U+2203 "" (7x11) */
    0xfe, 0x04, 0x08, 0x10, 0x3f, 0xc0, 0x81, 0x02, 0x07, 0xf8,
    /* U+2205 "" (12x12) */
    0x1f, 0x23, 0x1e, 0x60, 0xcc, 0x1a, 0x81, 0x28, 0x23, 0x84, 0x38, 0x82,
    0xd0, 0x26, 0x06, 0x70, 0xc9, 0xf0,
    /* U+2206 "" (9x11) */
    0x0c, 0x0e, 0x05, 0x02, 0xc3, 0x21, 0x10, 0x8c, 0xc2, 0x41, 0x20, 0xff,
    0xe0,
    /* U+2207 "" (9x11) */
    0xff, 0xa0, 0xd0, 0x4c, 0x22, 0x31, 0x10, 0xc8, 0x2c, 0x14, 0x0e, 0x03,
    0x00,
    /* U+2208 "" (9x9) */
    0x3f, 0xb0, 0x30, 0x10, 0x0f, 0xfc, 0x03, 0x00, 0xc0, 0x3f, 0x80,
    /* U+2209 "" (9x13) */
    0x01, 0x00, 0x8f, 0xec, 0x4c, 0x24, 0x33, 0xff, 0x18, 0x88, 0x34, 0x0f,
    0xe2, 0x01, 0x00,
    /* U+220F "" (9x15) */
    0xff, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0xc0, 0xe0,
    0x70, 0x38, 0x1c, 0x0e, 0x06,
    /* U+2211 "" (9x15) */
    0xff, 0xe0, 0x18, 0x06, 0x01, 0x00, 0xc0, 0x30, 0x18, 0x0c, 0x0c, 0x0c,
    0x06, 0x06, 0x06, 0x03, 0xfe,
    /* U+2212 "" (8x1) */
    0xff,
    /* U+221A "" (9x13) */
    0x00, 0x80, 0xc0, 0x40, 0x20, 0x20, 0x13, 0x08, 0xc8, 0x24, 0x12, 0x0e,
    0x03, 0x01, 0x80,
    /* U+221D "" (7x5) */
    0x63, 0x3a, 0x24, 0xe7, 0x60,
    /* U+221E "" (10x6) */
    0x73, 0xb7, 0xb8, 0xc6, 0x31, 0x9c, 0xdc, 0xe0,
    /* U+2227 "" (9x9) */
    0x0c, 0x0e, 0x05, 0x86, 0x42, 0x23, 0x09, 0x04, 0x81, 0x80, 0x80,
    /* U+2228 "" (9x9) */
    0xc0, 0xa0, 0xd8, 0x44, 0x62, 0x20, 0x90, 0x50, 0x18, 0x08, 0x00,
    /* U+2229 "" (9x11) */
    0x3e, 0x31, 0xb0, 0x70, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60,
    0x20,
    /* U+222A "" (9x10) */
    0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x83, 0x63, 0x1f, 0x00,
    /* U+222B "" (6x18) */
    0x1c, 0x43, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c,
    0x33, 0x80,
    /* U+2248 "" (7x5) */
    0xf1, 0x3c, 0x07, 0x89, 0xe0,
    /* U+2260 "" (7x8) */
    0x0c, 0x13, 0xf8, 0xc1, 0x1f, 0xc8, 0x10,
    /* U+2261 "" (8x7) */
    0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff,
    /* U+2264 "" (7x9) */
    0x06, 0x31, 0x86, 0x03, 0x01, 0x80, 0x80, 0xfe,
    /* U+2265 "" (7x9) */
    0xc0, 0x60, 0x38, 0x31, 0xce, 0x20, 0x00, 0xfe,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 104, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 146, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 32, .adv_w = 213, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 187, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 65, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 84, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 92, .adv_w = 69, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 93, .adv_w = 82, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 94, .adv_w = 69, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 95, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 146, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 69, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 69, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 218, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 225, .adv_w = 146, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 229, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 236, .adv_w = 111, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 230, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 264, .adv_w = 164, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 166, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 133, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 186, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 190, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 70, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 383, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 232, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 195, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 200, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 155, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 200, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 481, .adv_w = 159, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 238, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 150, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 84, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 615, .adv_w = 95, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 84, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 631, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 638, .adv_w = 114, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 639, .adv_w = 72, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 641, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 157, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 157, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 88, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 157, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 707, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 66, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 730, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 239, .box_w = 13, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 157, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 790, .adv_w = 157, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 802, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 92, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 201, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 861, .adv_w = 131, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 874, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 97, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 892, .adv_w = 111, .box_w = 1, .box_h = 17, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 895, .adv_w = 97, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 904, .adv_w = 146, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 906, .adv_w = 114, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 910, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 925, .adv_w = 94, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 929, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 942, .adv_w = 69, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 943, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 950, .adv_w = 146, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 957, .adv_w = 149, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 988, .adv_w = 159, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1001, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 192, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1033, .adv_w = 149, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 147, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 215, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1072, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1085, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 179, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1109, .adv_w = 179, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1124, .adv_w = 166, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1141, .adv_w = 173, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1158, .adv_w = 146, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1159, .adv_w = 155, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 138, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1179, .adv_w = 189, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1187, .adv_w = 183, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1198, .adv_w = 183, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1209, .adv_w = 175, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1222, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1234, .adv_w = 99, .box_w = 6, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1248, .adv_w = 146, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1253, .adv_w = 146, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1260, .adv_w = 146, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1267, .adv_w = 146, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1275, .adv_w = 146, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x2076, 0x2150, 0x2152, 0x2153, 0x2155, 0x2156, 0x2157, 0x2158, 0x2159,
    0x215f, 0x2161, 0x2162, 0x216a, 0x216d, 0x216e, 0x2177, 0x2178, 0x2179, 0x217a,
    0x217b, 0x2198, 0x21b0, 0x21b1, 0x21b4, 0x21b5,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8630, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 36, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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

const lv_font_t humid1_font_plex_math_regular_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 25,
    .base_line = 7,
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

#endif /* #if HUMID1_FONT_PLEX_MATH_REGULAR_16 */
