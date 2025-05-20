#include <iostream>

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
    void PostOrder(CBinNode* p);
    void Reverse(CBinNode* p);
    void PreOrder(CBinNode* p);
public:
    CBinNode* m_root = nullptr;
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


void CBinTree::PostOrder(CBinNode* p) {
    if (!p) return;
    PostOrder(p->nodes[0]);
    PostOrder(p->nodes[1]);
    cout << p->value << " ";
}

void CBinTree::PreOrder(CBinNode* p) {
    if (!p) return;
    cout << p->value << " ";
    PreOrder(p->nodes[0]);
    PreOrder(p->nodes[1]);
}

void CBinTree::Reverse(CBinNode* p) {
    if (!p) return;
    Reverse(p->nodes[1]);
    cout << p->value << " ";
    Reverse(p->nodes[0]);
}

void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
    PostOrder(m_root);
    cout << endl;
    PreOrder(m_root);
    cout << endl;
    Reverse(m_root);
    cout << endl;
}




int main() {
    CBinTree t;
    CBinTree t2;

    t.Insert(50);
    t.Insert(40);
    t.Insert(70);
    t.Insert(30);
    t.Insert(45);
    t.Insert(43);
    t.Insert(49);
    t.Insert(80);
    t.Insert(90);
    t.Insert(100);

    t.print();



}
