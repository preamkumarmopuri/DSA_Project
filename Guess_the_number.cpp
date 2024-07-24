//GUESS THE
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    string name;
    int points;
    int hints[3]; // Store hints left
};

bool comparePlayers(const Player& a, const Player& b) {
    return a.points > b.points;
}

void showLeaderboard(const vector<Player>& leaderboard) {
    cout << "\n--- Leaderboard ---\n";
    for (const auto& player : leaderboard) {
        cout << player.name << ": " << player.points << " points\n";
    }
    cout << "-------------------\n";
}

void showPlayerStats(const Player& player) {
    cout << "\n--- Player Stats ---\n";
    cout << "Total points earned: " << player.points << "\n";
    cout << "Hints left: \n";
    cout << "  Easy mode: " << player.hints[0] << "\n";
    cout << "  Medium mode: " << player.hints[1] << "\n";
    cout << "  Hard mode: " << player.hints[2] << "\n";
    cout << "--------------------\n";
}

int getMaxHints(int mode) {
    switch (mode) {
        case 1: return 5; // Easy
        case 2: return 3; // Medium
        case 3: return 1; // Hard
        case 4: return 0; // Expert
        case 5: return 0; // Legendary
        default: return 0;
    }
}

int getMaxTries(int mode) {
    switch (mode) {
        case 1: return 8; // Easy
        case 2: return 7; // Medium
        case 3: return 5; // Hard
        case 4: return 3; // Expert
        case 5: return 1; // Legendary
        default: return 0;
    }
}

vector<int> generateNumbers(int mode, int range) {
    vector<int> numbers;
    if (mode == 5) { // Legendary
        int count = (range < 20) ? 3 : 5;
        while (numbers.size() < count) {
            int num = rand() % (range + 1);
            if (find(numbers.begin(), numbers.end(), num) == numbers.end()) {
                numbers.push_back(num);
            }
        }
    } else {
        numbers.push_back(rand() % (range + 1));
    }
    return numbers;
}

void playGame(Player& player) {
    int range, mode;
    cout << "Enter the range (starting from 0): ";
    cin >> range;
    cout << "Choose mode: 1. Easy 2. Medium 3. Hard 4. Expert 5. Legendary: ";
    cin >> mode;

    int maxTries = getMaxTries(mode);
    int maxHints = getMaxHints(mode);
    int hintsLeft = player.hints[mode - 1]; // Use stored hints for the selected mode
    vector<int> numbersToGuess = generateNumbers(mode, range);
    int triesLeft = maxTries;
    int guess;
    bool won = false;

    int triesBeforeHint = 2;

    while (triesLeft > 0) {
        if (mode == 5) { // Legendary mode
            cout << "Choose from these numbers: ";
            for (int num : numbersToGuess) {
                cout << num << " ";
            }
            cout << endl;
        }

        cout << "You have " << triesLeft << " tries left. Enter your guess: ";
        cin >> guess;

        if (find(numbersToGuess.begin(), numbersToGuess.end(), guess) != numbersToGuess.end()) {
            cout << "Correct! You win!\n";
            int pointsWon = 10;
            if (maxHints > 0 && hintsLeft != maxHints) {
                pointsWon -= 2;
            }
            player.points += pointsWon;
            cout << "You earned " << pointsWon << " points. Total points: " << player.points << "\n";
            won = true;
            break;
        } else {
            cout << "Incorrect guess.\n";
            triesLeft--;

            if (mode != 5 && triesBeforeHint == 0 && triesLeft > 0 && hintsLeft > 0) {
                char useHint;
                cout << "Do you want a hint? You have " << hintsLeft << " hints left (y/n): ";
                cin >> useHint;
                if (useHint == 'y' || useHint == 'Y') {
                    hintsLeft--;
                    player.hints[mode - 1] = hintsLeft; // Update stored hints for the selected mode
                    if (guess < numbersToGuess[0]) {
                        cout << "Hint: The number is higher than " << guess << "\n";
                    } else {
                        cout << "Hint: The number is lower than " << guess << "\n";
                    }
                }
                triesBeforeHint = 2;
            } else {
                triesBeforeHint--;
            }
        }
    }

    if (!won) {
        cout << "You lost! The correct numbers were ";
        for (int num : numbersToGuess) {
            cout << num << " ";
        }
        cout << ".\n";
    }
}

void buyHint(Player& player) {
    if (player.points >= 30) {
        player.points -= 30;
        cout << "You have successfully bought a hint! 30 points deducted.\n";
        cout << "Total points: " << player.points << "\n";
    } else {
        cout << "Insufficient points to buy a hint. You need 30 points but have only " << player.points << " points.\n";
    }
}
void displayWelcomeLogo() {
    cout << "******************" << endl;
    cout << "*                                                *" << endl;
    cout << "*       Welcome to GUESS THE NUMBER Game!        *" << endl;
    cout << "*                                                *" << endl;
    cout << "*                 Best of Luck!                  *" << endl;
    cout << "*                                                *" << endl;
    cout << "******************" << endl;
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Player> leaderboard;
    Player currentPlayer;
    int choice;
    bool playerWon = false;

    displayWelcomeLogo();

    cout << "Enter your name: ";
    cin >> currentPlayer.name;
    currentPlayer.points = 0;
    currentPlayer.hints[0] = getMaxHints(1); // Easy mode
    currentPlayer.hints[1] = getMaxHints(2); // Medium mode
    currentPlayer.hints[2] = getMaxHints(3); // Hard mode

    do {
        cout << "\n1. Play Game\n2. Show Leaderboard\n3. Buy Hint\n4. Show Player Stats\n5. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(currentPlayer);
                if (currentPlayer.points > 0) {
                    playerWon = true;
                }
                break;
            case 2:
                showLeaderboard(leaderboard);
                break;
            case 3:
                buyHint(currentPlayer);
                break;
            case 4:
                showPlayerStats(currentPlayer);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }

        if (choice == 1) {
            cout << "\nDo you want to continue? 1. Yes 2. Show Leaderboard 3. Show Player Stats 4. Buy Hint 5. Exit: ";
            cin >> choice;

            if (choice == 2) {
                showLeaderboard(leaderboard);
            } else if (choice == 3) {
                showPlayerStats(currentPlayer);
            } else if (choice == 4) {
                buyHint(currentPlayer);
            } else if (choice == 1) {
                bool found = false;
                for (auto& player : leaderboard) {
                    if (player.name == currentPlayer.name) {
                        player.points = currentPlayer.points;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    leaderboard.push_back(currentPlayer);
                }
                sort(leaderboard.begin(), leaderboard.end(), comparePlayers);
            }
        }
    } while (choice != 5);
    
    cout << "Thank you for playing!\n";
}

