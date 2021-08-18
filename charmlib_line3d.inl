// -----------------------------------------------------------------------
inline void _drawline3d(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    int dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
        int dz = (z2 > z1) ? (z2 - z1) : (z1 - z2);
    int sx = (x2 >= x1) ? (1) : (-1);
    int sy = (y2 >= y1) ? (1) : (-1);
        int sz = (z2 >= z1) ? (1) : (-1);

    if (dy < dx)
    {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
            int dd = (dz << 1) - dx;
            int dz1 = dz << 1;
            int dz2 = (dz - dx) << 1;
        pixel3d(x1, y1, z1);
        int x = x1 + sx;
        int y = y1;
            int z = z1;
        for (int i = 1; i <= dx; i++)
        {
            if (d > 0)
            {
                d += d2;
                y += sy;
            }
            else
                d += d1;

                if (dd > 0)
                {
                    dd += dz2;
                    z += sz;
                }
                else
                    dd += dz1;

            pixel3d(x, y, z);
            x += sx;
        }
    }
    else
    {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
            int dd = (dz << 1) - dy;
            int dz1 = dz << 1;
            int dz2 = (dz - dy) << 1;
        pixel3d(x1, y1, z1);
        int x = x1;
        int y = y1 + sy;
            int z = z1;
        for (int i = 1; i <= dy; i++)
        {
            if (d > 0)
            {
                d += d2;
                x += sx;
            }
            else
                d += d1;

                if (dd > 0)
                {
                    dd += dz2;
                    z += sz;
                }
                else
                    dd += dz1;  

            pixel3d(x, y, z);
            y += sy;
        }
    }
}
inline void _drawline3d_cb(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    int dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);
        int dz = (z2 > z1) ? (z2 - z1) : (z1 - z2);
    int sx = (x2 >= x1) ? (1) : (-1);
    int sy = (y2 >= y1) ? (1) : (-1);
        int sz = (z2 >= z1) ? (1) : (-1);

    if (dy < dx)
    {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
            int dd = (dz << 1) - dx;
            int dz1 = dz << 1;
            int dz2 = (dz - dx) << 1;
        pixel3d_cb(x1, y1, z1);
        int x = x1 + sx;
        int y = y1;
            int z = z1;
        for (int i = 1; i <= dx; i++)
        {
            if (d > 0)
            {
                d += d2;
                y += sy;
            }
            else
                d += d1;

                if (dd > 0)
                {
                    dd += dz2;
                    z += sz;
                }
                else
                    dd += dz1;

            pixel3d_cb(x, y, z);
            x += sx;
        }
    }
    else
    {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
            int dd = (dz << 1) - dy;
            int dz1 = dz << 1;
            int dz2 = (dz - dy) << 1;
        pixel3d_cb(x1, y1, z1);
        int x = x1;
        int y = y1 + sy;
            int z = z1;
        for (int i = 1; i <= dy; i++)
        {
            if (d > 0)
            {
                d += d2;
                x += sx;
            }
            else
                d += d1;

                if (dd > 0)
                {
                    dd += dz2;
                    z += sz;
                }
                else
                    dd += dz1;

            pixel3d_cb(x, y, z);
            y += sy;
        }
    }
}
/* 3d-линия с помощью pixel3d() */
void drawline3d(int x1, int y1, int z1, int x2, int y2, int z2)
{
    int x = min(x1, x2);
    int y = min(y1, y2);
    int x3 = max(x1, x2);
    int y3 = max(y1, y2);

    if (x < 0 || y < 0 || x3 > CMAX_X || y3 > CMAX_Y)
        _drawline3d_cb(x1, y1, z1, x2, y2, z2);
    else
        _drawline3d(x1, y1, z1, x2, y2, z2);
}

// -----------------------------------------------------------------------
