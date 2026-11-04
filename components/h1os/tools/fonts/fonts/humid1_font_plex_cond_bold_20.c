/*******************************************************************************
 * Font: humid1_font_plex_cond_bold_20 (IBM Plex Cond Bold)
 * Size: 20 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_BOLD_20
#define HUMID1_FONT_PLEX_COND_BOLD_20 1
#endif

#if HUMID1_FONT_PLEX_COND_BOLD_20

extern const lv_font_t humid1_font_plex_sans_bold_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x14) */
    0xff, 0xff, 0xff, 0x48, 0x7f, 0xc0,
    /* U+0022 "" (7x6) */
    0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xc0,
    /* U+0023 "#" (11x14) */
    0x18, 0xc3, 0x10, 0x62, 0x3f, 0xf7, 0xfe, 0x23, 0x04, 0x61, 0x8c, 0x31,
    0x1f, 0xfb, 0xff, 0x11, 0x82, 0x30, 0xc6, 0x00,
    /* U+0024 "$" (10x18) */
    0x0c, 0x03, 0x03, 0xf1, 0xff, 0xed, 0xbb, 0x0e, 0xc3, 0xf0, 0x7f, 0x07,
    0xe0, 0xfc, 0x37, 0x0d, 0xfb, 0xff, 0xf8, 0xfc, 0x0c, 0x03, 0x00,
    /* U+0025 "%" (16x14) */
    0x7c, 0x18, 0x7c, 0x30, 0xee, 0x30, 0xee, 0x60, 0xee, 0x40, 0xee, 0xc0,
    0xff, 0xbe, 0x7d, 0xbe, 0x03, 0x77, 0x02, 0x77, 0x06, 0x77, 0x0c, 0x77,
    0x0c, 0x7e, 0x18, 0x3e,
    /* U+0026 "&" (12x14) */
    0x3f, 0x07, 0xf8, 0x73, 0x87, 0x38, 0x7b, 0x03, 0xf0, 0x3c, 0x77, 0xe7,
    0xe7, 0xee, 0x3e, 0xe3, 0xcf, 0x3e, 0x7e, 0xe3, 0xc7,
    /* U+0027 "'" (3x6) */
    0xff, 0xff, 0xc0,
    /* U+0028 "(" (6x18) */
    0x1c, 0xe3, 0x1c, 0x63, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe1, 0x87, 0x1c,
    0x38, 0x70,
    /* U+0029 ")" (6x18) */
    0xe1, 0xc3, 0x0e, 0x38, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x63, 0x8e,
    0x73, 0x80,
    /* U+002A "" (9x9) */
    0x1c, 0x06, 0x22, 0x3d, 0x7f, 0xf8, 0xe0, 0xd8, 0xee, 0x63, 0x00,
    /* U+002B "+" (9x9) */
    0x1c, 0x0e, 0x07, 0x03, 0x8f, 0xff, 0xfc, 0x70, 0x38, 0x1c, 0x00,
    /* U+002C "," (3x6) */
    0xff, 0xb5, 0x80,
    /* U+002D "-" (5x3) */
    0xff, 0xfe,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (8x19) */
    0x07, 0x06, 0x06, 0x0e, 0x0c, 0x0c, 0x0c, 0x1c, 0x18, 0x18, 0x38, 0x30,
    0x30, 0x30, 0x70, 0x60, 0x60, 0xe0, 0xc0,
    /* U+0030 "0" (10x14) */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1d, 0xce, 0x7f, 0x8f, 0x80,
    /* U+0031 "1" (10x14) */
    0x3e, 0x1f, 0x87, 0xe3, 0xb8, 0x4e, 0x03, 0x80, 0xe0, 0x38, 0x0e, 0x03,
    0x80, 0xe0, 0x38, 0x7f, 0xdf, 0xf0,
    /* U+0032 "2" (9x14) */
    0x3e, 0x3f, 0xb8, 0xf8, 0x70, 0x38, 0x1c, 0x1c, 0x1e, 0x1e, 0x1e, 0x1e,
    0x1e, 0x0f, 0xff, 0xfc,
    /* U+0033 "3" (9x14) */
    0x3e, 0x3f, 0xd8, 0xe0, 0x70, 0x38, 0xf8, 0x7c, 0x0f, 0x03, 0x81, 0xd0,
    0xfc, 0xff, 0xf1, 0xf0,
    /* U+0034 "4" (11x14) */
    0x07, 0x81, 0xf0, 0x3e, 0x0d, 0xc1, 0xb8, 0x67, 0x0c, 0xe3, 0x1c, 0x63,
    0x9f, 0xff, 0xff, 0x81, 0xc0, 0x38, 0x07, 0x00,
    /* U+0035 "5" (9x14) */
    0xff, 0x7f, 0xb8, 0x1c, 0x0e, 0x07, 0x73, 0xfd, 0xc7, 0x03, 0x81, 0xd0,
    0xfc, 0x7f, 0xf3, 0xf0,
    /* U+0036 "6" (10x14) */
    0x0f, 0x07, 0x83, 0xc1, 0xe0, 0x70, 0x3b, 0xcf, 0xfb, 0xcf, 0xe1, 0xf8,
    0x7e, 0x1d, 0xcf, 0x7f, 0x8f, 0xc0,
    /* U+0037 "7" (9x14) */
    0xff, 0xff, 0xf8, 0xfc, 0x7e, 0x30, 0x38, 0x1c, 0x0c, 0x0e, 0x07, 0x03,
    0x03, 0x81, 0xc0, 0xe0,
    /* U+0038 "8" (9x14) */
    0x3e, 0x7f, 0xf8, 0xfc, 0x7e, 0x39, 0xf1, 0xfd, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x77, 0xf1, 0xf0,
    /* U+0039 "9" (10x14) */
    0x3f, 0x1f, 0xef, 0x3b, 0x87, 0xe1, 0xf8, 0x7f, 0x3d, 0xff, 0x3d, 0x80,
    0xe0, 0x78, 0x3c, 0x1e, 0x0f, 0x00,
    /* U+003A ":" (3x11) */
    0xff, 0x80, 0x00, 0xff, 0x80,
    /* U+003B ";" (3x13) */
    0xff, 0x80, 0x07, 0xfd, 0xac,
    /* U+003C "<" (7x12) */
    0x02, 0x0c, 0x79, 0xe7, 0x9c, 0x3c, 0x3c, 0x3c, 0x1c, 0x18, 0x10,
    /* U+003D "=" (9x7) */
    0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xfe,
    /* U+003E ">" (8x12) */
    0xc0, 0xe0, 0xf8, 0x3c, 0x1e, 0x07, 0x0f, 0x1e, 0x7c, 0xf0, 0xe0, 0x80,
    /* U+003F "?" (8x14) */
    0x7c, 0xfe, 0xe7, 0x47, 0x07, 0x0f, 0x3e, 0x38, 0x38, 0x00, 0x00, 0x38,
    0x38, 0x38,
    /* U+0040 "@" (15x18) */
    0x07, 0xe0, 0x3f, 0xe0, 0xe0, 0xe3, 0x80, 0xe6, 0x00, 0xd8, 0xec, 0xf1,
    0xf9, 0xe6, 0x33, 0xcc, 0x67, 0x98, 0xcf, 0x31, 0x9e, 0x63, 0x3c, 0x7f,
    0xcc, 0xe7, 0x1c, 0x00, 0x1c, 0x00, 0x1f, 0xf0, 0x0f, 0xe0,
    /* U+0041 "A" (11x14) */
    0x1e, 0x03, 0xc0, 0x7c, 0x1d, 0x83, 0xb0, 0x67, 0x0c, 0xe3, 0x9c, 0x7f,
    0x8f, 0xfb, 0x87, 0x70, 0x6c, 0x0f, 0x81, 0xc0,
    /* U+0042 "B" (10x14) */
    0xff, 0xbf, 0xee, 0x1f, 0x87, 0xe1, 0xf8, 0x7f, 0xf3, 0xfe, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xff, 0xbf, 0xc0,
    /* U+0043 "C" (10x14) */
    0x1f, 0x0f, 0xe7, 0x1f, 0x82, 0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x38,
    0x0e, 0x09, 0xc7, 0x3f, 0x87, 0xc0,
    /* U+0044 "D" (10x14) */
    0xfe, 0x3f, 0xee, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x8e, 0xff, 0x3f, 0x80,
    /* U+0045 "E" (9x14) */
    0xff, 0xff, 0xf8, 0x1c, 0x0e, 0x07, 0x03, 0xfd, 0xfe, 0xe0, 0x70, 0x38,
    0x1c, 0x0f, 0xff, 0xfc,
    /* U+0046 "F" (9x14) */
    0xff, 0xff, 0xf8, 0x1c, 0x0e, 0x07, 0x03, 0xfd, 0xfe, 0xe0, 0x70, 0x38,
    0x1c, 0x0e, 0x07, 0x00,
    /* U+0047 "G" (11x14) */
    0x1f, 0x07, 0xf9, 0xc7, 0xf0, 0x4e, 0x01, 0xc0, 0x38, 0xff, 0x1f, 0xe0,
    0xfc, 0x1f, 0x87, 0xb8, 0xf7, 0xfe, 0x3d, 0xc0,
    /* U+0048 "H" (10x14) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7f, 0xff, 0xff, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x70,
    /* U+0049 "I" (6x14) */
    0xff, 0xf3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0xff, 0xf0,
    /* U+004A "J" (8x14) */
    0x7f, 0x7f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0xc7, 0xe7,
    0xfe, 0x7c,
    /* U+004B "K" (11x14) */
    0xe1, 0xfc, 0x3b, 0x8e, 0x73, 0x8e, 0x71, 0xdc, 0x3f, 0x87, 0xf0, 0xf7,
    0x1e, 0xf3, 0x8e, 0x71, 0xee, 0x1d, 0xc1, 0xc0,
    /* U+004C "L" (8x14) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xff, 0xff,
    /* U+004D "M" (12x14) */
    0xf0, 0xff, 0x0f, 0xf0, 0xff, 0x9f, 0xf9, 0xfe, 0x97, 0xef, 0x7e, 0xf7,
    0xe6, 0x7e, 0x67, 0xe4, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    /* U+004E "N" (11x14) */
    0xf0, 0xfe, 0x1f, 0xe3, 0xfc, 0x7f, 0xcf, 0xd9, 0xfb, 0x3f, 0x37, 0xe6,
    0xfc, 0xff, 0x8f, 0xf1, 0xfe, 0x1f, 0xc3, 0xc0,
    /* U+004F "O" (11x14) */
    0x1f, 0x07, 0xf1, 0xc7, 0x70, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x1f, 0x83, 0xb8, 0xe3, 0xf8, 0x3e, 0x00,
    /* U+0050 "P" (10x14) */
    0xff, 0x3f, 0xee, 0x1f, 0x87, 0xe1, 0xf8, 0x7f, 0xfb, 0xfc, 0xe0, 0x38,
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0x00,
    /* U+0051 "Q" (11x18) */
    0x1f, 0x07, 0xf1, 0xc7, 0x30, 0x6e, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x1f, 0x83, 0xb8, 0xe7, 0xfc, 0x7f, 0x07, 0xc0, 0x70, 0x0f, 0x80,
    0xf0,
    /* U+0052 "R" (10x14) */
    0xff, 0x3f, 0xee, 0x1f, 0x87, 0xe1, 0xf8, 0x7f, 0xfb, 0xfc, 0xe7, 0x39,
    0xce, 0x3b, 0x8e, 0xe3, 0xf8, 0x70,
    /* U+0053 "S" (9x14) */
    0x3e, 0x3f, 0xf8, 0xdc, 0x0e, 0x07, 0xe1, 0xfc, 0xff, 0x0f, 0x81, 0xd0,
    0xfc, 0x7f, 0xf3, 0xf0,
    /* U+0054 "T" (10x14) */
    0xff, 0xff, 0xf1, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xc0, 0x70, 0x1c, 0x07,
    0x01, 0xc0, 0x70, 0x1c, 0x07, 0x00,
    /* U+0055 "U" (10x14) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0xcf, 0x7f, 0x8f, 0xc0,
    /* U+0056 "V" (12x14) */
    0xe0, 0x77, 0x0e, 0x70, 0xe7, 0x0e, 0x30, 0xc3, 0x9c, 0x39, 0xc3, 0x9c,
    0x19, 0x81, 0xd8, 0x1f, 0x80, 0xf0, 0x0f, 0x00, 0xf0,
    /* U+0057 "W" (16x14) */
    0xc3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc7, 0xe3, 0xc6, 0xe6, 0xc6, 0x66, 0xee,
    0x66, 0xee, 0x76, 0x6e, 0x76, 0x6c, 0x76, 0x6c, 0x3c, 0x6c, 0x3c, 0x7c,
    0x3c, 0x3c, 0x3c, 0x38,
    /* U+0058 "X" (11x14) */
    0xe1, 0xde, 0x39, 0xce, 0x3d, 0xc3, 0xf0, 0x3e, 0x07, 0x80, 0xf0, 0x3f,
    0x07, 0xe1, 0xce, 0x39, 0xee, 0x1d, 0xc3, 0xc0,
    /* U+0059 "Y" (11x14) */
    0xe0, 0xfe, 0x1d, 0xc7, 0x38, 0xe3, 0xb8, 0x77, 0x07, 0xc0, 0xf8, 0x0e,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x00,
    /* U+005A "Z" (9x14) */
    0xff, 0xff, 0xc1, 0xe0, 0xe0, 0xe0, 0x70, 0x70, 0x38, 0x38, 0x38, 0x1c,
    0x1c, 0x0f, 0xff, 0xfc,
    /* U+005B "[" (4x18) */
    0xff, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xff,
    /* U+005C "" (7x19) */
    0xc1, 0x83, 0x83, 0x06, 0x0e, 0x0c, 0x18, 0x30, 0x70, 0x60, 0xc1, 0xc1,
    0x83, 0x06, 0x0e, 0x0c, 0x18,
    /* U+005D "]" (5x18) */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0xff, 0xc0,
    /* U+005E "^" (9x8) */
    0x1c, 0x1e, 0x0f, 0x8e, 0xc6, 0x77, 0x1b, 0x8f, 0x83,
    /* U+005F "_" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+0060 "`" (3x5) */
    0x5b, 0xb2,
    /* U+0061 "a" (9x11) */
    0x3e, 0x3f, 0x98, 0xe0, 0x73, 0xfb, 0xff, 0x8f, 0xc7, 0xe3, 0xff, 0xde,
    0xe0,
    /* U+0062 "b" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xe7, 0xfb, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7e, 0x3f, 0xfb, 0xb8,
    /* U+0063 "c" (8x11) */
    0x3e, 0x7f, 0xe3, 0xe0, 0xe0, 0xe0, 0xe0, 0xe2, 0xe3, 0x7f, 0x3e,
    /* U+0064 "d" (9x15) */
    0x03, 0x81, 0xc0, 0xe0, 0x73, 0xbb, 0xff, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7e, 0x3b, 0xfc, 0xee,
    /* U+0065 "e" (9x11) */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7f, 0xff, 0xff, 0x81, 0xc0, 0x73, 0x3f, 0xcf,
    0x80,
    /* U+0066 "f" (6x15) */
    0x3d, 0xf7, 0x1c, 0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x00,
    /* U+0067 "g" (10x17) */
    0x03, 0x80, 0xe3, 0xe1, 0xfc, 0xe3, 0xb8, 0xee, 0x39, 0xfc, 0x3e, 0x30,
    0x0c, 0x03, 0xfe, 0x3f, 0xf0, 0x7c, 0x1f, 0xff, 0x7f, 0x00,
    /* U+0068 "h" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xf7, 0xff, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7e, 0x3f, 0x1f, 0x8e,
    /* U+0069 "i" (3x15) */
    0xff, 0x8f, 0xff, 0xff, 0xff, 0xf8,
    /* U+006A "j" (5x19) */
    0x39, 0xce, 0x03, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x3f, 0xfc,
    /* U+006B "k" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x3f, 0x3b, 0x9d, 0xdc, 0xfc, 0x7f, 0x3f,
    0x9c, 0xee, 0x77, 0x1f, 0x8e,
    /* U+006C "l" (4x15) */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xef, 0x70,
    /* U+006D "m" (13x11) */
    0xee, 0x77, 0xff, 0xf9, 0xcf, 0xce, 0x7e, 0x73, 0xf3, 0x9f, 0x9c, 0xfc,
    0xe7, 0xe7, 0x3f, 0x39, 0xf9, 0xce,
    /* U+006E "n" (9x11) */
    0xef, 0x7f, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xe0,
    /* U+006F "o" (9x11) */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0x3f, 0x8f,
    0x80,
    /* U+0070 "p" (9x15) */
    0xee, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xff, 0xbb,
    0x9c, 0x0e, 0x07, 0x03, 0x80,
    /* U+0071 "q" (9x15) */
    0x3b, 0xbf, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xbf, 0xce,
    0xe0, 0x70, 0x38, 0x1c, 0x0e,
    /* U+0072 "r" (6x11) */
    0xef, 0xff, 0xf8, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x00,
    /* U+0073 "s" (8x11) */
    0x3e, 0xff, 0xe6, 0xe0, 0xfc, 0x7e, 0x3f, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0074 "t" (6x14) */
    0x71, 0xc7, 0x3f, 0xfd, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x7c, 0xf0,
    /* U+0075 "u" (9x11) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xff, 0xde,
    0xe0,
    /* U+0076 "v" (10x11) */
    0xe1, 0xf8, 0x66, 0x39, 0xce, 0x73, 0x8c, 0xc3, 0x30, 0xfc, 0x3e, 0x07,
    0x81, 0xe0,
    /* U+0077 "w" (15x11) */
    0xe3, 0x8e, 0xc7, 0x1d, 0x8b, 0x33, 0xb6, 0x67, 0x6d, 0xc6, 0xdb, 0x8d,
    0xb6, 0x1b, 0x2c, 0x34, 0x78, 0x78, 0xf0, 0x71, 0xc0,
    /* U+0078 "x" (9x11) */
    0xc3, 0x73, 0x99, 0x8f, 0xc3, 0xc1, 0xe0, 0xf0, 0xfc, 0x7e, 0x73, 0xb0,
    0xe0,
    /* U+0079 "y" (10x15) */
    0xe1, 0xd8, 0x67, 0x39, 0xce, 0x73, 0x8c, 0xc3, 0xf0, 0xfc, 0x1e, 0x07,
    0x81, 0xe0, 0x30, 0x1c, 0x1f, 0x07, 0x80,
    /* U+007A "z" (8x11) */
    0xff, 0xff, 0x0f, 0x0e, 0x1c, 0x3c, 0x38, 0x70, 0xf0, 0xff, 0xff,
    /* U+007B "{" (6x18) */
    0x3c, 0xf3, 0x8e, 0x38, 0xe3, 0x8e, 0xf3, 0xc3, 0x8e, 0x38, 0xe3, 0x8e,
    0x3c, 0xf0,
    /* U+007C "|" (3x18) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (6x18) */
    0xf3, 0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x1c, 0x73, 0x8e, 0x38, 0xe3, 0x8e,
    0xfb, 0xc0,
    /* U+007E "~" (9x4) */
    0x70, 0x7c, 0x07, 0xe0, 0xe0,
    /* U+00B0 "" (7x7) */
    0x38, 0xfb, 0x1e, 0x3c, 0x6f, 0x8e, 0x00,
    /* U+00B1 "" (9x12) */
    0x1c, 0x0e, 0x07, 0x1f, 0xff, 0xf8, 0xe0, 0x70, 0x38, 0x00, 0x00, 0x3f,
    0xff, 0xf0,
    /* U+00B2 "" (5x7) */
    0x74, 0xc6, 0x77, 0x73, 0xe0,
    /* U+00B3 "" (5x7) */
    0xf4, 0xc6, 0xe1, 0xcf, 0xc0,
    /* U+00B5 "" (9x15) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xff, 0xf6,
    0xfc, 0x0e, 0x07, 0x03, 0x80,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (9x8) */
    0x63, 0x3b, 0x8f, 0x83, 0x83, 0xe3, 0xbb, 0x8e, 0x82,
    /* U+00F7 "" (9x11) */
    0x1c, 0x0e, 0x07, 0x00, 0x00, 0x07, 0xff, 0xfe, 0x00, 0x1c, 0x0e, 0x07,
    0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 68, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 93, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 145, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 12, .adv_w = 180, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 171, .box_w = 10, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 283, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 209, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 78, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 107, .adv_w = 97, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 121, .adv_w = 97, .box_w = 6, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 135, .adv_w = 178, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 146, .adv_w = 173, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 157, .adv_w = 91, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 160, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 162, .adv_w = 91, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 135, .box_w = 8, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 183, .adv_w = 173, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 173, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 173, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 173, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 173, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 97, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 97, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 365, .adv_w = 173, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 173, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 384, .adv_w = 173, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 145, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 260, .box_w = 15, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 444, .adv_w = 198, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 193, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 188, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 202, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 176, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 169, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 207, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 209, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 162, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 202, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 647, .adv_w = 236, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 209, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 205, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 190, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 205, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 751, .adv_w = 195, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 178, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 169, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 202, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 191, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 842, .adv_w = 283, .box_w = 16, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 870, .adv_w = 196, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 185, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 175, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 97, .box_w = 4, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 935, .adv_w = 135, .box_w = 7, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 952, .adv_w = 97, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 964, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 973, .adv_w = 160, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 976, .adv_w = 173, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 978, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 176, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1008, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 176, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1036, .adv_w = 163, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 109, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1061, .adv_w = 160, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1083, .adv_w = 173, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1100, .adv_w = 84, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 85, .box_w = 5, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1118, .adv_w = 168, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 89, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1143, .adv_w = 259, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1161, .adv_w = 173, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 163, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1187, .adv_w = 176, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1204, .adv_w = 176, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1221, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1230, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1241, .adv_w = 109, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1252, .adv_w = 173, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1265, .adv_w = 157, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1279, .adv_w = 242, .box_w = 15, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1300, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1313, .adv_w = 159, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1332, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1343, .adv_w = 108, .box_w = 6, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1357, .adv_w = 118, .box_w = 3, .box_h = 18, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 1364, .adv_w = 108, .box_w = 6, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1378, .adv_w = 173, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1383, .adv_w = 135, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1390, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1404, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1409, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1414, .adv_w = 174, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1431, .adv_w = 104, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 1433, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1442, .adv_w = 173, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 1}
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
    3, 13, 3, 15, 3, 34, 3, 43, 3, 87, 6, 3, 6, 8, 6, 11,
    7, 53, 7, 55, 7, 58, 8, 13, 8, 15, 8, 34, 8, 43, 9, 72,
    9, 75, 11, 13, 11, 15, 11, 34, 11, 43, 11, 87, 11, 88, 11, 90,
    13, 3, 13, 8, 13, 11, 13, 32, 13, 36, 13, 40, 13, 48, 13, 50,
    13, 53, 13, 54, 13, 55, 13, 56, 13, 58, 13, 68, 13, 69, 13, 70,
    13, 71, 13, 80, 13, 82, 13, 85, 13, 87, 13, 88, 13, 90, 13, 98,
    13, 99, 14, 36, 14, 40, 14, 48, 14, 50, 14, 53, 14, 57, 14, 58,
    15, 3, 15, 8, 15, 11, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50,
    15, 53, 15, 54, 15, 55, 15, 56, 15, 58, 15, 68, 15, 69, 15, 70,
    15, 71, 15, 80, 15, 82, 15, 85, 15, 87, 15, 88, 15, 90, 15, 98,
    15, 99, 16, 16, 16, 34, 16, 53, 16, 55, 16, 56, 16, 58, 16, 66,
    27, 53, 27, 55, 27, 58, 28, 53, 28, 55, 28, 58, 32, 13, 32, 15,
    32, 34, 33, 57, 33, 58, 34, 3, 34, 8, 34, 11, 34, 13, 34, 15,
    34, 32, 34, 34, 34, 53, 34, 55, 34, 57, 34, 58, 34, 64, 34, 91,
    34, 98, 34, 99, 35, 64, 36, 16, 36, 57, 36, 64, 37, 3, 37, 8,
    37, 11, 37, 13, 37, 15, 37, 16, 37, 34, 37, 43, 37, 53, 37, 55,
    37, 56, 37, 57, 37, 58, 37, 59, 39, 7, 39, 13, 39, 15, 39, 16,
    39, 33, 39, 34, 39, 36, 39, 40, 39, 43, 39, 48, 39, 50, 39, 64,
    39, 66, 39, 68, 39, 69, 39, 70, 39, 71, 39, 72, 39, 75, 39, 78,
    39, 79, 39, 80, 39, 81, 39, 82, 39, 83, 39, 84, 39, 85, 39, 86,
    39, 87, 39, 88, 39, 89, 39, 90, 39, 91, 40, 53, 40, 55, 40, 58,
    42, 14, 43, 16, 43, 64, 44, 3, 44, 7, 44, 8, 44, 11, 44, 14,
    44, 33, 44, 36, 44, 40, 44, 43, 44, 48, 44, 50, 44, 52, 44, 53,
    44, 55, 44, 56, 44, 58, 44, 66, 44, 68, 44, 69, 44, 70, 44, 71,
    44, 77, 44, 78, 44, 79, 44, 80, 44, 81, 44, 82, 44, 83, 44, 85,
    44, 86, 44, 87, 44, 88, 44, 90, 44, 98, 44, 99, 45, 3, 45, 8,
    45, 11, 45, 14, 45, 32, 45, 33, 45, 36, 45, 40, 45, 48, 45, 50,
    45, 53, 45, 54, 45, 55, 45, 56, 45, 58, 45, 68, 45, 69, 45, 70,
    45, 80, 45, 82, 45, 85, 45, 87, 45, 88, 45, 90, 45, 98, 45, 99,
    48, 13, 48, 15, 48, 16, 48, 34, 48, 53, 48, 55, 48, 56, 48, 57,
    48, 58, 48, 64, 49, 7, 49, 13, 49, 15, 49, 16, 49, 34, 49, 43,
    49, 57, 49, 58, 49, 59, 49, 64, 49, 72, 50, 13, 50, 15, 50, 16,
    50, 34, 50, 53, 50, 55, 50, 56, 50, 57, 50, 58, 50, 64, 52, 16,
    52, 64, 53, 7, 53, 13, 53, 14, 53, 15, 53, 16, 53, 27, 53, 28,
    53, 33, 53, 34, 53, 36, 53, 40, 53, 43, 53, 48, 53, 50, 53, 52,
    53, 64, 53, 66, 53, 68, 53, 69, 53, 70, 53, 71, 53, 72, 53, 78,
    53, 79, 53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87,
    53, 88, 53, 89, 53, 90, 53, 91, 54, 7, 54, 13, 54, 15, 54, 16,
    54, 34, 54, 64, 55, 7, 55, 13, 55, 14, 55, 15, 55, 16, 55, 27,
    55, 28, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 48, 55, 50,
    55, 52, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72, 55, 80,
    55, 82, 55, 84, 55, 86, 56, 7, 56, 13, 56, 14, 56, 15, 56, 16,
    56, 33, 56, 34, 56, 36, 56, 40, 56, 43, 56, 48, 56, 50, 56, 64,
    56, 66, 56, 68, 56, 69, 56, 70, 56, 72, 56, 80, 56, 82, 56, 84,
    56, 91, 57, 14, 57, 64, 58, 7, 58, 13, 58, 14, 58, 15, 58, 16,
    58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40, 58, 43, 58, 48,
    58, 50, 58, 52, 58, 64, 58, 66, 58, 67, 58, 68, 58, 69, 58, 70,
    58, 71, 58, 72, 58, 73, 58, 74, 58, 75, 58, 76, 58, 78, 58, 79,
    58, 80, 58, 81, 58, 82, 58, 83, 58, 84, 58, 85, 58, 86, 58, 87,
    58, 88, 58, 89, 58, 90, 58, 91, 59, 14, 64, 36, 64, 40, 64, 43,
    64, 48, 64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56, 64, 58,
    64, 59, 64, 66, 64, 68, 64, 69, 64, 70, 64, 72, 64, 75, 64, 77,
    64, 80, 64, 82, 64, 84, 64, 85, 64, 86, 64, 87, 64, 88, 66, 13,
    66, 15, 66, 16, 66, 34, 66, 53, 66, 58, 66, 64, 67, 53, 67, 55,
    67, 58, 67, 64, 68, 34, 68, 43, 68, 53, 68, 58, 68, 59, 68, 99,
    70, 53, 70, 58, 70, 64, 71, 13, 71, 15, 71, 16, 71, 43, 71, 55,
    71, 64, 71, 99, 72, 10, 72, 16, 72, 34, 72, 64, 72, 75, 73, 53,
    73, 55, 73, 56, 73, 58, 74, 98, 74, 99, 76, 7, 76, 14, 76, 33,
    76, 36, 76, 40, 76, 48, 76, 50, 76, 52, 76, 53, 76, 55, 76, 56,
    76, 58, 76, 68, 76, 69, 76, 70, 76, 80, 76, 82, 76, 84, 76, 85,
    76, 86, 76, 87, 76, 88, 76, 90, 76, 98, 76, 99, 77, 14, 77, 53,
    77, 55, 77, 58, 77, 77, 77, 85, 77, 90, 77, 98, 77, 99, 78, 53,
    78, 58, 79, 53, 79, 55, 79, 56, 79, 58, 80, 53, 80, 58, 80, 64,
    81, 53, 81, 55, 81, 58, 81, 64, 82, 58, 83, 3, 83, 8, 83, 11,
    83, 13, 83, 15, 83, 36, 83, 40, 83, 48, 83, 50, 83, 64, 83, 71,
    83, 85, 83, 87, 83, 90, 83, 98, 83, 99, 84, 53, 84, 55, 84, 58,
    84, 64, 85, 53, 85, 58, 86, 53, 86, 55, 86, 58, 87, 7, 87, 13,
    87, 15, 87, 34, 87, 43, 87, 64, 88, 3, 88, 8, 88, 11, 88, 13,
    88, 15, 88, 53, 88, 58, 88, 64, 89, 7, 89, 14, 89, 53, 89, 58,
    90, 7, 90, 13, 90, 15, 90, 34, 90, 64, 91, 13, 91, 15, 91, 34,
    91, 57, 98, 13, 98, 15, 98, 42, 98, 43, 98, 53, 98, 55, 98, 56,
    98, 58, 98, 71, 98, 72, 98, 74, 98, 84, 98, 85, 98, 87, 98, 88,
    98, 90, 99, 13, 99, 15, 99, 34, 99, 43, 99, 53, 99, 55, 99, 71,
    99, 74, 99, 85, 99, 87, 99, 88, 99, 90, 99, 91,
};

