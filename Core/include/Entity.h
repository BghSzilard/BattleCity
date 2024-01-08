#pragma once

namespace BattleCity::GameLogic
{
  class Entity
  {
  public:
      enum class MoveDirection {
          UP = 0,
          DOWN = 180,
          LEFT = 270,
          RIGHT = 90
      };

  	bool isAlive;
  };
}