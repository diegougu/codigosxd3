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
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    bool isCousins(int x, int y);
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


bool CBinTree::isCousins(int x, int y) {
    if (m_root == nullptr || x == y) {
        return false;
    }
    else if (m_root->nodes[0]->value == x || m_root->nodes[1]->value == y || m_root->value == x || m_root->value == y) {
        return false;
    }

    queue<CBinNode*> rec;
    rec.push(m_root);
    bool findx = false;
    bool findy = false;
    while (!rec.empty()) {
        int n = rec.size();

        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();

            if (p->value == x) {
                findx = true;
            }

            if (p->value == y) {
                findy = true;
            }

            if (p->nodes[0] != nullptr && p->nodes[1] != nullptr && (p->nodes[0]->value == x || p->nodes[1]->value == x) && (p->nodes[0]->value == y || p->nodes[1]->value == y)) {
                return false;
            }

            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }

        }

        if ((findy == true && findx == false) || (findx == true && findy == false)) {
            return false;
        }

    }

    return true;
}

int main() {
    CBinTree t;
    CBinTree t2;

    t.Insert(50);
    t.Insert(40);
    t.Insert(60);
    t.Insert(30);
    t.Insert(45);
    t.Insert(70);
    t.Insert(20);
    t.Insert(35);
    t.Insert(43);
    t.Insert(49);
    t.Insert(65);
    t.Insert(80);

    t.print();
    cout << t.isCousins(20, 35) << endl;
    cout << t.isCousins(40, 60) << endl;
    cout << t.isCousins(30, 70) << endl;
    cout << t.isCousins(43, 45) << endl;
    cout << t.isCousins(43, 30) << endl;
    cout << t.isCousins(65, 20) << endl;
    cout << t.isCousins(20, 49) << endl;
    cout << t.isCousins(80, 40) << endl;


}
