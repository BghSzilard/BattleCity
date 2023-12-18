#pragma once
#include "Sprite.h"
#include "Timer.h"
#include "TileMap.h"
#include "SFMLTank.h"

namespace BattleCity
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

//		Sprite m_spr;
		SFML::TileMap m_tileMap;
        SFML::SFMLTank m_playerTank;

		void menu();

		GameState determineGameState(int option);

		void singlePlayer();
	};
}