#include "Cola.h"

Cola::Cola() {

}

void Cola::Encolar(Nodo*& inicio, Nodo*& fin) { //Punteros enviados por referencia      
    Nodo* Elemento = new Nodo; //Creacion del nodo
    if (inicio == NULL) {
        inicio = fin = Elemento; 

        cout << "Codigo: "; cin >> Elemento->dato.Codigo;
        cin.ignore();
        cout << "Nombres: "; getline(cin, Elemento->dato.Nombre);
        cout << "Carrera: "; getline(cin, Elemento->dato.Carrera);
        
    }
    else {
        fin->puntero = Elemento; 
        fin = Elemento; 
        cout << "Codigo: "; cin >> Elemento->dato.Codigo;
        cin.ignore();
        cout << "Nombres: "; getline(cin, Elemento->dato.Nombre);
        cout << "Carrera: "; getline(cin, Elemento->dato.Carrera);
        cout << endl;
  
    }
}

void Cola::Desencolar(Nodo*& inicio) {
    if (inicio != NULL) {
        cout << "Codigo: " << inicio->dato.Codigo << endl;
        cout << "Nombres: " << inicio->dato.Nombre << endl;
        cout << "Carrera: " << inicio->dato.Carrera << endl;
        inicio = inicio->puntero; 
    }
    else {
        cout << "La cola se encuentra vacia" << endl;
    }
}
 void Cola::MostrarCola(Nodo*& inicio){
        Nodo* actual = inicio;
        cout << "Cola: "<<endl;
        while (actual != NULL) {
            cout<< actual->dato<<" "<<endl;
            actual = actual->puntero;
        }
        cout << endl;
    }