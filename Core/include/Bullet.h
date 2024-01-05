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
	int getWidth() const;
	int getHeight() const;
	GameConfig::MoveDirection getDirection() const;
	void setDirection(GameConfig::MoveDirection direction);
	BulletType getBulletType() const;
	float getSpeed() const;


	void move();

    ~Bullet();
private:

	void determineMoveStrategy();
	
	IMoveStrategy* m_moveStrategy;
	int m_height, m_width;

	Position m_position;
	GameConfig::MoveDirection m_direction;
	BulletType m_bulletType;
};