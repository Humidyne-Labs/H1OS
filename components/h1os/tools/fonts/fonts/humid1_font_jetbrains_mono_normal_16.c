/*******************************************************************************
 * Font: humid1_font_jetbrains_mono_normal_16 (jetbrains_mono normal)
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

#ifndef HUMID1_FONT_JETBRAINS_MONO_NORMAL_16
#define HUMID1_FONT_JETBRAINS_MONO_NORMAL_16 1
#endif

#if HUMID1_FONT_JETBRAINS_MONO_NORMAL_16

extern const lv_font_t humid1_icon_fa7_solid_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xff, 0xff, 0x0f,
    /* U+0022 "" (5x5) */
    0xce, 0x73, 0x9c, 0x80,
    /* U+0023 "#" (8x12) */
    0x02, 0x22, 0x22, 0xff, 0xff, 0x64, 0x64, 0x64, 0xff, 0x4c, 0x4c, 0xc8,
    /* U+0024 "$" (8x16) */
    0x10, 0x10, 0x3c, 0x7e, 0xd6, 0xd0, 0xf0, 0x78, 0x3e, 0x1e, 0x13, 0xd3,
    0xfe, 0x7c, 0x10, 0x10,
    /* U+0025 "%" (9x12) */
    0x70, 0xec, 0xf6, 0x5b, 0x4f, 0xe1, 0x20, 0x20, 0x3f, 0x34, 0x92, 0x51,
    0x38, 0xf0,
    /* U+0026 "&" (8x12) */
    0x38, 0x7c, 0x46, 0x40, 0x60, 0x60, 0xf3, 0x9a, 0x8e, 0x8c, 0xce, 0x7b,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x15) */
    0x1b, 0x99, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x86, 0x1c, 0x60,
    /* U+0029 ")" (5x15) */
    0xc3, 0x0c, 0x21, 0x8c, 0x63, 0x18, 0xc6, 0x67, 0x72, 0x00,
    /* U+002A "" (8x8) */
    0x10, 0x18, 0x10, 0xf7, 0x7c, 0x38, 0x6c, 0x66,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xfe, 0x18, 0x18, 0x10,
    /* U+002C "," (3x5) */
    0x7b, 0x48,
    /* U+002D "-" (6x2) */
    0xff, 0xe0,
    /* U+002E "." (3x3) */
    0x7f, 0x80,
    /* U+002F "/" (7x15) */
    0x06, 0x0c, 0x18, 0x60, 0xc1, 0x06, 0x0c, 0x30, 0x60, 0xc3, 0x06, 0x08,
    0x30, 0x00,
    /* U+0030 "0" (7x12) */
    0x38, 0xff, 0x1e, 0x1c, 0x3b, 0x76, 0xe1, 0xc3, 0x85, 0x99, 0xe0,
    /* U+0031 "1" (8x12) */
    0x18, 0x78, 0xf8, 0x98, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0xff,
    /* U+0032 "2" (8x12) */
    0x3c, 0x7e, 0xc6, 0xc2, 0x06, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xfe, 0xff,
    /* U+0033 "3" (7x12) */
    0x7e, 0xfc, 0x30, 0xc3, 0x87, 0x81, 0x83, 0x03, 0x8f, 0xbb, 0xe0,
    /* U+0034 "4" (7x12) */
    0x04, 0x18, 0x61, 0xc3, 0x0c, 0xf9, 0xe3, 0xff, 0xfc, 0x18, 0x30,
    /* U+0035 "5" (7x12) */
    0x7e, 0xfd, 0x02, 0x05, 0x9f, 0xd1, 0x81, 0x02, 0x85, 0x99, 0xe0,
    /* U+0036 "6" (8x12) */
    0x08, 0x18, 0x30, 0x30, 0x60, 0x7c, 0xe6, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0037 "7" (8x12) */
    0xfe, 0xff, 0xc2, 0xc6, 0x06, 0x0c, 0x0c, 0x08, 0x18, 0x18, 0x30, 0x30,
    /* U+0038 "8" (7x12) */
    0x3c, 0xff, 0x1e, 0x36, 0x67, 0x8f, 0x23, 0xc3, 0x85, 0x9b, 0xe0,
    /* U+0039 "9" (8x12) */
    0x3c, 0x7e, 0xc6, 0xc3, 0xc3, 0xc6, 0x7e, 0x3e, 0x0c, 0x18, 0x18, 0x30,
    /* U+003A ":" (3x9) */
    0x7d, 0x00, 0x07, 0x60,
    /* U+003B ";" (3x12) */
    0x7d, 0x00, 0x03, 0xdb, 0x40,
    /* U+003C "<" (7x8) */
    0x06, 0x39, 0xc6, 0x0e, 0x07, 0x03, 0x81,
    /* U+003D "=" (7x6) */
    0xff, 0xfc, 0x00, 0x0f, 0xef, 0xc0,
    /* U+003E ">" (7x8) */
    0xe0, 0xf0, 0x78, 0x30, 0xe7, 0xbc, 0x60,
    /* U+003F "?" (6x12) */
    0xe3, 0xe0, 0xc3, 0x0c, 0x67, 0x98, 0x20, 0x06, 0x18,
    /* U+0040 "@" (8x15) */
    0x3c, 0x7e, 0xc3, 0x83, 0x8f, 0x9b, 0x91, 0x91, 0x91, 0x9b, 0x9f, 0x80,
    0xc0, 0x78, 0x38,
    /* U+0041 "A" (8x12) */
    0x18, 0x38, 0x38, 0x2c, 0x2c, 0x64, 0x66, 0x66, 0x7e, 0xc2, 0xc3, 0xc3,
    /* U+0042 "B" (8x12) */
    0xf8, 0xfe, 0xc6, 0xc2, 0xc6, 0xfc, 0xfe, 0xc6, 0xc3, 0xc3, 0xfe, 0xfc,
    /* U+0043 "C" (7x12) */
    0x3c, 0xff, 0x1e, 0x1c, 0x18, 0x30, 0x60, 0xc1, 0x85, 0xb9, 0xe0,
    /* U+0044 "D" (7x12) */
    0x79, 0xff, 0x1e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x8f, 0xff, 0xe0,
    /* U+0045 "E" (6x12) */
    0xff, 0xf8, 0x20, 0x83, 0xff, 0xe0, 0x82, 0x0c, 0x3f,
    /* U+0046 "F" (8x12) */
    0xfe, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (8x12) */
    0x3c, 0x7e, 0xc6, 0xc2, 0xc0, 0xc0, 0xdf, 0xcf, 0xc3, 0xc6, 0x6e, 0x3c,
    /* U+0048 "H" (7x12) */
    0xc3, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0049 "I" (7x12) */
    0x7e, 0xfc, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x31, 0xff, 0xf0,
    /* U+004A "J" (7x12) */
    0x1e, 0x3c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0x8f, 0xbb, 0xe0,
    /* U+004B "K" (8x12) */
    0xc3, 0xc6, 0xc6, 0xcc, 0xcc, 0xf8, 0xf8, 0xcc, 0xcc, 0xc6, 0xc6, 0xc3,
    /* U+004C "L" (7x12) */
    0x81, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xf7, 0xf0,
    /* U+004D "M" (7x12) */
    0xc3, 0x8f, 0x9d, 0x3a, 0xbb, 0x76, 0xe1, 0xc3, 0x87, 0x0e, 0x10,
    /* U+004E "N" (7x12) */
    0x43, 0xc7, 0x8f, 0x9d, 0x3a, 0x76, 0xe5, 0xcf, 0x9f, 0x1e, 0x30,
    /* U+004F "O" (7x12) */
    0x3c, 0xff, 0x1e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x8d, 0xb9, 0xe0,
    /* U+0050 "P" (8x12) */
    0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (7x15) */
    0x38, 0xff, 0x1e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x85, 0x99, 0xe0, 0xc0,
    0xc1, 0x80,
    /* U+0052 "R" (8x12) */
    0x78, 0xfe, 0xc6, 0xc3, 0xc3, 0xc6, 0xfc, 0xcc, 0xcc, 0xc6, 0xc6, 0xc3,
    /* U+0053 "S" (8x12) */
    0x3c, 0x7e, 0xc6, 0xc0, 0xe0, 0x78, 0x3e, 0x06, 0x03, 0xc3, 0xee, 0x7c,
    /* U+0054 "T" (8x12) */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (7x12) */
    0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x8d, 0xb9, 0xe0,
    /* U+0056 "V" (8x12) */
    0x83, 0xc3, 0xc2, 0xc6, 0x66, 0x66, 0x64, 0x6c, 0x2c, 0x3c, 0x38, 0x38,
    /* U+0057 "W" (9x12) */
    0x48, 0xe6, 0x53, 0x29, 0xb4, 0xda, 0xad, 0x56, 0xea, 0x73, 0x39, 0x9c,
    0xc6, 0x60,
    /* U+0058 "X" (8x12) */
    0xc2, 0xc6, 0x66, 0x6c, 0x3c, 0x18, 0x18, 0x3c, 0x6c, 0x66, 0xc6, 0xc3,
    /* U+0059 "Y" (8x12) */
    0x83, 0xc3, 0xc6, 0x66, 0x6c, 0x3c, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x12) */
    0x7f, 0xfc, 0x18, 0x60, 0xc3, 0x06, 0x18, 0x60, 0xc3, 0xff, 0xf0,
    /* U+005B "[" (4x15) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,
    /* U+005C "" (7x15) */
    0xc0, 0xc1, 0x83, 0x03, 0x06, 0x04, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60,
    0xc0, 0x80,
    /* U+005D "]" (5x15) */
    0xf9, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xff, 0xc0,
    /* U+005E "^" (6x7) */
    0x31, 0xc7, 0xb6, 0xce, 0x38, 0x40,
    /* U+005F "_" (8x2) */
    0xfe, 0xff,
    /* U+0060 "`" (3x3) */
    0xdd, 0x80,
    /* U+0061 "a" (7x9) */
    0x3c, 0xfd, 0x18, 0x37, 0xf8, 0x71, 0xe3, 0x7e,
    /* U+0062 "b" (7x12) */
    0x41, 0x83, 0x06, 0xef, 0xf8, 0xf0, 0xe1, 0xc3, 0x8f, 0x9e, 0xe0,
    /* U+0063 "c" (7x9) */
    0x3c, 0xff, 0x1e, 0x0c, 0x18, 0x30, 0xb3, 0x3c,
    /* U+0064 "d" (7x12) */
    0x02, 0x04, 0x09, 0xd7, 0xf8, 0xf0, 0xe1, 0xc3, 0x8d, 0x9b, 0xf0,
    /* U+0065 "e" (7x9) */
    0x3c, 0xdf, 0x0e, 0x1f, 0xf8, 0x30, 0x33, 0x3c,
    /* U+0066 "f" (8x12) */
    0x0e, 0x1f, 0x30, 0x30, 0xff, 0xfe, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    /* U+0067 "g" (7x12) */
    0x3a, 0xff, 0x1e, 0x1c, 0x38, 0xf9, 0xbf, 0x02, 0x0c, 0xf9, 0xe0,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0xef, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (8x12) */
    0x18, 0x18, 0x00, 0x78, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7f, 0xff,
    /* U+006A "j" (6x16) */
    0x04, 0x30, 0xc0, 0x7d, 0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x3f, 0xfc,
    /* U+006B "k" (8x12) */
    0x40, 0xc0, 0xc0, 0xc3, 0xc6, 0xcc, 0xcc, 0xf8, 0xcc, 0xce, 0xc6, 0xc3,
    /* U+006C "l" (9x12) */
    0x78, 0x7c, 0x06, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x03,
    0xe1, 0xf0,
    /* U+006D "m" (8x9) */
    0xb6, 0xdb, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93,
    /* U+006E "n" (7x9) */
    0xdd, 0xff, 0x1e, 0x1c, 0x38, 0x70, 0xe1, 0xc2,
    /* U+006F "o" (7x9) */
    0x3c, 0xff, 0x1e, 0x1c, 0x38, 0x70, 0xb7, 0x3c,
    /* U+0070 "p" (7x12) */
    0xdd, 0xff, 0x1e, 0x1c, 0x38, 0x71, 0xf3, 0xdd, 0x83, 0x06, 0x00,
    /* U+0071 "q" (7x12) */
    0x3a, 0xff, 0x1e, 0x1c, 0x38, 0x71, 0xb7, 0x7e, 0x04, 0x08, 0x10,
    /* U+0072 "r" (7x9) */
    0xb9, 0xfb, 0x1c, 0x38, 0x10, 0x20, 0x40, 0x80,
    /* U+0073 "s" (7x9) */
    0x3c, 0xff, 0x03, 0x07, 0xc0, 0xc0, 0xf3, 0x7e,
    /* U+0074 "t" (7x11) */
    0x30, 0x63, 0xff, 0xf3, 0x06, 0x0c, 0x18, 0x30, 0x7c, 0x78,
    /* U+0075 "u" (7x9) */
    0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x71, 0xb7, 0x3c,
    /* U+0076 "v" (8x9) */
    0xc3, 0xc2, 0xc6, 0x66, 0x64, 0x6c, 0x3c, 0x38, 0x38,
    /* U+0077 "w" (8x9) */
    0x91, 0x99, 0x9b, 0x9b, 0xea, 0xea, 0xe6, 0x66, 0x66,
    /* U+0078 "x" (8x9) */
    0xc2, 0x66, 0x6c, 0x3c, 0x18, 0x3c, 0x6c, 0x66, 0xc3,
    /* U+0079 "y" (8x12) */
    0xc3, 0xc2, 0x66, 0x66, 0x64, 0x3c, 0x3c, 0x18, 0x18, 0x10, 0x30, 0x30,
    /* U+007A "z" (7x9) */
    0x7e, 0xfc, 0x38, 0x61, 0x86, 0x18, 0x7f, 0xfe,
    /* U+007B "{" (7x15) */
    0x0e, 0x38, 0x60, 0xc1, 0x83, 0x1e, 0x7c, 0x18, 0x10, 0x60, 0xc1, 0x81,
    0xc1, 0x80,
    /* U+007C "|" (2x15) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (7x15) */
    0xf0, 0x60, 0xc1, 0x83, 0x06, 0x07, 0x8f, 0x30, 0x60, 0xc1, 0x83, 0x1e,
    0x38, 0x00,
    /* U+007E "~" (8x3) */
    0xf3, 0xdb, 0x8e,
    /* U+00B0 "" (5x5) */
    0x32, 0x62, 0x93, 0x00,
    /* U+00B1 "" (8x9) */
    0x18, 0x18, 0x18, 0xff, 0xfe, 0x18, 0x18, 0x18, 0xff,
    /* U+00B2 "" (5x7) */
    0x7e, 0x42, 0x36, 0x3d, 0xe0,
    /* U+00B3 "" (5x7) */
    0x78, 0x8c, 0x38, 0xec, 0xc0,
    /* U+00B5 "" (7x12) */
    0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x71, 0xf3, 0xfd, 0x83, 0x06, 0x00,
    /* U+00B7 "" (3x3) */
    0x7f, 0x80,
    /* U+00D7 "" (6x6) */
    0xcf, 0xe7, 0x1e, 0xde, 0x20,
    /* U+00F7 "" (7x9) */
    0x10, 0x70, 0x60, 0x0f, 0xef, 0xc0, 0x1c, 0x18,
    /* U+0394 "" (8x12) */
    0x18, 0x38, 0x38, 0x2c, 0x2c, 0x64, 0x64, 0x46, 0x46, 0xc2, 0xc7, 0xff,
    /* U+03A9 "" (8x12) */
    0x3c, 0x7e, 0xc6, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0xc2, 0x66, 0xee, 0xef,
    /* U+03B1 "" (7x9) */
    0x3a, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xb7, 0x7e,
    /* U+03B2 "" (8x15) */
    0x3c, 0x7e, 0xc6, 0xc2, 0xc6, 0xdc, 0xde, 0xc6, 0xc3, 0xc3, 0xfe, 0xfc,
    0xc0, 0xc0, 0xc0,
    /* U+03B3 "" (8x12) */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x2c, 0x3c, 0x38, 0x18, 0x18, 0x18, 0x18,
    /* U+03B4 "" (8x12) */
    0x7e, 0x7e, 0x60, 0x30, 0x08, 0x3c, 0x66, 0xc2, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+03B5 "" (7x9) */
    0x3c, 0xff, 0x0b, 0x07, 0x9c, 0x30, 0x73, 0x7e,
    /* U+03B8 "" (7x12) */
    0x18, 0xff, 0x1e, 0x1c, 0x3f, 0xff, 0xe1, 0xc3, 0x8d, 0x99, 0xe0,
    /* U+03BB "" (8x12) */
    0x30, 0x30, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x64, 0x66, 0x46, 0xc2, 0xc3,
    /* U+03BC "" (7x12) */
    0xc3, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0xfd, 0x83, 0x06, 0x00,
    /* U+03C0 "" (9x9) */
    0xff, 0xbf, 0xc8, 0x84, 0x42, 0x21, 0x10, 0x88, 0x46, 0x21, 0x80,
    /* U+03C3 "" (8x9) */
    0x3f, 0x7e, 0xc6, 0xc2, 0xc2, 0xc2, 0xc6, 0x66, 0x3c,
    /* U+03C4 "" (7x9) */
    0xff, 0xfc, 0x40, 0x81, 0x02, 0x04, 0x0f, 0x0e,
    /* U+03C6 "" (8x12) */
    0x9c, 0x9e, 0x93, 0x93, 0x93, 0x93, 0x93, 0xde, 0x7c, 0x18, 0x18, 0x10,
    /* U+03C9 "" (8x9) */
    0x44, 0xc6, 0xc3, 0x93, 0x93, 0x93, 0x93, 0xdb, 0xee,
    /* U+2013 "" (8x2) */
    0xff, 0xfe,
    /* U+2014 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2018 "" (3x5) */
    0x2d, 0xec,
    /* U+2019 "" (3x5) */
    0xfb, 0x48,
    /* U+201C "" (7x5) */
    0x26, 0xcd, 0x9f, 0x6c, 0xc0,
    /* U+201D "" (7x4) */
    0x66, 0xcd, 0x96, 0x60,
    /* U+2022 "" (4x4) */
    0x6f, 0xfe,
    /* U+2026 "" (8x3) */
    0x92, 0xdb, 0xdb,
    /* U+2030 "" (10x12) */
    0x62, 0x2c, 0x89, 0x42, 0x70, 0x68, 0x04, 0x01, 0x00, 0xb6, 0x3a, 0xd4,
    0x95, 0x2e, 0x3e,
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
    {.bitmap_index = 3, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 154, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 154, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 63, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 83, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 91, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 99, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 6, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 103, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 243, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 250, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 263, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 287, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 154, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 481, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 154, .box_w = 4, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 597, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 611, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 621, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 627, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 629, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 631, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 700, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 723, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 735, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 797, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 808, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 816, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 842, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 881, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 903, .adv_w = 154, .box_w = 2, .box_h = 15, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 907, .adv_w = 154, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 921, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 924, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 928, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 937, .adv_w = 154, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 942, .adv_w = 154, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 947, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 958, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 960, .adv_w = 154, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 965, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 973, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 985, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 997, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1020, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1032, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1052, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1063, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1075, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1086, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1097, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1114, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1126, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1137, .adv_w = 154, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1140, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 1142, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1144, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1149, .adv_w = 154, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 1153, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 1155, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1158, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1173, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1182, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1196, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1205, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0}
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

const lv_font_t humid1_font_jetbrains_mono_normal_16 = {
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

#endif /* #if HUMID1_FONT_JETBRAINS_MONO_NORMAL_16 */
