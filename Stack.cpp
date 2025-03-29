#include <iostream>
using namespace std;

template <class T>
class Stack {
private:
	T* top = nullptr;
	T elems[10];
public:
	void push(T x);
	void pop(T& e);
};


template <class T>
void Stack<T>::push(T x) {
	if (top == nullptr) {
		top = elems;
		*top = x;
	}
	else if (top == elems + 9) {
		return;
	}
	else {
		top++;
		*top = x;
	}
}

template <class T>
void Stack<T>::pop(T& e) {
	if (top == nullptr || top < elems) {
		top = nullptr;
		e = -43857498;
		return;
	}
	else {
		e = *top;
		top--;
	}
}


int main() {
	Stack<int> pila;
	for (int i = 0; i < 10; i++) {
		pila.push(i);
	}
	int x = 0;
	for (int i = 0; i < 12; i++) {
		pila.pop(x);
		cout << x << " ";
	}
	cout << endl;

	for (int i = 0; i < 4; i++) {
		pila.push(i);
	}

	for (int i = 0; i < 2; i++) {
		pila.pop(x);
		cout << x << " ";
	}
}
