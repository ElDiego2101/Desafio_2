#include <iostream>
#include "red.h"
#include "complementario.h"
#include "venta.h"
using namespace std;


int main() {
    string metodo_pago, doc_cliente,tipo;
    string nombreArchivo = "baseDatos";
    short dia = leerDia(nombreArchivo);
    string hora=horaReal();
    int L_vendidos,dinero;
    bool ver=true;
    bool ban = true;
    char opcion;
    Red TerMex;
    cout << "Dia actual: " << dia << endl;
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
             << "7. Cambiar estado de un surtidor." << endl
             << "8. Cantidad de litros vendidos para cada categoria de combustible." << endl
             << "9. Simulacion de una venta de combustible." << endl
             <<"M. Ajustar precios del combustible."<<endl
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
            limpiarConsola();
            TerMex.ELiminarSurtidor();
            break;
        case '6':
            break;
        case '7':
            limpiarConsola();
            TerMex.EstadoSurtidor();
            break;
        case '8':
            break;
        case '9'://marco el ambito de esas variables
        limpiarConsola();
        {
            cout<<"Ingrese el tipo de combustible que desea tanquear: "<<endl;

            cout << "Ingrese la cantidad de litros vendidos: ";
            cin >> L_vendidos;
            cout << "Ingrese el metodo de pago (Efectivo/Tarjeta): ";
            cin >> metodo_pago;
            cout << "Ingrese el documento del cliente: ";
            cin >> doc_cliente;
            cout << "Ingrese la cantidad de dinero recibida: ";
            cin >> dinero;

            // Crear un objeto de la clase Venta usando los datos proporcionados
            Venta miVenta(dia, hora, L_vendidos, metodo_pago, doc_cliente, dinero);
            cout<<miVenta.getID()<<endl;
            break;
        }
        case 'M':
            if(ver){
                TerMex.AjustarPrecios();
                ver=false;
            }else{
                cout<<"lo sentimos, espera al siguiente dia para ajustar los precios"<<endl;
            }
            break;
        case 'N':

            actualizarDia(nombreArchivo, dia);
            ban=false;
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
