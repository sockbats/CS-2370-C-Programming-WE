#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int GetWordFrequency(vector<string> wordsList, string currWord) {
    int counter = 0;
    transform(currWord.begin(), currWord.end(), currWord.begin(), ::tolower);
    for (auto i: wordsList) {
        transform(i.begin(), i.end(), i.begin(), ::tolower);
        if (i == currWord) {
            counter++;
        }
    }
    return counter;
}

int main() {
    string input, temp;
    vector<string> wordList;
    int counter = 0;
    getline(cin, input);
    for (auto i: input) {
        if (i != ' ' && i != '\0') {
            temp.push_back(i);
        }
        else if (wordList.empty()) {
            wordList.push_back(temp);
            temp = "";
        }
        else if (counter < stoi(wordList.at(0))) {
            wordList.push_back(temp);
            temp = "";
            counter++;
        }
    }
    if (wordList.empty() || counter < stoi(wordList.at(0))) {
        wordList.push_back(temp);
        temp = "";
        counter++;
    }
    wordList.erase(wordList.begin());

    for (auto i: wordList) {
        cout << i << " " << GetWordFrequency(wordList, i) << "\n";
    }
    return 0;
}
