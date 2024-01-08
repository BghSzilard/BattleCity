#pragma once

#include "Bullet.h"
#include "GameConfig.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

#include <memory>

class SFMLBullet : public sf::Drawable
{
public:

	SFMLBullet(BattleCity::TextureManager&, std::shared_ptr<Bullet>& bullet);

	std::shared_ptr<Bullet> bullet();
private:

	void setTexture();
	void setSprite();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::shared_ptr<Bullet> m_bullet;
	
	sf::Sprite m_sprite;
	sf::Texture& m_texture;
	BattleCity::TextureManager& m_textureManager;
};