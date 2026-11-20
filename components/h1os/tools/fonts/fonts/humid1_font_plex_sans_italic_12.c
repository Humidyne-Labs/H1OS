/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_12 (sans italic)
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

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_12
#define HUMID1_FONT_PLEX_SANS_ITALIC_12 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_12

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_12);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x9) */
    0x32, 0x66, 0x64, 0x0c, 0xc0,
    /* U+0022 "" (5x4) */
    0x5a, 0xf5, 0xa0,
    /* U+0023 "#" (8x9) */
    0x0a, 0x12, 0x7f, 0x34, 0x24, 0xfe, 0x68, 0x48, 0x48,
    /* U+0024 "$" (7x11) */
    0x08, 0x79, 0xfb, 0x87, 0x07, 0x87, 0x0a, 0xfc, 0xf0, 0x80,
    /* U+0025 "%" (9x9) */
    0x71, 0xa9, 0xb4, 0x92, 0x86, 0xb8, 0xd4, 0x5a, 0x4f, 0x43, 0x00,
    /* U+0026 "&" (8x9) */
    0x1c, 0x34, 0x24, 0x38, 0x3b, 0x4e, 0xcc, 0x4e, 0x7e,
    /* U+0027 "'" (2x4) */
    0x5f,
    /* U+0028 "(" (4x12) */
    0x12, 0x64, 0xc8, 0x88, 0x88, 0xc4,
    /* U+0029 ")" (5x12) */
    0x30, 0x84, 0x31, 0x8c, 0x62, 0x31, 0x19, 0x80,
    /* U+002A "" (6x6) */
    0x10, 0x4f, 0xdc, 0x71, 0x40,
    /* U+002B "+" (6x7) */
    0x10, 0xc3, 0x3f, 0x20, 0x82, 0x00,
    /* U+002C "," (2x4) */
    0x76,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x11) */
    0x0c, 0x20, 0x84, 0x10, 0x82, 0x10, 0x42, 0x08, 0x00,
    /* U+0030 "0" (6x9) */
    0x39, 0xbc, 0xf3, 0x8e, 0x38, 0xb6, 0x70,
    /* U+0031 "1" (5x9) */
    0x3b, 0xf6, 0x21, 0x18, 0xc6, 0xf8,
    /* U+0032 "2" (7x9) */
    0x1c, 0x4c, 0x18, 0x30, 0xc3, 0x0c, 0x30, 0xfc,
    /* U+0033 "3" (7x9) */
    0x3c, 0x4c, 0x18, 0x21, 0x81, 0x81, 0x66, 0x78,
    /* U+0034 "4" (7x9) */
    0x0e, 0x18, 0x51, 0x26, 0xc9, 0xbf, 0x84, 0x08,
    /* U+0035 "5" (6x9) */
    0x7d, 0x04, 0x3e, 0xd8, 0x20, 0xa6, 0xf0,
    /* U+0036 "6" (5x9) */
    0x19, 0x99, 0xfd, 0xc6, 0x3b, 0x70,
    /* U+0037 "7" (6x9) */
    0x7f, 0x3c, 0xc6, 0x18, 0xc2, 0x18, 0x40,
    /* U+0038 "8" (6x9) */
    0x39, 0xb4, 0xd2, 0x7b, 0x68, 0xb6, 0xf0,
    /* U+0039 "9" (6x9) */
    0x39, 0xbc, 0xf3, 0x7c, 0x61, 0x8c, 0x60,
    /* U+003A ":" (2x7) */
    0x70, 0x28,
    /* U+003B ";" (3x9) */
    0x2c, 0x00, 0x92, 0x80,
    /* U+003C "<" (6x6) */
    0x0c, 0xe6, 0x30, 0x60, 0xc0,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3e,
    /* U+003E ">" (5x7) */
    0x61, 0x86, 0x37, 0x62, 0x00,
    /* U+003F "?" (5x9) */
    0x76, 0xc6, 0x36, 0x20, 0x18, 0xc0,
    /* U+0040 "@" (9x10) */
    0x1e, 0x19, 0x97, 0xb2, 0xda, 0x6d, 0x26, 0x95, 0x7e, 0xc0, 0x3e, 0x00,
    /* U+0041 "A" (7x9) */
    0x0c, 0x38, 0x51, 0xa2, 0x4f, 0xd1, 0xe3, 0x86,
    /* U+0042 "B" (7x9) */
    0x3e, 0x4c, 0x8b, 0x37, 0xcc, 0xd1, 0xa3, 0xfc,
    /* U+0043 "C" (6x9) */
    0x3d, 0xbc, 0x30, 0x82, 0x08, 0x33, 0x70,
    /* U+0044 "D" (8x9) */
    0x3c, 0x26, 0x23, 0x63, 0x63, 0x42, 0x46, 0x4c, 0xf8,
    /* U+0045 "E" (7x9) */
    0x3e, 0x40, 0x83, 0x07, 0xcc, 0x10, 0x20, 0xfc,
    /* U+0046 "F" (7x9) */
    0x3e, 0x40, 0x83, 0x07, 0xcc, 0x10, 0x20, 0xc0,
    /* U+0047 "G" (7x9) */
    0x3c, 0xcf, 0x06, 0x08, 0xf0, 0xa1, 0x66, 0x7c,
    /* U+0048 "H" (8x9) */
    0x21, 0x21, 0x23, 0x63, 0x7f, 0x62, 0x42, 0x42, 0xc6,
    /* U+0049 "I" (5x9) */
    0x39, 0x8c, 0x62, 0x10, 0x8c, 0xf0,
    /* U+004A "J" (6x9) */
    0x3c, 0x30, 0xc3, 0x0c, 0x20, 0xb6, 0x70,
    /* U+004B "K" (8x9) */
    0x23, 0x26, 0x2c, 0x68, 0x78, 0x6c, 0x4c, 0x44, 0xc6,
    /* U+004C "L" (5x9) */
    0x31, 0x18, 0xc6, 0x31, 0x1f, 0xf8,
    /* U+004D "M" (10x9) */
    0x30, 0xcc, 0x63, 0x39, 0xee, 0x6d, 0x93, 0x64, 0x91, 0x04, 0xc1, 0x00,
    /* U+004E "N" (8x9) */
    0x31, 0x31, 0x31, 0x7b, 0x6b, 0x4a, 0x4e, 0x46, 0xc6,
    /* U+004F "O" (7x9) */
    0x3c, 0xcb, 0x1e, 0x38, 0x70, 0xe1, 0x66, 0x70,
    /* U+0050 "P" (8x9) */
    0x3e, 0x37, 0x63, 0x66, 0x7e, 0x60, 0x40, 0xc0, 0xc0,
    /* U+0051 "Q" (7x12) */
    0x38, 0xcb, 0x1e, 0x38, 0x70, 0xe1, 0x66, 0xf8, 0xe0, 0x81, 0x80,
    /* U+0052 "R" (8x9) */
    0x3e, 0x22, 0x23, 0x66, 0x7c, 0x6c, 0x4c, 0x44, 0xc4,
    /* U+0053 "S" (7x9) */
    0x1c, 0x4d, 0x83, 0x83, 0xc1, 0x81, 0x66, 0x78,
    /* U+0054 "T" (6x9) */
    0xfc, 0xc3, 0x0c, 0x20, 0x86, 0x18, 0x60,
    /* U+0055 "U" (7x9) */
    0x42, 0x8d, 0x1e, 0x2c, 0x50, 0xa3, 0x7c, 0x70,
    /* U+0056 "V" (7x9) */
    0xc7, 0x8f, 0x32, 0x64, 0x8b, 0x1c, 0x38, 0x60,
    /* U+0057 "W" (11x9) */
    0xc4, 0x79, 0x8b, 0x33, 0x6a, 0x4d, 0x48, 0xab, 0x19, 0xc3, 0x38, 0x66,
    0x00,
    /* U+0058 "X" (8x9) */
    0x23, 0x36, 0x34, 0x1c, 0x18, 0x38, 0x6c, 0x4c, 0xc4,
    /* U+0059 "Y" (7x9) */
    0xc6, 0x89, 0x33, 0xc3, 0x06, 0x08, 0x10, 0x60,
    /* U+005A "Z" (7x9) */
    0x3e, 0x0c, 0x30, 0xc1, 0x86, 0x18, 0x60, 0xfc,
    /* U+005B "[" (5x12) */
    0x39, 0x88, 0xc6, 0x31, 0x08, 0x46, 0x31, 0xc0,
    /* U+005C "" (2x12) */
    0xaa, 0xff, 0x55,
    /* U+005D "]" (4x12) */
    0x33, 0x33, 0x22, 0x26, 0x64, 0x4c,
    /* U+005E "^" (6x5) */
    0x38, 0xe6, 0xb3, 0x8c,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x2) */
    0xd0,
    /* U+0061 "a" (7x7) */
    0x36, 0xd9, 0x12, 0x2c, 0xcb, 0x9b, 0x00,
    /* U+0062 "b" (6x10) */
    0x20, 0x82, 0x1b, 0x7d, 0x94, 0x51, 0x6f, 0xe0,
    /* U+0063 "c" (5x7) */
    0x76, 0xe1, 0x08, 0x4b, 0x80,
    /* U+0064 "d" (7x10) */
    0x02, 0x04, 0x19, 0xb6, 0xc8, 0x91, 0x66, 0x5c, 0xd8,
    /* U+0065 "e" (5x7) */
    0x76, 0xe7, 0xe8, 0x4b, 0xc0,
    /* U+0066 "f" (6x13) */
    0x0c, 0x61, 0x0e, 0x30, 0xc3, 0x0c, 0x20, 0x82, 0x18, 0xc0,
    /* U+0067 "g" (7x11) */
    0x06, 0x79, 0xb2, 0x66, 0xcf, 0x1c, 0x3e, 0x8d, 0x9b, 0xe0,
    /* U+0068 "h" (6x10) */
    0x20, 0x82, 0x1b, 0x7d, 0x94, 0x53, 0x4f, 0x30,
    /* U+0069 "i" (2x10) */
    0x43, 0xfa, 0xb0,
    /* U+006A "j" (4x13) */
    0x10, 0x03, 0x33, 0x22, 0x26, 0x66, 0xc0,
    /* U+006B "k" (6x10) */
    0x20, 0x82, 0x19, 0x69, 0xe7, 0x16, 0x4b, 0x30,
    /* U+006C "l" (2x10) */
    0x57, 0xfa, 0xb0,
    /* U+006D "m" (10x7) */
    0x6d, 0x9f, 0xb6, 0x4d, 0x12, 0x4c, 0x93, 0x2c, 0x8c,
    /* U+006E "n" (6x7) */
    0x6d, 0xf6, 0x51, 0x4d, 0x3c, 0xc0,
    /* U+006F "o" (5x7) */
    0x76, 0xe3, 0x19, 0xcb, 0x80,
    /* U+0070 "p" (6x10) */
    0x6d, 0xf6, 0x51, 0x45, 0xbf, 0xb0, 0x82, 0x00,
    /* U+0071 "q" (7x10) */
    0x36, 0xd9, 0x12, 0x2c, 0xcb, 0x9b, 0x04, 0x08, 0x10,
    /* U+0072 "r" (5x7) */
    0x7b, 0x10, 0x84, 0x23, 0x00,
    /* U+0073 "s" (5x7) */
    0x3b, 0x58, 0xf1, 0xed, 0xc0,
    /* U+0074 "t" (3x8) */
    0x5f, 0x6d, 0x26,
    /* U+0075 "u" (5x7) */
    0xce, 0x63, 0x39, 0xdf, 0x60,
    /* U+0076 "v" (5x7) */
    0x8c, 0xe5, 0x6e, 0x73, 0x00,
    /* U+0077 "w" (8x7) */
    0x99, 0x99, 0xbb, 0xaa, 0xee, 0xcc, 0xcc,
    /* U+0078 "x" (6x7) */
    0x65, 0xa3, 0x8c, 0x71, 0x68, 0x80,
    /* U+0079 "y" (6x10) */
    0x45, 0x34, 0x92, 0x51, 0xc7, 0x18, 0x63, 0x00,
    /* U+007A "z" (6x7) */
    0x7c, 0x61, 0x8c, 0x63, 0x0f, 0x80,
    /* U+007B "{" (5x12) */
    0x19, 0x88, 0x42, 0x61, 0x0c, 0x42, 0x10, 0xc0,
    /* U+007C "|" (3x12) */
    0x2d, 0xa4, 0x96, 0xd2, 0x40,
    /* U+007D "}" (4x12) */
    0x33, 0x32, 0x33, 0x26, 0x44, 0x4c,
    /* U+007E "~" (5x2) */
    0xe1, 0xc0,
    /* U+00B0 "" (5x5) */
    0x72, 0xa7, 0xa7, 0x00,
    /* U+00B1 "" (7x9) */
    0x08, 0x10, 0x63, 0xf1, 0x82, 0x04, 0x00, 0xfc,
    /* U+00B2 "" (3x4) */
    0x65, 0x70,
    /* U+00B3 "" (3x4) */
    0x6c, 0xe0,
    /* U+00B5 "" (7x10) */
    0x66, 0xc9, 0x12, 0x24, 0xc9, 0xbb, 0x40, 0x81, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x6) */
    0x4b, 0xcc, 0xed, 0xc0,
    /* U+00F7 "" (6x7) */
    0x30, 0xc0, 0x3f, 0x00, 0x86, 0x00,
    /* U+0394 "" (7x9) */
    0x0c, 0x38, 0x71, 0xa2, 0x6c, 0xd1, 0xe3, 0xfe,
    /* U+03A9 "" (8x9) */
    0x1e, 0x37, 0x63, 0x63, 0x43, 0x43, 0x66, 0x2c, 0xee,
    /* U+03BC "" (6x8) */
    0x65, 0x94, 0x53, 0x4f, 0xb8, 0x20,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (9x1) */
    0xff, 0x80,
    /* U+2018 "" (3x4) */
    0x6b, 0x60,
    /* U+2019 "" (3x4) */
    0x6d, 0x60,
    /* U+201C "" (5x4) */
    0x6a, 0xf7, 0xb0,
    /* U+201D "" (5x4) */
    0x6b, 0xd3, 0x20,
    /* U+2022 "" (3x4) */
    0x7f, 0xf0,
    /* U+2026 "" (9x2) */
    0x4d, 0xe4, 0xc0,
    /* U+2030 "" (14x9) */
    0x71, 0x01, 0x4c, 0x0d, 0x20, 0x25, 0x00, 0x6b, 0x98, 0x6a, 0xd1, 0x6a,
    0x49, 0xeb, 0x43, 0x38,
    /* U+2190 "" (9x5) */
    0x20, 0x30, 0x3f, 0xec, 0x02, 0x00,
    /* U+2191 "" (5x8) */
    0x67, 0xaa, 0x42, 0x10, 0x84,
    /* U+2192 "" (8x5) */
    0x04, 0x02, 0xff, 0x03, 0x06,
    /* U+2193 "" (5x8) */
    0x21, 0x08, 0x42, 0x7d, 0xc4,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 45, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 58, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 89, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 8, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 109, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 27, .adv_w = 178, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 49, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 48, .adv_w = 66, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 66, .box_w = 5, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 106, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 73, .adv_w = 57, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 75, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 75, .adv_w = 57, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 86, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 61, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 61, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 162, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 167, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 170, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 93, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 170, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 193, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 110, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 106, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 78, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 101, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 97, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 153, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 133, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 133, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 335, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 108, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 119, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 176, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 121, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 109, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 62, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 421, .adv_w = 86, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 424, .adv_w = 62, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 430, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 434, .adv_w = 105, .box_w = 7, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 435, .adv_w = 113, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 436, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 456, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 65, .box_w = 6, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 480, .adv_w = 101, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 490, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 52, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 508, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 53, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 167, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 105, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 547, .adv_w = 111, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 556, .adv_w = 74, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 66, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 149, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 96, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 600, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 68, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 614, .adv_w = 71, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 619, .adv_w = 68, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 625, .adv_w = 115, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 627, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 631, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 65, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 641, .adv_w = 64, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 643, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 652, .adv_w = 65, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 653, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 657, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 686, .adv_w = 111, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 687, .adv_w = 147, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 689, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 691, .adv_w = 54, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 693, .adv_w = 97, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 696, .adv_w = 97, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 699, .adv_w = 79, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 701, .adv_w = 165, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 252, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 168, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 726, .adv_w = 168, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 168, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 736, .adv_w = 168, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_italic_12 = {
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

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_12 */
