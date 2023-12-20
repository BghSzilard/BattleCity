#pragma once

#include "IMoveStrategy.h"
#include "Position.h"

class MoveUpwardStrategy : public IMoveStrategy
{
public:

	Position move(Position position, float speed);
};