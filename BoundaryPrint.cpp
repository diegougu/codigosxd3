#include <iostream>
#include <vector>
#include <stack>

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
    void leafs(CBinNode* p, vector<int>& vals);
public:
    void Boundary();
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

void CBinTree::leafs(CBinNode* p, vector<int>& vals) {
    if (!p) return;
    leafs(p->nodes[0], vals);
    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        for (int i = 0; i < vals.size(); i++) {
            if (vals[i] == p->value) {
                return;
            }
        }
        vals.push_back(p->value);
    }
    leafs(p->nodes[1], vals);

}

bool findV(vector<int> vals, int n) {
    for (int i = 0; i < vals.size(); i++) {
        if (vals[i] == n) {
            return true;
        }
    }
    return false;
}


void CBinTree::Boundary() {
    vector<int> vals;
    CBinNode* p = m_root;
    while (p) {
        vals.push_back(p->value);
        if (p->nodes[0] == nullptr && p->nodes[1] != nullptr) {
            p = p->nodes[1];
        }
        else {
            p = p->nodes[0];
        }
    }
    leafs(m_root, vals);
    stack<int> rightrec;
    p = m_root;
    while (p) {
        if (!findV(vals, p->value)) {
            rightrec.push(p->value);
        }        

        if (p->nodes[1] == nullptr && p->nodes[0] != nullptr) {
            p = p->nodes[0];
        }
        else {
            p = p->nodes[1];
        }
    }    
    

    while (!rightrec.empty()) {
        vals.push_back(rightrec.top());
        rightrec.pop();
    }


    for (int i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;

}

int main() {
    CBinTree t;

    t.Insert(50);
    t.Insert(40);
    t.Insert(70);
    t.Insert(30);
    t.Insert(43);
    t.Insert(20);
    t.Insert(23);
    t.Insert(25);
    t.Insert(41);
    t.Insert(45);
    t.Insert(80);
    t.Insert(90);
    t.Insert(85);
    t.Insert(100);

    t.Boundary();

}
