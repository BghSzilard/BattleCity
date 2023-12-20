#include <cassert>
#include "TextureManager.h"

sf::Texture BattleCity::TextureManager::getTilesTexture()
{
    bool readSuccess = m_tilesTexture.loadFromFile(GameConfig::TILES_TEXTURE_PATH);

    assert(readSuccess);

    return m_tilesTexture;
}

sf::Texture BattleCity::TextureManager::getBulletTexture()
{
    bool readSuccess = m_bulletTexture.loadFromFile(GameConfig::BULLET_TEXTURE_PATH);

    assert(readSuccess);

    return m_bulletTexture;
}