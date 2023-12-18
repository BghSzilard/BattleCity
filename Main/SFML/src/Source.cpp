#include "SFMLMenu.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

int main()
{
    BattleCity::TextureManager TextureManager;
	BattleCity::Game MyGame(TextureManager);
	MyGame.runGame();
}