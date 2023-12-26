#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
	string username;
	int game1Highscore;
	string password;
	int coins;

public:
	User(string uname, int id, int g1score, int g2score, string pwd, int c)
		: username(move(uname)), game1Highscore(g1score),
		password(move(pwd)), coins(c) {}

	void setUsername(const string& uname) {
		username = uname;
	}


	void setGame1Highscore(int score) {
		game1Highscore = score;
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


	int getGame1Highscore() const {
		return game1Highscore;
	}


	string getPassword() const {
		return password;
	}

	int getCoins() const {
		return coins;
	}




	friend istream& operator>>(istream& is, User& user) {
		is >> user.username;
		is >> user.game1Highscore;
		is >> user.password;
		is >> user.coins;
		return is;
	}
};
