#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Event.hpp>

#include "LoadSettings.h"

class Deathmenu
{
public:
	Deathmenu(sf::RenderWindow* window, sf::Event* e);
	~Deathmenu(void);

	void showMenu();
	void draw();

private:
	sf::RectangleShape _backgroundShape;

	sf::RenderWindow* _window;
	sf::Event* _e;

	sf::Font _font;
	sf::Text _text;
};
