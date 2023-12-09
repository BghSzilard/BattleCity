#include "Game.h"
#include "Menu.h"

namespace BattleCity
{
	Game::Game() : FPSclock{ font }
	{
		std::srand(unsigned(std::time(nullptr)));
		// hardcoded screen size so that map nicely fills the screen (can be modified later)
		window.create(sf::VideoMode(1024, 1024), "Battle City");
		window.setFramerateLimit(60);

		font.loadFromFile("sfml_assets/fonts/joystix monospace.ttf");
		//move literals to Constants/Config header ofc
		m_tileMap.load("core_assets/maps/map.txt", "sfml_assets/textures/tileset.png");

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
		// Create a Menu with the window reference
		Menu menu(window);

		// Main game loop
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			// Clear the window
			window.clear();

			// Draw the menu
			menu.draw();

			// Display the window
			window.display();
		}

		state = GameState::EXIT;
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