//
// Created by Botond on 18.12.2023.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Tank.h"
#include "TextureManager.h"
#include "SFMLBullet.h"

#include <functional>

namespace BattleCity::SFML
{
    class SFMLTank : public sf::Drawable, public sf::Transformable
    {
    public:
        using OnBulletShotCallback = std::function<void(const SFMLTank&, SFMLBullet&& bullet)>;

        OnBulletShotCallback onBulletShot;

        void setOnBulletShot(OnBulletShotCallback&& callback);

        void shootBullet();

        explicit SFMLTank(TextureManager& textureManager, sf::Vector2f position);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        // this function moves the tank relative to its current position
        void moveTank(float x, float y);

        GameLogic::Tank::MoveDirection getMoveDirection();
        void setMoveDirection(GameLogic::Tank::MoveDirection direction);
    private:
        void initTankTexture();

        TextureManager& m_textureManager;

        GameLogic::Tank m_tankModel;

        sf::Texture& m_tankTexture;
        sf::Sprite m_tankSprite;
    };
}
