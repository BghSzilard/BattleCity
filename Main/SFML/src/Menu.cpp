#include "Menu.h"

#include <array>
#include <SFML/Graphics.hpp>

Menu::Menu(sf::RenderWindow& window): m_window(window)
{

	font.loadFromFile(GameConfig::FONT_PATH);

	for (int i = 0; i < menuOptions.size(); ++i)
	{
		menuOptionsText[i].setFont(font);
		menuOptionsText[i].setCharacterSize(window.getSize().y / 12);
		menuOptionsText[i].setString(menuOptions[i]);

		menuOptionsText[i].setPosition(float(window.getSize().y / 3),
			float(window.getSize().y / 2.5 + i * window.getSize().y / 6.4));
	}
}

void Menu::draw()
{
	for (int i = 0; i < menuOptions.size(); ++i)
	{
		m_window.draw(menuOptionsText[i]);
	}
}