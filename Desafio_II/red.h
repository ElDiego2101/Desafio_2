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
    int pos_est;
    int capacidad;
    int capacidad_est;

public:
    Red();
    ~Red();
    void AgregarEstacion();
    void consulta();

};

#endif // RED_H
