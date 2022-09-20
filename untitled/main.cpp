#include <iostream>
#include <string>

void PrintMenu() {
    std::cout << "\nMENU\nc - Number of non-whitespace characters\nw - Number of words\nf - Find text\n"
                 "r - Replace all !'s\ns - Shorten spaces\nq - Quit\n\nChoose an option:\n";
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

int GetNumOfWords(const std::string text) {
    int output = 0;
    for (int i = 0; i < std::size(text); i++) {
        if ((text[i] == ' ' && text[i-1] != ' ')|| text[i] == '\n') {
            output++;
        }
    }
    return output;
}

void FindText(std::string toFind, std::string text) {

}

void ReplaceExclamation(std::string& text) {

}

void ShortenSpace(std::string& text) {

}

void ExecuteMenu(char action, std::string text) {
    std::string tex;
    switch (action) {
        case 'c':
            std::cout << "Number of non-whitespace characters: " << GetNumOfNonWSCharacters(text) << "\n";
            break;
        case 'w':
            std::cout << "Number of words: " << GetNumOfWords(text) << "\n";
            break;
        case 'f':
            FindText(tex, text);
            break;
        case 'r':
            ReplaceExclamation(text);
            break;
        case 's':
            ShortenSpace(text);
            break;
        default:
            break;
    }
}

int main() {
    std::cout << "Enter a sample text:\n";
    std::string input;
    std::getline(std::cin, input);
    std::cout << "\nYou entered: " << input << "\n";
    char action = '\0';
    while (action != 'q') {
        PrintMenu();
        std::cin >> action;
        action = char(tolower(action));
        if (action == 'c' || action == 'w' || action == 'f' || action == 'r' || action == 's' || action == 'q')
            ExecuteMenu(action, input);
    }
    return 0;
}
