#include <cassert>
#include "TextureManager.h"

sf::Texture& BattleCity::TextureManager::getTilesTexture()
{
    if (!m_tilesTexture.has_value())
    {
        sf::Texture texture;

        bool readSuccess = texture.loadFromFile(GameConfig::TILES_TEXTURE_PATH);

        assert(readSuccess);

        m_tilesTexture = texture;
    }

    return m_tilesTexture.value();
}

sf::Texture& BattleCity::TextureManager::getTankTexture()
{
    if (!m_tankTexture.has_value())
    {
        sf::Texture texture;

        bool readSuccess = texture.loadFromFile(GameConfig::TANK_TEXTURE_PATH);

        assert(readSuccess);

        m_tankTexture = texture;
    }

    return m_tankTexture.value();
}

