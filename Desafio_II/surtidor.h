#ifndef SURTIDOR_H
#define SURTIDOR_H
#include <iostream>
using namespace std;

class Surtidor
{
private:
    string ID_sr;
    string Model_mq;
    bool estado_surtidor;
public:
    Surtidor(string _ID_sr, string _Model_mq, bool _estado_surtidor);
    string getNombre();

    bool getEstado_surtidor() const;
    void setEstado_surtidor(bool newEstado_surtidor);
};

#endif // SURTIDOR_H
