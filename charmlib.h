#ifndef CHARMLIB_H
#define CHARMLIB_H

//#define NDEBUG
#include <cassert>


#define CHR_BLACK (char)32
#define CHR_GRAY12 (char)176
#define CHR_GRAY25 (char)177
#define CHR_GRAY75 (char)178
#define CHR_WHITE (char)219

#define CHR_BIGDOT (char)249
#define CHR_DOT (char)250
#define CHR_SQUARE (char)254

#define CHR_UPPERLEFTCORNER (char)218
#define CHR_UPPERRIGHTCORNER (char)191
#define CHR_BOTTOMLEFTCORNER (char)192
#define CHR_BOTTOMRIGHTCORNER (char)217
#define CHR_HORLINE (char)196
#define CHR_VERTLINE (char)179
#define CHR_CROSS (char)197

#define CHR_DBL_UPPERLEFTCORNER (char)188
#define CHR_DBL_UPPERRIGHTCORNER (char)200
#define CHR_DBL_BOTTOMLEFTCORNER (char)187
#define CHR_DBL_BOTTOMRIGHTCORNER (char)201
#define CHR_DBL_HORLINE (char)205
#define CHR_DBL_VERTLINE (char)186
#define CHR_DBL_CROSS (char)206

typedef unsigned char byte;

/* запомнить максимальные значения координат */
void setmaxxy(int max_x, int max_y);
/* создать в памяти ещё один буфер */
char* create_screen(int width_plus_one, int height, char fillchar = ' ');
/* запомнить адрес буфера для отрисовки */
void setcurrentscreen(char* screen, int width_plus_one);
/* удалить ранее созданный буфер */
void delete_screen(char* screen);
/* отобразить буфер в консоли */
void print_current_screen();

/* printf(...) в буфере screen, начиная с позиции (x, y) */
void printfxy(int x, int y, const char* fmt, ...);
/* курсор консоли установить в (xpos, ypos) */
void gotoxy(int xpos, int ypos);
/* курсор консоли сделать невидимым */
void cursor_off();
/* задержка на N тысячных секунды */
void sleep(int milliseconds);

/* вывод символа без контроля границ */
inline void pixel(int x, int y, char pixel = CHR_WHITE);
/* вывод символа с контролем границ */
inline void pixel_cb(int x, int y, char pixel = CHR_WHITE);
/* вывод символа без контроля границ */
inline void pixel(int x, int y, byte pixel);
/* вывод символа с контролем границ */
inline void pixel_cb(int x, int y, byte pixel);

/* ч/б точка в полсимвола без контроля границ */
inline void pixel_2(int x, int big_y, char pixel = CHR_WHITE);
/* ч/б точка в полсимвола с контролем границ */
inline void pixel_cb_2(int x, int big_y, char pixel = CHR_WHITE);

/* точка с заданной интенсивностью k = 0..1.0F, используя setpalette() */
inline void pixel(int x, int y, float k = 1.0F);
/* точка с заданной интенсивностью, контроль границ */
inline void pixel_cb(int x, int y, float k = 1.0F);

/* 3d-точка на основе setdepth3d() и setpalette() */
inline void pixel3d(int x, int y, int z);
/* 3d-точка с контролем границ */
inline void pixel3d_cb(int x, int y, int z);
/* установка видимого диапазона для 3d-палитры */
void setdepth3d(int z1, int z2);
/* установка палитры символов для pixel3d, etc */
void setpalette(const char* palette);

// --- спрайты из "charmlib_sprites.inl" ---

///* вывод спрайта с масштабированием, интенсивность пикселя 0..1F */
//void drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);
///* вывод спрайта с масштабированием, интенсивность пикселя 0..255 */
//void drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

/* вывод спрайта с масштабированием, интенсивность пикселя 0..1F или 0..(byte)255 */
template <typename T> void drawsprite(T* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

/* вывод спрайта с масштабированием, интенсивность пикселя 0..1F */
extern template void drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);
/* вывод спрайта с масштабированием, интенсивность пикселя 0..255 */
extern template void drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

// --- линии из "charmlib_lines.inl" ---

/* линия символом pen */
void drawline(int x1, int y1, int x2, int y2, char pen = CHR_WHITE);
/* линия ч/б полусимволом */
void drawline_2(int x1, int y1, int x2, int y2, char pen = CHR_WHITE);
/* 3d-линия */
void drawline3d(int x1, int y1, int z1, int x2, int y2, int z2);

// --- прямоугольники и рамки из "charmlib_rectangles.inl" ---

/* рамка прямоугольника символом pen */
void drawrectangle(int x1, int y1, int x2, int y2, char fillchar = CHR_WHITE);
/* рамка прямоугольника ч/б полусимволом */
void drawrectangle_2(int x1, int big_y1, int x2, int big_y2, char fillchar = CHR_WHITE);
/* прямоугольник, закрашенный символом fillchar */
void drawfilledrectangle(int x1, int y1, int x2, int y2, char fillchar = CHR_WHITE);
/* прямоугольник, закрашенный ч/б полусимволом */
void drawfilledrectangle_2(int x1, int y1, int x2, int big_y2, char fillchar = CHR_WHITE);

/* очистка канвы пробелом */
void clear_canvas(void);

// --- функции для работы с текстом из "charmlib_text.inl" ---

/* символ ASCII(0..127) 8x8, начиная с верхнего левого угла (x, y) */
void drawchar8x8(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* частичное (сдвинутое влево-вверх) изображение символа ASCII 8x8 */
void drawchar8x8_shifted(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/* текст с помощью drawchar8x8() */
void drawtext8x8(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* текст с помощью drawchar8x8_shifted() */
void drawtext8x8_shifted(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/*аналог drawchar8x8() для отрисовки ч/б полусимволами */
void drawchar8x8_2(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*аналог drawchar8x8_shifted() для отрисовки ч/б полусимволами */
void drawchar8x8_2_shifted(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/*аналог drawtext8x8() для отрисовки ч/б полусимволами */
void drawtext8x8_2(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*аналог drawtext8x8_shifted() для отрисовки ч/б полусимволами */
void drawtext8x8_2_shifted(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/* символ CP1251 8x10, начиная с верхнего левого угла (x, y) */
void drawchar8x10(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* частичное (сдвинутое влево-вверх) изображение символа CP1251 8x10 */
void drawchar8x10_shifted(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/* текст с помощью drawchar8x10() */
void drawtext8x10(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* текст с помощью drawchar8x10_shifted() */
void drawtext8x10_shifted(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/*аналог drawchar8x10() для отрисовки ч/б полусимволами */
void drawchar8x10_2(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*аналог drawchar8x10_shifted() для отрисовки ч/б полусимволами */
void drawchar8x10_2_shifted(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/*аналог drawtext8x10() для отрисовки ч/б полусимволами */
void drawtext8x10_2(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*аналог drawtext8x10_shifted() для отрисовки ч/б полусимволами */
void drawtext8x10_2_shifted(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);





#endif // !CHARMLIB_H
