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
	void RotateLinkedListblockwise(int k, int d);
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
void LinkedList<T>::RotateLinkedListblockwise(int k, int d) {
	if (head == nullptr || head->next == nullptr || k <= 1) {
		return;
	}

	node<T>** start = &head;
	while (*start != nullptr) {
		node<T>** end = &(*start);
		for (int i = 1; i < k && (*end)->next != nullptr; i++, end = &((*end)->next));
		if (d >= 1) {
			node<T>* save = *end;
			*end = save->next;
			save->next = *start;
			*start = save;
		}
		else {
			node<T>* save3 = *start;
			node<T>* save = *end;
			node<T>* save2 = (*start)->next;
			(*start)->next = save->next;
			save->next = *start;
			*start = save2;
			end = &(save3->next);
		}
		start = end;
	}
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	LinkedList<int> l5;

	for (int i = 9; i >= 1; i--) {
		l1.push(i);
	}
	l1.print();
	l1.RotateLinkedListblockwise(3,1);
	l1.print();


	for (int i = 15; i >= 1; i--) {
		l2.push(i);
	}
	l2.print();
	l2.RotateLinkedListblockwise(4, -1);
	l2.print();
}
