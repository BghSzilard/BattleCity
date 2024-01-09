//
// Created by Botond on 18.12.2023.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Tank.h"
#include "TextureManager.h"
#include "SFMLBullet.h"

#include <functional>
#include <memory>

namespace BattleCity::SFML
{
    class SFMLTank : public sf::Drawable
    {
    public:
        explicit SFMLTank(TextureManager& textureManager, std::shared_ptr<GameLogic::Tank>& tank, sf::Color color = sf::Color::White);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::shared_ptr<GameLogic::Tank> tank();

    private:
        void initTankTexture();

        TextureManager& m_textureManager;

        std::shared_ptr<GameLogic::Tank> m_tankModel;

        sf::Texture& m_tankTexture;
        mutable sf::Sprite m_tankSprite;
    };
}
