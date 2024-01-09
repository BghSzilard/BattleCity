#pragma once

#include "ILevelReader.h"

#include <fstream>

namespace BattleCity::GameLogic
{
  class TextLevelReader : public ILevelReader
  {
  public:
      TextLevelReader() = default;

      Level readLevel(std::string path) override;

  private:
      std::ifstream m_textFile;
  };
}
