#include <iostream>
using namespace std;

template <class T>
struct node{
	T arr[10];
	node<T>* next = nullptr;
};

template <class T>
class LinkedArrayQueue {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	T* headptr = nullptr;
	T* tailptr = nullptr;
public:
	void push(T x);
	void pop(T& e);
};

template <class T>
void LinkedArrayQueue<T>::push(T x) {
	if (head == nullptr && tail == nullptr) {
		node<T>* newnode = new node<T>;
		head = newnode;
		tail = newnode;
		headptr = head->arr;
		tailptr = head->arr;
		*tailptr = x;
	}
	else if (tailptr == tail->arr + 9) {
		node<T>* newnode = new node<T>;
		tail->next = newnode;
		tail = tail->next;
		tailptr = tail->arr;
		*tailptr = x;
	}
	else {
		tailptr++;
		*tailptr = x;
	}
}

template <class T>
void LinkedArrayQueue<T>::pop(T& e) {
	if (head == nullptr && tail == nullptr) {
		e = -9999;
		return;
	}
	else if (headptr == head->arr + 9 || (head == tail && headptr == tailptr)) {
		node<T>* temp = head;
		e = *headptr;
		if (head->next == nullptr) {
			head = nullptr;
			tail = nullptr;
		}
		else {
			head = head->next;
			headptr = head->arr;
		}
		delete temp;
	}
	else {
		e = *headptr;
		headptr++;
	}
}

int main() {
	LinkedArrayQueue<int> q;
	for (int i = 0; i < 23; i++) {
		cout << i << " ";
		q.push(i);
	}

	cout << endl;

	for (int i = 0; i < 20; i++) {
		int e = 0;
		q.pop(e);
		cout << e << " ";
	}

	cout << endl;

	for (int i = 0; i < 3; i++) {
		int e = 0;
		q.pop(e);
		cout << e << " ";
	}

	cout << endl;

	for (int i = 0; i < 4; i++) {
		cout << i << " ";
		q.push(i);
	}

	cout << endl;

	for (int i = 0; i < 2; i++) {
		int e = 0;
		q.pop(e);
		cout << e << " ";
	}
}
