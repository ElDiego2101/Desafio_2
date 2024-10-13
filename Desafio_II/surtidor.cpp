#include "surtidor.h"

bool Surtidor::getEstado_surtidor() const
{
    return estado_surtidor;
}

void Surtidor::setEstado_surtidor(bool newEstado_surtidor)
{
    estado_surtidor = newEstado_surtidor;
}

Surtidor::Surtidor(string _ID_sr, string _Model_mq, bool _estado_surtidor)
    : ID_sr(_ID_sr), Model_mq(_Model_mq), estado_surtidor(_estado_surtidor) {}

string Surtidor :: getNombre() { return ID_sr; }
