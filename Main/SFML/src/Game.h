#pragma once

#include "Timer.h"
#include "TileMap.h"
#include "SFMLTank.h"
#include "SFMLEagle.h"
#include "GameLogic.h"

namespace BattleCity::SFML
{
	class Game
	{
	public:
		explicit Game(TextureManager& textureManager);

		enum class GameState { SFMLMenu, SinglePlayerGame, TwoPlayerGame, EXIT };

		void runGame();

	private:
		void checkTankTileCollision();
		void checkBulletTileCollision();
		void checkEnemyTankPlayerBulletCollision();
		void checkEaglePlayerBulletCollision();
		void checkCollision();

	private:
		sf::RenderWindow m_window;

//		GameState m_icon;  // needed to determine the position of the tank in the menu
		GameState m_state; // current manu status of the game (menu, single, multi etc)

        TextureManager& m_textureManager;

        BattleCity::GameLogic::GameLogic m_gameModel;

        std::vector<SFML::SFMLTank> tanks;
        std::vector<std::unique_ptr<SFMLBullet>> bullets;

		std::vector<std::unique_ptr<SFMLEagle>> m_eagles;

        std::vector<std::shared_ptr<GameLogic::Tank>> playerTanks;
		std::vector<GameLogic::Bullet*> playerBullets;

//		Sprite m_spr;
		SFML::TileMap m_tileMap;
        SFML::SFMLTank m_playerTank;
        SFML::SFMLTank m_playerTank2;

        std::vector<std::unique_ptr<SFML::SFMLTank>> m_enemyTanks;

        std::unique_ptr<SFMLBullet> m_playerBullet;
        std::unique_ptr<SFMLBullet> m_playerBullet2;

		void menu();

		GameState determineGameState(int option);

		void singlePlayer();
		void twoPlayer();

        bool bulletAlive(SFMLBullet& bullet);
    };
}