#pragma once

#include "IMoveStrategy.h"
#include "Position.h"

class MoveLeftwardStrategy : public IMoveStrategy
{
public:

	Position move(Position position, float speed);
};