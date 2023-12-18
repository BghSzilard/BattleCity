#pragma once

#include "GameConfig.h"

class Bullet
{
public:

	Bullet(float startX, float startY, GameConfig::Direction direction);
	
	virtual void move() = 0;

protected:

	float m_startX;
	float m_startY;
	GameConfig::Direction m_direction;
};