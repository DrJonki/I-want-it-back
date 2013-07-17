#pragma once

#include <SFML\Graphics.hpp>

#include "Globals.h"

class Pausemenu
{
public:
	Pausemenu(sf::RenderWindow* window, sf::Event* e);
	~Pausemenu(void);

	bool update();


private:
	void draw();

	sf::RenderWindow* _window;
	sf::Event* _e;
};

