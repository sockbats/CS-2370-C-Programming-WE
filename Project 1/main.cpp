#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int outputRoster(vector<int> jerseys, vector<int> ratings) {
    cout << "ROSTER\n";
    for (int i = 0; i < jerseys.size(); i++) {
        cout << "Player " << i + 1 << " -- Jersey number: " << jerseys[i] << ", Rating: " << ratings[i] << "\n";
    }
    cout << "\n";
    return 0;
}

int getPlayerIndex(vector<int> jerseys) {
    int jersey = -1;
    while (!(jersey >= 0 && jersey <= 99)) {
        cout << "Enter a jersey number:\n";
        cin >> jersey;
    }
    auto index = find(jerseys.begin(), jerseys.end(), jersey);
    if (index != jerseys.end())
    {
        return index - jerseys.begin();
    }
    else {
        cout << "Player does not exist.\n";
        getPlayerIndex(jerseys);
    }
    return 0;
}

int main() {
    vector<int> jerseys;
    vector<int> ratings;
    for (int i = 1; i < 6; i++) {
        int jersey = -1, rating = -1;
        while (!(jersey >= 0 && jersey <= 99)) {
            cout << "Enter player " << i << "'s jersey number:\n";
            cin >> jersey;
        }
        jerseys.push_back(jersey);
        while (!(rating >= 1 && rating <= 9)) {
            cout << "Enter player " << i << "'s rating:\n";
            cin >> rating;
        }
        ratings.push_back(rating);
        cout << "\n";
    }
    outputRoster(jerseys, ratings);
    char menu = 's';
    while (menu != 'q') {
        cout << "MENU\na - Add player\nd - Remove player\nu - Update player rating\nr - Output players above a rating\n"
                "o - Output roster\nq - Quit\n\nChoose an option:\n";
        cin >> menu;
        int jersey = -1, rating = -1, j = 0, k = 0;
        switch(menu) {
            case 'a':
                while (!(jersey >= 0 && jersey <= 99)) {
                    cout << "Enter a new player's jersey number:\n";
                    cin >> jersey;
                }
                jerseys.push_back(jersey);
                while (!(rating >= 1 && rating <= 9)) {
                    cout << "Enter the player's rating:\n";
                    cin >> rating;
                }
                ratings.push_back(rating);
                cout << "\n";
                break;

            case 'd':
                jersey = getPlayerIndex(jerseys);
                jerseys.erase(jerseys.begin() + jersey);
                ratings.erase(ratings.begin() + jersey);
                break;

            case 'u':
                jersey = getPlayerIndex(jerseys);
                while (!(rating >= 1 && rating <= 9)) {
                    cout << "Enter a new rating for player:\n";
                    cin >> rating;
                }
                ratings[jersey] = rating;
                break;

            case 'r':
                while (!(rating >= 1 && rating <= 9)) {
                    cout << "Enter a rating:\n";
                    cin >> rating;
                }
                cout << "ABOVE " << rating << "\n";
                for (auto i: ratings) {
                    if (i > rating) {
                        cout << "Player " << j + 1 << " -- Jersey number: " << jerseys[j] << ", Rating: " << ratings[j] << "\n";
                    }
                    j++;
                }
                cout << "\n";
                break;

            case 'o':
                outputRoster(jerseys, ratings);
                break;

            default:
                break;
        }
    }

    return 0;
}
