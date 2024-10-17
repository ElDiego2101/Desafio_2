#ifndef VENTA_H
#define VENTA_H
#include <iostream>
    using namespace std;

class Venta
{
private:
    short ID;
    short tipoCombustible;
    int dinero=0;
    short fecha;
    string hora;
    int L_vendidos;
    string metodo_pago;
    string doc_cliente;
    static short cont_idventas;
public:
    Venta(short _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero,short _tipoCombustible);
    void calcularPrecio();
    short getID() const;
    short getFecha() const;
    string getHora() const;
    int getL_vendidos() const;
    string getMetodo_pago() const;
    string getDoc_cliente() const;
    int getDinero() const;
    static short getCont_idventas();
    short getTipoCombustible() const;
};
#endif // VENTA_H
