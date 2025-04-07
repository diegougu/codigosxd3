#include <iostream>
using namespace std;

template <class T>
struct node{
	T valor;
	node<T>* next = nullptr;
	node<T>* prev = nullptr;
	node(T v, node<T>* nx = nullptr, node<T>* px = nullptr) : valor(v), next(nx), prev(px) {}
};

template <class T>
class CList {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	int elems = 0;
public:
	void push_back(T x);
	void push_front(T x);
	void pop_back();
	void pop_front();
	T& operator[](int pos);
	void print();
};

template <class T>
void CList<T>::push_back(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr && tail == nullptr) {
		head = newnode;
		tail = newnode;
	}
	else {
		newnode->prev = tail;
		tail->next = newnode;
		tail = tail->next;
	}
	elems++;
}

template <class T>
void CList<T>::push_front(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr && tail == nullptr) {
		head = newnode;
		tail = newnode;
	}
	else {
		newnode->next = head;
		head->prev = newnode;
		head = head->prev;
	}
	elems++;
}

template <class T>
void CList<T>::pop_back() {
	if (head == nullptr && tail == nullptr) {
		return;
	}
	else {
		node<T>* temp = tail;
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
		}
		delete temp;
		elems--;
	}
}

template <class T>
void CList<T>::pop_front() {
	if (head == nullptr && tail == nullptr) {
		return;
	}
	else {
		node<T>* temp = head;
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			head = head->next;
			head->prev = nullptr;
		}
		delete temp;
		elems--;
	}
}

template <class T>
T& CList<T>::operator[](int pos) {
	if (pos > elems || pos < 0) {
		static T dummy;
		return dummy;
	}
	int i = 0;
	node<T>* p = head;
	while (i != pos && p) {
		p = p->next;
		i++;
	}
	return p->valor;
}

template <class T>
void CList<T>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


int main() {
	CList<int> l;
	for (int i = 0; i < 10; i++) {
		l.push_back(i);
	}

	l.print();

	for (int i = 10; i < 13; i++) {
		l.push_front(i);
	}

	l.print();

	for (int i = 0; i < 5; i++) {
		l.pop_back();
		l.print();
	}

	for (int i = 0; i < 7; i++) {
		l.pop_front();
		l.print();
	}

	for (int i = 3; i < 8; i++) {
		l.push_front(i);
	}

	l.print();

	l[3] = 99;
	l.print();
}
