#pragma once

#include "Timer.h"
#include "TileMap.h"
#include "SFMLTank.h"
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
		sf::RenderWindow m_window;

//		GameState m_icon;  // needed to determine the position of the tank in the menu
		GameState m_state; // current manu status of the game (menu, single, multi etc)

        TextureManager& m_textureManager;

        BattleCity::GameLogic::GameLogic m_gameModel;

        std::vector<SFML::SFMLTank> tanks;
        std::vector<SFMLBullet> bullets;

//		Sprite m_spr;
		SFML::TileMap m_tileMap;
        SFML::SFMLTank m_playerTank;

        std::vector<SFML::SFMLTank> m_enemyTanks;

        std::unique_ptr<SFMLBullet> m_playerBullet;

		void menu();

		GameState determineGameState(int option);

		void singlePlayer();

        bool bulletAlive(const SFMLBullet& bullet);
    };
}