#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T>
class LinkedList {
private:
public:
	node<T>* head = nullptr;
	void push(T x);
	void print();
	void SplitLinkedListInParts(int k);
};


template <class T>
void LinkedList<T>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
	}
	else {
		newnode->next = head;
		head = newnode;
	}
}


template <class T>
void LinkedList<T>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template <class T>
void LinkedList<T>:: SplitLinkedListInParts(int k) {
	node<T>* p = head;
	int cnodes = 0;
	for (node<T>* x = head; x ; x = x->next, cnodes++);
	vector<node<T>*> list;
	int val = cnodes / k;
	while (p != nullptr) {
		node<T>* q = p;
		int j = 1;
		for (; j < val; j++, q = q->next);
		if (j >= val) {
			list.push_back(p);
			p = q;
			if (list.size() == k && p->next != nullptr) {
				q = q->next;
				p = q;
			}
			
			if (p != nullptr) {
				p = p->next;
			}
			q->next = nullptr;
		}
		else {
			list.push_back(p);
			p = p->next;
		}		
	}

	if (list.size() < k) {
		while (list.size() != k) {
			list.push_back(nullptr);
		}
	}

	for (int i = 0; i < list.size(); i++) {
		for (node<int>* p = list[i]; p; p = p->next) {
			cout << p->valor << " ";
		}
		cout << endl;
	}

	cout << "--------------------------------------------" << endl;

}






int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;
	LinkedList<int> l3;
	LinkedList<int> l4;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10};
	int arr2[3] = {1,2,3};
	int arr3[5] = { 1,1,1,1,2 };
	int arr4[8] = { 1,3,4,1,4,1,3,1 };

	for (int i = 0; i < 10; i++) {
		l1.push(arr[i]);
	}

	for (int i = 0; i < 3; i++) {
		l2.push(arr2[i]);
	}

	for (int i = 0; i < 5; i++) {
		l3.push(arr3[i]);
	}

	for (int i = 0; i < 8; i++) {
		l4.push(arr4[i]);
	}

	l1.SplitLinkedListInParts(3);
	l2.SplitLinkedListInParts(5);
	l3.SplitLinkedListInParts(2);
	l4.SplitLinkedListInParts(4);



}
