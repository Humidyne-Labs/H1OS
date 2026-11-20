/*******************************************************************************
 * Font: humid1_font_plex_mono_italic_12 (mono italic)
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

#ifndef HUMID1_FONT_PLEX_MONO_ITALIC_12
#define HUMID1_FONT_PLEX_MONO_ITALIC_12 1
#endif

#if HUMID1_FONT_PLEX_MONO_ITALIC_12

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_12);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x8) */
    0x6d, 0xa4, 0x36,
    /* U+0022 "" (4x3) */
    0x5d, 0x90,
    /* U+0023 "#" (7x8) */
    0x1a, 0x29, 0xd9, 0x22, 0x9d, 0xd6, 0x28,
    /* U+0024 "$" (7x10) */
    0x08, 0x7d, 0xa3, 0xc3, 0x83, 0x85, 0xfe, 0x38, 0x60,
    /* U+0025 "%" (8x8) */
    0x33, 0x52, 0x54, 0x70, 0x0c, 0x3a, 0x56, 0x8c,
    /* U+0026 "&" (7x8) */
    0x1c, 0x68, 0x91, 0xe5, 0x1b, 0x36, 0xb6,
    /* U+0027 "'" (2x3) */
    0x5c,
    /* U+0028 "(" (4x10) */
    0x12, 0x64, 0xc8, 0x8c, 0x46,
    /* U+0029 ")" (4x10) */
    0x23, 0x11, 0x11, 0x32, 0x6c,
    /* U+002A "" (6x5) */
    0x30, 0xcf, 0xdc, 0xd0,
    /* U+002B "+" (6x6) */
    0x30, 0xcf, 0xc8, 0x20, 0x80,
    /* U+002C "," (2x4) */
    0x7a,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (7x10) */
    0x06, 0x08, 0x30, 0x41, 0x82, 0x08, 0x30, 0x41, 0x80,
    /* U+0030 "0" (6x8) */
    0x39, 0x3c, 0x6b, 0x8e, 0x39, 0x9c,
    /* U+0031 "1" (5x8) */
    0x3b, 0xf4, 0x23, 0x18, 0xdf,
    /* U+0032 "2" (7x8) */
    0x3c, 0xcc, 0x18, 0x21, 0xc6, 0x18, 0x7e,
    /* U+0033 "3" (7x8) */
    0x3c, 0x4c, 0x18, 0xc0, 0xc0, 0xb3, 0x3c,
    /* U+0034 "4" (7x8) */
    0x0c, 0x38, 0xd1, 0x64, 0xdf, 0xc2, 0x04,
    /* U+0035 "5" (6x8) */
    0x7d, 0x0c, 0x3e, 0xcc, 0x39, 0xbc,
    /* U+0036 "6" (6x8) */
    0x19, 0x84, 0x3e, 0xce, 0x38, 0x9c,
    /* U+0037 "7" (6x8) */
    0xff, 0x38, 0x86, 0x30, 0xc6, 0x10,
    /* U+0038 "8" (7x8) */
    0x3c, 0xcd, 0x99, 0xe6, 0x58, 0xf3, 0x3c,
    /* U+0039 "9" (6x8) */
    0x7b, 0x3c, 0xf3, 0xfc, 0x63, 0x18,
    /* U+003A ":" (3x6) */
    0x6c, 0x0d, 0x80,
    /* U+003B ";" (3x7) */
    0x6c, 0x0d, 0xa0,
    /* U+003C "<" (6x7) */
    0x04, 0x77, 0x30, 0xe0, 0xe0, 0x80,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3e,
    /* U+003E ">" (5x5) */
    0x61, 0xc2, 0x7c, 0x00,
    /* U+003F "?" (5x8) */
    0xf4, 0xc6, 0xe4, 0x03, 0x18,
    /* U+0040 "@" (6x9) */
    0x39, 0x39, 0xeb, 0xae, 0xab, 0xa0, 0xf0,
    /* U+0041 "A" (6x8) */
    0x1c, 0x73, 0xc9, 0x65, 0xfc, 0x71,
    /* U+0042 "B" (6x8) */
    0x79, 0x3c, 0xfe, 0xca, 0x29, 0xbc,
    /* U+0043 "C" (6x8) */
    0x39, 0x3c, 0x30, 0x82, 0x0c, 0x9c,
    /* U+0044 "D" (7x8) */
    0x3c, 0x4d, 0x9b, 0x36, 0x68, 0xd3, 0x7c,
    /* U+0045 "E" (6x8) */
    0x7d, 0x0c, 0x3e, 0xc2, 0x08, 0x3e,
    /* U+0046 "F" (6x8) */
    0x7d, 0x0c, 0x3e, 0xc2, 0x08, 0x20,
    /* U+0047 "G" (6x8) */
    0x39, 0x3c, 0x20, 0x9e, 0x2c, 0x9e,
    /* U+0048 "H" (7x8) */
    0x22, 0xcd, 0x9b, 0xf6, 0x48, 0x91, 0x66,
    /* U+0049 "I" (7x8) */
    0x3e, 0x30, 0x60, 0xc1, 0x82, 0x0c, 0x7e,
    /* U+004A "J" (6x8) */
    0x7c, 0x30, 0x82, 0x08, 0x69, 0xbc,
    /* U+004B "K" (7x8) */
    0x22, 0x4d, 0xb3, 0xc7, 0x8d, 0x93, 0x62,
    /* U+004C "L" (5x8) */
    0x62, 0x11, 0x8c, 0x63, 0x1f,
    /* U+004D "M" (7x8) */
    0x66, 0xed, 0xfa, 0xd5, 0x68, 0xf1, 0x62,
    /* U+004E "N" (7x8) */
    0x32, 0xe5, 0xda, 0xb5, 0xcb, 0x93, 0x66,
    /* U+004F "O" (6x8) */
    0x39, 0x3c, 0xe3, 0x8e, 0x39, 0x9c,
    /* U+0050 "P" (6x8) */
    0x79, 0x3c, 0xf3, 0xfb, 0x08, 0x20,
    /* U+0051 "Q" (6x10) */
    0x39, 0x3c, 0xe3, 0x8e, 0x3d, 0x9c, 0x3c, 0x60,
    /* U+0052 "R" (6x8) */
    0x79, 0x3c, 0xf3, 0xfb, 0x49, 0xa6,
    /* U+0053 "S" (6x8) */
    0x39, 0x1c, 0x1c, 0x38, 0x29, 0xbc,
    /* U+0054 "T" (7x8) */
    0xfe, 0x60, 0xc1, 0x82, 0x04, 0x08, 0x30,
    /* U+0055 "U" (6x8) */
    0xc7, 0x3c, 0xf3, 0x8e, 0x2d, 0xbc,
    /* U+0056 "V" (7x8) */
    0xc7, 0x8b, 0x36, 0x45, 0x8a, 0x1c, 0x30,
    /* U+0057 "W" (8x8) */
    0x43, 0x42, 0x5a, 0x5a, 0x4a, 0x6e, 0xec, 0xcc,
    /* U+0058 "X" (7x8) */
    0x62, 0x6c, 0xf0, 0xc3, 0x85, 0x13, 0x62,
    /* U+0059 "Y" (7x8) */
    0xc6, 0x99, 0x23, 0x83, 0x04, 0x08, 0x30,
    /* U+005A "Z" (7x8) */
    0x7e, 0x0c, 0x30, 0xc3, 0x0c, 0x38, 0x7e,
    /* U+005B "[" (5x10) */
    0x7a, 0x10, 0x84, 0x62, 0x10, 0x87, 0x00,
    /* U+005C "" (3x10) */
    0x99, 0x24, 0x99, 0x24,
    /* U+005D "]" (6x10) */
    0x3c, 0x30, 0x82, 0x08, 0x21, 0x84, 0x13, 0xc0,
    /* U+005E "^" (6x5) */
    0x30, 0xe4, 0xb3, 0x80,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (1x2) */
    0xc0,
    /* U+0061 "a" (6x6) */
    0x6f, 0x28, 0xa2, 0x9b, 0xa0,
    /* U+0062 "b" (7x8) */
    0x20, 0x41, 0xb3, 0x36, 0x68, 0x93, 0x6c,
    /* U+0063 "c" (5x6) */
    0x7e, 0x71, 0x0d, 0xb8,
    /* U+0064 "d" (6x8) */
    0x04, 0x37, 0xf3, 0x8a, 0x29, 0xbe,
    /* U+0065 "e" (5x6) */
    0x7e, 0x7f, 0x0c, 0xb8,
    /* U+0066 "f" (8x10) */
    0x0f, 0x08, 0x7e, 0x18, 0x18, 0x10, 0x10, 0xb0, 0xf0, 0x60,
    /* U+0067 "g" (6x8) */
    0x7f, 0x38, 0xa2, 0x9b, 0xe1, 0x3c,
    /* U+0068 "h" (5x8) */
    0x42, 0x37, 0x9c, 0xc6, 0x33,
    /* U+0069 "i" (5x8) */
    0x31, 0xbc, 0x46, 0x35, 0xee,
    /* U+006A "j" (5x10) */
    0x08, 0x5e, 0x21, 0x08, 0xd6, 0xb3, 0x00,
    /* U+006B "k" (6x8) */
    0x41, 0x0d, 0xb2, 0xca, 0xcb, 0xe6,
    /* U+006C "l" (5x8) */
    0xf1, 0x88, 0xc6, 0x35, 0xee,
    /* U+006D "m" (7x6) */
    0x76, 0xb5, 0x4e, 0xb9, 0x52, 0x80,
    /* U+006E "n" (5x6) */
    0xde, 0x73, 0x18, 0xcc,
    /* U+006F "o" (6x6) */
    0x7b, 0x28, 0xe2, 0x99, 0xc0,
    /* U+0070 "p" (7x8) */
    0x6c, 0xcd, 0x9a, 0x34, 0xdb, 0x30, 0x60,
    /* U+0071 "q" (6x8) */
    0x7f, 0x38, 0xa2, 0x9b, 0xe1, 0x84,
    /* U+0072 "r" (6x6) */
    0xfd, 0xc6, 0x18, 0x61, 0x80,
    /* U+0073 "s" (5x6) */
    0x7e, 0x78, 0x79, 0xf8,
    /* U+0074 "t" (6x8) */
    0x30, 0x8f, 0xd8, 0x61, 0xa7, 0x9c,
    /* U+0075 "u" (6x6) */
    0xcf, 0x38, 0xa2, 0xdb, 0xe0,
    /* U+0076 "v" (6x6) */
    0xc9, 0x34, 0xb2, 0xd3, 0x80,
    /* U+0077 "w" (7x6) */
    0x5a, 0xa5, 0x4e, 0xbf, 0x4b, 0x00,
    /* U+0078 "x" (7x6) */
    0x36, 0xb4, 0x40, 0x8b, 0x7b, 0x80,
    /* U+0079 "y" (6x8) */
    0xcf, 0x38, 0xa2, 0xdb, 0xe1, 0x38,
    /* U+007A "z" (7x6) */
    0x3e, 0x98, 0x61, 0xa6, 0x5b, 0x80,
    /* U+007B "{" (6x10) */
    0x1c, 0xc3, 0x04, 0x13, 0x83, 0x08, 0x41, 0xc0,
    /* U+007C "|" (3x10) */
    0x25, 0xb4, 0x92, 0xd8,
    /* U+007D "}" (6x10) */
    0x38, 0x20, 0x84, 0x10, 0x73, 0x04, 0x13, 0xc0,
    /* U+007E "~" (6x3) */
    0x66, 0xb9, 0x80,
    /* U+00B0 "" (4x4) */
    0x7d, 0x9f,
    /* U+00B1 "" (7x7) */
    0x08, 0x31, 0xf8, 0x81, 0x00, 0x3f, 0x00,
    /* U+00B2 "" (4x4) */
    0x71, 0x6e,
    /* U+00B3 "" (4x4) */
    0x76, 0x3e,
    /* U+00B5 "" (7x8) */
    0x66, 0xcd, 0x92, 0x26, 0xdf, 0xb0, 0x60,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x5) */
    0x4b, 0xcc, 0xe8, 0x80,
    /* U+00F7 "" (6x6) */
    0x30, 0x0f, 0xc0, 0x00, 0x80,
    /* U+0394 "" (6x9) */
    0x1c, 0x73, 0xcf, 0x65, 0x94, 0x71, 0xfc,
    /* U+03A9 "" (7x9) */
    0x1c, 0x6d, 0x9b, 0x34, 0x68, 0xd1, 0x14, 0xec,
    /* U+03BC "" (7x8) */
    0x66, 0xcd, 0x92, 0x26, 0xdf, 0xb0, 0x60,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (7x1) */
    0xfe,
    /* U+2018 "" (2x4) */
    0x5e,
    /* U+2019 "" (3x4) */
    0x7b, 0x40,
    /* U+201C "" (6x3) */
    0x25, 0xbd, 0x80,
    /* U+201D "" (6x3) */
    0x6d, 0xbd, 0x80,
    /* U+2022 "" (3x3) */
    0x7f, 0x80,
    /* U+2026 "" (6x1) */
    0xf4,
    /* U+2030 "" (6x8) */
    0xe2, 0x8e, 0xf8, 0x6a, 0xdb, 0x7e,
    /* U+2190 "" (7x5) */
    0x30, 0xc3, 0xfb, 0x03, 0x00,
    /* U+2191 "" (5x8) */
    0x33, 0xea, 0x42, 0x10, 0x84,
    /* U+2192 "" (7x5) */
    0x08, 0x1b, 0xf8, 0x60, 0x80,
    /* U+2193 "" (5x8) */
    0x21, 0x08, 0x42, 0x7d, 0xc4,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 115, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 115, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 5, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 37, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 115, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 57, .adv_w = 115, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 58, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 115, .box_w = 3, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 115, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 137, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 146, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 150, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 162, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 271, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 339, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 343, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 351, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 355, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 356, .adv_w = 115, .box_w = 1, .box_h = 2, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 357, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 115, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 393, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 399, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 416, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 449, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 455, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 498, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 512, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 516, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 524, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 527, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 529, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 538, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 540, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 547, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 2},
    {.bitmap_index = 548, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 552, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 557, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 579, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 580, .adv_w = 115, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 581, .adv_w = 115, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 582, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 584, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 587, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 590, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 592, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 604, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 614, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_italic_12 = {
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

#endif /* #if HUMID1_FONT_PLEX_MONO_ITALIC_12 */
