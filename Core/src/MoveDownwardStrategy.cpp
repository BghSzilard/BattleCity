#include "MoveDownwardStrategy.h"

Position MoveDownwardStrategy::move(Position position, float speed)
{
	position.y += speed;
	return position;
}