#define SPRITE(i, j) (*(sprite + (i)*swidth + (j)))

// -----------------------------------------------------------------------
template <typename T>
inline void _drawsprite(T* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        float tmp = (float)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        float u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            float tmp = (float)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            float t = tmp - w;

            float d1 = (1 - t) * (1 - u);
            float d2 = t * (1 - u);
            float d3 = t * u;
            float d4 = (1 - t) * u;

            T p1 = SPRITE(h, w);
            T p2 = SPRITE(h, w + 1);
            T p3 = SPRITE(h + 1, w + 1);
            T p4 = SPRITE(h + 1, w);

            T k = (T)(p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4);

            if (typeid(T) == typeid(byte))
                k /= 255;

            pixel(x1 + j, y1 + i, k);
        }
    }
}
template <typename T>
inline void _drawsprite_cb(T* sprite, int swidth, int sheight, int x1, int y1, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        float tmp = (float)(i) / (height - 1) * (sheight - 1);
        int h = (int)tmp;
        if (h < 0) h = 0;
        else
            if (h >= sheight - 1)
                h = sheight - 2;
        float u = tmp - h;

        for (int j = 0; j < width; j++)
        {
            float tmp = (float)(j) / (width - 1) * (swidth - 1);
            int w = (int)tmp;
            if (w < 0) w = 0;
            else
                if (w >= swidth - 1)
                    w = swidth - 2;
            float t = tmp - w;

            float d1 = (1 - t) * (1 - u);
            float d2 = t * (1 - u);
            float d3 = t * u;
            float d4 = (1 - t) * u;

            T p1 = SPRITE(h, w);
            T p2 = SPRITE(h, w + 1);
            T p3 = SPRITE(h + 1, w + 1);
            T p4 = SPRITE(h + 1, w);

            T k = (T)(p1 * d1 + p2 * d2 + p3 * d3 + p4 * d4);

            if (typeid(T) == typeid(byte))
                k /= 255;

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


