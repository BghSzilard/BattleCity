#include "Tank.h"
#include "Bullet.h"

#include <vector>

namespace BattleCity::GameLogic
{
	class GameLogic
	{
	public:

		void checkCollision();

	private:

		void checkEnemyTankPlayerBulletCollision();
		void checkPlayerTankEnemyBulletCollision();
		void checkPlayerBulletEnemyBulletCollision();
		//void checkPlayerTankEnemyTankCollision();

		bool isCollision(int x1, int x2, int width1, int width2, int y1, int y2, int height1, int height2);

		std::vector<Tank> m_enemyTanks;
		std::vector<Tank> m_playerTanks;
		std::vector<Bullet> m_playerBullets;
		std::vector<Bullet> m_enemyBullets;
		
	};
}