#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "DEFINITIONS.h"

#include "Map.h"
#include "TextureManager.h"

namespace BattleCity::SFML
{
    class TileMap : public sf::Drawable, public sf::Transformable
    {
    private:

    public:

        explicit TileMap(TextureManager& manager);

        void initMap();

        void initMapTexture();


    private:

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::VertexArray m_vertices;
        sf::Texture& m_tileset;

        GameLogic::Map m_mapModel;
    };
}