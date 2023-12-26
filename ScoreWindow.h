#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
const int Primary_Text_Offset = 650;

class ScoreWindow
{
public:
	ScoreWindow();
	void displayTime(bool , bool , int);
	void setScore(int);
	int getScore();
	sf::Text getText(int);
	int ScoreCalc(int , int  , int );
	void Start();
private:
	int score;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Text text_array[9];
	sf::Font font;
};



