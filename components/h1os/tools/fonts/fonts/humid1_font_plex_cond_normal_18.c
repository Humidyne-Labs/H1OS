/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_18 (IBM Plex Cond Normal)
 * Size: 18 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_18
#define HUMID1_FONT_PLEX_COND_NORMAL_18 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_18

extern const lv_font_t humid1_font_plex_sans_normal_18;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x13) */
    0x55, 0x55, 0x53, 0xc0,
    /* U+0022 "" (4x5) */
    0x99, 0x99, 0x90,
    /* U+0023 "#" (10x13) */
    0x09, 0x06, 0x41, 0x10, 0x44, 0x7f, 0xc4, 0x81, 0x20, 0x48, 0xff, 0x88,
    0x82, 0x20, 0x98, 0x24, 0x00,
    /* U+0024 "$" (7x17) */
    0x10, 0x21, 0xf6, 0xb9, 0x12, 0x24, 0x38, 0x3c, 0x2c, 0x48, 0x99, 0x3a,
    0x9f, 0x08, 0x10,
    /* U+0025 "%" (13x13) */
    0x70, 0x64, 0x42, 0x22, 0x31, 0x11, 0x08, 0x90, 0x45, 0x81, 0xc9, 0xc0,
    0xd1, 0x04, 0x88, 0x44, 0x46, 0x22, 0x21, 0x13, 0x07, 0x00,
    /* U+0026 "&" (9x13) */
    0x38, 0x22, 0x11, 0x08, 0x86, 0x81, 0xc1, 0xc7, 0xb2, 0x8f, 0x43, 0x20,
    0xd8, 0xe7, 0x98,
    /* U+0027 "'" (1x5) */
    0xf8,
    /* U+0028 "(" (4x17) */
    0x32, 0x44, 0x88, 0x88, 0x88, 0x88, 0x84, 0x42, 0x30,
    /* U+0029 ")" (4x17) */
    0xc4, 0x22, 0x11, 0x11, 0x11, 0x11, 0x12, 0x24, 0x40,
    /* U+002A "" (6x6) */
    0x20, 0x8e, 0xcc, 0x73, 0x20,
    /* U+002B "+" (8x8) */
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x17) */
    0x08, 0x42, 0x11, 0x08, 0x42, 0x21, 0x08, 0x44, 0x21, 0x08, 0x80,
    /* U+0030 "0" (8x13) */
    0x3c, 0x42, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x42,
    0x3c,
    /* U+0031 "1" (7x13) */
    0x30, 0xe3, 0x44, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x8f, 0xe0,
    /* U+0032 "2" (7x13) */
    0x3d, 0x8f, 0x08, 0x10, 0x20, 0x41, 0x06, 0x18, 0x61, 0x86, 0x0f, 0xe0,
    /* U+0033 "3" (6x13) */
    0x7a, 0x10, 0x41, 0x0d, 0xc0, 0x81, 0x04, 0x18, 0x62, 0x70,
    /* U+0034 "4" (9x13) */
    0x06, 0x07, 0x02, 0x83, 0x41, 0x21, 0x90, 0x88, 0xc4, 0x42, 0x7f, 0xc0,
    0x80, 0x40, 0x20,
    /* U+0035 "5" (7x13) */
    0xff, 0x02, 0x04, 0x08, 0x17, 0x31, 0x01, 0x02, 0x06, 0x0e, 0x27, 0x80,
    /* U+0036 "6" (7x13) */
    0x18, 0x60, 0x82, 0x04, 0x17, 0xb1, 0x41, 0x83, 0x06, 0x0a, 0x23, 0x80,
    /* U+0037 "7" (8x13) */
    0xff, 0x82, 0x86, 0x06, 0x04, 0x0c, 0x08, 0x08, 0x18, 0x10, 0x30, 0x30,
    0x20,
    /* U+0038 "8" (8x13) */
    0x3c, 0x46, 0x42, 0x42, 0x42, 0x3c, 0x66, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,
    /* U+0039 "9" (7x13) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x71, 0xbd, 0x04, 0x08, 0x20, 0xc3, 0x00,
    /* U+003A ":" (2x10) */
    0xf0, 0x00, 0xf0,
    /* U+003B ";" (2x12) */
    0xf0, 0x00, 0xfe,
    /* U+003C "<" (7x10) */
    0x06, 0x18, 0xc3, 0x08, 0x18, 0x1c, 0x0c, 0x0e, 0x04,
    /* U+003D "=" (8x5) */
    0xff, 0x00, 0x00, 0x00, 0xff,
    /* U+003E ">" (7x11) */
    0x81, 0x81, 0x80, 0xc0, 0xc0, 0x41, 0x86, 0x30, 0xc3, 0x00,
    /* U+003F "?" (6x13) */
    0x7b, 0x38, 0x41, 0x04, 0x31, 0x84, 0x10, 0x00, 0x0c, 0x30,
    /* U+0040 "@" (12x15) */
    0x0f, 0x83, 0x0c, 0x60, 0x24, 0xeb, 0x99, 0x99, 0x09, 0x90, 0x99, 0x09,
    0x90, 0x99, 0x8b, 0x8f, 0xe4, 0x00, 0x40, 0x03, 0x00, 0x0f, 0xc0,
    /* U+0041 "A" (9x13) */
    0x18, 0x0e, 0x05, 0x06, 0x82, 0x41, 0x31, 0x88, 0x84, 0x7f, 0x60, 0xb0,
    0x50, 0x38, 0x18,
    /* U+0042 "B" (8x13) */
    0xfc, 0x82, 0x82, 0x82, 0x82, 0x82, 0xfc, 0x82, 0x81, 0x81, 0x81, 0x83,
    0xfe,
    /* U+0043 "C" (8x13) */
    0x3c, 0x42, 0x43, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x41, 0x42,
    0x3c,
    /* U+0044 "D" (8x13) */
    0xfc, 0x86, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x86,
    0xfc,
    /* U+0045 "E" (7x13) */
    0xff, 0x02, 0x04, 0x08, 0x10, 0x3f, 0x40, 0x81, 0x02, 0x04, 0x0f, 0xe0,
    /* U+0046 "F" (6x13) */
    0xfe, 0x08, 0x20, 0x82, 0x0f, 0xe0, 0x82, 0x08, 0x20, 0x80,
    /* U+0047 "G" (9x13) */
    0x3e, 0x30, 0x90, 0x30, 0x08, 0x04, 0x02, 0x1f, 0x01, 0x80, 0xc0, 0x50,
    0x2c, 0x73, 0xe8,
    /* U+0048 "H" (8x13) */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81,
    /* U+0049 "I" (5x13) */
    0xf9, 0x08, 0x42, 0x10, 0x84, 0x21, 0x08, 0x4f, 0x80,
    /* U+004A "J" (6x13) */
    0x7c, 0x10, 0x41, 0x04, 0x10, 0x41, 0x04, 0x18, 0x73, 0x78,
    /* U+004B "K" (8x13) */
    0x82, 0x86, 0x8c, 0x98, 0x90, 0xb0, 0xf0, 0xd8, 0x88, 0x8c, 0x86, 0x86,
    0x83,
    /* U+004C "L" (6x13) */
    0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0xfc,
    /* U+004D "M" (10x13) */
    0xc0, 0xf0, 0x3e, 0x1e, 0x85, 0xb3, 0x64, 0x99, 0xe6, 0x31, 0x8c, 0x60,
    0x18, 0x06, 0x01, 0x80, 0x40,
    /* U+004E "N" (8x13) */
    0xc1, 0xc1, 0xe1, 0xa1, 0xb1, 0x91, 0x99, 0x89, 0x8d, 0x85, 0x87, 0x83,
    0x83,
    /* U+004F "O" (9x13) */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x50,
    0x4c, 0x63, 0xe0,
    /* U+0050 "P" (7x13) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x40, 0x81, 0x02, 0x04, 0x08, 0x00,
    /* U+0051 "Q" (9x16) */
    0x3e, 0x31, 0x90, 0x50, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x50,
    0x4c, 0x63, 0xe0, 0x40, 0x20, 0x1c,
    /* U+0052 "R" (7x13) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x44, 0x8d, 0x0a, 0x14, 0x18, 0x20,
    /* U+0053 "S" (7x13) */
    0x7d, 0x8e, 0x04, 0x08, 0x0e, 0x0f, 0x03, 0x02, 0x06, 0x0e, 0x27, 0x80,
    /* U+0054 "T" (9x13) */
    0xff, 0x84, 0x02, 0x01, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00, 0x80,
    /* U+0055 "U" (8x13) */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42,
    0x3c,
    /* U+0056 "V" (9x13) */
    0xc0, 0xa0, 0x58, 0x6c, 0x32, 0x11, 0x08, 0xcc, 0x64, 0x12, 0x0b, 0x07,
    0x81, 0x80, 0xc0,
    /* U+0057 "W" (14x13) */
    0xc3, 0x05, 0x0e, 0x34, 0x28, 0xd8, 0xa2, 0x66, 0x88, 0x9a, 0x22, 0x4d,
    0x89, 0x36, 0x24, 0x50, 0xf1, 0x41, 0x85, 0x06, 0x14, 0x18, 0x60,
    /* U+0058 "X" (8x13) */
    0x81, 0xc3, 0x66, 0x24, 0x3c, 0x18, 0x18, 0x3c, 0x24, 0x66, 0x42, 0xc3,
    0x81,
    /* U+0059 "Y" (9x13) */
    0xc1, 0xa0, 0x98, 0xc4, 0x43, 0x60, 0xa0, 0x70, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00, 0x80,
    /* U+005A "Z" (8x13) */
    0xff, 0x03, 0x06, 0x06, 0x0c, 0x08, 0x18, 0x10, 0x20, 0x60, 0x40, 0xc0,
    0xff,
    /* U+005B "[" (3x17) */
    0xf2, 0x49, 0x24, 0x92, 0x49, 0x24, 0xe0,
    /* U+005C "" (5x17) */
    0x84, 0x30, 0x84, 0x21, 0x84, 0x21, 0x0c, 0x21, 0x08, 0x61, 0x08,
    /* U+005D "]" (3x17) */
    0xe4, 0x92, 0x49, 0x24, 0x92, 0x49, 0xe0,
    /* U+005E "^" (8x7) */
    0x18, 0x38, 0x24, 0x64, 0x42, 0xc2, 0x83,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (3x3) */
    0xc9, 0x80,
    /* U+0061 "a" (8x10) */
    0x78, 0xc4, 0x04, 0x04, 0x7c, 0x84, 0x84, 0x84, 0x8c, 0x77,
    /* U+0062 "b" (7x14) */
    0x81, 0x02, 0x04, 0x0b, 0x98, 0xa0, 0xc1, 0x83, 0x06, 0x0c, 0x1c, 0x57,
    0x00,
    /* U+0063 "c" (6x10) */
    0x39, 0x18, 0x60, 0x82, 0x08, 0x21, 0x44, 0xe0,
    /* U+0064 "d" (7x14) */
    0x02, 0x04, 0x08, 0x13, 0xa8, 0xe0, 0xc1, 0x83, 0x06, 0x0c, 0x14, 0x67,
    0x40,
    /* U+0065 "e" (7x10) */
    0x38, 0x8a, 0x0c, 0x1f, 0xf0, 0x20, 0x41, 0x44, 0x78,
    /* U+0066 "f" (5x14) */
    0x39, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08, 0x42, 0x10,
    /* U+0067 "g" (8x15) */
    0x03, 0x3c, 0x66, 0x42, 0x42, 0x42, 0x66, 0x3c, 0x40, 0x40, 0x7e, 0x81,
    0x81, 0x83, 0x7e,
    /* U+0068 "h" (6x14) */
    0x82, 0x08, 0x20, 0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x86, 0x10,
    /* U+0069 "i" (1x14) */
    0xcf, 0xfc,
    /* U+006A "j" (2x18) */
    0x50, 0x55, 0x55, 0x55, 0x70,
    /* U+006B "k" (6x14) */
    0x82, 0x08, 0x20, 0x8e, 0x29, 0x2c, 0xf3, 0x49, 0xa2, 0x8e, 0x10,
    /* U+006C "l" (2x14) */
    0xaa, 0xaa, 0xaa, 0xb0,
    /* U+006D "m" (11x10) */
    0xb9, 0xd9, 0xce, 0x10, 0xc2, 0x18, 0x43, 0x08, 0x61, 0x0c, 0x21, 0x84,
    0x30, 0x84,
    /* U+006E "n" (6x10) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x86, 0x10,
    /* U+006F "o" (7x10) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x44, 0x70,
    /* U+0070 "p" (7x14) */
    0xb9, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xc5, 0x72, 0x04, 0x08, 0x10,
    0x00,
    /* U+0071 "q" (7x14) */
    0x3a, 0x8e, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x46, 0x74, 0x08, 0x10, 0x20,
    0x40,
    /* U+0072 "r" (4x10) */
    0xbc, 0x88, 0x88, 0x88, 0x88,
    /* U+0073 "s" (6x10) */
    0x7a, 0x38, 0x20, 0xf0, 0xf0, 0x41, 0x85, 0xe0,
    /* U+0074 "t" (5x13) */
    0x21, 0x09, 0xf2, 0x10, 0x84, 0x21, 0x08, 0x43, 0x80,
    /* U+0075 "u" (6x10) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0xcd, 0xd0,
    /* U+0076 "v" (8x10) */
    0xc3, 0x42, 0x42, 0x66, 0x24, 0x24, 0x24, 0x3c, 0x18, 0x18,
    /* U+0077 "w" (11x10) */
    0x8c, 0x31, 0x86, 0x29, 0xe5, 0x2c, 0xa4, 0xa4, 0x94, 0x92, 0x8c, 0x51,
    0x86, 0x30,
    /* U+0078 "x" (7x10) */
    0x87, 0x89, 0x21, 0x43, 0x06, 0x1a, 0x24, 0xc5, 0x0c,
    /* U+0079 "y" (7x14) */
    0x83, 0x85, 0x1a, 0x24, 0x4d, 0x8a, 0x14, 0x28, 0x30, 0x40, 0x81, 0x0c,
    0x00,
    /* U+007A "z" (6x10) */
    0xfc, 0x30, 0x86, 0x10, 0x86, 0x10, 0xc3, 0xf0,
    /* U+007B "{" (5x17) */
    0x39, 0x08, 0x42, 0x10, 0x84, 0xc3, 0x08, 0x42, 0x10, 0x84, 0x38,
    /* U+007C "|" (1x17) */
    0xff, 0xff, 0x80,
    /* U+007D "}" (5x17) */
    0xe1, 0x08, 0x42, 0x10, 0x84, 0x19, 0x88, 0x42, 0x10, 0x84, 0xe0,
    /* U+007E "~" (7x2) */
    0xf0, 0x1c,
    /* U+00B0 "" (6x6) */
    0x7b, 0x38, 0x61, 0xcd, 0xe0,
    /* U+00B1 "" (8x11) */
    0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0xff,
    /* U+00B2 "" (4x7) */
    0x69, 0x13, 0x6c, 0xf0,
    /* U+00B3 "" (4x7) */
    0x79, 0x16, 0x19, 0xe0,
    /* U+00B5 "" (6x14) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0xcf, 0xd8, 0x20, 0x82, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x7) */
    0xc2, 0xc8, 0xe0, 0xc2, 0xcc, 0xd0, 0x80,
    /* U+00F7 "" (8x9) */
    0x18, 0x18, 0x00, 0x00, 0xff, 0x00, 0x00, 0x18, 0x18,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 61, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 74, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 110, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 7, .adv_w = 183, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 155, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 241, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 180, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 63, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 77, .adv_w = 87, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 86, .adv_w = 87, .box_w = 4, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 95, .adv_w = 119, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 100, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 108, .adv_w = 71, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 109, .adv_w = 104, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 110, .adv_w = 71, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 101, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 122, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 156, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 156, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 74, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 74, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 252, .adv_w = 156, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 156, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 266, .adv_w = 156, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 124, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 231, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 309, .adv_w = 167, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 170, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 175, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 151, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 145, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 183, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 104, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 133, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 165, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 130, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 210, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 183, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 184, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 158, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 184, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 530, .adv_w = 166, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 151, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 149, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 176, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 158, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 233, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 82, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 668, .adv_w = 101, .box_w = 5, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 679, .adv_w = 82, .box_w = 3, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 156, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 693, .adv_w = 146, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 694, .adv_w = 156, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 11},
    {.bitmap_index = 696, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 151, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 151, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 143, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 85, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 137, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 773, .adv_w = 148, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 66, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 66, .box_w = 2, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 791, .adv_w = 137, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 71, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 227, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 151, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 850, .adv_w = 151, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 863, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 126, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 92, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 903, .adv_w = 201, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 130, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 939, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 947, .adv_w = 89, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 958, .adv_w = 83, .box_w = 1, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 961, .adv_w = 89, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 972, .adv_w = 156, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 974, .adv_w = 122, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 979, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 92, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 994, .adv_w = 92, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 998, .adv_w = 149, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1009, .adv_w = 85, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 1010, .adv_w = 156, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1017, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 72, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 8, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    3, 13, 3, 15, 3, 34, 3, 43, 6, 3, 6, 8, 6, 11, 7, 53,
    7, 58, 8, 13, 8, 15, 8, 34, 8, 43, 8, 87, 9, 53, 9, 55,
    9, 56, 9, 57, 9, 58, 9, 72, 9, 75, 9, 90, 11, 13, 11, 15,
    11, 52, 11, 53, 11, 55, 11, 56, 11, 58, 11, 59, 11, 87, 11, 88,
    11, 89, 11, 90, 11, 91, 13, 3, 13, 8, 13, 11, 13, 32, 13, 34,
    13, 43, 13, 53, 13, 55, 13, 57, 13, 58, 13, 59, 13, 66, 13, 87,
    13, 91, 14, 34, 14, 42, 14, 43, 14, 52, 14, 53, 14, 55, 14, 56,
    14, 57, 14, 58, 14, 59, 14, 71, 14, 72, 14, 75, 14, 87, 14, 88,
    14, 89, 14, 90, 14, 91, 15, 3, 15, 8, 15, 11, 15, 32, 15, 34,
    15, 43, 15, 53, 15, 55, 15, 57, 15, 58, 15, 59, 15, 66, 15, 87,
    15, 91, 16, 16, 16, 34, 16, 53, 16, 55, 16, 56, 16, 58, 27, 53,
    27, 55, 27, 57, 27, 58, 28, 53, 28, 55, 28, 57, 28, 58, 32, 13,
    32, 15, 32, 34, 34, 13, 34, 15, 34, 16, 34, 34, 34, 43, 34, 53,
    34, 57, 34, 58, 34, 64, 34, 89, 34, 91, 35, 13, 35, 15, 35, 16,
    35, 53, 35, 55, 35, 57, 35, 58, 35, 64, 35, 89, 35, 98, 35, 99,
    36, 64, 37, 13, 37, 15, 37, 16, 37, 34, 37, 53, 37, 64, 39, 7,
    39, 13, 39, 15, 39, 16, 39, 34, 39, 43, 39, 64, 39, 66, 39, 72,
    40, 16, 42, 7, 42, 14, 42, 33, 42, 53, 42, 68, 42, 69, 42, 70,
    42, 80, 42, 82, 42, 84, 42, 87, 42, 90, 43, 64, 44, 10, 44, 13,
    44, 14, 44, 15, 44, 16, 44, 34, 44, 59, 44, 91, 45, 3, 45, 8,
    45, 11, 45, 13, 45, 14, 45, 15, 45, 16, 45, 32, 45, 53, 45, 55,
    45, 58, 45, 64, 45, 91, 45, 98, 45, 99, 48, 3, 48, 7, 48, 8,
    48, 11, 48, 13, 48, 15, 48, 16, 48, 32, 48, 34, 48, 43, 48, 53,
    48, 55, 48, 56, 48, 57, 48, 58, 48, 59, 48, 64, 49, 7, 49, 13,
    49, 15, 49, 16, 49, 34, 49, 43, 49, 64, 50, 3, 50, 7, 50, 8,
    50, 11, 50, 13, 50, 15, 50, 16, 50, 32, 50, 34, 50, 43, 50, 53,
    50, 55, 50, 56, 50, 57, 50, 58, 50, 59, 50, 64, 52, 14, 52, 43,
    52, 85, 53, 3, 53, 8, 53, 10, 53, 11, 53, 13, 53, 14, 53, 15,
    53, 16, 53, 32, 53, 34, 53, 53, 53, 55, 53, 56, 53, 58, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 80, 53, 82, 53, 84,
    53, 86, 53, 91, 53, 98, 53, 99, 54, 13, 54, 15, 54, 16, 54, 64,
    55, 7, 55, 13, 55, 14, 55, 15, 55, 16, 55, 33, 55, 34, 55, 43,
    55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72, 55, 80, 55, 82,
    55, 84, 56, 7, 56, 13, 56, 14, 56, 15, 56, 16, 56, 33, 56, 34,
    56, 36, 56, 40, 56, 43, 56, 48, 56, 50, 56, 64, 56, 66, 56, 68,
    56, 69, 56, 70, 56, 72, 56, 78, 56, 79, 56, 80, 56, 81, 56, 82,
    56, 83, 56, 84, 56, 89, 56, 91, 57, 14, 58, 7, 58, 13, 58, 14,
    58, 15, 58, 16, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40,
    58, 43, 58, 48, 58, 50, 58, 52, 58, 64, 58, 66, 58, 68, 58, 69,
    58, 70, 58, 71, 58, 72, 58, 74, 58, 75, 58, 78, 58, 79, 58, 80,
    58, 81, 58, 82, 58, 83, 58, 84, 58, 85, 58, 86, 58, 87, 58, 88,
    58, 89, 58, 90, 58, 91, 59, 3, 59, 8, 59, 10, 59, 11, 59, 13,
    59, 15, 59, 16, 59, 64, 59, 91, 59, 98, 59, 99, 64, 34, 64, 36,
    64, 40, 64, 48, 64, 50, 64, 53, 64, 54, 64, 55, 64, 56, 64, 57,
    64, 58, 64, 59, 64, 68, 64, 69, 64, 70, 64, 72, 64, 75, 64, 80,
    64, 82, 64, 85, 64, 87, 64, 89, 66, 3, 66, 8, 66, 11, 66, 53,
    66, 55, 66, 58, 67, 14, 67, 16, 67, 43, 67, 53, 68, 53, 70, 53,
    70, 55, 70, 58, 70, 64, 71, 3, 71, 8, 71, 10, 71, 11, 71, 32,
    71, 36, 71, 40, 71, 48, 71, 50, 71, 53, 71, 55, 71, 56, 71, 57,
    71, 58, 71, 62, 71, 64, 71, 87, 71, 90, 71, 94, 71, 98, 71, 99,
    72, 55, 72, 58, 73, 53, 73, 58, 76, 7, 76, 14, 76, 33, 76, 36,
    76, 40, 76, 48, 76, 50, 76, 53, 76, 55, 76, 56, 76, 58, 76, 68,
    76, 69, 76, 70, 76, 72, 76, 80, 76, 82, 76, 84, 76, 85, 76, 86,
    76, 87, 76, 88, 76, 90, 76, 98, 76, 99, 77, 13, 77, 15, 77, 16,
    77, 34, 77, 43, 77, 56, 77, 57, 77, 59, 77, 64, 78, 53, 78, 58,
    79, 53, 79, 58, 80, 53, 80, 58, 80, 64, 81, 14, 81, 16, 81, 43,
    81, 53, 83, 3, 83, 8, 83, 11, 83, 13, 83, 15, 83, 34, 83, 64,
    83, 98, 84, 53, 84, 55, 84, 58, 84, 64, 85, 14, 85, 53, 85, 58,
    86, 53, 87, 3, 87, 8, 87, 11, 87, 13, 87, 15, 87, 64, 88, 7,
    88, 13, 88, 15, 88, 34, 88, 43, 88, 53, 88, 55, 88, 58, 88, 64,
    88, 66, 88, 72, 89, 53, 89, 64, 90, 3, 90, 8, 90, 11, 90, 13,
    90, 15, 90, 64, 90, 98, 91, 14, 91, 53, 91, 58, 91, 68, 91, 69,
    91, 70, 91, 80, 91, 82, 98, 13, 98, 15, 98, 34, 98, 43, 99, 13,
    99, 15, 99, 34, 99, 43,
};

