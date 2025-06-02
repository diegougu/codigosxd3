#include <iostream>
#include <vector>
using namespace std;


template <class T>
struct Greater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct Less {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T, class C>
class Priorityqueue {
public:
	vector<T> pq;
	C comp;
	void push(T x);
	void pop();
	void print();
};

template <class T, class C>
void Priorityqueue<T, C>::push(T x) {
	pq.push_back(x);
	bool determ = true;
	int act = pq.size() - 1;
	while (act != 0 && determ == true) {
		int posiblenewpos = (act % 2 == 0) ? (act / 2) - 1 : (act / 2);
		if (comp(pq[act], pq[posiblenewpos])) {
			swap(pq[act], pq[posiblenewpos]);
			act = posiblenewpos;
		}
		else {
			determ = false;
		}
	}
}

template <class T, class C>
void Priorityqueue<T, C>::print() {
	for (int i = 0; i < pq.size(); i++) {
		cout << pq[i] << " ";
	}
	cout << endl;
}

template <class T, class C>
void Priorityqueue<T, C>::pop(){
	if (pq.empty()) {
		return;
	}

	pq.front() = pq.back();
	pq.pop_back();
	int act = 0;
	bool determ = false;
	while (determ == false) {
		int left = (act + 1) * 2 - 1;
		int right = (act + 1) * 2;

		if (left < pq.size() && right < pq.size()) {
			if (comp(pq[left], pq[act]) && comp(pq[left], pq[right])) {
				swap(pq[left], pq[act]);
				act = left;
			}
			else if (comp(pq[right], pq[act]) && comp(pq[right], pq[left])) {
				swap(pq[right], pq[act]);
				act = right;
			}
			else {
				determ = true;
			}
		}
		else if (left < pq.size() && right >= pq.size() && comp(pq[left], pq[act])) {
			swap(pq[left], pq[act]);
			act = left;
		}
		else if (left >= pq.size() && right < pq.size() && comp(pq[right], pq[act])) {
			swap(pq[right], pq[act]);
			act = right;
		}
		else {
			determ = true;
		}

	}
}



int main() {
	Priorityqueue<int, Greater<int>> q;
	q.push(100);
	q.print();
	q.push(90);
	q.print();
	q.push(80);
	q.print();
	q.push(70);
	q.print();
	q.push(200);
	q.print();
	q.push(300);
	q.print();
	q.push(500);
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
}


