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
class CircularDoubleLinkedList {
private:
	node<T>* head = nullptr;
	bool find(C comp, T x, node<T>**& p);
public:
	void add(T x);
	void del(T x);
	void print();
};


template <class T, class C>
bool CircularDoubleLinkedList<T, C>::find(C comp, T x, node<T>**& p) {
	do {
		p = &((*p)->next);
	} while (*p != head && comp(x, (*p)->valor));
	
	return x == (*p)->valor;
}

template <class T, class C>
void CircularDoubleLinkedList<T, C>::add(T x) {
	C comp;
	node<T>** p = &head;

	if (*p && find(comp, x, p)) {
		return;
	}
	
	node<T>* newnode = new node<T>(x);

	if (*p && comp(head->valor, x)) {
		node<T>* q = head->prev;
		newnode->next = head;
		head->prev = newnode;
		newnode->prev = q;
		q->next = newnode;
		head = newnode;
	}
	else {
		if (head == nullptr) {
			head = newnode;
			head->next = head;
			head->prev = head;
		}
		else {
			newnode->next = *p;
			newnode->prev = (*p)->prev;
			(*p)->prev = newnode;
			*p = newnode;
		}
	}


}

template <class T, class C>
void CircularDoubleLinkedList<T, C>::del(T x) {
	C comp;
	node<T>** p = &head;
	if (head == nullptr || (head->valor != x && !find(comp, x, p))) {
		return;
	}

	if (x == head->valor) {
		node<T>* temp = head;
		head = head->next;
		temp->prev->next = head;
		head->prev = temp->prev;
		if (head == temp) {
			head = nullptr;
		}
		delete temp;
	}
	else {
		node<T>* temp = *p;
		*p = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}

}

template <class T, class C>
void CircularDoubleLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->valor << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}

int main() {
	CircularDoubleLinkedList<int, CGreater<int>> l1;
	int arr[10] = { 9,1,3,2,5,4,7,8,10,6 };
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
