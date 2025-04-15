#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
    void RemoveLeafsGivenAvalue(int x);
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


void CBinTree::RemoveLeafsGivenAvalue(int x) {
    if (m_root == nullptr) {
        return;
    }

    queue<CBinNode**> rec;
    rec.push(&m_root);
    bool determ = true;
    while (!rec.empty()) {
        CBinNode** p = rec.front();

        rec.pop();

        if ((*p)->nodes[0] != nullptr) {
            rec.push(&((*p)->nodes[0]));
        }

        if ((*p)->nodes[1] != nullptr) {
            rec.push(&((*p)->nodes[1]));
        }

        if ((*p)->value == x && (*p)->nodes[0] == nullptr && (*p)->nodes[1] == nullptr) {
            CBinNode* temp = *p;
            *p = nullptr;
            delete temp;
            determ = false;
        }
        
        
        if (determ == false && rec.empty()) {
            rec.push(&m_root);
            determ = true;
        }

    }
}

int main() {
    CBinTree t, t2;
    t.m_root = new CBinNode(1);
    t.m_root->nodes[0] = new CBinNode(2);
    t.m_root->nodes[1] = new CBinNode(3);
    t.m_root->nodes[0]->nodes[0] = new CBinNode(4);
    t.m_root->nodes[0]->nodes[1] = new CBinNode(4);
    t.m_root->nodes[0]->nodes[1]->nodes[0] = new CBinNode(1);
    t.m_root->nodes[0]->nodes[1]->nodes[1] = new CBinNode(4);
    t.m_root->nodes[1]->nodes[1] = new CBinNode(4);
    t.m_root->nodes[1]->nodes[1]->nodes[1] = new CBinNode(4);
    t.m_root->nodes[1]->nodes[1]->nodes[1]->nodes[1] = new CBinNode(4);

    t.print();
    t.RemoveLeafsGivenAvalue(4);
    t.print();

    t2.m_root = new CBinNode(1);
    t2.m_root->nodes[0] = new CBinNode(2);
    t2.m_root->nodes[1] = new CBinNode(3);
    t2.m_root->nodes[0]->nodes[0] = new CBinNode(4);
    t2.m_root->nodes[0]->nodes[1] = new CBinNode(4);
    t2.m_root->nodes[0]->nodes[1]->nodes[0] = new CBinNode(1);
    t2.m_root->nodes[0]->nodes[1]->nodes[1] = new CBinNode(4);
    t2.m_root->nodes[1]->nodes[1] = new CBinNode(4);
    t2.m_root->nodes[1]->nodes[1]->nodes[1] = new CBinNode(4);
    t2.m_root->nodes[1]->nodes[1]->nodes[1]->nodes[1] = new CBinNode(10);
    t2.print();
    t2.RemoveLeafsGivenAvalue(4);
    t2.print();
}
