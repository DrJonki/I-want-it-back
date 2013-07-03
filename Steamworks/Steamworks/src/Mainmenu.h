#pragma once

#include <SFML\Graphics.hpp>

#include <sstream>
#include <vector>

#include "EngineSettings.h"
#include "LoadSettings.h"
#include "Globals.h"
#include "GameText.h"
#include "GameButton.h"

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

	sf::Font _font;
	std::vector<GameButton> button;

	static const enum
	{
		BUT_START,
		BUT_CAMPAIGN,
		BUT_LEVEL,
		BUT_SETTINGS,
		BUT_CREDITS,
		BUT_EXIT,
		BUT_LAST
	};
};