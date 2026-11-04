/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_14 (IBM Plex Sans Italic)
 * Size: 14 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_14
#define HUMID1_FONT_PLEX_SANS_ITALIC_14 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_14

extern const lv_font_t humid1_font_plex_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x11) */
    0x69, 0x24, 0xa4, 0x12, 0x00,
    /* U+0022 "" (4x4) */
    0x99, 0xaa,
    /* U+0023 "#" (8x11) */
    0x09, 0x12, 0x12, 0x7f, 0x24, 0x24, 0x24, 0xfe, 0x48, 0x48, 0x50,
    /* U+0024 "$" (8x13) */
    0x04, 0x1e, 0x2b, 0x68, 0x68, 0x38, 0x1c, 0x16, 0x12, 0x12, 0xd6, 0x78,
    0x10,
    /* U+0025 "%" (10x11) */
    0x30, 0x52, 0x24, 0x92, 0x2c, 0x92, 0x1d, 0x70, 0x94, 0x49, 0x12, 0x48,
    0x94, 0x18,
    /* U+0026 "&" (8x11) */
    0x1c, 0x24, 0x44, 0x6c, 0x38, 0x73, 0x92, 0x8c, 0x8c, 0x8c, 0xf2,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (4x14) */
    0x13, 0x24, 0x48, 0x88, 0x88, 0x88, 0x44,
    /* U+0029 ")" (5x14) */
    0x10, 0x82, 0x10, 0x84, 0x21, 0x10, 0x88, 0x44, 0x40,
    /* U+002A "" (6x5) */
    0x10, 0x4f, 0xcc, 0x50,
    /* U+002B "+" (6x7) */
    0x10, 0x41, 0x3f, 0x10, 0x82, 0x00,
    /* U+002C "," (2x4) */
    0x56,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (7x14) */
    0x02, 0x08, 0x10, 0x60, 0x81, 0x04, 0x08, 0x20, 0x41, 0x02, 0x0c, 0x10,
    0x00,
    /* U+0030 "0" (7x11) */
    0x1c, 0x49, 0x0a, 0x1c, 0x30, 0xe1, 0xc2, 0x85, 0x91, 0xc0,
    /* U+0031 "1" (6x11) */
    0x18, 0xa4, 0x82, 0x08, 0x61, 0x04, 0x10, 0x4f, 0xc0,
    /* U+0032 "2" (7x11) */
    0x3c, 0xc9, 0x18, 0x30, 0x41, 0x86, 0x18, 0x61, 0x03, 0xf0,
    /* U+0033 "3" (7x11) */
    0x3c, 0xc8, 0x18, 0x20, 0x47, 0x03, 0x02, 0x05, 0x11, 0xc0,
    /* U+0034 "4" (6x11) */
    0x04, 0x31, 0xc5, 0x25, 0x9c, 0xa2, 0xfc, 0x20, 0x80,
    /* U+0035 "5" (7x11) */
    0x3e, 0x41, 0x02, 0x07, 0x88, 0x81, 0x02, 0x05, 0x19, 0xc0,
    /* U+0036 "6" (6x11) */
    0x08, 0x42, 0x10, 0x7b, 0x18, 0x61, 0x87, 0x37, 0x80,
    /* U+0037 "7" (6x11) */
    0xfe, 0x18, 0xc2, 0x10, 0x42, 0x08, 0x41, 0x08, 0x00,
    /* U+0038 "8" (7x11) */
    0x3c, 0xcd, 0x0a, 0x14, 0x47, 0x31, 0x42, 0x85, 0x19, 0xe0,
    /* U+0039 "9" (6x11) */
    0x7b, 0x38, 0x61, 0x86, 0x37, 0x82, 0x10, 0x8c, 0x00,
    /* U+003A ":" (2x8) */
    0x50, 0x0a,
    /* U+003B ";" (3x10) */
    0x24, 0x00, 0x12, 0x50,
    /* U+003C "<" (7x8) */
    0x06, 0x30, 0xc6, 0x04, 0x06, 0x06, 0x04,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xe0,
    /* U+003E ">" (6x8) */
    0x60, 0xc0, 0x81, 0x0c, 0xcc, 0x20,
    /* U+003F "?" (6x11) */
    0x39, 0x38, 0x43, 0x08, 0xc6, 0x00, 0x01, 0x04, 0x00,
    /* U+0040 "@" (10x13) */
    0x0f, 0x0c, 0x32, 0x05, 0x35, 0x93, 0x64, 0x5b, 0x26, 0x89, 0xb2, 0xe7,
    0xe8, 0x01, 0x00, 0x3e, 0x00,
    /* U+0041 "A" (8x11) */
    0x04, 0x0e, 0x0a, 0x12, 0x12, 0x32, 0x22, 0x7e, 0x42, 0xc2, 0x83,
    /* U+0042 "B" (7x11) */
    0x7e, 0x85, 0x0a, 0x14, 0x2f, 0xb1, 0xc1, 0x87, 0x0b, 0xe0,
    /* U+0043 "C" (7x11) */
    0x1c, 0xc5, 0x0c, 0x08, 0x10, 0x20, 0x40, 0x83, 0x89, 0xe0,
    /* U+0044 "D" (8x11) */
    0x7c, 0x42, 0x43, 0x41, 0x43, 0x43, 0xc2, 0x82, 0x86, 0x84, 0xf8,
    /* U+0045 "E" (7x11) */
    0x7e, 0x81, 0x02, 0x04, 0x0f, 0xb0, 0x40, 0x81, 0x03, 0xf0,
    /* U+0046 "F" (7x11) */
    0x7e, 0x81, 0x02, 0x04, 0x0f, 0xb0, 0x40, 0x81, 0x02, 0x00,
    /* U+0047 "G" (8x11) */
    0x1e, 0x63, 0x40, 0xc0, 0x80, 0x8e, 0x82, 0x82, 0x82, 0xc6, 0x7a,
    /* U+0048 "H" (8x11) */
    0x61, 0x41, 0x41, 0x41, 0x41, 0x7f, 0xc2, 0x82, 0x82, 0x82, 0x82,
    /* U+0049 "I" (6x11) */
    0x3c, 0x41, 0x04, 0x10, 0xc2, 0x08, 0x20, 0x8f, 0x00,
    /* U+004A "J" (7x11) */
    0x3e, 0x0c, 0x10, 0x20, 0x40, 0x81, 0x06, 0x89, 0x11, 0xc0,
    /* U+004B "K" (8x11) */
    0x63, 0x46, 0x44, 0x48, 0x50, 0x70, 0xd8, 0x88, 0x8c, 0x84, 0x84,
    /* U+004C "L" (5x11) */
    0x62, 0x10, 0x84, 0x23, 0x10, 0x84, 0x3e,
    /* U+004D "M" (10x11) */
    0x60, 0xd8, 0x75, 0x1d, 0x4a, 0x52, 0x97, 0x28, 0x8a, 0x26, 0x81, 0x20,
    0x48, 0x10,
    /* U+004E "N" (8x11) */
    0x61, 0x61, 0x51, 0x51, 0x51, 0x5b, 0x8a, 0x8a, 0x8e, 0x86, 0x86,
    /* U+004F "O" (8x11) */
    0x1e, 0x22, 0x41, 0xc1, 0x81, 0x81, 0x81, 0x83, 0x82, 0xc4, 0x78,
    /* U+0050 "P" (7x11) */
    0x7e, 0x85, 0x0a, 0x14, 0x2f, 0xa0, 0x40, 0x81, 0x02, 0x00,
    /* U+0051 "Q" (8x13) */
    0x1e, 0x22, 0x41, 0xc1, 0x81, 0x81, 0x81, 0x82, 0x82, 0x4c, 0x38, 0x20,
    0x38,
    /* U+0052 "R" (7x11) */
    0x7e, 0x85, 0x0a, 0x14, 0x2f, 0xa2, 0x44, 0x8d, 0x0a, 0x10,
    /* U+0053 "S" (8x11) */
    0x1e, 0x23, 0x20, 0x60, 0x30, 0x1c, 0x02, 0x02, 0x02, 0xc6, 0x78,
    /* U+0054 "T" (8x11) */
    0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x20, 0x20, 0x20, 0x20,
    /* U+0055 "U" (8x11) */
    0x41, 0x41, 0x41, 0x43, 0x42, 0xc2, 0x82, 0x82, 0x84, 0xc4, 0x78,
    /* U+0056 "V" (7x11) */
    0x83, 0x0e, 0x14, 0x68, 0x93, 0x24, 0x48, 0xa0, 0xc1, 0x00,
    /* U+0057 "W" (12x11) */
    0xc6, 0x1c, 0x63, 0x46, 0x24, 0xa2, 0x4a, 0x45, 0x24, 0x52, 0xc5, 0x28,
    0x62, 0x86, 0x30, 0x43, 0x00,
    /* U+0058 "X" (9x11) */
    0x21, 0x90, 0x84, 0x82, 0xc1, 0xc0, 0x40, 0x60, 0x48, 0x64, 0x23, 0x20,
    0x80,
    /* U+0059 "Y" (7x11) */
    0x87, 0x0a, 0x22, 0x45, 0x0c, 0x18, 0x30, 0x40, 0x81, 0x00,
    /* U+005A "Z" (8x11) */
    0x3f, 0x03, 0x02, 0x04, 0x0c, 0x18, 0x10, 0x20, 0x60, 0xc0, 0xfe,
    /* U+005B "[" (5x14) */
    0x19, 0x08, 0x42, 0x11, 0x08, 0x42, 0x10, 0x88, 0x60,
    /* U+005C "" (2x14) */
    0xaa, 0xaa, 0x55, 0x50,
    /* U+005D "]" (5x14) */
    0x38, 0x84, 0x21, 0x08, 0x84, 0x21, 0x08, 0x44, 0x60,
    /* U+005E "^" (7x6) */
    0x18, 0x30, 0x93, 0x24, 0x50, 0x40,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xa4,
    /* U+0061 "a" (6x8) */
    0x3d, 0x18, 0x61, 0x86, 0x39, 0x9b,
    /* U+0062 "b" (6x11) */
    0x61, 0x04, 0x16, 0x65, 0x18, 0x61, 0x86, 0x2f, 0x00,
    /* U+0063 "c" (6x8) */
    0x39, 0x38, 0x20, 0x82, 0x08, 0x9c,
    /* U+0064 "d" (7x11) */
    0x02, 0x04, 0x09, 0xe4, 0x50, 0xa1, 0x42, 0x8d, 0x31, 0xb0,
    /* U+0065 "e" (6x8) */
    0x39, 0x18, 0xfc, 0x82, 0x08, 0x9c,
    /* U+0066 "f" (6x14) */
    0x0c, 0x21, 0x0f, 0x10, 0x41, 0x0c, 0x20, 0x82, 0x08, 0x23, 0x00,
    /* U+0067 "g" (8x12) */
    0x03, 0x3c, 0x64, 0x44, 0x44, 0x38, 0x40, 0x40, 0x7c, 0x84, 0x84, 0xf8,
    /* U+0068 "h" (6x11) */
    0x61, 0x04, 0x16, 0x65, 0x18, 0x63, 0x8a, 0x28, 0xc0,
    /* U+0069 "i" (3x11) */
    0x60, 0x25, 0xa4, 0x93, 0x00,
    /* U+006A "j" (5x14) */
    0x18, 0x00, 0x21, 0x18, 0x84, 0x21, 0x08, 0x84, 0x60,
    /* U+006B "k" (6x11) */
    0x61, 0x04, 0x11, 0x49, 0x4a, 0x34, 0x92, 0x68, 0xc0,
    /* U+006C "l" (3x11) */
    0x69, 0x24, 0xa4, 0x93, 0x00,
    /* U+006D "m" (10x8) */
    0x59, 0x9b, 0x9c, 0x46, 0x31, 0x88, 0xe2, 0x28, 0x8a, 0x23,
    /* U+006E "n" (6x8) */
    0x59, 0x9c, 0x61, 0x8e, 0x28, 0xa3,
    /* U+006F "o" (6x8) */
    0x39, 0x18, 0x61, 0x86, 0x38, 0x9c,
    /* U+0070 "p" (7x11) */
    0x2c, 0x65, 0x8a, 0x14, 0x28, 0x51, 0x3c, 0x81, 0x02, 0x00,
    /* U+0071 "q" (6x11) */
    0x3d, 0x18, 0x61, 0x86, 0x39, 0x9a, 0x08, 0x21, 0x80,
    /* U+0072 "r" (4x8) */
    0x56, 0xc8, 0x88, 0x88,
    /* U+0073 "s" (6x8) */
    0x39, 0x14, 0x1c, 0x18, 0x1c, 0x9e,
    /* U+0074 "t" (4x10) */
    0x24, 0xf4, 0x44, 0x88, 0x8c,
    /* U+0075 "u" (6x8) */
    0x45, 0x1c, 0x63, 0x8a, 0x29, 0xbb,
    /* U+0076 "v" (6x8) */
    0x86, 0x38, 0xa6, 0x51, 0xc6, 0x18,
    /* U+0077 "w" (9x8) */
    0x88, 0xc4, 0x65, 0x32, 0xaa, 0x55, 0x32, 0x99, 0x8c,
    /* U+0078 "x" (7x8) */
    0x62, 0x48, 0xa0, 0x83, 0x05, 0x12, 0x42,
    /* U+0079 "y" (7x11) */
    0x42, 0x8d, 0x12, 0x62, 0x87, 0x0c, 0x18, 0x20, 0xc3, 0x00,
    /* U+007A "z" (6x8) */
    0x7c, 0x30, 0x84, 0x21, 0x8c, 0x3e,
    /* U+007B "{" (5x14) */
    0x18, 0x8c, 0x42, 0x13, 0x08, 0x42, 0x10, 0x84, 0x30,
    /* U+007C "|" (3x14) */
    0x24, 0xa4, 0x92, 0x92, 0x49, 0x00,
    /* U+007D "}" (4x14) */
    0x31, 0x11, 0x11, 0x12, 0x22, 0x44, 0x4c,
    /* U+007E "~" (6x2) */
    0xe0, 0x70,
    /* U+00B0 "" (4x5) */
    0x79, 0x99, 0xe0,
    /* U+00B1 "" (8x10) */
    0x04, 0x04, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x18, 0x00, 0xfe,
    /* U+00B2 "" (4x5) */
    0x79, 0x24, 0xe0,
    /* U+00B3 "" (4x5) */
    0x71, 0x61, 0xe0,
    /* U+00B5 "" (7x11) */
    0x22, 0x45, 0x8a, 0x14, 0x48, 0x93, 0x3b, 0x81, 0x02, 0x00,
    /* U+00B7 "" (2x2) */
    0x70,
    /* U+00D7 "" (6x6) */
    0x41, 0x92, 0x8c, 0x7b, 0x20,
    /* U+00F7 "" (6x8) */
    0x18, 0x60, 0x00, 0xfc, 0x03, 0x08,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 53, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 61, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 130, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 31, .adv_w = 202, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 52, .box_w = 1, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 57, .adv_w = 73, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 64, .adv_w = 73, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 73, .adv_w = 101, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 77, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 84, .adv_w = 87, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 85, .adv_w = 61, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 85, .box_w = 7, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 99, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 66, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 66, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 200, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 211, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 105, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 193, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 243, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 87, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 110, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 176, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 152, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 423, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 125, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 193, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 134, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 126, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 71, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 536, .adv_w = 85, .box_w = 2, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 540, .adv_w = 71, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 549, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 555, .adv_w = 123, .box_w = 7, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 556, .adv_w = 133, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 557, .adv_w = 131, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 131, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 69, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 605, .adv_w = 114, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 59, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 57, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 640, .adv_w = 116, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 59, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 190, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 127, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 695, .adv_w = 82, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 72, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 126, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 166, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 108, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 748, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 74, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 763, .adv_w = 69, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 769, .adv_w = 74, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 776, .adv_w = 134, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 778, .adv_w = 102, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 781, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 791, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 794, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 797, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 807, .adv_w = 71, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 808, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 813, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1}
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
    3, 13, 3, 15, 3, 34, 3, 43, 6, 3, 6, 8, 6, 11, 7, 68,
    7, 70, 7, 80, 7, 82, 8, 13, 8, 15, 8, 34, 8, 53, 8, 87,
    8, 88, 8, 90, 11, 13, 11, 15, 11, 34, 11, 53, 11, 56, 11, 85,
    11, 87, 11, 88, 11, 90, 13, 3, 13, 8, 13, 11, 13, 32, 13, 36,
    13, 40, 13, 48, 13, 50, 13, 53, 13, 54, 13, 55, 13, 56, 13, 58,
    13, 66, 13, 68, 13, 69, 13, 70, 13, 80, 13, 82, 13, 85, 13, 86,
    13, 87, 13, 88, 13, 90, 13, 98, 13, 99, 14, 36, 14, 40, 14, 48,
    14, 50, 14, 66, 14, 68, 14, 69, 14, 70, 14, 80, 14, 82, 14, 85,
    15, 3, 15, 8, 15, 11, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50,
    15, 53, 15, 54, 15, 55, 15, 56, 15, 58, 15, 66, 15, 68, 15, 69,
    15, 70, 15, 80, 15, 82, 15, 85, 15, 86, 15, 87, 15, 88, 15, 90,
    15, 98, 15, 99, 16, 16, 16, 53, 16, 55, 16, 56, 16, 58, 32, 13,
    32, 15, 32, 34, 33, 53, 33, 58, 34, 3, 34, 8, 34, 11, 34, 32,
    34, 53, 34, 55, 34, 58, 34, 98, 34, 99, 35, 53, 35, 58, 35, 64,
    36, 3, 36, 8, 36, 11, 36, 56, 37, 64, 39, 7, 39, 13, 39, 15,
    39, 16, 39, 33, 39, 34, 39, 43, 39, 64, 39, 66, 39, 68, 39, 69,
    39, 70, 39, 72, 39, 75, 39, 78, 39, 79, 39, 80, 39, 81, 39, 82,
    39, 83, 39, 84, 39, 86, 39, 87, 39, 88, 39, 89, 39, 90, 39, 91,
    40, 64, 42, 64, 43, 64, 44, 7, 44, 14, 44, 33, 44, 36, 44, 40,
    44, 43, 44, 48, 44, 50, 44, 53, 44, 55, 44, 58, 44, 66, 44, 68,
    44, 69, 44, 70, 44, 71, 44, 80, 44, 82, 44, 85, 44, 86, 45, 3,
    45, 8, 45, 11, 45, 14, 45, 32, 45, 36, 45, 40, 45, 48, 45, 50,
    45, 53, 45, 55, 45, 58, 45, 64, 45, 87, 45, 88, 45, 90, 45, 98,
    45, 99, 48, 3, 48, 8, 48, 11, 48, 13, 48, 15, 48, 16, 48, 34,
    48, 43, 48, 53, 48, 55, 48, 57, 48, 58, 48, 59, 48, 64, 48, 99,
    49, 13, 49, 15, 49, 64, 50, 3, 50, 8, 50, 11, 50, 13, 50, 15,
    50, 16, 50, 34, 50, 43, 50, 53, 50, 55, 50, 57, 50, 58, 50, 59,
    50, 64, 50, 99, 51, 7, 51, 53, 51, 55, 51, 58, 51, 66, 51, 68,
    51, 69, 51, 70, 51, 72, 51, 80, 51, 82, 53, 7, 53, 13, 53, 14,
    53, 15, 53, 16, 53, 27, 53, 28, 53, 33, 53, 34, 53, 43, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 78, 53, 79, 53, 80,
    53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87, 53, 88, 53, 89,
    53, 90, 53, 91, 55, 10, 55, 32, 55, 98, 55, 99, 56, 32, 56, 98,
    56, 99, 57, 32, 57, 64, 57, 91, 57, 98, 57, 99, 58, 13, 58, 14,
    58, 15, 58, 16, 58, 34, 58, 66, 58, 68, 58, 69, 58, 70, 58, 72,
    58, 80, 58, 82, 59, 14, 60, 75, 64, 36, 64, 40, 64, 43, 64, 48,
    64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56, 64, 58, 64, 66,
    64, 68, 64, 69, 64, 70, 64, 77, 64, 80, 64, 82, 64, 84, 64, 85,
    64, 86, 64, 87, 64, 88, 66, 53, 66, 64, 67, 3, 67, 8, 67, 11,
    67, 53, 67, 55, 67, 58, 67, 64, 68, 53, 68, 55, 68, 58, 69, 64,
    70, 53, 70, 58, 71, 2, 71, 3, 71, 8, 71, 10, 71, 11, 71, 32,
    71, 52, 71, 53, 71, 55, 71, 56, 71, 58, 71, 62, 71, 94, 71, 98,
    71, 99, 72, 10, 72, 13, 72, 15, 72, 16, 72, 34, 72, 64, 72, 71,
    72, 75, 73, 3, 73, 8, 73, 11, 73, 53, 73, 55, 73, 58, 73, 64,
    74, 58, 75, 13, 75, 15, 75, 53, 75, 56, 75, 58, 76, 13, 76, 15,
    76, 59, 76, 64, 77, 53, 77, 58, 78, 3, 78, 8, 78, 11, 78, 53,
    78, 55, 78, 58, 79, 3, 79, 8, 79, 11, 79, 53, 79, 55, 79, 58,
    79, 64, 80, 3, 80, 8, 80, 11, 80, 13, 80, 15, 80, 53, 80, 55,
    80, 58, 80, 64, 80, 87, 80, 88, 80, 90, 81, 3, 81, 8, 81, 11,
    81, 53, 81, 55, 81, 58, 81, 64, 82, 53, 82, 58, 83, 3, 83, 8,
    83, 11, 83, 13, 83, 15, 83, 64, 83, 98, 83, 99, 84, 3, 84, 8,
    84, 11, 84, 53, 84, 55, 84, 56, 84, 57, 84, 58, 84, 64, 84, 72,
    84, 85, 84, 87, 84, 88, 84, 89, 84, 90, 85, 7, 85, 14, 85, 33,
    85, 53, 85, 55, 85, 58, 85, 66, 85, 68, 85, 69, 85, 70, 85, 71,
    85, 72, 85, 80, 85, 82, 85, 85, 86, 53, 86, 55, 86, 58, 87, 13,
    87, 15, 87, 53, 87, 58, 87, 64, 88, 3, 88, 8, 88, 11, 88, 98,
    88, 99, 89, 14, 89, 53, 90, 13, 90, 15, 90, 43, 90, 53, 90, 58,
    90, 64, 91, 34, 91, 98, 91, 99, 98, 13, 98, 15, 98, 34, 98, 43,
    99, 13, 99, 15, 99, 34, 99, 43, 100, 64,
};