static const int8_t kern_pair_values[] = {
    -29, -29, -16, -13, 8, -19, -19, -19, -13, -11, -19, -29, -29, -16, -13, 7,
    22, -29, -29, -16, -13, 8, 6, 6, -29, -29, -29, -26, -13, -13, -13, -13,
    -29, -11, -19, -13, -29, -5, -5, -5, -5, -5, -5, -9, -22, -16, -14, -16,
    -19, 5, 5, 5, 5, -14, -13, -19, -29, -29, -29, -26, -13, -13, -13, -13,
    -29, -11, -19, -13, -29, -5, -5, -5, -5, -5, -5, -9, -22, -16, -14, -16,
    -19, -61, -27, 6, 3, 2, 3, -16, -13, -10, -16, -13, -10, -16, -38, -38,
    -10, -13, -13, -16, -16, -16, 6, 6, -16, 3, -18, -18, 2, -22, 5, 3,
    -19, -16, -20, -6, -6, -17, -3, -3, -3, -13, -13, -14, -12, -3, -8, -10,
    -7, -9, -12, -3, -13, -32, -32, -27, -10, -24, -10, -10, -18, -10, -10, -45,
    -13, -10, -11, -10, -2, -14, -3, -10, -10, -10, -10, -11, -10, -10, -5, -8,
    -6, -5, -13, -6, -8, -8, -8, -13, -10, -11, -27, -3, -10, -3, -3, -18,
    -10, -12, -12, -6, -12, -12, -3, -8, -8, -3, -6, -3, -8, -8, -8, -6,
    -3, -3, -3, -8, -3, -8, -3, -10, -6, -6, -6, -6, -6, -6, -26, -26,
    -26, -11, -19, -3, -13, -13, -13, -13, -24, -5, -18, -13, -28, -3, -3, -3,
    -3, -3, -8, -13, -10, -11, -26, -22, -13, -13, -14, -6, -8, -8, -7, -10,
    -13, -32, -10, -35, -35, -29, -22, -17, -11, -8, -8, -48, -10, -13, -13, -14,
    -6, -8, -8, -7, -10, -13, -32, -11, -19, -10, -29, -14, -29, -32, -13, -13,
    -10, -18, -8, -8, -14, -8, -8, -4, -26, -19, -18, -18, -18, -5, -22, -14,
    -14, -18, -14, -18, -14, -19, -14, -8, -11, -8, -6, -16, -3, -11, -11, -13,
    -6, -22, -11, -19, -11, -19, -21, -10, -10, -10, -18, -8, -8, -13, -8, -8,
    -8, -32, -11, -11, -11, -11, -13, -11, -11, -8, -8, -11, -13, -6, -13, -16,
    -6, -9, -7, -7, -10, -7, -7, -22, -10, -8, -8, -8, -8, -8, -8, -5,
    -6, -13, 6, -18, -29, -19, -29, -32, -16, -16, -13, -22, -13, -13, -13, -13,
    -13, -14, -35, -18, -3, -17, -16, -17, -8, -18, -3, -3, -4, -3, -14, -14,
    -17, -16, -16, -14, -16, -8, -13, -8, -6, -13, -11, -16, -13, -32, -32, -16,
    -32, -32, -19, -26, -22, -32, -22, -35, 8, -10, -19, -13, -19, 11, 18, -18,
    -19, -13, -13, -21, -11, -22, -16, 3, 3, 6, 3, -22, -18, 3, -21, -11,
    -19, -16, 3, 2, -15, -17, 2, 2, -18, -19, -19, -17, -17, -10, -7, 11,
    -20, 13, 9, 11, 8, 18, 10, -18, -11, -8, -18, 6, 6, -3, -14, -3,
    -4, -4, -4, -4, -2, -7, -6, -2, -15, -2, -1, -2, -2, -1, -3, -3,
    -3, -4, -2, -2, -3, -3, -3, -4, -2, -5, -3, -2, -2, -6, -6, -18,
    -18, -18, -11, -8, -18, -18, -19, -19, -21, -11, -19, -16, -10, 10, 10, 10,
    -26, -26, 3, 3, 3, 3, -26, 3, 3, 3, 3, 13, 10, -18, -11, -15,
    -16, -8, -6, -14, -8, -16, -6, -22, -22, -10, -6, -22, 6, 6, 6, -16,
    -16, -11, -13, -16, -10, -11, -11, -10, -10, -21, -21, -11, -26, 3, 3, 3,
    3, -16, -16, 2, -18, 6, 3, 3, 2, 6, 2, 6, 3, 6, 6, 5,
    3, -19, -19, -16, -19, 6, 3, 6, 3, 8, 6, 3, 5, 2,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 590,
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
const lv_font_t humid1_font_plex_cond_bold_20 = {
#else
lv_font_t humid1_font_plex_cond_bold_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 27,
    .base_line = 6,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_20,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_BOLD_20 */
