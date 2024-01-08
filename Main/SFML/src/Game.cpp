#include "Game.h"
#include "SFMLMenu.h"
#include "GameConfig.h"
#include "SFMLBullet.h"
#include "SFMLEagle.h"

#include <algorithm>

namespace BattleCity::SFML
{
    Game::Game(TextureManager &textureManager)
            : m_textureManager(textureManager), m_gameModel(std::make_unique<GameLogic::LevelFactory>()),
              m_tileMap(m_textureManager,
			  std::move(m_gameModel.getLevel())),
              m_playerTank(m_textureManager, std::make_shared<GameLogic::Tank>(GameConfig::INITIAL_TANK_POS_X, GameConfig::INITIAL_TANK_POS_Y, GameLogic::Tank::MoveDirection::UP)),
              m_playerTank2(m_textureManager, std::make_shared<GameLogic::Tank>(GameConfig::INITIAL_TANK_POS_X+64, GameConfig::INITIAL_TANK_POS_Y+64, GameLogic::Tank::MoveDirection::UP))
    {
//		std::srand(unsigned(std::time(nullptr)));
        // hardcoded screen size so that map nicely fills the screen (can be modified later)
        m_window.create(sf::VideoMode(1024, 1024), GameConfig::WINDOW_NAME);
        m_window.setFramerateLimit(GameConfig::FRAME_LIMIT);

		m_state = GameState::SFMLMenu;

		m_playerTank.tank()->setOnBulletShot(
			[this](const GameLogic::Tank&, std::shared_ptr<GameLogic::Bullet> bullet)
			{
				m_playerBullet = std::make_unique<SFMLBullet>(m_textureManager, bullet);
			}
		);
		m_playerTank2.tank()->setOnBulletShot(
			[this](const GameLogic::Tank&, std::shared_ptr<GameLogic::Bullet> bullet)
			{
				m_playerBullet2 = std::make_unique<SFMLBullet>(m_textureManager, bullet);
			}
		);

		m_enemyTanks.emplace_back(SFML::SFMLTank(textureManager, std::make_shared<GameLogic::Tank>(150.f, 150.f, GameLogic::Tank::MoveDirection::UP)));

		m_enemyTanks[0].tank()->setOnBulletShot(
			[this](const GameLogic::Tank&, std::shared_ptr<GameLogic::Bullet> bullet)
			{
				bullets.emplace_back(std::make_unique<SFMLBullet>(m_textureManager, bullet));
			}
		);
	}

	void Game::runGame()
	{
		while (m_state != GameState::EXIT)
		{
			switch (m_state)
			{
			case GameState::SFMLMenu:
				menu();
				break;
			case GameState::SinglePlayerGame:
				singlePlayer();
				break;
			case GameState::TwoPlayerGame:
				twoPlayer();
				break;
			}
		}
	}

