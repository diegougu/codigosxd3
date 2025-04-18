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
	bool ver(node<T>* p, int x);
public:
	node<T>* head = nullptr;
	void push(T x);
	void print();
	void removeNodesFromRight();
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
bool LinkedList<T>::ver(node<T>* p, int x) {
	for (; p; p = p->next) {
		if (p->valor != x) {
			return false;
		}
	}
	return true;
}

template <class T>
void LinkedList<T>::removeNodesFromRight() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>* fin = head;
	for (; fin->next != nullptr; fin = fin->next);
	int maximun = fin->valor;

	do {
		node<T>* p = fin;
		while (p->valor <= maximun && p != head) {
			node<T>* newpos = head;
			for (; newpos->next != p; newpos = newpos->next);
			p = newpos;
		}

		if (p == head && p->valor < maximun) {
			head = fin;
			return;
		}
		else if (p == head && this->ver(p, p->valor) == true) {
			return;
		}
		else {
			p->next = fin;
			fin = p;
			maximun = fin->valor;
		}
	} while (fin != head);

}

int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	LinkedList<int> l5;

	l1.push(8);
	l1.push(3);
	l1.push(13);
	l1.push(2);
	l1.push(5);
	l1.print();
	l1.removeNodesFromRight();
	l1.print();


	l2.push(5);
	l2.push(4);
	l2.push(3);
	l2.push(2);
	l2.push(1);
	l2.print();
	l2.removeNodesFromRight();
	l2.print();

	l3.push(5);
	l3.push(6);
	l3.push(7);
	l3.push(8);
	l3.push(9);
	l3.push(10);
	l3.print();
	l3.removeNodesFromRight();
	l3.print();

	l4.push(1);
	l4.push(1);
	l4.push(1);
	l4.push(1);
	l4.push(1);
	l4.push(1);
	l4.print();
	l4.removeNodesFromRight();
	l4.print();

}
