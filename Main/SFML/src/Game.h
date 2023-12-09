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

		enum class GameState { Menu, SinglePlayerGame, TwoPlayerGame, EXIT };

		void runGame();

	private:
		sf::RenderWindow window;

		GameState icon;  // needed to determine the position of the tank in the menu
		GameState state; // current manu status of the game (menu, single, multi etc)

		Sprite spr;
		SFML::TileMap m_tileMap;

		sf::Font font;
		Timer FPSclock;

		void menu();
		void eventsMenu();

		void singlePlayer();
	};
}