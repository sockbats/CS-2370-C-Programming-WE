#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>

std::map<char, int> letterFrequency(const std::string& word) {
    std::map<char, int> out;
    for (auto i: word) {
        if (out.count(i)) {
            out.at(i)++;
        }
        else {
            out.insert({i, 1});
        }
    }
    return out;
}

bool isSubset(const std::map<char, int>& child, const std::map<char, int>& parent) {
    for (auto i: child) {
        if (!parent.count(i.first))
            return false;
        if (child.at(i.first) > parent.at(i.first))
            return false;
    }
    return true;
}


int main(int argc, char *argv[]) {
    auto const NWORDS = 81483;
    std::default_random_engine dre(time(nullptr));
    std::uniform_int_distribution<int> di(0,NWORDS);
    int n = di(dre);

    std::ifstream wordFile("words.txt");
    std::vector<std::string> words;
    if (wordFile) {
        std::string word;
        while (wordFile >> word) {
            words.push_back(word);
        }
        wordFile.close();
    }
    else {
        return -1;
    }
    std::string word;
    if (argc == 2) {
        word = argv[1];
    }
    if (word.length() < 3) {
        word = words.at(n);
    }
    auto wordFreq = letterFrequency(word);
    std::map<unsigned long long, std::vector<std::string>> subwords;
    for (const auto& i: words) {
        auto currWordFreq = letterFrequency(i);
        if (isSubset(currWordFreq, wordFreq)) {
            if (!subwords.count(i.length())) {
                subwords.insert({i.length(), std::vector<std::string>()});
            }
            subwords[i.length()].push_back(i);
        }
    }
    subwords.erase(2);
    std::cout << "The word is " << word << ": \n\n";
    for (const auto& i: subwords) {
        auto lyst = i.second;
        std::sort(lyst.begin(), lyst.end());
        for (const auto& j: lyst) {
            std::cout << j << "\n";
        }
    }
    return 0;
}
