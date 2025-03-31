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
    int Burn(CBinNode* x);
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



bool findV(vector<int> arr, int val) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == val) {
            return true;
        }
    }
    return false;
}

int CBinTree::Burn(CBinNode* x) {
    if (m_root == nullptr) {
        return -1;
    }
    
    int time = -1;
    
    queue<CBinNode*> rec;
    vector<int> mark;
    rec.push(x);
    while (!rec.empty()) {
        int n = rec.size();


        for (int i = 0; i < n; i++) {
        
            CBinNode* p = rec.front();
            rec.pop();
            mark.push_back(p->value);
            CBinNode* father = m_root;

            while (father != p && (father->nodes[0] != p && father->nodes[1] != p)) {
                father = father->nodes[father->value < p->value];
            }

            if (father != p && !findV(mark, father->value)) {
                rec.push(father);
            }

            if (p->nodes[0] != nullptr && !findV(mark, p->nodes[0]->value)) {
                rec.push(p->nodes[0]);
            }
            
            if (p->nodes[1] != nullptr && !findV(mark, p->nodes[1]->value)) {
                rec.push(p->nodes[1]);
            }
            
        }

        time++;
    }

    return time;


}

int main() {
    CBinTree t;
    CBinTree t2;

    t.Insert(50);
    t.Insert(40);
    t.Insert(70);
    t.Insert(30);
    t.Insert(45);
    t.Insert(43);
    t.Insert(49);
    t.Insert(80);
    t.Insert(90);
    t.Insert(100);

    t2.Insert(50);
    t2.Insert(30);
    t2.Insert(70);
    t2.Insert(20);
    t2.Insert(40);
    t2.Insert(10);
    t2.Insert(35);
    t2.Insert(80);

    cout << t.Burn(t.m_root->nodes[0]->nodes[1]->nodes[1]) << endl;
    cout << t2.Burn(t2.m_root->nodes[0]->nodes[1]->nodes[0]) << endl;

}
