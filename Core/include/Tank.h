//
// Created by Botond on 18.12.2023.
//

#pragma once

#include "GameConfig.h"

#include <cassert>

namespace BattleCity::GameLogic
{
    class Tank
    {
    public:
        Tank();

        void setPosition(int x, int y);

        [[nodiscard]] int getXPosition() const;

        [[nodiscard]] int getYPosition() const;

    private:
        int m_xPos, m_yPos;
    };
}
