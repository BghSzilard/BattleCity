#include "Eagle.h"
#include "GameConfig.h"

namespace BattleCity::GameLogic
{
	Eagle::Eagle() : m_position{ GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT - 100 }
	{

	}

	Eagle::Eagle(Position position)
		: m_position(position) {}

	Position Eagle::getPosition()
	{
		return m_position;
	}

	void Eagle::setPosition(Position position)
	{
		m_position = position;
	}
}