	void Game::menu()
	{
		// Create a Menu with the window reference
		SFMLMenu menu(m_window);

		// Main game loop
		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up)
				{
					menu.changeMenuOption(SFMLMenu::MenuDirection::Upward);
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down)
				{
					menu.changeMenuOption(SFMLMenu::MenuDirection::Downward);
				}
				else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Enter)
				{
					int chosenOption = menu.getChosenOption();
					m_state = determineGameState(chosenOption);
					return;
				}
			}

			// Clear the window
			m_window.clear();

			// Draw the menu
			menu.draw();

			// Display the window
			m_window.display();
		}

		m_state = GameState::EXIT;
	}

    Game::GameState Game::determineGameState(int option)
    {
        switch (option)
        {
            case 0:
                return Game::GameState::SinglePlayerGame;
                break;
            case 1:
                return Game::GameState::TwoPlayerGame;
                break;
            case 2:
                return Game::GameState::EXIT;
                break;
            default:
                return Game::GameState::EXIT;
        }
    }


	void Game::singlePlayer()
	{
		sf::Event event;
		SFMLEagle eagle;

		while (m_window.pollEvent(event))
		{
			// Press ESC or the X button in the window
			if (event.type == sf::Event::Closed ||
				event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_state = GameState::EXIT;
		}

		// TODO: Check bounds of screen
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::LEFT);
			m_playerTank.tank()->moveTank(-1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::RIGHT);
			m_playerTank.tank()->moveTank(1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::UP);
			m_playerTank.tank()->moveTank(0, -1.f * GameConfig::TANK_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::DOWN);
			m_playerTank.tank()->moveTank(0, 1.f * GameConfig::TANK_SPEED);
		}
		if (!m_playerBullet && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_playerTank.tank()->shootBullet();
		}

		m_window.clear();
		m_window.draw(m_tileMap);
		m_window.draw(m_playerTank);
		for (auto& tank : m_enemyTanks)
		{
			m_window.draw(tank);
		}
		if (m_playerBullet)
		{
			m_window.draw(*m_playerBullet);
			m_playerBullet->bullet()->move();
		}
		m_window.draw(eagle);
		for (auto& bullet : bullets)
		{
			if (bulletAlive(*bullet))
			{
				bullet->bullet()->move();
				m_window.draw(*bullet);
			}
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
			[this](std::unique_ptr<SFMLBullet>& bullet)
			{ return !bulletAlive(*bullet); }),
			bullets.end());


		m_window.display();

		if (m_playerBullet && !bulletAlive(*m_playerBullet))
			m_playerBullet = nullptr;
	}

	void Game::twoPlayer()
	{
		sf::Event event;
		SFMLEagle eagle;

		while (m_window.pollEvent(event))
		{
			// Press ESC or the X button in the window
			if (event.type == sf::Event::Closed ||
				event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_state = GameState::EXIT;
		}

		// TODO: Check bounds of screen
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::LEFT);
			m_playerTank.tank()->moveTank(-1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::RIGHT);
			m_playerTank.tank()->moveTank(1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::UP);
			m_playerTank.tank()->moveTank(0, -1.f * GameConfig::TANK_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_playerTank.tank()->setTankDirection(GameLogic::Tank::MoveDirection::DOWN);
			m_playerTank.tank()->moveTank(0, 1.f * GameConfig::TANK_SPEED);
		}

		if (!m_playerBullet && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			m_playerTank.tank()->shootBullet();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_playerTank2.tank()->setTankDirection(GameLogic::Tank::MoveDirection::LEFT);
			m_playerTank2.tank()->moveTank(-1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_playerTank2.tank()->setTankDirection(GameLogic::Tank::MoveDirection::RIGHT);
			m_playerTank2.tank()->moveTank(1.0f * GameConfig::TANK_SPEED, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_playerTank2.tank()->setTankDirection(GameLogic::Tank::MoveDirection::UP);
			m_playerTank2.tank()->moveTank(0, -1.f * GameConfig::TANK_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_playerTank2.tank()->setTankDirection(GameLogic::Tank::MoveDirection::DOWN);
			m_playerTank2.tank()->moveTank(0, 1.f * GameConfig::TANK_SPEED);
		}

		if (!m_playerBullet2 && sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			m_playerTank2.tank()->shootBullet();
		}

		m_window.clear();
		m_window.draw(m_tileMap);
		m_window.draw(m_playerTank);
		m_window.draw(m_playerTank2);
		for (auto& tank : m_enemyTanks)
		{
			m_window.draw(tank);
		}
		if (m_playerBullet)
		{
			m_window.draw(*m_playerBullet);
			m_playerBullet->bullet()->move();
		}
		if (m_playerBullet2)
		{
			m_window.draw(*m_playerBullet2);
			m_playerBullet2->bullet()->move();
		}
		m_window.draw(eagle);
		for (auto& bullet : bullets)
		{
			if (bulletAlive(*bullet))
			{
				bullet->bullet()->move();
				m_window.draw(*bullet);
			}
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
			[this](std::unique_ptr<SFMLBullet>& bullet)
			{ return !bulletAlive(*bullet); }),
			bullets.end());


		m_window.display();

		if (m_playerBullet && !bulletAlive(*m_playerBullet))
			m_playerBullet = nullptr;
		if (m_playerBullet2 && !bulletAlive(*m_playerBullet2))
			m_playerBullet2 = nullptr;
	}

	bool Game::bulletAlive(SFMLBullet& bullet)
	{
		float xPos = bullet.bullet()->getPosition().x;
		float yPos = bullet.bullet()->getPosition().y;
		return (xPos >= 0 && xPos < GameConfig::SCREEN_WIDTH) && (yPos >= 0 && yPos < GameConfig::SCREEN_HEIGHT);
	}
}