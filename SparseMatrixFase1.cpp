#include <iostream>
using namespace std;

struct node {
	int val;
	int x;
	int y;
	node* next = nullptr;
	node(int v, int x_, int y_ , node* n = nullptr) : val(v), x(x_), y(y_), next(n) {}
};

class SparseMatrixFase1 {
public:
	int ejex = 0;
	int ejey = 0;
	node* head = nullptr;
	SparseMatrixFase1(int ex, int ey) : ejex(ex), ejey(ey) {}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
private:
	bool find(node**& p, int x, int y);
};

bool SparseMatrixFase1::find(node**& p, int x, int y) {
	p = &head;
	for (; *p && (*p)->x < x; p = &((*p)->next));

	for(; *p && (*p)->y < y; p = &((*p)->next));
	return *p && (*p)->x == x && (*p)->y == y;
}

void SparseMatrixFase1::set(int x, int y, int v) {
	if (x >= ejex || y >= ejey) {
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
		node* newnode = new node(v,x,y);
		newnode->next = *p;
		*p = newnode;
	}
}

int SparseMatrixFase1::get(int x, int y) {
	if (x >= ejex || y >= ejey) {
		return 0;
	}
	node** p;
	if (find(p, x, y)) {
		return (*p)->val;
	}
	return 0;
}

void SparseMatrixFase1::print() {
	for (node* p = head; p; p = p->next) {
		cout << "( " << p->x << "," << p->y << " ," << p->val << " )" << endl;
	}
	cout << endl;
}

int main() {
	SparseMatrixFase1 m1(8, 8);
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
	cout << m1.get(0, 1) << endl;
	cout << m1.get(1, 0) << endl;
	cout << m1.get(2, 1) << endl;
	cout << m1.get(3, 3) << endl;

}
