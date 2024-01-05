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

		std::vector<Tank> m_tanks;
		std::vector<Bullet> m_bullets;
	};
}