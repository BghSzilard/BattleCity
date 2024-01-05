#pragma once

#include "GameConfig.h"
#include "Position.h"
#include "IMoveStrategy.h"
#include "Entity.h"

#include <memory>

class Bullet : public Entity
{
public:

	//for collision detection: player's bullets should kill enemy tanks, but enemy tanks shooting each other should not effect them
	enum class BulletType
	{
		PlayerBullet,
		EnemyBullet
	};

	Bullet(Position position, GameConfig::MoveDirection direction, BulletType bulletType);

	Position getPosition() const;
	GameConfig::MoveDirection getDirection();
	BulletType getBulletType();
	int getWidth();
	int getHeight();

	void move();

private:

	void determineMoveStrategy();
	
	int m_height, m_width;

	std::unique_ptr<IMoveStrategy> m_moveStrategy;
	Position m_position;
	GameConfig::MoveDirection m_direction;
	BulletType m_bulletType;
};