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
	void ReverseII(int n, int m);
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
void LinkedList<T>::ReverseII(int left, int right) {
	if(head == nullptr || head->next == nullptr || left == right){
		return;
	}

	node<T>** links = &head;
	node<T>** linke = &head;

	for (int i = 1; i < left && *links; i++, links = &((*links)->next));
	for (int i = 1; i < right && *linke; i++, linke = &((*linke)->next));

	
	node<T>* start = *links;
	node<T>* end = *linke;
	node<T>* save = end->next;
	*links = end;
	while (start != end) {
		node<T>* p = start;
		for (; p->next != end; p = p->next);
		end->next = p;
		end = p;
	}
	start->next = save;
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	LinkedList<int> l5;

	for (int i = 5; i >= 1; i--) {
		l1.push(i);
	}

	l1.print();
	l1.ReverseII(2,4);
	l1.print();

	for (int i = 10; i >= 1; i--) {
		l2.push(i);
	}
	l2.print();
	l2.ReverseII(1, 4);
	l2.print();

	for (int i = 10; i >= 1; i--) {
		l3.push(i);
	}
	l3.print();
	l3.ReverseII(1, 10);
	l3.print();

}
