#include <iostream>

using namespace std;

template <class T>
struct CGreater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct CLess {
	bool operator()(T a, T b) {
		return a < b;
	}
};


template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node<T>* prev = nullptr;
	node(T v, node<T>* n = nullptr, node<T>* p = nullptr) : valor(v), next(n), prev(p) {}
};

template <class T, class C>
class DoubleLinkedList {
private:
	node<T>* head = nullptr;
public:
	void push(T x);
	void print();
	void RemoveDuplicates();
};


template <class T, class C>
void DoubleLinkedList<T, C>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
	}
	else {
		newnode->next = head;
		head->prev = newnode;
		head = newnode;
	}
}

template <class T, class C>
void DoubleLinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template<class T, class C>
void DoubleLinkedList<T, C>::RemoveDuplicates() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>** p = &head;
	while (*p) {
		node<T>** q = &((*p)->next);
		while (*q) {
			if (*q && (*p)->valor == (*q)->valor) {
				node<T>* temp = *q;
				*q = temp->next;
				if (temp->next != nullptr) {
					temp->next->prev = temp->prev;
				}
				delete temp;
			}
			else {
				q = &((*q)->next);
			}
		}
		p = &((*p)->next);
	}
}

int main() {
	DoubleLinkedList<int, CGreater<int>> l1;

	int arr[10] = {1,1,2,1,1,2,3,3,5,6};

	for (int i = 0; i < 10; i++) {
		l1.push(arr[i]);
		l1.print();
	}

	l1.RemoveDuplicates();
	l1.print();

}


