/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_16 (IBM Plex Sans Italic)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_16
#define HUMID1_FONT_PLEX_SANS_ITALIC_16 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x12) */
    0x25, 0xb4, 0x92, 0x02, 0x40,
    /* U+0022 "" (5x5) */
    0x4a, 0xf5, 0x29, 0x00,
    /* U+0023 "#" (10x12) */
    0x0c, 0x82, 0x40, 0x91, 0xff, 0x12, 0x04, 0x83, 0x20, 0x98, 0xff, 0x09,
    0x04, 0x81, 0x20,
    /* U+0024 "$" (9x16) */
    0x02, 0x02, 0x07, 0xc6, 0xb2, 0x41, 0x20, 0xd0, 0x78, 0x0f, 0x04, 0x82,
    0x41, 0x2d, 0x21, 0xe0, 0x40, 0x20,
    /* U+0025 "%" (11x12) */
    0x70, 0x5b, 0x1a, 0x22, 0x4c, 0x89, 0x21, 0x29, 0xbb, 0x48, 0xd9, 0x12,
    0x24, 0x45, 0x09, 0x60, 0xe0,
    /* U+0026 "&" (9x12) */
    0x1c, 0x19, 0x08, 0x84, 0x42, 0x41, 0xc1, 0xc7, 0x92, 0x8e, 0x43, 0x23,
    0x8f, 0x20,
    /* U+0027 "'" (2x5) */
    0x5e, 0x80,
    /* U+0028 "(" (5x16) */
    0x08, 0x8c, 0x44, 0x21, 0x18, 0x84, 0x21, 0x0c, 0x21, 0x04,
    /* U+0029 ")" (5x16) */
    0x10, 0xc2, 0x10, 0x84, 0x21, 0x08, 0x44, 0x23, 0x11, 0x10,
    /* U+002A "" (6x6) */
    0x30, 0x8f, 0xc8, 0x52, 0x40,
    /* U+002B "+" (8x9) */
    0x08, 0x08, 0x08, 0x08, 0xff, 0x10, 0x10, 0x10, 0x10,
    /* U+002C "," (2x4) */
    0x56,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (8x15) */
    0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x30, 0x20, 0x60,
    0x40, 0x40, 0x80,
    /* U+0030 "0" (8x12) */
    0x1e, 0x32, 0x61, 0x41, 0x41, 0xc3, 0xc3, 0x82, 0x82, 0xc6, 0x44, 0x78,
    /* U+0031 "1" (7x12) */
    0x0c, 0x29, 0x92, 0x60, 0xc1, 0x02, 0x04, 0x08, 0x30, 0x47, 0xf0,
    /* U+0032 "2" (8x12) */
    0x1e, 0x22, 0x43, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xfe,
    /* U+0033 "3" (8x12) */
    0x1e, 0x62, 0x03, 0x02, 0x06, 0x18, 0x06, 0x02, 0x02, 0x86, 0x84, 0x78,
    /* U+0034 "4" (8x12) */
    0x07, 0x06, 0x0e, 0x1a, 0x12, 0x36, 0x66, 0xc4, 0x84, 0xfe, 0x0c, 0x0c,
    /* U+0035 "5" (8x12) */
    0x3f, 0x20, 0x20, 0x20, 0x5c, 0x66, 0x02, 0x02, 0x02, 0x86, 0xc4, 0x78,
    /* U+0036 "6" (7x12) */
    0x06, 0x30, 0xc1, 0x06, 0x0b, 0xb1, 0xe1, 0x83, 0x05, 0x13, 0xc0,
    /* U+0037 "7" (8x12) */
    0x7f, 0xc2, 0x86, 0x04, 0x0c, 0x08, 0x18, 0x10, 0x20, 0x60, 0x40, 0xc0,
    /* U+0038 "8" (8x12) */
    0x1e, 0x23, 0x61, 0x63, 0x22, 0x1c, 0x66, 0xc2, 0x82, 0x82, 0xc6, 0x78,
    /* U+0039 "9" (7x12) */
    0x3c, 0x8f, 0x0c, 0x18, 0x78, 0xdf, 0x02, 0x08, 0x30, 0xc3, 0x00,
    /* U+003A ":" (3x9) */
    0x6c, 0x00, 0x06, 0x80,
    /* U+003B ";" (4x11) */
    0x33, 0x00, 0x00, 0x06, 0x44, 0x80,
    /* U+003C "<" (7x9) */
    0x06, 0x38, 0xc6, 0x08, 0x18, 0x0c, 0x0c, 0x08,
    /* U+003D "=" (8x5) */
    0x7f, 0x00, 0x00, 0x00, 0xfe,
    /* U+003E ">" (7x9) */
    0x60, 0x60, 0x30, 0x30, 0x21, 0x8c, 0x70, 0x80,
    /* U+003F "?" (6x12) */
    0x7a, 0x38, 0xc3, 0x19, 0xc4, 0x10, 0x00, 0x0c, 0x30,
    /* U+0040 "@" (12x14) */
    0x07, 0xc1, 0x86, 0x20, 0x36, 0x69, 0x49, 0x95, 0x09, 0x91, 0x99, 0x13,
    0x91, 0x28, 0xfc, 0x80, 0x04, 0x00, 0x60, 0x03, 0xf0,
    /* U+0041 "A" (9x12) */
    0x06, 0x03, 0x03, 0xc1, 0x61, 0x90, 0x88, 0xc4, 0x7e, 0x41, 0x20, 0xb0,
    0x70, 0x30,
    /* U+0042 "B" (9x12) */
    0x3f, 0x10, 0x98, 0x68, 0x24, 0x33, 0xe1, 0x0d, 0x82, 0xc1, 0x41, 0xa0,
    0x9f, 0x80,
    /* U+0043 "C" (9x12) */
    0x1e, 0x18, 0x98, 0x68, 0x0c, 0x04, 0x02, 0x01, 0x00, 0x80, 0x41, 0x91,
    0x87, 0x80,
    /* U+0044 "D" (9x12) */
    0x3e, 0x10, 0x98, 0x68, 0x14, 0x0a, 0x0d, 0x07, 0x83, 0xc1, 0x41, 0xa1,
    0x9f, 0x80,
    /* U+0045 "E" (8x12) */
    0x3f, 0x20, 0x60, 0x40, 0x40, 0x7e, 0x40, 0xc0, 0xc0, 0x80, 0x80, 0xfe,
    /* U+0046 "F" (8x12) */
    0x3f, 0x20, 0x60, 0x40, 0x40, 0x7e, 0x40, 0xc0, 0xc0, 0x80, 0x80, 0x80,
    /* U+0047 "G" (9x12) */
    0x1f, 0x18, 0xd8, 0x28, 0x0c, 0x04, 0x02, 0x1f, 0x03, 0x81, 0x60, 0x90,
    0xc7, 0xe0,
    /* U+0048 "H" (10x12) */
    0x20, 0xc8, 0x36, 0x09, 0x02, 0x40, 0x9f, 0xe4, 0x1b, 0x06, 0xc1, 0x20,
    0x48, 0x12, 0x0c,
    /* U+0049 "I" (7x12) */
    0x3e, 0x10, 0x60, 0x81, 0x02, 0x04, 0x18, 0x30, 0x40, 0x87, 0xc0,
    /* U+004A "J" (8x12) */
    0x1f, 0x03, 0x02, 0x02, 0x02, 0x02, 0x06, 0x06, 0x04, 0x84, 0xcc, 0x78,
    /* U+004B "K" (9x12) */
    0x21, 0x90, 0x98, 0x8c, 0x84, 0x82, 0xc1, 0xa1, 0x98, 0xc4, 0x43, 0x20,
    0x90, 0x60,
    /* U+004C "L" (6x12) */
    0x20, 0x86, 0x18, 0x41, 0x04, 0x30, 0xc2, 0x08, 0x3f,
    /* U+004D "M" (11x12) */
    0x30, 0x66, 0x0d, 0xc2, 0xbc, 0xd4, 0x96, 0x94, 0x93, 0x96, 0x22, 0xc8,
    0x50, 0x1a, 0x03, 0x40, 0x40,
    /* U+004E "N" (10x12) */
    0x30, 0x4c, 0x37, 0x09, 0x62, 0x48, 0x92, 0x24, 0xdb, 0x16, 0xc5, 0x21,
    0xc8, 0x32, 0x0c,
    /* U+004F "O" (9x12) */
    0x1e, 0x18, 0xd8, 0x28, 0x1c, 0x0e, 0x06, 0x03, 0x01, 0x81, 0xc0, 0x90,
    0x87, 0x80,
    /* U+0050 "P" (9x12) */
    0x3f, 0x10, 0x98, 0x6c, 0x34, 0x12, 0x19, 0xf9, 0x80, 0xc0, 0x40, 0x20,
    0x10, 0x00,
    /* U+0051 "Q" (9x15) */
    0x1e, 0x18, 0xd8, 0x28, 0x1c, 0x0e, 0x06, 0x03, 0x01, 0x81, 0xc0, 0xb0,
    0xcf, 0xc1, 0x80, 0x80, 0x60,
    /* U+0052 "R" (9x12) */
    0x3f, 0x10, 0x98, 0x6c, 0x34, 0x12, 0x19, 0xf9, 0x88, 0xc4, 0x43, 0x21,
    0x90, 0x40,
    /* U+0053 "S" (9x12) */
    0x1f, 0x18, 0xc8, 0x04, 0x03, 0x01, 0xf0, 0x1c, 0x02, 0x01, 0x00, 0xb0,
    0x87, 0x80,
    /* U+0054 "T" (8x12) */
    0xff, 0x10, 0x10, 0x30, 0x30, 0x20, 0x20, 0x20, 0x20, 0x60, 0x60, 0x40,
    /* U+0055 "U" (9x12) */
    0x20, 0xb0, 0x58, 0x28, 0x14, 0x1a, 0x09, 0x05, 0x82, 0xc1, 0x61, 0x11,
    0x87, 0x80,
    /* U+0056 "V" (8x12) */
    0x81, 0x83, 0x82, 0x86, 0xc4, 0xc4, 0xc8, 0x48, 0x50, 0x50, 0x60, 0x60,
    /* U+0057 "W" (13x12) */
    0x86, 0x1c, 0x30, 0xa3, 0x85, 0x14, 0x68, 0xa2, 0x49, 0x32, 0x49, 0x14,
    0x48, 0xa2, 0x85, 0x14, 0x30, 0xe1, 0x86, 0x00,
    /* U+0058 "X" (10x12) */
    0x20, 0x44, 0x21, 0x18, 0x6c, 0x0a, 0x03, 0x00, 0xc0, 0x50, 0x36, 0x18,
    0x84, 0x32, 0x04,
    /* U+0059 "Y" (8x12) */
    0x81, 0x82, 0xc6, 0x44, 0x48, 0x78, 0x30, 0x20, 0x20, 0x20, 0x60, 0x60,
    /* U+005A "Z" (10x12) */
    0x3f, 0xc0, 0x60, 0x10, 0x0c, 0x06, 0x03, 0x01, 0x80, 0x40, 0x30, 0x18,
    0x0c, 0x03, 0xfc,
    /* U+005B "[" (6x15) */
    0x1c, 0x41, 0x0c, 0x20, 0x82, 0x08, 0x61, 0x04, 0x10, 0x43, 0x0e, 0x00,
    /* U+005C "" (2x15) */
    0xad, 0x55, 0x55, 0x54,
    /* U+005D "]" (5x15) */
    0x18, 0x42, 0x31, 0x08, 0x42, 0x31, 0x08, 0x42, 0x13, 0x00,
    /* U+005E "^" (7x7) */
    0x18, 0x70, 0xb2, 0x2c, 0x50, 0xc0, 0x80,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (2x3) */
    0xd4,
    /* U+0061 "a" (8x9) */
    0x3b, 0x66, 0xc2, 0x82, 0x86, 0x86, 0x84, 0xcc, 0x76,
    /* U+0062 "b" (7x13) */
    0x20, 0x41, 0x83, 0x05, 0xcc, 0x50, 0xa1, 0xc3, 0x06, 0x1e, 0x2b, 0x80,
    /* U+0063 "c" (6x9) */
    0x3d, 0x1c, 0x20, 0x82, 0x08, 0x73, 0x78,
    /* U+0064 "d" (8x13) */
    0x01, 0x01, 0x01, 0x03, 0x3b, 0x66, 0xc2, 0x82, 0x86, 0x86, 0x84, 0xcc,
    0x76,
    /* U+0065 "e" (7x9) */
    0x3c, 0xcf, 0x1c, 0x2f, 0x90, 0x20, 0x66, 0x78,
    /* U+0066 "f" (7x16) */
    0x06, 0x10, 0x20, 0x43, 0xc3, 0x04, 0x08, 0x10, 0x20, 0xc1, 0x02, 0x04,
    0x08, 0x60,
    /* U+0067 "g" (9x14) */
    0x01, 0x81, 0x07, 0x84, 0x46, 0x23, 0x10, 0xf0, 0x80, 0x40, 0x20, 0x1f,
    0x90, 0x48, 0x27, 0xe0,
    /* U+0068 "h" (7x13) */
    0x20, 0x41, 0x83, 0x05, 0xcc, 0xd0, 0xa1, 0xc7, 0x0a, 0x14, 0x28, 0x60,
    /* U+0069 "i" (3x13) */
    0x24, 0x04, 0x92, 0xd2, 0x4c,
    /* U+006A "j" (5x16) */
    0x08, 0x40, 0x01, 0x08, 0x42, 0x31, 0x08, 0x42, 0x31, 0x18,
    /* U+006B "k" (7x13) */
    0x20, 0x41, 0x83, 0x04, 0x29, 0x96, 0x38, 0xf1, 0xb2, 0x24, 0x48, 0xc0,
    /* U+006C "l" (3x13) */
    0x25, 0xb4, 0x92, 0xd2, 0x4c,
    /* U+006D "m" (12x9) */
    0x5c, 0xe6, 0x72, 0x46, 0x24, 0x62, 0xc4, 0x28, 0x42, 0x84, 0x68, 0x46,
    0x8c, 0x70,
    /* U+006E "n" (7x9) */
    0x5c, 0xcd, 0x0a, 0x1c, 0x70, 0xa1, 0x42, 0x86,
    /* U+006F "o" (7x9) */
    0x3c, 0xcf, 0x0c, 0x18, 0x30, 0xe1, 0x66, 0x78,
    /* U+0070 "p" (8x12) */
    0x2e, 0x31, 0x21, 0x21, 0x61, 0x41, 0x43, 0x62, 0x5c, 0xc0, 0x80, 0x80,
    /* U+0071 "q" (7x12) */
    0x3a, 0xcd, 0x0c, 0x18, 0x70, 0xe1, 0x66, 0x74, 0x08, 0x30, 0x40,
    /* U+0072 "r" (5x9) */
    0x5b, 0x10, 0x8c, 0x42, 0x10, 0x80,
    /* U+0073 "s" (7x9) */
    0x3c, 0xc5, 0x03, 0x03, 0xc0, 0x81, 0x62, 0x78,
    /* U+0074 "t" (4x11) */
    0x22, 0xf4, 0x44, 0x4c, 0xc8, 0xe0,
    /* U+0075 "u" (7x9) */
    0x42, 0x85, 0x0e, 0x3c, 0x50, 0xa1, 0x6e, 0x76,
    /* U+0076 "v" (7x9) */
    0x83, 0x0f, 0x12, 0x64, 0x8b, 0x14, 0x38, 0x60,
    /* U+0077 "w" (11x9) */
    0x84, 0x31, 0x8f, 0x31, 0x67, 0x2d, 0x28, 0xa5, 0x18, 0xc3, 0x18, 0x43,
    0x00,
    /* U+0078 "x" (8x9) */
    0x23, 0x22, 0x34, 0x18, 0x18, 0x38, 0x2c, 0x44, 0x86,
    /* U+0079 "y" (8x12) */
    0x41, 0x43, 0x62, 0x24, 0x24, 0x28, 0x28, 0x30, 0x30, 0x20, 0x20, 0xc0,
    /* U+007A "z" (7x9) */
    0x7e, 0x0c, 0x30, 0x41, 0x06, 0x18, 0x60, 0xfc,
    /* U+007B "{" (5x15) */
    0x19, 0x08, 0x42, 0x21, 0x10, 0xc2, 0x31, 0x08, 0x43, 0x00,
    /* U+007C "|" (4x16) */
    0x32, 0x22, 0x22, 0x44, 0x44, 0x48, 0x88, 0x88,
    /* U+007D "}" (5x15) */
    0x38, 0x46, 0x21, 0x08, 0x41, 0x11, 0x08, 0x42, 0x23, 0x00,
    /* U+007E "~" (6x2) */
    0xe0, 0x70,
    /* U+00B0 "" (5x6) */
    0x76, 0x63, 0x19, 0xb8,
    /* U+00B1 "" (9x11) */
    0x06, 0x02, 0x01, 0x00, 0x83, 0xf8, 0x60, 0x20, 0x10, 0x00, 0x00, 0x3f,
    0xc0,
    /* U+00B2 "" (5x6) */
    0x72, 0xc4, 0x44, 0x78,
    /* U+00B3 "" (5x6) */
    0x70, 0x5c, 0x29, 0x70,
    /* U+00B5 "" (8x12) */
    0x21, 0x21, 0x21, 0x23, 0x63, 0x42, 0x42, 0x66, 0x7b, 0xc0, 0x80, 0x80,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (7x6) */
    0x22, 0x68, 0x61, 0xc6, 0xd8, 0xc0,
    /* U+00F7 "" (8x9) */
    0x08, 0x08, 0x00, 0x00, 0xff, 0x00, 0x00, 0x10, 0x30,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 60, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 69, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 174, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 148, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 230, .box_w = 11, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 172, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 60, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 75, .adv_w = 84, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 85, .adv_w = 84, .box_w = 5, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 95, .adv_w = 116, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 100, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 109, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 110, .adv_w = 99, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 111, .adv_w = 70, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 97, .box_w = 8, .box_h = 15, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 127, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 75, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 75, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 254, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 267, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 120, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 221, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 305, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 167, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 139, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 99, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 151, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 174, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 537, .adv_w = 160, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 168, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 221, .box_w = 13, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 153, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 144, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 81, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 677, .adv_w = 97, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 681, .adv_w = 81, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 691, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 698, .adv_w = 140, .box_w = 8, .box_h = 1, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 699, .adv_w = 152, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 700, .adv_w = 149, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 146, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 125, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 79, .box_w = 7, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 763, .adv_w = 130, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 779, .adv_w = 145, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 791, .adv_w = 68, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 65, .box_w = 5, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 806, .adv_w = 133, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 68, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 217, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 145, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 865, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 876, .adv_w = 93, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 82, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 144, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 912, .adv_w = 189, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 925, .adv_w = 126, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 934, .adv_w = 124, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 946, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 954, .adv_w = 84, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 964, .adv_w = 78, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 972, .adv_w = 84, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 982, .adv_w = 154, .box_w = 6, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 984, .adv_w = 116, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 988, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1001, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1005, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1009, .adv_w = 145, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1021, .adv_w = 81, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 1022, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1028, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1}
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
    7, 55, 7, 58, 8, 13, 8, 15, 8, 34, 8, 43, 9, 53, 9, 55,
    9, 56, 9, 58, 9, 75, 11, 13, 11, 15, 11, 34, 11, 53, 11, 56,
    11, 85, 11, 87, 11, 88, 11, 90, 13, 3, 13, 8, 13, 11, 13, 32,
    13, 34, 13, 36, 13, 40, 13, 48, 13, 50, 13, 53, 13, 55, 13, 57,
    13, 58, 13, 59, 13, 91, 15, 3, 15, 8, 15, 11, 15, 32, 15, 34,
    15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 55, 15, 57, 15, 58,
    15, 59, 15, 91, 16, 16, 16, 34, 16, 53, 27, 53, 27, 55, 27, 58,
    28, 53, 28, 55, 28, 58, 32, 13, 32, 15, 32, 34, 33, 53, 33, 55,
    33, 57, 33, 58, 34, 3, 34, 8, 34, 11, 34, 32, 34, 53, 34, 55,
    34, 58, 34, 98, 34, 99, 35, 58, 35, 64, 36, 14, 36, 33, 36, 53,
    36, 58, 36, 64, 36, 66, 36, 69, 37, 14, 39, 7, 39, 13, 39, 15,
    39, 16, 39, 33, 39, 34, 39, 43, 39, 64, 39, 66, 39, 68, 39, 69,
    39, 70, 39, 72, 39, 78, 39, 79, 39, 80, 39, 81, 39, 82, 39, 83,
    39, 84, 39, 86, 39, 87, 39, 89, 39, 90, 40, 3, 40, 8, 40, 11,
    40, 53, 40, 55, 40, 56, 40, 58, 40, 99, 43, 16, 43, 64, 44, 7,
    44, 14, 44, 33, 44, 36, 44, 40, 44, 48, 44, 50, 44, 66, 44, 68,
    44, 69, 44, 70, 44, 80, 44, 82, 44, 86, 45, 3, 45, 8, 45, 11,
    45, 14, 45, 32, 45, 36, 45, 40, 45, 48, 45, 50, 45, 53, 45, 54,
    45, 55, 45, 56, 45, 58, 45, 64, 45, 87, 45, 88, 45, 90, 45, 98,
    45, 99, 48, 13, 48, 15, 48, 16, 48, 53, 48, 55, 48, 58, 48, 64,
    49, 3, 49, 8, 49, 11, 49, 13, 49, 15, 49, 36, 49, 40, 49, 48,
    49, 50, 49, 56, 49, 64, 49, 88, 49, 98, 49, 99, 50, 13, 50, 15,
    50, 16, 50, 53, 50, 55, 50, 58, 50, 64, 51, 58, 53, 13, 53, 14,
    53, 15, 53, 16, 53, 27, 53, 28, 53, 33, 53, 34, 53, 43, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 78, 53, 79, 53, 80,
    53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87, 53, 88, 53, 89,
    53, 90, 53, 91, 53, 99, 54, 13, 54, 15, 54, 16, 54, 34, 54, 43,
    54, 64, 54, 72, 55, 7, 55, 13, 55, 14, 55, 15, 55, 16, 55, 27,
    55, 28, 55, 33, 55, 34, 55, 43, 55, 64, 55, 66, 55, 68, 55, 69,
    55, 70, 55, 72, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82, 55, 83,
    55, 84, 55, 86, 55, 87, 55, 88, 55, 89, 55, 90, 56, 13, 56, 15,
    56, 64, 57, 7, 57, 14, 57, 27, 57, 28, 57, 33, 57, 36, 57, 40,
    57, 43, 57, 48, 57, 50, 57, 66, 57, 68, 57, 69, 57, 70, 57, 72,
    57, 80, 57, 82, 57, 85, 57, 86, 57, 87, 57, 88, 57, 90, 58, 10,
    58, 13, 58, 14, 58, 15, 58, 16, 58, 32, 58, 34, 58, 66, 58, 68,
    58, 69, 58, 70, 58, 72, 58, 80, 58, 82, 58, 98, 58, 99, 59, 13,
    59, 14, 59, 15, 59, 64, 59, 98, 64, 36, 64, 40, 64, 43, 64, 48,
    64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56, 64, 58, 64, 66,
    64, 68, 64, 69, 64, 70, 64, 77, 64, 80, 64, 82, 64, 84, 64, 85,
    64, 86, 64, 87, 64, 88, 66, 13, 66, 15, 66, 16, 66, 34, 66, 53,
    66, 57, 66, 59, 66, 64, 67, 53, 67, 55, 67, 58, 68, 53, 68, 55,
    68, 58, 69, 13, 69, 15, 69, 34, 69, 36, 69, 40, 69, 48, 69, 50,
    69, 57, 69, 59, 69, 64, 70, 53, 70, 58, 70, 98, 70, 99, 71, 13,
    71, 15, 71, 53, 71, 64, 71, 98, 71, 99, 72, 10, 72, 13, 72, 15,
    72, 16, 72, 34, 72, 64, 72, 71, 72, 75, 73, 53, 73, 58, 73, 64,
    74, 13, 74, 15, 74, 34, 74, 57, 74, 59, 74, 64, 74, 98, 74, 99,
    75, 53, 75, 58, 76, 13, 76, 15, 76, 34, 76, 57, 76, 59, 76, 64,
    77, 13, 77, 15, 77, 34, 77, 57, 77, 59, 77, 64, 78, 3, 78, 8,
    78, 11, 78, 53, 78, 55, 78, 56, 78, 58, 78, 87, 78, 90, 79, 53,
    79, 58, 79, 64, 80, 3, 80, 8, 80, 11, 80, 53, 80, 55, 80, 58,
    80, 64, 80, 87, 80, 88, 80, 90, 81, 53, 81, 55, 81, 58, 82, 53,
    82, 58, 83, 13, 83, 15, 83, 64, 83, 72, 84, 3, 84, 8, 84, 11,
    84, 14, 84, 42, 84, 53, 84, 55, 84, 56, 84, 57, 84, 58, 84, 64,
    84, 72, 84, 84, 84, 85, 84, 87, 84, 88, 84, 89, 84, 90, 84, 91,
    84, 98, 85, 64, 86, 53, 86, 58, 86, 64, 87, 13, 87, 15, 87, 34,
    87, 53, 87, 58, 87, 64, 88, 13, 88, 15, 88, 53, 89, 14, 89, 53,
    90, 7, 90, 13, 90, 15, 90, 43, 90, 53, 90, 58, 90, 64, 90, 72,
    91, 34, 91, 98, 91, 99, 98, 53, 98, 55, 98, 56, 98, 66, 98, 68,
    98, 69, 98, 70, 98, 71, 98, 74, 98, 80, 98, 82, 98, 85, 98, 87,
    98, 88, 98, 90, 98, 91, 99, 53, 99, 55, 99, 56, 99, 71, 99, 74,
    99, 75, 99, 85, 99, 87, 99, 88, 99, 90, 99, 91, 100, 64,
};

