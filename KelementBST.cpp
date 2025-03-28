#include <iostream>
#include <queue>
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
    void Inverse(CBinNode* p, int& i, int i2, int& val);
public:
    CBinNode* m_root = nullptr;
    int KelementBST(int k);
    bool Insert(int x);
    bool Remove(int x);
    void print();
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

void CBinTree::Inverse(CBinNode* p, int& i, int i2, int& val) {
    if (!p) return;

    Inverse(p->nodes[1], i, i2, val);
    i++;
    if (i == i2) {
        val = p->value;
    }

    Inverse(p->nodes[0], i, i2, val);

}

int CBinTree::KelementBST(int k) {
    if (m_root == nullptr || k == 0) return 0;
    int val = 0;
    int i = 0;
    Inverse(m_root, i, k, val);
    return val;

}

int main() {
    CBinTree t;

    t.Insert(20);
    t.Insert(8);
    t.Insert(22);
    t.Insert(4);
    t.Insert(12);
    t.Insert(10);
    t.Insert(14);

    cout << t.KelementBST(3) << endl;
    cout << t.KelementBST(2) << endl;
    cout << t.KelementBST(1) << endl;
    cout << t.KelementBST(6) << endl;
    cout << t.KelementBST(7) << endl;


}
