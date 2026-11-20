/*******************************************************************************
 * Font: humid1_font_plex_serif_normal_16 (serif normal)
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

#ifndef HUMID1_FONT_PLEX_SERIF_NORMAL_16
#define HUMID1_FONT_PLEX_SERIF_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_SERIF_NORMAL_16

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
    0xff, 0xea, 0x0f,
    /* U+0022 "" (5x4) */
    0xde, 0xe7, 0x00,
    /* U+0023 "#" (7x12) */
    0x24, 0x48, 0x97, 0xf2, 0x48, 0x92, 0x24, 0xfe, 0x91, 0x24, 0x00,
    /* U+0024 "$" (7x14) */
    0x10, 0x79, 0x5e, 0xad, 0x0e, 0x0f, 0x0f, 0x17, 0x2f, 0x53, 0xc1, 0x02,
    0x00,
    /* U+0025 "%" (13x12) */
    0x70, 0x86, 0xc4, 0x26, 0x41, 0x12, 0x09, 0xb0, 0x6d, 0x39, 0xda, 0x40,
    0xb3, 0x0d, 0x98, 0x4c, 0xc2, 0x24, 0x20, 0xe0,
    /* U+0026 "&" (11x12) */
    0x3c, 0x0c, 0xc1, 0x18, 0x33, 0x03, 0xc0, 0x63, 0xb6, 0x64, 0x68, 0x87,
    0x10, 0x63, 0x1e, 0x3c, 0x70,
    /* U+0027 "'" (2x4) */
    0xfe,
    /* U+0028 "(" (4x14) */
    0x12, 0x6c, 0xcc, 0xcc, 0xcc, 0xc6, 0x21,
    /* U+0029 ")" (4x14) */
    0x84, 0x63, 0x33, 0x33, 0x33, 0x26, 0xc8,
    /* U+002A "" (6x6) */
    0x32, 0xdf, 0xff, 0xb4, 0xc0,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00,
    /* U+002C "," (2x4) */
    0xf7,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x15) */
    0x18, 0x84, 0x23, 0x10, 0x84, 0x62, 0x10, 0x8c, 0x42, 0x00,
    /* U+0030 "0" (7x12) */
    0x38, 0x8b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x8d, 0x11, 0xc0,
    /* U+0031 "1" (7x12) */
    0x18, 0xf3, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x63, 0xf0,
    /* U+0032 "2" (7x12) */
    0x79, 0x8b, 0x18, 0x30, 0x41, 0x86, 0x08, 0x20, 0xc7, 0x1f, 0xf0,
    /* U+0033 "3" (7x12) */
    0x7d, 0x8f, 0x18, 0x30, 0xc7, 0x03, 0x83, 0x07, 0x0f, 0x1b, 0xc0,
    /* U+0034 "4" (9x12) */
    0x06, 0x07, 0x03, 0x82, 0xc1, 0x61, 0x31, 0x98, 0x8c, 0xff, 0x83, 0x01,
    0x81, 0xf0,
    /* U+0035 "5" (7x12) */
    0x7e, 0x8d, 0x02, 0x0c, 0x1f, 0x03, 0x83, 0x06, 0x0f, 0x33, 0xc0,
    /* U+0036 "6" (7x12) */
    0x3c, 0xcd, 0x8e, 0x0c, 0x1f, 0xb1, 0xe3, 0xc2, 0x8d, 0x99, 0xe0,
    /* U+0037 "7" (7x12) */
    0xff, 0x0e, 0x18, 0x20, 0xc1, 0x82, 0x0c, 0x10, 0x20, 0xc1, 0x00,
    /* U+0038 "8" (7x12) */
    0x38, 0x8b, 0x1e, 0x36, 0x47, 0x1f, 0x63, 0x83, 0x07, 0x1b, 0xc0,
    /* U+0039 "9" (7x12) */
    0x39, 0x8b, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x06, 0x0f, 0x33, 0xc0,
    /* U+003A ":" (2x9) */
    0x70, 0x03, 0x40,
    /* U+003B ";" (3x11) */
    0xfc, 0x00, 0x07, 0xef, 0x00,
    /* U+003C "<" (7x7) */
    0x06, 0x31, 0x86, 0x03, 0x01, 0x81, 0x80,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (7x7) */
    0xc0, 0x60, 0x30, 0x31, 0x8c, 0x20, 0x00,
    /* U+003F "?" (6x12) */
    0xfb, 0x38, 0xc3, 0x0c, 0x63, 0x08, 0x20, 0x03, 0x0c,
    /* U+0040 "@" (13x14) */
    0x07, 0xc0, 0xc1, 0x8c, 0x04, 0xc7, 0x94, 0xcc, 0xe6, 0x67, 0x63, 0x3b,
    0x11, 0xd8, 0x9e, 0x4c, 0xb3, 0x98, 0xc0, 0x03, 0x06, 0x07, 0xc0,
    /* U+0041 "A" (12x12) */
    0x06, 0x00, 0x60, 0x0f, 0x00, 0xb0, 0x1b, 0x01, 0x18, 0x11, 0x83, 0xf8,
    0x20, 0xc2, 0x0c, 0x60, 0xcf, 0x1f,
    /* U+0042 "B" (9x12) */
    0xfe, 0x31, 0x98, 0xcc, 0x66, 0x33, 0xf1, 0x8c, 0xc3, 0x61, 0xb0, 0xd8,
    0xdf, 0xc0,
    /* U+0043 "C" (9x12) */
    0x1f, 0x31, 0xd8, 0x58, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x30, 0x18,
    0x63, 0xe0,
    /* U+0044 "D" (10x12) */
    0xfe, 0x18, 0xc6, 0x19, 0x83, 0x60, 0xd8, 0x36, 0x0d, 0x83, 0x60, 0xd8,
    0x66, 0x33, 0xf8,
    /* U+0045 "E" (9x12) */
    0xff, 0x30, 0x98, 0x4c, 0x06, 0x03, 0xf1, 0x80, 0xc0, 0x60, 0x30, 0x58,
    0x7f, 0xe0,
    /* U+0046 "F" (8x12) */
    0xff, 0x61, 0x61, 0x60, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x60, 0xf8,
    /* U+0047 "G" (10x12) */
    0x1f, 0x0c, 0x66, 0x0b, 0x00, 0xc0, 0x30, 0x0c, 0x3f, 0x06, 0xc1, 0x98,
    0x63, 0x18, 0x7e,
    /* U+0048 "H" (11x12) */
    0xf3, 0xec, 0x19, 0x83, 0x30, 0x66, 0x0c, 0xff, 0x98, 0x33, 0x06, 0x60,
    0xcc, 0x19, 0x83, 0x79, 0xf0,
    /* U+0049 "I" (4x12) */
    0xf6, 0x66, 0x66, 0x66, 0x66, 0x6f,
    /* U+004A "J" (6x16) */
    0x7c, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc2, 0x30,
    /* U+004B "K" (11x12) */
    0xfb, 0xcc, 0x31, 0x8c, 0x33, 0x06, 0x40, 0xd8, 0x1f, 0x83, 0x30, 0x63,
    0x0c, 0x71, 0x86, 0x7c, 0x70,
    /* U+004C "L" (9x12) */
    0xf8, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0xd8,
    0x7f, 0xf0,
    /* U+004D "M" (13x12) */
    0xf0, 0x3b, 0x83, 0x9c, 0x1c, 0xb0, 0xe5, 0x8b, 0x24, 0x59, 0x32, 0xc9,
    0xa6, 0x47, 0x32, 0x39, 0x91, 0x8d, 0xc4, 0xf0,
    /* U+004E "N" (11x12) */
    0xe1, 0xee, 0x19, 0xc3, 0x2c, 0x65, 0xcc, 0x99, 0x91, 0xb2, 0x3e, 0x43,
    0xc8, 0x39, 0x07, 0x78, 0x60,
    /* U+004F "O" (10x12) */
    0x1e, 0x18, 0x66, 0x0b, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xd8,
    0x26, 0x18, 0x78,
    /* U+0050 "P" (8x12) */
    0xfe, 0x63, 0x63, 0x63, 0x63, 0x63, 0x66, 0x7c, 0x60, 0x60, 0x60, 0xf8,
    /* U+0051 "Q" (10x16) */
    0x1e, 0x18, 0x66, 0x0b, 0x03, 0xc0, 0xf0, 0x3c, 0x0f, 0x03, 0xc0, 0xd0,
    0x36, 0x18, 0xfc, 0x0e, 0x01, 0x80, 0x60, 0x0e,
    /* U+0052 "R" (10x12) */
    0xfe, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0x87, 0xc1, 0xb8, 0x66, 0x18,
    0xc6, 0x3b, 0xe7,
    /* U+0053 "S" (7x12) */
    0x3d, 0x8f, 0x16, 0x0e, 0x0f, 0x07, 0x07, 0x07, 0x0f, 0x1b, 0xc0,
    /* U+0054 "T" (10x12) */
    0xff, 0xf3, 0x38, 0xc4, 0x30, 0x0c, 0x03, 0x00, 0xc0, 0x30, 0x0c, 0x03,
    0x00, 0xc0, 0xfc,
    /* U+0055 "U" (11x12) */
    0xf9, 0xe6, 0x08, 0xc1, 0x18, 0x23, 0x04, 0x60, 0x8c, 0x11, 0x82, 0x30,
    0x46, 0x08, 0xc2, 0x07, 0x80,
    /* U+0056 "V" (11x12) */
    0xf9, 0xee, 0x18, 0xc2, 0x18, 0x43, 0x18, 0x32, 0x06, 0x40, 0xd8, 0x0e,
    0x01, 0xc0, 0x38, 0x02, 0x00,
    /* U+0057 "W" (17x12) */
    0xf8, 0xc7, 0xb8, 0x61, 0x8c, 0x70, 0x86, 0x3c, 0x43, 0x16, 0x60, 0xcb,
    0x30, 0x6d, 0x90, 0x34, 0x68, 0x1e, 0x3c, 0x07, 0x1c, 0x03, 0x86, 0x01,
    0x83, 0x00,
    /* U+0058 "X" (11x12) */
    0xf9, 0xc6, 0x30, 0xe4, 0x0d, 0x80, 0xe0, 0x1c, 0x03, 0x80, 0x78, 0x13,
    0x06, 0x30, 0x86, 0x79, 0xf0,
    /* U+0059 "Y" (10x12) */
    0xfb, 0xd8, 0x23, 0x08, 0xc4, 0x19, 0x06, 0x80, 0xe0, 0x30, 0x0c, 0x03,
    0x00, 0xc0, 0x7c,
    /* U+005A "Z" (8x12) */
    0xff, 0x86, 0x86, 0x0c, 0x1c, 0x18, 0x38, 0x30, 0x60, 0x61, 0xc1, 0xff,
    /* U+005B "[" (3x15) */
    0xfa, 0x49, 0x24, 0x92, 0x49, 0xb8,
    /* U+005C "" (4x14) */
    0x88, 0x44, 0x44, 0x22, 0x22, 0x11, 0x11,
    /* U+005D "]" (3x15) */
    0xe4, 0x92, 0x49, 0x24, 0x92, 0xf8,
    /* U+005E "^" (7x7) */
    0x10, 0x70, 0xa3, 0x64, 0x58, 0xe0, 0x80,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0xc8, 0x80,
    /* U+0061 "a" (8x9) */
    0x7c, 0xec, 0x46, 0x06, 0x7e, 0xc6, 0xc6, 0xce, 0x77,
    /* U+0062 "b" (9x13) */
    0xf0, 0x18, 0x0c, 0x06, 0x03, 0xf1, 0x8c, 0xc6, 0x63, 0x31, 0x98, 0xcc,
    0x66, 0x3e, 0xf0,
    /* U+0063 "c" (7x9) */
    0x3c, 0x8f, 0x16, 0x0c, 0x18, 0x30, 0x30, 0x3c,
    /* U+0064 "d" (9x13) */
    0x0e, 0x01, 0x00, 0x80, 0x43, 0xe2, 0x33, 0x09, 0x84, 0xc2, 0x61, 0x30,
    0x88, 0xc3, 0xb8,
    /* U+0065 "e" (7x9) */
    0x38, 0x8b, 0x1e, 0x3f, 0xf8, 0x30, 0x31, 0x3c,
    /* U+0066 "f" (7x13) */
    0x1e, 0x64, 0xc1, 0x87, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x8f, 0xc0,
    /* U+0067 "g" (8x13) */
    0x3f, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x20, 0x60, 0x3e, 0x43, 0xc3, 0x43,
    0x7e,
    /* U+0068 "h" (10x13) */
    0xf0, 0x0c, 0x03, 0x00, 0xc0, 0x3f, 0x0c, 0xc3, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x18, 0xc6, 0xf9, 0xc0,
    /* U+0069 "i" (5x13) */
    0x31, 0x80, 0x07, 0x18, 0xc6, 0x31, 0x8c, 0x6f, 0x80,
    /* U+006A "j" (4x17) */
    0x23, 0x00, 0xf3, 0x33, 0x33, 0x33, 0x33, 0x26, 0xc0,
    /* U+006B "k" (10x13) */
    0xf0, 0x0c, 0x03, 0x00, 0xc0, 0x37, 0x8c, 0xc3, 0x60, 0xf0, 0x3c, 0x0d,
    0x83, 0x70, 0xcc, 0xf9, 0xc0,
    /* U+006C "l" (5x13) */
    0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x6f, 0x80,
    /* U+006D "m" (15x9) */
    0x7f, 0x78, 0x63, 0x30, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x18, 0xc6, 0xf9, 0xce,
    /* U+006E "n" (9x9) */
    0xfe, 0x31, 0x98, 0xcc, 0x66, 0x33, 0x19, 0x8c, 0xc6, 0xf3, 0x80,
    /* U+006F "o" (8x9) */
    0x3c, 0x46, 0xc2, 0xc3, 0xc3, 0xc3, 0xc2, 0x46, 0x3c,
    /* U+0070 "p" (9x13) */
    0xff, 0x18, 0xcc, 0x66, 0x33, 0x19, 0x8c, 0xc6, 0x63, 0x3f, 0x18, 0x0c,
    0x06, 0x0f, 0x80,
    /* U+0071 "q" (9x13) */
    0x3b, 0xa3, 0x31, 0x98, 0x4c, 0x26, 0x13, 0x19, 0x8c, 0x7a, 0x01, 0x00,
    0x80, 0xc0, 0xf8,
    /* U+0072 "r" (6x9) */
    0xfd, 0x96, 0x18, 0x61, 0x86, 0x18, 0xf0,
    /* U+0073 "s" (6x9) */
    0x7b, 0x3c, 0xb8, 0x78, 0x78, 0xf3, 0xf8,
    /* U+0074 "t" (5x11) */
    0x21, 0x3e, 0x42, 0x10, 0x84, 0x21, 0x0e,
    /* U+0075 "u" (10x9) */
    0xe3, 0x88, 0x62, 0x18, 0x86, 0x21, 0x88, 0x63, 0x18, 0xce, 0x1d, 0xc0,
    /* U+0076 "v" (9x9) */
    0xf3, 0xb0, 0x88, 0x46, 0x63, 0x20, 0xd0, 0x70, 0x38, 0x0c, 0x00,
    /* U+0077 "w" (14x9) */
    0xf3, 0x3d, 0x8c, 0x66, 0x39, 0x8d, 0xe4, 0x34, 0x90, 0xd3, 0xc1, 0xce,
    0x06, 0x18, 0x18, 0x60,
    /* U+0078 "x" (9x9) */
    0xff, 0x99, 0x86, 0x83, 0x80, 0xc0, 0xf0, 0xd8, 0x46, 0xf7, 0x80,
    /* U+0079 "y" (9x13) */
    0xf3, 0xb0, 0x88, 0x46, 0x63, 0x20, 0xd0, 0x78, 0x18, 0x0c, 0x06, 0x02,
    0x03, 0x07, 0x00,
    /* U+007A "z" (7x9) */
    0xff, 0x18, 0x60, 0xc3, 0x0c, 0x18, 0xe3, 0xfe,
    /* U+007B "{" (5x15) */
    0x19, 0x8c, 0x63, 0x19, 0x98, 0x61, 0x8c, 0x63, 0x18, 0x60,
    /* U+007C "|" (1x17) */
    0xff, 0xff, 0x80,
    /* U+007D "}" (5x15) */
    0xe3, 0x08, 0x42, 0x10, 0xc3, 0x31, 0x08, 0x42, 0x33, 0x00,
    /* U+007E "~" (7x3) */
    0x63, 0x26, 0x30,
    /* U+00B0 "" (5x5) */
    0x74, 0xa3, 0x27, 0x00,
    /* U+00B1 "" (7x9) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00, 0xfe,
    /* U+00B2 "" (5x7) */
    0x74, 0xc6, 0x22, 0x27, 0xe0,
    /* U+00B3 "" (5x7) */
    0xf4, 0xc4, 0xe1, 0xcf, 0xc0,
    /* U+00B5 "" (8x13) */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x67, 0x7b, 0x40, 0xc0, 0x60,
    0x60,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0x85, 0x33, 0x8c, 0x6b, 0x10,
    /* U+00F7 "" (7x8) */
    0x10, 0x20, 0x07, 0xf0, 0x00, 0x04, 0x08,
    /* U+0394 "" (9x12) */
    0x18, 0x0c, 0x0f, 0x05, 0x82, 0xc3, 0x31, 0x18, 0x8c, 0xc3, 0x41, 0xa0,
    0xdf, 0xf0,
    /* U+03A9 "" (11x12) */
    0x1f, 0x0c, 0x33, 0x03, 0x60, 0x6c, 0x0d, 0x81, 0xb0, 0x33, 0x0e, 0x3b,
    0x11, 0x4f, 0x69, 0xfd, 0xf0,
    /* U+03BC "" (8x13) */
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x67, 0x7b, 0x40, 0xc0, 0x60,
    0x60,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (16x1) */
    0xff, 0xff,
    /* U+2018 "" (3x5) */
    0x2a, 0x6c,
    /* U+2019 "" (2x4) */
    0xf7,
    /* U+201C "" (6x5) */
    0x25, 0x29, 0xb7, 0xc8,
    /* U+201D "" (6x5) */
    0xdb, 0x74, 0xf2, 0x90,
    /* U+2022 "" (4x5) */
    0x7f, 0xff, 0x70,
    /* U+2026 "" (12x2) */
    0xc6, 0x3c, 0x63,
    /* U+2030 "" (19x12) */
    0x70, 0x80, 0x1b, 0x10, 0x02, 0x64, 0x00, 0x44, 0x80, 0x09, 0xb0, 0x01,
    0xb4, 0xe3, 0x9d, 0xa4, 0xd8, 0x2c, 0xd3, 0x0d, 0x9a, 0x21, 0x33, 0x4c,
    0x22, 0x4d, 0x88, 0x38, 0xe0,
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
    {.bitmap_index = 0, .adv_w = 89, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 113, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 143, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 230, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 194, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 62, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 68, .adv_w = 93, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 93, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 87, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 94, .adv_w = 68, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 95, .adv_w = 79, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 96, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 74, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 107, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 147, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 75, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 77, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 228, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 235, .adv_w = 143, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 239, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 246, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 240, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 278, .adv_w = 185, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 189, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 187, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 205, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 97, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 95, .box_w = 6, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 415, .adv_w = 183, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 241, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 197, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 194, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 157, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 194, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 530, .adv_w = 172, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 160, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 272, .box_w = 17, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 173, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 97, .box_w = 3, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 681, .adv_w = 74, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 688, .adv_w = 97, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 694, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 701, .adv_w = 118, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 702, .adv_w = 74, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 704, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 161, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 161, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 99, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 771, .adv_w = 142, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 784, .adv_w = 167, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 86, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 810, .adv_w = 81, .box_w = 4, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 819, .adv_w = 154, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 83, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 246, .box_w = 15, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 169, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 161, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 897, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 912, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 94, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 165, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 225, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 972, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 149, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 998, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1006, .adv_w = 111, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1016, .adv_w = 143, .box_w = 1, .box_h = 17, .ofs_x = 4, .ofs_y = -4},
    {.bitmap_index = 1019, .adv_w = 111, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1029, .adv_w = 147, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1032, .adv_w = 102, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1036, .adv_w = 143, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 106, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1049, .adv_w = 106, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1054, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1067, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1068, .adv_w = 143, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1073, .adv_w = 143, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1080, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1094, .adv_w = 197, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 157, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1124, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1125, .adv_w = 256, .box_w = 16, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1127, .adv_w = 68, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1129, .adv_w = 68, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1130, .adv_w = 119, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1134, .adv_w = 119, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1138, .adv_w = 97, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1141, .adv_w = 224, .box_w = 12, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 332, .box_w = 19, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1180, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1194, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_serif_normal_16 = {
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

#endif /* #if HUMID1_FONT_PLEX_SERIF_NORMAL_16 */
