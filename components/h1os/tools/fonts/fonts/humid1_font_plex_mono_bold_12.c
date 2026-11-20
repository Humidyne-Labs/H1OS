/*******************************************************************************
 * Font: humid1_font_plex_mono_bold_12 (mono bold)
 * Size: 12 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_bold_12 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_MONO_BOLD_12
#define HUMID1_FONT_PLEX_MONO_BOLD_12 1
#endif

#if HUMID1_FONT_PLEX_MONO_BOLD_12

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_bold_12);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x8) */
    0xff, 0x4f,
    /* U+0022 "" (5x3) */
    0xde, 0xf6,
    /* U+0023 "#" (7x8) */
    0x36, 0x7b, 0xbb, 0x66, 0xdd, 0xde, 0x6c,
    /* U+0024 "$" (6x10) */
    0x31, 0xef, 0xbc, 0xf9, 0xf3, 0xff, 0xf8, 0xc0,
    /* U+0025 "%" (7x8) */
    0x63, 0x2a, 0x57, 0x01, 0xca, 0x54, 0xc6,
    /* U+0026 "&" (7x8) */
    0x78, 0xd1, 0x83, 0xbf, 0xdb, 0xbf, 0x3b,
    /* U+0027 "'" (2x3) */
    0xfc,
    /* U+0028 "(" (4x10) */
    0x36, 0x6c, 0xcc, 0xc6, 0x63,
    /* U+0029 ")" (4x10) */
    0xc6, 0x73, 0x33, 0x37, 0x6c,
    /* U+002A "" (6x6) */
    0x32, 0xdf, 0xde, 0xfd, 0x20,
    /* U+002B "+" (6x6) */
    0x30, 0xc3, 0x3f, 0x70, 0xc0,
    /* U+002C "," (3x4) */
    0xff, 0x60,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (3x2) */
    0xfc,
    /* U+002F "/" (5x10) */
    0x18, 0xc6, 0x63, 0x31, 0x8c, 0xc6, 0x00,
    /* U+0030 "0" (7x8) */
    0x38, 0xdb, 0x1e, 0xbc, 0x78, 0xdb, 0x1c,
    /* U+0031 "1" (7x8) */
    0x38, 0xf3, 0x60, 0xc1, 0x83, 0x06, 0x3f,
    /* U+0032 "2" (6x8) */
    0x7b, 0x70, 0xc3, 0x19, 0xce, 0x3f,
    /* U+0033 "3" (6x8) */
    0x7b, 0x30, 0xce, 0x1c, 0x3d, 0xde,
    /* U+0034 "4" (7x8) */
    0x1c, 0x38, 0xb3, 0x64, 0xdf, 0xc3, 0x06,
    /* U+0035 "5" (6x8) */
    0xff, 0x8c, 0x3f, 0xfc, 0x3f, 0xfe,
    /* U+0036 "6" (7x8) */
    0x3c, 0xe1, 0x87, 0xee, 0xf8, 0xff, 0xbe,
    /* U+0037 "7" (6x8) */
    0xff, 0x3c, 0xc6, 0x18, 0x63, 0x0c,
    /* U+0038 "8" (6x8) */
    0x7b, 0xbc, 0xde, 0xef, 0x3f, 0xde,
    /* U+0039 "9" (7x8) */
    0x7d, 0xdf, 0x1f, 0x77, 0xe1, 0x87, 0x3c,
    /* U+003A ":" (3x6) */
    0xfc, 0x0f, 0xc0,
    /* U+003B ";" (3x8) */
    0xfc, 0x0f, 0xb6,
    /* U+003C "<" (5x7) */
    0x09, 0xfd, 0x8f, 0x1c, 0x20,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (5x7) */
    0x87, 0x1e, 0x37, 0xf2, 0x00,
    /* U+003F "?" (5x8) */
    0x76, 0xc6, 0x37, 0x01, 0x8c,
    /* U+0040 "@" (7x9) */
    0x3c, 0xcb, 0x7f, 0xbf, 0x7e, 0xf7, 0xb0, 0x38,
    /* U+0041 "A" (7x8) */
    0x38, 0x79, 0xf3, 0x66, 0xcf, 0xfb, 0xe3,
    /* U+0042 "B" (6x8) */
    0xfb, 0x7c, 0xfe, 0xdf, 0x3d, 0xfe,
    /* U+0043 "C" (6x8) */
    0x79, 0xbc, 0x30, 0xc3, 0x06, 0xde,
    /* U+0044 "D" (6x8) */
    0xfb, 0xfc, 0xf3, 0xcf, 0x3f, 0xfe,
    /* U+0045 "E" (6x8) */
    0xff, 0x8c, 0x3f, 0xe3, 0x0e, 0x3f,
    /* U+0046 "F" (6x8) */
    0xff, 0x8c, 0x3f, 0xe3, 0x0c, 0x30,
    /* U+0047 "G" (6x8) */
    0x79, 0xfc, 0xb0, 0xdf, 0x3e, 0xdb,
    /* U+0048 "H" (6x8) */
    0xcf, 0x3c, 0xff, 0xff, 0x3c, 0xf3,
    /* U+0049 "I" (5x8) */
    0xff, 0xcc, 0x63, 0x1b, 0xff,
    /* U+004A "J" (5x8) */
    0xf8, 0xc6, 0x31, 0x8f, 0x7e,
    /* U+004B "K" (6x8) */
    0xcf, 0x7d, 0xbc, 0xfb, 0x6c, 0xf3,
    /* U+004C "L" (6x8) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0f, 0xbf,
    /* U+004D "M" (7x8) */
    0xef, 0xdf, 0xff, 0xfd, 0x7a, 0xf1, 0xe3,
    /* U+004E "N" (6x8) */
    0xef, 0xbe, 0xff, 0xff, 0x7d, 0xf7,
    /* U+004F "O" (7x8) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,
    /* U+0050 "P" (6x8) */
    0xfb, 0x7c, 0xf3, 0xfb, 0x0c, 0x30,
    /* U+0051 "Q" (7x10) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdf, 0x3c, 0x30, 0x38,
    /* U+0052 "R" (6x8) */
    0xfb, 0x7c, 0xf3, 0xfb, 0x6d, 0xb3,
    /* U+0053 "S" (6x8) */
    0x7f, 0xbc, 0x3e, 0x7c, 0x3d, 0xfe,
    /* U+0054 "T" (7x8) */
    0xff, 0xfc, 0xc1, 0x83, 0x06, 0x0c, 0x18,
    /* U+0055 "U" (6x8) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xde,
    /* U+0056 "V" (7x8) */
    0xe7, 0xcd, 0xbb, 0x66, 0xcf, 0x8f, 0x1c,
    /* U+0057 "W" (7x8) */
    0xc7, 0x8f, 0x5f, 0xff, 0xff, 0xfb, 0xf7,
    /* U+0058 "X" (7x8) */
    0xe6, 0xd8, 0xf1, 0xc3, 0x8f, 0x9b, 0x67,
    /* U+0059 "Y" (6x8) */
    0xcf, 0xb7, 0x9e, 0x30, 0xc3, 0x0c,
    /* U+005A "Z" (6x8) */
    0xfc, 0x71, 0x8e, 0x71, 0x8e, 0x3f,
    /* U+005B "[" (5x10) */
    0xff, 0x31, 0x8c, 0x63, 0x18, 0xc7, 0xc0,
    /* U+005C "" (5x10) */
    0xc6, 0x18, 0xc6, 0x18, 0xc3, 0x18, 0xc0,
    /* U+005D "]" (5x10) */
    0xfb, 0xc6, 0x31, 0x8c, 0x63, 0x1f, 0xc0,
    /* U+005E "^" (6x5) */
    0x71, 0xed, 0xa3, 0x88,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x2) */
    0xf0,
    /* U+0061 "a" (6x6) */
    0x78, 0x77, 0xf3, 0xdd, 0xb0,
    /* U+0062 "b" (6x8) */
    0xc3, 0x0f, 0xbf, 0xcf, 0x3f, 0xfe,
    /* U+0063 "c" (6x6) */
    0x7b, 0xbc, 0x30, 0xed, 0xe0,
    /* U+0064 "d" (6x8) */
    0x0c, 0x37, 0xfb, 0xcf, 0x3e, 0xdf,
    /* U+0065 "e" (6x6) */
    0x7b, 0xff, 0xf0, 0xe9, 0xe0,
    /* U+0066 "f" (6x8) */
    0x3c, 0xcf, 0xcc, 0x30, 0xc3, 0x3f,
    /* U+0067 "g" (6x9) */
    0x0d, 0xef, 0xf3, 0x79, 0x07, 0xff, 0xfc,
    /* U+0068 "h" (6x8) */
    0xc3, 0x0d, 0xbf, 0xcf, 0x3c, 0xf3,
    /* U+0069 "i" (6x8) */
    0x30, 0xcf, 0x0c, 0x30, 0xc3, 0x3f,
    /* U+006A "j" (4x10) */
    0x33, 0xf3, 0x33, 0x33, 0x3f,
    /* U+006B "k" (6x8) */
    0xc3, 0x0c, 0xf6, 0xf3, 0xed, 0xf3,
    /* U+006C "l" (6x8) */
    0xf3, 0xc3, 0x0c, 0x30, 0xcf, 0xff,
    /* U+006D "m" (6x6) */
    0xff, 0xff, 0x7d, 0xf7, 0xd0,
    /* U+006E "n" (6x6) */
    0xdb, 0xfc, 0xf3, 0xcf, 0x30,
    /* U+006F "o" (6x6) */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0,
    /* U+0070 "p" (6x8) */
    0xfb, 0xfc, 0xf3, 0xff, 0xec, 0x30,
    /* U+0071 "q" (6x8) */
    0x7f, 0xbc, 0xf3, 0xed, 0xf0, 0xc3,
    /* U+0072 "r" (6x6) */
    0xed, 0xc6, 0x18, 0x63, 0xe0,
    /* U+0073 "s" (5x6) */
    0x7e, 0x7c, 0xfd, 0xfc,
    /* U+0074 "t" (6x8) */
    0x30, 0xcf, 0xcc, 0x30, 0xc3, 0x0f,
    /* U+0075 "u" (6x6) */
    0xcf, 0x3c, 0xf3, 0xfd, 0xb0,
    /* U+0076 "v" (7x6) */
    0xe6, 0xdd, 0xb3, 0x63, 0x87, 0x00,
    /* U+0077 "w" (7x6) */
    0xdb, 0xb7, 0x6f, 0x76, 0xed, 0xc0,
    /* U+0078 "x" (7x6) */
    0x6e, 0xf8, 0xe1, 0xc7, 0xdd, 0xc0,
    /* U+0079 "y" (7x8) */
    0xe6, 0xcd, 0xb1, 0xe3, 0x83, 0x0e, 0x38,
    /* U+007A "z" (6x6) */
    0xfc, 0x73, 0x9c, 0xe3, 0xf0,
    /* U+007B "{" (5x10) */
    0x39, 0x08, 0x63, 0x70, 0xc6, 0x21, 0xc0,
    /* U+007C "|" (2x10) */
    0xff, 0xff, 0xf0,
    /* U+007D "}" (5x10) */
    0xf1, 0x8c, 0xc6, 0x1d, 0x84, 0x37, 0x80,
    /* U+007E "~" (7x3) */
    0x76, 0xff, 0x70,
    /* U+00B0 "" (4x4) */
    0x6b, 0x9e,
    /* U+00B1 "" (6x7) */
    0x30, 0xcf, 0xdc, 0x33, 0xff, 0xc0,
    /* U+00B2 "" (3x4) */
    0xe5, 0x70,
    /* U+00B3 "" (3x4) */
    0xec, 0xf0,
    /* U+00B5 "" (6x8) */
    0xcf, 0x3c, 0xf3, 0xff, 0xfc, 0x30,
    /* U+00B7 "" (3x2) */
    0xfc,
    /* U+00D7 "" (5x5) */
    0xcf, 0xdd, 0xfd, 0x80,
    /* U+00F7 "" (6x6) */
    0x30, 0x0f, 0xc0, 0x00, 0xc0,
    /* U+0394 "" (6x9) */
    0x39, 0xe7, 0x9f, 0x6f, 0xbc, 0xff, 0xfc,
    /* U+03A9 "" (7x9) */
    0x38, 0xfb, 0x9e, 0x3c, 0x78, 0xdb, 0x36, 0xee,
    /* U+03BC "" (6x8) */
    0xcf, 0x3c, 0xf3, 0xff, 0xfc, 0x30,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (7x1) */
    0xfe,
    /* U+2018 "" (3x3) */
    0x6f, 0x00,
    /* U+2019 "" (3x3) */
    0x7f, 0x00,
    /* U+201C "" (7x3) */
    0x26, 0xdb, 0xb0,
    /* U+201D "" (6x3) */
    0xdf, 0x69, 0x80,
    /* U+2022 "" (4x3) */
    0xff, 0xf0,
    /* U+2026 "" (7x1) */
    0xfe,
    /* U+2030 "" (7x8) */
    0xc1, 0xc3, 0x93, 0x86, 0xc9, 0x56, 0x9e,
    /* U+2190 "" (7x5) */
    0x30, 0xe3, 0xfb, 0xf3, 0x00,
    /* U+2191 "" (6x8) */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0c,
    /* U+2192 "" (7x6) */
    0x18, 0x3b, 0xff, 0xf1, 0xc1, 0x00,
    /* U+2193 "" (6x8) */
    0x30, 0xc3, 0x0c, 0x33, 0xf7, 0x8c,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 115, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 19, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 34, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 44, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 54, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 115, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 57, .adv_w = 115, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 65, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 115, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 115, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 136, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 144, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 162, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 268, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 333, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 340, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 347, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 351, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 352, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 353, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 393, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 410, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 443, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 449, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 494, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 506, .adv_w = 115, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 509, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 516, .adv_w = 115, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 519, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 521, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 529, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 531, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 537, .adv_w = 115, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 538, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 542, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 547, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 568, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 569, .adv_w = 115, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 570, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 572, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 574, .adv_w = 115, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 577, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 580, .adv_w = 115, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 582, .adv_w = 115, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 595, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 607, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_bold_12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 8,
    .x_height = 6,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_12,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_BOLD_12 */
