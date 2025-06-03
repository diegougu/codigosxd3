#include <iostream>
#include <vector>
using namespace std;

class SparseMatrixFase0 {
public:
	int x1, y1;
	int** ejex = nullptr;

	SparseMatrixFase0(int _x, int _y) : x1(_x), y1(_y) {
		ejex = new int* [x1];
		for (int** i = ejex; i < ejex + x1; i++) {
			*i = new int[y1];
			for (int* j = *i; j < *i + y1; j++) {
				*j = 0;
			}
		}
	}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
};

void SparseMatrixFase0::set(int x, int y, int v) {
	if (x > x1 || y > y1) {
		return;
	}

	int** posx = ejex + x;
	int* posy = *posx + y;

	*posy = v;
}

int SparseMatrixFase0::get(int x, int y) {
	if (x > x1 || y > y1) {
		return 0;
	}
	int** posx = ejex + x;
	int* posy = *posx + y;
	return *posy;
}

void SparseMatrixFase0::print() {
	for (int** i = ejex; i < ejex + x1; i++) {
		for (int* j = *i; j < *i + y1; j++) {
			if (*j != 0) {
				cout << *j << " ";
			}
		}
	}
	cout << endl;
}

int main() {
	SparseMatrixFase0 m1(8, 8);
	m1.set(0, 3, 37);
	m1.print();
	m1.set(0, 2, 15);
	m1.print();
	m1.set(1, 0, 25);
	m1.print();
	m1.set(0, 1, 53);
	m1.print();
	m1.set(1, 3, 95);
	m1.print();
	m1.set(0, 0, 54);
	m1.print();
	m1.set(3, 3, 51);
	m1.print();
	m1.set(2, 1, 60);
	m1.print();
	m1.set(1, 2, 57);
	m1.print();
	m1.set(5, 5, 27);
	m1.print();
	m1.set(4, 2, 17);
	m1.print();

	cout << m1.get(0, 0) << endl;
	cout << m1.get(1, 0) << endl;
	cout << m1.get(0, 1) << endl;
	cout << m1.get(2, 1) << endl;

}
