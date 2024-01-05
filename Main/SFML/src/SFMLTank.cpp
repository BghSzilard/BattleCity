//
// Created by Botond on 18.12.2023.
//

#include "SFMLTank.h"

BattleCity::SFML::SFMLTank::SFMLTank(TextureManager& textureManager, sf::Vector2f position)
        : m_tankModel(position.x, position.y),
        m_textureManager(textureManager)
        , m_tankTexture(textureManager.getTankTexture())
{
    m_tankSprite.setTexture(m_tankTexture);

    m_tankSprite.setOrigin(sf::Vector2f(m_tankSprite.getLocalBounds().width , m_tankSprite.getLocalBounds().height)/2.f);

    //texture is 512x512, and we want the tank to be the same size as the tiles (64x64) => scale by a factor of 1/8=0.125
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
//    m_tankSprite.move(x, y);
    m_tankSprite.move(x, y);
}

void BattleCity::SFML::SFMLTank::setOnBulletShot(BattleCity::SFML::SFMLTank::OnBulletShotCallback &&callback)
{
    onBulletShot = std::move(callback);
}

void BattleCity::SFML::SFMLTank::shootBullet()
{
    // ... do some shit
    SFMLBullet bullet{ m_textureManager, m_tankModel.getXPosition(), m_tankModel.getYPosition(), getMoveDirection(), Bullet::BulletType::PlayerBullet };
    if (onBulletShot) {
        onBulletShot(*this, std::move(bullet));
    }
}

GameConfig::MoveDirection BattleCity::SFML::SFMLTank::getMoveDirection()
{
    return m_tankModel.getTankDirection();
}

void BattleCity::SFML::SFMLTank::setMoveDirection(GameConfig::MoveDirection direction)
{
    m_tankModel.setTankDirection(direction);
    m_tankSprite.setRotation((float)static_cast<int>(direction));
}
