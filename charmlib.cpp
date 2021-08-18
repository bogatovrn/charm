#include <windows.h>
#include <stdio.h>

#include "charmlib.h"

/* максимальное значение X */
int CMAX_X;
/* максимальное значение Y */
int CMAX_Y;
/* внутренн€€ ширина буфера = CMAX_Y+2 */
int CSCR_WIDTH;
/* указатель на текущий буфер вывода */
char *CSCR_PTR;

/* видимый диапазон значений z */
int CMINZ, CMAXZ;

const char CPALETTE_2[] = { 32, 250, 176, 177, 178, 219 };

/* палитра символов дл€ pixel3d */
const char* CPALETTE = CPALETTE_2;

/* количество символов в палитре CPALETTE */
int CPALETTE_LEN = 6;

inline int mystrlen(const char* str); // пока что нужна только дл€ printfxy() и setpalette()

void setmaxxy(int max_x, int max_y)
{
	CMAX_X = max_x;
	CMAX_Y = max_y;
}

char* create_screen(int width_plus_one, int height, char fillchar)
{
	char* scr = new char[width_plus_one * height];
	for (int i = 0; i < height; ++i, *(scr + i * width_plus_one - 1) = '\n')
		for (int j = 0; j < width_plus_one - 1; j++)
			*(scr + i * width_plus_one + j) = fillchar;
	*(scr + height * width_plus_one - 1) = 0;

	return scr;
}

void setcurrentscreen(char* screen, int width_plus_one)
{
	CSCR_PTR = screen;
	CSCR_WIDTH = width_plus_one;
}

void delete_screen(char* screen)
{
	delete screen;
}

void print_current_screen()
{
	gotoxy(0, 0);
	printf("%s", CSCR_PTR);
}

/* вывод символа без контрол€ границ */
inline void pixel(int x, int y, char pixel)
{
	*(CSCR_PTR + y * CSCR_WIDTH + x) = pixel;
}

/* вывод символа с контролем границ */
inline void pixel_cb(int x, int y, char pixel)
{
	if (x>=0 && x<=CMAX_X && y>=0 && y<=CMAX_Y)
		*(CSCR_PTR + y * CSCR_WIDTH + x) = pixel;
}

/* ч/б точка в полсимвола без контрол€ границ */
inline void pixel_2(int x, int big_y, char pixel)
{
	byte prev = (byte)*(CSCR_PTR + (big_y / 2) * CSCR_WIDTH + x);
	if (prev < 219 || prev > 223 || prev == 221 || prev == 222) prev = 32;

	const int map[2][2][4] = {
		{{ 32, 220, 220, 32 },
		{ 223, 219, 219, 223 }},
		{{ 32, 223, 32, 223 },
		{ 220, 219, 220, 219 }} };

	int bit = !(pixel == 32);
	*(CSCR_PTR + (big_y / 2) * CSCR_WIDTH + x) = (char)map[big_y & 1][bit][(prev >> 1) & 3];
}

/* ч/б точка в полсимвола с контролем границ */
inline void pixel_cb_2(int x, int big_y, char pixel)
{
	if (x >= 0 && x <= CMAX_X && big_y >= 0 && big_y <= CMAX_Y)
		pixel_2(x, big_y, pixel);
}

/* точка с заданной интенсивностью k = 0..1.0F, использу€ setpalette() */
inline void pixel(int x, int y, float k)
{
	pixel(x, y, CPALETTE[ (int)(k * (CPALETTE_LEN - 1)) ]);
}

/* точка с заданной интенсивностью, контроль границ */
inline void pixel_cb(int x, int y, float k)
{
	if (x >= 0 && x <= CMAX_X && y >= 0 && y <= CMAX_Y)
		pixel(x, y, k);
}

