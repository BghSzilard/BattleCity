#include "Game.h"

namespace BattleCity
{
	Game::Game() : FPSclock{ font }
	{
		std::srand(unsigned(std::time(nullptr)));
		// hardcoded screen size so that map nicely fills the screen (can be modified later)
		window.create(sf::VideoMode(1024, 1024), "Battle City");
		window.setFramerateLimit(60);

		font.loadFromFile("data/joystix monospace.ttf");
		//move literals to Constants/Config header ofc
		m_tileMap.load("data/map.txt", "data/tileset.png");

		state = GameState::Menu;
	}

	void Game::runGame()
	{
		while (state != GameState::EXIT)
		{
			switch (state)
			{
			case GameState::Menu:
				menu();
				break;
			case GameState::SinglePlayerGame:
				singlePlayer();
				break;
			}
		}
	}

	void Game::menu()
	{
		const int ILE{ 3 };
		sf::Text tekst[ILE];
		sf::String str[]{ "1 player", "2 players", "Exit" };
		sf::Sprite menuStone = spr.stoneBig;

		for (int i = 0; i < ILE; i++) {
			tekst[i].setFont(font);
			tekst[i].setCharacterSize(window.getSize().y / 12);

			tekst[i].setString(str[i]);
			tekst[i].setPosition(float(window.getSize().y / 3),
				float(window.getSize().y / 2.5 + i * window.getSize().y / 6.4));
		}

		//spr.tankIco.setScale(float(map.pr.scale * 1.5), float(map.pr.scale * 1.5));


		icon = GameState::SinglePlayerGame;

		while (state == GameState::Menu) {
			FPSclock.stopClock();
			eventsMenu();

			//change the color to red 
			for (int i = 0; i < ILE; i++) {
				if (i == int(icon) - 1) {
					tekst[i].setFillColor(sf::Color::Red);
					spr.tankIco.setPosition(tekst[i].getPosition());
					spr.tankIco.move(float(window.getSize().x) / float(-20.0), 0);
				}
				// put the color to be white 
				else tekst[i].setFillColor(sf::Color::White);
			}
			window.clear();
			// build the menu stone
			/*for (int y = 0; y < 15; y++) {
				for (int x = 0; x < map.pr.widthInBlocks / 2; x++) {
					if (x == 0 || y == 0 || x == map.pr.widthInBlocks / 2 - 1 || y == 14) {
						menuStone.setScale(map.pr.scale, map.pr.scale);
						menuStone.setPosition(float(map.pr.sides + x * (map.pr.blockSize * 2)), float(map.pr.topBot + y * (map.pr.blockSize * 2)));
						window.draw(menuStone);
					}
				}
			}*/
			/*spr.backGround.setPosition(float(std::round(map.pr.widthInBlocks / 8) * map.pr.blockSize + map.pr.sides), float(4 * map.pr.blockSize + map.pr.topBot));
			spr.backGround.setScale(map.pr.scale * 0.8, map.pr.scale * 0.8);
			window.draw(spr.backGround);

			spr.control.setPosition(1050, 780);
			float(float(map.pr.widthInBlocks * 30) - float(4 * map.pr.blockSize + map.pr.topBot)), float(std::round(map.pr.widthInBlocks / 8) * map.pr.blockSize + map.pr.sides);
			spr.control.setScale(map.pr.scale * 1.2, map.pr.scale * 1.2);
			window.draw(spr.control);
			window.draw(spr.tankIco);*/
			for (int i = 0; i < ILE; i++) {
				window.draw(tekst[i]);
			}
			FPSclock.draw(window);
			window.display();
		}
	}

	void Game::eventsMenu()
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			// Press ESC or the X button in the window
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				state = GameState::EXIT;
			// 1 player mode (tank in the right position + enter)
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
				icon == GameState::SinglePlayerGame) {
				state = GameState::SinglePlayerGame;
			}
			// 2 players mode (tank in the right position + enter)
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
				icon == GameState::TwoPlayerGame) {
				state = GameState::TwoPlayerGame;
			}
			// EXIT mode (tank in the right position + enter)
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
				icon == GameState::EXIT) {
				state = GameState::EXIT;
			}
			// moving the tank icon - arrow up
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up && int(icon) > 1) {
				switch (icon) {
				case GameState::TwoPlayerGame: icon = GameState::SinglePlayerGame;
					break;
				case GameState::EXIT: icon = GameState::TwoPlayerGame;
					break;
				}
			}
			// moving the tank icon - arrow down
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down && int(icon) < 3) {
				switch (icon) {
				case GameState::SinglePlayerGame: icon = GameState::TwoPlayerGame;
					break;
				case GameState::TwoPlayerGame: icon = GameState::EXIT;
					break;
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T) {
				FPSclock.switchClock();
			}
		}
	}

	void Game::singlePlayer()
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			// Press ESC or the X button in the window
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				state = GameState::EXIT;

			window.clear();
			window.draw(m_tileMap);
			window.display();
		}
	}

}