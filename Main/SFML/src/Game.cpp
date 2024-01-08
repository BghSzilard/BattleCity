#include "Game.h"
#include "SFMLMenu.h"
#include "GameConfig.h"
#include "SFMLBullet.h"
#include "SFMLEagle.h"

#include <algorithm>
#include <iostream>

namespace BattleCity::SFML
{
	Game::Game(TextureManager& textureManager)
		: m_textureManager(textureManager), m_gameModel(std::make_unique<GameLogic::LevelFactory>()),
		m_tileMap(m_textureManager,
			std::move(m_gameModel.getLevel())),
		m_playerTank(m_textureManager, std::make_shared<GameLogic::Tank>(GameConfig::INITIAL_TANK_POS_X, GameConfig::INITIAL_TANK_POS_Y, GameLogic::Tank::MoveDirection::UP)),
		m_playerTank2(m_textureManager, std::make_shared<GameLogic::Tank>(GameConfig::INITIAL_TANK_POS_X + 64, GameConfig::INITIAL_TANK_POS_Y + 64, GameLogic::Tank::MoveDirection::UP)),
		m_eagles()
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

		m_enemyTanks.emplace_back(std::make_unique<SFMLTank>(textureManager, std::make_shared<GameLogic::Tank>(150.f, 150.f, GameLogic::Tank::MoveDirection::UP)));

		m_enemyTanks[0]->tank()->setOnBulletShot(
			[this](const GameLogic::Tank&, std::shared_ptr<GameLogic::Bullet> bullet)
			{
				bullets.emplace_back(std::make_unique<SFMLBullet>(m_textureManager, bullet));
			}
		);

		m_eagles.emplace_back(std::make_unique<SFMLEagle>(std::make_shared<GameLogic::Eagle>(Position{64*5, 20})));
		m_eagles.emplace_back(std::make_unique<SFMLEagle>(std::make_shared<GameLogic::Eagle>(Position{64*10, 30})));
		m_eagles.emplace_back(std::make_unique<SFMLEagle>(std::make_shared<GameLogic::Eagle>(Position{64*7, 64*14})));
		m_eagles.emplace_back(std::make_unique<SFMLEagle>(std::make_shared<GameLogic::Eagle>(Position{64*4, 64*12})));
		m_eagles.emplace_back(std::make_unique<SFMLEagle>(std::make_shared<GameLogic::Eagle>(Position{64*11, 64*12})));
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
					this->~Game();
					auto& asd = m_textureManager;
					new(this) Game(asd);
					m_state = determineGameState(chosenOption);
					switch (m_state) {
					case GameState::TwoPlayerGame:
						playerTanks.push_back(m_playerTank2.tank());
					case GameState::SinglePlayerGame:
						playerTanks.push_back(m_playerTank.tank());
					}
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

		checkCollision();

		m_window.clear();
		m_window.draw(m_tileMap);
		m_window.draw(m_playerTank);
		for (auto& tank : m_enemyTanks)
		{
			m_window.draw(*tank);
		}
		if (m_playerBullet)
		{
			m_window.draw(*m_playerBullet);
			m_playerBullet->bullet()->move();
		}
		for (auto& eagle : m_eagles) {
			m_window.draw(*eagle);
		}
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

		if (m_playerBullet && (!m_playerBullet->bullet()->isAlive || !bulletAlive(*m_playerBullet)))
			m_playerBullet = nullptr;

