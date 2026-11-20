/*******************************************************************************
 * Font: humid1_font_plex_sans_bold_12 (sans bold)
 * Size: 12 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_12 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_SANS_BOLD_12
#define HUMID1_FONT_PLEX_SANS_BOLD_12 1
#endif

#if HUMID1_FONT_PLEX_SANS_BOLD_12

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_12);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x9) */
    0xff, 0xd3, 0xc0,
    /* U+0022 "" (5x4) */
    0xde, 0xf7, 0xb0,
    /* U+0023 "#" (7x9) */
    0x26, 0x4f, 0xff, 0xf4, 0x5f, 0xff, 0xe4, 0xc8,
    /* U+0024 "$" (6x11) */
    0x31, 0xef, 0xfc, 0xf1, 0xf3, 0xcf, 0xfd, 0xe3, 0x00,
    /* U+0025 "%" (11x9) */
    0x71, 0x9f, 0x63, 0x6c, 0x7f, 0x07, 0xfc, 0x1f, 0xc6, 0xd8, 0xdf, 0x31,
    0xc0,
    /* U+0026 "&" (8x9) */
    0x38, 0x7c, 0x6c, 0x78, 0x7b, 0xff, 0xce, 0xfe, 0x7f,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (4x12) */
    0x36, 0x6c, 0xcc, 0xcc, 0xc6, 0x63,
    /* U+0029 ")" (4x12) */
    0xe6, 0x73, 0x33, 0x33, 0x37, 0x6e,
    /* U+002A "" (8x7) */
    0x18, 0x18, 0xff, 0x7e, 0x3c, 0x76, 0x26,
    /* U+002B "+" (6x6) */
    0x30, 0xcf, 0xff, 0x30, 0xc0,
    /* U+002C "," (2x4) */
    0xf6,
    /* U+002D "-" (4x2) */
    0xff,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x11) */
    0x08, 0xc6, 0x23, 0x18, 0x8c, 0x62, 0x30,
    /* U+0030 "0" (7x9) */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xbe, 0x38,
    /* U+0031 "1" (7x9) */
    0x38, 0xf3, 0x62, 0xc1, 0x83, 0x06, 0x3f, 0x7e,
    /* U+0032 "2" (6x9) */
    0x7b, 0xf4, 0xc3, 0x18, 0xc6, 0x3f, 0xfc,
    /* U+0033 "3" (6x9) */
    0x7b, 0xf0, 0xcf, 0x38, 0x34, 0xff, 0x78,
    /* U+0034 "4" (7x9) */
    0x1c, 0x38, 0xf3, 0x66, 0xdf, 0xff, 0x86, 0x0c,
    /* U+0035 "5" (6x9) */
    0xfb, 0xec, 0x3e, 0xfc, 0x34, 0xff, 0x78,
    /* U+0036 "6" (6x9) */
    0x39, 0xc6, 0x3e, 0xff, 0x3c, 0xff, 0x78,
    /* U+0037 "7" (6x9) */
    0xff, 0xfc, 0xc7, 0x18, 0x63, 0x8c, 0x30,
    /* U+0038 "8" (6x9) */
    0x7b, 0xfc, 0xdf, 0x7b, 0x3c, 0xff, 0x78,
    /* U+0039 "9" (6x9) */
    0x7b, 0xfc, 0xf3, 0xfd, 0xf1, 0xce, 0x70,
    /* U+003A ":" (2x7) */
    0xf0, 0x3c,
    /* U+003B ";" (2x8) */
    0xf0, 0xf6,
    /* U+003C "<" (5x6) */
    0x1b, 0xb9, 0xc7, 0x0c,
    /* U+003D "=" (6x5) */
    0xff, 0xf0, 0x3f, 0xfc,
    /* U+003E ">" (4x8) */
    0x8c, 0xe3, 0x3e, 0xc8,
    /* U+003F "?" (6x9) */
    0x7b, 0xf0, 0xc7, 0x38, 0xc0, 0x0c, 0x30,
    /* U+0040 "@" (9x11) */
    0x3e, 0x31, 0xb0, 0x73, 0xdb, 0x6d, 0xb6, 0xdb, 0xbe, 0x60, 0x3f, 0x07,
    0x80,
    /* U+0041 "A" (8x9) */
    0x1c, 0x3c, 0x3c, 0x36, 0x36, 0x7e, 0x7f, 0x63, 0xe3,
    /* U+0042 "B" (7x9) */
    0xfd, 0xfb, 0x37, 0xef, 0xd8, 0xf1, 0xff, 0xfc,
    /* U+0043 "C" (7x9) */
    0x3c, 0xff, 0x96, 0x0c, 0x18, 0x39, 0x3f, 0x3c,
    /* U+0044 "D" (7x9) */
    0xf9, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xfe, 0xf8,
    /* U+0045 "E" (6x9) */
    0xff, 0xfc, 0x3e, 0xff, 0x0c, 0x3f, 0xfc,
    /* U+0046 "F" (6x9) */
    0xff, 0xfc, 0x3e, 0xfb, 0x0c, 0x30, 0xc0,
    /* U+0047 "G" (7x9) */
    0x38, 0xff, 0x06, 0x0d, 0xf9, 0xf1, 0xbf, 0x36,
    /* U+0048 "H" (7x9) */
    0xc7, 0x8f, 0x1f, 0xff, 0xf8, 0xf1, 0xe3, 0xc6,
    /* U+0049 "I" (4x9) */
    0xff, 0x66, 0x66, 0x6f, 0xf0,
    /* U+004A "J" (6x9) */
    0x7c, 0xf0, 0xc3, 0x0c, 0x34, 0xff, 0x78,
    /* U+004B "K" (7x9) */
    0xc7, 0x9b, 0x76, 0xcf, 0x9f, 0xb3, 0x67, 0xc6,
    /* U+004C "L" (5x9) */
    0xc6, 0x31, 0x8c, 0x63, 0x1f, 0xf8,
    /* U+004D "M" (8x9) */
    0xe3, 0xe7, 0xe7, 0xff, 0xff, 0xdb, 0xcb, 0xc3, 0xc3,
    /* U+004E "N" (7x9) */
    0xe7, 0xcf, 0xdf, 0xbd, 0xfb, 0xf3, 0xe7, 0xc6,
    /* U+004F "O" (7x9) */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xbe, 0x38,
    /* U+0050 "P" (7x9) */
    0xfd, 0xff, 0x1e, 0x3f, 0xff, 0x30, 0x60, 0xc0,
    /* U+0051 "Q" (7x12) */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0x7c, 0x70, 0x70, 0xe0,
    /* U+0052 "R" (7x9) */
    0xfd, 0xff, 0x1e, 0x3f, 0xff, 0xb3, 0x66, 0xce,
    /* U+0053 "S" (6x9) */
    0x7b, 0xfc, 0x3c, 0x7c, 0x70, 0xff, 0x78,
    /* U+0054 "T" (6x9) */
    0xff, 0xf3, 0x0c, 0x30, 0xc3, 0x0c, 0x30,
    /* U+0055 "U" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x7c,
    /* U+0056 "V" (8x9) */
    0xc3, 0x66, 0x66, 0x66, 0x76, 0x3c, 0x3c, 0x3c, 0x18,
    /* U+0057 "W" (12x9) */
    0xe6, 0x36, 0x76, 0x6f, 0x66, 0xf6, 0x6f, 0x63, 0x9e, 0x39, 0xc3, 0x9c,
    0x39, 0xc0,
    /* U+0058 "X" (8x9) */
    0x67, 0x76, 0x3e, 0x3c, 0x1c, 0x3c, 0x3e, 0x66, 0xe7,
    /* U+0059 "Y" (8x9) */
    0xe7, 0x66, 0x76, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (6x9) */
    0xff, 0xf1, 0xce, 0x31, 0xce, 0x3f, 0xfc,
    /* U+005B "[" (3x12) */
    0xff, 0x6d, 0xb6, 0xdb, 0xf0,
    /* U+005C "" (5x11) */
    0x86, 0x30, 0x86, 0x30, 0x86, 0x30, 0x86,
    /* U+005D "]" (3x12) */
    0xfd, 0xb6, 0xdb, 0x6f, 0xf0,
    /* U+005E "^" (6x5) */
    0x31, 0xc7, 0xb6, 0xcc,
    /* U+005F "_" (6x2) */
    0xff, 0xf0,
    /* U+0060 "`" (2x2) */
    0xd0,
    /* U+0061 "a" (6x7) */
    0x79, 0xf0, 0xdf, 0xcf, 0xf6, 0xc0,
    /* U+0062 "b" (6x10) */
    0xc3, 0x0c, 0x36, 0xff, 0x3c, 0xf3, 0xff, 0xe0,
    /* U+0063 "c" (5x7) */
    0x7f, 0xf1, 0x8c, 0x7d, 0xe0,
    /* U+0064 "d" (6x10) */
    0x0c, 0x30, 0xdf, 0xff, 0x3c, 0xf3, 0xfd, 0xb0,
    /* U+0065 "e" (6x7) */
    0x7b, 0xff, 0xff, 0xc3, 0xf7, 0x80,
    /* U+0066 "f" (4x10) */
    0x77, 0x6f, 0xf6, 0x66, 0x66,
    /* U+0067 "g" (6x11) */
    0x0d, 0xff, 0xf3, 0xfd, 0xef, 0xbf, 0x8f, 0xff, 0x80,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0c, 0x36, 0xff, 0x3c, 0xf3, 0xcf, 0x30,
    /* U+0069 "i" (2x10) */
    0xf3, 0xff, 0xf0,
    /* U+006A "j" (3x13) */
    0x6c, 0x36, 0xdb, 0x6d, 0xfe,
    /* U+006B "k" (6x10) */
    0xc3, 0x0c, 0x33, 0xdb, 0xef, 0xbe, 0xdf, 0x30,
    /* U+006C "l" (3x10) */
    0xdb, 0x6d, 0xb6, 0xec,
    /* U+006D "m" (10x7) */
    0xd9, 0xbf, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcc,
    /* U+006E "n" (6x7) */
    0xdb, 0xfc, 0xf3, 0xcf, 0x3c, 0xc0,
    /* U+006F "o" (6x7) */
    0x7b, 0xfc, 0xf3, 0xcf, 0xf7, 0x80,
    /* U+0070 "p" (6x10) */
    0xfb, 0xfc, 0xf3, 0xcf, 0xff, 0xb0, 0xc3, 0x00,
    /* U+0071 "q" (6x10) */
    0x6f, 0xfc, 0xf3, 0xcf, 0xf6, 0xc3, 0x0c, 0x30,
    /* U+0072 "r" (4x7) */
    0xff, 0xcc, 0xcc, 0xc0,
    /* U+0073 "s" (5x7) */
    0x7f, 0xf1, 0xf1, 0xfd, 0xc0,
    /* U+0074 "t" (4x9) */
    0x66, 0xff, 0x66, 0x67, 0x70,
    /* U+0075 "u" (6x7) */
    0xcf, 0x3c, 0xf3, 0xcf, 0xf6, 0xc0,
    /* U+0076 "v" (6x7) */
    0xc5, 0x36, 0xdb, 0x78, 0xe3, 0x80,
    /* U+0077 "w" (10x7) */
    0xcc, 0xdb, 0xb6, 0xed, 0xea, 0x7b, 0x8c, 0xe3, 0x38,
    /* U+0078 "x" (7x7) */
    0xee, 0xd8, 0xe1, 0xc3, 0x8d, 0xbb, 0x00,
    /* U+0079 "y" (7x10) */
    0xc6, 0xc9, 0xb3, 0x66, 0xc7, 0x0e, 0x1c, 0x70, 0xe0,
    /* U+007A "z" (5x7) */
    0xff, 0xcc, 0xe6, 0x7f, 0xe0,
    /* U+007B "{" (4x12) */
    0x77, 0x66, 0x6e, 0xc6, 0x66, 0x77,
    /* U+007C "|" (2x12) */
    0xff, 0xff, 0xff,
    /* U+007D "}" (4x12) */
    0xe6, 0x66, 0x67, 0x36, 0x66, 0x6e,
    /* U+007E "~" (5x3) */
    0xc7, 0xce,
    /* U+00B0 "" (4x5) */
    0x6f, 0x9f, 0x60,
    /* U+00B1 "" (6x8) */
    0x30, 0xcf, 0xff, 0x30, 0xcf, 0xff,
    /* U+00B2 "" (3x4) */
    0xe5, 0x70,
    /* U+00B3 "" (3x4) */
    0xec, 0xf0,
    /* U+00B5 "" (6x10) */
    0xcf, 0x3c, 0xf3, 0xcf, 0xff, 0xf0, 0xc3, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x6) */
    0x0e, 0xdc, 0xef, 0xe4,
    /* U+00F7 "" (6x7) */
    0x30, 0xcf, 0xff, 0x00, 0xc3, 0x00,
    /* U+0394 "" (7x9) */
    0x38, 0x71, 0xf3, 0x66, 0xcd, 0xf1, 0xff, 0xfe,
    /* U+03A9 "" (7x9) */
    0x38, 0xff, 0x9e, 0x3c, 0x7c, 0xdb, 0x77, 0xee,
    /* U+03BC "" (7x9) */
    0xcd, 0x9b, 0x36, 0x6c, 0xdf, 0xbf, 0xe0, 0xc0,
    /* U+2013 "" (6x2) */
    0xff, 0xf0,
    /* U+2014 "" (8x2) */
    0xff, 0xff,
    /* U+2018 "" (2x4) */
    0x7f,
    /* U+2019 "" (2x4) */
    0xf6,
    /* U+201C "" (5x4) */
    0x4e, 0xf7, 0xb0,
    /* U+201D "" (5x4) */
    0xde, 0xd3, 0x20,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (10x2) */
    0xcc, 0xf3, 0x30,
    /* U+2030 "" (16x9) */
    0x71, 0x80, 0xfb, 0x00, 0xdb, 0x00, 0xfe, 0x00, 0x7f, 0xce, 0x0f, 0xff,
    0x1b, 0x7b, 0x1b, 0xfb, 0x31, 0xce,
    /* U+2190 "" (8x6) */
    0x20, 0x60, 0xff, 0xff, 0x60, 0x20,
    /* U+2191 "" (6x8) */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0c,
    /* U+2192 "" (9x5) */
    0x06, 0x03, 0xbf, 0xef, 0xe0, 0x60,
    /* U+2193 "" (6x8) */
    0x30, 0xc3, 0x0c, 0x33, 0xf7, 0x8c,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 45, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 65, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 101, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 116, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 191, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 141, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 46, .adv_w = 65, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 52, .adv_w = 65, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 58, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 65, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 78, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 72, .adv_w = 63, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 95, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 80, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 67, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 67, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 157, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 161, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 165, .adv_w = 115, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 98, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 174, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 189, .adv_w = 135, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 86, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 104, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 158, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 322, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 194, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 134, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 405, .adv_w = 95, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 412, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 417, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 421, .adv_w = 106, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 423, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 424, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 73, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 108, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 471, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 58, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 487, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 61, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 173, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 528, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 536, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 76, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 168, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 106, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 587, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 74, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 598, .adv_w = 85, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 601, .adv_w = 74, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 607, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 609, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 612, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 67, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 620, .adv_w = 66, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 622, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 630, .adv_w = 71, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 631, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 635, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 122, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 665, .adv_w = 113, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 667, .adv_w = 150, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 669, .adv_w = 60, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 670, .adv_w = 60, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 671, .adv_w = 108, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 674, .adv_w = 108, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 677, .adv_w = 85, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 679, .adv_w = 180, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 272, .box_w = 16, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 180, .box_w = 8, .box_h = 6, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 706, .adv_w = 180, .box_w = 6, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 180, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 718, .adv_w = 180, .box_w = 6, .box_h = 8, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_bold_12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 9,
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
    .fallback = &humid1_font_plex_sans_normal_12,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_BOLD_12 */
