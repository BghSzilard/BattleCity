#pragma once



#include "ITankMovementStrategy.h"
#include "GameConfig.h"
#include "Entity.h"


namespace BattleCity::GameLogic
{
  class TankMovementStrategy : public ITankMovementStrategy
  {
  public:
      TankMovementStrategy();

      Position move() override;
      Entity::MoveDirection getMoveDirection();

  private:
      Position m_prevPos;
      Entity::MoveDirection m_direction;
  };
}
