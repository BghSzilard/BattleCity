//
// Created by Botond on 18.12.2023.
//

#pragma once

#include "GameConfig.h"
#include "Entity.h"
#include "Bullet.h"
#include "ITankMovementStrategy.h"

#include <cassert>
#include <functional>

#include <memory>

namespace BattleCity::GameLogic
{
    class Tank : public Entity
    {
    public:
        Tank(float x, float y);

        void setPosition(float x, float y);

        [[nodiscard]] float getXPosition() const;

        [[nodiscard]] float getYPosition() const;

        [[nodiscard]] int getHeight() const;

        [[nodiscard]] int getWidth() const;

        [[nodiscard]] int getTankSpeed() const;
        // this function moves tank relative to current position

        void moveTank(float x, float y);


        using OnBulletShotCallback = std::function<void(const Tank&, std::shared_ptr<Bullet> bullet)>;
        void setOnBulletShot(OnBulletShotCallback&& callback);

        void shootBullet();

        [[nodiscard]] GameConfig::MoveDirection getTankDirection() const;

        void setTankDirection(GameConfig::MoveDirection mTankDirection);

    private:
        OnBulletShotCallback onBulletShot;
        float m_xPos, m_yPos;
        int m_width, m_height;
        int m_tankSpeed;
        GameConfig::MoveDirection m_tankDirection;

        ITankMovementStrategy* m_tankMovementStrategy;
    };
}
