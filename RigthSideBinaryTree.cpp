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
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    void RightSideView();
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



void CBinTree::RightSideView() {
    if (m_root == nullptr) {
        return;
    }

    vector<int> rightvals;
    queue<CBinNode*> rec;


    rec.push(m_root);
    while (!rec.empty()) {
        
        int n = rec.size();
        bool pos = true;

        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();

            rec.pop();

            if (pos == true) {
                rightvals.push_back(p->value);
                pos = false;
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }

            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }
        }

    }
    
    for (int i = 0; i < rightvals.size(); i++) {
        cout << rightvals[i] << " ";
    }
    cout << endl;

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

    t3.Insert(20);
    t3.Insert(15);
    t3.Insert(50);
    t3.Insert(40);
    t3.Insert(13);
    t3.Insert(10);
    t3.Insert(5);

    t.RightSideView();
    t2.RightSideView();
    t3.RightSideView();

}
