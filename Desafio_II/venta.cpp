#include "venta.h"

short Venta::getID() const
{
    return ID;
}

Venta::Venta(short _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero)
    : fecha(_fecha), hora(_hora), L_vendidos(_L_vendidos),
    metodo_pago(_metodo_pago), doc_cliente(_doc_cliente), dinero(_dinero) {ID=++cont_idventas;}

short Venta::cont_idventas = 0;
