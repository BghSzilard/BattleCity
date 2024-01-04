#include "SFMLEagle.h"

SFMLEagle::SFMLEagle()
{
	setTexture();
	setSprite();

	auto position = m_eagle.getPosition();

	m_sprite.setPosition(position.x, position.y);
}

Position SFMLEagle::getPosition()
{
	return m_eagle.getPosition();
}

void SFMLEagle::setTexture()
{
	m_texture = m_textureManager.getEagleTexture();
}

void SFMLEagle::setSprite()
{
	m_sprite.setTexture(m_texture);
}

void SFMLEagle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}