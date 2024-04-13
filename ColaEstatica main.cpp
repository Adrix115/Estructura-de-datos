#include "Cola.h"

int main()
{
    Cola cola;
    int opcion, Valor;
    do
    {
        cout << "Menú de opciones:" << endl;
        cout << "1. Encolar" << endl;
        cout << "2. Desencolar" << endl;
        cout << "3. Mostrar cola" << endl;
        cout << "4. Vaciar cola" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            int elemento;
            cout << "Ingrese el valor a encolar: ";
            cin >> elemento;
            cola.Encolar(elemento);
            break;
        case 2:
            cola.Desencolar();
            break;
        case 3:
            cola.mostrar();
            break;
        case 4:
            cola.VaciarCola();
            break;
        case 5:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción no valida." << endl;
            break;
        }
    } while (opcion != 5);

    return 0;
}