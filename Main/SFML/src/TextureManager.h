#pragma once

#include "GameConfig.h"

#include <optional>

#include "SFML/Graphics.hpp"

namespace BattleCity
{
    class TextureManager
    {
    public:
        TextureManager() = default;

        sf::Texture getBulletTexture();
        sf::Texture getEagleTexture();
        sf::Texture& getTilesTexture();

        sf::Texture& getTankTexture();

    private:
        sf::Texture m_bulletTexture;
        sf::Texture m_eagleTexture;
        std::optional<sf::Texture> m_tilesTexture;
        std::optional<sf::Texture> m_tankTexture;
    };
}
