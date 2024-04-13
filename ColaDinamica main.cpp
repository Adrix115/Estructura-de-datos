#include "Cola.h"

int main() {
    Cola cola;
    Nodo* inicio = NULL, * fin = NULL; //Punteros libres para el manejo de la cola
    int opcion = 0;
    do {
        cout << "MENU DE COLA" << endl;
        cout << "1. Empty" << endl;
        cout << "2. Push" << endl;
        cout << "3. Pop" << endl;
        cout << "4. Show" << endl;
        cout << "5. End" << endl;
        cout << "Opcion: "; cin >> opcion;
        switch (opcion) {
        case 1:
            if (inicio == NULL)
                cout << "La cola se encuentra vacia" << endl;
            else
                cout << "Existe(n) elemento(s) dentro de la cola" << endl;
            break;
        case 2:
            cola.Encolar(inicio, fin);
            break;
        case 3:
            cola.Desencolar(inicio);
            break;
        case 4:
            cola.MostrarCola(inicio);
            break;
        default:
            cout << "Seleccione una opcion disponible" << endl;
            break;
        }
    } while (opcion != 5);

    return 0;
}