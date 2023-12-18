#include "TileMap.h"
//#include "Map.h"
//
//Map::Map(Sprite& spr, Timer& FPSclock, sf::RenderWindow& window) : spr{ spr }, GameClock{ FPSclock }, window{ window } {
//	
//}
//
//
//void Map::draw(sf::RenderTarget& window, sf::RenderStates) const
//{
//	
//}

namespace BattleCity::SFML
{
    TileMap::TileMap(TextureManager& textureManager)
            : m_mapModel()
            , m_tileset(textureManager.getTilesTexture())
    {
        m_vertices.setPrimitiveType(sf::Triangles);

        initMap();
        initMapTexture();
    }

    // error/exception handling
    void TileMap::initMap()
    {
        size_t width = m_mapModel.getWidth();
        size_t height = m_mapModel.getHeight();

        // multiply by 6, because every tile has 2 triangles (triangle has 3 points 2*3=6)
        m_vertices.resize(width * height * 6);

        for (unsigned int i = 0; i < height; ++i)
            for (unsigned int j = 0; j < width; ++j)
            {
                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex *triangles = &m_vertices[(i * width + j) * 6];

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f((float) j * GameConfig::MAP_TILE_SIZE, (float) i * GameConfig::MAP_TILE_SIZE);
                triangles[1].position = sf::Vector2f((float) (j + 1) * GameConfig::MAP_TILE_SIZE, (float) i * GameConfig::MAP_TILE_SIZE);
                triangles[2].position = sf::Vector2f((float) j * GameConfig::MAP_TILE_SIZE, (float) (i + 1) * GameConfig::MAP_TILE_SIZE);
                triangles[3].position = sf::Vector2f((float) j * GameConfig::MAP_TILE_SIZE, (float) (i + 1) * GameConfig::MAP_TILE_SIZE);
                triangles[4].position = sf::Vector2f((float) (j + 1) * GameConfig::MAP_TILE_SIZE, (float) i * GameConfig::MAP_TILE_SIZE);
                triangles[5].position = sf::Vector2f((float) (j + 1) * GameConfig::MAP_TILE_SIZE, (float) (i + 1) * GameConfig::MAP_TILE_SIZE);
            }
    }

    void TileMap::initMapTexture()
    {
        size_t width = m_mapModel.getWidth();
        size_t height = m_mapModel.getHeight();

        for (unsigned int i = 0; i < height; ++i)
            for (unsigned int j = 0; j < width; ++j)
            {
                // get the current tile number
                int tileNumber = m_mapModel.at(i, j);

                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex *triangles = &m_vertices[(i * width + j) * 6];

                // divide by 32 because tile textures in tileset.png are 32x32 each
                const uint32_t scaleFactor = GameConfig::MAP_TILE_SIZE / 32;

                // define the 6 matching texture coordinates
                triangles[0].texCoords = sf::Vector2f((float) tileNumber * GameConfig::MAP_TILE_SIZE / scaleFactor, 0.f);
                triangles[1].texCoords = sf::Vector2f((float) (tileNumber + 1) * GameConfig::MAP_TILE_SIZE / scaleFactor, 0.f);
                triangles[2].texCoords = sf::Vector2f((float) tileNumber * GameConfig::MAP_TILE_SIZE / scaleFactor,
                                                      (float) GameConfig::MAP_TILE_SIZE / scaleFactor);
                triangles[3].texCoords = sf::Vector2f((float) tileNumber * GameConfig::MAP_TILE_SIZE / scaleFactor,
                                                      (float) GameConfig::MAP_TILE_SIZE / scaleFactor);
                triangles[4].texCoords = sf::Vector2f((float) (tileNumber + 1) * GameConfig::MAP_TILE_SIZE / scaleFactor, 0.f);
                triangles[5].texCoords = sf::Vector2f((float) (tileNumber + 1) * GameConfig::MAP_TILE_SIZE / scaleFactor,
                                                      (float) GameConfig::MAP_TILE_SIZE / scaleFactor);
            }
    }

    void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
}