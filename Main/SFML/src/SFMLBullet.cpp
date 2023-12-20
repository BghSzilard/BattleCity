#include "SFMLBullet.h"

SFMLBullet::SFMLBullet(float startX, float startY, GameConfig::MoveDirection direction, Bullet::BulletType bulletType) 
	: m_bullet({startX, startY}, direction, bulletType)
{
	
	m_sprite.setPosition(startX, startY);
	setTexture();
	setSprite();
}

void SFMLBullet::move()
{
	m_bullet.move();
	auto position = m_bullet.getPosition();
	m_sprite.setPosition(position.x, position.y);
}

Position SFMLBullet::getPosition()
{
	return m_bullet.getPosition();
}

GameConfig::MoveDirection SFMLBullet::getDirection()
{
	return m_bullet.getDirection();
}

Bullet::BulletType SFMLBullet::getBulletType()
{
	return m_bullet.getBulletType();
}

void SFMLBullet::setTexture()
{
	m_texture = m_textureManager.getBulletTexture();
}

void SFMLBullet::setSprite()
{
	m_sprite.setTexture(m_texture);

	auto direction = m_bullet.getDirection();

	switch (direction)
	{
	case GameConfig::MoveDirection::LEFT:
		m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
		break;
	case GameConfig::MoveDirection::RIGHT:
		m_sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
		break;
	case GameConfig::MoveDirection::UP:
		m_sprite.setTextureRect(sf::IntRect(80, 0, 40, 40));
		break;
	case GameConfig::MoveDirection::DOWN:
		m_sprite.setTextureRect(sf::IntRect(120, 0, 40, 40));
		break;
	}

}

void SFMLBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}