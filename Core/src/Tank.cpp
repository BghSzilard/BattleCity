//
// Created by Botond on 18.12.2023.
//

#include "Tank.h"

BattleCity::GameLogic::Tank::Tank()
    : m_xPos(GameConfig::INITIAL_TANK_POS_X)
    , m_yPos(GameConfig::INITIAL_TANK_POS_Y)
{

}

void BattleCity::GameLogic::Tank::setPosition(int x, int y)
{
    // TODO: asserts
    assert(0 <= x);
    assert(0 <= y);

    m_xPos = x;
    m_yPos = y;
}

int BattleCity::GameLogic::Tank::getXPosition() const
{
    return m_xPos;
}

int BattleCity::GameLogic::Tank::getYPosition() const
{
    return m_yPos;
}

