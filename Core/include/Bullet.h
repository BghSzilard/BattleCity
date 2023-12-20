#pragma once

#include "GameConfig.h"

class Bullet
{
public:

	Bullet() = default;

	//for collision detection: player's bullets should kill enemy tanks, but enemy tanks shooting each other should not effect them
	enum class BulletType
	{
		PlayerBullet,
		EnemyBullet
	};

	void setStartX(float startX);
	void setStartY(float startY);
	void setDirection(GameConfig::MoveDirection direction);

	float getStartX();
	float getStartY();
	GameConfig::MoveDirection getDirection();

private:

	float m_startX;
	float m_startY;
	GameConfig::MoveDirection m_direction;
	BulletType m_bulletType;
};