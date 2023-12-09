#include "Map.h"

namespace BattleCity
{
    namespace GameLogic
    {
        bool Map::readFromFile(const std::string& filePath)
        {
            std::ifstream file(filePath);

            if (!file.is_open()) {
                return false;
            }

            int height, width;
            file >> height >> width;

            m_map.resize(height, std::vector<int>(width));

            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    file >> m_map[i][j];
                }
            }

            file.close();
            return true;
        }
        const size_t Map::getWidth() const
        {
            return m_map[0].size();
        }

        const size_t Map::getHeight() const
        {
            return m_map.size();
        }

        const int Map::at(size_t row, size_t column) const
        {
            // exception handling

            if (row >= m_map.size() || column >= m_map[0].size())
                return -1;

            return m_map[row][column];
        }
    }
}