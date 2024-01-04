#include "Eagle.h"
#include "Gameconfig.h"

Eagle::Eagle() : m_position{ GameConfig::SCREEN_WIDTH / 2, GameConfig::SCREEN_HEIGHT - 100}
{

}

Position Eagle::getPosition()
{
	return m_position;
}