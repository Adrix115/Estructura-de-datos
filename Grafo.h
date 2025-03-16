#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Grafo {
private:
    int V;        // Número de nodos
    int** adj;    // Matriz de adyacencia
    bool esDirigido; // Verifica si el grafo es dirigido o no
    bool esEtiquetado; // Verifica si el grafo es etiquetado o no
    string* etiquetas; // Arreglo dinámico de etiquetas para los nodos

public:
    Grafo() : V(0), adj(nullptr), esDirigido(false), esEtiquetado(false), etiquetas(nullptr) {}

    ~Grafo() {
        liberarMemoria();
    }

    void liberarMemoria() {
        if (adj) {
            for (int i = 0; i < V; i++) {
                delete[] adj[i];
            }
            delete[] adj;
            adj = nullptr;
        }
        if (etiquetas) {
            delete[] etiquetas;
            etiquetas = nullptr;
        }
    }

    void inicializarGrafo(int numNodos, bool dirigido, bool etiquetado) {
        liberarMemoria();
        V = numNodos;
        esDirigido = dirigido;
        esEtiquetado = etiquetado;
        adj = new int* [V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V]();
        }
        if (esEtiquetado) {
            etiquetas = new string[V];
            for (int i = 0; i < V; i++) {
                etiquetas[i] = "Nodo " + to_string(i);
            }
        }
        else {
            etiquetas = nullptr;
        }
    }

    // NUEVA FUNCIÓN: Agregar un nodo al grafo
    void agregarNodo() {
        int nuevoV = V + 1;
        // Crear nueva matriz de adyacencia de tamaño nuevoV x nuevoV
        int** nuevaAdj = new int* [nuevoV];
        for (int i = 0; i < nuevoV; i++) {
            nuevaAdj[i] = new int[nuevoV](); // Inicializa con 0
        }
        // Copiar datos de la matriz antigua
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                nuevaAdj[i][j] = adj[i][j];
            }
        }
        // Liberar la matriz antigua y asignar la nueva
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        adj = nuevaAdj;
        // Si el grafo es etiquetado, copiar etiquetas y asignar una por defecto al nuevo nodo
        if (esEtiquetado) {
            string* nuevasEtiquetas = new string[nuevoV];
            for (int i = 0; i < V; i++) {
                nuevasEtiquetas[i] = etiquetas[i];
            }
            nuevasEtiquetas[V] = "Nodo " + to_string(V);
            delete[] etiquetas;
            etiquetas = nuevasEtiquetas;
        }
        V = nuevoV;
        cout << "Nodo agregado correctamente. Nuevo total de nodos: " << V << "\n";
    }

    void agregarArista(int u, int v) {
        if (u >= V || v >= V) {
            cout << "Error: uno de los nodos no existe.\n";
            return;
        }
        adj[u][v] = 1;
        if (!esDirigido) {
            adj[v][u] = 1;
        }
    }

    void eliminarArista(int u, int v) {
        if (u >= V || v >= V) {
            cout << "Error: uno de los nodos no existe.\n";
            return;
        }
        adj[u][v] = 0;
        if (!esDirigido) {
            adj[v][u] = 0;
        }
        cout << "Arista eliminada entre " << u << " y " << v << "\n";
    }

    void eliminarNodo(int nodo) {
        if (nodo >= V) {
            cout << "Error: el nodo no existe.\n";
            return;
        }
        int nuevoV = V - 1;
        int** nuevaAdj = new int* [nuevoV];
        for (int i = 0; i < nuevoV; i++) {
            nuevaAdj[i] = new int[nuevoV]();
        }
        string* nuevasEtiquetas = nullptr;
        if (esEtiquetado) {
            nuevasEtiquetas = new string[nuevoV];
        }
        for (int i = 0, ni = 0; i < V; i++) {
            if (i == nodo)
                continue;
            for (int j = 0, nj = 0; j < V; j++) {
                if (j == nodo)
                    continue;
                nuevaAdj[ni][nj] = adj[i][j];
                nj++;
            }
            if (esEtiquetado) {
                nuevasEtiquetas[ni] = etiquetas[i];
            }
            ni++;
        }
        liberarMemoria();
        adj = nuevaAdj;
        if (esEtiquetado) {
            etiquetas = nuevasEtiquetas;
        }
        V = nuevoV;
        cout << "Nodo " << nodo << " eliminado correctamente.\n";
    }

    void agregarEtiqueta(int nodo, const string& etiqueta) {
        if (!esEtiquetado) {
            cout << "Este grafo no es etiquetado.\n";
            return;
        }
        if (nodo >= V) {
            cout << "Error: el nodo no existe.\n";
            return;
        }
        etiquetas[nodo] = etiqueta;
    }

    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "Archivo no encontrado. Creando uno nuevo...\n";
            return;
        }
        string linea;
        int numNodos = 0;
        bool dirigido = false;
        bool etiquetado = false;
        // Leer configuración y número de nodos
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string palabra;
            ss >> palabra;
            if (palabra == "Dirigido:") {
                string tipo;
                ss >> tipo;
                dirigido = (tipo == "Si");
            }
            else if (palabra == "Etiquetado:") {
                string tipo;
                ss >> tipo;
                etiquetado = (tipo == "Si");
            }
            else if (palabra == "Nodos:") {
                ss >> numNodos;
                inicializarGrafo(numNodos, dirigido, etiquetado);
            }
            else if (palabra == "Aristas:") {
                // Leer aristas hasta encontrar la sección de etiquetas (si la hay)
                while (getline(archivo, linea)) {
                    if (linea.find("Etiquetas:") != string::npos) {
                        break;
                    }
                    if (linea.empty())
                        continue;
                    stringstream aristaStream(linea);
                    int u, v;
                    char guion;
                    if (aristaStream >> u >> guion >> v) {
                        agregarArista(u, v);
                    }
                }
                // Leer etiquetas si corresponde
                if (esEtiquetado) {
                    for (int i = 0; i < V; i++) {
                        if (getline(archivo, linea)) {
                            stringstream ss2(linea);
                            int idx;
                            char colon;
                            string et;
                            ss2 >> idx >> colon;
                            getline(ss2, et);
                            if (!et.empty() && et[0] == ' ')
                                et.erase(0, 1);
                            etiquetas[idx] = et;
                        }
                    }
                }
                break; // Se terminó de leer aristas (y etiquetas)
            }
        }
        archivo.close();
        cout << "Grafo cargado correctamente desde " << nombreArchivo << "\n";
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "Error al abrir el archivo para escritura.\n";
            return;
        }
        archivo << "Dirigido: " << (esDirigido ? "Si" : "No") << "\n";
        archivo << "Etiquetado: " << (esEtiquetado ? "Si" : "No") << "\n";
        archivo << "Nodos: " << V << "\n";
        archivo << "Aristas:\n";
        if (esDirigido) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (adj[i][j] == 1) {
                        archivo << i << " - " << j << "\n";
                    }
                }
            }
        }
        else {
            for (int i = 0; i < V; i++) {
                for (int j = i + 1; j < V; j++) {
                    if (adj[i][j] == 1) {
                        archivo << i << " - " << j << "\n";
                    }
                }
            }
        }
        if (esEtiquetado) {
            archivo << "Etiquetas:\n";
            for (int i = 0; i < V; i++) {
                archivo << i << ": " << etiquetas[i] << "\n";
            }
        }
        archivo.close();
        cout << "Grafo guardado en " << nombreArchivo << " correctamente.\n";
    }

    void mostrarListaAdyacencia() {
        cout << "Lista de adyacencia:\n";
        for (int i = 0; i < V; i++) {
            if (esEtiquetado)
                cout << i << " (" << etiquetas[i] << ") -> ";
            else
                cout << i << " -> ";
            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1) {
                    if (esEtiquetado)
                        cout << j << " (" << etiquetas[j] << ") ";
                    else
                        cout << j << " ";
                }
            }
            cout << "\n";
        }
    }

    void dfs(int nodo, bool* visitado) {
        visitado[nodo] = true;
        if (esEtiquetado)
            cout << nodo << " (" << etiquetas[nodo] << ") ";
        else
            cout << nodo << " ";
        for (int i = 0; i < V; i++) {
            if (!visitado[i] && adj[nodo][i] == 1)
                dfs(i, visitado);
        }
    }

    void recorridoDFS(int inicio) {
        bool* visitado = new bool[V]();
        cout << "Recorrido en profundidad (DFS): ";
        if (inicio >= 0 && inicio < V) {
            dfs(inicio, visitado);
        }
        else {
            cout << "Nodo inicial inválido.";
        }
        cout << "\n";
        delete[] visitado;
    }

    void bfs(int inicio) {
        if (inicio >= V) {
            cout << "Error: el nodo de inicio no existe.\n";
            return;
        }
        bool* visitado = new bool[V]();
        queue<int> q;
        visitado[inicio] = true;
        q.push(inicio);
        cout << "Recorrido en amplitud (BFS): ";
        while (!q.empty()) {
            int nodo = q.front();
            q.pop();
            if (esEtiquetado)
                cout << nodo << " (" << etiquetas[nodo] << ") ";
            else
                cout << nodo << " ";
            for (int i = 0; i < V; i++) {
                if (!visitado[i] && adj[nodo][i] == 1) {
                    visitado[i] = true;
                    q.push(i);
                }
            }
        }
        cout << "\n";
        delete[] visitado;
    }

    void recorridoBFS() {
        cout << "Ingrese el nodo de inicio para BFS: ";
        int inicio;
        cin >> inicio;
        bfs(inicio);
    }

    void mostrarMatrizAdyacencia() {
        cout << "Matriz de adyacencia:\n  ";
        if (esEtiquetado) {
            for (int i = 0; i < V; i++) {
                cout << etiquetas[i] << " ";
            }
            cout << "\n";
            for (int i = 0; i < V; i++) {
                cout << etiquetas[i] << " ";
                for (int j = 0; j < V; j++) {
                    cout << adj[i][j] << " ";
                }
                cout << "\n";
            }
        }
        else {
            for (int i = 0; i < V; i++) {
                cout << i << " ";
            }
            cout << "\n";
            for (int i = 0; i < V; i++) {
                cout << i << " ";
                for (int j = 0; j < V; j++) {
                    cout << adj[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }
};
