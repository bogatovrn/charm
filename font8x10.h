#define FONTNAME() 8x10
#define FONTWIDTH 8
#define FONTHIGHT 10
#define FONTRANGE 256
#define FONTPIXEL(chr,i,j) ((font8x10[i][(unsigned char)(chr)] & (1 << (7 - (j)))) != 0)

//Font 8x10, Codepage Windows-1251
//const unsigned char font8x10[10][256];
