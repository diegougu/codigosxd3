#include <iostream>
using namespace std;
class XVector
{
public:
    XVector(int size_map, int size_vec);
    void expand(int newsize_map);
    void push_back(int x);
    void push_front(int x);
    int& operator[](int pos);

    int** map = nullptr;
    int** ini_map = nullptr;
    int** fin_map = nullptr;
    int* ini_vec = nullptr;
    int* fin_vec = nullptr;
    int size_map, size_vec;
    int elements = 0;
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    map = new int* [size_map];
    ini_map = map;
    fin_map = map;
}


int& XVector::operator[](int pos) {
    if (pos >= elements) {
        static int dummy;
        return dummy;
    }

    int map_pos = pos / size_vec;
    int vec_pos = pos % size_vec;
    int** m = map + map_pos;
    int* v = *m + vec_pos;

    return *v;
}


void XVector::expand(int newsize_map) {
    int** newmap = new int* [newsize_map];
    ini_map = newmap;
    fin_map = newmap + size_map - 1;
    for (int i = 0; i < size_map; i++) {
        newmap[i] = map[i];
    }
    
    int** temp = map;
    map = newmap;
    delete temp;
}


void XVector::push_front(int x) {
    if (ini_vec == nullptr && fin_vec == nullptr) {
        *ini_map = new int[size_vec];
        ini_vec = *ini_map;
        fin_vec = *ini_map;
        *ini_vec = x;
    }
    else if (fin_vec == *fin_map + size_vec - 1) {
        if (fin_map == map + size_map - 1) {
            expand(size_map * 2);
        }
        int temp = *fin_vec;
        int** i = fin_map;
        int* j = fin_vec;
        *(fin_vec + 1) = *fin_vec;
        while (i >= ini_map) {
            while (j >= *i) {
                if (j == *i && i != ini_map) {
                    *j = *(*(i - 1) + size_vec - 1);

                }
                else {
                    *j = *(j - 1);
                }
                j--;
            }
            i--;
            j = *i + size_vec - 1;
        }

        fin_map++;
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = temp;
        *ini_vec = x;

    }
    else {
        int** i = fin_map;
        int* j = fin_vec;
        *(fin_vec + 1) = *fin_vec;
        while (i >= ini_map) {
            while (j >= *i) {
                if (j == *i && i != ini_map) {
                    *j = *(*(i - 1) + size_vec - 1);

                }
                else {
                    *j = *(j - 1);
                }
                j--;
            }
            i--;
            j = *i + size_vec - 1;
        }

        *ini_vec = x;
        fin_vec++;

    }
    elements++;
}

void XVector::push_back(int x) {
    if (ini_vec == nullptr && fin_vec == nullptr) {
        *fin_map = new int[size_vec];
        ini_vec = *fin_map;
        fin_vec = *fin_map;
        *fin_vec = x;
    }
    else if (fin_vec == *fin_map + size_vec - 1) {
        if (fin_map == map + size_map - 1) {
            expand(size_map * 2);
        }
        fin_map++;
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = x;
    }
    else {
        fin_vec++;
        *fin_vec = x;
    }
    elements++;
}

void print(XVector* p)
{ //no modificar esta función
    for (int i = 0; i < p->size_vec; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    //no modificar esta función main
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}
