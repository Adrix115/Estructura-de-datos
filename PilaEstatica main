#include "Pila.h"

int main() {
    int dato, n, opcion;
    Pila pila1, pila2;

    cout << "MENU" << endl;
    do {
        cout << "*****Pila en lista enlazada*****" << endl;
        cout << "[1]Push en Pila " << endl;
        cout << "[2]Pop en Pila " << endl;
        cout << "[3]Mostrar Pila " << endl;
        cout << "[4]Limpiar Pila " << endl;
        cout << "[5]Iguales" << endl;
        cout << "[0]Salir" << endl;
        cout << "\nIngresa tu opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "¿Cuantos elementos quieres introducir a la pila 1?: ";
            cin >> n;
            do {
                cout << "Digite el elemento de la pila 1: ";
                cin >> dato;
                pila1.push(dato);
                n--;
            } while (n > 0);
            break;
        case 2:
            pila1.pop();
            break;
        case 3:
            pila1.ver_pila();
            break;
        case 4:
            pila1.LimpiarPila();
            break;
        case 5:
            cout << "¿Cuantos elementos quieres introducir a la pila 2?: ";
            cin >> n;
            do {
                cout << "Digite el elemento de la pila 2: ";
                cin >> dato;
                pila2.push(dato);
                n--;
            } while (n > 0);
            if (pila1.Iguales(pila2)) {
                cout << "Las pilas son iguales." << endl;
            }
            else {
                cout << "Las pilas no son iguales." << endl;
            }
            break;
        case 0:
            return 0;
        default:
            cout << "Opcion no valida. Por favor ingresa una opción correcta." << endl;
            break;
        }
    } while (opcion != 0);

    return 0;
}
