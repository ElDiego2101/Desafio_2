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
    limpiarConsola();
    cout<<"precios regulados con exito"<<endl;

}


void Red::AgregarEstacion()
{
    string nombre, ID, gerente, region, P_Geo;
    string hora=horaReal();
    int tanqueRegular=randomNumero(100,200,hora);
    int tanquePremiun=randomNumero(100,200,hora);
    int tanqueEcoExtra=randomNumero(100,200,hora);
    cout << "Ingrese el nombre de la nueva estacion: ";
    cin >> nombre;
    cout << "Ingrese el ID de la estacion: ";
    cin >> ID;
    cout << "Ingrese el gerente de la estacion: ";
    cin >> gerente;
    cout << "Ingrese la region (norte, centro, sur): ";
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
    arreglo_estacion[pos_est] = new Estacion(nombre, ID, gerente, region, P_Geo, tanqueRegular,tanquePremiun,tanqueEcoExtra);

    limpiarConsola();
    cout << endl << "Estacion agregada con exito." << endl;
    cout << "Por favor ingrese dos surtidores a la estacion: " << endl;
    for(int i = 0;i<2;i++){
        cout << "Ingrese el ID del surtidor: ";
        cin >> ID;
        cout << "Ingrese el modelo del surtidor: ";
        cin >> nombre;
        nuevo_arreglo_surtidores[pos_est][i] = new Surtidor(ID, nombre, true);
        limpiarConsola();
        cout << endl << "*Surtidor creado con exito*" << endl;
    }
    arreglo_surtidores = nuevo_arreglo_surtidores;
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

    for(int i = 0; i < capacidad_est; i++) {
        if(est_elim == arreglo_estacion[i]->getNombre()) {
            pos_est_elim = i;
        }
    }

    if(pos_est_elim < 0) {
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
    cout<<"estacion eliminada con exito"<<endl;
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

    cout<<"Estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout <<"-"<< arreglo_estacion[i]->getNombre() << endl;
    }

    cout << "Ingrese el nombre de la estacion a la que quiere agregar un surtidor: " << endl;
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

    limpiarConsola();
    cout << endl << "*Surtidor agregado con exito.*" << endl;
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

    limpiarConsola();
    cout << "*Surtidor '" << surtidor << "' eliminado con exito.*" << endl;





}
void Red::EstadoSurtidor(){
    string estSurtidor;
    cout<<"estaciones: "<<endl;
    for (int i = 0; i < capacidad_est; i++) {
        cout << endl << arreglo_estacion[i]->getNombre() << endl;
    }

    cout << "Ingrese el nombre de la estación a la que quiere modificar un surtidor: " << endl;
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
    limpiarConsola();

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
    short tipo;
    cout<<"1.Regular"<<endl;
    cout<<"2.Premium"<<endl;
    cout<<"3.EcoExtra"<<endl;
    cout<<"ingrese el tipo de combustible que quiere tanquear"<<endl;
    cin>>tipo;
    short var;
    if(region=="norte"){
        var=1;
    }else if(region=="centro"){
        var=2;
    }else if(region=="sur"){
        var=3;
    }
    int precio=precios[var][tipo-1];
    cout << "Ingrese la cantidad de litros de gasolina: ";
    L_vendidos=arreglo_estacion[pos_est]->MermarTanque(var,L_vendidos);
    cout << "Ingrese el metodo de pago (Efectivo/Tarjeta): ";
    cin >> metodo_pago;
    cout << "Ingrese el documento del cliente: ";
    cin >> doc_cliente;
    dinero=L_vendidos*precio;
    Venta* miVenta = new Venta(dia, hora, L_vendidos, metodo_pago, doc_cliente, dinero,tipo);
    arreglo_surtidores[pos_est][indice]->AgregarVenta(miVenta);
    arreglo_surtidores[pos_est][indice]->ventastipoC();
    Venta** nuevo_arreglo_ventas = new Venta*[capacidad + 1];
    for (int i = 0; i < capacidad; ++i) {
        nuevo_arreglo_ventas[i] = arreglo_ventas[i];
    }
    nuevo_arreglo_ventas[capacidad] = miVenta;
    arreglo_ventas = nuevo_arreglo_ventas;
    capacidad++;
    limpiarConsola();
    cout << "Venta registrada exitosamente." << endl;
}


void Red::MontoTotalCombustible(){
    short contadorTotalR;
    short contadorTotalP;
    short contadorTotalE;
    short total;
    short disponible;
    short vendido;
    cout<<"1.Regular"<<endl;
    for (int var = 0; var < capacidad_est; ++var) {
        disponible=arreglo_estacion[var]->getTanqueRegular();
        total=arreglo_estacion[var]->getTRegular();
        vendido=total-disponible;
        cout<<"la estacion: "<<arreglo_estacion[var]->getNombre()<<" vendio "<<vendido<<" litros de regular"<<endl;
        contadorTotalR+=vendido;
    }
    cout<<""<<endl;
    cout<<"el total de litros de regular son: "<<contadorTotalR<<endl;

    cout<<"2.Premium"<<endl;
    for (int var = 0; var < capacidad_est; ++var) {
        disponible=arreglo_estacion[var]->getTanquePremiun();
        total=arreglo_estacion[var]->getTanquePremiun();
        vendido=total-disponible;
        cout<<"la estacion: "<<arreglo_estacion[var]->getNombre()<<" vendio "<<vendido<<" litros de premium"<<endl;
        contadorTotalP+=vendido;
    }
    cout<<""<<endl;
    cout<<"el total de litros de premium son: "<<contadorTotalP<<endl;


    cout<<"3.EcoExtra"<<endl;
    for (int var = 0; var < capacidad_est; ++var) {
        disponible=arreglo_estacion[var]->getTanqueEcoExtra();
        total=arreglo_estacion[var]->getTanqueEcoExtra();
        vendido=total-disponible;
        cout<<"la estacion: "<<arreglo_estacion[var]->getNombre()<<" vendio "<<vendido<<" litros de EcoExtra"<<endl;
        contadorTotalE+=vendido;
    }
    cout<<""<<endl;
    cout<<"el total de litros de EcoExtra son: "<<contadorTotalE<<endl;
}

void Red::MontoTotalVentas(){
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
    cout<<"regular: "<<endl;
    cout<<totalR<<endl;
    cout<<"premium"<<endl;
    cout<<totalP<<endl;
    cout<<"EcoExtra"<<endl;
    cout<<totalE<<endl;

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
