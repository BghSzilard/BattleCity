#pragma once

#include "Bullet.h"
#include "GameConfig.h"

#include <SFML\Graphics.hpp>

class SFMLBullet : public sf::Drawable
{
public:

	SFMLBullet(Sprite& sprite, float startX, float startY, GameConfig::MoveDirection direction);

private:

	Bullet m_bullet;
};