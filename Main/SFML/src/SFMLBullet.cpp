#include "SFMLBullet.h"

namespace BattleCity::SFML
{
    SFMLBullet::SFMLBullet(BattleCity::TextureManager &textureManager, float startX, float startY,
                           GameLogic::Bullet::MoveDirection direction, GameLogic::Bullet::BulletType bulletType)
            : m_bullet(Position(startX, startY), direction, bulletType),
              m_textureManager(textureManager),
              m_texture(textureManager.getBulletTexture())
    {
        m_sprite.setPosition(startX, startY);
        //	setTexture();
        setSprite();
    }

    void SFMLBullet::move()
    {
        m_bullet.move();
        auto position = m_bullet.getPosition();
        m_sprite.setPosition(position.x, position.y);
    }

    Position SFMLBullet::getPosition() const
    {
        return m_bullet.getPosition();
    }

    GameLogic::Bullet::MoveDirection SFMLBullet::getDirection()
    {
        return m_bullet.getDirection();
    }

    GameLogic::Bullet::BulletType SFMLBullet::getBulletType()
    {
        return m_bullet.getBulletType();
    }

    void SFMLBullet::setTexture()
    {
        m_texture = m_textureManager.getBulletTexture();
    }

    void SFMLBullet::setSprite()
    {
        m_sprite.setTexture(m_texture);

        auto direction = m_bullet.getDirection();

        switch (direction)
        {
            case GameLogic::Bullet::MoveDirection::LEFT:
                m_sprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
                break;
            case GameLogic::Bullet::MoveDirection::RIGHT:
                m_sprite.setTextureRect(sf::IntRect(40, 0, 40, 40));
                break;
            case GameLogic::Bullet::MoveDirection::UP:
                m_sprite.setTextureRect(sf::IntRect(80, 0, 40, 40));
                break;
            case GameLogic::Bullet::MoveDirection::DOWN:
                m_sprite.setTextureRect(sf::IntRect(120, 0, 40, 40));
                break;
        }

    }

    void SFMLBullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        // apply the texture
        states.texture = &m_texture;

        target.draw(m_sprite, states);
    }
}
