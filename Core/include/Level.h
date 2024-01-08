//
// Created by Botond on 08.01.2024.
//

#pragma once

#include "Map.h"
#include "Tank.h"

#include <vector>
#include <memory>

namespace BattleCity::GameLogic
{
  class Level
  {
  public:
      using TankPtr         = std::shared_ptr<Tank>;
      using TankCollection  = std::vector<TankPtr>;

      Level(Map map, TankCollection  enemyTanks);

      //TODO: expose Map and Tank collection
      Map& getMap();
  private:
      Map m_map;
      TankCollection m_enemyTanks;
  };
}
