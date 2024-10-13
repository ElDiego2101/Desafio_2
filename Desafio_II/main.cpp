#include <iostream>
#include "red.h"
#include "complementario.h"
using namespace std;


int main() {
    char opcion;
    bool ban = true;
    Red TerMex;
    string hora=horaReal();
    cout<<hora<<endl;
    cout << "**Bienvenido a la red de combustible 'TerMax'.**" << endl << endl;
    while (ban) {
        cout << endl << "*Ingrese la opcion deseada.*" << endl
             << "1. Agregar una estacion de servicio (E/S)." << endl
             << "2. Eliminar una (E/S) de la red nacional." << endl
             << "3. Monto total de ventas para cada tipo de combustible." << endl
             << "4. Agregar un surtidor a una (E/S)." << endl
             << "5. Eliminar un surtidor de una (E/S)." << endl
             << "6. Consultar las transacciones de los surtidores de una (E/S)." << endl
             << "7. Activar un surtidor de una (E/S)." << endl
             << "8. Desactivar un surtidor de una (E/S)." << endl
             << "9. Cantidad de litros vendidos para cada categoria de combustible." << endl
             << "M. Simulacion de una venta de combustible." << endl
             << "N. Salir." << endl << endl

             << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion){
        case '1':
          limpiarConsola();
          TerMex.AgregarEstacion();
            break;
        case '2':
            limpiarConsola();
            TerMex.EliminarEstacion();
            break;
        case '3':
            break;
        case '4':
            limpiarConsola();
            TerMex.AgregarSurtidor();
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            limpiarConsola();
            TerMex.EstadoSurtidor();
            break;
        case '8':
            break;
        case '9':
            break;
        case 'M':
            break;
        case 'N':
            break;
        case 'J':
            limpiarConsola();
           TerMex.consulta();
            break;
        default:
            cout<<"elija una opcion valida"<<endl;


        }

    }

    return 0;
}
