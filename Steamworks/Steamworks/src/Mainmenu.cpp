#include "Mainmenu.h"


Mainmenu::Mainmenu(sf::RenderWindow* window) : _window(window)
{}


Mainmenu::~Mainmenu(void)
{
	_window->close();
}


bool Mainmenu::showMenu()
{
	_window->create(sf::VideoMode(g_windowWidth, g_windowHeight), "Template title :(", sf::Style::Close);
	_window->setVerticalSyncEnabled(g_useVSync);


	return 1;
}

LoadSettings Mainmenu::getSettings()
{
	return _settings;
}