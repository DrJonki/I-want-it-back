#include "Mainmenu.h"


Mainmenu::Mainmenu(sf::RenderWindow* window) : _window(window)
{
	_settings._campaign = "Default";
	_settings._level = "1";
}


Mainmenu::~Mainmenu(void)
{}


bool Mainmenu::showMenu()
{
	return 1;
}

LoadSettings Mainmenu::getSettings()
{
	return _settings;
}