#pragma once

#include "INavigationStrategy.h"

class NavigateDownwardStrategy : public INavigationStrategy
{
public:

	int determineChosenOption(int currentChosenOption);
};