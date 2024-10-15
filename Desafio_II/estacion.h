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
    short tanqueRegular;
    short tanquePremiun;
    short tanqueEcoExtra;

public:
    Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, short _tanqueRegular,short _tanquePremiun,short _tanqueEcoExtra);
    string getNombre();
    string getID_est() const;
    string getGerente() const;
    string getRegion() const;
    string getP_Geo() const;
};

#endif // ESTACION_H
