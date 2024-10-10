#ifndef VENTA_H
#define VENTA_H
#include <iostream>
using namespace std;

class Venta
{
private:
    string ID;
    string fecha;
    string hora;
    int L_vendidos;
    string metodo_pago;
    string doc_cliente;
    int dinero;
public:
    Venta(string _ID, string _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero);
};

#endif // VENTA_H
