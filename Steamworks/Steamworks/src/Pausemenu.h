#pragma once

#include <SFML\Graphics.hpp>

#include "Globals.h"
#include "EngineSettings.h"
#include "GameButton.h"

class Pausemenu
{
public:
	Pausemenu(sf::RenderWindow* window, sf::Event* e, EngineSettings& esettings);
	~Pausemenu(void);

	bool showMenu(bool paused);
	void draw();

	sf::View& getView(const unsigned short view);

private:
	void update();
	void init();
	void restartVideo();
	void resetViews();

	sf::View _view[3];
	sf::View pauseView;

	sf::RenderWindow* _window;
	sf::Event* _e;

	EngineSettings _engineSettings;

	sf::Font _font;
	//Main buttons
	std::vector<GameButton> mainButton;

	//Settings
	std::vector<GameButton> settingButton;
	std::vector<sf::Text> settingText;

	sf::CircleShape selectionShape;
	std::vector<GameButton> confirmButton;

	static const enum
	{
		CON_APPLY,
		CON_BACK
	};

	sf::RectangleShape pauseBackground;

	static const enum
	{
		BUT_START,
		BUT_SETTINGS,
		BUT_EXIT,
		BUT_EXITTOWIN,
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

