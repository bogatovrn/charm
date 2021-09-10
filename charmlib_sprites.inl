#define SPRITE(i, j) (*(sprite + (i)*swidth + (j)))

// -----------------------------------------------------------------------
inline void _drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        double tmp = (double)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        double u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            double tmp = (double)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            double t = tmp - w;

            double d1 = (1 - t) * (1 - u);
            double d2 = t * (1 - u);
            double d3 = t * u;
            double d4 = (1 - t) * u;

            float p1 = SPRITE(h, w);
            float p2 = SPRITE(h, w + 1);
            float p3 = SPRITE(h + 1, w + 1);
            float p4 = SPRITE(h + 1, w);

            float k = p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4;

            pixel(x1 + j, y1 + i, k);
        }
    }
}

inline void _drawsprite_cb(float* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        double tmp = (double)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        double u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            double tmp = (double)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            double t = tmp - w;

            double d1 = (1 - t) * (1 - u);
            double d2 = t * (1 - u);
            double d3 = t * u;
            double d4 = (1 - t) * u;

            float p1 = SPRITE(h, w);
            float p2 = SPRITE(h, w + 1);
            float p3 = SPRITE(h + 1, w + 1);
            float p4 = SPRITE(h + 1, w);

            float k = p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4;

            pixel_cb(x1 + j, y1 + i, k);
        }
    }
}
// -----------------------------------------------------------------------
inline void _drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        double tmp = (double)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        double u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            double tmp = (double)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            double t = tmp - w;

            double d1 = (1 - t) * (1 - u);
            double d2 = t * (1 - u);
            double d3 = t * u;
            double d4 = (1 - t) * u;

            byte p1 = SPRITE(h, w);
            byte p2 = SPRITE(h, w + 1);
            byte p3 = SPRITE(h + 1, w + 1);
            byte p4 = SPRITE(h + 1, w);

            float k = (float)(p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4)/255;

            pixel(x1 + j, y1 + i, k);
        }
    }
}

inline void _drawsprite_cb(byte* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        double tmp = (double)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        double u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            double tmp = (double)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            double t = tmp - w;

            double d1 = (1 - t) * (1 - u);
            double d2 = t * (1 - u);
            double d3 = t * u;
            double d4 = (1 - t) * u;

            byte p1 = SPRITE(h, w);
            byte p2 = SPRITE(h, w + 1);
            byte p3 = SPRITE(h + 1, w + 1);
            byte p4 = SPRITE(h + 1, w);

            float k = (p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4) / 255;

            pixel_cb(x1 + j, y1 + i, k);
        }
    }
}


/* вывод спрайта с масштабированием, интенсивность пикселя 0..1F */
template <typename T> void drawsprite(T* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2)
{
    if (x1 < 0 || y1 < 0 || x2 > CMAX_X || y2 > CMAX_Y)
        _drawsprite_cb(sprite, swidth, sheight, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
    else
        _drawsprite(sprite, swidth, sheight, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

// -----------------------------------------------------------------------
template void drawsprite(float* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);
template void drawsprite(byte* sprite, int swidth, int sheight, int x1, int y1, int x2, int y2);


