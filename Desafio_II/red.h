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
    void EliminarEstacion();
    void consulta();
    void AgregarSurtidor();
    //vamos hacer que si mandamos 1 activamos y si mandamos cero desactivemos
    void EstadoSurtidor();


};

#endif // RED_H
