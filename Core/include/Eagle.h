#pragma once

#include "Position.h"

namespace BattleCity::GameLogic
{
	class Eagle
	{
	public:

		Eagle();
		Eagle(Position position);

		Position getPosition();
		void setPosition(Position position);

	private:

		Position m_position;
	};
}