
#include "estacion.h"
#include "complementario.h"

    string Estacion::getID_est() const
{
    return ID_est;
}

string Estacion::getGerente() const
{
    return gerente;
}

string Estacion::getRegion() const
{
    return region;
}

string Estacion::getP_Geo() const
{
    return P_Geo;
}


short Estacion::getTanqueRegular() const
{
    return tanqueRegular;
}

void Estacion::setTanqueRegular(short newTanqueRegular)
{
    tanqueRegular = newTanqueRegular;
}

short Estacion::getTanquePremiun() const
{
    return tanquePremiun;
}

void Estacion::setTanquePremiun(short newTanquePremiun)
{
    tanquePremiun = newTanquePremiun;
}

short Estacion::getTanqueEcoExtra() const
{
    return tanqueEcoExtra;
}

void Estacion::setTanqueEcoExtra(short newTanqueEcoExtra)
{
    tanqueEcoExtra = newTanqueEcoExtra;
}

short Estacion::getTRegular() const
{
    return tRegular;
}

short Estacion::getTPremiun() const
{
    return tPremiun;
}

short Estacion::getTEcoExtra() const
{
    return tEcoExtra;
}

Estacion::Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, short _tanqueRegular, short _tanquePremiun, short _tanqueEcoExtra)
    : nombre(_nombre), ID_est(_ID_est), gerente(_gerente), region(_region), P_Geo(_P_Geo), tanqueRegular(_tanqueRegular),tanquePremiun(_tanquePremiun), tanqueEcoExtra(_tanqueEcoExtra){
    tRegular=_tanqueRegular;
    tPremiun=_tanquePremiun;
    tEcoExtra=_tanqueEcoExtra;
}

string Estacion :: getNombre() { return nombre; }

short Estacion::MermarTanque(short tipo, int litros) {
    short* tanque;
    switch(tipo) {
    case 0:
        tanque = &tanqueRegular;
        break;
    case 1:
        tanque = &tanquePremiun;
        break;
    case 2:
        tanque = &tanqueEcoExtra;
        break;
    default:
        cout << "Tipo de combustible no válido." << endl;
        return 0;
    }

    if (*tanque == 0) {
        cout << "Lo sentimos, no tenemos combustible de este tipo." << endl;
        return 0;
    }

    if (*tanque < litros) {
        cout << "Solo podemos venderle " << *tanque << " litros." << endl;
        litros = *tanque;
        *tanque = 0;
    } else {
        *tanque -= litros;
    }

    return litros;
}
