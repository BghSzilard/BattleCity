#include "SFMLBullet.h"

SFMLBullet::SFMLBullet(BattleCity::TextureManager& textureManager, std::shared_ptr<Bullet>& bullet)
	: m_bullet{ bullet },
    m_textureManager(textureManager),
    m_texture(textureManager.getBulletTexture())
{
	setSprite();
}


std::shared_ptr<Bullet> SFMLBullet::bullet()
{
	return m_bullet;
}

void SFMLBullet::setTexture()
{
	m_texture = m_textureManager.getBulletTexture();
}

void SFMLBullet::setSprite()
{
	m_sprite.setTexture(m_texture);

	auto direction = m_bullet->getDirection();

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
    // apply the texture
    states.texture = &m_texture;
	
	auto position = m_bullet->getPosition();
	states.transform.translate(position.x, position.y);

	target.draw(m_sprite, states);
}
