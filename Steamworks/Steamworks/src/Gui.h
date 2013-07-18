#pragma once

#include <SFML\Graphics.hpp>

#include "Globals.h"

class Gui
{
public:
	Gui(sf::RenderWindow* window);
	~Gui(void);

	void update();
	void draw();

private:
	sf::Texture _soundShapeTexture;
	sf::RectangleShape _soundShape[2];

	sf::RenderWindow* _window;
};

