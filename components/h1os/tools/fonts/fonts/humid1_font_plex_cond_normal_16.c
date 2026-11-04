/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_16 (IBM Plex Cond Normal)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_16
#define HUMID1_FONT_PLEX_COND_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xaa, 0xaa, 0x8f,
    /* U+0022 "" (4x4) */
    0x99, 0x99,
    /* U+0023 "#" (8x12) */
    0x12, 0x12, 0x22, 0x22, 0xff, 0x24, 0x24, 0x24, 0xff, 0x44, 0x44, 0x48,
    /* U+0024 "$" (7x16) */
    0x10, 0x21, 0xf6, 0xb9, 0x12, 0x34, 0x3c, 0x1c, 0x24, 0x4c, 0x9d, 0x6f,
    0x84, 0x08,
    /* U+0025 "%" (12x12) */
    0x70, 0x48, 0x88, 0x89, 0x88, 0x90, 0x8b, 0x08, 0xae, 0x75, 0x10, 0xd1,
    0x09, 0x11, 0x91, 0x11, 0x12, 0x0e,
    /* U+0026 "&" (8x12) */
    0x38, 0x44, 0x44, 0x44, 0x6c, 0x38, 0x73, 0x8a, 0x8e, 0x84, 0xc6, 0x7b,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (4x16) */
    0x24, 0x44, 0x88, 0x88, 0x88, 0x88, 0x44, 0x23,
    /* U+0029 ")" (4x16) */
    0x46, 0x22, 0x11, 0x11, 0x11, 0x11, 0x22, 0x4c,
    /* U+002A "" (6x6) */
    0x10, 0x4f, 0xcc, 0x28, 0x20,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00,
    /* U+002C "," (2x4) */
    0xf6,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x15) */
    0x08, 0x44, 0x21, 0x08, 0x84, 0x21, 0x10, 0x84, 0x62, 0x00,
    /* U+0030 "0" (7x12) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x05, 0x11, 0xc0,
    /* U+0031 "1" (7x12) */
    0x30, 0xa2, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x47, 0xf0,
    /* U+0032 "2" (7x12) */
    0x79, 0x9a, 0x10, 0x20, 0x41, 0x82, 0x08, 0x20, 0xc3, 0x07, 0xf0,
    /* U+0033 "3" (6x12) */
    0x7b, 0x10, 0x41, 0x0c, 0xc0, 0xc1, 0x04, 0x1c, 0xde,
    /* U+0034 "4" (8x12) */
    0x0c, 0x0c, 0x14, 0x14, 0x24, 0x24, 0x44, 0x44, 0x84, 0xff, 0x04, 0x04,
    /* U+0035 "5" (6x12) */
    0xfe, 0x08, 0x20, 0xbb, 0x30, 0x41, 0x06, 0x18, 0x9c,
    /* U+0036 "6" (7x12) */
    0x18, 0x61, 0x82, 0x0b, 0xd8, 0xa0, 0xc1, 0x83, 0x05, 0x11, 0xc0,
    /* U+0037 "7" (7x12) */
    0xff, 0x0a, 0x10, 0x60, 0x81, 0x06, 0x08, 0x10, 0x60, 0x81, 0x00,
    /* U+0038 "8" (7x12) */
    0x7d, 0x8e, 0x0c, 0x1c, 0x67, 0x31, 0xc1, 0x83, 0x07, 0x1b, 0xe0,
    /* U+0039 "9" (7x12) */
    0x79, 0x8a, 0x0c, 0x18, 0x38, 0xde, 0x82, 0x04, 0x18, 0x61, 0x80,
    /* U+003A ":" (2x9) */
    0xf0, 0x03, 0xc0,
    /* U+003B ";" (2x11) */
    0xf0, 0x03, 0xf8,
    /* U+003C "<" (6x9) */
    0x0c, 0x63, 0x30, 0x81, 0x83, 0x03, 0x04,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x9) */
    0xc1, 0x83, 0x03, 0x04, 0x63, 0x30, 0x80,
    /* U+003F "?" (6x12) */
    0x7b, 0x18, 0x41, 0x0c, 0xc2, 0x08, 0x00, 0x03, 0x0c,
    /* U+0040 "@" (11x14) */
    0x1f, 0x04, 0x19, 0x01, 0x27, 0x99, 0x13, 0x22, 0x64, 0x4c, 0x89, 0x91,
    0x31, 0xf9, 0x00, 0x20, 0x02, 0x00, 0x3f, 0x00,
    /* U+0041 "A" (9x12) */
    0x0c, 0x0a, 0x05, 0x02, 0x81, 0x21, 0x10, 0x88, 0x7e, 0x41, 0x20, 0x90,
    0x58, 0x30,
    /* U+0042 "B" (7x12) */
    0xfd, 0x06, 0x0c, 0x18, 0x3f, 0xa0, 0xc1, 0x83, 0x06, 0x0f, 0xe0,
    /* U+0043 "C" (7x12) */
    0x3c, 0x8e, 0x0c, 0x08, 0x10, 0x20, 0x40, 0x81, 0x05, 0x19, 0xe0,
    /* U+0044 "D" (7x12) */
    0xf9, 0x0a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x17, 0xc0,
    /* U+0045 "E" (6x12) */
    0xfe, 0x08, 0x20, 0x83, 0xf8, 0x20, 0x82, 0x08, 0x3f,
    /* U+0046 "F" (6x12) */
    0xfe, 0x08, 0x20, 0x83, 0xe8, 0x20, 0x82, 0x08, 0x20,
    /* U+0047 "G" (8x12) */
    0x3c, 0x42, 0xc1, 0x80, 0x80, 0x80, 0x87, 0x81, 0x81, 0x41, 0x43, 0x3d,
    /* U+0048 "H" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x3f, 0xe0, 0xc1, 0x83, 0x06, 0x0c, 0x10,
    /* U+0049 "I" (4x12) */
    0xf2, 0x22, 0x22, 0x22, 0x22, 0x2f,
    /* U+004A "J" (5x12) */
    0x78, 0x42, 0x10, 0x84, 0x21, 0x0c, 0x62, 0xe0,
    /* U+004B "K" (7x12) */
    0x87, 0x0a, 0x24, 0xc9, 0x14, 0x3c, 0x68, 0x89, 0x1a, 0x14, 0x30,
    /* U+004C "L" (5x12) */
    0x84, 0x21, 0x08, 0x42, 0x10, 0x84, 0x21, 0xf0,
    /* U+004D "M" (9x12) */
    0xc1, 0xe0, 0xe8, 0xb4, 0x59, 0x4c, 0xa6, 0x53, 0x11, 0x88, 0xc0, 0x60,
    0x30, 0x10,
    /* U+004E "N" (7x12) */
    0xc3, 0x87, 0x0d, 0x1a, 0x32, 0x64, 0xc5, 0x8b, 0x16, 0x1c, 0x30,
    /* U+004F "O" (8x12) */
    0x3c, 0x42, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x42, 0x3c,
    /* U+0050 "P" (7x12) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x40, 0x81, 0x02, 0x04, 0x00,
    /* U+0051 "Q" (8x15) */
    0x3c, 0x42, 0xc2, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3e,
    0x08, 0x08, 0x0c,
    /* U+0052 "R" (7x12) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x46, 0x8d, 0x0a, 0x1c, 0x10,
    /* U+0053 "S" (7x12) */
    0x7d, 0x8e, 0x04, 0x0c, 0x0f, 0x07, 0x01, 0x03, 0x07, 0x1b, 0xe0,
    /* U+0054 "T" (8x12) */
    0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    /* U+0055 "U" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x05, 0x13, 0xe0,
    /* U+0056 "V" (8x12) */
    0xc1, 0x41, 0x43, 0x63, 0x22, 0x22, 0x26, 0x34, 0x14, 0x14, 0x14, 0x18,
    /* U+0057 "W" (13x12) */
    0xc6, 0x1a, 0x28, 0x91, 0x44, 0x8a, 0x24, 0x53, 0x32, 0x90, 0xb6, 0x85,
    0x14, 0x28, 0xa1, 0x45, 0x0a, 0x30, 0x21, 0x80,
    /* U+0058 "X" (7x12) */
    0x83, 0x8d, 0x13, 0x62, 0x87, 0x0e, 0x14, 0x6c, 0x8b, 0x1c, 0x10,
    /* U+0059 "Y" (7x12) */
    0x83, 0x8d, 0x12, 0x22, 0x85, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    /* U+005A "Z" (7x12) */
    0xfe, 0x0c, 0x10, 0x60, 0x82, 0x0c, 0x10, 0x60, 0x82, 0x07, 0xf0,
    /* U+005B "[" (2x15) */
    0xea, 0xaa, 0xaa, 0xac,
    /* U+005C "" (4x15) */
    0x88, 0x8c, 0x44, 0x46, 0x22, 0x21, 0x11, 0x10,
    /* U+005D "]" (2x15) */
    0xd5, 0x55, 0x55, 0x5c,
    /* U+005E "^" (7x7) */
    0x30, 0x51, 0xa2, 0x2c, 0x50, 0xe0, 0x00,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xb4,
    /* U+0061 "a" (7x9) */
    0x79, 0x88, 0x10, 0x27, 0xd0, 0xa1, 0x46, 0x76,
    /* U+0062 "b" (6x13) */
    0x82, 0x08, 0x20, 0xfb, 0x28, 0x61, 0x86, 0x18, 0x72, 0xb8,
    /* U+0063 "c" (6x9) */
    0x79, 0x38, 0x20, 0x82, 0x08, 0x13, 0x78,
    /* U+0064 "d" (6x13) */
    0x04, 0x10, 0x41, 0x7d, 0x38, 0x61, 0x86, 0x18, 0x53, 0x74,
    /* U+0065 "e" (6x9) */
    0x79, 0x28, 0x61, 0xfe, 0x08, 0x13, 0x78,
    /* U+0066 "f" (4x13) */
    0x74, 0x44, 0xf4, 0x44, 0x44, 0x44, 0x40,
    /* U+0067 "g" (7x13) */
    0x06, 0x71, 0x12, 0x24, 0x47, 0x10, 0x20, 0x40, 0xfa, 0x0c, 0x17, 0xc0,
    /* U+0068 "h" (6x13) */
    0x82, 0x08, 0x20, 0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x84,
    /* U+0069 "i" (1x13) */
    0x8f, 0xf8,
    /* U+006A "j" (2x16) */
    0x40, 0x55, 0x55, 0x57,
    /* U+006B "k" (6x13) */
    0x82, 0x08, 0x20, 0x8a, 0x6b, 0x28, 0xf2, 0x49, 0xa2, 0x8c,
    /* U+006C "l" (2x13) */
    0xaa, 0xaa, 0xaa, 0xc0,
    /* U+006D "m" (11x9) */
    0xb9, 0xd9, 0xce, 0x10, 0xc2, 0x18, 0x43, 0x08, 0x61, 0x0c, 0x21, 0x84,
    0x20,
    /* U+006E "n" (6x9) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0x61, 0x84,
    /* U+006F "o" (7x9) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xa2, 0x38,
    /* U+0070 "p" (6x12) */
    0xfb, 0x28, 0x61, 0x86, 0x18, 0x72, 0xba, 0x08, 0x20,
    /* U+0071 "q" (6x12) */
    0x7d, 0x38, 0x61, 0x86, 0x18, 0x53, 0x74, 0x10, 0x41,
    /* U+0072 "r" (4x9) */
    0xbc, 0x88, 0x88, 0x88, 0x80,
    /* U+0073 "s" (5x9) */
    0x74, 0x61, 0x87, 0x04, 0x31, 0x70,
    /* U+0074 "t" (4x11) */
    0x44, 0xf4, 0x44, 0x44, 0x44, 0x70,
    /* U+0075 "u" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x74,
    /* U+0076 "v" (7x9) */
    0xc2, 0x89, 0x12, 0x22, 0xc5, 0x0a, 0x14, 0x10,
    /* U+0077 "w" (10x9) */
    0x88, 0x65, 0x29, 0x4a, 0x52, 0xd4, 0x95, 0x25, 0x31, 0x8c, 0x63, 0x00,
    /* U+0078 "x" (6x9) */
    0x8f, 0x25, 0x0c, 0x31, 0x44, 0xa2, 0x8c,
    /* U+0079 "y" (6x12) */
    0x87, 0x14, 0x53, 0x68, 0xa2, 0x8c, 0x10, 0x42, 0x18,
    /* U+007A "z" (6x9) */
    0xfc, 0x30, 0x84, 0x30, 0x84, 0x30, 0xfc,
    /* U+007B "{" (4x15) */
    0x32, 0x22, 0x22, 0x2c, 0x62, 0x22, 0x22, 0x30,
    /* U+007C "|" (1x16) */
    0xff, 0xff,
    /* U+007D "}" (4x15) */
    0xc4, 0x44, 0x44, 0x43, 0x64, 0x44, 0x44, 0xc0,
    /* U+007E "~" (6x2) */
    0xf0, 0x70,
    /* U+00B0 "" (5x6) */
    0x74, 0x63, 0x18, 0xb8,
    /* U+00B1 "" (7x10) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00, 0x01, 0xfc,
    /* U+00B2 "" (4x6) */
    0x79, 0x12, 0x4f,
    /* U+00B3 "" (4x6) */
    0x71, 0x61, 0x96,
    /* U+00B5 "" (6x12) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0xf6, 0x08, 0x20,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0xc5, 0xa3, 0x0e, 0x4f, 0x10,
    /* U+00F7 "" (7x9) */
    0x30, 0x60, 0x00, 0x0f, 0xe0, 0x00, 0x18, 0x30,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 54, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 98, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 5, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 138, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 214, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 56, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 62, .adv_w = 77, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 70, .adv_w = 77, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 78, .adv_w = 106, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 83, .adv_w = 138, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 90, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 92, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 92, .adv_w = 63, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 89, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 103, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 138, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 138, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 66, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 66, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 216, .adv_w = 138, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 138, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 227, .adv_w = 138, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 110, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 206, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 263, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 151, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 155, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 135, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 129, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 163, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 93, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 118, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 116, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 163, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 163, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 447, .adv_w = 148, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 132, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 156, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 207, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 73, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 561, .adv_w = 89, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 569, .adv_w = 73, .box_w = 2, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 573, .adv_w = 138, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 580, .adv_w = 130, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 581, .adv_w = 138, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 582, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 75, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 122, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 131, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 58, .box_w = 1, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 58, .box_w = 2, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 659, .adv_w = 122, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 63, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 201, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 710, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 719, .adv_w = 85, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 112, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 81, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 179, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 763, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 115, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 779, .adv_w = 108, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 794, .adv_w = 74, .box_w = 1, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 796, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 804, .adv_w = 138, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 806, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 810, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 82, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 822, .adv_w = 82, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 825, .adv_w = 133, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 834, .adv_w = 76, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 835, .adv_w = 138, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 840, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0}
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
    3, 13, 3, 15, 3, 34, 3, 53, 3, 87, 3, 88, 3, 90, 6, 3,
    6, 8, 6, 11, 7, 53, 7, 58, 8, 13, 8, 15, 8, 34, 8, 36,
    8, 40, 8, 43, 8, 48, 8, 50, 8, 68, 8, 69, 8, 70, 8, 72,
    8, 80, 8, 82, 9, 75, 11, 13, 11, 15, 11, 34, 11, 36, 11, 40,
    11, 43, 11, 48, 11, 50, 11, 68, 11, 69, 11, 70, 11, 72, 11, 80,
    11, 82, 13, 3, 13, 8, 13, 11, 13, 32, 13, 36, 13, 40, 13, 48,
    13, 50, 13, 53, 13, 54, 13, 55, 13, 56, 13, 58, 13, 87, 13, 88,
    13, 90, 13, 98, 13, 99, 14, 34, 14, 42, 14, 43, 14, 52, 14, 53,
    14, 55, 14, 57, 14, 58, 14, 59, 14, 89, 14, 91, 15, 3, 15, 8,
    15, 11, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 54,
    15, 55, 15, 56, 15, 58, 15, 87, 15, 88, 15, 90, 15, 98, 15, 99,
    16, 16, 16, 34, 16, 36, 16, 40, 16, 43, 16, 48, 16, 50, 16, 52,
    16, 66, 16, 68, 16, 69, 16, 70, 16, 72, 16, 74, 16, 75, 16, 78,
    16, 79, 16, 80, 16, 82, 16, 83, 16, 84, 16, 86, 16, 89, 32, 13,
    32, 15, 33, 53, 33, 55, 33, 58, 34, 3, 34, 8, 34, 11, 34, 13,
    34, 15, 34, 43, 34, 53, 34, 58, 34, 64, 34, 99, 36, 64, 37, 13,
    37, 15, 37, 16, 37, 34, 37, 53, 37, 55, 37, 57, 37, 58, 37, 59,
    37, 64, 39, 13, 39, 15, 39, 16, 39, 34, 39, 43, 39, 64, 39, 72,
    42, 14, 43, 64, 44, 14, 45, 3, 45, 8, 45, 11, 45, 13, 45, 15,
    45, 16, 45, 34, 45, 53, 45, 58, 45, 59, 45, 64, 45, 89, 45, 91,
    45, 98, 45, 99, 48, 13, 48, 15, 48, 64, 49, 7, 49, 13, 49, 15,
    49, 16, 49, 34, 49, 43, 49, 59, 49, 64, 49, 72, 50, 13, 50, 15,
    50, 64, 52, 14, 53, 3, 53, 8, 53, 10, 53, 11, 53, 13, 53, 14,
    53, 15, 53, 16, 53, 34, 53, 53, 53, 58, 53, 64, 53, 66, 53, 68,
    53, 69, 53, 70, 53, 72, 53, 80, 53, 82, 53, 84, 53, 86, 53, 91,
    53, 99, 54, 13, 54, 15, 54, 16, 54, 64, 55, 7, 55, 13, 55, 14,
    55, 15, 55, 16, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 48,
    55, 50, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72, 55, 80,
    55, 82, 55, 84, 56, 13, 56, 15, 56, 64, 57, 14, 58, 7, 58, 13,
    58, 14, 58, 15, 58, 16, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36,
    58, 40, 58, 43, 58, 48, 58, 50, 58, 52, 58, 64, 58, 66, 58, 67,
    58, 68, 58, 69, 58, 70, 58, 71, 58, 72, 58, 73, 58, 74, 58, 75,
    58, 76, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82, 58, 83, 58, 84,
    58, 85, 58, 86, 58, 87, 58, 88, 58, 89, 58, 90, 58, 91, 59, 3,
    59, 8, 59, 11, 59, 13, 59, 15, 59, 16, 59, 64, 59, 91, 59, 98,
    59, 99, 64, 36, 64, 40, 64, 48, 64, 50, 64, 53, 64, 54, 64, 55,
    64, 56, 64, 57, 64, 58, 64, 59, 64, 68, 64, 69, 64, 70, 64, 72,
    64, 75, 64, 80, 64, 82, 64, 87, 66, 3, 66, 8, 66, 11, 66, 53,
    66, 55, 66, 58, 67, 14, 67, 53, 68, 98, 68, 99, 70, 53, 70, 55,
    70, 58, 70, 64, 71, 13, 71, 15, 71, 16, 71, 43, 71, 64, 73, 53,
    73, 58, 74, 58, 75, 53, 75, 55, 75, 56, 75, 58, 76, 7, 76, 14,
    76, 33, 76, 53, 76, 55, 76, 58, 76, 72, 76, 86, 76, 87, 76, 98,
    76, 99, 78, 3, 78, 8, 78, 11, 78, 53, 78, 55, 78, 56, 78, 58,
    78, 87, 78, 90, 79, 53, 79, 58, 80, 53, 80, 58, 80, 64, 81, 14,
    81, 53, 83, 3, 83, 8, 83, 11, 83, 13, 83, 15, 83, 36, 83, 40,
    83, 48, 83, 50, 83, 55, 83, 56, 83, 64, 83, 71, 83, 85, 83, 87,
    83, 88, 83, 90, 83, 98, 83, 99, 84, 53, 84, 58, 86, 53, 87, 3,
    87, 8, 87, 11, 87, 13, 87, 15, 87, 64, 88, 3, 88, 8, 88, 11,
    88, 99, 89, 3, 89, 8, 89, 11, 89, 34, 89, 64, 90, 3, 90, 8,
    90, 11, 90, 13, 90, 15, 90, 64, 90, 98, 91, 14, 91, 53, 98, 13,
    98, 15, 98, 88, 99, 13, 99, 15, 99, 34,
};

