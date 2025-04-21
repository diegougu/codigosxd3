#include <iostream>
using namespace std;

template <class T>
class CVector {
private:
	void ExpandOrColapse(int newtam);
public:
	int ite = 0;
	int tam = 0;
	CVector(int t = 5) : tam(t) {}
	T* arr = new T[tam];
	void push_back(T x);
	void push_front(T x);
	void pop_back();
	void pop_front();
	T& operator[](int pos);
	void print();
};

template <class T>
void CVector<T>::ExpandOrColapse(int newtam) {
	T* newarr = new T[newtam];
	T* temp = arr;
	for (int i = 0; i < ite; i++) {
		newarr[i] = arr[i];
	}
	arr = newarr;
	tam = newtam;
	delete temp;
}

template <class T>
void CVector<T>::push_back(T x) {
	if (ite == tam) {
		ExpandOrColapse(tam * 2);
	}
	arr[ite] = x;
	ite++;
}

template <class T>
void CVector<T>::push_front(T x) {
	if (ite == tam) {
		ExpandOrColapse(tam * 2);
	}
	for (int i = ite; i > 0; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = x;
	ite++;
}

template <class T>
void CVector<T>::pop_back() {
	if (ite == 0) {
		return;
	}
	else if (ite == tam / 2) {
		ExpandOrColapse(tam / 2);
	}
	ite--;
}

template <class T>
void CVector<T>::pop_front() {
	if (ite == 0) {
		return;
	}
	else if (ite == tam / 2) {
		ExpandOrColapse(tam / 2);
	}
	for (int i = 0; i < ite; i++) {
		arr[i] = arr[i + 1];
	}
	ite--;
}

template <class T>
T& CVector<T>::operator[](int pos) {
	if (pos < 0 || pos > ite) {
		static T dummy;
		return dummy;
	}
	return arr[pos];
}

template <class T>
void CVector<T>::print() {
	for (int i = 0; i < ite; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

template <class T, class K>
struct AdaptorQueue {
	K adap;
	void push(T x) {
		adap.push_back(x);
	}

	void pop() {
		adap.pop_front();
	}

	void print() {
		adap.print();
	}
};


template <class T, class K>
struct AdaptorStack{
	K adap;
	void push(T x) {
		adap.push_back(x);
	}

	void pop() {
		adap.pop_back();
	}

	void print() {
		adap.print();
	}
};

int main() {
	AdaptorStack<int, CVector<int>> adaptor;
	for (int i = 0; i < 25; i++) {
		adaptor.push(i);
	}
	adaptor.print();

	for (int i = 0; i < 5; i++) {
		adaptor.pop();
	}
	adaptor.print();

	cout << "---------------------------------------------------------------------" << endl;
	AdaptorQueue<int, CVector<int>> adaptor2;
	for (int i = 0; i < 25; i++) {
		adaptor2.push(i);
	}

	adaptor2.print();

	for (int i = 0; i < 5; i++) {
		adaptor2.pop();
	}

	adaptor2.print();
}
