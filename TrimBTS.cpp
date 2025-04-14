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
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    bool Insert(int x);
    bool Remove(int x,CBinNode*& newnode);
    void TrimBTS(int low, int high);
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

bool CBinTree::Remove(int x, CBinNode*& newnode) {
    CBinNode** p;
    if (!find(x, p)) {
        return false;
    }

    bool ver = ((*p)->nodes[0] && (*p)->nodes[1]);
    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        newnode = *p;
        p = q;
    }

    CBinNode* temp = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    if (!ver) {
        newnode = *p;
    }
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

void CBinTree::TrimBTS(int low, int high) {
    if (m_root == nullptr) {
        return;
    }
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        CBinNode* p = rec.front();
        if (p != nullptr && (p->value < low || p->value > high)) {
            bool dis = p->nodes[0] && p->nodes[1];
            CBinNode* newnode;
            Remove(p->value, newnode);
            rec.front() = newnode;
        }
        else {
            rec.pop();
            if (p != nullptr && p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p != nullptr && p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }
        }
    }
}

int main() {
    CBinTree t, t2, t3, t4, t5;
    t.Insert(1);
    t.Insert(0);
    t.Insert(2);
    t.print();
    t.TrimBTS(1, 2);
    t.print();

    t2.Insert(3);
    t2.Insert(0);
    t2.Insert(4);
    t2.Insert(2);
    t2.Insert(1);
    t2.print();
    t2.TrimBTS(1, 3);
    t2.print();

    t3.Insert(20);
    t3.Insert(10);
    t3.Insert(30);
    t3.Insert(3);
    t3.Insert(15);
    t3.Insert(40);
    t3.print();
    t3.TrimBTS(21, 50);
    t3.print();

    t4.Insert(10);
    t4.Insert(20);
    t4.Insert(30);
    t4.Insert(5);
    t4.Insert(3);
    t4.Insert(1);
    t4.print();
    t4.TrimBTS(1, 5);
    t4.print();
}
