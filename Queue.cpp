#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
	T arr[10];
	T* head = arr;
	T* tail = arr;
	int elems = 0;
public:
	void push(T x);
	void pop(T& e);
};

template <class T>
void Queue<T>::push(T x) {
	if ((head == arr && tail == arr + 10) || ((tail != arr && head != arr) && tail == head)) {
		cout << "full" << endl;
		return;
	}
	else if (head != arr && tail == arr + 10) {
		tail = arr;
	}
	*tail = x;
	tail++;
	elems++;
}

template <class T>
void Queue<T>::pop(T& e) {
	if (elems == 0) {
		return;
	}
	else if (head == arr + 9) {
		e = *head;
		head = arr;
		elems--;
	}
	else {
		e = *head;
		head++;
		elems--;
	}
}





int main() {
	Queue<int> q;
	for (int i = 0; i < 15; i++) {
		cout << i << endl;
		q.push(i);
	}

	for (int i = 0; i < 5; i++) {
		int e = 0;
		q.pop(e);
		cout << e << endl;
	}

	for (int i = 30; i < 35; i++) {
		q.push(i);
	}

	for (int i = 0; i < 1; i++) {
		int e = 0;
		q.pop(e);
		cout << e << endl;
	}
}
