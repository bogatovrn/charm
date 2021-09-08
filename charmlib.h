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

/* ��������� ������������ �������� ��������� */
void setmaxxy(int max_x, int max_y);
/* ������� � ������ ��� ���� ����� */
char* create_screen(int width_plus_one, int height, char fillchar = ' ');
/* ��������� ����� ������ ��� ��������� */
void setcurrentscreen(char* screen, int width_plus_one);
/* ������� ����� ��������� ����� */
void delete_screen(char* screen);
/* ���������� ����� � ������� */
void print_current_screen();

/* printf(...) � ������ screen, ������� � ������� (x, y) */
void printfxy(int x, int y, const char* fmt, ...);
/* ������ ������� ���������� � (xpos, ypos) */
void gotoxy(int xpos, int ypos);
/* ������ ������� ������� ��������� */
void cursor_off();
/* �������� �� N �������� ������� */
void sleep(int milliseconds);

/* ����� ������� ��� �������� ������ */
inline void pixel(int x, int y, char pixel = CHR_WHITE);
/* ����� ������� � ��������� ������ */
inline void pixel_cb(int x, int y, char pixel = CHR_WHITE);
/* ����� ������� ��� �������� ������ */
inline void pixel(int x, int y, byte pixel);
/* ����� ������� � ��������� ������ */
inline void pixel_cb(int x, int y, byte pixel);

/* �/� ����� � ���������� ��� �������� ������ */
inline void pixel_2(int x, int big_y, char pixel = CHR_WHITE);
/* �/� ����� � ���������� � ��������� ������ */
inline void pixel_cb_2(int x, int big_y, char pixel = CHR_WHITE);

/* ����� � �������� �������������� k = 0..1.0F, ��������� setpalette() */
inline void pixel(int x, int y, float k = 1.0F);
/* ����� � �������� ��������������, �������� ������ */
inline void pixel_cb(int x, int y, float k = 1.0F);

/* 3d-����� �� ������ setdepth3d() � setpalette() */
inline void pixel3d(int x, int y, int z);
/* 3d-����� � ��������� ������ */
inline void pixel3d_cb(int x, int y, int z);
/* ��������� �������� ��������� ��� 3d-������� */
void setdepth3d(int z1, int z2);
/* ��������� ������� �������� ��� pixel3d, etc */
void setpalette(const char* palette);

// --- ������� �� "charmlib_sprites.inl" ---

///* ����� ������� � ����������������, ������������� ������� 0..1F */
//void drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);
///* ����� ������� � ����������������, ������������� ������� 0..255 */
//void drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

/* ����� ������� � ����������������, ������������� ������� 0..1F ��� 0..(byte)255 */
template <typename T> void drawsprite(T* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

/* ����� ������� � ����������������, ������������� ������� 0..1F */
extern template void drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);
/* ����� ������� � ����������������, ������������� ������� 0..255 */
extern template void drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);

// --- ����� �� "charmlib_lines.inl" ---

/* ����� �������� pen */
void drawline(int x1, int y1, int x2, int y2, char pen = CHR_WHITE);
/* ����� �/� ������������ */
void drawline_2(int x1, int y1, int x2, int y2, char pen = CHR_WHITE);
/* 3d-����� */
void drawline3d(int x1, int y1, int z1, int x2, int y2, int z2);

// --- �������������� � ����� �� "charmlib_rectangles.inl" ---

/* ����� �������������� �������� pen */
void drawrectangle(int x1, int y1, int x2, int y2, char fillchar = CHR_WHITE);
/* ����� �������������� �/� ������������ */
void drawrectangle_2(int x1, int big_y1, int x2, int big_y2, char fillchar = CHR_WHITE);
/* �������������, ����������� �������� fillchar */
void drawfilledrectangle(int x1, int y1, int x2, int y2, char fillchar = CHR_WHITE);
/* �������������, ����������� �/� ������������ */
void drawfilledrectangle_2(int x1, int y1, int x2, int big_y2, char fillchar = CHR_WHITE);

/* ������� ����� �������� */
void clear_canvas(void);

// --- ������� ��� ������ � ������� �� "charmlib_text.inl" ---

/* ������ ASCII(0..127) 8x8, ������� � �������� ������ ���� (x, y) */
void drawchar8x8(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* ��������� (��������� �����-�����) ����������� ������� ASCII 8x8 */
void drawchar8x8_shifted(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/* ����� � ������� drawchar8x8() */
void drawtext8x8(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* ����� � ������� drawchar8x8_shifted() */
void drawtext8x8_shifted(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/*������ drawchar8x8() ��� ��������� �/� ������������� */
void drawchar8x8_2(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*������ drawchar8x8_shifted() ��� ��������� �/� ������������� */
void drawchar8x8_2_shifted(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/*������ drawtext8x8() ��� ��������� �/� ������������� */
void drawtext8x8_2(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*������ drawtext8x8_shifted() ��� ��������� �/� ������������� */
void drawtext8x8_2_shifted(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/* ������ CP1251 8x10, ������� � �������� ������ ���� (x, y) */
void drawchar8x10(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* ��������� (��������� �����-�����) ����������� ������� CP1251 8x10 */
void drawchar8x10_shifted(char chr, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/* ����� � ������� drawchar8x10() */
void drawtext8x10(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/* ����� � ������� drawchar8x10_shifted() */
void drawtext8x10_shifted(const char* text, int x, int y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

/*������ drawchar8x10() ��� ��������� �/� ������������� */
void drawchar8x10_2(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*������ drawchar8x10_shifted() ��� ��������� �/� ������������� */
void drawchar8x10_2_shifted(char chr, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
/*������ drawtext8x10() ��� ��������� �/� ������������� */
void drawtext8x10_2(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
/*������ drawtext8x10_shifted() ��� ��������� �/� ������������� */
void drawtext8x10_2_shifted(const char* text, int x, int big_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);





#endif // !CHARMLIB_H
