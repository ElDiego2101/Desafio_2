#ifndef RED_H
#define RED_H
#include "surtidor.h"
#include "venta.h"
#include "estacion.h"

class Red
{
private:
    Estacion** arreglo_estacion;
    Surtidor*** arreglo_surtidores;
    Venta** arreglo_ventas;
    int* contador_surtidores;
    int contador;
    int capacidad;

public:
    Red();
};

#endif // RED_H