/* 3d-точка на основе setdepth3d() и setpalette() */
inline void pixel3d(int x, int y, int z)
{
	int i = CPALETTE_LEN - 1 - (z - CMINZ) * CPALETTE_LEN / (CMAXZ - CMINZ + 1);
	pixel(x, y, CPALETTE[ max(0, min(CPALETTE_LEN - 1, i)) ]);

	//pixel(x, y, '0'+z); // нагл€дный тест значений z
}

/* 3d-точка с контролем границ */
inline void pixel3d_cb(int x, int y, int z)
{
	if (x >= 0 && x <= CMAX_X && y >= 0 && y <= CMAX_Y)
		pixel3d(x, y, z);
}

/* установка палитры символов дл€ pixel3d, etc */
void setpalette(const char *palette)
{
	CPALETTE = palette;
	CPALETTE_LEN = mystrlen(palette);
}

/* установка видимого диапазона дл€ 3d-палитры */
void setdepth3d(int z1, int z2)
{
	CMINZ = z1;
	CMAXZ = z2;
}

// -----------------------------------------------------------------------
inline int mystrlen(const char* str) // пока что нужна только дл€ printfxy() и setpalette()
{
	int i = 0; for (; str[i]; i++); return i;
}

/* printf(...) в буфере screen, начина€ с позиции (x, y) */
void printfxy(int x, int y, const char* fmt, ...)
{
	char* buf = new char[mystrlen(fmt) * 4];

	va_list args;
	va_start(args, fmt);
	int len = _vscprintf(fmt, args) + 1;
	vsprintf_s(buf, len, fmt, args);
	va_end(args);

	char* dest = CSCR_PTR + y * CSCR_WIDTH + x;
	for (; *buf != 0 && *dest != 0;)
		if (*dest == '\n') dest++;
		else *dest++ = *buf++;	
}

// -----------------------------------------------------------------------
// --- обЄртки дл€ WinAPI ------------------------------------------------
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

// -----------------------------------------------------------------------
// --- спрайты
// -----------------------------------------------------------------------
#include "charmlib_sprites.inl"


// -----------------------------------------------------------------------
// --- линии --------------------------------------------
// -----------------------------------------------------------------------
#define POSTFIX
#define PIXEL pixel
#define PIXEL_CB pixel_cb
#include "charmlib_lines.inl"
#define POSTFIX _2
#define PIXEL pixel_2
#define PIXEL_CB pixel_cb_2
#include "charmlib_lines.inl"

#include "charmlib_line3d.inl"


// -----------------------------------------------------------------------
// --- пр€моугольники и рамки --------------------------------------------
// -----------------------------------------------------------------------
#define POSTFIX
#define PIXEL pixel
#define PIXEL_CB pixel_cb
#include "charmlib_rectangles.inl"
#define POSTFIX _2
#define PIXEL pixel_2
#define PIXEL_CB pixel_cb_2
#include "charmlib_rectangles.inl"

/* очистка канвы пробелом */
void clear_canvas(void)
{
	drawfilledrectangle(0, 0, CMAX_X, CMAX_Y, ' ');
}


// -----------------------------------------------------------------------
// --- функции дл€ работы с текстом --------------------------------------
// -----------------------------------------------------------------------

// (два шрифта, дл€ каждого -- по два способа вывода пикселей)
#include "font8x8.inl"
#include "font8x8.h"
#define POSTFIX
#define PIXEL pixel
#define PIXEL_CB pixel_cb
#include "charmlib_text.inl"
#include "font8x8.h"
#define POSTFIX _2
#define PIXEL pixel_2
#define PIXEL_CB pixel_cb_2
#include "charmlib_text.inl"

#include "font8x10.inl"
#include "font8x10.h"
#define POSTFIX
#define PIXEL pixel
#define PIXEL_CB pixel_cb
#include "charmlib_text.inl"
#include "font8x10.h"
#define POSTFIX _2
#define PIXEL pixel_2
#define PIXEL_CB pixel_cb_2
#include "charmlib_text.inl"
