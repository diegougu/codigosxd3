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
	bool find(T x, C comp, node<T>**& p);
public:
	void add(T x);
	void del(T x);
	void print();
};

template <class T, class C>
bool DoubleLinkedList<T, C>::find(T x, C comp, node<T>**& p) {
	for (; *p && comp(x, (*p)->valor); p = &((*p)->next));
	return *p && (*p)->valor == x;
}

template <class T, class C>
void DoubleLinkedList<T, C>::add(T x) {
	C comp;
	node<T>** p = &head;
	
	if (find(x, comp, p)) {
		return;
	}
	
	node<T>* newnode = new node<T>(x);
	newnode->next = *p;
	if (*p) {
		newnode->prev = (*p)->prev;
		(*p)->prev = newnode;
	}
	*p = newnode;

}

template <class T, class C>
void DoubleLinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template <class T, class C>
void DoubleLinkedList<T, C>::del(T x) {
	C comp;
	node<T>** p = &head;

	if (head == nullptr || !find(x, comp, p)) {
		return;
	}

	node<T>* temp = *p;
	*p = temp->next;

	if (temp->next != nullptr) {
		temp->next->prev = (*p)->prev;
	}

	delete temp;
}


int main() {
	DoubleLinkedList<int, CGreater<int>> l1;

	int arr[10] = { 9,1,2,3,7,6,4,8,10,5 };

	for (int i = 0; i < 10; i++) {
		l1.add(arr[i]);
		l1.print();
	}

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << endl;
		l1.del(arr[i]);
		l1.print();
	}
}


