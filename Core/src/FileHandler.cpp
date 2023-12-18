#include "FileHandler.h"

BattleCity::Matrix<int> BattleCity::FileHandler::getMapData()
{
    m_fileStream.open(GameConfig::MAP_FILE_PATH);

    assert(m_fileStream.is_open());

    int height, width;
    m_fileStream >> height >> width;

    Matrix<int> mapData(height, std::vector<int>(width));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            m_fileStream >> mapData[i][j];
        }
    }

    m_fileStream.close();

    assert(m_fileStream.eof());

    return mapData;
}
