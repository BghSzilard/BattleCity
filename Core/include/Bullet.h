#pragma once

#include "GameConfig.h"
#include "Position.h"
#include "IMoveStrategy.h"

#include <memory>

class Bullet
{
public:

	//for collision detection: player's bullets should kill enemy tanks, but enemy tanks shooting each other should not effect them
	enum class BulletType
	{
		PlayerBullet,
		EnemyBullet
	};

	Bullet(Position position, GameConfig::MoveDirection direction, BulletType bulletType);

	Position getPosition();
	GameConfig::MoveDirection getDirection();
	void setDirection(GameConfig::MoveDirection direction);
	BulletType getBulletType();

	void move();

private:

	void determineMoveStrategy();

	const float BULLET_SPEED = 10;
	
	std::unique_ptr<IMoveStrategy> m_moveStrategy;
	Position m_position;
	GameConfig::MoveDirection m_direction;
	BulletType m_bulletType;
};