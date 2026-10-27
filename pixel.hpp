#ifndef PIXEL_HPP
#define PIXEL_HPP

struct Pixel
{
    unsigned char r, g, b;
    unsigned int x, y;
};

Pixel crearPixel(unsigned int x, unsigned int y);

#endif