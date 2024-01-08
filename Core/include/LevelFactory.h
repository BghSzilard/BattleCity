//
// Created by Botond on 08.01.2024.
//

#pragma once

#include "ILevelFactory.h"
#include "ILevelReader.h"

#include <string_view>

namespace BattleCity::GameLogic
{
  class LevelFactory : public ILevelFactory
  {
  public:
      //TODO: Inject ILevelReader
      LevelFactory();

      //TODO: Pointer to ILevel for polymorphism
      Level createLevel(int levelNumber) override;

      std::string getLevelPath(int levelNumber);
  private:
      std::unique_ptr<ILevelReader> m_levelReader;
  };

}