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
	int pairsum();
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
int LinkedList<T>::pairsum() {
	if (head == nullptr || head->next == nullptr) {
		return -1;
	}

	node<T>* fin = head;
	for (; fin->next != nullptr; fin = fin->next);

	int maxsum = INT_MIN;
	
	for (node<T>* ini = head; fin->next != ini; ini = ini->next) {
		if (ini->valor + fin->valor > maxsum) {
			maxsum = ini->valor + fin->valor;
		}

		node<T>* prev = ini;
		for (; prev->next != fin; prev = prev->next);
		fin = prev;
	}

	return maxsum;



}


int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	LinkedList<int> l5;

	l1.push(1);
	l1.push(2);
	l1.push(4);
	l1.push(5);
	l1.print();
	cout << l1.pairsum() << endl;

	l2.push(10000);
	l2.push(1);
	l2.print();
	cout << l2.pairsum() << endl;

	l3.push(3);
	l3.push(7);
	l3.push(3);
	l3.push(3);
	l3.push(8);
	l3.push(11);
	l3.push(10);
	l3.push(3);
	l3.print();
	cout << l3.pairsum() << endl;


}
