#pragma once
#include <array>
#include <string>
#include "GameConfig.h"

class Menu
{
private:

	std::array<std::string, GameConfig::OPTIONS.size()> menuOptions = GameConfig::OPTIONS;
	std::array<sf::Text, GameConfig::OPTIONS.size()> menuOptionsText;

	sf::RenderWindow& m_window;
	sf::Font font;


public:

	Menu(sf::RenderWindow& window);

	void draw();
};