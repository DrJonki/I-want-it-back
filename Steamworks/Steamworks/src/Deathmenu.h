#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Event.hpp>

#include "LoadSettings.h"
#include "GameButton.h"

class Deathmenu
{
public:
	Deathmenu(sf::RenderWindow* window, sf::Event* e);
	~Deathmenu(void);

	void showMenu();
	void draw();

private:
	void init();

	sf::RectangleShape _backgroundShape;

	sf::RenderWindow* _window;
	sf::Event* _e;

	sf::Font _font;

	std::vector<GameButton> _button;

	static const enum
	{
		BUT_RESTART,
		BUT_EXIT,
		BUT_LAST
	};
};
