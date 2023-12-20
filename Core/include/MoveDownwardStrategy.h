#pragma once

#include "IMoveStrategy.h"
#include "Position.h"

class MoveDownwardStrategy : public IMoveStrategy
{
public:

	Position move(Position position, float speed);
};