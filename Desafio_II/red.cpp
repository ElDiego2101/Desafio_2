#include "red.h"
#include "surtidor.h"
#include "venta.h"
#include "estacion.h"
#include "complementario.h"
#include <fstream>

    Red::Red()
{
    capacidad = 0;
    capacidad_est = 0;
    pos_est = 0;
    arreglo_estacion = new Estacion*[capacidad_est];
    arreglo_surtidores = new Surtidor**[capacidad];
    contador_surtidores = new int[capacidad];
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
    limpiarConsola();
    cout<<"precios regulados con exito"<<endl;

}

void Red::AgregarEstacion() {
    string nombre, ID, gerente, region, P_Geo;
    string hora = horaReal();
    int tanqueRegular = randomNumero(100, 200, hora);
    int tanquePremiun = randomNumero(100, 200, hora);
    int tanqueEcoExtra = randomNumero(100, 200, hora);

    cout << "Ingrese el nombre de la nueva estacion: ";
    cin >> nombre;
    bool idValido = false;
    while (!idValido) {
        cout << "Ingrese el ID de la estacion: ";
        cin >> ID;

        idValido = true;  // Inicialmente asumimos que el ID es válido
        // Verificar si el ID es numérico
        if (!esNumerico(ID)) {
            limpiarConsola();
            cout << "Error: El ID debe ser numerico. Intente de nuevo." << endl;
            idValido = false;
        }
    }

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
            limpiarConsola();
            cout << "Error: El nombre de la estacion '" << nombre << "' ya existe." << endl;
            duplicadoNombre = true;
        }
        if (ID_normalizado == ID && !duplicadoID) {
            limpiarConsola();
            cout << "Error: El ID de la estacion '" << ID << "' ya existe." << endl;
            duplicadoID = true;
        }
        if (P_Geo_normalizado == P_Geo && !duplicadoGeo) {
            limpiarConsola();
            cout << "Error: La posicion geografica '" << P_Geo << "' ya existe." << endl;
            duplicadoGeo = true;
        }
    }

    if (duplicadoNombre || duplicadoID || duplicadoGeo) {
        return; // Salir de la función si hay duplicados
    }

    // Crear nuevos arreglos para las estaciones y surtidores
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

    // Crear los dos surtidores por defecto
    arreglo_surtidores[pos_est] = new Surtidor*[2];
    contador_surtidores[pos_est] = 2; // Inicializar el contador en 2 por defecto
    arreglo_estacion[pos_est] = new Estacion(nombre, ID, gerente, region, P_Geo, tanqueRegular, tanquePremiun, tanqueEcoExtra);

    limpiarConsola();
    cout << endl << "Estacion agregada con exito." << endl;
    cout << "Por favor ingrese dos surtidores a la estacion: " << endl;
    string ID_a;
    for (int i = 0; i < 2; i++) {
        bool idValido = false;
        while (!idValido) {
            cout << "Ingrese el ID del surtidor: ";
            cin >> ID;

            if (i == 1 && ID == ID_a) {
                limpiarConsola();
                cout << "Error: El ID del surtidor '" << ID << "' ya existe. Ingrese otro ID." << endl;
                continue;  // Vuelve a solicitar el ID
            }

            // Verificar si el ID es numérico
            if (!esNumerico(ID)) {
                limpiarConsola();
                cout << "Error: El ID debe ser numérico. Intente de nuevo." << endl;
                continue;  // Vuelve a solicitar el ID
            }

            // Si es el primer surtidor, guardamos el ID
            if (i == 0) {
                ID_a = ID;
            }

            cout << "Ingrese el modelo del surtidor: ";
            cin >> nombre;

            idValido = true;  // El ID es válido
        }
        arreglo_surtidores[pos_est][i] = new Surtidor(ID, nombre, true);
        cout << endl << "*Surtidor creado con exito*" << endl;
        cout<<endl<<"ingrese el siguiente surtidor: " <<endl;
    }

    pos_est++;
    capacidad_est++;
    capacidad++;

    // Limpiar la consola antes de mostrar el mensaje final
    limpiarConsola();
    cout << endl << "*Estacion agregada con exito.*" << endl;
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

    for(int i = 0; i < capacidad_est; i++) {
        if(est_elim == arreglo_estacion[i]->getNombre()) {
            pos_est_elim = i;
        }
    }

    if(pos_est_elim < 0) {
        limpiarConsola();
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
    limpiarConsola();
    cout<<"Estacion eliminada con exito"<<endl;
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

    cout << "Estaciones: " << endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << "-" << arreglo_estacion[i]->getNombre() << endl;
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
        limpiarConsola();
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }

    int total_surtidores = contador_surtidores[pos_est];
    Surtidor** nuevo_arreglo_surtidores = new Surtidor*[total_surtidores + 1];

    for (int i = 0; i < total_surtidores; i++) {
        nuevo_arreglo_surtidores[i] = arreglo_surtidores[pos_est][i];
    }

    bool idValido = false;
    while (!idValido) {
        cout << "Ingrese el ID del surtidor: " << endl;
        cin >> id;

        idValido = true;  // Inicialmente asumimos que el ID es válido

        // Verificar si el ID ya existe entre los surtidores de la estación actual
        for (int i = 0; i < total_surtidores && idValido; i++) {
            if (nuevo_arreglo_surtidores[i]->getNombre() == id) {
                cout << "Error: El ID del surtidor '" << id << "' ya existe. Ingrese otro ID." << endl;
                idValido = false;  // El ID ya existe, solicitamos otro
            }
        }

        // Verificar si el ID es numérico
        if (!esNumerico(id)) {
            limpiarConsola();
            cout << "Error: El ID debe ser numerico. Intente de nuevo." << endl;
            idValido = false;
        }
    }

    cout << "Ingrese el modelo del surtidor: " << endl;
    cin >> nombre_a;

    nuevo_arreglo_surtidores[total_surtidores] = new Surtidor(id, nombre_a, true);

    delete[] arreglo_surtidores[pos_est];
    arreglo_surtidores[pos_est] = nuevo_arreglo_surtidores;

    contador_surtidores[pos_est] += 1;
    capacidad++;

    limpiarConsola();
    cout << endl << "*Surtidor agregado con exito.*" << endl;
}

