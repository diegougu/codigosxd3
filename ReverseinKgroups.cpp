#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct ASC {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T, class C>
class LinkedList {
private:
	node<T>* head = nullptr;
	bool find(C comp, T x, node<T>**& p);
	void Reverse(pair<node<T>*, node<T>*> x, node<T>*& p);
public:
	void ReverseInKGroups(int k);
	void add(T x);
	void del(T x);
	void print();
};

template <class T, class C>
bool LinkedList<T, C>::find(C comp, T x, node<T>**& p) {
	p = &head;
	for (; *p && comp(x, (*p)->valor); p = &((*p)->next));
	return *p && (*p)->valor == x;
}

template <class T, class C>
void LinkedList<T, C>::add(T x) {
	node<T>** p;
	C comp;
	if (find(comp, x, p)) {
		return;
	}
	node<T>* temp = new node<T>(x);
	temp->next = *p;
	*p = temp;
}

template <class T, class C>
void LinkedList<T, C>::del(T x) {
	node<T>** p;
	C comp;
	if (!find(comp, x, p)) {
		return;
	}
	node<T>* temp = *p;
	*p = temp->next;
	delete temp;
}

template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


template <class T, class C>
void LinkedList<T, C>::Reverse(pair<node<T>*, node<T>*> x, node<T>*& p) {
	node<T>* ini = x.first;
	node<T>* fin = x.second;
	node<T>* copy = fin;
	while (fin != ini) {
		node<T>* p = ini;
		for (; p->next != fin; p = p->next);
		fin->next = p;
		fin = p;
	}
	ini->next = nullptr;
	p = copy;
	if (ini == head) {
		head = copy;
	}
	

}


template <class T, class C>
void LinkedList<T, C>::ReverseInKGroups(int k) {
	if (head == nullptr || k <= 1 || head->next == nullptr) {
		return;
	}
	node<T>* p = head;
	int i = 1;
	vector<pair<node<T>*, node<T>*>> groups;
	pair<node<T>*, node<T>*> x;
	x.first = nullptr;
	x.second = nullptr;
	while (p) {
		if (i == 1) {
			x.first = p;
		}

		if (i == k || p->next == nullptr) {
			x.second = p;
			i = 0;
			groups.push_back(x);
			x.first = nullptr;
			x.second = nullptr;
		}
		i++;
		p = p->next;

	}

	vector<node<T>*> conect;
	for (int i = 0; i < groups.size(); i++) {
		node<T>* p;
		Reverse(groups[i], p);
		conect.push_back(p);
	}

	for (int i = 0; i < conect.size() - 1; i++) {
		node<T>* p = conect[i];
		for (; p->next != nullptr; p = p->next);
		node<T>* q = conect[i + 1];
		p->next = q;

	}


}


int main() {
	LinkedList<int, ASC<int>> l1;
	LinkedList<int, DESC<int>> l2;
	int arr[8] = { 5,4,3,1,2,7,6,8 };
	for (int i = 0; i < 8; i++) {
		l1.add(arr[i]);
	}
	l1.print();
	l1.ReverseInKGroups(3);
	l1.print();
}
