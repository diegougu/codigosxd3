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
    void PopulatingNextPointer();
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

void CBinTree::PopulatingNextPointer() {
    if (m_root == nullptr) {
        return;
    }

    queue<CBinNode*> rec;
    rec.push(m_root);
    int c = 1;
    int posNULL = 1;
    while (!rec.empty()) {
        CBinNode* p = rec.front();
        rec.pop();
        if (c == posNULL) {
            p->next = nullptr;
            posNULL = posNULL * 2 + 1;
        }
        else {
            p->next = rec.front();
        }
        
        if (p->nodes[0] != nullptr) {
            rec.push(p->nodes[0]);
        }
        if (p->nodes[1] != nullptr) {
            rec.push(p->nodes[1]);
        }


        c++;
    }
}

int main() {
    CBinTree t;
    t.Insert(100);
    t.Insert(80);
    t.Insert(120);
    t.Insert(60);
    t.Insert(90);
    t.Insert(110);
    t.Insert(150);
    t.Insert(50);
    t.Insert(70);
    t.Insert(85);
    t.Insert(95);
    t.Insert(105);
    t.Insert(115);
    t.Insert(140);
    t.Insert(200);


    t.print();
    t.PopulatingNextPointer();
    t.print();
}