void Red::ELiminarSurtidor(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }
    cout << "Ingrese el nombre de la estacion a la que quiere eliminar un surtidor: " << endl;
    cin >> estSurtidor;
    int pos_est = -1;
    for (int i = 0; i < capacidad_est; i++) {
        if (estSurtidor == arreglo_estacion[i]->getNombre()) {
            pos_est = i;
            break;
        }
    }
    if (pos_est < 0) {
        limpiarConsola();
        cout << endl << "*La estacion ingresada no existe.*" << endl;
        return;
    }
    int contador=contador_surtidores[pos_est];
    if(contador==2){
        cout<<"lo sentimos, no puedes eliminar un surtidor porque la estacion debe de tener minimo dos surtidores"<<endl;
        return;
    }
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

    Surtidor** nuevo_arreglo_surtidores = new Surtidor*[contador - 1];
    for (int i = 0, j = 0; i < contador; i++) {
        if (i != var) {
            nuevo_arreglo_surtidores[j] = arreglo_surtidores[pos_est][i];
            j++;
        }
    }
    delete[] arreglo_surtidores[pos_est];
    arreglo_surtidores[pos_est] = nuevo_arreglo_surtidores;
    contador_surtidores[pos_est]--;
    limpiarConsola();
    cout << "*Surtidor '" << surtidor << "' eliminado con exito.*" << endl;
}
void Red::EstadoSurtidor(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }
    cout <<endl<< "Ingrese el nombre de la estacion a la que quiere modificar un surtidor: " << endl;
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
    limpiarConsola();
    cout<<"surtidores: "<<endl;
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
        limpiarConsola();
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
    limpiarConsola();
    if (estado == 0 && arreglo_surtidores[pos_est][var]->getEstado_surtidor() == 1) {
        arreglo_surtidores[pos_est][var]->setEstado_surtidor(false);
        limpiarConsola();
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ha sido desactivado." << endl;
    } else if (estado == 1 && arreglo_surtidores[pos_est][var]->getEstado_surtidor() == 0) {
        arreglo_surtidores[pos_est][var]->setEstado_surtidor(true);
        limpiarConsola();
        cout << "El surtidor '" << arreglo_surtidores[pos_est][var]->getNombre() << "' ha sido activado." << endl;
    } else {
        limpiarConsola();
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
        limpiarConsola();
        cout << endl << "*La estación ingresada no existe.*" << endl;
        return;
    }
    limpiarConsola();
    cout<<"surtidores: "<<endl;
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
        limpiarConsola();
        cout << "Surtidor no encontrado." << endl;
        return;
    }
    arreglo_surtidores[pos_est][var]->MostrarVentas();

}

