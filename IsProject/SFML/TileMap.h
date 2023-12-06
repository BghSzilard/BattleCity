#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "../DEFINITIONS.h"

#include "../GameLogic/Map.h"

namespace BattleCity
{
    namespace SFML
    {
        class TileMap : public sf::Drawable, public sf::Transformable
        {
        public:

            bool load(const std::string& tilesetPath, sf::Vector2u tileSize, GameLogic::Map map);

        private:

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::VertexArray m_vertices;
            sf::Texture m_tileset;
        };
    }
}