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
	void Reverse();
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
void LinkedList<T>::Reverse() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	
	node<T>* fin = head;
	for (; fin->next != nullptr; fin = fin->next);
	node<T>* copyF = fin;
	while (fin != head) {
		node<T>* ini = head;
		for (; ini->next != fin; ini = ini->next);
		fin->next = ini;
		fin = ini;
	}
	fin->next = nullptr;
	head = copyF;
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	for (int i = 10; i > 0; i--) {
		l1.push(i);
	}
	l1.print();
	l1.Reverse();
	l1.print();

	for (int i = 9; i > 0; i--) {
		l2.push(i);
	}
	l2.print();
	l2.Reverse();
	l2.print();
}
