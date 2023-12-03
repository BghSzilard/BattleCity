#pragma once
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Game
{
public:
	enum class GameState {Menu, SinglePayerGame, EXIT};
	
	void runGame();

private:
	
	GameState icon;  // needed to determine the position of the tank in the menu
	GameState state; // current manu status of the game (menu, single, multi etc)

	
};