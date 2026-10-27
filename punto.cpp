#include "punto.hpp"

Punto crearPunto(unsigned int x, unsigned int y, unsigned char c)
{
    Punto p;
    p.x = x;
    p.y = y;

    p.r = c;
    p.g = c;
    p.b = c;

    return p;
}