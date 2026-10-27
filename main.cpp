#include "parser.hpp"
#include "pixel.hpp"
#include "mapa.hpp"
#include "punto.hpp"
#include "mediciones.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <vector>
#include <utility>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>

using namespace std;

void guardarMatrizComoPNG(const std::vector<std::vector<Pixel>>& matriz, const std::string& rutaArchivo) {
    if (matriz.empty() || matriz[0].empty()) return;

    int alto = matriz.size();
    int ancho = matriz[0].size();
    int canales = 3; // 3 canales para RGB (Rojo, Verde, Azul)

    // 1. Aplanar el vector 2D en un vector continuo de unsigned char
    std::vector<unsigned char> datosPlanos;
    datosPlanos.reserve(ancho * alto * canales);

    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            datosPlanos.push_back(matriz[y][x].r);
            datosPlanos.push_back(matriz[y][x].g);
            datosPlanos.push_back(matriz[y][x].b);
        }
    }

    // 2. Exportar usando stb_image_write
    // Parámetros: (nombre, ancho, alto, canales, datos, bytes por línea)
    int resultado = stbi_write_png(
        rutaArchivo.c_str(), 
        ancho, 
        alto, 
        canales, 
        datosPlanos.data(), 
        ancho * canales
    );

    if (!resultado) {
        std::cerr << "Error al guardar " << rutaArchivo << std::endl;
    }
}

int main()
{
    //crear mapa
    Mapa m, mm;
    
    vector<Punto> puntos;

    //leer posicion de los puntos y tamaño del mapa
    ifstream file("input.txt");
    if(!file.is_open())
    {
        cerr << "No se pudo abrir input.txt" << endl;
        return 1;
    }

    string linea;
    bool primeraLinea = true;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 255);

    while (getline(file, linea))
    {
        vector<string> tokens = separar(linea);
        if (tokens.size() < 2) continue; // linea vacia o incompleta

        if (primeraLinea)
        {
            m.x = stoi(tokens[0]); // ancho
            m.y = stoi(tokens[1]); // alto
            primeraLinea = false;
            continue; // la primera línea es el tamaño, no un punto
        }

        unsigned int px = stoi(tokens[0]);
        unsigned int py = stoi(tokens[1]);
        if (px >= m.x || py >= m.y)
        {
            cerr << "Punto fuera del mapa ignorado: " << px << "," << py << endl;
            continue;
        }

        Punto p = crearPunto(px, py, 0);
        p.r = distrib(gen);
        p.g = distrib(gen);
        p.b = distrib(gen);
        puntos.push_back(p);
    }

    if (primeraLinea || puntos.empty())
    {
        cerr << "input.txt debe tener el tamaño del mapa y al menos un punto" << endl;
        return 1;
    }

    // matriz[fila y][columna x]; cada pixel debe conocer su propia posicion
    m.matriz.assign(m.y, vector<Pixel>(m.x));
    for (unsigned int i = 0; i < m.y; i++)
    {
        for (unsigned int j = 0; j < m.x; j++)
        {
            m.matriz[i][j] = crearPixel(j, i);
        }
    }

    mm = m; // copia el tamaño y la matriz base

    // calcular el punto más cercano para cada celda
    for (unsigned int i = 0; i < m.y; i++)
    {
        for (unsigned int j = 0; j < m.x; j++)
        {
            double distMinE = 1.7976931348623157e308;
            double distMinM = distMinE;
            Punto minE = puntos[0], minM = puntos[0];

            for (size_t a = 0; a < puntos.size(); a++)
            {
                double dE = euclidiana(m.matriz[i][j], puntos[a]);
                double dM = manhattan(m.matriz[i][j], puntos[a]);

                if (dE < distMinE) { distMinE = dE; minE = puntos[a]; }
                if (dM < distMinM) { distMinM = dM; minM = puntos[a]; }
            }

            Pixel &pe = m.matriz[i][j];
            pe.r = minE.r;  pe.g = minE.g;  pe.b = minE.b;

            Pixel &pm = mm.matriz[i][j];
            pm.r = minM.r;  pm.g = minM.g;  pm.b = minM.b;
        }
    }

    guardarMatrizComoPNG(m.matriz, "euc.png");
    guardarMatrizComoPNG(mm.matriz, "Man.png");
    return 0;
}
