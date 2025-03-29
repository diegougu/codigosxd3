#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
struct CGreaster {
	inline bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct CLess {
	inline bool operator()(T a, T b) {
		return a < b;
	}
};

class Comparator {
public:
	virtual bool comp(int a, int b) = 0;
};

class CGreaster_Poli : public Comparator {
public:
	bool comp(int a, int b) override { return a > b; }
};

class CLess_Poli : public Comparator {
public:
	bool comp(int a, int b) override { return a < b; }
};

bool FLess(int a, int b) {
	return a < b;
}

bool FGreaster(int a, int b) {
	return a > b;
}

template <class T>
double bubbleSortfuntor(int* arr, int n, T k) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (k(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration<double, milli>(end - start).count();
}

double bubbleSortPoli(int* arr, int n, Comparator* p) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (p->comp(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration<double, milli>(end - start).count();
}

double bubbleSortPunteroAFuncion(int* arr, int n, bool (*PF)(int, int)) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (PF(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration<double, milli>(end - start).count();
}

double bubbleSort(int* arr, int n) {
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration<double, milli>(end - start).count();
}

void refill(int* arr, int n) {
	for (int i = 0, j = n; i < n; i++, j--) {
		arr[i] = j;
	}
}



int main() {
	bool (*PF)(int, int) = &FLess;
	bool (*PF2)(int, int) = &FGreaster;
	CGreaster<int> g;
	CLess<int> l;
	CLess_Poli l2;
	CGreaster_Poli g2;

	vector<int> sizes = { 10, 50, 100, 500, 1000 };

	for (int i = 0; i < sizes.size(); i++) {
		int* ar = new int[sizes[i]];
		refill(ar, sizes[i]);

		cout << "Array size: " << sizes[i] << endl;
		cout << "Bubble Sort Default: " << bubbleSort(ar, sizes[i]) << " ms" << endl;
		refill(ar, sizes[i]);
		cout << "Bubble Sort Functor: " << bubbleSortfuntor(ar, sizes[i], g) << " ms" << endl;
		refill(ar, sizes[i]);
		cout << "Bubble Sort Polimorismo: " << bubbleSortPoli(ar, sizes[i], &g2) << " ms" << endl;
		refill(ar, sizes[i]);
		cout << "Bubble Sort Puntero a funcion: " << bubbleSortPunteroAFuncion(ar, sizes[i], PF2) << " ms" << endl;
		cout << "--------------------------------------" << endl;

		delete[] ar;
	}

}
