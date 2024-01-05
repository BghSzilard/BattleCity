#include "GameLogic.h"

#include <algorithm>

namespace BattleCity::GameLogic
{
  struct CollSize {
  	int w, h;
  };

  CollSize getCollisionSize(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
  {
  	int w = width1 + width2 + std::max(std::abs(x1 - (x2 + width2)), std::abs(x2 - (x1 + width1)));
  	int h = height1 + height2 + std::max(std::abs(y1 - (y2 + height2)), std::abs(y2 - (y1 + height1)));
  	return { w, h };
  }

  void GameLogic::checkEnemyTankPlayerBulletCollision()
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

  void GameLogic::checkPlayerTankEnemyBulletCollision()
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

  void GameLogic::checkPlayerBulletEnemyBulletCollision()
  {
  	auto& playerTanks = m_playerBullets;
  	auto& enemyBullets = m_enemyBullets;

  	for (int i = 0; i < playerTanks.size(); ++i)
  	{
  		for (int j = 0; j < enemyBullets.size(); ++j)
  		{
  			int xTank = playerTanks[i].getPosition().x;
  			int yTank = playerTanks[i].getPosition().y;
  			int widthTank = playerTanks[i].getWidth();
  			int heightTank = playerTanks[i].getHeight();

  			int xBullet = enemyBullets[j].getPosition().x;
  			int yBullet = enemyBullets[j].getPosition().y;
  			int widthBullet = enemyBullets[j].getWidth();
  			int heightBullet = enemyBullets[j].getHeight();

  			if (isCollision(xTank, yTank, widthTank, heightTank, xBullet, yBullet, widthBullet, heightBullet))
  			{
  				playerTanks[i].isAlive = false;
  				enemyBullets[i].isAlive = false;
  			}
  		}
  	}
  }

  void GameLogic::checkTankTileCollision()
  {
  	auto& playerTanks = m_playerTanks;
  	auto& enemyTanks = m_enemyTanks;

  	for (int k = 0; k < playerTanks.size(); ++k)
  	{
  		for (int i = 0; i < m_map.getWidth(); ++i)
  		{
  			for (int j = 0; j < m_map.getHeight(); ++j)
  			{
  				int xTank = playerTanks[i].getXPosition();
  				int yTank = playerTanks[i].getYPosition();
  				int widthTank = playerTanks[i].getWidth();
  				int heightTank = playerTanks[i].getHeight();

  				int xTile = i * GameConfig::MAP_TILE_SIZE;
  				int yTile = j * GameConfig::MAP_TILE_SIZE;
  				int widthTile = GameConfig::MAP_TILE_SIZE;
  				int heightTile = GameConfig::MAP_TILE_SIZE;

  				if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
  				{
  					switch (m_map.at(i, j)) {
  					case 0: // brick
  					case 1: // stone
  					case 2: // water
  					{
  						auto collSize = getCollisionSize(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile);
  						switch (playerTanks[i].getTankDirection()) {
  						case GameConfig::MoveDirection::LEFT: {
  							playerTanks[i].setPosition(xTank + collSize.w, yTank);
  							break;
  						}
  						case GameConfig::MoveDirection::UP: {
  							playerTanks[i].setPosition(xTank, yTank + collSize.h);
  							break;
  						}
  						case GameConfig::MoveDirection::RIGHT: {
  							playerTanks[i].setPosition(xTank - collSize.w, yTank);
  							break;
  						}
  						case GameConfig::MoveDirection::DOWN: {
  							playerTanks[i].setPosition(xTank, yTank - collSize.h);
  							break;
  						}
  						}
  						break;
  					}
  					default:
  						break;
  					}
  				}
  			}
  		}
  	}
  	for (int k = 0; k < enemyTanks.size(); ++k)
  	{
  		for (int i = 0; i < m_map.getWidth(); ++i)
  		{
  			for (int j = 0; j < m_map.getHeight(); ++j)
  			{
  				int xTank = enemyTanks[i].getXPosition();
  				int yTank = enemyTanks[i].getYPosition();
  				int widthTank = enemyTanks[i].getWidth();
  				int heightTank = enemyTanks[i].getHeight();

  				int xTile = i * GameConfig::MAP_TILE_SIZE;
  				int yTile = j * GameConfig::MAP_TILE_SIZE;
  				int widthTile = GameConfig::MAP_TILE_SIZE;
  				int heightTile = GameConfig::MAP_TILE_SIZE;

  				if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
  				{
  					switch (m_map.at(i, j)) {
  					case 0: // brick
  					case 1: // stone
  					case 2: // water
  					{
  						auto collSize = getCollisionSize(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile);
  						switch (enemyTanks[i].getTankDirection()) {
  						case GameConfig::MoveDirection::LEFT: {
  							enemyTanks[i].setPosition(xTank + collSize.w, yTank);
  							break;
  						}
  						case GameConfig::MoveDirection::UP: {
  							enemyTanks[i].setPosition(xTank, yTank + collSize.h);
  							break;
  						}
  						case GameConfig::MoveDirection::RIGHT: {
  							enemyTanks[i].setPosition(xTank - collSize.w, yTank);
  							break;
  						}
  						case GameConfig::MoveDirection::DOWN: {
  							enemyTanks[i].setPosition(xTank, yTank - collSize.h);
  							break;
  						}
  						}
  						break;
  					}
  					default:
  						break;
  					}
  				}
  			}
  		}
  	}
  }

  void GameLogic::checkBulletTileCollision()
  {
  	auto& playerBullets = m_playerBullets;
  	auto& enemyBullets = m_enemyBullets;

  	for (int k = 0; k < playerBullets.size(); ++k)
  	{
  		for (int i = 0; i < m_map.getWidth(); ++i)
  		{
  			for (int j = 0; j < m_map.getHeight(); ++j)
  			{
  				int xTank = playerBullets[i].getPosition().x;
  				int yTank = playerBullets[i].getPosition().y;
  				int widthTank = playerBullets[i].getWidth();
  				int heightTank = playerBullets[i].getHeight();

  				int xTile = i * GameConfig::MAP_TILE_SIZE;
  				int yTile = j * GameConfig::MAP_TILE_SIZE;
  				int widthTile = GameConfig::MAP_TILE_SIZE;
  				int heightTile = GameConfig::MAP_TILE_SIZE;

  				if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
  				{
  					switch (m_map.at(i, j)) {
  					case 0: // brick
  					{
  						playerBullets[i].isAlive = false;
  						m_map.at(i, j) = 4;
  					}
  					case 1: // stone
  					{
  						playerBullets[i].isAlive = false;
  						break;
  					}
  					default:
  						break;
  					}
  				}
  			}
  		}
  	}
  	for (int k = 0; k < enemyBullets.size(); ++k)
  	{
  		for (int i = 0; i < m_map.getWidth(); ++i)
  		{
  			for (int j = 0; j < m_map.getHeight(); ++j)
  			{
  				int xTank = enemyBullets[i].getPosition().x;
  				int yTank = enemyBullets[i].getPosition().y;
  				int widthTank = enemyBullets[i].getWidth();
  				int heightTank = enemyBullets[i].getHeight();

  				int xTile = i * GameConfig::MAP_TILE_SIZE;
  				int yTile = j * GameConfig::MAP_TILE_SIZE;
  				int widthTile = GameConfig::MAP_TILE_SIZE;
  				int heightTile = GameConfig::MAP_TILE_SIZE;

  				if (isCollision(xTank, yTank, widthTank, heightTank, xTile, yTile, widthTile, heightTile))
  				{
  					switch (m_map.at(i, j)) {
  					case 0: // brick
  					{
  						enemyBullets[i].isAlive = false;
  						m_map.at(i, j) = 4;
  					}
  					case 1: // stone
  					{
  						enemyBullets[i].isAlive = false;
  						break;
  					}
  					default:
  						break;
  					}
  				}
  			}
  		}
  	}
  }

  bool GameLogic::isCollision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
  {
  	if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2)
  	{
  		return true;
  	}

  	return false;
  }


  void GameLogic::checkCollision()
  {
  	checkEnemyTankPlayerBulletCollision();
  	checkPlayerTankEnemyBulletCollision();
  	checkPlayerBulletEnemyBulletCollision();
  	checkTankTileCollision();
  	checkBulletTileCollision();
  	std::remove_if(m_playerTanks.begin(), m_playerTanks.end(), [](const Tank& tank) {return !tank.isAlive; });
  	std::remove_if(m_enemyTanks.begin(), m_enemyTanks.end(), [](const Tank& tank) {return !tank.isAlive; });
  	std::remove_if(m_enemyBullets.begin(), m_enemyBullets.end(), [](const Bullet& bullet) {return !bullet.isAlive; });
  	std::remove_if(m_playerBullets.begin(), m_playerBullets.end(), [](const Bullet& bullet) {return !bullet.isAlive; });
  
  }
}