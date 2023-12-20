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