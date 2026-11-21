/*******************************************************************************
 * Font: humid1_font_terminus_bold_20 (terminus bold)
 * Size: 20 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: exact-mono (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_20 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_TERMINUS_BOLD_20
#define HUMID1_FONT_TERMINUS_BOLD_20 1
#endif

#if HUMID1_FONT_TERMINUS_BOLD_20

extern const lv_font_t humid1_icon_fa7_solid_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x13) */
    0xff, 0xff, 0xc3, 0xc0,
    /* U+0022 "" (6x4) */
    0xcf, 0x3c, 0xf3,
    /* U+0023 "#" (8x13) */
    0x66, 0x66, 0x66, 0x66, 0xff, 0x66, 0x66, 0x66, 0xff, 0x66, 0x66, 0x66,
    0x66,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x7e, 0xdb, 0xd8, 0xd8, 0xd8, 0x7e, 0x1b, 0x1b, 0x1b, 0xdb,
    0x7e, 0x18, 0x18,
    /* U+0025 "%" (7x12) */
    0xe7, 0x4f, 0xb0, 0x61, 0x83, 0x0c, 0x18, 0x60, 0xdf, 0x2e, 0x70,
    /* U+0026 "&" (9x13) */
    0x3c, 0x33, 0x19, 0x8c, 0xc3, 0xc0, 0xc0, 0xe6, 0xdb, 0xc7, 0x61, 0xb0,
    0xcc, 0xf3, 0xd8,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (4x13) */
    0x36, 0x6c, 0xcc, 0xcc, 0xcc, 0x66, 0x30,
    /* U+0029 ")" (4x13) */
    0xc6, 0x63, 0x33, 0x33, 0x33, 0x66, 0xc0,
    /* U+002A "" (9x7) */
    0x63, 0x1b, 0x07, 0x1f, 0xf1, 0xc1, 0xb1, 0x8c,
    /* U+002B "+" (8x7) */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x4) */
    0x6d, 0xe0,
    /* U+002D "-" (8x1) */
    0xff,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (7x12) */
    0x06, 0x0c, 0x30, 0x61, 0x83, 0x0c, 0x18, 0x60, 0xc3, 0x06, 0x00,
    /* U+0030 "0" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc7, 0xcf, 0xdb, 0xf3, 0xe3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0031 "1" (6x13) */
    0x31, 0xcf, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0xfc,
    /* U+0032 "2" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0,
    0xff,
    /* U+0033 "3" (8x13) */
    0x7e, 0xc3, 0xc3, 0x03, 0x03, 0x03, 0x3e, 0x03, 0x03, 0x03, 0xc3, 0xc3,
    0x7e,
    /* U+0034 "4" (8x13) */
    0x03, 0x07, 0x0f, 0x1b, 0x33, 0x63, 0xc3, 0xc3, 0xc3, 0xff, 0x03, 0x03,
    0x03,
    /* U+0035 "5" (8x13) */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0x03, 0x03, 0x03, 0x03, 0xc3, 0xc3,
    0x7e,
    /* U+0036 "6" (8x13) */
    0x3e, 0x60, 0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0037 "7" (8x13) */
    0xff, 0xc3, 0xc3, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x18, 0x18,
    0x18,
    /* U+0038 "8" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0039 "9" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x06,
    0x7c,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (3x10) */
    0x6c, 0x00, 0x1b, 0x78,
    /* U+003C "<" (8x13) */
    0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06,
    0x03,
    /* U+003D "=" (8x5) */
    0xff, 0x00, 0x00, 0x00, 0xff,
    /* U+003E ">" (8x13) */
    0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60,
    0xc0,
    /* U+003F "?" (8x13) */
    0x3c, 0x66, 0xc3, 0xc3, 0x03, 0x06, 0x0c, 0x18, 0x18, 0x00, 0x00, 0x18,
    0x18,
    /* U+0040 "@" (9x13) */
    0x7f, 0x60, 0xf0, 0x79, 0xfd, 0x9e, 0xcf, 0x67, 0xb3, 0xd9, 0xe7, 0xf0,
    0x18, 0x07, 0xf8,
    /* U+0041 "A" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3,
    /* U+0042 "B" (8x13) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xfe,
    /* U+0043 "C" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc3,
    0x7e,
    /* U+0044 "D" (8x13) */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6,
    0xfc,
    /* U+0045 "E" (8x13) */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xff,
    /* U+0046 "F" (8x13) */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+0047 "G" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0048 "H" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3,
    /* U+0049 "I" (4x13) */
    0xf6, 0x66, 0x66, 0x66, 0x66, 0x66, 0xf0,
    /* U+004A "J" (8x13) */
    0x0f, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0xc6, 0xc6, 0xc6,
    0x7c,
    /* U+004B "K" (8x13) */
    0xc3, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3,
    0xc3,
    /* U+004C "L" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xff,
    /* U+004D "M" (9x13) */
    0x80, 0xe0, 0xf8, 0xfe, 0xfd, 0xde, 0x4f, 0x07, 0x83, 0xc1, 0xe0, 0xf0,
    0x78, 0x3c, 0x18,
    /* U+004E "N" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0xc3, 0xc3,
    0xc3,
    /* U+004F "O" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0050 "P" (8x13) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0,
    /* U+0051 "Q" (8x15) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xcf,
    0x7e, 0x06, 0x03,
    /* U+0052 "R" (8x13) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3,
    0xc3,
    /* U+0053 "S" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0x7e, 0x03, 0x03, 0x03, 0xc3, 0xc3,
    0x7e,
    /* U+0054 "T" (8x13) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18,
    /* U+0055 "U" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7e,
    /* U+0056 "V" (8x13) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x3c, 0x18,
    0x18,
    /* U+0057 "W" (9x13) */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x93, 0xdd, 0xfb, 0xf8,
    0xf8, 0x38, 0x08,
    /* U+0058 "X" (8x13) */
    0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0xc3,
    0xc3,
    /* U+0059 "Y" (8x13) */
    0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18,
    /* U+005A "Z" (8x13) */
    0xff, 0x03, 0x03, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xc0, 0xc0,
    0xff,
    /* U+005B "[" (4x13) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,
    /* U+005C "" (7x12) */
    0xc1, 0x81, 0x83, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30,
    /* U+005D "]" (4x13) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,
    /* U+005E "^" (8x4) */
    0x18, 0x3c, 0x66, 0xc3,
    /* U+005F "_" (8x1) */
    0xff,
    /* U+0060 "`" (4x3) */
    0xc6, 0x30,
    /* U+0061 "a" (8x9) */
    0x7e, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f,
    /* U+0062 "b" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xfe,
    /* U+0063 "c" (8x9) */
    0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e,
    /* U+0064 "d" (8x13) */
    0x03, 0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x7f,
    /* U+0065 "e" (8x9) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0xc3, 0x7e,
    /* U+0066 "f" (7x13) */
    0x1e, 0x60, 0xc1, 0x8f, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x00,
    /* U+0067 "g" (8x12) */
    0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x7e,
    /* U+0068 "h" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3,
    /* U+0069 "i" (4x13) */
    0x66, 0x00, 0xe6, 0x66, 0x66, 0x66, 0xf0,
    /* U+006A "j" (6x16) */
    0x0c, 0x30, 0x00, 0x1c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0f, 0x3c, 0xde,
    /* U+006B "k" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xd8, 0xcc, 0xc6,
    0xc3,
    /* U+006C "l" (4x13) */
    0xe6, 0x66, 0x66, 0x66, 0x66, 0x66, 0xf0,
    /* U+006D "m" (8x9) */
    0xfe, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (8x9) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+006F "o" (8x9) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e,
    /* U+0070 "p" (8x12) */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (8x12) */
    0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03,
    /* U+0072 "r" (8x9) */
    0xdf, 0xf0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0073 "s" (8x9) */
    0x7e, 0xc3, 0xc0, 0xc0, 0x7e, 0x03, 0x03, 0xc3, 0x7e,
    /* U+0074 "t" (7x13) */
    0x30, 0x60, 0xc1, 0x8f, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x81, 0xe0,
    /* U+0075 "u" (8x9) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f,
    /* U+0076 "v" (8x9) */
    0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x18,
    /* U+0077 "w" (8x9) */
    0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e,
    /* U+0078 "x" (8x9) */
    0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0xc3,
    /* U+0079 "y" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x7e,
    /* U+007A "z" (8x9) */
    0xff, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xff,
    /* U+007B "{" (6x13) */
    0x1c, 0xc3, 0x0c, 0x30, 0xce, 0x0c, 0x30, 0xc3, 0x0c, 0x1c,
    /* U+007C "|" (2x13) */
    0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (6x13) */
    0xe0, 0xc3, 0x0c, 0x30, 0xc1, 0xcc, 0x30, 0xc3, 0x0c, 0xe0,
    /* U+007E "~" (8x4) */
    0x73, 0xdb, 0xdb, 0xce,
    /* U+00B0 "" (6x5) */
    0x7b, 0x3c, 0xf3, 0x78,
    /* U+00B1 "" (8x10) */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00, 0xff,
    /* U+00B2 "" (6x7) */
    0x7b, 0x3c, 0xc6, 0x31, 0x8f, 0xc0,
    /* U+00B3 "" (6x7) */
    0x7b, 0x30, 0xce, 0x0f, 0x37, 0x80,
    /* U+00B5 "" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xfb, 0xc0, 0xc0, 0xc0,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (8x7) */
    0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3,
    /* U+00F7 "" (8x9) */
    0x18, 0x18, 0x00, 0x00, 0xff, 0x00, 0x00, 0x18, 0x18,
    /* U+0394 "" (8x13) */
    0x18, 0x18, 0x18, 0x3c, 0x3c, 0x3c, 0x66, 0x66, 0x66, 0xc3, 0xc3, 0xc3,
    0xff,
    /* U+03A9 "" (8x13) */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x66,
    0xe7,
    /* U+03B1 "" (9x9) */
    0x7d, 0xe3, 0xb1, 0x98, 0xcc, 0x66, 0x33, 0x19, 0x8e, 0x7d, 0x80,
    /* U+03B2 "" (8x16) */
    0x7c, 0xc6, 0xc6, 0xc6, 0xc4, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xfe, 0xc0, 0xc0, 0xc0,
    /* U+03B3 "" (8x12) */
    0xc3, 0xc3, 0xc3, 0x66, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18,
    /* U+03B4 "" (8x13) */
    0x7e, 0x30, 0x18, 0x0c, 0x3e, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,
    /* U+03B5 "" (8x9) */
    0x7e, 0xc3, 0xc0, 0xc0, 0x7c, 0xc0, 0xc0, 0xc3, 0x7e,
    /* U+03B8 "" (7x13) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0xe3, 0xc7, 0x8f, 0x1e, 0x37, 0xc0,
    /* U+03BB "" (8x13) */
    0x30, 0x30, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0x66, 0xc3, 0xc3,
    0xc3,
    /* U+03BC "" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xfb, 0xc0, 0xc0, 0xc0,
    /* U+03C0 "" (8x9) */
    0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+03C3 "" (9x9) */
    0x3f, 0xb3, 0x30, 0xd8, 0x6c, 0x36, 0x1b, 0x0c, 0xcc, 0x3c, 0x00,
    /* U+03C4 "" (8x9) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0e,
    /* U+03C6 "" (8x12) */
    0x4e, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e, 0x18, 0x18, 0x18,
    /* U+03C9 "" (8x9) */
    0x66, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xff, 0x66,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (9x1) */
    0xff, 0x80,
    /* U+2018 "" (3x4) */
    0x7b, 0x60,
    /* U+2019 "" (3x4) */
    0x6d, 0xe0,
    /* U+201C "" (7x4) */
    0x67, 0x9b, 0x36, 0x60,
    /* U+201D "" (7x4) */
    0x66, 0xcd, 0x9e, 0x60,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (10x12) */
    0xe6, 0x29, 0x8e, 0xc0, 0x30, 0x18, 0x06, 0x03, 0x00, 0xc0, 0x60, 0x1b,
    0xfc, 0xb7, 0x3f,
    /* U+2190 "" (9x8) */
    0x10, 0x18, 0x18, 0x1f, 0xff, 0xfb, 0x00, 0xc0, 0x20,
    /* U+2191 "" (8x13) */
    0x18, 0x3c, 0x7e, 0xdb, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18,
    /* U+2192 "" (9x8) */
    0x04, 0x03, 0x00, 0xdf, 0xff, 0xf8, 0x18, 0x18, 0x08,
    /* U+2193 "" (8x13) */
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xdb, 0x7e, 0x3c,
    0x18,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 160, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 160, .box_w = 2, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 160, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 7, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 160, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 160, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 11},
    {.bitmap_index = 62, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 84, .adv_w = 160, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 91, .adv_w = 160, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 93, .adv_w = 160, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 94, .adv_w = 160, .box_w = 2, .box_h = 2, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 160, .box_w = 2, .box_h = 8, .ofs_x = 4, .ofs_y = 1},
    {.bitmap_index = 235, .adv_w = 160, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 239, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 160, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 257, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 160, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 517, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 160, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 665, .adv_w = 160, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 666, .adv_w = 160, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 13},
    {.bitmap_index = 668, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 745, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 160, .box_w = 6, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 777, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 160, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 836, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 848, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 926, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 160, .box_w = 2, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 949, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 959, .adv_w = 160, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 963, .adv_w = 160, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 967, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 977, .adv_w = 160, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 983, .adv_w = 160, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 989, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1001, .adv_w = 160, .box_w = 2, .box_h = 2, .ofs_x = 4, .ofs_y = 5},
    {.bitmap_index = 1002, .adv_w = 160, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1009, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1018, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1031, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1055, .adv_w = 160, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1071, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1083, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1096, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1105, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1117, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1130, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1142, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1151, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1162, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1171, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1183, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1192, .adv_w = 160, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1193, .adv_w = 160, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1195, .adv_w = 160, .box_w = 3, .box_h = 4, .ofs_x = 4, .ofs_y = 11},
    {.bitmap_index = 1197, .adv_w = 160, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 11},
    {.bitmap_index = 1199, .adv_w = 160, .box_w = 7, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 1203, .adv_w = 160, .box_w = 7, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 1207, .adv_w = 160, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 1209, .adv_w = 160, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1211, .adv_w = 160, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1235, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1248, .adv_w = 160, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1257, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_terminus_bold_20 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 20,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 13,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = 0,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_20,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_TERMINUS_BOLD_20 */
