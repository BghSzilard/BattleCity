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
        private:
            const uint32_t kTileSize = 64;

        public:

            TileMap();

            bool load(const std::string&, const std::string&);
            bool setModel(const std::string&);
            bool setTexture(const std::string&);


        private:

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::VertexArray m_vertices;
            sf::Texture m_tileset;
            GameLogic::Map m_mapModel;
        };
    }
}