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
    void caseTreeNull(CBinNode* p, vector<int>& vals);
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


void findvals(CBinNode* p, CBinNode* q, vector<int>& vals) {
    queue<CBinNode*> rec;
    queue<CBinNode*> rec2;

    if (p != nullptr) {
        rec.push(p);
    }

    if (q != nullptr) {
        rec2.push(q);
    }

    vals.push_back(INT_MAX);
    while (!rec.empty() || !rec2.empty()) {
        CBinNode* x = !rec.empty() ? rec.front() : nullptr;
        CBinNode* y = !rec2.empty() ? rec2.front() : nullptr;

        if (!rec.empty()) {
            rec.pop();
        }

        if (!rec2.empty()) {
            rec2.pop();
        }

        if (x != nullptr) {
            int pos = 0;
            while (pos < vals.size()) {
                if (x->value < vals[pos]) {
                    break;
                }
                pos++;
            }

            int temp = vals[pos];
            int temp2 = vals[pos];
            vals[pos] = x->value;
            pos++;
            for (int i = pos; i < vals.size(); i++) {
                temp = vals[i];
                vals[i] = temp2;
                temp2 = temp;
            }
            
            vals.push_back(temp);

        }

        if (y != nullptr) {
            int pos = 0;
            while (pos < vals.size()) {
                if (y->value < vals[pos]) {
                    break;
                }
                pos++;
            }

            int temp = vals[pos];
            int temp2 = vals[pos];
            vals[pos] = y->value;
            pos++;
            for (int i = pos; i < vals.size(); i++) {
                temp = vals[i];
                vals[i] = temp2;
                temp2 = temp;
            }

            vals.push_back(temp);
        }

        if (x != nullptr && x->nodes[0] != nullptr) {
            rec.push(x->nodes[0]);
        }

        if (x != nullptr && x->nodes[1] != nullptr) {
            rec.push(x->nodes[1]);
        }

        if (y != nullptr && y->nodes[0] != nullptr) {
            rec2.push(y->nodes[0]);
        }

        if (y != nullptr && y->nodes[1] != nullptr) {
            rec2.push(y->nodes[1]);
        }

    }

    vals.pop_back();
}

void getAllElements(CBinTree x1, CBinTree x2, vector<int>& vals) {
    if (x1.m_root == nullptr && x2.m_root == nullptr) {
        vals.push_back(-1);
    }

    findvals(x1.m_root, x2.m_root, vals);
}

int main() {
    CBinTree t1, t2;
    t1.Insert(50);
    t1.Insert(10);
    t1.Insert(20);
    t1.Insert(60);
    t1.Insert(80);
    t1.Insert(55);
    t1.Insert(56);
    t1.Insert(100);
    t1.Insert(90);

    t2.Insert(100);
    t2.Insert(20);
    t2.Insert(10);
    t2.Insert(500);
    t2.Insert(50);
    t2.Insert(55);

    vector<int> vals;
    getAllElements(t1, t2, vals);
    for (int i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;
}
