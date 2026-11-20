/*******************************************************************************
 * Font: humid1_font_noto_sans_bold_14 (noto_sans bold)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_noto_sans_normal_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_NOTO_SANS_BOLD_14
#define HUMID1_FONT_NOTO_SANS_BOLD_14 1
#endif

#if HUMID1_FONT_NOTO_SANS_BOLD_14

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_noto_sans_normal_14);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x10) */
    0xff, 0xff, 0xb0, 0xf8,
    /* U+0022 "" (5x4) */
    0xde, 0xf7, 0xb0,
    /* U+0023 "#" (9x10) */
    0x1b, 0x0d, 0x1f, 0xef, 0xf3, 0x63, 0xfb, 0xfc, 0x78, 0x2c, 0x36, 0x00,
    /* U+0024 "$" (6x10) */
    0x7b, 0xfc, 0x38, 0xf0, 0xf1, 0xc7, 0xfd, 0xc0,
    /* U+0025 "%" (12x10) */
    0x70, 0xc7, 0x98, 0xd9, 0x8d, 0xb6, 0x7b, 0xf7, 0x6b, 0x05, 0xb0, 0xcb,
    0x08, 0xf1, 0x8e,
    /* U+0026 "&" (9x10) */
    0x78, 0x3e, 0x13, 0x0f, 0x07, 0x1f, 0xdf, 0x3d, 0x8e, 0xff, 0x3d, 0xc0,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (3x12) */
    0x6f, 0x6d, 0xb6, 0xd9, 0xb0,
    /* U+0029 ")" (3x12) */
    0xd9, 0xb6, 0xdb, 0x6f, 0x60,
    /* U+002A "" (6x7) */
    0x30, 0xcf, 0xff, 0x7b, 0xe4, 0x00,
    /* U+002B "+" (7x7) */
    0x30, 0x60, 0xc7, 0xff, 0xc6, 0x0c, 0x00,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (4x2) */
    0x7f,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x10) */
    0x0c, 0x71, 0x86, 0x30, 0xc7, 0x18, 0x63, 0x80,
    /* U+0030 "0" (7x10) */
    0x79, 0xfb, 0x36, 0x7c, 0xf9, 0xf3, 0xe6, 0xfc, 0xf0,
    /* U+0031 "1" (6x10) */
    0x1d, 0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c, 0x70,
    /* U+0032 "2" (7x10) */
    0x7d, 0xfd, 0x38, 0x70, 0xe3, 0x8e, 0x38, 0xff, 0xfc,
    /* U+0033 "3" (7x10) */
    0x7d, 0xfc, 0x3b, 0xe7, 0xc1, 0xc3, 0x87, 0xff, 0xf0,
    /* U+0034 "4" (8x10) */
    0x0e, 0x0e, 0x1e, 0x3e, 0x76, 0x66, 0xff, 0xff, 0x0e, 0x0e,
    /* U+0035 "5" (8x10) */
    0x7c, 0xfc, 0xe0, 0xf8, 0xfc, 0x0e, 0x0e, 0x0f, 0xfe, 0xfc,
    /* U+0036 "6" (7x10) */
    0x3d, 0xfb, 0x86, 0xcf, 0xd9, 0xf3, 0xe7, 0xfc, 0xf0,
    /* U+0037 "7" (8x10) */
    0xff, 0x7f, 0x06, 0x0e, 0x0c, 0x1c, 0x1c, 0x18, 0x38, 0x30,
    /* U+0038 "8" (7x10) */
    0x79, 0xff, 0xbf, 0x77, 0xdf, 0xb3, 0xc3, 0xfe, 0x78,
    /* U+0039 "9" (7x10) */
    0x79, 0xff, 0xbf, 0x3e, 0xef, 0xcf, 0x87, 0xfd, 0xf0,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (3x10) */
    0xdf, 0x00, 0x3e, 0xd8,
    /* U+003C "<" (6x6) */
    0x0c, 0xee, 0x38, 0x3c, 0x30,
    /* U+003D "=" (7x5) */
    0xfd, 0xfc, 0x07, 0xef, 0xe0,
    /* U+003E ">" (6x6) */
    0xc1, 0xc1, 0xc7, 0x7b, 0x00,
    /* U+003F "?" (7x10) */
    0x7d, 0xfc, 0x38, 0x73, 0xc7, 0x00, 0x18, 0x38, 0x60,
    /* U+0040 "@" (11x11) */
    0x1f, 0x07, 0xf9, 0xff, 0x6f, 0xbf, 0x37, 0xe6, 0xfc, 0xde, 0xfe, 0xec,
    0x8f, 0xf0, 0x7c, 0x00,
    /* U+0041 "A" (10x10) */
    0x1e, 0x07, 0x81, 0xf0, 0xec, 0x33, 0x0c, 0xe7, 0xf9, 0xfe, 0x61, 0xf8,
    0x70,
    /* U+0042 "B" (8x10) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xfe, 0xfe, 0xe7, 0xe7, 0xff, 0xfc,
    /* U+0043 "C" (8x10) */
    0x3f, 0x7f, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x7f, 0x3e,
    /* U+0044 "D" (9x10) */
    0xfc, 0x7f, 0x39, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f, 0xce, 0xfe, 0x7e, 0x00,
    /* U+0045 "E" (6x10) */
    0xff, 0xfe, 0x38, 0xff, 0xfe, 0x38, 0xff, 0xf0,
    /* U+0046 "F" (6x10) */
    0xff, 0xfe, 0x38, 0xff, 0xfe, 0x38, 0xe3, 0x80,
    /* U+0047 "G" (9x10) */
    0x0f, 0x9f, 0x9c, 0x0c, 0x06, 0x77, 0x7f, 0x8f, 0xe7, 0x7f, 0x9f, 0x80,
    /* U+0048 "H" (9x10) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7f, 0xff, 0xff, 0x8f, 0xc7, 0xe3, 0xf1, 0xc0,
    /* U+0049 "I" (6x10) */
    0xfd, 0xe3, 0x0c, 0x30, 0xc3, 0x0c, 0x7b, 0xf0,
    /* U+004A "J" (5x13) */
    0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xcf, 0xee, 0x00,
    /* U+004B "K" (8x10) */
    0xe7, 0xe7, 0xee, 0xfc, 0xfc, 0xfc, 0xee, 0xe6, 0xe7, 0xe3,
    /* U+004C "L" (7x10) */
    0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xff, 0xfc,
    /* U+004D "M" (12x10) */
    0xf0, 0xff, 0x0f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0xbf, 0xff, 0x7e, 0xf7,
    0xef, 0x7e, 0xe7,
    /* U+004E "N" (10x10) */
    0xf1, 0xfc, 0x7f, 0x9f, 0xf7, 0xfd, 0xfb, 0xfe, 0xff, 0x9f, 0xe3, 0xf8,
    0xf0,
    /* U+004F "O" (9x10) */
    0x3e, 0x3f, 0xb8, 0xfc, 0x3e, 0x1f, 0x0f, 0x87, 0xc7, 0x7f, 0x1f, 0x00,
    /* U+0050 "P" (8x10) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0051 "Q" (10x12) */
    0x3e, 0x1f, 0xee, 0x1b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x86, 0x7f, 0x8f,
    0xc0, 0x70, 0x0e,
    /* U+0052 "R" (8x10) */
    0xfc, 0xfe, 0xe6, 0xe6, 0xfe, 0xfc, 0xec, 0xee, 0xe7, 0xe3,
    /* U+0053 "S" (7x10) */
    0x7d, 0xfb, 0x87, 0x0f, 0x87, 0x87, 0x87, 0xfd, 0xf0,
    /* U+0054 "T" (8x10) */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (9x10) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0x7f, 0x1f, 0x00,
    /* U+0056 "V" (10x10) */
    0xe1, 0xd8, 0x67, 0x39, 0xce, 0x33, 0x0f, 0xc3, 0xf0, 0x78, 0x1e, 0x07,
    0x00,
    /* U+0057 "W" (14x10) */
    0xe3, 0x9f, 0x9e, 0x76, 0x79, 0xdd, 0xe6, 0x77, 0xf9, 0xff, 0xe3, 0xef,
    0x8f, 0x3c, 0x3c, 0xf0, 0xf3, 0xc0,
    /* U+0058 "X" (10x10) */
    0x61, 0xdc, 0xe3, 0xb0, 0xfc, 0x1e, 0x07, 0x83, 0xf0, 0xcc, 0x73, 0xb8,
    0x70,
    /* U+0059 "Y" (9x10) */
    0xe3, 0xb9, 0x9d, 0xc7, 0xc3, 0xe0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x00,
    /* U+005A "Z" (8x10) */
    0xff, 0x7f, 0x0e, 0x0e, 0x1c, 0x38, 0x38, 0x70, 0xff, 0xff,
    /* U+005B "[" (3x13) */
    0xff, 0x6d, 0xb6, 0xdb, 0x7e,
    /* U+005C "" (6x10) */
    0xe1, 0x86, 0x1c, 0x30, 0xc3, 0x86, 0x1c, 0x30,
    /* U+005D "]" (4x13) */
    0xf7, 0x33, 0x33, 0x33, 0x33, 0x3f, 0x70,
    /* U+005E "^" (7x6) */
    0x30, 0xf1, 0xe6, 0x6c, 0xd0, 0xc0,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (4x3) */
    0xce, 0x30,
    /* U+0061 "a" (7x8) */
    0x7c, 0xfc, 0x3b, 0xff, 0xf9, 0xff, 0xbb,
    /* U+0062 "b" (8x11) */
    0xe0, 0xe0, 0xe0, 0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc,
    /* U+0063 "c" (6x8) */
    0x3f, 0xfe, 0x30, 0xc3, 0x8f, 0xdf,
    /* U+0064 "d" (7x11) */
    0x0e, 0x1c, 0x3b, 0xff, 0xfd, 0xf1, 0xe3, 0xef, 0xfd, 0xd8,
    /* U+0065 "e" (7x8) */
    0x3d, 0xff, 0x1f, 0xff, 0xfc, 0x3f, 0x9e,
    /* U+0066 "f" (5x11) */
    0x7b, 0xf9, 0xff, 0xf3, 0x9c, 0xe7, 0x38,
    /* U+0067 "g" (7x11) */
    0x7f, 0xff, 0x9e, 0x3c, 0x7c, 0xff, 0xbf, 0x07, 0xff, 0xf0,
    /* U+0068 "h" (8x11) */
    0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0069 "i" (3x11) */
    0xc0, 0x7f, 0xff, 0xff, 0x80,
    /* U+006A "j" (5x14) */
    0x39, 0xc0, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x7f, 0xf8,
    /* U+006B "k" (8x11) */
    0xe0, 0xe0, 0xe0, 0xe7, 0xee, 0xfc, 0xf8, 0xfc, 0xee, 0xee, 0xe7,
    /* U+006C "l" (3x11) */
    0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+006D "m" (12x8) */
    0xfe, 0xef, 0xff, 0xe7, 0x3e, 0x73, 0xe7, 0x3e, 0x73, 0xe7, 0x3e, 0x73,
    /* U+006E "n" (8x8) */
    0xfe, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+006F "o" (7x8) */
    0x7d, 0xff, 0xbe, 0x3c, 0x7d, 0xff, 0xbe,
    /* U+0070 "p" (8x11) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0,
    /* U+0071 "q" (7x11) */
    0x7f, 0xff, 0x9e, 0x3c, 0x7c, 0xff, 0xbf, 0x06, 0x0c, 0x18,
    /* U+0072 "r" (5x8) */
    0xdf, 0xf9, 0xce, 0x73, 0x9c,
    /* U+0073 "s" (6x8) */
    0x7f, 0xfe, 0x3e, 0x7c, 0x7f, 0xfe,
    /* U+0074 "t" (5x9) */
    0x67, 0xff, 0xce, 0x73, 0x9f, 0x78,
    /* U+0075 "u" (8x8) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7f,
    /* U+0076 "v" (8x8) */
    0xe3, 0x67, 0x77, 0x76, 0x3e, 0x3e, 0x3c, 0x1c,
    /* U+0077 "w" (12x8) */
    0xe7, 0x36, 0x77, 0x6f, 0x77, 0xff, 0x7d, 0xe3, 0xde, 0x39, 0xe3, 0x9c,
    /* U+0078 "x" (8x8) */
    0xe7, 0x77, 0x3e, 0x3c, 0x3e, 0x3e, 0x77, 0xe7,
    /* U+0079 "y" (8x11) */
    0xe3, 0x67, 0x77, 0x76, 0x3e, 0x3c, 0x1c, 0x1c, 0x18, 0x78, 0x70,
    /* U+007A "z" (7x8) */
    0xfe, 0xfc, 0x71, 0xc3, 0x8e, 0x3f, 0xff,
    /* U+007B "{" (6x13) */
    0x1c, 0xe3, 0x0c, 0x33, 0xcf, 0x0c, 0x30, 0xc3, 0x8f, 0x18,
    /* U+007C "|" (2x14) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+007D "}" (5x13) */
    0xc7, 0x18, 0xc6, 0x3d, 0xec, 0x63, 0x19, 0xcc, 0x00,
    /* U+007E "~" (7x3) */
    0x41, 0xfc, 0x70,
    /* U+00B0 "" (5x5) */
    0x77, 0xe7, 0xf7, 0x00,
    /* U+00B1 "" (7x9) */
    0x30, 0x63, 0xf7, 0xf3, 0x06, 0x0c, 0x7e, 0xfc,
    /* U+00B2 "" (6x6) */
    0x79, 0x61, 0x8e, 0x73, 0xf0,
    /* U+00B3 "" (4x6) */
    0xff, 0xf3, 0xbf,
    /* U+00B5 "" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe0, 0xe0, 0xe0,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0xcf, 0xf7, 0x9e, 0xff, 0x30,
    /* U+00F7 "" (7x7) */
    0x30, 0x63, 0xf7, 0xf0, 0x06, 0x0c, 0x00,
    /* U+0394 "" (9x10) */
    0x1e, 0x0f, 0x07, 0x87, 0xe3, 0x31, 0x99, 0xce, 0xc3, 0xff, 0xff, 0xc0,
    /* U+03A9 "" (11x10) */
    0x1f, 0x07, 0xf1, 0xc7, 0x38, 0x66, 0x0c, 0xc1, 0x9c, 0x71, 0x8c, 0x7b,
    0xff, 0x7c,
    /* U+03BC "" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe0, 0xe0, 0xe0,
    /* U+2013 "" (5x2) */
    0xff, 0xc0,
    /* U+2014 "" (12x2) */
    0xff, 0xff, 0xff,
    /* U+2018 "" (3x4) */
    0x6d, 0xf0,
    /* U+2019 "" (3x3) */
    0x6f, 0x80,
    /* U+201C "" (7x3) */
    0x66, 0xdb, 0xb0,
    /* U+201D "" (7x3) */
    0x6e, 0xdb, 0xb0,
    /* U+2022 "" (4x5) */
    0x6f, 0xff, 0x60,
    /* U+2026 "" (10x2) */
    0xcc, 0xf3, 0x30,
    /* U+2030 "" (17x10) */
    0x70, 0xc0, 0x3c, 0xc0, 0x36, 0x40, 0x1b, 0x6c, 0x67, 0xbf, 0x7b, 0xb5,
    0xb4, 0x16, 0xd2, 0x19, 0x6d, 0x08, 0xf7, 0x8c, 0x71, 0x80,
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
    {.bitmap_index = 0, .adv_w = 67, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 135, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 209, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 66, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 55, .adv_w = 82, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 60, .adv_w = 82, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 65, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 71, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 78, .adv_w = 66, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 72, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 80, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 99, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 66, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 71, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 187, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 192, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 197, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 202, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 201, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 227, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 167, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 162, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 95, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 81, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 329, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 218, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 189, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 181, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 413, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 153, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 224, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 149, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 74, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 525, .adv_w = 99, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 74, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 540, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 546, .adv_w = 87, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 547, .adv_w = 88, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 549, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 144, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 140, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 94, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 607, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 75, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 75, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 632, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 75, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 227, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 696, .adv_w = 108, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 135, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 199, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 760, .adv_w = 112, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 95, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 777, .adv_w = 123, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 781, .adv_w = 95, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 790, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 793, .adv_w = 103, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 797, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 92, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 810, .adv_w = 92, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 813, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 824, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 825, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 830, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 837, .adv_w = 155, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 177, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 874, .adv_w = 112, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 876, .adv_w = 224, .box_w = 12, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 879, .adv_w = 56, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 881, .adv_w = 56, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 883, .adv_w = 112, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 886, .adv_w = 107, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 889, .adv_w = 91, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 892, .adv_w = 192, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 895, .adv_w = 294, .box_w = 17, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 921, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 922, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 926, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_noto_sans_bold_14 = {
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
    .fallback = &humid1_font_noto_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_NOTO_SANS_BOLD_14 */
