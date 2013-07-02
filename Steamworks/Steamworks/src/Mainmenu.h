#pragma once

#include <SFML\Graphics.hpp>

#include <sstream>

#include "EngineSettings.h"
#include "LoadSettings.h"
#include "Globals.h"
#include "GameText.h"

class Mainmenu
{
public:
	Mainmenu(sf::RenderWindow*, sf::Event*);
	~Mainmenu(void);

	bool showMenu();
	LoadSettings getLoadSettings() { return _loadSettings; };
	EngineSettings getEngineSettings() { return _engineSettings; };

private:
	void init();
	void update();
	void draw();

	sf::RenderWindow* _window;
	sf::Event* _e;
	LoadSettings _loadSettings;
	EngineSettings _engineSettings;

	sf::Font font;
};