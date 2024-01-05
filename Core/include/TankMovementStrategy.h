#pragma once

#include "ITankMovementStrategy.h"
#include "GameConfig.h"

class TankMovementStrategy : public ITankMovementStrategy
{
public:
    TankMovementStrategy();

    Position move() override;
    GameConfig::MoveDirection getMoveDirection();

private:
    Position m_prevPos;
    GameConfig::MoveDirection m_direction;
};
