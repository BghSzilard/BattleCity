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

namespace BattleCity
{
    namespace SFML
    {
        TileMap::TileMap()
        {
            m_vertices.setPrimitiveType(sf::Triangles);
        }

        bool TileMap::load(const std::string& mapFilePath, const std::string& texturePath)
        {
            return setModel(mapFilePath) && setTexture(texturePath);
        }

        // error/exception handling
        bool TileMap::setModel(const std::string& mapPath)
        {
            bool fileRead = m_mapModel.readFromFile(mapPath);
            if (!fileRead)
                return false;

            size_t width = m_mapModel.getWidth();
            size_t height = m_mapModel.getHeight();
            
            // multiply by 6, because every tile has 2 triangles (triangle has 3 points 2*3=6)
            m_vertices.resize(width * height * 6);

            for (unsigned int i = 0; i < height; ++i)
                for (unsigned int j = 0; j < width; ++j)
                {
                    // get the current tile number
                    int tileNumber = m_mapModel.at(i, j);

                    // get a pointer to the triangles' vertices of the current tile
                    sf::Vertex* triangles = &m_vertices[(i * width + j) * 6];

                    // define the 6 corners of the two triangles
                    triangles[0].position = sf::Vector2f((float)j * kTileSize, (float)i * kTileSize);
                    triangles[1].position = sf::Vector2f((float)(j + 1) * kTileSize, (float)i * kTileSize);
                    triangles[2].position = sf::Vector2f((float)j * kTileSize, (float)(i + 1) * kTileSize);
                    triangles[3].position = sf::Vector2f((float)j * kTileSize, (float)(i + 1) * kTileSize);
                    triangles[4].position = sf::Vector2f((float)(j + 1) * kTileSize, (float)i * kTileSize);
                    triangles[5].position = sf::Vector2f((float)(j + 1) * kTileSize, (float)(i + 1) * kTileSize);
                }

            return true;
        }

        bool TileMap::setTexture(const std::string& texturePath)
        {
            if (!m_tileset.loadFromFile(texturePath))
                return false;

            size_t width = m_mapModel.getWidth();
            size_t height = m_mapModel.getHeight();

            for (unsigned int i = 0; i < height; ++i)
                for (unsigned int j = 0; j < width; ++j)
                {
                    // get the current tile number
                    int tileNumber = m_mapModel.at(i, j);

                    // get a pointer to the triangles' vertices of the current tile
                    sf::Vertex* triangles = &m_vertices[(i * width + j) * 6];

                    // divide by 32 because tile textures in tileset.png are 32x32 each
                    const uint32_t scaleFactor = kTileSize / 32;

                    // define the 6 matching texture coordinates
                    triangles[0].texCoords = sf::Vector2f((float)tileNumber * kTileSize / scaleFactor, 0.f);
                    triangles[1].texCoords = sf::Vector2f((float)(tileNumber + 1) * kTileSize / scaleFactor, 0.f);
                    triangles[2].texCoords = sf::Vector2f((float)tileNumber * kTileSize / scaleFactor, (float)kTileSize / scaleFactor);
                    triangles[3].texCoords = sf::Vector2f((float)tileNumber * kTileSize / scaleFactor, (float)kTileSize / scaleFactor);
                    triangles[4].texCoords = sf::Vector2f((float)(tileNumber + 1) * kTileSize / scaleFactor, 0.f);
                    triangles[5].texCoords = sf::Vector2f((float)(tileNumber + 1) * kTileSize / scaleFactor, (float)kTileSize / scaleFactor);
                }

            return true;
        }

        void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &m_tileset;

            // draw the vertex array
            target.draw(m_vertices, states);
        }
    }
}