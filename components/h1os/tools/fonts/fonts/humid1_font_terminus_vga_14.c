/*******************************************************************************
 * Font: humid1_font_terminus_vga_14 (terminus vga)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: exact-mono (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_14 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef HUMID1_FONT_TERMINUS_VGA_14
#define HUMID1_FONT_TERMINUS_VGA_14 1
#endif

#if HUMID1_FONT_TERMINUS_VGA_14

extern const lv_font_t humid1_icon_fa7_solid_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xfc, 0xf0,
    /* U+0022 "" (6x3) */
    0xcf, 0x3c, 0xc0,
    /* U+0023 "#" (7x10) */
    0x6c, 0xd9, 0xb7, 0xf6, 0xcd, 0xbf, 0xb6, 0x6c, 0xd8,
    /* U+0024 "$" (8x13) */
    0x18, 0x18, 0x7e, 0xdb, 0xd8, 0xd8, 0x7e, 0x1b, 0x1b, 0xdb, 0x7e, 0x18,
    0x18,
    /* U+0025 "%" (8x10) */
    0x66, 0xd6, 0x6c, 0x0c, 0x18, 0x18, 0x30, 0x36, 0x6b, 0x66,
    /* U+0026 "&" (7x10) */
    0x38, 0xd9, 0xb1, 0xc7, 0x7b, 0xb3, 0x66, 0xdc, 0xec,
    /* U+0027 "'" (2x3) */
    0xfc,
    /* U+0028 "(" (4x10) */
    0x36, 0xcc, 0xcc, 0xcc, 0x63,
    /* U+0029 ")" (4x10) */
    0xc6, 0x33, 0x33, 0x33, 0x6c,
    /* U+002A "" (7x5) */
    0x6c, 0x73, 0xf9, 0xc6, 0xc0,
    /* U+002B "+" (6x5) */
    0x30, 0xcf, 0xcc, 0x30,
    /* U+002C "," (3x3) */
    0x6f, 0x00,
    /* U+002D "-" (7x1) */
    0xfe,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x10) */
    0x0c, 0x31, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0x00,
    /* U+0030 "0" (7x10) */
    0x7d, 0x8f, 0x1e, 0x7d, 0xfe, 0xf9, 0xe3, 0xc6, 0xf8,
    /* U+0031 "1" (6x10) */
    0x31, 0xcf, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xf0,
    /* U+0032 "2" (7x10) */
    0x7d, 0x8f, 0x18, 0x30, 0xc3, 0x0c, 0x30, 0xc1, 0xfc,
    /* U+0033 "3" (7x10) */
    0x7d, 0x8f, 0x18, 0x33, 0xc0, 0xc1, 0xe3, 0xc6, 0xf8,
    /* U+0034 "4" (7x10) */
    0x06, 0x1c, 0x79, 0xb6, 0x78, 0xff, 0x83, 0x06, 0x0c,
    /* U+0035 "5" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0xc0, 0xc1, 0x83, 0xc6, 0xf8,
    /* U+0036 "6" (7x10) */
    0x3c, 0xc3, 0x06, 0x0f, 0xd8, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0037 "7" (7x10) */
    0xfe, 0x0c, 0x18, 0x60, 0xc3, 0x06, 0x18, 0x30, 0x60,
    /* U+0038 "8" (7x10) */
    0x7d, 0x8f, 0x1e, 0x37, 0xd8, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0039 "9" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x6f, 0xc1, 0x83, 0x0c, 0xf0,
    /* U+003A ":" (2x7) */
    0xf0, 0x3c,
    /* U+003B ";" (3x8) */
    0x6c, 0x00, 0xde,
    /* U+003C "<" (6x9) */
    0x0c, 0x63, 0x18, 0xc1, 0x83, 0x06, 0x0c,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x9) */
    0xc1, 0x83, 0x06, 0x0c, 0x63, 0x18, 0xc0,
    /* U+003F "?" (7x10) */
    0x7d, 0x8f, 0x1e, 0x30, 0xc3, 0x06, 0x00, 0x18, 0x30,
    /* U+0040 "@" (8x10) */
    0x7e, 0xc3, 0xcf, 0xdb, 0xdb, 0xdb, 0xdb, 0xcf, 0xc0, 0x7f,
    /* U+0041 "A" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0042 "B" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd8, 0xf1, 0xe3, 0xc7, 0xf8,
    /* U+0043 "C" (7x10) */
    0x7d, 0x8f, 0x1e, 0x0c, 0x18, 0x30, 0x63, 0xc6, 0xf8,
    /* U+0044 "D" (7x10) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xcd, 0xf0,
    /* U+0045 "E" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0x98, 0x30, 0x60, 0xc1, 0xfc,
    /* U+0046 "F" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0x98, 0x30, 0x60, 0xc1, 0x80,
    /* U+0047 "G" (7x10) */
    0x7d, 0x8f, 0x1e, 0x0c, 0x1b, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0048 "H" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0049 "I" (4x10) */
    0xf6, 0x66, 0x66, 0x66, 0x6f,
    /* U+004A "J" (7x10) */
    0x1e, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x66, 0xcc, 0xf0,
    /* U+004B "K" (7x10) */
    0xc7, 0x8f, 0x36, 0xcf, 0x1e, 0x36, 0x66, 0xc7, 0x8c,
    /* U+004C "L" (7x10) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xfc,
    /* U+004D "M" (8x10) */
    0x81, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+004E "N" (7x10) */
    0xc7, 0x8f, 0x1f, 0x3f, 0x7b, 0xf3, 0xe3, 0xc7, 0x8c,
    /* U+004F "O" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (7x11) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xde, 0xf8, 0x18,
    /* U+0052 "R" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xbc, 0x6c, 0xcd, 0x8c,
    /* U+0053 "S" (7x10) */
    0x7d, 0x8f, 0x06, 0x07, 0xc0, 0xc1, 0xe3, 0xc6, 0xf8,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0056 "V" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x6d, 0x9b, 0x36, 0x38, 0x70,
    /* U+0057 "W" (8x10) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xe7, 0xc3, 0x81,
    /* U+0058 "X" (7x10) */
    0xc7, 0x8d, 0xb3, 0x63, 0x87, 0x1b, 0x36, 0xc7, 0x8c,
    /* U+0059 "Y" (8x10) */
    0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x10) */
    0xfe, 0x0c, 0x18, 0x61, 0x86, 0x18, 0x60, 0xc1, 0xfc,
    /* U+005B "[" (4x10) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcf,
    /* U+005C "" (6x10) */
    0xc3, 0x06, 0x18, 0x30, 0xc1, 0x86, 0x0c, 0x30,
    /* U+005D "]" (4x10) */
    0xf3, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (6x3) */
    0x31, 0xec, 0xc0,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x2) */
    0xcc,
    /* U+0061 "a" (7x7) */
    0x7c, 0x0d, 0xfe, 0x3c, 0x78, 0xdf, 0x80,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x07, 0xec, 0x78, 0xf1, 0xe3, 0xc7, 0xf8,
    /* U+0063 "c" (7x7) */
    0x7d, 0x8f, 0x06, 0x0c, 0x18, 0xdf, 0x00,
    /* U+0064 "d" (7x10) */
    0x06, 0x0c, 0x1b, 0xfc, 0x78, 0xf1, 0xe3, 0xc6, 0xfc,
    /* U+0065 "e" (7x7) */
    0x7d, 0x8f, 0x1f, 0xfc, 0x18, 0x1f, 0x00,
    /* U+0066 "f" (7x10) */
    0x1e, 0x60, 0xc7, 0xe3, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+0067 "g" (7x9) */
    0x7f, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x7c,
    /* U+0068 "h" (7x10) */
    0xc1, 0x83, 0x07, 0xec, 0x78, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0069 "i" (4x10) */
    0x66, 0x0e, 0x66, 0x66, 0x6f,
    /* U+006A "j" (6x12) */
    0x0c, 0x30, 0x07, 0x0c, 0x30, 0xc3, 0x0f, 0x3c, 0xde,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x06, 0x3c, 0xdb, 0x3c, 0x6c, 0xcd, 0x8c,
    /* U+006C "l" (4x10) */
    0xe6, 0x66, 0x66, 0x66, 0x6f,
    /* U+006D "m" (8x7) */
    0xfe, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (7x7) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x80,
    /* U+006F "o" (7x7) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x00,
    /* U+0070 "p" (7x9) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc0,
    /* U+0071 "q" (7x9) */
    0x7f, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x06,
    /* U+0072 "r" (7x7) */
    0xdf, 0xe3, 0x86, 0x0c, 0x18, 0x30, 0x00,
    /* U+0073 "s" (7x7) */
    0x7f, 0x83, 0x03, 0xe0, 0x60, 0xff, 0x00,
    /* U+0074 "t" (7x10) */
    0x30, 0x60, 0xc7, 0xe3, 0x06, 0x0c, 0x18, 0x30, 0x3c,
    /* U+0075 "u" (7x7) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x80,
    /* U+0076 "v" (7x7) */
    0xc7, 0x8f, 0x1b, 0x66, 0xc7, 0x0e, 0x00,
    /* U+0077 "w" (8x7) */
    0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e,
    /* U+0078 "x" (7x7) */
    0xc7, 0x8d, 0xb1, 0xc6, 0xd8, 0xf1, 0x80,
    /* U+0079 "y" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x7c,
    /* U+007A "z" (7x7) */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x3f, 0x80,
    /* U+007B "{" (5x10) */
    0x3b, 0x18, 0xcc, 0x31, 0x8c, 0x61, 0xc0,
    /* U+007C "|" (2x10) */
    0xff, 0xff, 0xf0,
    /* U+007D "}" (5x10) */
    0xe1, 0x8c, 0x61, 0x98, 0xc6, 0x37, 0x00,
    /* U+007E "~" (8x3) */
    0x73, 0xdb, 0xce,
    /* U+00B0 "" (5x4) */
    0x76, 0xf6, 0xe0,
    /* U+00B1 "" (6x7) */
    0x30, 0xcf, 0xcc, 0x30, 0x0f, 0xc0,
    /* U+00B2 "" (5x6) */
    0x76, 0xc6, 0x66, 0x7c,
    /* U+00B3 "" (5x6) */
    0xf0, 0xdc, 0x31, 0xf8,
    /* U+00B5 "" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x79, 0xfd, 0xe0, 0xc0,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x6) */
    0xc6, 0xd8, 0xe1, 0xc6, 0xd8, 0xc0,
    /* U+00F7 "" (6x7) */
    0x30, 0xc0, 0x3f, 0x00, 0xc3, 0x00,
    /* U+0394 "" (8x10) */
    0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0x66, 0xc3, 0xc3, 0xff,
    /* U+03A9 "" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xb6, 0x6d, 0xdc,
    /* U+03B1 "" (8x7) */
    0x7b, 0xce, 0xcc, 0xcc, 0xcc, 0xce, 0x7b,
    /* U+03B2 "" (7x12) */
    0x79, 0x9b, 0x36, 0x4f, 0xd8, 0xf1, 0xe3, 0xc7, 0xfb, 0x06, 0x00,
    /* U+03B3 "" (8x9) */
    0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18,
    /* U+03B4 "" (7x10) */
    0x7e, 0x60, 0x63, 0xec, 0x78, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+03B5 "" (7x7) */
    0x7d, 0x8f, 0x03, 0xcc, 0x18, 0xdf, 0x00,
    /* U+03B8 "" (6x10) */
    0x7b, 0x3c, 0xf3, 0xff, 0x3c, 0xf3, 0xcd, 0xe0,
    /* U+03BB "" (8x10) */
    0x30, 0x30, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3,
    /* U+03BC "" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x79, 0xfd, 0xe0, 0xc0,
    /* U+03C0 "" (7x7) */
    0xff, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x80,
    /* U+03C3 "" (7x7) */
    0x7f, 0x9b, 0x36, 0x6c, 0xd9, 0x9e, 0x00,
    /* U+03C4 "" (8x7) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0e,
    /* U+03C6 "" (8x9) */
    0x4e, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e, 0x18, 0x18,
    /* U+03C9 "" (8x7) */
    0x66, 0xc3, 0xdb, 0xdb, 0xdb, 0xff, 0x66,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (3x3) */
    0x7b, 0x00,
    /* U+2019 "" (3x3) */
    0x6f, 0x00,
    /* U+201C "" (7x3) */
    0x67, 0x9b, 0x30,
    /* U+201D "" (7x3) */
    0x66, 0xcf, 0x30,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (8x10) */
    0xec, 0xac, 0xf8, 0x18, 0x30, 0x30, 0x60, 0x7f, 0xd5, 0xdf,
    /* U+2190 "" (7x6) */
    0x20, 0xc3, 0xff, 0xf6, 0x04, 0x00,
    /* U+2191 "" (6x10) */
    0x31, 0xef, 0xcc, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (7x6) */
    0x08, 0x1b, 0xff, 0xf0, 0xc1, 0x00,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x3f, 0x78, 0xc0,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 128, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 128, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 48, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 63, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 67, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 70, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 128, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 128, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 184, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 361, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 466, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 467, .adv_w = 128, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 468, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 524, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 547, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 590, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 598, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 657, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 128, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 128, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 684, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 687, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 697, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 701, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 709, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 710, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 716, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 722, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 759, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 768, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 810, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 840, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 848, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 849, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 851, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 853, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 856, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 859, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 861, .adv_w = 128, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 879, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 893, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0308, 0x030b, 0x030c, 0x0310, 0x0313,
    0x0314, 0x0316, 0x0319, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72,
    0x1f76, 0x1f80, 0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 36, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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

const lv_font_t humid1_font_terminus_vga_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 14,
    .base_line = 2,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 7,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = 0,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_TERMINUS_VGA_14 */
