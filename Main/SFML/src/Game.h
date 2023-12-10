#pragma once
#include "Sprite.h"
#include "Timer.h"
#include "TileMap.h"

namespace BattleCity
{
	class Game
	{
	public:
		Game();

		enum class GameState { SFMLMenu, SinglePlayerGame, TwoPlayerGame, EXIT };

		void runGame();

	private:
		sf::RenderWindow m_window;

		GameState m_icon;  // needed to determine the position of the tank in the menu
		GameState m_state; // current manu status of the game (menu, single, multi etc)

		Sprite m_spr;
		SFML::TileMap m_tileMap;

		sf::Font m_font;
		Timer m_FPSclock;

		void menu();
		GameState determineGameState(int option);

		void singlePlayer();
	};
}