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
    precios = new short*[3]; // Se asigna memoria para 3 regiones
    for (int i = 0; i < 3; ++i) {
        precios[i] = new short[3]; // Cada región tiene 3 precios
    }
    precioRegular = 0;
    precioPremiun = 0;
    precioEcoMax = 0;
}
void Red::AjustarPrecios(){
    cout << "1. Region Norte" << endl;
    cout << "2. Region Centro" << endl;
    cout << "3. Region Sur" << endl;

    for (int var = 0; var < 3; ++var) {
        cout << "Precios para la region " << var + 1 << endl;
        cout << "Regular: " << endl;
        cin >> precioRegular;
        cout << "Premium: " << endl;
        cin >> precioPremiun;
        cout << "EcoMax: " << endl;
        cin >> precioEcoMax;
        precios[var][0] = precioRegular;  // Regular
        precios[var][1] = precioPremiun;  // Premium
        precios[var][2] = precioEcoMax;   // EcoMax
    }
}
void Red::SimulacionVenta(){
    string nombreArchivo = "baseDatos";
    string estSurtidor;
    short dia = leerDia(nombreArchivo);
    string metodo_pago, doc_cliente;
    int L_vendidos,dinero;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }
    cout<<"ingrese la estacion donde se va a realizar la venta: "<<endl;
    cin >> estSurtidor;

    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
            break;
        }
    }

    if (pos_est < 0) {
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }
    string hora=horaReal();
    int limite_s=contador_surtidores[pos_est];
    limite_s-=1;
    short indice=randomNumero(0,limite_s,hora);
    string region=arreglo_estacion[pos_est]->getRegion();
    int tipo;
    cout<<"1.Regular"<<endl;
    cout<<"2.Premium"<<endl;
    cout<<"3.EcoExtra"<<endl;
    cout<<"ingrese el tipo de combustible que quiere tanquear"<<endl;
    cin>>tipo;
    short var;
    if(region=="norte"){
        var=0;
    }else if(region=="centro"){
        var=1;
    }else if(region=="sur"){
        var=2;
    }
    int precio=precios[var][tipo-1];
    cout << "Ingrese la cantidad de litros de gasolina: ";
    cin >> L_vendidos;
    cout << "Ingrese el metodo de pago (Efectivo/Tarjeta): ";
    cin >> metodo_pago;
    cout << "Ingrese el documento del cliente: ";
    cin >> doc_cliente;
    dinero=L_vendidos*precio;
    Venta* miVenta = new Venta(dia, hora, L_vendidos, metodo_pago, doc_cliente, dinero);
    arreglo_surtidores[pos_est][indice]->AgregarVenta(miVenta);
    Venta** nuevo_arreglo_ventas = new Venta*[capacidad + 1];
    for (int i = 0; i < capacidad; ++i) {
        nuevo_arreglo_ventas[i] = arreglo_ventas[i];
    }
    nuevo_arreglo_ventas[capacidad] = miVenta;
    arreglo_ventas = nuevo_arreglo_ventas;
    capacidad++;
    cout << "Venta registrada exitosamente." << endl;
}
Red::~Red() {
    for (int i = 0; i < capacidad; ++i) {
        delete arreglo_ventas[i];
    }
    for (int i = 0; i < 3; ++i) {
        delete[] precios[i];
    }
    delete[] precios;
    delete[] arreglo_estacion;
    delete[] contador_surtidores;
    for (int i = 0; i < capacidad; i++) {
        delete[] arreglo_surtidores[i];
    }
    delete[] arreglo_surtidores;
    delete[] arreglo_ventas;
}

