#include <iostream>
#include <vector>
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

	bool findU(T x);
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
bool LinkedList<T>::findU(T x) {
	for (node<T>* p = head; p; p = p->next) {
		if (p->valor == x) {
			return true;
		}
	}

	return false;
}


template <class T>
void UnionAndIntersection(LinkedList<T>* l1, LinkedList<T>* l2, vector<LinkedList<T>>& UoI) {

	LinkedList<T> Union;
	LinkedList<T> Intersection;
	
	for (node<T>* p = l1->head; p; p = p->next) {
		node<T>* q = l2->head;
		for (; q; q = q->next) {
			if (q->valor == p->valor) {
				Union.push(p->valor);
				Intersection.push(p->valor);
			}
		}
	}


	for (node<T>* p = l1->head; p; p = p->next) {
		if (!Union.findU(p->valor)) {
			Union.push(p->valor);
		}
	}

	for (node<T>* p = l2->head; p; p = p->next) {
		if (!Union.findU(p->valor)) {
			Union.push(p->valor);
		}
	}

	UoI.push_back(Union);
	UoI.push_back(Intersection);

}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	l1.push(10);
	l1.push(15);
	l1.push(4);
	l1.push(20);


	l2.push(8);
	l2.push(4);
	l2.push(2);
	l2.push(10);

	vector<LinkedList<int>> UoI;

	UnionAndIntersection(&l1, &l2, UoI);

	for (int i = 0; i < UoI.size(); i++) {
		UoI[i].print();
	}


}
