#include "red.h"
#include "surtidor.h"
#include "venta.h"
#include "estacion.h"
#include "complementario.h"

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
    string hora=horaReal();
    int tanque=randomNumero(100,200,hora);
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
    //inicializar el contador en 2 por defecto
    contador_surtidores[pos_est]=2;
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
    cout<<*arreglo_surtidores[1];
    pos_est++;
    capacidad_est++;
    capacidad++;

}

void Red::EliminarEstacion()
{
    string est_elim;
    int pos_est_elim = -1;
    cout << "Estaciones disponibles: " << endl;
    for(int i = 0; i < capacidad_est; i++) {
        cout << endl << "-" << arreglo_estacion[i]->getNombre();
    }
    cout << endl << endl << "Ingrese la estacion a eliminar: ";
    cin >> est_elim;

    // Encontrar la estación a eliminar
    for(int i = 0; i < capacidad_est; i++) {
        if(est_elim == arreglo_estacion[i]->getNombre()) {
            pos_est_elim = i;
        }
    }

    if(pos_est_elim < 0) {
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }

    // Eliminar los surtidores de la estación
    int total = contador_surtidores[pos_est_elim];
    for (int var = 0; var < total; ++var) {
        delete arreglo_surtidores[pos_est_elim][var];
    }
    delete[] arreglo_surtidores[pos_est_elim];

    // Crear nuevo arreglo de surtidores
    Surtidor*** nuevo_arreglo_surtidores = new Surtidor**[capacidad - 1];
    for (int i = 0; i < capacidad; i++) {
        if (i < pos_est_elim) {
            nuevo_arreglo_surtidores[i] = arreglo_surtidores[i];
        } else if (i > pos_est_elim) {
            nuevo_arreglo_surtidores[i - 1] = arreglo_surtidores[i];
        }
    }
    delete[] arreglo_surtidores;
    arreglo_surtidores = nuevo_arreglo_surtidores;

    // Crear nuevo arreglo de contadores de surtidores
    int* nuevo_contador_surtidores = new int[capacidad_est - 1];
    for (int i = 0; i < pos_est_elim; i++) {
        nuevo_contador_surtidores[i] = contador_surtidores[i];
    }
    for (int i = pos_est_elim; i < capacidad_est - 1; i++) {
        nuevo_contador_surtidores[i] = contador_surtidores[i + 1];
    }
    delete[] contador_surtidores;
    contador_surtidores = nuevo_contador_surtidores;

    // Crear nuevo arreglo de estaciones
    Estacion** nuevo_arreglo_estaciones = new Estacion*[capacidad_est - 1];
    for (int i = 0; i < capacidad_est; i++) {
        if (i < pos_est_elim) {
            nuevo_arreglo_estaciones[i] = arreglo_estacion[i];
        } else if (i > pos_est_elim) {
            nuevo_arreglo_estaciones[i - 1] = arreglo_estacion[i];
        }
    }
    delete[] arreglo_estacion;
    arreglo_estacion = nuevo_arreglo_estaciones;

    capacidad_est--;
    capacidad--;
}


void Red :: consulta()
{
    for(int i = 0; i < capacidad_est;i++){
    cout << endl << arreglo_estacion[i]->getNombre() << endl << "Surtidores: " << endl;
        for(int j = 0; j < contador_surtidores[i];j++){
            cout << arreglo_surtidores[i][j]->getNombre() << endl;
        }
    }

}

void Red::AgregarSurtidor() {
    string id;
    string nombre_a;
    string estSurtidor;

    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }

    cout << "Ingrese el nombre de la estación a la que quiere agregar un surtidor: " << endl;
    cin >> estSurtidor;


    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
            break;
        }
    }

    if (pos_est < 0) {
        cout << endl << "*La estación ingresada no existe.*" << endl;
        return;
    }

    int total_surtidores = contador_surtidores[pos_est];


    Surtidor** nuevo_arreglo_surtidores = new Surtidor*[total_surtidores + 1];

    for (int i = 0; i < total_surtidores; i++) {
        nuevo_arreglo_surtidores[i] = arreglo_surtidores[pos_est][i];
    }

    cout << "Ingrese el ID del surtidor: " << endl;
    cin >> id;
    cout << "Ingrese el modelo del surtidor: " << endl;
    cin >> nombre_a;

    nuevo_arreglo_surtidores[total_surtidores] = new Surtidor(id, nombre_a, true);

    delete[] arreglo_surtidores[pos_est];
    arreglo_surtidores[pos_est] = nuevo_arreglo_surtidores;

    contador_surtidores[pos_est] += 1;
    capacidad++;

    cout << endl << "*Surtidor agregado con éxito.*" << endl;
}

void Red::EstadoSurtidor(){
    string estSurtidor;
    cout<<"ingrese la estacion: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }

    cout << "Ingrese el nombre de la estación a la que quiere agregar un surtidor: " << endl;
    cin >> estSurtidor;
    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
            break;
        }
    }
    if (pos_est < 0) {
        cout << endl << "*La estación ingresada no existe.*" << endl;
        return;
    }
    int contador=contador_surtidores[pos_est];
    for (int var = 0; var < contador; ++var) {
        cout << arreglo_surtidores[pos_est][var]->getNombre() << "-" << (arreglo_surtidores[pos_est][var]->getEstado_surtidor() ? "Activa" : "Desactivo") << endl;
    }
    string surtidor;
    cout<<"ingrese el surtidor a modificar:  "<<endl;
    cin>>surtidor;
    int var = -1;

    for (int i = 0; i < contador_surtidores[pos_est]; i++) {
        if (arreglo_surtidores[pos_est][i]->getNombre() == surtidor) {
            var = i;
            break;
        }
    }

    if (var == -1) {
        cout << "Surtidor no encontrado." << endl;
        return;
    }
    short estado;
    char r;
    cout<<"1.activar"<<endl;
    cout<<"2.desactivar"<<endl;
    cin>>r;
    switch(r){
    case '1':
        estado=1;
        break;
    case '2':
        estado=0;
        break;
    }

    if (estado == 0 && arreglo_surtidores[pos_est][var]->getEstado_surtidor() == 1) {
        arreglo_surtidores[pos_est][var]->setEstado_surtidor(false);
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ha sido desactivado." << endl;
    } else if (estado == 1 && arreglo_surtidores[pos_est][var]->getEstado_surtidor() == 0) {
        arreglo_surtidores[pos_est][var]->setEstado_surtidor(true);
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ha sido activado." << endl;
    } else {
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ya está en el estado deseado." << endl;
    }

}
