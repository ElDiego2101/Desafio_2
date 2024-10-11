#include "red.h"
#include "surtidor.h"
#include "venta.h"
#include "estacion.h"

Red::Red()
{
    capacidad = 0;
    capacidad_est = 0;
    pos_est = 0;
    arreglo_estacion = new Estacion*[capacidad_est];
    arreglo_surtidores = new Surtidor**[capacidad];
    contador_surtidores = new int[capacidad];
    arreglo_ventas = new Venta*[capacidad];
}

Red::~Red() {
    delete[] arreglo_estacion;
    delete[] contador_surtidores;
    for (int i = 0; i < capacidad; i++) {
        delete[] arreglo_surtidores[i];
    }
    delete[] arreglo_surtidores;
    delete[] arreglo_ventas;
}

void Red::AgregarEstacion()
{
    string nombre, ID, gerente, region, P_Geo;
    int tanque=150;
    cout << "Ingrese el nombre de la nueva estacion: ";
    cin >> nombre;
    cout << "Ingrese el ID de la estacion: ";
    cin >> ID;
    cout << "Ingrese el gerente de la estacion: ";
    cin >> gerente;
    cout << "Ingrese la region en la que se encuentra la estacion (norte, centro, sur): ";
    cin >> region;
    cout << "Ingrese la ubicacion geografica (coordenadas GPS): ";
    cin >> P_Geo;
    Surtidor*** nuevo_arreglo_surtidores = new Surtidor**[capacidad+1];
    Estacion** nuevo_arreglo_estaciones = new Estacion*[capacidad_est+1];
    for(int i=0;i<capacidad_est;i++){
        nuevo_arreglo_estaciones[i] = arreglo_estacion[i];
        nuevo_arreglo_surtidores[i] = arreglo_surtidores[i];
    }
    delete[] arreglo_estacion;
    delete[] arreglo_surtidores;

    arreglo_surtidores = nuevo_arreglo_surtidores;
    arreglo_estacion = nuevo_arreglo_estaciones;
    arreglo_surtidores[pos_est] = new Surtidor*[2];
    arreglo_estacion[pos_est] = new Estacion(nombre, ID, gerente, region, P_Geo, tanque);

    cout << endl << "Estacion agregada con exito." << endl;
    cout << "Por favor ingrese dos surtidores a la estacion: " << endl;
    for(int i = 0;i<2;i++){
        cout << "Ingrese el ID del surtidor: ";
        cin >> ID;
        cout << "Ingrese el modelo del surtidor: ";
        cin >> nombre;
        nuevo_arreglo_surtidores[pos_est][i] = new Surtidor(ID, nombre, true);
        cout << endl << "*Surtidor creado con exito*" << endl;
    }
    arreglo_surtidores = nuevo_arreglo_surtidores;
    pos_est++;
    capacidad_est++;
    capacidad++;

}
void Red :: consulta()
{
    for(int i = 0; i < capacidad_est;i++){
    cout << endl << arreglo_estacion[i]->getNombre() << endl << "Surtidores: " << endl;
        for(int j = 0; j < capacidad;j++){
            cout << arreglo_surtidores[i][j]->getNombre() << endl;
        }
    }
}
