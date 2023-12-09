#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Timer.h"

struct Window {
	int topBot;		    // empty space at the top and bottom of the screen
	int sides;		    // blank field on the left and right of the screen
	int blockSize;		// block size after reduction
	int sideMenu;		// width of the side panel
	float scale;		// scale of the block relative to its base dimension
	int widthInBlocks;	// the width of the map in blocks
};

class Map: public sf::Drawable
{
public:

	Window pr;
	Timer& GameClock;
	Sprite& spr;
	sf::RenderWindow& window;
	Map(Sprite&, Timer& FPSclock, sf::RenderWindow&);

private:

	virtual void draw(sf::RenderTarget& window, sf::RenderStates) const;
};