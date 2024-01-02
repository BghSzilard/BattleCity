#include "MoveLeftwardStrategy.h"

Position MoveLeftwardStrategy::move(Position position, float speed)
{
	position.x -= speed;
	return position;
}