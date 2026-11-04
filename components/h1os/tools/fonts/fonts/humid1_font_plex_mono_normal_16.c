/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_16 (IBM Plex Mono Normal)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_MONO_NORMAL_16
#define HUMID1_FONT_PLEX_MONO_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_MONO_NORMAL_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0x55, 0x55, 0x0f,
    /* U+0022 "" (4x4) */
    0x99, 0x99,
    /* U+0023 "#" (9x12) */
    0x19, 0x09, 0x84, 0xc2, 0x4f, 0x39, 0x90, 0x99, 0xcf, 0x24, 0x32, 0x19,
    0x09, 0x80,
    /* U+0024 "$" (7x16) */
    0x10, 0x21, 0xf6, 0xb9, 0x12, 0x34, 0x3c, 0x1c, 0x24, 0x4c, 0x9d, 0x6f,
    0x84, 0x08,
    /* U+0025 "%" (9x12) */
    0x70, 0xc4, 0xa2, 0x51, 0x48, 0xe3, 0x80, 0x1c, 0x71, 0x28, 0xa4, 0x52,
    0x30, 0xe0,
    /* U+0026 "&" (8x12) */
    0x38, 0x44, 0x40, 0x40, 0x60, 0x73, 0xd2, 0x8a, 0x8e, 0x86, 0xca, 0x7b,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (4x16) */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x84, 0x46, 0x21,
    /* U+0029 ")" (4x16) */
    0x84, 0x22, 0x11, 0x11, 0x11, 0x12, 0x24, 0x48,
    /* U+002A "" (7x8) */
    0x10, 0x20, 0x47, 0xb3, 0x87, 0x0a, 0x22,
    /* U+002B "+" (8x8) */
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10,
    /* U+002C "," (3x4) */
    0x6d, 0x60,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (7x16) */
    0x02, 0x0c, 0x10, 0x20, 0xc1, 0x02, 0x08, 0x10, 0x20, 0x81, 0x02, 0x08,
    0x10, 0x60,
    /* U+0030 "0" (8x12) */
    0x3c, 0x42, 0x82, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x82, 0x42, 0x3c,
    /* U+0031 "1" (7x12) */
    0x30, 0xe3, 0x44, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x47, 0xf0,
    /* U+0032 "2" (7x12) */
    0x7d, 0x8a, 0x08, 0x10, 0x20, 0xc3, 0x0c, 0x30, 0xc3, 0x07, 0xf0,
    /* U+0033 "3" (7x12) */
    0x3c, 0x8c, 0x08, 0x10, 0x67, 0x01, 0x81, 0x02, 0x07, 0x13, 0xc0,
    /* U+0034 "4" (9x12) */
    0x06, 0x07, 0x02, 0x83, 0x41, 0x21, 0x90, 0x88, 0xc4, 0x42, 0x7f, 0xc0,
    0x80, 0x40,
    /* U+0035 "5" (7x12) */
    0xfd, 0x02, 0x04, 0x08, 0x17, 0xb1, 0x81, 0x03, 0x07, 0x13, 0xc0,
    /* U+0036 "6" (7x12) */
    0x18, 0x61, 0x82, 0x0b, 0x98, 0xa0, 0xc1, 0x83, 0x05, 0x11, 0xc0,
    /* U+0037 "7" (8x12) */
    0xff, 0x82, 0x86, 0x06, 0x04, 0x0c, 0x08, 0x18, 0x10, 0x10, 0x30, 0x20,
    /* U+0038 "8" (8x12) */
    0x3c, 0x66, 0x42, 0x42, 0x66, 0x18, 0x66, 0x81, 0x81, 0x81, 0x42, 0x3c,
    /* U+0039 "9" (7x12) */
    0x38, 0x8a, 0x0c, 0x18, 0x38, 0xde, 0x82, 0x04, 0x18, 0x61, 0x80,
    /* U+003A ":" (2x9) */
    0xf0, 0x03, 0xc0,
    /* U+003B ";" (2x11) */
    0xf0, 0x03, 0xe8,
    /* U+003C "<" (7x9) */
    0x02, 0x1c, 0x63, 0x0c, 0x18, 0x0c, 0x0e, 0x06,
    /* U+003D "=" (8x4) */
    0xff, 0x00, 0x00, 0xff,
    /* U+003E ">" (7x9) */
    0x81, 0xc0, 0xc0, 0x60, 0x60, 0xc6, 0x38, 0xc0,
    /* U+003F "?" (7x12) */
    0x3d, 0x8e, 0x08, 0x10, 0x20, 0x86, 0x08, 0x00, 0x00, 0xc1, 0x80,
    /* U+0040 "@" (7x13) */
    0x3c, 0x8a, 0x0c, 0x79, 0x32, 0x64, 0xc9, 0x93, 0x1f, 0x02, 0x03, 0xc0,
    /* U+0041 "A" (8x12) */
    0x18, 0x38, 0x28, 0x24, 0x24, 0x64, 0x46, 0x7e, 0xc2, 0x82, 0x83, 0x81,
    /* U+0042 "B" (7x12) */
    0xfd, 0x0e, 0x0c, 0x18, 0x7f, 0xa1, 0xc1, 0x83, 0x06, 0x17, 0xe0,
    /* U+0043 "C" (7x12) */
    0x3c, 0x8e, 0x0c, 0x08, 0x10, 0x20, 0x40, 0x81, 0x05, 0x19, 0xe0,
    /* U+0044 "D" (7x12) */
    0xf9, 0x0a, 0x14, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x0a, 0x17, 0xc0,
    /* U+0045 "E" (7x12) */
    0xff, 0x02, 0x04, 0x08, 0x1f, 0xa0, 0x40, 0x81, 0x02, 0x07, 0xf0,
    /* U+0046 "F" (7x12) */
    0xff, 0x02, 0x04, 0x08, 0x1f, 0xa0, 0x40, 0x81, 0x02, 0x04, 0x00,
    /* U+0047 "G" (7x12) */
    0x3c, 0x8e, 0x0c, 0x08, 0x10, 0x23, 0xc1, 0x83, 0x05, 0x19, 0xd0,
    /* U+0048 "H" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x3f, 0xe0, 0xc1, 0x83, 0x06, 0x0c, 0x10,
    /* U+0049 "I" (7x12) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x47, 0xf0,
    /* U+004A "J" (6x12) */
    0x7c, 0x10, 0x41, 0x04, 0x10, 0x41, 0x06, 0x1c, 0xde,
    /* U+004B "K" (7x12) */
    0x87, 0x0a, 0x34, 0xcb, 0x16, 0x34, 0x6c, 0x8d, 0x0a, 0x1c, 0x10,
    /* U+004C "L" (6x12) */
    0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x82, 0x08, 0x3f,
    /* U+004D "M" (7x12) */
    0xc7, 0x8f, 0x1d, 0x5a, 0xb7, 0x64, 0xc9, 0x83, 0x06, 0x0c, 0x10,
    /* U+004E "N" (7x12) */
    0xc3, 0x87, 0x8d, 0x1b, 0x32, 0x64, 0xcd, 0x8b, 0x1e, 0x1c, 0x30,
    /* U+004F "O" (8x12) */
    0x3c, 0x42, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x42, 0x3c,
    /* U+0050 "P" (7x12) */
    0xfd, 0x0e, 0x0c, 0x18, 0x30, 0xff, 0x40, 0x81, 0x02, 0x04, 0x00,
    /* U+0051 "Q" (8x15) */
    0x3c, 0x42, 0xc2, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x7c,
    0x10, 0x10, 0x0e,
    /* U+0052 "R" (7x12) */
    0xfd, 0x0e, 0x0c, 0x18, 0x30, 0xff, 0x4c, 0x89, 0x1a, 0x14, 0x10,
    /* U+0053 "S" (7x12) */
    0x7d, 0x8e, 0x04, 0x0c, 0x0f, 0x07, 0x01, 0x03, 0x07, 0x13, 0xe0,
    /* U+0054 "T" (9x12) */
    0xff, 0x84, 0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+0055 "U" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x05, 0x13, 0xe0,
    /* U+0056 "V" (8x12) */
    0x83, 0x83, 0xc2, 0x42, 0x46, 0x46, 0x64, 0x24, 0x2c, 0x38, 0x38, 0x18,
    /* U+0057 "W" (9x12) */
    0x81, 0xe0, 0xf0, 0x79, 0x25, 0xd2, 0xa9, 0x54, 0xaa, 0x55, 0x3b, 0x98,
    0xcc, 0x60,
    /* U+0058 "X" (8x12) */
    0x83, 0xc2, 0x66, 0x24, 0x38, 0x18, 0x18, 0x3c, 0x64, 0x46, 0xc2, 0x83,
    /* U+0059 "Y" (9x12) */
    0xc1, 0xa0, 0x98, 0xc4, 0x41, 0x40, 0xa0, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+005A "Z" (8x12) */
    0xff, 0x03, 0x06, 0x04, 0x0c, 0x08, 0x10, 0x30, 0x20, 0x40, 0xc0, 0xff,
    /* U+005B "[" (4x15) */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf0,
    /* U+005C "" (6x16) */
    0x82, 0x08, 0x10, 0x41, 0x82, 0x08, 0x30, 0x41, 0x02, 0x08, 0x20, 0x41,
    /* U+005D "]" (4x15) */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xf0,
    /* U+005E "^" (8x7) */
    0x18, 0x38, 0x2c, 0x64, 0x42, 0xc2, 0x81,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (2x3) */
    0xd4,
    /* U+0061 "a" (8x9) */
    0x78, 0xcc, 0x04, 0x04, 0x7c, 0x84, 0x84, 0x8c, 0x77,
    /* U+0062 "b" (7x13) */
    0x81, 0x02, 0x04, 0x0b, 0x98, 0xa0, 0xc1, 0x83, 0x06, 0x0e, 0x2b, 0x80,
    /* U+0063 "c" (6x9) */
    0x39, 0x18, 0x20, 0x82, 0x08, 0x11, 0x38,
    /* U+0064 "d" (7x13) */
    0x02, 0x04, 0x08, 0x13, 0xa8, 0xe0, 0xc1, 0x83, 0x06, 0x0a, 0x33, 0xa0,
    /* U+0065 "e" (7x9) */
    0x38, 0x8a, 0x0c, 0x1f, 0xf0, 0x20, 0x23, 0x3c,
    /* U+0066 "f" (7x13) */
    0x1e, 0x20, 0x40, 0x8f, 0xe2, 0x04, 0x08, 0x10, 0x20, 0x40, 0x8f, 0xe0,
    /* U+0067 "g" (8x14) */
    0x03, 0x04, 0x3e, 0x42, 0x42, 0x42, 0x3c, 0x40, 0x40, 0x40, 0x7e, 0x81,
    0x81, 0x7e,
    /* U+0068 "h" (6x13) */
    0x82, 0x08, 0x20, 0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x84,
    /* U+0069 "i" (7x13) */
    0x18, 0x30, 0x00, 0x0f, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x8f, 0xe0,
    /* U+006A "j" (6x16) */
    0x0c, 0x30, 0x00, 0xfc, 0x10, 0x41, 0x04, 0x10, 0x41, 0x04, 0x10, 0x7f,
    /* U+006B "k" (7x13) */
    0x81, 0x02, 0x04, 0x08, 0x51, 0x24, 0x50, 0xd1, 0x32, 0x34, 0x28, 0x60,
    /* U+006C "l" (7x13) */
    0xf0, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x8f, 0xe0,
    /* U+006D "m" (7x9) */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x92,
    /* U+006E "n" (6x9) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x84,
    /* U+006F "o" (7x9) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xa2, 0x38,
    /* U+0070 "p" (7x12) */
    0xb9, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xe2, 0xb9, 0x02, 0x04, 0x00,
    /* U+0071 "q" (7x12) */
    0x3a, 0x8e, 0x0c, 0x18, 0x30, 0x60, 0xa3, 0x3a, 0x04, 0x08, 0x10,
    /* U+0072 "r" (7x9) */
    0xf6, 0x30, 0x40, 0x81, 0x02, 0x04, 0x08, 0xfc,
    /* U+0073 "s" (7x9) */
    0x7d, 0x0e, 0x06, 0x07, 0xc0, 0xc0, 0xc3, 0x7c,
    /* U+0074 "t" (8x12) */
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x0f,
    /* U+0075 "u" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x74,
    /* U+0076 "v" (7x9) */
    0x82, 0x85, 0x0a, 0x22, 0x44, 0x8a, 0x1c, 0x18,
    /* U+0077 "w" (8x9) */
    0x99, 0x99, 0x99, 0xa9, 0xab, 0xaa, 0xa6, 0x66, 0x66,
    /* U+0078 "x" (7x9) */
    0xc2, 0xcc, 0xb1, 0xc1, 0x87, 0x0b, 0x23, 0xc2,
    /* U+0079 "y" (7x12) */
    0x83, 0x07, 0x12, 0x26, 0xc5, 0x0a, 0x1c, 0x10, 0x60, 0x87, 0x00,
    /* U+007A "z" (7x9) */
    0xfe, 0x0c, 0x30, 0x41, 0x04, 0x18, 0x60, 0xfe,
    /* U+007B "{" (6x15) */
    0x3c, 0x82, 0x08, 0x10, 0x41, 0x38, 0x10, 0x41, 0x08, 0x20, 0x83, 0xc0,
    /* U+007C "|" (1x16) */
    0xff, 0xff,
    /* U+007D "}" (7x15) */
    0xf0, 0x20, 0x40, 0x82, 0x04, 0x08, 0x0f, 0x20, 0x40, 0x80, 0x81, 0x02,
    0x3c, 0x00,
    /* U+007E "~" (8x4) */
    0x61, 0x91, 0x8a, 0x8e,
    /* U+00B0 "" (5x6) */
    0x76, 0xe3, 0x1d, 0xb8,
    /* U+00B1 "" (8x11) */
    0x10, 0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x00, 0x00, 0xff,
    /* U+00B2 "" (4x6) */
    0x79, 0x12, 0xcf,
    /* U+00B3 "" (4x6) */
    0xf1, 0x61, 0x9e,
    /* U+00B5 "" (6x11) */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0xfd, 0x82, 0x08, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x7) */
    0x02, 0x8c, 0xb0, 0xc3, 0x8c, 0xb0, 0x80,
    /* U+00F7 "" (8x9) */
    0x18, 0x18, 0x00, 0x00, 0xff, 0x00, 0x00, 0x18, 0x18,
    /* U+0394 "" (8x11) */
    0x18, 0x18, 0x3c, 0x24, 0x24, 0x66, 0x42, 0x42, 0xc3, 0x81, 0xff,
    /* U+03A9 "" (8x11) */
    0x3c, 0x46, 0x83, 0x81, 0x81, 0x81, 0x81, 0x83, 0x42, 0x64, 0xe7,
    /* U+03BC "" (6x11) */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0xfd, 0x82, 0x08, 0x00,
    /* U+03C0 "" (9x8) */
    0xff, 0x91, 0x08, 0x84, 0x42, 0x21, 0x10, 0x88, 0x47,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 2, .box_h = 12, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 5, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 154, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 9},
    {.bitmap_index = 60, .adv_w = 154, .box_w = 4, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 68, .adv_w = 154, .box_w = 4, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 76, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 154, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 93, .adv_w = 154, .box_w = 5, .box_h = 1, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 94, .adv_w = 154, .box_w = 2, .box_h = 2, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 109, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 154, .box_w = 2, .box_h = 9, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 154, .box_w = 2, .box_h = 11, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 231, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 239, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 243, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 251, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 274, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 463, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 154, .box_w = 4, .box_h = 15, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 582, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 594, .adv_w = 154, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 602, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 609, .adv_w = 154, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 610, .adv_w = 154, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 611, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 154, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 719, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 777, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 788, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 816, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 859, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 879, .adv_w = 154, .box_w = 1, .box_h = 16, .ofs_x = 4, .ofs_y = -3},
    {.bitmap_index = 881, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 895, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 899, .adv_w = 154, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 903, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 917, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 920, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 929, .adv_w = 154, .box_w = 2, .box_h = 2, .ofs_x = 4, .ofs_y = 4},
    {.bitmap_index = 930, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 937, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 946, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 957, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 968, .adv_w = 154, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 977, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x0310,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 785, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 12, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

#if LVGL_VERSION_MAJOR >= 8
const lv_font_t humid1_font_plex_mono_normal_16 = {
#else
lv_font_t humid1_font_plex_mono_normal_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_16 */
