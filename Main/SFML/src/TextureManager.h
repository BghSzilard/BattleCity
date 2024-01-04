#pragma once

#include "GameConfig.h"

#include "SFML/Graphics.hpp"

namespace BattleCity
{
    class TextureManager
    {
    public:
        TextureManager() = default;

        sf::Texture getTilesTexture();
        sf::Texture getBulletTexture();
        sf::Texture getEagleTexture();

    private:
        sf::Texture m_tilesTexture;
        sf::Texture m_bulletTexture;
        sf::Texture m_eagleTexture;
    };
}
