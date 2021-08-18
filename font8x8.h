#define FONTNAME() 8x8
#define FONTWIDTH 8
#define FONTHIGHT 8
#define FONTRANGE 128
#define FONTPIXEL(chr,i,j) ((font8x8[(unsigned char)(chr)][(i)] & (1 << (7 - (j)))) != 0)

/*****************************************************************************
 Ascii 8 by 8 regular font - only first 128 characters are supported.
*****************************************************************************/

/*
 * Each array entry holds the bits for 8 horizontal scan lines, topmost
 * first.  The most significant bit of each constant is the leftmost bit of
 * the scan line.
 */

//const unsigned char font8x8[][8];
