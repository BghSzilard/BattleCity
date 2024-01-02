#pragma once

#include "IMoveStrategy.h"
#include "Position.h"

class MoveRightwardStrategy : public IMoveStrategy
{
public:

	Position move(Position position, float speed);
};