#include "Pila.h"
Pila::Pila() {
    tope = -1;
}

void Pila::push(int& elemento) {
    if (pila_llena()) {
        cout << "La pila ha alcanzado su capacidad máxima." << endl;
    }
    else {
        tope++;
        vector[tope] = elemento;
        cout << "Elemento " << elemento << " insertado en la pila." << endl;
    }
}

bool Pila::pila_vacia() {
    return tope == -1;
}

bool Pila::pila_llena() {
    return tope == MAX - 1;
}

void Pila::pop() {
    if (pila_vacia()) {
        cout << "La pila está vacía. No se puede eliminar ningún elemento." << endl;
    }
    else {
        int eliminado = vector[tope];
        tope--;
        cout << "Elemento " << eliminado << " eliminado de la pila." << endl;
    }
}

void Pila::LimpiarPila() {
    tope = -1;
    cout << "La pila ha sido limpiada." << endl;
}

void Pila::ver_pila() {
    if (pila_vacia()) {
        cout << "La pila está vacía." << endl;
    }
    else {
        cout << "Elementos de la pila:" << endl;
        for (int i = tope; i >= 0; i--) {
            cout << vector[i] << endl;
        }
    }
}

bool Pila::Iguales(Pila& otra_pila) {
    if (tope != otra_pila.tope) {
        return false;
    }
    for (int i = 0; i <= tope; i++) {
        if (vector[i] != otra_pila.vector[i]) {
            return false;
        }
    }
    return true;
}
