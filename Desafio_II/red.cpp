#include "red.h"
#include "surtidor.h"
#include "venta.h"
#include "estacion.h"

Red::Red()
{
    capacidad = 1;
    arreglo_estacion = new Estacion*[capacidad];
    arreglo_surtidores = new Surtidor**[capacidad];
    contador_surtidores = new int[capacidad];
    arreglo_ventas = new Venta*[capacidad];
}
