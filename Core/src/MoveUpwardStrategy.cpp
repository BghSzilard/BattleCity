#include "MoveUpwardStrategy.h"

Position MoveUpwardStrategy::move(Position position, float speed)
{
	position.y -= speed;
	return position;
}