#ifndef SURTIDOR_H
#define SURTIDOR_H

#include <iostream>
#include <string>
using namespace std;

class Venta; // Asegúrate de incluir la definición de la clase Venta

class Surtidor {
private:
    string ID_sr;
    string Model_mq;
    bool estado_surtidor;
    Venta** ventas;
    int num_ventas;
    int tR, tP, tE; // total de ventas por tipo

public:
    Surtidor(string _ID_sr, string _Model_mq, bool _estado_surtidor);

    bool getEstado_surtidor() const;
    void setEstado_surtidor(bool newEstado_surtidor);
    int getTR() const;
    int getTP() const;
    int getTE() const;

    string getNombre();
    void AgregarVenta(Venta* nuevaVenta);
    void MostrarVentas() const;
    void ventastipoC();

    // Métodos getters que causan el error
    Venta** getVentas() const; // Declaración
    int getNumVentas() const;  // Declaración
};

#endif // SURTIDOR_H