		if (m_enemyTanks.empty()) {
			m_state = GameState::SFMLMenu;
		}
	}

	void Game::twoPlayer()
	{
		sf::Event event;

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

		checkCollision();

		m_window.clear();
		m_window.draw(m_tileMap);
		m_window.draw(m_playerTank);
		m_window.draw(m_playerTank2);
		for (auto& tank : m_enemyTanks)
		{
			m_window.draw(*tank);
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

		if (m_playerBullet && (!m_playerBullet->bullet()->isAlive || !bulletAlive(*m_playerBullet)))
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

	struct CollSize
	{
		int w, h;
	};

	CollSize getCollisionSize(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
	{
		int w = width1 + width2 - std::max(std::abs(x1 - (x2 + width2)), std::abs(x2 - (x1 + width1)));
		int h = height1 + height2 - std::max(std::abs(y1 - (y2 + height2)), std::abs(y2 - (y1 + height1)));
		return { w, h };
	}

	bool isCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
	{
		if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2)
		{
			return true;
		}

		return false;
	}

	void Game::checkTankTileCollision()
	{
		auto& playerTanks = this->playerTanks;
		auto& enemyTanks = m_enemyTanks;

		for (int k = 0; k < playerTanks.size(); ++k)
		{
			for (int i = 0; i < m_tileMap.getMap().getWidth(); ++i)
			{
				for (int j = 0; j < m_tileMap.getMap().getHeight(); ++j)
				{
					int widthTank = playerTanks[k]->getWidth();
					int heightTank = playerTanks[k]->getHeight();
					int xTank = playerTanks[k]->getXPosition();
					int yTank = playerTanks[k]->getYPosition();

					int xTile = j * GameConfig::MAP_TILE_SIZE;
					int yTile = i * GameConfig::MAP_TILE_SIZE;
					int widthTile = GameConfig::MAP_TILE_SIZE;
					int heightTile = GameConfig::MAP_TILE_SIZE;


					if (isCollision(xTank - widthTank / 2, yTank - heightTank / 2, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
					{
						switch (m_tileMap.getMap().at(i, j))
						{
						case 0: // brick
						case 1: // stone
						case 2: // water
						{
							auto collSize = getCollisionSize(xTank - widthTank / 2, yTank - heightTank / 2, widthTank, heightTank, xTile, yTile,
								widthTile, heightTile);
							switch (playerTanks[k]->getTankDirection())
							{
							case GameLogic::Tank::MoveDirection::LEFT:
							{
								playerTanks[k]->setPosition(xTank + collSize.w, yTank);
								break;
							}
							case GameLogic::Tank::MoveDirection::UP:
							{
								playerTanks[k]->setPosition(xTank, yTank + collSize.h);
								break;
							}
							case GameLogic::Tank::MoveDirection::RIGHT:
							{
								playerTanks[k]->setPosition(xTank - collSize.w, yTank);
								break;
							}
							case GameLogic::Tank::MoveDirection::DOWN:
							{
								playerTanks[k]->setPosition(xTank, yTank - collSize.h);
								break;
							}
							}
							break;
						}
						default:
							break;
						}
					}
				}
			}
		}
		//for (int k = 0; k < enemyTanks.size(); ++k)
		//{
		//	for (int i = 0; i < m_tileMap.getMap().getWidth(); ++i)
		//	{
		//		for (int j = 0; j < m_tileMap.getMap().getHeight(); ++j)
		//		{
		//			int xTank = enemyTanks[k].tank()->getXPosition();
		//			int yTank = enemyTanks[k].tank()->getYPosition();
		//			int widthTank = enemyTanks[k].tank()->getWidth();
		//			int heightTank = enemyTanks[k].tank()->getHeight();

		//			int xTile = j * GameConfig::MAP_TILE_SIZE;
		//			int yTile = i * GameConfig::MAP_TILE_SIZE;
		//			int widthTile = GameConfig::MAP_TILE_SIZE;
		//			int heightTile = GameConfig::MAP_TILE_SIZE;

		//			if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
		//			{
		//				switch (m_tileMap.getMap().at(i, j))
		//				{
		//				case 0: // brick
		//				case 1: // stone
		//				case 2: // water
		//				{
		//					auto collSize = getCollisionSize(xTank, yTank, widthTank, heightTank, xTile, yTile,
		//						widthTile, heightTile);
		//					switch (enemyTanks[i].tank()->getTankDirection())
		//					{
		//					case GameLogic::Tank::MoveDirection::LEFT:
		//					{
		//						enemyTanks[k].tank()->setPosition(xTank + collSize.w, yTank);
		//						break;
		//					}
		//					case GameLogic::Tank::MoveDirection::UP:
		//					{
		//						enemyTanks[k].tank()->setPosition(xTank, yTank + collSize.h);
		//						break;
		//					}
		//					case GameLogic::Tank::MoveDirection::RIGHT:
		//					{
		//						enemyTanks[k].tank()->setPosition(xTank - collSize.w, yTank);
		//						break;
		//					}
		//					case GameLogic::Tank::MoveDirection::DOWN:
		//					{
		//						enemyTanks[k].tank()->setPosition(xTank, yTank - collSize.h);
		//						break;
		//					}
		//					}
		//					break;
		//				}
		//				default:
		//					break;
		//				}
		//			}
		//		}
		//	}
		//}
	}

	void Game::checkBulletTileCollision()
	{
		auto& playerBullets = m_playerBullet;
		//auto &enemyBullets = m_enemyBullets;

		if (playerBullets)
			for (int i = 0; i < m_tileMap.getMap().getWidth(); ++i)
			{
				for (int j = 0; j < m_tileMap.getMap().getHeight(); ++j)
				{
					int xTank = playerBullets->bullet()->getPosition().x;
					int yTank = playerBullets->bullet()->getPosition().y;
					int widthTank = playerBullets->bullet()->getWidth();
					int heightTank = playerBullets->bullet()->getHeight();

					int xTile = j * GameConfig::MAP_TILE_SIZE;
					int yTile = i * GameConfig::MAP_TILE_SIZE;
					int widthTile = GameConfig::MAP_TILE_SIZE;
					int heightTile = GameConfig::MAP_TILE_SIZE;

					if (playerBullets->bullet()->isAlive && isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
					{
						switch (m_tileMap.getMap().at(i, j))
						{
						case 0: // brick
						{
							playerBullets->bullet()->isAlive = false;
							m_tileMap.getMap().at(i, j) = 4;
							m_tileMap.initMapTexture();
						}
						case 1: // stone
						{
							playerBullets->bullet()->isAlive = false;
							break;
						}
						default:
							break;
						}
					}
				}
			}
		//        for (int k = 0; k < enemyBullets.size(); ++k)
		//        {
		//            for (int i = 0; i < m_map.getWidth(); ++i)
		//            {
		//                for (int j = 0; j < m_map.getHeight(); ++j)
		//                {
		//                    int xTank = enemyBullets[i].getPosition().x;
		//                    int yTank = enemyBullets[i].getPosition().y;
		//                    int widthTank = enemyBullets[i].getWidth();
		//                    int heightTank = enemyBullets[i].getHeight();
		//
		//                    int xTile = i * GameConfig::MAP_TILE_SIZE;
		//                    int yTile = j * GameConfig::MAP_TILE_SIZE;
		//                    int widthTile = GameConfig::MAP_TILE_SIZE;
		//                    int heightTile = GameConfig::MAP_TILE_SIZE;
		//
		//                    if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
		//                    {
		//                        switch (m_map.at(i, j))
		//                        {
		//                            case 0: // brick
		//                            {
		//                                enemyBullets[i].isAlive = false;
		//                                m_map.at(i, j) = 4;
		//                            }
		//                            case 1: // stone
		//                            {
		//                                enemyBullets[i].isAlive = false;
		//                                break;
		//                            }
		//                            default:
		//                                break;
		//                        }
		//                    }
		//                }
		//            }
		//        }
	}

	void Game::checkEnemyTankPlayerBulletCollision()
	{
		auto& tanks = m_enemyTanks;
		playerBullets.clear();
		if (m_state == GameState::SinglePlayerGame && m_playerBullet) {
			playerBullets.push_back(m_playerBullet->bullet().get());
		}
		if (m_state == GameState::TwoPlayerGame && m_playerBullet2) {
			playerBullets.push_back(m_playerBullet2->bullet().get());
		}

		for (int i = 0; i < tanks.size(); ++i)
		{
			for (int j = 0; j < playerBullets.size(); ++j)
			{
				int xTank = tanks[i]->tank()->getXPosition();
				int yTank = tanks[i]->tank()->getYPosition();
				int widthTank = tanks[i]->tank()->getWidth();
				int heightTank = tanks[i]->tank()->getHeight();

				int xBullet = playerBullets[j]->getPosition().x;
				int yBullet = playerBullets[j]->getPosition().y;
				int widthBullet = playerBullets[j]->getWidth();
				int heightBullet = playerBullets[j]->getHeight();

				if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
				{
					tanks[i]->tank()->isAlive = false;
					playerBullets[j]->isAlive = false;
				}
			}
		}
	}

	void Game::checkEaglePlayerBulletCollision()
	{
		auto& eagles = m_eagles;
		playerBullets.clear();
		if (m_state == GameState::SinglePlayerGame && m_playerBullet) {
			playerBullets.push_back(m_playerBullet->bullet().get());
		}
		if (m_state == GameState::TwoPlayerGame && m_playerBullet2) {
			playerBullets.push_back(m_playerBullet2->bullet().get());
		}

		for (int i = 0; i < eagles.size(); ++i)
		{
			for (int j = 0; j < playerBullets.size(); ++j)
			{
				int xTank = eagles[i]->eagle()->getPosition().x;
				int yTank = eagles[i]->eagle()->getPosition().y;
				int widthTank = 100;
				int heightTank = 100;

				int xBullet = playerBullets[j]->getPosition().x;
				int yBullet = playerBullets[j]->getPosition().y;
				int widthBullet = playerBullets[j]->getWidth();
				int heightBullet = playerBullets[j]->getHeight();

				if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
				{
					m_state = GameState::SFMLMenu;
					return;
				}
			}
		}
	}

	void Game::checkCollision()
	{
		checkTankTileCollision();
		checkBulletTileCollision();
		checkEnemyTankPlayerBulletCollision();
		checkEaglePlayerBulletCollision();
		//std::remove_if(m_playerTanks.begin(), m_playerTanks.end(), [](const Tank& tank)
		//	{ return !tank.isAlive; });
		m_enemyTanks.erase(std::remove_if(m_enemyTanks.begin(), m_enemyTanks.end(), [](const std::unique_ptr<SFMLTank>& tank)
			{ return !tank->tank()->isAlive; }), m_enemyTanks.end());
		//std::remove_if(m_enemyBullets.begin(), m_enemyBullets.end(), [](const Bullet& bullet)
		//	{ return !bullet.isAlive; });
		//std::remove_if(m_playerBullets.begin(), m_playerBullets.end(), [](const Bullet& bullet)
		//	{ return !bullet.isAlive; });
	}
}