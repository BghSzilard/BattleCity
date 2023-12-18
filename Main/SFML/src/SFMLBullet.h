#pragma once

#include "Bullet.h"
#include "Sprite.h"
#include "GameConfig.h"

#include <SFML\Graphics.hpp>

class SFMLBullet : public Bullet, public sf::Drawable
{
public:

	SFMLBullet(Sprite& sprite, float startX, float startY, GameConfig::Direction direction);

private:

	Sprite m_sprite;
};