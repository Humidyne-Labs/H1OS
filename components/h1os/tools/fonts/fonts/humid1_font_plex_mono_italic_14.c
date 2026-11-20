/*******************************************************************************
 * Font: humid1_font_plex_mono_italic_14 (mono italic)
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

#ifndef HUMID1_FONT_PLEX_MONO_ITALIC_14
#define HUMID1_FONT_PLEX_MONO_ITALIC_14 1
#endif

#if HUMID1_FONT_PLEX_MONO_ITALIC_14

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
    0x6d, 0xa4, 0x86, 0xd8,
    /* U+0022 "" (6x4) */
    0x6d, 0xa5, 0xb6,
    /* U+0023 "#" (9x10) */
    0x09, 0x05, 0x86, 0x8e, 0x73, 0x61, 0xa3, 0x9c, 0x58, 0x68, 0x24, 0x00,
    /* U+0024 "$" (7x12) */
    0x08, 0x7d, 0xfe, 0xcd, 0x0f, 0x07, 0x0b, 0x37, 0x7b, 0xe1, 0x00,
    /* U+0025 "%" (9x10) */
    0x38, 0xa4, 0x92, 0xcb, 0xc7, 0x00, 0x30, 0xa4, 0xd2, 0x4b, 0x47, 0x00,
    /* U+0026 "&" (8x10) */
    0x0e, 0x12, 0x32, 0x32, 0x14, 0x58, 0xc8, 0xcc, 0xcd, 0x66,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (5x13) */
    0x19, 0x98, 0x8c, 0x42, 0x10, 0x84, 0x31, 0x86, 0x00,
    /* U+0029 ")" (5x13) */
    0x30, 0x86, 0x30, 0x84, 0x63, 0x18, 0x8c, 0xcc, 0x00,
    /* U+002A "" (7x7) */
    0x18, 0x23, 0xff, 0xe7, 0x8f, 0x32, 0x00,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf3, 0x06, 0x08, 0x00,
    /* U+002C "," (3x4) */
    0x7f, 0x40,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (3x3) */
    0x7d, 0x80,
    /* U+002F "/" (8x13) */
    0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60,
    0xc0,
    /* U+0030 "0" (7x10) */
    0x3c, 0xcf, 0x1e, 0x3d, 0x7a, 0xe1, 0xc2, 0xcc, 0xf0,
    /* U+0031 "1" (7x10) */
    0x3c, 0xf9, 0x66, 0xc1, 0x83, 0x06, 0x0c, 0x11, 0xfc,
    /* U+0032 "2" (8x10) */
    0x1e, 0x33, 0x03, 0x03, 0x06, 0x04, 0x18, 0x30, 0x60, 0xfe,
    /* U+0033 "3" (7x10) */
    0x7c, 0x8c, 0x18, 0x63, 0x81, 0x83, 0x06, 0x8d, 0xf0,
    /* U+0034 "4" (8x10) */
    0x07, 0x0e, 0x1e, 0x16, 0x36, 0x66, 0xc6, 0xff, 0x04, 0x0c,
    /* U+0035 "5" (7x10) */
    0x7e, 0x81, 0x02, 0x0d, 0xd9, 0xc1, 0x83, 0xcd, 0xf0,
    /* U+0036 "6" (7x10) */
    0x1c, 0x71, 0xc3, 0x0f, 0xd9, 0xf1, 0xe3, 0xcc, 0xf0,
    /* U+0037 "7" (7x10) */
    0x7f, 0x8f, 0x18, 0x60, 0xc3, 0x06, 0x18, 0x60, 0xc0,
    /* U+0038 "8" (8x10) */
    0x1e, 0x33, 0x23, 0x23, 0x3e, 0x66, 0x43, 0xc3, 0x66, 0x3c,
    /* U+0039 "9" (7x10) */
    0x3c, 0xcf, 0x1e, 0x3c, 0x6f, 0xc3, 0x0c, 0x38, 0xc0,
    /* U+003A ":" (3x8) */
    0x7f, 0x01, 0xb6,
    /* U+003B ";" (4x10) */
    0x37, 0x60, 0x00, 0x64, 0xc8,
    /* U+003C "<" (7x8) */
    0x02, 0x1c, 0xe7, 0x0e, 0x0e, 0x07, 0x02,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xe0,
    /* U+003E ">" (6x8) */
    0x41, 0xc3, 0x83, 0x0c, 0xee, 0x20,
    /* U+003F "?" (6x10) */
    0x7b, 0x30, 0xc6, 0x71, 0x80, 0x18, 0xe3, 0x00,
    /* U+0040 "@" (7x12) */
    0x3c, 0xcd, 0x0e, 0xfb, 0x76, 0xe9, 0xd2, 0xbd, 0x03, 0x03, 0xc0,
    /* U+0041 "A" (8x10) */
    0x0e, 0x1e, 0x1e, 0x36, 0x36, 0x26, 0x7e, 0x42, 0xc2, 0xc3,
    /* U+0042 "B" (7x10) */
    0x7c, 0xcd, 0x1a, 0x3f, 0x99, 0xb1, 0xe2, 0xcd, 0xf0,
    /* U+0043 "C" (7x10) */
    0x3c, 0xcd, 0x06, 0x0c, 0x18, 0x30, 0x62, 0xcc, 0xf0,
    /* U+0044 "D" (7x10) */
    0x7c, 0xcd, 0x1a, 0x3c, 0x78, 0xf1, 0xe2, 0xcd, 0xf0,
    /* U+0045 "E" (7x10) */
    0x7e, 0xc1, 0x82, 0x0f, 0xd8, 0x30, 0x60, 0xc1, 0xf8,
    /* U+0046 "F" (7x10) */
    0x7e, 0xc1, 0x82, 0x0f, 0xd8, 0x30, 0x60, 0xc1, 0x00,
    /* U+0047 "G" (7x10) */
    0x3c, 0xcd, 0x06, 0x0c, 0x1b, 0xf1, 0xe2, 0xcc, 0xf8,
    /* U+0048 "H" (8x10) */
    0x31, 0x33, 0x23, 0x63, 0x7f, 0x63, 0x62, 0x66, 0x46, 0xc6,
    /* U+0049 "I" (7x10) */
    0x7e, 0x30, 0x60, 0xc1, 0x06, 0x0c, 0x18, 0x31, 0xf8,
    /* U+004A "J" (7x10) */
    0x3e, 0x0c, 0x18, 0x20, 0xc1, 0x83, 0x06, 0xc9, 0xe0,
    /* U+004B "K" (8x10) */
    0x63, 0x66, 0x4c, 0x58, 0xf8, 0xf8, 0xd8, 0xcc, 0x8c, 0x86,
    /* U+004C "L" (6x10) */
    0x61, 0x86, 0x18, 0x61, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+004D "M" (9x10) */
    0x33, 0xb9, 0xdd, 0xcf, 0xe7, 0xf2, 0xd9, 0x2d, 0x86, 0xc2, 0x61, 0x00,
    /* U+004E "N" (8x10) */
    0x31, 0x39, 0x39, 0x7b, 0x6b, 0x6b, 0x6e, 0x4e, 0x4e, 0xc6,
    /* U+004F "O" (7x10) */
    0x3c, 0xcf, 0x1e, 0x3c, 0x78, 0xe1, 0xc2, 0xcc, 0xf0,
    /* U+0050 "P" (7x10) */
    0x7c, 0xcd, 0x9a, 0x3c, 0x7f, 0xb0, 0x60, 0xc1, 0x00,
    /* U+0051 "Q" (7x13) */
    0x3c, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe2, 0xcc, 0xf0, 0xc0, 0xf0, 0xc0,
    /* U+0052 "R" (7x10) */
    0x7c, 0xcd, 0x9a, 0x3c, 0x7f, 0xb6, 0x64, 0xcd, 0x18,
    /* U+0053 "S" (7x10) */
    0x3c, 0xcd, 0x02, 0x07, 0x01, 0x81, 0x82, 0x8d, 0xf0,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    /* U+0055 "U" (7x10) */
    0x62, 0x87, 0x1e, 0x3c, 0x78, 0xf1, 0x62, 0xcc, 0xf0,
    /* U+0056 "V" (8x10) */
    0xc3, 0xc3, 0x46, 0x46, 0x6c, 0x6c, 0x68, 0x78, 0x78, 0x70,
    /* U+0057 "W" (9x10) */
    0x60, 0xb0, 0xdb, 0x69, 0xa5, 0xd2, 0xb9, 0x5c, 0xcc, 0xe6, 0x73, 0x00,
    /* U+0058 "X" (9x10) */
    0x31, 0x99, 0x8d, 0x83, 0xc1, 0xc0, 0xe0, 0xf0, 0xcc, 0x66, 0x63, 0x00,
    /* U+0059 "Y" (8x10) */
    0xc3, 0x66, 0x64, 0x6c, 0x38, 0x30, 0x30, 0x30, 0x30, 0x30,
    /* U+005A "Z" (8x10) */
    0x3f, 0x03, 0x06, 0x0e, 0x0c, 0x18, 0x30, 0x70, 0x60, 0xfe,
    /* U+005B "[" (6x13) */
    0x3c, 0x82, 0x18, 0x61, 0x04, 0x10, 0x43, 0x0c, 0x30, 0xf0,
    /* U+005C "" (4x13) */
    0xc4, 0x44, 0x66, 0x22, 0x23, 0x31, 0x10,
    /* U+005D "]" (7x13) */
    0x3e, 0x0c, 0x10, 0x20, 0x41, 0x83, 0x06, 0x08, 0x10, 0x20, 0xcf, 0x80,
    /* U+005E "^" (7x6) */
    0x18, 0x78, 0xb3, 0x2c, 0x70, 0xc0,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xf4,
    /* U+0061 "a" (7x7) */
    0x77, 0x9f, 0x16, 0x68, 0xdb, 0xbb, 0x80,
    /* U+0062 "b" (7x10) */
    0x60, 0xc1, 0x02, 0xee, 0x78, 0xf1, 0xe2, 0xcd, 0x70,
    /* U+0063 "c" (6x7) */
    0x3d, 0x9c, 0x30, 0xc3, 0x37, 0x80,
    /* U+0064 "d" (7x10) */
    0x02, 0x0c, 0x1b, 0xbc, 0x78, 0xf1, 0x46, 0xcd, 0xd8,
    /* U+0065 "e" (7x7) */
    0x3c, 0xcf, 0x37, 0xcc, 0x19, 0x9e, 0x00,
    /* U+0066 "f" (9x13) */
    0x07, 0x86, 0x03, 0x07, 0xe0, 0xc0, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x26,
    0x1a, 0x07, 0x00,
    /* U+0067 "g" (7x10) */
    0x77, 0x8f, 0x1e, 0x28, 0xd9, 0xbb, 0x06, 0x99, 0xe0,
    /* U+0068 "h" (7x10) */
    0x60, 0xc1, 0x82, 0xee, 0x58, 0xf1, 0x66, 0x8d, 0x18,
    /* U+0069 "i" (6x10) */
    0x18, 0x60, 0x3c, 0x30, 0xc3, 0x09, 0x2c, 0xc0,
    /* U+006A "j" (6x13) */
    0x0c, 0x30, 0x1f, 0x08, 0x61, 0x86, 0x18, 0x69, 0x3c, 0x70,
    /* U+006B "k" (7x10) */
    0x60, 0xc1, 0x82, 0xee, 0x78, 0xb7, 0x78, 0xdf, 0x38,
    /* U+006C "l" (6x10) */
    0xf0, 0x43, 0x0c, 0x30, 0x82, 0x19, 0x68, 0xc0,
    /* U+006D "m" (8x7) */
    0x7b, 0x49, 0x49, 0x5b, 0xdb, 0xdb, 0x92,
    /* U+006E "n" (7x7) */
    0x5d, 0x8b, 0x1e, 0x2c, 0xd1, 0xa3, 0x00,
    /* U+006F "o" (7x7) */
    0x38, 0x8b, 0x1e, 0x38, 0x59, 0x9e, 0x00,
    /* U+0070 "p" (8x10) */
    0x2e, 0x73, 0x63, 0x63, 0x62, 0x66, 0x5c, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x10) */
    0x77, 0x8f, 0x1e, 0x28, 0xd9, 0xbb, 0x06, 0x0c, 0x10,
    /* U+0072 "r" (6x7) */
    0xed, 0x86, 0x10, 0x43, 0x0c, 0x00,
    /* U+0073 "s" (6x7) */
    0x3d, 0x16, 0x1e, 0x0e, 0x3f, 0x80,
    /* U+0074 "t" (7x10) */
    0x10, 0x60, 0xc7, 0xf3, 0x04, 0x18, 0x32, 0x6c, 0x60,
    /* U+0075 "u" (7x7) */
    0x47, 0x8f, 0x16, 0x2c, 0xd9, 0xbb, 0x00,
    /* U+0076 "v" (7x7) */
    0xe4, 0xcd, 0x9a, 0x2c, 0xdb, 0x1c, 0x00,
    /* U+0077 "w" (8x7) */
    0x69, 0x49, 0x49, 0x59, 0xdb, 0xda, 0x68,
    /* U+0078 "x" (8x7) */
    0x33, 0x5d, 0x18, 0x18, 0x18, 0xdb, 0xee,
    /* U+0079 "y" (7x10) */
    0x47, 0x8f, 0x16, 0x2c, 0xd9, 0x9b, 0x06, 0x19, 0xe0,
    /* U+007A "z" (8x7) */
    0x3b, 0x67, 0x0c, 0x18, 0x32, 0x72, 0xde,
    /* U+007B "{" (6x13) */
    0x1c, 0x82, 0x0c, 0x30, 0xce, 0x08, 0x21, 0x84, 0x30, 0x70,
    /* U+007C "|" (3x13) */
    0x2d, 0xb4, 0x96, 0xda, 0x48,
    /* U+007D "}" (7x13) */
    0x3c, 0x08, 0x10, 0x61, 0x83, 0x03, 0x88, 0x10, 0x30, 0x60, 0xcf, 0x00,
    /* U+007E "~" (7x3) */
    0x63, 0x6e, 0x70,
    /* U+00B0 "" (5x5) */
    0x3a, 0x73, 0x97, 0x00,
    /* U+00B1 "" (8x8) */
    0x0c, 0x0c, 0x7f, 0x08, 0x18, 0x18, 0x00, 0xfe,
    /* U+00B2 "" (4x5) */
    0x63, 0x2c, 0xe0,
    /* U+00B3 "" (4x5) */
    0x63, 0x62, 0xe0,
    /* U+00B5 "" (8x10) */
    0x23, 0x63, 0x63, 0x62, 0x66, 0x66, 0x7e, 0xc0, 0xc0, 0xc0,
    /* U+00B7 "" (3x3) */
    0x5f, 0x00,
    /* U+00D7 "" (6x6) */
    0x45, 0xb3, 0x8e, 0x7b, 0x30,
    /* U+00F7 "" (7x7) */
    0x18, 0x30, 0x07, 0xf0, 0x06, 0x0c, 0x00,
    /* U+0394 "" (7x10) */
    0x0e, 0x3c, 0x79, 0xb3, 0x64, 0xd9, 0xb3, 0xc3, 0xfc,
    /* U+03A9 "" (8x10) */
    0x1e, 0x33, 0x63, 0x63, 0x63, 0x63, 0x63, 0x66, 0x2c, 0xee,
    /* U+03BC "" (8x10) */
    0x23, 0x63, 0x63, 0x62, 0x66, 0x66, 0x7e, 0xc0, 0xc0, 0xc0,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (3x4) */
    0x2d, 0xe0,
    /* U+2019 "" (3x4) */
    0x7b, 0x40,
    /* U+201C "" (6x4) */
    0x65, 0x3c, 0xf6,
    /* U+201D "" (7x4) */
    0x6f, 0xdb, 0x24, 0xc0,
    /* U+2022 "" (4x4) */
    0x7f, 0xf6,
    /* U+2026 "" (7x2) */
    0xdb, 0xb4,
    /* U+2030 "" (7x10) */
    0x61, 0x62, 0x87, 0x33, 0x98, 0x1f, 0xe9, 0x92, 0xf8,
    /* U+2190 "" (8x5) */
    0x30, 0x60, 0xff, 0x60, 0x30,
    /* U+2191 "" (6x10) */
    0x10, 0xe7, 0xfd, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (8x5) */
    0x0c, 0x06, 0xff, 0x06, 0x0c,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xcf, 0x5f, 0x38, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 30, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 6},
    {.bitmap_index = 53, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 78, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 85, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 134, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 88, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 103, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 134, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 134, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 204, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 215, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 240, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 402, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 503, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 510, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 522, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 528, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 529, .adv_w = 134, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 530, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 134, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 583, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 592, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 619, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 667, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 676, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 734, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 751, .adv_w = 134, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 756, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 768, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 771, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 775, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 786, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 789, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 799, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 801, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 806, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 813, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 842, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 843, .adv_w = 134, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 844, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 846, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 4, .ofs_y = 6},
    {.bitmap_index = 848, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 851, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 855, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 857, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 873, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 881, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 886, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_italic_14 = {
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_ITALIC_14 */
