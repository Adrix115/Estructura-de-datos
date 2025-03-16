#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Función auxiliar para obtener el máximo entre dos enteros.
int myMax(int a, int b) {
    return (a > b) ? a : b;
}

// Definición de nodo
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
    int height; // Usado en AVL
    TreeNode(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// Clase base abstracta para árboles
class BinaryTree {
protected:
    TreeNode* root;

    // Función para serializar el árbol en preorden con marcador '#' para nodos nulos.
    void serialize(ostream& out, TreeNode* node) {
        if (!node) {
            out << "# ";
            return;
        }
        out << node->value << " ";
        serialize(out, node->left);
        serialize(out, node->right);
    }

    // Función para deserializar el árbol a partir de la representación generada.
    TreeNode* deserialize(istream& in) {
        string token;
        if (!(in >> token))
            return nullptr;
        if (token == "#")
            return nullptr;
        int val = stoi(token);
        TreeNode* node = new TreeNode(val);
        node->left = deserialize(in);
        node->right = deserialize(in);
        int hl = (node->left ? node->left->height : 0);
        int hr = (node->right ? node->right->height : 0);
        node->height = 1 + myMax(hl, hr);
        return node;
    }

public:
    BinaryTree() : root(nullptr) {}
    virtual void insert(int value) = 0;
    virtual void remove(int value) = 0;

    // Recorridos: se pasa una referencia a un ostream para poder escribir en consola o archivo.
    void preOrder(TreeNode* node, ostream& out) {
        if (node) {
            out << node->value << " ";
            preOrder(node->left, out);
            preOrder(node->right, out);
        }
    }
    void inOrder(TreeNode* node, ostream& out) {
        if (node) {
            inOrder(node->left, out);
            out << node->value << " ";
            inOrder(node->right, out);
        }
    }
    void postOrder(TreeNode* node, ostream& out) {
        if (node) {
            postOrder(node->left, out);
            postOrder(node->right, out);
            out << node->value << " ";
        }
    }

    TreeNode* getRoot() { return root; }

    // Guarda la estructura completa del árbol en el archivo indicado.
    void saveTree(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error al abrir el archivo para guardar." << endl;
            return;
        }
        serialize(file, root);
        file.close();
        cout << "Arbol guardado en " << filename << endl;
    }

    // Carga la estructura completa del árbol desde el archivo indicado.
    void loadTree(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error al abrir el archivo para cargar." << endl;
            return;
        }
        root = deserialize(file);
        file.close();
        cout << "Arbol cargado desde " << filename << endl;
    }
};

// =======================================
// Árbol Binario Común (sin orden)
// =======================================
class CommonBinaryTree : public BinaryTree {
public:
    // Inserta de forma recursiva: si hay espacio en el subárbol izquierdo, lo usa; si no, en el derecho; 
    // en caso de tener ambos hijos, se recurre al subárbol izquierdo.
    void insert(int value) override {
        if (!root)
            root = new TreeNode(value);
        else
            insertRec(root, value);
    }

    // Eliminación de nodo en árbol binario común.
    void remove(int value) override {
        root = removeNode(root, value);
    }

private:
    void insertRec(TreeNode* node, int value) {
        if (!node->left) {
            node->left = new TreeNode(value);
            return;
        }
        else if (!node->right) {
            node->right = new TreeNode(value);
            return;
        }
        else {
            // Se inserta en el subárbol izquierdo (método simple; podría alternarse para balancear)
            insertRec(node->left, value);
        }
    }

    // Función para eliminar un nodo en un árbol binario común usando recorrido en nivel.
    TreeNode* removeNode(TreeNode* root, int value) {
        if (!root)
            return root;

        // Si el árbol tiene un solo nodo
        if (!root->left && !root->right) {
            if (root->value == value) {
                delete root;
                return nullptr;
            }
            else {
                return root;
            }
        }

        TreeNode* keyNode = nullptr;
        TreeNode* lastNode = nullptr;
        TreeNode* parentOfLast = nullptr;

        // Usamos un arreglo fijo para simular una cola (tamaño máximo 100 nodos)
        TreeNode* queue[100];
        int front = 0, rear = 0;
        queue[rear++] = root;
        while (front < rear) {
            TreeNode* temp = queue[front++];
            if (temp->value == value)
                keyNode = temp;
            if (temp->left) {
                parentOfLast = temp;
                queue[rear++] = temp->left;
            }
            if (temp->right) {
                parentOfLast = temp;
                queue[rear++] = temp->right;
            }
            lastNode = temp;
        }

        if (keyNode) {
            // Reemplazamos el valor del nodo a eliminar por el del nodo más profundo (último en nivel)
            keyNode->value = lastNode->value;
            // Ahora eliminamos el último nodo
            if (parentOfLast) {
                if (parentOfLast->right == lastNode)
                    parentOfLast->right = nullptr;
                else if (parentOfLast->left == lastNode)
                    parentOfLast->left = nullptr;
            }
            else {
                // Si no hay padre, el árbol se queda vacío
                root = nullptr;
            }
            delete lastNode;
        }
        return root;
    }
};

