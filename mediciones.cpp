#include <cmath>
#include "mediciones.hpp"

// Se convierte a double antes de restar: con unsigned int, 3 - 10 da un
// numero enorme (wrap-around) en lugar de -7.
double euclidiana(Pixel pi, Punto pu)
{
    double dx = (double)pi.x - (double)pu.x;
    double dy = (double)pi.y - (double)pu.y;
    return sqrt(dx * dx + dy * dy);
}

double manhattan(Pixel pi, Punto pu)
{
    double dx = (double)pi.x - (double)pu.x;
    double dy = (double)pi.y - (double)pu.y;
    return fabs(dx) + fabs(dy);
}
