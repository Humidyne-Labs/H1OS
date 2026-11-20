/*******************************************************************************
 * Font: humid1_font_plex_mono_italic_16 (mono italic)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_MONO_ITALIC_16
#define HUMID1_FONT_PLEX_MONO_ITALIC_16 1
#endif

#if HUMID1_FONT_PLEX_MONO_ITALIC_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x11) */
    0x33, 0x76, 0x66, 0x40, 0xee, 0xc0,
    /* U+0022 "" (6x5) */
    0xcf, 0x2d, 0xb6, 0xd8,
    /* U+0023 "#" (10x11) */
    0x0c, 0x83, 0x60, 0x91, 0xef, 0x7b, 0xc4, 0x8f, 0x7b, 0xde, 0x24, 0x1b,
    0x06, 0xc0,
    /* U+0024 "$" (8x15) */
    0x04, 0x0c, 0x3e, 0x7f, 0x6b, 0x68, 0x78, 0x3e, 0x1f, 0x13, 0xd7, 0xfe,
    0x7c, 0x30, 0x30,
    /* U+0025 "%" (10x11) */
    0x38, 0x5f, 0x26, 0xd9, 0x3c, 0x78, 0x0c, 0xc0, 0x78, 0xf2, 0x6d, 0x93,
    0xe8, 0x70,
    /* U+0026 "&" (9x11) */
    0x0e, 0x0f, 0x86, 0x63, 0x31, 0xb3, 0xf3, 0xb1, 0x98, 0xce, 0xff, 0xdc,
    0xc0,
    /* U+0027 "'" (3x5) */
    0x6d, 0xac,
    /* U+0028 "(" (6x14) */
    0x0c, 0x63, 0x18, 0x43, 0x0c, 0x30, 0xc3, 0x0c, 0x10, 0x60, 0xc0,
    /* U+0029 ")" (6x14) */
    0x30, 0x60, 0x83, 0x0c, 0x30, 0xc3, 0x0c, 0x61, 0x8c, 0x63, 0x00,
    /* U+002A "" (8x8) */
    0x08, 0x18, 0xd9, 0xff, 0x3c, 0x3c, 0x6c, 0x44,
    /* U+002B "+" (8x8) */
    0x08, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x30,
    /* U+002C "," (4x5) */
    0x76, 0x6c, 0xc0,
    /* U+002D "-" (5x2) */
    0x7f, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x00,
    /* U+002F "/" (9x14) */
    0x01, 0x80, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x08, 0x0c,
    0x0c, 0x06, 0x06, 0x00,
    /* U+0030 "0" (8x11) */
    0x1e, 0x7f, 0x63, 0xe3, 0xc3, 0xdb, 0xdb, 0xc3, 0xc6, 0xfe, 0x78,
    /* U+0031 "1" (8x11) */
    0x1e, 0x3c, 0x7c, 0xec, 0x4c, 0x0c, 0x0c, 0x18, 0x18, 0xff, 0xfe,
    /* U+0032 "2" (9x11) */
    0x0f, 0x1f, 0xcc, 0x60, 0x30, 0x38, 0x38, 0x38, 0x38, 0x70, 0x7f, 0xbf,
    0xc0,
    /* U+0033 "3" (8x11) */
    0x1e, 0x7f, 0x63, 0x07, 0x3e, 0x3e, 0x06, 0x06, 0xc6, 0xfe, 0x78,
    /* U+0034 "4" (9x11) */
    0x03, 0x83, 0xc3, 0xc3, 0x61, 0x31, 0x99, 0x8d, 0xff, 0xff, 0x83, 0x01,
    0x80,
    /* U+0035 "5" (8x11) */
    0x3f, 0x7f, 0x60, 0x7c, 0x7e, 0x47, 0x03, 0x07, 0xc6, 0xfe, 0x78,
    /* U+0036 "6" (8x11) */
    0x0e, 0x18, 0x30, 0x7e, 0xfe, 0xe7, 0xc3, 0xc3, 0xc6, 0xfe, 0x78,
    /* U+0037 "7" (9x11) */
    0x7f, 0xbf, 0xd0, 0xd8, 0xe0, 0x60, 0x60, 0x30, 0x30, 0x38, 0x18, 0x18,
    0x00,
    /* U+0038 "8" (8x11) */
    0x1e, 0x7f, 0x63, 0x63, 0x3e, 0x7e, 0xc7, 0xc3, 0xc7, 0xfe, 0x7c,
    /* U+0039 "9" (8x11) */
    0x1e, 0x7f, 0x63, 0xc3, 0xc3, 0xe7, 0x7f, 0x7e, 0x0c, 0x18, 0x70,
    /* U+003A ":" (4x9) */
    0x77, 0x60, 0x00, 0xee, 0xc0,
    /* U+003B ";" (5x11) */
    0x39, 0xcc, 0x00, 0x01, 0xcc, 0x66, 0x30,
    /* U+003C "<" (8x9) */
    0x01, 0x07, 0x1e, 0x78, 0xe0, 0x70, 0x3c, 0x0e, 0x02,
    /* U+003D "=" (8x6) */
    0xff, 0xff, 0x00, 0x00, 0xff, 0xfe,
    /* U+003E ">" (7x9) */
    0x40, 0xe0, 0xf0, 0x70, 0x63, 0xde, 0x70, 0x80,
    /* U+003F "?" (7x11) */
    0x3c, 0xff, 0x18, 0x30, 0xc7, 0x18, 0x00, 0x60, 0xc1, 0x80,
    /* U+0040 "@" (8x13) */
    0x1e, 0x3f, 0x63, 0xcf, 0xdf, 0xdb, 0xf3, 0xb3, 0xbf, 0x9e, 0xc0, 0xfc,
    0x7c,
    /* U+0041 "A" (9x11) */
    0x0e, 0x07, 0x87, 0xc3, 0x63, 0xb1, 0x98, 0xcc, 0xfe, 0x7f, 0x71, 0xf0,
    0x60,
    /* U+0042 "B" (8x11) */
    0x7e, 0x7f, 0x63, 0x63, 0x7e, 0x7e, 0xc6, 0xc3, 0xc6, 0xfe, 0xfc,
    /* U+0043 "C" (8x11) */
    0x1e, 0x3f, 0x73, 0x61, 0xc0, 0xc0, 0xc0, 0xc2, 0xc6, 0x7e, 0x38,
    /* U+0044 "D" (8x11) */
    0x7e, 0x7f, 0x63, 0x63, 0x63, 0xe3, 0xc3, 0xc7, 0xc6, 0xfe, 0xf8,
    /* U+0045 "E" (8x11) */
    0x7f, 0x7f, 0x60, 0x60, 0x7f, 0x7e, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe,
    /* U+0046 "F" (9x11) */
    0x7f, 0xbf, 0xd8, 0x0c, 0x07, 0xe3, 0xf3, 0x01, 0x80, 0xc0, 0x60, 0x30,
    0x00,
    /* U+0047 "G" (8x11) */
    0x1e, 0x3f, 0x63, 0xe3, 0xc0, 0xcf, 0xcf, 0xc3, 0xc6, 0xfe, 0x76,
    /* U+0048 "H" (10x11) */
    0x30, 0xcc, 0x63, 0x18, 0xc6, 0x7f, 0x9f, 0xe6, 0x39, 0x8c, 0x63, 0x18,
    0xce, 0x30,
    /* U+0049 "I" (8x11) */
    0x7f, 0x7f, 0x0c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x30, 0xfe, 0xfe,
    /* U+004A "J" (8x11) */
    0x3f, 0x3f, 0x03, 0x03, 0x06, 0x06, 0x06, 0x06, 0xce, 0xfc, 0x78,
    /* U+004B "K" (9x11) */
    0x61, 0xb1, 0x99, 0x8d, 0x87, 0xc7, 0xe3, 0xf1, 0x98, 0xc6, 0x63, 0x31,
    0xc0,
    /* U+004C "L" (7x11) */
    0x30, 0x61, 0x83, 0x06, 0x0c, 0x18, 0x30, 0xc1, 0xff, 0xf8,
    /* U+004D "M" (10x11) */
    0x31, 0xce, 0x73, 0xbd, 0xfe, 0x6f, 0x9b, 0x66, 0x99, 0x06, 0x41, 0xb0,
    0x4c, 0x30,
    /* U+004E "N" (9x11) */
    0x71, 0xb8, 0x9c, 0xce, 0x65, 0xb6, 0xdb, 0x6d, 0x9c, 0xce, 0x47, 0x23,
    0x80,
    /* U+004F "O" (8x11) */
    0x1e, 0x7f, 0x63, 0xe3, 0xc3, 0xc3, 0xc3, 0xc7, 0xc6, 0xfe, 0x78,
    /* U+0050 "P" (8x11) */
    0x7e, 0x7f, 0x63, 0x63, 0x63, 0x7f, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (8x14) */
    0x1e, 0x7f, 0x63, 0xe3, 0xc3, 0xc3, 0xc3, 0xc7, 0xc6, 0xfe, 0x7c, 0x1b,
    0x0f, 0x0e,
    /* U+0052 "R" (8x11) */
    0x7e, 0x7f, 0x63, 0x63, 0x63, 0x7f, 0xfc, 0xcc, 0xcc, 0xc6, 0xc6,
    /* U+0053 "S" (8x11) */
    0x1e, 0x7f, 0x63, 0x60, 0x78, 0x7e, 0x0f, 0x07, 0xc6, 0xfe, 0x7c,
    /* U+0054 "T" (9x11) */
    0xff, 0xff, 0xc3, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x18, 0x0c,
    0x00,
    /* U+0055 "U" (9x11) */
    0x61, 0xb1, 0xd8, 0xcc, 0x6c, 0x36, 0x1b, 0x0d, 0x8c, 0xc6, 0x7f, 0x1f,
    0x00,
    /* U+0056 "V" (8x11) */
    0xc3, 0xc3, 0xc6, 0xc6, 0xcc, 0xcc, 0xcc, 0xd8, 0xf8, 0xf0, 0x70,
    /* U+0057 "W" (10x11) */
    0x60, 0x58, 0x36, 0x0d, 0xbb, 0x6e, 0x9b, 0xe7, 0xf9, 0x5e, 0x77, 0x3d,
    0xce, 0x70,
    /* U+0058 "X" (10x11) */
    0x30, 0xce, 0x61, 0xb8, 0x7c, 0x1e, 0x03, 0x81, 0xe0, 0xd8, 0x77, 0x18,
    0xcc, 0x38,
    /* U+0059 "Y" (9x11) */
    0xe1, 0xb1, 0xd8, 0xc6, 0xc3, 0xe1, 0xe0, 0x60, 0x30, 0x18, 0x18, 0x0c,
    0x00,
    /* U+005A "Z" (10x11) */
    0x3f, 0xcf, 0xf0, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x3f,
    0xcf, 0xf0,
    /* U+005B "[" (7x14) */
    0x3e, 0x7c, 0xc1, 0x82, 0x04, 0x18, 0x30, 0x60, 0x81, 0x06, 0x0f, 0x9f,
    0x00,
    /* U+005C "" (4x14) */
    0x8c, 0xcc, 0x44, 0x66, 0x62, 0x23, 0x33,
    /* U+005D "]" (8x14) */
    0x1f, 0x1e, 0x02, 0x02, 0x06, 0x06, 0x06, 0x04, 0x04, 0x0c, 0x0c, 0x0c,
    0x7c, 0xf8,
    /* U+005E "^" (8x7) */
    0x1c, 0x1e, 0x36, 0x76, 0x63, 0xc3, 0xc3,
    /* U+005F "_" (8x2) */
    0xff, 0xff,
    /* U+0060 "`" (3x3) */
    0xcd, 0x80,
    /* U+0061 "a" (8x8) */
    0x3b, 0x7f, 0xe6, 0xc6, 0xc6, 0xce, 0xf7, 0x67,
    /* U+0062 "b" (8x12) */
    0x60, 0x60, 0x60, 0x60, 0x6e, 0x7f, 0xe3, 0xc3, 0xc3, 0xc6, 0xfe, 0xdc,
    /* U+0063 "c" (7x8) */
    0x3c, 0xff, 0x9e, 0x0c, 0x38, 0xff, 0x3c,
    /* U+0064 "d" (9x12) */
    0x01, 0x81, 0x80, 0xc0, 0x63, 0xb3, 0xfb, 0x9d, 0x84, 0xc6, 0x67, 0x3f,
    0x8e, 0xc0,
    /* U+0065 "e" (8x8) */
    0x3e, 0x7f, 0xe3, 0xc6, 0xfc, 0xc2, 0xfe, 0x7c,
    /* U+0066 "f" (10x15) */
    0x03, 0xc1, 0xf0, 0x60, 0x18, 0x3f, 0xcf, 0xf0, 0xc0, 0x30, 0x0c, 0x03,
    0x00, 0xc2, 0x60, 0xd8, 0x1e, 0x03, 0x00,
    /* U+0067 "g" (9x11) */
    0x1d, 0x9f, 0xdc, 0xec, 0x36, 0x33, 0x39, 0xfc, 0x76, 0x46, 0x7f, 0x1f,
    0x00,
    /* U+0068 "h" (8x12) */
    0x70, 0x60, 0x60, 0x60, 0x6e, 0x7f, 0xe7, 0xe3, 0xc6, 0xc6, 0xc6, 0xc6,
    /* U+0069 "i" (7x11) */
    0x0c, 0x38, 0x07, 0xcf, 0x83, 0x04, 0x19, 0x36, 0x78, 0xe0,
    /* U+006A "j" (7x14) */
    0x06, 0x0c, 0x03, 0xf7, 0xc1, 0x83, 0x06, 0x0c, 0x32, 0x66, 0xcf, 0x8e,
    0x00,
    /* U+006B "k" (8x12) */
    0x70, 0x60, 0x60, 0x60, 0x6e, 0x7f, 0xe7, 0xe6, 0xd8, 0xdb, 0xdf, 0xce,
    /* U+006C "l" (6x12) */
    0xf3, 0xc3, 0x0c, 0x31, 0x86, 0x18, 0x6d, 0xf7, 0x9c,
    /* U+006D "m" (9x8) */
    0x6d, 0xbf, 0xdb, 0x29, 0xb4, 0xde, 0x4f, 0x27, 0xb2,
    /* U+006E "n" (8x8) */
    0x6e, 0x7f, 0xe7, 0xe3, 0xc6, 0xc6, 0xc6, 0xc6,
    /* U+006F "o" (8x8) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc7, 0xc6, 0xfe, 0x78,
    /* U+0070 "p" (9x11) */
    0x37, 0x1f, 0xdc, 0x6c, 0x36, 0x1b, 0x19, 0xfc, 0xdc, 0xc0, 0x60, 0x30,
    0x00,
    /* U+0071 "q" (8x11) */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc6, 0xce, 0xfe, 0x76, 0x06, 0x0c, 0x0c,
    /* U+0072 "r" (7x8) */
    0xf7, 0xfd, 0xc3, 0x06, 0x0c, 0x18, 0x30,
    /* U+0073 "s" (7x8) */
    0x3e, 0xfd, 0x83, 0xe3, 0xe0, 0xff, 0xbe,
    /* U+0074 "t" (8x11) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x30, 0x30, 0x32, 0x36, 0x3c, 0x38,
    /* U+0075 "u" (8x8) */
    0x63, 0x63, 0xc3, 0xc6, 0xc6, 0xce, 0xf6, 0x66,
    /* U+0076 "v" (8x8) */
    0xe2, 0xe3, 0x63, 0x63, 0x66, 0x6e, 0x7c, 0x70,
    /* U+0077 "w" (9x8) */
    0x65, 0xb6, 0xdb, 0x69, 0xb4, 0xde, 0xcf, 0xec, 0xdc,
    /* U+0078 "x" (10x8) */
    0x19, 0x8e, 0xe6, 0xcc, 0x32, 0x8c, 0x37, 0x6f, 0xf1, 0x98,
    /* U+0079 "y" (9x11) */
    0x31, 0x98, 0xd8, 0x6c, 0x66, 0x33, 0x39, 0xfc, 0x6e, 0x46, 0x7f, 0x1f,
    0x00,
    /* U+007A "z" (8x8) */
    0x7b, 0x7f, 0xce, 0x1c, 0x30, 0xe2, 0xff, 0x9e,
    /* U+007B "{" (7x14) */
    0x1e, 0x3c, 0xc0, 0x81, 0x83, 0x3c, 0x78, 0x30, 0x61, 0x82, 0x07, 0x8f,
    0x00,
    /* U+007C "|" (4x14) */
    0x33, 0x32, 0x66, 0x66, 0x64, 0xcc, 0xcc,
    /* U+007D "}" (7x14) */
    0x3c, 0x78, 0x30, 0x41, 0x82, 0x07, 0x8f, 0x30, 0x60, 0x40, 0x8f, 0x1e,
    0x00,
    /* U+007E "~" (8x4) */
    0x71, 0xfb, 0xde, 0x8e,
    /* U+00B0 "" (5x5) */
    0x76, 0x63, 0x37, 0x00,
    /* U+00B1 "" (9x10) */
    0x06, 0x03, 0x03, 0x0f, 0xf7, 0xf8, 0x60, 0x30, 0x00, 0xff, 0x7f, 0x80,
    /* U+00B2 "" (5x6) */
    0x72, 0xc6, 0x64, 0x78,
    /* U+00B3 "" (5x6) */
    0x70, 0xcc, 0x29, 0x78,
    /* U+00B5 "" (9x11) */
    0x31, 0x98, 0xd8, 0x6c, 0x76, 0x33, 0x39, 0xfc, 0xf6, 0xc0, 0x60, 0x30,
    0x00,
    /* U+00B7 "" (3x3) */
    0x7d, 0x80,
    /* U+00D7 "" (8x7) */
    0x62, 0x67, 0x3e, 0x38, 0x3c, 0xee, 0xc6,
    /* U+00F7 "" (8x8) */
    0x08, 0x18, 0x00, 0xff, 0xff, 0x00, 0x10, 0x30,
    /* U+0394 "" (9x11) */
    0x0e, 0x07, 0x87, 0xc3, 0x63, 0x31, 0x98, 0xcc, 0xc6, 0x63, 0x7f, 0xff,
    0xc0,
    /* U+03A9 "" (9x11) */
    0x0f, 0x1f, 0xcc, 0x6e, 0x36, 0x1b, 0x0d, 0x86, 0xc6, 0x36, 0x7b, 0xfd,
    0xc0,
    /* U+03BC "" (9x11) */
    0x31, 0x98, 0xd8, 0x6c, 0x76, 0x33, 0x39, 0xfc, 0xf6, 0xc0, 0x60, 0x30,
    0x00,
    /* U+2013 "" (8x2) */
    0xff, 0xff,
    /* U+2014 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2018 "" (4x5) */
    0x13, 0x36, 0xe0,
    /* U+2019 "" (4x5) */
    0x76, 0x6c, 0xc0,
    /* U+201C "" (7x5) */
    0x32, 0xcd, 0x9e, 0x6c, 0xc0,
    /* U+201D "" (8x5) */
    0x77, 0x66, 0x66, 0xcc, 0xcc,
    /* U+2022 "" (4x4) */
    0x7f, 0xfe,
    /* U+2026 "" (8x2) */
    0xd9, 0xdb,
    /* U+2030 "" (8x11) */
    0x70, 0xd0, 0x90, 0x93, 0xfe, 0x70, 0xf7, 0x59, 0xc9, 0xdb, 0x7e,
    /* U+2190 "" (8x6) */
    0x30, 0x60, 0xff, 0xff, 0x60, 0x30,
    /* U+2191 "" (7x11) */
    0x18, 0x79, 0xff, 0xf5, 0xa3, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+2192 "" (9x6) */
    0x06, 0x01, 0xbf, 0xff, 0xf0, 0x30, 0x30,
    /* U+2193 "" (7x11) */
    0x18, 0x30, 0x60, 0xc1, 0x83, 0x16, 0xff, 0x7e, 0x78, 0x60,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 4, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 10, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 68, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 98, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 106, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 109, .adv_w = 154, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 111, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 129, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 154, .box_w = 4, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 154, .box_w = 5, .box_h = 11, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 257, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 272, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 303, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 506, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 633, .adv_w = 154, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 640, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 654, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 661, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 663, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 665, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 706, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 154, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 733, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 746, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 781, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 827, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 840, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 851, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 901, .adv_w = 154, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 911, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 924, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 932, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 945, .adv_w = 154, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 952, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 965, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 969, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 973, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 985, .adv_w = 154, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 989, .adv_w = 154, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 993, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1006, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 1008, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1015, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1023, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1036, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1062, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1064, .adv_w = 154, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1067, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1070, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 1073, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1078, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1083, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 1085, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1104, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1114, .adv_w = 154, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1121, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_italic_16 = {
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

#endif /* #if HUMID1_FONT_PLEX_MONO_ITALIC_16 */
