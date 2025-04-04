#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
	T arr[10];
	T* head = arr;
	T* tail = arr - 1;
public:
	void push(T x);
	void pop(T& e);
	void print();
};

template <class T>
void Queue<T>::push(T x) {
	if ((head == arr && tail == arr + 9) || ((tail != arr && head != arr) && tail == head)) {
		return;
	}
	else if (tail == arr + 9 && head != arr) {
		tail = arr;
		*tail = x;
	}
	else {
		tail++;
		*tail = x;
	}
}

template <class T>
void Queue<T>::pop(T& e) {
	if (head == tail) {
		return;
	}
	else if (head == arr + 9) {
		head = arr;
		e = *head;
	}
	else {
		e = *head;
		head++;
	}
}


template <class T>
void Queue<T>::print() {
	T* p = head;
	while (p != tail) {
		if (p == arr + 10 && p != tail) {
			p = arr;
		}
		cout << *p << " ";
		if (!(p == arr + 10 && p != tail)) {
			p++;
		}
	}
	cout << *tail << endl;
}


int main() {
	Queue<int> q;
	for (int i = 0; i < 15; i++) {
		q.push(i);
	}
	q.print();

	for (int i = 0; i < 5; i++) {
		int e = 0;
		q.pop(e);
		cout << e << endl;
	}
	q.print();

	for (int i = 30; i < 35; i++) {
		q.push(i);
	}
	q.print();

	for (int i = 0; i < 1; i++) {
		int e = 0;
		q.pop(e);
		cout << e << endl;
	}
	q.print();

}
