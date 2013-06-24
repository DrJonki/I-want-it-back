#pragma once

#include <SFML\Graphics.hpp>

class GameButton
{
public:
	GameButton(sf::RenderWindow*);
	~GameButton(void);

private:
	sf::RenderWindow* _window;
};

