#include <iostream>
using namespace std;

class SparseMatrixFase3;

struct objx;

struct node {
	int val, x, y;
	node* right = nullptr;
	node* bottom = nullptr;
	node(int v, int _x, int _y, node* r = nullptr, node* b = nullptr) : val(v), x(_x), y(_y), right(r), bottom(b) {}
};

class SparseMatrixFase3 {
public:
	int xtam, ytam;
	node** ejex = nullptr;
	node** ejey = nullptr;
	SparseMatrixFase3(int x_, int y_) : xtam(x_), ytam(y_) {
		ejex = new node* [xtam];
		ejey = new node* [ytam];
		for (int i = 0; i < xtam; i++) {
			ejex[i] = nullptr;
		}

		for (int i = 0; i < ytam; i++) {
			ejey[i] = nullptr;
		}
	}

	void set(int x, int y, int val);
	int get(int x, int y);
	void print();
	objx operator()(int x, int y);
private:
	bool findright(node**& p, int x, int y);
	bool findbottom(node**& q, int x, int y);
};

struct objx {
	SparseMatrixFase3* m = nullptr;
	objx(SparseMatrixFase3* m_ = nullptr) : m(m_) {}
	int x, y;
	objx operator=(int v) {
		m->set(x, y, v);
		return *this;
	}

	operator int() {
		return m->get(x, y);
	}

	objx operator=(objx& ox) {
		m->set(x, y, ox.m->get(ox.x, ox.y));
		return *this;
	}
};


bool SparseMatrixFase3::findright(node**& p, int x, int y) {
	p = &ejex[x];
	for (; *p && (*p)->y < y; p = &((*p)->right));
	return *p && (*p)->x == x && (*p)->y == y;
}

bool SparseMatrixFase3::findbottom(node**& q, int x ,int y) {
	q = &ejey[y];
	for (; *q && (*q)->x < x; q = &((*q)->bottom));
	return *q && (*q)->x == x && (*q)->y == y;
}

void SparseMatrixFase3::set(int x, int y, int val) {
	if (x >= xtam || y >= ytam) {
		return;
	}

	node** p = &ejex[x];
	node** q = &ejey[y];
	bool fr = findright(p, x, y);
	bool fb = findbottom(q, x, y);
	if (fr && fb) {
		if (val != 0) {
			(*p)->val = val;
		}
		else {
			node* temp = *p;
			*p = temp->right;
			*q = temp->bottom;
			delete temp;
		}
	}
	else {
		node* newnode = new node(val, x, y);
		newnode->right = *p;
		*p = newnode;
		newnode->bottom = *q;
		*q = newnode;
	}
}

int SparseMatrixFase3::get(int x, int y) {
	if (x >= xtam || y >= ytam) {
		return 0;
	}

	node** p = &ejex[x];
	node** q = &ejey[y];

	bool fr = findright(p, x, y);
	bool fb = findbottom(q, x, y);
	if (fr && fb) {
		return (*p)->val;
	}
	return 0;
}

void SparseMatrixFase3::print() {
	for (int i = 0; i < xtam; i++) {
		for (int j = 0; j < ytam; j++) {
			cout << "( " << i << " ," << j << ", " << get(i, j) << " )" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

objx SparseMatrixFase3::operator()(int x, int y) {
	objx ox(this);
	ox.x = x;
	ox.y = y;
	return ox;
}

int main() {
	SparseMatrixFase3 m(4, 4);

	m(0, 1) = 5;
	m(0, 2) = 10;
	m(0, 0) = 3;
	m(0, 3) = 8;

	m(1, 3) = 12;
	m(1, 0) = 6;
	m(1, 2) = 9;

	m(2, 2) = 14;
	m(2, 1) = 4;

	m(3, 3) = 11;
	m(3, 0) = 7;

	cout << "Contenido de la matriz tras inserciones:\n";
	m.print();

	cout << "\nAccesos individuales (operator()):\n";
	cout << "m(0, 0) = " << m(0, 0) << endl;
	cout << "m(0, 2) = " << m(0, 2) << endl;
	cout << "m(1, 2) = " << m(1, 2) << endl;
	cout << "m(3, 0) = " << m(3, 0) << endl;
	cout << "m(3, 2) = " << m(3, 2) << " (debería ser 0, no existe)\n";

	m(1, 2) = 99;
	cout << "\nDespués de modificar m(1, 2) = 99:\n";
	m.print();

	m(0, 1) = 0;
	m(3, 3) = 0;
	cout << "\nDespués de eliminar m(0, 1) y m(3, 3):\n";
	m.print();
	cout << m(2, 3) << " " << m(1, 2) << endl;
	m(2, 3) = m(1, 2); 
	cout << "\nDespués de m(2, 3) = m(1, 2):\n";
	m.print();

	return 0;
}
