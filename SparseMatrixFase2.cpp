#include <iostream>
using namespace std;

struct node {
	int val, x, y;
	node* next = nullptr;
	node(int v, int _x, int _y, node* n = nullptr) : val(v), x(_x), y(_y), next(n) {}
};

class SparseMatrixFase2 {
public:
	int x1, y1;
	node** ejex = nullptr;
	SparseMatrixFase2(int x_, int y_) : x1(x_), y1(y_) {
		ejex = new node* [x1];
		for (int i = 0; i < x1; i++) {
			ejex[i] = nullptr;
		}
	}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
private:
	bool find(node**& p, int x, int y);
};

bool SparseMatrixFase2::find(node**& p, int x, int y) {
	p = &ejex[x];
	for (; *p && (*p)->y < y; p = &((*p)->next));
	return *p && (*p)->x == x && (*p)->y == y;
}

void SparseMatrixFase2::set(int x, int y, int v) {
	if (x >= x1 || y >= y1) {
		return;
	}
	node** p;
	if (find(p, x, y)) {
		if (v != 0) {
			(*p)->val = v;
		}
		else {
			node* temp = *p;
			*p = temp->next;
			delete temp;
		}
	}
	else {
		node* newnode = new node(v, x, y);
		newnode->next = *p;
		*p = newnode;
	}
}

int SparseMatrixFase2::get(int x, int y) {
	if (x >= x1 && y >= y1) {
		return 0;
	}
	
	node** p;
	if (find(p, x, y)) {
		return (*p)->val;
	}
	else {
		return 0;
	}
}

void SparseMatrixFase2::print() {
	for (int i = 0; i < x1; i++) {
		for (int j = 0; j < y1; j++) {
			cout << "( " << i << ", " << j << " ," << get(i, j)<< " )" << endl;
		}
	}
	cout << endl;
}

int main() {
	SparseMatrixFase2 m1(6, 6);
	m1.set(0, 3, 37);
	m1.set(0, 2, 15);
	m1.set(1, 0, 25);
	m1.set(0, 1, 53);
	m1.set(1, 3, 95);
	m1.set(0, 0, 54);
	m1.set(3, 3, 51);
	m1.set(2, 1, 60);
	m1.set(1, 2, 57);
	m1.set(5, 5, 27);
	m1.set(4, 2, 17);
	m1.print();

	cout << m1.get(0, 0) << endl;
	cout << m1.get(0, 1) << endl;
	cout << m1.get(1, 0) << endl;
	cout << m1.get(2, 1) << endl;
	cout << m1.get(3, 3) << endl;

}
