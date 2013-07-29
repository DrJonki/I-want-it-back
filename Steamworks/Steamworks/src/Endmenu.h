#pragma once

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System\Time.hpp>

#include "LoadSettings.h"
#include "GameButton.h"

class Endmenu
{
public:
	Endmenu(sf::RenderWindow* window, sf::Event* e, LoadSettings* lsettings);
	~Endmenu(void);

	void showMenu(float time);
	void draw();

private:
	void init();

	sf::RectangleShape _backgroundShape;

	sf::RenderWindow* _window;
	sf::Event* _e;

	LoadSettings* _lSettings;

	sf::Font _font;
	sf::Text _timeText;
	sf::Text _nextLevelText;

	static const enum
	{
		BUT_CONTINUE,
		BUT_RESTART,
		BUT_EXIT,
		BUT_LAST
	};
	std::vector<GameButton> _button;
};

