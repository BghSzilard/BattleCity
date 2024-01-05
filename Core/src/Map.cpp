#include "Map.h"

namespace BattleCity::GameLogic
{
    Map::Map(Matrix<int> tiles)
    {
        m_map = std::move(tiles);
    }

    size_t Map::getWidth() const
    {
        return m_map[0].size();
    }

    size_t Map::getHeight() const
    {
        return m_map.size();
    }

    int Map::at(size_t row, size_t column) const
    {
        // exception handling

        if (row >= m_map.size() || column >= m_map[0].size())
            return -1;

        return m_map[row][column];
    }

    int& Map::at(size_t row, size_t column)
    {
        return m_map[row][column];
    }

}