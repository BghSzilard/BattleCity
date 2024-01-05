#pragma once

#include "Bullet.h"
#include "GameConfig.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

class SFMLBullet : public sf::Drawable
{
public:

	SFMLBullet(BattleCity::TextureManager&, float startX, float startY, GameConfig::MoveDirection direction, Bullet::BulletType bulletType);

	void move();

	Position getPosition() const;
	GameConfig::MoveDirection getDirection();
	Bullet::BulletType getBulletType();
private:

	void setTexture();
	void setSprite();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)  const;

	Bullet m_bullet;
	sf::Sprite m_sprite;
	sf::Texture& m_texture;
	BattleCity::TextureManager& m_textureManager;
};