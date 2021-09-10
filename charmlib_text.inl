// перед включением этого файла должны быть определены
// функции вывода точки PIXEL и PIXEL_CB, например:

//#define PIXEL pixel_2
//#define PIXEL_CB pixel_cb_2

// и соответствующий POSTFIX, дл€ приведЄнного примера:
//#define POSTFIX _2

// перед включением этого файла должен быть включЄн файл шрифта
// с объ€влением массива с растром, констант FONTNAME(), FONTWIDTH, FONTHIGHT, FONTRANGE, булевского макроса FONTPIXEL(chr,i,j):

//#define FONTNAME() 8x10
//#define FONTWIDTH 8
//#define FONTHIGHT 10
//#define FONTRANGE 256
//#define FONTPIXEL(chr,i,j) ((font8x10[i][(unsigned char)(chr)] & (1 << (7 - (j)))) != 0)

#define CONCAT3(x,y) x##y
#define CONCAT2(x,y) CONCAT3(x,y)
#define CONCAT(x,y,z) CONCAT2(x,CONCAT2(y,z))

#define DRAWCHAR CONCAT(drawchar,FONTNAME(),POSTFIX)
#define _DRAWCHAR CONCAT2(_,DRAWCHAR)
#define _DRAWCHAR_CB CONCAT2(_DRAWCHAR,_cb)
#define DRAWCHAR_SHIFTED CONCAT2(DRAWCHAR,_shifted)

#define DRAWTEXT CONCAT(drawtext,FONTNAME(),POSTFIX)
#define DRAWTEXT_SHIFTED CONCAT2(DRAWTEXT,_shifted)

// -----------------------------------------------------------------------
inline void _DRAWCHAR(char chr, int x, int y, char pen, char background, int thickness)
{
	for (int i = 0; i < FONTHIGHT; i++)
		for (int j = 0; j < FONTWIDTH; j++)
			if (FONTPIXEL(chr, i,j))
				for (int ii = 0; ii < thickness; ii++)
					for (int jj = 0; jj < thickness; jj++)
						PIXEL(x + j * thickness + jj, y + i * thickness + ii, pen);
			else if (background != 0)
				for (int ii = 0; ii < thickness; ii++)
					for (int jj = 0; jj < thickness; jj++)
						PIXEL(x + j * thickness + jj, y + i * thickness + ii, background);
}
inline void _DRAWCHAR_CB(char chr, int x, int y, char pen, char background, int thickness)
{
	for (int i = 0; i < FONTHIGHT; i++)
		for (int j = 0; j < FONTWIDTH; j++)
			if (FONTPIXEL(chr, i, j))
				for (int ii = 0; ii < thickness && (y + i * thickness + ii) <= CMAX_Y; ii++)
					for (int jj = 0; jj < thickness && (x + j * thickness + jj) <= CMAX_X; jj++)
						PIXEL_CB(x + j * thickness + jj, y + i * thickness + ii, pen);
			else if (background != 0)
				for (int ii = 0; ii < thickness && (y + i * thickness + ii) <= CMAX_Y; ii++)
					for (int jj = 0; jj < thickness && (x + j * thickness + jj) <= CMAX_X; jj++)
						PIXEL_CB(x + j * thickness + jj, y + i * thickness + ii, background);
}
/* символ, начина€ с верхнего левого угла (x, y) */
void DRAWCHAR(char chr, int x, int y, char pen, char background, int thickness)
{
	if ((unsigned int)chr >= FONTRANGE) return;
	if (chr <= 0 || x + FONTWIDTH * thickness < 0 || y + FONTHIGHT * thickness < 0 || x > CMAX_X || y > CMAX_Y) return;
	if (x < 0 || y < 0 || x + FONTWIDTH * thickness > CMAX_X || y + FONTHIGHT * thickness > CMAX_Y)
		_DRAWCHAR_CB(chr, x, y, pen, background, thickness);
	else
		_DRAWCHAR(chr, x, y, pen, background, thickness);
}

/* частичное (сдвинутое влево-вверх) изображение символа */
void DRAWCHAR_SHIFTED(char chr, int x, int y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	if ((unsigned char)chr >= FONTRANGE) return;

	for (int i = 0; i < FONTHIGHT; i++)
		for (int j = 0; j < FONTWIDTH; j++)
			if (FONTPIXEL(chr, i, j))
			{
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= CMAX_Y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= CMAX_X; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							PIXEL_CB(x - shiftleft + j * thickness + jj, y - shiftup + i * thickness + ii, pen);
			}
			else if (background != 0)
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= CMAX_Y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= CMAX_X; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							PIXEL_CB(x - shiftleft + j * thickness + jj, y - shiftup + i * thickness + ii, background);
}

/* текст с помощью drawchar() */
void DRAWTEXT(const char* text, int x, int y, char pen, char background, int thickness)
{
	if (*text == 0) return;
	DRAWCHAR(*text++, x, y, pen, background, thickness);
	x += FONTWIDTH * thickness;
	for (int dx = 0; *text && (x + dx <= CMAX_X); dx += FONTWIDTH * thickness)
		DRAWCHAR(*text++, x + dx, y, pen, background, thickness);
}

/* текст с помощью drawchar_shifted() */
void DRAWTEXT_SHIFTED(const char* text, int x, int y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	if (*text == 0) return;
	DRAWCHAR_SHIFTED(*text++, x, y, pen, background, thickness, shiftleft, shiftup);
	x += FONTWIDTH * thickness - shiftleft;
	for (int dx = 0; *text && (x + dx <= CMAX_X); dx += FONTWIDTH * thickness)
		DRAWCHAR_SHIFTED(*text++, x + dx, y, pen, background, thickness, 0, shiftup);
}

#undef FONTNAME
#undef FONTWIDTH
#undef FONTHIGHT
#undef FONTRANGE
#undef FONTPIXEL
#undef PIXEL
#undef PIXEL_CB

#undef CONCAT3
#undef CONCAT2
#undef CONCAT

#undef DRAWCHAR
#undef _DRAWCHAR
#undef _DRAWCHAR_CB
#undef DRAWCHAR_SHIFTED

#undef DRAWTEXT
#undef DRAWTEXT_SHIFTED

#undef POSTFIX
