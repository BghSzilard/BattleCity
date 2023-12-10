#pragma once

class INavigationStrategy
{
public:
	virtual ~INavigationStrategy() {};
	virtual int determineChosenOption(int currentOption) = 0;
};