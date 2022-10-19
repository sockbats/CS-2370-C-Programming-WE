#include <iostream>
#include "bits.h"

int main() {
    Bits bit;
    std::cout << bit << " " << bit.to_int() << "\n";
    bit.set(15);
    std::cout << bit << " " << bit.to_int() << "\n";
    bit.reset(12);
    std::cout << bit << " " << bit.to_int() << "\n";

    return 0;
}