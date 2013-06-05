#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <Box2D\Box2D.h>

#include "Globals.h"

namespace
{
	bool exitState = false;

	sf::RenderWindow gameWindow;
	sf::Event e;

	sf::Clock updateClock;
}

void init()
{
	gameWindow.create(sf::VideoMode(g_windowWidth, g_windowHeight), "Steamworks", sf::Style::Close);
	gameWindow.setVerticalSyncEnabled(true);
	
	updateClock.restart();
}

void deInit()
{
	gameWindow.close();
}

void update()
{
	updateClock.restart();
}

void render()
{
	gameWindow.clear();

	gameWindow.display();
}

void pollEvents()
{
	while (gameWindow.pollEvent(e)){
		if (e.type == sf::Event::KeyPressed){
			exitState = true;
		}
	}
}

int main()
{
	init();

	while (!exitState){
		sf::Time updateTime = updateClock.getElapsedTime();

		if (updateTime.asMilliseconds() > 15) update();
		render();
		pollEvents();

	}

	return 0;
}