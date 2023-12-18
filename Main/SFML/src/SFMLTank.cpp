//
// Created by Botond on 18.12.2023.
//

#include "SFMLTank.h"

BattleCity::SFML::SFMLTank::SFMLTank(TextureManager& textureManager)
        : m_tankModel()
        , m_tankTexture(textureManager.getTankTexture())
{
    // define the position of the triangle's points
    m_tankSprite.setTexture(m_tankTexture);

    //texture is 512x512, and we want the tank to be the same size as the tiles (64x64) => scale by a factor of 1/8=0.125
    m_tankSprite.setScale(0.125f, 0.125f);
}

void BattleCity::SFML::SFMLTank::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = &m_tankTexture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(m_tankSprite, states);
}

void BattleCity::SFML::SFMLTank::initTankTexture()
{

}
