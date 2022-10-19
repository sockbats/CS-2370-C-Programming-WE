#include "bits.h"

void Bits::set(int pos) {
    this->at(pos);
}

void Bits::set() {
    this->bits = -1;
}

void Bits::reset(int pos) {
    this->at(pos);
}

void Bits::reset() {
    this->bits = 0;
}

void Bits::assign(int pos, bool val) {

}

void Bits::assign(Bits::IType n) {

}

void Bits::toggle(int pos) {

}

void Bits::toggle() {

}

void Bits::shift(int n) {

}

void Bits::rotate(int n) {

}

int Bits::ones() const {
    return 0;
}
