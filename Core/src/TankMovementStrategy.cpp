//
// Created by Botond on 05.01.2024.
//

#include "TankMovementStrategy.h"

namespace BattleCity::GameLogic
{
  TankMovementStrategy::TankMovementStrategy()
      : m_prevPos(Position(0 , 0)),
      m_direction(Entity::MoveDirection::UP)
  {

  }
}
