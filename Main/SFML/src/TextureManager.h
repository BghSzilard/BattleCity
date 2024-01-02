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

    private:
        sf::Texture m_tilesTexture;
        sf::Texture m_bulletTexture;
    };
}
