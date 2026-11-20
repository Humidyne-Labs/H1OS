/*******************************************************************************
 * Font: humid1_font_terminus_normal_20 (terminus normal)
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

#ifndef HUMID1_FONT_TERMINUS_NORMAL_20
#define HUMID1_FONT_TERMINUS_NORMAL_20 1
#endif

#if HUMID1_FONT_TERMINUS_NORMAL_20

extern const lv_font_t humid1_icon_fa7_solid_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (1x13) */
    0xff, 0x98,
    /* U+0022 "" (5x4) */
    0x8c, 0x63, 0x10,
    /* U+0023 "#" (7x13) */
    0x44, 0x89, 0x12, 0x2f, 0xe8, 0x91, 0x22, 0xfe, 0x89, 0x12, 0x24, 0x40,
    /* U+0024 "$" (7x15) */
    0x10, 0x21, 0xf4, 0x99, 0x12, 0x24, 0x3e, 0x12, 0x24, 0x4c, 0x97, 0xc2,
    0x04, 0x00,
    /* U+0025 "%" (8x12) */
    0xe2, 0xa2, 0xe4, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x27, 0x45, 0x47,
    /* U+0026 "&" (8x13) */
    0x38, 0x44, 0x44, 0x44, 0x28, 0x10, 0x29, 0x45, 0x82, 0x82, 0x82, 0x45,
    0x39,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (3x13) */
    0x29, 0x49, 0x24, 0x91, 0x22,
    /* U+0029 ")" (3x13) */
    0x89, 0x12, 0x49, 0x25, 0x28,
    /* U+002A "" (7x7) */
    0x44, 0x50, 0x47, 0xf1, 0x05, 0x11, 0x00,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00,
    /* U+002C "," (2x4) */
    0x56,
    /* U+002D "-" (7x1) */
    0xfe,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (6x12) */
    0x04, 0x10, 0x82, 0x10, 0x42, 0x08, 0x41, 0x08, 0x20,
    /* U+0030 "0" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x71, 0x64, 0xd1, 0xc3, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0031 "1" (5x13) */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x21, 0x08, 0x4f, 0x80,
    /* U+0032 "2" (7x13) */
    0x7d, 0x06, 0x0c, 0x10, 0x20, 0x41, 0x04, 0x10, 0x41, 0x04, 0x0f, 0xe0,
    /* U+0033 "3" (7x13) */
    0x7d, 0x06, 0x08, 0x10, 0x20, 0x4f, 0x01, 0x02, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0034 "4" (7x13) */
    0x02, 0x0c, 0x28, 0x92, 0x28, 0x60, 0xc1, 0x83, 0xfc, 0x08, 0x10, 0x20,
    /* U+0035 "5" (7x13) */
    0xff, 0x02, 0x04, 0x08, 0x1f, 0x80, 0x81, 0x02, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0036 "6" (7x13) */
    0x3c, 0x82, 0x04, 0x08, 0x1f, 0xa0, 0xc1, 0x83, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0037 "7" (7x13) */
    0xff, 0x06, 0x08, 0x10, 0x40, 0x82, 0x04, 0x10, 0x20, 0x40, 0x81, 0x00,
    /* U+0038 "8" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x5f, 0x41, 0x83, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0039 "9" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xbf, 0x02, 0x04, 0x08, 0x27, 0x80,
    /* U+003A ":" (1x8) */
    0xc3,
    /* U+003B ";" (2x10) */
    0x50, 0x05, 0x60,
    /* U+003C "<" (7x13) */
    0x02, 0x08, 0x20, 0x82, 0x08, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    /* U+003D "=" (7x5) */
    0xfe, 0x00, 0x00, 0x0f, 0xe0,
    /* U+003E ">" (7x13) */
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x82, 0x08, 0x20, 0x82, 0x08, 0x00,
    /* U+003F "?" (7x13) */
    0x38, 0x8a, 0x0c, 0x10, 0x20, 0x82, 0x08, 0x10, 0x00, 0x00, 0x81, 0x00,
    /* U+0040 "@" (8x13) */
    0x7e, 0x81, 0x81, 0x8f, 0x91, 0x91, 0x91, 0x91, 0x93, 0x8d, 0x80, 0x80,
    0x7f,
    /* U+0041 "A" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x20,
    /* U+0042 "B" (7x13) */
    0xfd, 0x06, 0x0c, 0x18, 0x3f, 0xa0, 0xc1, 0x83, 0x06, 0x0c, 0x1f, 0xc0,
    /* U+0043 "C" (7x13) */
    0x7d, 0x06, 0x0c, 0x08, 0x10, 0x20, 0x40, 0x81, 0x02, 0x0c, 0x17, 0xc0,
    /* U+0044 "D" (7x13) */
    0xf9, 0x0a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x2f, 0x80,
    /* U+0045 "E" (7x13) */
    0xff, 0x02, 0x04, 0x08, 0x10, 0x3e, 0x40, 0x81, 0x02, 0x04, 0x0f, 0xe0,
    /* U+0046 "F" (7x13) */
    0xff, 0x02, 0x04, 0x08, 0x10, 0x3e, 0x40, 0x81, 0x02, 0x04, 0x08, 0x00,
    /* U+0047 "G" (7x13) */
    0x7d, 0x06, 0x0c, 0x08, 0x10, 0x27, 0xc1, 0x83, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0048 "H" (7x13) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x20,
    /* U+0049 "I" (3x13) */
    0xe9, 0x24, 0x92, 0x49, 0x2e,
    /* U+004A "J" (7x13) */
    0x0e, 0x08, 0x10, 0x20, 0x40, 0x81, 0x02, 0x05, 0x0a, 0x14, 0x27, 0x80,
    /* U+004B "K" (7x13) */
    0x83, 0x06, 0x14, 0x49, 0x14, 0x30, 0x50, 0x91, 0x12, 0x14, 0x18, 0x20,
    /* U+004C "L" (7x13) */
    0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x02, 0x04, 0x0f, 0xe0,
    /* U+004D "M" (8x13) */
    0x81, 0xc3, 0xa5, 0xa5, 0x99, 0x99, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x81,
    /* U+004E "N" (7x13) */
    0x83, 0x06, 0x0c, 0x1c, 0x34, 0x64, 0xc5, 0x87, 0x06, 0x0c, 0x18, 0x20,
    /* U+004F "O" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0050 "P" (7x13) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x40, 0x81, 0x02, 0x04, 0x08, 0x00,
    /* U+0051 "Q" (7x15) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x97, 0xc0,
    0x80, 0x80,
    /* U+0052 "R" (7x13) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x7f, 0x60, 0xa1, 0x22, 0x24, 0x28, 0x20,
    /* U+0053 "S" (7x13) */
    0x7d, 0x06, 0x0c, 0x08, 0x10, 0x1f, 0x01, 0x02, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0054 "T" (7x13) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x00,
    /* U+0055 "U" (7x13) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x17, 0xc0,
    /* U+0056 "V" (7x13) */
    0x83, 0x06, 0x0c, 0x14, 0x48, 0x91, 0x22, 0x28, 0x50, 0xa0, 0x81, 0x00,
    /* U+0057 "W" (8x13) */
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x99, 0x99, 0xa5, 0xa5, 0xc3,
    0x81,
    /* U+0058 "X" (7x13) */
    0x83, 0x05, 0x12, 0x22, 0x85, 0x04, 0x14, 0x28, 0x89, 0x14, 0x18, 0x20,
    /* U+0059 "Y" (7x13) */
    0x83, 0x05, 0x12, 0x22, 0x85, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x00,
    /* U+005A "Z" (7x13) */
    0xfe, 0x04, 0x08, 0x10, 0x41, 0x04, 0x10, 0x41, 0x02, 0x04, 0x0f, 0xe0,
    /* U+005B "[" (3x13) */
    0xf2, 0x49, 0x24, 0x92, 0x4e,
    /* U+005C "" (6x12) */
    0x82, 0x04, 0x10, 0x20, 0x81, 0x04, 0x08, 0x20, 0x41,
    /* U+005D "]" (3x13) */
    0xe4, 0x92, 0x49, 0x24, 0x9e,
    /* U+005E "^" (7x4) */
    0x10, 0x51, 0x14, 0x10,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0x88, 0x80,
    /* U+0061 "a" (7x9) */
    0x7c, 0x04, 0x0b, 0xf8, 0x30, 0x60, 0xc1, 0x7e,
    /* U+0062 "b" (7x13) */
    0x81, 0x02, 0x04, 0x0f, 0xd0, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x1f, 0xc0,
    /* U+0063 "c" (7x9) */
    0x7d, 0x06, 0x04, 0x08, 0x10, 0x20, 0x41, 0x7c,
    /* U+0064 "d" (7x13) */
    0x02, 0x04, 0x08, 0x17, 0xf0, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x17, 0xe0,
    /* U+0065 "e" (7x9) */
    0x7d, 0x06, 0x0c, 0x1f, 0xf0, 0x20, 0x41, 0x7c,
    /* U+0066 "f" (6x13) */
    0x1c, 0x82, 0x08, 0xf8, 0x82, 0x08, 0x20, 0x82, 0x08, 0x20,
    /* U+0067 "g" (7x12) */
    0x7f, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x7e, 0x04, 0x0b, 0xe0,
    /* U+0068 "h" (7x13) */
    0x81, 0x02, 0x04, 0x0f, 0xd0, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x20,
    /* U+0069 "i" (3x13) */
    0x48, 0x0c, 0x92, 0x49, 0x2e,
    /* U+006A "j" (5x16) */
    0x08, 0x40, 0x01, 0x84, 0x21, 0x08, 0x42, 0x10, 0xc6, 0x2e,
    /* U+006B "k" (7x13) */
    0x81, 0x02, 0x04, 0x08, 0x30, 0xa2, 0x48, 0xe1, 0x22, 0x24, 0x28, 0x20,
    /* U+006C "l" (3x13) */
    0xc9, 0x24, 0x92, 0x49, 0x2e,
    /* U+006D "m" (7x9) */
    0xfd, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x92,
    /* U+006E "n" (7x9) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82,
    /* U+006F "o" (7x9) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x7c,
    /* U+0070 "p" (7x12) */
    0xfd, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xfd, 0x02, 0x04, 0x00,
    /* U+0071 "q" (7x12) */
    0x7f, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x7e, 0x04, 0x08, 0x10,
    /* U+0072 "r" (7x9) */
    0x9f, 0x43, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
    /* U+0073 "s" (7x9) */
    0x7d, 0x06, 0x04, 0x07, 0xc0, 0x40, 0xc1, 0x7c,
    /* U+0074 "t" (6x13) */
    0x20, 0x82, 0x08, 0xf8, 0x82, 0x08, 0x20, 0x82, 0x08, 0x1c,
    /* U+0075 "u" (7x9) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x7e,
    /* U+0076 "v" (7x9) */
    0x83, 0x06, 0x0a, 0x24, 0x45, 0x0a, 0x08, 0x10,
    /* U+0077 "w" (7x9) */
    0x83, 0x06, 0x0c, 0x99, 0x32, 0x64, 0xc9, 0x7c,
    /* U+0078 "x" (7x9) */
    0x83, 0x05, 0x11, 0x41, 0x05, 0x11, 0x41, 0x82,
    /* U+0079 "y" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x7e, 0x04, 0x0b, 0xe0,
    /* U+007A "z" (7x9) */
    0xfe, 0x04, 0x10, 0x41, 0x04, 0x10, 0x40, 0xfe,
    /* U+007B "{" (5x13) */
    0x19, 0x08, 0x42, 0x13, 0x04, 0x21, 0x08, 0x41, 0x80,
    /* U+007C "|" (1x13) */
    0xff, 0xf8,
    /* U+007D "}" (5x13) */
    0xc1, 0x08, 0x42, 0x10, 0x64, 0x21, 0x08, 0x4c, 0x00,
    /* U+007E "~" (7x4) */
    0x63, 0x26, 0x4c, 0x60,
    /* U+00B0 "" (5x5) */
    0x74, 0x63, 0x17, 0x00,
    /* U+00B1 "" (7x10) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00, 0x01, 0xfc,
    /* U+00B2 "" (5x7) */
    0x74, 0x62, 0x22, 0x23, 0xe0,
    /* U+00B3 "" (5x7) */
    0x74, 0x42, 0x60, 0xc5, 0xc0,
    /* U+00B5 "" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc3, 0xfb, 0x02, 0x04, 0x00,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (7x7) */
    0x82, 0x88, 0xa0, 0x82, 0x88, 0xa0, 0x80,
    /* U+00F7 "" (7x9) */
    0x10, 0x20, 0x00, 0x0f, 0xe0, 0x00, 0x08, 0x10,
    /* U+0394 "" (7x13) */
    0x10, 0x20, 0x41, 0x42, 0x85, 0x11, 0x22, 0x45, 0x06, 0x0c, 0x1f, 0xe0,
    /* U+03A9 "" (7x13) */
    0x7d, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82, 0x88, 0xa1, 0x4e, 0xe0,
    /* U+03B1 "" (8x9) */
    0x7b, 0x86, 0x84, 0x84, 0x84, 0x84, 0x84, 0x86, 0x7b,
    /* U+03B2 "" (7x16) */
    0x79, 0x0a, 0x14, 0x28, 0x9f, 0xa0, 0xc1, 0x83, 0x06, 0x0c, 0x1f, 0xd0,
    0x20, 0x40,
    /* U+03B3 "" (7x12) */
    0x83, 0x06, 0x0a, 0x24, 0x48, 0x8a, 0x14, 0x10, 0x20, 0x40, 0x80,
    /* U+03B4 "" (7x13) */
    0x7c, 0x40, 0x40, 0x43, 0xc8, 0xe0, 0xc1, 0x83, 0x06, 0x0a, 0x23, 0x80,
    /* U+03B5 "" (7x9) */
    0x7d, 0x06, 0x04, 0x07, 0x90, 0x20, 0x41, 0x7c,
    /* U+03B8 "" (6x13) */
    0x7a, 0x18, 0x61, 0x86, 0x1f, 0xe1, 0x86, 0x18, 0x61, 0x78,
    /* U+03BB "" (7x13) */
    0x20, 0x40, 0x40, 0x81, 0x05, 0x0a, 0x22, 0x44, 0x8a, 0x0c, 0x18, 0x20,
    /* U+03BC "" (7x12) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc3, 0xfb, 0x02, 0x04, 0x00,
    /* U+03C0 "" (7x9) */
    0xff, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82,
    /* U+03C3 "" (8x9) */
    0x3f, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38,
    /* U+03C4 "" (7x9) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x0c,
    /* U+03C6 "" (7x12) */
    0x4d, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x7c, 0x20, 0x40, 0x80,
    /* U+03C9 "" (7x9) */
    0x45, 0x06, 0x0c, 0x99, 0x32, 0x64, 0xc9, 0x6c,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (2x4) */
    0x6a,
    /* U+2019 "" (2x4) */
    0x56,
    /* U+201C "" (6x4) */
    0x46, 0x28, 0xa2,
    /* U+201D "" (6x4) */
    0x45, 0x14, 0x62,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (7x2) */
    0x93, 0x24,
    /* U+2030 "" (10x12) */
    0xe4, 0x29, 0x0e, 0x80, 0x20, 0x10, 0x04, 0x02, 0x00, 0x80, 0x40, 0x17,
    0x79, 0x56, 0x77,
    /* U+2190 "" (9x7) */
    0x10, 0x10, 0x10, 0x1f, 0xf4, 0x01, 0x00, 0x40,
    /* U+2191 "" (7x13) */
    0x10, 0x71, 0x54, 0x91, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x81, 0x00,
    /* U+2192 "" (9x7) */
    0x04, 0x01, 0x00, 0x5f, 0xf0, 0x10, 0x10, 0x10,
    /* U+2193 "" (7x13) */
    0x10, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x11, 0x25, 0x51, 0xc1, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 160, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 160, .box_w = 1, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 160, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 5, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 160, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 31, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 160, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 11},
    {.bitmap_index = 57, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 160, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 74, .adv_w = 160, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 81, .adv_w = 160, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 160, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 83, .adv_w = 160, .box_w = 1, .box_h = 2, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 160, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 160, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 160, .box_w = 1, .box_h = 8, .ofs_x = 4, .ofs_y = 1},
    {.bitmap_index = 211, .adv_w = 160, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 214, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 160, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 231, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 160, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 468, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 160, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 160, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 600, .adv_w = 160, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 601, .adv_w = 160, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 13},
    {.bitmap_index = 603, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 672, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 160, .box_w = 5, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 699, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 160, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 751, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 762, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 831, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 160, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 160, .box_w = 1, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 850, .adv_w = 160, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 160, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 863, .adv_w = 160, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 867, .adv_w = 160, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 160, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 881, .adv_w = 160, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 886, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 897, .adv_w = 160, .box_w = 1, .box_h = 2, .ofs_x = 4, .ofs_y = 5},
    {.bitmap_index = 898, .adv_w = 160, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 905, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 913, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 925, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 937, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 160, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 960, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 971, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 160, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1001, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1013, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1024, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1032, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1041, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 160, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1060, .adv_w = 160, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1068, .adv_w = 160, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1069, .adv_w = 160, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1070, .adv_w = 160, .box_w = 2, .box_h = 4, .ofs_x = 4, .ofs_y = 11},
    {.bitmap_index = 1071, .adv_w = 160, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 11},
    {.bitmap_index = 1072, .adv_w = 160, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 1075, .adv_w = 160, .box_w = 6, .box_h = 4, .ofs_x = 2, .ofs_y = 11},
    {.bitmap_index = 1078, .adv_w = 160, .box_w = 4, .box_h = 4, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 1080, .adv_w = 160, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1082, .adv_w = 160, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1097, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1105, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1117, .adv_w = 160, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1125, .adv_w = 160, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_terminus_normal_20 = {
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

#endif /* #if HUMID1_FONT_TERMINUS_NORMAL_20 */
