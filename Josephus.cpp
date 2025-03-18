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
	void Josephus(int k);
};



template <class T>
void LinkedList<T>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
		head->next = head;
	}
	else {
		node<T>* p = head;
		do {
			p = p->next;
		} while (p->next != head);
		p->next = newnode;
		newnode->next = head;
	}
}


template <class T>
void LinkedList<T>::print() {
	if (head == nullptr) {
		cout << " " << endl;
		return;
	}
	node<T>* p = head;
	do {
		cout << p->valor << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}



template <class T>
void LinkedList<T>::Josephus(int k) {
	if (head == nullptr || k == 0) {
		return;
	}

	node<T>** p = &head;

	while (*p) {
		this->print();
		for (int i = 1; i < k; i++, p = &((*p)->next));
		node<T>* temp = *p;

		if (*p == head && head->next == head) {
			head = nullptr;
		}
		else if (*p == head) {
			head = head->next;
			*p = head;
		}
		else {
			*p = temp->next;
		}
		delete temp;

		

	}

}



int main() {
	LinkedList<int> l1;
	for (int i = 0; i < 10; i++) {
		l1.push(i);
	}

	l1.Josephus(5);
}
