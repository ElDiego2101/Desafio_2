
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
    short indice;
    short nuevo_total;
    cout<<tipo<<endl;

    if (tipo == 1) {
        indice = tanqueRegular;
    } else if (tipo == 2) {
        indice = tanquePremiun;
    } else if (tipo == 3) {
        indice = tanqueEcoExtra;
    } else {
        cout << "Tipo de combustible no válido." << endl;
        return 0;
    }

    nuevo_total = indice - litros;

    if (nuevo_total < 0) {
        cout << "Solo podemos venderle " << indice << " litros" << endl;
        litros = indice;
        nuevo_total = 0;
    }

    if (tipo == 1) {
        tanqueRegular = nuevo_total;
    } else if (tipo == 2) {
        tanquePremiun = nuevo_total;
    } else if (tipo == 3) {
        tanqueEcoExtra = nuevo_total;
    }

    if (litros == 0) {
        cout << "Lo sentimos, no tenemos combustible de este tipo." << endl;
    }

    return litros;
}
