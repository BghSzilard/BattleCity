//
// Created by Botond on 08.01.2024.
//

#include "TextLevelReader.h"

namespace BattleCity::GameLogic
{
  Level TextLevelReader::readLevel(std::string path)
  {
      m_textFile.open(path);

      assert(m_textFile.is_open());

      int height, width;
      m_textFile >> height >> width;

      Matrix<int> mapData(height, std::vector<int>(width));

      for (int i = 0; i < height; ++i)
      {
          for (int j = 0; j < width; ++j)
          {
              m_textFile >> mapData[i][j];
          }
      }

      Map map(mapData);

      int nrEnemyTanks;
      m_textFile >> nrEnemyTanks;
      Level::TankCollection enemyTanks(nrEnemyTanks);
      for(int i = 0; i < nrEnemyTanks; i++)
      {
          int xPos, yPos, direction;
          m_textFile >> xPos >> yPos >> direction;
          enemyTanks[i] = std::make_shared<Tank>(xPos, yPos, static_cast<Tank::MoveDirection>(direction));
      }

      m_textFile.close();

      return Level(map, enemyTanks);
  }
}
