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
    m_tankSprite.setOrigin(sf::Vector2f(m_tankSprite.getLocalBounds().width , m_tankSprite.getLocalBounds().height)/2.f);
    this->setOrigin(sf::Vector2f(m_tankSprite.getLocalBounds().width , m_tankSprite.getLocalBounds().height)/2.f);

    m_tankSprite.setScale(0.125f, 0.125f);
    m_tankSprite.setPosition(m_tankModel.getXPosition(), m_tankModel.getYPosition());
    this->setPosition(m_tankModel.getXPosition(), m_tankModel.getYPosition());
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

void BattleCity::SFML::SFMLTank::moveTank(float x, float y)
{

    m_tankModel.setPosition(m_tankModel.getXPosition()+x, m_tankModel.getYPosition()+y);
    this->move(x, y);
}
