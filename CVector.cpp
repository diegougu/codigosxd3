#include <iostream>
using namespace std;

template <class T>
class CVector {
private:
	void ExpandOrColapse(int newtam);
public:
	int ite = 0;
	int tam = 0;
	CVector(int t = 1) : tam(t) {}
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
		//cout << ite << " " << tam << endl;
		ExpandOrColapse(tam / 2);
		//cout << ite << " " << tam << endl;
	}
	ite--;
}

template <class T>
void CVector<T>::pop_front() {
	if (ite == 0) {
		return;
	}
	else if (ite == tam / 2) {
		//cout << ite << " " << tam << endl;
		ExpandOrColapse(tam / 2);
		//cout << ite << " " << tam << endl;
	}
	for (int i = 0; i < ite; i++) {
		arr[i] = arr[i + 1];
	}
	ite--;
}

template <class T>
T& CVector<T>::operator[](int pos) {
	if (pos < 0 || pos > ite) {
		static int dummy = -9999;
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

int main() {
	CVector<int> v(10);
	for (int i = 0; i < 10; i++) {
		v.push_back(i);
	}
	v.print();

	for (int i = 10; i < 20; i++) {
		v.push_front(i);
	}
	v.print();

	for (int i = 0; i < 10; i++) {
		v.pop_back();
		v.print();
	}

	for (int i = 0; i < 10; i++) {
		v.pop_front();
		v.print();
	}

	for (int i = 0; i < 3; i++) {
		v.push_back(i);
	}
	v.print();

}
