#include <iostream>
using namespace std;

template <class T>
struct arrNode {
	const static int tam = 10;
	T arr[tam];
	arrNode<T>* next = nullptr;
	arrNode<T>* prev = nullptr;
};

template <class T>
class LinkedDeque {
private:
	arrNode<T>* map = nullptr;
	arrNode<T>* ini = nullptr;
	arrNode<T>* fin = nullptr;
	T* ini_arr = nullptr;
	T* fin_arr = nullptr;
	int elements = 0;
public:
	void push_back(T x);
	void push_front(T x);
	void pop_back();
	void pop_front();
	void print();
	T& operator[](int pos);
};


template <class T>
void LinkedDeque<T>::push_back(T x) {
	if (map == nullptr) {
		arrNode<T>* temp = new arrNode<T>;
		map = temp;
		ini = temp;
		fin = temp;
		ini_arr = ini->arr + (ini->tam / 2);
		fin_arr = ini->arr + (ini->tam / 2);
		*fin_arr = x;
		elements++;
	}
	else if (fin_arr == fin->arr + fin->tam - 1) {
		arrNode<T>* temp = new arrNode<T>;
		fin->next = temp;
		temp->prev = fin;
		fin = fin->next;
		fin_arr = fin->arr;
		*fin_arr = x;
		elements++;
	}
	else {
		fin_arr++;
		*fin_arr = x;
		elements++;
	}
}

template <class T>
void LinkedDeque<T>::push_front(T x) {
	if (map == nullptr) {
		arrNode<T>* temp = new arrNode<T>;
		map = temp;
		ini = temp;
		fin = temp;
		ini_arr = ini->arr + (ini->tam / 2);
		fin_arr = ini->arr + (ini->tam / 2);
		*ini_arr = x;
		elements++;
	}
	else if (ini_arr == ini->arr) {
		arrNode<T>* temp = new arrNode<T>;
		temp->next = ini;
		ini->prev = temp;
		ini = ini->prev;
		ini_arr = ini->arr + ini->tam - 1;
		*ini_arr = x;
		elements++;
	}
	else {
		ini_arr--;
		*ini_arr = x;
		elements++;
	}
}

template <class T>
void LinkedDeque<T>::pop_back() {
	if (map == nullptr) {
		return;
	}
	else if (map == ini && map == fin && fin_arr == ini_arr && elements == 1) {
		arrNode<T>* temp = map;
		map = nullptr;
		ini = nullptr;
		fin = nullptr;
		delete temp;
		elements--;
	}
	else if (fin_arr == fin->arr) {
		if (fin == map) {
			map = map->prev;
		}
		arrNode<T>* temp = fin;
		fin = fin->prev;
		fin->next = nullptr;
		fin_arr = fin->arr + fin->tam - 1;
		elements--;
		delete temp;
	}
	else {
		fin_arr--;
		elements--;
	}
}

template <class T>
void LinkedDeque<T>::pop_front() {
	if (map == nullptr) {
		return;
	}
	else if (map == ini && map == fin && fin_arr == ini_arr && elements == 1) {
		arrNode<T>* temp = map;
		map = nullptr;
		ini = nullptr;
		fin = nullptr;
		delete temp;
		elements--;
	}
	else if (ini_arr == ini->arr + ini->tam - 1) {
		if (ini == map) {
			map = map->next;
		}
		arrNode<T>* temp = ini;
		ini = ini->next;
		ini->prev = nullptr;
		ini_arr = ini->arr;
		elements--;
		delete temp;
	}
	else {
		ini_arr++;
		elements--;
	}
}

template <class T>
void LinkedDeque<T>::print() {
	arrNode<T>* p = ini;
	T* ptr = ini_arr;

	while (p != nullptr) {
		cout << "[ ";
		T* end = (p == fin) ? fin_arr : (p->arr + p->tam - 1);

		for (; ptr <= end; ptr++) {
			cout << *ptr << " ";
		}
		cout << "] -> ";
		p = p->next;
		if (p != nullptr) ptr = p->arr;
	}
	cout << endl;
}


template <class T>
T& LinkedDeque<T>::operator[](int pos) {
	if (pos >= elements) {
		static T x;
		return x;
	}
	int count = 0;
	arrNode<T>* p = ini;
	T* ptr = ini_arr;

	while (p != nullptr) {
		while (ptr <= p->arr + p->tam - 1 && ptr <= fin_arr) {
			if (count == pos) {
				return *ptr;
			}
			count++;
			ptr++;
		}
		p = p->next;
		if (p != nullptr) ptr = p->arr;
	}
}


int main() {
	LinkedDeque<int> l1;

	for (int i = 0; i < 13; i++) {
		l1.push_back(i);
	}
	l1.print();

	for (int i = 13; i < 27; i++) {
		l1.push_front(i);
	}
	l1.print();

	for (int i = 0; i < 10; i++) {
		l1.pop_back();
	}
	l1.print();

	for (int i = 0; i < 10; i++) {
		l1.pop_front();
	}
	l1.print();
}
