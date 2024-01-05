#pragma once

#include <string>
#include <fstream>
#include <memory>

#include "DEFINITIONS.h"
#include "GameConfig.h"

#include "FileHandler.h"

namespace BattleCity::GameLogic
{
    class Map
    {
    public:
        Map(Matrix<int> tiles);

        // maybe create StreamReader/FileStreamReader (idk)

        [[nodiscard]] size_t getWidth() const;

        [[nodiscard]] size_t getHeight() const;

        [[nodiscard]] int at(size_t row, size_t column) const;

        [[nodiscard]] int& at(size_t row, size_t column);

        //TODO: Values of matrix must be modifiable
    private:
        Matrix<int> m_map;
    };
}
