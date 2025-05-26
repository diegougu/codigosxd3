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
    void leafinorder(CBinNode* p, int level, int& sum, int& max);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    int deepestLeavesSum();
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

void CBinTree::leafinorder(CBinNode* p, int level, int& sum, int& max) {
    if (!p) return;
    leafinorder(p->nodes[0], level + 1, sum, max);
    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        if (level > max) {
            sum = 0;
            sum += p->value;
            level = max;
        }
        else if (level == max) {
            sum += p->value;
        }
    }
    leafinorder(p->nodes[1], level + 1, sum, max);

}

int CBinTree::deepestLeavesSum() {
    int sum = 0;
    if (m_root == nullptr) {
        return sum;
    }
    int max = 0;
    leafinorder(m_root, 0, sum, max);
    return sum;
}

int main() {
    CBinTree t;
    t.Insert(42);
    t.Insert(20);
    t.Insert(60);
    t.Insert(10);
    t.Insert(30);
    t.Insert(35);
    t.Insert(70);
    t.Insert(80);
    t.Insert(90);
    t.print();
    cout << t.deepestLeavesSum() << endl;
}
