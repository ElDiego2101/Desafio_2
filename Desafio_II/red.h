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
    short** precios;
    int* contador_surtidores;
    int pos_est;
    int capacidad;
    int capacidad_est;
    short precioRegular;
    short precioPremiun;
    short precioEcoMax;
    friend short randomNumero(int limite_i,int limite_s,string semilla);


public:
    Red();
    ~Red();
    void AgregarEstacion();
    void AjustarPrecios();
    void EliminarEstacion();
    void consulta();
    void AgregarSurtidor();
    void ELiminarSurtidor();
    //vamos hacer que si mandamos 1 activamos y si mandamos cero desactivemos
    void EstadoSurtidor();
    void SimulacionVenta();
    void ConsultarTransacciones();


};

#endif // RED_H
