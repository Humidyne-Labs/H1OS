/*******************************************************************************
 * Font: humid1_font_plex_mono_bold_14 (mono bold)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_bold_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_MONO_BOLD_14
#define HUMID1_FONT_PLEX_MONO_BOLD_14 1
#endif

#if HUMID1_FONT_PLEX_MONO_BOLD_14

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_bold_14);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x10) */
    0xff, 0xec, 0x86, 0xf8,
    /* U+0022 "" (6x5) */
    0xef, 0xbe, 0xfb, 0xec,
    /* U+0023 "#" (8x10) */
    0x1e, 0x16, 0x36, 0x77, 0x77, 0x36, 0xef, 0xee, 0x6c, 0x6c,
    /* U+0024 "$" (7x12) */
    0x30, 0xfb, 0xf6, 0x8f, 0x1f, 0x9f, 0x8f, 0x97, 0xfd, 0xe1, 0x80,
    /* U+0025 "%" (8x10) */
    0x73, 0xf3, 0xde, 0xfe, 0x70, 0x07, 0x3f, 0x6d, 0x6f, 0xc7,
    /* U+0026 "&" (8x10) */
    0x38, 0x7c, 0x60, 0x60, 0x33, 0x7f, 0xde, 0xce, 0xfe, 0x73,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x13) */
    0x19, 0x98, 0xcc, 0x63, 0x18, 0xc3, 0x18, 0x61, 0x80,
    /* U+0029 ")" (5x13) */
    0xe3, 0x8c, 0x31, 0x8c, 0x63, 0x18, 0xcc, 0xee, 0x00,
    /* U+002A "" (7x7) */
    0x30, 0x63, 0xff, 0xe7, 0x9f, 0x93, 0x00,
    /* U+002B "+" (7x6) */
    0x30, 0x63, 0xff, 0xe3, 0x06, 0x00,
    /* U+002C "," (4x5) */
    0x76, 0x6e, 0xc0,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (6x13) */
    0x0c, 0x31, 0xc6, 0x18, 0xe3, 0x0c, 0x71, 0x86, 0x38, 0xc0,
    /* U+0030 "0" (8x10) */
    0x3c, 0x7e, 0x67, 0xe3, 0xfb, 0xeb, 0xe3, 0x67, 0x7e, 0x3c,
    /* U+0031 "1" (7x10) */
    0x78, 0xf3, 0x66, 0xc1, 0x83, 0x06, 0x0c, 0x7f, 0xfc,
    /* U+0032 "2" (7x10) */
    0x79, 0xfb, 0x38, 0x70, 0xc3, 0x9c, 0x70, 0xff, 0xfc,
    /* U+0033 "3" (7x10) */
    0x79, 0xfa, 0x38, 0x73, 0xc7, 0x83, 0xe7, 0xfe, 0xf0,
    /* U+0034 "4" (8x10) */
    0x0e, 0x1e, 0x3e, 0x36, 0x66, 0x66, 0xff, 0xff, 0x06, 0x06,
    /* U+0035 "5" (7x10) */
    0xfd, 0xfb, 0x06, 0xef, 0xe9, 0xc1, 0xe7, 0xfc, 0xf0,
    /* U+0036 "6" (8x10) */
    0x1e, 0x38, 0x70, 0x7e, 0x7f, 0xe7, 0xe3, 0x67, 0x7e, 0x3c,
    /* U+0037 "7" (7x10) */
    0xff, 0xff, 0x3c, 0x61, 0xc3, 0x86, 0x1c, 0x30, 0xe0,
    /* U+0038 "8" (8x10) */
    0x3c, 0x7e, 0x67, 0x67, 0x7e, 0x7e, 0x67, 0xe7, 0x7f, 0x3e,
    /* U+0039 "9" (8x10) */
    0x3c, 0x7e, 0xe7, 0xe7, 0xe7, 0x7f, 0x3e, 0x0e, 0x1c, 0x38,
    /* U+003A ":" (3x8) */
    0xff, 0x81, 0xff,
    /* U+003B ";" (4x10) */
    0x67, 0x60, 0x07, 0x66, 0xec,
    /* U+003C "<" (6x8) */
    0x04, 0x77, 0xb8, 0xe1, 0xe1, 0xc1,
    /* U+003D "=" (7x5) */
    0xff, 0xf8, 0x07, 0xff, 0xc0,
    /* U+003E ">" (6x8) */
    0x83, 0x87, 0x87, 0x1d, 0xee, 0x20,
    /* U+003F "?" (6x10) */
    0x7b, 0xf4, 0xc3, 0x3c, 0xc0, 0x0c, 0x70, 0xc0,
    /* U+0040 "@" (8x12) */
    0x3c, 0x76, 0x63, 0x4f, 0xdb, 0xdb, 0xdb, 0xdb, 0x4f, 0x60, 0x70, 0x1c,
    /* U+0041 "A" (8x10) */
    0x3c, 0x3c, 0x3e, 0x3e, 0x76, 0x66, 0x7f, 0x7f, 0xe7, 0xe3,
    /* U+0042 "B" (7x10) */
    0xf9, 0xfb, 0x3e, 0x7f, 0xdf, 0xb3, 0xe7, 0xff, 0xf8,
    /* U+0043 "C" (8x10) */
    0x3c, 0x7e, 0x67, 0x60, 0xe0, 0xe0, 0x60, 0x67, 0x7e, 0x3c,
    /* U+0044 "D" (7x10) */
    0xf9, 0xfb, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7, 0xfd, 0xf0,
    /* U+0045 "E" (6x10) */
    0xff, 0xfe, 0x38, 0xff, 0xfe, 0x38, 0xff, 0xf0,
    /* U+0046 "F" (7x10) */
    0xff, 0xfb, 0x06, 0x0f, 0xdf, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0047 "G" (8x10) */
    0x3c, 0x7e, 0x67, 0xe0, 0xee, 0xef, 0xe3, 0x67, 0x7f, 0x3b,
    /* U+0048 "H" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7f, 0xff, 0xf3, 0xe7, 0xcf, 0x9c,
    /* U+0049 "I" (7x10) */
    0xff, 0xf8, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0xfd, 0xfc,
    /* U+004A "J" (7x10) */
    0x3e, 0x7c, 0x18, 0x30, 0x60, 0xc1, 0xf3, 0x7e, 0x78,
    /* U+004B "K" (7x10) */
    0xcf, 0x9b, 0x77, 0xcf, 0x9f, 0x3f, 0x66, 0xcf, 0x8c,
    /* U+004C "L" (7x10) */
    0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xfd, 0xfc,
    /* U+004D "M" (8x10) */
    0xf7, 0xf7, 0xff, 0xff, 0xff, 0xfb, 0xeb, 0xe3, 0xe3, 0xe3,
    /* U+004E "N" (7x10) */
    0xe7, 0xcf, 0x9f, 0xbf, 0x7b, 0xf7, 0xef, 0xdf, 0x9c,
    /* U+004F "O" (8x10) */
    0x3c, 0x7e, 0x67, 0xe7, 0xe3, 0xe3, 0xe7, 0x67, 0x7e, 0x3c,
    /* U+0050 "P" (7x10) */
    0xfd, 0xff, 0xbf, 0x7f, 0xff, 0xb8, 0x70, 0xe1, 0xc0,
    /* U+0051 "Q" (8x13) */
    0x3c, 0x7e, 0x67, 0xe7, 0xe3, 0xe3, 0xe3, 0x67, 0x7e, 0x3c, 0x18, 0x1e,
    0x0f,
    /* U+0052 "R" (7x10) */
    0xfd, 0xff, 0xbf, 0x7f, 0xff, 0xbf, 0x76, 0xef, 0xdc,
    /* U+0053 "S" (7x10) */
    0x7d, 0xfb, 0x07, 0x0f, 0xcf, 0xc3, 0xc7, 0xfc, 0xf0,
    /* U+0054 "T" (8x10) */
    0xff, 0xff, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    /* U+0055 "U" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7, 0xfc, 0xf0,
    /* U+0056 "V" (8x10) */
    0xe3, 0xe7, 0x67, 0x67, 0x76, 0x76, 0x3e, 0x3e, 0x3c, 0x3c,
    /* U+0057 "W" (8x10) */
    0xc3, 0xc3, 0xdb, 0xdb, 0xdf, 0xff, 0xff, 0xf7, 0xf7, 0x77,
    /* U+0058 "X" (8x10) */
    0xe7, 0x76, 0x7e, 0x3c, 0x3c, 0x3c, 0x3e, 0x7e, 0x67, 0xe7,
    /* U+0059 "Y" (8x10) */
    0xe3, 0x67, 0x76, 0x3e, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x10) */
    0xff, 0xfc, 0x70, 0xe3, 0x8e, 0x1c, 0x70, 0xff, 0xfc,
    /* U+005B "[" (5x13) */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xff, 0x80,
    /* U+005C "" (6x13) */
    0xc3, 0x86, 0x18, 0x70, 0xc3, 0x0e, 0x18, 0x61, 0xc3, 0x0c,
    /* U+005D "]" (5x13) */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x80,
    /* U+005E "^" (8x6) */
    0x1c, 0x3c, 0x3e, 0x66, 0x67, 0xe3,
    /* U+005F "_" (7x2) */
    0xff, 0xf8,
    /* U+0060 "`" (3x3) */
    0xcd, 0x80,
    /* U+0061 "a" (7x7) */
    0x79, 0xf8, 0x33, 0xec, 0xdf, 0xf9, 0x80,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x06, 0xef, 0xf9, 0xf3, 0xe7, 0xff, 0xb8,
    /* U+0063 "c" (7x7) */
    0x79, 0xfb, 0x06, 0x0c, 0x1f, 0xde, 0x00,
    /* U+0064 "d" (8x10) */
    0x07, 0x07, 0x07, 0x37, 0x7f, 0x67, 0xe7, 0x67, 0x7f, 0x37,
    /* U+0065 "e" (7x7) */
    0x79, 0xfb, 0x3f, 0xfc, 0x1f, 0x9f, 0x00,
    /* U+0066 "f" (7x10) */
    0x1e, 0x7c, 0xc7, 0xff, 0xe6, 0x0c, 0x18, 0xfd, 0xfc,
    /* U+0067 "g" (7x12) */
    0x04, 0x1d, 0xe7, 0xec, 0xdd, 0x9e, 0x7e, 0xff, 0x8f, 0x3f, 0xe0,
    /* U+0068 "h" (7x10) */
    0xc1, 0x83, 0x06, 0xef, 0xf9, 0xf3, 0xe7, 0xcf, 0x9c,
    /* U+0069 "i" (7x10) */
    0x38, 0x30, 0x07, 0xc7, 0x87, 0x0e, 0x1c, 0x7f, 0xfc,
    /* U+006A "j" (5x13) */
    0x18, 0xc1, 0xff, 0x8c, 0x63, 0x18, 0xc7, 0xff, 0x00,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x06, 0x7d, 0xdf, 0x3e, 0x6e, 0xdd, 0x9c,
    /* U+006C "l" (7x10) */
    0xf9, 0xf0, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0xff, 0xfc,
    /* U+006D "m" (8x7) */
    0xdb, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (7x7) */
    0xdd, 0xff, 0x3e, 0x7c, 0xf9, 0xf3, 0x80,
    /* U+006F "o" (8x7) */
    0x3c, 0x7e, 0x67, 0xe7, 0x67, 0x7e, 0x3c,
    /* U+0070 "p" (7x10) */
    0xdd, 0xff, 0x3e, 0x7c, 0xff, 0xf7, 0x60, 0xc1, 0x80,
    /* U+0071 "q" (8x10) */
    0x37, 0x7f, 0x67, 0xe7, 0x67, 0x7f, 0x37, 0x07, 0x07, 0x07,
    /* U+0072 "r" (7x7) */
    0xf7, 0xfd, 0xc3, 0x87, 0x1f, 0x3f, 0x00,
    /* U+0073 "s" (7x7) */
    0x7d, 0xfb, 0x87, 0xe0, 0xff, 0x9e, 0x00,
    /* U+0074 "t" (6x10) */
    0x30, 0xc7, 0x3f, 0xfd, 0xc7, 0x1c, 0x7c, 0xf0,
    /* U+0075 "u" (7x7) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xdb, 0x80,
    /* U+0076 "v" (8x7) */
    0xe3, 0x67, 0x76, 0x76, 0x3e, 0x3c, 0x1c,
    /* U+0077 "w" (8x7) */
    0xdb, 0xdb, 0xdf, 0xdf, 0xf7, 0x77, 0x77,
    /* U+0078 "x" (8x7) */
    0x67, 0x76, 0x3c, 0x1c, 0x3c, 0x76, 0xe7,
    /* U+0079 "y" (8x10) */
    0xe3, 0x67, 0x76, 0x76, 0x3e, 0x3c, 0x1c, 0x18, 0x78, 0x70,
    /* U+007A "z" (7x7) */
    0xff, 0xfc, 0x73, 0xcf, 0x1f, 0xff, 0x80,
    /* U+007B "{" (6x13) */
    0x3c, 0xc3, 0x0c, 0x18, 0xef, 0x06, 0x18, 0xc3, 0x0c, 0x3c,
    /* U+007C "|" (2x13) */
    0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (6x13) */
    0xf0, 0xe1, 0x8c, 0x30, 0xe3, 0xcc, 0x30, 0xc1, 0x8e, 0xf0,
    /* U+007E "~" (7x4) */
    0x67, 0xee, 0xfc, 0xe0,
    /* U+00B0 "" (6x5) */
    0x39, 0xbc, 0xdb, 0x38,
    /* U+00B1 "" (7x9) */
    0x30, 0x63, 0xff, 0xe3, 0x06, 0x00, 0x7e, 0xfe,
    /* U+00B2 "" (4x5) */
    0x7f, 0x36, 0xf0,
    /* U+00B3 "" (4x5) */
    0xf7, 0x7f, 0xf0,
    /* U+00B5 "" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xff, 0xe0, 0xc1, 0x80,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (6x7) */
    0x47, 0xb7, 0xce, 0x7f, 0xb4, 0x40,
    /* U+00F7 "" (7x8) */
    0x30, 0x70, 0x07, 0xff, 0xc0, 0x0e, 0x18,
    /* U+0394 "" (8x10) */
    0x3c, 0x3c, 0x3e, 0x3e, 0x76, 0x76, 0x67, 0x67, 0xff, 0xff,
    /* U+03A9 "" (8x10) */
    0x3c, 0x7e, 0x67, 0xe7, 0xe7, 0xe7, 0x67, 0x76, 0x77, 0xf7,
    /* U+03BC "" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xff, 0xe0, 0xc1, 0x80,
    /* U+2013 "" (7x2) */
    0xff, 0xf8,
    /* U+2014 "" (8x2) */
    0xff, 0xff,
    /* U+2018 "" (4x5) */
    0x37, 0x76, 0xe0,
    /* U+2019 "" (3x5) */
    0xff, 0x68,
    /* U+201C "" (8x5) */
    0x33, 0x37, 0x76, 0x66, 0xee,
    /* U+201D "" (7x5) */
    0xef, 0xdf, 0x36, 0x6d, 0x80,
    /* U+2022 "" (5x4) */
    0xf7, 0xff, 0xe0,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (8x10) */
    0x70, 0xf0, 0xf0, 0x72, 0x1c, 0x60, 0x3f, 0x2d, 0x2d, 0x3f,
    /* U+2190 "" (7x6) */
    0x30, 0xc3, 0xff, 0xf6, 0x04, 0x00,
    /* U+2191 "" (6x10) */
    0x10, 0xe7, 0xff, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (8x6) */
    0x0c, 0x0e, 0xff, 0xff, 0x0e, 0x0c,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xcf, 0xdf, 0x38, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 8, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 134, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 51, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 60, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 76, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 82, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 134, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 87, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 99, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 134, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 134, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 202, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 213, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 239, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 400, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 495, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 505, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 514, .adv_w = 134, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 520, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 522, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 524, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 584, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 659, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 669, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 729, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 746, .adv_w = 134, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 750, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 760, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 764, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 768, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 779, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 782, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 791, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 793, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 799, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 816, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 835, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 837, .adv_w = 134, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 839, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 842, .adv_w = 134, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 844, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 849, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 854, .adv_w = 134, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 857, .adv_w = 134, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 875, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 134, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 889, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_bold_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 7,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_BOLD_14 */
