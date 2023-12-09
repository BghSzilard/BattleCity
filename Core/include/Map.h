#pragma once

#include <string>
#include <fstream>

#include "DEFINITIONS.h"

namespace BattleCity
{
    namespace GameLogic
    {
        class Map
        {
        public:
            Map() = default;

            // maybe create StreamReader->FileStreamReader
            bool readFromFile(const std::string& );

            const size_t getWidth() const;
            const size_t getHeight() const;

            const int at(size_t row, size_t column) const;

            //TODO: Values of matrix must be modifiable
        private:
            Matrix<int> m_map;
        };
    }
}
