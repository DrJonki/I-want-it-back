#pragma once

#include <SFML\Graphics.hpp>

#include <sstream>

#include "LoadSettings.h"
#include "Globals.h"
#include "GameText.h"

class Mainmenu
{
public:
	Mainmenu(sf::RenderWindow*, sf::Event&);
	~Mainmenu(void);

	bool showMenu();
	LoadSettings getSettings();

private:
	void init();
	void update();
	void draw();

	sf::RenderWindow* _window;
	sf::Event& _e;
	LoadSettings _settings;

	sf::Font font;
};