static const int8_t kern_pair_values[] = {
    -20, -20, -18, -7, -16, -16, -16, 2, 2, 2, 2, -20, -20, -18, 6, 4,
    4, 4, -20, -20, -18, 6, 3, 3, 4, 4, 4, -20, -20, -20, -17, -13,
    -13, -13, -13, -18, -12, -13, -7, -13, -10, -10, -10, -10, -10, -10, -6, -10,
    -11, -8, -10, -11, -11, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2,
    -20, -20, -20, -17, -13, -13, -13, -13, -18, -12, -13, -7, -13, -10, -10, -10,
    -10, -10, -10, -6, -10, -11, -8, -10, -11, -11, -27, 7, 4, 4, 4, -26,
    -26, -4, -11, -13, -18, -18, -18, -7, -12, -11, -16, -7, -9, -6, -9, -11,
    2, 2, 2, 2, -12, -7, -18, -18, -9, -4, -8, -6, -22, -7, -7, -7,
    -7, -7, -2, -4, -4, -7, -4, -7, -4, -4, -6, -4, -2, -8, -4, -2,
    4, 2, -10, -6, -12, -9, -6, -6, -3, -6, -6, -4, -3, -3, -9, -9,
    -9, -9, -4, -9, -9, -4, -7, -22, -22, -22, -9, -10, -7, -7, -7, -7,
    -15, -14, -16, 11, -11, -7, -9, -16, -13, -4, -4, -4, -8, -8, -7, -1,
    -2, -7, -7, -3, -11, -2, -12, -1, -22, -22, -22, -4, -4, -4, -8, -8,
    -7, -1, -2, -7, -7, -3, -11, -2, -12, -1, -6, -5, -6, -9, -7, -7,
    -7, -7, -7, -7, -7, -6, -18, -11, -18, -16, -9, -9, -7, -12, -7, -9,
    -15, -15, -15, -15, -18, -10, -10, -15, -10, -15, -10, -15, -11, -8, -9, -11,
    -9, -11, 4, 3, 9, 9, 7, 9, 9, 2, 4, 2, 4, 4, -13, -11,
    -13, -13, -12, -11, -11, -11, -11, -12, -11, -11, -9, 2, -22, -22, -13, -22,
    -22, -13, -18, -24, -16, -11, -18, -20, -20, -20, -20, -6, -20, -20, -10, -10,
    -12, -16, -9, -13, 9, -9, -9, -9, -16, -10, -16, -9, -10, -6, -11, 9,
    -16, -13, 4, 7, 7, 6, 7, 7, 7, 8, 3, 4, 4, 3, 3, 9,
    11, 9, 7, 7, 11, 6, 18, 7, 10, -8, -8, -8, -12, -8, -13, 9,
    -6, -2, -2, -13, -2, -13, 4, 4, 4, 7, -4, -6, -8, -8, -8, -12,
    -8, -13, -8, -8, -8, -12, -8, -13, 9, -9, -9, -9, -4, -4, -16, -10,
    -16, -9, -6, -5, -6, -9, -9, -9, -16, -10, -16, -9, -13, -13, 7, 7,
    7, -15, -15, -13, 7, 7, -4, -4, -4, -15, -11, -4, -4, -16, -4, -3,
    -4, -4, -4, -4, -4, -1, -4, -2, -5, -1, -4, -1, -1, -1, -1, -1,
    -2, -1, -1, -1, -13, -7, -11, -10, -10, -8, -6, -11, 4, 4, 4, 6,
    4, -8, -11, -10, -10, -6, -9, -6, -13, 4, 4, 4, -11, -11, -7, -9,
    -11, -11, -11, -9, 9,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 469,
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
const lv_font_t humid1_font_plex_sans_italic_14 = {
#else
lv_font_t humid1_font_plex_sans_italic_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_14 */
