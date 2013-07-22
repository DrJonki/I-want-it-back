#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Texture.hpp>

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

