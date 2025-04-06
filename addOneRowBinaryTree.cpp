#include <iostream>
#include <queue>
#include <deque>

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
    bool Remove(int x);
    void print();
    void addOneRow(int x, int depth);
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

void CBinTree::addOneRow(int x, int depth) {
    if (m_root == nullptr || depth <= 1) {
        return;
    }

    queue<CBinNode*> rec;
    deque<CBinNode*> dads;
    rec.push(m_root);
    int i = 1;
    while (!rec.empty()) {
        int n = rec.size();

        if (i != depth) {
            dads.clear();
        }

        for (int t = 0; t < n && !rec.empty(); t++) {
            CBinNode* p = rec.front();
            rec.pop();
            dads.push_back(p);

            if (i == depth) {
                for (int j = 0; j < n; j++) {
                    CBinNode* newnode = new CBinNode(x);
                    for (int k = 0; k < dads.size(); k++) {
                        if (dads[k]->nodes[0] == p) {
                            newnode->nodes[0] = dads[k]->nodes[0];
                            dads[k]->nodes[0] = newnode;
                        }

                        if (dads[k]->nodes[1] == p) {
                            newnode->nodes[1] = dads[k]->nodes[1];
                            dads[k]->nodes[1] = newnode;
                        }
                    }

                    if (!rec.empty()) {
                        p = rec.front();
                        rec.pop();
                    }
                }
            }
            else {
                if (p->nodes[0] != nullptr) {
                    rec.push(p->nodes[0]);
                }

                if (p->nodes[1] != nullptr) {
                    rec.push(p->nodes[1]);
                }
            }
        }
        i++;
    }

}

int main() {
    CBinTree t, t2, t3;
    t.Insert(4);
    t.Insert(2);
    t.Insert(6);
    t.Insert(1);
    t.Insert(3);
    t.Insert(5);

    t.print();
    t.addOneRow(99, 2);
    t.print();

    t2.Insert(4);
    t2.Insert(2);
    t2.Insert(1);
    t2.Insert(3);
    t2.print();
    t2.addOneRow(100, 3);
    t2.print();

    t3.Insert(50);
    t3.Insert(30);
    t3.Insert(60);
    t3.Insert(25);
    t3.Insert(40);
    t3.Insert(20);
    t3.Insert(27);
    t3.Insert(55);
    t3.Insert(70);
    t3.Insert(51);
    t3.Insert(56);
    t3.print();
    t3.addOneRow(200, 4);
    t3.print();

}
