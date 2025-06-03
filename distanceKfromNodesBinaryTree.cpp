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
    void distanceK(vector<int>& vals, int k, CBinNode* n);
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

bool findVC(vector<CBinNode*> record, CBinNode* p) {
    for (int i = 0; i < record.size(); i++) {
        if (record[i] == p) {
            return true;
        }
    }
    return false;
}

void CBinTree::distanceK(vector<int>& vals, int k, CBinNode* n) {
    if (n == nullptr || m_root == nullptr) {
        return;
    }
    vector<CBinNode*> record;
    queue<pair<CBinNode*, int>> rec;
    int pos = 0;
    rec.push(make_pair(n, pos));
    record.push_back(n);

    while (!rec.empty()) {
        CBinNode* p = rec.front().first;
        int pi = rec.front().second;
        rec.pop();

        if (pi == k) {
            vals.push_back(p->value);
        }

        CBinNode* father = m_root;
        while (father != p && father->nodes[0] != p && father->nodes[1] != p) {
            father = father->nodes[father->value < p->value];
        }
        if (father != nullptr && !findVC(record, father)) {
            record.push_back(father);
            rec.push(make_pair(father, pi + 1));
        }

        if (p->nodes[0] != nullptr && !findVC(record, p->nodes[0])) {
            record.push_back(p->nodes[0]);
            rec.push(make_pair(p->nodes[0], pi + 1));
        }

        if (p->nodes[1] != nullptr && !findVC(record, p->nodes[1])) {
            record.push_back(p->nodes[1]);
            rec.push(make_pair(p->nodes[1], pi + 1));
        }
    }
    

}

int main() {
    CBinTree t;
    t.Insert(30);
    t.Insert(20);
    t.Insert(60);
    t.Insert(10);
    t.Insert(25);
    t.Insert(23);
    t.Insert(29);
    t.Insert(70);
    t.Insert(55);
    t.print();

    vector<int> vals;
    t.distanceK(vals, 2, t.m_root->nodes[0]);
    for (int i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;
}
