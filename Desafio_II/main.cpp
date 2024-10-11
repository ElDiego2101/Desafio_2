#include <iostream>
#include "red.h"
using namespace std;


int main() {
    char opcion;
    bool ban = true;
    Red TerMex;
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

        if (opcion == '1') {
            TerMex.AgregarEstacion();
        } else if (opcion == '2') {
            TerMex.EliminarEstacion();
        } else if (opcion == '3') {

        } else if (opcion == '4') {

        } else if (opcion == '5') {

        } else if (opcion == '6') {

        } else if (opcion == '7') {

        } else if (opcion == '8') {

        } else if (opcion == '9') {

        } else if (opcion == 'm' || opcion == 'M') {

        } else if (opcion == 'n' || opcion == 'N') {
            ban = false;
        } else if (opcion == 'a') {
            TerMex.consulta();
        }
    }

    return 0;
}
