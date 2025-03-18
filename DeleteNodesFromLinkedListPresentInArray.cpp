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
	void DNFLLPIA(vector<T>& nums);
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
void LinkedList<T>::DNFLLPIA(vector<T>& nums) {
	if (head == nullptr) {
		return;
	}

	for (int i = 0; i < nums.size(); i++) {
		for (node<T>** p = &head; *p; p = &((*p)->next)) {
			while (nums[i] == (*p)->valor) {
				node<T>* temp = *p;
				*p = temp->next;
				delete temp;
			}

		}
	}
}



int main() {
	LinkedList<int> l1;
	LinkedList<int> l2;

	vector<int> nums;
	vector<int> nums2;

	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);

	l1.push(5);
	l1.push(4);
	l1.push(3);
	l1.push(2);
	l1.push(1);

	l1.print();
	l1.DNFLLPIA(nums);
	l1.print();

	l2.push(2);
	l2.push(1);
	l2.push(2);
	l2.push(1);
	l2.push(2);
	l2.push(1);
	l2.push(2);
	l2.push(1);
	l2.push(1);

	nums2.push_back(1);
	nums2.push_back(4);

	l2.print();
	l2.DNFLLPIA(nums2);
	l2.print();
}
