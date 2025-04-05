#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct node {
	T arr[10];
	node<T>* next = nullptr;
};

template <class T>
class LinkedArrayStack {
private:
	node<T>* List = nullptr;
	T* top = nullptr;
public:
	void push(T x);
	void pop(T& e);
};

template <class T>
void LinkedArrayStack<T>::push(T x) {
	if (List == nullptr && top == nullptr) {
		node<T>* newnode = new node<T>;
		List = newnode;
		top = List->arr;
		*top = x;
	}
	else if (top == List->arr + 9) {
		node<T>* newnode = new node<T>;
		newnode->next = List;
		List = newnode;
		top = List->arr;
		*top = x;
	}
	else {
		top++;
		*top = x;
	}
}

template <class T>
void LinkedArrayStack<T>::pop(T& e) {
	if (List == nullptr && top == nullptr) {
		e = -9999;
		return;
	}
	else if (top == List->arr) {
		e = *top;
		node<T>* temp = List;
		List = List->next;
		if (List == nullptr) {
			top = nullptr;
		}
		else {
			top = List->arr + 9;
		}
		delete temp;
	}
	else {
		e = *top;
		top--;
	}
}


int main() {
	LinkedArrayStack<int> s;
	for (int i = 0; i < 17; i++) {
		s.push(i);
	}

	for (int i = 0; i < 17; i++) {
		int e = 0;
		s.pop(e);
		cout << e << " ";
	}

	cout << endl;

	for (int i = 0; i < 5; i++) {
		s.push(i);
	}

	for (int i = 0; i < 2; i++) {
		int e = 0;
		s.pop(e);
		cout << e << " ";
	}



}
	
