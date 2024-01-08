#pragma once

#include "Level.h"

namespace BattleCity::GameLogic
{
  class ILevelFactory
  {
  public:
      virtual Level createLevel(int levelNumber) = 0;
  };
}
