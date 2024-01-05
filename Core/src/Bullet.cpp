#include "Bullet.h"
#include "MoveDownwardStrategy.h"
#include "MoveUpwardStrategy.h"
#include "MoveLeftwardStrategy.h"
#include "MoveRightwardStrategy.h"

Bullet::Bullet(Position position, GameConfig::MoveDirection direction, BulletType bulletType)
: m_position(position)
{
	m_direction = direction;
	m_bulletType = bulletType;

	determineMoveStrategy();
}

Bullet::BulletType Bullet::getBulletType() const
{
	return m_bulletType;
}

void Bullet::determineMoveStrategy()
{
	switch (m_direction)
	{
	case GameConfig::MoveDirection::LEFT:
		m_moveStrategy = new MoveLeftwardStrategy();
		break;
	case GameConfig::MoveDirection::RIGHT:
		m_moveStrategy = new MoveRightwardStrategy();
		break;
	case GameConfig::MoveDirection::UP:
		m_moveStrategy = new MoveUpwardStrategy();
		break;
	case GameConfig::MoveDirection::DOWN:
		m_moveStrategy = new MoveDownwardStrategy();
		break;
	}
}

void Bullet::move()
{
	m_position = m_moveStrategy->move(m_position, GameConfig::BULLET_SPEED);
}

Position Bullet::getPosition() const
{
	return m_position;
}

GameConfig::MoveDirection Bullet::getDirection() const
{
	return m_direction;
}


int Bullet::getWidth() const
{
	return m_width;
}

int Bullet::getHeight() const
{
	return m_height;
}

void Bullet::setDirection(GameConfig::MoveDirection direction)
{
	m_direction = direction;
	determineMoveStrategy();
}

float Bullet::getSpeed() const
{
	return GameConfig::BULLET_SPEED;
}



Bullet::~Bullet()
{
    // can't delete...
}
