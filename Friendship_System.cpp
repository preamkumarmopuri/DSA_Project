//FRIENDSHIP SYSTEM
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class User {
public:
    string firstName;
    string lastName;
    int age;
    string gender;

    User() {};

    User(string firstName, string lastName, int age, string gender) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
        this->gender = gender;
    }
};

// MAP user-name to USER
map<string, User> mapUserName;

// MAPPING ONE FRIEND TO ANOTHER FRIEND
map<string, set<string>> Friends;

void addUser(string userName, User user) {
    if (mapUserName.find(userName) == mapUserName.end()) {
        mapUserName[userName] = user;
    } else {
        cout << "UserName Already Taken\n";
    }
}

void makeThemFriend(string userName1, string userName2) {
    if (mapUserName.find(userName1) != mapUserName.end() && mapUserName.find(userName2) != mapUserName.end()) {
        Friends[userName1].insert(userName2);
        Friends[userName2].insert(userName1);
    } else {
        cout << "One or both usernames do not exist\n";
    }
}

void displayAllUser() {
    for (auto i : mapUserName) {
        cout << "UserName: " << i.first << " " << i.second.firstName << " " << i.second.lastName << "\n";
    }
}

void displayAllFriendships() {
    for (auto i : Friends) {
        cout << i.first << " -> ";
        set<string> friends = i.second;
        for (auto j : friends) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

int main() {
    string userName, firstName, lastName, gender;
    int age;

    // Taking input for the first user
    cout << "Enter the first user's details:\n";
    cout << "Enter UserName: ";
    cin >> userName;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender: ";
    cin >> gender;

    User user1(firstName, lastName, age, gender);
    addUser(userName, user1);

    // Taking input for the second user
    cout << "\nEnter the second user's details:\n";
    cout << "Enter UserName: ";
    cin >> userName;
    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Gender: ";
    cin >> gender;

    User user2(firstName, lastName, age, gender);
    addUser(userName, user2);

    // Making the two users friends
    string userName1, userName2;
    cout << "\nEnter the usernames of the two users you want to make friends:\n";
    cout << "Enter the first UserName: ";
    cin >> userName1;
    cout << "Enter the second UserName: ";
    cin >> userName2;
    makeThemFriend(userName1, userName2);

    // Display all friendships
    displayAllFriendships();
}
