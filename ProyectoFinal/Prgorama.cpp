#include <iostream>
#include <string>
using namespace std;

// Definición de la estructura Node para representar los nodos de la lista enlazada
struct Node
{
    string data;    // Almacena el dato del nodo (en este caso, el nombre del alumno)
    Node* next;     // Puntero al siguiente nodo en la lista
};

// Declaración de la variable global head que apunta al inicio de la lista
Node* head = NULL;

// Declaración de la variable global numLista que se utiliza para rastrear el número de lista durante la búsqueda
int numLista = 0;

// Prototipos de funciones
void InsertOnList(Node*&, const string&);
void ShowList(Node*);
void EliminarNodo(Node*&, const string&);
void eliminarLista(Node*&);
bool SearchOnList(Node*, const string&, int&);
bool containsOnlyLettersOrSpaces(const string&);
bool isLetterOrSpace(char c);

int main()
{
    int Continue;
    int option;
    string n;
    do
    {
        system("cls");
        cout << "" << endl;
        cout << "Menu de la lista de Alumnos:" << endl;
        cout << "1. Aniadir Alumno" << endl;
        cout << "2. Mostrar lista" << endl;
        cout << "3. Buscar Numero de lista" << endl;
        cout << "4. Dar de baja un Alumno" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "Inserte el nombre: ";
            cin.ignore(); // Limpiar el buffer de entrada antes de leer la línea
            getline(cin, n); // Leer toda la línea, incluidos los espacios en blanco
            if (!SearchOnList(head, n, numLista))
                InsertOnList(head, n);
            else
                cout << "Este alumno ya se encuentra en la lista." << endl;
            break;
        case 2:
            ShowList(head);
            break;
        case 3:
            cout << "Inserte el nombre completo: ";
            cin.ignore(); // Limpiar el buffer de entrada antes de leer la línea
            getline(cin, n); // Leer toda la línea, incluidos los espacios en blanco
            if (SearchOnList(head, n, numLista))
            {
                cout << "El Alumno \"" << n << "\" ha sido encontrado" << endl;
                cout << "con numero de lista: " << numLista << endl;
            }
            else
            {
                cout << "El Alumno \"" << n << "\" no ha sido encontrado." << endl;
            }
            break;
        case 4:
            cout << "Ingresa el nombre del alumno que desea dar de baja: ";
            cin.ignore(); // Limpiar el buffer de entrada antes de leer la línea
            getline(cin, n); // Leer toda la línea, incluidos los espacios en blanco
            EliminarNodo(head, n);
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

        cout << "<<< Deseas realizar algo mas?\n (1) = Si\n (0) = No" << endl;
        cout << ">>> Tu opcion: ";
        cin >> Continue;
        cout << "\n";

    } while (Continue != 0);
    return 0;
}

// Función para verificar si un carácter es una letra (A-Z, a-z) o un espacio en blanco
bool isLetterOrSpace(char c) {
    // Verifica las letras mayúsculas y minúsculas estándar y el espacio en blanco
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
        return true;
    }
    return false;
}

// Función para verificar si una cadena contiene solo letras y espacios en blanco
bool containsOnlyLettersOrSpaces(const string& str) {
    for (char c : str) {
        if (!isLetterOrSpace(c)) {
            return false;
        }
    }
    return true;
}

// Función para insertar un nuevo nodo en la lista
void InsertOnList(Node*& head, const string& n)
{
    if (!containsOnlyLettersOrSpaces(n)) {
        cout << "El nombre no debe contener numeros ni caracteres especiales." << endl;
        return;
    }

    // Crear un nuevo nodo
    Node* new_node = new Node();
    new_node->data = n;

    // Recorrer la lista para encontrar la posición de inserción
    Node* tail = head;
    Node* aux2 = NULL;
   
    // Comparación lexicográfica de cadenas
    while ((tail != NULL) && (tail->data < n))
    {
        aux2 = tail;
        tail = tail->next;
    }

    // Inserción en la cabeza de la lista si es el primer nodo o se debe insertar antes del primer nodo
    if (head == tail)
    {
        head = new_node;
    }
    else
    {
        // Insertar el nuevo nodo entre aux2 y tail
        aux2->next = new_node;
    }
    // Conectar el nuevo nodo con el resto de la lista
    new_node->next = tail;
    cout << "Alumno aniadido correctamente: " << n << endl;
}

// Función para mostrar todos los elementos de la lista
void ShowList(Node* head)
{
    Node* actual = head;
    while (actual != NULL)
    {
        cout << actual->data << endl;
        actual = actual->next;
    }
    cout << endl;
}

// Función para eliminar un nodo de la lista
void EliminarNodo(Node*& head, const string& n)
{
    if (head != NULL)
    {
        Node* aux_delete = head;
        Node* previous = NULL;

        while ((aux_delete != NULL) && (aux_delete->data != n))
        {
            previous = aux_delete;
            aux_delete = aux_delete->next;
        }

        if (aux_delete == NULL)
        {
            cout << "El elemento no se ha encontrado en la lista." << endl;
        }
        else if (previous == NULL)
        {
            // Si el elemento a eliminar es el primer nodo
            head = head->next;
            delete aux_delete;
            cout << "Elemento eliminado." << endl;
        }
        else
        {
            // Conectar el nodo anterior al nodo siguiente al nodo a eliminar
            previous->next = aux_delete->next;
            delete aux_delete;
            cout << "Elemento eliminado." << endl;
        }
    }
}

// Función para eliminar todos los nodos de la lista
void eliminarLista(Node*& head)
{
    while (head != NULL)
    {
        Node* aux_delete = head;
        head = aux_delete->next;
        delete aux_delete;
    }
    cout << "La lista ha sido eliminada." << endl;
}

// Función para buscar un elemento en la lista y obtener su número de lista
bool SearchOnList(Node* head, const string& n, int& numLista)
{
    bool flag = false;
    Node* actual = head;
    numLista = 0;
    while (actual != nullptr)
    {
        numLista++;
        if (actual->data == n)
        {
            flag = true;
            break;
        }
        actual = actual->next;
    }

    return flag;
}

