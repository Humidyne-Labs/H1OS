/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_16 (mono normal)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_MONO_NORMAL_16
#define HUMID1_FONT_PLEX_MONO_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_MONO_NORMAL_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x11) */
    0x6d, 0xb4, 0x80, 0x7d, 0x80,
    /* U+0022 "" (5x5) */
    0xde, 0xf7, 0xbc, 0x80,
    /* U+0023 "#" (9x11) */
    0x1b, 0x0d, 0x86, 0xce, 0x71, 0x20, 0x90, 0xd9, 0xef, 0x26, 0x12, 0x09,
    0x00,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x3e, 0xda, 0xd8, 0xd8, 0x78, 0x3c, 0x1b, 0x1b, 0x1b, 0xda,
    0x7c, 0x18, 0x18,
    /* U+0025 "%" (9x11) */
    0x70, 0xac, 0xb2, 0xd9, 0x45, 0x83, 0x98, 0x12, 0x69, 0x24, 0xb2, 0x70,
    0xc0,
    /* U+0026 "&" (9x11) */
    0x1c, 0x13, 0x18, 0x0c, 0x03, 0x01, 0x8d, 0x25, 0x9e, 0xc6, 0x33, 0x8e,
    0x60,
    /* U+0027 "'" (2x5) */
    0xff, 0x80,
    /* U+0028 "(" (5x14) */
    0x19, 0x98, 0x8c, 0x63, 0x18, 0xc6, 0x10, 0xc3, 0x0c,
    /* U+0029 ")" (5x14) */
    0xc3, 0x08, 0x61, 0x08, 0x63, 0x10, 0x8c, 0x46, 0x60,
    /* U+002A "" (8x8) */
    0x18, 0x18, 0x99, 0xff, 0x38, 0x3c, 0x64, 0x44,
    /* U+002B "+" (8x7) */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x4) */
    0x6f, 0x60,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (3x3) */
    0x7d, 0x80,
    /* U+002F "/" (7x14) */
    0x06, 0x0c, 0x10, 0x60, 0xc1, 0x06, 0x08, 0x30, 0x60, 0x83, 0x04, 0x18,
    0x00,
    /* U+0030 "0" (8x11) */
    0x3c, 0x66, 0xc2, 0xc3, 0xdb, 0xdb, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0031 "1" (8x11) */
    0x38, 0x78, 0xc8, 0x88, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff,
    /* U+0032 "2" (8x11) */
    0x7c, 0xc6, 0x06, 0x06, 0x06, 0x04, 0x08, 0x30, 0x60, 0xc0, 0xff,
    /* U+0033 "3" (7x11) */
    0x7d, 0x8c, 0x18, 0x30, 0x67, 0x81, 0x81, 0x03, 0x8d, 0xf0,
    /* U+0034 "4" (9x11) */
    0x07, 0x07, 0x87, 0xc3, 0x63, 0x31, 0x99, 0x8d, 0x86, 0xff, 0x81, 0x80,
    0xc0,
    /* U+0035 "5" (8x11) */
    0x7e, 0x40, 0x40, 0xc0, 0xdc, 0x46, 0x03, 0x03, 0x03, 0xc6, 0x7c,
    /* U+0036 "6" (8x11) */
    0x1c, 0x38, 0x70, 0x60, 0xdc, 0xc6, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0037 "7" (8x11) */
    0xff, 0xc3, 0xc6, 0x06, 0x0c, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30,
    /* U+0038 "8" (8x11) */
    0x3c, 0x46, 0xc2, 0xc2, 0x46, 0x3c, 0xc6, 0xc3, 0xc3, 0xc6, 0x7c,
    /* U+0039 "9" (8x11) */
    0x3c, 0x46, 0xc2, 0xc3, 0xc3, 0xc7, 0x7e, 0x06, 0x0c, 0x18, 0x30,
    /* U+003A ":" (3x9) */
    0x7d, 0x80, 0x1f, 0x60,
    /* U+003B ";" (3x11) */
    0x7d, 0x80, 0x03, 0x7b, 0x00,
    /* U+003C "<" (7x9) */
    0x02, 0x1c, 0x73, 0x8c, 0x0e, 0x07, 0x07, 0x02,
    /* U+003D "=" (8x4) */
    0xff, 0x00, 0x00, 0xff,
    /* U+003E ">" (7x9) */
    0x81, 0xc0, 0xe0, 0x70, 0x61, 0xce, 0x70, 0x80,
    /* U+003F "?" (7x11) */
    0x7d, 0x8c, 0x18, 0x31, 0xc2, 0x00, 0x00, 0x38, 0x70, 0xe0,
    /* U+0040 "@" (8x13) */
    0x3c, 0x46, 0xc2, 0x9f, 0x93, 0x93, 0xb3, 0x93, 0x93, 0x9f, 0xc0, 0x60,
    0x3c,
    /* U+0041 "A" (9x11) */
    0x1c, 0x0e, 0x07, 0x82, 0xc3, 0x21, 0x98, 0x8c, 0xfe, 0x61, 0xb0, 0xf0,
    0x60,
    /* U+0042 "B" (8x11) */
    0xfc, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0xc6, 0xc3, 0xc3, 0xc6, 0xfc,
    /* U+0043 "C" (7x11) */
    0x3c, 0xcf, 0x0e, 0x0c, 0x18, 0x30, 0x60, 0xc2, 0xcc, 0xf0,
    /* U+0044 "D" (8x11) */
    0xfc, 0xc6, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0xc6, 0xfc,
    /* U+0045 "E" (7x11) */
    0xff, 0x83, 0x06, 0x0c, 0x1f, 0xf0, 0x60, 0xc1, 0x83, 0xf8,
    /* U+0046 "F" (8x11) */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (8x11) */
    0x3c, 0x66, 0xc2, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3, 0xc3, 0x67, 0x7b,
    /* U+0048 "H" (7x11) */
    0xc3, 0x87, 0x0e, 0x1c, 0x3f, 0xf0, 0xe1, 0xc3, 0x87, 0x08,
    /* U+0049 "I" (7x11) */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x33, 0xf8,
    /* U+004A "J" (7x11) */
    0x7e, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0x89, 0xe0,
    /* U+004B "K" (8x11) */
    0xc3, 0xc6, 0xcc, 0xdc, 0xd8, 0xf8, 0xec, 0xcc, 0xc6, 0xc3, 0xc3,
    /* U+004C "L" (7x11) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xf8,
    /* U+004D "M" (8x11) */
    0xc7, 0xe7, 0xe7, 0xff, 0xbb, 0x9b, 0x93, 0x83, 0x83, 0x83, 0x83,
    /* U+004E "N" (7x11) */
    0xe3, 0xc7, 0x8f, 0x9d, 0x3b, 0x76, 0xe7, 0xcf, 0x8f, 0x18,
    /* U+004F "O" (8x11) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0050 "P" (8x11) */
    0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (8x13) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0x66, 0x3c, 0x18,
    0x1e,
    /* U+0052 "R" (8x11) */
    0xfe, 0xc6, 0xc3, 0xc3, 0xc7, 0xfe, 0xcc, 0xcc, 0xc6, 0xc6, 0xc3,
    /* U+0053 "S" (8x11) */
    0x3e, 0xc2, 0xc0, 0xc0, 0x60, 0x3c, 0x06, 0x03, 0x03, 0xc6, 0x7c,
    /* U+0054 "T" (9x11) */
    0xff, 0x86, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+0055 "U" (8x11) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0xc2, 0xc2, 0x46, 0x3c,
    /* U+0056 "V" (8x11) */
    0x83, 0xc3, 0xc2, 0xc6, 0x66, 0x66, 0x64, 0x2c, 0x3c, 0x38, 0x38,
    /* U+0057 "W" (9x11) */
    0xc0, 0xa0, 0x50, 0x29, 0xb4, 0xda, 0xed, 0x56, 0xaf, 0x73, 0xb9, 0xdc,
    0xc0,
    /* U+0058 "X" (8x11) */
    0xc3, 0xc6, 0x66, 0x3c, 0x38, 0x18, 0x3c, 0x6c, 0x66, 0xc6, 0xc3,
    /* U+0059 "Y" (9x11) */
    0xc1, 0xb0, 0xcc, 0xc6, 0x61, 0xe0, 0xe0, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+005A "Z" (8x11) */
    0xff, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60, 0xc0, 0xff,
    /* U+005B "[" (5x14) */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x7c,
    /* U+005C "" (6x14) */
    0x82, 0x0c, 0x10, 0x61, 0x82, 0x0c, 0x10, 0x61, 0x82, 0x0c, 0x10,
    /* U+005D "]" (6x14) */
    0xfc, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0f, 0xf0,
    /* U+005E "^" (8x7) */
    0x18, 0x3c, 0x6c, 0x66, 0xc6, 0xc3, 0x83,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (2x3) */
    0xd4,
    /* U+0061 "a" (8x8) */
    0x78, 0x46, 0x06, 0x7e, 0xc6, 0xc6, 0xc6, 0x7b,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xdc,
    /* U+0063 "c" (7x8) */
    0x3c, 0xcf, 0x06, 0x0c, 0x18, 0x19, 0x9e,
    /* U+0064 "d" (7x12) */
    0x02, 0x04, 0x08, 0x17, 0xb8, 0xf0, 0xe1, 0xc3, 0x87, 0x1b, 0xd0,
    /* U+0065 "e" (8x8) */
    0x3c, 0x46, 0xc3, 0xff, 0xc0, 0xc0, 0x66, 0x3c,
    /* U+0066 "f" (8x12) */
    0x0f, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xfe,
    /* U+0067 "g" (8x12) */
    0x07, 0x3c, 0x66, 0xc6, 0x46, 0x66, 0x7c, 0x40, 0x7e, 0xc3, 0xc3, 0x7e,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0x0d, 0xd8, 0xf0, 0xe1, 0xc3, 0x87, 0x0e, 0x10,
    /* U+0069 "i" (7x12) */
    0x30, 0x60, 0x00, 0x0f, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc7, 0xf0,
    /* U+006A "j" (6x15) */
    0x0c, 0x30, 0x00, 0xfc, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x37, 0x80,
    /* U+006B "k" (8x12) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf8, 0xfc, 0xcc, 0xc6, 0xc3,
    /* U+006C "l" (8x12) */
    0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff,
    /* U+006D "m" (8x8) */
    0xb6, 0x93, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b, 0x9b,
    /* U+006E "n" (7x8) */
    0xdd, 0x8f, 0x0e, 0x1c, 0x38, 0x70, 0xe1,
    /* U+006F "o" (8x8) */
    0x3c, 0x46, 0xc2, 0xc3, 0xc3, 0xc2, 0x46, 0x3c,
    /* U+0070 "p" (8x11) */
    0xdc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xdc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x11) */
    0x7b, 0x8f, 0x0e, 0x1c, 0x38, 0x71, 0xbd, 0x02, 0x04, 0x08,
    /* U+0072 "r" (8x8) */
    0xf3, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfe,
    /* U+0073 "s" (7x8) */
    0x3c, 0x87, 0x03, 0xc1, 0xe0, 0x71, 0xbe,
    /* U+0074 "t" (7x11) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x78,
    /* U+0075 "u" (7x8) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xbf,
    /* U+0076 "v" (8x8) */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x2c, 0x38, 0x18,
    /* U+0077 "w" (9x8) */
    0xcc, 0xa6, 0x53, 0x2a, 0xb5, 0x5a, 0x99, 0xcc, 0xe6,
    /* U+0078 "x" (8x8) */
    0xc6, 0x66, 0x3c, 0x38, 0x38, 0x2c, 0x66, 0xc7,
    /* U+0079 "y" (8x11) */
    0xc3, 0xc2, 0x46, 0x64, 0x2c, 0x3c, 0x38, 0x18, 0x10, 0x30, 0xe0,
    /* U+007A "z" (7x8) */
    0xfe, 0x0c, 0x30, 0xc3, 0x0c, 0x18, 0x7f,
    /* U+007B "{" (6x14) */
    0x3c, 0x82, 0x0c, 0x10, 0x4e, 0x04, 0x10, 0xc2, 0x08, 0x20, 0xf0,
    /* U+007C "|" (2x14) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+007D "}" (6x14) */
    0xf0, 0x43, 0x0c, 0x61, 0x83, 0xd8, 0x60, 0x83, 0x04, 0x13, 0xc0,
    /* U+007E "~" (8x3) */
    0x73, 0xdb, 0x8e,
    /* U+00B0 "" (6x5) */
    0x73, 0x28, 0xf2, 0x70,
    /* U+00B1 "" (8x10) */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x00, 0xff,
    /* U+00B2 "" (4x6) */
    0xeb, 0x36, 0xcf,
    /* U+00B3 "" (4x6) */
    0xe3, 0x61, 0x9e,
    /* U+00B5 "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xff, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (3x3) */
    0x7d, 0x80,
    /* U+00D7 "" (6x7) */
    0x87, 0x37, 0x8c, 0x7b, 0x38, 0x40,
    /* U+00F7 "" (8x7) */
    0x18, 0x18, 0x00, 0xff, 0x00, 0x18, 0x18,
    /* U+0394 "" (8x11) */
    0x38, 0x38, 0x3c, 0x6c, 0x64, 0x66, 0x46, 0xc6, 0xc3, 0xc3, 0xff,
    /* U+03A9 "" (8x11) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0x66, 0x6c, 0xef,
    /* U+03BC "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xff, 0xc1, 0x83, 0x00,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (10x1) */
    0xff, 0xc0,
    /* U+2018 "" (3x5) */
    0x2d, 0xfc,
    /* U+2019 "" (4x5) */
    0x76, 0x6c, 0xc0,
    /* U+201C "" (7x5) */
    0x22, 0xcd, 0x9f, 0x7c, 0xc0,
    /* U+201D "" (7x5) */
    0xef, 0x9b, 0x34, 0x48, 0x80,
    /* U+2022 "" (4x4) */
    0xef, 0xfe,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (10x11) */
    0x70, 0x34, 0x09, 0x83, 0x44, 0x76, 0x0e, 0x07, 0xb8, 0x9a, 0x24, 0xc9,
    0xa1, 0xb8,
    /* U+2190 "" (9x7) */
    0x10, 0x1c, 0x1c, 0x1f, 0xf7, 0x01, 0xc0, 0x40,
    /* U+2191 "" (6x11) */
    0x21, 0xcf, 0xab, 0x20, 0x82, 0x08, 0x20, 0x82, 0x00,
    /* U+2192 "" (9x5) */
    0x06, 0x01, 0xbf, 0xe0, 0x60, 0x60,
    /* U+2193 "" (6x11) */
    0x20, 0x82, 0x08, 0x20, 0x82, 0x2b, 0xf9, 0xc2, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 9, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 37, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 154, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 65, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 83, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 98, .adv_w = 154, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 154, .box_w = 5, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 116, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 154, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 236, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 248, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 279, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 463, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 577, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 588, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 599, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 606, .adv_w = 154, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 607, .adv_w = 154, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 608, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 678, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 712, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 770, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 780, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 848, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 866, .adv_w = 154, .box_w = 2, .box_h = 14, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 870, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 881, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 884, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 888, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 901, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 904, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 914, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 916, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 922, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 929, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 940, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 961, .adv_w = 154, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 962, .adv_w = 154, .box_w = 10, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 964, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 966, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 969, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 974, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 979, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 981, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 997, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1005, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1014, .adv_w = 154, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1020, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_normal_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_16 */
