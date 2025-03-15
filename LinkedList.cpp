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
	void del(T x);
	void print();
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
void LinkedList<T, C>::del(T x) {
	node<T>** p;
	C comp;
	if (!find(comp, x, p)) {
		return;
	}
	node<T>* temp = *p;
	*p = temp->next;
	delete temp;
}

template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


int main() {
	LinkedList<int, ASC<int>> l1;
	LinkedList<int, DESC<int>> l2;
	int arr[8] = { 5,4,3,1,2,7,6,8 };
	for (int i = 0; i < 8; i++) {
		l1.add(arr[i]);
	}
	for (int i = 0; i < 8; i++) {
		l2.add(arr[i]);
	}
	l1.print();
	l2.print();
	cout << endl;
	for (int i = 0; i < 8; i++) {
		l1.del(arr[i]);
		l1.print();
	}
	for (int i = 0; i < 8; i++) {
		l2.del(arr[i]);
		l2.print();
	}
}
