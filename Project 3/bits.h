#ifndef PROJECT_3_BITS_H
#define PROJECT_3_BITS_H
#include <cassert>
#include <bitset>
#include <ostream>
#include <cmath>
#include <vector>

class Bits {
    using IType = unsigned long long; // We only have to change the integer type here, if desired
    enum {NBITS = sizeof(IType)*8};
    IType bits = 0;
public:
    Bits() = default;
    explicit Bits(IType n) {
        bits = n;
    }

    static int size() {
        return NBITS;
    }

    bool at(int pos) const {  // Returns (tests) the bit at bit-position pos
        assert(0 <= pos && pos < NBITS);
        return bits & (IType(1) << pos);
    }

    void set(int pos) {
        this->at(pos);
        auto bin = std::bitset<NBITS>(this->bits);
        if (!bin[pos]) {
            this->bits += (IType)pow(2, pos);
        }
    };        // Sets the bit at position pos

    void set() {
        this->bits = -1;
    };               // Sets all bits

    void reset(int pos) {
        this->at(pos);
        auto bin = std::bitset<NBITS>(this->bits);
        if (bin[pos]) {
            this->bits -= (IType)pow(2, pos);
        }
    };      // Resets (makes zero) the bit at position pos

    void reset() {
        this->bits = 0;
    };             // Resets all bits

    void assign(int pos, bool val) {
        this->at(pos);
        auto bin = std::bitset<NBITS>(this->bits);
        if (bin[pos] && val == 0) {
            this->bits -= (IType)pow(2, pos);
        }
        else {
            this->bits += (IType)pow(2, pos);
        }
    }; // Sets or resets the bit at position pos depending on val

    void assign(IType n) {
        this->bits = n;
    };     // Replaces the underlying integer with n

    void toggle(int pos) {
        this->at(pos);
        auto bin = std::bitset<NBITS>(this->bits);
        if (bin[pos] == 0) {
            this->bits += (IType)pow(2, pos);
        }
        else {
            this->bits -= (IType)pow(2, pos);
        }
    };     // Flips the bit at position pos

    void toggle() {
        IType temp = this->bits;
        this->bits = -1 - temp;
    };            // Flips all bits

    void shift(int n) {
        assert(n >= -NBITS && n <= NBITS);
        auto bin = std::bitset<NBITS>(this->bits);
        std::string shifted;
        if (n < 0) {
            for (int i = 0; i > n; i--) { // shift left
                bin = bin << 1;
            }
        }
        else {
            for (int i = 0; i < n; i++) { // shift right
                bin = bin >> 1;
            }
        }
        this->bits = std::bitset<NBITS>(bin).to_ullong();
    };        // If n > 0, shifts bits right n places; if n < 0, shifts left

    void rotate(int n) {
        assert(n >= -NBITS && n <= NBITS);
        n = -n;
        auto bin = std::bitset<NBITS>(this->bits).to_string();
        std::string shifted;
        if (n < 0) {
            shifted = bin.substr(NBITS + n, -1) + bin.substr(0, NBITS + n);
        }
        else {
            shifted = bin.substr(n, -1) + bin.substr(0, n);
        }
        this->bits = std::bitset<NBITS>(shifted).to_ullong();
    };       // If n > 0, rotates right n places; if n < 0, rotates left

    int ones() const {
        int ones = 0;
        auto bin = std::bitset<NBITS>(this->bits);
        for (auto i: bin.to_string()) {
            if (i == '1') {
                ones++;
            }
        }
        return ones;
    };         // Returns how many bits are set in the underlying integer

    int zeroes() const {      // Returns how many bits are reset in the underlying integer
        return NBITS - ones();
    }

    IType to_int() const {
        return bits;
    }

    bool operator==(const Bits& b2) const {
        return this->bits == b2.bits;
    }

    bool operator!=(const Bits& b2) const {
        return this->bits != b2.bits;
    }

    bool operator==(IType b2) const {
        return this->bits == b2;
    }

    bool operator!=(IType b2) const {
        return this->bits != b2;
    }

    friend bool operator==(const Bits& b1, const Bits& b2) {
        return b1.bits == b2.bits;
    }

    friend bool operator!=(const Bits& b1, const Bits& b2) {
        return b1.bits != b2.bits;
    }

    friend std::ostream& operator<<(std::ostream& os, const Bits& b) {
        return os << std::bitset<NBITS>(b.bits);    // Be sure to #include <bitset>
    }
};



#endif //PROJECT_3_BITS_H
