//
// Created by Botond on 18.12.2023.
//

#pragma once

#include <SFML/Graphics.hpp>

#include "Tank.h"
#include "TextureManager.h"

namespace BattleCity::SFML
{
    class SFMLTank : public sf::Drawable, public sf::Transformable
    {
    public:
        explicit SFMLTank(TextureManager& textureManager);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        void initTankTexture();

        GameLogic::Tank m_tankModel;

        sf::Texture& m_tankTexture;
        sf::Sprite m_tankSprite;
    };
}
