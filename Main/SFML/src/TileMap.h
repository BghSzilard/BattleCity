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
        const uint32_t kTileSize = 64;

    public:

        TileMap();

        void initMap();

        void initMapTexture();


    private:

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::VertexArray m_vertices;
        sf::Texture m_tileset;

        TextureManager m_textureManager;

        GameLogic::Map m_mapModel;
    };
}