#include "Game.h"

void Game::runGame()
{
	while (state != GameState::EXIT)
	{
		switch (state)
		{
		case GameState::Menu:
				break;
		case GameState::SinglePayerGame:
				break;
		}
	}
}