// =======================================
// Árbol Binario de Búsqueda (BST)
// =======================================
class BinarySearchTree : public BinaryTree {
public:
    void insert(int value) override {
        root = insertRec(root, value);
    }

    void remove(int value) override {
        root = deleteRec(root, value);
    }

private:
    TreeNode* insertRec(TreeNode* node, int value) {
        if (!node)
            return new TreeNode(value);
        if (value < node->value)
            node->left = insertRec(node->left, value);
        else
            node->right = insertRec(node->right, value);
        return node;
    }

    // Función para encontrar el nodo mínimo en el subárbol derecho.
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    TreeNode* deleteRec(TreeNode* node, int value) {
        if (!node)
            return node;
        if (value < node->value)
            node->left = deleteRec(node->left, value);
        else if (value > node->value)
            node->right = deleteRec(node->right, value);
        else {
            // Nodo encontrado
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (!temp) { // Sin hijos
                    temp = node;
                    node = nullptr;
                }
                else { // Con un hijo
                    *node = *temp;
                }
                delete temp;
            }
            else {
                // Nodo con dos hijos: se busca el sucesor (menor en el subárbol derecho)
                TreeNode* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = deleteRec(node->right, temp->value);
            }
        }
        return node;
    }
};

// =======================================
// Árbol AVL
// =======================================
class AVLTree : public BinaryTree {
public:
    void insert(int value) override {
        root = insertRec(root, value);
    }

