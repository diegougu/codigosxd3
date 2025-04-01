#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T>
class LinkedList {
private:
public:
	node<T>* head = nullptr;
	void push(T x);
	void print();
	bool Palindrome();
};


template <class T>
void LinkedList<T>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
	}
	else {
		newnode->next = head;
		head = newnode;
	}
}


template <class T>
void LinkedList<T>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}



template <class T>
bool LinkedList<T>::Palindrome() {
	if (head == nullptr || head->next == nullptr) {
		return 1;
	}

	node<T>* ini = head;
	node<T>* fin = head;
	for (; fin->next != nullptr; fin = fin->next);

	while (ini && fin != head && ini != fin) {
		if (ini->valor != fin->valor) {
			return false;
		}
		ini = ini->next;
		node<T>* ant = head;
		for (; ant->next != fin; ant = ant->next);
		fin = ant;
	}

	return true;
	
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	int arr[11] = { 1,1,2,3,4,5,4,3,2,1,1 };
	int arr2[6] = { 3,1,2,2,1,3 };
	int arr3[5] = { 1,1,1,1,2 };
	int arr4[8] = { 1,3,4,1,4,1,3,1 };

	for (int i = 0; i < 11; i++) {
		l1.push(arr[i]);
	}

	for (int i = 0; i < 6; i++) {
		l2.push(arr2[i]);
	}

	for (int i = 0; i < 5; i++) {
		l3.push(arr3[i]);
	}

	for (int i = 0; i < 8; i++) {
		l4.push(arr4[i]);
	}

	l1.print();
	l2.print();
	l3.print();
	l4.print();

	cout << "-------------------" << endl;

	cout << l1.Palindrome() << endl;
	cout << l2.Palindrome() << endl;
	cout << l3.Palindrome() << endl;
	cout << l4.Palindrome() << endl;


}
