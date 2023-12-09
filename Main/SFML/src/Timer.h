#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>

class Timer
{
private:
	sf::Font& font;
	sf::Text txt;
	sf::Clock time;

	int actualFPS, countFPS;
	bool clockON{ true };

public:

	Timer(sf::Font& font);
	void switchClock();
	void stopClock();
	void draw(sf::RenderWindow& window);
};