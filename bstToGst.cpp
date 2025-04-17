#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class CBinTree {
private:
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
    void Reverse(CBinNode* p, int& carry);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void bstToGst();
};

bool CBinTree::find(int x, CBinNode**& p) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
    CBinNode** p;
    if (find(x, p)) {
        return false;
    }
    *p = new CBinNode(x);
    return true;
}

CBinNode** CBinTree::Rep(CBinNode** p) {
    m_b = !m_b;
    p = &((*p)->nodes[!m_b]);
    while ((*p)->nodes[m_b]) {
        p = &((*p)->nodes[m_b]);
    }
    return p;
}

bool CBinTree::Remove(int x) {
    CBinNode** p;
    if (!find(x, p)) {
        return false;
    }


    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }

    CBinNode* temp = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete temp;
    return true;
}

void CBinTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}

void CBinTree::Reverse(CBinNode* p, int& carry) {
    if (!p) return;

    Reverse(p->nodes[1], carry);

    carry += p->value;
    p->value = carry;

    Reverse(p->nodes[0], carry);
}

void CBinTree::bstToGst() {
    int carry = 0;
    Reverse(m_root, carry);

}

int main() {
    CBinTree t;
    CBinTree t2;

    t.Insert(4);
    t.Insert(1);
    t.Insert(6);
    t.Insert(0);
    t.Insert(2);
    t.Insert(3);
    t.Insert(5);
    t.Insert(7);
    t.Insert(8);
    t.print();
    t.bstToGst();
    t.print();

    t2.Insert(5);
    t2.Insert(4);
    t2.Insert(3);
    t2.Insert(2);
    t2.Insert(1);
    t2.print();
    t2.bstToGst();
    t2.print();
}
