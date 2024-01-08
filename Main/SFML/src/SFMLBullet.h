#pragma once

#include "Bullet.h"
#include "GameConfig.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace BattleCity::SFML
{
	class SFMLBullet : public sf::Drawable
	{
	public:

		SFMLBullet(TextureManager&, std::shared_ptr<GameLogic::Bullet>& bullet);

		std::shared_ptr<GameLogic::Bullet> bullet();
	private:

		void setTexture();

		void setSprite();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::shared_ptr<GameLogic::Bullet> m_bullet;

		sf::Sprite m_sprite;
		sf::Texture& m_texture;
		BattleCity::TextureManager& m_textureManager;
	};
}