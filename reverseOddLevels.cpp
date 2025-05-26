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
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void reverseOddLevels();
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
        cout << endl;
        return;
    }
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();
            cout << p->value << " ";
            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }
        }
        cout << endl;
    }
}


void CBinTree::reverseOddLevels() {
    if (m_root == nullptr) return;
    queue<CBinNode**> rec;
    rec.push(&m_root);
    int level = 0;
    while (!rec.empty()) {
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            CBinNode** p = rec.front();
            rec.pop();

            if (level % 2 != 0) {
                if (i != n - 1) {
                    swap(((*p))->value, ((*rec.front())->value));
                }
            }

            if ((*p)->nodes[0] != nullptr) {
                rec.push(&((*p)->nodes[0]));
            }

            if ((*p)->nodes[1] != nullptr) {
                rec.push(&((*p)->nodes[1]));
            }

        }
        level++;
    }
}

int main() {
    CBinTree t;
    t.Insert(60);
    t.Insert(50);
    t.Insert(80);
    t.Insert(40);
    t.Insert(58);
    t.Insert(70);
    t.Insert(100);
    t.Insert(30);
    t.Insert(45);
    t.Insert(55);
    t.Insert(59);
    t.Insert(65);
    t.Insert(75);
    t.Insert(200);
    t.Insert(90);
    t.print();
    t.reverseOddLevels();
    t.print();
}
