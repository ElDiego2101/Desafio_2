#include "surtidor.h"
#include "complementario.h"
#include "venta.h"

bool Surtidor::getEstado_surtidor() const {
    return estado_surtidor;
}

void Surtidor::setEstado_surtidor(bool newEstado_surtidor) {
    estado_surtidor = newEstado_surtidor;
}

int Surtidor::getTR() const {
    return tR;
}

int Surtidor::getTP() const {
    return tP;
}

int Surtidor::getTE() const {
    return tE;
}

Surtidor::Surtidor(string _ID_sr, string _Model_mq, bool _estado_surtidor)
    : ID_sr(_ID_sr), Model_mq(_Model_mq), estado_surtidor(_estado_surtidor) {
    ventas = new Venta*[1]; // Inicializa el arreglo de ventas
    num_ventas = 0;
}
string Surtidor::getNombre() {
    return ID_sr;
}
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
void Surtidor::MostrarVentas() const {
    for (int i = 0; i < num_ventas; ++i) {
        cout << "id venta: " << ventas[i]->getID() << endl;
        cout << "documento: " << ventas[i]->getDoc_cliente() << endl;
        cout << "Litros vendidos: " << ventas[i]->getL_vendidos() << endl;
        cout << "dinero ingresado: " << ventas[i]->getDinero() << endl;
        cout << "metodo: " << ventas[i]->getMetodo_pago() << endl;
        cout << "fecha: " << ventas[i]->getFecha() << endl;
        cout << "hora: " << ventas[i]->getHora() << endl;
        cout << endl; // Salto de línea para separar cada venta
    }
    if (num_ventas == 0) {
        limpiarConsola();
        cout << "Lo sentimos, este surtidor no tiene ventas." << endl;
    }
}
void Surtidor::ventastipoC() {
    int totalR = 0;  // Total de combustible tipo 1 (regular)
    int totalP = 0;  // Total de combustible tipo 2 (premium)
    int totalE = 0;  // Total de combustible tipo 3 (extra)
    limpiarConsola();
    for (int i = 0; i < num_ventas; ++i) {
        short tipo = ventas[i]->getTipoCombustible();
        if (tipo == 1) {
            totalR += ventas[i]->getDinero();
        } else if (tipo == 2) {
            totalP += ventas[i]->getDinero();
        } else if (tipo == 3) {
            totalE += ventas[i]->getDinero();
        }
    }
    tR = totalR;
    tP = totalP;
    tE = totalE;
}
Venta** Surtidor::getVentas() const {
    return ventas;
}
int Surtidor::getNumVentas() const {
    return num_ventas;
}
