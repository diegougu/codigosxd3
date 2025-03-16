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
	void find(C comp, T x, node<T>**& p);
public:
	void RemoveDuplicatesII();
	void add(T x);
	void print();
};

template <class T, class C>
void LinkedList<T, C>::find(C comp, T x, node<T>**& p) {
	p = &head;
	for (; *p && comp(x, (*p)->valor); p = &((*p)->next));
}

template <class T, class C>
void LinkedList<T, C>::add(T x) {
	node<T>** p;
	C comp;
	find(comp, x, p);
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
void LinkedList<T, C>::RemoveDuplicatesII() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>** p = &head;
	for (; *p; p = &((*p)->next)) {
		node<T>** q = &((*p)->next);
		if (*q && (*p)->valor == (*q)->valor) {
			for (; *q && (*q)->valor == (*p)->valor; q = &((*q)->next));
			node<T>* temp1 = *p;
			node<T>* t = *q;
			*p = t;
			while (temp1 != t) {
				node<T>* temp2 = temp1;
				temp1 = temp1->next;
				delete temp2;
			}

			if (*p != head) {
				node<T>* reco = head;
				for (; reco->next != *p; reco = reco->next);
				p = &reco;
			}
		}

		if (*p == nullptr) {
			head = nullptr;
			return;
		}
	}

}

int main() {
	LinkedList<int, ASC<int>> l1;
	LinkedList<int, ASC<int>> l2;
	LinkedList<int, ASC<int>> l3;
	LinkedList<int, ASC<int>> l4;




	int arr[7] = { 1,2,3,3,4,4,5 };
	int arr2[5] = { 1,1,1,2,3 };
	int arr3[10] = { 1,2,2,2,2,2,3,4,4,5 };
	int arr4[4] = { 4,4,4,4 };

	for (int i = 0; i < 7; i++) {
		l1.add(arr[i]);
	}

	for (int i = 0; i < 5; i++) {
		l2.add(arr2[i]);
	}

	for (int i = 0; i < 10; i++) {
		l3.add(arr3[i]);
	}

	for (int i = 0; i < 4; i++) {
		l4.add(arr4[i]);
	}

	l1.print();
	l1.RemoveDuplicatesII();
	l1.print();

	l2.print();
	l2.RemoveDuplicatesII();
	l2.print();

	l3.print();
	l3.RemoveDuplicatesII();
	l3.print();

	l4.print();
	l4.RemoveDuplicatesII();
	l4.print();

}
