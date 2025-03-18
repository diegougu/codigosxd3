#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node<T>* jump = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T>
class LinkedList {
private:
public:
	node<T>* head = nullptr;
	void push(T x);
	void print();
	void JumpInK(int k);
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
void LinkedList<T>::JumpInK(int k) {
	if (head == nullptr) {
		return;
	}

	for (node<T>* p = head; p; p = p->next) {
		node<T>* q = p;
		for (int i = 0; i < k; i++) {
			if (q->next == nullptr) {
				q = head;
			}
			else {
				q = q->next;
			}
		}
		p->jump = q;
	}

	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << "jump to" << p->jump->valor << endl;
	}
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	for (int i = 0; i < 10; i++) {
		l1.push(i);
	}

	l1.JumpInK(5);
}
