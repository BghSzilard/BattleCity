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

        sf::Texture& getTilesTexture();

        sf::Texture& getTankTexture();

    private:
        std::optional<sf::Texture> m_tilesTexture;
        std::optional<sf::Texture> m_tankTexture;
    };
}
