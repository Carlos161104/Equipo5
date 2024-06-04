#include <iostream>
#include <cstdlib>

using namespace std;

struct Nodo
{
    int data;
    Nodo * next;
};
void createList(Nodo *&, int);
void showList(Nodo*);
void Joshep (Nodo *&, int);

Nodo * head = NULL;

int main(){
    system("cls");
    int peronas, muertes;
    cout << "Introduzca el numero de personas: ";
    cin >> peronas;
    cout << "Ingrese el numero de personas a eliminar:";
    cin >> muertes;
    
    createList(head, peronas);
    showList(head);
    Joshep(head, muertes);
    return 0;
}

void createList(Nodo *& head, int n){
    Nodo *first = NULL; 
    Nodo *last = NULL;

    for(int i = 1; i <= n; ++i){
        Nodo *new_nodo = new Nodo();
        new_nodo->data = i;
        Nodo *aux1 = head;
        Nodo *aux2 = NULL;

        while((aux1 != NULL) && (aux1->data < new_nodo->data)){
            aux2 = aux1;
            aux1 = aux1->next;
        }
        if(aux2 == NULL){
            head = new_nodo;
            first = new_nodo;
        } else {
            aux2->next = new_nodo;
        }
        last = new_nodo;
        new_nodo->next = aux1;
    }

    if(last != NULL){
        last->next = first;
    }
}

void showList(Nodo* head){
    Nodo *actual = head;
    do {
        cout << "|" << actual->data << "| -> ";
        actual = actual->next;
    } while(actual != head); 
    cout << "|" << head->data << "| (cabeza)" << endl; 
}

void Joshep (Nodo *&head, int n){
    Nodo *actual = head;
    Nodo *previous = NULL;
    int contador = 0;
    while (actual->next != actual){
        contador++;
        if(contador == n){
            previous->next = actual->next;
            delete actual;
            actual = previous->next;
            contador = 0;
        } else {
            previous = actual;
            actual = actual->next;
        }
    }
    cout << "El ganador es: " << actual->data << endl;
}