static const int8_t kern_pair_values[] = {
    -20, -20, -13, 6, 8, 6, 6, -15, -15, -15, -13, -12, -20, -20, -13, -3,
    -3, -8, -3, -3, -5, -5, -5, -3, -5, -5, 13, -20, -20, -13, -3, -3,
    -8, -3, -3, -5, -5, -5, -3, -5, -5, -20, -20, -20, -19, -13, -13, -13,
    -13, -23, -9, -17, -13, -19, -14, -10, -11, -13, -13, -5, -9, -7, -5, -13,
    -9, -13, -15, -9, -9, -6, -20, -20, -20, -19, -13, -13, -13, -13, -23, -9,
    -17, -13, -19, -14, -10, -11, -13, -13, -31, -17, -6, -6, -8, -6, -6, -3,
    -9, -10, -10, -10, -9, -4, -4, -4, -4, -10, -10, -4, -4, -4, -3, -29,
    -29, -10, -8, -10, -13, -13, -13, 5, 5, 4, -15, -15, 5, -13, -11, -11,
    -11, -8, -7, -7, -4, -5, -7, -5, -20, -24, -24, -13, -15, -11, -33, -10,
    -9, -18, -14, -17, -17, -17, 6, 6, 7, 4, -16, -18, 4, 9, 4, 5,
    -18, -15, -13, -13, -23, -6, -27, -27, -15, -15, -9, -6, -36, -6, -13, -13,
    -23, 3, 6, 6, 5, 6, -23, -13, -23, -20, -15, 6, 4, -19, -17, -15,
    -15, -15, -19, -15, -15, -17, -13, -13, 4, -9, -9, -8, -15, -9, -17, -9,
    -17, -13, -8, -12, -6, -6, -7, -6, -6, -20, -8, -8, -8, -8, -11, -8,
    -8, -6, -13, -13, -14, -13, -12, -19, -15, -19, -19, -10, -10, -10, -15, -8,
    -8, -7, -8, -8, -5, -19, -13, -2, -13, -12, -13, -3, -15, -2, -3, -4,
    -2, -10, -10, -13, -11, -12, -10, -10, -3, -9, -5, -4, -6, -6, -6, 3,
    3, 3, 8, 8, 3, 5, 5, 3, 3, -23, -23, -23, -23, -19, -15, -20,
    -14, 6, -19, 8, -15, -12, -15, 10, 15, -15, -12, -15, -6, -6, -6, -17,
    -8, -13, 3, -18, 4, 4, -14, -8, -13, -13, -10, -10, -4, -5, -12, -14,
    -13, -5, -6, -6, -3, -9, -4, -11, -3, -7, -4, -10, -3, -3, -3, -5,
    -5, -5, -5, -5, -14, -8, -5, -13, -2, -2, -14, -13, -15, -13, -14, 3,
    -18, 8, 8, 8, -19, -19, 3, 3, 3, 3, 3, 5, -18, 3, 3, 4,
    4, 4, 8, 5, -14, -11, -12, 8, 8, 8, -14, -14, -15, 6, 6, 6,
    5, 2, 2, 2, 2, 5, 6, 6, 6, -17, -17, -18, 6, -6, -9, -13,
    -13, 6, -13, -13, -13,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 405,
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
const lv_font_t humid1_font_plex_cond_normal_16 = {
#else
lv_font_t humid1_font_plex_cond_normal_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
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
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_16 */
