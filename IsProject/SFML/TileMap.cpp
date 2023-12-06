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
        bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, GameLogic::Map map)
        {
            size_t width = map.getWidth();
            size_t height = map.getHeight();

            // load the tileset texture
            if (!m_tileset.loadFromFile(tileset))
                return false;

            // resize the vertex array to fit the level size
            m_vertices.setPrimitiveType(sf::Triangles);

            // multiply by 6, because every tile has 2 triangles (triangle has 3 points 2*3=6)
            m_vertices.resize(width * height * 6);

            // populate the vertex array, with two triangles per tile
            for (unsigned int i = 0; i < height; ++i)
                for (unsigned int j = 0; j < width; ++j)
                {
                    // get the current tile number
                    int tileNumber = map.at(i, j);

                    // get a pointer to the triangles' vertices of the current tile
                    sf::Vertex* triangles = &m_vertices[(i * width + j) * 6];

                    // define the 6 corners of the two triangles
                    triangles[0].position = sf::Vector2f(j * tileSize.x, i * tileSize.y);
                    triangles[1].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                    triangles[2].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                    triangles[3].position = sf::Vector2f(j * tileSize.x, (i + 1) * tileSize.y);
                    triangles[4].position = sf::Vector2f((j + 1) * tileSize.x, i * tileSize.y);
                    triangles[5].position = sf::Vector2f((j + 1) * tileSize.x, (i + 1) * tileSize.y);


                    int scaleFactor = tileSize.x / 32;

                    // define the 6 matching texture coordinates
                    triangles[0].texCoords = sf::Vector2f(tileNumber * tileSize.x / scaleFactor, 0);
                    triangles[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x / scaleFactor, 0);
                    triangles[2].texCoords = sf::Vector2f(tileNumber * tileSize.x / scaleFactor, tileSize.y / scaleFactor);
                    triangles[3].texCoords = sf::Vector2f(tileNumber * tileSize.x / scaleFactor, tileSize.y / scaleFactor);
                    triangles[4].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x / scaleFactor, 0);
                    triangles[5].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x / scaleFactor, tileSize.y / scaleFactor);
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