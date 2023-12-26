#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
    string username;
    int ID;
    int game1Highscore;
    int game2Highscore;
    string password;
    int coins;

public:
    User(string uname, int id, int g1score, int g2score, string pwd, int c)
        : username(move(uname)), ID(id), game1Highscore(g1score), game2Highscore(g2score),
        password(move(pwd)), coins(c) {}

    void setUsername(const string& uname) {
        username = uname;
    }

    void setID(int id) {
        ID = id;
    }

    void setGame1Highscore(int score) {
        game1Highscore = score;
    }

    void setGame2Highscore(int score) {
        game2Highscore = score;
    }

    void setPassword(const string& pwd) {
        password = pwd;
    }

    void setCoins(int c) {
        coins = c;
    }

    string getUsername() const {
        return username;
    }

    int getID() const {
        return ID;
    }

    int getGame1Highscore() const {
        return game1Highscore;
    }

    int getGame2Highscore() const {
        return game2Highscore;
    }

    string getPassword() const {
        return password;
    }

    int getCoins() const {
        return coins;
    }

    void storeToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << username << "\n";
            file << ID << "\n";
            file << game1Highscore << "\n";
            file << game2Highscore << "\n";
            file << password << "\n";
            file << coins << "\n";
            file.close();
            cout << "User data stored successfully.\n";
        }
        else {
            cerr << "Unable to open the file.\n";
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            file >> username;
            file >> ID;
            file >> game1Highscore;
            file >> game2Highscore;
            file >> password;
            file >> coins;
            file.close();
            cout << "User data loaded successfully.\n";
        }

        else {
            cerr << "Unable to open the file.\n";
        }
    }
    friend istream& operator>>(istream& is, User& user) {
        is >> user.username;
        is >> user.ID;
        is >> user.game1Highscore;
        is >> user.game2Highscore;
        is >> user.password;
        is >> user.coins;
        return is;
    }
};
