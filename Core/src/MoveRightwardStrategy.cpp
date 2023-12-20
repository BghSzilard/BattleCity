#include "MoveRightwardStrategy.h"

Position MoveRightwardStrategy::move(Position position, float speed)
{
	position.x += speed;
	return position;
}