void Red::AgregarEstacion() {
    string nombre, ID, gerente, region, P_Geo;
    string hora = horaReal();
    int tanqueRegular = randomNumero(100, 200, hora);
    int tanquePremiun = randomNumero(100, 200, hora);
    int tanqueEcoExtra = randomNumero(100, 200, hora);

    cout << "Ingrese el nombre de la nueva estacion: ";
    cin >> nombre;
    cout << "Ingrese el ID de la estacion: ";
    cin >> ID;
    cout << "Ingrese el gerente de la estacion: ";
    cin >> gerente;

    bool regionValida = false;
    while (!regionValida) {
        cout << "Ingrese la region en la que se encuentra la estacion (norte, centro, sur): ";
        cin >> region;
        if (region == "norte" || region == "centro" || region == "sur") {
            regionValida = true;
        } else {
            cout << "Error: Region no valida. Intente de nuevo." << endl;
        }
    }

    bool P_GeoValida = false;
    while (!P_GeoValida) {
        cout << "Ingrese la ubicacion geografica (coordenadas GPS): ";
        cin >> P_Geo;
        if (esNumerico(P_Geo)) {
            P_GeoValida = true;
        } else {
            cout << "Error: La ubicacion geografica debe ser numerica. Intente de nuevo." << endl;
        }
    }

    bool duplicadoNombre = false, duplicadoID = false, duplicadoGeo = false;

    for (int i = 0; i < pos_est; i++) {
        string nombre_normalizado = arreglo_estacion[i]->getNombre();
        string ID_normalizado = arreglo_estacion[i]->getID_est();
        string P_Geo_normalizado = arreglo_estacion[i]->getP_Geo();

        if (nombre_normalizado == nombre && !duplicadoNombre) {
            cout << "Error: El nombre de la estacion '" << nombre << "' ya existe." << endl;
            duplicadoNombre = true;
        }
        if (ID_normalizado == ID && !duplicadoID) {
            cout << "Error: El ID de la estacion '" << ID << "' ya existe." << endl;
            duplicadoID = true;
        }
        if (P_Geo_normalizado == P_Geo && !duplicadoGeo) {
            cout << "Error: La posicion geografica '" << P_Geo << "' ya existe." << endl;
            duplicadoGeo = true;
        }
    }

    if (duplicadoNombre || duplicadoID || duplicadoGeo) {
        return; // Salir de la función si hay duplicados
    }

    Surtidor*** nuevo_arreglo_surtidores = new Surtidor**[capacidad + 1];
    Estacion** nuevo_arreglo_estaciones = new Estacion*[capacidad_est + 1];

    for (int i = 0; i < capacidad_est; i++) {
        nuevo_arreglo_estaciones[i] = arreglo_estacion[i];
        nuevo_arreglo_surtidores[i] = arreglo_surtidores[i];
    }
    delete[] arreglo_estacion;
    delete[] arreglo_surtidores;

    arreglo_surtidores = nuevo_arreglo_surtidores;
    arreglo_estacion = nuevo_arreglo_estaciones;
    arreglo_surtidores[pos_est] = new Surtidor*[2];
    contador_surtidores[pos_est] = 2; // Inicializar el contador en 2 por defecto
    arreglo_estacion[pos_est] = new Estacion(nombre, ID, gerente, region, P_Geo, tanqueRegular, tanquePremiun, tanqueEcoExtra);

    cout << endl << "Estacion agregada con exito." << endl;
    cout << "Por favor ingrese dos surtidores a la estacion: " << endl;

    for (int i = 0; i < 2; i++) {
        bool idDuplicado = true; // Inicializamos como verdadero para entrar al bucle

        while (idDuplicado) {
            cout << "Ingrese el ID del surtidor: ";
            cin >> ID;

            // Verificar si el ID del surtidor ya existe
            idDuplicado = false; // Suponemos que no hay duplicado
            for (int j = 0; j < i; j++) {
                if (nuevo_arreglo_surtidores[pos_est][j] != nullptr && nuevo_arreglo_surtidores[pos_est][j]->getNombre() == ID) {
                    cout << "Error: El ID del surtidor '" << ID << "' ya existe. Ingrese uno nuevo." << endl;
                    idDuplicado = true; // Hay un duplicado
                }
            }
        }

        cout << "Ingrese el modelo del surtidor: ";
        cin >> nombre;

        nuevo_arreglo_surtidores[pos_est][i] = new Surtidor(ID, nombre, true);
        cout << endl << "*Surtidor creado con exito*" << endl;
    }

    pos_est++;
    capacidad_est++;
    capacidad++;
}



void Red::EliminarEstacion() {
    string est_elim;
    int pos_est_elim = -1;
    cout << "Estaciones disponibles: " << endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << "-" << arreglo_estacion[i]->getNombre();
    }
    cout << endl << endl << "Ingrese la estacion a eliminar: ";
    cin >> est_elim;

    for (int i = 0; i < capacidad_est; i++) {
        if (est_elim == arreglo_estacion[i]->getNombre()) {
            pos_est_elim = i;
        }
    }

    if (pos_est_elim < 0) {
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }

    int total = contador_surtidores[pos_est_elim];
    for (int var = 0; var < total; ++var) {
        delete arreglo_surtidores[pos_est_elim][var];
    }
    delete[] arreglo_surtidores[pos_est_elim];

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

    int* nuevo_contador_surtidores = new int[capacidad_est - 1];
    for (int i = 0; i < pos_est_elim; i++) {
        nuevo_contador_surtidores[i] = contador_surtidores[i];
    }
    for (int i = pos_est_elim; i < capacidad_est - 1; i++) {
        nuevo_contador_surtidores[i] = contador_surtidores[i + 1];
    }
    delete[] contador_surtidores;
    contador_surtidores = nuevo_contador_surtidores;

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

    cout << endl << "*La estacion fue eliminada con exito.*" << endl; // Mensaje de éxito
}


