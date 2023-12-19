#include "Bullet.h"

Bullet::Bullet(float startX, float startY, GameConfig::Direction direction)
{
	m_startX = startX;
	m_startY = startY;
	m_direction = direction;
}

void Bullet::setStartX(float startX)
{
	m_startX = startX;
}

void Bullet::setStartY(float startY)
{
	m_startY = startY;
}

void Bullet::setDirection(GameConfig::MoveDirection direction)
{
	m_direction = direction;
}

float Bullet::getStartX()
{
	return m_startX;
}

float Bullet::getStartY()
{
	return m_startY;
}

GameConfig::MoveDirection Bullet::getDirection()
{
	return m_direction;
}
