//
// Created by Botond on 18.12.2023.
//

#include "Tank.h"

namespace BattleCity::GameLogic
{
  Tank::Tank(float x, float y, MoveDirection direction)
      : Entity()
      , m_tankSpeed(GameConfig::TANK_SPEED)
      , m_xPos(x)
      , m_yPos(y)
      , m_tankDirection(direction)
      , m_width(64)
      , m_height(64)
  {
      m_tankMovementStrategy = nullptr;
  }
  
  void Tank::setPosition(float x, float y)
  {
      assert(0 <= x);
      assert(0 <= y);
  
      m_xPos = x;
      m_yPos = y;
  }
  
  float Tank::getXPosition() const
  {
      return m_xPos;
  }
  
  float Tank::getYPosition() const
  {
      return m_yPos;
  }
  
  int Tank::getTankSpeed() const
  {
      return m_tankSpeed;
  }
  
  int Tank::getHeight() const
  {
      return m_height;
  }
  
  int Tank::getWidth() const
  {
      return m_width;
  }
  Tank::MoveDirection Tank::getTankDirection() const
  {
      return m_tankDirection;
  }
  
  void Tank::setTankDirection(Tank::MoveDirection mTankDirection)
  {
      m_tankDirection = mTankDirection;
  }
}

void BattleCity::GameLogic::Tank::setOnBulletShot(BattleCity::GameLogic::Tank::OnBulletShotCallback && callback)
{
    onBulletShot = std::move(callback);
}

void BattleCity::GameLogic::Tank::shootBullet()
{
    auto bullet = std::make_shared<Bullet>(Position{m_xPos, m_yPos}, getTankDirection(), Bullet::BulletType::PlayerBullet);
    if (onBulletShot) {
        onBulletShot(*this, bullet);
    }
}

void BattleCity::GameLogic::Tank::moveTank(float x, float y)
{
    setPosition(getXPosition() + x, getYPosition() + y);
}