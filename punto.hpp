#ifndef PUNTO_HPP
#define PUNTO_HPP

struct Punto
{
    unsigned char r, g, b;
    unsigned int x, y;
};

Punto crearPunto(unsigned int x, unsigned int y, unsigned char c);

#endif  