#pragma once

#include "GameConfig.h"
#include "INavigationStrategy.h"
#include "Menu.h"

#include <array>
#include <string>
#include <memory>



class SFMLMenu: public Menu
{
private:

	std::array<sf::Text, GameConfig::OPTIONS.size()> m_menuOptionsText;

	sf::RenderWindow& m_window;
	sf::Font m_font;

	void navigate(std::unique_ptr<INavigationStrategy> navigationStrategy);
	
public:

	enum class MenuDirection
	{
		Upward,
		Downward
	};

	SFMLMenu(sf::RenderWindow& window);
	
	void changeMenuOption(MenuDirection menuDirection);
	int getChosenOption() override;

	void draw();
};