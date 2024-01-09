//
// Created by Botond on 08.01.2024.
//

#include "Level.h"

#include <utility>

namespace BattleCity::GameLogic
{
  Level::Level(Map  map, TankCollection enemyTanks)
  : m_map(std::move(map))
  , m_enemyTanks(std::move(enemyTanks))
  {

  }

    Map &Level::getMap()
    {
        return m_map;
    }

    Level::TankCollection &Level::getEnemyTanks()
    {
        return m_enemyTanks;
    }
}
