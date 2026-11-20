/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_14 (sans italic)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_14
#define HUMID1_FONT_PLEX_SANS_ITALIC_14 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_14

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_14);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x10) */
    0x6d, 0xa4, 0x80, 0xd0,
    /* U+0022 "" (5x4) */
    0xde, 0xe5, 0x20,
    /* U+0023 "#" (9x10) */
    0x09, 0x84, 0x82, 0x47, 0xf1, 0x21, 0x93, 0xfc, 0x48, 0x4c, 0x24, 0x00,
    /* U+0024 "$" (7x12) */
    0x04, 0x3c, 0xab, 0x46, 0x87, 0x07, 0x8b, 0x17, 0xad, 0xf1, 0x80,
    /* U+0025 "%" (11x10) */
    0x30, 0x49, 0x11, 0x24, 0x6d, 0x8d, 0xec, 0xea, 0x42, 0xc8, 0x9b, 0x33,
    0x6c, 0x38,
    /* U+0026 "&" (8x10) */
    0x1c, 0x26, 0x66, 0x6c, 0x38, 0x7b, 0xde, 0x8c, 0xce, 0xf6,
    /* U+0027 "'" (2x4) */
    0xfa,
    /* U+0028 "(" (5x13) */
    0x19, 0x88, 0xc4, 0x63, 0x10, 0xc6, 0x30, 0x86, 0x00,
    /* U+0029 ")" (5x13) */
    0x30, 0x86, 0x10, 0x84, 0x23, 0x19, 0x8c, 0xcc, 0x00,
    /* U+002A "" (7x6) */
    0x18, 0x33, 0xf9, 0xc3, 0x89, 0x00,
    /* U+002B "+" (7x7) */
    0x18, 0x30, 0x47, 0xf3, 0x06, 0x08, 0x00,
    /* U+002C "," (3x4) */
    0x4d, 0x40,
    /* U+002D "-" (4x2) */
    0xff,
    /* U+002E "." (2x2) */
    0xe0,
    /* U+002F "/" (8x12) */
    0x03, 0x02, 0x06, 0x04, 0x0c, 0x18, 0x18, 0x30, 0x20, 0x60, 0x40, 0xc0,
    /* U+0030 "0" (7x10) */
    0x3c, 0xcd, 0x1e, 0x3c, 0x78, 0xf1, 0xe6, 0xcc, 0xe0,
    /* U+0031 "1" (6x10) */
    0x1c, 0xf6, 0xd2, 0x18, 0x61, 0x86, 0x13, 0xf0,
    /* U+0032 "2" (8x10) */
    0x1e, 0x33, 0x03, 0x03, 0x06, 0x04, 0x18, 0x30, 0x60, 0xfe,
    /* U+0033 "3" (7x10) */
    0x3c, 0x8c, 0x18, 0x63, 0x81, 0x83, 0x06, 0x8d, 0xe0,
    /* U+0034 "4" (8x10) */
    0x07, 0x0f, 0x0e, 0x1e, 0x36, 0x66, 0x46, 0xff, 0x0c, 0x0c,
    /* U+0035 "5" (7x10) */
    0x7e, 0xc1, 0x02, 0x0f, 0xc9, 0x81, 0x86, 0xcd, 0xf0,
    /* U+0036 "6" (7x10) */
    0x0c, 0x71, 0xc3, 0x0f, 0xd9, 0xb1, 0xe2, 0xcc, 0xf0,
    /* U+0037 "7" (7x10) */
    0xff, 0x1a, 0x30, 0xc1, 0x86, 0x08, 0x30, 0xc1, 0x80,
    /* U+0038 "8" (7x10) */
    0x3c, 0xcd, 0x1b, 0x27, 0x99, 0xa1, 0x42, 0xcc, 0xf0,
    /* U+0039 "9" (7x10) */
    0x3c, 0xcf, 0x1e, 0x3c, 0x6f, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+003A ":" (3x7) */
    0x6c, 0x01, 0xa0,
    /* U+003B ";" (4x9) */
    0x33, 0x00, 0x06, 0x64, 0x80,
    /* U+003C "<" (6x7) */
    0x04, 0x67, 0x30, 0xc1, 0x83, 0x00,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xe0,
    /* U+003E ">" (6x8) */
    0x41, 0xc3, 0x83, 0x1d, 0xce, 0x20,
    /* U+003F "?" (6x10) */
    0x7b, 0x30, 0xc3, 0x18, 0xc6, 0x00, 0x61, 0x00,
    /* U+0040 "@" (11x12) */
    0x0f, 0x86, 0x19, 0x81, 0x27, 0xbd, 0xb3, 0x26, 0xec, 0xd4, 0x9a, 0x9f,
    0x98, 0x01, 0x80, 0x1f, 0x00,
    /* U+0041 "A" (8x10) */
    0x0e, 0x0e, 0x1e, 0x1a, 0x32, 0x33, 0x7f, 0x63, 0xc3, 0xc3,
    /* U+0042 "B" (9x10) */
    0x3f, 0x18, 0xcc, 0x64, 0x67, 0xe3, 0x19, 0x8c, 0xc6, 0x63, 0x7f, 0x00,
    /* U+0043 "C" (8x10) */
    0x1e, 0x63, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0x7c,
    /* U+0044 "D" (8x10) */
    0x7c, 0x62, 0x43, 0x43, 0x43, 0xc3, 0xc3, 0xc6, 0x84, 0xf8,
    /* U+0045 "E" (7x10) */
    0x7e, 0xc1, 0x82, 0x0f, 0xd8, 0x30, 0x60, 0x81, 0xf8,
    /* U+0046 "F" (7x10) */
    0x7e, 0xc1, 0x82, 0x0f, 0xd8, 0x30, 0x60, 0x81, 0x00,
    /* U+0047 "G" (8x10) */
    0x1e, 0x63, 0x40, 0xc0, 0xc0, 0xcf, 0xc3, 0xc2, 0xc6, 0x7e,
    /* U+0048 "H" (10x10) */
    0x30, 0xcc, 0x33, 0x08, 0x86, 0x7f, 0x98, 0x66, 0x19, 0x84, 0x43, 0x30,
    0xc0,
    /* U+0049 "I" (6x10) */
    0x3c, 0x61, 0x0c, 0x30, 0xc3, 0x0c, 0x23, 0xc0,
    /* U+004A "J" (7x10) */
    0x1e, 0x0c, 0x18, 0x30, 0x60, 0x83, 0x06, 0xcc, 0xf0,
    /* U+004B "K" (9x10) */
    0x31, 0x99, 0x8d, 0x85, 0xc7, 0xc3, 0xe1, 0x98, 0xcc, 0x43, 0x61, 0x80,
    /* U+004C "L" (6x10) */
    0x30, 0xc3, 0x08, 0x61, 0x86, 0x18, 0x63, 0xf0,
    /* U+004D "M" (11x10) */
    0x30, 0x67, 0x1c, 0xe7, 0x9c, 0xf6, 0xf4, 0xdd, 0x99, 0x33, 0x26, 0x40,
    0xd8, 0x10,
    /* U+004E "N" (9x10) */
    0x61, 0xb8, 0xdc, 0x4a, 0x2d, 0xb6, 0xdb, 0x2d, 0x9c, 0x8e, 0x43, 0x00,
    /* U+004F "O" (8x10) */
    0x1e, 0x63, 0x63, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0xc6, 0x78,
    /* U+0050 "P" (9x10) */
    0x3f, 0x18, 0xcc, 0x64, 0x36, 0x33, 0xf1, 0x80, 0xc0, 0x40, 0x60, 0x00,
    /* U+0051 "Q" (8x12) */
    0x1e, 0x63, 0x63, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0xc6, 0x7c, 0x30, 0x38,
    /* U+0052 "R" (9x10) */
    0x3f, 0x18, 0xcc, 0x64, 0x36, 0x33, 0xf1, 0x98, 0xcc, 0x46, 0x61, 0x80,
    /* U+0053 "S" (8x10) */
    0x1e, 0x33, 0x60, 0x60, 0x38, 0x0e, 0x06, 0x06, 0xc6, 0x7c,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20, 0x60,
    /* U+0055 "U" (8x10) */
    0x61, 0x63, 0x63, 0x43, 0xc3, 0xc2, 0xc2, 0xc6, 0xc4, 0x78,
    /* U+0056 "V" (8x10) */
    0xc1, 0x43, 0x42, 0x66, 0x64, 0x6c, 0x68, 0x78, 0x70, 0x30,
    /* U+0057 "W" (12x10) */
    0x8e, 0x38, 0xe6, 0x8e, 0x69, 0xe4, 0x96, 0xcb, 0x68, 0xa7, 0x8e, 0x78,
    0xe7, 0x0c, 0x70,
    /* U+0058 "X" (9x10) */
    0x31, 0x99, 0x84, 0xc3, 0xc1, 0xc0, 0xe0, 0xf0, 0xcc, 0x66, 0x61, 0x80,
    /* U+0059 "Y" (7x10) */
    0x87, 0x8b, 0x32, 0xc7, 0x0c, 0x18, 0x30, 0x60, 0x80,
    /* U+005A "Z" (8x10) */
    0x3f, 0x03, 0x06, 0x0c, 0x0c, 0x18, 0x30, 0x60, 0x60, 0xfe,
    /* U+005B "[" (5x13) */
    0x39, 0x8c, 0x42, 0x31, 0x8c, 0x42, 0x31, 0x8e, 0x00,
    /* U+005C "" (3x12) */
    0xdb, 0x64, 0x92, 0x4d, 0xb0,
    /* U+005D "]" (5x13) */
    0x38, 0x84, 0x23, 0x18, 0xc4, 0x23, 0x18, 0xcc, 0x00,
    /* U+005E "^" (7x5) */
    0x18, 0x78, 0xb3, 0x2c, 0x60,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xb4,
    /* U+0061 "a" (7x7) */
    0x77, 0x9f, 0x14, 0x68, 0xdb, 0xbb, 0x00,
    /* U+0062 "b" (8x10) */
    0x30, 0x30, 0x30, 0x2e, 0x72, 0x63, 0x63, 0x66, 0x66, 0xdc,
    /* U+0063 "c" (5x7) */
    0x3e, 0x71, 0x08, 0x4d, 0xc0,
    /* U+0064 "d" (7x10) */
    0x02, 0x0c, 0x1b, 0xbc, 0xf8, 0xa3, 0x46, 0xdd, 0xd8,
    /* U+0065 "e" (6x7) */
    0x39, 0x3c, 0xfc, 0x83, 0x27, 0x00,
    /* U+0066 "f" (7x13) */
    0x0e, 0x10, 0x61, 0xe1, 0x02, 0x0c, 0x18, 0x30, 0x60, 0x81, 0x0c, 0x00,
    /* U+0067 "g" (8x11) */
    0x03, 0x3c, 0x66, 0x66, 0x64, 0x38, 0x40, 0x7c, 0x86, 0x86, 0xfc,
    /* U+0068 "h" (7x10) */
    0x30, 0x60, 0xc1, 0x77, 0x6c, 0x59, 0xb3, 0x47, 0x8c,
    /* U+0069 "i" (3x10) */
    0x6c, 0x2d, 0xb6, 0x98,
    /* U+006A "j" (5x13) */
    0x18, 0xc0, 0x21, 0x18, 0xc6, 0x21, 0x18, 0xcc, 0x00,
    /* U+006B "k" (7x10) */
    0x30, 0x60, 0xc1, 0x36, 0xcf, 0x1e, 0x34, 0x4d, 0x8c,
    /* U+006C "l" (3x10) */
    0x6d, 0xad, 0xb6, 0x98,
    /* U+006D "m" (11x7) */
    0x3e, 0xee, 0xed, 0x98, 0xb3, 0x36, 0x66, 0x8c, 0xf1, 0x18,
    /* U+006E "n" (7x7) */
    0x3e, 0xed, 0x9b, 0x36, 0x68, 0xf1, 0x80,
    /* U+006F "o" (6x7) */
    0x3b, 0x3c, 0xe3, 0x8f, 0x67, 0x00,
    /* U+0070 "p" (8x10) */
    0x2e, 0x72, 0x63, 0x63, 0x66, 0x66, 0xdc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x10) */
    0x77, 0x9f, 0x14, 0x68, 0xdb, 0xbb, 0x04, 0x18, 0x30,
    /* U+0072 "r" (6x7) */
    0x3d, 0x86, 0x18, 0x41, 0x0c, 0x00,
    /* U+0073 "s" (5x7) */
    0x7e, 0x70, 0xe1, 0xcf, 0xc0,
    /* U+0074 "t" (4x9) */
    0x66, 0xf4, 0xcc, 0xcc, 0xe0,
    /* U+0075 "u" (7x7) */
    0x47, 0x8b, 0x36, 0x6c, 0xdb, 0xbb, 0x00,
    /* U+0076 "v" (6x7) */
    0x87, 0x3d, 0xb6, 0xd3, 0xc6, 0x00,
    /* U+0077 "w" (10x7) */
    0xcc, 0xf7, 0x3d, 0xdb, 0xd6, 0xf7, 0x39, 0xce, 0x60,
    /* U+0078 "x" (7x7) */
    0x66, 0x48, 0xe1, 0xc3, 0x89, 0x33, 0x00,
    /* U+0079 "y" (7x10) */
    0x42, 0xcd, 0x93, 0x66, 0x8f, 0x0c, 0x18, 0x21, 0x80,
    /* U+007A "z" (7x7) */
    0x7e, 0x18, 0x61, 0x86, 0x0c, 0x3f, 0x00,
    /* U+007B "{" (6x13) */
    0x1c, 0x43, 0x0c, 0x31, 0x8c, 0x38, 0x61, 0x86, 0x10, 0x60,
    /* U+007C "|" (4x13) */
    0x33, 0x26, 0x66, 0x64, 0x4c, 0xcc, 0x80,
    /* U+007D "}" (5x13) */
    0x30, 0x84, 0x63, 0x0c, 0x67, 0x23, 0x18, 0x8c, 0x00,
    /* U+007E "~" (6x2) */
    0xe2, 0x70,
    /* U+00B0 "" (4x5) */
    0x79, 0x99, 0xe0,
    /* U+00B1 "" (8x8) */
    0x0c, 0x0c, 0x7f, 0x08, 0x18, 0x18, 0x00, 0xfe,
    /* U+00B2 "" (4x5) */
    0x71, 0x24, 0xe0,
    /* U+00B3 "" (4x5) */
    0x71, 0x63, 0xe0,
    /* U+00B5 "" (8x10) */
    0x23, 0x62, 0x66, 0x66, 0x66, 0x6e, 0xf6, 0xc0, 0xc0, 0xc0,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (6x6) */
    0x45, 0xb3, 0x8e, 0x7b, 0x30,
    /* U+00F7 "" (7x7) */
    0x18, 0x30, 0x07, 0xf0, 0x06, 0x0c, 0x00,
    /* U+0394 "" (8x10) */
    0x0e, 0x0e, 0x1a, 0x1a, 0x33, 0x33, 0x63, 0x63, 0xc3, 0xff,
    /* U+03A9 "" (9x10) */
    0x0f, 0x18, 0xc8, 0x6c, 0x36, 0x1b, 0x0d, 0x8e, 0x6e, 0xf6, 0x73, 0x80,
    /* U+03BC "" (8x10) */
    0x23, 0x62, 0x66, 0x66, 0x66, 0x6e, 0xf6, 0xc0, 0xc0, 0xc0,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (9x1) */
    0xff, 0x80,
    /* U+2018 "" (2x4) */
    0x6e,
    /* U+2019 "" (3x4) */
    0x6d, 0xe0,
    /* U+201C "" (5x4) */
    0x4c, 0xf7, 0x30,
    /* U+201D "" (6x4) */
    0x6d, 0xb6, 0xf2,
    /* U+2022 "" (4x4) */
    0x7f, 0xfe,
    /* U+2026 "" (9x2) */
    0x88, 0xc4, 0xc0,
    /* U+2030 "" (16x10) */
    0x30, 0x40, 0x48, 0x80, 0xc9, 0x80, 0xdb, 0x00, 0xde, 0xc7, 0x75, 0x6d,
    0x0b, 0x29, 0x13, 0x69, 0x33, 0x6b, 0x61, 0xce,
    /* U+2190 "" (10x5) */
    0x30, 0x18, 0x0f, 0xfd, 0x80, 0x30, 0x00,
    /* U+2191 "" (6x10) */
    0x10, 0xe7, 0xfd, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (10x5) */
    0x03, 0x00, 0x6f, 0xfc, 0x06, 0x03, 0x00,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xcf, 0x5f, 0x38, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 53, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 68, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 104, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 208, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 57, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 55, .adv_w = 78, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 78, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 124, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 79, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 86, .adv_w = 67, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 88, .adv_w = 88, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 89, .adv_w = 67, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 101, .box_w = 8, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 102, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 71, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 71, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 201, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 207, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 211, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 198, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 242, .adv_w = 145, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 156, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 91, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 178, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 156, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 140, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 422, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 206, .box_w = 12, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 137, .box_w = 7, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 72, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 529, .adv_w = 101, .box_w = 3, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 534, .adv_w = 72, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 543, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 548, .adv_w = 123, .box_w = 7, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 549, .adv_w = 132, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 550, .adv_w = 132, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 76, .box_w = 7, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 599, .adv_w = 118, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 610, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 62, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 60, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 632, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 62, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 195, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 130, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 678, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 687, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 110, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 77, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 129, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 174, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 741, .adv_w = 107, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 79, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 758, .adv_w = 83, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 765, .adv_w = 79, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 774, .adv_w = 134, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 776, .adv_w = 102, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 779, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 790, .adv_w = 75, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 793, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 803, .adv_w = 76, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 804, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 809, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 816, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 848, .adv_w = 129, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 849, .adv_w = 172, .box_w = 9, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 851, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 852, .adv_w = 63, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 854, .adv_w = 113, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 857, .adv_w = 113, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 860, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 862, .adv_w = 193, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 294, .box_w = 16, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 196, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 892, .adv_w = 196, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 196, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 907, .adv_w = 196, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_italic_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 7,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_14 */
