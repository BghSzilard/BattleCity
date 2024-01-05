//
// Created by Botond on 18.12.2023.
//

#pragma once

#include "GameConfig.h"
#include "Entity.h"

#include <cassert>

namespace BattleCity::GameLogic
{
    class Tank : public Entity
    {
    public:
        Tank();

        void setPosition(float x, float y);

        [[nodiscard]] float getXPosition() const;

        [[nodiscard]] float getYPosition() const;

        [[nodiscard]] int getHeight() const;

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getTankSpeed() const;
        // this function moves tank relative to current position
    private:
        float m_xPos, m_yPos;
        int m_width, m_height;
        int m_tankSpeed;
        GameConfig::MoveDirection m_tankDirection;
    public:
        [[nodiscard]] GameConfig::MoveDirection getTankDirection() const;

        void setTankDirection(GameConfig::MoveDirection mTankDirection);
    };
}
