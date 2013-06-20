#pragma once

#include <SFML\Graphics.hpp>

#include "LoadSettings.h"
#include "Globals.h"

class Mainmenu
{
public:
	Mainmenu(sf::RenderWindow*);
	~Mainmenu(void);

	bool showMenu();
	LoadSettings getSettings();

private:

	sf::RenderWindow* _window;
	LoadSettings _settings;
};

