#include "surtidor.h"

bool Surtidor::getEstado_surtidor() const
{
    return estado_surtidor;
}

void Surtidor::setEstado_surtidor(bool newEstado_surtidor)
{
    estado_surtidor = newEstado_surtidor;
}

Surtidor::Surtidor(string _ID_sr, string _Model_mq, bool _estado_surtidor)
    : ID_sr(_ID_sr), Model_mq(_Model_mq), estado_surtidor(_estado_surtidor) {
    ventas = new Venta*[1];
    num_ventas = 0;
}

string Surtidor :: getNombre() { return ID_sr; }

void Surtidor::AgregarVenta(Venta* nuevaVenta) {
    Venta** nuevoArreglo = new Venta*[num_ventas + 1];
    for (int i = 0; i < num_ventas; ++i) {
        nuevoArreglo[i] = ventas[i];
    }
    delete[] ventas;

    nuevoArreglo[num_ventas] = nuevaVenta;
    ventas = nuevoArreglo;
    num_ventas++;
}


void Surtidor::MostrarVentas()const{
    for (int i = 0; i < num_ventas; ++i) {
        cout << "id venta: " << ventas[i]->getID() << endl;
        cout << "documento: " << ventas[i]->getDoc_cliente() << endl;
        cout << "Litros vendidos: " << ventas[i]->getL_vendidos() << endl;
        cout << "dinero ingresado: " << ventas[i]->getDinero() << endl;
        cout << "metodo: " << ventas[i]->getMetodo_pago() << endl;
        cout << "fecha: " << ventas[i]->getFecha() << endl;
        cout << "hora: " << ventas[i]->getHora() << endl;
        // Agrega más detalles según lo que necesites mostrar
        cout << endl;
    }
}
