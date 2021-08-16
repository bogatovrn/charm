#ifndef FONT_LIB_H
#define FONT_LIB_H

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

char* create_screen(int width_plus_one, int height, char fillchar = ' ');
void delete_screen(char* screen);
void print_screen(char* screen);

inline void pixel(void* screen, int scr_width, int x, int y, char pixel = CHR_WHITE);

/* вывод символа с контролем границ */
void pixel_cb(void* screen, int scr_width, int max_x, int max_y, int x, int y, char pixel = CHR_WHITE);
void pixel2(void* screen, int scr_width, int x, int big_y, bool bit = true);
void pixel2_cb(void* screen, int scr_width, int x, int big_y, int max_x, int big_max_y, bool bit = true);

void drawrectangle(void* screen, int scr_width, int x1, int y1, int x2, int y2, int max_x, int max_y, char fillchar = CHR_WHITE);
void drawfilledrectangle(void* screen, int scr_width, int x1, int y1, int x2, int y2, char fillchar = ' ');

void drawchar8x8(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
void drawtext8x8(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1);
void drawchar8x8_shifted(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
void drawtext8x8_shifted(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

void drawchar8x10(void* screen, int scr_width, char chr, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);
void drawtext8x10(void* screen, int scr_width, const char* text, int x, int y, int max_x, int max_y, char pen = CHR_WHITE, char background = 0, int thickness = 1, int shiftleft = 0, int shiftup = 0);

void printfxy(void* screen, int scr_width, int x, int y, const char* fmt, ...);

void gotoxy(int xpos, int ypos);
void cursor_off();
void sleep(int milliseconds);

#endif // !FONT_LIB_H
