#include <windows.h>
#include <stdio.h>

#include "charmlib.h"
#include "font8x8.inl"
#include "font8x10.inl"

char* create_screen(int width_plus_one, int height, char fillchar)
{
	char* scr = new char[width_plus_one * height];
	for (int i = 0; i < height; ++i, *(scr + i * width_plus_one - 1) = '\n')
		for (int j = 0; j < width_plus_one - 1; j++)
			*(scr + i * width_plus_one + j) = fillchar;
	*(scr + height * width_plus_one - 1) = 0;
	return scr;
}

void delete_screen(char* screen)
{
	delete screen;
}

void print_screen(char* screen)
{
	gotoxy(0, 0);
	printf("%s", screen);
}

inline void pixel(void* screen, int scr_width, int x, int y, char pixel)
{
	*((char*)screen + y * scr_width + x) = pixel;
}

/* вывод символа с контролем границ */
inline void pixel_cb(void* screen, int scr_width, int x, int y, int max_x, int max_y, char pixel)
{
	if (x>=0 && x<=max_x && y>=0 && y<=max_y)
		*((char*)screen + y * scr_width + x) = pixel;
}

/*inline*/ void pixel2(void* screen, int scr_width, int x, int big_y, bool bit)
{
	const int map[2][2][4] = {
		{{ 32, 220, 220, 32 },
		{ 223, 219, 219, 223 }},
		{{ 32, 223, 32, 223 },
		{ 220, 219, 220, 219 }} };

	// 	zbuf[y/2][x] = map[ y&1 ][ bit ][ (zbuf[y/2][x]>>1)&3 ];
	*((char*)screen + (big_y/2) * scr_width  + x) = (char)map[big_y & 1][bit][(*((char*)screen + (big_y / 2) * scr_width + x) >> 1) & 3];
}

/*inline*/ void pixel2_cb(void* screen, int scr_width, int x, int big_y, int max_x, int big_max_y, bool bit)
{
	if (x >= 0 && x <= max_x && big_y >= 0 && big_y <= big_max_y)
		pixel2(screen, scr_width, x, big_y, bit);
}

void drawfilledrectangle(void* screen, int scr_width, int x1, int y1, int x2, int y2, char fillchar)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			*((char*)screen + y * scr_width + x) = fillchar;
}

inline void _drawrectangle(void* screen, int scr_width, int x1, int y1, int x2, int y2, char fillchar)
{
	for (int x = x1; x <= x2; x++)
		pixel(screen, scr_width, x, y1, fillchar),
		pixel(screen, scr_width, x, y2, fillchar);
	for (int y = y1+1; y < y2; y++)
		pixel(screen, scr_width, x1, y, fillchar),
		pixel(screen, scr_width, x2, y, fillchar);
}

inline void _drawrectangle_cb(void* screen, int scr_width, int x1, int y1, int x2, int y2, int max_x, int max_y, char fillchar)
{
	for (int x = x1; x <= x2; x++)
		pixel_cb(screen, scr_width, x, y1, max_x, max_y, fillchar),
		pixel_cb(screen, scr_width, x, y2, max_x, max_y, fillchar);
	for (int y = y1 + 1; y < y2; y++)
		pixel_cb(screen, scr_width, x1, y, max_x, max_y, fillchar),
		pixel_cb(screen, scr_width, x2, y, max_x, max_y, fillchar);
}

void drawrectangle(void* screen, int scr_width, int x1, int y1, int x2, int y2, int max_x, int max_y, char fillchar)
{
	int x = min(x1, x2);
	int y = min(y1, y2);
	int x3 = max(x1, x2);
	int y3 = max(y1, y2);

	if (x < 0 || y < 0 || x3 > max_x || y3 > max_y)
		_drawrectangle_cb(screen, scr_width, x1, y1, x2, y2, max_x, max_y, fillchar);
	else
		_drawrectangle(screen, scr_width, x1, y1, x2, y2, fillchar);
}

inline void _drawchar8x8(void* screen, int scr_width, char chr, int x, int y, char pen, char background, int thickness)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((font8x8[(unsigned char)chr][i] & (1 << (7 - j))) != 0)
				for (int ii = 0; ii < thickness; ii++)
					for (int jj = 0; jj < thickness; jj++)
						pixel2(screen, scr_width, x + j * thickness + jj, y + i * thickness + ii, pen);
			else if (background != 0)
				for (int ii = 0; ii < thickness; ii++)
					for (int jj = 0; jj < thickness; jj++)
						pixel2(screen, scr_width, x + j * thickness + jj, y + i * thickness + ii, background);
}

