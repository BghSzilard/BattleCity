#pragma once

#include <fstream>
#include <cassert>

#include "DEFINITIONS.h"
#include "GameConfig.h"

namespace BattleCity
{
    // or resource handler, idk
  class FileHandler
  {
  public:
      FileHandler() = default;

      [[nodiscard]] Matrix<int> getMapData();

  private:
      std::ifstream m_fileStream;
  };
}
