#pragma once

#include "ILevelReader.h"

#include <fstream>

namespace BattleCity::GameLogic
{
  class TextLevelReader : public ILevelReader
  {
  public:
      //TODO: Maybe TextLevelReader should have as constructor parameter the path to the folder containing the level files
      TextLevelReader() = default;

      Level readLevel(std::string path) override;

  private:
      std::ifstream m_textFile;
  };
}
