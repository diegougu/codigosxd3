#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

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
    void contorno(sf::RenderWindow& window);
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

    if (n->color == 1 || (n != nullptr && n->nodes[0] == nullptr && n->nodes[1] == nullptr)) {
        circle.setFillColor(sf::Color::Red);
    }
    else {
        circle.setFillColor(sf::Color::Black);
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

void CBinTree::contorno(sf::RenderWindow& window) {
    if (m_root == nullptr) {
        return;
    }

    CBinNode* p = m_root;
    CBinNode* q = m_root;

    while (p || q) {
        if (p != nullptr) {
            p->color = 1;
            if (p->nodes[0] != nullptr) {
                p = p->nodes[0];
            }
            else {
                p = p->nodes[1];
            }
        }

        if (q || nullptr) {
            q->color = 1;
            if (q->nodes[1] != nullptr) {
                q = q->nodes[1];
            }
            else {
                q = q->nodes[0];
            }

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
        t.contorno(window);
        window.display();
    }

    return 0;
}
