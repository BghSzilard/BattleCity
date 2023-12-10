#include "SFMLMenu.h"
#include "NavigateUpwardStrategy.h"
#include "NavigateDownwardStrategy.h"

#include <array>
#include <string>
#include <SFML/Graphics.hpp>

void SFMLMenu::navigate(std::unique_ptr<INavigationStrategy> navigationStrategy)
{
	std::string* firstMenuOption = &m_menuOptions[0];
	int chosenOptionNumber = m_chosenOption - firstMenuOption;
	
	m_menuOptionsText[chosenOptionNumber].setFillColor(sf::Color::White);
	chosenOptionNumber = navigationStrategy->determineChosenOption(chosenOptionNumber);
	m_chosenOption = &m_menuOptions[chosenOptionNumber];
	m_menuOptionsText[chosenOptionNumber].setFillColor(sf::Color::Red);

}


SFMLMenu::SFMLMenu(sf::RenderWindow& window): m_window(window)
{
	m_font.loadFromFile(GameConfig::FONT_PATH);

	for (int i = 0; i < m_menuOptions.size(); ++i)
	{
		m_menuOptionsText[i].setFont(m_font);
		m_menuOptionsText[i].setCharacterSize(window.getSize().y / 12);
		m_menuOptionsText[i].setString(m_menuOptions[i]);

		m_menuOptionsText[i].setPosition(float(window.getSize().x / 4),
			float(window.getSize().y / 3 + i * window.getSize().y / 6.4));
	}

	m_chosenOption = &m_menuOptions[0];
	m_menuOptionsText[0].setFillColor(sf::Color::Red);
}


void SFMLMenu::changeMenuOption(MenuDirection menuDirection)
{
	std::unique_ptr<INavigationStrategy> strategy;

	if (menuDirection == MenuDirection::Upward)
	{
		if (m_chosenOption == &m_menuOptions[0])
		{
			return;
		}

		strategy = std::make_unique<NavigateUpwardStrategy>();
	}
	else if (menuDirection == MenuDirection::Downward)
	{
		if (m_chosenOption == &m_menuOptions[m_menuOptions.size() - 1])
		{
			return;
		}

		strategy = std::make_unique<NavigateDownwardStrategy>();
	}

	navigate(std::move(strategy));
}

int SFMLMenu::getChosenOption()
{
	std::string* firstMenuOption = &m_menuOptions[0];
	int chosenOptionNumber = m_chosenOption - firstMenuOption;

	return chosenOptionNumber;
}


void SFMLMenu::draw()
{
	for (int i = 0; i < m_menuOptions.size(); ++i)
	{
		m_window.draw(m_menuOptionsText[i]);
	}
}