inline void _drawchar8x8_cb(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen, char background, int thickness)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((font8x8[(unsigned char)chr][i] & (1 << (7 - j))) != 0)
				for (int ii = 0; ii < thickness && (y + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x + j * thickness + jj) <= max_x; jj++)
						pixel2_cb(screen, scr_width, x + j * thickness + jj, y + i * thickness + ii, max_x, max_y, pen);
			else if (background != 0)
				for (int ii = 0; ii < thickness && (y + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x + j * thickness + jj) <= max_x; jj++)
						pixel2_cb(screen, scr_width, x + j * thickness + jj, y + i * thickness + ii, max_x, max_y, background);
}

void drawchar8x8(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen, char background, int thickness)
{
	if (chr <= 0 || x + 8 * thickness < 0 || y + 8 * thickness < 0 || x > max_x || y > max_y) return;
	if (x < 0 || y < 0 || x + 8 * thickness > max_x || y + 8 * thickness > max_y)
		_drawchar8x8_cb(screen, scr_width, chr, x, y, max_x, max_y, pen, background, thickness);
	else
		_drawchar8x8(screen, scr_width, chr, x, y, pen, background, thickness);
}

void drawtext8x8(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen, char background, int thickness)
{
	if (*text == 0) return;
	drawchar8x8(screen, scr_width, *text++, x, y, max_x, max_y, pen, background, thickness);
	x += 8 * thickness;
	for (int dx = 0; *text && (x + dx <= max_x); dx += 8 * thickness)
		drawchar8x8(screen, scr_width, *text++, x + dx, y, max_x, max_y, pen, background, thickness);
}

void drawchar8x8_shifted(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	if (chr <= 0) return;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((font8x8[(unsigned char)chr][i] & (1 << (7 - j))) != 0)
			{
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= max_x; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							pixel2_cb(screen, scr_width, x - shiftleft + j * thickness + jj, y - shiftup + i * thickness + ii, max_x, max_y, pen);
			}
			else if (background != 0)
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= max_x; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							pixel2_cb(screen, scr_width, x - shiftleft + j * thickness + jj, y - shiftup + i * thickness + ii, max_x, max_y, background);
}

void drawtext8x8_shifted(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	if (*text == 0) return;
	drawchar8x8_shifted(screen, scr_width, *text++, x, y, max_x, max_y, pen, background, thickness, shiftleft, shiftup);
	x += 8*thickness - shiftleft;
	for (int dx = 0; *text && (x + dx <= max_x); dx += 8*thickness)
		drawchar8x8_shifted(screen, scr_width, *text++, x + dx, y, max_x, max_y, pen, background, thickness, 0, shiftup);
}

void drawchar8x10(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 8; j++)
			if ((font8x10[i][(unsigned char)chr] & (1 << (7 - j))) != 0)
			{
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= max_x; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							*((char*)screen + (y - shiftup + i * thickness + ii) * scr_width + x - shiftleft + j * thickness + jj) = pen;
			}
			else if (background != 0)
			{
				for (int ii = 0; ii < thickness && (y - shiftup + i * thickness + ii) <= max_y; ii++)
					for (int jj = 0; jj < thickness && (x - shiftleft + j * thickness + jj) <= max_x; jj++)
						if (i * thickness + ii >= shiftup && j * thickness + jj >= shiftleft)
							*((char*)screen + (y - shiftup + i * thickness + ii) * scr_width + x - shiftleft + j * thickness + jj) = background;
			}
}

void drawtext8x10(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen, char background, int thickness, int shiftleft, int shiftup)
{
	if (*text == 0) return;
	drawchar8x10(screen, scr_width, *text++, x, y, max_x, max_y, pen, background, thickness, shiftleft, shiftup);
	x += 8 * thickness - shiftleft;
	for (int dx = 0; *text && (x + dx <= max_x); dx += 8 * thickness)
		drawchar8x10(screen, scr_width, *text++, x + dx, y, max_x, max_y, pen, background, thickness, 0, shiftup);
}

int mystrlen(const char* str)
{
	int i = 0; for (; str[i]; i++); return i;
}

void printfxy(void* screen, int scr_width, int x, int y, const char* fmt, ...)
{
	char* buf = new char[mystrlen(fmt) * 4];

	va_list args;
	va_start(args, fmt);
	int len = _vscprintf(fmt, args) + 1;
	vsprintf_s(buf, len, fmt, args);
	va_end(args);

	char* dest = (char*)screen + y * scr_width + x;
	for (; *buf != 0 && *dest != 0;)
		if (*dest == '\n') dest++;
		else *dest++ = *buf++;	
}

// -----------------------------------------------------------------------
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void cursor_off()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void sleep(int milliseconds)
{
	Sleep(milliseconds);
}