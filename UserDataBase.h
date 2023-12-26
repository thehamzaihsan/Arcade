#pragma once

#include <vector>
#include <algorithm>
#include "User.h"

class UserDatabase {
private:
    vector<User> users;

public:
    void addUser(const User& user) {
        users.push_back(user);
    }

    User* findUser(const string& username) {
        for (User& user : users) {
            if (user.getUsername() == username) {
                return &user;
            }
        }
        return nullptr;  // Return null if user not found
    }

    int findUserIndex(const string& username) {
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getUsername() == username) {
                return i;
            }
        }
        return -1;  // Return -1 if user not found
    }
    void replaceUser(const string& username, const User& newUser) {
        int index = findUserIndex(username);
        if (index != -1) {
            users[index] = newUser;
        }
    }

    User getUserByIndex(int index) {
        if (index >= 0 && index < users.size()) {
            return users[index];
        }
    }


    void storeAllUsersToFile(const string& filename) {
        ofstream file(filename, ios::app);  // Open the file in append mode
        if (file.is_open()) {
            for (const User& user : users) {
                file << user.getUsername() << "\n";
                file << user.getID() << "\n";
                file << user.getGame1Highscore() << "\n";
                file << user.getGame2Highscore() << "\n";
                file << user.getPassword() << "\n";
                file << user.getCoins() << "\n";
            }
            file.close();
            cout << "All user data stored successfully.\n";
        }
        else {
            cerr << "Unable to open the file.\n";
        }
    }

    void loadAllUsersFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            User tempUser("", 0, 0, 0, "", 0);
            while (file >> tempUser) {
                users.push_back(tempUser);
                cout << "User data loaded successfully.\n";
            }
            file.close();
        }
        else {
            cerr << "Unable to open the file.\n";
        }
    }

    void subtractCoin(const string& username) {
        int index = findUserIndex(username);
        if (index != -1) {
            users[index].setCoins(users[index].getCoins() - 1);
            cout << users[index].getCoins();
            storeAllUsersToFile("file.txt");
        }
        // Handle error if user not found
    }


};


