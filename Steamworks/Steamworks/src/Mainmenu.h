#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio\Music.hpp>

#include <sstream>
#include <vector>

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


	sf::CircleShape selectionShape;

	sf::RectangleShape titleBackground;
	SpriteAnimation titleAnimation;
	sf::Music titleMusic;

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

	int selectionState;
	int subSelectionState;
	int subSelectionMax;
	int menuState;
};