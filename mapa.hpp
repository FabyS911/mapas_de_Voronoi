#ifndef MAPA_HPP
#define MAPA_HPP
#include "pixel.hpp"
#include <vector>

struct Mapa
{
    // matriz[fila][columna] = matriz[y][x]
    std::vector<std::vector<Pixel>> matriz;

    // x = ancho, y = alto
    unsigned int x, y;
};

#endif