    void remove(int value) override {
        root = deleteRec(root, value);
    }

private:
    int getHeight(TreeNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(TreeNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = myMax(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = myMax(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    TreeNode* insertRec(TreeNode* node, int value) {
        if (!node)
            return new TreeNode(value);
        if (value < node->value)
            node->left = insertRec(node->left, value);
        else if (value > node->value)
            node->right = insertRec(node->right, value);
        else
            return node; // Valores duplicados no se insertan

        node->height = 1 + myMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Rotación simple o doble según corresponda
        if (balance > 1 && value < node->left->value)
            return rotateRight(node);
        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    // Función auxiliar similar a la de BST para encontrar el nodo mínimo.
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    TreeNode* deleteRec(TreeNode* node, int value) {
        if (!node)
            return node;
        if (value < node->value)
            node->left = deleteRec(node->left, value);
        else if (value > node->value)
            node->right = deleteRec(node->right, value);
        else {
            // Nodo encontrado
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (!temp) { // Sin hijos
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                TreeNode* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = deleteRec(node->right, temp->value);
            }
        }
        if (!node)
            return node;
        node->height = 1 + myMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
};

// =======================================
// Menú principal
// =======================================
int main() {
    // Se crean instancias de cada árbol
    CommonBinaryTree commonTree;
    BinarySearchTree bst;
    AVLTree avl;

    int op, value;
    do {
        cout << "\n--- Menu Principal Arboles ---\n";
        cout << "1. Insertar en Arbol Binario Comun\n";
        cout << "2. Insertar en Arbol Binario de Busqueda (BST)\n";
        cout << "3. Insertar en Arbol AVL\n";
        cout << "4. Eliminar en Arbol Binario Comun\n";
        cout << "5. Eliminar en BST\n";
        cout << "6. Eliminar en AVL\n";
        cout << "7. Recorrido Preorden (Comun)\n";
        cout << "8. Recorrido Inorden (Comun)\n";
        cout << "9. Recorrido Postorden (Comun)\n";
        cout << "10. Recorrido Preorden (BST)\n";
        cout << "11. Recorrido Inorden (BST)\n";
        cout << "12. Recorrido Postorden (BST)\n";
        cout << "13. Recorrido Preorden (AVL)\n";
        cout << "14. Recorrido Inorden (AVL)\n";
        cout << "15. Recorrido Postorden (AVL)\n";
        cout << "16. Guardar Arbol Comun (estructura completa)\n";
        cout << "17. Cargar Arbol Comun (estructura completa)\n";
        cout << "18. Guardar BST (estructura completa)\n";
        cout << "19. Cargar BST (estructura completa)\n";
        cout << "20. Guardar AVL (estructura completa)\n";
        cout << "21. Cargar AVL (estructura completa)\n";
        cout << "22. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        // Variables para manejo de archivos en recorridos
        ofstream file;
        switch (op) {
        case 1:
            cout << "Valor a insertar en Arbol Comun: ";
            cin >> value;
            commonTree.insert(value);
            break;
        case 2:
            cout << "Valor a insertar en BST: ";
            cin >> value;
            bst.insert(value);
            break;
        case 3:
            cout << "Valor a insertar en AVL: ";
            cin >> value;
            avl.insert(value);
            break;
        case 4:
            cout << "Valor a eliminar en Arbol Comun: ";
            cin >> value;
            commonTree.remove(value);
            break;
        case 5:
            cout << "Valor a eliminar en BST: ";
            cin >> value;
            bst.remove(value);
            break;
        case 6:
            cout << "Valor a eliminar en AVL: ";
            cin >> value;
            avl.remove(value);
            break;
        case 7: {
            cout << "Preorden (Comun): ";
            commonTree.preOrder(commonTree.getRoot(), cout);
            cout << endl;
            file.open("preorder_common.txt");
            if (file.is_open()) {
                commonTree.preOrder(commonTree.getRoot(), file);
                file.close();
                cout << "Guardado en preorder_common.txt" << endl;
            }
            break;
        }
        case 8: {
            cout << "Inorden (Comun): ";
            commonTree.inOrder(commonTree.getRoot(), cout);
            cout << endl;
            file.open("inorder_common.txt");
            if (file.is_open()) {
                commonTree.inOrder(commonTree.getRoot(), file);
                file.close();
                cout << "Guardado en inorder_common.txt" << endl;
            }
            break;
        }
        case 9: {
            cout << "Postorden (Comun): ";
            commonTree.postOrder(commonTree.getRoot(), cout);
            cout << endl;
            file.open("postorder_common.txt");
            if (file.is_open()) {
                commonTree.postOrder(commonTree.getRoot(), file);
                file.close();
                cout << "Guardado en postorder_common.txt" << endl;
            }
            break;
        }
        case 10: {
            cout << "Preorden (BST): ";
            bst.preOrder(bst.getRoot(), cout);
            cout << endl;
            file.open("preorder_bst.txt");
            if (file.is_open()) {
                bst.preOrder(bst.getRoot(), file);
                file.close();
                cout << "Guardado en preorder_bst.txt" << endl;
            }
            break;
        }
        case 11: {
            cout << "Inorden (BST): ";
            bst.inOrder(bst.getRoot(), cout);
            cout << endl;
            file.open("inorder_bst.txt");
            if (file.is_open()) {
                bst.inOrder(bst.getRoot(), file);
                file.close();
                cout << "Guardado en inorder_bst.txt" << endl;
            }
            break;
        }
        case 12: {
            cout << "Postorden (BST): ";
            bst.postOrder(bst.getRoot(), cout);
            cout << endl;
            file.open("postorder_bst.txt");
            if (file.is_open()) {
                bst.postOrder(bst.getRoot(), file);
                file.close();
                cout << "Guardado en postorder_bst.txt" << endl;
            }
            break;
        }
        case 13: {
            cout << "Preorden (AVL): ";
            avl.preOrder(avl.getRoot(), cout);
            cout << endl;
            file.open("preorder_avl.txt");
            if (file.is_open()) {
                avl.preOrder(avl.getRoot(), file);
                file.close();
                cout << "Guardado en preorder_avl.txt" << endl;
            }
            break;
        }
        case 14: {
            cout << "Inorden (AVL): ";
            avl.inOrder(avl.getRoot(), cout);
            cout << endl;
            file.open("inorder_avl.txt");
            if (file.is_open()) {
                avl.inOrder(avl.getRoot(), file);
                file.close();
                cout << "Guardado en inorder_avl.txt" << endl;
            }
            break;
        }
        case 15: {
            cout << "Postorden (AVL): ";
            avl.postOrder(avl.getRoot(), cout);
            cout << endl;
            file.open("postorder_avl.txt");
            if (file.is_open()) {
                avl.postOrder(avl.getRoot(), file);
                file.close();
                cout << "Guardado en postorder_avl.txt" << endl;
            }
            break;
        }
        case 16:
            // Guardar la estructura completa del Arbol Comun
            commonTree.saveTree("common_tree.txt");
            break;
        case 17:
            // Cargar la estructura completa del Arbol Comun
            commonTree.loadTree("common_tree.txt");
            break;
        case 18:
            // Guardar la estructura completa del BST
            bst.saveTree("bst_tree.txt");
            break;
        case 19:
            // Cargar la estructura completa del BST
            bst.loadTree("bst_tree.txt");
            break;
        case 20:
            // Guardar la estructura completa del AVL
            avl.saveTree("avl_tree.txt");
            break;
        case 21:
            // Cargar la estructura completa del AVL
            avl.loadTree("avl_tree.txt");
            break;
        case 22:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (op != 22);

    return 0;
}
