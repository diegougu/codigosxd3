// CicrcularLinkedList.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

using namespace std;

class node
{
public:
    int data = 0;
    node* next = nullptr;
};

class CircularLinkedList
{
    node* head = NULL;
public:
    bool find(int value, node**& pos) {
        pos = &head;
        do {
            pos = &((*pos)->next);
        } while (*pos != head && (*pos)->data < value);
        return (*pos)->data == value;
    }
    void add(int value)
    {
        if (head == nullptr) {
            node* temp = new node;
            temp->data = value;
            head = temp;
            head->next = head;
        }
        else if (value != head->data && value < head->data) {
            node* temp = new node;
            temp->data = value;
            node* tail = head;
            do {
                tail = tail->next;
            } while (tail->next != head);
            temp->next = head;
            head = temp;
            tail->next = head;
        }
        else {
            node** pos;
            if (find(value, pos)) {
                return;
            }
            node* temp = new node;
            temp->data = value;
            temp->next = *pos;
            *pos = temp;

        }

    }

    void del(int value)
    {
        if (head == nullptr) {
            return;
        }
        else if (value == head->data && head->next == head) {
            node* temp = head;
            head = nullptr;
            delete temp;
        }
        else if (value == head->data && head->next != head) {
            node* tail = head;
            do {
                tail = tail->next;
            } while (tail->next != head);
            node* temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        else {
            node** pos = &head;
            if (!find(value, pos)) {
                return;
            }

            node* temp = *pos;
            *pos = temp->next;

            delete temp;

        }

    }

    void print()
    {
        int cont = 0;
        node* ptr = head;
        cout << "head->";
        if (ptr->next == nullptr) return;
        while (head && cont < 1)
        {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
            if (ptr == head) cont++;
        }
        if (head) cout << ptr->data;
        cout << " <- head \n ";

    }
};

int main()
{
    int ADD[10] = { 2,4,6,8,10,1,3,5,7,9 };
    int DEL[10] = { 9,7,5,3,1,10,8,6,4,2 };
    CircularLinkedList CLL;
    for (int i = 0; i < 10; i++)
    {
        cout << "ADD " << ADD[i] << endl;
        CLL.add(ADD[i]);
        CLL.print();
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "DEL " << DEL[i] << endl;
        CLL.del(DEL[i]);
        CLL.print();
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
