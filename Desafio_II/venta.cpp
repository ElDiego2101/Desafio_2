#include "venta.h"

    short Venta::getID() const
{
    return ID;
}

short Venta::getFecha() const
{
    return fecha;
}

string Venta::getHora() const
{
    return hora;
}

int Venta::getL_vendidos() const
{
    return L_vendidos;
}

string Venta::getMetodo_pago() const
{
    return metodo_pago;
}

string Venta::getDoc_cliente() const
{
    return doc_cliente;
}

int Venta::getDinero() const
{
    return dinero;
}

short Venta::getCont_idventas()
{
    return cont_idventas;
}

short Venta::getTipoCombustible() const
{
    return tipoCombustible;
}

Venta::Venta(short _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero, short _tipoCombustible)
    : tipoCombustible(_tipoCombustible), dinero(_dinero), fecha(_fecha), hora(_hora),
    L_vendidos(_L_vendidos), metodo_pago(_metodo_pago), doc_cliente(_doc_cliente) {
    ID = ++cont_idventas;
}

short Venta::cont_idventas = 0;
