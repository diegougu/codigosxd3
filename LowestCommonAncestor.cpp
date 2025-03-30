#include <iostream>
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
    void LowestCommonAncestor(int x, int y);
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

void CBinTree::LowestCommonAncestor(int x, int y) {
    if (m_root == nullptr) {
        return;
    }

    CBinNode** p = &m_root;
    CBinNode** q = &m_root;

    int lowest = 0;
    while ((*p)->value != x || (*q)->value != y) {
        if ((*p)->value == (*q)->value) {
            lowest = (*p)->value;
        }
        
        if ((*p)->value != x) {
            p = &((*p)->nodes[(*p)->value < x]);
        }

        if ((*q)->value != y) {
            q = &((*q)->nodes[(*q)->value < y]);
        }


    }
    cout << lowest << " es el ancestro comun entre los nodos: " << x << " " << y << endl;
}

int main() {
    CBinTree t;

    t.Insert(100);
    t.Insert(200);
    t.Insert(80);
    t.Insert(300);
    t.Insert(90);
    t.Insert(70);
    t.Insert(60);
    t.Insert(68);
    t.Insert(250);
    t.Insert(400);

    t.print();

    t.LowestCommonAncestor(80, 200);
    t.LowestCommonAncestor(80, 90);
    t.LowestCommonAncestor(80, 68);
    t.LowestCommonAncestor(60, 68);
    t.LowestCommonAncestor(400, 250);


}
