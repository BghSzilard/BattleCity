#include "SFMLBullet.h"

SFMLBullet::SFMLBullet(Sprite& sprite, float startX, float startY, GameConfig::MoveDirection direction)
{
	m_sprite = sprite;
	m_bullet.setStartX(startX);
	m_bullet.setStartY(startY);
	m_bullet.setDirection(direction);
}