#pragma once

#include "INavigationStrategy.h"

class NavigateUpwardStrategy : public INavigationStrategy
{
public:

	int determineChosenOption(int currentChosenOption);
};