#include <iostream>
#include <string>
using namespace std;

int main() {
    string i = "hi";
//    cin >> i;
    getline(cin, i);
    cout << i;
    return 0;
}