static const int8_t kern_pair_values[] = {
    -23, -23, -14, -9, -17, -17, -17, -14, -14, -23, -23, -14, -9, 9, 6, 6,
    4, 1, 6, 5, 14, 3, -23, -23, 3, 7, 4, 6, 4, 1, 9, 7,
    2, 7, 3, -23, -23, -23, -22, 6, 4, -26, -19, 4, -22, 7, 1, -16,
    4, -6, -10, -7, -5, -14, -10, -4, -14, -17, -10, -1, -1, -1, -1, -1,
    -10, -1, -6, -23, -23, -23, -22, 6, 4, -26, -19, 4, -22, 7, 1, -16,
    4, -35, -19, 7, 4, 4, 6, -12, -6, -3, -12, -12, -6, -3, -12, -33,
    -33, -6, 6, 6, 3, 2, 5, -17, 2, -16, 6, 2, 3, -5, -5, -4,
    -5, -5, -4, -6, -17, -3, -3, -3, -12, -13, -13, -9, -8, -8, -22, -10,
    -27, -27, -15, -16, -12, -37, -10, -11, 3, -3, -10, -4, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -21, 3, 3, -16, 3, 3, 3, 3, 3, -19, -19,
    -19, 7, -12, 7, 8, -13, -18, -13, -20, 10, 6, -20, -17, -3, -1, -3,
    -3, -14, -14, -9, -1, -6, -1, -6, -6, -4, -6, -9, -3, -26, -7, -30,
    -30, -17, -16, -11, -40, -3, -1, -3, -3, -14, -14, -9, -1, -6, -1, -6,
    -6, -4, -6, -9, -3, -26, 3, 1, 1, 7, 7, 6, 7, -26, -14, -26,
    -22, 3, -17, 7, 3, 3, 5, -22, -19, -17, -17, -17, -22, -17, -17, -19,
    -14, -14, 3, 4, -10, -10, -9, -17, -10, -19, -10, -19, -14, -9, -13, -8,
    -23, -9, -9, -9, -9, -12, -9, -9, -7, -8, -14, -4, -14, -7, -5, -6,
    -4, -4, -5, -4, -4, -16, -6, -4, -4, -4, -6, -3, -3, -4, -4, -4,
    -3, -3, -2, -3, -14, -13, -22, -17, -22, -22, -12, -12, -12, -16, -9, -9,
    -8, -9, -9, -5, -22, -15, -14, -14, -14, -3, -17, -3, -5, -12, -12, -14,
    -12, -14, -12, -12, -3, -10, -6, -4, -7, -7, -7, 3, 3, 1, 3, 9,
    9, 3, 5, 5, 3, 3, 6, -26, -26, -26, -26, -22, -17, -23, -16, 7,
    -22, 9, -17, -13, -17, 12, 17, -17, -13, -11, -17, 6, -7, -7, -7, -19,
    -9, -14, 3, 1, 1, -20, -13, -16, -9, -15, -14, 9, 9, 8, 9, 7,
    4, 4, 4, 4, 10, 8, 9, 5, 7, 4, -14, 3, 3, 4, 7, 9,
    -2, -3, -16, -14, -4, -13, -3, -3, -3, -3, -3, -7, -4, -2, -11, -3,
    -2, -3, -3, -3, -2, -2, -2, -3, -3, -2, -2, -6, -6, 1, 1, 1,
    6, 4, 1, 4, 4, 7, -16, -14, -16, -14, -17, -15, -16, 3, 1, 1,
    -20, 9, 9, 9, -22, -22, -9, -20, 9, -16, -8, -13, -9, -6, -7, -5,
    -13, 9, 9, 9, -16, -16, -17, -6, -12, -12, -3, -4, -12, -3, -6, -10,
    -3, -5, -13, 6, 7, 7, 7, -19, -19, -20, 7, -7, -10, -4, -2, -2,
    -2, -2, -2, -14, -14, -10, -12, -14, -14, -14, -10,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 507,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
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
const lv_font_t humid1_font_plex_cond_normal_18 = {
#else
lv_font_t humid1_font_plex_cond_normal_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 24,
    .base_line = 5,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_18,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_18 */
