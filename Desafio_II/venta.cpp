#include "venta.h"

Venta::Venta(string _ID, string _fecha, string _hora, int _L_vendidos, string _metodo_pago, string _doc_cliente, int _dinero)
    : ID(_ID), fecha(_fecha), hora(_hora), L_vendidos(_L_vendidos),
        metodo_pago(_metodo_pago), doc_cliente(_doc_cliente), dinero(_dinero) {}
