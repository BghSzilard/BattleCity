#pragma once

#include <string>
#include <fstream>

#include "DEFINITIONS.h"
#include "GameConfig.h"

#include "FileHandler.h"

namespace BattleCity::GameLogic
{
    class Map
    {
    public:
        Map();

        // maybe create StreamReader/FileStreamReader (idk)

        [[nodiscard]] size_t getWidth() const;

        [[nodiscard]] size_t getHeight() const;

        [[nodiscard]] int at(size_t row, size_t column) const;

        //TODO: Values of matrix must be modifiable
    private:

        //Maybe create a "global" FileHandler and reference that from every class that needs it
        FileHandler m_fileHandler;

        Matrix<int> m_map;
    };
}
