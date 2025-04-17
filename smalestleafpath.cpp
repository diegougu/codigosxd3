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
    void Inorderleafs(CBinNode* p, vector<int>& path);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void smalestleaf(vector<int>& path);
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

void CBinTree::Inorderleafs(CBinNode* p, vector<int>& path) {
    if (!p) return;
    Inorderleafs(p->nodes[0], path);
    if (p != nullptr && p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        vector<int> posible_path;
        CBinNode** q = &m_root;
        for (; (*q)->value != p->value; q = &((*q)->nodes[(*q)->value < p->value])) {
            posible_path.push_back((*q)->value);
        }
        posible_path.push_back((*q)->value);

        if (path.empty()) {
            path = posible_path;
        }
        else if (posible_path.size() < path.size()) {
            path = posible_path;
        }
    }
    Inorderleafs(p->nodes[1], path);
}


void CBinTree::smalestleaf(vector<int>& path) {
    if (m_root == nullptr) {
        path.push_back(0);
    }
    Inorderleafs(m_root, path);
}

int main() {
    CBinTree t;
    CBinTree t2;
    CBinTree t3;
    t.Insert(50);
    t.Insert(20);
    t.Insert(60);
    t.Insert(10);
    t.Insert(30);

    t.print();

    vector<int> vec, vec2, vec3;
    t.smalestleaf(vec);
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;


    t2.Insert(50);
    t2.Insert(40);
    t2.Insert(60);
    t2.Insert(30);
    t2.Insert(45);
    t2.Insert(70);
    t2.Insert(80);
    t2.print();
    t2.smalestleaf(vec2);
    for (int i = 0; i < vec2.size(); i++) {
        cout << vec2[i] << " ";
    }
    cout << endl;
}
