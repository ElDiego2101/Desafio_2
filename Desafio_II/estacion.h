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
    short tanque;
public:
    Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, int _tanque);
    string getNombre();
    string getID_est() const;
    string getGerente() const;
    string getRegion() const;
    string getP_Geo() const;
    short getTanque() const;
};

#endif // ESTACION_H
