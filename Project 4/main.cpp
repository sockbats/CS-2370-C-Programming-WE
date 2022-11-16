#include <iostream>
#include "Vector.h"

int main() {
    Vector v;
    int num = 5;
    for (int i = 0; i < num; i++) {
        v.push_back(i);
    }
    std::cout << "\n";
    Vector v2(v);
    Vector v3 = v;
    v.insert(1, 12);
    for (int i = 0; i < num; i++) {
        std::cout << v.at(i) << " " << v2.at(i) << " " << v3.at(i) << "\n";
    }

    return 0;
}
