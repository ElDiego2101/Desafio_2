#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
using namespace std;

class Estacion
{
private:
    string nombre;
    string ID_est;
    string gerente;
    string region;
    string P_Geo;
    int tanque;
public:
    Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, int _tanque);
    string getNombre();

};

#endif // ESTACION_H
