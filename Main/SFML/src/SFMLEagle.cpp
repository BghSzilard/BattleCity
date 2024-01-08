#include "SFMLEagle.h"

namespace BattleCity::SFML
{
	SFMLEagle::SFMLEagle(std::shared_ptr<GameLogic::Eagle> eagle)
		: m_eagle{eagle}
	{
		setTexture();
		setSprite();

		auto position = m_eagle->getPosition();

		m_sprite.setPosition(position.x, position.y);
	}

	std::shared_ptr<GameLogic::Eagle> SFMLEagle::eagle()
	{
		return m_eagle;
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
}