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
	void SegregateEvenandOdd();
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
void LinkedList<T>::SegregateEvenandOdd() {
	node<T>** p = &head;
	while (*p) {
		if ((*p)->valor % 2 == 0 && *p != head) {
			node<T>* temp = *p;
			*p = temp->next;
			temp->next = head;
			head = temp;
		}
		else {
			p = &((*p)->next);
		}
	}
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	int arr[7] = { 17,15,8,9,2,4,6 };
	int arr2[10] = { 20,19,11,2,4,6,8,10,11,7 };
	for (int i = 0; i < 7; i++) {
		l1.push(arr[i]);
	}

	for (int i = 0; i < 10; i++) {
		l2.push(arr2[i]);
	}

	l1.print();
	l2.print();

	l1.SegregateEvenandOdd();
	l2.SegregateEvenandOdd();

	l1.print();
	l2.print();
}
