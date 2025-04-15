#include <iostream>
#include <vector>
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
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
    void pairMaxMin(int x, pair<int, int>& vals);
public:
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void closestNodes(vector<int>& queries, vector<pair<int, int>>& finded);
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


void CBinTree::pairMaxMin(int x, pair<int, int>& vals) {
    int min = INT_MIN;
    int max = INT_MAX;

    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        CBinNode* p = rec.front();

        rec.pop();
        
        if (p->value <= x && p->value >= min) {
            min = p->value;
        }


        if (p->value >= x && p->value <= max) {
            max = p->value;
        }

        if (p->nodes[0] != nullptr) {
            rec.push(p->nodes[0]);
        }

        if (p->nodes[1] != nullptr) {
            rec.push(p->nodes[1]);
        }
        
    }

    min = min == INT_MIN ? -1 : min;
    max = max == INT_MAX ? -1 : max;

    vals.first = min;
    vals.second = max;
}

void CBinTree::closestNodes(vector<int>& queries, vector<pair<int, int>>& finded) {
    if (m_root == nullptr) {
        return;
    }

    for (int i = 0; i < queries.size(); i++) {
        pair<int, int> vals;
        pairMaxMin(queries[i], vals);
        finded.push_back(vals);
    }



}

int main() {
    CBinTree t;
    t.Insert(6);
    t.Insert(2);
    t.Insert(13);
    t.Insert(1);
    t.Insert(4);
    t.Insert(9);
    t.Insert(15);
    t.Insert(14);

    t.print();
    vector<int> queries;
    queries.push_back(2);
    queries.push_back(5);
    queries.push_back(16);
    vector<pair<int, int>> finded;

    t.closestNodes(queries, finded);
    for (int i = 0; i < finded.size(); i++) {
        cout << finded[i].first << " " << finded[i].second << endl;
    }



}
