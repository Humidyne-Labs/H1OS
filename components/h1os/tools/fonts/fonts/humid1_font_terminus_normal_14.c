/*******************************************************************************
 * Font: humid1_font_terminus_normal_14 (terminus normal)
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

#ifndef HUMID1_FONT_TERMINUS_NORMAL_14
#define HUMID1_FONT_TERMINUS_NORMAL_14 1
#endif

#if HUMID1_FONT_TERMINUS_NORMAL_14

extern const lv_font_t humid1_icon_fa7_solid_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (1x10) */
    0xfe, 0xc0,
    /* U+0022 "" (4x3) */
    0x99, 0x90,
    /* U+0023 "#" (6x10) */
    0x49, 0x24, 0xbf, 0x49, 0x2f, 0xd2, 0x49, 0x20,
    /* U+0024 "$" (7x13) */
    0x10, 0x21, 0xf4, 0x99, 0x12, 0x1f, 0x09, 0x13, 0x25, 0xf0, 0x81, 0x00,
    /* U+0025 "%" (7x10) */
    0x65, 0x29, 0xa0, 0x41, 0x02, 0x08, 0x16, 0x52, 0x98,
    /* U+0026 "&" (6x10) */
    0x31, 0x24, 0x8c, 0x62, 0x58, 0xa2, 0x89, 0xd0,
    /* U+0027 "'" (1x3) */
    0xe0,
    /* U+0028 "(" (3x10) */
    0x2a, 0x49, 0x24, 0x44,
    /* U+0029 ")" (3x10) */
    0x88, 0x92, 0x49, 0x50,
    /* U+002A "" (6x5) */
    0x48, 0xcf, 0xcc, 0x48,
    /* U+002B "+" (5x5) */
    0x21, 0x3e, 0x42, 0x00,
    /* U+002C "," (2x3) */
    0x58,
    /* U+002D "-" (6x1) */
    0xfc,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (5x10) */
    0x08, 0x44, 0x22, 0x11, 0x08, 0x84, 0x00,
    /* U+0030 "0" (6x10) */
    0x7a, 0x18, 0x63, 0x96, 0x9c, 0x61, 0x85, 0xe0,
    /* U+0031 "1" (5x10) */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x27, 0xc0,
    /* U+0032 "2" (6x10) */
    0x7a, 0x18, 0x41, 0x08, 0x42, 0x10, 0x83, 0xf0,
    /* U+0033 "3" (6x10) */
    0x7a, 0x18, 0x41, 0x38, 0x10, 0x61, 0x85, 0xe0,
    /* U+0034 "4" (6x10) */
    0x04, 0x31, 0x49, 0x46, 0x1f, 0xc1, 0x04, 0x10,
    /* U+0035 "5" (6x10) */
    0xfe, 0x08, 0x20, 0xf8, 0x10, 0x41, 0x85, 0xe0,
    /* U+0036 "6" (6x10) */
    0x39, 0x08, 0x20, 0xfa, 0x18, 0x61, 0x85, 0xe0,
    /* U+0037 "7" (6x10) */
    0xfc, 0x10, 0x42, 0x08, 0x41, 0x08, 0x20, 0x80,
    /* U+0038 "8" (6x10) */
    0x7a, 0x18, 0x61, 0x7a, 0x18, 0x61, 0x85, 0xe0,
    /* U+0039 "9" (6x10) */
    0x7a, 0x18, 0x61, 0x85, 0xf0, 0x41, 0x09, 0xc0,
    /* U+003A ":" (1x7) */
    0xc6,
    /* U+003B ";" (2x8) */
    0x50, 0x16,
    /* U+003C "<" (5x9) */
    0x08, 0x88, 0x88, 0x20, 0x82, 0x08,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (5x9) */
    0x82, 0x08, 0x20, 0x88, 0x88, 0x80,
    /* U+003F "?" (6x10) */
    0x7a, 0x18, 0x61, 0x08, 0x41, 0x00, 0x10, 0x40,
    /* U+0040 "@" (7x10) */
    0x7d, 0x06, 0x7d, 0x1a, 0x34, 0x69, 0xcd, 0x80, 0xfc,
    /* U+0041 "A" (6x10) */
    0x7a, 0x18, 0x61, 0x87, 0xf8, 0x61, 0x86, 0x10,
    /* U+0042 "B" (6x10) */
    0xfa, 0x18, 0x61, 0xfa, 0x18, 0x61, 0x87, 0xe0,
    /* U+0043 "C" (6x10) */
    0x7a, 0x18, 0x60, 0x82, 0x08, 0x21, 0x85, 0xe0,
    /* U+0044 "D" (6x10) */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x61, 0x8b, 0xc0,
    /* U+0045 "E" (6x10) */
    0xfe, 0x08, 0x20, 0xf2, 0x08, 0x20, 0x83, 0xf0,
    /* U+0046 "F" (6x10) */
    0xfe, 0x08, 0x20, 0xf2, 0x08, 0x20, 0x82, 0x00,
    /* U+0047 "G" (6x10) */
    0x7a, 0x18, 0x60, 0x82, 0x78, 0x61, 0x85, 0xe0,
    /* U+0048 "H" (6x10) */
    0x86, 0x18, 0x61, 0xfe, 0x18, 0x61, 0x86, 0x10,
    /* U+0049 "I" (3x10) */
    0xe9, 0x24, 0x92, 0x5c,
    /* U+004A "J" (6x10) */
    0x1c, 0x20, 0x82, 0x08, 0x20, 0xa2, 0x89, 0xc0,
    /* U+004B "K" (6x10) */
    0x86, 0x29, 0x28, 0xc3, 0x0a, 0x24, 0x8a, 0x10,
    /* U+004C "L" (6x10) */
    0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x83, 0xf0,
    /* U+004D "M" (7x10) */
    0x83, 0x8e, 0xac, 0x99, 0x30, 0x60, 0xc1, 0x83, 0x04,
    /* U+004E "N" (6x10) */
    0x86, 0x18, 0x71, 0xa6, 0x58, 0xe1, 0x86, 0x10,
    /* U+004F "O" (6x10) */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x61, 0x85, 0xe0,
    /* U+0050 "P" (6x10) */
    0xfa, 0x18, 0x61, 0x87, 0xe8, 0x20, 0x82, 0x00,
    /* U+0051 "Q" (6x11) */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x61, 0x95, 0xe0, 0x40,
    /* U+0052 "R" (6x10) */
    0xfa, 0x18, 0x61, 0x87, 0xea, 0x24, 0x8a, 0x10,
    /* U+0053 "S" (6x10) */
    0x7a, 0x18, 0x20, 0x78, 0x10, 0x61, 0x85, 0xe0,
    /* U+0054 "T" (7x10) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20,
    /* U+0055 "U" (6x10) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x85, 0xe0,
    /* U+0056 "V" (6x10) */
    0x86, 0x18, 0x61, 0x85, 0x24, 0x92, 0x30, 0xc0,
    /* U+0057 "W" (7x10) */
    0x83, 0x06, 0x0c, 0x18, 0x32, 0x64, 0xd5, 0xc7, 0x04,
    /* U+0058 "X" (6x10) */
    0x86, 0x14, 0x92, 0x30, 0xc4, 0x92, 0x86, 0x10,
    /* U+0059 "Y" (7x10) */
    0x83, 0x05, 0x12, 0x22, 0x82, 0x04, 0x08, 0x10, 0x20,
    /* U+005A "Z" (6x10) */
    0xfc, 0x10, 0x42, 0x10, 0x84, 0x20, 0x83, 0xf0,
    /* U+005B "[" (3x10) */
    0xf2, 0x49, 0x24, 0x9c,
    /* U+005C "" (5x10) */
    0x84, 0x10, 0x82, 0x10, 0x42, 0x08, 0x40,
    /* U+005D "]" (3x10) */
    0xe4, 0x92, 0x49, 0x3c,
    /* U+005E "^" (5x3) */
    0x22, 0xa2,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x2) */
    0x90,
    /* U+0061 "a" (6x7) */
    0x78, 0x17, 0xe1, 0x86, 0x17, 0xc0,
    /* U+0062 "b" (6x10) */
    0x82, 0x08, 0x3e, 0x86, 0x18, 0x61, 0x87, 0xe0,
    /* U+0063 "c" (6x7) */
    0x7a, 0x18, 0x20, 0x82, 0x17, 0x80,
    /* U+0064 "d" (6x10) */
    0x04, 0x10, 0x5f, 0x86, 0x18, 0x61, 0x85, 0xf0,
    /* U+0065 "e" (6x7) */
    0x7a, 0x18, 0x7f, 0x82, 0x07, 0x80,
    /* U+0066 "f" (6x10) */
    0x1c, 0x82, 0x3e, 0x20, 0x82, 0x08, 0x20, 0x80,
    /* U+0067 "g" (6x9) */
    0x7e, 0x18, 0x61, 0x86, 0x17, 0xc1, 0x78,
    /* U+0068 "h" (6x10) */
    0x82, 0x08, 0x3e, 0x86, 0x18, 0x61, 0x86, 0x10,
    /* U+0069 "i" (3x10) */
    0x48, 0x64, 0x92, 0x5c,
    /* U+006A "j" (5x12) */
    0x08, 0x40, 0x30, 0x84, 0x21, 0x0c, 0x62, 0xe0,
    /* U+006B "k" (6x10) */
    0x82, 0x08, 0x21, 0x8a, 0x4e, 0x24, 0x8a, 0x10,
    /* U+006C "l" (3x10) */
    0xc9, 0x24, 0x92, 0x5c,
    /* U+006D "m" (7x7) */
    0xfd, 0x26, 0x4c, 0x99, 0x32, 0x64, 0x80,
    /* U+006E "n" (6x7) */
    0xfa, 0x18, 0x61, 0x86, 0x18, 0x40,
    /* U+006F "o" (6x7) */
    0x7a, 0x18, 0x61, 0x86, 0x17, 0x80,
    /* U+0070 "p" (6x9) */
    0xfa, 0x18, 0x61, 0x86, 0x1f, 0xa0, 0x80,
    /* U+0071 "q" (6x9) */
    0x7e, 0x18, 0x61, 0x86, 0x17, 0xc1, 0x04,
    /* U+0072 "r" (6x7) */
    0xbf, 0x08, 0x20, 0x82, 0x08, 0x00,
    /* U+0073 "s" (6x7) */
    0x7e, 0x08, 0x1e, 0x04, 0x1f, 0x80,
    /* U+0074 "t" (6x10) */
    0x20, 0x82, 0x3e, 0x20, 0x82, 0x08, 0x20, 0x70,
    /* U+0075 "u" (6x7) */
    0x86, 0x18, 0x61, 0x86, 0x17, 0xc0,
    /* U+0076 "v" (6x7) */
    0x86, 0x18, 0x52, 0x48, 0xc3, 0x00,
    /* U+0077 "w" (7x7) */
    0x83, 0x06, 0x4c, 0x99, 0x32, 0x5f, 0x00,
    /* U+0078 "x" (6x7) */
    0x86, 0x14, 0x8c, 0x4a, 0x18, 0x40,
    /* U+0079 "y" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x17, 0xc1, 0x78,
    /* U+007A "z" (6x7) */
    0xfc, 0x21, 0x08, 0x42, 0x0f, 0xc0,
    /* U+007B "{" (4x10) */
    0x34, 0x44, 0x84, 0x44, 0x43,
    /* U+007C "|" (1x10) */
    0xff, 0xc0,
    /* U+007D "}" (4x10) */
    0xc2, 0x22, 0x12, 0x22, 0x2c,
    /* U+007E "~" (7x3) */
    0x63, 0x26, 0x30,
    /* U+00B0 "" (4x4) */
    0x69, 0x96,
    /* U+00B1 "" (5x7) */
    0x21, 0x3e, 0x42, 0x03, 0xe0,
    /* U+00B2 "" (4x6) */
    0x69, 0x12, 0x4f,
    /* U+00B3 "" (4x6) */
    0xe1, 0x61, 0x1e,
    /* U+00B5 "" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x3f, 0x60, 0x80,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (6x6) */
    0x85, 0x23, 0x0c, 0x4a, 0x10,
    /* U+00F7 "" (5x7) */
    0x21, 0x01, 0xf0, 0x10, 0x80,
    /* U+0394 "" (7x10) */
    0x10, 0x20, 0xa1, 0x44, 0x48, 0x91, 0x41, 0x83, 0xfc,
    /* U+03A9 "" (6x10) */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x52, 0x4b, 0x30,
    /* U+03B1 "" (6x7) */
    0x76, 0x38, 0xa2, 0x8a, 0x37, 0x40,
    /* U+03B2 "" (6x12) */
    0x72, 0x28, 0xa4, 0xfa, 0x18, 0x61, 0x87, 0xe8, 0x20,
    /* U+03B3 "" (7x9) */
    0x83, 0x05, 0x12, 0x22, 0x85, 0x04, 0x08, 0x10,
    /* U+03B4 "" (6x10) */
    0x7c, 0x81, 0x1e, 0x86, 0x18, 0x61, 0x85, 0xe0,
    /* U+03B5 "" (6x7) */
    0x7a, 0x18, 0x1c, 0x82, 0x17, 0x80,
    /* U+03B8 "" (5x10) */
    0x74, 0x63, 0x1f, 0xc6, 0x31, 0x8b, 0x80,
    /* U+03BB "" (7x10) */
    0x20, 0x40, 0x40, 0x82, 0x85, 0x11, 0x22, 0x83, 0x04,
    /* U+03BC "" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x3f, 0x60, 0x80,
    /* U+03C0 "" (6x7) */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x40,
    /* U+03C3 "" (6x7) */
    0x7e, 0x28, 0xa2, 0x8a, 0x27, 0x00,
    /* U+03C4 "" (7x7) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x03, 0x00,
    /* U+03C6 "" (7x9) */
    0x4d, 0x26, 0x4c, 0x99, 0x32, 0x5f, 0x08, 0x10,
    /* U+03C9 "" (7x7) */
    0x45, 0x06, 0x4c, 0x99, 0x32, 0x5b, 0x00,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (7x1) */
    0xfe,
    /* U+2018 "" (2x3) */
    0x68,
    /* U+2019 "" (2x3) */
    0x58,
    /* U+201C "" (5x3) */
    0x4c, 0xa4,
    /* U+201D "" (5x3) */
    0x4a, 0x64,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (7x2) */
    0x93, 0x24,
    /* U+2030 "" (7x10) */
    0x49, 0x51, 0x40, 0x82, 0x04, 0x10, 0x2a, 0xab, 0x28,
    /* U+2190 "" (7x5) */
    0x20, 0x83, 0xfa, 0x02, 0x00,
    /* U+2191 "" (5x10) */
    0x23, 0xaa, 0x42, 0x10, 0x84, 0x21, 0x00,
    /* U+2192 "" (7x5) */
    0x08, 0x0b, 0xf8, 0x20, 0x80,
    /* U+2193 "" (5x10) */
    0x21, 0x08, 0x42, 0x10, 0x95, 0x71, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 128, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 4, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 24, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 128, .box_w = 1, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 42, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 54, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 58, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 59, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 60, .adv_w = 128, .box_w = 1, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 128, .box_w = 1, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 128, .box_w = 2, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 150, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 159, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 316, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 408, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 409, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 410, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 459, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 479, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 128, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 517, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 524, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 576, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 128, .box_w = 1, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 597, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 599, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 128, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 607, .adv_w = 128, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 610, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 617, .adv_w = 128, .box_w = 1, .box_h = 2, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 618, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 623, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 628, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 660, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 668, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 705, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 732, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 740, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 741, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 742, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 743, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 745, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 747, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 749, .adv_w = 128, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 765, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 777, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_terminus_normal_14 = {
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

#endif /* #if HUMID1_FONT_TERMINUS_NORMAL_14 */