static const int8_t kern_pair_values[] = {
    -23, -23, -20, -8, -18, -18, -18, -15, -6, -15, -23, -23, -20, -8, 5, 5,
    5, 5, 8, -23, -23, -20, 6, 4, 4, 5, 5, 5, -23, -23, -23, -19,
    4, -15, -15, -15, -15, -20, -15, 3, -15, 8, 4, -23, -23, -23, -19, 4,
    -15, -15, -15, -15, -20, -15, 3, -15, 8, 4, -31, -12, 8, -10, -5, -10,
    -10, -5, -10, -29, -29, -5, -13, -10, -8, -15, -20, -20, -20, -8, -14, -13,
    -18, -8, -10, -10, -13, -5, -3, -3, -4, -5, -3, -3, 4, -8, -20, -20,
    -10, -5, -9, -6, -26, -8, -8, -8, -8, -8, -5, -5, -8, -5, -8, -5,
    -5, -6, -5, -9, -5, -3, -3, -3, -9, -6, -4, -10, -3, -8, -12, -6,
    -14, -10, -6, -6, -6, -6, -10, -10, -10, -10, -10, -10, -8, -26, -26, -26,
    -10, -12, -8, -8, -8, -8, -18, -7, -16, -7, -18, 13, -13, -8, -10, -18,
    -15, -9, -9, -8, -8, -8, -13, -14, 1, 1, 1, -26, -26, 4, 4, 4,
    4, 4, -26, 1, 3, 3, -9, -9, -8, -8, -8, -13, -14, -10, -20, -13,
    -20, -18, -10, -10, -8, -14, -8, -10, -17, -17, -17, -17, -20, -12, -12, -17,
    -12, -17, -12, -17, -13, -9, -10, -13, -10, -13, 10, -8, -8, -5, -2, -4,
    -9, -3, -8, -15, -6, -15, -13, -5, -5, -6, -8, -5, -13, -8, -8, -8,
    -8, -10, -4, -4, -8, -4, -8, -4, -5, -5, -3, -3, -3, -3, -8, -8,
    -8, -4, -10, -3, -3, -8, -4, -4, -3, -4, -4, -8, -8, -8, -8, -5,
    -8, -8, -3, -4, -3, -5, -3, 5, -15, -13, -15, -15, 4, -14, -13, -13,
    -13, -13, -14, -13, -13, 5, 5, 8, -10, 8, 8, 8, -26, -26, -15, -26,
    -26, -15, -20, -27, -18, -13, -20, -23, -23, -23, -23, -6, -23, -23, -12, -12,
    -14, -18, -10, 3, 3, 3, 4, -15, 4, 4, 10, -18, -12, -18, -12, -7,
    -12, 5, 5, 5, 3, 3, 3, 3, 4, 4, 10, -18, -15, 5, 5, -13,
    -13, 9, -8, 10, 13, 10, 8, 8, 13, 6, 20, 8, 12, -14, -15, 10,
    5, 5, 5, 4, 5, 10, 5, 5, -15, -15, 5, 5, 4, 3, 5, 8,
    5, 5, 5, 4, 4, 10, -9, -9, -9, -14, -9, -5, -15, -3, -2, -14,
    -15, 10, -10, -10, -10, -18, -12, -18, -10, -6, -6, -6, -18, -12, -18, -15,
    -15, -17, -17, -15, -6, -5, -5, -5, -3, -3, -17, -13, -5, -5, -18, -5,
    -4, -2, -4, -5, -5, -5, -5, -3, -3, 10, -15, -13, 10, -12, -12, -5,
    -9, -6, -13, -8, -8, -10, -9, -13, -5, -12, -12, -7, -10, -6, -15, -5,
    5, 5, 5, 3, 5, 3, 5, 3, 5, 3, 3, 6, 3, 3, 3, 5,
    6, 5, 3, 3, 5, 3, 3, 4, 5, 3, 5, 5, 5, 3, 10,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 495,
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
const lv_font_t humid1_font_plex_sans_italic_16 = {
#else
lv_font_t humid1_font_plex_sans_italic_16 = {
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

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_16 */
