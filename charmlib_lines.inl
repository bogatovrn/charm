// перед включением этого файла должны быть определены
// функции вывода точки PIXEL и PIXEL_CB, например:

//#define PIXEL pixel_2
//#define PIXEL_CB pixel_cb_2

// и соответствующий POSTFIX, для приведённого примера:
//#define POSTFIX _2

#define CONCAT3(x,y) x##y
#define CONCAT2(x,y) CONCAT3(x,y)
#define CONCAT(x,y,z) CONCAT2(x,CONCAT2(y,z))

#define DRAWLINE CONCAT(drawline,POSTFIX)
#define _DRAWLINE CONCAT(_,DRAWLINE)
#define _DRAWLINE_CB CONCAT(_DRAWLINE,_cb)

// -----------------------------------------------------------------------
inline void _DRAWLINE(int x1, int y1, int x2, int y2, char pen)
{
    int dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    int dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
    int sx = (x2 >= x1) ? (1) : (-1);
    int sy = (y2 >= y1) ? (1) : (-1);

    if (dy < dx)
    {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
        PIXEL(x1, y1, pen);
        int x = x1 + sx;
        int y = y1;
        for (int i = 1; i <= dx; i++)
        {
            if (d > 0)
            {
                d += d2;
                y += sy;
            }
            else
                d += d1;
            PIXEL(x, y, pen);
            x += sx;
        }
    }
    else
    {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
        PIXEL(x1, y1, pen);
        int x = x1;
        int y = y1 + sy;
        for (int i = 1; i <= dy; i++)
        {
            if (d > 0)
            {
                d += d2;
                x += sx;
            }
            else
                d += d1;
            PIXEL(x, y, pen);
            y += sy;
        }
    }
}
inline void _DRAWLINE_CB(int x1, int y1, int x2, int y2, char pen)
{
    int dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    int dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
    int sx = (x2 >= x1) ? (1) : (-1);
    int sy = (y2 >= y1) ? (1) : (-1);

    if (dy < dx)
    {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
        PIXEL_CB(x1, y1, pen);
        int x = x1 + sx;
        int y = y1;
        for (int i = 1; i <= dx; i++)
        {
            if (d > 0)
            {
                d += d2;
                y += sy;
            }
            else
                d += d1;
            PIXEL_CB(x, y, pen);
            x += sx;
        }
    }
    else
    {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
        PIXEL_CB(x1, y1, pen);
        int x = x1;
        int y = y1 + sy;
        for (int i = 1; i <= dy; i++)
        {
            if (d > 0)
            {
                d += d2;
                x += sx;
            }
            else
                d += d1;
            PIXEL_CB(x, y, pen);
            y += sy;
        }
    }
}
/* линия символом pen */
void DRAWLINE(int x1, int y1, int x2, int y2, char pen)
{
	int x = min(x1, x2);
	int y = min(y1, y2);
	int x3 = max(x1, x2);
	int y3 = max(y1, y2);

	if (x < 0 || y < 0 || x3 > CMAX_X || y3 > CMAX_Y)
		_DRAWLINE_CB(x1, y1, x2, y2, pen);
	else
		_DRAWLINE(x1, y1, x2, y2, pen);
}

// -----------------------------------------------------------------------



#undef PIXEL
#undef PIXEL_CB
#undef POSTFIX

#undef CONCAT3
#undef CONCAT2
#undef CONCAT

#undef  DRAWLINE
#undef _DRAWLINE
#undef _DRAWLINE_CB

