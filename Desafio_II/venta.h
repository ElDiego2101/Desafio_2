#ifndef VENTA_H
#define VENTA_H
#include <iostream>
using namespace std;

class Venta
{
private:
    short ID;
    short fecha;
    string hora;
    int L_vendidos;
    string metodo_pago;
    string doc_cliente;
    int dinero;
    static short cont_idventas;
public:
    Venta(short _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero);
    void calcularPrecio();
    short getID() const;
};
#endif // VENTA_H
