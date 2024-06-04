#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NODES = 100;  // Máximo número de nodos permitidos

// Estructura para representar un nodo en la estructura de datos Union-Find
struct Node {
    int data;  // Valor del nodo
    Node* parent;  // Puntero al nodo padre en el árbol
    int rank;  // Usado para "union by rank" para mantener el árbol balanceado
};

Node nodes[MAX_NODES];  // Array para almacenar todos los nodos
int nodeCount = 0;  // Contador de nodos creados

// Función para crear un nuevo nodo con un valor dado
void createNode(int data) {
    if (nodeCount < MAX_NODES) {
        nodes[nodeCount].data = data;
        nodes[nodeCount].parent = &nodes[nodeCount];  // Al inicio, cada nodo es su propio padre (conjunto de un elemento)
        nodes[nodeCount].rank = 0;  // Rango inicial 0
        nodeCount++;
    } else {
        cout << "Error: Se alcanzó el límite máximo de nodos." << endl;
    }
}

// Función para encontrar un nodo por su valor
Node* findNode(int data) {
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].data == data) {
            return &nodes[i];
        }
    }
    return nullptr;  // Retorna nullptr si no se encuentra el nodo
}

// Función para encontrar el representante (raíz) del conjunto al que pertenece un nodo
Node* findSet(int data) {
    Node* node = findNode(data);
    if (!node) {
        cout << "Error: Nodo no encontrado." << endl;
        return nullptr;
    }
    if (node->parent != node) {
        node->parent = findSet(node->parent->data);  // Compresión de camino: hace que todos los nodos apunten directamente a la raíz
    }
    return node->parent;
}

// Función para unir dos conjuntos
void unionSets(int x, int y) {
    Node* rootX = findSet(x);
    Node* rootY = findSet(y);
    if (!rootX || !rootY) return;  // Si algún nodo no se encontró, se sale de la función
    if (rootX != rootY) {  // Si los nodos no están ya en el mismo conjunto
        // Union by rank: se une el árbol más pequeño al más grande
        if (rootX->rank < rootY->rank) {
            swap(rootX, rootY);  // Asegura que rootX tenga siempre el rango más alto o igual
        }
        rootY->parent = rootX;  // Hace que rootY sea hijo de rootX
        if (rootX->rank == rootY->rank) {
            rootX->rank++;  // Si los rangos son iguales, se incrementa el rango de rootX
        }
    }
}

// Función para mostrar todos los conjuntos actuales
void displaySets() {
    bool printed[MAX_NODES] = {false};  // Array para rastrear qué nodos ya se han impreso
    cout << "Conjuntos actuales:\n";
    for (int i = 0; i < nodeCount; i++) {
        if (!printed[i] && nodes[i].parent == &nodes[i]) {  // Si es una raíz no impresa
            cout << "{ " << nodes[i].data << " ";
            for (int j = i + 1; j < nodeCount; j++) {
                if (findSet(nodes[j].data) == &nodes[i]) {  // Si j pertenece al mismo conjunto que i
                    cout << nodes[j].data << " ";
                    printed[j] = true;  // Marca j como impreso
                }
            }
            cout << "}\n";
            printed[i] = true;  // Marca i como impreso
        }
    }
}

int main() {
    // Crear nodos individuales (cada uno en su propio conjunto)
    for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9}) {
        createNode(i);
    }
    displaySets();

    // Unir algunos conjuntos
    unionSets(1, 2);  // Une el conjunto de 1 con el de 2
    unionSets(3, 4);  // Une el conjunto de 3 con el de 4
    unionSets(3, 5);  // Une el conjunto resultante con el de 5
    unionSets(6, 7);  // Une el conjunto de 6 con el de 7
    unionSets(6, 8);  // Une el conjunto resultante con el de 8
    unionSets(1, 6);  // Une los dos grandes conjuntos creados

    cout << "\nDespués de algunas uniones:\n";
    displaySets();

    // Buscar a qué conjunto pertenece cada elemento
    cout << "\nBúsquedas:\n";
    Node* set5 = findSet(5);
    Node* set2 = findSet(2);
    Node* set9 = findSet(9);

    // Muestra el representante de cada conjunto
    if (set5) cout << "5 pertenece al conjunto con representante: " << set5->data << endl;
    if (set2) cout << "2 pertenece al conjunto con representante: " << set2->data << endl;
    if (set9) cout << "9 pertenece al conjunto con representante: " << set9->data << endl;

    return 0;
}