void Red::SimulacionVenta(){
    string nombreArchivo = "baseDatos";
    string estSurtidor;
    short dia = leerDia(nombreArchivo);
    string metodo_pago, doc_cliente;
    int L_vendidos, dinero;

    cout<<"Estaciones:"<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }

    cout << "Ingrese la estacion donde se va a realizar la venta: " << endl;
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

    string hora = horaReal();
    int limite_s = contador_surtidores[pos_est];
    limite_s -= 1;
    short indice = randomNumero(0, limite_s, hora);
    string region = arreglo_estacion[pos_est]->getRegion();
    short tipo;
    limpiarConsola();
    cout<<"tipos de combustible: "<<endl;
    cout << "1. Regular" << endl;
    cout << "2. Premium" << endl;
    cout << "3. EcoExtra" << endl;
    cout << "Ingrese el tipo de combustible que quiere tanquear: ";
    cin >> tipo;

    short var;
    if (region == "norte") {
        var = 0;
    } else if (region == "centro") {
        var = 1;
    } else if (region == "sur") {
        var = 2;
    }
    limpiarConsola();
    int precio = precios[var][tipo - 1];
    cout << "Ingrese la cantidad de litros de gasolina: ";
    cin >> L_vendidos;

    L_vendidos = arreglo_estacion[pos_est]->MermarTanque(var, L_vendidos);
    bool metodoValido = false;
    while (!metodoValido) {
        cout << "Ingrese el metodo de pago (efectivo/Tarjeta): ";
        cin >> metodo_pago;
        if (metodo_pago == "efectivo" || metodo_pago == "tarjeta") {
            metodoValido = true;
        } else {
            cout << "Error: Metodo de pago invalido. Intente de nuevo." << endl;
        }
    }
    cout << "Ingrese el documento del cliente: ";
    cin >> doc_cliente;

    dinero = L_vendidos * precio;
    Venta* miVenta = new Venta(dia, hora, L_vendidos, metodo_pago, doc_cliente, dinero, tipo);
    arreglo_surtidores[pos_est][indice]->AgregarVenta(miVenta);
    arreglo_surtidores[pos_est][indice]->ventastipoC();

    // Guardar la venta en el archivo
    ofstream archivo(nombreArchivo, ios::app); // Abrir en modo append
    if (archivo.is_open()) {
        archivo << "Venta: " << dia << ", " << hora << ", " << L_vendidos << " litros, "
                << metodo_pago << ", " << doc_cliente << ", " << dinero << ", " << tipo << endl;
        archivo.close();
    } else {
        limpiarConsola();
        cout << "No se pudo abrir el archivo para guardar la venta." << endl;
    }

    limpiarConsola();
    cout << "Venta registrada exitosamente." << endl;
}


