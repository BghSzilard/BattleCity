#include "Bullet.h"
#include "MoveDownwardStrategy.h"
#include "MoveUpwardStrategy.h"
#include "MoveLeftwardStrategy.h"
#include "MoveRightwardStrategy.h"

namespace BattleCity::GameLogic
{
  Bullet::Bullet(Position position, Bullet::MoveDirection direction, BulletType bulletType)
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
  	case MoveDirection::LEFT:
  		m_moveStrategy = new MoveLeftwardStrategy();
  		break;
  	case MoveDirection::RIGHT:
  		m_moveStrategy = new MoveRightwardStrategy();
  		break;
  	case MoveDirection::UP:
  		m_moveStrategy = new MoveUpwardStrategy();
  		break;
  	case MoveDirection::DOWN:
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

  Bullet::MoveDirection Bullet::getDirection() const
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

  void Bullet::setDirection(MoveDirection direction)
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

}