#include <iostream>
using namespace std;

struct Node {
    int sum = 0;
    int start_index, final_index;
    Node* children[2] = { nullptr, nullptr };
    Node(int* arr, int start, int end) {
        this->start_index = start;
        this->final_index = end;

        if (start == end) {
            sum = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            children[0] = new Node(arr, start, mid);
            children[1] = new Node(arr, mid + 1, end);
            sum = children[0]->sum + children[1]->sum;
        }
    }



    // No toques esto :)
    int query(int start, int end) {
        if (start == start_index && end == final_index) return this->sum;

        int answer = 0;
        if (start <= children[0]->final_index) {
            answer += children[0]->query(start, min(children[0]->final_index, end));
        }
        if (children[1]->start_index <= end) {
            answer += children[1]->query(max(children[1]->start_index, start), end);
        }
        return answer;
    }
};

// Tampoco toques esto ;)
struct SegmentationTree {
    Node* head = nullptr;
    int size_arr;

    SegmentationTree(int* arr, int size) {
        // Indice de inicio = 0
        // Ultimo indice = size-1
        this->size_arr = size;
        head = new Node(arr, 0, size - 1);
    }

    int query_sum(int start, int end) {
        if (!head) return 0;
        return head->query(start, end);
    }
};

int main() {

    int arr_a[5] = { 1,2,3,4,5 };

    int arr_b[10] = { 2,3,5,7,11,13,17,19,23,29 };

    int arr_c[15] = { 1,2,3,4,5,-5,-6,-7,-8,-9,10,20,30,40,50 };

    // Dara Segmentation Fault si no implementas lo pedido :)

    SegmentationTree A(arr_a, 5);

    cout << "TEST A:";
    cout << "\nSuma en rango [0, 4] = " << A.query_sum(0, 4);
    cout << "\nSuma en rango [2, 2] = " << A.query_sum(2, 2);
    cout << "\nSuma en rango [0, 1] = " << A.query_sum(0, 1);
    cout << "\nSuma en rango [3, 4] = " << A.query_sum(3, 4);
    cout << "\nSuma en rango [1, 3] = " << A.query_sum(1, 3);

    SegmentationTree B(arr_b, 10);

    cout << "\n\nTEST B:";
    cout << "\nSuma en rango [2, 8] = " << B.query_sum(2, 8);
    cout << "\nSuma en rango [0, 0] = " << B.query_sum(0, 0);
    cout << "\nSuma en rango [9, 9] = " << B.query_sum(9, 9);
    cout << "\nSuma en rango [0, 7] = " << B.query_sum(0, 7);
    cout << "\nSuma en rango [3, 9] = " << B.query_sum(3, 9);

    SegmentationTree C(arr_c, 15);

    cout << "\n\nTEST C:";
    cout << "\nSuma en rango [0, 14]  = " << C.query_sum(0, 14);
    cout << "\nSuma en rango [0, 4]   = " << C.query_sum(0, 4);
    cout << "\nSuma en rango [5, 9]   = " << C.query_sum(5, 9);
    cout << "\nSuma en rango [10, 14] = " << C.query_sum(10, 14);
    cout << "\nSuma en rango [2, 13]  = " << C.query_sum(2, 13);

    cout << endl;

    return 0;
}
