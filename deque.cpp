#include <iostream>

using namespace std;

template <class T>
class Deque {
private:
	int elements = 0;
	int map_tam = 0;
	int arr_tam = 0;
	int arrays = 0;
	T** map = nullptr;
	T** ini_map = nullptr;
	T** fin_map = nullptr;
	T* ini_array = nullptr;
	T* fin_array = nullptr;
	void ExpandOrColapse(int newtammap);
public:
	Deque(int tm, int ta) : map_tam(tm), arr_tam(ta) {
		map = new T * [map_tam];
		ini_map = map + (map_tam / 2);
		fin_map = ini_map;
	}
	void push_front(T x);
	void push_back(T x);
	void pop_front();
	void pop_back();
	T& operator[](int pos);
	void print();
};

template <class T>
T& Deque<T>::operator[](int pos) {
	if (pos >= elements) {
		static T random;
		return random;
	}

	int espaciosvacios = ini_array - *ini_map;
	int posmap = pos / arr_tam;
	int posarray = (pos % arr_tam) + espaciosvacios;
	T** m = ini_map + posmap;
	T* a = *m + posarray;
	return *a;

}

template <class T>
void Deque<T>::ExpandOrColapse(int newtammap) {
	T** newmapa = new T * [newtammap];
	T** i = newmapa + arrays - 1;
	T** j = ini_map;
	ini_map = i;
	while (j <= fin_map) {
		*i = *j;
		i++;
		j++;
	}
	fin_map = i - 1;
	map_tam = newtammap;
	map = newmapa;
}

template <class T>
void Deque<T>::push_back(T x) {
	if (ini_array == nullptr && fin_array == nullptr) {
		*fin_map = new T[arr_tam];
		ini_array = *fin_map + (arr_tam / 2);
		fin_array = *fin_map + (arr_tam / 2);
		*fin_array = x;
		elements++;
		arrays++;
	}
	else if (fin_array == *fin_map + arr_tam - 1) {
		if (fin_map == map + map_tam - 1) {
			ExpandOrColapse(map_tam * 2);
		}
		fin_map++;
		*fin_map = new T[arr_tam];
		fin_array = *fin_map;
		*fin_array = x;
		elements++;
		arrays++;
	}
	else {
		fin_array++;
		*fin_array = x;
		elements++;
	}
}

template <class T>
void Deque<T>::push_front(T x) {
	if (ini_array == nullptr && fin_array == nullptr) {
		*fin_map = new T[arr_tam];
		ini_array = *fin_map + (arr_tam / 2);
		fin_array = *fin_map + (arr_tam / 2);
		*ini_array = x;
		elements++;
		arrays++;
	}
	else if (ini_array == *ini_map) {
		ini_map--;
		*ini_map = new T[arr_tam];
		ini_array = *ini_map + arr_tam - 1;
		*ini_array = x;
		elements++;
		arrays++;
	}
	else {
		ini_array--;
		*ini_array = x;
		elements++;
	}
}

template <class T>
void Deque<T>::pop_front() {
	if (ini_array == nullptr && fin_array == nullptr && elements == 0) {
		return;
	}
	else if (ini_array == fin_array && elements == 1 && ini_map == fin_map) {
		ini_array = nullptr;
		fin_array = nullptr;
		T* temp = *ini_map;
		elements--;
		arrays--;
		delete temp;
	}
	else if (ini_array == *ini_map + arr_tam - 1) {
		if (arrays == map_tam / 2) {
			ExpandOrColapse(map_tam / 2);
		}
		T* temp = *ini_map;
		ini_map++;
		ini_array = *ini_map;
		elements--;
		arrays--;
		delete temp;
	}
	else {
		ini_array++;
		elements--;
	}
}

template <class T>
void Deque<T>::pop_back() {
	if (ini_array == nullptr && fin_array == nullptr && elements == 0) {
		return;
	}
	else if (ini_array == fin_array && elements == 1 && ini_map == fin_map) {
		ini_array = nullptr;
		fin_array = nullptr;
		T* temp = *ini_map;
		elements--;
		arrays--;
		delete temp;
	}
	else if (fin_array == *fin_map) {
		if (arrays == map_tam / 2) {
			ExpandOrColapse(map_tam / 2);
		}
		T* temp = *fin_map;
		fin_map--;
		fin_array = *fin_map + (arr_tam - 1);
		elements--;
		arrays--;
		delete temp;
	}
	else {
		fin_array--;
		elements--;
	}
}

template <class T>
void Deque<T>::print() {
	T** temp_ini = ini_map;
	T* ini_array_temp = ini_array;
	while (temp_ini <= fin_map) {
		cout << "[ ";
		while (ini_array_temp <= *temp_ini + arr_tam - 1) {
			cout << *ini_array_temp << " ";
			if (ini_array_temp == fin_array) {
				break;
			}
			ini_array_temp++;
		}
		cout << " ] ";
		temp_ini++;
		ini_array_temp = *temp_ini;
	}
	cout << endl;
}

int main() {
	Deque<int> d(3, 5);
	d.push_front(5);
	d.push_back(6);
	d.push_back(7);
	d.push_back(8);
	d.push_back(9);
	d.push_back(10);
	d.push_back(11);
	d.push_back(12);
	d.push_back(13);
	d.push_back(14);
	d.push_front(4);
	d.push_front(3);
	d.push_front(2);
	d.push_front(1);
	d.print();

	d.pop_back();
	d.print();
	d.pop_back();
	d.print();

	d.pop_front();
	d.print();
	d.pop_front();
	d.print();


	Deque<int> d2(5, 7);
	d2.push_front(9);
	d2.push_front(7);
	d2.push_front(4);
	d2.push_front(1);
	d2.push_front(3);
	d2.push_front(8);
	d2.push_back(6);
	d2.push_back(5);
	d2.push_back(2);
	d2.push_back(7);

	d2.print();
	int valor = d2[7];
	int valor2, valor3, valor4;
	valor2 = d2[1];
	valor3 = d2[0];
	valor4 = d2[8];
	cout << valor << endl;
	cout << valor2 << endl;
	cout << valor3 << endl;
	cout << valor4;


}
