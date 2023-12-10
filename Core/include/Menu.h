#pragma once

#include "GameConfig.h"

#include <string>
#include <array>

class Menu
{
protected:

	std::string* m_chosenOption;
	std::array<std::string, GameConfig::OPTIONS.size()> m_menuOptions = GameConfig::OPTIONS;

public:
	
	virtual int getChosenOption() = 0;
	virtual ~Menu() = default;
};