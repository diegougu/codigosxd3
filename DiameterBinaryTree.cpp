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
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
    void CalculateValues(CBinNode* p, int depth, vector<int>& vals);
public:
    int Diameter();
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

void CBinTree::CalculateValues(CBinNode* p, int depth, vector<int>& vals) {
    if (!p) return;

    CalculateValues(p->nodes[0], depth + 1, vals);

    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        if (vals.size() == 1) {
            if (depth > vals[0]) {
                vals[0] = depth;
            }
        }
        else {
            vals.push_back(depth);
        }
    }
    CalculateValues(p->nodes[1], depth + 1, vals);

}

int CBinTree::Diameter() {
    if (m_root == nullptr || (m_root->nodes[0] == nullptr && m_root->nodes[1] == nullptr)) {
        return 0;
    }
    
    int depth = 1;
    int depth2 = 1;
    vector<int> vals;
    vector<int> vals2;

    CalculateValues(m_root->nodes[0], depth, vals);
    CalculateValues(m_root->nodes[1], depth2, vals2);

    int d = !vals.empty() ? vals[0] : 0;
    int d2 = !vals2.empty() ? vals2[0] : 0;
    
    return d + d2;

}

int main() {
    CBinTree t, t2, t3;
    t.Insert(10);
    t.Insert(5);
    t.Insert(20);
    t.Insert(4);
    t.Insert(9);
    t.Insert(7);
    t.Insert(30);
    t.Insert(40);

    t2.Insert(50);
    t2.Insert(70);
    t2.Insert(30);
    t2.Insert(15);
    t2.Insert(40);

    t3.Insert(10);
    t3.Insert(1);

    cout << t.Diameter() << endl;
    cout << t2.Diameter() << endl;
    cout << t3.Diameter() << endl;

}
