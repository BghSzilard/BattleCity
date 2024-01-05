#include "GameLogic.h"

#include <algorithm>

void BattleCity::GameLogic::GameLogic::checkEnemyTankPlayerBulletCollision()
{

	auto& tanks = m_enemyTanks;
	auto& bullets = m_playerBullets;

	for (int i = 0; i < tanks.size(); ++i)
	{
		for (int j = 0; j < bullets.size(); ++j)
		{
			int xTank = tanks[i].getXPosition();
			int yTank = tanks[i].getYPosition();
			int widthTank = tanks[i].getWidth();
			int heightTank = tanks[i].getHeight();

			int xBullet = bullets[j].getPosition().x;
			int yBullet = bullets[j].getPosition().y;
			int widthBullet= bullets[j].getWidth();
			int heightBullet = bullets[j].getHeight();

			if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
			{
				tanks[i].isAlive = false;
				bullets[i].isAlive = false;
			}
		}
	}

	

}

void BattleCity::GameLogic::GameLogic::checkPlayerTankEnemyBulletCollision()
{
	auto& tanks = m_playerTanks;
	auto& bullets = m_enemyBullets;

	for (int i = 0; i < tanks.size(); ++i)
	{
		for (int j = 0; j < bullets.size(); ++j)
		{
			int xTank = tanks[i].getXPosition();
			int yTank = tanks[i].getYPosition();
			int widthTank = tanks[i].getWidth();
			int heightTank = tanks[i].getHeight();

			int xBullet = bullets[j].getPosition().x;
			int yBullet = bullets[j].getPosition().y;
			int widthBullet = bullets[j].getWidth();
			int heightBullet = bullets[j].getHeight();

			if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
			{
				tanks[i].isAlive = false;
				bullets[i].isAlive = false;
			}
		}
	}

	
}

void BattleCity::GameLogic::GameLogic::checkPlayerBulletEnemyBulletCollision()
{
	auto& playerBullets = m_playerBullets;
	auto& enemyBullets = m_enemyBullets;

	for (int i = 0; i < playerBullets.size(); ++i)
	{
		for (int j = 0; j < enemyBullets.size(); ++j)
		{
			int xTank = playerBullets[i].getPosition().x;
			int yTank = playerBullets[i].getPosition().y;
			int widthTank = playerBullets[i].getWidth();
			int heightTank = playerBullets[i].getHeight();

			int xBullet = enemyBullets[j].getPosition().x;
			int yBullet = enemyBullets[j].getPosition().y;
			int widthBullet = enemyBullets[j].getWidth();
			int heightBullet = enemyBullets[j].getHeight();

			if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
			{
				playerBullets[i].isAlive = false;
				enemyBullets[i].isAlive = false;
			}
		}
	}

	
}


bool BattleCity::GameLogic::GameLogic::isCollision(int x1, int y1, int width1, int height1 , int x2, int y2, int width2, int height2)
{
	if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2) 
	{
		return true; 
	}

	return false;
}

void BattleCity::GameLogic::GameLogic::checkCollision()
{
	checkEnemyTankPlayerBulletCollision();
	checkPlayerTankEnemyBulletCollision();
	std::remove_if(m_playerTanks.begin(), m_playerTanks.end(), [](const Tank& tank) {return !tank.isAlive; });
	std::remove_if(m_enemyTanks.begin(), m_enemyTanks.end(), [](const Tank& tank) {return !tank.isAlive; });
	std::remove_if(m_enemyBullets.begin(), m_enemyBullets.end(), [](const Bullet& bullet) {return !bullet.isAlive; });
	std::remove_if(m_playerBullets.begin(), m_playerBullets.end(), [](const Bullet& bullet) {return !bullet.isAlive; });

}