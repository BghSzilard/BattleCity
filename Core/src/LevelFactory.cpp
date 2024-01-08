#include "LevelFactory.h"
#include "TextLevelReader.h"

namespace BattleCity::GameLogic
{
    LevelFactory::LevelFactory()
            : m_levelReader(std::make_unique<TextLevelReader>())
    {

    }

    Level LevelFactory::createLevel(int levelNumber)
    {
        return m_levelReader->readLevel(getLevelPath(levelNumber));
    }

    std::string LevelFactory::getLevelPath(int levelNumber)
    {
        return GameConfig::LEVEL_DIR_PATH + "level" + std::to_string(levelNumber) + ".txt";
    }

}
