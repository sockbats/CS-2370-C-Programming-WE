#include <iostream>
#include "bits.h"

int main() {
    Bits bit;
    std::cout << bit << " " << bit.to_int() << "\n";
    bit.set(15);
    bit.set(14);
    bit.set(11);
    bit.set(27);
    bit.set(22);
    bit.set(53);
    bit.set(47);
    bit.set(62);
    bit.set(55);
    bit.set(44);
    bit.set(0);
    std::cout << bit << " " << bit.to_int() << "\n";
    bit.rotate(10);
    std::cout << bit << " " << bit.to_int() << "\n";
    bit.rotate(-10);
    std::cout << bit << " " << bit.to_int() << "\n";
    return 0;
}
