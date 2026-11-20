/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_12 (mono normal)
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

#ifndef HUMID1_FONT_PLEX_MONO_NORMAL_12
#define HUMID1_FONT_PLEX_MONO_NORMAL_12 1
#endif

#if HUMID1_FONT_PLEX_MONO_NORMAL_12

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_12);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x8) */
    0x55, 0x4f,
    /* U+0022 "" (4x3) */
    0xff, 0xf0,
    /* U+0023 "#" (7x8) */
    0x14, 0x49, 0xb9, 0x42, 0x9d, 0xca, 0x24,
    /* U+0024 "$" (6x11) */
    0x20, 0x8f, 0xa8, 0xe3, 0xc2, 0xc9, 0xed, 0xc2, 0x00,
    /* U+0025 "%" (7x8) */
    0xe7, 0xcb, 0xa7, 0x01, 0xca, 0xf4, 0xce,
    /* U+0026 "&" (6x8) */
    0x71, 0x04, 0x1b, 0x9a, 0x69, 0x9b,
    /* U+0027 "'" (2x3) */
    0xfc,
    /* U+0028 "(" (3x10) */
    0x2b, 0x49, 0x26, 0x44,
    /* U+0029 ")" (3x10) */
    0x89, 0x12, 0x4a, 0x50,
    /* U+002A "" (6x5) */
    0x10, 0x4f, 0xce, 0x68,
    /* U+002B "+" (6x6) */
    0x20, 0x82, 0x3f, 0x20, 0x80,
    /* U+002C "," (3x3) */
    0x6b, 0x00,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x10) */
    0x08, 0xc4, 0x22, 0x11, 0x88, 0x44, 0x00,
    /* U+0030 "0" (5x8) */
    0x76, 0xe3, 0x58, 0xc7, 0x6e,
    /* U+0031 "1" (6x8) */
    0x73, 0x49, 0x04, 0x10, 0x41, 0x3f,
    /* U+0032 "2" (6x8) */
    0x72, 0x60, 0x86, 0x10, 0x8c, 0x3f,
    /* U+0033 "3" (5x8) */
    0xf4, 0xc6, 0xe1, 0x86, 0x7e,
    /* U+0034 "4" (6x8) */
    0x18, 0xe6, 0x92, 0x8b, 0xf0, 0x82,
    /* U+0035 "5" (5x8) */
    0xfc, 0x21, 0xe9, 0x86, 0x7e,
    /* U+0036 "6" (6x8) */
    0x31, 0x8c, 0x3e, 0xce, 0x1c, 0xde,
    /* U+0037 "7" (6x8) */
    0xfe, 0x30, 0x86, 0x10, 0xc2, 0x18,
    /* U+0038 "8" (6x8) */
    0x7a, 0x38, 0xde, 0xce, 0x1c, 0xde,
    /* U+0039 "9" (6x8) */
    0x7b, 0x38, 0x73, 0x7c, 0x21, 0x8c,
    /* U+003A ":" (2x6) */
    0xf0, 0xf0,
    /* U+003B ";" (2x7) */
    0xf0, 0xf8,
    /* U+003C "<" (5x7) */
    0x08, 0xd9, 0x86, 0x1c, 0x20,
    /* U+003D "=" (6x3) */
    0xfc, 0x0f, 0xc0,
    /* U+003E ">" (5x7) */
    0x86, 0x0c, 0x33, 0x72, 0x00,
    /* U+003F "?" (5x8) */
    0xf4, 0x42, 0x62, 0x01, 0x8c,
    /* U+0040 "@" (6x9) */
    0x7b, 0x3b, 0xe9, 0xa6, 0x9b, 0xf0, 0x78,
    /* U+0041 "A" (7x8) */
    0x18, 0x70, 0xa1, 0x66, 0xcf, 0x91, 0xe3,
    /* U+0042 "B" (5x8) */
    0xf4, 0x63, 0xe9, 0xc6, 0x7e,
    /* U+0043 "C" (5x8) */
    0x7e, 0x61, 0x08, 0x43, 0x2f,
    /* U+0044 "D" (5x8) */
    0xf4, 0xe3, 0x18, 0xc6, 0x7e,
    /* U+0045 "E" (5x8) */
    0xfc, 0x21, 0xf8, 0x42, 0x1f,
    /* U+0046 "F" (5x8) */
    0xfc, 0x21, 0xf8, 0x42, 0x10,
    /* U+0047 "G" (6x8) */
    0x7b, 0x38, 0x20, 0x9e, 0x1c, 0xdf,
    /* U+0048 "H" (5x8) */
    0x8c, 0x63, 0xf8, 0xc6, 0x31,
    /* U+0049 "I" (5x8) */
    0xf9, 0x08, 0x42, 0x10, 0x9f,
    /* U+004A "J" (5x8) */
    0x78, 0x42, 0x10, 0x86, 0x6e,
    /* U+004B "K" (6x8) */
    0x8a, 0x6b, 0x38, 0xf2, 0x49, 0xa3,
    /* U+004C "L" (5x8) */
    0x84, 0x21, 0x08, 0x42, 0x1f,
    /* U+004D "M" (6x8) */
    0xcf, 0x3f, 0xed, 0xa6, 0x18, 0x61,
    /* U+004E "N" (5x8) */
    0xce, 0x73, 0x5a, 0xde, 0x73,
    /* U+004F "O" (6x8) */
    0x7b, 0x38, 0x61, 0x86, 0x1c, 0xde,
    /* U+0050 "P" (5x8) */
    0xf4, 0x63, 0x3f, 0x42, 0x10,
    /* U+0051 "Q" (6x10) */
    0x7b, 0x38, 0x61, 0x86, 0x1c, 0xde, 0x20, 0xf0,
    /* U+0052 "R" (5x8) */
    0xf4, 0x63, 0x3f, 0x5a, 0x53,
    /* U+0053 "S" (5x8) */
    0x74, 0x61, 0xc3, 0x86, 0x7e,
    /* U+0054 "T" (7x8) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08,
    /* U+0055 "U" (5x8) */
    0x8c, 0x63, 0x18, 0xc6, 0x6e,
    /* U+0056 "V" (7x8) */
    0xc6, 0x89, 0x13, 0x22, 0xc5, 0x0e, 0x0c,
    /* U+0057 "W" (6x8) */
    0x86, 0x1b, 0x6d, 0xb7, 0xdc, 0xf3,
    /* U+0058 "X" (6x8) */
    0x8f, 0x27, 0x0c, 0x71, 0x4c, 0xa3,
    /* U+0059 "Y" (7x8) */
    0xc6, 0x89, 0xb1, 0xc3, 0x02, 0x04, 0x08,
    /* U+005A "Z" (6x8) */
    0xfc, 0x31, 0x84, 0x21, 0x8c, 0x3f,
    /* U+005B "[" (4x10) */
    0xf8, 0x88, 0x88, 0x88, 0x8f,
    /* U+005C "" (5x10) */
    0x82, 0x10, 0xc2, 0x10, 0x42, 0x18, 0x40,
    /* U+005D "]" (4x10) */
    0xf1, 0x11, 0x11, 0x11, 0x1f,
    /* U+005E "^" (5x5) */
    0x32, 0x97, 0x18, 0x00,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x2) */
    0xd0,
    /* U+0061 "a" (6x6) */
    0x72, 0x60, 0xbe, 0x8b, 0xb0,
    /* U+0062 "b" (5x8) */
    0x84, 0x2d, 0x38, 0xc6, 0x76,
    /* U+0063 "c" (5x6) */
    0x76, 0x61, 0x0c, 0xb8,
    /* U+0064 "d" (5x8) */
    0x08, 0x5b, 0x38, 0xc6, 0x2d,
    /* U+0065 "e" (5x6) */
    0x74, 0xff, 0x0c, 0xb8,
    /* U+0066 "f" (6x8) */
    0x3c, 0x8f, 0xc8, 0x20, 0x82, 0x3f,
    /* U+0067 "g" (6x9) */
    0x0d, 0xc8, 0xa2, 0x72, 0x0f, 0xa3, 0xf8,
    /* U+0068 "h" (5x8) */
    0x84, 0x2d, 0x38, 0xc6, 0x31,
    /* U+0069 "i" (5x8) */
    0x20, 0x38, 0x42, 0x10, 0x9f,
    /* U+006A "j" (4x10) */
    0x10, 0xf1, 0x11, 0x11, 0x1f,
    /* U+006B "k" (5x8) */
    0x84, 0x27, 0x6e, 0x7a, 0x71,
    /* U+006C "l" (5x8) */
    0xe1, 0x08, 0x42, 0x10, 0x9f,
    /* U+006D "m" (5x6) */
    0xff, 0xeb, 0x5a, 0xd4,
    /* U+006E "n" (5x6) */
    0xb4, 0xe3, 0x18, 0xc4,
    /* U+006F "o" (6x6) */
    0x7b, 0x38, 0x61, 0xcd, 0xe0,
    /* U+0070 "p" (5x8) */
    0xb4, 0xe3, 0x19, 0xda, 0x10,
    /* U+0071 "q" (5x8) */
    0x6c, 0xe3, 0x18, 0xb4, 0x21,
    /* U+0072 "r" (6x6) */
    0xec, 0x82, 0x08, 0x23, 0xe0,
    /* U+0073 "s" (5x6) */
    0x74, 0x30, 0x38, 0xf8,
    /* U+0074 "t" (6x8) */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x0f,
    /* U+0075 "u" (5x6) */
    0x8c, 0x63, 0x1d, 0xfc,
    /* U+0076 "v" (5x6) */
    0x8c, 0x76, 0xa7, 0x18,
    /* U+0077 "w" (7x6) */
    0x93, 0xb5, 0x2b, 0x66, 0xcd, 0x80,
    /* U+0078 "x" (5x6) */
    0x8a, 0x8c, 0xe5, 0x44,
    /* U+0079 "y" (6x8) */
    0x8f, 0x25, 0x94, 0x30, 0x82, 0x30,
    /* U+007A "z" (5x6) */
    0xf8, 0xcc, 0xcc, 0x7c,
    /* U+007B "{" (5x10) */
    0x39, 0x08, 0x61, 0x70, 0x46, 0x21, 0xc0,
    /* U+007C "|" (2x10) */
    0xff, 0xff, 0xf0,
    /* U+007D "}" (5x10) */
    0xe1, 0x08, 0x84, 0x1d, 0x0c, 0x27, 0x00,
    /* U+007E "~" (5x3) */
    0xc5, 0x46,
    /* U+00B0 "" (4x4) */
    0x69, 0x96,
    /* U+00B1 "" (6x7) */
    0x20, 0x8f, 0xc8, 0x20, 0x0f, 0xc0,
    /* U+00B2 "" (3x4) */
    0xe5, 0x70,
    /* U+00B3 "" (3x4) */
    0xec, 0xf0,
    /* U+00B5 "" (5x8) */
    0x8c, 0x63, 0x1d, 0xfe, 0x10,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x5) */
    0x8a, 0x8c, 0xe8, 0x80,
    /* U+00F7 "" (6x6) */
    0x20, 0x0f, 0xc0, 0x00, 0x80,
    /* U+0394 "" (6x9) */
    0x30, 0xc7, 0x9a, 0x49, 0x3c, 0xf1, 0xfc,
    /* U+03A9 "" (6x9) */
    0x79, 0x38, 0x61, 0x86, 0x1c, 0xde, 0xfc,
    /* U+03BC "" (5x8) */
    0x8c, 0x63, 0x1d, 0xfe, 0x10,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (7x1) */
    0xfe,
    /* U+2018 "" (3x3) */
    0x6b, 0x00,
    /* U+2019 "" (2x3) */
    0xe8,
    /* U+201C "" (5x3) */
    0x4e, 0xf6,
    /* U+201D "" (5x3) */
    0x4e, 0xe4,
    /* U+2022 "" (3x3) */
    0xff, 0x80,
    /* U+2026 "" (5x2) */
    0xad, 0x40,
    /* U+2030 "" (7x8) */
    0xe1, 0x43, 0xb3, 0x03, 0x69, 0x52, 0x9b,
    /* U+2190 "" (7x5) */
    0x20, 0xc3, 0xfb, 0x02, 0x00,
    /* U+2191 "" (5x8) */
    0x77, 0xea, 0x42, 0x10, 0x84,
    /* U+2192 "" (7x5) */
    0x08, 0x1b, 0xf8, 0x60, 0x80,
    /* U+2193 "" (5x8) */
    0x21, 0x08, 0x42, 0x55, 0xc4,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 115, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 115, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 34, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 115, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 54, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 115, .box_w = 2, .box_h = 6, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 115, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 123, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 131, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 148, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 242, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 301, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 308, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 313, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 317, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 318, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 319, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 355, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 370, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 398, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 403, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 442, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 453, .adv_w = 115, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 456, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 463, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 465, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 467, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 475, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 477, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 482, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 483, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 487, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 492, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 511, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 512, .adv_w = 115, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 513, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 515, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 516, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 518, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 520, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 522, .adv_w = 115, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 536, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 546, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_normal_12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 8,
    .x_height = 6,
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

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_12 */
