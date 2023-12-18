#include "SFMLBullet.h"

SFMLBullet::SFMLBullet(Sprite& sprite, float startX, float startY, GameConfig::Direction direction): Bullet(startX, startY, direction)
{
	m_sprite = sprite;
}