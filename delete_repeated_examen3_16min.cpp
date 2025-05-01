#include <iostream>
using namespace std;

struct Node {
    Node* next = nullptr;
    int val;

    Node(int v) {
        this->val = v;
    }
};

struct SortedLinkedList {

    Node* head = nullptr;

    // Inits a linked list with array (And the array is sorted)
    SortedLinkedList(int* arr, int size) {
        Node** p = &(head);
        for (int i = 0; i < size; ++i) {
            *p = new Node(arr[i]);
            p = &((*p)->next);
        }
    }

    void print() {
        Node* p = head;
        for (Node* p = head; p; p = p->next) cout << p->val << " -> ";
        cout << "NULL" << endl;
    }


    void delete_repeated() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Node* p = head;
        while (p != nullptr) {
            Node* q = p->next;
            if (p != nullptr && q != nullptr && p->val == q->val) {
                for (; q->next != nullptr && q->val == p->val; q = q->next);
                Node* temp = p->next;
                if (q->next == nullptr && p->val == q->val) {
                    p->next = nullptr;
                }
                else {
                    p->next = q;
                }

                do {
                    Node* temp2 = temp;
                    temp = temp->next;
                    delete temp2;
                } while (temp != nullptr && temp != q);
            }
            p = p->next;
        }
    }

};

int main() {

    int arr_a[5] = { 1,2,2,2,5 };

    int arr_b[5] = { -4,-4,-4,-4,-4 };

    int arr_c[10] = { 2,2,2,7,7,7,7,9,9,9 };

    int arr_d[10] = { 2,3,5,7,11,13,17,19,23,29 }; // No se elimina nada


    SortedLinkedList A(arr_a, 5);

    cout << "TEST A:";
    cout << "\nCon repetidos:\n";
    A.print();

    cout << "Sin Repetidos:\n";
    A.delete_repeated();
    A.print();


    SortedLinkedList B(arr_b, 5);

    cout << "\nTEST B:";
    cout << "\nCon repetidos:\n";
    B.print();
    cout << "Sin Repetidos:\n";
    B.delete_repeated();
    B.print();


    SortedLinkedList C(arr_c, 10);

    cout << "\nTEST C:";
    cout << "\nCon repetidos:\n";
    C.print();
    cout << "Sin Repetidos:\n";
    C.delete_repeated();
    C.print();

    SortedLinkedList D(arr_d, 10);

    cout << "\nTEST D:";
    cout << "\nCon repetidos:\n";
    D.print();
    cout << "Sin Repetidos:\n";
    D.delete_repeated();
    D.print();


    cout << endl;

    return 0;
}
