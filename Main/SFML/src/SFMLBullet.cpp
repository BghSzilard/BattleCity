#include "SFMLBullet.h"

SFMLBullet::SFMLBullet(float startX, float startY, GameConfig::MoveDirection direction)
{
	m_bullet.setStartX(startX);
	m_bullet.setStartY(startY);
	m_bullet.setDirection(direction);
	m_sprite.setPosition(startX, startY);
	setTexture();
	setSprite();
}

void SFMLBullet::setTexture()
{
	m_texture = m_textureManager.getBulletTexture();
}

void SFMLBullet::setSprite()
{
	m_sprite.setTexture(m_texture);
}

void SFMLBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}