#include <iostream>
#include <bitset>
using namespace std;

int main() {
    unsigned int num, right, left;
    cout << "Enter the integer that holds the bits: ";
    cin >> num;
    cout << "\nEnter the rightmost bit position: ";
    cin >> right;
    cout << "\nEnter the leftmost bit position: ";
    cin >> left;
    bitset<32> numBin = num;
    bitset<32> endBin(numBin.to_string().substr(31 - left, left - right + 1));
    cout << "\nExtracting bits " << right << " through " << left <<" from " << num << " = " << numBin << ":\nResult = " << endBin.to_ulong() << " = " << endBin;
    return 0;
}
