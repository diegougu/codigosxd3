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
	void Reorder();
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
void LinkedList<T>::Reorder() {
	if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
		return;
	}

	node<T>* top = head;
	node<T>* bottom = head;
	for (; bottom->next != nullptr; bottom = bottom->next);


	while (top != bottom && top->next != bottom) {
		node<T>* recoloc_T = top->next;
		node<T>* recoloc_B = head;
		bottom->next = top->next;
		for (; recoloc_B->next != bottom; recoloc_B = recoloc_B->next);
		top->next = bottom;
		top = recoloc_T;
		bottom = recoloc_B;
		recoloc_B->next = nullptr;
	}


}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	for (int i = 10; i > 0; i--) {
		l1.push(i);
	}
	l1.print();
	l1.Reorder();
	l1.print();

	for (int i = 9; i > 0; i--) {
		l2.push(i);
	}
	l2.print();
	l2.Reorder();
	l2.print();
}
