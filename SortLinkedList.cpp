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
	void Sort();
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
void LinkedList<T>::Sort() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>* p = head;
	node<T>* q = head;

	while (p && q) {
		q = p->next;
		if (q != nullptr && p != nullptr && p->valor > q->valor) {
			node<T>* recoP = head;
			if (p == head) {
				head = q;

			}
			else {
				for (; recoP->next != p; recoP = recoP->next);
				recoP->next = q;
			}
			p->next = q->next;
			q->next = p;
			p = head;
			q = p;
		}
		else {
			p = p->next;
		}
	}

}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	int arr[7] = { 3,2,1,7,5,6,4 };
	int arr2[10] = { 10,6,7,8,9,1,2,4,3,5 };

	for (int i = 0; i < 7; i++) {
		l1.push(arr[i]);
	}

	for (int i = 0; i < 10; i++) {
		l2.push(arr2[i]);
	}

	l1.print();
	l1.Sort();
	l1.print();

	cout << endl;

	l2.print();
	l2.Sort();
	l2.print();
}
