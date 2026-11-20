/*******************************************************************************
 * Font: humid1_font_noto_sans_normal_14 (noto_sans normal)
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

#ifndef HUMID1_FONT_NOTO_SANS_NORMAL_14
#define HUMID1_FONT_NOTO_SANS_NORMAL_14 1
#endif

#if HUMID1_FONT_NOTO_SANS_NORMAL_14

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_14);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xfc, 0xf0,
    /* U+0022 "" (4x3) */
    0x99, 0x90,
    /* U+0023 "#" (9x10) */
    0x1a, 0x09, 0x04, 0x8f, 0xf1, 0x61, 0xa3, 0xfc, 0x48, 0x24, 0x12, 0x00,
    /* U+0024 "$" (6x10) */
    0x7b, 0xf8, 0x38, 0x70, 0x70, 0x41, 0xf8, 0x80,
    /* U+0025 "%" (10x10) */
    0x61, 0x2c, 0x89, 0x22, 0x56, 0xb6, 0xfa, 0x91, 0xa4, 0x49, 0x22, 0xc8,
    0x60,
    /* U+0026 "&" (9x10) */
    0x38, 0x26, 0x13, 0x0d, 0x03, 0x02, 0xca, 0x35, 0x0c, 0xc7, 0x3c, 0xc0,
    /* U+0027 "'" (1x3) */
    0xe0,
    /* U+0028 "(" (3x13) */
    0x6b, 0x49, 0x24, 0x93, 0x26,
    /* U+0029 ")" (3x13) */
    0x99, 0x26, 0xdb, 0x69, 0x68,
    /* U+002A "" (6x7) */
    0x30, 0xcf, 0xff, 0x71, 0x64, 0x00,
    /* U+002B "+" (6x7) */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0x00,
    /* U+002C "," (2x4) */
    0xfa,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x10) */
    0x08, 0xc4, 0x23, 0x11, 0x8c, 0x46, 0x00,
    /* U+0030 "0" (6x10) */
    0x7b, 0x3c, 0x61, 0x86, 0x18, 0x71, 0xcd, 0xe0,
    /* U+0031 "1" (5x10) */
    0x3b, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc0,
    /* U+0032 "2" (7x10) */
    0x79, 0x98, 0x10, 0x60, 0xc3, 0x0c, 0x30, 0xc1, 0xfc,
    /* U+0033 "3" (6x10) */
    0x7a, 0x30, 0x43, 0x78, 0x30, 0x41, 0x0f, 0xe0,
    /* U+0034 "4" (8x10) */
    0x06, 0x0e, 0x1e, 0x36, 0x66, 0x46, 0xff, 0x06, 0x06, 0x06,
    /* U+0035 "5" (6x10) */
    0xff, 0x0c, 0x30, 0xf8, 0x30, 0x41, 0x0f, 0xe0,
    /* U+0036 "6" (6x10) */
    0x3d, 0x8c, 0x2e, 0xce, 0x18, 0x71, 0x4c, 0xe0,
    /* U+0037 "7" (6x10) */
    0xfc, 0x10, 0xc2, 0x18, 0x43, 0x0c, 0x21, 0x80,
    /* U+0038 "8" (6x10) */
    0x7b, 0xdc, 0xf3, 0x79, 0xec, 0xe1, 0xcd, 0xe0,
    /* U+0039 "9" (6x10) */
    0x7b, 0x38, 0x61, 0xcd, 0xf0, 0x43, 0x19, 0xc0,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (3x10) */
    0x6c, 0x00, 0x1b, 0x58,
    /* U+003C "<" (6x6) */
    0x0c, 0xee, 0x30, 0x38, 0x30,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (6x6) */
    0xc1, 0xc0, 0xc3, 0x73, 0x00,
    /* U+003F "?" (5x10) */
    0xf0, 0xc2, 0x33, 0x31, 0x00, 0x63, 0x00,
    /* U+0040 "@" (11x11) */
    0x1f, 0x06, 0x19, 0x3d, 0x6d, 0xb9, 0x13, 0x26, 0x64, 0xdc, 0xee, 0xc0,
    0x0c, 0x00, 0xfc, 0x00,
    /* U+0041 "A" (9x10) */
    0x0c, 0x0e, 0x07, 0x02, 0xc3, 0x21, 0x19, 0xfc, 0xc6, 0x41, 0xe0, 0xc0,
    /* U+0042 "B" (7x10) */
    0xfd, 0x8f, 0x0e, 0x3f, 0xd8, 0xf0, 0xe1, 0xc7, 0xf8,
    /* U+0043 "C" (7x10) */
    0x3e, 0xc3, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x60, 0x7c,
    /* U+0044 "D" (8x10) */
    0xfc, 0xc6, 0xc3, 0xc1, 0xc1, 0xc1, 0xc1, 0xc3, 0xc6, 0xfc,
    /* U+0045 "E" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+0046 "F" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0x00,
    /* U+0047 "G" (8x10) */
    0x1e, 0x60, 0x40, 0xc0, 0xc7, 0xc1, 0xc1, 0xc1, 0x63, 0x3f,
    /* U+0048 "H" (8x10) */
    0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
    /* U+0049 "I" (5x10) */
    0xf9, 0x88, 0x42, 0x10, 0x84, 0x37, 0xc0,
    /* U+004A "J" (4x13) */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,
    /* U+004B "K" (8x10) */
    0xc2, 0xc6, 0xcc, 0xd8, 0xf0, 0xf8, 0xc8, 0xcc, 0xc6, 0xc3,
    /* U+004C "L" (6x10) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+004D "M" (11x10) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf8, 0xfd, 0x17, 0xb6, 0xf6, 0x9e, 0x73, 0xce,
    0x78, 0x8c,
    /* U+004E "N" (9x10) */
    0xc1, 0xf0, 0xfc, 0x7a, 0x3d, 0x9e, 0x6f, 0x17, 0x8f, 0xc3, 0xe0, 0xc0,
    /* U+004F "O" (9x10) */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0x63, 0x1f, 0x00,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (9x12) */
    0x3e, 0x31, 0xb0, 0x78, 0x18, 0x0c, 0x07, 0x03, 0x83, 0x63, 0x1f, 0x01,
    0x80, 0x60,
    /* U+0052 "R" (7x10) */
    0xfd, 0x8b, 0x1e, 0x3c, 0x5f, 0x32, 0x66, 0xc7, 0x84,
    /* U+0053 "S" (6x10) */
    0x7f, 0x08, 0x30, 0x70, 0x70, 0xc1, 0x0f, 0xe0,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (8x10) */
    0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc3, 0x62, 0x3c,
    /* U+0056 "V" (9x10) */
    0xc1, 0xa0, 0x98, 0xcc, 0x42, 0x21, 0xb0, 0xd0, 0x38, 0x1c, 0x0c, 0x00,
    /* U+0057 "W" (13x10) */
    0xc3, 0x1a, 0x38, 0xd1, 0xc4, 0xca, 0x26, 0x5b, 0x16, 0x58, 0xe2, 0x87,
    0x1c, 0x38, 0xe0, 0xc3, 0x00,
    /* U+0058 "X" (8x10) */
    0x43, 0x62, 0x36, 0x1c, 0x18, 0x1c, 0x34, 0x26, 0x63, 0xc1,
    /* U+0059 "Y" (8x10) */
    0xc3, 0x42, 0x66, 0x34, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (8x10) */
    0x7f, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60, 0xff,
    /* U+005B "[" (3x12) */
    0xfa, 0x49, 0x24, 0x92, 0x70,
    /* U+005C "" (5x10) */
    0xc2, 0x18, 0xc2, 0x18, 0x42, 0x18, 0x40,
    /* U+005D "]" (4x12) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (6x6) */
    0x30, 0xc4, 0x92, 0x86, 0x10,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (3x3) */
    0x99, 0x80,
    /* U+0061 "a" (6x8) */
    0x78, 0x30, 0xdf, 0xce, 0x38, 0xdd,
    /* U+0062 "b" (7x11) */
    0xc1, 0x83, 0x07, 0xec, 0x78, 0xf0, 0xe1, 0xc7, 0x8f, 0xf0,
    /* U+0063 "c" (5x8) */
    0x7e, 0x31, 0x08, 0x63, 0x0f,
    /* U+0064 "d" (7x11) */
    0x06, 0x0c, 0x1b, 0xfc, 0xf8, 0xe1, 0xc3, 0xc7, 0x9d, 0xf8,
    /* U+0065 "e" (6x8) */
    0x3b, 0x38, 0x7f, 0x83, 0x0c, 0x0f,
    /* U+0066 "f" (6x11) */
    0x3c, 0xc6, 0x3e, 0x61, 0x86, 0x18, 0x61, 0x86, 0x00,
    /* U+0067 "g" (7x12) */
    0x7f, 0x9f, 0x1c, 0x38, 0x78, 0xf3, 0xbf, 0x06, 0x0c, 0x33, 0xc0,
    /* U+0068 "h" (7x11) */
    0xc1, 0x83, 0x07, 0xee, 0x78, 0xf1, 0xe3, 0xc7, 0x8f, 0x18,
    /* U+0069 "i" (2x11) */
    0x83, 0xff, 0xfc,
    /* U+006A "j" (4x15) */
    0x33, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,
    /* U+006B "k" (6x11) */
    0xc3, 0x0c, 0x33, 0xdb, 0x4f, 0x3c, 0xdb, 0x3c, 0x40,
    /* U+006C "l" (2x11) */
    0xff, 0xff, 0xfc,
    /* U+006D "m" (11x8) */
    0xfd, 0xd8, 0xcf, 0x18, 0xe3, 0x1c, 0x43, 0x88, 0x71, 0x0e, 0x21,
    /* U+006E "n" (7x8) */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    /* U+006F "o" (7x8) */
    0x79, 0x9b, 0x1c, 0x38, 0x78, 0xf3, 0x3c,
    /* U+0070 "p" (7x12) */
    0xfd, 0x8f, 0x1e, 0x1c, 0x38, 0xf1, 0xfe, 0xc1, 0x83, 0x06, 0x00,
    /* U+0071 "q" (7x12) */
    0x7f, 0x9f, 0x1c, 0x38, 0x78, 0xf3, 0xbf, 0x06, 0x0c, 0x18, 0x30,
    /* U+0072 "r" (5x8) */
    0xff, 0x31, 0x8c, 0x63, 0x18,
    /* U+0073 "s" (5x8) */
    0x7c, 0x31, 0xc3, 0x84, 0x3e,
    /* U+0074 "t" (5x10) */
    0x23, 0x3e, 0xc6, 0x31, 0x8c, 0x61, 0xc0,
    /* U+0075 "u" (7x8) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xbf,
    /* U+0076 "v" (7x8) */
    0xc2, 0x8d, 0x1b, 0x22, 0xc7, 0x0e, 0x0c,
    /* U+0077 "w" (11x8) */
    0xc6, 0x29, 0xcd, 0x39, 0xb5, 0x26, 0xb4, 0x73, 0x8c, 0x61, 0x8c,
    /* U+0078 "x" (6x8) */
    0x8f, 0x27, 0x8c, 0x31, 0xec, 0xe3,
    /* U+0079 "y" (7x12) */
    0xc2, 0x8d, 0x1b, 0x22, 0xc5, 0x8e, 0x0c, 0x18, 0x20, 0xc7, 0x00,
    /* U+007A "z" (6x8) */
    0x7c, 0x31, 0x86, 0x30, 0x86, 0x3f,
    /* U+007B "{" (5x13) */
    0x19, 0x8c, 0x63, 0x13, 0x84, 0x31, 0x8c, 0x61, 0x80,
    /* U+007C "|" (2x15) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (5x13) */
    0xe1, 0x0c, 0x63, 0x18, 0x66, 0x31, 0x8c, 0x4e, 0x00,
    /* U+007E "~" (6x2) */
    0xe0, 0x70,
    /* U+00B0 "" (4x5) */
    0x69, 0x99, 0x70,
    /* U+00B1 "" (6x9) */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0x00, 0xfc,
    /* U+00B2 "" (5x6) */
    0x70, 0xc4, 0x66, 0x7c,
    /* U+00B3 "" (5x6) */
    0x70, 0xdc, 0x31, 0xf8,
    /* U+00B5 "" (7x12) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xff, 0xc1, 0x83, 0x06, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0x85, 0x23, 0x0c, 0x4a, 0x10,
    /* U+00F7 "" (6x7) */
    0x30, 0xc0, 0x3f, 0x00, 0xc3, 0x00,
    /* U+0394 "" (8x10) */
    0x18, 0x18, 0x1c, 0x34, 0x26, 0x26, 0x62, 0x43, 0xc3, 0xff,
    /* U+03A9 "" (11x10) */
    0x1f, 0x06, 0x31, 0x83, 0x30, 0x66, 0x04, 0xc1, 0x98, 0x31, 0x04, 0x31,
    0x9f, 0x7c,
    /* U+03BC "" (7x12) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xff, 0xc1, 0x83, 0x06, 0x00,
    /* U+2013 "" (5x1) */
    0xf8,
    /* U+2014 "" (12x1) */
    0xff, 0xf0,
    /* U+2018 "" (2x3) */
    0x5c,
    /* U+2019 "" (3x3) */
    0x7b, 0x00,
    /* U+201C "" (5x3) */
    0x4a, 0xf6,
    /* U+201D "" (5x3) */
    0x7e, 0xf4,
    /* U+2022 "" (3x4) */
    0x7f, 0xb0,
    /* U+2026 "" (9x2) */
    0xc9, 0xe4, 0x40,
    /* U+2030 "" (15x10) */
    0x61, 0x01, 0x64, 0x02, 0x48, 0x04, 0xac, 0x6b, 0x6d, 0x5d, 0x4a, 0x46,
    0x94, 0x89, 0x29, 0x22, 0xd4, 0x43, 0x18,
    /* U+2190 "" (9x3) */
    0x40, 0x7f, 0xd0, 0x00,
    /* U+2191 "" (4x2) */
    0x6f,
    /* U+2192 "" (9x3) */
    0x01, 0x7f, 0xc0, 0x40,
    /* U+2193 "" (3x3) */
    0x8c, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 62, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 132, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 190, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 168, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 54, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 51, .adv_w = 70, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 56, .adv_w = 70, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 61, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 73, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 72, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 75, .adv_w = 61, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 132, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 61, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 64, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 171, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 176, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 184, .adv_w = 101, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 201, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 207, .adv_w = 147, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 147, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 125, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 163, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 168, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 65, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 142, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 207, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 176, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 179, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 376, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 166, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 212, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 137, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 129, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 74, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 477, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 74, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 490, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 495, .adv_w = 97, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 496, .adv_w = 67, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 498, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 111, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 130, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 81, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 555, .adv_w = 142, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 61, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 576, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 213, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 137, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 624, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 635, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 111, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 180, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 119, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 694, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 89, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 709, .adv_w = 123, .box_w = 2, .box_h = 15, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 713, .adv_w = 89, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 722, .adv_w = 128, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 724, .adv_w = 99, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 727, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 82, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 738, .adv_w = 82, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 742, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 753, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 754, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 759, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 765, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 175, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 800, .adv_w = 112, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 801, .adv_w = 224, .box_w = 12, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 803, .adv_w = 43, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 804, .adv_w = 43, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 806, .adv_w = 87, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 808, .adv_w = 84, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 810, .adv_w = 88, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 812, .adv_w = 177, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 267, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 838, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 839, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 843, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_noto_sans_normal_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 20,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_NOTO_SANS_NORMAL_14 */
