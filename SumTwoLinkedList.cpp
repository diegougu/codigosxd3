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
	void SumTwoLinkedList(LinkedList<T> l1, LinkedList<T> l2);
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
void LinkedList<T>::SumTwoLinkedList(LinkedList<T> l1, LinkedList<T> l2) {
	int carry = 0;
	node<T>* l1_tail = l1.head;
	node<T>* l2_tail = l2.head;
	for (; l1_tail->next != nullptr; l1_tail = l1_tail->next);
	for (; l2_tail->next != nullptr; l2_tail = l2_tail->next);

	while (l1_tail || l2_tail) {

		int l1_val_tail = l1_tail ? l1_tail->valor : 0;
		int l2_val_tail = l2_tail ? l2_tail->valor : 0;

		int sum = l1_val_tail + l2_val_tail + carry;
		int p = 0;
		if (sum >= 10) {
			p = sum % 10;
			carry = sum / 10;
			push(p);
		}
		else {
			carry = 0;
			push(sum);
		}
		
		node<T>* newposl1 = l1.head;
		node<T>* newposl2 = l2.head;


		if (l1_tail != l1.head && l1_tail != nullptr) {
			for (; newposl1->next != l1_tail; newposl1 = newposl1->next);
			l1_tail = newposl1;
		}
		else {
			l1_tail = nullptr;

		}

		if (l2_tail != l2.head && l2_tail != nullptr) {
			for (; newposl2->next != l2_tail; newposl2 = newposl2->next);
			l2_tail = newposl2;
		}
		else {
			l2_tail = nullptr;
		}


	}
}



int main() {
	LinkedList<int> l1, l2, result;

	l1.push(2);
	l1.push(4);
	l1.push(3);
	l1.push(3);
	l1.push(5);


	l2.push(5);
	l2.push(6);
	l2.push(4);

	cout << "Lista 1: ";
	l1.print();

	cout << "Lista 2: ";
	l2.print();

	result.SumTwoLinkedList(l1, l2);

	cout << "Resultado de la suma: ";
	result.print();

	return 0;
}
