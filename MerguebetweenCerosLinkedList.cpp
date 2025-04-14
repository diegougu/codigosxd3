#include <iostream>
#include <vector>
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
	void MerguebetweenCeros();
	
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
void LinkedList<T>::MerguebetweenCeros() {
	if (head == nullptr) {
		return;
	}

	node<T>** p = &head;
	while (*p != nullptr) {
		node<T>** q = &*p;
		int suma = 0;
		do {
			suma += (*q)->valor;
			q = &((*q)->next);
		} while ((*q)->valor != 0);
		(*q)->valor = suma;
		*p = *q;
		q = &((*q)->next);
		p = &*q;
	}
}




int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;

	int arr[8] = { 0,2,5,4,0,3,1,0 };
	int arr2[8] = { 0,2,2,0,3,0,1,0 };
	for (int i = 0; i < 8; i++) {
		l1.push(arr[i]);
	}

	l1.print();
	l1.MerguebetweenCeros();
	l1.print();

	for (int i = 0; i < 8; i++) {
		l2.push(arr2[i]);
	}
	l2.print();
	l2.MerguebetweenCeros();
	l2.print();

}
