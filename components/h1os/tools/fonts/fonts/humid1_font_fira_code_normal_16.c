/*******************************************************************************
 * Font: humid1_font_fira_code_normal_16 (fira_code normal)
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

#ifndef HUMID1_FONT_FIRA_CODE_NORMAL_16
#define HUMID1_FONT_FIRA_CODE_NORMAL_16 1
#endif

#if HUMID1_FONT_FIRA_CODE_NORMAL_16

extern const lv_font_t humid1_icon_fa7_solid_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x11) */
    0xff, 0xfc, 0x3c,
    /* U+0022 "" (5x5) */
    0xde, 0xf6, 0xb4, 0x00,
    /* U+0023 "#" (8x11) */
    0x26, 0x26, 0x7e, 0xff, 0x64, 0x64, 0x64, 0xfe, 0xec, 0x4c, 0x4c,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x7e, 0x7a, 0xd8, 0xf8, 0x78, 0x1e, 0x1e, 0x1b, 0x1b, 0xde,
    0x7c, 0x18, 0x18,
    /* U+0025 "%" (9x11) */
    0x71, 0x6d, 0xb6, 0x9b, 0xc7, 0x40, 0x40, 0x6c, 0x29, 0x34, 0x92, 0x50,
    0xe0,
    /* U+0026 "&" (8x11) */
    0x7c, 0x44, 0xc0, 0x40, 0x3f, 0x76, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (5x15) */
    0x19, 0x98, 0xcc, 0x63, 0x18, 0xc6, 0x30, 0xc6, 0x18, 0x60,
    /* U+0029 ")" (5x15) */
    0xc3, 0x18, 0x63, 0x0c, 0x63, 0x18, 0xcc, 0x66, 0x73, 0x00,
    /* U+002A "" (8x7) */
    0x18, 0x18, 0xdf, 0xfe, 0x38, 0x2c, 0x66,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x6) */
    0x7d, 0xbd, 0x80,
    /* U+002D "-" (6x2) */
    0xff, 0xf0,
    /* U+002E "." (3x3) */
    0x7d, 0x80,
    /* U+002F "/" (8x15) */
    0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60,
    0xc0, 0xc0, 0x80,
    /* U+0030 "0" (8x11) */
    0x3c, 0x66, 0xc6, 0xce, 0xcb, 0xd3, 0xd3, 0xe2, 0xe6, 0x66, 0x3c,
    /* U+0031 "1" (7x11) */
    0x31, 0xe2, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x73, 0xf8,
    /* U+0032 "2" (7x11) */
    0x7d, 0x9c, 0x18, 0x30, 0x61, 0x86, 0x18, 0x61, 0xc3, 0xf8,
    /* U+0033 "3" (7x11) */
    0x7d, 0x9c, 0x18, 0x31, 0xc7, 0x81, 0x83, 0x07, 0x9d, 0xf0,
    /* U+0034 "4" (8x11) */
    0x10, 0x30, 0x30, 0x20, 0x64, 0x44, 0xc4, 0xff, 0x0e, 0x04, 0x04,
    /* U+0035 "5" (7x11) */
    0x7e, 0xc1, 0x83, 0x07, 0xcd, 0xc1, 0x83, 0x07, 0x9d, 0xf0,
    /* U+0036 "6" (8x11) */
    0x3e, 0x60, 0x60, 0xc0, 0xfe, 0xe6, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0037 "7" (7x11) */
    0xfe, 0x0c, 0x18, 0x60, 0xc1, 0x06, 0x0c, 0x30, 0x61, 0x80,
    /* U+0038 "8" (8x11) */
    0x7c, 0x66, 0xc6, 0xc6, 0x7c, 0x7c, 0xc6, 0xc3, 0xc3, 0xe6, 0x7c,
    /* U+0039 "9" (7x11) */
    0x7d, 0xcf, 0x1e, 0x3c, 0x7d, 0xdf, 0x83, 0x0c, 0x79, 0xc0,
    /* U+003A ":" (3x8) */
    0xfd, 0x00, 0xff,
    /* U+003B ";" (3x11) */
    0xfd, 0x00, 0xfb, 0x7b, 0x00,
    /* U+003C "<" (7x8) */
    0x06, 0x39, 0xc7, 0x0e, 0x0e, 0x07, 0x03,
    /* U+003D "=" (7x6) */
    0x7f, 0xfc, 0x00, 0x0f, 0xef, 0xc0,
    /* U+003E ">" (6x8) */
    0xc1, 0xc3, 0x83, 0x0c, 0xe7, 0x30,
    /* U+003F "?" (7x11) */
    0x7d, 0xcc, 0x18, 0x31, 0xc3, 0x0c, 0x00, 0x00, 0x70, 0xe0,
    /* U+0040 "@" (9x12) */
    0x7e, 0x71, 0x80, 0x60, 0x13, 0xcb, 0x65, 0x33, 0x99, 0xcc, 0xa6, 0x5f,
    0x26, 0xf0,
    /* U+0041 "A" (9x11) */
    0x1c, 0x0e, 0x05, 0x82, 0xc3, 0x21, 0x98, 0x8c, 0xfe, 0x61, 0xa0, 0xf0,
    0x60,
    /* U+0042 "B" (8x11) */
    0xfc, 0xee, 0xc6, 0xc6, 0xfe, 0xfe, 0xc7, 0xc3, 0xc3, 0xfe, 0xfc,
    /* U+0043 "C" (8x11) */
    0x3f, 0x73, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0x73, 0x3f,
    /* U+0044 "D" (8x11) */
    0xfc, 0xce, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xce, 0xf8,
    /* U+0045 "E" (7x11) */
    0xfd, 0x83, 0x06, 0x0c, 0x1f, 0xb0, 0x60, 0xc1, 0x83, 0xf8,
    /* U+0046 "F" (7x11) */
    0xff, 0x83, 0x06, 0x0c, 0x1f, 0xb0, 0x60, 0xc1, 0x83, 0x00,
    /* U+0047 "G" (8x11) */
    0x3e, 0x62, 0xc0, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3, 0xc3, 0x63, 0x3e,
    /* U+0048 "H" (7x11) */
    0xc3, 0x87, 0x0e, 0x1f, 0xff, 0xf0, 0xe1, 0xc3, 0x87, 0x08,
    /* U+0049 "I" (7x11) */
    0xfe, 0xfc, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0xff, 0xf8,
    /* U+004A "J" (7x11) */
    0x3e, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x07, 0x9f, 0xf0,
    /* U+004B "K" (8x11) */
    0xc3, 0xc6, 0xcc, 0xdc, 0xf8, 0xf8, 0xd8, 0xcc, 0xc6, 0xc7, 0xc3,
    /* U+004C "L" (7x11) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xfb, 0xf8,
    /* U+004D "M" (9x11) */
    0x63, 0xb9, 0xdc, 0xee, 0x75, 0x7a, 0xad, 0x76, 0x9b, 0x4d, 0xe0, 0xf0,
    0x60,
    /* U+004E "N" (7x11) */
    0xe3, 0xc7, 0x8f, 0x9d, 0x3b, 0x76, 0xe5, 0xcf, 0x9f, 0x18,
    /* U+004F "O" (8x11) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0x83, 0xc3, 0xc3, 0xc2, 0x66, 0x3c,
    /* U+0050 "P" (7x11) */
    0xf9, 0x9a, 0x1c, 0x38, 0x79, 0xbe, 0x40, 0x81, 0x02, 0x00,
    /* U+0051 "Q" (8x14) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0x66, 0x3c, 0x07,
    0x03, 0x01,
    /* U+0052 "R" (8x11) */
    0xfc, 0xe6, 0xc3, 0xc3, 0xc6, 0xfe, 0xfc, 0xcc, 0xc6, 0xc6, 0xc3,
    /* U+0053 "S" (8x11) */
    0x7e, 0xe6, 0xc0, 0xc0, 0x78, 0x3e, 0x07, 0x03, 0x03, 0xc6, 0x7c,
    /* U+0054 "T" (9x11) */
    0xff, 0xbf, 0xc3, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+0055 "U" (8x11) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xe6, 0x7c,
    /* U+0056 "V" (9x11) */
    0xc1, 0xb0, 0xd8, 0x6c, 0x63, 0x31, 0x98, 0xc8, 0x2c, 0x1e, 0x0e, 0x03,
    0x00,
    /* U+0057 "W" (10x11) */
    0xc0, 0xf3, 0x2c, 0xcb, 0x36, 0x5d, 0x95, 0x65, 0x79, 0xde, 0x73, 0x1c,
    0xc7, 0x30,
    /* U+0058 "X" (8x11) */
    0xc3, 0xe6, 0x64, 0x3c, 0x38, 0x38, 0x3c, 0x6c, 0x66, 0xc6, 0xc3,
    /* U+0059 "Y" (9x11) */
    0xe1, 0xb0, 0xcc, 0xc6, 0x61, 0xe0, 0xe0, 0x30, 0x18, 0x0c, 0x06, 0x03,
    0x00,
    /* U+005A "Z" (8x11) */
    0xff, 0x7f, 0x06, 0x0c, 0x1c, 0x18, 0x30, 0x70, 0x60, 0xfe, 0xff,
    /* U+005B "[" (4x15) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,
    /* U+005C "" (8x14) */
    0x80, 0xc0, 0x40, 0x60, 0x20, 0x30, 0x10, 0x18, 0x18, 0x0c, 0x0c, 0x06,
    0x06, 0x03,
    /* U+005D "]" (5x15) */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xbd, 0xe0,
    /* U+005E "^" (6x5) */
    0x71, 0xec, 0xa3, 0x84,
    /* U+005F "_" (8x2) */
    0xfe, 0xff,
    /* U+0060 "`" (4x3) */
    0x8e, 0x30,
    /* U+0061 "a" (7x9) */
    0x38, 0xf8, 0x18, 0x37, 0xf8, 0xf1, 0xe7, 0x7a,
    /* U+0062 "b" (8x12) */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe6, 0xc3, 0xc3, 0xc3, 0xc7, 0xe6, 0xfc,
    /* U+0063 "c" (7x9) */
    0x1c, 0x7d, 0x86, 0x0c, 0x18, 0x18, 0x39, 0x3e,
    /* U+0064 "d" (7x12) */
    0x06, 0x0c, 0x19, 0xb7, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0xbb, 0xf0,
    /* U+0065 "e" (8x9) */
    0x18, 0x7e, 0x46, 0xc2, 0xff, 0xc0, 0xc0, 0x62, 0x3e,
    /* U+0066 "f" (8x12) */
    0x1f, 0x18, 0x30, 0x30, 0xfe, 0x7c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    /* U+0067 "g" (8x12) */
    0x3f, 0x7c, 0xc6, 0xc6, 0xc6, 0x7c, 0x40, 0x78, 0x7e, 0x03, 0xc3, 0xfe,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0x6f, 0xfc, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (6x13) */
    0x20, 0xc2, 0x00, 0x03, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0xfc,
    /* U+006A "j" (6x16) */
    0x08, 0x30, 0xc0, 0x3d, 0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xbc,
    /* U+006B "k" (8x12) */
    0x40, 0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf8, 0xd8, 0xcc, 0xc6, 0xc3,
    /* U+006C "l" (7x12) */
    0xf1, 0xe0, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xe0, 0xf0,
    /* U+006D "m" (8x9) */
    0x22, 0xff, 0x9b, 0x93, 0x93, 0x93, 0x93, 0x93, 0x93,
    /* U+006E "n" (7x9) */
    0x4d, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    /* U+006F "o" (8x9) */
    0x18, 0x7e, 0xc6, 0xc2, 0xc3, 0xc3, 0xc6, 0x66, 0x3c,
    /* U+0070 "p" (8x12) */
    0x5c, 0xfe, 0xe6, 0xc3, 0xc3, 0xc3, 0xc6, 0xe6, 0xfc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (7x12) */
    0x32, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0x7e, 0x0c, 0x18, 0x30,
    /* U+0072 "r" (8x9) */
    0x66, 0x6f, 0x3b, 0x32, 0x30, 0x30, 0x30, 0x70, 0xf8,
    /* U+0073 "s" (7x9) */
    0x18, 0xfd, 0x03, 0x07, 0xc1, 0xc1, 0xe3, 0x7c,
    /* U+0074 "t" (7x10) */
    0x30, 0x63, 0xf1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x3c,
    /* U+0075 "u" (7x9) */
    0x43, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0x7e,
    /* U+0076 "v" (7x8) */
    0xc3, 0x8d, 0x9b, 0x22, 0xc7, 0x8e, 0x0c,
    /* U+0077 "w" (9x8) */
    0xc0, 0xa6, 0x53, 0x6b, 0xb7, 0x5b, 0xb9, 0xcc, 0x66,
    /* U+0078 "x" (8x9) */
    0x42, 0x66, 0x6c, 0x3c, 0x38, 0x3c, 0x6c, 0x66, 0xc7,
    /* U+0079 "y" (7x11) */
    0xc3, 0x8d, 0x9b, 0x26, 0xc5, 0x8e, 0x1c, 0x18, 0x61, 0x80,
    /* U+007A "z" (7x9) */
    0x7e, 0xfc, 0x38, 0x61, 0x86, 0x1c, 0x7f, 0xfe,
    /* U+007B "{" (5x15) */
    0x39, 0x8c, 0x63, 0x19, 0xdc, 0x71, 0x8c, 0x63, 0x18, 0xe0,
    /* U+007C "|" (2x20) */
    0xbf, 0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (6x15) */
    0xe0, 0xc3, 0x0c, 0x30, 0xc3, 0x07, 0x30, 0x83, 0x0c, 0x30, 0xce, 0x00,
    /* U+007E "~" (8x3) */
    0x20, 0xf3, 0x9e,
    /* U+00B0 "" (5x5) */
    0x76, 0x63, 0x97, 0x80,
    /* U+00B1 "" (6x9) */
    0x20, 0xc3, 0x3f, 0x30, 0xc0, 0x00, 0xfc,
    /* U+00B2 "" (5x5) */
    0x78, 0xc6, 0xef, 0x80,
    /* U+00B3 "" (4x5) */
    0xf3, 0x71, 0xf0,
    /* U+00B5 "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xfb, 0xff, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (3x3) */
    0x7d, 0x80,
    /* U+00D7 "" (5x6) */
    0x8e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (6x8) */
    0x30, 0xc0, 0x3f, 0xfc, 0x03, 0x0c,
    /* U+0394 "" (9x11) */
    0x1c, 0x0f, 0x07, 0x86, 0xc3, 0x21, 0x99, 0x8c, 0xc6, 0x61, 0xbf, 0xff,
    0xe0,
    /* U+03A9 "" (8x11) */
    0x7c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0x66, 0xef,
    /* U+03B1 "" (8x9) */
    0x30, 0x7a, 0xce, 0xc6, 0xc6, 0xc6, 0xc6, 0xce, 0x7b,
    /* U+03B2 "" (8x15) */
    0x3c, 0x6e, 0xc6, 0xc6, 0xc6, 0xdc, 0xce, 0xc3, 0xc3, 0xc3, 0xe6, 0xfe,
    0xc0, 0xc0, 0xc0,
    /* U+03B3 "" (8x11) */
    0xc3, 0x62, 0x66, 0x24, 0x3c, 0x3c, 0x18, 0x18, 0x10, 0x10, 0x10,
    /* U+03B4 "" (8x12) */
    0x3c, 0x64, 0x60, 0x70, 0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x7c,
    /* U+03B5 "" (7x9) */
    0x3c, 0xfd, 0x83, 0x07, 0xdc, 0x30, 0x71, 0x7e,
    /* U+03B8 "" (8x12) */
    0x3c, 0x6e, 0x46, 0xc2, 0xc3, 0xff, 0xff, 0xc3, 0xc2, 0xc6, 0x66, 0x3c,
    /* U+03BB "" (8x12) */
    0x60, 0x70, 0x18, 0x18, 0x38, 0x3c, 0x2c, 0x6c, 0x64, 0xc6, 0xc6, 0xc3,
    /* U+03BC "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xfb, 0xff, 0xc1, 0x83, 0x00,
    /* U+03C0 "" (9x8) */
    0xff, 0x91, 0x88, 0xc4, 0x62, 0x31, 0x18, 0x8c, 0x42,
    /* U+03C3 "" (8x9) */
    0x1f, 0x7f, 0xe6, 0xc2, 0xc3, 0xc3, 0xc6, 0x66, 0x7c,
    /* U+03C4 "" (7x8) */
    0xfe, 0x60, 0xc1, 0x83, 0x06, 0x06, 0x0f,
    /* U+03C6 "" (9x12) */
    0x27, 0x37, 0xd3, 0x79, 0xbc, 0xde, 0x6d, 0x36, 0xdf, 0x3f, 0x06, 0x03,
    0x01, 0x80,
    /* U+03C9 "" (9x8) */
    0x41, 0xa0, 0xf2, 0x79, 0x9c, 0xce, 0x6d, 0xb6, 0xee,
    /* U+2013 "" (8x2) */
    0xff, 0xff,
    /* U+2014 "" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+2018 "" (3x6) */
    0x2d, 0xfe, 0x80,
    /* U+2019 "" (3x6) */
    0x7d, 0xbc, 0x80,
    /* U+201C "" (6x6) */
    0x45, 0x3c, 0xf7, 0xdc, 0x20,
    /* U+201D "" (6x5) */
    0x4b, 0x7c, 0xf2, 0x98,
    /* U+2022 "" (4x5) */
    0x4f, 0xff, 0x60,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (8x11) */
    0xe0, 0x90, 0x90, 0xe7, 0x1c, 0xe0, 0x00, 0xe7, 0x99, 0x9d, 0xe7,
    /* U+2190 "" (10x10) */
    0x0c, 0x06, 0x03, 0x81, 0xc0, 0xff, 0xdf, 0xe3, 0x00, 0x60, 0x1c, 0x02,
    0x00,
    /* U+2191 "" (10x11) */
    0x08, 0x07, 0x03, 0xe1, 0xfe, 0xcd, 0xe3, 0x20, 0xc0, 0x30, 0x0c, 0x03,
    0x00, 0xc0,
    /* U+2192 "" (9x10) */
    0x0c, 0x07, 0x01, 0x80, 0x6f, 0xfb, 0xfc, 0x0c, 0x0c, 0x0c, 0x04, 0x00,
    /* U+2193 "" (9x10) */
    0x0c, 0x06, 0x03, 0x01, 0x80, 0xc6, 0x67, 0xb6, 0xfe, 0x1e, 0x06, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 2, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 154, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 58, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 85, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 93, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 96, .adv_w = 154, .box_w = 6, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 98, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 115, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 154, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 154, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 227, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 234, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 240, .adv_w = 154, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 246, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 270, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 456, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 154, .box_w = 4, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 572, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 586, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 596, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 600, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 602, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 604, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 676, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 154, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 709, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 741, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 770, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 781, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 815, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 850, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 868, .adv_w = 154, .box_w = 2, .box_h = 20, .ofs_x = 4, .ofs_y = -5},
    {.bitmap_index = 873, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 885, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 888, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 892, .adv_w = 154, .box_w = 6, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 899, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 903, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 906, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 916, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 918, .adv_w = 154, .box_w = 5, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 922, .adv_w = 154, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 928, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 961, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 976, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 987, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 999, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1007, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1031, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1041, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1050, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1059, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1066, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1080, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1089, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1091, .adv_w = 154, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1094, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1097, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1100, .adv_w = 154, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 1105, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 1109, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 1112, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1114, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1125, .adv_w = 154, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1138, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1152, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1164, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0}
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

const lv_font_t humid1_font_fira_code_normal_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 6,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
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

#endif /* #if HUMID1_FONT_FIRA_CODE_NORMAL_16 */
