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
    void InorderSums(CBinNode* p, vector<vector<int>>& path);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void Sumpath();
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

void CBinTree::InorderSums(CBinNode* p, vector<vector<int>>& path) {
    if (!p) return;
    InorderSums(p->nodes[0], path);

    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        vector<int> posiblePath;
        int count = 0;
        for (CBinNode** q = &m_root; *q ; q = &((*q)->nodes[(*q)->value < p->value])) {
            count += (*q)->value;
            posiblePath.push_back((*q)->value);
        }
        path.push_back(posiblePath);


    }

    InorderSums(p->nodes[1], path);

}

void CBinTree::Sumpath() {
    vector<vector<int>> path;
    InorderSums(m_root, path);
    for (int i = 0; i < path.size(); i++) {
        int val = 0;
        for (int j = 0; j < path[i].size(); j++) {
            cout << path[i][j] << "+";
            val += path[i][j];
        }
        cout << " = " << val << endl;
    } 
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
    t.Sumpath();


}
