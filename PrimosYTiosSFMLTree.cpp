#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct CBinNode
{
    int value;
    int color;
    CBinNode* nodes[2];
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0; color = 0;
    }
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    void primosytios(int n, sf::RenderWindow& window);
private:
    bool Find(int x, CBinNode**& p);
    CBinNode* m_root;
    bool m_b;
    void color(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY);
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
}

void CBinTree::color(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY) {
    if (n == nullptr) return;

    sf::CircleShape circle(30);

    circle.setPosition(x, y);

    if (n->color == 1) {
        circle.setFillColor(sf::Color::Green);
    }
    else if (n->color == 2) {
        circle.setFillColor(sf::Color::Blue);
    }
    else {
        circle.setFillColor(sf::Color::Red);
    }

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Error al cargar la fuente\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(n->value));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 10, y + 5);

    window.draw(circle);
    window.draw(text);

    if (n->nodes[0] != nullptr) {
        sf::Vertex lineaIzquierda[] = {
            sf::Vertex(sf::Vector2f(x + 30, y + 30)),
            sf::Vertex(sf::Vector2f(x - offsetX + 30, y + offsetY + 30))
        };
        window.draw(lineaIzquierda, 2, sf::Lines);
        color(n->nodes[0], window, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (n->nodes[1] != nullptr) {
        sf::Vertex lineaDerecha[] = {
            sf::Vertex(sf::Vector2f(x + 30, y + 30)),
            sf::Vertex(sf::Vector2f(x + offsetX + 30, y + offsetY + 30))
        };
        window.draw(lineaDerecha, 2, sf::Lines);
        color(n->nodes[1], window, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}

void CBinTree::primosytios(int x, sf::RenderWindow& window) {
    if (m_root == nullptr || m_root->value == x || (m_root->nodes[0] != nullptr && m_root->nodes[0]->value == x) || (m_root->nodes[1] != nullptr && m_root->nodes[1]->value == x)) {
        color(m_root, window, 400, 50, 200, 100);
    }
    vector<CBinNode*> tios;
    queue<CBinNode*> rec;
    rec.push(m_root);
    bool finded = false;
    while (!rec.empty() && finded == false) {
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();

            if ((p->nodes[0] != nullptr && p->nodes[0]->value == x) || (p->nodes[1] != nullptr && p->nodes[1]->value == x)) {
                finded = true;
            }
            else {
                tios.push_back(p);
            }

            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }
            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }
        }
        if (finded == false) {
            tios.clear();
        }
    }
    for (int i = 0; i < tios.size(); i++) {
        tios[i]->color = 1;
        if (tios[i]->nodes[0] != nullptr) {
            tios[i]->nodes[0]->color = 2;
        }

        if (tios[i]->nodes[1] != nullptr) {
            tios[i]->nodes[1]->color = 2;
        }
    }
    color(m_root, window, 400, 50, 200, 100);
}


bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}

int main()
{
    CBinTree t;
    t.Insert(100);
    t.Insert(30);
    t.Insert(200);
    t.Insert(10);
    t.Insert(40);
    t.Insert(24);
    t.Insert(20);
    t.Insert(300);
    t.Insert(250);
    t.Insert(270);
    t.Insert(70);
    t.Insert(80);
    t.Insert(150);
    t.Insert(170);
    t.Insert(120);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualización del Árbol Binario");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        t.primosytios(120, window);
        window.display();
    }

    return 0;
}
