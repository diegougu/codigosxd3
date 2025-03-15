#include <iostream>
using namespace std; 

template <class T>
struct ASC {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T, class C>
class LinkedList {
private:
	node<T>* head = nullptr;
	bool find(C comp, T x, node<T>**& p);
public:
	void add(T x);
	void print();
	void SwapPairNodes();
};

template <class T, class C>
bool LinkedList<T, C>::find(C comp, T x, node<T>**& p) {
	p = &head;
	for (; *p && comp(x, (*p)->valor); p = &((*p)->next));
	return *p && (*p)->valor == x;
}

template <class T, class C>
void LinkedList<T, C>::add(T x) {
	node<T>** p;
	C comp;
	if (find(comp, x, p)) {
		return;
	}
	node<T>* temp = new node<T>(x);
	temp->next = *p;
	*p = temp;
}


template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


template <class T, class C>
void LinkedList<T, C>::SwapPairNodes() {
	if (head == nullptr || (head != nullptr && head->next == nullptr)) {
		return;
	}
	node<T>* prev = head;
	node<T>* act = head;
	node<T>** save = &head;
	while (prev && act) {
		act = act->next;

		if (act != nullptr) {
			*save = act;
			save = &(prev->next);

			prev->next = act->next;
			act->next = prev;

			prev = prev->next;
			act = prev;
		}
	}
}

int main() {
	int arr[5] = { 1,2,3,4,5 };
	int arr2[6] = { 1,2,3,4,5,6 };
	int arr3[3] = { 1,2,3 };

	LinkedList<int, ASC<int>> l1;
	LinkedList<int, ASC<int>> l2;
	LinkedList<int, ASC<int>> l3;

	for (int i = 0; i < 5; i++) {
		l1.add(arr[i]);
	}
	for (int i = 0; i < 6; i++) {
		l2.add(arr2[i]);
	}
	for (int i = 0; i < 3; i++) {
		l3.add(arr2[i]);
	}
	l1.print();
	l1.SwapPairNodes();
	l1.print();

	cout << endl;
	l2.print();
	l2.SwapPairNodes();
	l2.print();

	cout << endl;
	l3.print();
	l3.SwapPairNodes();
	l3.print();
}
