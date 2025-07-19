#include "gamesfml.h"
#include "game.h"



int gamemenu() {
	sf::RenderWindow window(sf::VideoMode(600, 600), "game menu");

	sf::Font font;
	if (!font.loadFromFile("tuffy.ttf")) {
		std::cerr << "could not load font ! \n";
		return 0;
	}

	sf::Text title("tic tac toc", font,60);
	title.setFillColor(sf::Color::Yellow);
	title.setPosition(150,20);

	sf::Text option[3];
	std::string msg[] = { "1. Player vs Player","2. Player vs AI" ,"3. exit the game" };
	for (int i = 0; i < 3; i++)
	{
		option[i].setFont(font);
		option[i].setString(msg[i]);
		option[i].setCharacterSize(40);
		option[i].setFillColor(sf::Color::Green);
		option[i].setPosition(sf::Vector2f(150, (i * 100) + 150));
	}
	int mode = 0;

	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2f mouspos(sf::Mouse::getPosition(window));
		for (int i = 0; i < 3; i++) {
			if (option[i].getGlobalBounds().contains(mouspos)) {
				option[i].setFillColor(sf::Color::Magenta);
			}
			else
			{
				option[i].setFillColor(sf::Color::Green);
			}
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				for (int i = 0; i < 3; i++)
				{
					if (option[i].getGlobalBounds().contains(mouspos)) {
						window.close();
						return i + 1;
					}
				}
			}
		}

		window.clear(sf::Color(30,30,30));

		window.draw(title);

		for (auto& menu : option) {
			window.draw(menu);
		}
		window.display();
	}
	return 0;
}



// grid and game function --->
void gamesf(int mode) {

	// Create SFML window
	sf::RenderWindow window(sf::VideoMode(600, 600), "Tic Tac Toe - SFML");
	// Load font
	sf::Font font;
	if (!font.loadFromFile("tuffy.ttf")) {
		// Make sure this font file exists in your project folder
		std::cerr << "Could not load font!\n";
		return;
	}

	//variabls --->
	bool gameend = false;
	char currentPlayer = 'X';
	int turnCount = 0;

	std::string statusMessage = "Player X's turn";

	sf::Text statustext;
	statustext.setFont(font);
	statustext.setCharacterSize(24);
	statustext.setFillColor(sf::Color::Red);
	statustext.setPosition(sf::Vector2f(10.f, 10.f));



	// make gride 
	sf::RectangleShape grid[4];
	//vertical line
	for (int i = 0; i < 2; i++)
	{
		grid[i].setSize(sf::Vector2f(5.f, 600.f));
		grid[i].setPosition((i + 1) * 200.f, 0.f);
		grid[i].setFillColor(sf::Color::Magenta);

	}
	//horizontal lines
	for (int i = 2; i < 4; i++)
	{
		grid[i].setSize(sf::Vector2f(600.f, 5.f));
		grid[i].setPosition(0.f, (i - 1) * 200.f);
		grid[i].setFillColor(sf::Color::Magenta);

	}

	//reset board 
	resetbord();

	while (window.isOpen()) {
		// event-->
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { window.close(); }

			if (!gameend) {
				if (currentPlayer == 'X') {
					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
					{
						int x = event.mouseButton.x / 200;
						int y = event.mouseButton.y / 200;
						int choice = y * 3 + x + 1;
						if (choice >= 1 && choice <= 9) {
							if (placemarker(choice, 'X'))
							{
								turnCount++;
								if (winner('X')) {
									statusMessage = "player 'X' wins ! ";
									gameend = true;
								}
								else if (turnCount == 9) {
									statusMessage = "it's a draw!";
									gameend = true;
								}
								else {
									currentPlayer = 'O';
									statusMessage = (mode == 2) ? "computer's turn" : "player 'O' 's turns";
								}
							}
						}
					}
				}
				else {
					// AI truns --->
					if (mode == 2)
					{
						int choice = modeai();
						sf::sleep(sf::milliseconds(500));

						if (placemarker(choice, 'O')) {

							turnCount++;
							if (winner('O')) {
								statusMessage = (mode == 2) ? "Computer wins!" : "Player O wins!";
								gameend = true;
							}
							else if (turnCount == 9) {
								statusMessage = "it's a draw!";
								gameend = true;
							}
							else {
								currentPlayer = 'X';
								statusMessage = "player 'X' 's turns";
							}
						}

					}
					// human's turn --->
					else {
						if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
						{
							int x = event.mouseButton.x / 200;
							int y = event.mouseButton.y / 200;
							int choice = y * 3 + x + 1;
							if (choice >= 1 && choice <= 9) {
								if (placemarker(choice, 'O'))
								{
									turnCount++;
									if (winner('O')) {
										statusMessage = (mode == 2) ? "Computer wins!" : "Player O wins!";
										gameend = true;
									}
									else if (turnCount == 9) {
										statusMessage = "it's a draw!";
										gameend = true;
									}
									else {
										currentPlayer = 'X';
										statusMessage = "player 'X' 's turns";
									}

								}
							}
						}
					}

				}

			}
			if (gameend && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				resetbord();
				gameend = false;
				currentPlayer = 'X';
				turnCount = 0;
				statusMessage = "Player X's turn";
			}


		}

		window.clear(sf::Color::Black);


		// draw grids
		for (auto& line : grid) {
			window.draw(line);
		}

		//drow symble --->
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
			{
				char val = space[i][j];
				if (val == 'O' || val == 'X') {
					sf::Text marker;
					marker.setFont(font);
					marker.setString(std::string(1, val));
					marker.setCharacterSize(150);
					marker.setFillColor(sf::Color::Cyan);
					marker.setPosition(static_cast<float>(j * 200 + 50), static_cast<float>(i * 200));
					window.draw(marker);
				}
			}
		}


		//status msg --->
		statustext.setString(statusMessage);
		window.draw(statustext);
		window.display();



	}
}

