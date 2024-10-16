#include "complementario.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using namespace std;
string horaReal(){
    chrono::time_point<chrono::system_clock> ahora = chrono::system_clock::now();
    time_t tiempo_actual = chrono::system_clock::to_time_t(ahora);
    //lo pasamos a un string leible
    string hora_e = ctime(&tiempo_actual);

    string solo_hora = hora_e.substr(11, 8);    //solo tenemos en cuenta los segundos
    return solo_hora;
}

void limpiarConsola(){
    for(int i=0;i<20;i++){
        cout<<" "<<endl;
    }
}
short randomNumero(int limite_i, int limite_s, string semilla) {
    string segundos = semilla.substr(6, 2);
    if (!segundos.empty()) {
        unsigned short semilla1 = stoi(segundos);
        int rango = limite_s - limite_i + 1;

        unsigned short aleatorio = (semilla1 * 110 + 12345) % rango;

        aleatorio += limite_i;
    return aleatorio;
    } else {
        cout << "Lo sentimos, la hora está vacía, por lo tanto no podremos generar un número aleatorio." << endl;
        return -1;
    }
}
short leerDia(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    int dia = 1;

    if (archivo.is_open()) {
        string linea;
        getline(archivo, linea);
        dia = stoi(linea);
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo. Inicializando el día en 1." << endl;
    }

    return dia;
}
void actualizarDia(const string& nombreArchivo, int diaActual) {
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string primeraLinea, restoContenido, linea;


        getline(archivo, primeraLinea);


        while (getline(archivo, linea)) {
            restoContenido += linea + "\n";
        }

        archivo.close();

        ofstream archivoSalida(nombreArchivo);
        if (archivoSalida.is_open()) {
            archivoSalida << (diaActual + 1) << endl;
            archivoSalida << restoContenido;
            archivoSalida.close();
            cout << "El dia ha sido actualizado a " << diaActual + 1 << endl;
        } else {
            cout << "No se pudo abrir el archivo para escritura." << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}


bool esNumerico(const string& str) {
    for (char c : str) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

