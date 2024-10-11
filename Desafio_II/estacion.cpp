#include "estacion.h"

Estacion::Estacion(string _nombre, string _ID_est, string _gerente, string _region, string _P_Geo, int _tanque)
    : nombre(_nombre), ID_est(_ID_est), gerente(_gerente), region(_region), P_Geo(_P_Geo), tanque(_tanque) {}

string Estacion :: getNombre() { return nombre; }
