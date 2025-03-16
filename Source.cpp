#include "Grafo.h"

int main() {
    Grafo grafo;
    string nombreArchivo = "grafo.txt";
    ifstream archivo(nombreArchivo);
    bool dirigido, etiquetado = true;
    if (archivo) {
        // Si el archivo existe, se carga el grafo desde él
        grafo.cargarDesdeArchivo(nombreArchivo);
    }
    else {
        cout << "El grafo es dirigido? (1 = Si, 0 = No): ";
        cin >> dirigido;
        cout << "El grafo es etiquetado? (1 = Si, 0 = No): ";
        cin >> etiquetado;
        cout << "Ingrese el numero de nodos: ";
        int numNodos;
        cin >> numNodos;
        grafo.inicializarGrafo(numNodos, dirigido, etiquetado);
    }
    archivo.close(); 

    int opcion, u, v, nodo;
    string etiqueta;
    do {
        cout << "\nMENU DE GRAFOS\n";
        cout << "\n1. Agregar arista\n";
        cout << "2. Eliminar arista\n";
        cout << "3. Eliminar nodo\n";
        cout << "4. Agregar etiqueta a nodo\n";
        cout << "5. Mostrar lista de adyacencia\n";
        cout << "6. Agregar nodo\n"; 
        cout << "7. Guardar y salir\n";
        cout << "8. Recorrido en BFS\n";
        cout << "9. Recorrido en DFS\n";
        cout << "10. Matriz de Adyacencia\n\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "Ingrese nueva arista (u v): ";
            cin >> u >> v;
            grafo.agregarArista(u, v);
            break;
        case 2:
            cout << "Ingrese la arista a eliminar (u v): ";
            cin >> u >> v;
            grafo.eliminarArista(u, v);
            break;
        case 3:
            cout << "Ingrese el nodo a eliminar: ";
            cin >> nodo;
            grafo.eliminarNodo(nodo);
            break;
        case 4:
            if (etiquetado) {
                cout << "Ingrese el nodo y su etiqueta: ";
                cin >> nodo >> etiqueta;
                grafo.agregarEtiqueta(nodo, etiqueta);
            }
            else {
                cout << "Este grafo no admite etiquetas.\n";
            }
            break;
        case 5:
            grafo.mostrarListaAdyacencia();
            break;
        case 6:
            grafo.agregarNodo();
            break;
        case 7:
            grafo.guardarEnArchivo(nombreArchivo);
            cout << "Guardando y saliendo...\n";
            break;
        case 8:
            grafo.recorridoBFS();
            break;
        case 9:
            cout << "Ingrese el nodo de inicio para DFS: ";
            cin >> nodo;
            grafo.recorridoDFS(nodo);
            break;
        case 10:
            grafo.mostrarMatrizAdyacencia();
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
    } while (opcion != 7);
    return 0;
}
