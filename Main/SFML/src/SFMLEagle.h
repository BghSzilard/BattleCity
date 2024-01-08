#pragma once

#include "Eagle.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

namespace BattleCity::SFML {

	class SFMLEagle : public sf::Drawable
	{
	public:

		SFMLEagle(std::shared_ptr<GameLogic::Eagle> eagle);

		std::shared_ptr<GameLogic::Eagle> eagle();

	private:

		void setTexture();
		void setSprite();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)  const;

		std::shared_ptr<GameLogic::Eagle> m_eagle;
		sf::Sprite m_sprite;
		sf::Texture m_texture;
		BattleCity::TextureManager m_textureManager;
	};
}