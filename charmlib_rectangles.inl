// перед включением этого файла должны быть определены
// функции вывода точки PIXEL и PIXEL_CB, например:

//#define PIXEL pixel_2
//#define PIXEL_CB pixel_cb_2

// и соответствующий POSTFIX, для приведённого примера:
//#define POSTFIX _2

#define CONCAT3(x,y) x##y
#define CONCAT2(x,y) CONCAT3(x,y)
#define CONCAT(x,y,z) CONCAT2(x,CONCAT2(y,z))

#define DRAWFILLEDRECTANGLE CONCAT(drawfilledrectangle,POSTFIX)
#define _DRAWFILLEDRECTANGLE CONCAT(_,DRAWFILLEDRECTANGLE)
#define _DRAWFILLEDRECTANGLE_CB CONCAT(_DRAWFILLEDRECTANGLE,_cb)

#define DRAWRECTANGLE CONCAT(drawrectangle,POSTFIX)
#define _DRAWRECTANGLE CONCAT(_,DRAWRECTANGLE)
#define _DRAWRECTANGLE_CB CONCAT(_DRAWRECTANGLE,_cb)

// -----------------------------------------------------------------------
inline void _DRAWFILLEDRECTANGLE(int x1, int y1, int x2, int y2, char fillchar)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			PIXEL(x, y, fillchar);
}
inline void _DRAWFILLEDRECTANGLE_CB(int x1, int y1, int x2, int y2, char fillchar)
{
	for (int y = y1; y <= y2; y++)
		for (int x = x1; x <= x2; x++)
			PIXEL_CB(x, y, fillchar);
}
/* прямоугольник, закрашенный символом fillchar */
void DRAWFILLEDRECTANGLE(int x1, int y1, int x2, int y2, char fillchar)
{
	int x = min(x1, x2);
	int y = min(y1, y2);
	int x3 = max(x1, x2);
	int y3 = max(y1, y2);

	if (x < 0 || y < 0 || x3 > CMAX_X || y3 > CMAX_Y)
		_DRAWFILLEDRECTANGLE_CB(x, y, x3, y3, fillchar);
	else
		_DRAWFILLEDRECTANGLE(x, y, x3, y3, fillchar);
}

// -----------------------------------------------------------------------
inline void _DRAWRECTANGLE(int x1, int y1, int x2, int y2, char pen)
{
	for (int x = x1; x <= x2; x++)
		PIXEL(x, y1, pen),
		PIXEL(x, y2, pen);
	for (int y = y1 + 1; y < y2; y++)
		PIXEL(x1, y, pen),
		PIXEL(x2, y, pen);
}
inline void _DRAWRECTANGLE_CB(int x1, int y1, int x2, int y2, char pen)
{
	for (int x = x1; x <= x2; x++)
		PIXEL_CB(x, y1, pen),
		PIXEL_CB(x, y2, pen);
	for (int y = y1 + 1; y < y2; y++)
		PIXEL_CB(x1, y, pen),
		PIXEL_CB(x2, y, pen);
}
/* рамка прямоугольника символом pen */
void DRAWRECTANGLE(int x1, int y1, int x2, int y2, char pen)
{
	int x = min(x1, x2);
	int y = min(y1, y2);
	int x3 = max(x1, x2);
	int y3 = max(y1, y2);

	if (x < 0 || y < 0 || x3 > CMAX_X || y3 > CMAX_Y)
		_DRAWRECTANGLE_CB(x, y, x3, y3, pen);
	else
		_DRAWRECTANGLE(x, y, x3, y3, pen);
}

#undef PIXEL
#undef PIXEL_CB
#undef POSTFIX

#undef CONCAT3
#undef CONCAT2
#undef CONCAT

#undef DRAWFILLEDRECTANGLE
#undef _DRAWFILLEDRECTANGLE
#undef _DRAWFILLEDRECTANGLE_CB

#undef DRAWRECTANGLE
#undef _DRAWRECTANGLE
#undef _DRAWRECTANGLE_CB

