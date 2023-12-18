#include "Bullet.h"

Bullet::Bullet(float startX, float startY, GameConfig::Direction direction)
{
	m_startX = startX;
	m_startY = startY;
	m_direction = direction;
}