#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void PrintMenu() {
    std::cout << "MENU\nc - Number of non-whitespace characters\nw - Number of words\nf - Find text\n"
                 "r - Replace all !'s\ns - Shorten spaces\nq - Quit";
}

int GetNumOfNonWSCharacters(const std::string& text) {
    int output = 0;
    for (auto i: text) {
        if (i != ' ' && i != '\n') {
            output++;
        }
    }
    return output;
}

int GetNumOfWords(const std::string& text) {
    int output = 1;
    for (int i = 0; i < text.length(); i++) {
        if ((text[i] == ' ' && text[i-1] != ' ')|| text[i] == '\n') {
            output++;
        }
    }
    return output;
}

int FindText(std::string toFind, std::string text) {
    int output = 0, counter = 1;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == toFind[0]) {
            for (int j = 1; j < toFind.length(); j++) {
                if (text[j + i] == toFind[j]) {
                    if (++counter == toFind.length()) {
                        output += 1;
                        counter = 1;
                    }
                }
                else {
                    counter = 1;
                    break;
                }
            }
        }
    }
    return output;
}

void ReplaceExclamation(std::string& text) {
    for (char& i : text) {
        if (i == '!') {
            i = '.';
        }
    }
}

void ShortenSpace(std::string& text) {
    std::vector<char> vec;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ' && text[i-1] == ' ') {

        }
        else {
            vec.push_back(text[i]);
        }
    }
    std::string s(vec.begin(), vec.end());
    text = s;
}

void ExecuteMenu(char action, std::string text) {
    std::string tex;
    switch (action) {
        case 'c':
            std::cout << "Number of non-whitespace characters: " << GetNumOfNonWSCharacters(text) << "\n\n";
            break;
        case 'w':
            std::cout << "Number of words: " << GetNumOfWords(text) << "\n\n";
            break;
        case 'f':
            std::cout << "Enter a word or phrase to be found:\n";
            std::cin.ignore();
            std::getline(std::cin, tex);
            std::cout << "\"" << tex << "\" instances: " << FindText(tex, text) << "\n\n";
            break;
        case 'r':
            ReplaceExclamation(text);
            std::cout << "Edited text: " << text << "\n\n";
            break;
        case 's':
            ShortenSpace(text);
            std::cout << "Edited text: " << text << "\n\n";
            break;
        default:
            break;
    }
}

int main() {
    std::cout << "Enter a sample text:\n";
    std::string input;
    std::getline(std::cin, input);
    std::cout << "\nYou entered: " << input << "\n\n";
    char action = '\0';
    while (action != 'q') {
        PrintMenu();
        std::cout << "\n\nChoose an option:\n";
        std::cin >> action;
        action = char(tolower(action));
        if (action == 'c' || action == 'w' || action == 'f' || action == 'r' || action == 's' || action == 'q')
            ExecuteMenu(action, input);
    }
    return 0;
}
