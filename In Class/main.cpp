#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFS("myfile.txt");
    if (!outFS) {
        cout << "Could not open file myoutfile.txt." << endl;
        return 1;
    }
    outFS << "This is a test data.";
    outFS.close();

    ifstream inFS("myfile.txt");
    string str;
    cout << "Reading from file..." << endl;
    inFS >> str;
    cout << str << endl;
    return 0;
}