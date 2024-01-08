#include "SFMLMenu.h"
#include "Game.h"

#include <SFML/Graphics.hpp>

int main()
{
    BattleCity::TextureManager TextureManager;
	BattleCity::SFML::Game MyGame(TextureManager);
	MyGame.runGame();
}