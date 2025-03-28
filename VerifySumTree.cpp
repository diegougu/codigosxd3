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
    bool VerifySumTree();
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

bool CBinTree::VerifySumTree() {
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        CBinNode* p = rec.front();
        rec.pop();

        int i = p->nodes[0] ? p->nodes[0]->value : 0;
        int d = p->nodes[1] ? p->nodes[1]->value : 0;

        if ((i != 0 && d != 0) &&  i + d != p->value) {
            return false;
        }


        if (p->nodes[0] != nullptr) {
            rec.push(p->nodes[0]);
        }

        if (p->nodes[1] != nullptr) {
            rec.push(p->nodes[1]);
        }

    }
    return true;
}

int main() {
    CBinTree t;
    CBinTree t2;

    t.m_root = new CBinNode(10);
    t.m_root->nodes[0] = new CBinNode(8);
    t.m_root->nodes[1] = new CBinNode(2);
    t.m_root->nodes[0]->nodes[0] = new CBinNode(5);
    t.m_root->nodes[0]->nodes[1] = new CBinNode(2);
    t.m_root->nodes[1]->nodes[0] = new CBinNode(2);

    t2.m_root = new CBinNode(35);
    t2.m_root->nodes[0] = new CBinNode(20);
    t2.m_root->nodes[1] = new CBinNode(15);
    t2.m_root->nodes[0]->nodes[0] = new CBinNode(15);
    t2.m_root->nodes[0]->nodes[1] = new CBinNode(5);
    t2.m_root->nodes[1]->nodes[0] = new CBinNode(10);
    t2.m_root->nodes[1]->nodes[1] = new CBinNode(5);

    t.print();
    t2.print();
    cout << t.VerifySumTree() << endl;
    cout << t2.VerifySumTree() << endl;

}
