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
	void insertGreatestCommonDivisors();
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

int GreatestCommonDivisors(int a, int b) {
	int n = (a > b) ? a : b;
	int common = 0;
	for (int i = 1; i <= n; i++) {
		if (a % i == 0 && b % i == 0 && i >= common) {
			common = i;
		}
	}
	return common;
}

template <class T>
void LinkedList<T>::insertGreatestCommonDivisors() {
	if (head == nullptr) {
		return;
	}
	node<T>* p = head;
	while (p->next != nullptr) {
		node<T>* q = p->next;
		int maxi = GreatestCommonDivisors(p->valor, q->valor);
		node<T>* temp = new node<T>(maxi);
		temp->next = q;
		p->next = temp;
		p = q;
	}
}

int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	l1.push(3);
	l1.push(10);
	l1.push(6);
	l1.push(18);
	l1.print();
	l1.insertGreatestCommonDivisors();
	l1.print();

	l2.push(5);
	l2.push(10);
	l2.push(12);
	l2.push(20);
	l2.push(21);
	l2.push(19);
	l2.push(2);
	l2.print();
	l2.insertGreatestCommonDivisors();
	l2.print();
}
