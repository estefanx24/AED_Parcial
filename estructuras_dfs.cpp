#include <iostream>
using namespace std;

// Definición del nodo del árbol binario de búsqueda
struct TreeNode {
    int value;         // Valor del nodo
    TreeNode* left;    // Puntero al hijo izquierdo
    TreeNode* right;   // Puntero al hijo derecho

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}  // Constructor
};

// Clase para representar el árbol binario de búsqueda
class BST {
public:
    TreeNode* root;  // Puntero a la raíz del árbol

    BST() : root(nullptr) {}  // Constructor del árbol, inicialmente vacío

    // Función para insertar un nuevo nodo en el árbol
    void insert(int val) {
        root = insertRec(root, val);  // Llamada recursiva para insertar
    }

    // Función para eliminar un nodo del árbol
    void remove(int val) {
        root = removeRec(root, val);  // Llamada recursiva para eliminar
    }

    // Función para imprimir el árbol en orden (In-Order Traversal)
    void inOrder() {
        inOrderRec(root);
        cout << endl;
    }

private:
    // Función recursiva para insertar un nuevo valor en el árbol
    TreeNode* insertRec(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);  // Si el nodo es nulo, creamos uno nuevo
        }

        if (val < node->value) {
            node->left = insertRec(node->left, val);  // Insertar en el subárbol izquierdo
        } else if (val > node->value) {
            node->right = insertRec(node->right, val);  // Insertar en el subárbol derecho
        }

        return node;  // Retornamos el nodo (actualizado o nuevo)
    }

    // Función recursiva para eliminar un valor del árbol
    TreeNode* removeRec(TreeNode* node, int val) {
        if (node == nullptr) return node;  // Si el árbol está vacío, retornamos nulo

        if (val < node->value) {
            node->left = removeRec(node->left, val);  // Si el valor es menor, buscamos en el subárbol izquierdo
        } else if (val > node->value) {
            node->right = removeRec(node->right, val);  // Si el valor es mayor, buscamos en el subárbol derecho
        } else {
            // Encontramos el nodo a eliminar
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Nodo con dos hijos: obtenemos el sucesor en orden (el menor en el subárbol derecho)
            TreeNode* temp = minValueNode(node->right);
            node->value = temp->value;  // Reemplazamos el valor por el sucesor

            // Eliminamos el sucesor
            node->right = removeRec(node->right, temp->value);
        }

        return node;
    }

    // Función auxiliar para encontrar el nodo con el valor mínimo (el más a la izquierda)
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Función recursiva para imprimir el árbol en orden
    void inOrderRec(TreeNode* node) {
        if (node != nullptr) {
            inOrderRec(node->left);  // Recorremos el subárbol izquierdo
            cout << node->value << " ";  // Imprimimos el valor del nodo actual
            inOrderRec(node->right);  // Recorremos el subárbol derecho
        }
    }
};

int main() {
    BST tree;

    // Insertamos algunos valores en el árbol
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Imprimimos el árbol en orden
    cout << "Árbol en orden: ";
    tree.inOrder();

    // Eliminamos un nodo
    cout << "Eliminamos 20\n";
    tree.remove(20);
    cout << "Árbol en orden: ";
    tree.inOrder();

    // Eliminamos un nodo con dos hijos
    cout << "Eliminamos 50\n";
    tree.remove(50);
    cout << "Árbol en orden: ";
    tree.inOrder();

    return 0;
}
