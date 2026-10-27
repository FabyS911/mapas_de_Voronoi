#include "pixel.hpp"

Pixel crearPixel(unsigned int x, unsigned int y)
{
    Pixel p;
    p.x = x;
    p.y = y;

    p.r = 255;
    p.g = 255;
    p.b = 255;

    return p;
}