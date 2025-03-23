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
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template<class T, class C>
class CircularLinkedList {
private:
	node<T>* head = nullptr;
	bool find(T x, C comp, node<T>**& p);
public:
	void add(T x);
	void del(T x);
	void print();
};


template <class T, class C>
bool CircularLinkedList<T, C>::find(T x, C comp, node<T>**& p) {
	do {
		p = &((*p)->next);
	} while ((*p)->next != head && comp(x, (*p)->valor));

	return (*p)->valor == x;
}


template <class T, class C>
void CircularLinkedList<T, C>::add(T x) {
	C comp;
	node<T>** p = &head;
	if (*p && find(x, comp, p)) {
		return;
	}

	node<T>* newnode = new node<T>(x);
	if (*p && !comp(x, head->valor)) {
		node<T>* q = head;
		do {
			q = q->next;
		} while (q->next != head);
		newnode->next = head;
		q->next = newnode;
		head = newnode;

	}
	else {
		newnode->next = *p;
		*p = newnode;
		if (head->next == nullptr) {
			head->next = head;
		}
	}
}


template <class T, class C>
void CircularLinkedList<T, C>::print() {
	node<T>* p = head;
	if (head == nullptr) {
		cout << "nullptr" << endl;
		return;
	}
	do {
		cout << p->valor << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}

template <class T, class C>
void CircularLinkedList<T, C>::del(T x) {
	C comp;
	node<T>** p = &head;
	if (head == nullptr || (!find(x, comp, p) && head->valor != x)) {
		return;
	}


	if (x == head->valor) {
		node<T>* q = head;
		do {
			q = q->next;
		} while (q->next != head);

		node<T>* temp = head;
		head = head->next;
		q->next = head;

		if (head->next == head) {
			head = nullptr;
		}
		delete temp;
	}
	else {
		node<T>* temp = *p;
		*p = temp->next;
		delete temp;
	}
}

int main() {
	CircularLinkedList<int, CGreater<int>> l1;

	int arr[10] = { 10,1,2,3,7,6,4,8,9,5 };

	for (int i = 0; i < 10; i++) {
		l1.add(arr[i]);
		l1.print();
	}


	for (int i = 0; i < 10; i++) {
		l1.del(arr[i]);
		l1.print();
	}
}


