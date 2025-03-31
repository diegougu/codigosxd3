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
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    CBinNode* m_root = nullptr;
    void FindLargestValueRow();
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


void CBinTree::FindLargestValueRow() {
    vector<int> vals;

    queue<CBinNode*> rec;

    rec.push(m_root);

    while (!rec.empty()) {
        int n = rec.size();
        int largest = INT_MIN;
        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();

            if (p->value > largest) {
                largest = p->value;
            }

            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }
            
        }

        vals.push_back(largest);

    }

    for (int i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;
}

int main() {
    CBinTree t;
    CBinTree t2;

    t.m_root = new CBinNode(10);
    t.m_root->nodes[0] = new CBinNode(1);
    t.m_root->nodes[1] = new CBinNode(20);
    t.m_root->nodes[0]->nodes[0] = new CBinNode(50);
    t.m_root->nodes[0]->nodes[1] = new CBinNode(22);
    t.m_root->nodes[1]->nodes[0] = new CBinNode(60);

    t2.m_root = new CBinNode(35);
    t2.m_root->nodes[0] = new CBinNode(20);
    t2.m_root->nodes[1] = new CBinNode(15);
    t2.m_root->nodes[0]->nodes[0] = new CBinNode(15);
    t2.m_root->nodes[0]->nodes[1] = new CBinNode(5);
    t2.m_root->nodes[1]->nodes[0] = new CBinNode(31);
    t2.m_root->nodes[1]->nodes[1] = new CBinNode(30);

    t.print();
    t2.print();

    t.FindLargestValueRow();
    t2.FindLargestValueRow();

}
