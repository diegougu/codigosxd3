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


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}


void Inorder2(CBinNode** p, CBinNode** q) {
    if (!*p && !*q || (*p && !*q)) {
        return;
    }

    if (*p && *q) {
        (*p)->value += (*q)->value;
    }
    else if (!*p && *q) {
        *p = *q;
        return;
    }

    Inorder2(&((*p)->nodes[0]), &((*q)->nodes[0]));

    Inorder2(&((*p)->nodes[1]), &((*q)->nodes[1]));

}



CBinTree* mergue(CBinTree t1, CBinTree t2) {
    if (t1.m_root == nullptr && t2.m_root == nullptr) {
        return nullptr;
    }
    else if (t1.m_root != nullptr && t2.m_root == nullptr) {
        return &t1;
    }
    else if (t1.m_root == nullptr && t2.m_root != nullptr) {
        return &t2;
    }

    Inorder2(&t1.m_root, &t2.m_root);
    return &t1;
}


int main() {
    CBinTree t1, t2;

    t1.Insert(80);
    t1.Insert(30);
    t1.Insert(100);
    t1.Insert(20);
    t1.print();
    t2.Insert(100);
    t2.Insert(50);
    t2.Insert(200);
    t2.Insert(300);
    t2.Insert(60);
    t2.Insert(55);
    t2.Insert(70);
    t2.print();
    CBinTree* x = mergue(t1, t2);
    x->print();

}