void Red::MontoTotalCombustible() {
    short contadorTotalR = 0;  // Inicializamos los contadores
    short contadorTotalP = 0;
    short contadorTotalE = 0;
    short total;
    short disponible;
    short vendido;

    cout << "Monto total de cada tipo de combustible por estacion y su total: " << endl;

    // Regular
    cout << "1. Regular: " << endl;
    for (short var = 0; var < capacidad_est; ++var) {
        disponible = arreglo_estacion[var]->getTanqueRegular();
        total = arreglo_estacion[var]->getTRegular();
        vendido = total - disponible;
        cout << "La estacion " << arreglo_estacion[var]->getNombre() << " vendio " << vendido << " litros de Regular" << endl;
        contadorTotalR += vendido;
    }
    cout << "El total de litros de Regular son: " << contadorTotalR << endl << endl;

    // Premium
    cout << "2. Premium: " << endl;
    for (int var = 0; var < capacidad_est; ++var) {
        disponible = arreglo_estacion[var]->getTanquePremiun();
        total = arreglo_estacion[var]->getTPremiun();
        vendido = total - disponible;
        cout << "La estacion " << arreglo_estacion[var]->getNombre() << " vendio " << vendido << " litros de Premium" << endl;
        contadorTotalP += vendido;
    }
    cout << "El total de litros de Premium son: " << contadorTotalP << endl << endl;

    // EcoExtra
    cout << "3. EcoExtra: " << endl;
    for (int var = 0; var < capacidad_est; ++var) {
        disponible = arreglo_estacion[var]->getTanqueEcoExtra();
        total = arreglo_estacion[var]->getTEcoExtra();
        vendido = total - disponible;
        cout << "La estacion " << arreglo_estacion[var]->getNombre() << " vendio " << vendido << " litros de EcoExtra" << endl;
        contadorTotalE += vendido;
    }
    cout << "El total de litros de EcoExtra son: " << contadorTotalE << endl;
}
void Red::MontoTotalVentas(){
    cout<<"monto total de ventas por cada tipo de combustible: "<<endl;
    short contador;
    int totalR=0;
    int totalP=0;
    int totalE=0;
    for (int var = 0; var <capacidad_est ; ++var) {
        contador=contador_surtidores[var];
        for (int j = 0; j < contador; ++j) {
            totalR=arreglo_surtidores[var][j]->getTR();
            totalP=arreglo_surtidores[var][j]->getTP();
            totalE=arreglo_surtidores[var][j]->getTE();
        }
    }
    cout<<"el total de ventas de cada combustible es: "<<endl;
    cout<<"regular: ";
    cout<<totalR<<endl;
    cout<<"premium: ";
    cout<<totalP<<endl;
    cout<<"EcoExtra: ";
    cout<<totalE<<endl;

}

void Red::GuardarVentas(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para guardar las ventas." << endl;
        return;
    }

    for (int i = 0; i < capacidad_est; ++i) {
        if (arreglo_estacion[i] != nullptr) {
            archivo << "Estacion: " << arreglo_estacion[i]->getNombre() << endl;
            archivo << "ID: " << arreglo_estacion[i]->getID_est() << endl;

            for (int j = 0; j < contador_surtidores[i]; ++j) {
                if (arreglo_surtidores[i][j] != nullptr) {
                    archivo << "  Surtidor: " << arreglo_surtidores[i][j]->getNombre() << endl;

                    Venta** ventas = arreglo_surtidores[i][j]->getVentas();
                    int num_ventas = arreglo_surtidores[i][j]->getNumVentas();

                    for (int k = 0; k < num_ventas; ++k) {
                        if (ventas[k] != nullptr) {
                            archivo << "    ID Venta: " << ventas[k]->getID() << endl;
                            archivo << "    Documento Cliente: " << ventas[k]->getDoc_cliente() << endl;
                            archivo << "    Litros Vendidos: " << ventas[k]->getL_vendidos() << endl;
                            archivo << "    Dinero Ingresado: " << ventas[k]->getDinero() << endl;
                            archivo << "    Método: " << ventas[k]->getMetodo_pago() << endl;
                            archivo << "    Fecha: " << ventas[k]->getFecha() << endl;
                            archivo << "    Hora: " << ventas[k]->getHora() << endl;
                        }
                    }
                }
            }
        }
    }

    archivo.close();
    cout << "Ventas guardadas exitosamente en " << nombreArchivo << endl;
}

Red::~Red() {
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
}

