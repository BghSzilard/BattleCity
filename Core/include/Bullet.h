#pragma once

#include "GameConfig.h"

class Bullet
{
public:

	//Might be a good idea to have a tank object in the constructor once it has been defined
	Bullet(float startX, float startY, GameConfig::Direction direction);

	//for collision detection: player's bullets should kill enemy tanks, but enemy tanks shooting each other should not effect them
	enum class BulletType
	{
		PlayerBullet,
		EnemyBullet
	};

	public void setStartX(float startX);
	public void setStartY(float startY);
	public void setDirection(GameConfig::MoveDirection direction);

	public float getStartX();
	public float getStartY();
	public GameConfig::MoveDirection getDirection();

private:

	float m_startX;
	float m_startY;
	GameConfig::MoveDirection m_direction;
	BulletType m_bulletType;
};