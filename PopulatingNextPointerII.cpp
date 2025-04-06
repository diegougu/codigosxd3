#include <iostream>
#include <queue>
using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];
    CBinNode* next;

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        next = nullptr;
    }
};

class CBinTree {
private:
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void PopulatingNextPointerII();
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



void CBinTree::print() {
    if (m_root == nullptr) {
        return;
    }
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        CBinNode* p = rec.front();

        rec.pop();

        cout << "El next de " << p->value << "es : " << endl;


        if (p->next == nullptr) {
            cout << "NULL" << endl;
        }
        else {
            cout << p->next->value << endl;
        }

        if (p->nodes[0] != nullptr) {
            rec.push(p->nodes[0]);
        }
        if (p->nodes[1] != nullptr) {
            rec.push(p->nodes[1]);
        }

    }
    cout << "-------------------------------------------" << endl;

}

void CBinTree::PopulatingNextPointerII() {
    if (m_root == nullptr) {
        return;
    }

    queue<CBinNode*> rec;
    rec.push(m_root);

    while (!rec.empty()) {
        int n = rec.size();

        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();
            if (i != n - 1) {
                p->next = rec.front();
            }

            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }

        }
    }
}

int main() {
    CBinTree t, t2;

    t.Insert(10);
    t.Insert(5);
    t.Insert(20);
    t.Insert(3);
    t.Insert(8);
    t.Insert(30);

    t.PopulatingNextPointerII();
    t.print();

    t2.Insert(50);
    t2.Insert(40);
    t2.Insert(80);
    t2.Insert(45);
    t2.Insert(41);
    t2.Insert(47);
    t2.Insert(90);
    t2.Insert(85);
    t2.Insert(100);
    t2.Insert(83);
    t2.Insert(200);
    
    t2.PopulatingNextPointerII();
    t2.print();

}
