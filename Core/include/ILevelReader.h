//
// Created by Botond on 08.01.2024.
//

#pragma once


#include "Level.h"

namespace BattleCity::GameLogic
{
  class ILevelReader
  {
  public:
      virtual Level readLevel(std::string path) = 0;
  };
}
