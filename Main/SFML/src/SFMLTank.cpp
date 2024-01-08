//
// Created by Botond on 18.12.2023.
//

#include "SFMLTank.h"
#include <iostream>

namespace BattleCity::SFML
{
	SFMLTank::SFMLTank(TextureManager& textureManager, std::shared_ptr<GameLogic::Tank>& tank)
		: m_tankModel(tank),
		m_textureManager(textureManager),
		m_tankTexture(textureManager.getTankTexture()) {

		m_tankSprite.setTexture(m_tankTexture);
		//texture is 512x512, and we want the tank to be the same size as the tiles (64x64) => scale by a factor of 1/8=0.125
		m_tankSprite.setScale(0.125f, 0.125f);

		m_tankSprite.setOrigin(sf::Vector2f(m_tankSprite.getLocalBounds().width, m_tankSprite.getLocalBounds().height) / 2.f);
	}

	void BattleCity::SFML::SFMLTank::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		//states.transform.scale(0.125f, 0.125f);
		//states.transform.rotate((float)static_cast<int>(m_tankModel->getTankDirection()));
		m_tankSprite.setRotation((float)static_cast<int>(m_tankModel->getTankDirection()));
		states.transform.translate(m_tankModel->getXPosition(), m_tankModel->getYPosition());

		// apply the texture
		//states.texture = &m_tankTexture;

		//std::cout << static_cast<int>(m_tankModel->getTankDirection()) << ' '
		//	<< m_tankModel->getXPosition() << ' '
		//	<< m_tankModel->getYPosition() << ' ' << std::endl;
		// you may also override states.shader or states.blendMode if you want

			// draw the vertex array
		target.draw(m_tankSprite, states);
	}

	std::shared_ptr<BattleCity::GameLogic::Tank> BattleCity::SFML::SFMLTank::tank()
	{
		return m_tankModel;
	}

	void BattleCity::SFML::SFMLTank::initTankTexture()
	{

	}
}