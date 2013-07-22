#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Audio\Music.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include <vector>

#include "EngineSettings.h"
#include "LoadSettings.h"
#include "GameButton.h"

class Mainmenu
{
public:
	Mainmenu(sf::RenderWindow*, sf::Event*);
	~Mainmenu(void);

	bool showMenu();
	LoadSettings& getLoadSettings() { return _loadSettings; };
	EngineSettings& getEngineSettings() { return _engineSettings; };

private:
	void init();
	void update();
	void draw();

	void initLevels();
	void restartVideo();

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
	static const enum
	{
		CON_APPLY,
		CON_BACK
	};


	sf::Texture titleTexture;
	sf::RectangleShape titleBackground;
	sf::Music titleMusic;
	const int titleMinAlpha;

	sf::Clock updateClock;

	static const enum
	{
		BUT_START,
		BUT_LEVEL,
		BUT_INFO,
		BUT_SETTINGS,
		BUT_CREDITS,
		BUT_EXIT,
		BUT_LAST
	};

	bool levelMenuSelected;
	int levelSelection;
	sf::Text levelMenuText;

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