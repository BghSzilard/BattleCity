//
// Created by Botond on 18.12.2023.
//

#include "Tank.h"

BattleCity::GameLogic::Tank::Tank()
    : m_xPos(GameConfig::INITIAL_TANK_POS_X)
    , m_yPos(GameConfig::INITIAL_TANK_POS_Y)
    , m_tankSpeed(GameConfig::TANK_SPEED)
{

}
BattleCity::GameLogic::Tank::Tank(float x, float y)
    : m_tankSpeed(GameConfig::TANK_SPEED)
    , m_xPos(x)
    , m_yPos(y)
    , m_tankDirection(GameConfig::MoveDirection::DOWN)
    , m_width(64)
    , m_height(64)
{}

void BattleCity::GameLogic::Tank::setPosition(float x, float y)
{
    // TODO: asserts
    assert(0 <= x);
    assert(0 <= y);

    m_xPos = x;
    m_yPos = y;
}

float BattleCity::GameLogic::Tank::getXPosition() const
{
    return m_xPos;
}

float BattleCity::GameLogic::Tank::getYPosition() const
{
    return m_yPos;
}

int BattleCity::GameLogic::Tank::getTankSpeed() const
{
    return m_tankSpeed;
}

int BattleCity::GameLogic::Tank::getHeight() const
{
    return m_height;
}

int BattleCity::GameLogic::Tank::getWidth() const
{
    return m_width;
}
GameConfig::MoveDirection BattleCity::GameLogic::Tank::getTankDirection() const
{
    return m_tankDirection;
}

void BattleCity::GameLogic::Tank::setTankDirection(GameConfig::MoveDirection mTankDirection)
{
    m_tankDirection = mTankDirection;
}

