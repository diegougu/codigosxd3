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
	void DeleteNafterMnodes(int n, int m);
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
void LinkedList<T>::DeleteNafterMnodes(int n, int m) {
	if (head == nullptr || m == 0 || n == 0) {
		return;
	}

	node<T>** p = &head;

	for (int i = 0; i < m && *p; i++, p = &((*p)->next));

	node<T>* q = *p;
	for (int i = 1; i < n && q; i++, q = q->next);

	if (*p && q) {
		node<T>* temp = *p;
		*p = q->next;
		q->next = nullptr;
		while (temp) {
			node<T>* temp2 = temp;
			temp = temp->next;
			delete temp2;
		}
	}



}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	int arr[7] = { 17,15,8,9,2,4,6 };
	int arr2[10] = { 20,19,11,2,4,6,8,10,11,7 };
	for (int i = 0; i < 7; i++) {
		l1.push(arr[i]);
	}

	for (int i = 0; i < 10; i++) {
		l2.push(arr2[i]);
	}

	l1.print();
	l2.print();

	l1.DeleteNafterMnodes(4,2);
	l2.DeleteNafterMnodes(1,5);

	l1.print();
	l2.print();
}
