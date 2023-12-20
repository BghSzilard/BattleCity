#pragma once

#include "Position.h"

class IMoveStrategy
{
public:
	virtual ~IMoveStrategy() {};
	virtual Position move(Position position, float speed) = 0;
};