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


Estacion::Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, short _tanqueRegular, short _tanquePremiun, short _tanqueEcoExtra)
    : nombre(_nombre), ID_est(_ID_est), gerente(_gerente), region(_region), P_Geo(_P_Geo), tanqueRegular(_tanqueRegular),tanquePremiun(_tanquePremiun), tanqueEcoExtra(_tanqueEcoExtra){}

string Estacion :: getNombre() { return nombre; }
