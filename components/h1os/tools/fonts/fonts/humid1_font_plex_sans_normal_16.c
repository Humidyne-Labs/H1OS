/*******************************************************************************
 * Font: humid1_font_plex_sans_normal_16 (sans normal)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_SANS_NORMAL_16
#define HUMID1_FONT_PLEX_SANS_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_SANS_NORMAL_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_icon_fa7_solid_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x11) */
    0xff, 0x55, 0x3c,
    /* U+0022 "" (5x5) */
    0xce, 0x73, 0x9c, 0x80,
    /* U+0023 "#" (9x11) */
    0x11, 0x09, 0x8c, 0x9f, 0xf2, 0x21, 0x10, 0x89, 0xff, 0x64, 0x22, 0x11,
    0x00,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x3e, 0xd2, 0xd0, 0xd0, 0x70, 0x3c, 0x16, 0x13, 0x13, 0xd6,
    0x7c, 0x18, 0x18,
    /* U+0025 "%" (13x11) */
    0x70, 0x66, 0xc2, 0x32, 0x31, 0x93, 0x0d, 0xb0, 0x39, 0x38, 0x1b, 0x61,
    0x91, 0x08, 0x88, 0xc6, 0xcc, 0x1c,
    /* U+0026 "&" (10x11) */
    0x3c, 0x19, 0x86, 0x61, 0x98, 0x3c, 0x0e, 0x04, 0xdf, 0x1c, 0xc3, 0x31,
    0xe3, 0xdc,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (4x14) */
    0x32, 0x64, 0xcc, 0xcc, 0xcc, 0x46, 0x23,
    /* U+0029 ")" (4x14) */
    0xc6, 0x23, 0x31, 0x11, 0x13, 0x32, 0x6c,
    /* U+002A "" (6x7) */
    0x30, 0xcf, 0xde, 0x39, 0x24, 0x00,
    /* U+002B "+" (8x7) */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (2x4) */
    0xf6,
    /* U+002D "-" (4x2) */
    0xff,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x14) */
    0x0c, 0x30, 0x86, 0x18, 0x43, 0x0c, 0x20, 0x86, 0x10, 0x43, 0x00,
    /* U+0030 "0" (8x11) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0031 "1" (8x11) */
    0x38, 0x78, 0xc8, 0x88, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff,
    /* U+0032 "2" (8x11) */
    0x7c, 0xc6, 0x06, 0x06, 0x06, 0x04, 0x08, 0x10, 0x20, 0xc0, 0xff,
    /* U+0033 "3" (7x11) */
    0x7d, 0x8c, 0x18, 0x30, 0x67, 0x81, 0x83, 0x07, 0x8d, 0xf0,
    /* U+0034 "4" (8x11) */
    0x0c, 0x1c, 0x14, 0x34, 0x24, 0x44, 0xc4, 0x84, 0xff, 0x04, 0x04,
    /* U+0035 "5" (8x11) */
    0x7e, 0x40, 0x40, 0x40, 0xdc, 0xc6, 0x03, 0x03, 0x03, 0xc6, 0x3c,
    /* U+0036 "6" (8x11) */
    0x1c, 0x30, 0x60, 0x60, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0037 "7" (8x11) */
    0xff, 0xc2, 0xc6, 0xc6, 0x0c, 0x0c, 0x08, 0x18, 0x18, 0x30, 0x30,
    /* U+0038 "8" (8x11) */
    0x3c, 0x46, 0xc2, 0xc2, 0x46, 0x3c, 0xc6, 0xc3, 0xc3, 0xc6, 0x7c,
    /* U+0039 "9" (8x11) */
    0x3c, 0x46, 0xc2, 0xc3, 0xc3, 0xc7, 0x7e, 0x06, 0x0c, 0x18, 0x30,
    /* U+003A ":" (1x8) */
    0xc3,
    /* U+003B ";" (3x10) */
    0x48, 0x00, 0x13, 0x58,
    /* U+003C "<" (7x9) */
    0x02, 0x1c, 0x73, 0x8e, 0x0e, 0x07, 0x07, 0x02,
    /* U+003D "=" (8x4) */
    0xff, 0x00, 0x00, 0xff,
    /* U+003E ">" (6x7) */
    0xc1, 0xc1, 0x83, 0x19, 0xcc, 0x00,
    /* U+003F "?" (6x11) */
    0x7b, 0x38, 0xc3, 0x0c, 0x73, 0x88, 0x00, 0xc3, 0x00,
    /* U+0040 "@" (12x13) */
    0x0f, 0x83, 0x06, 0x60, 0x24, 0xf9, 0x89, 0x99, 0x89, 0x98, 0x99, 0x89,
    0x89, 0x94, 0xee, 0x60, 0x03, 0x00, 0x0f, 0xc0,
    /* U+0041 "A" (9x11) */
    0x1c, 0x0e, 0x0d, 0x06, 0xc2, 0x63, 0x31, 0x8c, 0xfe, 0xc1, 0x60, 0xe0,
    0x60,
    /* U+0042 "B" (9x11) */
    0xfe, 0x61, 0xb0, 0xd8, 0x6c, 0x37, 0xf3, 0x0d, 0x83, 0xc1, 0xe1, 0xbf,
    0x80,
    /* U+0043 "C" (8x11) */
    0x3e, 0x63, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0x63, 0x3e,
    /* U+0044 "D" (9x11) */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xe1, 0xbf,
    0x80,
    /* U+0045 "E" (8x11) */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff,
    /* U+0046 "F" (7x11) */
    0xff, 0x83, 0x06, 0x0c, 0x1f, 0xf0, 0x60, 0xc1, 0x83, 0x00,
    /* U+0047 "G" (9x11) */
    0x3e, 0x31, 0xb0, 0x58, 0x0c, 0x06, 0x3f, 0x07, 0x83, 0xc1, 0xb1, 0xcf,
    0xe0,
    /* U+0048 "H" (9x11) */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0x07, 0x83, 0xc1, 0xe0, 0xf0,
    0x60,
    /* U+0049 "I" (5x11) */
    0xfb, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0x3e,
    /* U+004A "J" (6x11) */
    0x7c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0f, 0x3f, 0x80,
    /* U+004B "K" (9x11) */
    0xc3, 0xe1, 0xb1, 0x99, 0x8d, 0x87, 0xe3, 0xb1, 0x8c, 0xc7, 0x61, 0xb0,
    0x60,
    /* U+004C "L" (7x11) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xf8,
    /* U+004D "M" (11x11) */
    0xe0, 0xfc, 0x1f, 0xc7, 0xf8, 0xfd, 0xb7, 0x9c, 0xf3, 0x9e, 0x23, 0xc4,
    0x78, 0x0f, 0x01, 0x80,
    /* U+004E "N" (9x11) */
    0xe1, 0xf0, 0xfc, 0x7f, 0x3d, 0x9e, 0x6f, 0x37, 0x8f, 0xc7, 0xe1, 0xf0,
    0x60,
    /* U+004F "O" (9x11) */
    0x3e, 0x31, 0x90, 0x78, 0x3c, 0x0e, 0x07, 0x03, 0x83, 0x41, 0xb1, 0x8f,
    0x80,
    /* U+0050 "P" (8x11) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (9x13) */
    0x3e, 0x31, 0x90, 0x78, 0x3c, 0x0e, 0x07, 0x03, 0x83, 0xc1, 0xb1, 0x8f,
    0x81, 0x80, 0xe0,
    /* U+0052 "R" (8x11) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc6, 0xc6, 0xc7, 0xc3, 0xc3,
    /* U+0053 "S" (8x11) */
    0x3c, 0xc6, 0xc0, 0xc0, 0x60, 0x3c, 0x06, 0x03, 0x03, 0xc6, 0x7c,
    /* U+0054 "T" (9x11) */
    0xff, 0x86, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+0055 "U" (9x11) */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0x41, 0x31, 0x8f,
    0x80,
    /* U+0056 "V" (10x11) */
    0xc0, 0xd8, 0x66, 0x19, 0x86, 0x33, 0x0c, 0xc3, 0x30, 0x68, 0x1e, 0x07,
    0x80, 0xc0,
    /* U+0057 "W" (13x11) */
    0x87, 0x0e, 0x38, 0xf1, 0xc7, 0x8a, 0x3c, 0xd9, 0x24, 0xd9, 0xa2, 0xcd,
    0x16, 0x78, 0xe1, 0x87, 0x0c, 0x18,
    /* U+0058 "X" (9x11) */
    0xc3, 0x71, 0x99, 0x86, 0x83, 0xc0, 0xc0, 0xf0, 0x4c, 0x66, 0x61, 0xb0,
    0xe0,
    /* U+0059 "Y" (9x11) */
    0xe1, 0xb0, 0xcc, 0xc6, 0x61, 0xe0, 0xf0, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+005A "Z" (8x11) */
    0xff, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60, 0xc0, 0xff,
    /* U+005B "[" (3x14) */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6d, 0xc0,
    /* U+005C "" (5x14) */
    0x86, 0x30, 0x86, 0x30, 0x86, 0x30, 0x84, 0x30, 0x84,
    /* U+005D "]" (3x14) */
    0xed, 0xb6, 0xdb, 0x6d, 0xb7, 0xc0,
    /* U+005E "^" (8x6) */
    0x18, 0x38, 0x2c, 0x66, 0x46, 0xc3,
    /* U+005F "_" (9x1) */
    0xff, 0x80,
    /* U+0060 "`" (2x3) */
    0xd4,
    /* U+0061 "a" (7x8) */
    0x79, 0x98, 0x13, 0xec, 0x50, 0xb3, 0x3b,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0xdc,
    /* U+0063 "c" (7x8) */
    0x7d, 0x8b, 0x06, 0x0c, 0x18, 0x31, 0xbe,
    /* U+0064 "d" (7x12) */
    0x06, 0x0c, 0x18, 0x37, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1b, 0xf0,
    /* U+0065 "e" (7x8) */
    0x7d, 0x8f, 0x1f, 0xfc, 0x18, 0x39, 0xbe,
    /* U+0066 "f" (5x12) */
    0x19, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08, 0x40,
    /* U+0067 "g" (7x12) */
    0x06, 0xfb, 0x36, 0x3c, 0x79, 0x9e, 0x60, 0x7f, 0x06, 0x0f, 0xe0,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0x0d, 0xdc, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (2x12) */
    0xfc, 0xff, 0xff,
    /* U+006A "j" (3x15) */
    0x6d, 0x86, 0xdb, 0x6d, 0xb6, 0xf0,
    /* U+006B "k" (7x12) */
    0xc1, 0x83, 0x06, 0x0c, 0x79, 0xb6, 0x7c, 0xf9, 0x9b, 0x1e, 0x30,
    /* U+006C "l" (3x12) */
    0xdb, 0x6d, 0xb6, 0xdb, 0x30,
    /* U+006D "m" (12x8) */
    0xdd, 0xec, 0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3c, 0x63,
    /* U+006E "n" (7x8) */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    /* U+006F "o" (7x8) */
    0x39, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x9c,
    /* U+0070 "p" (8x11) */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0xdc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x11) */
    0x7f, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xbf, 0x06, 0x0c, 0x18,
    /* U+0072 "r" (5x8) */
    0xde, 0x31, 0x8c, 0x63, 0x18,
    /* U+0073 "s" (6x8) */
    0x7b, 0x3c, 0x3c, 0x3c, 0x3c, 0xde,
    /* U+0074 "t" (5x11) */
    0x31, 0x8d, 0xf3, 0x18, 0xc6, 0x31, 0x8e,
    /* U+0075 "u" (7x8) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xbf,
    /* U+0076 "v" (8x8) */
    0xc3, 0x42, 0x66, 0x66, 0x24, 0x3c, 0x1c, 0x18,
    /* U+0077 "w" (11x8) */
    0x8c, 0x31, 0xcf, 0x39, 0xe5, 0x25, 0xb4, 0xe7, 0x9c, 0x71, 0x8c,
    /* U+0078 "x" (7x8) */
    0xc7, 0x99, 0xe1, 0xc3, 0x8f, 0x33, 0x63,
    /* U+0079 "y" (8x11) */
    0xc3, 0x63, 0x66, 0x66, 0x34, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x70,
    /* U+007A "z" (6x8) */
    0xfc, 0x31, 0x8c, 0x61, 0x8c, 0x3f,
    /* U+007B "{" (5x14) */
    0x39, 0x8c, 0x63, 0x33, 0x98, 0xe3, 0x8c, 0x63, 0x1c,
    /* U+007C "|" (2x14) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+007D "}" (4x14) */
    0xc6, 0x66, 0x66, 0x31, 0x36, 0x66, 0x6e,
    /* U+007E "~" (7x2) */
    0xf1, 0x1c,
    /* U+00B0 "" (6x5) */
    0x73, 0x28, 0xf2, 0x70,
    /* U+00B1 "" (7x10) */
    0x10, 0x30, 0x67, 0xf1, 0x83, 0x06, 0x0c, 0x01, 0xfc,
    /* U+00B2 "" (4x6) */
    0xeb, 0x36, 0xcf,
    /* U+00B3 "" (4x6) */
    0xe3, 0x63, 0x3e,
    /* U+00B5 "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xff, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (2x3) */
    0xfc,
    /* U+00D7 "" (6x7) */
    0x87, 0x37, 0x8c, 0x7b, 0x38, 0x40,
    /* U+00F7 "" (8x7) */
    0x18, 0x18, 0x00, 0xff, 0x00, 0x18, 0x18,
    /* U+0394 "" (9x11) */
    0x1c, 0x0e, 0x0d, 0x06, 0xc2, 0x63, 0x31, 0x8d, 0x86, 0xc3, 0x60, 0xff,
    0xe0,
    /* U+03A9 "" (10x12) */
    0x1e, 0x18, 0xc4, 0x1b, 0x02, 0xc0, 0xf0, 0x3c, 0x0b, 0x06, 0x63, 0x8c,
    0xcf, 0x3c, 0x0e,
    /* U+03BC "" (8x11) */
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xe6, 0xfb, 0xc0, 0xc0, 0xc0,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (11x1) */
    0xff, 0xe0,
    /* U+2018 "" (2x4) */
    0x7f,
    /* U+2019 "" (2x4) */
    0xf6,
    /* U+201C "" (6x4) */
    0x47, 0x2c, 0xf3,
    /* U+201D "" (6x4) */
    0xcf, 0x34, 0xe2,
    /* U+2022 "" (4x4) */
    0x7f, 0xf7,
    /* U+2026 "" (11x2) */
    0xc6, 0x78, 0xcc,
    /* U+2030 "" (19x11) */
    0x70, 0x60, 0x1b, 0x08, 0x03, 0x23, 0x00, 0x64, 0xc0, 0x0d, 0xb0, 0x00,
    0xe4, 0xe3, 0x81, 0xb6, 0xc8, 0x64, 0x59, 0x08, 0x8b, 0x23, 0x1b, 0x64,
    0xc1, 0xc7, 0x00,
    /* U+2190 "" (12x7) */
    0x10, 0x03, 0x00, 0x60, 0x0f, 0xff, 0x60, 0x03, 0x00, 0x10, 0x00,
    /* U+2191 "" (6x11) */
    0x21, 0xcf, 0xaf, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x00,
    /* U+2192 "" (11x5) */
    0x01, 0x80, 0x1b, 0xff, 0x80, 0x60, 0x18,
    /* U+2193 "" (6x11) */
    0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x2f, 0xf9, 0xc2, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 60, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 76, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 174, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 153, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 242, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 181, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 65, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 69, .adv_w = 86, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 76, .adv_w = 86, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 83, .adv_w = 132, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 89, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 96, .adv_w = 74, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 97, .adv_w = 103, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 98, .adv_w = 74, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 107, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 110, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 79, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 79, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 224, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 236, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 242, .adv_w = 125, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 229, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 271, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 162, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 175, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 146, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 183, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 136, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 131, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 208, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 183, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 182, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 182, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 475, .adv_w = 168, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 486, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 148, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 161, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 237, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 164, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 158, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 151, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 83, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 598, .adv_w = 107, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 607, .adv_w = 83, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 613, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 619, .adv_w = 144, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 621, .adv_w = 154, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 622, .adv_w = 141, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 152, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 148, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 696, .adv_w = 68, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 68, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 705, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 73, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 226, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 144, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 758, .adv_w = 152, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 768, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 93, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 148, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 131, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 205, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 132, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 830, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 91, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 845, .adv_w = 90, .box_w = 2, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 849, .adv_w = 91, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 856, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 858, .adv_w = 120, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 862, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 89, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 874, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 877, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 887, .adv_w = 91, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 888, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 894, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 901, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 184, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 929, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 940, .adv_w = 151, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 941, .adv_w = 200, .box_w = 11, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 943, .adv_w = 73, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 944, .adv_w = 73, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 945, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 948, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 951, .adv_w = 105, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 953, .adv_w = 217, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 343, .box_w = 19, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 219, .box_w = 12, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 994, .adv_w = 219, .box_w = 6, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1003, .adv_w = 219, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1010, .adv_w = 219, .box_w = 6, .box_h = 11, .ofs_x = 4, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_normal_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
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
    .fallback = &humid1_icon_fa7_solid_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_NORMAL_16 */
