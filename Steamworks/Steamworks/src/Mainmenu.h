#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>

#include <sstream>
#include <vector>
#include <cmath>

#include "EngineSettings.h"
#include "LoadSettings.h"
#include "Globals.h"
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

	void initLevels();

	sf::RenderWindow* _window;
	sf::Event* _e;
	LoadSettings _loadSettings;
	EngineSettings _engineSettings;

	sf::Font _font;
	//Main buttons
	std::vector<GameButton> mainButton;

	//Campaign
	std::vector<sf::Text> campaignText;

	//Level
	std::vector<sf::Text> levelText;

	//Settings
	std::vector<GameButton> settingButton;
	std::vector<sf::Text> settingText;

	//Credits
	sf::Text creditsText[2];

	sf::CircleShape selectionShape;
	std::vector<GameButton> confirmButton;

	sf::RectangleShape titleBackground;
	SpriteAnimation titleAnimation;
	sf::Music titleMusic;

	sf::Clock updateClock;

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

	static const enum
	{
		SET_RESOLUTION,
		SET_VSYNC,
		SET_FULLSCREEN,
		SET_AA,
		SET_SMOOTH,
		SET_GVOLUME,
		SET_MVOLUME,
		SET_SVOLUME,
		SET_AVOLUME,
		SET_LAST
	};
};