void Red :: consulta()
{
    for(int i = 0; i < capacidad_est;i++){
    cout << endl << arreglo_estacion[i]->getNombre() << endl << "Surtidores: " << endl;
    cout<<capacidad<<endl;
    cout<<capacidad_est<<endl;
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

    cout << "Ingrese el nombre de la estacion a la que quiere agregar un surtidor: " << endl;
    cin >> estSurtidor;

    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
        }
    }

    if (pos_est < 0) {
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }

    int total_surtidores = contador_surtidores[pos_est];

    // Verificar si el ID del surtidor ya existe
    bool idRepetido = false;
    cout << "Ingrese el ID del surtidor: " << endl;
    cin >> id;

    for (int i = 0; i < total_surtidores && !idRepetido; i++) {
        if (arreglo_surtidores[pos_est][i]->getID_sr() == id) { // Uso correcto del método getID_sr
            idRepetido = true;
            cout << "El ID del surtidor ya existe." << endl;
        }
    }

    if (!idRepetido) {
        cout << "Ingrese el modelo del surtidor: " << endl;
        cin >> nombre_a;

        Surtidor** nuevo_arreglo_surtidores = new Surtidor*[total_surtidores + 1];

        for (int i = 0; i < total_surtidores; i++) {
            nuevo_arreglo_surtidores[i] = arreglo_surtidores[pos_est][i];
        }

        nuevo_arreglo_surtidores[total_surtidores] = new Surtidor(id, nombre_a, true);

        delete[] arreglo_surtidores[pos_est];
        arreglo_surtidores[pos_est] = nuevo_arreglo_surtidores;

        contador_surtidores[pos_est] += 1;
        capacidad++;

        cout << endl << "*Surtidor agregado con éxito.*" << endl;
    }
}



void Red::ELiminarSurtidor(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }
    cout << "Ingrese el nombre de la estación a la que quiere eliminar un surtidor: " << endl;
    cin >> estSurtidor;
    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
            break;
        }
    }
    if (pos_est < 0) {
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }
    int contador=contador_surtidores[pos_est];
    for (int var = 0; var < contador; ++var) {
        cout << arreglo_surtidores[pos_est][var]->getNombre() << "-" << (arreglo_surtidores[pos_est][var]->getEstado_surtidor() ? "Activa" : "Desactivo") << endl;
    }
    string surtidor;
    cout<<"ingrese el surtidor a eliminar:  "<<endl;
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
    delete arreglo_surtidores[pos_est][var];

    // Crear un nuevo arreglo de surtidores, excluyendo el surtidor eliminado
    Surtidor** nuevo_arreglo_surtidores = new Surtidor*[contador - 1];
    for (int i = 0, j = 0; i < contador; i++) {
        if (i != var) {
            nuevo_arreglo_surtidores[j] = arreglo_surtidores[pos_est][i];
            j++;
        }
    }

    // Eliminar el viejo arreglo de surtidores
    delete[] arreglo_surtidores[pos_est];

    // Actualizar el arreglo de surtidores con el nuevo
    arreglo_surtidores[pos_est] = nuevo_arreglo_surtidores;

    // Actualizar el contador de surtidores
    contador_surtidores[pos_est]--;

    cout << "*Surtidor '" << surtidor << "' eliminado con éxito.*" << endl;





}
void Red::EstadoSurtidor(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
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
        cout << endl << "*La estacion ingresada no existe.*" << endl;
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
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ya esta en el estado deseado." << endl;
    }

}

void Red::ConsultarTransacciones(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }
    cout << "Ingrese el nombre de la estacion de los surtidores que quiere acceder: " << endl;
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
    cout<<"ingrese el surtidor que quiera ver sus transacciones:  "<<endl;
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
    arreglo_surtidores[pos_est][var]->MostrarVentas();

}
