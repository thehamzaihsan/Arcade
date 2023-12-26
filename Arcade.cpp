#include <TGUI/TGUI.hpp>
#include <TGUI/Signal.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <cstdlib>
#include "Game.h"
#include "UserDataBase.h"
#include "User.h"

using namespace tgui;
using namespace std;

class Application {
public:
	//void ArcadeMenu(string);

	Application() : window(sf::VideoMode(900, 640), "Arcade Simulator"), gui(window) {
		MainPage();
		userdatabase.loadAllUsersFromFile("file.txt");
		currentUserScore = 0;
		Game1 = false;
	}

	void run() {
		Game Minesweeper(&window, &event);
		sf::RectangleShape rec;
		rec.setSize(sf::Vector2f(20.0f, 20.0f));

		gamestart = true;
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}


				gui.handleEvent(event);

			}

			cout << "GameStart: " << gamestart << endl;
			cout << "Game1: " << Game1 << endl;

			if (Game1 == true)
			{
				//cout << "update";
				if (gamestart == true)
				{
					//cout << "start";
					Minesweeper.Start();
					gamestart = false;
				}
				Minesweeper.Update();
				currentUserScore = Minesweeper.getscore();

			}


			window.clear(sf::Color::Black);
			gui.draw();
			if (Game1 == true)
			{
				Minesweeper.Render();
			}
			window.display();
		}
	}

	void onButtonClicked() {
		std::cout << "Button clicked!" << std::endl;
	}

	void HighScore(string username) {
		int ID = userdatabase.findUserIndex(username);
		User user = userdatabase.getUserByIndex(ID);
		gui.loadWidgetsFromFile("HighScore.txt");
		auto Backf = gui.get<tgui::Button>("Back");
		Backf->onClick([this, username] { ArcadeMenu(username); });
		vector<User> users_temp = userdatabase.getAllUsers();

		auto ListView = gui.get<tgui::ListView>("ListView");
		for (int i = 0; i < users_temp.size(); i++) {
			ListView->addItem({ users_temp[i].getUsername() , to_string(users_temp[i].getGame1Highscore()) });
		}

		auto coins = gui.get<tgui::Label>("coins");
		coins->setText(to_string(user.getCoins()));

		auto usernameLabel = gui.get<tgui::Label>("Username");
		usernameLabel->setText(username);
	}


	void ArcadeMenu(string username) {
		int ID = userdatabase.findUserIndex(username);
		User user = userdatabase.getUserByIndex(ID);

		gui.loadWidgetsFromFile("ArcadeMenu.txt");
		auto Back = gui.get<tgui::Button>("Back");
		Back->onClick([this, username, ID] {

			if (Game1 == true)
			{
				gamestart = true;
				setGame(false);
				ArcadeMenu(username);

				userdatabase.addHigscore(username, currentUserScore);


			}
			else {
				LoginPage();
			}
			});

		auto coins = gui.get<tgui::Label>("coins");

		auto HighScoreButton = gui.get<tgui::Button>("HighScores");
		HighScoreButton->onClick([this, username] {
			if (Game1 == false)
			{
				HighScore(username);

			}

			});
		auto GamePlay1 = gui.get<tgui::Button>("MineSweeper");
		GamePlay1->onClick([this, username, coins, ID] {

			if (Game1 == false)
			{

				setGame(true);
				userdatabase.subtractCoin(username);
				User usern = userdatabase.getUserByIndex(ID);
				coins->setText(to_string(usern.getCoins()));

			}

			});
		auto BounceL1 = gui.get<tgui::Button>("Bounce1");

		BounceL1->onClick([this, username, coins, ID] {
			if (Game1 == false)
			{

				User usern = userdatabase.getUserByIndex(ID);
				if (usern.getCoins() > 0)
				{
					userdatabase.subtractCoin(username);
					coins->setText(to_string(usern.getCoins()));
					system("D:\\Projects\\Arcade\\x64\\Debug\\Level1\\BounceClassic.exe");
				}
			}

			});
		auto BounceL2 = gui.get<tgui::Button>("Bounce2");

		BounceL2->onClick([this, username, coins, ID] {

			if (Game1 == false)
			{
				User usern = userdatabase.getUserByIndex(ID);
				if (usern.getCoins() > 0)
				{
					userdatabase.subtractCoin(username);
					coins->setText(to_string(usern.getCoins()));
					system("D:\\Projects\\Arcade\\x64\\Debug\\Level2\\BounceClassic.exe");
				}

			}

			});




		auto usernameLabel = gui.get<tgui::Label>("Username");
		usernameLabel->setText(username);
		coins->setText(to_string(user.getCoins()));



	}

	void LoginPage() {
		gui.loadWidgetsFromFile("Login.txt");

		auto usernameBox = gui.get<tgui::EditBox>("Username");
		auto passwordBox = gui.get<tgui::EditBox>("Password");
		auto Warning1 = gui.get<tgui::Label>("Warning1");



		auto LoginButton = gui.get<tgui::Button>("Login");
		LoginButton->onClick([this, usernameBox, passwordBox, Warning1] {

			std::string username = usernameBox->getText().toStdString();
			std::string password = passwordBox->getText().toStdString();



			if (userdatabase.findUser(username) != nullptr)
			{
				int ID = userdatabase.findUserIndex(username);
				User user = userdatabase.getUserByIndex(ID);
				if (user.getPassword() != password)
				{
					Warning1->setVisible(true);
				}
				else {
					Warning1->setVisible(false);
					ArcadeMenu(username);

				}
			}
			else {
				Warning1->setVisible(true);

			}

			});

		auto Back = gui.get<tgui::Button>("Back");
		Back->onClick([&] { MainPage(); });
	}



	void SignUpPage() {
		gui.loadWidgetsFromFile("SignUp.txt");

		auto usernameBox = gui.get<tgui::EditBox>("Username");
		auto passwordBox = gui.get<tgui::EditBox>("password");
		auto ConfpasswordBox = gui.get<tgui::EditBox>("ConfirmPassword");

		auto Warning1 = gui.get<tgui::Label>("Warning1");
		auto Warning2 = gui.get<tgui::Label>("Warning2");

		auto SignUpButton = gui.get<tgui::Button>("SignUp");
		SignUpButton->onClick([this, usernameBox, passwordBox, ConfpasswordBox, Warning1, Warning2] {

			std::string username = usernameBox->getText().toStdString();
			std::string password = passwordBox->getText().toStdString();
			std::string ConfPassword = ConfpasswordBox->getText().toStdString();

			cout << username << endl;
			cout << password << endl;
			cout << ConfPassword << endl;

			if (userdatabase.findUser(username) == nullptr)
			{
				if (ConfPassword == password)
				{
					User newUser(username, 00, 00, 00, password, 10);
					userdatabase.addUser(newUser);
					userdatabase.storeAllUsersToFile("file.txt");
					LoginPage();
				}
				else {
					Warning2->setVisible(true);
				}

			}
			else {
				Warning1->setVisible(true);
			}
			});

		auto Back = gui.get<tgui::Button>("Back");
		Back->onClick([this] { MainPage(); });
	}


	void MainPage() {
		gui.loadWidgetsFromFile("Main.txt");
		auto LoginButton = gui.get<tgui::Button>("LoginButton");
		LoginButton->onClick([&] { LoginPage(); });
		auto SignUpButton = gui.get<tgui::Button>("SignUp");
		SignUpButton->onClick([&] { SignUpPage(); });
		auto Exit = gui.get<tgui::Button>("Exit");
		Exit->onClick([&] {
			window.close();

			});
	}

	void setGame(bool b) {
		Game1 = b;
	}

private:
	sf::RenderWindow window;
	sf::Event event;
	tgui::Gui gui;
	bool Game1;
	UserDatabase userdatabase;
	int currentUserScore;
	bool  gamestart;
};

int main() {
	Application app;
	app.run();
	return 0;

}
