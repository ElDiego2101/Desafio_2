#ifndef COMPLEMENTARIO_H
#define COMPLEMENTARIO_H
#include <string>

using namespace std;
string horaReal();
short leerDia(const string& nombreArchivo);
void actualizarDia(const string& nombreArchivo, int diaActual);
string leerInformacion(string archivo);
string guardarInformacion();
short randomNumero(int limite_i,int limite_s,string semilla);
void limpiarConsola();
bool esNumerico(const string& str);


#endif // COMPLEMENTARIO_H
