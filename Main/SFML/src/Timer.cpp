#include "Timer.h"

Timer::Timer(sf::Font& font) : font{ font }, actualFPS{}, countFPS{}
{
	time.restart();
}

void Timer::switchClock()
{
	clockON = !clockON;
}

void Timer::stopClock()
{
	if (clockON)
	{
		switchClock();
	}
}

void Timer::draw(sf::RenderWindow& window)
{
	if (clockON)
	{
		countFPS = int(time.getElapsedTime().asSeconds());
		txt.setFont(font);
		txt.setCharacterSize(window.getSize().y / 24);
		txt.setFillColor(sf::Color::Red);
		txt.setString("Clock: " + std::to_string(int(countFPS)));
		txt.setPosition(float(window.getSize().x - txt.getGlobalBounds().width), float(0.0));

		window.draw(txt);
	}
}