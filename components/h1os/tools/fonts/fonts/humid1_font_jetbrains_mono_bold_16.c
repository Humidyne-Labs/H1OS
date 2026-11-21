/*******************************************************************************
 * Font: humid1_font_jetbrains_mono_bold_16 (jetbrains_mono bold)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_JETBRAINS_MONO_BOLD_16
#define HUMID1_FONT_JETBRAINS_MONO_BOLD_16 1
#endif

#if HUMID1_FONT_JETBRAINS_MONO_BOLD_16

extern const lv_font_t humid1_icon_fa7_solid_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xff, 0xff, 0x0f,
    /* U+0022 "" (6x5) */
    0xcf, 0x7d, 0xf7, 0xcc,
    /* U+0023 "#" (9x12) */
    0x19, 0x0c, 0x84, 0xcf, 0xf7, 0xf9, 0x98, 0xc8, 0x6e, 0xff, 0xb3, 0x19,
    0x8c, 0xc0,
    /* U+0024 "$" (8x16) */
    0x10, 0x10, 0x3c, 0x7e, 0xf6, 0xd0, 0xf0, 0x78, 0x3e, 0x1f, 0x17, 0xd7,
    0xfe, 0x7c, 0x10, 0x10,
    /* U+0025 "%" (9x12) */
    0x70, 0xfc, 0xf6, 0x5b, 0x6f, 0xe1, 0x60, 0x20, 0x3f, 0x34, 0x92, 0x51,
    0xb8, 0xf0,
    /* U+0026 "&" (8x12) */
    0x38, 0x7c, 0x66, 0x60, 0x60, 0x70, 0xf3, 0xdf, 0xce, 0xce, 0xfe, 0x7b,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x15) */
    0x1b, 0xf9, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xc7, 0x1c, 0x20,
    /* U+0029 ")" (5x15) */
    0xc7, 0x1c, 0x71, 0x8c, 0x63, 0x18, 0xce, 0x67, 0x72, 0x00,
    /* U+002A "" (8x8) */
    0x18, 0x18, 0x98, 0xff, 0x7e, 0x38, 0x6c, 0x66,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xfe, 0x18, 0x18, 0x18,
    /* U+002C "," (3x5) */
    0xff, 0x68,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0x7d, 0x80,
    /* U+002F "/" (7x15) */
    0x06, 0x0c, 0x38, 0x60, 0xc3, 0x86, 0x0c, 0x38, 0x61, 0xc3, 0x06, 0x1c,
    0x30, 0x00,
    /* U+0030 "0" (8x12) */
    0x3c, 0x7e, 0xe6, 0xc7, 0xc7, 0xdf, 0xdf, 0xc7, 0xc7, 0xc7, 0xfe, 0x7c,
    /* U+0031 "1" (8x12) */
    0x18, 0x7c, 0xfc, 0xdc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xff, 0xff,
    /* U+0032 "2" (8x12) */
    0x38, 0x7e, 0xe6, 0xc6, 0x06, 0x06, 0x0c, 0x18, 0x30, 0x70, 0xff, 0xff,
    /* U+0033 "3" (8x12) */
    0x7e, 0xfe, 0x0e, 0x1c, 0x38, 0x3e, 0x0e, 0x07, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0034 "4" (7x12) */
    0x0c, 0x18, 0x61, 0xc7, 0x0c, 0xf9, 0xe3, 0xff, 0xfc, 0x18, 0x30,
    /* U+0035 "5" (8x12) */
    0xfe, 0xfe, 0xe0, 0xe0, 0xfc, 0xfe, 0xe7, 0x07, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0036 "6" (8x12) */
    0x1c, 0x18, 0x38, 0x30, 0x60, 0xfe, 0xfe, 0xc7, 0xc3, 0xc7, 0xfe, 0x7c,
    /* U+0037 "7" (8x12) */
    0xff, 0xff, 0xc7, 0xc6, 0x0e, 0x0c, 0x0c, 0x1c, 0x18, 0x38, 0x30, 0x70,
    /* U+0038 "8" (8x12) */
    0x3c, 0x7e, 0xe6, 0xc6, 0xe6, 0x7c, 0x7c, 0xe6, 0xc7, 0xc7, 0xfe, 0x7c,
    /* U+0039 "9" (8x12) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x0e, 0x0c, 0x1c, 0x18, 0x30,
    /* U+003A ":" (3x9) */
    0x7d, 0x80, 0x17, 0xe0,
    /* U+003B ";" (3x12) */
    0x7d, 0x80, 0x07, 0xfb, 0x40,
    /* U+003C "<" (7x8) */
    0x06, 0x3d, 0xe7, 0x0f, 0x07, 0x83, 0x81,
    /* U+003D "=" (7x6) */
    0xff, 0xfc, 0x00, 0x0f, 0xff, 0xc0,
    /* U+003E ">" (7x8) */
    0xe0, 0xf0, 0x78, 0x30, 0xe7, 0xbc, 0x60,
    /* U+003F "?" (6x12) */
    0xf3, 0xe1, 0xc3, 0x0d, 0xf7, 0x98, 0x40, 0x06, 0x18,
    /* U+0040 "@" (9x15) */
    0x1e, 0x1f, 0x98, 0x68, 0x3c, 0x7e, 0x6f, 0x27, 0x93, 0xc9, 0xe6, 0xf3,
    0xe8, 0x06, 0x01, 0xe0, 0x70,
    /* U+0041 "A" (8x12) */
    0x18, 0x38, 0x3c, 0x3c, 0x6c, 0x6c, 0x66, 0x6e, 0xfe, 0xc6, 0xc3, 0xc3,
    /* U+0042 "B" (8x12) */
    0xf8, 0xfe, 0xc7, 0xc7, 0xc6, 0xfc, 0xfe, 0xc7, 0xc3, 0xc7, 0xfe, 0xfc,
    /* U+0043 "C" (8x12) */
    0x3c, 0x7e, 0xe7, 0xc2, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc7, 0x7e, 0x3c,
    /* U+0044 "D" (8x12) */
    0xf8, 0xfe, 0xc6, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xc7, 0xfe, 0xfc,
    /* U+0045 "E" (7x12) */
    0x7f, 0xff, 0x87, 0x0e, 0x1f, 0xff, 0xf0, 0xe1, 0xc3, 0xff, 0xf0,
    /* U+0046 "F" (8x12) */
    0xfe, 0xff, 0xe0, 0xc0, 0xc0, 0xfe, 0xfe, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (8x12) */
    0x3c, 0x7e, 0xe7, 0xc2, 0xc0, 0xc0, 0xcf, 0xcf, 0xc7, 0xc7, 0x7e, 0x3c,
    /* U+0048 "H" (7x12) */
    0xc3, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0049 "I" (7x12) */
    0x7f, 0xfc, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x33, 0xff, 0xf0,
    /* U+004A "J" (7x12) */
    0x1e, 0x7c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0x8f, 0xfb, 0xe0,
    /* U+004B "K" (8x12) */
    0xc3, 0xc7, 0xc6, 0xce, 0xcc, 0xfc, 0xfc, 0xcc, 0xce, 0xc6, 0xc7, 0xc7,
    /* U+004C "L" (7x12) */
    0x81, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xff, 0xf0,
    /* U+004D "M" (8x12) */
    0xc7, 0xe7, 0xe7, 0xef, 0xff, 0xfb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+004E "N" (8x12) */
    0xc2, 0xe3, 0xe3, 0xf3, 0xf3, 0xd3, 0xdb, 0xdb, 0xcf, 0xcf, 0xcf, 0xc7,
    /* U+004F "O" (8x12) */
    0x3c, 0x7e, 0xe6, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc6, 0xfe, 0x7c,
    /* U+0050 "P" (8x12) */
    0xf8, 0xfe, 0xc7, 0xc3, 0xc3, 0xe7, 0xfe, 0xf8, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (8x15) */
    0x3c, 0x7e, 0xe6, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    0x0c, 0x06, 0x07,
    /* U+0052 "R" (8x12) */
    0xf8, 0xfe, 0xc7, 0xc7, 0xc7, 0xee, 0xfe, 0xfc, 0xcc, 0xce, 0xc6, 0xc7,
    /* U+0053 "S" (8x12) */
    0x3c, 0x7e, 0xe6, 0xc0, 0xe0, 0x7c, 0x3e, 0x07, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0054 "T" (8x12) */
    0xff, 0xff, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (8x12) */
    0xc2, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc6, 0x7e, 0x7c,
    /* U+0056 "V" (8x12) */
    0xc3, 0xc3, 0xc7, 0xe6, 0xe6, 0x66, 0x66, 0x6c, 0x7c, 0x3c, 0x3c, 0x38,
    /* U+0057 "W" (9x12) */
    0xcc, 0xe6, 0xf3, 0x79, 0xb5, 0xda, 0xad, 0xd6, 0xef, 0x77, 0xb9, 0x9c,
    0xce, 0x60,
    /* U+0058 "X" (8x12) */
    0xc3, 0xe6, 0x66, 0x7c, 0x3c, 0x38, 0x38, 0x3c, 0x6c, 0x66, 0xe6, 0xc3,
    /* U+0059 "Y" (8x12) */
    0xc3, 0xc3, 0xe6, 0x66, 0x6c, 0x3c, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x12) */
    0x7f, 0xfc, 0x38, 0x71, 0xc3, 0x0e, 0x18, 0x70, 0xc3, 0xff, 0xf0,
    /* U+005B "[" (5x15) */
    0xff, 0xb1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x7f, 0xc0,
    /* U+005C "" (7x15) */
    0xc1, 0xc1, 0x83, 0x83, 0x06, 0x0e, 0x0c, 0x18, 0x38, 0x30, 0x70, 0x60,
    0xc1, 0x80,
    /* U+005D "]" (5x15) */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x33, 0xff, 0xe0,
    /* U+005E "^" (7x7) */
    0x18, 0x70, 0xf3, 0x66, 0x7c, 0xf0, 0x80,
    /* U+005F "_" (8x2) */
    0xfe, 0xff,
    /* U+0060 "`" (3x3) */
    0xdd, 0x80,
    /* U+0061 "a" (8x9) */
    0x3c, 0x7e, 0xc6, 0x07, 0x7f, 0xc7, 0xc7, 0xef, 0x7f,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe6, 0xc7, 0xc7, 0xc7, 0xe6, 0xfe, 0xdc,
    /* U+0063 "c" (8x9) */
    0x3c, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc7, 0x7e, 0x7c,
    /* U+0064 "d" (7x12) */
    0x02, 0x0c, 0x1b, 0xb7, 0xfc, 0xf1, 0xe3, 0xc7, 0x8f, 0xfb, 0xf0,
    /* U+0065 "e" (8x9) */
    0x3c, 0x7e, 0xc6, 0xc7, 0xff, 0xc0, 0xc0, 0xfe, 0x7c,
    /* U+0066 "f" (8x12) */
    0x0e, 0x1f, 0x38, 0x30, 0xff, 0xff, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    /* U+0067 "g" (7x12) */
    0x36, 0xff, 0x1e, 0x3c, 0x78, 0xf9, 0xbf, 0x06, 0x0c, 0xf9, 0xe0,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0xef, 0xfc, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (8x13) */
    0x08, 0x18, 0x18, 0x00, 0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff,
    0xff,
    /* U+006A "j" (7x16) */
    0x04, 0x1c, 0x30, 0x07, 0xcf, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1,
    0xbf, 0x7c,
    /* U+006B "k" (8x12) */
    0xc0, 0xc0, 0xc0, 0xc3, 0xc6, 0xce, 0xec, 0xfc, 0xfc, 0xce, 0xc6, 0xc7,
    /* U+006C "l" (9x12) */
    0x78, 0x7c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0e, 0x03,
    0xe1, 0xf0,
    /* U+006D "m" (8x9) */
    0xf6, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (8x9) */
    0xdc, 0xfe, 0xe6, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7,
    /* U+006F "o" (8x9) */
    0x3c, 0x7e, 0xe6, 0xc7, 0xc7, 0xc7, 0xc6, 0x7e, 0x7c,
    /* U+0070 "p" (8x12) */
    0xdc, 0xfe, 0xe6, 0xc7, 0xc7, 0xc7, 0xe6, 0xfe, 0xdc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x12) */
    0x32, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x7e, 0x0c, 0x18, 0x30,
    /* U+0072 "r" (8x9) */
    0xde, 0xff, 0xe7, 0xe3, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0073 "s" (8x9) */
    0x7c, 0xfe, 0xc2, 0xe0, 0x7e, 0x07, 0x07, 0xff, 0x7e,
    /* U+0074 "t" (8x11) */
    0x30, 0x30, 0xfe, 0xff, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x1e,
    /* U+0075 "u" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xbf, 0x3c,
    /* U+0076 "v" (8x9) */
    0xc3, 0xc7, 0xe6, 0x66, 0x66, 0x6c, 0x3c, 0x3c, 0x38,
    /* U+0077 "w" (9x9) */
    0xcc, 0xe6, 0xd3, 0x69, 0xb7, 0x5b, 0xbd, 0xdc, 0xe6, 0x73, 0x00,
    /* U+0078 "x" (8x9) */
    0xc7, 0x66, 0x7c, 0x3c, 0x38, 0x3c, 0x6c, 0x66, 0xc7,
    /* U+0079 "y" (8x12) */
    0xc3, 0xc7, 0xe6, 0x66, 0x6e, 0x3c, 0x3c, 0x3c, 0x18, 0x38, 0x30, 0x30,
    /* U+007A "z" (7x9) */
    0xff, 0xfc, 0x38, 0xe3, 0x86, 0x18, 0x7f, 0xfe,
    /* U+007B "{" (7x15) */
    0x0e, 0x3c, 0x70, 0xe1, 0xc3, 0xbe, 0x7c, 0x1c, 0x38, 0x70, 0xe1, 0xc1,
    0xc1, 0x80,
    /* U+007C "|" (2x15) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (7x15) */
    0xf1, 0xe0, 0xc1, 0x83, 0x06, 0x0f, 0x8f, 0x38, 0x60, 0xc1, 0x83, 0x1e,
    0x38, 0x00,
    /* U+007E "~" (8x4) */
    0x20, 0xf3, 0xdb, 0x8e,
    /* U+00B0 "" (5x5) */
    0x32, 0x72, 0x93, 0x00,
    /* U+00B1 "" (8x9) */
    0x18, 0x18, 0x38, 0xff, 0xff, 0x18, 0x18, 0xfe, 0xff,
    /* U+00B2 "" (5x7) */
    0x7e, 0x42, 0x36, 0x7d, 0xe0,
    /* U+00B3 "" (5x7) */
    0x78, 0x8c, 0x38, 0xfd, 0xc0,
    /* U+00B5 "" (7x12) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xff, 0xfd, 0x83, 0x06, 0x00,
    /* U+00B7 "" (3x3) */
    0x7d, 0x80,
    /* U+00D7 "" (6x6) */
    0xcf, 0xf7, 0x9e, 0xff, 0x30,
    /* U+00F7 "" (6x9) */
    0x21, 0xc3, 0x00, 0xff, 0xf0, 0x1c, 0x30,
    /* U+0394 "" (8x12) */
    0x18, 0x3c, 0x3c, 0x3c, 0x6c, 0x6e, 0x66, 0x66, 0xc6, 0xc7, 0xff, 0xff,
    /* U+03A9 "" (8x12) */
    0x3c, 0x7e, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0x6e, 0xef, 0xef,
    /* U+03B1 "" (7x9) */
    0x32, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xff, 0x7e,
    /* U+03B2 "" (8x15) */
    0x3c, 0x7e, 0xe7, 0xc7, 0xc6, 0xdc, 0xde, 0xc7, 0xc3, 0xc7, 0xfe, 0xfc,
    0xc0, 0xc0, 0xc0,
    /* U+03B3 "" (8x12) */
    0xc3, 0xc7, 0xe6, 0x66, 0x66, 0x6c, 0x3c, 0x38, 0x18, 0x18, 0x18, 0x18,
    /* U+03B4 "" (8x12) */
    0x7e, 0xfe, 0x70, 0x38, 0x1c, 0x7e, 0xe7, 0xc7, 0xc3, 0xc7, 0xfe, 0x7c,
    /* U+03B5 "" (8x9) */
    0x7c, 0xfe, 0xc2, 0xe0, 0x78, 0xe0, 0xc0, 0xff, 0x7e,
    /* U+03B8 "" (8x12) */
    0x38, 0x7e, 0xe6, 0xc7, 0xc7, 0xff, 0xff, 0xc7, 0xc7, 0xc6, 0x7e, 0x7c,
    /* U+03BB "" (8x12) */
    0x30, 0x30, 0x18, 0x18, 0x38, 0x3c, 0x3c, 0x6e, 0x66, 0xe6, 0xc7, 0xc3,
    /* U+03BC "" (8x12) */
    0xc6, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe6, 0xfe, 0xfc, 0xc0, 0xc0, 0xc0,
    /* U+03C0 "" (9x9) */
    0xff, 0xff, 0xdd, 0xce, 0xe7, 0x73, 0xb9, 0xdc, 0xe7, 0x71, 0x80,
    /* U+03C3 "" (8x9) */
    0x3f, 0x7f, 0xe6, 0xc6, 0xc7, 0xc7, 0xc6, 0xfe, 0x7c,
    /* U+03C4 "" (8x9) */
    0xfe, 0xff, 0x38, 0x38, 0x38, 0x38, 0x38, 0x1e, 0x1e,
    /* U+03C6 "" (8x12) */
    0x9c, 0x9e, 0x9b, 0x9b, 0x9b, 0x9b, 0xdb, 0xfe, 0x7c, 0x18, 0x18, 0x18,
    /* U+03C9 "" (8x9) */
    0x44, 0xc6, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xff, 0xee,
    /* U+2013 "" (7x2) */
    0xff, 0xfc,
    /* U+2014 "" (10x2) */
    0xff, 0xff, 0xe0,
    /* U+2018 "" (3x5) */
    0x2d, 0xfc,
    /* U+2019 "" (4x5) */
    0x76, 0x6e, 0x40,
    /* U+201C "" (8x5) */
    0x77, 0x66, 0xe6, 0xee, 0xcc,
    /* U+201D "" (8x5) */
    0x67, 0x66, 0xee, 0xcc, 0xcc,
    /* U+2022 "" (4x4) */
    0xef, 0xfe,
    /* U+2026 "" (8x3) */
    0xdb, 0xdb, 0xdb,
    /* U+2030 "" (10x12) */
    0x62, 0x3c, 0x89, 0x43, 0x70, 0x78, 0x06, 0x01, 0x00, 0xf6, 0x3e, 0xd4,
    0xbd, 0x2e, 0x7e,
    /* U+2190 "" (8x9) */
    0x18, 0x30, 0x60, 0x40, 0xff, 0xc0, 0x60, 0x20, 0x10,
    /* U+2191 "" (9x12) */
    0x08, 0x0e, 0x0f, 0xcd, 0x3c, 0x88, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02,
    0x01, 0x00,
    /* U+2192 "" (8x9) */
    0x18, 0x0c, 0x04, 0x02, 0xff, 0x02, 0x06, 0x0c, 0x18,
    /* U+2193 "" (9x12) */
    0x08, 0x04, 0x02, 0x01, 0x00, 0x80, 0x40, 0x21, 0x11, 0x49, 0x9f, 0x87,
    0x81, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 2, .box_h = 12, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 154, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 37, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 154, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 65, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 93, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 103, .adv_w = 154, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 105, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 121, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 249, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 262, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 269, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 154, .box_w = 9, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 295, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 497, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 616, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 630, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 640, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 647, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 649, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 651, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 724, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 762, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 827, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 838, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 875, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 895, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 904, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 916, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 938, .adv_w = 154, .box_w = 2, .box_h = 15, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 942, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 956, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 960, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 964, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 154, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 978, .adv_w = 154, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 983, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 994, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 996, .adv_w = 154, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1001, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 1008, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1020, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1032, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1040, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1055, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1067, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1079, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1088, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1100, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1112, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1124, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1153, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1165, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1176, .adv_w = 154, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1179, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 1181, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1184, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1189, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1194, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 1196, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1199, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1214, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1223, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1237, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1246, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0}
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

const lv_font_t humid1_font_jetbrains_mono_bold_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 12,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_JETBRAINS_MONO_BOLD_16 */
