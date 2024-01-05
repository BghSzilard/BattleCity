#include "GameLogic.h"

void BattleCity::GameLogic::GameLogic::checkEnemyTankPlayerBulletCollision()
{
	for (int i = 0; i < m_enemyTanks.size(); ++i)
	{
		for (int j = 0; j < m_playerBullets.size(); ++j)
		{
			int xTank = m_enemyTanks[i].getXPosition();
			int yTank = m_enemyTanks[i].getYPosition();
			int widthTank = m_enemyTanks[i].getWidth();
			int heightTank = m_enemyTanks[i].getHeight();

			int xBullet = m_playerBullets[j].getPosition().x;
			int yBullet = m_playerBullets[j].getPosition().y;
			int widthBullet= m_playerBullets[j].getWidth();
			int heightBullet = m_playerBullets[j].getHeight();

			if (isCollision(xTank, xBullet, widthTank, widthBullet, yTank, yBullet, heightTank, heightBullet))
			{
				m_enemyTanks.erase(m_enemyTanks.begin() + i);
				m_playerBullets.erase(m_playerBullets.begin() + j);
			}
		}
	}
}

bool BattleCity::GameLogic::GameLogic::isCollision(int x1, int x2, int width1, int width2, int y1, int y2, int height1, int height2)
{
	if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2) {
		return true; // Collision detected
	}

	return false; // No collision
}